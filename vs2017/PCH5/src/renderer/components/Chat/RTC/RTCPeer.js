const EventEmitter = require('events').EventEmitter
const RTCPeer = require('RTCPeer')
const RTCMedia = require('RTCMedia')
const RTCChannel = require('RTCChannel')

// config = { 
//   media: { id:123, audio: true, video: { width: 1280, height: 720 }},,
//   channel: { id, ordered, maxPacketLifeTime, maxRetransmits, protocol, negotiated}, 
//   rtc: RTCConfiguration { bundlePolicy, certificates, , peerIdentity, rtcpMuxPolicy
//        iceCandidatePoolSize, iceServers, iceTransportPolicy}
// }

/**
 * RTC房间，工厂管理类，负责peer、media、channel和信令signal的创建生命周期管理
 * 
 * @class RTCPeer
 * @extends {EventEmitter}
 */
class RTCPeer extends EventEmitter {
  /**
   * Creates an instance of RTCPeer.
   * @param {json} rtcOptions 
   * @param {json} mediaOptions 
   * @param {json} cahnnelOptions 
   * @memberof RTCPeer
   */
  constructor(rtcOptions, mediaOptions, cahnnelOptions) {
    this.signal = new RTCSignal()
    this.signal.on('getStunServer', () => {
      config.rtc.iceServer = this.signal.iceServer
      this.init(rtcOptions, mediaOptions, cahnnelOptions)
    })
  }

  init() {
    // var PeerConnection = (window.PeerConnection ||
    //   window.webkitPeerConnection00 ||
    //   window.webkitRTCPeerConnection ||
    //   window.mozRTCPeerConnection);
    var PeerConnection = window.webkitRTCPeerConnection || window.RTCPeerConnection
    this._pc = new PeerConnection(config.rtc)
    this._mediaLocal = new RTCMediaLocal(pc, config)
    this._mediaRemote = new RTCMediaRemote(pc, config)
    
    this._channel = new RTCChannel(pc, config)

    this._pc.oniceconnectionstatechange = this.onIceConnectionStateChange
    this._pc.onicegatheringstatechange = onIcegatheringstatechange
    this._pc.onsignalingstatechange = onSignalingstatechange
    this._pc.onicecandidate = this.onIceCandidate
    // this._pc.onicecandidateerror = onIcecandidateerror
    // this._pc.onconnectionstatechange = onConnectionstatechange

    // this._pc.ontrack = this.ontrack
    // self._pc.onaddstream
  }

  /**
   * 关闭房间，清除所有资源
   * 
   * @memberof RTCPeer
   */
  close() {
    for (m of [this._media, this._channel, this._pc]) {
      m.close()
      m = null
    }

    this.emit('close')
  }
  
  /**
   * 当打洞协商时，网络等状态发生变化
   * 
   * @memberof RTCPeer
   */
  onIceConnectionStateChange() {
    if (pc.iceConnectionState in ['failed', 'disconnected']) {
      this.emit('error', pc.iceConnectionState)
      pc.close()
    }
  }

  /**
   * 当协商SDP在发送或者已发送
   * 
   * @param {any} event 
   * @memberof RTCPeer
   */
  onIceCandidate(event) {
    // Send the candidate to the remote peer
    if (event.candidate) {
      this.signal.sendSDP(this._pc.currentLocalDescription.sdp)
    } else {
      // All ICE candidates have been sent   
      if (this.currentLocalDescription.sdp && !this.currentRemoteDescription.sdp) {
        addOffer(event.candidate.candidate)
      } else if (!this.currentLocalDescription.sdp && this.currentRemoteDescription.sdp) {
        addAnswer(event.candidate.candidate)
      }
    }
  }

