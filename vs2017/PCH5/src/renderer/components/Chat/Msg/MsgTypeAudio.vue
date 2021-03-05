<template>
    <div class="audio-play" :class="[message.messageObject.fromId === user_account.userId&&!isMixMsg?'audio-play-mine':'audio-play-other', {'audio-no-ready': !this.isDownLoad }]"  @click.stop="open">
      <div class="audio-box" >
        <span class="voice-icon" :class="voiceClass">
          <span class="voice-2"></span>
          <span class="voice-3"></span>
          <span class="voice-4"></span>
        </span>
      </div>
      <i class="icon play-icon" v-if='isShowBtn'  v-html="playBtnContent"></i>
      <v-badge class="audio-unread"
                v-if="isShowBadge"
                :isDot='true' 
                :value='1'>
      </v-badge>
      <span class='media-time' >{{mediaTime+'"'}}</span>
      <div  v-if="isDecode" >
      <audio id='audio' class="audio-msg" @error="handleErrorAudio" :data="message.messageObject.msgId"  ref="msgAudios" @play="check" @pause="voiceClass = 'strength-no'" @ended="voiceClass = 'strength-no'" :src="'file://'+ audioSource" autoplay ></audio>
      </div>
    </div>
</template>


<script>
import { mapGetters } from 'vuex'
import FileMixin from '../Mixins/FileMixins'
import AMR from './amrnb.js'
export default {
  data() {
    return {
      decryptFiles: '',
      isClick: false,
      audioSource: '',
      mediaTime: '',
      isDecode: false,
      voiceClass: 'strength-no',
      state: 0,
      playBtnContent: '&#xe778;',
      isShowBtn: false,
      isDownLoad: false
    }
  },
  mixins: [FileMixin],
  watch: {
    $route() {
      if (this.$refs.msgAudios && !this.$refs.msgAudios.paused) {
        this.$refs.msgAudios.pause()
      }
    },
    voiceClass() {
      this.voiceClass === 'strength-no'
        ? (this.playBtnContent = '&#xe778;')
        : (this.playBtnContent = '&#xe663;')
    }
  },
  created() {
    console.log('auido', this.message)
    // * 获取音频消息的总时长
    this.mediaTime = Math.floor(this.message.messageObject.mediaTime / 1000)
    // * 获取语音消息信息 本地路径
    this.getFileInfo(this.user_audioPath, this.message.messageObject.url).then( successResult => {
      if (this.isExistFile) {
        this.isShowBtn = true;
        this.state = 0;
        this.isDownLoad = true
        console.log('this.isExistFile')
      } else {
         this.playBtnContent = '&#xe61d;'
         this.downLoad()
      }
    })
  },
  computed: {
    // * 是否显示首播红点
    isShowBadge() {
      return !this.isExistFile && !this.isClick && this.message.messageObject.fromId !== this.user_account.userId
    },

    computedLength() {
      if (this.mediaTime < 5) {
        return 'width:70px'
      } else if (this.mediaTime >= 5 && this.mediaTime < 10) {
        return 'width:120px'
      } else if (this.mediaTime >= 10 && this.mediaTime < 15) {
        return 'width:160px'
      } else if (this.mediaTime >= 15 && this.mediaTime < 20) {
        return 'width:200px'
      } else if (this.mediaTime >= 20 && this.mediaTime < 30) {
        return 'width:240px'
      } else if (this.mediaTime >= 30 && this.mediaTime < 40) {
        return 'width:320px'
      } else if (this.mediaTime >= 40 && this.mediaTime < 50) {
        return 'width:400px'
      } else {
        return 'width:480px'
      }
    },
    ...mapGetters(['user_audioPath', 'user_account'])
  },
  methods: {

    // * 异常处理
    handleErrorAudio(e) {
      // * 1.用户终止 2.网络错误 3.解码错误 4.URL无效(视频格式不被支持)  
      console.log('handle error audio...', e.currentTarget.error.code)
      let deviceType = JSON.parse(this.message.messageObject.msgProperties).deviceType;
      console.log('deviceType', deviceType)
      this.audioSource = this.decryptFiles;
      this.isDecode = true;
    },

    // * 检查播放状态 保证只能播放一个语音
    check() {
      let audios = document.getElementsByClassName('audio-msg')
      if (audios.length > 1) {
        for (var i = 0; i < audios.length; i++) {
          if (!audios[i].paused && audios[i].attributes[2].nodeValue != this.message.messageObject.msgId) {
            audios[i].pause()
          }
        }
      }
    },

    // * 下载语音文件
    downLoad() {
      this.downLoadFile().then(successResp => {
        console.log('successResp::', successResp)
        this.isShowBtn = true;
        if (successResp.code === 0) {
          this.state = 0;
          this.playBtnContent = '&#xe778;'
          this.isDownLoad = true
        } else {
          this.playBtnContent = '&#xe61d;'
          this.state = -1;
          this.$Service.log('downLoadFile_Audio fail')
        }
      })
    },

    // * 打开语音消息
    open() {
      if (!this.isShowBtn) return
      if (this.state !== 0) {
        this.isShowBtn = false
        this.playBtnContent = '&#xe658;'
        this.downLoad()
        return
      }

      // * 防止重复点击 导致的重复解密
      if (this.isClick && !this.isDecode) return
      this.voiceClass = this.voiceClass === 'strength-no' ? 'strength-ready' : 'strength-no'

      if (!this.isClick) {
        this.isClick = true

        // * 阅后即焚的语音消息 需要点击后才开始倒计时 从而销毁
        if (this.message.messageObject.activeType) {
          this.$emit('audioHasClick')
        }

        this.decryptFiles = this.createCachePath(this.user_audioPath, this.message.messageObject.fileName, this.message.messageObject.uuid)
        this.decrypted(this.message.messageObject.encryptKey, this.encryptFileSavePath, this.decryptFiles).then(resp => {
          this.isNeedDecode()
        })
      } else {
        /**
         * 点击过 判断音频文件是否下载成功
         * 如果下载成功 则控制暂停与播放
         * 没有下载成功则不做处理
         */
        if (this.audioSource) {
          let myAudio = this.$refs.msgAudios
          console.log('this.audioSource:::::::', myAudio)
          myAudio.paused
            ? (myAudio.load(), (this.voiceClass = 'strength-ready'))
            : (myAudio.pause(), (this.voiceClass = 'strength-no'))
        }
      }
    },

    // * 特殊处理 以前标准版pc发的语音 存在格式问题 需要异常处理
    isNeedDecode() {
      if (this.decryptFiles.includes('.wav')) {
        this.audioSource = this.decryptFiles
        this.isDecode = true
      } else {
        this.decodeWav()
      }
    },

    // 解密语音
    decodeWav() {
      let audioSource = this.decryptFiles.substr(0, this.decryptFiles.lastIndexOf('.') + 1) + 'wav'
      console.log('audioSource', this.audioSource)
      this.$fs.readFile(this.decryptFiles, (err,data)=>{
        let wav = AMR.toWAV(new Uint8Array(data));
        this.$fs.writeFile(audioSource, wav,  (err) => {
          if (err) throw err;
            console.log('It\'s saved!');
            this.$nextTick(()=>{
              this.audioSource = audioSource;
              this.isDecode = true;
            })
        })
      })
    }
  },
  props: {
    message: Object,
    isMixMsg: Boolean
  }
}
</script>
<style lang="scss" scoped>
.audio-no-ready {
  opacity: 0.6;
  .play-icon {
    color: $--color-msg-prompt-danger;
  }
}
.play-icon {
  position: absolute;
  top: 9px;
  color: #fff;
  width: 20px;
  height: 20px;
  border-radius: $--border-radius-circle;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: $--font-size-small;
}
  .audio-download-faile {
    color: $--color-msg-prompt-danger;
  }
