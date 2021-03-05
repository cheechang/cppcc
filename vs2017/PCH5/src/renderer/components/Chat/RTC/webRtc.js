import {rtcService} from '../../../IpcHandler/service';
export class WebRtc {
  constructor() {
    this._isOfferer = null;   // 是否为视频发起者
    this._offerInfo = null;   // 若自己为发起者，则此参数为{'userId':'xxxxxx'}其中userId为对方id;若为接收者，则此参数为发起者相关信息
    this._pc = null;  // RTCPeerConnection对象
    this._iceServer = null; // 打洞服务器信息
    this._mediaStreamTrack = null;  // 媒体流对象，用于关闭音视频
  };
  // 开启音视频(外部调用接口)
  startVideo (isOfferer, offerInfo) {
    this._isOfferer = isOfferer;
    this._offerInfo = offerInfo;
    rtcService('getStunServer',res => {
      var tunUrl = 'stun:' + res.stunAddr + ':' + res.stunPort;
      console.log(res);
      this._iceServer = {
        iceServer: [{ url: tunUrl, username: res.account, password: res.password }],
        bundlePolicy: 'max-bundle',
        rtcpMuxPolicy: 'negotiate'
      };
      this.createChannel();
    });
  };

  // 关闭音视频(外部调用接口)
  stopVideo () {
    this._pc.close();
    rtcService('leaveChannel',(res => {
      console.log('leaveChannelResult:' + JSON.stringify(res));
    }));
    this._mediaStreamTrack.stop();
  };

  // 设置远端视频（发起音视频后对方返回sdp时调用）(外部调用接口)
  setRemoteVideo (sdp, type) { // type:是否为offer
    var sd = this._pc.remoteDescription;
    sd.type = type ? 'offer' : 'answer';
    sd.sdp = sdp;
    this.setCandidateFromSdp(sdp);
    this._pc.setRemoteDescription(sd, () => {
      console.log('setRemoteDescripton success!!!');
      this._pc.onaddstream = (event) => {
        var video = document.getElementById('hisVideo');
        video.src = URL.createObjectURL(event.stream);
        video.play();
      };
    }, (err) => {
      console.log(err);
    });
  };

  // 创建RTC连接(内部调用接口)
  createChannel () {
    var PeerConnection = window.webkitRTCPeerConnection || window.RTCPeerConnection
    this._pc = new PeerConnection(this._iceServer);
    // 调用摄像头获取本地视频流
    navigator.getUserMedia({
      audio: true,
      video: { width: 1280, height: 720 }
    }, (stream) => {
      var video = document.getElementById('myVideo');
      video.src = window.URL.createObjectURL(stream);
      video.play();
      this._mediaStreamTrack = typeof stream.stop === 'function' ? stream : stream.getTracks()[1];
      this._pc.addStream(stream);
      // 如果是音视频发起者
      if (this._isOfferer) {
        this.createOffer();
      } else {
        this.createAnswer();
      }
    }, (err) => { console.log('getUserMediaErr' + err); });
  };

  // 创建Offer，发起视频(内部调用接口)
  createOffer() {
    this._pc.createOffer((offer) => {
      this._pc.setLocalDescription(offer);
      console.log('offer.sdp:' + offer.sdp);
      this._pc.onicecandidate = (event) =>{
        //console.log('onicecandidate event!!!' + JSON.stringify(event.candidate));
        if(event.candidate == null){
          console.log('offer.sdp:' + offer.sdp);
          let info = {
            targetId: this._offerInfo.userId, /// < 目标Id 创建/邀请
            reject: false, /// < true  代表用于拒绝申请加入会议//保留
            videoType: 2, /// < 1，语音  2，视频 3,多人UI语音 ,4多人UI视频 ,5四人广播音频  6四人广播视频
            firstSdp: offer.sdp,   /// < 生成第一次sdp
            operType: 0
          };
          rtcService('createChannel', res => {
            console.log('createChannelResult:' + JSON.stringify(res));
          },info);
        }
        else{
          offer.sdp = this.addCandidateToSdp(offer.sdp,event.candidate);
        }
      };
    }, (err) => { console.log('createOfferErr:' + err); });
  };

  // 创建Answer，接收视频(内部调用接口)
  createAnswer() {
    console.log('sdp:  ' + this._offerInfo.sdp);
    this.setRemoteVideo(this._offerInfo.sdp, true);
    this._pc.createAnswer((answer) => {
      this._pc.setLocalDescription({sdp:answer.sdp,type:'answer'});
      this._pc.onicecandidate = (event) =>{
        //console.log('onicecandidate event!!!' + JSON.stringify(event.candidate));
        if(event.candidate == null){
          console.log('answer.sdp:' + answer.sdp);
          let info = {
            channelId: this._offerInfo.channelId,
            targetId: this._offerInfo.userId, /// < 目标Id 创建/邀请
            videoType: 2, /// < 1，语音  2，视频
            secondSdp: answer.sdp,   /// < 生成第二次sdp
            type: 1
          };
          rtcService('acceptOrReject', res => {
            console.log('acceptOrRejectResult:' + JSON.stringify(res));
          },info);
        }
        else{
          answer.sdp = this.addCandidateToSdp(answer.sdp,event.candidate);
        }
      };
    }, (err) => { console.log('createAnswerErr:' + err); });
  };

  // 向sdp中插入candidate信息(内部调用接口)
  addCandidateToSdp(sdp, candidate){
    if(candidate.candidate.indexOf("udp")!= -1){
      let candidateStr = 'a=' + candidate.candidate + '\n';
      let indexAudio = sdp.indexOf("c=IN")
      let sdpStrHead = sdp.substring(0,indexAudio);
      sdpStrHead = sdpStrHead.concat(candidateStr);
      let sdpStrTail = sdp.substring(indexAudio);
      sdp = sdpStrHead + sdpStrTail;
    }
    return sdp;
  };
  
 // 从对方的sdp中提取candidate并设置candidate(内部调用接口)
  setCandidateFromSdp(sdp){
      while(sdp.indexOf('a=candidate')!= -1){
        let index = sdp.indexOf('a=candidate');
        sdp = sdp.substring(index);
        let newCandidate;
        let nextIndex;
        if(sdp.indexOf('a=candidate',12)!= -1){
            nextIndex = sdp.indexOf('a=candidate',12);
        }
        else{
            nextIndex = sdp.indexOf('c=IN',12);
        }
        newCandidate = sdp.substring(2,nextIndex);
        sdp = sdp.substring(nextIndex);
        //console.log('newCandidate:::' + newCandidate);
        var candidate = new RTCIceCandidate({candidate:newCandidate,sdpMid:"audio",sdpMLineIndex:0});
        this._pc.addIceCandidate(candidate,() =>{
          console.log('addIceCandidate success!!!');
        },(err) => {
          console.log(err);
        });
      }
  }
};
