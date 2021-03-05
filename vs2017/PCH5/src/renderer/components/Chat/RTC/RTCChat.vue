<template>
  <div class="video-area">
    <full-screen-video v-if="fullScreen" :myVideoSrc= "getMyVideoSrc()" @close="fullScreen=false"></full-screen-video>
    <div class="videos">
      <video id="hisVideo" class="his-video" @dblclick="changeClass()"></video>
      <i class="icon" @click="fullScreen=true">&#xe786;</i>
      <video id="myVideo" class="my-video"  @dblclick="changeClass()"></video>
    </div>
    <div class="his-info">
      <div class="tip-name">
        <v-avatar :src="tipAvatar" class="user-avatar"/>
        {{tipName}}
      </div>
      <div class = "tip-info">{{tipInfo}}</div>
      <div class="hang-up" @click="stopVideo" v-if="!waitting">挂 断</div>
      <div class = "buttonArea" v-if="waitting">
      <div class="accept" @click="acceptVideo" v-if="waitting">接 受</div>
      <div class="reject" @click="rejectVideo" v-if="waitting">拒 绝</div>
      </div>
    </div>
  </div>
</template>
<script>
import Peer from './peer';
import fullScreenVideo from './FullScreenVideo.vue';
const callWebRtc = new Peer();
export default {
  beforeDestroy () {
    console.log('beforeDestroy video.vue')
    this.$signalMonitor.$off('ChannelEvent',this.handleChannelEvent);
  },
  created() {
    console.log('created Video.vue');
    this.$signalMonitor.$on('ChannelEvent', this.handleChannelEvent);
    if (this.isCaller) {
      this.tipInfo = '您正在发起视频通话...';
      this.startVideo(this.offerInfo);
    } else {
      this.waitting = true;
      this.tipInfo = '请求与您进行视频通话...';
    }
    
    this.toolTip = {
      2: this.offerInfo.userName + ' 挂断了视频会话',
      3: this.offerInfo.userName + ' 拒绝了您的视频请求',
      4: this.offerInfo.userName + ' 正在与他人进行视频会话',
      5: '视频会话超时',
      6: '视频会话取消',
      8: '视频链接已经断开',
      13: this.offerInfo.userName + ' 挂断了视频会话'
    }
  },
  data() {
    return {
      waitting: false,
      tipInfo: '',
      tipName: this.offerInfo.userName,
      tipAvatar: this.offerInfo.userAvatar,
      fullScreen: false
    };
  },
  components: {
    fullScreenVideo
  },
  props: {
    isCaller: false,
    offerInfo: {}
  },
  mounted() {
    signaling.on('leaveChannel', () => {

    });  
  },
  methods: {
    getMyVideoSrc() {
      var myVideo = document.getElementById('hisVideo');
      return myVideo.src;
    },
    changeClass() {
      var myVideo = document.getElementById('myVideo');
      var hisVideo = document.getElementById('hisVideo');
      if (this.tipInfo == '您正在进行视频通话...') {
        [myVideo.src, hisVideo.src] = [hisVideo.src, myVideo.src]
        myVideo.play();
        hisVideo.play();
      }
    },
    call(offerinfo) {
      signaling.emit(this.isCaller, offerinfo);
    },
    accept() {
      signaling.emit(this.isCaller, this.offerInfo);
      this.tipInfo = '您正在进行视频通话...';
      this.waitting = false;
    },
    reject() {
      signaling.emit(this.isCaller, this.offerInfo);
      let info = {
        channelId: this.offerInfo.channelId,
        targetId: this.offerInfo.userId, /// < 目标Id 创建/邀请
        videoType: 2, /// < 1，语音  2，视频
        type: 2
      };
      this.$Service.rtcService(
        'acceptOrReject',
        res => {
          // this.$emit('closeVideo');
          this.$signalMonitor.$emit('closeVideo', '');
        },
        info
      );
    },

    stopVideo() {
      callWebRtc.stopVideo();
      this.$signalMonitor.$emit('closeVideo', '');
    },


    handleChannelEvent(resp){
      console.log('handleChannelEvent');
      // type: 1,请求 2,挂断 3,请求被拒 4,对方忙 5,超时 6,取消7,连接成功,8,连接断开,9,其他端已接受,10,P2P完成,11,收到accept 消息 现在需要调用createAnswer 12,收到responce 代表现在要调用setRemoteDescrption
      if (resp.type === 11) {
        this.tipInfo = '您正在进行视频通话...';
        callWebRtc.setRemoteVideo(resp.sdp, false);
      }

      const messageInfo = this.toolTip[resp.type]
      if (messageInfo != undefined) {
        this.stopVideo();
        this.$dialog.alert({
          message: messageInfo,
          confirmText: '确认',
          onConfirm: () => {}
        });
      }
    }
  }
};
</script>