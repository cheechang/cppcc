<template>
  <div class="phone-verify">
    <div class="phone-verify-page">
      <!-- 服务器 -->
      <v-tip :style="{'pointer-events':'none'}">
        <v-input
          class="inputs"
          v-model="server"
          :type="'text'"
          :isBorder="false"
          hasLine
          :maxlength="50"
          :isAuth="true"
          :inputLineSite="'-1px'"
          :placeholder="$t('auth.server')"
        ></v-input>
      </v-tip>
      <!-- 国家码/手机号 -->
      <v-tip class="tip-table" hasLine :isLightLine="isLightLine" :style="{'pointer-events':'none'}">
        <div class="nation-code" v-if="type===1">
          <span>+{{nationCode.replace(/\b(0+)/gi,'')}}</span>
          <i
            class="icon icon-option"
            :class="{'scale-icon': !isOptionHide}"
            @click.self.stop="isOptionHide = !isOptionHide"
          >&#xe77a;</i>
          <span class="line"></span>
        </div>
        <v-input
          class="inputs"
          v-model="account"
          :type="'text'"
          :isBorder="false"
          :placeholder="$t('auth.phone')"
          :maxlength="18"
          @focus="isLightLine = true"
          @blur="isLightLine = false"
        ></v-input>
      </v-tip>
      <!-- 验证码 -->
      <v-tip
        :isSuccess="isSuccess"
        :tipLabelMsg="errorMsg"
        :isLabelTip="isErrorBox"
        @close="isErrorBox = false"
      >
        <v-input
          class="inputs"
          hasLine
          hasLabel
          v-model="verifyCode"
          :type="'text'"
          :isAuth="true"
          :inputLineSite="'-1px'"
          :customType="'input-size'"
          :isBorder="false"
          :placeholder="$t('auth.verifyCode')"
          :position="'right'"
          :maxlength="50"
        >
          <v-button
            slot="expand"
            class="ver-code"
            :class="{'btn-disable':isCodeDisabled}"
            :disable="isCodeDisabled"
            :ripple="false"
            :type="codelodingState"
            @click="getRegCode"
          >{{regCode}}</v-button>
        </v-input>
      </v-tip>
      <!-- 下一步 -->
      <v-btn
        class="auth-button"
        :size="'v-button--max_width'"
        :disable="!isDisable"
        :type="lodingState"
        @click="next"
      >{{$t('auth.next')}}</v-btn>
      <div class="back-login">
      <span @click="cancel" class="txt-link">{{$t('auth.cancelLogin')}}</span>
    </div>
    </div>
  </div>
</template>

