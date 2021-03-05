<template>
  <div class="video-area">
    <div class="bg" :style="{'background-image':`url(file:///${tipAvatar})`}"></div>
    <div class="videos" v-show="videoType==2">
      <video id="big_render" class="his-video" @dblclick="switchRender()"></video>
      <video id="small_render" class="my-video" @dblclick="switchRender()"></video>
    </div>
    <div class="videos" v-if="videoType==1">
      <audio id="his_audio" class="his-video"></audio>
      <audio id="my_audio" class="my-video"></audio>
    </div>
    <div class="his-info" v-if="videoType==1">
      <v-avatar class="user-avatar" :src="tipAvatar"/>
      <span class="his-name">{{tipName}}</span>
      <div class="tip-state-audio" v-if="showLights">
        <span :class="['state-circle',{'state-pass': light_1}]"></span>
        <span :class="['state-circle',{'state-pass': light_2}]"></span>
        <span :class="['state-circle',{'state-pass': light_3}]"></span>
        <span :class="['state-circle',{'state-pass': light_4}]"></span>
      </div>
      <span class="tip-info" v-if="show_tip_or_timer">{{tipInfo}}</span>
      <span class="tip-info" v-if="!show_tip_or_timer">{{tipTime}}</span>
    </div>
    <p
      :style="{'position':'absolute','color':'#fff','font-size':'18px','left':'34%'}"
      v-if="showTargetBusy"
    >{{$t('chat.remoteBusy')}}</p>
    <div class="tip-state-video" v-show="videoType==2" v-if="showLights">
      <span :class="['state-circle',{'state-pass': light_1}]"></span>
      <span :class="['state-circle',{'state-pass': light_2}]"></span>
      <span :class="['state-circle',{'state-pass': light_3}]"></span>
      <span :class="['state-circle',{'state-pass': light_4}]"></span>
    </div>
    <div class="operate">
      <span class="tip-info" v-show="videoType==2" v-if="show_tip_or_timer">{{tipInfo}}</span>
      <span class="tip-info" v-show="videoType==2" v-if="!show_tip_or_timer">{{tipTime}}</span>
      <div>
        <div class="hang-up" @click="hangUpByUI" v-if="!waitting">
          <i class="icon" :title="$t('chat.hangUp')">&#xea2a;</i>
        </div>
        <div class="deal-Area" v-if="waitting">
          <i
            class="icon"
            @click="rejectVideo"
            :style="{'background':'#fff','color':'red'}"
            :title="$t('chat.reject')"
          >&#xea2a;</i>
          <i
            class="icon"
            @click="acceptVideo"
            :style="{'color':'#4cbc3c','background':'#fff', 'margin-left': '35px'}"
            :title="$t('chat.accept')"
          >&#xe654;</i>
        </div>
      </div>
    </div>
  </div>
</template>
<style >
.tip-state-video {
  bottom: 75px;
  display: flex;
  justify-content: center;
  width: 100%;
  position: absolute;
}
.state-circle {
  width: 8px;
  height: 8px;
  margin: 10px;
  border-radius: 8px;
  background-color: #ffffff;
}
.state-wait {
  background-color: white;
}

.state-pass {
  background-color: green;
}
</style>


