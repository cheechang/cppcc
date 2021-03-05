/**
 * @file      Manage the user's api.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class UserService {
  constructor(client, utils) {
      this._user = client.userService();
      this._utils = utils;
  }

  addLocalSetting(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.addLocalSetting(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  addLocalSettingSync(param) {
    return this._user.addLocalSettingSync(param);
  }

  addOrDeleteApplication(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.addOrDeleteApplication(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  addOrDeleteCustomEmoticon(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.addOrDeleteCustomEmoticon(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  changeHiddenPasswd(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.changeHiddenPasswd(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  circleOfFriend(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.circleOfFriend(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  createAppRoom(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.createAppRoom(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  deleteLocalSetting(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.deleteLocalSetting(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  deleteLocalSettingSync(param) {
    return this._user.deleteLocalSettingSync(param);
  }

  delHiddenTarget(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.delHiddenTarget(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  deleteDeviceLoginRecord(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.deleteDeviceLoginRecord(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  transLocalData(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.transLocalData(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  wakeUp(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.wakeUp(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getAccountInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getAccountInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getAppInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getAppInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGlobalNoDisturbMode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getGlobalNoDisturbMode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }
  
  getHiddenTarget(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getHiddenTarget(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getIdByAccount(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getIdByAccount(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getEntAppInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getEntAppInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getInstalledApplication(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getInstalledApplication(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getInstalledApplicationSorted(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getInstalledApplicationSorted(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getLocalSetting(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getLocalSetting(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getLocalSettingSync(param) {
    return this._user.getLocalSettingSync(param);
  }

  getMsgNotifyMode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getMsgNotifyMode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getOauthCode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getOauthCode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getPersonalData(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getPersonalData(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getDeviceLoginRecord(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getDeviceLoginRecord(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getServerTime(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getServerTime(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getServerTimeSync(param) {
    return this._user.getServerTimeSync(param)
  }

  getSetting(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getSetting(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getUserDefineVoice(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getUserDefineVoice(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getUserNoDisturbMode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getUserNoDisturbMode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getGlobalNoDisturbListMode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.getGlobalNoDisturbListMode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  pageQueryEmoticon(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.pageQueryEmoticon(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  queryEmoticon(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.queryEmoticon(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  QueryEmoticonPackageByLabel(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.QueryEmoticonPackageByLabel(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  queryEmotionInPackage(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.queryEmotionInPackage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  queryMarketApplication(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.queryMarketApplication(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  singleQueryEmoticonPackage(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.singleQueryEmoticonPackage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  regCircleOfFriendNotifyCb(param, cb) {
    this._user.regCircleOfFriendNotifyCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regGetMyselfCb(param, cb) {
    this._user.regGetMyselfCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regOperateUserCb(param, cb) {
    this._user.regOperateUserCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regUpdateFinished(param, cb) {
    this._user.regUpdateFinished(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regUserHeadImgUpdateCb(param, cb) {
    this._user.regUserHeadImgUpdateCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  setAppOrder(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setAppOrder(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setGolbalNoDisturbMode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setGolbalNoDisturbMode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setGolbalNoDisturbListMode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setGolbalNoDisturbListMode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setHiddenTarget(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setHiddenTarget(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setMsgNotifyMode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setMsgNotifyMode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setOnlineState(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setOnlineState(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setPersonalData(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setPersonalData(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setSetting(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setSetting(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setUserDefineVoice(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setUserDefineVoice(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setUserNoDisturbMode(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.setUserNoDisturbMode(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  updateAccountInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.updateAccountInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  updateAppRoomInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.updateAppRoomInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  updateAppRoomMem(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.updateAppRoomMem(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  updateExtendInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.updateExtendInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  updateLocalSetting(param, cb) {
    return new Promise((resolve, reject)=>{
      this._user.updateLocalSetting(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }
  
}
module.exports = UserService;