<script>
import Vue from "vue";
import { mapGetters } from "vuex";
import config from "./../../../comm/config.js";
import vTip from "./common/tooltip.vue";
import vBtn from "./common/button.vue";
import vClickOutside from "./../Chat/v-click-outside/index.js";
import { versionCompire, getErrorMsg } from "../../utils/utils.js";
export default {
  name: "register-page",
  components: {
    vTip,
    vBtn
  },
  directives: {
    clickOutside: vClickOutside.directive
  },
  data() {
    return {
      type:1,
      server: "",
      nationCode: "+86",
      account: "",
      isLightLine: false,
      isOptionHide: true,
      verifyCode: "",
      regCode: this.$t("auth.getVerifyCode"),
      isLoading: false,
      isCodeLoading: false,
      isCodeSend: false,
      errorMsg: "",
      isErrorBox: false,
      isSuccess: false,
      isGetCodeBtnDisable: false,
      clock: 0,
      registryId:'',
    };
  },
  computed: {
    ...mapGetters(["auth_nationCode"]),

    // 加载动画显示
    lodingState() {
      return this.isLoading ? "is-loading" : "";
    },

    // 获取验证码等待动画
    codelodingState() {
      return this.isCodeLoading ? "is-loading" : "";
    },

    // 下一步按钮可点击状态
    isDisable() {
      return (
        this.server !== "" &&
        this.account !== "" &&
        this.verifyCode !== "" &&
        this.isCodeSend
      );
    },

    // 获取验证码按钮能否点击
    isCodeDisabled() {
      return this.account === "" || this.isGetCodeBtnDisable;
    }
  },
  created() {
    this.nationCode =
      this.auth_nationCode === ""
        ? this.$Service.config.getSystemNationCode()
        : this.auth_nationCode;
    this.server = this.$route.query.server;
    this.account = this.$route.query.account;
    this.type = this.$route.query.type;
    console.log(this.server,' ',this.account);
  },
  methods: {
      cancel() {
        this.$Service.auth.logout(null, resps => {
          this.$Service.log(`账号激活:点击登录后弹出手机认证界面，未激活直接关闭弹框调用登出接口返回:${JSON.stringify(resps)}`);
          this.$ipc.send("tray-logout");
        });
        this.$router.push({ path: '/Login'});
      },
    // 下一步
    next() {
      /**
       * 1. 下一步加载等待过程中禁止再次点击
       * 2. 匹配验证码格式
       */
      if (this.isLoading) return;
      let verRule = /^[0-9a-zA-Z]*$/g;
      if (!verRule.test(this.verifyCode)) {
        this.isErrorBox = true;
        this.errorMsg = this.$t("auth.codeEmpty");
        this.isSuccess = false;
        return;
      }
      this.$Service.auth.verifyMailOrPhoneCode({code:this.verifyCode,type:this.type,registryId:this.registryId}, resp=>{
          if(resp.code === 0){ //验证通过
            console.log('激活账号手机验证:::获取验证码:::验证通过')
            this.$router.push({ path: '/Activate'});
          }
          else{
            this.isSuccess = false;
            this.errorMsg = getErrorMsg(resp.code);
            this.isErrorBox = true;
          }
      });
    },


    // 点击获取验证码
    getRegCode() {
      // 显示加载动画
      this.isCodeLoading = true;
      // 禁用按钮点击
      this.isGetCodeBtnDisable = true;
      let param = {
          mailOrPhone: this.type === 1? this.nationCode + this.account : this.account,
          type:this.type,
          language:this.$Service.config.getLanguage()
      };
      this.$Service.log(
          `激活账号手机验证:::获取验证码:::入参:::${JSON.stringify(param)}`
        );
      this.$Service.auth.getVerifyMailOrPhoneCode(param, this._getVerifyMailOrPhoneCodeHandler);
      // 调用预登陆接口，判断是否可注册
    },

    // 获取验证码回调
    _getVerifyMailOrPhoneCodeHandler(resp) {
      this.$Service.log(`激活账号手机验证:::获取验证码:::返回:::${JSON.stringify(resp)}`);
      this.isCodeLoading = false;
      if (resp.code !== 0) {
        //  错误处理
        this.isGetCodeBtnDisable = false;
        this.errorMsg = getErrorMsg(resp.code);
        this.isErrorBox = true;
        return;
      }
      //  成功后需要提示
      this.errorMsg = this.$t("auth.verCodeSent");
      this.isErrorBox = true;
      this.isSuccess = true;
      this.registryId = resp.registryId;
      this.regCode = `${resp.timeOut}s`;
      this.clock = setInterval(() => {
        resp.timeOut--;
        this.regCode = resp.timeOut + "s";
        if (resp.timeOut < 1) {
          //  TODO: 倒计时结束后取消禁用
          this.clearClock();
        }
      }, 1000);
      this.isCodeSend = true;
    },
    clearClock() {
      clearInterval(this.clock);
      console.log("clear close::", this.clock);
      this.clock = 0;
      this.regCode = this.$t("auth.getVerifyCode");
      this.isGetCodeBtnDisable = false;
    }
  }
};
</script>

<style lang="scss">
@import "./_auth";
.phone-verify {
  display: none;
  flex-direction: column;
  width: 280px;
  height: auto;
  position: relative;
  .auth-tip {
    width: 100%;
    margin: 5px 0;
    border-bottom: 1px solid $--border-color-blue;
  }
  .input-border {
    border-bottom: none !important;
  }
  input {
    font-size: $--font-size-mid;
  }
  .phone-verify-page {
    .tip-table {
      display: inline-flex;
      justify-content: flex-start;
      position: relative;
      .nation-code {
        display: flex;
        justify-content: flex-start;
        align-items: center;
        padding-left: 8px;
        width: 90px;
        position: relative;
        span {
          color: get-grey-color(base);
        }
        .icon-option {
          top: 5px;
          /* margin-left: 20px; */
          position: absolute;
          right: 4px;
        }
        .line {
          display: inline-block;
          border-left: 1px solid $--border-color-grey;
          height: 15px;
          margin: 0 7px 0 10px;
          position: absolute;
          right: -7px;
        }
      }
      .option-list {
        width: 100%;
        height: 200px;
        background: $--color-white;
        padding: 10px 0;
        // max-height: 200px;
        overflow-y: auto;
        position: absolute;
        right: 0;
        top: 34px;
        border-radius: $--border-radius-base;
        @include z-index(btn);
        .nation-item {
          width: 100%;
          padding: 8px 10px;
          cursor: default;
          &:hover {
            background: get-grey-color(lighten-2);
          }
        }
      }
    }
    .control.has-icons-right .icon.is-right {
      right: 0px;
      width: 85px;
    }
    .ver-code {
      font-size: $--font-size-mid;
      display: inline-block;
      padding-right: 5px;
      padding-top: 6px;
      color: get-grey-color(darken-3);
      background: $--color-white;
      font-family: "\5FAE\8F6F\96C5\9ED1", "Microsoft YaHei", Arial, Helvetica,
        sans-serif, "\5B8B\4F53";
      &:hover {
        background: $--color-white;
        color: get-blue-color(blue);
      }
    }
    .already-account {
      font-size: $--font-size-small;
      justify-content: flex-start;
      padding-left: 68px;
    }
    .auth-button {
      margin: 25px 0 0 0;
    }
    .back-login {
    display: flex;
    justify-content: center;
    padding-top: 15px;
    font-size: $--font-size-mid;
     span {
       padding: 0 5px;
       cursor: pointer;
     }
    }
  }
}
</style>
