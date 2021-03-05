<template>
  <div class="change-avatar">
    <div class="modal-title theme-bgc_font">
      <span>{{$t('account.changeAvatar')}}</span>
      <i class="icon" @click="$emit('close')">&#xe650;</i>
    </div>
    <img-cropper
      class="img-cropper"
      @restore-optional="restoreOptional"
      :isRestoreOptional="isRestoreOptional"
      :isUserCenterModify="isUserCenterModify"
      :saveImg="isSaveImg" :isLoading="isLoading"
      @imgEmpty="emptyWarn"
      @uploading="uploadLoading"
    ></img-cropper>
    <div class="change-header-btn cutting-line-before">
      <v-tooltip class="botton-pos" type="is-danger" position="is-left" :lable="tipLable" :active="tipActive" always>
        <v-button :type="`${buttonType} theme-botton is-primary`" :ripple="false" @click="saveUserAvatar">{{$t('common.save')}}</v-button>
      </v-tooltip>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import imgCropper from './../../Common/ImgCropper/imgCropper';
export default {
  data() {
    return {
      isSaveImg: false,
      isLoading: false,
      tipLable: '',
      tipActive: false,
      isRestoreOptional: false
    };
  },
  props: {
    id: String,
    isUserCenterModify: Boolean
  },
  computed: {
    ...mapGetters(['user_imgPath', 'user_account']),
    buttonType() {
      return this.isLoading ? 'is-loading' : '';
    }
  },
  components: {
    imgCropper
  },
  methods: {
    restoreOptional(val) {
      this.isRestoreOptional = false;
    },
    uploadLoading(data) {
      this.isSaveImg = false;
      let thumbImageInfo = this.$images.thumbImage(data, false);
      let savePath = this.user_imgPath + new Date().getTime() + '.jpg';
      let uploadAvatarParam = {
        path: savePath
      };
      console.log(uploadAvatarParam, '图片本地路径');
      this.$fs.writeFile(
        savePath,
        thumbImageInfo.originBuffer,
        (err) => {
          if (err) throw err;
          this.$Service.file.uploadAvatar(
            uploadAvatarParam,
            resp => {
              console.log('uploadAvatar:::', resp);
              if (resp.code !== 0) {
                this.uploadError(this.$t('user.uploadError'));
                this.$Service.file.fileOperate({filepath: savePath, type: 2})
              } else {
                this.updateUserAvatar(resp);
                this.$Service.file.fileOperate({filepath: savePath, type: 2})
              }
            }
          )
        }
      );
    },
    uploadSuccess() {
      [this.isLoading, this.isSaveImg] = [false, false];
      this.$emit('close');
      this.isRestoreOptional = true;
    },
    uploadError(msg) {
      [this.isLoading, this.tipActive, this.tipLable] = [false, true, msg];
      setTimeout(() => {
        this.tipActive = false;
      }, 1000);
    },
    emptyWarn() {
      [this.isLoading, this.isSaveImg, this.tipActive, this.tipLable] = [
        false,
        false,
        true,
        this.$t('user.emptyAvatar')
      ];
      setTimeout(() => {
        this.tipActive = false;
      }, 1000);
    },
    saveUserAvatar() {
      [this.isSaveImg, this.isLoading] = [true, true];
    },
    updateUserAvatar({ orgiJson, thumbJson }) {
      console.log(orgiJson, thumbJson, '------------');
      let srcImg = orgiJson && JSON.parse(orgiJson);
      console.log(srcImg, 'srcImg');
      if (srcImg.code !== 0 || srcImg.files[0].code !== 0) {
        this.uploadError(srcImg.msg || srcImg.files[0].msg);
        return;
      }
      let updateAccountInfoParam = {
        avatar: JSON.parse(orgiJson).files[0].images[1].url,
        thumbAvatar: JSON.parse(thumbJson).files[0].images[1].url
      };
      console.log('updateAccountInfoParam:::', updateAccountInfoParam);
      this.$Service.user.updateAccountInfo(
        updateAccountInfoParam,
        resp => {
          if (resp.code !== 0) {
            this.uploadError(this.$t('user.modifyError'));
          } else {
            console.log('updateAccountInfo Success');
            this.uploadSuccess();
          }
        }
      );
    }
  }
};
</script>
<style lang="scss">
.change-avatar {
  .modal-title{
    padding: 5px 5px 3px 9px;
    display: flex;
    justify-content: space-between;
  }
  .img-cropper {
    margin: 10px;
    padding: 10px;
    overflow: hidden;
    .show-info{
      height: 100%;
    }
  }
  .change-header-btn{
    height: 56px;
    position: relative;
    .botton-pos{
      position: absolute;
      right: 10px;
    }
  }
}
</style>
