<template>
  <div class="video-area">
    <div class="videos">
      <video id="big_render" class="my-video" tabIndex="-1"></video>
    </div>
    <div class="his-info" v-if="showInfo" >
      <!-- <div class="tip-name">
        <v-avatar :src="tipAvatar" class="user-avatar"/>
        {{tipName}}
      </div> -->
      <div class = "tip-info">{{showTargetBusy ? $t('chat.remoteBusy') :tipInfo}}</div>
      <div class="hang-up" @click="hangUp" v-if="!waitting">{{$t('chat.hangUp')}}</div>
      <div class = "buttonArea" v-if="waitting">
        <div class="accept" @click="acceptVideo" v-if="waitting">{{$t('chat.accept')}}</div>
        <div class="reject" @click="rejectVideo" v-if="waitting">{{$t('chat.reject')}}</div>
      </div>
    </div>
  </div>
</template>

<style scoped lang="scss">
.video-area {
  display: flex;
  flex-direction: column;
  align-items: center;
  height: 100%;
  background:  #27354f; //rgb(36, 37, 39);
  width: 100%;
  // z-index: 9;
  position: absolute;

  //left: 226px;
  .videos {
    height: 100%;
    width: 100%;
    //flex: 2;
    position: relative;
    // background: black;
    .my-video {
      height: 100%;
      width: 100%;
      //max-height: 720px;
      //display: flex;
      // background: black;
      cursor: none; // 隐藏鼠标
      position: relative;
      //left: 20px;
      //top: 20px;
      //color: white;
      //object-fit: fill;
    }
  }

  .his-info {
    flex: 1;
    display: flex;
    // background: #242527;
    font-size: 14px;
    position:absolute;
    //margin-left: 42%;
    top:0;
    left:0;
    width: 100%;
    height: 100%;
    flex-direction: column;
    align-items: center;
    .tip-name {
      width: 100%;
      color: white;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      .user-avatar {
        border-radius: $--border-radius-circle;
      }
    }
    .tip-info {
      height: 50px;
      color: white;
      display: flex;
      margin-top: 22%;
      align-items: center;
      justify-content: center;
      padding: 5px;
    }
    .buttonArea {
      height: 100px;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
    }
    .hang-up {
      width: 105px;
      padding: 5px;
      background: #384970;
      color: white;
      display: flex;
      align-items: center;
      justify-content: center;
      border-radius: $--border-radius-large;
      cursor: pointer;
    }
    .reject {
      height: 45px;
      width: 80px;
      background: #384970;
      color: white;
      display: flex;
      align-items: center;
      justify-content: center;
      border-radius: $--border-radius-large;
      cursor: pointer;
    }
    .accept {
      height: 45px;
      width: 80px;
      background: #384970;
      color: white;
      display: flex;
      align-items: center;
      justify-content: center;
      border-radius: $--border-radius-large;
      cursor: pointer;
    }
  }
}
</style>


<script>
import { RtcParam, Rtcsdk, RTC_PEER_TYPE } from "../../rtc/rtcsdk/rtcsdk";
import { RFB } from "../../rtc/remote_control/client/rfb";
import { Replay } from "../../rtc/remote_control/server/replay";
const { clipboard, remote, ipcRenderer } = require("electron");
const Service = remote.getGlobal('service')

const rtcplugin = remote.getGlobal("service")["rtcplugin"];
let rtcsdk = null;
let RTCP2P_self = null;
let caller_info = null;
let rfb = null;
let replay = null;
let remote_id = null;

// replay = new Replay();
// replay.win_test();

function OnRtcpluginMsg(req) {
  console.log("OnRtcpluginMsg:::", req);
  switch (req.type) {
    case 2: // 成员离开
      RTCP2P_self.hangUp();
      break;
    case 3: //  对方拒绝
      RTCP2P_self.hangUp();
      break;
    case 4: // 对方忙
      RTCP2P_self.showTargetBusy = true;
      setTimeout(() => {
        RTCP2P_self.hangUp();
      }, 5000);
      break;
    case 5: // 超时
      RTCP2P_self.hangUp();
      break;
    case 6: // 对方取消
      RTCP2P_self.hangUp();
      break;
    case 9: // 其他端处理
      RTCP2P_self.hangUp();
      break;
    case 11: // 对方接受
      rtcsdk.SetRemoteSDP(req.userId, req.sdp);
      break;
    case 13: // 房主离开
      RTCP2P_self.hangUp();
      break;
    case 20: // 视频转音频
      break;
    default:
      break;
  }
}

