<template>
  <div class="msglist-area"  v-chat-scroll   @scroll.passive.stop='hangdleScroll' ref="listBox" >
    <!-- 消息列表 msgListShow控制显示条数 -->
    <section class="load-area"  v-if="isShowLoad" >
    <div class="loaders loader-3">
      <div class="dot dot1"></div>
      <div class="dot dot2"></div>
      <div class="dot dot3"></div>
      <div class="dot dot4"></div>
    </div>
    </section>
      <!-- <vue-scroll   ref="vs" :ops="ops"  @handle-scroll="hangdleScroll"    class="message-list"> -->
       <div class="load-more-history-message"  v-if="isLoadHistoryMsg">
        <i class="timeicon icon">&#xe61f;</i><a class="load-more-msg-btn" @click="loadMoreHistoryMsg">{{$t('chat.searchHistory')}}</a>
      </div>
      <div class="v-msg-list-item"  v-for="(item, value, index) in messageObject" :key="item.messageObject.uuid" >
        <!-- 消息发送时间 5分钟之内发送 不显示  -->
        <v-message  :msgItem='item'
                    round='round'
                    :isOpen="isOpen"
                    :userInfo="userInfo"
                    :id="id"
                    :chatType="chatType"
                    :lastMsg="index!==0&&messageObject[Object.keys(messageObject)[index-1]]"
                    :indexs ='index'
                    :isSelectMore="isOpenAction"
                    @select-item="selectMultiItem"
                    @rightClick="addMenu(item, $event)"
                    @openMsgStateList ='openMsgStateList'
                    @handleScrollBottomToList ="scrollToBottom()"
                    @handleUnreadMsg ='handleUnreadMsg'
                    @handleEarseType='handleEarseType'
                    @handleReceipt='handleReceiptType'
                    @reEdit="reEdit"
                    @openChatGroupNotice="openChatGroupNotice">
        </v-message>
      </div>

      <!-- </vue-scroll> -->
        <!-- 右键菜单 包含消息操作 转发 删除 更多 -->
        <msg-menu-operate
                  v-if="isShowRightMenu" 
                  :isOpenAction='isOpenAction' 
                  :isActionForward="isActionForward" 
                  :selectActive="selectActive" 
                  :menuList="menuList" 
                  :id ="id"
                  :mixTextMessage="mixTextMessage" 
                  :isMixText="objectValues(mixTextMessage).length!==0"
                  :userInfo="userInfo"
                  :currentPos="currentPos"
                  :chatType ='chatType'
                  :footerDivider ='footerDivider'
                  :headDivider="headDivider"
                  :isAutoShowMsgState="isAutoShowMsgState"
                  :remindMsgSeconds="remindMsgSeconds"
                  @hasAtInList="hasAtInList"
                  @clearMenuList="menuList = []"
                  @closeRightMenu="closeRightMenu"
                  @handleActionShow="handleActionBoxShow"
                  @showAddRemind="showAddRemind"
                  >
        </msg-menu-operate>
        
        <div class="msg-notify" :class="[{'notice-close-expend':isExpendSidebar}, getModel]" v-if="isShowMsgNotify">
            <div class="notice-msg-count"  @click="scrollToBottom()">
              <i class="icon msg-to-bottom">&#xe638;</i>
              <span>{{`${unreadCountMsg} ${$t('chat.newMessage')}`}}</span>
            </div>
        
            <div class="notice-close"  @click="closeNotify">
              <i class="icon msg-notify-close">&#xe606;</i>
            </div>
        </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import { msgStructure, MsgRetract } from '../Msg'
