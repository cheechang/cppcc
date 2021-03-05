<template>
  <div class="register-page">
    <!-- 服务器 -->
    <v-tip>
      <v-input
        class="inputs"
        v-model="server"
        :type="'text'"
        :isBorder="false"
        hasLine
        :maxlength="50"
        :isAuth="false"
        :inputLineSite="'-1px'"
        :placeholder="$t('auth.server')"
      >
      </v-input>
    </v-tip>
    <!-- 国家码/手机号 -->
    <v-tip
      class="tip-table"
      hasLine
      :isLightLine="isLightLine"
    >
      <div class="nation-code">
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
      >
      </v-input>
      <transition name="zoom-in-top">
        <div
          v-if="!isOptionHide" 
          class="option-list boxshadow-0"
          v-click-outside="onClickOutside"
        >
          <div
            class="nation-item"
            v-for="(item, index) in originArray"
            :key="index"
            @click="selected(item, index)"
          >{{index}}</div>
        </div>
      </transition>
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
        :isAuth="false"
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
    <!-- 选择已有账号 -->
    <div class="more-button-layout already-account">
      <span class="txt-link" @click="gotoBack">{{$t('auth.cancelSignUp')}}</span>
      <span class="vertical-line"></span>
      <span class="txt-link" @click="gotoLogin">{{$t('auth.signined')}}</span>
    </div>
    <!-- 获取服务器说明 -->
    <div class="auth-description" v-if="clientConfig_auth.openServerIntro">
      <p>{{$t('auth.getServiceWay')}}：</p>
      <p>{{$t('auth.enterprise')}}</p>
      <p>{{$t('auth.individual')}}</p>
    </div>
  </div>
</template>

