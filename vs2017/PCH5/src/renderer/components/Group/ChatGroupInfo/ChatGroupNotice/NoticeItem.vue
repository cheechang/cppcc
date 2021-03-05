<template>
  <div class="notice-item">
    <!-- <div class="notice-title">{{ getNoticeTitle() }}</div> -->
    <div class="notice-content">
      <!-- <div class="notice-img" v-if="hasImage(item.content)">
        <img :style="{width: JSON.parse(item.content).pictureArray[0].width+'px', height: JSON.parse(item.content).pictureArray[0].height+'px'}"  :src="getNoticeImg()||imgSrc" @error="imgError"/>
      </div> -->
      <div class="notice-txt">
        <!-- <span v-html="getNoticeContentSubstr()"></span> -->
        <span>{{noFilterContent()}}</span>
        <span class="txt-collapse" v-if="!isFullExpend&&noFilterContent().length>105"></span>
      </div>
    </div>
    <p v-if="noFilterContent().length>105" class="notice-content-expend" @click="isExpendContent">{{ isFullExpend?`${$t('groups.seeLess')}`:`${$t('groups.seeMore')}` }}</p>
    <div class="notice-info">
      <div class="info-left" :style="{visibility: hasPermission?'visible':'hidden'}">
        <p v-for="(action, index) in actionType" :key="index" @click="editOrDelete(index)">{{action}}</p>
      </div>
      <!-- <div class="info-right">{{publish+item.name}}</div> -->
    </div>
  </div>
</template>
<script>
import ImgMixins from '../../../Chat/Mixins/ImgMixins'
import { escapeEmoji } from '../../../Chat/Emoji/emoji.js'
import { mapGetters } from 'vuex'
export default {
  mixins: [ImgMixins],
  props: {
    id: String,
    item: Object,
    hasPermission: false
  },
  data() {
    return {
      publish:  this.$t('groups.publishedOn') ,
      actionType: [`${this.$t('groups.edit')}`],
      isFullExpend: false,
      imgSrc: ''
    }
  },
  computed: {
    ...mapGetters(['user_imgPath'])
  },
  created() {
    if (this.getNoticeContent().length > 105) {
      this.isFullExpend = false
    } else {
      this.isFullExpend = true
    }
  },
  methods: {
    getNoticeImg() {
      let img = JSON.parse(this.item.content).pictureArray[0];
      if (this.$Service.file.fileOperate({ filepath: img.mediaUrl, type: 0})) {
        this.imgSrc = img.mediaUrl
        return `file://${this.imgSrc}`
      } else { 
        this.getImgPath(img.mediaUrl).then(imgUrl => {
          console.log('imgUrl:::', imgUrl)
          if (this.$Service.file.fileOperate({ filepath: imgUrl, type: 0})) {
            this.imgSrc = imgUrl
            return `file://${this.imgSrc}`
          } else {
            this.downloadImg(img)
          }
        })
      }
    },
    // getNoticeTitle() {
    //   if (this.noFilterContent().indexOf('</title>')>0) {
    //     return this.noFilterContent().split('</title>')[0]
    //   }
    //   return ''
    // },
    getNoticeContent() {
      if (this.noFilterContent().indexOf('</title>')>0) {
        return this.noFilterContent().split('</title>')[1]
      } else {
        return this.noFilterContent()
      }
    },
    getNoticeContentSubstr() {
      if (!this.isFullExpend) {
        return escapeEmoji(this.getNoticeContent().substr(0, 105))
      } else {
        return escapeEmoji(this.getNoticeContent())
      }
    },
    noFilterContent() {
      // if (this.isJSON(this.item.content)) {
      //   return JSON.parse(this.item.content).announce
      // }
      console.log(this.item)
      return this.item.announce;
    },
    isExpendContent() {
      this.isFullExpend = !this.isFullExpend;
    },
    editOrDelete(index) {
      let action = {
        0: () => this.editNotice(),
        1: () => this.deleteNotice()
      }
      action[index].call(this)
    },
    editNotice() {
      this.$emit('edit-notice', this.item, this.imgSrc)
    },
    deleteNotice() {
      this.$emit('delete-notice', this.item)
    },
    downloadImg(img) {
      let downloadImageParam = {
        targetId: this.id,
        url:  img.mediaUrl
      }
      console.log('downloadImageParam:::', downloadImageParam)
      this.$Service.file.downloadImage(downloadImageParam, resp => {
        console.log('downloadImage:::', resp)
          if (resp.code === 0) {
            console.log('encryptKey:::', img.enc_dec_key)
            if (!img.enc_dec_key) {
              this.imgSrc = this.user_imgPath+resp.imgName
              return `file://${this.imgSrc}`
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
                  this.imgSrc = destPath
                  return `file://${this.imgSrc}`
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
    isJSON(str) {
      try {
        if (typeof JSON.parse(str) == 'object') {
          return true;
        }
      } catch(e) {
      }
      return false
    },
    hasImage(str){
      if(this.isJSON(str) && JSON.parse(str).hasOwnProperty('pictureArray') && JSON.parse(str).pictureArray.length > 0){
        return true;
      }
      return false;
    }
  }
}
</script>
<style lang="scss">
.notice-item {
  margin: 10px 0;
  background: #fff;
  padding: 10px;
  border-radius: 3px;
  box-shadow: 0 0 10px 0 rgba(101, 111, 122, 0.5);
  user-select: text;
  &:hover {
    .info-left {
      opacity: 1 !important;
      transition: .6s
    }
  }
  .notice-content-expend {
    text-align: right;
    font-size: 14px;
    margin: 10px 0;
    color: #323a7b;
    cursor: pointer;
  }
  .notice-content {
    display: flex;
    margin: 10px 0 20px;
    .notice-img {
      margin-right: 20px;
      img {
        max-width: 160px;
        max-height: 120px;
      }
      img[src=""],img:not([src]) {
        display: none !important;
      }
    }
    .notice-txt {
      font-size: 14px;
      word-break: break-all;
      img {
        width: 20px;
      }
      .txt-collapse {
        &::after {
          display: inline;
          content: "......";
        }
      }
    }
  }
  .notice-info {
    display: flex;
    font-size: 12px;
    align-items: center;
    justify-content: space-between;
    .info-left {
      display: flex;
      opacity: 0;
      transition: .6s;
      p {
        cursor: pointer;
        margin-right: 8px;
      }
    }
    .info-right {
      
    }
  }
}
</style>