  /**
   * Offer时，向sdp中插入candidate信息
   * 
   * @param {string} sdp 
   * @memberof RTCPeer
   */
  addOffer(sdp) {
    if (sdp.indexOf("udp") != -1) {
      const indexAudio = sdp.indexOf("c=IN")
      const sdpStrHead = sdp.substring(0, indexAudio) + 'a=' + candidate.candidate + '\n'
      const sdpStrTail = sdp.substring(indexAudio)
      this._pc.currentLocalDescription.sdp = sdpStrHead + sdpStrTail
    }
  }

  /**
   * Answer时，从对方的sdp中提取candidate并设置candidate
   * 
   * @param {string} sdp 
   * @memberof RTCPeer
   */
  addAnswer(sdp) {
    while (this._pc.currentRemoteDescription.indexOf('a=candidate') != -1) {
      sdp = sdp.substring(sdp.indexOf('a=candidate'))
      const nextIndex = sdp.indexOf('a=candidate', 12)
      if (nextIndex === -1) {
        nextIndex = sdp.indexOf('c=IN', 12)
      }
      const newCandidate = sdp.substring(2, nextIndex)
      sdp = sdp.substring(nextIndex)
      //console.log('newCandidate:::' + newCandidate)
      const candidate = new RTCIceCandidate({
        candidate: newCandidate,
        sdpMid: "audio",
        sdpMLineIndex: 0
      })
      this._pc.addIceCandidate(candidate, () => {
        console.log('addIceCandidate success!!!')
      }, (err) => {
        console.log(err)
      })
    }
  }

  // Media and signal

  /**
   * 发起呼叫请求
   * 
   * @param {number} calleeID 接收方豆豆ID
   * @param {string} signalType 通话类型
   * @param {RTCPeerDescription} createOffer.signalDesc
   * @memberof RTCPeer
   */
  call(calleeID, signalType) {
    this._pc.createOffer((signalDesc) => {
      this._pc.setLocalDescription(signalDesc, 
        () => this.signal.sendOfferSDP(signalDesc.sdp, calleeID, signalType),
        onSDPError)},
      onSDPError,
      opts)  
  }

  /**
   * 回应接听响应
   * 
   * @param {number} calleeID 接收方豆豆ID
   * @param {boolean} isAccept 接听或者挂断
   * @param {RTCPeerDescription} createAnswer.signalDesc
   * @memberof RTCPeer
   */
  accept(callerID, isAccept = true) {
    this._pc.createAnswer((signalDesc) => {
      this._pc.setRemoteDescription(signalDesc, 
        () => this.signal.sendAnswerSDP(signalDesc.sdp, callerID, isAccept),
        onSDPError)},
      onSDPError,
      opts)  

  }

  /**
   * 回应拒绝响应
   * 
   * @param {number} calleeID 接收方豆豆ID
   * @memberof RTCPeer
   */
  reject(callerID) {
    accept(callerID, false)
  }

  /**
   * 回应挂断响应
   * 
   * @memberof RTCPeer
   */
  hangup() {
    rtcService('leaveChannel', res => {
    })
    if (this.peer) {
      this.peer.close()
    }
  }

  onSDPError(err) {
    this.signal.emit('error', err)
  }

  /**
   * 静音，或者去掉静音
   * 
   * @param {boolean} isMute 
   * @memberof RTCPeer
   */
  muteMicphone(isMute) {
    this._mediaLocal.muteMicphone(isMute)
  }

  /**
   * 关闭摄像头，或者开启摄像头
   * 
   * @param {boolean} isDisable
   * @memberof RTCPeer
   */
  disableCamera() {
    this._mediaLocal.disableCamera(isDisable)
  }


  // DataChannel

  /**
   * 发送文件。需在2点间协商后
   * 
   * @param {any} filename 
   * @param {any} onprogress 
   * @param {any} onsuccse 
   * @param {any} onerror 
   * @memberof RTCPeer
   */
  sendFile(filename, onprogress, onsuccse, onerror) {
    if (hadCandidate) {
      onerror('not candidate')
      return
    }
  }

  sendMessage(msg, onsuccse, onerror) {

  }


}