let cnt = 0;
let client_mask = 0;

function onRFBCallBack(e) {
  // if (e[0] !== client_mask) { // mask改变，需要立即处理
  //   client_mask = e[0];
  //   cnt = 3;
  // }

  // if (cnt === 3) {
  console.log("111112313123");
  if (remote_id !== null) {
    rtcsdk.SendData(remote_id, null, e.buffer);
    //document.getElementById('keyboard').focus();
  }
  //   cnt = 0;
  // }
  // else {
  //   cnt++;
  // }
}

export default {
  name: "singleVideo",
  beforeDestroy() {},
  beforeCreate() {},
  computed: {
    test2() {
      if (this.is_server) {
        return { height: "300px", width: "200px" };
      } else {
        return { height: "768px", width: "1440px" };
      }
    }
  },
  created() {
    ipcRenderer.on("closeRtc", () => {
      console.log("closeRtccloseRtccloseRtc");
      this.hangUp();
    });
    let language = Service.config.getLanguage()
    console.log('language:::', language)
    this.$i18n.locale = language;
    console.log('this.$i18n', this.$i18n)
    RTCP2P_self = this;
    let length = window.location.hash.split("?").length;
    if (length === 2) {
      // 主叫
      console.log("RTC_INFO: 主叫");
      console.log('remote', this.$t('chat.requestRemote'))
      this.tipInfo = this.$t('chat.requestRemote');
      this.waitting = false;
      this.is_server = true;
      replay = new Replay();
    } else {
      ipcRenderer.send('plugin-notify',true);
      console.log("RTC_INFO: 被叫");
      caller_info = rtcplugin.getData();
      this.tipInfo =  this.$t('chat.requestedRemote');
      this.is_server = false;
      this.waitting = true;
    }
  },
  data() {
    return {
      showTargetBusy:false,
      showInfo: true,
      waitting: false, // false:主叫；true：被叫
      tipName: "TEST", // 对方的名字
      tipAvatar: null, // 对方头像
      tipInfo: this.$t('chat.remoteAssistance'), //
      render: null,
      w: "",
      h: "",
      is_server: null
    };
  },
  mounted() {
    rtcsdk = new Rtcsdk(this.OnRtcsdkMsg);
    rtcplugin.regChannelEventCb(OnRtcpluginMsg);
    if (this.waitting === false) {
      let _this = this;
      async function CreateOffer(res) {
        let peer_id = window.location.hash.split("?")[1];
        let peer_type = RTC_PEER_TYPE.DESKTOP | RTC_PEER_TYPE.DATA;
        let rtc_param2 = new RtcParam();
        rtc_param2.ice_server=res["stunList"];
        // rtc_param2.ice_port=res.stunPort;
        // rtc_param2.ice_user =  res.account;
        // rtc_param2.ice_pwd = res.password;
        rtc_param2.sdp = null;
        rtc_param2.call_back = _this.OnRtcsdkMsg;
        rtc_param2.local_render = null;
        rtc_param2.remote_render = null;
        await rtcsdk.CreatePeer(peer_id, peer_type, rtc_param2);
      }

      rtcplugin.getStunServer(res => {
        CreateOffer(res);
      });
    }
  },
  methods: {
    OnRtcsdkMsg(peer_id, msg_type, msg, data_size) {
      switch (msg_type) {
        case 101:
          {
            let request = {
              targetId: peer_id,
              reject: false,
              videoType: 9,
              firstSdp: msg,
              operType: 0
            };
            console.log(request);
            rtcplugin.createChannel(request, res => {
              console.log("RtcP2P:createChannel()", res);
            });
          }
          break;
        case 102: // kAnswer
          {
            let request = {
              channelId: peer_id,
              targetId: peer_id, /// < 目标Id 创建/邀请
              videoType: 9, /// < 1，语音  2，视频
              secondSdp: msg, /// < 生成第二次sdp
              type: 1
            };
            console.log(request);
            rtcplugin.acceptOrReject(request, res => {
              console.log("RtcP2P:createChannel()", res);
            });
          }
          break;
        case 301: // kDataChannelOpen
          {
            this.tipInfo = this.$t('chat.remotingComputer');
            remote_id = peer_id;
          }
          break;
        case "kData":
          {
            replay.deal(msg);
          }
          break;
        default:
          break;
      }
    },
    test_onfocus() {
      console.log("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
    },
    switchRender() {
      console.log("GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
      // var myVideo = document.getElementById('small_render');
      // var hisVideo = document.getElementById('big_render');
      // //if (this.tipInfo == '您正在进行视频通话...') {
      //   [myVideo.src, hisVideo.src] = [hisVideo.src, myVideo.src];
      //   myVideo.play();
      //   hisVideo.play();
      // //}
    },
    acceptVideo() {
      ipcRenderer.send('plugin-notify',false);
      console.log("RTC_INFO: accept");
      rtcsdk = new Rtcsdk(this.OnRtcsdkMsg);
      rtcplugin.regChannelEventCb(OnRtcpluginMsg);
      let this_ = this;
      async function CreateOffer(res) {
        let peer_id = caller_info.userId;
        let peer_type = RTC_PEER_TYPE.DATA; // TODO ：被叫时peer类型无用
        let rtc_param2 = new RtcParam();
        rtc_param2.ice_server=res["stunList"];
        // rtc_param2.ice_port=res.stunPort;
        // rtc_param2.ice_user =  res.account;
        // rtc_param2.ice_pwd = res.password;
        rtc_param2.sdp = caller_info.sdp;
        rtc_param2.call_back = this_.OnRtcsdkMsg;
        rtc_param2.local_render = null;
        RTCP2P_self.InitRender("big_render");
        rtc_param2.remote_render = RTCP2P_self.render;
        await rtcsdk.CreatePeer(peer_id, peer_type, rtc_param2);
      }
      rtcplugin.getStunServer(res => {
        CreateOffer(res);
      });
      this.waitting = false;
      this.showInfo = false;

      // var mouse =  document.getElementById('mouse');
      // var keyboard = document.getElementById('haha');

      //var input = document.getElementById('myCanvas');
      var input = document.getElementById("big_render");

      rfb = new RFB(input, null, onRFBCallBack);
      input.focus();
    },
    rejectVideo() {
      console.log("RTC_INFO: rejcet");
      rtcplugin.resetCallback();
      let request = {
        channelId: caller_info.channelId,
        targetId: caller_info.userId, /// < 目标Id 创建/邀请
        videoType: 9, /// < 1，语音  2，视频
        type: 2 // 1：接受，2：拒绝
      };
      rtcplugin.acceptOrReject(request, res => {
        console.log("RtcP2P:acceptOrReject()", res);
      });
      setTimeout(() => {window.close();}, 500);
    },
    hangUp() {
      console.log("RTC_INFO: hang up");
      rtcplugin.resetCallback();
      rtcplugin.leaveChannel(res => {
        console.log("RtcP2P:leaveChannel()", res);
      });
      ipcRenderer.send('plugin-notify',false);
      setTimeout(() => {window.close();}, 500);
    },
    InitRender(render_name) {
      RTCP2P_self.render = document.getElementById(render_name);
      RTCP2P_self.render.addEventListener(
        "canplay",
        function(ev) {
          RTCP2P_self.w = RTCP2P_self.render.videoWidth;
          console.log(
            "RC_INFO, show remote desktop",
            RTCP2P_self.render.videoHeight,
            ":",
            RTCP2P_self.render.videoWidth
          );
        },
        false
      );
    }
  }
};
</script>