<style lang="scss">
.notices {
  .toast {
    margin-top: 0px !important;
    // border-radius: 20px!important;
    padding: 0.55em 0.5em;
    min-width: 0px !important;
    border-top-width: 3px;
    border-top-color: rgba(0, 0, 0, 0.3);
    border-top-style: none !important;
    div {
      width: 100%;
    }
  }
}
.video-area {
  display: flex;
  align-items: center;
  flex-direction: column;
  width: 100%;
  height: 100%;
  z-index: 1;
  position: absolute;
  background: currentColor;
  // background: #27354f; //rgba(30, 3, 4a, 0.2);

  .bg {
    position: absolute;
    width: 100%;
    height: 100%;
    // background: url(file:///Users/zxj/Library/Containers/com.vrv.Linkdood/Data/Linkdood/public/head/hd2_0_head_20180815_1720_tiny_1R94_4d3d00001386085c.jpg);
    background-size: cover;
    background-position: center;
    // filter: blur(8px);
    filter: blur(20px) grayscale(30%);
    background-repeat: no-repeat;
    opacity: 0.6;
  }

  .videos {
    height: 100%;
    width: 100%;
    position: relative;
    .my-video {
      height: 100%;
      width: 100%;
      display: flex;
      color: white;
    }
    .his-video {
      position: absolute;
      left: 10px;
      top: 40px;
      height: 90px;
      border: 2px solid #fff;
      border-radius: $--border-radius-base;
      width: 119px;
      display: flex;
      align-items: center;
      justify-content: center;
      background: #323232;
    }
  }
  .his-info {
    flex: 1;
    display: flex;
    position: absolute;
    font-size: 14px;
    flex-direction: column;
    align-items: center;
    width: 100%;
    justify-content: center;
    top: 80px;
    .user-avatar {
      width: 80px;
      height: 80px;
      border-radius: $--border-radius-circle;
    }
    .his-name {
      top: 50px;
      font-size: 18px;
      color: white;
      white-space: nowrap;
      text-overflow: ellipsis;
      overflow: hidden;
      max-width: 160px;
      padding: 5px;
    }
    .tip-info {
      height: 50px;
      color: white;
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 5px;
    }
    .tip-state-audio {
      width: 100%;
      display: flex;
      justify-content: center;
    }
  }
  .operate {
    flex: 1;
    display: flex;
    position: absolute;
    font-size: 14px;
    flex-direction: column;
    // height: 60px;
    align-items: center;
    width: 100%;
    justify-content: space-between;
    bottom: 35px;
    .tip-info {
      //height: 50px;
      color: white;
      // display: flex;
      // align-items: center;
      // justify-content: center;
      // padding: 5px;
    }
    .deal-Area {
      font-size: 12px;
      display: flex;
      align-items: center;
      justify-content: center;
      cursor: pointer;
      .icon {
        font-size: 40px;
        height: 20px;
      }
      &:hover {
        opacity: 1;
      }
    }
    .stats {
      display: flex;
      opacity: 0.5;
      position: absolute;
      top: 35px;
      left: 1px;
      /* border-radius: 10px; */
      cursor: pointer;
      .icon {
        font-size: 18px;
      }
      &:hover {
        opacity: 1;
      }
    }
    .hang-up {
      background: #fff;
      color: red;
      font-size: 12px;
      display: flex;
      opacity: 0.5;
      align-items: center;
      justify-content: center;
      cursor: pointer;
      .icon {
        font-size: 40px;
      }
      &:hover {
        opacity: 1;
      }
    }
  }
}
</style>

<script>
import { RtcParam, Rtcsdk, RTC_PEER_TYPE } from "../../rtc/rtcsdk/rtcsdk";
const { clipboard, remote, ipcRenderer } = require("electron");
const rtcplugin = remote.getGlobal("service")["rtcplugin"];
const Service = remote.getGlobal("service");
const chat_service = remote.getGlobal("service").chat;
const user_service = remote.getGlobal("service").user;

let rtcsdk = null;
let RTCP2P_self = null;
let caller_info = null;
let sametime_call = 0;
let sametime_call_info = 0;
let seachParam = null;
let video_type;
let callee_id;
let isBurn = false; // 是否单次阅读 (阅后即焚 )
let ugly_weak_type = -1;
let ugly_hangup_by_rtcplugin = false;

let pass1 = true;
let pass2 = false;
let pass3 = true;

let ans_sdp = null;

let failed_timeout = null;

 // 弱提示是否已经插入，即若提示只插入一次
let weaktip_inserted = false;

// 被叫一收到呼叫消息，就进行createAnswer，之后如果webrtc不能在30s内联通，
// 会导致failed状态，这种情况不处理
let is_callee_ice_connected= false;

