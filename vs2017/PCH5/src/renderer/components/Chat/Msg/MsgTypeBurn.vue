<template>
  <div class="msgtype-burn">
    <div class="burn-msg-body" :class="{'video-padding':isVideoMsg}">
      
      <component v-if="isNormalMsg" :is="currentMsg" :class="{'bubble-msg':isAudioMsg}" :message="message" :id="id" :isOpen="isOpen" @audioHasClick="audioBurn"></component>
      <div v-else>{{this.$t('chat.notSupportedBurnChat')}}</div>
    </div>

    <div class="modal-card-foot" slot="footer-bottom" >
      <div class="burn-msg-countdown" @click="pauseOrPlayBurn" :title="isPause ? this.$t('chat.continue'):this.$t('chat.pause')">
      <i class="icon clock-bg">&#xe6b8;</i>
      <span class="countdown">{{countDown + 's'}}</span>
      </div>
      <v-button class="burn-immediate" @click="burnImmediate">{{this.$t('chat.burnImmediate')}}</v-button>
    </div>
  </div>
</template>
<script>
const burnMsg = {
  Text: 2,
  Audio: 3,
  Image: 5,
  File: 6,
  Card: 7,
  MirVideo: 89
};
import MsgMixin from "@/components/Chat/msgMixin";

export default {
  data() {
    return {
      countDown: 0,
      timer: {},
      isAudioClick: false,
      isAudioMsg: false,
      isVideoMsg: false,
      isNormalMsg: true,
      isPause: false
    };
  },
  mixins: [MsgMixin],
  mounted() {
    let msgtype = this.message.messageObject.msgType
    if (msgtype === 3) {
      this.isAudioMsg = true
    }
    if (msgtype === 89) {
      this.isVideoMsg = true
    }
    /** 文件暂不支持阅后即焚 防止用户下载 */
    if (msgtype === 6) {
      this.isNormalMsg = false
    }
    this.handleBurn();
  },
  props: {
    currentMsg: Object | String,
    message: Object,
    id: String,
    isOpen: Boolean
  },
  beforeDestroy() {
    clearInterval(this.timer);
  }, 
  methods: {
    pauseOrPlayBurn() {
      this.isPause = !this.isPause;
      if (this.isPause) {
        clearInterval(this.timer);
      } else {
        this.handleBurn()
      }
    },
    burnImmediate() {
      clearInterval(this.timer);
      this.delMsg(this.message.messageObject.targetId, this.message.messageObject.msgId);
      // this.$set(this.testDate, `id_${'1001'}`, "1");
      // this.$set(this.testDate, `id_${'1003'}`, "1");
      // this.$set(this.testDate, `id_${'1002'}`, "1");
      // this.$set(this.testDate, `id_${'911112123123123002'}`, "1");
      // this.$set(this.testDate, `id_${'611112123123123002'}`, "1");
      // this.$set(this.testDate, `id_${'811112123123123002'}`, "1");
      // this.$set(this.testDate, `id_${'1009'}`, "1");
      // for (var i in this.testDate) {
      //   console.log(i);
      // }
    },
        /** 
     * 音频消息的阅后即焚需要特殊处理
     * 需在打开语音后才计算时间
     */
    audioBurn() {
      this.isAudioClick = true;
      this.handleBurn()
    },
    handleBurn() {
      if (this.message.messageObject.activeType === 1) {
        if (!this.countDown) {
          this.countDown = this.computedBurnTime();
        }
        if ((this.message.messageObject.msgType === 3 || this.message.messageObject.msgType === 89 )&& !this.isAudioClick) {
          return;
        }
        this.timer = setInterval(() => {
          if (this.countDown <= 1) {
            clearInterval(this.timer);
            this.delMsg(
              this.message.messageObject.targetId,
              this.message.messageObject.msgId
            );
          } else {
            this.countDown--;
          }
        }, 1000);
      }
    },

    /**
     * 计算销毁时间
     * 图片消息默认20秒销毁
     * 音频消息为本语音消息的长度+2
     * 文本消息根据文字长度来判断
     */
    computedBurnTime() {
      let burnTime;
      switch (this.message.messageObject.msgType) {
        case burnMsg.Text:
          burnTime = this.textBurnTime();
          break;

        case burnMsg.Audio:
          burnTime =
            Math.floor(this.message.messageObject.mediaTime / 1000) + 5;
          break;

        case burnMsg.Image:
          burnTime = 20;
          break;

        // case burnMsg.File:
        //   burnTime = 5;
        //   break;

        case burnMsg.Card:
          burnTime = 10;
          break;

        case burnMsg.MirVideo: 
          burnTime =
            Math.floor(this.message.messageObject.vedioLenth / 1000) + 5;
          break;
        default:
          burnTime = 5;
          break;
      }
      return burnTime;
    },

    textBurnTime() {
      let burnTime,
        content = this.message.messageObject.body;
      if (content.length < 20) {
        burnTime = 5;
      } else if (content.length < 40) {
        burnTime = 10;
      } else if (content.length < 60) {
        burnTime = 15;
      } else {
        burnTime = 20;
      }
      return burnTime;
    }
  }
};
</script>
<style lang="scss">
.burns-msg-box {
  width: 460px;
  border-radius: 3px;
  .modal-background {
    pointer-events: none!important;
  }
}
#burn-box {
.modal-background {
    pointer-events: none;
  }
}
.msgtype-burn {
  .modal-card {
    width: 460px;
    border-radius: 3px;
  }

  .video-padding {
    padding: 10px 0;
  }

  .burn-msg-body {
    min-height: 220px;
    width: 100%;
    border: solid 1px #dbdbdb;
    display: flex;
    justify-content: center;
    align-items: center;
    .bubble-msg {
      border-radius: 18px;
      background: $--color-danger;
      color: #fff;
      box-shadow: $--box-shadow-rd;
    }
  }
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  padding: 12px;
  .modal-card-foot {
    background: none;
    width: 100%;
    display: flex;
    justify-content: center;
    padding: 12px;
    border-top: none;
    .burn-msg-countdown {
      width: 40px;
      height: 40px;
      // border-radius: 50%;
      // border: solid 1px $--color-danger;
      margin-right: 15px;
      display: flex;
      justify-content: center;
      align-items: center;
      color: $--color-danger;
      position: relative;
      .clock-bg {
        font-size: 40px;
        height: 40px;
        width: 40px;
        display: flex;
        align-items: center;
        justify-content: center;
      }
      .countdown {
        position: absolute;
        font-size: 12px;
        width: 100%;
        height: 100%;
        display: flex;
        align-items: center;
        justify-content: center;
        left:0; //fix xp
      }
    }
    .burn-immediate{
      width: 160px;
      background: $--color-danger;
      color: #fff;
      box-shadow: $--box-shadow-rd;
    }
  }
}
</style>
