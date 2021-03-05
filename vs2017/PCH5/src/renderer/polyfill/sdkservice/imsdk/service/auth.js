import Service from './service';
export default class AuthService extends Service {
  constructor() {
    super("auth");
  }

  getRSA(param, cb) {
    this._process("getRSA", param, cb);
  }

  login(param, cb) {
    this._process("login", param, cb);
  }

  prelogin(param, cb) {
    this._process("prelogin", param, cb);
  }

  logout(param, cb) {
    this._process("logout", param, cb);
  }

  autoLogin(param, cb) {
    this._process("autoLogin", param, cb);
  }

  offlinelogin(param, cb) {
    this._process("offlinelogin", param, cb);
  }

  offLineToLogin(param, cb) {
    this._process("offLineToLogin", param, cb);
  }

  abortLogin(param, cb) {
    this._process("abortLogin", param, cb);
  }

  verifyImgCode(param, cb) {
    this._process("verifyImgCode", param, cb);
  }

  signup(param, cb) {
    this._process("signup", param, cb);
  }

  signupOld(param, cb) {
    this._process("signupOld", param, cb);
  }

  setNameAndPassword(param, cb) {
    this._process("setNameAndPassword", param, cb);
  }

  getqVerifyCodes(param, cb) {
    this._process("getqVerifyCodes", param, cb);
  }

  getRegCode(param, cb) {
    this._process("getRegCode", param, cb);
  }
  
  quickRegister(param, cb) {
    this._process("quickRegister", param, cb);
  }

  bindMail(param, cb) {
    this._process("bindMail", param, cb);
  }

  getBindPhoneCode(param, cb) {
    this._process("getBindPhoneCode", param, cb);
  }

  bindPhone(param, cb) {
    this._process("bindPhone", param, cb);
  }

  changePassword(param, cb) {
    this._process("changePassword", param, cb);
  }

  getPasswordRule(param, cb) {
    this._process("getPasswordRule", param, cb);
  }

  getResetPwCode(param, cb) {
    this._process("getResetPwCode", param, cb);
  }

  getSecUrl(param, cb) {
    this._process("getSecUrl", param, cb);
  }

  resetPassword(param, cb) {
    this._process("resetPassword", param, cb);
  }

  getCertOutDate() {
    return "";  //  TODO: 实现同步方式
  }

  getClientKey(param, cb) {
    this._process("getClientKey", param, cb);
  }

  checkOrRefreshAccessToken(param, cb) {
    this._process("checkOrRefreshAccessToken", param, cb);
  }

  getAuthAccessToken(param, cb) {
    this._process("getAuthAccessToken", param, cb);
  }

  getAuthUserBean(param, cb) {
    this._process("getAuthUserBean", param, cb);
  }

  getLoginAuthCode(param, cb) {
    this._process("getLoginAuthCode", param, cb);
  }

  getWebSiteAuth(param, cb) {
    this._process("getWebSiteAuth", param, cb);
  }

  regDbUpdated(param, cb) {
    this._process("regDbUpdated", param, cb);
  }

  regNetChangedCb(param, cb) {
    this._process("regNetChangedCb", param, cb);
  }

  regReLoginCb(param, cb) {
    this._process("regReLoginCb", param, cb);
  }

  regUpgrageCb(param, cb) {
    this._process("regUpgrageCb", param, cb);
  }
}