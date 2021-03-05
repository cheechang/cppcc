<template>
  <div class="model-container-layout">
    <!-- 最近会话列表 -->
    <chatList class="model-container-left chat-list" :isShowAnimate="isShowAnimate" :class="{'chat-list-65': isListResize_65, 'chat-list-180': isListResize_180, 'chat-list-226': isListResize_226}" id="test" ref="test"></chatList>
    <div class="contact-drag-line" @mousedown="bindResize"></div>
    <!-- 路由区域 为消息展示区 -->
    <keep-alive  exclude="ChatSystem">
      <div class="home-detail-content">
        <div :class="{'home-detail-top-win':!$is.isOSX}"></div>
        <router-view  class="model-container-right" :style="{height:!$is.isOSX? 'calc(100% - 27px)':'100%'}"></router-view>
      </div>
    </keep-alive>

    <!-- -----------------识别好友/群二维码，显示对应卡片详情------------ -->
    
    <!-- 联系人卡片详情页 -->
    <contact-info v-if='isShowContactInfo' @close="isShowContactInfo=false"></contact-info>
    <!-- 群卡片详情页 -->
    <v-modal  cardSize="group-info-area" v-if='isShowGroupInfo'  @close="isShowGroupInfo=false">
      <group-info :isNotAllowMsg="true" :qrcodeId="qrcodeId"></group-info>
    </v-modal>
  </div>
</template>
<script>
import chatList from './ChatList.vue';
import { mapGetters } from 'vuex';
import { msgStructure } from './Msg';
import MsgMxin from './msgMixin.js'
import ContactMixin from '../Contact/ContactMixin.js';
import GroupMixin from "../Group/GroupMixin";
const { remote } = require('electron');
const getWindowStatus = remote.getGlobal('getWindowStatus')
const SCREENDISPLAY = {
  NORMAL: 'NORMAL',
  HIDE: 'HIDE',
  AUTO: 'AUTO'
}
const SOUND_REMIND = {
  OPEN : 'OPEN',
  CLOSE: 'CLOSE'
}

