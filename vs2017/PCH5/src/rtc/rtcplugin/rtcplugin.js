import {
  ipcMain
} from 'electron'
import {
  resolve
} from 'path'
import i18n from '../../comm/i18n'
import {
  isDev,
  isOSX
} from "../../comm/is";
const pkg = require('../../../package.json')

// this.$ipc.send('new-window', 'http://localhost:9080/#/RTCP2P', 'RTCP2P')    
let rtcplugin_self = null;
export class Rtcplugin {

  constructor(rtc_service, newWindow) {
    rtcplugin_self = this;
    this.rtc_service_ = rtc_service;
    this.data_ = null;
    this.multiCallback = null;
    this.rtc_service_.regChannelEventCb(null, this.origin_callback);
    this.rtc_service_.regMultiEventCb(null, this.mutil_callback);
    this.rtc_service_.multiExtraRequest({
      type: 1,
      cmdJson: '{"pcOnOff":"on"}'
    });
    this.newWindow_ = newWindow;
    this.fileFileReceiverNotify = null;
    this.RtcFileCb = null;
    this.state_ = null;
    var json2 = {};
    json2.resend_callmsg_switch = 'on';
    json2.resend_callmsg_subtime = '8';
    var jsonStr2 = JSON.stringify(json2);
    this.rtc_service_.extraEventCall({
      eventType: 7,
      reserveJson: '',
      strInfo: jsonStr2
    });
    var json = {};
    json.ownerTip = '对方版本过低,请通知对方升级!';
    json.peerTip = '您的版本过低，请升级后使用!';
    var jsonStr = JSON.stringify(json);
    this.rtc_service_.extraEventCall({
      eventType: 1,
      reserveJson: jsonStr,
      strInfo: ''
    });
    this.RTCWeakTipsCallBack = null;
    this.SetNotifySwitch('off'); // 默认关闭通知
    rtcplugin_self.req_ = null;

    this.multiCallList = []; // 推送数据列表
    // this.multiCallMap = new Map(); // 对应房间 推送数据列表

    // 重写的单点音视频回调
    this.singleRtcCallBack = null;
    this.singleRtcMsgList = [];

  }

  //
  // 音视频消息通知开关，默认关闭通知
  // 参数为'on'/'off'
  //
  SetNotifySwitch(on_off) {
    rtcplugin_self.log('on_off:::', on_off);
    var json = {};
    json.notifySwitch = on_off;
    var jsonStr = JSON.stringify(json);
    this.rtc_service_.extraEventCall({
      eventType: 7,
      reserveJson: '',
      strInfo: jsonStr
    });
  }

  setData(data) {
    this.data_ = data;
  }

  getData() {
    return this.data_;
  }
  // -----多人视频 begin------
  // { annotation: '',
  // extendJson: '',
  // groupId: '4338338654',
  // members: [ '4328634461', '4328634505' ],
  // onwerId: '4328634461',
  // roomId: '4328634461-1552633766829',
  // roomName: '测试房间',
  // selects: [ '4328634505' ],
  // type: 1,
  // userId: '4328634461' }

  mutil_callback(resp) {
    if (rtcplugin_self.multiCallback) {
      rtcplugin_self.multiCallback(resp);
    }
    global.service.log(`rtcplugin::mutil_callback 1:${resp.roomId}`);
    if (resp) {
      rtcplugin_self.multiCallList.push(resp);
    }

    global.service.log(`rtcplugin::mutil_callback:${JSON.stringify(resp)}`);
    switch (resp.type) { // 事件类型(1呼叫 2邀请 3进房 4挂断 5结束 6超时 7应答)
      case 1: {
        rtcplugin_self.openOptionUI(1, resp);
      }
      break;
    case 3:
      break;
    case 4: {

    }
    break;
    case 5: {
      // global.postMsgToRender('exit_meeting_response',resp);
      // global.postMsgToRender('closeSubWin','InternalWindow');
    }
    break;
    case 6: {

    }
    break;
    default:
      break;
    }
  }

  clearMultiCbList() {
    this.multiCallList = [];
  }

