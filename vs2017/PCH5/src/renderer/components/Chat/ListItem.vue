<template>
    <div class="card list-card-item">
    <!-- 置顶图标 -->
    <i class="icon chatlist-topping" v-if="item.isTop&&item.id !=='10000'">&#xe67a;</i>
    <div class="card-content" ref="card" >
      <div class="media" >
        <div class="media-left">
          <!-- 头像组件 -->
          <v-avatar ref="chatAvatar" size='is-small' :src='computedAvatar' :title='name' :sex="item.chatType==1?item.gender:item.chatType==2?4:3" shape="round"></v-avatar>
          <online v-if="hasOpenOnline && item.chatType === 1" :itemId="item.id"></online>
        </div>
        <div class="media-content">
          <div class="title" >
             <!-- 名称显示 -->
            <div class="title-left">
              <span class="title-content">{{showInfo}}
              </span>
              <!-- <i class="icon chatlist-isCompany" v-if="isCompany" v-html="$t('chat.companyContent')">&#xe6b4;</i> -->
            </div>
            
             <!-- 获取最后一条消息的发送时间 -->
            <span class="chatlist-time" v-text="getDate"></span>
          </div>
           <!-- 最后一条消息展示 -->
          <div class="subtitle" :class="{'has-at-me':item.lastAtMsgID!=='0'&& !item.state, 'all-notify':item.lastAtMsgID!=='0'&& (item.state && item.state === 2), 'rtcfile-notify':item.isRtcFile}">
            <i class="icon msg-fail-notify" v-if="item.state && item.state === 2">&#xe63b;</i>
            <!-- 如果最后有人@ 存在lastAtMsgID 则显示 -->
            <span v-if="item.unreadCount&&item.lastAtMsgID!=='0'"
                  class="notice-at-me">{{$t('chat.ATme')}}
            </span>
            <span class="contents" v-html="lastMessage"></span>
            <div class="chatlist-subscript">
            <span class="remind" v-if="item.disturbSet === 3"><i class="icon " >&#xe74c;</i></span>
            <v-badge class="chatlist-unreadcount" v-if="item.unreadCount" :max='99' :class="{'disturb-mode':item.disturbSet === 3}" :isDot='false' :value='getUnreadCount'></v-badge>
            <!-- PC 删除最近会话按钮 -->
            <i class="icon btn-chatlist-del" @click.stop="delChat(item)">&#xe650;</i>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import { getDateDiff } from '@/../comm/time'
import { getLastMessage } from './message'
import ContactMixin from '../Contact/ContactMixin';
import config from '../../../comm/config.js';
import Online from '../Common/Online';
 // const _ripple = require('../Common/Ripple.js');
