<template>
  <div class="msg-type-group-notice" @dblclick="expendGroupNottice">
    <div class="type-group-notice">
      <div class="type-card-upper">
        <div class="type-notice-img" v-if="hasNoticeImg()">
          <img :src="getNoticeImg()||imgSrc" @error="imgError"/>
        </div>
        <div class="type-notice-content">
          <div class="contents content-title" v-if="getNoticeTitle()">{{ getNoticeTitle() }}</div>
          <div class="contents content-detail" v-html="getNoticeDetail()"></div>
        </div>
      </div>
      <div class="type-notice-label">{{$t('groups.groupNotice')}}</div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import { escapeEmoji } from '../Emoji/emoji.js'
import ImgMixins from '../Mixins/ImgMixins'
export default {
  mixins: [ImgMixins],
  props: {
    message: Object
  },
  data() {
    return {
      item : {},
      noticeContent: '',
      imgSrc: ''
    }
  },
  computed: {
    ...mapGetters([ 'user_account', 'user_imgPath'])
  },
  created () {
    console.log('in group-notice', this.message.messageObject.body);
    if (!this.isJSON(this.message.messageObject.body)) return;
    let body = JSON.parse(this.message.messageObject.body)
    this.noticeContent = body.content
  },
  methods: {
    isJSON(str) {
      try {
        if (typeof JSON.parse(str) == 'object') {
          return true;
        }
      } catch(e) {}
      return false
    },
    hasNoticeImg() {
      if (!this.isJSON(this.noticeContent)) return false;
      return JSON.parse(this.noticeContent).pictureArray && JSON.parse(this.noticeContent).pictureArray.length > 0
    },
    getSrcImg() {
      console.log(this.isJSON(this.noticeContent),  this.noticeContent)
      if (!this.isJSON(this.noticeContent)) return '';
      if (JSON.parse(this.noticeContent).pictureArray &&
          JSON.parse(this.noticeContent).pictureArray.length > 0
      ) {
        return JSON.parse(this.noticeContent).pictureArray[0].mediaUrl
      }
    },
    getNoticeTitle() {
      if (this.getBaseContent().indexOf('</title>')!==-1) {
        return this.getBaseContent().split('</title>')[0]
      }
      return ''
    },
    getNoticeDetail() {
      if (this.getBaseContent().indexOf('</title>')!==-1) {
        return escapeEmoji(this.getBaseContent().split('</title>')[1])
      } else {
        return escapeEmoji(this.getBaseContent())
      }
    },
    getBaseContent() {
      if (!this.isJSON(this.noticeContent)) {
        return this.noticeContent
      } else {
        return JSON.parse(this.noticeContent).announce
      }
    },
    getNoticeImg() {
      let img = JSON.parse(this.noticeContent).pictureArray[0];
      if (this.$Service.file.fileOperate({ filepath: img.mediaUrl, type: 0})) {
        this.imgSrc = `file://${img.mediaUrl}`
        return this.imgSrc
      } else { 
        this.getImgPath(img.mediaUrl).then(imgUrl => {
          console.log('imgUrl:::', imgUrl)
          if (this.$Service.file.fileOperate({ filepath: imgUrl, type: 0})) {
            this.imgSrc = `file://${imgUrl}`
            return this.imgSrc
          } else {
            this.downloadImg(img)
          }
        })
      }
    },
    downloadImg(img) {
      let downloadImageParam = {
        targetId: this.$route.query.id,
        url:  img.mediaUrl
      }
      console.log('downloadImageParam:::', downloadImageParam)
      this.$Service.file.downloadImage(downloadImageParam, resp => {
        console.log('downloadImage:::', resp)
          if (resp.code === 0) {
            console.log('encryptKey:::', img.enc_dec_key)
            if (!img.enc_dec_key) {
              this.imgSrc = `file://${this.user_imgPath}${resp.imgName}`
              return this.imgSrc
            }
            let cachePath = `${this.user_imgPath}${resp.imgName.substr(0, resp.imgName.lastIndexOf('/'))}/cache`
            let createFile = this.$Service.file.fileOperate({ filepath: cachePath, type: 1})
            console.log('createFile:::', createFile)
            if (createFile) {
              let destPath = `${cachePath}/${resp.imgName.substr(resp.imgName.lastIndexOf('/') + 1)}`
              console.log('destPath::::', destPath)
              this.decryptImg(img.enc_dec_key, resp.imgName, destPath).then(decryptResp => {
                console.log('decryptResp:::', decryptResp)
                if (decryptResp.result) {
                  this.imgSrc = `file://${destPath}`
                  return this.imgSrc
                } else { 
                  return undefined
                }
              }) 
            } else {
              return undefined
            }
          } else {
            return undefined
          }
      })
    },
    decryptImg(encryptKey, imgName, destPath) {
      return new Promise((resolve, reject) => {
      let decryptFileParam = {
        encryptkey: encryptKey,
        srcpath: this.user_imgPath + imgName,
        destpath: destPath
      }
      let decryptFileCb = decryptFileRes => {
        resolve(decryptFileRes)
      }
      this.$Service.file.decryptFile (decryptFileParam, decryptFileCb)
      })
    },
    imgError(e) {
	    e.target.src='';
    },
    expendGroupNottice(){
      this.$emit('openChatGroupNotice', {index: 1, view: 'notice', components:'ChatGroupNotice'});
    }
  }
};
</script>
<style lang="scss">
.msg-type-group-notice{
  padding: 3px;
  .type-group-notice {
    width: 290px;
    background: #fff;
    color: #000;
    border-radius: 16px;
    .type-card-upper {
      height: 90px;
      display: flex;
      align-items: center;
      margin: 0 10px;
      .type-notice-img {
        img {
          width: 60px;
          height: 60px;
          min-width: 60px;
        }
      }
      .type-notice-content {
        display: flex;
        flex-direction: column;
        margin-left: 10px;
        height: 83px;
        .content-title {
          flex: 1;
          display: flex;
          align-items: center;
          white-space: nowrap;
          text-overflow: ellipsis;
          overflow: hidden;
          max-width: 250px;
          letter-spacing: 1px;
          color: #323a7b;
        }
        .contents {
          flex: 1;
          overflow: hidden;
          // white-space: nowrap;
          // text-overflow: ellipsis;
          .v-text-emoji {
            width: 17px;
          }
        }
      }
    }
    .type-notice-label {
      border-top: 1px solid #ccc;
      height: 30px;
      display: flex;
      align-items: center;
      padding: 0 10px;
      font-size: 12px;
    }
  }
}
</style>