import { getDateDiff } from '../../../../comm/time'
import { encryptionPassword } from '../../../../comm/util'
// import GroupMemberInfo from '../../Group/ChatGroupInfo/ChatMemberInfo'
import MsgMenuOperate from './RightMenu'
import MsgMxin from '../msgMixin'
const IMG_DICVALUE = 'isSavePicturesToAlbums'
export default {
  data() {
    return {
      isLoadHistoryMsg: false,
      listArea: null, // 消息列表容器 之后可能会对此容器有操作
      isShowRightMenu: false,
      menuList: [], // 消息右键列表
      currentPos: {
        // 记录右键列表的横纵坐标
        top: String,
        left: String
      },
      selectActive: null, // 右键选中消息的信息(message、targetId...)
      isForward: false, // 是否转发消息
      mixTextMessage: {},
      isMemberInfoShow: false,
      isMsgStatusList: false,
      isPauseScroll: false,
      memberInfo: {},
      unreadCountMsg: 0,
      isShowMsgNotify: false,
      isNeedToScroll: false,
      lastScrollPosition: 0,
      headDivider: '',
      footerDivider: '',
      isAutoShowMsgState: false,
      unreadArray: [],
      isShowLoad: true,
      userMaxReadId: '',
      pendingEarseMsg: {},
      pendingReceiptMsg:{},
      isShowEarseBox: false,
      isGroupEid:false
      // testMsg: [],
      // testId: ''
    }
  },
  mixins: [MsgMxin],
  props: {
    isExpendSidebar: Boolean,
    messageObject: Array | Object,
    isOpen: Boolean,
    userInfo: Map | Function,
    id: String,
    isActionForward: Boolean, // 这里是右键菜单'更多'里的转发
    isOpenAction: Boolean,
    hasMixMsgDelete: Boolean,
    chatType: Number,
    remindMsgSeconds: Number,
    isWinFocus: Boolean
  },
  mounted() {
    this.$nextTick(() => {
    console.log('=============vvv=======')
    let unreadCountMsg = 1;
    if(this.chat_chatList[this.id]&& this.chat_chatList[this.id].unreadCount){
      unreadCountMsg = this.chat_chatList[this.id].unreadCount
    }
    this.getHistoryMsg(this.id, unreadCountMsg).then(msgs => {
      this.$emit('open-chat-top')
      if(!msgs.length) return
      //  this.testMsg = msgs
      //  this.testId = this.testMsg[this.testMsg.length - 1].msgId
      this.setMessageRead(this.id)
      this.scrollToBottom()
      this.chatType === 1 ? this.getUserMsgUnreadCount() : this.getGroupMsgUnreadCount()
    });

    if(this.chatType === 2){
      console.log('============isEidGroup==============')
      this.isEidGroup(this.id,isEid => this.isGroupEid = isEid);
    }
  })
  },
  watch: {
    isWinFocus() {
      // 窗口获取焦点，当前会话处理阅后回执缓存消息，非当前会话过滤掉
      if (!this.isOpen) return;
      // * 处理阅后回执消息 （激活状态下， 判断是该会话否有缓存阅后回执消息）
      console.log('pendingReceiptMsg::', this.pendingReceiptMsg)
      if (Object.keys(this.pendingReceiptMsg).length) {
        _.forEach(this.pendingReceiptMsg, element => {
          if (this.chat_chatContent[element.targetId][`id_${element.msgId}`]) {
            this.handleReceipt(element)
          } else { // 窗口失焦后，撤回了回执消息，则获焦后也不再回执
            this.$delete(this.pendingReceiptMsg, element.msgId)
          }
        })
      }
    },
    isOpen() {
      this.$nextTick(() => {
        if (this.isOpen) {
          /** 如果消息缓存被清除 显示加载更多按钮  */
          if (!this.isLoadHistoryMsg) this.isLoadHistoryMsg = true

          if (this.isNeedToScroll) {
            this.scrollToBottom()
            this.isNeedToScroll = false
          }
          /** 其他路由切过来 滚动条位置丢失 需要置底部 */
          if (this.$refs.listBox.scrollTop === 0) {
            this.scrollToBottom()
          }

          console.log('length', this.unreadArray.length)
          if (this.chatType === 2) {
            // * 临时处理已读未读
            if (this.unreadArray && this.unreadArray.length) {
              _.forEach(this.unreadArray, element => {
                element.snapshotId = this.chat_chatContent[this.id][`id_${element.msgId}`].messageObject.snapshotId
                this.$Service.log(`msgId:: ${element.msgId}   snapshotId::::  ${element.snapshotId}`)
              })
            }
            this.getGroupMsgUnreadCount()
          }

          // * 处理橡皮擦消息 （未处于激活状态下， 橡皮擦消息）
          console.log('pendingEarseMsg::', this.pendingEarseMsg)
          if (Object.keys(this.pendingEarseMsg).length) {
            this.handleEarseMsg(this.pendingEarseMsg)
          }
          // * 处理阅后回执消息 （未处于激活状态下， 阅后回执消息）
          console.log('pendingReceiptMsg::', this.pendingReceiptMsg)
          if (Object.keys(this.pendingReceiptMsg).length) {
            _.forEach(this.pendingReceiptMsg, element => {
              console.log('isExist:::',this.chat_chatContent[element.targetId][`id_${element.msgId}`])
              if (this.chat_chatContent[element.targetId][`id_${element.msgId}`]) {
                this.handleReceipt(element)
              } else { // 打开会话前，撤回了回执消息，则不回执
                this.$delete(this.pendingReceiptMsg, element.msgId)
              }
            })
          }
        }
      })
    },
    isOpenAction(isOpen) {
      if (!isOpen) {
        this.isShowRightMenu = false
        this.mixTextMessage = {}
      }
    },

    // * 删除选中的消息 (combine)
    hasMixMsgDelete() {
      if (this.hasMixMsgDelete) {
        for (let i in this.mixTextMessage) {
          this.delMsg(this.id, i)
        }
        this.$emit('handleActionBoxShow', false)
      }
    },

    mixTextMessage: {
      handler: function(value) {
        this.$emit('msgSelectLength', _.values(value).length)
      },
      deep: true
    }
  },
  methods: {
     objectValues(obj) {
       return _.values(obj);
     },
    /**
     * handleUnreadMsg 处理未读消息
     * @param {Object} arg arg.type 1 新增 2 删除
     **/  
    handleUnreadMsg(arg) {
      console.log('arg', arg)
      if (arg.type === 1) {
        this.unreadArray.push(arg.msg)
      } else {
        this.unreadArray = _.filter(this.unreadArray, element => element.msgId !== arg.msgId )
      }
    },

    /**
     * getUserMsgUnreadCount 获取个人消息未读
     * @param {String} targetId 用户id
     */
    getUserMsgUnreadCount() {
      this.$Service.chat.getContractMaxReadId({targetId: this.id}, resp => {
        console.log('getContractMaxReadId', resp)
        if (resp.maxReadId === '0') return // 旧服务还不支持已读未读
        this.userMaxReadId = resp.maxReadId
        this.$Service.log(`userMaxReadId:::     ${this.userMaxReadId}`)
        return this.$store.dispatch('UPDATE_UNREADCOUNT', {targetId: this.id, msgId: resp.maxReadId, maxUnReadCount: 1, targetIsGroup:false});
      })
    },
    
    /**
     * getGroupMsgUnreadCount 获取群内消息已读未读
     * @param {String} groupId 群Id
     * @param {Array} snapShotInfos 消息的快照Id
     */
    getGroupMsgUnreadCount() {
      if (!this.unreadArray.length) return 
      let getGroupMsgUnreadCounterParam = {
        groupId: this.id,
        snapShotInfos: this.unreadArray
      }
      console.log('this.unreadArray', this.unreadArray)
      this.$Service.log(`getGroupMsgUnreadCounter::::    id: ${this.id}  length::${this.unreadArray.length}`)
      this.$Service.chat.getGroupMsgUnreadCounter(getGroupMsgUnreadCounterParam, resp=> {
        console.log('getGroupMsgUnreadCounter::', resp)
        let unReadCounter = Object.assign({}, resp)
          unReadCounter.msgs.forEach(e => {
            if (e.unreadCount === 0) {
              this.unreadArray = _.filter(this.unreadArray, element => { element.messageId !== e.messageId })
            }
            this.$store.dispatch('UPDATE_UNREADCOUNT', {targetId: this.id, msgId: e.messageId, maxUnReadCount: e.maxUnreadCount, unReadCount:e.unreadCount , snapshotId:e.snapshotId, targetIsGroup: true});
          })
      })
    },

    // * 打开消息状态列表 ( 仅群 )
    openMsgStateList(arg) {
      this.isShowRightMenu = true
      this.isAutoShowMsgState = true 
      this.selectActive = arg
    },

    // * 关闭消息提醒
    closeNotify() {
      if (this.isShowMsgNotify) {
        this.isShowMsgNotify = false
      }
      if (this.unreadCountMsg > 0) {
        this.unreadCountMsg = 0
      }
    },

    // * 处理滚动
    hangdleScroll(e) {
      if (e.srcElement.scrollTop + e.srcElement.offsetHeight >= e.srcElement.scrollHeight) {
        console.log('changeScrollModel:::::')
        this.lastScrollPosition = e.srcElement.scrollTop
          /** 手动滚动置底部是 关闭所有提醒 */
        if (this.isShowMsgNotify) {
          this.isShowMsgNotify = false
          this.unreadCountMsg = 0
        }
      }
    },

    // * 滚动到底部
    scrollToBottom() {
      this.$nextTick(() => {
        this.$refs.listBox.scrollTop = this.$refs.listBox.scrollHeight
        this.lastScrollPosition = this.$refs.listBox.scrollTop
        /** 如果存在消息提醒 则关闭 */
        if (this.isShowMsgNotify) {
          this.isShowMsgNotify = false
          this.unreadCountMsg = 0
        }
      })
    },


    /**
     * 加载更多历史消息
     * initHeight 初始高度
     */
    loadMoreHistoryMsg() {
      let msgId 
      if (Object.keys(this.messageObject).length) {
        msgId =  (this.messageObject[Object.keys(this.messageObject)[0]].messageObject.msgId - 1).toString()
      } else {
        msgId = 0
      }

      this.isPauseScroll = true;
      let initNode = this.$el.getElementsByClassName('v-msg-list-item')[0]
      this.getHistoryMsg(
        this.id,
        10,
        msgId,
      ).then(msg => {
        this.$nextTick(() => {
          if (msg.length) {
            if (initNode === undefined) {
              this.isPauseScroll = false
              return
            }  

            if (this.chatType === 2) {
              this.getGroupMsgUnreadCount()
            }
            initNode.scrollIntoViewIfNeeded(false)
            setTimeout(() => {this.isPauseScroll = false}, 10)
          }
        })
      })
    },

    /**
     * selectMultiItem 选中或取消选中项回调处理
     * @param {Object} item 选中项消息体
     * @param {String} name 选中项消息发送人姓名
     * @param {Boolean} isChecked: Boolean 是否选中
     */
    selectMultiItem({ item, isChecked }) {
      console.log('item...', item)
      // 特殊处理文件和图片消息一键发送
      let isFilterType = item.msgType == 5 || item.msgType == 6;
      // 是否是自己发送的消息
      let isSelfSend = item.fromId == this.user_account.userId;
      if (!isFilterType || !isSelfSend) {
        this._handleMixMsg(item, isChecked)
      } else {
        console.log('get imgUrl...')
        let getMessagesParam = { targetId: item.targetId, count: 1, msgId: item.msgId, flag: 2}
        this.$Service.chat.getMessages(getMessagesParam, resp => {
          console.log('getMessages', resp)
          if (item.msgType == 5) {
            item.mainUrl = resp.msgs[0].mainUrl
            item.thumbUrl = resp.msgs[0].thumbUrl
          } else if (item.msgType == 6) {
            item.url = resp.msgs[0].url
          }
          this._handleMixMsg(item, isChecked)
        });
      }
    },

    // * 处理actionbox的显隐
    handleActionBoxShow(value) {
      this.$emit('handleActionBoxShow', value)
    },

    /**
     * _handleMixMsg 处理混合消息
     * @param {Object} item 
     * @param {Booleen} isChecked 是否选中
     */
    _handleMixMsg(item, isChecked) {
      console.log('_handleMixMsg', item)
      let chatObjectInfo = this.userInfo[item.fromId]
      console.log('chatObjectInfo', this.userInfo[item.fromId])
      let singleMessage = {
        userName: chatObjectInfo.name || chatObjectInfo.remark,
        userPic: chatObjectInfo.thumbAvatar,
        userSex: chatObjectInfo.gender
      }
      console.log('_handleMixMsg ========>', msgStructure(item).messageObject)
      let msg = Object.assign(singleMessage, msgStructure(item).messageObject)
      isChecked && this.$set(this.mixTextMessage, msg.msgId, msg)
      !isChecked && this.$delete(this.mixTextMessage, msg.msgId)
    },

    /**
     * @param {Number} type 右键类型 1 头像右键菜单 2 消息右键菜单
     * 头像右键菜单 单聊：添加好友（陌生人），查看资料 群聊：添加好友（陌生人），查看资料，@他
     * 消息右键菜单 删除 转发 5分钟之内支持撤回
     */
    addMenu(item, arg) {
      console.log('item', item,this.memberInfo)
      this.selectActive = item.messageObject
      if (arg.type === 1) { //头像右键菜单
        this.footerDivider = ''
        this.headDivider = ''
        
        if (this.chatType === 2 && this.userInfo[item.messageObject.fromId]) this.menuList.push(this.$t('chat.atTa'));
        this.menuList.push(this.$t('chat.detail'))  /** 查看资料 */
      
        if (!this.contact_contactList[item.messageObject.fromId]) {  /** 如果此人为陌生人 新增添加好友 */
          this.menuList.push(this.$t('organizations.addFriend'))
        }  
      } else { // 消息右键菜单
       
        console.log('===============',this.isGroupEid)
        if(this.isGroupEid && this.msgTopSwitch()){
          this.menuList.push('置顶')
        }
        //console.log('msgTopSwitch',this.msgTopSwitch(),this.isGroupEid)
        if (item.messageObject.preDefined && JSON.parse(item.messageObject.preDefined).RtcFile) return //文件直传不显示右键菜单
        if (this.isOpenAction) return // 组合消息
        if (!arg.isMsgSuccess) { // 失败消息
          this._handleFailMsgMenu(arg)
          return
        }

        if (this.selectActive.msgType === 2 && !arg.isSpecialMsg) {
           this.headDivider = this.$t('chat.copy')  // 头部分组
        }

        if (this.selectActive.msgType === 89) {
          this.menuList.push(this.$t('chat.silentPlay'))
        }

        this.footerDivider = this.$t('chat.delete')  // 尾部分组
        console.log('this.footerDivider', this.footerDivider)
        if (this.selectActive.msgType !== 3 && !arg.isSpecialMsg) {
          this.menuList.push(this.$t('chat.forward'))
        }
        if (this.selectActive.msgType === 5) { // 图片支持右键另存为
          if (!this.chat_chatDicValue[IMG_DICVALUE]) { // 服务器不支持则默认允许另存为
            this.menuList.push(this.$t('chat.saveAs'));
          } else if (this.chat_chatDicValue[IMG_DICVALUE] === '1') { // 服务器支持，则获取后台配置是否允许另存为
            this.menuList.push(this.$t('chat.saveAs'));
          }
        }
        
        if (this.selectActive.msgType === 6 && this.selectActive.defaultPath) {
          this.menuList.push(this.$t('chat.saveAs')); // 文件在默认路径时支持另存为
        }
        let commonType = [2, 3, 6, 9, 89]

        let collectType = [...commonType, 5]
        if (collectType.includes(this.selectActive.msgType) && this.work_isOpenNotes) {
          this.menuList.push(this.$t('chat.collection'));
        }
        
        // let msgRemindType = [...commonType, 4]
        // if (msgRemindType.includes(this.selectActive.msgType)) {
        //   this.menuList.push(this.$t('account.msgNotification'));
        // }
        /**
         * 【消息置顶】
         * 右键菜单时 获取该消息置顶状态（是/否）
         */
        // if (this.msgTopSwitch()) { // 消息置顶开关
        //   this.menuList.push(this.msgTopStatus()?'取消置顶':'置顶'); // 消息置顶状态
        // }
       
        let personalInfo = this.userInfo[this.user_account.userId]
        if (this.selectActive.fromId === this.user_account.userId) {
          if (this.chatType === 2) {
            this.menuList.push(this.$t('chat.msgStatus'));
          } 
          console.log('personalInfo.memberType', personalInfo.memberType)
          if (Date.parse(new Date()) - this.selectActive.time < 300000 && personalInfo.memberType !== 3) {
            this.menuList.push(this.$t('chat.Recall'));
          }
        }

        if (personalInfo.memberType === 3) {
          this.menuList.push(this.$t('chat.Recall'));
        }
        if (!arg.isSpecialMsg) {
          this.menuList.push(this.$t('chat.more'))
        }
      }

      this.setMenuAttributes(arg)
    },

    /**
     * 消息置顶开关
     * - 必要条件：1.后台配置开启
     * - 设置条件：1.文本消息 2.群会话 3.权限
     * @return {Boolean} - On/Off
     */
    msgTopSwitch() {
      if (this.isGroupEid) {
        let memberType = this.userInfo[this.user_account.userId].memberType
        // 成员权限是否满足匹配
        let isMatchMemberPermission = memberType && (memberType===2 || memberType===3)
        // 消息类型是否满足匹配
        let isMatchMsg = this.selectActive.msgType === 2
        // 会话类型是否满足匹配
        let isMatchChat = this.chatType === 2
        return isMatchMemberPermission && isMatchMsg && isMatchChat
      }
      return false
    },

    /**
     * 消息置顶状态：置顶/取消置顶
     */
    msgTopStatus() {
      return this.$Service.chat.isGroupTopMsgSync({
        targetId: this.id,
        relateMsgId: this.selectActive.msgId
      })
    },
    /**
     * 发送失败消息的右键菜单
     */
    _handleFailMsgMenu(arg) {
      this.footerDivider = ''
      this.menuList.push(this.$t('chat.delete'))
      if ((this.selectActive.msgType & 0x00FF) === 2 && !arg.isSpecialMsg) {
        this.headDivider = this.$t('chat.copy')
      }
      this.setMenuAttributes(arg)
    },
    /**
     * 计算右键菜单位置、宽高
     */
    setMenuAttributes(arg) {
      this.isShowRightMenu = true
      let minusWidth = 88

      minusWidth =
        arg.event.clientX + minusWidth < document.body.clientWidth
          ? 0
          : minusWidth + 8

      this.currentPos.left = arg.event.clientX - minusWidth + 'px'
      let addHeight = (this.menuList.length) * 33 + 16
      if (this.headDivider) addHeight += 33
      if (this.footerDivider) addHeight += 33
      addHeight =
        addHeight + arg.event.clientY < document.body.clientHeight
          ? 0
          : addHeight + 8

      this.currentPos.top = arg.event.clientY - addHeight + 'px'
    },

    // * 关闭右键按钮
    closeRightMenu() {
      this.isShowRightMenu = false
      this.menuList=[]
      this.headDivider = ''
      this.footerDivider = ''
      this.isAutoShowMsgState = false
    },

    // * 重新编辑 
    reEdit(arg) {
      this.$emit('reEdit', arg)
    },

    // * 消息列表中触发了@
    hasAtInList(arg) {
      this.$emit('hasAtInList', arg)
    },

    /* 
     * handleEarseMsg处理橡皮擦消息
     * onConfirm 确认  删除消息处理 当天获取到当天的消息 更具msgid删除  删除全部 deleteMessageByTime
     * onCancel 取消 更行消息的deal  字段
     */
    async handleEarseMsg(msg) {
      this.isShowEarseBox = true
      let isEarseToday = msg.msgObj.body.includes('today') ? true : false
      let earseTypeValue = isEarseToday? this.$t('chat.earseToday') : this.$t('chat.earseAll')
      let userName
      if (this.userInfo[msg.msgObj.fromId]) {
        userName = this.userInfo[msg.msgObj.fromId].name||this.userInfo[msg.msgObj.fromId].remark
      } else {
        userName = await this.getUserInfo(msg.msgObj.fromId)
      }
      this.$Service.log(`userName handleEarseMsg ${userName||''}`)
      if (this.chatType === 1) {
        console.log('msg::', msg)
        this.$dialog.confirm(
          {
            message: this.$t('chat.earseDelete', {value: earseTypeValue}),
            confirmText: this.$t('chat.agree'),
            cancelText: this.$t('chat.reject'), 
            onConfirm: () => {
            this.isShowEarseBox = false
            if (isEarseToday) {
              this.delMsgFromDay(this.id, msg.msgObj.time).then(() => {
                this.handleReceiptWeak({tipType: 5, tipTime: new Date().getTime(), operType: 1, isStore:1,  operUser: this.user_account.name,  userInfo:userName, limitRange: [msg.msgObj.fromId], body: '&:delete|today'}) 
              })
            }  else {
              this.deleteMessageById(this.id).then(() => {
                this.handleReceiptWeak({tipType: 5, tipTime: new Date().getTime(), operType: 1, isStore:1,  operUser: this.user_account.name,  userInfo: userName, limitRange: [msg.msgObj.fromId], body: '&:delete|all'}) 
              })
            }
        },
        onCancel:()=>{ 
          console.log('onCancel.....');
          this.isShowEarseBox = false
          this.updateEarseMsg(msg)
          this.handleReceiptWeak({tipType: 5, operType: 2, isStore:1, operUser: this.user_account.name, userInfo:userName, limitRange: [msg.msgObj.fromId]}) 
        }});
      } else {
        console.log('isEarseToday', isEarseToday)
        if (isEarseToday) {
          await this.delMsgFromDay(this.id, msg.msgObj.time)
        }  else {
          await this.deleteMessageById(this.id)
        }
        this.isShowEarseBox = false
        this.handleReceiptWeak({tipType: 5, operType: 1, isStore:1,  operUser: this.user_account.name,  userInfo: userName, limitRange: [msg.msgObj.fromId]})
        this.$toast.open({duration: 5000, message: this.$t('chat.earseGroupTip', {name:userName, time:earseTypeValue}), position: 'is-top', type: 'is-warning'});
      }
      this.pendingEarseMsg = {}
    },

    getUserInfo(id) {
      console.log('getUserInfo', id)
      return new Promise(resolve => {
        this.$Service.search.getUserInfo({userId: id}, userInfo => {
          console.log('getUserInfo', userInfo)
          let name
          if (userInfo&&userInfo.users.name) {
            name = userInfo.users.name
          } else {
            name = ''
          }
          this.$Service.log(`getUserInfo recepit name ${name||''}`)
          resolve(name)
        })
      })
    },

    handleEarseType(msg) {
      console.log('handleEarseType::', msg)
     
      if (this.isOpen) {
        if (this.isShowEarseBox) {
          this.updateMsgDeal(msg)
          // this.updateEarseMsg(msg)
          return
        }
        this.handleEarseMsg(msg)
        this.updateMsgDeal(msg)
      } else {
        this.pendingEarseMsg = msg
      }
    },


    handleReceiptType(msg) {
      if(this.isOpen&&this.isWinFocus) {
        this.handleReceipt(msg)
      } else {
        this.$set(this.pendingReceiptMsg, msg.msgId, msg)
      }
    },
    async handleReceipt(msg) {
      let isReceipt = _.endsWith(msg.body, '<<<')
      let limitRange,
      relatedUsers
      if (isReceipt) {
        relatedUsers = [msg.fromId]
      } else {
        limitRange = [msg.fromId]
      }
      let userName
      // let userName = this.userInfo[msg.fromId] && this.userInfo[msg.fromId].name||this.userInfo[msg.fromId].remark
      if (this.userInfo[msg.fromId]) {
        userName = this.userInfo[msg.fromId].name||this.userInfo[msg.fromId].remark
      } else {
        userName = await this.getUserInfo(msg.fromId)
      }
      // if (!userName) {
      //  userName =  await this.getUserInfo(msg.fromId)
      // }
      this.$Service.log(`userName recepit userName ${userName||''}`)
      if (!this.hasAtAllMember(msg)) { // 如果没有 @全体成员，则阅后回执
        this.handleReceiptWeak({tipType: 4, operType: 1, operUser: this.user_account.name, userInfo: userName, relatedUsers:relatedUsers, limitRange: limitRange, tipTime: msg.time}) 
      } else { // 如果@全体成员并且群人数小于50则阅后回执，否则不回执
        if (Object.keys(this.userInfo).length < 50) {
          this.handleReceiptWeak({tipType: 4, operType: 1, operUser: this.user_account.name, userInfo: userName, relatedUsers:relatedUsers, limitRange: limitRange, tipTime: msg.time}) 
        }
      }
      this.updateMsgDeal(msg)
      if (this.pendingReceiptMsg && this.pendingReceiptMsg[msg.msgId]) {
         this.$delete(this.pendingReceiptMsg, msg.msgId)
      }
    },
    /**
     * 是否消息relatedUsers/limitRange中有@全体成员
     * @param {Object} msg - 消息体
     */
    hasAtAllMember(msg) {
      let relatedUsersInclude = msg.relatedUsers.length && msg.relatedUsers.includes(msg.targetId)
      let limitRangeInclude = msg.limitRange.length && msg.limitRange.includes(msg.targetId)
      return relatedUsersInclude || limitRangeInclude
    },

    getUserInfo(id) {
      console.log('getUserInfo', id)
      return new Promise(resolve => {
        this.$Service.search.getUserInfo({userId: id}, userInfo => {
          console.log('getUserInfo', userInfo)
          let name
          if (userInfo&&userInfo.users.name) {
            name = userInfo.users.name
          } else {
            name = ''
          }
          this.$Service.log(`getUserInfo recepit name ${name||''}`)
          resolve(name)
        })
      })
    },
    updateEarseMsg(msg) {
      let updateMsg = Object.assign({}, msg.msgObj)
      updateMsg.deal = true
      this.$Service.chat.updateMsg(updateMsg, resp => {
        console.log('updateMsg::', resp)
      })
    },
    openChatGroupNotice(param){
      this.$emit('openChatGroupNotice', param);
    },
    showAddRemind(msgBody) {
      this.$emit('showMsgRemind',msgBody)
    }
  },
  computed: {
    getModel () {
      return this.user_localConfig.editBox_mode !== 'editBox_standard' ? 'classic-list' : 'standard-list'
    },
    ...mapGetters([
      'user_account',
      'contact_contactList',
      'chat_chatList',
      'user_localConfig',
      'chat_chatContent',
      'chat_chatContentTop',
      'user_systemConfig',
      'chat_chatDicValue',
      'work_isOpenNotes'
    ])
  },
  components: {
    // GroupMemberInfo,
    MsgMenuOperate,
    Message: function(resolve) {
      require(['../../../ui/components/message/Message.vue'], resolve)
    }
  }
}
</script>

