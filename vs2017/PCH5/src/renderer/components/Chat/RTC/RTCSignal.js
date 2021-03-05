const EventEmitter = require('events').EventEmitter

/**
 * Signaling and session for peer
 * 
 * @class RTCSignal
 * @extends {EventEmitter}
 */
class RTCSignal extends EventEmitter {
  /**
   * Creates an instance of RTCSignal.
   * @memberof RTCSignal
   */
  constructor() {
    this.sessioninfo = {
      channelId: 0,
      targetId: 0, /// < 目标Id 创建/邀请
      videoType: 0,
      firstSdp: '',   /// < 生成第一次sdp
      secondSdp: '',   /// < 生成第二次sdp
      type: 1,
      reject: false, /// < true  代表用于拒绝申请加入会议//保留
      operType: 0
    }

    this.sessionType = [
      '', 'audio', 'video', 'audioMulti', 'videoMulti', 'audioBroadcast', 'videoBroadcast'
    ]
    
    rtcService('getStunServer', res => {
      const stunUrl = 'stun:' + res.stunAddr + ':' + res.stunPort
      this.iceServer = [{ url: tunUrl, username: res.account, password: res.password }]
      // this.emit('error', 'getStunServer')
    })

    rtcService('regChannelEventCb', resp => {
      console.log('收到音视频信息：' + JSON.stringify(resp))
      const eventType = [
        'called', 'endcall', 'reject', 'busy', 'timeout', 'cancel',
        '', '', 'occupy', '', 'accepted', '', 'room not found', 'members',
        'audio change', 'video change', '', '', '']
      this.emit(eventType[resp.type], resp)
    })
  }

/**
 * 发送请求消息到接收方，通过RTCPlugin插件
 * 
 * @param {string} sdp 
 * @param {string} calleeID 
 * @param {string} sessionType 
 * @memberof RTCSignal
 */
sendOfferSDP(sdp, calleeID, sessionType) {
  this.sessioninfo.targetId = calleeID
  this.sessioninfo.sessionType = this.sessionType.indexOf(sessionType)
  this.sessioninfo.firstSdp = sdp  /// < 生成第一次sdp
  rtcService('createChannel', res => {
    this.emit('sendSDP', 'offer', res),
    this.sessioninfo.channelId = res.channelId
  }, this.sessioninfo)
}

/**
 * 发送应答消息到发送方，通过RTCPlugin插件
 * 
 * @param {string} sdp
 * @param {string} callerID 
 * @param {boolean} isAccept 
 * @memberof RTCSignal
 */
  sendAnswerSDP(sdp, callerID, isAccept) {
    this.sessioninfo.targetId = callerID
    this.sessioninfo.secondSdp = sdp
    rtcService('acceptOrReject', res => {
      this.emit('sendSDP', 'awser', res)
    }, this.sessioninfo)
  }

  
}