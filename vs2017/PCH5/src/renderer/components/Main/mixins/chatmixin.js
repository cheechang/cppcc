/**
 * @file      Manages the chat's common methods for the main page.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.9.10
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 * @mixin
 */
import { mapGetters } from 'vuex';
import { getLastMessage } from '../../Chat/message';
import {SubType, RtcStatus} from '../../../../rtc/file/constant';
import MsgMxin from '../../Chat/msgMixin.js';
import GroupMixin from '../../Group/GroupMixin';
import { msgStructure } from "../../Chat/Msg";

const CHAT_TYPE_SYSTEM = '10000',   //  系统消息
      CHAT_MSG_STATE_FAILUE = 2;    //  发送失败消息类型

const MSG_TYPE_HTML = 1,
      MSG_TYPE_TEXT = 2,
      MSG_TYPE_IMAGE = 5,
      MSG_TYPE_TIP = 8,
      MSG_TYPE_VIDEO = 14,
      MSG_TYPE_WITHDRAW = 18,
      MSG_TYPE_TEMPLATE = 26,
      MSG_TYPE_NINEIMG = 28,
      MSG_TYPE_MSGREADFLAG = 34,
      MSG_TYPE_TOP = 64,
      MSG_TYPE_MICVIDEO = 89,
      MSG_TYPE_SYSTEM = 100;

const MSG_SUBTYPE_VIDEO = 14;

const SOUND_REMIND = {
  OPEN: 'OPEN',
  CLOSE: 'CLOSE'
};

