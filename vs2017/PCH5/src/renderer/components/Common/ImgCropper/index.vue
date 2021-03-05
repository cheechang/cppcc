<template>
  <div class="modal-avatar">
    <v-modal cardSize="img-class" @close="$emit('close')">
      <div class="modal-card-head" slot="header-top">
        <p class="modal-card-title">{{from === 1 ? $t('user.updateGroupAvatar'):$t('user.updateAvatar')}}</p>
        <i class="icon" @click="$emit('close')">&#xe603;</i>
      </div>
      <img-cropper class="img-cropper" :gender="gender" :avatar="avatar" :saveImg="isSaveImg" :isLoading="isLoading" @imgEmpty="emptyWarn" @uploading="uploadLoading"></img-cropper>
      <div class="modal-card-foot" slot="footer-bottom">
        <v-tooltip type="is-danger" :lable="tipLable" :active="tipActive" always>
          <v-button :type="`${buttonType} is-primary`" :ripple="false" @click="saveUserAvatar">{{$t('common.save')}}</v-button>
        </v-tooltip>
        <v-button  @click="$emit('close')">{{$t('common.cancel')}}</v-button>
      </div>
    </v-modal>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import imgCropper from './imgCropper.vue';
export default {
  data() {
    return {
      isSaveImg: false,
      isLoading: false,
      tipLable: '',
      tipActive: false
    };
  },
  props: {
    // 0:修改用户头像 1:修改群头像
    from: Number,
    id: String,
    gender: Number,
    avatar: String
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
    uploadLoading(data) {
      this.isSaveImg = false;
      let thumbImageInfo = this.$images.thumbImage(data, false);
      let savePath = this.user_imgPath + new Date().getTime() + '.jpg';
      let uploadAvatarParam = {
        path: savePath
      };
      this.$fs.writeFile(
        savePath,
        thumbImageInfo.originBuffer,
        resps => {
          this.$Service.file.uploadAvatar(
            uploadAvatarParam,
            resp => {
              if (resp.code !== 0) {
                this.uploadError(this.$t('user.uploadError'));
                // this.$Service.file.fileOperate({filepath: savePath, type: 2})
              } else {
                if (this.from === 0) this.updateUserAvatar(resp);
                else if (this.from === 1) this.updateGroupAvatar(resp);
                // this.$Service.file.fileOperate({filepath: savePath, type: 2})
              }
            }
          );
        }
      );
    },
    uploadSuccess() {
      [this.isLoading, this.isSaveImg] = [false, false];
      this.$emit('close');
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
      let srcImg = orgiJson && JSON.parse(orgiJson);
      if (srcImg.code !== 0 || srcImg.files[0].code !== 0) {
        this.uploadError(srcImg.msg || srcImg.files[0].msg);
        return;
      }
      let updateAccountInfoParam = {
        srcAvatar: JSON.parse(orgiJson).files[0].images[1].url,
        avatar: JSON.parse(thumbJson).files[0].images[1].url
      };
      this.$Service.user.updateAccountInfo(
        updateAccountInfoParam,
        resp => {
          if (resp.code !== 0) {
            this.uploadError(this.$t('user.modifyError'));
          } else {
            this.uploadSuccess();
          }
        }
      );
    },
    updateGroupAvatar({ thumbJson }) {
      let setGroupInfoParam = {
        groupId: this.id,
        groupIcon: JSON.parse(thumbJson).files[0].images[1].url
      };
      this.$Service.group.setGroupInfo(
        setGroupInfoParam,
        resp => {
          if (resp.code !== 0) {
            this.uploadError(this.$t('user.modifyError'));
          } else {
            this.uploadSuccess();
          }
        }
      );
    }
  }
};
</script>
<style lang="scss">
.modal-avatar {
  .img-class {
    height: 428px;
    width: 660px;
    border-radius: $--border-radius-base;
    overflow: hidden;
    background: #ffffff;
    .modal-card-head {
      height: 20px;
      background: #f0f0f0;
      border-bottom: none;
      .modal-card-title {
        font-size: 14px;
      }
      .icon {
        font-size: 14px;
        margin-right: -20px;
      }
    }
    .img-cropper {
      margin: 10px 10px 20px 20px;
      padding: 0px;
    }
    .modal-card-foot {
      height: 50px;
      background: #ffffff;
      border-top: none;
      justify-content: flex-end;
      .button {
        height: 30px;
        font-size: 14px;
        margin-right: 10px;
      }
    }
  }
}
</style>
