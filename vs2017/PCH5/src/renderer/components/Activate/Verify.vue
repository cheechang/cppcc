<template>
<v-modal>
  <div class="phone-verify">
    <div class="phone-verify-page">
      <!--头部标题-->
      <headerTip :headerName="headerTipName"></headerTip>
      <!--显示邮箱/手机号-->
      <div class="nationCode-phone">
        <h3>{{account}}</h3>
      </div>

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
          @keyup-enter='next'
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
  </v-modal>
</template>

<script>
import Vue from "vue";
import { mapGetters } from "vuex";
import config from "../../../comm/config.js";
import headerTip from "./HeaderTip.vue";
import vTip from "../Auth/common/tooltip.vue";
import vBtn from "../Auth/common/button.vue";
import ActivateMixin from "./ActivateMixins.js";
import vClickOutside from "./../Chat/v-click-outside/index.js";
import { versionCompire, getErrorMsg } from "../../utils/utils.js";
export default {
  mixins: [ActivateMixin],
  name: "register-page",
  components: {
    vTip,
    vBtn,
    headerTip
  },
  directives: {
    clickOutside: vClickOutside.directive
  },
  data() {
    return {
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
      verifyType: this.$route.query.verifyType,
      verifyField:'',
      accountNum:''
    };
  },
  computed: {
    ...mapGetters([
      "auth_nationCode",
      "user_account",
      "user_loginInfo"
      ]),

    //根据登录方式传头部标题名称
    headerTipName(){
      return this.user_loginInfo.userType === 1 ? this.$t('auth.shortMessageVerify') : this.$t('auth.emailVerify');
    },
    // 加载动画显示
    lodingState() {
      return this.isLoading ? "is-loading" : "";
    },

    // 获取验证码等待动画
    codelodingState() {
      return this.isCodeLoading ? "is-loading" : "";
    },
    account() {      
      return this.user_loginInfo.userType === 1 ? `+${this.auth_nationCode.replace(/\b(0+)/gi,'')} ${this.user_loginInfo.account}` : `${this.user_loginInfo.account}`;
    },
    // 下一步按钮可点击状态
    isDisable() {
      return ( this.verifyCode !== "" && this.isCodeSend );
    },
    // 获取验证码按钮能否点击
    isCodeDisabled() {
      return this.account === "" || this.isGetCodeBtnDisable;
    }
  },
  methods: {
     
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
            console.log('激活账号手机验证:::获取验证码:::验证通过');
            this.$router.push({ path: '/ChangePwd'});
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
          mailOrPhone: this.user_loginInfo.userType === 1? this.auth_nationCode + this.user_loginInfo.account : this.user_loginInfo.account,
          type:this.user_loginInfo.userType,
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
@import "./../Auth/_auth";
.phone-verify {
  display: flex;
  flex-direction: column;
  height: auto;
  position: relative;
  margin: 0 auto;
  .phone-verify-page {
    width: 90%;
    margin: 0 auto;
    .verify-tip{
      padding-right: 5px;
      height:25px;
    }
  }
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
    .nationCode-phone{
      width:81%;
      margin:  auto;
      margin-bottom: 10px;
      h3{
        text-align: center;
        margin-top:10px;
      }
      .input-size{
        width:57%;
        padding-right: 5px;
      }
    .ver-code{
      position: relative;
      right:47px;
      }
   }
    
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
    margin-bottom: 13px;
     span {
       padding: 0 5px;
       cursor: pointer;
     }
    }
  }

</style>
