import utils from '../utils';
export default class DDBus {
  constructor() {
    //  获取当前的运行环境，使用相关的bus实例
    //this.bus
    let agent = navigator.userAgent.toLowerCase();
    console.log('is Web: ', utils.isWeb());
    // if (agent.indexOf("electron") !== -1) {
    //   this.$bus = require("./ipc-bus").default;
    // } else {
    //   this.$bus = require("./web-bus").default;
    // }
    if (utils.isWeb()) {
      this.$bus = require("./web-bus").default;
    } else {
      console.log('is Web: ', utils.isWeb());
      this.$bus = require("./ipc-bus").default;
    }
  }

  bus() {
    console.log("in bus.js: ", this.$bus);
    return new this.$bus();
  }
}