  openOptionUI(type, resp) {
    let result = global.judgePlginSubWinStatus('InternalWindow')
    if (result.busy) {
      const request = {
        reqType: 5,
        annotation: "busy",
        groupId: resp.groupId,
        roomId: resp.roomId
      };
      rtcplugin_self.hangUp(request, cb => {
        rtcplugin_self.log('openOptionUI hangUp :: busy', cb);
      });
      return
    }
    i18n.locale = global.language;
    let title = i18n.t('chat.douShipin');
    return rtcplugin_self.newWindow_({
      winTitle: title,
      winIcon: '',
      winType: 'InternalWindow',
      winUrl: `#/MultiMeeting?type=${type}&adminId=${resp.onwerId}&members=${resp.members}&roomId=${resp.roomId}&groupId=${resp.groupId}`,
      shapeType: 'normal'
    }, {
      width: 320,
      height: 480
    });
  }

  openMeetingUI(resp) {
    // let result = global.judgePlginSubWinStatus('mediadood')
    // if (result.busy) {
    //   return
    // }
    let version = `${pkg.version}-${global.service.config.getSdkVersion()}`;
    let platform = isOSX ? 'pc-mac' : 'pc-win';
    let serverInfo = rtcplugin_self.rtc_service_.getMultiServerSync();

    rtcplugin_self.log('openMeetingUI=>>', serverInfo);
    let {
      turnAddr
    } = serverInfo;
    let serverUrl = "";
    let serverPort = "";
    i18n.locale = global.language;
    let title = resp.title || i18n.t('chat.douShipin');
    if (turnAddr && turnAddr.indexOf(":") !== -1) {
      serverUrl = turnAddr.split(":")[0];
      serverPort = turnAddr.split(":")[1];
    }
    let startTime = resp.startTime || new Date().getTime();
    const members = JSON.stringify(resp.members); //[];//resp.members.split(",");
    let template_static = "vrv-static/plugins";
    const mediadood = template_static + "/mediadood/index.html";
    let url = `${mediadood}?roomId=${resp.roomId}&displayName=${
          resp.userName
        }&userID=${resp.userId}&members=${
          members
        }&serverUrl=${serverUrl}&serverPort=${serverPort}&clientInfo=${
          version}&platform=${platform}&title=${title}&desc=${resp.desc}&groupId=${resp.groupId}&adminId=${resp.adminId}&locale=${
            i18n.locale}&startTime=${startTime}&version=2.0.0&lg=vrv`;
    rtcplugin_self.log('openMeetingUI>>', url, resp);
    return rtcplugin_self.newWindow_({
      winTitle: title,
      winIcon: '',
      winType: 'mediadood',
      winUrl: url,
      shapeType: 'normal'
    }, {
      width: 800,
      height: 600
    });
  }

  regMultiEventCb(callback) {
    rtcplugin_self.multiCallback = callback;
  }

  getMultiCbList() {
    return this.multiCallList;
  }

  // 呼叫
  callMutil(request, callback) { // groupId、roomId、roomName、members
    this._multiTalkRequest(request, cb => {
      callback(cb);
      rtcplugin_self.openMeetingUI(request);
    });
  }

  inviteMembers(request, callback) { // groupId、roomId、members(邀请成员列表)
    this._multiTalkRequest(request, callback);
  }
  // 同意 
  joinMeeting(request, callback) { // groupId、roomId、members(当前已经在通话中的成员列表,从server拿到的)
    rtcplugin_self._multiTalkRequest(request, cb => {
      rtcplugin_self.openMeetingUI(request);
      callback(cb);
    });
  }

  // 模板联入
  joinByTemplate(request, callback) {
    rtcplugin_self._multiTalkRequest(request, cb => {
      callback(cb);
    });
  }

  // 挂断
  // annotation、groupId、roomId
  //           "hungup" : UI用户正常点"挂断"按钮，则赋此值
  //           "busy" : UI正忙，自动回复挂断，则赋此值
  hangUp(request, callback) {
    this._multiTalkRequest(request, cb => {
      rtcplugin_self.log('hangUp>>1 ', cb);
      callback(cb);
    });
  }

  // 设置心跳
  keepalive(request, callback) {
    this._multiTalkRequest(request, cb => {
      rtcplugin_self.log('keepalive>>1 ', cb);
      callback(cb);
    });
  }

  // 成员变动 通知
  memberNotify(request, callback) {
    this._multiTalkRequest(request, cb => {
      rtcplugin_self.log('keepalive>>1 ', cb);
      callback(cb);
    });
  }

  _multiTalkRequest(request, callback) {
    rtcplugin_self.log('_multiTalkRequest>>', request);
    rtcplugin_self.rtc_service_.multiTalkRequest(request, callback);
  }
  // -----多人视频 end------

