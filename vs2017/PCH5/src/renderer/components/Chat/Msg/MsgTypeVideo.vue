<template>
  <div class="type-tip-msg">
    <span class="tip-body">
      <i class="icon icon-tip-msg">&#xe7fb;</i>{{videoBodyTip}}</span>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import MsgTypeFile from './MsgTypeFile'
import FileMixin from '../Mixins/FileMixins'
export default {
  props: {
    message: Object,
    id: String
  },
  data() {
    return {
      videoBody: {}
    }
  },
  mixins: [FileMixin],
  created() {
    this.videoBody = JSON.parse(this.message.messageObject.body)
  },
  computed: {
    videoClass() {
      return this.message.messageObject.fromId === this.user_account.userId ? 'video-play-mine' : 'video-play-other'
    },
    videoBodyTip() {
      
      if (this.videoBody.VideoType === '7') {
        let msgVideo = this.message.messageObject
        if (msgVideo.msgType === 15) {

          if (this.videoBody.VideoStatus === 'cancel' || this.videoBody.VideoStatus === 'reject') {
            // return this.$t('chat.fileTransCan')
          } 
        } else {
          if (this.videoBody.VideoStatus === 'cancel') {
            // return this.$t('chat.fileTransTimeOut')
          }
        }
      } else if (this.videoBody.VideoType === '1'||this.videoBody.VideoType === '2'||this.videoBody.VideoType === '9') {
        let tipStr;
        let msgVideo = this.message.messageObject
        if (msgVideo.msgType === 14||msgVideo.msgType === 15) {
          if(this.videoBody.msgModel){
            switch (this.videoBody.msgModel) {
              case "1":  //对方超时
                tipStr = this.$t('chat.notResponse')
                break;
              case "2":  //已取消
                tipStr = this.$t('chat.cancelled')
                break;
              case "3":  //已拒绝
                tipStr = this.$t('chat.beRefused')
                break;
              case "4":  //通话时长
                tipStr = `${this.$t('chat.callDuration')} ${this.timeToFormat(this.videoBody.msgInfo/1000)}`;
                break;
              case "6":  //其他设备处理
                tipStr = this.$t('chat.proccessedAtYourPhone');
                break;
              default:
                break;
            }
          }
          else{
            if (this.videoBody.VideoStatus === 'cancel') {
              tipStr = this.$t('chat.cancelled')
            }
            else if (this.videoBody.VideoStatus === 'reject') {
              tipStr = this.$t('chat.rejected')
            } 
            else if (this.videoBody.VideoStatus === 'call'|| this.videoBody.VideoStatus === 'remoteCall') {
             tipStr = this.$t('chat.request')
            }
          }
        }
        switch (this.videoBody.VideoType) {
          case '1':
            return `${this.$t('chat.audioCall')} ${tipStr}`
          case '9':
            return `${this.$t('chat.remoteAssistance')} ${tipStr}`
          default:
            return `${this.$t('chat.videoCall')} ${tipStr}`
        }
      } else {
        return this.$t('chat.video');
      } 
    },
    ...mapGetters(['user_audioPath', 'user_account'])
  },
  components: {
    MsgTypeFile
  }
}
</script>