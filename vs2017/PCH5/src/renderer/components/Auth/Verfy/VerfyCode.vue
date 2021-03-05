<template>
  <v-modal cardSize="verfy-class" @close="$emit('close')">
    <div class="verfy-body">
    <div class="alert">
      <i class="icon delete" @click="[$emit('verfy')]"></i>
      <div class="text">{{$t('auth.loginRetry')}}</div>
      <div class="text">{{$t('auth.inputVerifyCode')}}</div>
    </div>
    <div class="verfy-code">
      <div class="input-code">
        <input
          class="verify-input"
          :placeholder="$t('auth.verifyCode')"
          v-model="inputImgCode"
        >
        <div class="img-code">
          <img :src="verifyCode">
        </div>
        <v-button
          class="change-code"
          @click="getImgCode"
        >{{$t('auth.changeVerifyCode')}}</v-button>
      </div>
      <p
        class="help is-danger"
        :style="{visibility:isVerfyCodeEmpty?'visible':'hidden'}"
      >
        <i class="icon" @click="isVerfyCodeEmpty=false">&#xe644;</i>
        {{errorWarn}}
      </p>
    </div>
    <v-button class="button is-primary" :disable="inputImgCode === ''" @click="imgCodeVerfy()">
      {{$t('common.confirm')}}
    </v-button>
    </div>
  </v-modal>
</template>

<script>
import Vue from 'vue';
import { getErrorMsg } from './../../../utils/utils.js'
import UnicomAuthMixins from '../Login/UnicomAuthMixins';
export default {
  mixins: [UnicomAuthMixins],
  data() {
    return {
      verifyCode: '',
      errorWarn: '',
      inputImgCode: '',
      isVerfyCodeEmpty: false,
      createImgCount: 0,
      newFileName: '',
      param: {
        account: '',
        code: ''
      },
      tempImgArr:[]
    };
  },
  props: {
    nation: String,
    account: String,
    userType:Number,
    img: String,
    multiPleServers:Boolean
  },
  created() {
    this.getImgCode();
  },
  methods: {
    closeVerfyBox() {
      $emit('verfy');

    },
    getLoginAccount() {
      let user = (this.userType === 1 || this.userType === 96) ? this.nation + this.account : this.account;
      return user;
    },
    delImgCode() {
      if(this.tempImgArr.length > 0){
        for(let di in this.tempImgArr) {
          this.$Service.file.fileOperate({filepath:this.tempImgArr[di], type:2})
        }
      }
    },
    /**
     * 验证码是否正确
     */
    imgCodeVerfy() {
      this.param.code = this.inputImgCode;
      this.$emit('codeVerfy',this.param)

      // this.$Service.log(`图片验证码:::点击验证入参:::${JSON.stringify(this.param)}`);
      // if(this.multiPleServers){
      //   //子服务器登录
      //   this.$mutipleServers.verifyImgCode(
      //     this.param,
      //     this._imgCodeVerfyHandler
      //   );
      // }
      // else{
      //   this.$Service.auth.verifyImgCode(
      //     this.param,
      //     this._imgCodeVerfyHandler
      //   );
      // }
    },
    _imgCodeVerfyHandler({code, img}) {
      this.$Service.log(`图片验证码:::点击验证返回:::${code, img}`);
      if (code !== 0) {
        // 验证失败
        ++this.createImgCount;
        this.fileReName(img);
        if (getErrorMsg(code)) {
          // 提示错误
          [this.errorWarn, this.isVerfyCodeEmpty] = [
            getErrorMsg(code),
            true
          ];
        }
        setTimeout(() => {
          this.isVerfyCodeEmpty = false
        }, 2000)
      } else {
        // 验证成功
        if (this.inputImgCode !== '') {
          this.$emit('verfy');
          this.delImgCode();
        } else {
          [this.errorWarn, this.isVerfyCodeEmpty] = [
            this.$t('auth.codeEmpty'),
            true
          ];
        }
      }
    },
    /**
     * 获取验证码图片
     */
    getImgCode() {
      this.getNewVerifyCodeInfo(this.account,data => {
        console.log(data)
        this.verifyCode = data
      })
      // console.log(this.param, '验证码');
      // ++this.createImgCount;
      // [this.param.account, this.param.code] = [
      //   this.getLoginAccount(),
      //   ''
      // ];
      // this.$Service.log(`图片验证码:::获取验证码入参:::${JSON.stringify(this.param)}`);
      // if(this.multiPleServers){
      //   //子服务器登录
      //   this.$mutipleServers.verifyImgCode(
      //     this.param,
      //     this._getImgCodeHandler
      //   );
      // }
      // else{
      //   this.$Service.auth.verifyImgCode(
      //     this.param,
      //     this._getImgCodeHandler
      //   );
      // }
    },
    _getImgCodeHandler({ code, img }) {
      this.$Service.log(`图片验证码:::获取验证码返回:::${code, img}`);
      if (code !== 0) {
        [this.errorWarn, this.isVerfyCodeEmpty] = [
          this.$t('auth.getVerifyCodeRetry'),
          true
        ];
      } else {
        this.fileReName(img);
      }
    },
    /**
     * 文件重命名、删除
     * @param img 图片路径
     */
    fileReName(img) {
      let [dateTimeStamp, delImgCode] = [
        new Date().getTime(),
        this.newFileName
      ];
      this.newFileName = img.substring(0, img.indexOf('.')) + dateTimeStamp + '.png';
      this.tempImgArr.push(this.newFileName);
      let fileOperateParam = {
        filepath: img, //路径
        type: 3, // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
        newName: this.newFileName, //重命名文件全路径
      };
      let renameRes = this.$Service.file.fileOperate(fileOperateParam);
      if(renameRes){
        if (this.createImgCount === 1) {
          this.verifyCode = this.newFileName;
        } else {
          let delFile = this.$Service.file.fileOperate({filepath:this.tempImgArr[0], type:2});
          this.tempImgArr.splice(0,1)
          if(delFile){
            this.verifyCode = this.newFileName;
          }
        }
      }
    }
  }
};
</script>