function OnRtcsdkMsg(peer_id, msg_type, msg, data_size) {
  Service.log(
    `OnRtcsdkMsg>> 0 = ,${msg_type} -- ${RTCP2P_self.videoType}`
  );
  switch (msg_type) {
    case "failed": {
      /*if (!is_callee_ice_connected) return;
      RTCP2P_self.show_tip_or_timer = true;
      RTCP2P_self.tipInfo = RTCP2P_self.$t("rtc.tip_ice_fail");
      RTCP2P_self.failTimer = setTimeout(() => {
        RTCP2P_self.showToast(
          RTCP2P_self.$t("rtc.weaknet"),
          "is-info",
          3 * 1000
        );
        failed_timeout = setTimeout(() => {
          console.log("3333333333333333333333333333333333");
          rtcplugin.extraEventCall({
            eventType: 13,
            reserveJson: "",
            strInfo: ""
          });
          RTCP2P_self.hangUpInner();
        }, 3 * 1000);
      }, 27 * 1000);*/
      break;
    }
    case "disconnected": {
        RTCP2P_self.show_tip_or_timer = true;
        RTCP2P_self.tipInfo = RTCP2P_self.$t("rtc.tip_reconnecting");
        if (!is_callee_ice_connected) return;
        RTCP2P_self.show_tip_or_timer = true;
        //RTCP2P_self.tipInfo = RTCP2P_self.$t("rtc.tip_ice_fail");
        RTCP2P_self.failTimer = setTimeout(() => {
          RTCP2P_self.showToast(
            RTCP2P_self.$t("rtc.weaknet"),
            "is-info",
            3 * 1000
          );
          failed_timeout = setTimeout(() => {
            rtcplugin.extraEventCall({
              eventType: 13,
              reserveJson: "",
              strInfo: ""
            });
            RTCP2P_self.hangUpInner();
          }, 3 * 1000);
        }, 47 * 1000);
        break;
      }
    case 101:
      {
        var req = rtcplugin.GetReq();
        if (
          req &&
          req.type === 1 &&
          req.videoType === video_type &&
          req.userId === req.userId
        ) {
          sametime_call = 1;
          sametime_call_info = req;
        }
        if (sametime_call === 1) {
          RTCP2P_self.destroyAndCreateAnswer();
          return;
        }
        let request = {
          targetId: peer_id,
          reject: false,
          videoType: RTCP2P_self.videoType,
          firstSdp: msg,
          operType: isBurn ? 3 : 0 // 0 普通模式 3 单次阅读
        };
        Service.log(`createChannel:${JSON.stringify(request)}`);
        rtcplugin.createChannel(request, res => {
          Service.log(`createChannel:${JSON.stringify(res)}`);
          if (res.code !== 0)
            RTCP2P_self.hangUpInner();
          RTCP2P_self.light('1');
          RTCP2P_self.setOfflineTimer(true);
        });
      }
      break;
    case 102: { // kAnswer
      let request = {
        channelId: caller_info.userId,
        targetId: caller_info.userId, /// < 目标Id 创建/邀请
        videoType: RTCP2P_self.videoType, /// < 1，语音  2，视频
        secondSdp: msg, /// < 生成第二次sdp
        type: 1
      };
      Service.log(`acceptOrReject:${JSON.stringify(request)}`);
      rtcplugin.acceptOrReject(request, res => {
        Service.log(`acceptOrReject:${JSON.stringify(res)}`);
        if (res.code === 0) {
          Service.log(`acceptOrReject:successed`);
          RTCP2P_self.light('3');
        } else {
          Service.log(`acceptOrReject:failed`);
          // http://192.168.6.160/linkdood-standard/av/rtc_docment/单人音视频/RTC_被叫接听_返回码添加_20190829.txt
          if (res.code === 100023501) {
            RTCP2P_self.showToast(this.$t("rtc.otherAnswerTip"), "is-info", 10*1000);
            setTimeout(() => {
              RTCP2P_self.hangUpInner();
            }, 2000);
            return;
          }
          RTCP2P_self.hangUpInner();
          return;
        }
      });
      break;
    }
    case 103: {
      is_callee_ice_connected  = true;
      ipcRenderer.send("plugin-notify", false);
      RTCP2P_self.show_tip_or_timer = false;

      if (failed_timeout !== null)
        clearTimeout(failed_timeout);

      RTCP2P_self.light('4');
      let myDate = new Date(); //获取系统当前时间
      RTCP2P_self.start_time = myDate.getTime();
      RTCP2P_self.is_connected = true;
      if (!RTCP2P_self.isConnection) {
        // 当已经连接成功后，避免通话时长乱跳
        RTCP2P_self.showDuration(true);
      }
      RTCP2P_self.setTimeoutTimer(false);
      RTCP2P_self.setOfflineTimer(false);
      // 清除 30秒重连倒计时
      if (RTCP2P_self.failTimer) {
        clearTimeout(RTCP2P_self.failTimer);
        RTCP2P_self.failTimer = null;
      }
      RTCP2P_self.showLights = false;
      break;
    }
    case 301: // kDataChannelOpen
      {
        rtcsdk.SendData(peer_id, "this is datachannel!");
      }
      break;
    case "kStats": {
      // 回调音视频状态
      var stats =
        "版本:\r\n" +
        "  客户端版本:\r\n" +
        "  服务端版本:\r\n" +
        "设备:\r\n" +
        "  视频输入设备:" +
        msg.device.videoinput +
        "\r\n" +
        "  音频输入设备:" +
        msg.device.audioinput +
        "\r\n" +
        "  音频输出设备:" +
        msg.device.audiooutput +
        "\r\n" +
        "网络穿透:\r\n" +
        "  服务地址:" +
        msg.nat_traversal.server_addr +
        "\r\n" +
        "  服务状态:\r\n" +
        "  本机状态:\r\n" +
        "点击查看详细数据";
      RTCP2P_self.stats = stats;
      break;
    }
    default:
      break;
  }
}

