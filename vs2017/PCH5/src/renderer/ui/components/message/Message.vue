<template>
  <div class="v-message">
      <!-- 消息发送时间 5分钟之内发送 不显示  -->
      <div v-if="isShowTime" class="time">{{getTimes}}</div>
      <div v-if="isNeedAvatarMsg" class="medias" :style="computedStyle" :class="computedAside" >
        <!-- xp版本适配修改 -->
        <v-checkbox v-if="isSelectMore&&!msgDisable" :style="msgSelectedStyle" @change="addItem" :disabled="msgDisable"></v-checkbox>
        <!-- <v-checkbox v-if="isSelectMore&&!msgDisable" class="msg-select-item" @change="addItem" :disabled="msgDisable"></v-checkbox> -->
        <div class="media-left" @contextmenu.stop ="avatarRightClick" >
          <v-avatar :src='computedUserInfo||avatar'  @dblclick.native="openChat" :sex="gender" :shape="round" size="is-small"></v-avatar>
        </div>
        <div class="media-contents" :style="contentMarginRight">
            <!-- 消息发送者名称显示 仅在群情况下显示 -->
            <span   v-if="chatType === 2&&!isMine"
                    v-text="groupName"
                    class="group-name">
            </span>
            <!-- 消息气泡 -->
            <div class="messages-body"  @contextmenu.stop ="msgRightClick" >
             
              <div class="fire-countdown theme-botton" v-if="countDown" >{{countDown}}</div>
              <div class="unread-count-msg" :style="computedUnreadColor" :title="$t('chat.msgStatus')" :class="{'group-msg-state': chatType === 2}" v-if="isShowUnread" @click="openList" v-html="unReadCount"></div>
              <!-- 特殊消息 密聊消息 抖一抖 橡皮擦 阅后即焚消息 的提示图标 -->
              <div class="special-msg-icon-box" :class="{'special-msg-fail' : !isSuccess}" v-if ="JudgeSpecialMsg||isLock">
                <div class="operate-btn"  v-if="specialMsgIcon">
                  <v-tooltip class="btn-tooltips" type="is-light" position="is-top" :lable="specialMsgLable" always></v-tooltip>
                  <i class="icon icon-type" :class="specialMsgClass" v-html="specialMsgIcon" @click="specialHandleClick"></i>
                </div>
                <div class="operate-btn" v-if="isLock">
                    <v-tooltip class="btn-tooltips" type="is-light" position="is-top" :lable="$t('chat.privateChat')" always></v-tooltip>
                    <i class="icon icon-type lock" @click="decryptMsg" >&#xe610;</i>
                </div>
              </div>
           
              <!-- 密聊 阅后即焚拦截组件 -->
              <div class="msg-bubble message-cover" :class="{'mine_bubble':isMine}"  v-if="( isFire === 1 && !isMine) || isLock===1" v-text="directMsgTypeContent" @click="handleClickDirectContent"></div>
              <!-- 根据各种不同的消息类型 加载不同的消息组件 -->
              <component v-else :is="currentViews" class="msg-bubble" :class="[{'mine_bubble':isMine},{'msg-bubble-opacity':user_waterMark}]" :message='msgItem' :id="id" :isOpen="isOpen" :chatType="chatType" @hasRead="hasRead" @disableRightClick="isSuccess=false"  @handleScrollBottom="handleScrollBottom" @openChatGroupNotice="openChatGroupNotice"></component>
            </div>
        </div>
      </div>
      <div v-else>
        <!-- 弱提示消息  撤回消息 音视频消息 -->
        <component :is="_handleNoAvatarMsg" :message="msgItem"  :id='id' @reEditHandleClick="$emit('reEdit', msgItem)"></component>
      </div>
      <!-- 阅后即焚 -->
      <v-modal cardSize="burns-msg-box" id="burn-box" v-if="isBurnMsg"  @close="isBurnMsg= false">
        <msg-type-burn  :currentMsg='currentViews' :message='msgItem' :id="id" :isOpen="isOpen" ></msg-type-burn>
      </v-modal>
      <chat-divider-list v-if="isDividerListShow" :readOnly="true" :id="id" :dividerIdListIds="JSON.parse(msgItem.messageObject.body)" @close="isDividerListShow=false"></chat-divider-list>
  </div>