<style lang="scss">
.verfy-class {
  width: 282px;
  // height: 238px;
  .modal-card-body{
    border-radius: $--border-radius-base;
    overflow: hidden;
  }
  .verfy-body {
    padding: 20px;
    .alert {
      font-size: $--font-size-mid;
      padding: 0px 18px 20px 18px;
      color: get-grey-color(darken-3);
      .delete {
        position: absolute;
        right: 3px;
        top: 3px;
      }
    }
    .verfy-code {
      display: flex;
      flex-direction: column;
      .is-danger {
        @include z-index(btn);
        height: 36px;
        margin: 0;
        color: $--color-danger;
        line-height: 36px;
        background: #febdbc;
        @include ellipsis;
        i {
          display: inline;
          margin: 0px 5px 0px 5px;
        }
      }
      .input-code {
        display: flex;
        .verify-input {
          width: 140px;
          height: 33px;
          outline: none;
          border: 1px solid $--border-color-blue!important;
          border-right: 0!important;
          font-family: inherit;
          padding-left: 8px;
        }
        .change-code {
          position: absolute;
          cursor: pointer;
          right: 21px;
          width: 99px;
          border: none;
          padding: 0px;
          outline: 0 none;
          background: $--color-white;
          font-size: $--font-size-mid;
          color: get-grey-color(darken-3);
          margin-top: 36px;
          white-space: nowrap;
        }
        .img-code {
          flex: 1;
          height: 33px;
          border: 1px solid $--border-color-blue;
          img{
            height: 100%;
          }
        }
      }
    }
    .is-primary {
      background-color: $--color-info;
      height: 40px;
      width: 100%;
    }
  }
}
</style>
