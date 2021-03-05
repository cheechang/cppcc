/**
 * @file      Manage the config's api.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 */
class ConfigService {
  constructor(client, utils) {
      this._config = client.configService();
      this._utils = utils;
  }

  getAutoStart() {
    return this._config.getAutoStart();
  }

  getAutoStartAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getAutoStart();
      resolve(resp);
    });
  }

  getIsRoming() {
    return this._config.getIsRoming();
  }

  getIsRomingAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getIsRoming();
      resolve(resp);
    });
  }

  getLastPreLoginData(param) {
    return this._config.getLastPreLoginData(param);
  }

  getLastPreLoginDataAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getLastPreLoginData(param);
      resolve(resp);
    });
  }

  getLoginExData(param, cb) {
    return this._config.getLoginExData(param, resp => {
        this._utils.makeCallBack(resp, cb);
    });
  }

  getLoginExDataAsync(param, cb) {
    return new Promise((resolve, reject)=>{
      this._config.getLoginExDataAsync(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getLoginInfos(param, cb) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getLoginInfos(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMultiChannelAddress(param, cb) {
    return new Promise((resolve, reject)=>{
      this._config.getMultiChannelAddress(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getMultiChannelAddressAsync(param, cb) {
    return new Promise((resolve, reject)=>{
      this._config.getMultiChannelAddressAsync(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  getNetProxy() {
    return this._config.getNetProxy();
  }

  getNetProxyAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getNetProxy();
      resolve(resp);
    });
  }

  getPreloginInfoEx() {
    return this._config.getPreloginInfoEx();
  }

  getPreloginInfoExAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getPreloginInfoEx();
      resolve(resp);
    });
  }

  getSdkVersion() {
    return this._config.getSdkVersion();
  }

  getSdkVersionAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getSdkVersion();
      resolve(resp);
    });
  }

  getSubServerInfo() {
    return this._config.getSubServerInfo();
  }

  getSubServerInfoAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getSubServerInfo();
      resolve(resp);
    });
  }

  getUserTypeById(param) {
    return this._config.getUserTypeById(param);
  }

  getUserTypeByIdAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getUserTypeById(param);
      resolve(resp);
    });
  }

  getMsgParserMode() {
    return this._config.getMsgParserMode();
  }

  getMsgParserModeAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getMsgParserMode();
      resolve(resp);
    });
  }

  getSystemNationCode() {
    return this._config.getSystemNationCode();
  }

  getSystemNationCodeAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getSystemNationCode();
      resolve(resp);
    });
  }
  
  getCapsLockStatus() {
    return this._config.getCapsLockStatus();
  }

  getCapsLockStatusAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getCapsLockStatus();
      resolve(resp);
    });
  }

  getLanguage() {
    return this._config.getLanguage();
  }

  getLanguageAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getLanguage();
      resolve(resp);
    });
  }

  getSystemLanguage() {
    return this._config.getSystemLanguage();
  }

  getSystemLanguageAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.getSystemLanguage();
      resolve(resp);
    });
  }

  headImgPath(param,cb) {
    return this._config.headImgPath(param,resp=>{
      this._utils.makeCallBack(resp, cb);
    });
  }

  headImgPathAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.headImgPath(null);
      resolve(resp);
    });
  }

  rootPath() {
    return this._config.rootPath();
  }

  rootPathAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.rootPath();
      resolve(resp);
    });
  }

  userAudioPath(param,cb) {
    return this._config.userAudioPath(param,resp=>{
      this._utils.makeCallBack(resp, cb);
    });
  }

  userAudioPathAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.userAudioPath(null);
      resolve(resp);
    });
  }

  userCachePath(param,cb) {
    return this._config.userCachePath(param,resp=>{
      this._utils.makeCallBack(resp, cb);
    });
  }

  userCachePathAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.userCachePath(null);
      resolve(resp);
    });
  }

  userEmotionPath(param,cb) {
    return this._config.userEmotionPath(param,resp=>{
      this._utils.makeCallBack(resp, cb);
    });
  }

  userEmotionPathAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.userEmotionPath(null);
      resolve(resp);
    });
  }

  userFilePath(param,cb) {
    return this._config.userFilePath(param,resp=>{
      this._utils.makeCallBack(resp, cb);
    });
  }

  userFilePathAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.userFilePath(null);
      resolve(resp);
    });
  }

  userImgPath(param,cb) {
    return this._config.userImgPath(param,resp=>{
      this._utils.makeCallBack(resp, cb);
    });
  }

  userImgPathAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.userImgPath(null);
      resolve(resp);
    });
  }

  userVideoPath(param,cb) {
    return this._config.userVideoPath(param,resp=>{
      this._utils.makeCallBack(resp, cb);
    });
  }

  userVideoPathAsync() {
    return new Promise((resolve, reject)=>{
      let resp = this._config.userVideoPath(null);
      resolve(resp);
    });
  }

  setAppName(param) {
    return this._config.setAppName(param);
  }

  setAppNameAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setAppName(param);
      resolve(resp);
    });
  }

  setAppVersion(param) {
    return this._config.setAppVersion(param);
  }

  setAppVersionAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setAppVersion(param);
      resolve(resp);
    });
  }

  setAutoStart(param) {
    return this._config.setAutoStart(param);
  }

  setAutoStartAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setAutoStart(param);
      resolve(resp);
    });
  }

  setCertificatePath(param) {
    return this._config.setCertificatePath(param);
  }

  setCertificatePathAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setCertificatePath(param);
      resolve(resp);
    });
  }

  setHttpsLogin(param) {
    return this._config.setHttpsLogin(param);
  }

  setHttpsLoginAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setHttpsLogin(param);
      resolve(resp);
    });
  }

  setInterConnect(param) {
    return this._config.setInterConnect(param);
  }

  setInterConnectAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setInterConnect(param);
      resolve(resp);
    });
  }

  setIsRoming(param) {
    return this._config.setIsRoming(param);
  }

  setIsRomingAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setIsRoming(param);
      resolve(resp);
    });
  }

  setLanguage(param) {
    return this._config.setLanguage(param);
  }

  setLanguageAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setLanguage(param);
      resolve(resp);
    });
  }

  setLanguage(param) {
    return this._config.setLanguage(param);
  }

  setLanguageAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setLanguage(param);
      resolve(resp);
    });
  }

  setLanguageType(param) {
    return this._config.setLanguage(param);
  }

  setLanguageTypeAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setLanguageType(param);
      resolve(resp);
    });
  }

  setLoginInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._config.setLoginInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setLogLevel(param) {
    return this._config.setLogLevel(param);
  }

  setLogLevelAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setLogLevel(param);
      resolve(resp);
    });
  }

  setMsgParserMode(param) {
    return this._config.setMsgParserMode(param);
  }

  setMsgParserModeAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setMsgParserMode(param);
      resolve(resp);
    });
  }

  setMultichannel(param) {
    return this._config.setMultichannel(param);
  }

  setMultichannelAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setMultichannel(param);
      resolve(resp);
    });
  }

  setNetProxy(param) {
    return this._config.setNetProxy(param);
  }

  setNetProxyAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setNetProxy(param);
      resolve(resp);
    });
  }

  setNetStatus(param) {
    return this._config.setNetStatus(param);
  }

  setNetStatusAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setNetStatus(param);
      resolve(resp);
    });
  }

  setNotifyStatus(param) {
    return this._config.setNotifyStatus(param);
  }

  setNotifyStatusAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setNotifyStatus(param);
      resolve(resp);
    });
  }

  setOffloginSwitch(param) {
    return this._config.setOffloginSwitch(param);
  }

  setOffloginSwitchAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setOffloginSwitch(param);
      resolve(resp);
    });
  }

  setPlugPower(param) {
    return this._config.setPlugPower(param);
  }

  setPlugPowerAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setPlugPower(param);
      resolve(resp);
    });
  }

  setPwIsCrypt(param) {
    return this._config.setPwIsCrypt(param);
  }

  setPwIsCryptAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setPwIsCrypt(param);
      resolve(resp);
    });
  }

  setRootPath(param) {
    return this._config.setRootPath(param);
  }

  setRootPathAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setRootPath(param);
      resolve(resp);
    });
  }

  setSubServerInfo(param) {
    return this._config.setSubServerInfo(param);
  }

  setSubServerInfoAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setSubServerInfo(param);
      resolve(resp);
    });
  }

  setTextCoding(param) {
    return this._config.setTextCoding(param);
  }

  setTextCodingAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setTextCoding(param);
      resolve(resp);
    });
  }

  setTicket(param) {
    return this._config.setTicket(param);
  }

  setTicketAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.setTicket(param);
      resolve(resp);
    });
  }

  setHideBuddySwitch(param) {
    this._config.setHideBuddySwitch(param);
  }

  delLoginInfo(param) {
    return this._config.delLoginInfo(param);
  }

  delLoginInfoAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.delLoginInfo(param);
      resolve(resp);
    });
  }

  reNotifyData(param) {
    return this._config.reNotifyData(param);
  }

  reNotifyDataAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.reNotifyData(param);
      resolve(resp);
    });
  }

  launchOtherApp(param) {
    return this._config.launchOtherApp(param);
  }

  launchOtherAppAsync(param) {
    return new Promise((resolve, reject)=>{
      let resp = this._config.launchOtherApp(param);
      resolve(resp);
    });
  }

  startUpScreenShot() {
    this._config.startUpScreenShot();
  }

  shutDownScreenShot() {
    this._config.shutDownScreenShot();
  }

  setScreenShotHotKey(param,cb) {
    this._config.setScreenShotHotKey(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  setScreenShotHotKeyAsync(param,cb) {
    return new Promise((resolve, reject)=>{
      this._config.setScreenShotHotKey(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    });
  }

  setScreenDisplay(param) {
    this._config.setScreenDisplay(param);
  }

  screenShot() {
    this._config.screenShot();
  }

  regScreenShotCb(param, cb) {
    this._config.regScreenShotCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regIsSystemIdleCb(param, cb) {
    this._config.regIsSystemIdleCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }

  regTheThridPartyMsgCb(param, cb) {
    this._config.regTheThridPartyMsgCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
}
module.exports = ConfigService;