</template>
<script>
const burnMsg = {
      Text: 2,
      Audio: 3,
      Image: 5,
      File: 6,
      Card: 7
}
const msgComponent = {
      2 : MsgTypeText, // 文本消息
      3 : MsgTypeAudio, // 语音消息
      4 : MsgTypeMap, // 位置消息
      5 : MsgTypeImage, // 图片消息
      6 : MsgTypeFile,  // 文件消息
      7 : MsgTypeCard, // 卡片消息
      8 : MsgTypeWeak,
      9 : MsgTypeWebLink, //网页链接
      12: MsgTypeImgtext, // 图文消息
      13: MsgTypeMixText,  // 组合消息
      14: MsgTypeVideo, // 音视频消息
      15: MsgTypeVideo, 
      18: MsgTypeRetract, // 撤回消息
      19: MsgDynamicExp, // 动态表情
      26: MsgTypeTemplate, // 模板消息
      28: MsgTypeNineImgs, // 九图消息
      36: MsgTypeAppShare, // 应用分享消息
      37: MsgTypeDivider, // 应用分享消息
      64: MsgTypeGroupNotice, // 群公告
      89: MsgTypeMicroVideo //微视频消息
}
import { mapGetters } from 'vuex'

import {
  MsgTypeText,
  MsgTypeImage,
  MsgTypeUnknow,
  MsgTypeFile,
  MsgTypeTemplate,
  MsgTypeImgtext,
  MsgTypeWeak,
  MsgTypeWebLink,
  // MsgTypeForward,
  MsgTypeRetract,
  MsgTypeMixText,
  MsgTypeAudio,
  MsgTypeCard,
  MsgDynamicExp,
  MsgTypeVideo,
  MsgTypeMicroVideo,
  MsgTypeNineImgs,
  MsgTypeAppShare,
  MsgTypeDivider,
  MsgTypeGroupNotice,
  MsgTypeMap
} from '@/components/Chat/Msg/index';
import msgTypeBurn from '@/components/Chat/Msg/MsgTypeBurn';
import { getDateDiff } from '../../../../comm/time';
import { isWinXp } from '../../../../comm/is';
import ContactMixin from '@/components/Contact/ContactMixin';
import MsgMixin from '@/components/Chat/msgMixin';
import { msgStructure, isJson } from '@/components/Chat/Msg';
const moment = require('moment')
export default {
  name: 'vMessage',
  mixins: [ContactMixin, MsgMixin],
  data() {
    return {
      groupName: '',
      avatar: '',
      manDefault: require('vrv-static/resources/images/contact/manDefault.png'),
      isFire: false,
      isLock: false,
      isFlash: false,
      isEraser: false,
      isDelay: false,
      gender: 0,
      specialMsgClass: '',
      specialMsgIcon: '',
      specialMsgLable: '',
      countDown: 0,
      isAudioClick: false,
      isSpecialMsg: false,
      isMine: false,
      isSuccess: true,
      isBurnMsg: false,
      isReceipt: false,
      isNeedReceipt: false,
      // eraserToday: 0
      isDividerListShow: false,
      isDivider: false
    }
  },
  props: {
    msgItem: Object,
    round: String,
    lastMsgTime: Number | Boolean,
    userInfo: Map | Function | Object,
    isComputed: false,
    id: String,
    isSelectMore: Boolean,
    isOpen: Boolean,
    chatType: String | Number,
    indexs: String | Number,
    lastMsg: Boolean | Object,
    isSelectBg: {
      default: false,
      type: Boolean
    },
    openMsgUnread: {
      default: true,
      type: Boolean
    }
  },
  created() {
    if (this.msgItem.flag === 1) {
      this.isSuccess = false
    }
  },
  mounted() {
    console.log('mounted message')
    /*根据消息类型获取不同的消息图标 阅后即焚 密聊 抖一抖*/
    console.log('mounted::: message', this.msgItem.messageObject.uuid)
    // this.$Service.log(`uid:::   ${this.msgItem.messageObject.uuid||''}`)
    this.getmsgTypeIcon()
    this.isMine = this.msgItem.messageObject.fromId === this.user_account.userId
    if (this.msgItem.messageObject.deviceType === 2 && this.isFire && this.isMine) {
      this.handleBurn(this.msgItem.messageObject.msgId)
    }

    if (this.isNeedReceipt && !this.isMine && !this.msgItem.messageObject.deal) {
       // * tipType 4 阅后回执 operType 操作类型 1 同意 
      let relatedUsers = this.msgItem.messageObject.relatedUsers
      console.log('relatedUsers::', relatedUsers)
      if (this.chatType === 1 || (relatedUsers && (relatedUsers.includes(this.user_account.userId)||relatedUsers.includes(this.id)))) {
        console.log('relatedUsers', relatedUsers)
        this.$emit('handleReceipt',  this.msgItem.messageObject)
      }
    }

    // if (!this.isMine && this.isEraser && !this.msgItem.messageObject.deal && this.chatType === 1) {
    //   console.log('eraserToday:::::::', this.eraserToday)
    //   this.$emit('handleEarseType', {type: this.eraserToday, messageObject: this.msgItem.messageObject})
  
    if (!this.isMine && this.isEraser && !this.msgItem.messageObject.deal) {
      // * tipType 4 阅后回执 operType 操作类型 1 同意 
      let relatedUsers = this.msgItem.messageObject.relatedUsers
      if (this.chatType === 1 || (relatedUsers && (relatedUsers.includes(this.user_account.userId) || relatedUsers.includes(this.id)))) {
        console.log('relatedUsers', relatedUsers)
        // this.$emit('handleReceipt',  this.msgItem.messageObject)
        this.$emit('handleEarseType', {msgObj: this.msgItem.messageObject})
      }
    }
    
    if (this.chatType === 2 && this.isMine && this.msgItem.messageObject.isNeedHandleUnread) {
      console.log('message', this.msgItem.messageObject.msgId)
      this.$emit('handleUnreadMsg', {msg: {msgId: this.msgItem.messageObject.msgId, snapshotId:this.msgItem.messageObject.snapshotId}, type: 1})
    }
  },

  beforeDestroy() {
    if (this.chatType === 2 && this.isMine) {
      console.log('message', this.msgItem.messageObject.msgId)
      this.$emit('handleUnreadMsg', {msgId:this.msgItem.messageObject.msgId, type: 2})
    }
  },
  computed: {
    ...mapGetters(['user_waterMark','chat_is_sector_open']),
    computedStyle() {
      return {
        // 'margin-right': this.isSelectMore?'40px':this.mediaMarginRight,
        // 适配xp版本聊天界面多选框位置
        'margin-right': this.isSelectMore?this.selectedMarginRight:this.mediaMarginRight,
        background: this.isSelectBg?'#ffedc4':''
      }
    },
    computedUnreadColor() {
      switch (this.unReadCount) {
        case this.$t('chat.unRead'): // 个人-未读
        case this.$t('chat.allUnread'): // 群-全部未读
          return { color: '#5d5d5d' }

        case this.$t('chat.read'): // 个人-已读
        case this.$t('chat.allRead'): // 群-全部已读
          return { color: '#2196F3' }
        
        default:
          let msg = this.msgItem.messageObject
          console.log(msg.maxUnReadCount, msg.unReadCount)
          if (msg.maxUnReadCount-1 !== msg.unReadCount) { // 部分已读
            return { color: '#a86d05' }
          } else { // 全部未读
            return { color: '#5d5d5d' }
          }
          break;
      }
    },
    isNeedAvatarMsg() {
      let typeArrs = [8, 18, 14, 15];
      return !typeArrs.includes(this.msgItem.messageObject.msgType);
    },
    contentMarginRight(){
      // 适配xp版本聊天内容显示位置
      return {'margin-right':isWinXp?'-28px':'0px'};
      // return {'margin-right':isWinXp?'-30px':'0px'};
      // return {'margin-right': '0px'};
    },
    // 适配xp版本多选框显示时，自己发送信息的位置显示问题
    selectedMarginRight() {
      return isWinXp ? '67px': '40px';
    },
    // 适配xp版本多选框位置显示
    msgSelectedStyle() {
      return {
        'position': 'absolute',
        'top': '8px',
        'right': isWinXp ? '-60px' : '-35px'
      }
    },
    // xp版本自己发送的信息的显示问题
    mediaMarginRight(){
      return isWinXp?'27px':'0px';
      // return isWinXp?'25px':'0px';
      // return '0px';
    },
    _handleNoAvatarMsg() {
      let type =
        this.msgItem.messageObject.msgType & 0x00ff
          ? this.msgItem.messageObject.msgType & 0x00ff
          : this.msgItem.messageObject.msgType & 0xff00
      /**
       * type {Number} 为消息类型 包含发送失败 上传失败
       * msgComponent {Object} 消息组件对象
       */
      console.log('type::', type)
      return  msgComponent[type]
    },

    isShowTime() {
      if (typeof(this.lastMsg) === 'boolean') {
        return true
      }
      return this.msgItem.messageObject.time - this.lastMsg.messageObject.time > 300000
        ? 1
        : 0
    },

    isShowUnread() {
      if (this.isMine && this.id !== this.user_account.userId && this.isSuccess && this.openMsgUnread) {
        return true
        // return this.chatType === 1 ? true : this.msgItem.messageObject.maxUnReadCount!==0
      }
    },

    unReadCount() {
      console.log('unReadCount:::::')
      let msg = this.msgItem.messageObject
      if (this.chatType === 2 && !msg.maxUnReadCount && !msg.unReadCount && !parseInt(msg.snapshotId)) {
        return this.$t('chat.allUnread')
      }
      return this.chatType === 1 ? msg.maxUnReadCount !== 1  ? `${this.$t('chat.unRead')}` : `${this.$t('chat.read')}` : msg.unReadCount !== 0 ? this.$t('chat.someUnread', {value: msg.unReadCount}) : this.$t('chat.allRead')
    },
    /**
     * 获取消息发送时间
     */
    getTimes() {
      console.log('getTimes')
      return getDateDiff(parseInt(this.msgItem.messageObject.time))
    },
    /** 根据不同的消息类型 加载对应的消息组件 */
    currentViews() {
      let type =
        this.msgItem.messageObject.msgType & 0x00ff
          ? this.msgItem.messageObject.msgType & 0x00ff
          : this.msgItem.messageObject.msgType & 0xff00
      /**
       * type {Number} 为消息类型 包含发送失败 上传失败
       * msgComponent {Object} 消息组件对象
       */
      return msgComponent.hasOwnProperty(type) 
           ? msgComponent[type]
           : MsgTypeUnknow
    },
    /** 区分消息左右分边 */
    computedAside() {
      if (this.id === this.user_account.userId) {
         return this.msgItem.messageObject.deviceType === 1
          ? 'v-message-right'
          : 'v-message-left'
      } else {
         return this.isMine
          ? 'v-message-right'
          : 'v-message-left'
      }
    },
    /**
     * 获取消息发送者信息
     * 名称
     * 头像
     */
    computedUserInfo() {
     if (this.userInfo && Object.keys(this.userInfo).length) {
        /**
         * 获取群内成员对应的名称 remark
         * 如果没有改成员的remark 显示改成员的ID
         */
        let userInfo = this.userInfo[this.msgItem.messageObject.fromId]
        // console.log('userInfo',userInfo)
        if(userInfo && (userInfo.remark !== undefined || userInfo.name !== undefined)) {
           this.groupName = userInfo.remark
           this.gender =userInfo.gender
           if(this.chat_is_sector_open && userInfo.sector !== undefined && userInfo.sector !== ''){
             this.groupName = userInfo.remark+'-'+userInfo.sector
           }
           if (this.msgItem.messageObject.isPrivateMsg !== 0) {
              this.isLock = this.isMine && this.msgItem.messageObject.deviceType === 1 ? 2 :this.msgItem.messageObject.isPrivateMsg
              console.log('this.isLock:::', this.isLock)
           }
          /**
            * 获取群内成员对应的头像 avatar
            * 如果没有改成员的avatar 显示默认头像
            */
            return userInfo.thumbAvatar !== undefined ? userInfo.thumbAvatar : ''
        } else {
          // 此时数据没有拉取回来 先展示ID
          this.$Service.log(`getUnknowUserInfo in Message::::: ${this.msgItem.messageObject.fromId}`)
          let type = this.$Service.config.getUserTypeById({ targetId: this.msgItem.messageObject.fromId })
          this.getUnknowUserInfo(type)
          this.groupName = this.msgItem.messageObject.fromId
          
          return ''
        }
      } else {
        if (this.chatType === 2) {
          let type = this.$Service.config.getUserTypeById({ targetId: this.msgItem.messageObject.fromId})
          this.groupName = type === 1 ? this.$t('chat.groupMember') : this.$t('chat.appNotice')
        }
        return ''
      }
    },
    // 判断是否是特殊消息 然后设置特殊消息的信息 图标 tooltip css类名
    JudgeSpecialMsg() {
      if (this.isFire) {
        this.setSpecialMsgInfo('&#xe635;', '', this.$t('groups.burnChat'))
        return this.isSpecialMsg = true
      }  else if (this.isFlash) {
        this.setSpecialMsgInfo('&#xe65a;', 'flash', this.$t('chat.shake'))
        return this.isSpecialMsg = true
      } else if (this.isEraser) {
        this.setSpecialMsgInfo('&#xe643;', 'eraser', this.$t('chat.earse'))
        return this.isSpecialMsg = true
      } else if (this.isDelay) {
        this.setSpecialMsgInfo('&#xe661;', 'delay', `${this.$t('chat.delayMessage')} : ${moment(this.msgItem.messageObject.delayTime).format('MM-DD HH:mm')}`)
        return this.isSpecialMsg = true
      } else if (this.isReceipt) {
        this.setSpecialMsgInfo('&#xe6bd;', 'receipt', this.$t('chat.receiptMessage'))
        return this.isSpecialMsg = true
      } else if (this.isDivider) {
        this.setSpecialMsgInfo('&#xe6c9;', 'divider', '潜水者')
        return this.isSpecialMsg = true
      }
    },
    /**
     * 判断当前消息checkbox是否可选
     * @returns {Boolean}
     */
    msgDisable() {
      if (!this.isSuccess) return true
      let typeArrs = [3, 8, 13, 14, 15, 18, 26];
      if (!msgComponent.hasOwnProperty(this.msgItem.messageObject.msgType)) {
        return true
      }
      // let typeArrs = [3, 8, 13, 14, 15, 18, 26, 89];
      // 避免返回值为Number类型
      if (!this.isLock) {
        console.log('no lock...')
        return typeArrs.includes(this.msgItem.messageObject.msgType)||this.isSpecialMsg
      } else {
        console.log('lock...')
        return true
      }
    },

    // * 密聊 阅后即焚
    directMsgTypeContent() {
      return this.isLock === 1 ? this.$t('chat.privateMsg') : this.$t('groups.burnChat')
    },

    allowChat() {
      let extend = this.contact_groupExtension[this.$route.query.id];
      let isFriend = this.contact_contactList[this.msgItem.messageObject.fromId];
      return (extend && extend.disallowStrangerChat && extend.disallowStrangerChat == 0) || isFriend
    },

    ...mapGetters([
      'chat_chatContent',
      'chat_objectInfo',
      'user_account',
      'chat_chatList',
      'contact_contactList',
      'contact_groupExtension'
    ])
  },
  methods: {
    handleScrollBottom() {
      console.log('handleScrollBottom::::')
      this.$emit('handleScrollBottomToList')
    },

    msgRightClick($event) {
      // if (!this.isSuccess) return
      this.$emit('rightClick', {type: 2, event:$event, isSpecialMsg: this.isSpecialMsg||this.isLock, isMsgSuccess:this.isSuccess})
      //  this.$emit('rightClick', {type: 2, event:$event, isSpecialMsg: this.isSpecialMsg||this.isLock})
    },

    /** 双击头像 打开对应会话 */
    openChat() {
      if (this.isMine || !this.allowChat) return
      let item = this.userInfo[this.msgItem.messageObject.fromId]
      this.startChat(item, 1)
    },

    avatarRightClick($event) {
     if (this.isMine) return
     this.$emit('rightClick', {type: 1, event:$event, name:this.groupName})
    },

    hasRead(msgId) {
      if (!this.isSuccess) {
        this.isSuccess = true
      }
      if (this.chatType === 2 && this.isMine) {
        console.log('message', this.msgItem.messageObject.msgId)
        this.$emit('handleUnreadMsg', {msg: {msgId: this.msgItem.messageObject.msgId, snapshotId:this.msgItem.messageObject.snapshotId}, type: 1})
      }
      this.handleBurn(this.msgItem.messageObject.msgId)
    },

    handleBurn(msgId) {
      if (this.msgItem.messageObject.activeType === 1) {
        this.countDown = this.computedBurnTime();
        if (this.msgItem.messageObject.msgType=== 3 && !this.isMine && !this.isAudioClick) return
        let timer = setInterval(() => {
          if (this.countDown < 1) {
            clearInterval(timer)
            this.delMsg(this.msgItem.messageObject.targetId, msgId)
          } else {
            this.countDown--
          }
        }, 1000)
      }
    },

    addItem(isChecked) {
      this.$emit('select-item', {
        item: this.msgItem.messageObject,
        isChecked: isChecked
      });
    },

    /** 打开消息状态 */
    openList() {
      if (this.chatType !== 2) return
      this.$emit('openMsgStateList', this.msgItem.messageObject)
    },

    /**设置特殊消息的信息 图标 类名 toolTip */
    setSpecialMsgInfo(icon, className, label) {
        this.specialMsgIcon = icon;
        this.specialMsgClass = className;
        this.specialMsgLable = label;
    },

    /** 特殊消息点击事件 */
    specialHandleClick() {
      if (this.isDivider) {
        this.isDividerListShow = true
      }
      if (this.isMine) return 
      if (this.isLock === 1) {
        console.log('this.isLock::::', this.isLock)
        return this.$dialog.alert({message: this.$t('chat.decryptMsgFirst'), onfirmText: this.$t('common.confirm'), onConfirm: () => {}});
      } 
      if (this.isFire === 1) {
        console.log('isFire::::')
        this.isBurnMsg = true
      } 
    },

    handleClickDirectContent() {
      if (this.isLock === 1) {
        console.log('this.isLock::::', this.isLock)
        return this.decryptMsg()
      } 
      if (this.isFire === 1) {
        console.log('isFire::::')
        this.isBurnMsg = true
      } 

    },

    /** 解密消息 */
    decryptMsg() {
      console.log('decryptMsg')
      console.log('this.msgItem', this.msgItem)
      console.log('this.isLock', this.isLock)
      if (this.isLock === 2) {
        return
      }
      let inputInfo = this.isMine? this.$t('chat.setPassword'):this.$t('chat.inputPassword')
      this.$dialog.prompt({
        title: this.$t('chat.inputPassword'),
        confirmText: this.$t('common.sure'),
        cancelText: this.$t('common.cancel'),
        inputAttrs: {
          placeholder: this.$t('chat.inputPassword'),
          maxlength: 24,
          min: 6,
          type: 'password'
        },
        required: true,
        onConfirm: value => {
          let setPrivateKeyParam = {
              targetId: this.id,    // 传入会话对应的ID，群或者人
              passwd: value       // 私信秘钥  为空代表清除私信密码
          }
          this.$Service.chat.setPrivateKey(setPrivateKeyParam, resp => {
            console.log('setPrivateKey  message:::', resp)
              if (resp.code === 0) {
                let envMsg = [];
                for (let i in this.chat_chatContent[this.id]) {
                  if (this.chat_chatContent[this.id][i].messageObject.isPrivateMsg === 1) {
                    envMsg.push(this.chat_chatContent[this.id][i].messageObject.msgId)
                  }
                }
                /**
                 * 解密消息
                 * @param {String} targetId 传入会话对应的ID，群或者人
                 * @param {Array} msgIds 要解密的消息ID集合
                 * @param {Function} cb 回调函数返回解密后的消息 然后替换之前加密消息
                 */
                let decryptMsgParam = {
                    targetId: this.id,     // 传入会话对应的ID，群或者人
                    msgIds: envMsg  // 要解密的消息ID集合
                }

                let decryptMsgCb = resp => {
                  console.log('resp:::', resp)
                   if (resp.code === 0) {
                    let decryptMsgIndex = resp.msgs.findIndex(e =>e.msgId  === this.msgItem.messageObject.msgId)
                    let decryptResult = resp.msgs[decryptMsgIndex].isPrivateMsg !== 1
                    console.log('decryptResult:::', decryptResult)
                    if (decryptResult) {
                      resp.msgs.forEach(element => {
                        if (element.isPrivateMsg !== 1) {
                          console.log('element::', element)
                          let replaceMsg = msgStructure(element)
                          this.$store.commit('REPLACE_CHATCONTENT', { id:this.id, msg:replaceMsg });
                        }
                      });
                    } else {
                      let toastMsg = {
                          message: this.$t('chat.passwordMismatch'),
                          type: 'is-danger'
                      }
                      this.$toast.open(toastMsg);
                      this.$Service.log(`decryptMsg passwordMismatch`)
                    }
                   }
                }
                this.$Service.chat.decryptMsg(decryptMsgParam, decryptMsgCb)
              }
          })
        }
      });
    },
    /**
     * 计算销毁时间
     * 图片消息默认20秒销毁
     * 音频消息为本语音消息的长度+2
     * 文本消息根据文字长度来判断
     */
    computedBurnTime() {
      let burnTime;
      switch (this.msgItem.messageObject.msgType) {
        case burnMsg.Text:
        burnTime = this.textBurnTime()
        break

        case burnMsg.Audio:
        burnTime =  Math.floor(this.msgItem.messageObject.mediaTime / 1000) + 5
        break
        
        case burnMsg.Image:
        case burnMsg.File:
        burnTime = 20
        break

        case burnMsg.Card:
        burnTime = 10
        break

        default:
        break
      }
      return burnTime
    },

    textBurnTime() {
      let burnTime ,
          content = this.msgItem.messageObject.body;
      if (content.length < 20) {
        burnTime = 5
      } else if (content.length < 40) {
        burnTime = 10
      } else if (content.length < 60) {
        burnTime = 15
      } else {
        burnTime = 20
      }
      return burnTime
    },


    /**
     * 消息类型
     * @param {Number} from - 0：阅后即焚 1：私聊
     * @returns {Boolean} 是否是阅后即焚|私聊消息
     */
    getmsgTypeIcon() {
      try {
        let msgObj = this.msgItem.messageObject
        console.log('this.msgItem.messageObject::', this.msgItem.messageObject)
        if (msgObj.msgType === 2) {
            this.isFlash = msgObj.body.includes('&:flash') // 抖一抖
            this.isDelay = msgObj.isDelay
            this.isEraser = msgObj.body.includes('&:delete|')   // 橡皮擦
            this.isNeedReceipt = msgObj.isReceipt  // 是否需要回执

            // * 单聊情况下 isReceipt 为true  则为阅后回执
            if (this.chatType === 1) {
               this.isReceipt = this.isNeedReceipt
            } else if (this.chatType === 2) { // 群聊情况下 isReceipt && 携带 "<<<" 为阅后回执消息
              if (msgObj.isReceipt && _.endsWith(msgObj.body, '<<<')) { // 阅后回执 
                console.log('endwidth', _.endsWith(msgObj.body, '<<<'))
                this.isReceipt = true
              }
            }
           
            // if (this.isEraser) {
            //   this.eraserToday = msgObj.body.includes('today') ? 1 : 0
            // }
        } else if (msgObj.msgType === 37) { 
          this.isDivider = true
        }
        if (msgObj.activeType && msgObj.activeType == 1)  this.isFire = 1; 
        if (msgObj.isPrivateMsg !== 0) { // 密聊消息
          this.isLock = msgObj.fromId === this.user_account.userId && msgObj.deviceType === 1
              ? 2
              : msgObj.isPrivateMsg
        }
      } catch (error) {
        console.log('error-message', error)
      }
    },

    /** 获取未知人员消息 */
    getUnknowUserInfo(type) {
      console.log('getUnknowUserInfo::')
      if (type === 1) {
      /**
       * 获取陌生人信息
       * @param {Stirng} userId 目标对象的id
       */
        let getUserInfoParam = { userId: this.msgItem.messageObject.fromId }
        let getUserInfoCb = successRes => {
          if (successRes.code === 0) {
            this.avatar = successRes.users.thumbAvatar
            this.groupName = successRes.users.name
            this.gender =successRes.users.gender
          }
        }
        this.$Service.search.getUserInfo( getUserInfoParam, getUserInfoCb)
      } else {
        /**
         * 获取应用信息
         * @param {Stirng} appId 目标应用的id
         */
         let getAppInfoParam = {appId: this.msgItem.messageObject.fromId }
         let getAppInfoCb = resp => {
            this.avatar = resp.info.appIcon
            this.groupName = resp.info.appName
         }
        this.$Service.user.getAppInfo(getAppInfoParam, getAppInfoCb)
      }
    },
    openChatGroupNotice(param){
      this.$emit('openChatGroupNotice', param);
    }
    //  updateMsg(msg) {
    //   let updateMsg = Object.assign({}, msg.messageObject)
    //   updateMsg.deal = true
    //   this.$Service.chat.updateMsg(updateMsg, resp => {
    //     console.log('updateMsg::', resp)
    //   })
    //  }


  },

  components: {
    MsgTypeText,
    MsgTypeImage,
    MsgTypeUnknow,
    MsgTypeFile,
    MsgTypeWeak,
    MsgTypeTemplate,
    MsgTypeNineImgs,
    MsgTypeImgtext,
    MsgTypeWebLink,
    // MsgTypeForward,
    MsgTypeRetract,
    MsgDynamicExp,
    MsgTypeVideo,
    msgTypeBurn,
    MsgTypeGroupNotice,
    ChatDividerList: resolve => require(['@/components/Chat/ChatContent/ChatDividerList'], resolve)
  }
}
</script>