export default {
  mixins: [ContactMixin],
  // directives: { Ripple: _ripple.default },
  data(){
    return {
      name: '',
      avatar:'',
      whereFrom: '',
      isCompany: false, // 是否是企业号
      myDevice:  require('vrv-static/resources/images/common/mydevice.png'),
    }
  },
  props: {
    item: Object,
    chatOnlineList: Object
  },
  components: {
    Online
  },
  computed: {

    computedAvatar() {
      if (config.defalutAvatar.includes(this.avatar)) {
        return this.avatar
      }
      let fileOperateParam = {
        filepath: this.avatar,
        type: 0
      }
      if (!this.avatar || !this.$Service.file.fileOperate(fileOperateParam)) {
        return undefined
      }
      return this.avatar
    },
    hasOpenOnline() {
      return this.$config && this.$config.account && this.$config.account.openOnlineStatus;
    },

    // 获取时间
    getDate() {
       return getDateDiff(parseInt(this.item.msgTime), 'simple')
    },

    /**
     * 显示名称
     * 如果名称为空 则取获取用户信息（人、群、机器人）
     */
    showInfo() {
      /** 系统消息 */
      if (this.item.id === '10000') {
         this.avatar = config.defalutAvatar[5]
         let system = this.$t('chat.notice')
         this.name = system
         return system
      }
      /** 我的设备 */
      if (this.item.id === this.user_account.userId) {
         this.avatar = this.myDevice
         let myDevices = this.$t('contacts.device')
         this.name = myDevices
         return myDevices
      }
      if (this.item.chatType === 1) { // 个人
     
        /**
         * 如果联系人中存在此id 则显示联系人对应名称
         * 联系人中没有此id 则使用最近会话自身携带的图片和名称
         * 如果是陌生人 最近会话中也不存在名称 调取getUserInfo 接口
         */
        let contactInfo = this.contact_contactList[this.item.id]
        if (contactInfo) {
          this.avatar = contactInfo.thumbAvatar
          this.name = contactInfo.remark||contactInfo.name
          this.isCompany = false
          return contactInfo.remark||contactInfo.name
        } else {
          this.isCompany = true
          if (this.item.name) {
              this.avatar = this.item.thumbAvatar;
              this.name =  this.item.name;
          } else {
            this.getUserInfo(this.item.id)
          }
          return this.name
        }
      } else if (this.item.chatType === 2) { // 群
       let groupInfo = this.contact_groupList[this.item.id]
        if (groupInfo) {
          this.avatar = groupInfo.avatar||''
          this.name = groupInfo.groupName
          return groupInfo.groupName
        } else {
          if (this.item.name) {
            this.avatar = this.item.thumbAvatar;
            this.name = this.item.name
            return  this.item.name
          } 
        }
      } else { // 机器人
        if (this.contact_appList[this.item.id]) {
          this.avatar = this.contact_appList[this.item.id].thumbAvatar
          this.name = this.contact_appList[this.item.id].name
          return this.contact_appList[this.item.id].name
        } else {
          if (this.item.name) {
            this.avatar = this.item.thumbAvatar;
            this.name = this.item.name;
          } else {
            this.getAppInfo(this.item.id)
          }
          return this.name
        }
      }
    },

    /**
     * 获取最后一条消息
     * 如若从其他页面跳转至 会话模块 主动获取最后一条消息
     * @param {string} targetId 传入会话对应的ID，群或者人
     * @param {number} msgId 传入查询消息的起始ID，将从该消息的下一条消息开始查询
     * @param {number} count 传入查询消息总数
     * @param {number} flag  传入上一页还是下一页 向上偏移 0；向下偏移 
     */
    lastMessage() {
      if (this.item.isRtcFile) {
        return this.$t('chat.directTransfer')
      }
      if (this.item.chatType === 2) {
        this.whereFrom = this.item.whereFrom ? `${this.item.whereFrom}: ` : ''
      } else if (this.item.chatType === 1 && this.item.id !== "10000") {
        this.whereFrom = this.item.sendUserId === this.user_account.userId?`${this.$t('chat.you')}: `:''
      }
      let getMsgcb = resp => {
        let msg = {
          targetId: resp.id, 
          msgId: 0, 
          count: 1,
          flag: 0 
        }
        this.$Service.chat.getMessages(msg, lastMsg => {
          if (lastMsg.msgs.length) {
            resp.msgType = lastMsg.msgs[0].msgType
            resp.msgProp = lastMsg.msgs[0].msgProperties
            resp.operType = lastMsg.msgs[0].activeType
            resp.lastMsg = JSON.stringify({body: lastMsg.msgs[0].body})
            resp.msgTime = parseInt(lastMsg.msgs[0].time)
          }
        })
      }
      // 1. 清空内容后whereFrom改变将引起计算属性重新获取最后一条消息内容lastMsg 2.[消息类型] 取决于 当前会话最后一条消息内容lastMsg是否为空
      // return  this.whereFrom + (this.item.lastMsg?getLastMessage(this.item, this.item.hasOwnProperty('delSign') ? getMsgcb : null):'')
      // 先判断是否为系统消息
      if(this.item.id === "10000"){
        return this.$t('msgType.100');
      }
      return  this.whereFrom + (this.item.lastMsg?getLastMessage(this.item, this.item.hasOwnProperty('delSign') ? getMsgcb : null):'')
    },

    /**
     * 获取未读数 
     * 当正处于聊天的过程中 不显示未读（将其设置为已读）
     */
    getUnreadCount() {
      return this.item.unreadCount < 100 ? this.item.unreadCount : '99'
    },
    onlineItem() {
      return this.contact_contactOnlineStateList[this.item.id]||this.chatOnlineList[this.item.id];
    },
    ...mapGetters([
      'contact_contactList',
      'contact_appList',
      'contact_groupList',
      'user_account',
      'chat_chatList',
      'contact_contactOnlineStateList'
    ]),
  },
  methods: {
    /**
     * 设置消息已读
     * @param {string} targetId
     * @param {string} msgId
     */
    setMessageRead(item) {
      let setMessageReadParam = {
          targetId: item.id,
          msgId: item.msgId
      }

      this.$Service.chat.setMessageRead(setMessageReadParam, resp => {})
    },

    /**
     * 删除最近会话
     * @param {string} targetId 删除会话人的Id
     */
    delChat(item) {
      if (item.delSign === '') { //此时为手动添加的最近会话

        this.$store.dispatch('SET_CHATLIST', { flag: 32, chats: [item] });

      } else {
        let removeChatParam = { targetId: item.id };

        let removeChatCb = resp => this.$store.dispatch('SET_CHATLIST', { flag: 32, chats: [item] });

        this.$Service.chat.removeChat(removeChatParam, removeChatCb);
      }
      this.$store.commit('DEL_CHATCONTENT_BYID', item.id)
      this.$store.commit('DEL_CHAT_OBJECT', item.id)
      if (this.$route.query.id ===  item.id) { 
        this.$router.push('/Chat');
      }
    },

    getAppInfo(id) {
      let getAppInfoParam = { appId: id };
        let getAppInfoCb = resp => {
          if (resp.info.appName && this.chat_chatList[id]) {
            console.log('getAppInfo', resp)
            this.$store.dispatch('UPDATE_CHATLIST', { id:id, thumbAvatar:resp.info.appIcon, isTop:0, name:resp.info.appName })
          } else {
            this.avatar = '';
            this.name = '';
          }
      }
        this.$Service.user.getAppInfo(getAppInfoParam, getAppInfoCb);
    },

    getUserInfo(id) {
      let getUserInfoParam = { userId: id };
      let getUserInfoCb = successRes => {
        /**因为计算属性 如果successRes.users.name为'' 会无限调取接口 防止这种特殊情况做的处理 */
        if (successRes.users.name && this.chat_chatList[id]) {
          console.log('getUserInfoCb', successRes)
          this.$store.dispatch('UPDATE_CHATLIST', { id: id, thumbAvatar:successRes.users.thumbAvatar, isTop:0, name:successRes.users.name })
        } else {
          this.avatar = '';
          this.name = '';
        }
      } 
      this.$Service.search.getUserInfo(getUserInfoParam, getUserInfoCb)
    }
  }
}
</script>
<style lang="scss" scoped>
.list-card-item {

  .chatlist-topping {
    position: absolute;
    left: -3px;
    top: -3px;
    transform: rotate(-90deg);
    font-size:$--font-size-mid;
    color: get-grey-color(lighten-1);
  }
  
  .card-content {
    height: 3.8rem;
    padding: 0.5rem;
    
    .title-left {
      display: flex;
      align-items: center;
      max-width: 75%;
      .title-content {
        @include ellipsis;
       
      }
       .chatlist-isCompany {
          font-size:$--font-size-mid;
          color: $--color-msg-prompt-low;
          font-size: 14px;
          width: 10px;
          height: 13px;
          background: #fff;
          margin-left: 6px;
          border-radius: 15px;
          // margin-top: 3px;
        }
    }
     .has-at-me {
    .contents {
      width: 48%;
    }
    }

    .all-notify {
      .contents {
        width: 28%;
      }
    }

    .rtcfile-notify {
      .contents {
        color: $--color-msg-prompt-middle;
      }
    }



    .chatlist-subscript {
      display: flex;
      position: absolute;
      right: 4px;
      margin-top: 2px;
    }
    
    .chatlist-time {
      font-size: 0.7rem;
      font-weight: 500;
      margin-right: 4px;
    }

    .chatlist-unreadcount {
      font-weight: 500;
      margin-left: 2px;
    }

    .disturb-mode {
      background: $--color-msg-prompt-low;
    }

    &:hover .chatlist-unreadcount {
      display: none;
    }

    &:hover .remind {
      display: none;
    }

    .btn-chatlist-del {
      display: none;
      position: absolute;
      right: -6px;
      top: -2px;
      font-size:$--font-size-big;
      &:hover {
        cursor: pointer;
      }
    }
    .remind {
      border-radius: $--border-radius-circle;
      display: flex;
      justify-content: center;
      align-items: center;
      width: 16px;
      position: absolute;
      left: -15px;
      top: -4px;
      .icon{
        font-size:$--font-size-primary;
        color: get-grey-color(lighten-1);;
      }
    }
    .notice-at-me {
      color: $--color-msg-prompt-middle;
      font-size: $--font-size-small;
      font-weight: 500;
      white-space: nowrap;
    }
    .msg-fail-notify {
      color: $--color-msg-prompt-danger;
    }
  }
  &:hover .btn-chatlist-del {
    display: block;
  }
}
</style>