<script>
import Vue from 'vue';
import { mapGetters } from "vuex";
import vTip from "./../common/tooltip.vue";
import vBtn from "./../common/button.vue";
import vClickOutside from "./../../Chat/v-click-outside/index.js";
import { getErrorMsg } from '../../../utils/utils.js';
export default {
  name: 'register-page',
  components: {
    vTip,
    vBtn
  },
  directives: {
    clickOutside: vClickOutside.directive
  },
  data() {
    return {
      server: '',
      nationCode: '+86',
      account: '',
      isLightLine: false,
      isOptionHide: true,
      verifyCode: '',
      regCode: this.$t('auth.getVerifyCode'),
      isLoading: false,
      isCodeLoading: false,
      isCodeSend: false,
      errorMsg: '',
      isErrorBox: false,
      isSuccess: false,
      isGetCodeBtnDisable: false,
      clock: 0,
      userId: '',
      isNewServer: false
    }
  },
  computed: {
    ...mapGetters(['auth_nationCode','clientConfig_auth']),

    // 国家码下拉按钮数据
    originArray() {
      return this.$i18n.messages[`${this.$i18n.locale}`].AreaCode;
    },

    // 加载动画显示
    lodingState() {
      return this.isLoading ? 'is-loading' : '';
    },

    // 获取验证码等待动画
    codelodingState() {
      return this.isCodeLoading ? 'is-loading' : '';
    },

    // 下一步按钮可点击状态
    isDisable() {
      return (
        this.server !== '' && this.account !== '' && this.verifyCode !== '' && this.isCodeSend);
    },

    // 获取验证码按钮能否点击
    isCodeDisabled() {
      return this.account === '' || this.isGetCodeBtnDisable || this.server === '';
    }
  },
  watch: {
    isOptionHide(val) {
      console.log(val);
      val ? this.$emit('is-nodrag', false) : this.$emit('is-nodrag', true);
    },
    $route(to, from) {
      if (
        (from.path === '/Login' || from.path === '/PreLogin' || from.path === '/LoginInitPage')&&
        to.path === '/first'
      ) {
        console.log('is init form for back');
        if (this.clock === 0) {
          this.server = this.$route.query.server;
          this.nationCode = this.auth_nationCode === '' ? this.$Service.config.getSystemNationCode() : this.auth_nationCode;
          this.account = '';
          this.verifyCode = '';
        }
      }
    }
  },
  created() {
    this.nationCode = this.auth_nationCode === '' ? this.$Service.config.getSystemNationCode() : this.auth_nationCode;
    this.server = this.$route.query.server;
    console.log(this.server);
  },
  methods: {
    // 点击列表外部区域关闭下拉列表
    onClickOutside() {
      this.isOptionHide = true;
    },

    // 选择国家/地区
    selected(item, index) {
      this.nationCode = item;
      this.isOptionHide = true;
    },

    // 下一步
    next() {
      /**
       * 1. 下一步加载等待过程中禁止再次点击
       * 2. 匹配验证码格式
       */
      if (this.isLoading) return;
      let verRule = /^[0-9a-zA-Z]*$/g;
      if(!verRule.test(this.verifyCode)) {
        this.isErrorBox = true;
        this.errorMsg = this.$t('auth.codeEmpty');
        this.isSuccess = false;
        return
      }
      this.signup();
    },

    /**
     * 通过获取的验证码登录账号
     * 登录成功后调用设置用户信息接口设置密码/名字的
     */
    signup() {
      this.isLoading = true;
      let param = {
        regCode: this.verifyCode,
        account: this.nationCode + this.account 
      };
      this.$Service.log(`注册:::新服务注册:::入参:::${JSON.stringify(param)}`);
      this.$Service.auth.signup(param, this._signupHandler);
    },
    _signupHandler(resp) {
      this.$Service.log(`注册:::新服务注册:::返回:::${JSON.stringify(resp)}`);
      this.isLoading = false;
      if (resp.code !== 0) {
        this.errorMsg = getErrorMsg(resp.code)
        this.isErrorBox = true;
        this.isSuccess = false;
        return;
      }
      //  获取密码规则
      this.userId = resp.userId;
      this.$Service.auth.getPasswordRule({server: this.server}, this._getPasswordRuleHandler);
      //  设置登录历史
      this.setLoginData();
    },
    setLoginData() {
      let info = {
        userId: this.userId,
        account: this.account,
        isAutoLogin: 0,
        isRemberPass: 0,
        nation: this.nationCode,
        userType: 1,
        server: this.server,
        last_login_time: new Date().getTime().toString(),
        name: '',
        user_icon: ''
      };

      //  先将登录信息存入vuex中，等待获取到用户信息后统一存入数据库
      this.$store.commit('SET_LOGININFO', Object.assign({}, info));
      this.$store.commit('SET_USER_LOCALCONFIG', { key: 'userServer_for_auth_request', value: this.server });
 
      Vue.prototype.$userver = this.server;
    },

    _getPasswordRuleHandler(resp) {
      this.$Service.log(`激活账号获取密码规则:::${resp.code}`);
      console.log('isOldServer isNewServer:::', this.isNewServer);
      this.isLoading = false;
      this.$router.push({path: '/second', query: {userId:this.userId, pwdRule: resp, server:this.server}});
    },

    gotoBack() {
      this.$router.go(-1)
    },

    gotoLogin() {
      this.$router.push({path: '/Prelogin'})
    },

    // 点击获取验证码
    getRegCode() {
      let phoneRule = /^[0-9]{5,18}$/g;
      if(!phoneRule.test(this.account)) {
        this.isErrorBox = true;
        this.errorMsg = this.$t('ErrorCode.388');
        this.isSuccess = false;
        return
      }

      // 显示加载动画
      this.isCodeLoading = true;
      // 禁用按钮点击
      this.isGetCodeBtnDisable = true;
      // 调用预登陆接口，判断是否可注册
      this.$Service.auth.prelogin(
        { server: this.server },
        resp => {
          this.$Service.log(`注册:::获取预登陆信息:::返回json:::${JSON.stringify(resp)}`);
          if (resp.code !== 0 || resp === undefined || resp.json === undefined || resp.json === '') {
            this.errorMsg = getErrorMsg(resp.code);
            this.isErrorBox = true;
            this.isLoading = false;
            this.isGetCodeBtnDisable = false;
            this.isCodeLoading = false;
            return;
          }
          let obj = JSON.parse(resp.json);
          console.log('obj:::', obj);

          //  获取服务器版本号
          let serverVersion = obj.ServerVersion || obj.serverVersion;
          this.$Service.log(`注册:::服务器版本号:::${serverVersion}`);
          this.$store.commit('SET_SERVERVERSION', serverVersion);

          //  判断是否允许注册
          let isRegisterEnabled = (obj.systemConfig & 1) === 1;
        
          if (!isRegisterEnabled) {
            this.errorMsg = this.$t('auth.notAllowed');
            this.isErrorBox = true;
            this.isSuccess = false;
            this.isCodeLoading = false;
            this.isGetCodeBtnDisable = false;
            this.clearClock();
            return;
          };
          console.log('nation::', this.nationCode);
          let param = {
            account: this.nationCode + this.account,
            server: this.server,
            type: 1
          }
          // let nameReg = /^.{1,24}$/;

          this.$Service.log(`注册:::获取验证码:::入参:::${JSON.stringify(param)}`);
          this.$Service.auth.getRegCode(param, this._getRegCodeHandler);
        }
      )
    },

    // 获取验证码回调
    _getRegCodeHandler(resp) {
      this.$Service.log(`注册:::获取验证码:::返回:::${JSON.stringify(resp)}`);
      this.isCodeLoading = false;
      if (resp.code !== 0) {
        //  错误处理
        this.isGetCodeBtnDisable = false;
        this.errorMsg = getErrorMsg(resp.code);
        this.isErrorBox = true;
        return;
      }
      //  成功后需要提示
      this.errorMsg = this.$t('auth.verCodeSent');
      this.isErrorBox = true;
      this.isSuccess = true;
      this.regCode = `${resp.time}s`;
      this.clock = setInterval(() => {
        resp.time--;
        this.regCode = resp.time + "s";
        if (resp.time < 1) {
           //  TODO: 倒计时结束后取消禁用
           this.clearClock();
        }
      }, 1000);
      this.isCodeSend = true;
    },
    clearClock() {
      clearInterval(this.clock);
      console.log('clear close::', this.clock);
      this.clock = 0;
      this.regCode = this.$t('auth.getVerifyCode');
      this.isGetCodeBtnDisable = false;
    }
  }
};
</script>

<style lang="scss">
@import "./../_auth";
.register-page {
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
        bottom: 7px;
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
  // .btn-disable {
  //   color: get-grey-color(lighten-1);

  //   &:hover {
  //     background: $--color-white;
  //     color: get-grey-color(lighten-1);
  //   }
  // }
  .already-account {
    font-size: $--font-size-small;
    justify-content: flex-start;
    padding-left: 68px;
  }
  .auth-button {
    margin: 15px 0 0 0;
  }
}
</style>