<style lang="scss" scoped>

.v-message {
  .medias {
    padding: 0.5rem;
    display: flex;
    .media-left {
      margin: 0px;
      position: absolute;
      .avatar {
        width: 28px;
        height: 28px;
      }
    }
    // .msg-select-item {
    //   position: absolute;
    //   right: -35px;
    //   top: 8px;
    // }

  }
  
    @mixin outward {
    margin-bottom: 4px;
    font-size: 15px;
    position: relative;
    .image {
      height: 40px;
      width: 40px;
      overflow: hidden;
      border-radius: $--border-radius-circle;
    }
    .media-title {
      position: absolute;
      font-size: 12px;
      display: flex;
      top: -20px;
      color: #919492;
    }
    .messages-body {
      display: flex;
      justify-content: center;
      align-items: center;
      margin-bottom: 4px;
      margin-top: 32px;
      .fire-countdown {
        height: 18px;
        width: 18px;
        text-align: center;
        line-height: 18px;
        border-radius: $--border-radius-circle;
        color: #fff;
        font-size: .65rem;
      }
      .special-msg-icon-box {
        display: flex;
        flex-direction: column;
        .operate-btn {
          .icon-type {
              z-index: 9;
              font-size: 0.85rem;
              color: $--color-msg-prompt-danger;
            }

            .lock {
              color: $--color-msg-prompt-low;
            }
            .flash {
              color: $--color-msg-prompt-low;
            }
            .delay{
              font-size: 18px;
              color: $--color-msg-prompt-middle;
            }
            .receipt {
              font-size: 18px;
              color: $--color-msg-prompt-low;
            }
            .divider {
              color: $--color-msg-prompt-low;
              font-size: 16px;
            }
            .eraser {
              color: $--color-msg-prompt-low;
              font-size: 12px;
            }
          .btn-tooltips {
            display: none;
          }
          &:hover .btn-tooltips {
            display: block;
          }
        }
        &.special-msg-fail {
          margin-right: 14px;
        }
      }
      .msg-bubble {
        max-width: 400px;
        min-width: 60px;
        display: flex;
        justify-content: center;
        word-wrap: break-word;
        word-break: break-all;
        position: relative;
        border-radius: $--border-radius-msg;
        font-weight: 500;
        font-size: 0.85rem;
      }
    }
  }

  .v-message-right {
    @include outward;
    flex-direction: $--message-flex-direction;
    .media-title {
      right: 25px;
    }
    .messages-body {
      flex-direction: row;
      .unread-count-msg {
        font-size: 12px;
        display: flex;
        align-self: flex-end;
        margin-right: 5px;
        margin-bottom: -2px;
        // color: $--color-msg-prompt-low;
        
        &.group-msg-state{
          &:hover {
            color: $--color-text-hover;
            text-decoration:underline;
            cursor: pointer;
          }
        }
      }
      .msg-bubble {
        @include bg_color($--background-msgbuble-primary, 'msgbuble');
        color: #fff;
        box-shadow:$--box-shadow-elevation;
      }
      .msg-bubble-opacity {
        // opacity: 0.8;
        @include bg_color($--background-msgbuble-primary, 'msgbuble');
        color: #fff;
        box-shadow:$--box-shadow-elevation;
      }
    }
  }

  .v-message-left {
    @include outward;
    .media-title {
      left: 25px;
    }

    .group-name {
      position: absolute;
      left: 44px;
      top: 12px;
      font-size: 0.75rem;
      font-weight: 500;
      min-width: 100px;
      color: #767676;
      letter-spacing: 0.5px;
    }
    .messages-body {
      flex-direction: row-reverse;
      .msg-bubble {
        background: #f5f5f7 100%;
        //background: rgba(207, 207, 216, 0.3);
        color: #000;
        box-shadow:$--box-shadow-rd;
      }
      .msg-bubble-opacity{
        //background: #f5f5f7 100%;
        background: rgba(245,245,247, 0.7);
        color: #000;
        box-shadow:$--box-shadow-rd;
      }
    }
  }
  .time {
    height: 20px;
    font-size: 12px;
    display: flex;
    color: #919492;
    align-items: center;
    justify-content: center;
  }
  .message-cover {
    padding: 6px 10px;
    font-size: 0.85rem;
    &:hover {
      text-decoration:underline;
      color: $--color-msg-prompt-low!important;
    }
  }


}
</style>
