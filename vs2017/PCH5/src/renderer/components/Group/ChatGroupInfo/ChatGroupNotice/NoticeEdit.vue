<template>
  <div class="notice-edit">
    <!-- <div class="edit-img">
      <img :src="selectedImg"/>
    </div> -->
    <div class="edit-content">
      <!-- <div class="edit-title">
        <v-input class="title-input" type="textarea" v-model="noticeTitle" :placeholder="$t('groups.title')" :isBorder="false" :minlength="4" :maxlength="40"></v-input>
      </div> -->
      <!-- <div class="edit-action-type">
        <transition name="slide-down">
          <Emoji class="v-emoji" v-if="isShowEmoji" v-click-outside="onClickOutside" :isHideDynamic="true" :isEncryptMsg="false" @select="selectEmoji"></Emoji>
        </transition>
        <div class="action-item" v-for="(actionItem, index) in actionsType" :key="index" @click.passive.stop="handleTypeAction(index)">
          <i class="icon type-icon" v-html="actionItem.icon"></i>
          <P class="type-name">{{ actionItem.name }}</P>
          <input v-if="index==1" type="file" id="addImg" @change="uploadImg" accept="image/gif,image/jpeg,image/jpg,image/png,image/svg"/>
        </div>
      </div> -->
      <div class="edit-txt">
        <div class="edit-textarea" id="editable" ref="editArea" contenteditable="true" @input="limitInput"></div>
        <v-button :class="`publish-btn theme-bgc_font`" type="is-primary" @click="handleGroupNotice">{{$t('groups.publishNotice')}}</v-button>
        <!-- <v-input ref="editArea" class="txt-input" type="textarea" v-model="noticeContent" :isBorder="false" :maxlength="1000"></v-input> -->
        <!-- <div class="edit-textarea" ref="editArea" contenteditable="true" @keydown="keyChange" @input="editInput"> -->
      </div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import vClickOutside from '../../../Chat/v-click-outside/index.js'
