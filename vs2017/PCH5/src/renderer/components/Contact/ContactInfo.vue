<template>
  <div class="router-detail">
    <card-lists 
      :lists="contactInfoItem" 
      :img="contactInfo.thumbAvatar&&contactInfo.thumbAvatar.replace(/\\/g, '\\\\')" 
      :name="contactInfo.remark||contactInfo.name"
      :gender="contactInfo.gender"
      :dialList="dialList"
      :qrcode="qrcode"
      @icon-click="handleIconClick"
      @click-button="handleButtonClick">
      <div slot="contact-invisiable" class="contact-invisiable" v-if="isContactInvisiable">
        <span class="icon visiable-icon-text">&#xe610;</span>
        <p class="visiable-text">{{ $t('contacts.visiableInfo')}}</p>
      </div>
    </card-lists>
    <chat-search-list v-if="isShare" type='card' :shareId="$route.query.id" :hasShare="true" @close="isShare=false"></chat-search-list>
  </div>
</template>
<script>
import _ from 'lodash';
import CardLists from '../Common/CardLists/index.vue';
import { mapGetters } from 'vuex';
import mixin from './ContactMixin.js';
import chatSearchList from '../Chat/Msg/ChatSearchList';
import { isWinXp } from '../../../comm/is';
export default {
  components: {
    CardLists,
    chatSearchList
  },
  data() {
    return {
      contactInfoItem: [],
      dialList: [
        { id:'msg', icon: '&#xe68d;', color: '#4caf50', tooltip: this.$t('contacts.message') },// 0
        { id: 'edit', icon: '&#xe67c;', color: '#3f51b5', tooltip: this.$t('contacts.edit') }, // 1
        { id: 'add', icon: '&#xe62c;', color: '#3f51b5', tooltip: this.$t('organizations.addFriend') },// 2 
        { id: 'delete', icon: '&#xe61a;', color: '#f44336', tooltip: this.$t('contacts.delete') },// 3
        { id: 'share', icon: '&#xe6d9;', color: '#009688', tooltip: this.$t('contacts.share') }// 4
      ],
      qrcode: {},
      orgUserInfo: {},
      isShare: false,
      orgName:'',
      isContactInvisiable: false
    }
  },
  created(){

  },
  mixins: [mixin],
  computed: {
    ...mapGetters([
      'contact_contactList', 
      'http_head', 
      'user_usever', 
      'user_serverHost',
      'contact_enterpriseDicValues'
    ]),
    contactInfo() {
      return this.contact_contactList[this.$route.query.id]||this.orgUserInfo;
    }
  },
  watch: {
    $route: {
      handler: 'getUserFullInfo',
      immediate: true
    },
    contact_contactList(value) {
      if (value[this.$route.query.id]&&value[this.$route.query.id].flag !== 2) return;
      // 更新卡片信息：头像、性别
      this.contactInfoItem[0].title = value[this.$route.query.id].name;
      this.contactInfoItem[1].title = (value[this.$route.query.id].gender === 1 && this.$t('contacts.male')) || (value[this.$route.query.id].gender === 2 && this.$t('contacts.female')) || this.$t('account.secret');
      // 更新二维码信息：头像、性别
      console.log('i get qrcode: ', this.contact_enterpriseDicValues.isLocalHost);
      this.$Service.log(`i get qrcode:::${this.contact_enterpriseDicValues.isLocalHost}`);
      this.qrcode = {
        id: this.$route.query.id, 
        gender: value[this.$route.query.id].gender,
        host: this.contact_enterpriseDicValues.isLocalHost,
        elogo: this.user_usever, 
        serverhost: this.user_serverHost,
        type: 1
      }
    }
  },
  methods: {
    getUserFullInfo() {
      if (this.$route.name !== 'ContactInfo') return;
      this.$nextTick(()=>{
        this.contactInfoItem = [];
        this.getUserBaseInfo();
        if(this.$route.query.item.contactInvisiable){
          // 不显示详情
          this.isContactInvisiable = true;
          return;
        }
        this.isContactInvisiable = false;
       // this.getExtendConfig(102);
       // this.getUserExtendInfo(this.$route.query.id);
      });
    },
    getExtendConfig(parentId){
      this.$Service.contact.queryExtendedField(
        { parentId: parentId, dicKey : '' },
        resp => {
          let basicExtend = resp.EnterpriseDictionarys;
          basicExtend.forEach((e, index) => {
            let extend;
            try {
              extend = JSON.parse(e.extend);
            } catch (error) {
              
            }
            let tempObj = {
                key: 'extend',
                content: this.$t(`loginType.${e.dickey}`) === `loginType.${e.dickey}`?e.dicValue: (this.$t(`loginType.${e.dickey}`)|| e.dicValue),
                title: e.account||this.$t('groups.empty'),
                type: parentId===66? e.dickey:e.id,
            }
            if(extend.isShow===1&&extend.isFriend===1)
              this.contactInfoItem.push(tempObj);
          });

        });
    },
    /**
     * 获取联系人扩展信息
     * 快速切换时联系人扩展信息叠加：调用接口时定义中间变量，得到完整数据后回调存到vuex
     * 快速切换时联系人扩展信息显示错乱：添加id作为指针指向需要保存的数据
     */
    getUserExtendInfo(id, callback) {
      console.log('进入联系人扩展信息',id)
  
      this.$Service.enterprise.queryEntUserOneById({ userId: id+'', flag: 0 }, resp => {
        console.log('获取用户扩展字段json', resp);
        if (resp.code!==0 || resp.users.length===0) return;
        if (this.$route.query.hasOwnProperty('item') && this.$route.query.item.hasOwnProperty('isOrg') && this.$route.query.item.isOrg) {
          this.getOrgName(resp.users[0].orgID);
        }
        let result = JSON.parse(resp.users[0].extend);
        _.forEach(result, (value, key) => {
          this.$Service.contact.queryExtendedField({parentId:-2,dicKey:key}, resp=>{
            let extend;
            try {
              extend = JSON.parse(resp.EnterpriseDictionarys[0].extend);
            } catch (error) {  
            }
            console.log(`查字典--key(${key})对应的value:`, resp);
            if(resp.EnterpriseDictionarys && resp.EnterpriseDictionarys.length!==0) {
              if (!this.contact_contactList[this.$route.query.id]) { // 组织架构是否可见
                if (extend.isShow===1) {
                  this.addContactExtendItem(resp, value)
                }
              } else {
                if (extend.isFriend===1) { // 好友是否可见
                  this.addContactExtendItem(resp, value)
                }
              }
            }
          });
        });
      });
    },
    getOrgName(orgId){
      this.$Service.enterprise.getOrgInfo({ orgId, flag: 0}, resp => {
        if(resp.code === 0){
          let org = Object.assign({}, resp.org);
          console.log("组织名为：",org.remark)
          let index = _.findIndex(this.contactInfoItem, function(o) { return o.key === 'orgName'; });
         if(!isWinXp) {
            this.$set(this.contactInfoItem[index], 'title', org.remark);
         }
        }
      })
    },
    /**
     * 添加好友/组织成员扩展字段
     */
    addContactExtendItem(resp, value) {
      let tempObj ={
        key: 'extend',
        content: resp.EnterpriseDictionarys[0].dicValue,
        type: resp.EnterpriseDictionarys[0].id,
        title: value!=='[]'?value:''
      }
      this.contactInfoItem =  _.filter(this.contactInfoItem, element => element.type !== tempObj.type )
      if(!tempObj.title)  tempObj.title= this.$t('groups.empty');
      this.contactInfoItem.push(tempObj);
    },
    /**
     * 联系人/组织成员基础信息
     */
    getUserBaseInfo() {
    //  if (this.$route.query.id !== this.user_account.userId) {
      //    // 增加组织架构单向圈禁止聊天
      //    this.dialList[0].isHidden = this.$route.query.item.hasOwnProperty('allowChat')? !this.$route.query.item.allowChat:false;
      //    if (!this.contact_contactList[this.$route.query.id]) {
      //      this.dialList[2].isHidden = false;
      //      this.dialList[1].isHidden = this.dialList[3].isHidden = true;
      //      this.$Service.search.getUserInfo({ userId: this.$route.query.id }, resp=>this._handleContactInfoCb(resp.users, false));
      //    } else {
      //      this.dialList[2].isHidden = true;
      //      this.dialList[1].isHidden = this.dialList[3].isHidden = false;
      //      // this._handleContactInfoCb(this.contactInfo)
      //      this.$Service.contact.getContactInfo({ userId: this.$route.query.id }, resp=>this._handleContactInfoCb(resp));
      //    }
      //  } else {
        //this.dialList.forEach(e=>e.isHidden=true);
        // this.$Service.search.getUserInfo({ userId: this.$route.query.id },extendsResp => {
          // this.$Service.contact.getContactInfo({ userId: this.$route.query.id }, res=>this._handleContactInfoCb(res,extendsResp));
    //})
        this.$Service.search.getUserInfo({ userId: this.$route.query.id }, extendsResp=>this._handleContactInfoCb(extendsResp));
        this.dialList[0].isHidden = false;
        this.dialList[1].isHidden = true;
        this.dialList[2].isHidden = true;
        this.dialList[3].isHidden = false;
        this.dialList[4].isHidden = true;
        // this._handleContactInfoCb(this.user_account, false)
      //}
    },
    /**
     * 构造联系人/组织成员卡片数据对象
     */
    _handleContactInfoCb(extendsResp,isFriend=true) {
    // _handleContactInfoCb(res, extendsResp,isFriend=true) {
      console.log('jieguo:::::',extendsResp)
      let resp = extendsResp.users;// 普通的值
      let entExtends = JSON.parse(extendsResp.users.entExtends)[0]//扩展字段中的值

      console.log('entExtends',entExtends)
      // console.log(`${isFriend?'联系人':'组织成员信息'}`, res)
      // if(!isFriend) this.orgUserInfo = res;
      // if(this.$route.query.item.contactVisiable){
      //   return
      // }
      if(entExtends.type == 0){
        this.contactInfoItem.push(
        { key: 'name', title: resp.name, content:this.$t('contacts.name') },
        { key: 'gender', title: entExtends.gender||this.$t('account.secret'), content: this.$t('contacts.gender')},
        { key: 'CommitteeMember',title: entExtends.memberNum, content:this.$t('cppcc.CommitteeMember')},
        { key: 'national' ,title: entExtends.nation, content:this.$t('cppcc.national')},
        { key: 'post' ,title: entExtends.specialCommitteeDuty, content:this.$t('cppcc.post')},
        { key: 'circles',title: entExtends.sector, content:this.$t('cppcc.circles')},
        { key: 'group' ,title: entExtends.group, content:this.$t('cppcc.group')},
        { key: 'specialCommittee' ,title: entExtends.specialCommittee, content:this.$t('cppcc.specialCommittee')},
        { key: 'positionCommittee',title: entExtends.specialCommitteeDuty, content:this.$t('cppcc.positionCommittee')},
        { key: 'incumbentDuties' ,title: entExtends.specialCommitteeDuty, content:this.$t('cppcc.incumbentDuties')},
        { key: 'location' ,title: entExtends.myLocation, content:this.$t('cppcc.location')}
         //{ key: 'phone', title: resp.phones.length!==0 && resp.phones[0] && resp.phones[0].substring(4) ||  this.$t('groups.empty'), content: this.$t('contacts.phone'), icon: {left: '&#xe6fa;', right: ''} },
         //{ key: 'email', tooltip: this.$t('contacts.sendEmail'), title: resp.emails.length!==0 && resp.emails[0] || this.$t('groups.empty'), content: this.$t('contacts.email'), icon: {left: '&#xe68a;', right: ''} },
        )
      }else{
         this.contactInfoItem.push(
        { key: 'name', title: resp.name, content:this.$t('contacts.name') },
        { key: 'gender', title:entExtends.gender||this.$t('account.secret'), content: this.$t('contacts.gender')},
        { key: 'national' ,title: entExtends.nation, content:this.$t('cppcc.national')},
        { key: 'company' ,title: entExtends.specialCommitteeDuty, content:this.$t('cppcc.company')},
        { key: 'circles',title: entExtends.sector, content:this.$t('cppcc.department')},
        { key: 'group' ,title: entExtends.group, content:this.$t('cppcc.position')},
        )
      }
      
      if(this.$route.query.item.isOrg){
        this.contactInfoItem.push(
          { key: 'orgName', title: '', content: this.$t('organizations.org'), icon: {left: '&#xe6c5;', right: ''}, rows: true},
        )
      }
     // this.getUserContactInfo()
      // 组织成员--职位
      // this.$route.query.item.isOrg && this.addContactItem(1, this.$t('organizations.position'), [this.$route.query.item.duty||this.$t('groups.empty')])
      // 组织成员--账号状态 1：正常 2：停用
      // this.addContactItem(this.$route.query.item.status, this.$t('organizations.accountStatus'), [this.$t('organizations.normal'), this.$t('organizations.disabled'), this.$t('organizations.inactive')])
      // 组织成员--业务状态 1：初始状态，2：在高管群
      // this.addContactItem(this.$route.query.item.bizStatus, this.$t('organizations.businessStatus'), [this.$t('organizations.defaultStatus'), this.$t('organizations.executives')])
      console.log('i get qrcode: ', this.contact_enterpriseDicValues.isLocalHost);
      this.qrcode = {
        id: resp.id, 
        gender: resp.gender,
        host: this.contact_enterpriseDicValues.isLocalHost,
        elogo: this.user_usever, 
        serverhost: this.user_serverHost,
        type: 1
      }
      console.log('$initInfo========>', this.$initInfo)
    },
    /**
     * 获取好友的联系方式
     */
    getUserContactInfo() {
      this.$Service.search.getUserInfo({ userId: this.$route.query.id }, resp=>{
        console.log('resp::::', resp)
        try {
          let contact = JSON.parse(resp.users.extends)[0];
          if(contact.contactPhones){
            this.contactInfoItem.push({ key: 'phone', title: contact.contactPhones.split(',')[0], content: this.$t('contacts.phone'), icon: {left: '&#xe6fa;', right: ''} })
          }
          if(contact.contactEmails){
            this.contactInfoItem.push({ key: 'email', tooltip: this.$t('contacts.sendEmail'), title: contact.contactEmails.split(',')[0], content: this.$t('contacts.email'), icon: {left: '&#xe68a;', right: ''} })
          }
        } catch (error) {
          console.log('解析extends出错')
        }
      });
    },
    /**
     * 组织成员附加信息
     * @param {Number} key -附加信息原始的key值
     * @param {String} name -附加信息新的key值
     * @param {Array} info -附加信息key键对应的value值
     */
    addContactItem(key, name, info) {
      if (!key) return;
      this.contactInfoItem.push({ key: 'org', title: info[key-1], content: name, icon: {left: '', right: ''} },)
    },
    /**
     * 修改联系人备注
     */
    changeRemark() {
      this.$dialog.prompt({
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        inputAttrs: {
          placeholder: this.contactInfo.remark||this.contactInfo.name,
          maxlength: 20,
          value: this.contactInfo.remark||this.contactInfo.name
        },
        // required: true,
        onConfirm: value => {
          let info = { id: this.$route.query.id+'',remark: value.trim() };
          this.$Service.contact.updateContactInfo(info, resp => {
            console.log('更新备注返回：' + JSON.stringify(resp));
          });
        }
      });
    },
    handleIconClick(item) {
      if (item.key !== 'email' || item.title === '未填写') return;
      // this.$toast.open({
      //   message:'邮箱启动中...',
      //   type: 'is-success'
      // });
      this.$Service.config.launchOtherApp({
        path:`mailto:${item.title}`,
        runByAdmin:false,
        startParam:''
      });
    },
    shareToChat() {
      this.isShare = true;
    },
    handleButtonClick(index) {
      let contactActions = {
        0: () => this.startChat(this.contactInfo, 1),
        1: () => this.changeRemark(),
        2: () => this.addFriend(this.contactInfo.id, this.contactInfo.name),
        3: () => this.removeContact(this.contactInfo.id, true),
        4: () => this.shareToChat()
      }
      contactActions[index].call(this)
    }
  }
}
</script>



<style lang="scss" scoped>
/deep/ .card-item-content .default-content{
  height: 100%;
}
/deep/ .v-divder{
    display: none !important;
}
/deep/ .media-left{
  margin-right: 0px;
}
/deep/ .media-content{
  flex-direction: row !important;
  justify-content:flex-start;
  
  .title{
    width: 30%;
    padding-right: 15px;
    display: inline-block;
    margin-bottom: 0px; 
  }
  .subtitle{
    line-height: 32px;
    display: inline-block;
  }
}
.contact-invisiable {
  height:100%;
  width: 100%;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  .visiable-icon-text{
    font-size: 40px;
    &:hover{
      cursor: default;
    }
  }
  .visiable-text{
    margin-top: 20px;
    margin-bottom: 20px;
  }
}
</style>
