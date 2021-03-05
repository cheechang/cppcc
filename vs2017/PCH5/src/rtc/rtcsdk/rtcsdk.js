import { Peer } from './peer'
import {isWinXp} from '../../comm/is'
const { desktopCapturer } = window.require('electron');
//
// C42 = 6种组合
//   合法：AUDIO+VIDEO, AUDIO+DATA, AUDIO+DESTOP, VIDEO+DATA, DATA+DESTOP
//   非法：VIDEO+DESTOP
//
// C43 = 4种组合
//   合法：AUDIO+VIDEO+DATA, AUDIO+DATA+DESTOP
//   非法：VIDEO+DESTOP+*
//
const RTC_PEER_TYPE = {
  AUDIO:1,
  VIDEO:2,
  DATA:4,
  DESKTOP:8
};
export {RTC_PEER_TYPE};

export class RtcParam {
  construct() {
  this.ice_server='';
  this.ice_port='';
  this.ice_user = '';
  this.ice_pwd = '';
  this.sdp = null;
  this.call_back = null;
  this.local_render= null;
  this.remote_render= null;
  }
};

var RTCSDK_SELF = null;
export class Rtcsdk {

  constructor(call_back) {
    this.stream_ = null;
    this.peer_map_ = new Map();
    this.ice_server_ = null;
    this.OnRtcsdkMsg = call_back;
    this.has_video_device = false;
    this.has_audio_device = false;
    RTCSDK_SELF = this;
  }

  getChromeMediaSourceId() {
    console.log('getChromeMediaSourceId');
    return new Promise(function (resolve, reject) {
      console.log('Promise');
      desktopCapturer.getSources({ types: ['screen'] }, function (error, sources) {
          resolve(sources[0].id);
      });
    });
  }

  async getDevices(device_infos) {
    for (let i=0; i!==device_infos.length; ++i) {
      console.log('getDevices',device_infos[i].kind);
      if (device_infos[i].kind === 'videoinput') {
        RTCSDK_SELF.has_video_device = true;
      }
    }
  }

  async CreatePeer(peer_id, peer_type, rtc_param) {
    console.log('rtcsdk.js::CreatePeer');
    // 获取设备
    await navigator.mediaDevices.enumerateDevices().then(RTCSDK_SELF.getDevices);
  
    console.log('enumerateDevices().then');
    // TODO:检测peer_id
    this.ice_server_  = rtc_param.ice_server;
    let constraints = {};
    let has_datachannel = false;
    if (peer_type&RTC_PEER_TYPE.VIDEO && peer_type&RTC_PEER_TYPE.DESKTOP) {
      console.log("RTC_ERROR, Rtcsdk::CreatePeer(), wrong peer-type");
      return;
    }
    if (peer_type&RTC_PEER_TYPE.AUDIO)
      constraints.audio = true;
    if (peer_type&RTC_PEER_TYPE.VIDEO && RTCSDK_SELF.has_video_device===true)
      constraints.video = true;
    if (peer_type&RTC_PEER_TYPE.DESKTOP) {
      console.log('.getChromeMediaSourceId begin');
      let id = await this.getChromeMediaSourceId();
      //constraints.video = { mandatory: { chromeMediaSource: 'desktop',chromeMediaSourceId: id, maxWidth: 1280, maxHeight: 720, minWidth: 1280, minHeight: 720, } }
      //constraints.video = { mandatory: { chromeMediaSource: 'desktop',chromeMediaSourceId: id , maxWidth: 1280, maxHeight: 720,} }
      constraints.video = { mandatory: { chromeMediaSource: 'desktop',chromeMediaSourceId: id , maxWidth: 1280, maxHeight: 720,} }
    }
    if (peer_type&RTC_PEER_TYPE.DATA)
      has_datachannel = true;

    let len  = Object.keys(constraints).length;  
    console.log('constraints,len,this.stream_',constraints,len,this.stream_);
    if (len!==0 && this.stream_===null) {
      try {
        console.log('navigator.mediaDevices.getUserMedia,',constraints,len);
        this.stream_ = await navigator.mediaDevices.getUserMedia(constraints);
        console.log('this.stream_',this.stream_ );
        if (rtc_param.local_render !== null) {
          rtc_param.local_render.srcObject = this.stream_;
          //rtc_param.local_render.src = window.URL.createObjectURL(this.stream_);
          if(peer_type&RTC_PEER_TYPE.VIDEO){
            rtc_param.local_render.play();    
          } 
          rtc_param.local_render.muted = true;
        }
      }
      catch (e) {
        console.log("getUserMedia:",e.name,e.message);
      }
    }
    let peer = new Peer();
    this.peer_map_.set(peer_id, peer);
    this.peer_map_.get(peer_id).CreatePeer(peer_id, rtc_param, this.stream_, has_datachannel);
    console.log('peer',peer);
    this.GatherStatsAsync(peer_id);
  }