<style lang="scss" scoped>
.msglist-area {
  position: relative;
  padding: 0 4px 10px 20px;
  margin-right: 4px;
  box-sizing: border-box;
  width: 100%;
  display: flex;
  flex:1;
  flex-direction: column;
  overflow-x: hidden;
  .load-area {
    display: flex;
    justify-content: center;
    margin-left: 66px;
  }
  .loaders {    
      position: relative; 
      width: 100px; 
      height: 60px;
      border-radius: 50%; 
    }
  .loader-3 .dot { width: 8px; height: 8px; background: #eeeeee; border-radius: 50%; position: absolute; top: 20px; }
  .loader-3 .dot1 { left: 0px; -webkit-animation: dot-jump 0.5s cubic-bezier(0.77, 0.47, 0.64, 0.28) alternate infinite; animation: dot-jump 0.5s cubic-bezier(0.77, 0.47, 0.64, 0.28) alternate infinite; }
  .loader-3 .dot2 { left: 10px; -webkit-animation: dot-jump 0.5s 0.1s cubic-bezier(0.77, 0.47, 0.64, 0.28) alternate infinite; animation: dot-jump 0.5s 0.1s cubic-bezier(0.77, 0.47, 0.64, 0.28) alternate infinite; }
  .loader-3 .dot3 { left: 20px; -webkit-animation: dot-jump 0.5s 0.2s cubic-bezier(0.77, 0.47, 0.64, 0.28) alternate infinite; animation: dot-jump 0.5s 0.2s cubic-bezier(0.77, 0.47, 0.64, 0.28) alternate infinite; }
  .loader-3 .dot4 { left: 30px; -webkit-animation: dot-jump 0.5s 0.3s cubic-bezier(0.77, 0.47, 0.64, 0.28) alternate infinite; animation: dot-jump 0.5s 0.3s cubic-bezier(0.77, 0.47, 0.64, 0.28) alternate infinite; }
  
 @-webkit-keyframes dot-jump {
    0% {
    -webkit-transform: translateY(0);
    transform: translateY(0);
    }
    100% {
    -webkit-transform: translateY(-15px);
    transform: translateY(-15px);
    }
    }
  .classic-list {
    bottom: 160px;
  }
  .standard-list {
    bottom: 104px;
  }
  .msg-notify {
    position: fixed;
    right: 27px;
    display: flex;
    color: $--color-success;

    box-shadow: $--box-shadow-elevation;;
    background: #fff;
    padding: 4px;
    font-size: $--font-size-small;
    .notice-msg-count {
      cursor: pointer;
      display: flex;
      align-items: center;
      .msg-to-bottom {
        transform: rotate(90deg);
        font-size: 10px;
      }
    }
    .notice-close {
      border-left: solid 1px $--border-color-grey;
      margin-left: 10px;
    }

  }
  .notice-close-expend {
    right: 232px;
  }
  .load-more-history-message {
    text-align: center;
    color: get-blue-color(darken-4);
    font-size: $--font-size-small;
    .load-more-msg-btn {
      &:hover {
        text-decoration: underline;
          color: get-blue-color(darken-2);
      }
    }
  }
}
</style>