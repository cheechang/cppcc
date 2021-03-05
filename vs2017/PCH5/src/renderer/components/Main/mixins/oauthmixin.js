/**
 * @file      OAuth业务模块.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.9.10
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 * @mixin
 */
import { mapGetters } from 'vuex';
const mixin = {
  data () {
    return {
      authRequestInfo: null,
    };
  },
  computed: {
    ...mapGetters([
      'user_localConfig'
    ]),
    isShowOAuth() {
      if (!this.user_localConfig.thirdParty_authRequestInfo) {
        return false;
      }
      if (this.user_localConfig.userServer_for_auth_request === this.user_localConfig.thirdParty_authRequestInfo.elogo) {
        this._getAuthCode();
        return true;
      }
      this._switchServer();
      return false;
    },
  },
  methods: {

    _getAuthCode() {
      let param = {
        appId: this.user_localConfig.thirdParty_authRequestInfo.appID,
        operType: 3,
        cliType: 1,
        param: this.user_localConfig.thirdParty_authRequestInfo.appName
      };
      this.$Service.user.getOauthCode(param, this._getOAuthCodeHandler);
    },
    _getOAuthCodeHandler(resp) {
      if (resp.code !== 0) {
        this.responseOAuth(resp.code);
        return;
      }

      if (resp.silentAuth !== 1) {
        //  如果是非静默授权，则打开授权界面
        this.authRequestInfo = resp;
      } else {
        //  静默授权
        //  TODO： ?? VUEX操作是否有效
        this.user_localConfig.thirdParty_authRequestInfo.authCode = resp.authCode;
        this.responseOAuth(resp.code);
      }
    },
    _switchServer() {
      this.$dialog.confirm({
        message: `[${
          this.user_localConfig.thirdParty_authRequestInfo.appName
        }]请求在[${
          this.user_localConfig.thirdParty_authRequestInfo.elogo
        }]服务器进行授权登录,是否切换服务器进行授权?`,
        confirmText: this.$t("common.confirm"),
        cancelText: this.$t("common.cancel"),
        disableClickOutside: true,
        onCancel: () => {
          console.log("onCancel.....");
          this.responseOAuth(-1, true);
        },
        onConfirm: () => {
          this.$ipc.send("close-all-subWin");
        }
      });
    },

    responseOAuth(code, isCancle = false) {
      let authCode = '';
      let msg = '';
      if (code !== 0) {
        msg = 'get_authCode_error';
      }
      if (isCancle) {
        msg = 'user_refuse_auth';
      }
      if (code === 0) {
        authCode = this.authRequestInfo ? this.authRequestInfo.authCode : this.user_localConfig.thirdParty_authRequestInfo.authCode;
      }
      let data = {
        port: this.user_localConfig.thirdParty_authRequestInfo.port,
        code: code.toString(), // -1 或 0
        msg: msg,
        authCode: authCode,
        sdkErrCode: code.toString()
      };

      this.$callPlugin.responseAuthRequest(data);
      this.authRequestInfo = null;
      this.$store.commit('SET_USER_LOCALCONFIG', {
        key: 'thirdParty_authRequestInfo',
        value: ''
      });
    }
  },
};

export default mixin;