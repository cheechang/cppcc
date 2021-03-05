

import {isWinXp} from '../../comm/is'
export class Peer {
  constructor() {
    self = this;
    this.remote_id_ = null;
    this.local_sdp_ = null;
    this.peer_conn_ = null;
    this.remote_render_ = null;
    this.OnRtcsdkMsg_ = null;
    this.type_ = null;
    this.data_channel_ = null;

    this.ice_state_ = 'generating'; // 'generating', 'completed'
    this.id_of_settimeout_ = null;

    // 该回调的作用是
    // 如果没有网络连接，则无法生成ICE，则无法回调SDP
    self.no_network_timeout_10s_ = null;

    self.ice_1s_timeout = false;
    self.has_relay_ice = false;

  }    

  PeerCallBack(peer_id, msg_type, msg, data_size) {
    this.OnRtcsdkMsg_(peer_id, msg_type, msg, data_size);
  }

  CreatePeer(peer_id, rtc_param, stream, has_datachannel) {
    console.log("PEER.JS::CreatePeer");
    this.OnRtcsdkMsg_ = rtc_param.call_back; 
    this.remote_id_ = peer_id;
    this.remote_render_ = rtc_param.remote_render;

    let servers = [];
    for (var i=0; i<rtc_param.ice_server.length; ++i) {
      var ice_server = rtc_param.ice_server[i];
      servers.push({
        urls: 'turn:'+ice_server.stunAddr+':'+ice_server.stunPort,
        username: ice_server.account,
        credential: ice_server.password
      });
      servers.push({
        urls: 'stun:'+ice_server.stunAddr+':'+ice_server.stunPort,
        username: ice_server.account,
        credential: ice_server.password
      });
    }
    servers.push({
      urls: "stun:stun.l.google.com:19302"
    });

    let config = {
      iceServers:servers,
      sdpSemantics:'plan-b'
    };

    console.log("PEER.JS::RTCPeerConnection");
    if(isWinXp){
      var PeerConnection = window.webkitRTCPeerConnection || window.RTCPeerConnection
      this.peer_conn_ = new PeerConnection(config);
    }
    else{
      this.peer_conn_ = new RTCPeerConnection(config);
    }

    if (stream)
    this.peer_conn_.addStream(stream);
    this.peer_conn_.oniceconnectionstatechange = this._OnIceConnectionStateChange;
    this.peer_conn_.onicecandidate = this._OnIceCandidate;


    console.log("PEER.JS::createDataChannel");
    if (rtc_param.sdp === null) {      
      if (has_datachannel) {
        this.data_channel_ = this.peer_conn_.createDataChannel('sendDataChannel', null);
        this.data_channel_.onopen = this._OnDataChannelOpen;
        this.data_channel_.onmessage = this._OnData;
      } 
       
      this.type_ = 'offer';
      console.log("PEER.JS::createOffer");
      this.peer_conn_.createOffer (
        (signalDesc)=>{
          this.local_sdp_ = JSON.parse(JSON.stringify(signalDesc.sdp));
          this.peer_conn_.setLocalDescription(signalDesc, ()=>{}, (err)=>{console.log('RTC_ERROR, Peer::PeerConnection::setLocalDescription(), '+err);})

          self.no_network_timeout_10s_ = setTimeout(()=>{
            self.PeerCallBack(self.remote_id_, self.type_=='offer'?101:102 , self.local_sdp_, -1);
          }, 10000);
        
        },
        (err)=>{ console.log('RTC_ERROR, Peer::PeerConnection::createOffer(), '+err);}
      )  
    }
    else {
      if (has_datachannel) {
        console.log("PEER.JS::ondatachannel");
        this.peer_conn_.ondatachannel = function(event) {
          self.data_channel_ = event.channel;
          self.data_channel_.onopen = self._OnDataChannelOpen;
          self.data_channel_.onmessage = self._OnData;
        }
      }

      this.type_ = 'answer';
      this.SetRemoteSDP(rtc_param.sdp, 'offer');
      console.log("PEER.JS::createAnswer");
      this.peer_conn_.createAnswer(
        (answer) => {
          this.local_sdp_ = answer.sdp;
          this.peer_conn_.setLocalDescription({sdp:answer.sdp,type:'answer'});
        }, 
        (err) => { console.log('RTC_ERROR, Peer::PeerConnection::createAnswer(), '+err); }
      );
    }
  }

