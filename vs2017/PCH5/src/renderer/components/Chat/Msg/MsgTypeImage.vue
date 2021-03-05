<template>
  <div class="img-container" >
    <div class="type-image" :style="imgStyle" :class="[{'fail-img':isFail},{'image-opacity':user_waterMark}]">
      <!-- 缩略图显示 渐进式加载 -->
      <image-progress v-if="isShowThum" class="thum-img"
                     :src="thumImg"
                     :placeholder="placeholder"
                     :fallback = "placeholder? placeholder:failImg"
                     @click.native="reDownLoadImg"
                     @dblclick.native="showBig"
                     ref="imgs">
      </image-progress>
    </div>
    <div v-if="isThumProgress"  class="img-progress">
      <v-progress  :width=45 :percentage="progess" type="circle"></v-progress>
    </div>
    <i v-if="(state!==0&&state!==-3)||message.messageObject.msgType !== 5" class="icon" :class="message.messageObject.fromId === user_account.userId ?'msg-fail-self':'msg-fail-other'" @click="processFailed">&#xe63b;</i>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import imageProgress from '../Progressive-img/image.vue' 
import ImgMixins from '../Mixins/ImgMixins';
var gifyParse = require('gify-parse');
export default {
  data() {
    return {
      progess: 0,
      isBigProgress: false,
      isThumProgress: false,
      imgName: '', //图片保存名称
      destPath: '', //解密图片保存路径路径
      failImg: require('vrv-static/resources/images/message/fail_img.jpg'),
      placeholder: '', // 占位图
      extremeImg: '', // 极致缩略图
      thumImg: '', // 缩略图
      bigImg: '', // 大图
      isShowThum: false, //是否显示缩略图
      isShowbig: false, //是否显示大图，
      state: 0, // 消息状态 -1 发送上传失败  -2 下载
      isFail: false,
      isSendFail: false,
      // isClick: 0

    }
  },
  mixins: [ImgMixins],
  props: {
    message: Object,
    id: String,
    isMixMsg: Boolean,
    mixMsgId:  String,
    mixTargetId: String
  },
  mounted() {
    this.$Service.chat.getImgMsg({targetId: this.message.messageObject.targetId}, resp=> {
      console.log('getImgMsg::::::', resp)
    })
    this.loadImg() // 加载图片
  },
  methods: {
    async loadImg() {
     /**
      * message.flag 0 接收 1发送 2 直接加载
      * flag 0 时 需要下载
      * 下载图片
      * @param {String} targetId
      * @param {String} url
      * @param {Function} cb
      */
      if (this.message.flag === 0) { // flag 0 时 下载
      console.log('message::download', this.message)

      //判断图片下载状态
      this.getImgState()

        // 如果存在缩略图路径 而且路径真实存在 直接加载
        if (this.message.messageObject.thumbPath && this.$Service.file.fileOperate({ filepath: this.message.messageObject.thumbPath, type: 0})) {
          this.isShowThum = true;
          this.thumImg =  `file://${this.message.messageObject.thumbPath}`

        } else {
          this.getImgPath(this.message.messageObject.thumbUrl).then(imgUrl => {
            /**
             * 通过获取到的url 要判断图片是否被下载过
             * fileOperate 返回true 本地存在图片 false 本地不存在图片
             * 返回true 图片已下载 直接加载 false 下载图片
             */
          if ( this.$Service.file.fileOperate({ filepath: imgUrl, type: 0})) { //判断图片是否存在 存在直接加载
            [this.isShowThum, this.thumImg] = [true , `file://${imgUrl}`]
          } else {
              console.log('downloadImg::', this.message.messageObject.thumbUrl)
              this.isShowThum = true;
              /** pc携带极致缩略图 优先下载 */
              this.extremeImg = this.message.messageObject.thumBbinary
              if(this.extremeImg) this.placeholder = 'data:image/jpeg;base64,' + this.extremeImg
              this.downloadImg(this.message.messageObject.thumbUrl)
            }
          })
        }

      }

      /**
       * message.flag 1 发送图片
       */
      if (this.message.flag === 1) {
        console.log('message', JSON.stringify(this.message))
        if(this.$is.isOSX) { 
          let path = this.message.messageObject.mainPath
          if (!path.startsWith('/')) {
            this.message.messageObject.mainPath = '/'+ path
          }
        }
        this.message.flag = 0
        /**
          *thumbImageInfo 图片压缩后的信息(含宽、高、buffer)
          *message.thumbUrl 缩略图的保存路径
          *message.width 图片的宽
          *message.height 图片的高
          */
        
        this.thumImg = this.bigImg = this.message.messageObject.mainPath;
        // this.isShowThum = true;
        let msgType = this.thumImg.substr(this.thumImg.lastIndexOf('.') + 1)
        let isGif = msgType.match(/gif|GIF/g)
        let thumbImageInfo
        if (!isGif) {
           console.log('isGif',isGif);
          thumbImageInfo = this.$images.thumbImage(this.message.messageObject.mainPath, true)
          console.log('thumbImageInfo',thumbImageInfo);
          let thumlSave = `${this.user_imgPath}${this.message.messageObject.encryptKey}.jpeg`
          this.message.messageObject.thumBbinary = thumbImageInfo.thumBbinary
          if (!thumbImageInfo.originBuffer.length) { 
            this.message.messageObject.thumbPath = this.message.messageObject.mainPath;
          } else {
            this.message.messageObject.thumbPath = thumlSave;
            await this._writeThumbImg(this.message.messageObject.thumbPath, thumbImageInfo.originBuffer)
          }
        } else {
          let buffer = this.$fs.readFileSync(this.thumImg)
          thumbImageInfo = gifyParse.getInfo(buffer);
          console.log('thumbImageInfo', thumbImageInfo);
          this.message.messageObject.thumbPath = this.message.messageObject.mainPath;
        }

        // * 异常处理 类似于修改gif图后缀为普通jpg 导致获取宽高、 缓存失败
        if (!thumbImageInfo.width) {
          thumbImageInfo = await this._getErrorImgInfo(this.message.messageObject.thumbPath)
          console.log('thumbImageInfo>>>', thumbImageInfo)
        }
        this.message.messageObject.width = thumbImageInfo.width
        this.message.messageObject.height = thumbImageInfo.height
        console.log('width', this.message.messageObject.width)
        console.log('height', this.message.messageObject.height)
        this.isShowThum = true;
        // this.thumImg = this.bigImg = this.message.messageObject.mainPath;
        this.send_Img()
      }
      
      /**
       * flag 2  直接加载图片
       */
      if(this.message.flag === 2){
        [this.isShowThum, this.placeholder] = [true, '']
        this.thumImg = this.message.messageObject.thumbPath;
      }

    },

    /**
     * 根据messageType 来判断消息的状态
     * messageType 517 发送失败
     * messageType 261 上传失败
     */
    getImgState() {
      let msgType = this.message.messageObject.msgType
      if (msgType === 517 || msgType === 261) {
        this.state = -1;
      } 
    },

    // * 写入缩略图
    _writeThumbImg(path, buffer) {
      return new Promise((resolve, reject) => {
        this.$fs.writeFile(path, buffer, err => {
          if (err) {
            reject(err);
          }
          resolve(console.log('写入完成'))
        })
      })
    },

    // * 获取异常情况下图片的信息 类似于修改gif图后缀为普通jpg 导致获取宽高、 缓存失败
    _getErrorImgInfo(imgPath) {
      return new Promise((resolve) => {
        let image = new Image()
        image.src = imgPath
        image.onload = () => {
          let imgInfo = {
            width: image.width,
            height: image.height
          }
          resolve(imgInfo)
        }
      })
    },
    /**
     * 发送图片消息
     */
    send_Img() {
      /**
       * 发送失败的状态 发送前需要初始化
       */
      if(this.state !== 0) this.state = 0 // 防止点击多次发送 state -2 为消息发送失败
      this.isThumProgress = true;
      if(this.message.messageObject.msgType !== 5) this.message.messageObject.msgType = 5; //消息发送失败 重新发送需要修正type
      console.log('sendAppendixMessage:::', this.message.messageObject)
      // 一键发送图片
      this.$Service.chat.sendAppendixMessage(this.message.messageObject, resp=> {
        this.closeProgress() // 关闭所有进度
        console.log('sendImgRes::', resp)
        this.$Service.log(`sendImgRes:: ${resp.code}`)

        if (resp.code === 0) {
          let preMsgId = this.message.messageObject.msgId
          console.log('preMsgId', preMsgId, resp.msgId)
          this.$store.commit('UPDATE_MSGID', {id:this.id, preMsgId:preMsgId, msgId: resp.msgId, isFail:this.isSendFail, time: resp.time})
          this.$emit('hasRead', resp.msgId)
          let result= this.$isOpenMediaMsgPreivew()
          console.log('result', result)
          if (result && result.isOpen && this.message.messageObject.targetId === result.mediaMsgPreivewId) {
            console.log('image isOpen>>>>>')
            // this.$ipc.send('revokeImage', {type: 1})
            this.$ipc.send('handleSubWinMediaMsg', {winType: 'image' , operaType: 1} )
          }
        } else {
          this.state = -1 // state -2 为消息发送失败
          if (!this.isSendFail) {
            this.isSendFail = true;
          }
          /**
           * 如果发送失败且不再当前会话 需要修改会花列表状态
           */
          if (this.$route.query.id !== this.message.messageObject.targetId) {
            this.$store.dispatch('CHANGE_CHAT_LIST_STATE', {id: this.message.messageObject.targetId, type: 2} )
          }
        }
      }, progress => {
        this.progess = progress.process
      })
    },

  /**
    * imgUrl 图片下载地址
    * showImg true 下载缩略图 false 下载大图
    * downloadImage 下载图片
    * @param {string} targetId
    * @param {string} url
    * @param {Function} cb
    */
    downloadImg(imgUrl) {
   
      if (this.state !== 0) this.state = 0 // 防止图片下载失败 反复操作 state -3 下载失败
      this.isThumProgress = true;

      // let urls = `${this.isClick===0 ?'d://':''}${imgUrl}`
      // this.isClick ++
      let downloadImageParam = {
          targetId: this.message.messageObject.targetId,
          // url: urls,
          url:  imgUrl
      }
      console.log('downloadImageParam', downloadImageParam)

      let downloadImageProcess = process => { //图片下载进度
        this.progess = process.progess
      }

      this.$Service.file.downloadImage(downloadImageParam, resp => {
          this.$Service.log(`downloadImage -- code   ${resp.code}`)
          this.closeProgress() // 关闭进度显示
          // return;
          if (resp.code === 0) { // 图片下载成功
            this.imgName = resp.imgName // 图片文件名称

            /**
             * enc_dec_key 为空 图片不需要解密
             */
            if (!this.message.messageObject.encryptKey) {
              console.log('no encryptKey')
              if (this.isFail) this.isFail = false;
              if(this.state !==0) this.state = 0
              let thumbImg = `${this.user_imgPath}${this.imgName}`
              this.message.messageObject.thumbPath = thumbImg;
              this.thumImg = `file://${thumbImg}`
              return
            }

           /**
             * 解密文件夹路径 
             * 创建解密文件夹
             * fileOperate 1 创建文件夹
             * 根据解密文件夹路径 创建此文件夹
             */
            let cachePath = `${this.user_imgPath}${this.imgName.substr(0, this.imgName.lastIndexOf('/'))}/cache`
            let createFile = this.$Service.file.fileOperate({ filepath: cachePath + '/', type: 1})
            this.$Service.log(`isCreateFile? ${createFile}`)
            if (createFile) {
              // 图片解密后保存的路径
              this.destPath = `${cachePath}/${this.imgName.substr(this.imgName.lastIndexOf('/') + 1)}`
              this.$Service.log(`imgSavePath::  ${this.destPath}`)
              /** 解密图片 */
              this.decryptImg().then(decryptResp => {
                console.log('decryptResp', decryptResp)
                console.log('this.destPath', this.destPath)
                if (decryptResp.result) {
                  if (this.isFail) this.isFail = false;
                  [this.message.messageObject.thumbPath, this.thumImg] = [this.destPath, `file://${this.destPath}`]
                  if (this.state !== 0) this.state = 0;
                } else { 
                  this.thumImg  = this.extremeImg? 'data:image/jpeg;base64,' + this.extremeImg: (this.failImg, this.isFail=true);
                  this.state = -3 // 解密失败
                }
              }) 
            } else {
              this.$Service.log('created -- cache -- faile')
              this.state = -3 //state -3 创建缓存文件失败  需重新下载
              this.thumImg  = this.extremeImg? 'data:image/jpeg;base64,' + this.extremeImg: (this.failImg, this.isFail=true);
            }
          } else {  // 图片下载失败
            this.$Service.log(`imgdownLoad fail:: ${resp.code}`)
            this.state = -3 
            this.thumImg  = this.extremeImg? 'data:image/jpeg;base64,' + this.extremeImg: (this.failImg, this.isFail=true);
          }
      }, downloadImageProcess)
    },

    /**
     * 解密文件
     * encryptkey 解密密码
     * srcpath 图片路径
     * destpath 保存地址
     */
    decryptImg() {
      return new Promise((resolve, reject) => {
      let decryptFileParam = {
          encryptkey: this.message.messageObject.encryptKey,
          srcpath: this.user_imgPath + this.imgName,
          destpath: this.destPath
      }

      let decryptFileCb = decryptFileRes => {
        this.$Service.log(`imgDecryResult::  ${decryptFileRes.result}`)
        this.closeProgress() // 关闭进度显示
        resolve(decryptFileRes)
      }

      this.$Service.file.decryptFile (decryptFileParam, decryptFileCb)
      })
    },

    /** 关闭进度条 */
    closeProgress() {
      this.isThumProgress = false;
      this.progess = 0;
    },

    /** 显示大图 */
    showBig() {
      console.log('isMixMsg:::', this.isMixMsg)
      let imgPath = `vrv-static/plugins/imagepreivew/index.html?mode=normal&targetId=${this.message.messageObject.targetId}&msgId=${this.message.messageObject.msgId}`
      if (this.isMixMsg) {
        imgPath = `${imgPath}&mixTargetId=${this.mixTargetId}&mixMsgId=${this.mixMsgId}`
      }
      let winUrl = `${imgPath}&thumbImg=${this.thumImg}&isMixMsg=${this.isMixMsg}&hasImgSaveAs=${!this.chat_chatDicValue['isSavePicturesToAlbums'] || this.chat_chatDicValue['isSavePicturesToAlbums'] === '1'}`
      this.$ipc.send('new-window', { winUrl: winUrl, winType:'Imagepreivew',  winTitle:`${this.$t('chat.pictureViewer')}`, shapeType:'normal', targetId:this.message.messageObject.targetId}) 
      // if (!this.bigImg) { //防止多次点击
      //   if (this.message.messageObject.mainPath && this.$Service.file.fileOperate({ filepath: this.message.messageObject.mainPath, type: 0})) {
      //     this.bigImg = this.message.messageObject.mainPath
      //     this.$ipc.send('new-window', {winUrl:`${imgPath}&mediaUrl=${this.bigImg}`, winType:'Imagepreivew', winTitle:`${this.$t('chat.pictureViewer')}`, shapeType:'normal'})
      //   } else {
      //     // 获取大图的完整路径
      //     this.getImgPath(this.message.messageObject.mainUrl).then(imgUrl => {
      //       let fileOperateParam = {
      //           filepath: imgUrl, //路径
      //           type: 0 // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
      //       }
      //       /*
      //       * 判断大图是否存在
      //       * 不存在 开启新窗口时附带缩略图路径和大图路径
      //       * 若存在 直接带大图路径
      //       */ 
      //       let winUrl ;
      //       if (!this.$Service.file.fileOperate(fileOperateParam)) {
      //         winUrl = `${imgPath}&thumbImg=${this.thumImg}&mediaUrl=${this.message.messageObject.mainUrl}&user_imgPath=${this.user_imgPath}&destPath=${imgUrl}&enc_dec_key=${this.message.messageObject.encryptKey}`
      //       } else {
      //         this.bigImg = imgUrl;
      //         winUrl = `${imgPath}&mediaUrl=${this.bigImg}`
      //       }
      //       this.$ipc.send('new-window', { winUrl: winUrl, winType:'Imagepreivew',  winTitle:`${this.$t('chat.pictureViewer')}`, shapeType:'normal'}) 
      //     })  
      //   }
      // } else {
      //   this.$ipc.send('new-window', {winUrl:`${imgPath}&mediaUrl=${this.bigImg}`, winType:'Imagepreivew', winTitle:`${this.$t('chat.pictureViewer')}`, shapeType:'normal'})
      // }
    },

    /** 重新下载图片 */
    reDownLoadImg() {
      if (this.state !== -3) return 
      this.processFailed()
    },

    processFailed() {
      switch(this.state) {
        case -1: 
          {
            this.send_Img()
            break
          }
        case -3:
          {
            this.downloadImg(this.message.messageObject.thumbUrl, true)
            break
          }
        case -4:
          {
            this.decryptImg()
            break
          }
      }
    }
  },
  computed: {
    ...mapGetters(['user_imgPath','user_waterMark', 'chat_chatDicValue']),
    imgStyle() {
      console.log('im style')
      /**
       * 根据图片消息的宽度来确定显示图片的宽度
       * 根据图片消息的高度来确定显示图片的高度
       */
      /** 正常图片宽高计算 */
      let [imgWidth, imgHeight, containerWidth, containerHeight] = [this.message.messageObject.width, this.message.messageObject.height, 260, 280]
      let width, height;
      if(imgWidth && imgHeight){
        if (imgWidth < containerWidth && imgHeight < containerHeight) {  
            width = imgWidth;
            height =  imgHeight;
        } else { //原图片宽高比例 大于 图片框宽高比例,则以框的宽为标准缩放，反之以框的高为标准缩放  
          if (containerWidth / containerHeight  <= imgWidth / imgHeight) { //原图片宽高比例 大于 图片框宽高比例  
              width = containerWidth; //以框的宽度为标准  
              height = containerWidth * (imgHeight/imgWidth);
          }else{//原图片宽高比例 小于 图片框宽高比例  
            width = containerHeight * (imgWidth / imgHeight);
            height = containerHeight;  //以框的高度为标准  
          }  
        }
      }else{ // 当消息中不存在宽高的时候
        width = containerWidth;
        height = containerHeight; 
      }
        return { width: width  + 'px', height: height + 'px' };
      }
  },
  components: {
    imageProgress
  }
}
</script>
<style  lang="scss" scoped>
.img-container {
  width: fit-content;
  // height: fit-content;
  @mixin status {
    width: 20px;
    align-self: center;
    color:$--color-msg-prompt-danger;
    display: flex;
    align-items: center;
    position: absolute;
  }

  min-width: 40px;
  position: relative;
  background: transparent;
  border: none;
  align-self: center;
    .img-progress {
      margin:auto;
      position: absolute;
      left:0;
      right:0;
      top:0;
      bottom:0;
      width: 60px;
      height: 60px;
      display: flex;
      align-items: center;
      justify-content: center;
      // color: aliceblue;
    }
    .image-opacity{
      opacity: 0.9;
    }
    .type-image {
      position: relative;
      // width: 20px;
      // height: 20px;
      // overflow: hidden;
      // .thum-img {
      //   width: fit-content;
      //   // height: fit-content;
      // }
      &.fail-img {
      width: 180px!important;
      height: 120px!important;
      -webkit-user-drag: none;
        &:hover {
          cursor: pointer;
        }
        &:hover .thum-img {
        box-shadow: $--box-shadow-rd;
        }
      }
      // img {
      //   width: 100%;
      //   height: 100%;
      // }

    }
    .msg-fail-self {
      @include status;
      left: -22px;
    }
    .msg-fail-other {
      @include status;
      right: -25px;
    }
  }

</style>
