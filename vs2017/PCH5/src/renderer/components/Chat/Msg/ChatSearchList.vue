<template>
  <div class="forward-list">
    <v-modal  cardSize="forward-class" @close="$emit('close')">
      <v-field class="forward-search"  :tipLabel="$t('chat.searchRule')" >
        <v-input class='search-input' :placeholder="$t('chat.searchTip')" :isAutoFocus="true" v-model="searchText" :position="'left'" @keydown="navigateSearchList" @keyup-esc="$emit('close')">
          <i class="icon search-icon" slot="expand">&#xe68c;</i>
        </v-input>
      </v-field>
      <transition name="slide-up" v-if="searchText==''&&(type=='card' || type=='appShare')">
        <v-tabs position="is-centered" class="search-list-tab" v-model="currentTab" @change="changeTab">
          <v-tab-item :label="$t('contacts.friends')" class="search-list-items">
            <div class="search-contact-list" ref="searchContact" @scroll.passive.stop="loadMoreData(0)">
              <v-card-list class="card-list">
                <v-card v-for="(item,index) in contactList.slice(0, initContactLength)" :key="index" :title="item.name" @click.native.stop ="handleClick(item)">
                  <v-avatar size="is-small" :title="item.name" :src="item.thumbAvatar" :sex="item.gender" :offline="false" shape="round" slot="leftAvatar"></v-avatar>
                </v-card>
              </v-card-list>
            </div>
          </v-tab-item>
          <v-tab-item :label="$t('groups.group')" class="search-list-items">
            <div class="search-contact-list" ref="searchGroup" @scroll.passive.stop="loadMoreData(1)">
              <v-card-list class="card-list">
                <v-card v-for="item in groupList.slice(0, initGroupLength)" :key="item.groupId" :title="item.groupName" @click.native.stop ="handleClick(item)">
                  <v-avatar size='is-small' :title="item.groupName" :src='item.avatar' :sex="4" :offline="false" shape="round"  slot="leftAvatar"></v-avatar>
                </v-card>
              </v-card-list>
            </div>
          </v-tab-item>
          <v-tab-item v-if="contact_isInOrg===1" :label="$t('organizations.organization')">
            <org-tab-item :isPullOrgList="isPullOrgList" :isCardSearch="true" :sendCard="handleClick"></org-tab-item>
          </v-tab-item>
        </v-tabs>
      </transition>
      <div v-else class="forward-list-box" ref="forwardList"  @scroll.passive.stop="handleScroll">
        <v-card-list>
          <v-card v-for="(item, index) in currentForWardList"
                  v-if="item.id!==user_account.userId"
                  class="box-item-active"
                  :key="index"
                  :title="item.name||item.groupName||item.remark"
                  @click.native.stop ="handleClick(item)">
                <v-avatar size='is-small'
                      :src='item.thumbAvatar||item.avatar' 
                      :sex ='item.chatType==1?item.gender:item.chatType==2?4:0'
                      :offline="false" 
                      shape="round"
                      slot="leftAvatar">
                </v-avatar>
          </v-card>
        </v-card-list >
      </div>
      <div class="list-bg" v-show="searchText" >
        <local-search v-model="searchText" :hoverIndex="hoverIndex" :isContact="type==='receipt'" :forWard="true" :openChat="openChat" @updateList="setSearchData" :direction="direction" @forwardMsg="handleClick"></local-search>
      </div>
    </v-modal>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import { msgStructure, MsgMemberCard ,MsgAppShare} from '../Msg';
