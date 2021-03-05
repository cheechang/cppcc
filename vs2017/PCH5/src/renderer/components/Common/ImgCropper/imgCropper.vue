<template>
  <div class="content" :style="{marginBottom: isUserCenterModify?'0':''}">
    <div class="show-info">
      <div class="columns is-mobile" :style="isUserCenterModify?{display: 'flex', flexDirection: 'row-reverse'}:''">
        <div class="column is-9">
          <div class="cropper">
            <vue-cropper ref="cropper" :img="imgInfo.img" :outputSize="imgInfo.size" :outputType="imgInfo.outputType" :info="imgInfo.info" :canScale="imgInfo.canScale" :autoCrop="imgInfo.autoCrop" :autoCropWidth="imgInfo.width" :autoCropHeight="imgInfo.height" :fixed="imgInfo.fixed" :fixedNumber="imgInfo.fixedNumber" @changeCropEnd="finish()"></vue-cropper>
            <label class="btn" for="upload" v-if="imgInfo.img==''">{{$t('user.selectPic')}}</label>
            <input class="select-btn" type="file" id="upload" style="position:absolute; clip:rect(0 0 0 0);" accept="image/png, image/jpeg, image/gif, image/jpg" @change="uploadImg($event, 2)">
          </div>
        </div>
        <div class="column is-3">
          <div class="show-preview" :style="{width: previews.w + 'px', height: previews.h + 'px',  overflow: 'hidden', margin: '5px'}">
            <div :style="previews.div">
              <div v-if="isUserCenterModify">100*100</div>
              <v-avatar class="Thumbnail100" :sex="gender||this.user_account.gender" :src="avatar||option.img" :style="previews.img" size="is-large" :offline="false" shape="round"></v-avatar>
            </div>
            <div v-if="isUserCenterModify">
              <div :style="previews.div">
                <div>48*48</div>
                <v-avatar class="Thumbnail48" :sex="gender||this.user_account.gender" :src="avatar||option.img" :style="previews.img" size="is-large" :offline="false" shape="round"></v-avatar>
              </div>
              <div :style="previews.div">
                <div>24*24</div>
                <v-avatar class="Thumbnail24" :sex="gender||this.user_account.gender" :src="avatar||option.img" :style="previews.img" size="is-large" :offline="false" shape="round"></v-avatar>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import vueCropper from './vue-cropper';
import { mapGetters } from 'vuex';
// import { writeFile } from '../../../../comm/fileSystem';
// import { thumbImage } from '../../../../comm/images.ts';
// import thumbImage from '../../../../comm/electron/platForm.ts';
export default {
  data: function() {
    return {
      crap: false,
      previews: {},
      option: {
        img: '',
        size: 0.8,
        outputType: 'jpeg'
      },
      imgInfo: {
        img: '',
        info: true,
        size: 1,
        outputType: 'jpeg',
        canScale: true,
        autoCrop: true,
        // 只有自动截图开启 宽度高度才生效
        width: 150,
        height: 150,
        fixed: true,
        fixedNumber: [1, 1]
      }
    };
  },
  props: {
    saveImg: {
      type: Boolean,
      default: false
    },
    isLoading: {
      type: Boolean,
      default: false
    },
    gender: Number,
    avatar: String,
    isUserCenterModify: Boolean,
    isRestoreOptional: Boolean,
  },
  computed: {
    ...mapGetters(['user_account'])
  },
  watch: {
    saveImg: function() {
      if (this.saveImg) {
        this.finish();
      }
    },
    isLoading: function() {
      if (this.imgInfo.img === '' && this.isLoading) {
        this.$emit('imgEmpty');
      }
    },
    isRestoreOptional: function() {
      if(this.isRestoreOptional){
        this.imgInfo.img = '';
        this.option.img = '';
        document.getElementById('upload').value = '';
        this.$emit('restore-optional');
      }
    },
    "option.img":function(val, oldVal) {
      if(val == '' && this.isUserCenterModify == true){
        this.option.img = this.user_account.thumbAvatarUrl&&this.user_account.thumbAvatar;
      }
    },
    'user_account.thumbAvatar':function (val, oldVal) {
      if(this.isUserCenterModify){
        this.option.img = val;
      }
    }
  },
  created() {
    if(this.isUserCenterModify){
      console.log('this.isUserCenterModify');
      this.option.img = this.user_account.thumbAvatarUrl&&this.user_account.thumbAvatar;
    }
  },
  methods: {
    finish() {
      this.$refs.cropper.getCropData(data => {
        this.option.img = data;
        if (this.$props.saveImg) {
          // 防止图片正在保存时移动裁剪框后再次进入方法
          this.$emit('uploading', data);
        }
      });
    },
    uploadImg(e, num) {
      // console.log(e, num, '7777777777777');
      // 上传图片
      var file = e.target.files[0];
      if (!/\.(gif|jpg|jpeg|png|bmp|GIF|JPG|PNG)$/.test(e.target.value)) {
        alert(this.$t('user.imgPattern'));
        return false;
      }
      var reader = new FileReader();
      reader.onload = e => {
        this.imgInfo.img = e.target.result;
      };
      reader.readAsDataURL(file);
    }
  },
  components: {
    vueCropper
  }
};
</script>

<style lang="scss" scoped>
* {
  margin: 0;
  padding: 0;
}

.content {
  margin: auto;
  height: 308px;
  max-width: 660px;
  margin-bottom: 100px;
}

.btn {
  position: absolute;
  height: 40px;
  width: 120px;
  top: 50%;
  left: 50%;
  margin-top: -20px;
  margin-left: -60px;
  background: #a9a9a9;
  color: #1f2d3d;
  padding: 9px 15px;
  font-size: 16px;
  border-radius: $--border-radius-base;
  color: #fff;
}

.select-btn{
  width: 10px;
  height: 10px;
  position: absolute;
  top: 50%;
  left: 50%;
  margin-top: -5px;
  margin-left: -5px;
}

.show-info {
  overflow: hidden;
  width: 100%;
  .is-mobile {
    height: 308px;
    margin: 0px;
    .is-9 {
      background: #f0f0f0;
      padding: 0px;
      color: #ffffff;
      text-align: center;
    }
    .is-3 {
      background: #ffffff;
      padding: 0px;
      display: flex;
      justify-content: center;
      .show-preview{
        .Thumbnail100{
          width: 100px;
          height:100px;
          margin: 0 auto;
          margin-bottom:20px;
        }
        .Thumbnail48{
          width: 48px;
          height:48px;
          margin: 0 auto;
          margin-bottom:20px;
        }
        .Thumbnail24{
          width: 24px;
          height:24px;
          margin: 0 auto;
          margin-bottom:20px;
        }
      }
    }
  }
}

.cropper {
  height: 308px;
  background: #f0f0f0;
  position: relative;
}

@keyframes slide {
  0% {
    background-position: 0 0;
  }
  100% {
    background-position: -100% 0;
  }
}
</style>
