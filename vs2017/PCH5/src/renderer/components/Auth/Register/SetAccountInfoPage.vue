<template>
  <div class="account-info">
    <!-- 用户名 -->
    <v-tip>
      <v-input
        class="inputs"
        v-model="user"
        :type="'text'"
        :isBorder="false"
        hasLine
        :maxlength="'20'"
        :isAuth="true"
        :inputLineSite="'-1px'"
        :placeholder="$t('auth.userName')"
      >
      </v-input>
    </v-tip>
    <!-- 密码 -->
    <v-tip>
      <v-input
        class="inputs"
        v-model="password"
        :type="isPwd?'password':'text'"
        :isBorder="false"
        hasLine
        :maxlength="20"
        :isAuth="true"
        :inputLineSite="'-1px'"
        :placeholder="$t('auth.pwd')"
      >
        <i
          slot="expand"
          @click="showPwd"
          class="icon show-pwd"
          :style="{color: isPwd?'':'#1565C0'}"
        >&#xe68f;</i>
      </v-input>
    </v-tip>
    <!-- 确认密码 -->
    <v-tip
      :tipLabelMsg="errorMsg"
      :isLabelTip="isErrorBox"
      @close="isErrorBox = false"
    >
      <v-input
        class="inputs"
        v-model="confirmPwd"
        :type="isPwd?'password':'text'"
        :isBorder="false"
        hasLine
        :isAuth="true"
        :inputLineSite="'-1px'"
        :maxlength="20"
        :placeholder="$t('auth.confirmPassword')"
      >
      </v-input>
    </v-tip>
    <div class="pwd-rule">{{pwdRuleTip}}</div>
    <v-btn
      class="auth-button"
      :size="'v-button--max_width'"
      :disable="isDisable"
      :type="lodingState"
      @click="register"
    >{{$t('auth.register')}}</v-btn>
    <!-- 返回 -->
    <div class="back-login">
      <span @click="goBack" class="txt-link">{{$t('auth.goBack')}}</span>
    </div>
  </div>
</template>

<script>
import vTip from "./../common/tooltip.vue";
import vBtn from "./../common/button.vue";
import LoginMixins from './../Login/LoginMixins.js'
import { getPwdRuleString, analysisPwdRule, getErrorMsg } from '../../../utils/utils.js';
export default {
  name: 'account-info',
  mixins: [LoginMixins],
  components: {
    vTip,
    vBtn
  },
  data() {
    return {
      user: '',
      password: '',
      confirmPwd: '',
      isLoading: false,
      errorMsg: '',
      isErrorBox: false,
      pwdRuleTip: '',
      pwdRule: null,
      userId: '',
      server: '',
      isPwd: true
    }
  },
  computed: {
    // 下一步按钮可点击状态
    isDisable() {
      return this.user === '' || this.password === '' || this.confirmPwd === '';
    },
    // 加载动画显示
    lodingState() {
      return this.isLoading ? 'is-loading' : '';
    }
  },
  activated() {
    //  接收传来的userid和密码规则
    this.pwdRule = this.$route.query.pwdRule;
    this.userId = this.$route.query.userId;
    this.server = this.$route.query.server;
    this.pwdRuleTip = getPwdRuleString(this.pwdRule);
  },
  methods: {
    // 显示隐藏密码
    showPwd() {
      this.isPwd = !this.isPwd
    },
    // 注册
    register() {
      if (this.isLoading) return;
      this.isLoading = true;
      // 校验密码规则
      if (!analysisPwdRule(this.pwdRule, this.password)) {
        this.isErrorBox = true;
        this.errorMsg = this.$t('auth.pwdFormatError');
        this.isLoading = false;
        return;
      }
      if (this.confirmPwd !== this.password) {
        this.isErrorBox = true;
        this.errorMsg = this.$t('auth.confirmPasswordError');
        this.isLoading = false;
        return;
      }
      let param = {
        name: this.user,
        passwd: this.password
      };
      this.$Service.log(`注册:::新服务设置用户名/密码:::入参:::${JSON.stringify(param)}`);
      this.$Service.auth.setNameAndPasswd(param, this._setNameAndPasswdHandler);
    },
    _setNameAndPasswdHandler(resp) {
      this.$Service.log(`注册:::新服务设置用户名/密码:::返回:::${JSON.stringify(resp)}`);
      //  设置后不论是否成功都跳转至主页面
      // this.$router.push({path: '/Chat'});
      this.$Service.auth.prelogin(this.server, this._handlePreLogin);
      this.$ipc.send('login-successed');
    },
    // 返回时调用登出接口
    goBack() {
      this.$Service.auth.logout(null, resps => {});
      this.$router.go(-1);
    }
  }
}
</script>

<style lang="scss" scoped>
.account-info{
  .show-pwd{
    font-size: 9px;
    margin-top: 7px;
    pointer-events: auto;
  }
  .pwd-rule{
    padding: 11px 0 0px 0;
    font-size: $--font-size-small;
  }
  .back-login {
    display: flex;
    justify-content: center;
    padding-top: 15px;
    font-size: $--font-size-small;
    span {
      padding: 0 5px;
      cursor: pointer;
    }
  }
}
</style>
