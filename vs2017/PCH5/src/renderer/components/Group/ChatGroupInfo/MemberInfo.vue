<template>
  <div class="card-modal" v-if="isLoadFinished">
    <div class="modal-background" @click="isLoadFinished=false"></div>
    <card-lists 
      v-if="memberInfoItem.length!==0"
      class="member-lists"
      :lists="memberInfoItem" 
      :dialList="dialList"
      :qrcode="qrcode"
      :gender="item.gender||0"
      :img="item.thumbAvatar&&item.thumbAvatar.replace(/\\/g, '\\\\')" 
      :name="item.remark||item.name"
      @click-button="handleButtonClick">
    </card-lists>
  </div>
</template>
<script>
import CardLists from '../../Common/CardLists/index.vue';
import { mapGetters } from 'vuex';
import mixin from '../../Contact/ContactMixin.js';
export default {
  data() {
    return {
      isShowModal: true,
      memberInfoItem: [],
      dialList: [
        { id:'msg', icon: '&#xe68d;', color: '#4caf50', tooltip: this.$t('contacts.message')},
        { id: 'delete', icon: '&#xe61a;', color: '#f44336', tooltip: this.$t('contacts.delete')}, 
        { id: 'add', icon: '&#xe62c;', color: '#3f51b5', tooltip: this.$t('organizations.addFriend')}
      ],
      qrcode: {},
      isLoadFinished: false,
      item: {}
    }
  },
  mixins: [mixin],
  components: {
    CardLists
  },
  // props: {
  //   item: Object
  // },
  computed: {
    allowChat() {
      let extend = this.contact_groupExtension[this.$route.query.id];
      return extend && extend.disallowStrangerChat && extend.disallowStrangerChat == 0
    },
    ...mapGetters([
      'contact_contactList', 
      'http_head', 
      'contact_groupExtension', 
      'user_usever', 
      'user_serverHost',
      'contact_enterpriseDicValues'
    ])
  },
  watch: {
    $route() {
      this.isLoadFinished = false;
    }
  },
  created() {
    this.$signalMonitor.$on('expendMemberInfo', this.expendMemberInfo);
  },
  beforeDestroy() {
    this.$signalMonitor.$off('expendMemberInfo', this.expendMemberInfo);
  },
  methods: {
    expendMemberInfo(value) {
      this.isLoadFinished = true
      this.memberInfoItem = []
      this.item = value
      // 创建二维码
      this.createQrcode(value)
      // 创建详情页cardList
      this.getUserBaseInfo();
      this.getUserExtendInfo();
    },
    getUserBaseInfo() {
      if (this.item.id !== this.user_account.userId) {
        if (!this.contact_contactList[this.item.id]) {
          this.dialList[0].isHidden = !this.allowChat;
          this.dialList[1].isHidden = true;
          this.dialList[2].isHidden = false;
        } else {
          this.dialList[0].isHidden = false;
          this.dialList[1].isHidden = false;
          this.dialList[2].isHidden = true;
        }
      } else {
        this.dialList[1].isHidden = this.dialList[2].isHidden = true;
      }
      this.getMemberInfo(this.item)
    },
    getUserExtendInfo() {
      this.$Service.enterprise.queryEntUserOneById({ userId: this.item.id, flag: 0 }, resp => {
        console.log('获取用户扩展字段json', resp);
        if (resp.code!==0 || resp.users.length===0) return;
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
              if (!this.contact_contactList[this.item.id]) { // 非好友是否可见
                if (extend.isShow===1) {
                  this.memberInfoItem.push({
                    content: resp.EnterpriseDictionarys[0].dicValue,
                    title: value
                  });
                }
              } else {
                if (extend.isFriend===1) { // 好友是否可见
                  this.memberInfoItem.push({
                    content: resp.EnterpriseDictionarys[0].dicValue,
                    title: value
                  });
                }
              }
            }
          });
        });
      });
    },
    getMemberInfo(resp) {
      this.memberInfoItem.push(
        { title: resp.name, content: this.$t('contacts.name'), icon: {left: '&#xe630;', right: ''} },
        { title: (resp.gender === 1 && this.$t('account.male')) || (resp.gender === 2 && this.$t('account.female')) || this.$t('account.secret'), content: this.$t('user.sex'), icon: {left: '&#xe68b;', right: ''} },
        // { title: resp.phones.length!==0 && resp.phones[0] && resp.phones[0].substring(4) || this.$t('groups.empty'), content: this.$t('contacts.phone'), icon: {left: '&#xe6fa;', right: ''} },
        // { title: resp.emails.length!==0 && resp.emails[0] || this.$t('groups.empty'), content: this.$t('user.email'), icon: {left: '&#xe68a;', right: ''} },
      )
      if(this.contact_contactList[this.item.id]) {
        this.getUserContactInfo()
      }
    },
    getUserContactInfo() {
      this.$Service.search.getUserInfo({ userId: this.item.id }, resp=>{
        console.log('resp::::', resp)
        try {
          let contact = JSON.parse(resp.users.extends)[0];
          if(contact.contactPhones){
            this.memberInfoItem.push({ key: 'phone', title: contact.contactPhones.split(',')[0], content: this.$t('contacts.phone'), icon: {left: '&#xe6fa;', right: ''} })
          }
          if(contact.contactEmails){
            this.memberInfoItem.push({ key: 'email', tooltip: this.$t('contacts.sendEmail'), title: contact.contactEmails.split(',')[0], content: this.$t('contacts.email'), icon: {left: '&#xe68a;', right: ''} })
          }
        } catch (error) {
          console.log('解析extends出错')
        }
      });
    },
    createQrcode({id, avatar, gender}) {
      console.log('i get qrcode: ', this.contact_enterpriseDicValues.isLocalHost);
      this.qrcode = { 
        id, gender,
        address: this.http_head.preLoginAddress, 
        userver: this.$userver, 
        type: 1
      }
      this.qrcode = {
        id, gender,
        host: this.contact_enterpriseDicValues.isLocalHost,
        elogo: this.user_usever, 
        serverhost: this.user_serverHost,
        type: 1
      }
    },
    handleButtonClick(index) {
      switch (index) {
        case 0: // 发送消息
          this.startChat(this.item, 1)
          this.isLoadFinished = false;
          break;
        case 1: // 删除好友
          this.removeContact(this.item.id);
          break;
        case 2: // 添加好友
          this.addFriend(this.item.id, this.item.name);
          break;
        default:
          break;
      }
    }
  }
}
</script>
<style lang="scss">
.card-modal {
  bottom: 0;
  left: 0;
  right: 0;
  top: 0;
  align-items: center;
  justify-content: center;
  overflow: hidden;
  position: fixed;
  @include z-index(modal);
  width: 100%;
  display: flex;
  .member-lists {
    width: 34% !important;
  }
}
</style>