  _gotRemoteStream(e) {
    console.log("peer::_gotRemoteStream");
    if(isWinXp){
      var objUrl = window.URL.createObjectURL(e.stream);
      if (self.remote_render_.src !== objUrl){
          self.remote_render_.src = objUrl;
          self.remote_render_.play();      
        }
    }else{
        if (self.remote_render_.srcObject !== e.streams[0]) {
          self.remote_render_.srcObject = e.streams[0];
          self.remote_render_.play();      
        }
    }
  }

  SetRemoteSDP(sdp, type='answer') {
    console.log("PEER::SetRemoteSDP");
    if(isWinXp){
      self.peer_conn_.onaddstream = self._gotRemoteStream;
    }
    else{
      self.peer_conn_.addEventListener('track', self._gotRemoteStream);
    }
    var sd = new RTCSessionDescription();
    sd.type = type;
    sd.sdp = sdp;
    this.peer_conn_.setRemoteDescription(
      sd, 
      () => {
      }, 
      (err) => { console.log('RTC_ERROR, Peer::SetRemoteSDP()::PeerConnection::setRemoteDescription(), '+err);}
    );
  }


  Close() {
    this.peer_conn_.close();
  }

  SendData(data) {
    if (self.data_channel_)
      self.data_channel_.send(data);
  }


  _OnIceConnectionStateChange(event) {
    if (self.peer_conn_.iceConnectionState === 'connected') {
      // self.PeerCallBack(self.remote_id_, 103, -1, -1);
      self.peer_conn_.getStats().then(stats => {      
        let localCandidateId = null;
        let candidateType = -1;
        stats.forEach(report => {
          if (report.type === "candidate-pair" && report.state === "succeeded") {
            localCandidateId = report.localCandidateId;
          }
        });
        stats.forEach(report => {
          if (report.type === "local-candidate" && report.id === localCandidateId) {
            candidateType = report.candidateType;
          }
        });
        self.PeerCallBack(self.remote_id_, 103, candidateType, -1);
      });

    }
    else if (self.peer_conn_.iceConnectionState === 'failed') {
      self.PeerCallBack(self.remote_id_, 'failed', -1, -1);      
    }
    else if (self.peer_conn_.iceConnectionState === 'disconnected') {
      self.PeerCallBack(self.remote_id_, 'disconnected', -1, -1);      
    }
  }



  _IceCompleted() {
    console.log("Peer.js::_IceCompleted()");
    clearTimeout(self.id_of_settimeout_);
    self.PeerCallBack(self.remote_id_, self.type_=='offer'?101:102 , self.local_sdp_, -1);
  }

  _OnIceCandidate(event) {
    clearTimeout(self.no_network_timeout_10s_);
    // av\rtc_design\单人音视频\RTC_单人通话_candidate收集策略_20190904.txt
    if (event.candidate) {
      if (event.candidate.candidate.indexOf("udp")!=-1) {
        if (self.ice_1s_timeout === false)
          clearTimeout(this.id_of_settimeout_); // 取消ice生成超时
        console.log('zzzzzzzzzzzzzzzzzzzzzzz', event.candidate.candidate)
        if (event.candidate.candidate.indexOf("relay")!=-1) {
          self.has_relay_ice = true;
          if (self.ice_1s_timeout === true) {
            console.log("1s超时后，得到relay，直接返回");
            self._IceCompleted()
            return;           
          }
        }
      
        let MAX = 3;//TODO
        let ice = 'a=' + event.candidate.candidate + '\r\n'; 
        let iceTag = 'm=' + event.candidate.sdpMid;
        if (iceTag === 'm=data') {
          iceTag = "m=application";
          MAX = 2;
        }
        let pos = self.local_sdp_.indexOf(iceTag);
        for (let i = 0; i < MAX; ++i)
          pos = self.local_sdp_.indexOf("\r\n", pos+1);
        self.local_sdp_ = self.local_sdp_.substring(0, pos+2) 
                        + ice + self.local_sdp_.substring(pos+2, self.local_sdp_.length)

        //this.id_of_settimeout_ = setTimeout("self._IceCompleted()", 3000);  // 设置ice生成超时
        if (self.ice_1s_timeout === false)
          this.id_of_settimeout_ = setTimeout(()=>{
            self.ice_1s_timeout = true;
            if (self.has_relay_ice === true) {
              console.log("1s超时后，已经得到relay，直接返回");
              self._IceCompleted()
            } else {
              setTimeout(()=>{
                console.log("1s超时后，又经过6s超时，直接返回");
                self._IceCompleted()              
              }, 6000);
            }
          }, 1000);
      }
    }
  }

  _OnDataChannelOpen(event) {
    self.PeerCallBack(self.remote_id_, 301, -1, -1);
  }

  _OnData(event) {
    self.PeerCallBack(self.remote_id_, 'kData', event.data, -1);
  }

};