  SetRemoteSDP(remote_id, remote_sdp) {
      // TODO 
      this.peer_map_.get(remote_id).SetRemoteSDP(remote_sdp);
  }

  SendData(peer_id, label, data) {
    this.peer_map_.get(peer_id).SendData(data);
  }

  DestroyAll() {
    this.peer_map_.forEach(function (value, key, map) {
      value.Close();
    });
  }

  DestroyOne(peer_id) {
    // TODO
  }
  async GatherStatsAsync(remote_id) 
  {
    console.log('rtcsdk.js::GatherStatsAsync');
    var devices = await navigator.mediaDevices.enumerateDevices();

    var audioinput_name = null;
    var audiooutput_name = null;
    var videoinput_name = null;

    for (var i=0; i<devices.length; ++i) {
      var device = devices[i];
      if (device.label==="Default" || device.label==="Communications")
        continue;
      if (device.kind==="audioinput" && !audioinput_name)
        audioinput_name = device.label;
      if (device.kind==="audiooutput" && !audiooutput_name)
        audiooutput_name = device.label;
      if (device.kind==="videoinput" && !videoinput_name)
       videoinput_name = device.label;  
    }

    var stats = 
    {
      version : {
        client:0, // 从插件获取版本号
        server:0, // 未完成
        local_low:false, // 自己版本低， 提示升级
        remote_low:false // 对方版本低，提示升级
      },
      device : {
        audioinput:audioinput_name,
        audiooutput:audiooutput_name,
        videoinput:videoinput_name
      },
      nat_traversal :{
        server_addr:RTCSDK_SELF.ice_server_, // 打洞地址
        server_status:"",
        local_status:"" // host，relay 
      },
      detail : "chrome://webrtc-internals/"
    }

    if (RTCSDK_SELF.OnRtcsdkMsg) {
      RTCSDK_SELF.OnRtcsdkMsg('', 'kStats', stats, -1);
    }
  }

  async GatherStatsSync() {
    console.log('GatherStatsSync');
    var devices = await navigator.mediaDevices.enumerateDevices();

    var audioinput_name = null;
    var audiooutput_name = null;
    var videoinput_name = null;

    for (var i=0; i<devices.length; ++i) {
      var device = devices[i];
      if (device.label==="Default" || device.label==="Communications")
        continue;
      if (device.kind==="audioinput" && !audioinput_name)
        audioinput_name = device.label;
      if (device.kind==="audiooutput" && !audiooutput_name)
        audiooutput_name = device.label;
      if (device.kind==="videoinput" && !videoinput_name)
       videoinput_name = device.label;  
    }

    var stats = 
    {
      version : {
        client:0, // 从插件获取版本号
        server:0, // 未完成
        local_low:false, // 自己版本低， 提示升级
        remote_low:false // 对方版本低，提示升级
      },
      device : {
        audioinput:audioinput_name,
        audiooutput:audiooutput_name,
        videoinput:videoinput_name
      },
      nat_traversal :{
        server_addr:RTCSDK_SELF.ice_server_, // 打洞地址
        server_status:"",
        local_status:"" // host，relay 
      },
      detail : "chrome://webrtc-internals/"
    }

    return new Promise(function(resolve, reject) {
        resolve(stats);
    });
  }
};



