/**
 * @file      Manage the auth's api.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class AuthService {
  constructor(client, utils) {
    this._auth = client.authService();
    this._utils = utils;
  }

  login(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.login(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  logout(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.logout(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  autoLogin(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.autoLogin(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  offlinelogin(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.offlinelogin(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  offLineToLogin(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.offLineToLogin(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  prelogin(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.prelogin(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  abortLogin(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.abortLogin(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  verifyImgCode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.verifyImgCode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  signup(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.signup(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setNameAndPasswd(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.setNameAndPasswd(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getqVerifyCodes(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getqVerifyCodes(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getRegCode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getRegCode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  quickRegister(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.quickRegister(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  bindMail(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.bindMail(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getBindPhoneCode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getBindPhoneCode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  bindPhone(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.bindPhone(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  changePassword(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.changePassword(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getPasswordRule(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getPasswordRule(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getResetPwCode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getResetPwCode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getSecUrl(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getSecUrl(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  resetPassword(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.resetPassword(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getCertOutDate() {
    return this._auth.getCertOutDate();
  }

  getCertOutDateAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._auth.getCertOutDate();
      resolve(resp);
    });
  }

  getClientKey(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getClientKey(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  checkOrRefreshAccessToken(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.checkOrRefreshAccessToken(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getAuthAccessToken(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getAuthAccessToken(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getAuthUserBean(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getAuthUserBean(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getLoginAuthCode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getLoginAuthCode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getWebSiteAuth(param, cb) {
    return new Promise((resolve, reject)=>{
      this._auth.getWebSiteAuth(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  regDbUpdated(param, cb) {
    this._auth.regDbUpdated(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regNetChangedCb(param, cb) {
    this._auth.regNetChangedCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regReLoginCb(param, cb) {
    this._auth.regReLoginCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regUpgrageCb(param, cb) {
    this._auth.regUpgrageCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
}
module.exports = AuthService;