function OnRtcpluginMsg(req) {
  Service.log(`OnRtcpluginMsg>> 0 = ,${JSON.stringify(req)}`);
  switch (req.type) {
    case 1: // 处理对呼
    case 7:
      sametime_call = 1;
      sametime_call_info = req;
      break;
    case 2: // 成员离开
      let time = 1;
      if (RTCP2P_self.start_time !== 0) {
        let myDate = new Date(); //获取系统当前时间
        time = myDate.getTime() - RTCP2P_self.start_time;
      }
      if (RTCP2P_self.is_connected === true)
        RTCP2P_self.callback_to_sdk_and_ui("4", time.toString());
      else RTCP2P_self.callback_to_sdk_and_ui("1", "");
      RTCP2P_self.hangUpByRtcPlugin();
      break;
    case 3: //  对方拒绝
      // RTCP2P_self.callback_to_sdk_and_ui("3", "");
      RTCP2P_self.hangUpByRtcPlugin();
      break;
    case 4: // 对方忙
      RTCP2P_self.showTargetBusy = true;
      setTimeout(() => {
        RTCP2P_self.hangUpByRtcPlugin();
      }, 5000);
      break;
    case 5: // 超时
      RTCP2P_self.callback_to_sdk_and_ui("1", "");
      RTCP2P_self.hangUpByRtcPlugin();
      break;
    case 6: // 对方取消
      RTCP2P_self.hangUpByRtcPlugin();
      break;
    case 9: {// 其他端处理
      RTCP2P_self.callback_to_sdk_and_ui("6", "");
      RTCP2P_self.hangUpByRtcPlugin();
      break;
    }
    case 11: {// 对方接受
      RTCP2P_self.light('3');
      rtcsdk.SetRemoteSDP(req.userId, req.sdp);
      let extendJson = req.extendJson;
      try {
        extendJson = JSON.parse(extendJson);
      } catch (error) {
        Service.log(`RTCP2P::OnRtcpluginMsg parse extendJson fail: ${error}`);
      }
      let deviceType = extendJson.peer_devtype || 'pc'; 
      if(deviceType == 'ios' || deviceType == 'android'){
        ipcRenderer.send("change-window-type", {
          winUrl: `#/RTCP2P?type=${req.videoType}&Id=${req.userId}`, //'#/RTCP2P?type=' + type + '&Id=' + this.$route.query.id,
          winType: "RTCP2P",
          subType: 'toMoblie',
          winTitle: RTCP2P_self.$t("chat.audioCall"),
          winIcon: "",
          shapeType: "normal"
        });
      }
      break;
    }
    case 13: {
      // 房主离开
      let time = 1;
      if (RTCP2P_self.start_time !== 0) {
        let myDate = new Date(); //获取系统当前时间
        time = myDate.getTime() - RTCP2P_self.start_time;
      }
      if (RTCP2P_self.is_connected === true)
        RTCP2P_self.callback_to_sdk_and_ui("4", time.toString());
      else RTCP2P_self.callback_to_sdk_and_ui("1", "");
      RTCP2P_self.hangUpByRtcPlugin();
      break;
    }
    case 20: // 视频转音频
      ipcRenderer.send("change-window-type", {
        winUrl: `#/RTCP2P?type=${req.videoType}&Id=${req.userId}`, //'#/RTCP2P?type=' + type + '&Id=' + this.$route.query.id,
        winType: "RTCP2P",
        winTitle: RTCP2P_self.$t("chat.audioCall"),
        winIcon: "",
        subType: 'toAudio',
        shapeType: "normal"
      });
      RTCP2P_self.videoType = 1;
      break;
    case 27: { //对方ui弹出
      RTCP2P_self.light('2');
      break;
    }
    case 30: //存cache失败
    {
      RTCP2P_self.showToast(this.$t("rtc.tip_setcache_fail"), "is-info", 10*1000);
      setTimeout(() => {
          RTCP2P_self.hangUpInner();
        }, 3 * 1000);
    }
      break;
    case 31: //取cache失败
    {
      RTCP2P_self.showToast(this.$t("rtc.tip_getcache_fail"), "is-info", 10*1000);
      setTimeout(() => {
          RTCP2P_self.hangUpInner();
        }, 3 * 1000);
    }
      break;
    default:
      break;
  }
}

