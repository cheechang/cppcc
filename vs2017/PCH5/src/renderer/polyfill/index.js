import Vue from 'vue';
import DDBus from './bus';
import utils from './utils';
import Config from '../../comm/config';
import './sdkservice';

//  加载linkdood-plugin模块
if (utils.isWeb()) {
  Vue.prototype.$callPlugin = require('./bridge').default;
  Vue.prototype.$oauth = null;
  Vue.prototype.$initInfo = null;
  Vue.prototype.$judgePlginSubWinStatus = null;
  Vue.prototype.$isOpenMediaMsgPreivew = null;
  Vue.prototype.$dialogs = null;
  Vue.prototype.$shell = null;
  Vue.prototype.$images = null;
  Vue.prototype.$ConfigIni = require('./ConfigIni').default;
  Vue.prototype.$AppPath = require('../../comm/AppPath').default;
  Vue.prototype.$dbPath = '';
  Vue.prototype.$osxDirPath = '';
  Vue.prototype.$rtcplugin = null;
  Vue.prototype.$p2pUtils = null;
  Vue.prototype.$language = 'zh-CN';
  Vue.prototype.$setApHost = (host) => {};
  Vue.prototype.$nativeImage = null;
  Vue.prototype.$getFileIcon = (obj) => {};
  Vue.prototype.$getWindowStatus = () => {return false};
  Vue.prototype.$pkg = null;
  Vue.prototype.$serversLoginParam = null;
  Vue.prototype.$mutipleServers = null;
  process.env.ISWEB = true;
} else {
  let remote = window.require('electron').remote;
  Vue.prototype.$nativeImage = window.require('electron').nativeImage; 
  Vue.prototype.$callPlugin = remote.getGlobal('callPlugin');
  Vue.prototype.$oauth = remote.getGlobal('oauth');
  Vue.prototype.$mutipleServers = remote.getGlobal('mutipleServers');
  //Vue.prototype.$Service = remote.getGlobal('service');
  Vue.prototype.$initInfo = remote.getGlobal('initInfo');
  Vue.prototype.$judgePlginSubWinStatus = remote.getGlobal('judgePlginSubWinStatus');
  Vue.prototype.$isOpenMediaMsgPreivew = remote.getGlobal('isOpenMediaMsgPreivew');
  Vue.prototype.$dbPath = remote.getGlobal('dbPath');
  Vue.prototype.$osxDirPath = remote.getGlobal('osxDirPath');
  Vue.prototype.$dialogs = remote.dialog
  Vue.prototype.$shell = window.require('electron').shell
  Vue.prototype.$images = require('../../comm/images');
  //Vue.prototype.$images = remote.getGlobal('images');
  Vue.prototype.$pkg = remote.getGlobal('pkg');
  Vue.prototype.$ConfigIni = remote.getGlobal('ConfigIni');
  Vue.prototype.$AppPath = remote.getGlobal('AppPath');
  Vue.prototype.$rtcplugin = remote.getGlobal('service')['rtcplugin'];
  Vue.prototype.$p2pUtils = require('../../rtc/file/p2pUtils.js');
  Vue.prototype.$language = remote.getGlobal('language');
  Vue.prototype.$setApHost = remote.getGlobal('setApHost');
  Vue.prototype.$getFileIcon = remote.getGlobal('getFileIcon');
  Vue.prototype.$getWindowStatus = remote.getGlobal('getWindowStatus');
  Vue.prototype.$serversLoginParam = remote.getGlobal('serversLoginParam');
  process.env.ISWEB = false;
}

let bus = new DDBus();
Vue.prototype.$ipc = bus.bus();
Vue.prototype.$config = Config;