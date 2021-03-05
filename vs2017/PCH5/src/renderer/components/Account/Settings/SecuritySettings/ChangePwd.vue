<template>
	<div class="change-pwd">
    <span class="suer-sett-loading sett-loading-1" v-if="isLoading">
      <i class="icon loading-start" v-if="isDoing">&#xe6ac;</i>
      <i class="icon loading-success" v-if="!isDoing">&#xe632;</i>
    </span>
		<div v-if="!auth_loginByForgetPwd.isForgetPwdLogin" class="change-pwd-item ">
			<v-field class="fields">
				<input
          class="input-style"
          v-model="oldPwd"
          :customType="'input-size'"
          type="password"
          :placeholder="$t('account.oldPwd')"
          :maxlength="16"
        >
			</v-field>
		</div>
		<div class="change-pwd-item">
			<v-field class="fields">
				<input
          class="input-style"
          v-model="newPwd"
          :customType="'input-size'"
          type="password"
          :placeholder="$t('account.setNewPwd')"
          :maxlength="16"
        >
      </v-field>
		</div>
		<div class="change-pwd-item confirm-pwd">
			<v-field class="fields">
				<input
        class="input-style"
        v-model="confirmPwd"
        size="is-small"
        :customType="'input-size'"
        type="password"
        :placeholder="$t('account.repNewPwd')"
        :maxlength="16"
      >
			</v-field>
		</div>
    <div class="warn-info">{{ruleMsg}}</div>
		<div class="change-pwd-item">
			<v-button 
        class="confirm-change" 
        :class="{'theme-botton':!isDisable}"
        :disable="isDisable"
        @click="changePwd"
      >{{$t('common.confirm')}}</v-button>
		</div>
	</div>
</template>
<script>
import { mapGetters } from 'vuex';
import userMixin from './../../AccountMixin.js';
import { getPwdRuleString, analysisPwdRule, getErrorMsg } from '../../../../utils/utils.js';
export default {
  data() {
    return {
      oldPwd: '',
      newPwd: '',
      confirmPwd: '',
      ruleMsg: '',
      isLoading: false,
      isDoing: false,
      errorMsg: ''
    };
  },
  mixins: [userMixin],
  computed: {
    ...mapGetters([
      'pwd_rule',
      'auth_server',
      'user_account',
      'auth_loginByForgetPwd'
    ]),
    isDisable() {
      if (this.auth_loginByForgetPwd.isForgetPwdLogin) {
        return this.newPwd === '' || this.confirmPwd === '';
      }
      return this.newPwd === '' || this.oldPwd === '' || this.confirmPwd === '';
    }
  },
  created() {
    this.$Service.auth.getPasswordRule({server: this.auth_server}, this._getPasswordRuleHandler);
  },
  methods: {
    // 验证密码是否符合规则
    checkPassword() {
      if (this.newPwd === this.oldPwd && !this.auth_loginByForgetPwd.isForgetPwdLogin) {
        this.errorMsg = this.$t('account.newAndOld');
        return false;
      }
      if (this.confirmPwd !== this.newPwd) {
        this.errorMsg = this.$t('auth.confirmPasswordError');
        return false;
      }
      if (analysisPwdRule(this.rule, this.newPwd)) {
        return true;
      }
      this.errorMsg = this.$t('auth.newPwdFormat');
      return false;
    },

    // 修改密码
    changePwd(){
      this.isLoading = true;
      this.isDoing = true;
      if (!this.checkPassword()) {
        this.errPromptBox(this.errorMsg,'is-danger');
        this.isLoading = false;
        return;
      }
      let changePwdParam = {
        oldPw: this.oldPwd,
        newPw: this.newPwd
      };
      let setNamePwdParam = {
        passwd: this.newPwd,
        name: this.user_account.name
      };
      this.$Service.log(`修改密码:入参:${JSON.stringify(changePwdParam)}`);
      if (this.auth_loginByForgetPwd.isForgetPwdLogin) {
        this.$Service.auth.setNameAndPasswd(setNamePwdParam, this._changePasswordHandler);
        return
      }
      this.$Service.auth.changePassword(changePwdParam, this._changePasswordHandler);
    },
    _changePasswordHandler(resp){
      this.isLoading = false;
      this.$Service.log(`修改密码:返回:${resp.code}`);
      this.isLoading = false;
      if (resp.code !== 0) {
        this.errPromptBox(getErrorMsg(resp.code),'is-danger');
        return;
      }
      if (this.auth_loginByForgetPwd.isChangePwd) return; //处理baqi服务器上,修改密码时,在线状态推送flag为7的推送比此回调快
      this.$store.commit('SET_LOGIN_BY_FORGETPWD', {flag: 3, val: true});
      this.$dialog.alert({
        message: this.$t('account.pwdChangeSuccTip'),
        confirmText: this.$t('common.confirm'),
        onConfirm: () => {
          // localStorage.removeItem('is-regDialog');
          this.$ipc.send('tray-logout');
          this.$ipc.send('close-all-subWin');
          // this.auth_loginByForgetPwd.isForgetPwdLogin
        }
      })
    },

    // 忘记密码登录状态使用此接口

    _getPasswordRuleHandler(resp) {
      this.$Service.log(`激活账号获取密码规则返回:::${resp.code}`);
      this.rule = resp;
      this.ruleMsg = getPwdRuleString(this.rule);
    }
  }
};
</script>
<style lang="scss" scoped>
.input-tip:not(:last-child) {
	margin-bottom: 0!important;
}
.change-pwd {
  position: relative;
  .sett-loading-1{
    position: absolute;
    top: -17px;
    left: -28px;
  }
  .change-pwd-item {
		width: 100%;
		padding: 3px 0;
		display: flex;
		.fields{
			width: 35%;
			position: relative;
			.icon{
				position: absolute;
				right: 5px;
				top: 10px;
				font-size: $--font-size-mid;
			}
			.level-left {
				.affirm {
					height: 30px;
					font-size: $--font-size-mid;
				}
			}
			.input-style {
				height: 30px;
				width: 100%;
				border: 0;
				border-radius: $--border-radius-base;
				outline: none;
				background: #d3d3d3;
				padding-left: 10px;
				font-size: $--font-size-small;
			}
		}
		.complexity {
			display: flex;
			justify-content: flex-start;
			width: 320px;
			height: 30px;
			.pwd-complexity {
				height: 5px;
				width: 50%;
				display: flex;
				justify-content: space-between;
				margin-top: 13px;
				.pwd-bar {
					// display: inline-block;
					background: #dbdbdb;
					margin: 0 3px;
					height: 5px;
					// position: absolute;
					width: 90px;
				}
			}
		}	
    .confirm-change {
      height: 30px;
			color: $--color-white;
			width: 85px;
			padding: 5px 0;
			text-align: center;
			border: 0;
      outline: none;
      font-size: $--font-size-mid;
			border-radius: $--border-radius-base;
		}
  }
  .warn-info {
    padding: 3px 0;
  }
}
</style>