export default {
  name: "singleVideo",
  beforeDestroy() {
    // 清除 30秒重连倒计时
    if (RTCP2P_self.failTimer) {
      clearTimeout(RTCP2P_self.failTimer);
      RTCP2P_self.failTimer = null;
    }
    this.setTimeoutTimer(false);
    this.setOfflineTimer(false);
  },
  beforeCreate() {
    seachParam = new URLSearchParams(window.location.hash.split("?")[1]);
    //rtcplugin.regChannelEventCb(OnRtcpluginMsg);
    video_type = parseInt(seachParam.get("type"));
    callee_id = seachParam.get("Id");
    isBurn = seachParam.get('isBurn') === 'true';
    console.log("tcp2p>>", seachParam, video_type, callee_id);
  },
  created() {
    ipcRenderer.send("plugin-notify", true);
    ipcRenderer.on("closeRtc", () => {
      this.hangUpByMain();
    });
    RTCP2P_self = this;

    this.videoType = video_type;
    this.targetId = callee_id;

    user_service.getAccountInfo(null, info => {
      RTCP2P_self.local_id = info.id;
    });
    console.log("getTargetInfo>>", this.videoType === 1, this.videoType);

    if (this.targetId) {
      // 主叫
      console.log("RTC_INFO: 主叫");
      this.waitting = false;
      if (RTCP2P_self.waitting === false)
        this.tipInfo = this.$t("rtc.tip_init"); //'正在等待对方接受请求';
    } else {
      console.log("RTC_INFO: 被叫");
      this.setTimeoutTimer(true);
      caller_info = rtcplugin.getData();
      this.targetId = caller_info.userId;
      this.waitting = true;
      // if (this.videoType === 2)
      //   this.tipInfo = this.$t("rtc.inviteVideoRequest");
      // else this.tipInfo = this.$t("rtc.inviteVoiceRequest");
      rtcplugin.extraEventCall({ eventType: 12, reserveJson: "", strInfo: "" }); // 被叫弹出接听界面， 需要向主叫通知
    }
    this.getTargetInfo(this.targetId);
  },
  data() {
    return {
      start_time: 0, // 开始时间
      local_id: "",
      showTargetBusy: false, //对方忙提示
      waitting: false, // false:主叫；true：被叫
      isConnection: false, // 是否连通
      videoType: 1, // 1 音频  2 视频
      targetId: "", // 接收方id
      tipName: "", // 对方的名字
      tipAvatar: null, // 对方头像
      tipInfo: "", // 提示信息
      tipTime: "00.00", // 提示时间
      stats: "", // 音视频信息
      webRtcInfoWin: null,
      is_connected: false,
      closeTimer: null,
      light_1:false,
      light_2:false,
      light_3:false,
      light_4:false,
      showLights:true,
      // timer:{
      //   failed: null,
      //   timeout:null,
      //   offline:null,
      //   close:null
      // },
      show_tip_or_timer:true
    };
  },
  mounted() {
    Service.log(`RTCP2P::mounted`);

    // 处理呼叫和挂断消息同时到的问题
    if (rtcplugin.hasHangupMsg()) {
      setTimeout(()=>{
        RTCP2P_self.hangUpInner();
      }, 2000);
    }


    rtcplugin.regChannelEventCb(OnRtcpluginMsg);
    //rtcplugin.regSingleRtcCallBack(OnRtcpluginMsg);

    let language = Service.config.getLanguage();
    console.log("language:::", language);
    this.$i18n.locale = language;
    console.log("this.$i18n", this.$i18n);
    if (this.waitting === false) { // 主叫
      rtcsdk = new Rtcsdk(OnRtcsdkMsg);

      async function CreateOffer(res) {
        let peer_id = RTCP2P_self.targetId; //window.location.hash.split('=')[1];
        let peer_type =
          RTCP2P_self.videoType === 1
            ? RTC_PEER_TYPE.AUDIO
            : RTC_PEER_TYPE.VIDEO | RTC_PEER_TYPE.AUDIO;
        console.log("mounted>>", peer_type);
        let rtc_param2 = new RtcParam();
        rtc_param2.ice_server = res["stunList"];
        rtc_param2.sdp = null;
        rtc_param2.call_back = OnRtcsdkMsg;
        rtc_param2.local_render =
          RTCP2P_self.videoType === 1
            ? document.getElementById("my_audio")
            : document.getElementById("big_render");
        rtc_param2.remote_render =
          RTCP2P_self.videoType === 1
            ? document.getElementById("his_audio")
            : document.getElementById("small_render");

        await rtcsdk.CreatePeer(peer_id, peer_type, rtc_param2);
      }

      rtcplugin.getStunServer(res => {
        CreateOffer(res);
      });
    } else { // 被叫
      RTCP2P_self.light('1');
      /*rtcsdk = new Rtcsdk(OnRtcsdkMsg);
      async function CreateOffer(res) {
        let peer_id = caller_info.userId;
        let peer_type =
          RTCP2P_self.videoType === 1
            ? RTC_PEER_TYPE.AUDIO
            : RTC_PEER_TYPE.VIDEO | RTC_PEER_TYPE.AUDIO;
        let rtc_param2 = new RtcParam();
        rtc_param2.ice_server = res["stunList"];
        rtc_param2.sdp = caller_info.sdp;
        rtc_param2.call_back = OnRtcsdkMsg;
        rtc_param2.local_render =
          RTCP2P_self.videoType === 1
            ? document.getElementById("my_audio")
            : document.getElementById("big_render");
        rtc_param2.remote_render =
          RTCP2P_self.videoType === 1
            ? document.getElementById("his_audio")
            : document.getElementById("small_render");
        await rtcsdk.CreatePeer(peer_id, peer_type, rtc_param2);
      }
      rtcplugin.getStunServer(res => {
        CreateOffer(res);
      });*/
    }
    //this.startWaitTimer(true);
  },
  methods: {
    light(index) {
      if (index === '1') {
        RTCP2P_self.light_1 = true;
        RTCP2P_self.light_2 = false;
        RTCP2P_self.light_3 = false;
        RTCP2P_self.light_4 = false;
      } else if (index === '2') {
        RTCP2P_self.light_1 = true;
        RTCP2P_self.light_2 = true;
        RTCP2P_self.light_3 = false;
        RTCP2P_self.light_4 = false;
        if (RTCP2P_self.waitting === false)
          RTCP2P_self.tipInfo = this.$t("rtc.tip_2nd_light");
      } else if (index === '3') {
        RTCP2P_self.light_1 = true;
        RTCP2P_self.light_2 = true;
        RTCP2P_self.light_3 = true;
        RTCP2P_self.light_4 = false;
        RTCP2P_self.tipInfo = this.$t("rtc.tip_3rd_light");
      } else if (index === '4') {
        RTCP2P_self.light_1 = true;
        RTCP2P_self.light_2 = true;
        RTCP2P_self.light_3 = true;
        RTCP2P_self.light_4 = true;
      }
    },
    /**
     * 顶部提示气泡
     */
    showToast(m, t, duration = 2000) {
      console.log("ssssssssssssssssssssssssssssssssssssssss", this.$toast);
      this.$toast.open({
        duration: duration,
        message: m,
        position: "is-top",
        type: t
      });
    },
    getTargetInfo(userId) {
      Service.search.getUserInfo(
        {
          userId
        },
        userInfo => {
          console.log("getTargetInfo>>", userInfo);
          this.tipName = userInfo.users.remark || userInfo.users.name;
          this.tipAvatar = userInfo.users.thumbAvatar;
        }
      );
    },
    switchRender() {
      var myVideo = document.getElementById("small_render");
      var hisVideo = document.getElementById("big_render");
      if (myVideo.srcObject && hisVideo.srcObject) {
        [myVideo.srcObject, hisVideo.srcObject] = [
          hisVideo.srcObject,
          myVideo.srcObject
        ];
        myVideo.play();
        hisVideo.play();
      }
    },
    acceptVideo() {
      RTCP2P_self.light('2');
      rtcsdk = new Rtcsdk(OnRtcsdkMsg);
      async function CreateOffer(res) {
        let peer_id = caller_info.userId;
        let peer_type =
          RTCP2P_self.videoType === 1
            ? RTC_PEER_TYPE.AUDIO
            : RTC_PEER_TYPE.VIDEO | RTC_PEER_TYPE.AUDIO;
        let rtc_param2 = new RtcParam();
        rtc_param2.ice_server = res["stunList"];
        rtc_param2.sdp = caller_info.sdp;
        rtc_param2.call_back = OnRtcsdkMsg;
        rtc_param2.local_render =
          RTCP2P_self.videoType === 1
            ? document.getElementById("my_audio")
            : document.getElementById("big_render");
        rtc_param2.remote_render =
          RTCP2P_self.videoType === 1
            ? document.getElementById("his_audio")
            : document.getElementById("small_render");
        await rtcsdk.CreatePeer(peer_id, peer_type, rtc_param2);
      }
      rtcplugin.getStunServer(res => {
        CreateOffer(res);
      });
      RTCP2P_self.waitting = false;
    /*Service.log(`acceptVideo`);
      RTCP2P_self.light('2');
      this.setTimeoutTimer(false);

      let inter = null;
      inter = setInterval(function(){ 
        if (ans_sdp !== null) {
          clearInterval(inter);
          {
            let request = {
              channelId: caller_info.userId,
              targetId: caller_info.userId, /// < 目标Id 创建/邀请
              videoType: RTCP2P_self.videoType, /// < 1，语音  2，视频
              secondSdp: ans_sdp, /// < 生成第二次sdp
              type: 1
            };
            Service.log(`acceptOrReject:${JSON.stringify(request)}`);
            rtcplugin.acceptOrReject(request, res => {
              // http://192.168.6.160/linkdood-standard/av/rtc_docment/单人音视频/RTC_被叫接听_返回码添加_20190829.txt
              if (res === 100023501) {
                RTCP2P_self.showToast(this.$t("rtc.otherAnswerTip"), "is-info", 10*1000);
                setTimeout(() => {
                  RTCP2P_self.hangUpInner();
                }, 2000);
                return;
              }
              Service.log(`acceptOrReject:${JSON.stringify(res)}`);
              RTCP2P_self.light('3');
            });
          }

          RTCP2P_self.waitting = false;
          console.log('zzzzzzzzzzzzzzzzzzzzzzzz', ans_sdp);
        }
      }, 500);*/
    },
    rejectVideo() {
      Service.log(`rejectVideo`);
      this.setTimeoutTimer(false);
      rtcplugin.resetCallback();
      let request = {
        channelId: caller_info.channelId,
        targetId: caller_info.userId, /// < 目标Id 创建/邀请
        videoType: this.videoType, /// < 1，语音  2，视频
        type: 2 // 1：接受，2：拒绝
      };
      Service.log(`acceptOrReject${JSON.stringify(request)}`);
      rtcplugin.acceptOrReject(request, res => {
        Service.log(`acceptOrReject${JSON.stringify(res)}`);
      });
      this.hangUpByUI();
    },
    hangUpInner() {
      ipcRenderer.send("plugin-notify", false);
      rtcplugin.resetCallback();
      Service.log(`leaveChannel`);
      rtcplugin.leaveChannel(res => {
        Service.log(`leaveChannel:${JSON.stringify(res)}`);
      });
      setTimeout(() => {window.close();}, 500);
      if (this.webRtcInfoWin) this.webRtcInfoWin.close();
    },
    hangUpByMain() {
      Service.log(`hangUpByMain`);
      if (RTCP2P_self.is_connected) {
        Service.log(`hangUpByMain::Connected`);
        let myDate = new Date(); //获取系统当前时间
        let time = myDate.getTime() - RTCP2P_self.start_time;
        RTCP2P_self.callback_to_sdk_and_ui("4", time.toString());
      } else {
        if (!ugly_hangup_by_rtcplugin) {
          if (RTCP2P_self.waitting === false) {
            Service.log(`hangUpByMain::Cancel`);
            RTCP2P_self.callback_to_sdk_and_ui("2", "");
          } else {
            Service.log(`hangUpByMain::Reject`);
            //RTCP2P_self.callback_to_sdk_and_ui("3", "");
          }
        }
      }
      RTCP2P_self.hangUpInner();
    },
    hangUpByRtcPlugin() {
      ugly_hangup_by_rtcplugin = true;
      Service.log(`hangUpByRtcPlugin`);
      RTCP2P_self.hangUpInner();
    },
    hangUpByUI() {
      Service.log(`hangUpByUI`);
      if (RTCP2P_self.is_connected) {
        Service.log(`hangUpByUI::Connected`);
        let myDate = new Date(); //获取系统当前时间
        let time = myDate.getTime() - RTCP2P_self.start_time;
        RTCP2P_self.callback_to_sdk_and_ui("4", time.toString());
      } else {
        if (RTCP2P_self.waitting === false) {
          Service.log(`hangUpByUI::Cancel`);
          RTCP2P_self.callback_to_sdk_and_ui("2", "");
        } else {
          Service.log(`hangUpByUI::Reject`);
          RTCP2P_self.callback_to_sdk_and_ui("3", "");
        }
      }

      RTCP2P_self.hangUpInner();
    },
    showStatsWindow() {
      this.webRtcInfoWin = rtcplugin.openWebRtcInfoWindow();
      // 打开该地址chrome://webrtc-internals/
    },
    getStats() {
      // 只要
      return this.stats;
    },
    showDuration(bolean) {
      console.log("start>>" + bolean);
      let _this = this;
      let hour, minute, second;
      hour = minute = second = 0;
      if (bolean) {
        _this.isConnection = true;
        _this.timer = setInterval(function() {
          if (second >= 0) {
            second = second + 1;
          }
          if (second >= 60) {
            second = 0;
            minute = minute + 1;
          }
          if (minute >= 60) {
            minute = 0;
            hour = hour + 1;
          }
          if (hour) {
            _this.tipTime = `${hour}:${minute}:${second}`;
          } else {
            _this.tipTime = `${minute > 9 ? "" : "0"}${minute}:${
              second > 9 ? "" : "0"
            }${second}`;
          }
        }, 1000);
      } else {
        _this.isConnection = false;
        window.clearInterval(_this.showDuration(false));
      }
    },
    // 网络超时 计时器
    setTimeoutTimer(start) {
      if (start) {
        this.closeTimer = setTimeout(() => {
          if (this.waitting) { // 被叫
            RTCP2P_self.showToast(this.$t("rtc.callee_timeout"), "is-info", 10*1000);
          }
          setTimeout(()=>{
            RTCP2P_self.hangUpInner();
          }, 1000);
        }, 73 * 1000);
      } else {
        if (this.closeTimer) {
          clearTimeout(this.closeTimer);
          this.closeTimer = null;
        }
      }
    },
    // 对方不在线 计时器
    setOfflineTimer(start) {
      if (start) {
        this.offlineTimer = setTimeout(() => {
          // this.showToast('对方可能不在线...', 'is-info');
          //this.tipInfo = this.$t("rtc.tip_target_offline");
          this.showToast(this.$t("rtc.tip_target_offline"), "is-info");
        }, 58 * 1000);
      } else {
        if (this.offlineTimer) {
          clearTimeout(this.offlineTimer);
          this.offlineTimer = null;
        }
      }
    },
    destroyAndCreateAnswer() {
      Service.log(`sametime_call:${JSON.stringify(sametime_call_info)}`);
      rtcsdk.DestroyAll();

      async function CreateOffer(res) {
        let peer_id = sametime_call_info.userId;
        let peer_type =
          RTCP2P_self.videoType === 1
            ? RTC_PEER_TYPE.AUDIO
            : RTC_PEER_TYPE.VIDEO | RTC_PEER_TYPE.AUDIO;
        let rtc_param2 = new RtcParam();
        rtc_param2.ice_server = res["stunList"];
        rtc_param2.sdp = sametime_call_info.sdp;
        rtc_param2.call_back = OnRtcsdkMsg;
        rtc_param2.local_render =
          RTCP2P_self.videoType === 1
            ? document.getElementById("my_audio")
            : document.getElementById("big_render");
        rtc_param2.remote_render =
          RTCP2P_self.videoType === 1
            ? document.getElementById("his_audio")
            : document.getElementById("small_render");
        await rtcsdk.CreatePeer(peer_id, peer_type, rtc_param2);
      }
      rtcplugin.getStunServer(res => {
        CreateOffer(res);
      });
      this.waitting = false;
    },
    callback_to_sdk_and_ui(msgType, msgInfo) {
      if(isBurn) return; // 单次阅读不做处理
      if(weaktip_inserted === true)
        return;
      weaktip_inserted = true;

      if (ugly_weak_type !== -1) return;
      ugly_weak_type = msgType;
      Service.log(`callback_to_sdk_and_ui:${JSON.stringify(ugly_weak_type)}`);

      let to_sdk = true;
      if (msgType === "2" || msgType === "3" || msgType === "6")
        // 这两种情况不向sdk推送消息
        to_sdk = false;

      let myDate = new Date(); //获取系统当前时间
      let time = 0;
      time = myDate.getTime().toString();

      let msg = {};
      msg.msgType = 14;
      msg.fromId = RTCP2P_self.local_id;
      msg.targetId = RTCP2P_self.targetId;
      msg.time = time;
      msg.videoType = RTCP2P_self.videoType.toString();
      msg.msgModel = msgType;
      msg.msgInfo = msgInfo;
      msg.deviceType = 1;
      msg.toId = RTCP2P_self.targetId;
      msg.msgId = msg.time;
      msg.VideoType = RTCP2P_self.videoType.toString(); //用于向消息列表插入时适配
      msg.body = JSON.stringify(msg);

      if (to_sdk === true) {
        chat_service.insertMessage(msg, result => {});
      }

      rtcplugin.SendRTCWeakTips(msg);
    }
  }
};
</script>
