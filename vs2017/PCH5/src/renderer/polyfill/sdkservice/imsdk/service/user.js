import Service from './service';

export default class UserService extends Service {
  constructor() {
    super("user");
  }

  getAccountInfo(param, cb) {
    this._process("getAccountInfo", param, cb);
  }

  addLocalSetting(param, cb) {
    this._process("addLocalSetting", param, cb);
  }

  addLocalSettingSync(param, cb) {
    this._process("addLocalSettingSync", param, cb);
    return null;
  }

  addOrDeleteApplication(param, cb) {
    this._process("addOrDeleteApplication", param, cb);
  }

  addOrDeleteCustomEmoticon(param, cb) {
    this._process("addOrDeleteCustomEmoticon", param, cb);
  }

  changeHiddenPasswd(param, cb) {
    this._process("changeHiddenPasswd", param, cb);
  }

  circleOfFriend(param, cb) {
    this._process("circleOfFriend", param, cb);
  }

  createAppRoom(param, cb) {
    this._process("createAppRoom", param, cb);
  }

  deleteLocalSetting(param, cb) {
    this._process("deleteLocalSetting", param, cb);
  }

  deleteLocalSettingSync(param, cb) {
    this._process("deleteLocalSettingSync", param, cb);
    return null;
  }

  delHiddenTarget(param, cb) {
    this._process("delHiddenTarget", param, cb);
  }

  transLocalData(param, cb) {
    this._process("transLocalData", param, cb);
  }

  wakeUp(param, cb) {
    this._process("wakeUp", param, cb);
  }

  getAppInfo(param, cb) {
    this._process("getAppInfo", param, cb);
  }

  getGlobalNoDisturbMode(param, cb) {
    this._process("getGlobalNoDisturbMode", param, cb);
  }

  getHiddenTarget(param, cb) {
    this._process("getHiddenTarget", param, cb);
  }

  getIdByAccount(param, cb) {
    this._process("getIdByAccount", param, cb);
  }

  getInstalledApplication(param, cb) {
    this._process("getInstalledApplication", param, cb);
  }

  getInstalledApplicationSorted(param, cb) {
    this._process("getInstalledApplicationSorted", param, cb);
  }

  getLocalSetting(param, cb) {
    this._process("getLocalSetting", param, cb);
  }

  getMsgNotifyMode(param, cb) {
    this._process("getMsgNotifyMode", param, cb);
  }

  getOauthCode(param, cb) {
    this._process("getOauthCode", param, cb);
  }

  getPersonalData(param, cb) {
    this._process("getPersonalData", param, cb);
  }

  getServerTime(param, cb) {
    this._process("getServerTime", param, cb);
  }

  getServerTimeSync(param, cb) {
    this._process("getServerTimeSync", param, cb);
    return "";
  }

  getSetting(param, cb) {
    this._process("getSetting", param, cb);
  }

  getUserDefineVoice(param, cb) {
    this._process("getUserDefineVoice", param, cb);
  }

  getUserNoDisturbMode(param, cb) {
    this._process("getUserNoDisturbMode", param, cb);
  }

  pageQueryEmoticon(param, cb) {
    this._process("pageQueryEmoticon", param, cb);
  }

  queryEmoticon(param, cb) {
    this._process("queryEmoticon", param, cb);
  }

  QueryEmoticonPackageByLabel(param, cb) {
    this._process("QueryEmoticonPackageByLabel", param, cb);
  }

  queryEmotionInPackage(param, cb) {
    this._process("queryEmotionInPackage", param, cb);
  }

  queryMarketApplication(param, cb) {
    this._process("queryMarketApplication", param, cb);
  }

  singleQueryEmoticonPackage(param, cb) {
    this._process("singleQueryEmoticonPackage", param, cb);
  }

  regCircleOfFriendNotifyCb(param, cb) {
    //TODO: 
  }

  regGetMyselfCb(param, cb) {
    //TODO: 
  }

  regOperateUserCb(param, cb) {
    //TODO: 
  }

  regUpdateFinished(param, cb) {
    //TODO: 
  }

  regUserHeadImgUpdateCb(param, cb) {
    //TODO: 
  }

  setAppOrder(param, cb) {
    this._process("setAppOrder", param, cb);
  }

  setGolbalNoDisturbMode(param, cb) {
    this._process("setGolbalNoDisturbMode", param, cb);
  }

  setHiddenTarget(param, cb) {
    this._process("setHiddenTarget", param, cb);
  }

  setMsgNotifyMode(param, cb) {
    this._process("setMsgNotifyMode", param, cb);
  }

  setOnlineState(param, cb) {
    this._process("setOnlineState", param, cb);
  }

  setPersonalData(param, cb) {
    this._process("setPersonalData", param, cb);
  }

  setSetting(param, cb) {
    this._process("setSetting", param, cb);
  }

  setUserDefineVoice(param, cb) {
    this._process("setUserDefineVoice", param, cb);
  }

  setUserNoDisturbMode(param, cb) {
    this._process("setUserNoDisturbMode", param, cb);
  }

  updateAccountInfo(param, cb) {
    this._process("updateAccountInfo", param, cb);
  }

  updateAppRoomInfo(param, cb) {
    this._process("updateAppRoomInfo", param, cb);
  }

  updateAppRoomMem(param, cb) {
    this._process("updateAppRoomMem", param, cb);
  }

  updateExtendInfo(param, cb) {
    this._process("updateExtendInfo", param, cb);
  }

  updateLocalSetting(param, cb) {
    this._process("updateLocalSetting", param, cb);
  }

  updateLocalSettingSync(param, cb) {
    this._process("updateLocalSettingSync", param, cb);
    return false;
  }
}