const mixin = {
  mixins: [MsgMxin, GroupMixin],
  data() {
    /**
     * @param {bool}   - isOpenForward 是否显示消息转发界面
     * @param {string} - forwardMode 转发的消息类型
     * @param {Object} - imgPreviewParam 图片预览转发的参数
     */
    return {
      chattest: 'chattest',
      isOpenForward: false,
      isPermitSend: false,      //  意见反馈包是否压缩完成，true表示压缩完成
      zipFileSize: 0,
      forwardMode: '',
      imgPreviewParam: {},
      audio: require('vrv-static/resources/audio/8858.mp3'),
      audioGroupTone: require('vrv-static/resources/audio/push6.mp3'),
      msgHandler: null,
      lastRouteId: '',          //  最后一次会话路由ID，为了切换路由后，下次切换回来打开之前的会话
      handleType: '',           //  转发的类型 发送文件还是意见反馈
      dbPath: '',               //  数据库路径
    };
  },
  computed: {
    ...mapGetters([
      'user_account',
      'chat_chatContent',
      'chat_chatList',
      'chat_rtc_file_list'
    ])
  },
  methods: {
    initChat() {
      this.msgHandler = new Map([
        [MSG_TYPE_TEXT, this._msgTextHandle],
        [MSG_TYPE_TIP, this._msgTipHandle],
        [MSG_TYPE_VIDEO, this._msgVedioHandle],
        [MSG_TYPE_WITHDRAW, this._msgWithdrawHandle],
        [MSG_TYPE_TEMPLATE, this._msgTemplateHandle],
        [MSG_TYPE_MSGREADFLAG, this._msgReadFlagHandle],
        [MSG_TYPE_TOP, this._msgTopHandle],
        [MSG_TYPE_SYSTEM, this._msgSystemHandle]
      ]);
    },
    recvNewMsg(chat) {
      this.$Service.log('recv new message');
      //  通知托盘进行消息提醒
      //  获取最新消息的内容
      console.log('in recvNewMsg ', chat);
      let msg = Object.assign({}, chat);
      //  如果是文本消息，设置为不转换文本内容
      msg.banChangeText = true;
      //  获取最后一条消息内容
      msg.lastMsg = getLastMessage(msg, null);
      //  可以在tray中记录一个内容，更新由上层通知
      // msg.openTrayTip = this.user_localConfig.tray_tip === 'OPEN';
      this.$ipc.send('newMessage', msg);
        
      //  判断是否开启了声音提醒
      if (this.user_localConfig.sound_remind !== SOUND_REMIND.OPEN) {
        return;
      }
      this.$refs.ring.play();
      //  判断会话类型，如果是单人会话则直接播放提示音
      // if (msg.chatType === 1) {
      //   this.$refs.ring.play();
      //   return;
      // }

      // //  判断是否缓存了对应群的提示音
      // if (!this.user_groupToneList || !this.user_groupToneList[msg.id]) {
      //   //  如果没有缓存或者没有找到对应群的提示音，则需要播放默认铃声
      //   this.audioGroupTone = require('vrv-static/resources/audio/push6.mp3');
      //   this.getGroupSoundFromSDK(msg.id);
      // } else {
      //   //  如果存在缓存的铃声，则播放对应的铃声
      //   let currentTone = this.user_groupToneList[msg.id].split('.')[0];
      //   this.audioGroupTone = this.audioGroupTone === `/media/${currentTone}--audio.mp3` ? 
      //                         this.audioGroupTone : require(`vrv-static/resources/audio/${currentTone}.mp3`);
      // }
      // this.$nextTick(()=>{
      //   this.$refs.groupring.play();
      // });
    },

    /**
     * 文件转发接口
     * @description 接收托盘意见反馈及图片查看器发起的转发.
     */
    forwardFile(e, file) {
      if (!['forward', 'sendImg'].includes(file.mode)) {
        //  如果不是则是意见反馈
        this.forwardUnzipFile(e, file);
        return;
      }
      this.isOpenForward = true;
      this.forwardMode = args.mode;
      this.imgPreviewParam = args;
    },

    /**
     * 意见反馈文件转发
     * @description 接收托盘意见反馈及图片查看器发起的转发.
     */
    forwardUnzipFile(e, args) {
      this.dbPath = args.dbPath;
      this.isPermitSend = false;
      this.$dialog.confirm({
        message: this.$t('chat.sendLog'),
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          this.isOpenForward = true;
          this.handleType = 'suggestion';
        },
        onCancel: () => {
          this.isOpenForward = false;
        }
      });
    },

    /**
     * 意见反馈文件发送
     * @description 接收托盘意见反馈及图片查看器发起的转发.
     */
    onSendZipFile(e, arg) {
      this.isPermitSend = true;
      this.zipFileSize = arg;
    },

    /**
     * 窗口激活事件响应函数
     * @description 当主窗口被激活/获取焦点时响应，接收 window-focus 事件.
     * 主要是处理设置消息已读
     * 
     * @todo 可以放至会话模块中
     */
    onWindowFocus(e) {
      if (!['ChatRightArea', 'ChatSystem'].includes(this.$route.name)) {
        //  如果当前路由不是会话页则不设置已读
        return;
      }
      let currentChat = this.chat_chatList[this.$route.query.id];
      if (!currentChat || currentChat.unreadCount === 0) {
        //  如果当前会话没有未读消息，则退出
        return;
      }
      this.setMessageRead(currentChat.id);  //  在msgMixin中
    },

    /**
     * 更新各个会话中用户自己的头像
     */
    _updateSessionsAvatar(avatar) {
    
      //  判断文件是否存在，不存在则退出
      let fileOperateParam = {
        filepath: avatar,
        type: 0
      }
      if (!this.$Service.file.fileOperate(fileOperateParam)) {
        return
      }

      //  获取会话列表中对应的自己的头像
      for (let id in this.chat_chatContent) {
        let type = this.$Service.config.getUserTypeById({ targetId:  i });
        if (type !== 1) {
          continue;
        }
        this.$store.commit('UPDATE_MEMBER_AVATAR', {id, avatar, userId: this.user_account.userId})
      }
    },

    /**
     * 更新最后一次会话路由ID
     * 便于其他模块返回会话模块时 定位于之前的会话
     */
    updateLastRouteId(id) {
      this.lastRouteId = id;
    },

    /**
     * @breif 所有的会话模块消息推送处理
     */
    regChatNotify() {
      this.regRecontactCb();
      this.regMsgNoticeCb();
      this.regOfflineMsgCb();
      this.regBadWordUpdateCb();
    },

    /**
     * @breif 注册最近会话监听
     */
    regRecontactCb() {
      this.$Service.chat.regRecontactCb(null, this._regRecontactCbHandler);
    },
    _regRecontactCbHandler(resp) {
      console.log('resp::::', resp)
      if (!resp.chats.length) {
        return;
      }
      let recentChat = Object.assign({}, resp);
      let checkedInfo = this._checkFailMsg(recentChat.chats[0]);
      recentChat.chats[0] = Object.assign(recentChat.chats[0], checkedInfo);

      //  过滤被拒绝的好友消息
      recentChat.chats = _.filter(recentChat.chats, (element) => {
        if (element.isHidden === 1) {
          this.$Service.log(`需要隐藏的最近会话::::id:${element.id}:::name${element.name}`)
          return
        };
        return element.subType !== 203;
      });
      if (!recentChat.chats || !recentChat.chats.length) {
        return;
      }

      //  设置消息已读
      let isWindowFocus = this.$getWindowStatus();
      console.log('setMessagRead',checkedInfo.unreadCount,isWindowFocus)

      if (checkedInfo.unreadCount > 0 && this.$route.query.id === checkedInfo.id && isWindowFocus) {
        //  设置已读
        if(checkedInfo.msgType !== 100){
          this.$Service.chat.setMessageRead({targetId: checkedInfo.id, msgId: '0'})
        }else{
          let param ={
            type:checkedInfo.chatType,
            msgs:[checkedInfo.lastMsgId]
          }
          console.log('setMessagRead',param)
          this.$Service.sysMsg._sysmsg.setMessagRead(param,res =>{
          this.$Service.log(`setMessageRead:::::::    ${JSON.stringify(res)}`)
          })
        }
      }
      //  将会话列表存入vuex中
      this.$store.dispatch('SET_CHATLIST', recentChat);
      
      //  如果在会话中发送新消息，需要将会话列表的滚动条置顶
      const MSG_TYPE_SENDING = 8000;
      if (checkedInfo.sendUserId === this.user_account.userId && checkedInfo.msgType > MSG_TYPE_SENDING) {
        this.$signalMonitor.$emit('isScroll', checkedInfo.id);
      }

      //  新消息通知 判断消息免打扰状态
      if (checkedInfo.unreadCount === 0) {
        return;
      }
      //  判断是否设置了免打扰，先判断全局免打扰，再判断单个会话免打扰
      const GLOBAL_CHAT_DISTURB = 2,
            CHAT_DISTURB = 3;
      if (this.user_localConfig.msg_remind === GLOBAL_CHAT_DISTURB || checkedInfo.disturbSet === CHAT_DISTURB) {
        return;
      }
      this._chatNotify(checkedInfo);
    },

    /**
     * @breif 决定通知托盘 或者声音提醒 
     * @param {*} chat - 收到新会话列表的第一条会话信息
     */
    _chatNotify(chat) {
      const REMIND_MODE_TIME = 5;
      if (chat.msgRemindMode !== REMIND_MODE_TIME) {
        this.recvNewMsg(chat);
        return;
      }
      
      //  处理设置的时间段免打扰方式
      this.$Service.user.getGlobalNoDisturbListMode(null, resp => {
        let isContinue = true;
        let currentTime = new Date().getHours() * 3600 + new Date().getMinutes() * 60;
        resp.modeInfos.forEach(info => {
          if (!info.isOpen) {
            return;
          }
          info.endTime = info.startTime > info.endTime ? info.endTime + 86400 : info.endTime;
          isContinue = info.startTime <= currentTime && info.endTime >= currentTime;
          return;
        });
        if (!isContinue) {
          return;
        }
        this.recvNewMsg(chat);
      });
    },


    /**
     * @breif 检查是否存在发送失败的消息，如果存在则过滤掉
     * @param {object} chatinfo 
     * @return {object} 返回检查后的信息
     */
    _checkFailMsg(chatinfo) {
      let info = chatinfo;
      //  如果是系统消息或者
      if (info.id === CHAT_TYPE_SYSTEM) {
        return info;
      }
      if (this.$route.query.id === info.id) {
        return info;
      }

      if (!this.chat_chatList.hasOwnProperty(info.id)) {
        return info;
      }

      let chatItem = this.chat_chatList[info.id];
      if (!chatItem.hasOwnProperty('state') || chatItem.state !== CHAT_MSG_STATE_FAILUE) {
        return info;
      }
      info.state = CHAT_MSG_STATE_FAILUE;
      return info;
    },
    /**
     * 
     * @param {*群id} id 
     */
    getChatMsgTopList(id) {
      console.log('id:::::', id)
      let getGroupTopMsgByIdParam = {
        groupId: id,
        msgid: 0,
        pageNum: 1,
        pageSize: 100
      };
      console.log('getGroupTopMsgByIdParam', JSON.stringify(getGroupTopMsgByIdParam));
      this.$Service.chat.getGroupTopMsgById(getGroupTopMsgByIdParam, resp => {
        console.log('getGroupTopMsgById---msgs', resp.msgs&&JSON.stringify(resp.reminderMsgs))
        if(resp.code === 0){
          this.$store.commit('CLEAR_CHATCONTENT_TOP', {})
          _.forEach(resp.reminderMsgs, element => {
              this.$store.dispatch('SET_CHATCONTENT_TOP', element)
          })
        }
        else{
          this.$Service.log(`getGroupTopMsgById:${resp.code},id:${id}`);
        }
      })
    },
    /**
     * @breif 监听最新消息
     *
     */
    regMsgNoticeCb() {
      this.$Service.chat.regMsgNoticeCb(null, this._regMsgNoticeCbHandler);
    },
    _regMsgNoticeCbHandler(resp) {
      console.log('收到新消息', resp);
      if(resp.msgType === 8 && resp.tipType === 3 && (resp.operType == 6||resp.operType === 7)){
        this.getChatMsgTopList(resp.targetId)
      }
      if(resp.msgType== 18 && resp.fromId !== this.user_account.userId){
        if(resp.groupType !== undefined && resp.groupType==='eid'){
          this.deleteMessageById(resp.msgId);
          this.delMsg(resp.targetId,resp.revokeMsgId);
          return ;
        }
      }
      if(resp.msgType === 100){
        this._msgSystemHandle(resp);
        return;
      }
      let newMsg = Object.assign({}, resp)
      let isHandleStop = false;

      let handler = this.msgHandler.get(newMsg.msgType);
      // 一般情况下消息不需要回调处理，直接构造消息气泡
      if (handler) {
        isHandleStop = handler.call(this, newMsg);
      }
      // 接收的消息如果不需要构造消息气泡，则不会继续执行（已读未读处理、消息置顶等）
      if (isHandleStop) {
        console.log(`收到${newMsg.msgType}类型消息，中止执行`)
        return
      }

      this.$Service.log(`receiveNewMsg  targetId:${newMsg.targetId}::messageId:${newMsg.msgId}::messageType:${newMsg.msgType}`);

      if (!this.chat_chatContent[newMsg.targetId]) {
        return;
      }
      
      //  修改 单聊 已读未读状态
      this._msgUnreadStateHandle(newMsg);

      //  存入VUEX
      let msg = msgStructure(newMsg);
      this.$store.dispatch('SET_CHATCONTENT', msg);

      //  处理图片查看器打开的情况
      if ([MSG_TYPE_IMAGE, MSG_TYPE_NINEIMG].includes(newMsg.msgType)) {
        let result= this.$isOpenMediaMsgPreivew()
        if (result && result.isOpen && newMsg.targetId === result.mediaMsgPreivewId) {
          this.$ipc.send('handleSubWinMediaMsg', {winType: 'image' , operaType: 1, msg: newMsg} )
        }
      }
    },
    /**
     * @breif 消息提醒的处理函数
     * @param {*} msg - 消息提醒详细信息
     */
    _msgRemindHandle(msg) {
      // 预留收到消息提醒回调处理
      let remindMsg = Object.assign({},msg)
      console.log('remindMsg',remindMsg)
      
      console.log('JSON.parse',JSON.parse(remindMsg.msgProperties))
      remindMsg.msgType = JSON.parse(remindMsg.msgProperties).realMsgType
      console.log('remindMsg.msgType',remindMsg.msgType)
      console.log('消息提醒成功啦！')
    },
    /**
     * @breif 模板消息的处理函数
     * @param {*} msg - 模板消息详细信息
     */
    _msgTemplateHandle(msg) {
      // 消息提醒
      if (msg.subType === 1) {
        this._msgRemindHandle(msg);
        return;
      }
      //  处理视频会议对应的模板消息
      let detailUrl = null;
      try {
        detailUrl = JSON.parse(msg.detailUrl)
      } catch(error) {
        detailUrl = null;
      }
      if (msg.deal || !detailUrl) {
        //  该消息已处理或未能获取正确的URL信息
        return;
      }
      const { subType, roomID, deviceType } = detailUrl;
      if (subType !== MSG_SUBTYPE_VIDEO || !roomID) {
        return true;
      }

      let { userId } = detailUrl;
      //  获取参会者名称
      const users = msg.toUsers.split(',');
      if(!userId && users.length > 0){
        userId = users[users.length-1];
      }
      
      //  如果是主叫方，则弹出视频会议界面
      const DEVICE_TYPE_PC = 1;
      if (userId === this.user_account.userId && deviceType === DEVICE_TYPE_PC) {
        this._openVideoMeeting(detailUrl, JSON.stringify(users));
      }
      this.updateMsgDeal(msg);
    },

    /**
     * @breif 打开视频会议窗口
     * @param {*} meetingInfo - 视频会议详细信息
     */
    _openVideoMeeting(meetingInfo, members) {
      let {roomID, startTime, serverUrl, serverPort} = meetingInfo;

      //  获取服务地址及端口号
      if (!serverUrl || !serverPort) {
        let serverInfo = this.$Service.rtc.getMultiServerSync();
        let {turnAddr} = serverInfo;
        if (turnAddr && turnAddr.indexOf(':') !== -1) {
          serverUrl = turnAddr.split(':')[0];
          serverPort = turnAddr.split(':')[1];
        }
      }

      //  拼接视频会议地址信息
      let winUrl=`vrv-static/plugins/mediadood/index.html?roomId=${roomID}&serverUrl=${serverUrl}&serverPort=${serverPort}&displayName=${this.user_account.name}&userID=${this.user_account.userId}&startTime=${startTime}&members=${members}`;
      
      let winType='mediadood';
      let winTitle=this.$t('chat.douShipin');

      let meetingObj = { winUrl, winType, winTitle, shapeType: 'normal'}
      this.$ipc.send('new-window',meetingObj);
    },

    /**
     * @breif 处理已读未读标识消息
     * @param {*} msg - 消息详细信息
     */
    _msgReadFlagHandle(msg) {
      if (!this.chat_chatContent[msg.targetId]) {
        return true;
      }
      this.$store.dispatch('UPDATE_UNREADCOUNT', msg);
      return true;
    },

    /**
     * @breif 处理置顶消息
     * @param {*} msg - 消息详细信息
     */
    _msgTopHandle(msg) {
      const TOP_SUBTYPE_GROUPNOTICE = 1,  //  群公告
            TOP_SUBTYPE_SET = 2,          //  设置置顶
            TOP_SUBTYPE_REMOVE = 3;       //  移除置顶
      if (msg.subType === TOP_SUBTYPE_GROUPNOTICE) { // 群公告需要构建消息气泡
        this.$signalMonitor.$emit('sendGroupNotice', msg);
        return;
      }
      let action = msg.subType === TOP_SUBTYPE_SET ? 'SET_CHATCONTENT_TOP' : 'DEL_CHATCONTENT_TOP';
      this.$store.dispatch(action, msg);
      // 消息置顶
      return true;
    },

    /**
     * @breif 处理文本消息
     * @param {*} msg - 消息详细信息
     */
    _msgTextHandle(msg) {
      const MSG_DO_EARASER = '&:delete|',
            MSG_DO_SHAKE = '&:flash';
      //  处理橡皮擦消息
      if (msg.body.includes(MSG_DO_EARASER)) {
        this._msgEraserHandle(msg);
        return;
      } 
      if (msg.body.includes(MSG_DO_SHAKE)) {
        this._msgShakeHandle(msg);
        return;
      }
    },

    /**
     * @breif 处理橡皮擦消息
     * @param {*} msg - 消息详细信息
     */
    _msgEraserHandle(msg) {
      //  同步移动端删除发送方消息  发送方是自己
      if (msg.fromId !== this.user_account.userId) {
        return;
      }

      if (msg.body.includes('&:delete|today')) {
        this.delMsgFromDay(msg.targetId, msg.time)
      } else {
        this.deleteMessageById(msg.targetId)
      }
    },
    /**
     * @breif 处理抖一抖消息
     * @param {*} msg - 消息详细信息
     */
    _msgShakeHandle(msg) {
      if (msg.fromId === this.user_account.userId) {
        return;
      }
      if(msg.targetIsGroup && !msg.relatedUsers.includes(this.user_account.userId)) {
        return;
      }
      this.$ipc.send('win-shake-event');
    },

    /**
     * @breif 处理橡皮擦消息 100
     * @param {*} msg - 消息详细信息
     */
    _msgSystemHandle(msg) {
      if (!this.$route.query.id || this.$route.query.id !== CHAT_TYPE_SYSTEM) {
        return;
      }
      this.$signalMonitor.$emit('respsysMsg', msg);
    },

    /**
     * @breif 处理弱提示消息 8
     * 直传消息的特殊处理(CANCEL_SENDER 取消发送 REFUSE 拒绝 TIMEOUT超时 BUSY_RECEIVER 接收繁忙)
     * @param {*} msg - 消息详细信息
     */
    _msgTipHandle(msg) {
      const RTCSubTypes = [SubType.CANCEL_SENDER, SubType.REFUSE, SubType.TIMEOUT, SubType.BUSY_RECEIVER];
      if (!RTCSubTypes.includes(msg.operType)) {
        return;
      }
      let fileInfo = JSON.parse(msg.fileInfo);
      let isSender = msg.fromId === this.user_account.userId
      this.$p2pUtils.responseCancel(msg.targetId, isSender, fileInfo)
      this.$store.commit('FILTER_DEL_RTC_FILE', {id: msg.targetId, msgId:  fileInfo.msgId})
      this.delMsg(msg.targetId, fileInfo.msgId)
    },

    /**
     * @breif 处理音视频消息 14
     * 直传消息的处理
     * @param {*} msg - 消息详细信息
     */
    _msgVedioHandle(msg) {
      const VIDEOTYPE = {
        FILE: 'file'
      };
      if (msg.videostatus === VIDEOTYPE.FILE) {
        let body = JSON.parse(msg.body);
        let fileInfo = body.fileInfo;
        let chatRtcList = this.chat_rtc_file_list;
        if (Object.keys(chatRtcList).length >= 1 && !chatRtcList[msg.targetId]) {
          return this.$p2pUtils.acceptOrReject(msg.targetId, this.user_account.userId, fileInfo, false, '', (fileCb) => {
          }, (msgCb) => {
            console.log('msgCb', msgCb)
          }, SubType.BUSY_RECEIVER )
        }

        if (body.subType === SubType.SEND && new Date().getTime() - msg.time < 300000) {
          msg.fileName = fileInfo.filename;
          msg.size = fileInfo.size;
          msg.msgType = 6;
          msg.preDefined = JSON.stringify({ RtcFile: true })
          let msgTemp = msgStructure(msg);
          return this.$store.commit('SET_RTC_FILE', msgTemp)
      }
      }
    },

    /**
     * @breif 处理撤回消息 18
     * @param {*} msg - 消息详细信息
     */
    _msgWithdrawHandle(msg) {
      // 未缓存会话，不需要删除消息（打开会话时，在对应的消息气泡组件中将执行删除操作）
      if (!this.chat_chatContent[msg.targetId]) {
        return;
      }
      //  删除消息
      this.delMsg(msg.targetId, msg.revokeMsgId);

      //  特殊处理图片及微视频预览的情况
      let revokeMsg = this.chat_chatContent[msg.targetId][`id_${msg.revokeMsgId}`];
      if (!revokeMsg || ![MSG_TYPE_MICVIDEO, MSG_TYPE_IMAGE, MSG_TYPE_NINEIMG].includes(revokeMsg.messageObject.msgType)) {
        return;
      }
      let result= this.$isOpenMediaMsgPreivew()
      if (result && result.isOpen && msg.targetId === result.mediaMsgPreivewId) {
        let winType = revokeMsg.messageObject.msgType === MSG_TYPE_MICVIDEO ? 'video' : 'image' 
        this.$ipc.send('handleSubWinMediaMsg',  {winType: winType, operaType: 2, imgId: msg.revokeMsgId} )
      }
    },

    /**
     * @breif 修改 单聊 已读未读状态
     * 下列2种情况下将己方所有未读状态置为已读：
     * 1.收到对方已读推送；2.收到对方发送消息
     * @param {Object} msg - 消息对象
     */
    _msgUnreadStateHandle(msg) {
      let chatType = this.$Service.config.getUserTypeById({ targetId: msg.targetId })
      if (chatType === 1) {
        _.forEach(this.chat_chatContent[msg.targetId], element => {
          if (element.messageObject.maxUnReadCount === 1) {
            return;
          }
          this.$set(element.messageObject, 'maxUnReadCount', 1);
        });
      }
    },

    /**
     * @breif 注册离线消息
     */
    regOfflineMsgCb() {
      this.$Service.chat.regOfflineMsgCb(null, this._regOfflineMsgCbHandler);
    },
    _regOfflineMsgCbHandler(resp) {
      let offlineMsg = resp.msgs[0].msg;
      if (!offlineMsg || !this.chat_chatContent[offlineMsg.targetId]) {
        return;
      }
      this.getHistoryMsg(offlineMsg.targetId, resp.msgs[0].count, offlineMsg.msgId, true);
    },

    /**
     * @breif 监听敏感词更新
     */
    regBadWordUpdateCb() {
      this.$Service.chat.regBadWordUpdateCb(null, resp => {
        console.log('regBadWordUpdateCb', resp);
        if (resp.type === '3') {
          return;
        }
        this.$store.commit('SET_BAD_KEY_MODE', resp.type);
      });
    }
  },
};

export default mixin;