import LocalSearch from '../../Account/LocalSearch.vue';
import { homedir } from 'os'
import { encryptionPassword } from '../../../../../src/comm/util.js';
import { MsgFile, MsgImg } from '../Msg.js';
import OrgTabItem from "../../Contact/ContactTab/OrgTabItem.vue";
import { converseFullPinYin } from '../../../../comm/pinyin.js';
import { getErrorMsg } from '../../../utils/utils.js'
const HANDLETYPE = {
  FORWARD: 'forward',
  CARD: 'card',
  RECEIPT: 'receipt',
  SUGGESTION: 'suggestion',
  SENDIMAGE: 'sendImg',
  MIXMSG: 'mixMsg',
  APPSHARE: 'appShare'
}
export default {
  data() {
    return {
      searchText: '',
      hoverIndex: -1,
      searchListNum: '',
      direction: 40,
      openChat: false,
      myDeviceAvatar:  require('vrv-static/resources/images/common/mydevice.png'),
      initLength: 15,
      initContactLength: 20,
      initGroupLength: 20,
      forwardList: [],
      isPullOrgList: false,
      currentTab: 0
    }
  },

  components: {
    LocalSearch,
    OrgTabItem
  },

  watch:{
    searchText() {
      this.hoverIndex = -1;
    }
  },
  created() {
    if (this.contact_isInOrg === -1) {
        this.setOrganizationList();
      }
  },
  methods: {
    // 获取组织架构数据
    setOrganizationList() {
      let getVisibleOrgUsersParam = { type: 0, orgId: 0 };
      this.$Service.enterprise.getVisibleOrgUsers(
        getVisibleOrgUsersParam,
        resp => {
          let isShow = resp.orgs && resp.orgs.length !== 0;
          this.$store.commit("SET_ORGTAB_STATUS", isShow ? 1 : 0);
        }
      );
    },
    changeTab(value) {
      this.isPullOrgList = false;
      this.$nextTick(() => {
        // 避免重复拉取组织架构数据
        if (value === 2) this.isPullOrgList = true;
      });
    },
    loadMoreData(type) {
      console.log('loadMoreData============>', type)
      let currentLength = type === 0? this.initContactLength: this.initGroupLength
      let totalLength = type === 0? this.contactList.length: this.groupList.length
      this.$nextTick(() => {
        if (this.isScrollToBottom(type===0?this.$refs.searchContact:this.$refs.searchGroup))
          if (currentLength < totalLength) {
            //是否有更多数据
            if (totalLength - currentLength < 30) {
              if (type===0) {
                this.initContactLength = totalLength;
              } else {
                this.initGroupLength = totalLength;
              }
            } else {
              if (type===0) {
                this.initContactLength += 20;
              } else {
                this.initGroupLength += 20;
              }
            }
          }
      })
    },
    /**
     * 判断滚动条滚动到底部
     * @param {*} el - 绑定的dom元素
     * @returns - 是/否
     */
    isScrollToBottom(el) {
      let [scrollTop, offsetHeight, scrollHeight] = [el.scrollTop, el.offsetHeight, el.scrollHeight];
      return !(scrollTop + offsetHeight < scrollHeight);
    },

    // * 监听滚动条
    handleScroll(e) {
      console.log('handleScroll', e)
      if (this.initLength >= this.forwardList.length) return
      if (this.isScrollToBottom(this.$refs.forwardList)) { // 滚动条置底部
        console.log("to bottom");
        let num = 20
        if (this.initLength + num > this.forwardList.length) {
          num = this.forwardList.length - this.initLength
        }
        this.initLength += num
      }
    },
    
    /** 
     * 点击确定
     * 转发 or 发送名片消息
     */
    handleClick(item) {
      switch (this.type) {
        case HANDLETYPE.SUGGESTION:
        this.sendLog(item)
        break

        case HANDLETYPE.CARD:
        this.sendCardMsg(item)
        break

        case HANDLETYPE.FORWARD:
        this.sendForwardMsg(item)
        break

        case HANDLETYPE.SENDIMAGE:
        this.sendImg(item)
        break

        case HANDLETYPE.MIXMSG:
        this.sendMixTextMsg(item)
        break

        case HANDLETYPE.APPSHARE:
        this.sendAppShareMsg(item)
        break;

        case HANDLETYPE.RECEIPT: 
        this.sendMsgAtSome(item)
        break;

        default:
        break
      }
    },
    sendMsgAtSome(item) {
      this.$dialog.confirm({
        message: this.$t('chat.notifyMember', {value: item.name||item.remark}),
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          this.$emit('at-someone', item)
        }
      })
    },
    // 发送卡片消息
    sendCardMsg(item) {
      let msg = this.hasShare 
          ?  this.$t('contacts.sendContactCard', {value: item.name||item.groupName})
          :  this.$t('chat.sendCard', {value: item.name||item.groupName})
      this.$dialog.confirm({
        message: msg,
        // message: `发送"${item.name||item.groupName}"的名片到当前聊天?`,
        // confirmText: '确定',
        confirmText: this.$t('common.confirm'),
        // cancelText: '取消',
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          console.log('sendCardMsg:::::::::')
          let msgbase = {
              fromId: this.user_account.userId,
              targetId: this.hasShare ? (item.id || item.groupId) : this.$route.query.id,
              mediaUrl: this.hasShare ? this.shareId : (item.id || item.groupId),
              isPrivateMsg: this.isEncryptMsg ? 1 : 0,
              activeType: this.isBurn ? 1 : 0,
              localId: new Date().getTime(),
              msgType: 7,
              msgId: encryptionPassword().toString(),
              // time: new Date().getTime()
          };
          let msgMemberCard = new MsgMemberCard(msgbase, 1);
          if (this.chat_chatContent[msgbase.targetId]) {
            this.$store.dispatch('SET_CHATCONTENT', msgMemberCard);
          } else {
            this.$Service.chat.sendMessage(msgbase, resp => {
              this.$Service.log(`sendCardMsg code::: ${resp.code}`)
            });
          }
          // 关闭遮罩层
          this.$emit('close');
        }
      });
    },  

    /** 发送日志 */
    sendLog(item) {
      console.log('sendLog:::')
      if(!this.isPermitSend) {
        this.$dialog.alert({
          message: '日志文件正在压缩......',
          confirmText: this.$t('common.confirm'),
          onConfirm: () => { this.$emit('close')}
        })
      } else {
        this.$emit('close');
        let fileNameIndex = 0
        if(!this.$is.isOSX) { 
          fileNameIndex = this.dbPath.lastIndexOf('\\')+1
        } else {
          fileNameIndex = this.dbPath.lastIndexOf('\/')+1
        }
        let msgbase = {
          encryptKey: encryptionPassword().toString(),
          fileName: this.dbPath.substring(fileNameIndex),
          // fileName: 'suggesitons.zip',
          filePath: this.dbPath,
          fromId: this.user_account.userId,
          localId: new Date().getTime(),
          msgType: 6,
          msgId: encryptionPassword().toString(),
          targetId: item.id||item.userId||item.groupId,
          size: this.zipFileSize,
          isResume: true,
          // time: new Date().getTime()
        }
        if (this.chat_chatContent[msgbase.targetId]) {
          let msgFile = new MsgFile(msgbase, 1);
          this.$store.dispatch('SET_CHATCONTENT', msgFile)
        } else {
          this.$Service.chat.sendAppendixMessage(msgbase, resp => {
            this.$Service.log(`suggestions code::: ${resp.code}`)
          });
        }
      }
    },

    // 发送图片
    sendImg(item) {
     
      this.$emit('close');
      console.log('sendImg')
      let imagePath = this.imgPreviewParam.imgPath.replace('file:///', '')
      let msgbase = {
        encryptKey: encryptionPassword().toString(),
        fileName: '',
        fromId: this.user_account.userId,
        localId: new Date().getTime(),
        msgType: 5,
        mainPath: imagePath,
        msgId: encryptionPassword().toString(),
        targetId: item.id||item.userId||item.groupId,
        // time: new Date().getTime().toString()
      }
      
      let msgImg = new MsgImg(msgbase, 1);
      console.log('msgImg', msgImg)
      /**
       * 如果打开过此消息 直接插入数据
       * 没打开 则压缩发送
       */
      if (this.chat_chatContent[item.id || item.userId ||item.groupId]) {
        return this.$store.dispatch('SET_CHATCONTENT', msgImg)
      } 
      this.thumbImageAndSend(msgImg, imagePath)
    },

    // 发送转发消息
    sendForwardMsg(item) {
      
      this.$emit('close');// 关闭遮罩层
      let _this = this
      this.$dialog.confirm({
        message: this.$t('chat.sendForward', {value: item.name||item.groupName}),
        // message: `是否转发给：${item.name||item.groupName}?`,
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          let forWardObject
          if (this.selectActive) {
            forWardObject = Object.assign({}, this.selectActive)
          } else {
            forWardObject = Object.assign({}, this.chat_chatContent[this.imgPreviewParam.targetId][`id_${this.imgPreviewParam.msgId}`].messageObject)
            console.log('forWardObject::::::', forWardObject)
          }
          console.log('this.selectActive', this.selectActive)
          console.log('forWardObject:::', JSON.stringify(forWardObject))
          let forwardMessageParam = { // 转发参数
              fromTargetId: forWardObject.targetId, // 转发的消息的当前targetId
              toTargetId: item.id||item.userId||item.groupId, // 转发的消息的接收targetId
              messageId: forWardObject.msgId // 转发的消息ID
          }
          let forwardMessageCb = forwardMessage => {
            this.$Service.log(`forwardMessage code::: ${forwardMessage.code}`)
            if (forwardMessage.code === 0) {
              /**
               * 设置转发Id 在对应界面 绘制对应消息
               */
              forWardObject.msgId = forwardMessage.msgId
              forWardObject.fromId = this.user_account.userId
              forWardObject.targetId =  item.id||item.userId||item.groupId
              forWardObject.time = forwardMessage.time
              forWardObject.unReadCount = 0
              forWardObject.maxUnReadCount = 0
              // 消息构造器
              let forWardmsg = msgStructure(forWardObject);
              
              this.$set(forWardmsg, 'forWardId', item.id || item.userId ||item.groupId);
              console.log('id', item.id || item.userId ||item.groupId)
              if (this.chat_chatContent[item.id || item.userId ||item.groupId]) {
                console.log('forWardmsg', forWardmsg)

                forWardmsg.messageObject.isNeedHandleUnread = true
                this.$store.dispatch('SET_CHATCONTENT', forWardmsg)
                if (forWardmsg.messageObject.msgType === 5 || forWardmsg.messageObject.msgType === 28) {
                  let result= this.$isOpenMediaMsgPreivew()
                  if (result && result.isOpen && forWardmsg.messageObject.targetId === result.mediaMsgPreivewId) {
                    console.log('image forWardmsg>>>>>')
                    // this.$ipc.send('revokeImage', {type: 1})
                    this.$ipc.send('handleSubWinMediaMsg', {winType: 'image' , operaType: 1} )
                  }
                }
              }
            } else {
              if (forwardMessage.code === -16777143) {
                this.$toast.open({duration: 1500, message: '资源已过期', position: 'is-top', type: 'is-danger'});
              }
              this.$Service.log(`forwardMessage faile:::`)
            }
          }
          this.$Service.chat.forwardMessage(forwardMessageParam, forwardMessageCb)
        }
      });
    },

    sendMixTextMsg(item) {
      this.$emit('close');
      this.$dialog.confirm({
        message: this.$t('chat.sendForward', {value: item.name||item.groupName}),
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          let message = _.values(this.mixTextMessage);
          let msgbase = {
            fromId: this.user_account.userId,
            targetId: item.id||item.userId||item.groupId,
            mVt_msg: message,
            msgType: 13,
            isNeedHandleUnread: true
          };
          this.$Service.chat.sendMessage(msgbase, resp => {
            this.$Service.log(`mixTextMessage code::: ${resp.code}`)
            if (resp.code!==0) return;
            msgbase.msgId = resp.msgId;
            msgbase.time = resp.time;
            let newMsg = msgStructure(msgbase);
            if (this.chat_chatContent[msgbase.targetId]) {
              this.$store.dispatch('SET_CHATCONTENT', newMsg);
            }
          });
        }
      })
    },
    sendAppShareMsg(item){
      console.log('sendAppShareMsg::',item);
      this.$dialog.confirm({
        message: this.$t('contacts.sendAppShare', {value: item.name||item.groupName}),
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          let msgbase = {
              fromId: this.user_account.userId,
              targetId: item.id || item.groupId,
              localId: new Date().getTime(),
              msgType: 36,
              msgId: encryptionPassword().toString(),
              body: this.appShareBody,
              time: new Date().getTime()
          };
          
          let msgAppShare = new MsgAppShare(msgbase,1);
          if (this.chat_chatContent[msgbase.targetId]) {
            this.$store.dispatch('SET_CHATCONTENT', msgAppShare);
          } else {
            this.$Service.chat.sendMessage(msgbase, resp => {
              //this.$emit('shareFinish',resp.code);
            });
          }
          // 关闭遮罩层
          this.$emit('close');
        }
      });
    },
    setSearchData(len) {
      this.searchListNum = len;
    },

    navigateSearchList(e) {
      this.openChat = false;
      if (e.keyCode === 13 && this.hoverIndex !== -1) this.openChat = true;
      if (e.keyCode !== 38 && e.keyCode !== 40) return;
      if (this.searchListNum === 0) return;
      this.direction = e.keyCode;
      if (e.keyCode === 40) {
        if (this.searchListNum - 1 > this.hoverIndex) this.hoverIndex++;
      } else if (this.hoverIndex > 0) {
        this.hoverIndex--;
      }
    },

    thumbImageAndSend(msgImg, srcPath) {
      let thumbImageInfo = this.$images.thumbImage(srcPath, true)
      let thumlSave = `${this.user_imgPath}${msgImg.messageObject.encryptKey}.jpeg`
      
      msgImg.messageObject.width = thumbImageInfo.width
      msgImg.messageObject.height = thumbImageInfo.height
      msgImg.messageObject.thumBbinary = thumbImageInfo.thumBbinary

      this.$fs.writeFile(thumlSave, thumbImageInfo.originBuffer, () => {
        msgImg.messageObject.thumbPath = !thumbImageInfo.originBuffer.length ? srcPath : thumlSave
        this.$Service.chat.sendAppendixMessage(msgImg.messageObject, res => {
          console.log('sendAppendixMessage', res)
        })
      })
    }
  },
  computed: {
    ...mapGetters(['contact_contactList', 'contact_groupList', 'user_imgPath', 'user_account', 'chat_chatContent', 'chat_chatList', 'contact_isInOrg', 'chat_objectInfo']),
    currentForWardList() {
      if (this.type==='receipt') {
        let chatObj = this.chat_objectInfo[this.$route.query.id]
        let allMember = {}
        allMember[this.id] = {
          remark: this.$t('chat.allMem'),
          thumbAvatar: this.$config.defalutAvatar[4],
          chatType: 4,
          id: this.id
        }
        this.forwardList = Object.values(Object.assign(allMember, chatObj));
        return _.slice(this.forwardList, 0, this.initLength)
      }
      let tempList = Object.values(this.chat_chatList).filter(el => {
        if (el.id === this.user_account.userId) {
          el.name = this.$t('contacts.device')
          el.thumbAvatar = this.myDeviceAvatar
        }
        return el.msgType !== 100
      });
      this.forwardList =  _.orderBy(tempList, ['isTop', 'msgTime'], ['desc', 'desc'])
      return this.forwardList.slice(0, this.initLength);
    },
    contactList() {
      return _.orderBy(
        _.filter(this.contact_contactList, e => e.id && e.isApp == 2 && e.isHidden == 2),
        val => {
          return converseFullPinYin(val.pinyin.trim());
        },
        ['asc']
      )
    },
    groupList() {
      return _.orderBy(
        _.filter(this.contact_groupList,e=>e.groupId),
        val => {
          return converseFullPinYin(val.pinyin.trim());
        },
        ['asc']
      )
    }
  },
  props: {
    selectActive: Object,
    mixTextMessage: Object,
    isMixText: Boolean,
    type: {
      type: String,
      default: 'forward'
    },
    isEncryptMsg: {
      type: Boolean,
      default: false
    },
    isBurn: {
      type: Boolean,
      default: false
    },
    isSuggestion: {
      type: Boolean,
      default: false
    },
    isPermitSend: {
      type: Boolean,
      default: false
    },
    imgPreviewParam: {
      type: Object,
      required: false,
     default: () => ({})
    },
    zipFileSize: Number | String,
    dbPath: String,
    hasShare: {
      type: Boolean,
      default: false
    },
    shareId: String,
    appShareBody:String,
    id: String
  }
}
</script>
<style lang="scss" >
.forward-class {
  width: 300px;
  height: 450px;
}
.forward-list {
  .card {
    .card-content {
      height: 2.9rem;
      padding: 0.5rem;
    }
    .avatar {
      width: 30px;
      height: 30px;
    }
  }
  &:hover {
    overflow-y: auto;
  }
  .modal-card-body {
    overflow: hidden;
    padding: 10px;
    &:hover {
      overflow: auto;
    }
    
  .forward-search {
    height: 45px;
    padding: 15px;
    box-sizing: border-box;
      .input-tip .field {
        height: 30px !important;
      }
      .input {
        font-size: $--font-size-small;
        height: 30px;
      }
    }
    
    .list-bg{
      position: absolute;
      top: 50px;
      width: 100%;
      height: 400px;
      .search-area{
        .active {
         background: #e4f1fa;
        }
        background: #e4f1fa!important;
        .sup-title{
          // background: #d1e6f7;
        }
        .card{
          &:hover{
            background: #e4f1fa;
          }
        }
      }
    }
  }
  .forward-list-box{
    overflow: hidden;
    padding: 0 10px;
    display: flex;  //fit xp
    flex-direction: column; //fit xp
    flex: 1; //fit xp
    &:hover{
      overflow-y:auto; 
    }
    .box-item-active {
      &:hover {
        background: rgba(235, 235, 235, 0.50);
      }
    }
  }
  .search-list-tab {
    height: 100%;
    overflow: hidden;
    .tab-item {
      height: 100%;
    }
    .is-centered {
      font-size: 14px;
    }
    .tab-content {
      height: calc(100% - 36px);
      .search-list-items {
        height: 100%;
        .search-contact-list {
          height: 100%;
          overflow: auto;
          .card-list {
            height: 100%;
          }
        }
      }
    }
  }
}
</style>