import { insertNode } from '../../../Chat/At/at.js'
import { removeHtml } from '../../../Chat/Emoji/emoji.js'
import { getDateDiff } from '../../../../../comm/time.js'
import { encryptionPassword } from '../../../../../comm/util';
export default {
  props: {
    id: String,
    item: Object,
    noticeImg: String
  },
  data() {
    return {
      actionsType: [
        { icon: '&#xe70b;', name: this.$t('groups.emoji') },
        // { icon: '&#xe64b;', name: this.$t('groups.image') }
      ],
      isShowEmoji: false,
      noticeContent: '',
      noticeTitle: '',
      selectedImg: '',
      imgInfo: {}
    }
  },
  computed: {
    ...mapGetters(['user_account', 'chat_objectInfo'])
  },
  directives: {
    clickOutside: vClickOutside.directive
  },
  components: {
    Emoji: resolve => require(['../../../Chat/Emoji/index.vue'], resolve)
  },
  mounted() {
    if (!this.item||!this.item.content) return;
    if (this.isJSON(this.item.content)) {
      let announce = JSON.parse(this.item.content).announce;
      let pictureArray = JSON.parse(this.item.content).pictureArray;
      if ((announce).indexOf('</title>')>0) {
        this.$refs.editArea.innerHTML = announce.split('</title>')[1];
        this.noticeTitle = announce.split('</title>')[0]
      } else {
        this.$refs.editArea.innerHTML = announce;
      }
      if (pictureArray&&pictureArray.length>0) {
        this.selectedImg = this.noticeImg || pictureArray[0].mediaUrl;
        this.imgInfo = {
          enc_dec_key: '',
          fileName: pictureArray[0].fileName,
          thumbUrl: '',
          mediaUrl: pictureArray[0].mediaUrl,
          width: pictureArray[0].width,
          height: pictureArray[0].height
        }
      }
    } else {
      if ((this.item.content).indexOf('</title>')>0) {
        this.$refs.editArea.innerHTML = this.item.content.split('</title>')[1];
        this.noticeTitle = this.item.content.split('</title>')[0]
      } else {
        this.$refs.editArea.innerHTML = this.item.content;
      }
    }
  },
  methods: {
    isJSON(str) {
      try {
        if (typeof JSON.parse(str) == 'object') {
          return true;
        }
      } catch(e) {
      }
      return false
    },
    handleTypeAction(index) {
      if (index !== 0) {
        document.getElementById("addImg").click();
      } else {
        this.isShowEmoji = !this.isShowEmoji;
      }
    },
    uploadImg(event) {
      let reader = new FileReader();
      reader.readAsDataURL(event.target.files[0]);
      reader.onload = e => {
        let img = new Image();
        img.src = e.target.result;
        img.onload = img => {
          console.log(img.path[0].width, img.path[0].height)
          this.imgInfo = {
            enc_dec_key: '',
            fileName: event.target.files[0].name,
            thumbUrl: '',
            mediaUrl: event.target.files[0].path,
            width: img.path[0].width,
            height: img.path[0].height
          }
        }
      }
      this.selectedImg = event.target.files[0].path;
    },
    onClickOutside(event) {
      if (this.isShowEmoji) this.isShowEmoji=false
    },
    selectEmoji(emoji) {
      this.isShowEmoji = false
      console.log('emoji::::', emoji)
      if (emoji) {
        // 如果传过来emoji 则需要构造表情
        let emojis = require('vrv-static/resources/images/emoji/text_emoji/' + emoji.src + '.png')
        this.$refs.editArea.focus()
        var source = '<img class="v-text-emoji" type="emoji" alt="' +  emoji.alt + '" src="' + emojis + '">'
        insertNode(this.$refs.editArea, source)
      }
    },
    limitInput() {
      // let el = this.$refs.editArea;
      // let textLength = el.innerText.length
      // let limitLength = 50
      // if (textLength > limitLength) {
        // el.innerHTML = el.innerHTML.substring(0, limitLength)
        // let range = document.createRange();
        // let selection = window.getSelection();
        // range.setStart(el.childNodes[0], limitLength);
        // range.collapse(true);
        // selection.removeAllRanges();
        // selection.addRange(range);
        // el.focus();
      // }
    },
    handleGroupNotice() {
      console.log(this.$refs.editArea.innerHTML)
      let data = removeHtml(this.$refs.editArea, this.$refs.editArea.innerHTML)
      console.log('data', data)
      console.log('data.content', data.content)
      if(!this.checkPulbishRequired(data)) return
      if(!this.selectedImg) {
        this.publishNotice(data)
      } else {
        this.uploadeImg(this.selectedImg).then(() => {
          this.publishNotice(data)
        })
      }
    },
    publishNotice(data) {
      let content = data.content
        // announce: this.noticeTitle + '</title>' + data.content
      
      console.log(this.selectedImg, content)
      if (this.selectedImg) {
        content.pictureArray = [this.imgInfo];
      }
      let GroupAnnouncementInfo = {
        groupID: this.id,
        announcementID: this.item.announcementID || 0,
        createUserID: this.user_account.userId,
        createDt: new Date().getTime(),
        // content: JSON.stringify(content)
        content: content
      }
      console.log('GroupAnnouncementInfo::::', GroupAnnouncementInfo)
      let _handleAddNotice = resp => {
        console.log('resp::::', resp)
        let respCode = JSON.parse(resp);
        console.log(respCode)
        if (respCode.code !== 0) {
          this.$toast.open({
            message: this.$t(`ErrorCode.${respCode.code}`),
            type: 'is-danger'
          })
          this.$emit('close')
        } else {
          if (!this.chat_objectInfo[this.id][this.user_account.userId]) {
            console.log('测试进入情况1')
            this.$Service.search.getUserInfo({ userId: this.user_account.userId }, resp=>{
              this.$set(GroupAnnouncementInfo, 'publisher', resp.users.name)
            });
          } else {
            console.log('测试进入情况2')
            this.$set(GroupAnnouncementInfo, 'publisher', this.chat_objectInfo[this.id][this.user_account.userId].remark)
          }
          console.log('测试进入情况3')
          this.$set(GroupAnnouncementInfo, 'time', getDateDiff(parseInt(new Date().getTime())))
          console.log('GroupAnnouncementInfo:::::after', GroupAnnouncementInfo)
          this.$emit('close', GroupAnnouncementInfo)
        }
      }
      this.$Service.group._group.addGroupAnnouncement(GroupAnnouncementInfo, _handleAddNotice)
    },
    checkPulbishRequired(data) {
      let warnInfo = ''
      if (data.content.length === 0) {
        warnInfo = this.$t('groups.inputInformation')
      }
      if (data.content.length > 500) {
        warnInfo = this.$t('groups.warningExceed')
      }
      if (warnInfo) {
        this.$toast.open({ message: warnInfo, type: 'is-danger'})
        return false;
      }
      return true
    },
    uploadeImg(img) {
      console.log('img:::', img)
      return new Promise(resolve => {
        let uploadImageParam = {
          targetId: this.id,
          localId: '',
          thumbimg: '',
          srcimg: img,
          encryptkey: encryptionPassword().toString()
        }
        console.log('uploadImageParam:::', uploadImageParam)
        this.$Service.file.uploadImage(uploadImageParam, resp => {
          console.log('uploadImage', resp)
          if (resp.code === 0) {

            let srcJson = this.isJSON(resp.srcJson) && JSON.parse(resp.srcJson)
            this.imgInfo.mediaUrl = srcJson.files[0].url
            this.imgInfo.enc_dec_key = uploadImageParam.encryptkey
            resolve()
          } else {
            this.$toast.open({
              message: this.$t(`ErrorCode.${resp.code}`),
              type: 'is-danger'
            })
          }
        })
      })
    }
  }
}
</script>
<style lang="scss">
.notice-edit {
  display: flex;
  height: 100%;
  .edit-img {
    width: 140px;
    background: #f0f0f0;
    margin-right: 10px;
    padding: 10px;
  }
  .edit-content {
    flex: 1;
    display: flex;
    flex-direction: column;
    .edit-title {
      .title-input {
        textarea {
          min-height: 0px;
          height: 38px;
          font-size: 16px;
          resize: none;
          padding: 6px;
          font-weight: bold;
          box-shadow: none;
          border: 1px solid #ccc;
        }
      }
    }
    .edit-action-type {
      display: flex;
      margin: 6px 0;
      .slide-down-enter-active {
        transition: all 0.6s ease-out;
      }
      .slide-down-leave-active {
        transition: all 0.3s ease;
      }
      .slide-down-enter,
      .slide-down-leave-to {
        transform: translateY(-10px);
        opacity: 0.9;
      }
      .v-emoji {
        position: absolute;
        top: 89px;
        border-radius: $--border-radius-base;
        box-shadow: $--box-shadow-elevation;
      }
      .action-item {
        font-size: 14px;
        margin-right: 12px;
        cursor: pointer;
        display: flex;
        input {
          display: none;
        }
      }
    }
    .edit-txt {
      font-size: 14px;
      flex: 1;
      // .control {
      //   height: 100%;
      //   textarea {
      //     resize: none;
      //     height: 100%;
      //   }
      // }
      border: 1px solid #ccc;
      padding: 6px;
      border-radius: 3px;
      overflow: hidden;
      .edit-textarea {
        height: 82%;
        resize: none;
        font-family: inherit;
        letter-spacing: 0.5px;
        border: none;
        box-shadow: none;
        font-size: $--font-size-mid;
        color: #000;
        font-weight: 500;
        outline: none;
        overflow-y: auto;
        white-space: normal;
        -webkit-user-modify: read-write-plaintext-only;
        overflow-x: hidden;
        word-break:break-word;
        .v-text-emoji {
          width: 21px;
          height: 21px;
          margin: 0 2px;
          user-select: none;
        }
      }
      .publish-btn {
        position: absolute;
        right: 26px;
        bottom: 22px;
      }
    }
  }
}
</style>
