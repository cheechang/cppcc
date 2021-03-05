<template>
<v-modal>
  <div class="activate-account">
    <headerTip :headerName="$t('account.changePwd')"></headerTip>
    <v-tip class="session-item">
      <v-input
        class="inputs"
        hasLine
        hasLabel
        v-model="oldPwd"
        :type="'password'"
        :customType="'input-size'"
        :isBorder="false"
        :maxlength="24"
        :placeholder="$t('auth.currentPassword')"
      ></v-input>
    </v-tip>
    <v-tip class="session-item">
      <v-input
        class="inputs"
        hasLine
        hasLabel
        v-model="newPwd"
        :type="'password'"
        :customType="'input-size'"
        :isBorder="false"
        :maxlength="24"
        :placeholder="$t('auth.newPassword')"
      ></v-input>
    </v-tip>
    <v-tip
      class="session-item"
      :tipLabelMsg="errorMsg"
      :isLabelTip="isErrorBox"
      @close="isErrorBox = false"
    >
      <v-input
        class="inputs"
        hasLine
        hasLabel
        v-model="confirmPwd"
        :type="'password'"
        :customType="'input-size'"
        :isBorder="false"
        :maxlength="24"
        :placeholder="$t('auth.confirmPassword')"
        @keyup-enter='activate'
      ></v-input>
    </v-tip>
    <div class="pwd-rule">{{ruleMsg}}</div>
    <div class="loginTip pwd-rule">{{$t('auth.prompt')}}:{{$t('auth.pageTransition')}}</div>
    <v-btn
        class="auth-button"
        :size="'v-button--max_width'"
        :disable="isDisable"
        :type="loadingState"
        @click="activate"
      >{{$t('auth.activate')}}</v-btn>
    <div class="back-login">
      <span @click="cancel" class="txt-link">{{$t('auth.cancelLogin')}}</span>
    </div>

  </div>
    <!-- <v-modal v-if="alertCardModal" :cardStyle="alertCardStyle">
      <div class="box-title theme-bgc_font">提示</div>
      <div class="modal-card-body">
        <p class="card-body-font">即将跳转到登陆页面，请用新密码登录 3s</p>
      </div>
    </v-modal> -->
  </v-modal>
</template>
<script>
import { mapGetters } from 'vuex';
import vTip from '../Auth/common/tooltip.vue';
import vBtn from '../Auth/common/button.vue';
import headerTip from './HeaderTip.vue';
import ActivateMixin from "./ActivateMixins.js"
import { getPwdRuleString, analysisPwdRule, getErrorMsg } from '../../utils/utils.js';
import { setInterval } from 'timers';
export default {
  mixins:[ActivateMixin],
  components: {
    vTip,
    vBtn,
    headerTip
  },
  data() {
    return {
      oldPwd: '',
      newPwd: '',
      confirmPwd: '',
      ruleMsg: '',
      isLoading: false,
      errorMsg: '',
      isErrorBox: false,
      rule: null,
      alertCardStyle:{
        width: '330px',
        height: '125px',
        borderRadius: '4px'
      },
    }
  },
  computed: {
    ...mapGetters(['pwd_rule', 'auth_server']),
    loadingState() {
      return this.isLoading ? 'is-loading' : '';
    },
    isDisable() {
      return this.newPwd === '' || this.oldPwd === '' || this.confirmPwd === '';
    }
  },
  created() {
    this.$Service.log(`激活账号获取密码规则:::${this.auth_server}`);
    this.$Service.auth.getPasswordRule({server: this.auth_server}, this._getPasswordRuleHandler);
  },
  methods:{
    // 激活账号
    activate(){
      this.isLoading = true;
      if (!this.checkPassword()) {
        this.isErrorBox = true;
        this.isLoading = false;
        return;
      }
      if(this.oldPwd === this.newPwd){
        this.isErrorBox = true;
        this.isLoading = false;
        this.errorMsg = this.$t('auth.pwdCantSame')
        return;
      }
      let changePasswordParam = {
        oldPw: this.oldPwd,
        newPw: this.newPwd
      };
      this.$Service.log(`账号激活:入参:${JSON.stringify(changePasswordParam)}`);
      this.$Service.auth.changePassword(changePasswordParam, this._changePasswordHandler);
    },
    checkPassword() {
      if (this.confirmPwd !== this.newPwd) {
        this.errorMsg = this.$t('auth.confirmPwdFormat')
        return false;
      }
      if (analysisPwdRule(this.rule, this.newPwd)) {
        return true;
      }
      this.errorMsg = this.$t('auth.newPwdFormat')
      return false;
    },
    _changePasswordHandler(resp){
      this.$Service.log(`账号激活:返回:${resp.code}`);
      this.isLoading = false;
      if (resp.code !== 0) {
        this.$Service.log(`账号激活失败:返回:${resp.code}`);
        this.errorMsg = getErrorMsg(resp.code);
        this.isErrorBox = true;
        return;
      }
      
      this.$Service.auth.logout(null, resps => {
        this.$Service.log(`账号激活:调用登出接口返回:${JSON.stringify(resps)}`);
        this.$ipc.send('tray-logout');
      });
      this.$router.push({ path: '/Login'});
    },
    _getPasswordRuleHandler(resp) {
      this.$Service.log(`激活账号获取密码规则:::${resp.code}`);
      this.rule = resp;
      this.ruleMsg = getPwdRuleString(this.rule);
      },

  }
}
</script>
<style lang="scss">
@import './../Auth/_auth';
.activate-size{
  width: 300px;
  height: auto;
  .modal-card{
    width:250px;
    transition:1s;
  }
  
}
.input-tip:not(:last-child) {
  margin-bottom: 0!important;
}
.activate-account{
  display: flex;
  flex-direction: column;
  width: 90%;
  margin: 0 auto;
  height: auto;
  position: relative;
  .auth-font{
    font-size: $--font-size-mid;
  }
  .session-item{
    width: 100%;
    margin: 5px 0;
    .session-inp-title{
      padding-top: 7px;
      width: 80px;
      font-size: $--font-size-mid;
    }
  }
  .pwd-rule{
    padding: 11px 0 0px 0;
    font-size: $--font-size-small;
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

.box-title{
    padding: 6px 10px;
    display: flex;
    justify-content: space-between;
    font-size:16px;
}
.card-body-font{
    color: #4a4a4a;
    font-size: 1rem;
    font-weight: 400;
    line-height: 84px;
    padding-left:20px; 
}
</style>