// 引入mockjs
// const Mock = require('mockjs');
// 获取 mock.Random 对象
// const Random = Mock.Random;
export default {
  data() {
    return {
      isShowAnimate: false,
      x: 0,
      y: 0,
      isListResize_226: false,
      isListResize_180: false,
      isListResize_65: false,

      isShowContactInfo: false,
      isShowGroupInfo: false,
      qrcodeId: ''
    };
  },
  mixins: [MsgMxin, ContactMixin, GroupMixin],
  created() {
    console.log('chat created')
    /** 注册监听：查看大图>右键>识别二维码，加好友/群 */
    this.$ipc.on("addfriend-by-qrcode", this.addFriendOrGroup);
    this.loadChatListData(); // 注册监听 拉取数据
    /**注册插件消息弱提示推送 */
    this.$Service.rtcplugin.regRTCWeakTipsCallBack(resp=>{
        console.log('regRTCWeakTipsCallBack:',resp);
        if (!this.chat_chatContent[resp.targetId]) return
        this.setMsgFromMainProcess(resp);
    })
  },
  beforeDestroy() {
    this.$ipc.removeListener("addfriend-by-qrcode", this.addFriendOrGroup)
    this.$ipc.removeAllListeners(['screenShot']);
  },
  
  methods: {
    /**
     * 解密图片二维码成功后，执行添加好友/群操作
     * @param {String} arg - 二维码链接
     */
    addFriendOrGroup(e, arg) {
      console.log('arg::::', arg)
      if(arg.includes(this.user_account.userId)){
        return;
      }
      arg = arg.split('&')[0]
      this.qrcodeId = arg.substring(arg.lastIndexOf('=') + 1)
      // 判断是好友？群？
      let isUserType = arg.indexOf('user') !== -1
      if (!isUserType) {
        this.isShowContactInfo = false
        if (!this.contact_groupList[this.qrcodeId]) {
          this.addGroup(this.qrcodeId)
        } else {
          this.isShowGroupInfo = true
        }
      } else {
        this.isShowGroupInfo = false
        if (!this.contact_contactList[this.qrcodeId]) {
          this.addFriend(this.qrcodeId)
        } else {
          this.isShowContactInfo = true
          setTimeout(() => {
            this.$signalMonitor.$emit('expendChatMemberInfo', this.contact_contactList[this.qrcodeId]);
          }, 0)
        }
      }
      
    },
    loadChatListData() {
      /**
       * 获取用户聊天图片储存地址
       * 获取用户聊天文件存储地址
       * 获取用户聊天音频存储地址
       * 获取用户聊天微视频存储地址
       */
      /*this.$Service.config.userImgPath(null, resp => {
        this.$Service.log(`userImgPath:::  ${resp.path}`)
        this.$store.commit('UPDATE_IMG_PATH', resp.path);
      });
      this.$Service.config.userFilePath(null, resp => {
        this.$store.commit('UPDATE_FILE_PATH', resp.path);
      });
      this.$Service.config.userAudioPath(null, resp => {
        this.$store.commit('UPDATE_AUDIO_PATH', resp.path);
      });
      this.$Service.config.userVideoPath(null, resp => {
        this.$store.commit('UPDATE_VIDEO_PATH', resp.path);
      });*/

      /** 获取当前服务器处理 敏感词 模式 */
      this.$Service.contact.queryExtendedField({ parentId: 68, dicKey : 'badWordConfig'}, resp=>{
        if (resp.EnterpriseDictionarys.length) {
          this.$store.commit('SET_BAD_KEY_MODE', resp.EnterpriseDictionarys[0].extend);
        }
      });

      /**
       * 群成员信息更新推送
       * groupId: 群ID
       * member：更新的成员信息
       */
      this.$Service.group.regGrpMemInfoRefreshCb(null, resp => {
        console.log('收到群成员信息更新推送', resp);
        this.$store.dispatch('UPDATE_MEMBER_INFO', resp);
        this.$store.dispatch('UPDATE_CHATCONTENT', resp);
      });

      /** 
       * 群成员列表更新推送 
       * groupId: 群ID
       * members： 成员信息
       * operType： 1 添加 32 移除 33 退出
       */
      this.$Service.group.regGrpMemRefreshCb(null, resp => {
        console.log('收到群成员列表更新推送', resp);
        this.$store.dispatch('UPDATE_GROUP_MEMBER', resp);
      });
      // if (Object.keys(this.chat_chatList).length !== 0) return;
      // this.$Service.chat.getChatList(null, resp => {
      //   console.log('主动拉取最近会话消息::::', resp)
      //   if (!resp.chats.length) return
      //   let recentChat = Object.assign({}, resp)
      //   console.log('regRecontactCb', recentChat);
      //   this.checkFailMsg(recentChat);
      //   _.forEach(recentChat.chats, (element, index) => {
      //     if (element.chatType === 1) {
      //       this.$Service.contact.getContactInfo({ userId: element.id }, resp => {
      //         this.$set(element, 'isDisturbStatus', resp.disturbSet)
      //       });
      //     } else if (element.chatType === 2) {
      //       this.$Service.group.getGroupMsgRemindType({ groupId: element.id }, resp => {
      //         // mode提醒模式 1：提示并接收消息；2：不提示，接收仅显示数目；3：屏蔽消息
      //         console.log(element.id, element.name)
      //         console.log('getGroupMsgRemindType:::', resp)
      //         this.$set(element, 'isDisturbStatus', resp.mode)
      //       })
      //     }
      //   })
      //   let isWindowFocus = getWindowStatus()
      //   this.$Service.log(`recentChat---${recentChat.chats[0].id}---lastMsgId---${recentChat.chats[0].lastMsgId}---unreadCount---${recentChat.chats[0].unreadCount}--time---${recentChat.chats[0].msgTime}---lastAtMsgID---${recentChat.chats[0].lastAtMsgID}  ---soundTyoe--${this.user_localConfig.sound_remind} --focus--${isWindowFocus}`);
      //   if (recentChat.chats[0].unreadCount > 0 && this.$route.query.id === recentChat.chats[0].id && isWindowFocus) {
      //     recentChat.chats[0].unreadCount = 0
      //     this.setMessageRead(recentChat.chats[0].id)
      //   }
      //   // 主动拉取最近会话没有flag，默认添加
      //   recentChat.flag = 1
      //   this.$store.dispatch('SET_CHATLIST', recentChat);
      //   if (!recentChat.chats[0].unreadCount && recentChat.chats[0].sendUserId === this.user_account.userId && recentChat.chats[0].msgType> 8000) {
      //     console.log('recentChat.chats[0]', recentChat.chats[0])
      //     this.$signalMonitor.$emit('isScroll', recentChat.chats[0].id)
      //   }
      //   /**
      //   *  是否免打扰 决定通知托盘 或者声音提醒 
      //   *  user_localConfig.msg_remind 全局免打扰设置 0 接收并提醒  1 仅提醒  2 免打扰
      //   *  disturbSet 局部免打扰 1 接收并提醒  3 免打扰
      //     */
      //   if (this.user_localConfig.msg_remind !== 2 && recentChat.chats[0].unreadCount && recentChat.chats[0].disturbSet !==3) {
      //     this.$ipc.send('newMessage')
      //     if (this.user_localConfig.sound_remind === SOUND_REMIND.OPEN) {
      //       console.log('sound_remind::', this.user_localConfig.sound_remind)
      //       document.getElementById('audio').play();
      //     }
      //   }
      // })
    },

    /** 检查失败消息 */
    checkFailMsg(data) {
      let id = data.chats[0].id
      if (id === "10000") return
      if (this.$route.query.id === id) return 
      let chatItem = this.chat_chatList[id]
      if (chatItem && chatItem.state && chatItem.state === 2) data.chats[0].state = 2;
    },

  
    // 绑定需要拖拽改变大小的元素对象
    bindResize(e) {
      let el = this.$refs.test.$el
      this.x = e.clientX - el.offsetWidth;
      this.y = e.clientY - el.offsetHeight;
      el.setCapture
        ? (el.setCapture(), el.onmousemove = ev => { 
            this.mouseMove(ev || event)
          }, el.onmouseup = this.mouseUp)
        : (document.addEventListener('mousemove', this.mouseMove),document.addEventListener('mouseup', this.mouseUp))  
      e.preventDefault();
    },
    mouseMove(e) {
      let getCilentX = e.clientX;
      if (e.clientX > 226) getCilentX = 226;
      if (e.clientX < 65) getCilentX = 56;
      let chatAreaSize = getCilentX - this.x;
      if (chatAreaSize < 226) {
        this.isListResize_226 = true;
        if (chatAreaSize <= 180) {
          this.isListResize_226 = false;
          this.isListResize_180 = true
          if (chatAreaSize <= 65) {
            this.isListResize_180 = false
            this.isListResize_65 = true
          } else {
            this.isListResize_65 = false
          }
        } else {
          this.isListResize_180 = false
        }
      } else {
        this.isListResize_65 = false
        this.isListResize_180 = false
        this.isListResize_226 = false
      }
      this.$refs.test.$el.style.width = chatAreaSize + 'px';
    },
    mouseUp(e) {
      let el = this.$refs.test.$el;
      el.releaseCapture 
        ? (el.releaseCapture(),el.onmousemove = el.onmouseup = null) 
        : (document.removeEventListener('mousemove', this.mouseMove),document.removeEventListener('mouseup', this.mouseUp))
    }
    
  },

  components: {
    chatList,
    ContactInfo: resolve => require(['../Group/ChatGroupInfo/ChatMemberInfo'], resolve),
    GroupInfo: resolve => require(['../Group/ContactGroupInfo'], resolve)
  },
  computed: {
    ...mapGetters(['chat_chatContent', 'user_account', 'chat_chatList', 'user_imgPath', 'user_localConfig', 'contact_groupList', 'contact_contactList'])
  }
};
</script>
<style lang="scss">
.chat-list {
  z-index: 60;
}
.contact-drag-line {
  height: 100%;
  width: 6px;
  cursor: e-resize;
  position: relative;
  right: 6px;
  z-index: 9999;
  background: transparent;
}
.home-detail-top-win{
  width: calc(100% - 100px);
  height: 27px;
  -webkit-app-region: drag;
}
.home-detail-content{
  width: calc(100% - 227px);
}
.chat-list-226 {
  .chatlist-time {
    display: none !important;
  }
  .title-left {
    max-width: 95% !important;
  }
  .contents {
    width: 85% !important;
  }
}

.chat-list-180 {
  .chatlist-time {
    display: none !important;
  }
  .subtitle {
    margin-top: -34px !important;
    .msg-fail-notify,
    .notice-at-me,
    .contents {
      display: none !important;
    }
    .chatlist-subscript {
      margin-top: -4px !important;
    }
  }
  .card-content {
    width: 173px !important;
  }
  .title {
    margin-bottom: 0px !important;
  }
}


.chat-list-65 {
  width: 65px !important;
  .title {
    display: none !important;
  }
  .chatlist-subscript {
    margin-top: 2px !important;
  }
  .media-left {
    margin-right: 0px !important;
  }
  .card-content {
    width: 65px !important;
  }
  .msg-fail-notify,
  .notice-at-me,
  .contents {
    display: none !important;
  }
}
.group-info-area {
    width: 342px;
    .modal-card-body {
      background: none;
      .contact-group-info {
        width: 342px;
        .v-lists {
          width: 100%;
          .v-dial-list{
            left: -92px;
          }
        }
      }
    }
  }
</style>
