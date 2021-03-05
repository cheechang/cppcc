<template>
    <div >
      <div class="video-play"  :style="computedVideoType">
        <video style="width:100%;height:100%" ref="myVideo"  :poster="imgUrl" ></video>
        <div  class="video-btn"><i class="icon" @click="open()">&#xe8a3;</i></div>
        <!-- <v-button v-if="isLoading" :ripple="false"  class="loading is-loading is-large"></v-button> -->
      </div>
    </div>
</template>
<script>
import { mapGetters } from 'vuex'
import ImgMixins from '../Mixins/ImgMixins';
import FileMixin from '../Mixins/FileMixins';
export default {
  data() {
    return {
      decryptFiles: '',
      isClick: false,
      state: 0,
      imgUrl: '',
      destpath: '',
      isLoading: false,
      isDecrypt: false
    }
  },
  mixins: [ImgMixins, FileMixin],
  watch: {
    'message.messageObject' (videoMsg) {
      if (!videoMsg.mute) return
      this.open(true)
    }
  },
  mounted() {
    console.log('video::::::::', this.message)
     this.getImgPath(this.message.messageObject.preImgPath).then(imgUrl => {
        if (this.$Service.file.fileOperate({ filepath: imgUrl, type: 0})){ // 此时图片存在 
          this.imgUrl = imgUrl
        } else {  // 此时图片不存在 需要下载
          this.downloadImgs(this.message.messageObject.targetId, this.message.messageObject.preImgPath).then(resp => {
            if (resp.code === 0) { // 图片下载成功
              this.imgName = resp.imgName // 图片文件名称
              /**
               * 解密文件夹路径 
               * 创建解密文件夹
               * fileOperate 1 创建文件夹
               * 根据解密文件夹路径 创建此文件夹
               */
              let cachePath = `${this.user_imgPath}${this.imgName.substr(0, this.imgName.lastIndexOf('/'))}/cache`
              let isCreateVideoCache = this.$Service.file.fileOperate({ filepath: cachePath + '/', type: 1})
              this.$Service.log(`isCreateVideoCache:::    ${isCreateVideoCache}`)
              if (isCreateVideoCache) {
                this.destPath = `${cachePath}/${this.imgName.substr(this.imgName.lastIndexOf('/') + 1)}`
                this.$Service.log(`VideoFileSavePath:::    ${this.destPath}`)
                this.decryptImg()
              } else {
                this.$Service.log(`video preImg created -- cache -- faile:::`)
              }
            } else {
               this.$Service.log(`video preImg downfaile:::     ${resp.code}`)
            }
          })
        }
     })
    // 获取本地路径
    this.getFileInfo(this.user_videoPath, this.message.messageObject.vedioFileName)
  },
  computed: {
    ...mapGetters(['user_videoPath', 'user_account', 'user_imgPath']),
    computedVideoType() {
      let width, height;
      let [imgWidth, imgHeight, containerWidth, containerHeight] = [this.message.messageObject.vedioWideth, this.message.messageObject.vedioHight, 140, 248]
      if (containerWidth / containerHeight  <= imgWidth / imgHeight) { //原图片宽高比例 大于 图片框宽高比例  
        width = containerHeight;
        height = containerWidth;
      } else {//原图片宽高比例 小于 图片框宽高比例  
        width = containerWidth;
        height = containerHeight;
      }
      return { width: width  + 'px', height: height + 'px' };
    }
  },
  methods: {
    open(isMute = false) {
      /** isClick 防止重复点击 导致的重复下载或者解压 */
      if (this.message.messageObject.activeType) {
        this.$emit('audioHasClick')
      }
      this.updateVideoStatus()
      let fileName = this.message.messageObject.vedioFileName.replace(/\//ig, '\\')
      const videoPath = `vrv-static/plugins/videopreivew/index.html?&preImage=${this.imgUrl}&isMute=${isMute}&fileName=${fileName}`
      let winUrl
      if (!this.isDecrypt) {
        this.decryptFiles = this.createCachePath(this.user_videoPath, this.message.messageObject.vedioFileName)
        if (!this.$Service.file.fileOperate({filepath: this.decryptFiles,  type: 0})) {
         
          if (!this.isExistFile) {
            winUrl = `${videoPath}&videoStatus=download&mediaUrl=${this.message.messageObject.vedioFileName}&targetId=${this.message.messageObject.targetId}&user_videoPath=${this.user_videoPath}&enc_dec_key=${this.message.messageObject.encryptKey}&fromId=${this.message.messageObject.fromId}&msgId=${this.message.messageObject.msgId}&encryPath=${this.encryptFileSavePath}`
          } else {
            winUrl = `${videoPath}&videoStatus=decrypt&mediaUrl=${this.message.messageObject.vedioFileName}&targetId=${this.message.messageObject.targetId}&user_videoPath=${this.user_videoPath}&enc_dec_key=${this.message.messageObject.encryptKey}&fromId=${this.message.messageObject.fromId}&msgId=${this.message.messageObject.msgId}&encryPath=${this.encryptFileSavePath}`
          }
        } else {
          this.isDecrypt = true;
          winUrl = `${videoPath}&videoStatus=autoplay&videoPath=${this.decryptFiles}`
        }
      } else {
        winUrl = `${videoPath}&videoStatus=autoplay&videoPath=${this.decryptFiles}`
      }
      // this.$ipc.send('new-window', { winUrl: winUrl, winType:'MicroVideo',  winTitle:'视频预览预览', shapeType:'normal'}) 
      this.$ipc.send('new-window', { winUrl: winUrl, winType:'MicroVideo',  winTitle:this.$t('chat.videoPreview'), shapeType:'normal', targetId:this.message.messageObject.targetId }) 
      if (this.message.messageObject.mute) {
        this.$delete(this.message.messageObject, 'mute')
      } 
    },
    decryptImg() {

      let decryptFileParam = {
          encryptkey: this.message.messageObject.encryptKey,
          srcpath: this.user_imgPath + this.imgName,
          destpath: this.destPath
      }
      console.log('decryptFileParam:::', JSON.stringify(decryptFileParam))
      let decryptFileCb = decryptFileRes => {
        console.log('解密结果', decryptFileRes.result)
        this.imgUrl = this.destPath;
      }

      this.$Service.file.decryptFile (decryptFileParam, decryptFileCb)
    },
    /**
     * 微视频下载完成后，更新文件状态避免重新下载
     */
    updateVideoStatus() {
      // 微视频解密文件是否存在
      this.getFileInfo(this.user_videoPath, this.message.messageObject.vedioFileName)
      // 微视频解密后的文件是否存在
      let path = `${this.user_videoPath}cache/` + this.message.messageObject.vedioFileName.replace(/\//g, '_') // cache路径
      let hasVideoDownloaded = this.$Service.file.fileOperate({
        filepath: path,
        type: 0
      })
      if (!hasVideoDownloaded) { // 未下载过，或者文件被删了
        this.isDecrypt = false
      } else { // 已下载过
        this.isDecrypt = true
        this.decryptFiles = path
      }
    }
  },
  props: {
    message: Object
  }
}
</script>
<style lang="scss" scoped>
.video-play{
  position: relative;
  border-radius: $--border-radius-msg;
  overflow: hidden;
}
.loading{
  position: absolute;
  left: 50%;
  top: 50%;
  margin-left: -18px;
  margin-top: -27px;
  background: transparent;
}
.video-btn{   
  position: absolute;
    left: 0px;
    top: 0px;
    width: 100%;
    height: 100%;
  .icon{
    width: 60px;
    height: 60px;
    position: absolute;
    left: 50%;
    top: 50%;
    margin-left: -30px;
    margin-top: -30px;
    font-size: 60px;
    color: rgba(255, 255, 255, 0.8);
  }
}
</style>