.audio-unread {
  position: absolute;
  right: -16px;
  top: 15px;
}
.audio-play {
  height: 36px;
  width: 160px;
  position: relative;
  &:hover {
    cursor: pointer;
  }
}
.audio-play-mine {
  .media-time {
    right: 16px;
    color: #fff;
  }

  .play-icon {
    left: 14px;
    background: rgba(255, 255, 255, 0.6);
  }

  .audio-box {
    right: 20px;
    transform: rotate(-90deg);
  }
  .strength-ready {
    color: #fff;
  } /*已链接或曾连接过的颜色及信号强弱*/
  .strength-no {
    color: #fff;
  } /*未链接的颜色*/
}
.audio-play-other {
  .media-time {
    left: 16px;
    color: lightslategrey;
  }
  .play-icon {
    right: 14px;
    background: lightgrey;
  }
  .audio-box {
    left: 26px;
  }
  .strength-ready {
    color: lightslategrey;
  } /*已链接或曾连接过的颜色及信号强弱*/
  .strength-no {
    color: lightslategrey;
  } /*未链接的颜色*/
}
.media-time {
  position: absolute;
  top: 11px;
  font-size: 10px;
}
// .strength-ready{ color: lightslategrey; }/*已链接或曾连接过的颜色及信号强弱*/
// .strength-no{ color: lightslategrey;}/*未链接的颜色*/
.voice-icon {
  width: 20px;
  height: 20px;
  display: inline-block;
  position: relative;
  margin: 0 auto;
  float: left;
}
.voice-icon > span {
  display: block;
  position: absolute;
  border-radius: $--border-radius-circle;
}
.voice-icon .voice-1 {
  width: 3px;
  height: 3px;
  left: 50%;
  transform: translateX(-50%);
  bottom: 1px;
  background: currentcolor;
}
.voice-icon .voice-2,
.voice-icon .voice-3,
.voice-icon .voice-4 {
  border: 2px solid;
  border-color: currentcolor transparent transparent;
}
.voice-icon .voice-2 {
  width: 6px;
  height: 6px;
  left: 7px;
  bottom: 3px;
}
.voice-icon .voice-3 {
  width: 20px;
  height: 20px;
  left: 0px;
  bottom: -6px;
}
.voice-icon .voice-4 {
  width: 28px;
  height: 28px;
  left: -4px;
  bottom: -9px;
}
.voice-icon > span:after {
  content: '';
  display: block;
  position: absolute;
}
/*demo样式*/
.audio-box {
  width: 32px;
  height: 32px;
  position: absolute;
  top: 2px;
  display: flex;
  align-items: center;
  transform: rotate(90deg);
}
.voice-icon {
  transform: scale(0.8);
}
*,
*::after,
*::before {
  box-sizing: border-box;
}
.strength-ready .voice-3,
.strength-ready .voice-4 {
  -webkit-animation: bouncedelay 1.4s infinite ease-in-out;
  animation: bouncedelay 1.4s infinite ease-in-out;
  /* Prevent first frame from flickering when animation starts */
  -webkit-animation-fill-mode: both;
  animation-fill-mode: both;
}

.strength-ready .voice-3 {
  -webkit-animation-delay: -0.32s;
  animation-delay: -0.32s;
}

.strength-ready .voice-4 {
  -webkit-animation-delay: -0.16s;
  animation-delay: -0.16s;
}

@-webkit-keyframes bouncedelay {
  0% {
    opacity: 0;
  }
  80% {
    opacity: 1;
  }
}

@keyframes bouncedelay {
  0% {
    opacity: 0;
  }
  80% {
    opacity: 1;
  }
}
</style>