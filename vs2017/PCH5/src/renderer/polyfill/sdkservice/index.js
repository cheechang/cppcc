import Vue from 'vue';

//  接下来会执行登录
let service = null;

// 判断是否为electron
let agent = navigator.userAgent.toLowerCase();
if (agent.indexOf('electron') !== -1) {
  service = window.require('electron').remote.getGlobal('service');
} else {
  let sdkhelper = require('./imsdk')
  service = sdkhelper.service;
}
// 挂载全局服务
console.log('get service: ', service);
Vue.prototype.$Service = service;
console.log('get service: ', service.auth);

export default service;
