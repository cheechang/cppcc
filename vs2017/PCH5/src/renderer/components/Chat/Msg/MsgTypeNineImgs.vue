<template>
  <div class="nine-imgs-box">
    <div class="grid" :style="cumputedLength">
    <!-- <div v-for="(img, index) in nineImg" :key= index @click="reloadImage(img, index)"> -->
    <div v-for="(img, index) in nineImg" :key= index >
      <img v-if="img.isComplete" :src="img.thumbPath" @click="viewBigImg(index, $event)"/>
    </div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import ImgMixins from '../Mixins/ImgMixins';
export default {
  data() {
    return {
      nineImg: Array,
      successImg : []
    }
  },
  props: {
    message: Object,
    isMixMsg: Boolean,
    mixMsgId:  String,
    mixTargetId: String
  },
  mixins: [ImgMixins],
  mounted() {
    this.nineImg = this.message.messageObject.nine
    this.nineImg.forEach(element => {
        this.getImgPath(element.thumbUrl).then(imgUrl => {
        if (this.$Service.file.fileOperate({ filepath: imgUrl, type: 0})){ // 此时图片存在 
           this.$set(element, 'isComplete', true)
           element.thumbPath = imgUrl
        } else {  // 此时图片不存在 需要下载
          this.downloadImgs(this.message.messageObject.targetId, element.thumbUrl).then(resp => {
            if (resp.code === 0) { // 图片下载成功
              this.imgName = resp.imgName // 图片文件名称
              /**
               * 解密文件夹路径 
               * 创建解密文件夹
               * fileOperate 1 创建文件夹
               * 根据解密文件夹路径 创建此文件夹
               */
              let cachePath = `${this.user_imgPath}${this.imgName.substr(0, this.imgName.lastIndexOf('/'))}/cache`
              let createFile = this.$Service.file.fileOperate({ filepath: cachePath + '/', type: 1})
              // this.$log.debug('isCreateFile?', createFile)
              if (createFile) {
                this.destPath = `${cachePath}/${this.imgName.substr(this.imgName.lastIndexOf('/') + 1)}`
                 this.decryptImgs(this.imgName, element.encryptKey, this.destPath).then(resp => {
                  if (resp.result) {
                      console.log('保存路径::', this.destPath)
                      this.$set(element, 'isComplete', true)
                      element.thumbPath = resp.destPath
                  }
                 })
              } else {
                // this.$log.debug('created -- cache -- faile')
                // this.state = -3 //state -3 创建缓存文件失败  需重新下载
              }
            } else {
              // this.$log.debug('下载失败', resp.code)
            }
          })
        }
     })
    });
  },
  methods: {
    viewBigImg(index, e) {
      let mediaUrl = this.nineImg[index].mediaUrl
      let image_static = 'vrv-static/';
      // const imgPath = `${image_static}/plugins/imagepreivew/index.html?mode=muti&thumbImg=${e.target.currentSrc}&index=${index}&msgId=${this.message.messageObject.msgId}&targetId=${this.message.messageObject.targetId}&isMixMsg=${this.isMixMsg}`
      let imgPath = `${image_static}/plugins/imagepreivew/index.html?mode=muti&thumbImg=${e.target.currentSrc}&index=${index}&msgId=${this.message.messageObject.msgId}&targetId=${this.$route.query.id}&isMixMsg=${this.isMixMsg}&hasImgSaveAs=${!this.chat_chatDicValue['isSavePicturesToAlbums'] ||this.chat_chatDicValue['isSavePicturesToAlbums'] === '1'}`
      if (this.isMixMsg) {
        imgPath = `${imgPath}&mixTargetId=${this.mixTargetId}&mixMsgId=${this.mixMsgId}`
      }
     this.$ipc.send('new-window', {
        winUrl:`${imgPath}`, 
        winType:'Imagepreivew', 
        // winTitle:'图片预览',
        winTitle:`${this.$t('chat.pictureViewer')}`,
        shapeType:'normal',
        targetId:this.message.messageObject.targetId
      })
    },
    // reloadImage(img, index) {
    //   console.log('reloadImage index::::', index)
    //   if (img.isComplete) {
    //     return
    //   } 
    // }
  },
  computed: {
    ...mapGetters(['user_imgPath', 'chat_chatDicValue']),
    cumputedLength() {
      if (this.nineImg.length) {
        let picLength = this.nineImg.length;
        let columns = picLength > 4 ? '70px 70px 70px' : '70px 70px'
        let rows = picLength > 6 ? '70px 70px 70px' :  picLength > 2? '70px 70px': '70px'
        return {
          'grid-template-columns': columns,
          'grid-template-rows': rows
        }
      }

    }
  },
  components: {
  }
}
</script>
<style lang="scss" scoped>
.grid{
  display: grid;
  grid-gap: 3px;
  padding: 8px;
}
.grid > div {
  background: grey;
  /*大家不要被下面的代码迷惑，只是为了好看，哈哈*/
  display: flex;
  color: #fff;
  font-size: 150%;
  justify-content: center;
  align-items: center;
  overflow: hidden;
  img{
    width:100%;
    height: 100%;
    -webkit-user-drag: none;
  }
}
</style>
