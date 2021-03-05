import Service from "./service";

export default class ConfigService extends Service {
  constructor() {
    super("config");
  }

  getAutoStart(param, cb) {
    this._process("getAutoStart", param, cb);
  }

  getIsRoming(param, cb) {
    this._process("getIsRoming", param, cb);
  }

  getSystemNationCode() {
    return '';
  }

  getLastPreLoginData(param, cb) {
    this._process("getLastPreLoginData", param, cb);
  }

  getLoginExDataAsync(param, cb) {
    this._process("getLoginExDataAsync", param, cb);
  }

  getLoginInfos(param, cb) {
    this._process("getLoginInfos", param, cb);
  }

  getMultiChannelAddress(param, cb) {
    this._process("getMultiChannelAddress", param, cb);
  }

  getMultiChannelAddressAsync(param, cb) {
    this._process("getMultiChannelAddressAsync", param, cb);
  }

  getNetProxy(param, cb) {
    this._process("getNetProxy", param, cb);
  }

  getPreloginInfoEx(param, cb) {
    this._process("getPreloginInfoEx", param, cb);
  }

  getSdkVersion(param, cb) {
    this._process("getSdkVersion", param, cb);
  }

  getSubServerInfo(param, cb) {
    this._process("getSubServerInfo", param, cb);
  }

  getUserTypeById(param, cb) {
    this._process("getUserTypeById", param, cb);
  }

  headImgPath(param, cb) {
    this._process("headImgPath", param, cb);
    return { path: "" };
  }

  rootPath(param, cb) {
    this._process("rootPath", param, cb);
    return { path: "" };
  }

  userAudioPath(param, cb) {
    this._process("userAudioPath", param, cb);
    return { path: "" };
  }

  userCachePath(param, cb) {
    this._process("userCachePath", param, cb);
    return { path: "" };
  }

  userEmotionPath(param, cb) {
    this._process("userEmotionPath", param, cb);
    return { path: "" };
  }

  userFilePath(param, cb) {
    this._process("userFilePath", param, cb);
    return {path: ""};
  }

  userImgPath(param, cb) {
    this._process("userImgPath", param, cb);
    return { path: "" };
  }

  userVideoPath(param, cb) {
    this._process("userVideoPath", param, cb);
    return { path: "" };
  }

  getMsgParserMode(param, cb) {
    this._process("getMsgParserMode", param, cb);
  }

  setAppName(param, cb) {
    this._process("setAppName", param, cb);
  }

  setAppVersion(param, cb) {
    this._process("setAppVersion", param, cb);
  }

  setAutoStart(param, cb) {
    this._process("setAutoStart", param, cb);
  }

  setCertificatePath(param, cb) {
    this._process("setCertificatePath", param, cb);
  }

  setHttpsLogin(param, cb) {
    this._process("setHttpsLogin", param, cb);
  }

  setInterConnect(param, cb) {
    this._process("setInterConnect", param, cb);
  }

  setIsRoming(param, cb) {
    this._process("setIsRoming", param, cb);
  }

  setLanguage(param, cb) {
    this._process("setLanguage", param, cb);
  }

  setLanguageType(param, cb) {
    this._process("setLanguageType", param, cb);
  }

  setLoginInfo(param, cb) {
    this._process("setLoginInfo", param, cb);
  }

  setLogLevel(param, cb) {
    this._process("setLogLevel", param, cb);
  }

  setMsgParserMode(param, cb) {
    this._process("setMsgParserMode", param, cb);
  }

  setMultichannel(param, cb) {
    this._process("setMultichannel", param, cb);
  }

  setNetProxy(param, cb) {
    this._process("setNetProxy", param, cb);
  }

  setNetStatus(param, cb) {
    this._process("setNetStatus", param, cb);
  }

  setNotifyStatus(param, cb) {
    this._process("setNotifyStatus", param, cb);
  }

  setOffloginSwitch(param, cb) {
    this._process("setOffloginSwitch", param, cb);
  }

  setPlugPower(param, cb) {
    this._process("setPlugPower", param, cb);
  }

  setPwIsCrypt(param, cb) {
    this._process("setPwIsCrypt", param, cb);
  }

  setRootPath(param, cb) {
    this._process("setRootPath", param, cb);
  }

  setSubServerInfo(param, cb) {
    this._process("setSubServerInfo", param, cb);
  }

  setTextCoding(param, cb) {
    this._process("setTextCoding", param, cb);
  }

  setTicket(param, cb) {
    this._process("setTicket", param, cb);
  }

  delLoginInfo(param, cb) {
    this._process("delLoginInfo", param, cb);
  }

  reNotifyData(param, cb) {
    this._process("reNotifyData", param, cb);
  }

  regIsSystemIdleCb(param, cb) {
    this._process("regIsSystemIdleCb", param, cb);
  }

  regTheThridPartyMsgCb(param, cb) {
    this._process("regTheThridPartyMsgCb", param, cb);
  }
}