  origin_callback(req) {
    // this.singleRtcCallBack = null;
    // this.singleRtcMsgList = [];
    global.service.log(`rtcplugin::origin_callback:${JSON.stringify(req)}`);
    console.log('origin_callback', rtcplugin_self.RtcFileCb, req.videoType, req.type);

    if (req.type === 9) // 处理 界面未加载 时 收到挂断消息
      setTimeout(()=>{
        if (rtcplugin_self.singleRtcCallBack !== null)
        rtcplugin_self.singleRtcCallBack(req);
      }, 5000);

    if (rtcplugin_self.RtcFileCb && req.videoType === 7) // 设置 文件直传回调
      rtcplugin_self.RtcFileCb(req);

    rtcplugin_self.req_ = req;
    if (req.type !== 1) {
      if (rtcplugin_self.singleRtcCallBack !== null)
        rtcplugin_self.singleRtcCallBack(req);
      else
        rtcplugin_self.singleRtcMsgList.push(req);
    }
    else {
//    if (req.type === 1) {
      let extendJson = req.extendJson;
      try {
        extendJson = JSON.parse(extendJson);
      } catch (error) {
        global.service.log(`rtcplugin::origin_callback parse extendJson fail: ${error}`);
      }
      let isBurn = false;
      let deviceType = extendJson.peer_devtype || 'pc'; 
      console.log('extendJson==>', extendJson, extendJson.mode);
      if(extendJson.mode && extendJson.mode === 'single'){
        isBurn = true;
      }
      rtcplugin_self.setData(req);
      if (req.videoType === 1) { // 音频
        global.service.contact.getContactInfo({
          userId: req.userId
        }, resp => {
          //rtcplugin_self.log('getContactInfo:', resp);
          i18n.locale = global.language;
          rtcplugin_self.newWindow_({
            winTitle: `${i18n.t('chat.audioCall')}[${resp.remark?resp.remark :resp.name}]`,
            winIcon: resp.thumbAvatar,
            winType: 'RTCP2P',
            winUrl: `#/RTCP2P?type=1&isBurn=${isBurn}`,
            shapeType: 'normal'
          }, {
            width: 320,
            height: 480
          });
        })
      } else if (req.videoType === 2) { // 视频
        global.service.contact.getContactInfo({
          userId: req.userId
        }, resp => {
          //rtcplugin_self.log('getContactInfo:', resp);
          i18n.locale = global.language;
          rtcplugin_self.newWindow_({
            winTitle: `${i18n.t('chat.videoCall')}[${resp.remark?resp.remark :resp.name}]`,
            winIcon: resp.thumbAvatar,
            winType: 'RTCP2P',
            winUrl: `#/RTCP2P?type=2&isBurn=${isBurn}`,
            shapeType: 'normal'
          }, {
            width: deviceType == 'pc' ? 640 : 320,
            height: 480
          });
        })
      } else if (req.videoType === 9) { // 远程协助
        global.service.contact.getContactInfo({
          userId: req.userId
        }, resp => {
          //rtcplugin_self.log('getContactInfo:', resp);
          i18n.locale = global.language;
          rtcplugin_self.newWindow_({
            winTitle: `${i18n.t('chat.remoteAssistance')}[${resp.remark?resp.remark :resp.name}]`,
            winIcon: resp.thumbAvatar,
            winType: 'RemoteControl',
            winUrl: '#/RemoteControl',
            shapeType: 'normal'
          }, {
            width: 640,
            height: 480
          });
        })
      } else if (req.videoType === 7) { // 文件直传
        rtcplugin_self.log('origin_callback', req.videoType, rtcplugin_self.fileFileReceiverNotify);
        // if (rtcplugin_self.fileFileReceiverNotify) {
        //   rtcplugin_self.state_ = 'file';
        //   var obj = JSON.parse(req.sdp);
        //   var msg = {
        //     userId: req.userId,
        //     filename: obj.filename,
        //     filesize: obj.filesize
        //   };
        //   //rtcplugin_self.log("rtcplugin, rtcfile, req: ", msg);
        //   rtcplugin_self.fileFileReceiverNotify(msg);
        // } else {
        //   rtcplugin_self.log("fileFileReceiverNotify is null");
        // }
      }
    } 
    // else if (req.type === 6) { // // 文件直传，发送方取消
    //   let winType = null;
    //   switch (req.videoType) {
    //     case 2: {
    //       winType = 'RTCP2P';
    //       break;
    //     }
    //     case 9: {
    //       winType = 'RemoteControl';
    //       break;
    //     }
    //     case 7: {
    //       winType = 'RtcFile';
    //       break;
    //     }
    //     default: {
    //       break;
    //     }
    //   }
    //   global.postMsgToRender('closeSubWin', winType);
    //   if (rtcplugin_self.state_ === 'file') {
    //     rtcplugin_self.log('fromrtcfile:::::')
    //     rtcplugin_self.log("对方取消文件发送");
    //     if (rtcplugin_self.RtcFileCb) {
    //       rtcplugin_self.RtcFileCb('kCancel', null);
    //     }
    //   } else {
    //     rtcplugin_self.resetCallback();
    //   }
    // }
  }

  GetReq() {
    return rtcplugin_self.req_;
  }

  regFileReceiverNotify(notify) { // 文件接收端通知
    this.log('regFileReceiverNotify', notify);
    rtcplugin_self.fileFileReceiverNotify = notify;
  }

  regRtcFileCb(callback) { // 文件直传回调，由main render注册，回调到main render
    if(!rtcplugin_self.RtcFileCb){
      rtcplugin_self.RtcFileCb = callback;
    }
  }

  /*
    1. WeakTipsCB为音视频若提示回调，其参数为SimpleMsgVedio
    2. 离线消息MsgVedio已经由ChatService::InsertMessage插入到sdk数据库中
    3. SimpleMsgVedio是MsgVedio的简化版
       struct SimpleMsgVedio {
        string fromId; // 自己ID
        string targetId; // 对方ID
        string time; // 通话时长ms
        int videoType; // 1-音频；2-视频
        string msgModel; // 消息类型 “1”-对方超时；“2”-已取消；"3"-已拒绝； “4”-通话时长；“6”-其他设备处理
        msgInfo;
        deviceType;
        toId;
        msgId;
       };
  */
  regRTCWeakTipsCallBack(WeakTipsCB) {
    rtcplugin_self.RTCWeakTipsCallBack = WeakTipsCB;
  }

  SendRTCWeakTips(SimpleMsgVedio) {
    if (rtcplugin_self.RTCWeakTipsCallBack) {
      rtcplugin_self.RTCWeakTipsCallBack(SimpleMsgVedio);
      rtcplugin_self.log("Rtcplugin, ", SimpleMsgVedio)
    }
  }

  //  msg_type : msg
  //  kBegin
  //  kPercent : 0.17
  //  kEnd
  //  kReject
  //  kError : Disconnected, NoSpace, OpenFileFailed
  //  kTimeout
  //  kCancel
  //  kBusy
  SendMsgToMainRender(msg_type, msg = null) { // file render向main render发送消息
    if (rtcplugin_self.RtcFileCb)
      rtcplugin_self.RtcFileCb(msg_type, msg);
  }

  hasHangupMsg() {
    let ret = false;
    for (let i=0; i<rtcplugin_self.singleRtcMsgList.length; ++i) {
      let type = rtcplugin_self.singleRtcMsgList[i].type;
      if (type===6 || type===13) {
        ret = true;
        rtcplugin_self.singleRtcMsgList = [];
        break;
      }
    }
    return ret;
  }

  regChannelEventCb(callback) {
    this.singleRtcCallBack = callback;
    //this.rtc_service_.regChannelEventCb(null, callback);
  }

  resetCallback() {
    rtcplugin_self.state_ = null;
    rtcplugin_self.req_ = null;
    rtcplugin_self.singleRtcCallBack = null;
    rtcplugin_self.singleRtcMsgList = [];
    //this.rtc_service_.regChannelEventCb(null, this.origin_callback);
  }

  getStunServer(call_back) {
    this.rtc_service_.getStunServerList(null, call_back);
  }

  createChannel(request, call_back) {
    this.rtc_service_.createChannel(request, call_back);
  }

  acceptOrReject(request, call_back) {
    this.rtc_service_.acceptOrReject(request, call_back);
  }

  leaveChannel(call_back) {
    this.rtc_service_.leaveChannel(null, call_back);
  }

  extraEventCall(param) {
    this.rtc_service_.extraEventCall(param);
  }

  regExtraEventNotifyCb(cb) {
    this.rtc_service_.regExtraEventNotifyCb(cb);
  }

  log(tag, ...message){
    console.log(`rtcplugin::${tag}`, message);
  }
};
