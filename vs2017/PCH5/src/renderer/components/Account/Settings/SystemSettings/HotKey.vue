<template>
  <div class="various-item cutting-line-after">
    <div class="">{{$t('account.hotKeySett')}}</div>
    <div class="settings-content">
      <div class="cutting-line-after">
        <div class="">{{$t('account.chatSendMsg')}}：</div>
        <v-radio
          class="hot-key-radio"
          v-for="(item, index) in sendMsgRadioList"
          v-model="defaultRadio"
          :key="index"
          :lable="item"
          @change="hanleRadioChange(index)"
        ></v-radio>
      </div>
      
      <div class="cutting-line-after">
        <div class="">
        <div class="">{{$t('account.screenshotBy')}}</div>
        <div class="screenshot-setting">
          <input class="hot-key-input"
            lang="en"
            v-model="screenshotsKey" 
            @blur="setScreenshotKey" 
            @keydown="getInputScreenshotsKey($event)"
          >
          <p class="screenshot-setting-tip" v-if="user_localConfig.screenShotKeyConflict">({{$t('account.conflictOther')}})</p>
        </div>
        <!-- 截屏时是否隐藏窗口 -->
        <v-checkbox
          v-model="isScreenDisplay"
          @change="setScreenDisplay"
        >{{$t('account.hideForPrtsc')}}</v-checkbox>
      </div>
      </div>

       <div class="">
        <div class="">{{$t('account.arouseWindow')}}：</div>
        <input class="hot-key-input"
          lang="en"
          v-model="windowshow_key" 
          @blur="setWindowShow_Key" 
          @keydown="getInputWindowshowKey($event)"
        >
      </div>
      
      <div
        class="clear-chart-btn theme-botton"
        @click="resetUserLocalConfig"
      >{{$t('user.restoreDefault')}}</div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import userMixin from "./../../AccountMixin.js";
import config from "vrv-static/data/config.json";
import {getConfig,setConfig} from '../../../../../comm/util.js'
import { isOSX } from '../../../../../comm/is.js';
export default {
  data() {
    return {
      sendMsgRadioList: [this.$t('account.ctrlAndEnrer'), this.$t('account.enterSend')],
      // sendMsgRadioList: ["按Ctrl+Enter键", "按Enter键"],
      screenshotsKey: "",
      windowshow_key:'',
      isShowLoading: false,
      isLoading: false,
      localConfigKeyArr: ["send_msg_key", "screenshot_key", "screen_display"],
      isScreenDisplay: false,
      eKeyCode:0   //键盘输入的keycode
    };
  },
  computed: {
    ...mapGetters(["user_localConfig"]),
    defaultRadio() {
      if(this.user_localConfig.isSendMsgKey === false || this.user_localConfig.send_msg_key === 'ENTER') {
        return this.$t('account.enterSend')
      } else{
        return this.$t('account.ctrlAndEnrer')
      }
    }
  },
  created() {
    console.log(this.user_localConfig, "--------");
    this.screenshotsKey = this.user_localConfig.screenshot_key;
    this.windowshow_key = this.getWindowshowKey();
    this.isScreenDisplay = this.user_localConfig.screen_display === "HIDE";
  },
  mixins: [userMixin],
  methods: {
    //读取配置文件里windowshow_key 的值
    getWindowshowKey(){
      let defaultKey = "Alt+C";
      let key = getConfig({key:'windowshowKey'});
      if(key) defaultKey = key;
      if(key == 'emptyKey') defaultKey =''
      return defaultKey;
    },
    /**
     * 设置发送消息快捷键
     */
    hanleRadioChange(val) {
      let tempVal = "";
      if (val == "0") tempVal = this.$is.isOSX ? "COMMAND_ENTER" : "CTRL_ENTER";
      if (val == "1") tempVal = "ENTER";

      this.setUserConfigForDatabase(
        this.user_localConfig.isSendMsgKey,
        "send_msg_key",
        tempVal,
        "isSendMsgKey"
      );
    },
        /**
     * 获取input框中的设置截屏快捷键的值
     */
    checkWindowshow(){
      this.windowshow_key=this.windowshow_key.replace(/[\W]/g,'');
    },
    getInputWindowshowKey(e) {
      e.preventDefault();
      this.eKeyCode = e.keyCode;
      console.log(e);
      // if(e.keyCode == 8){
      //   this.windowshow_key="";
      //   return;
      // }
      let key = "";
      let ctrlKey = this.$is.isOSX ? e.metaKey : e.ctrlKey;
      // if (e.altKey && e.keyCode === 67) {
      //   this.errPromptBox("该快捷键已被占用", "is-danger");
      //   return;
      // }
      if ((e.shiftKey && ctrlKey) || e.shiftKey || ctrlKey || e.altKey) {
        if (e.keyCode >= 65 && e.keyCode <= 90) {
          if (ctrlKey) key = this.$is.isOSX ? "Command+" : "Ctrl+";
          if (e.shiftKey) key = "Shift+";
          if (e.altKey) key = "Alt+";
          if (e.shiftKey && e.altKey) key = "Shift+Alt+";
          if (e.ctrlKey && e.altKey)
            key = this.$is.isOSX ? "Command+Alt+" : "Ctrl+Alt+";
          if (e.shiftKey && ctrlKey)
            key = this.$is.isOSX ? "Shift+Command+" : "Shift+Ctrl+";
          this.windowshow_key = key + String.fromCharCode(e.keyCode);
          console.log(this.windowshow_key);
        }
      }
    },
    /**
     * 获取input框中的设置截屏快捷键的值
     */
    getInputScreenshotsKey(e) {
      e.preventDefault();
      console.log(e);
      this.eKeyCode = e.keyCode;
      let key = "";
      let ctrlKey = this.$is.isOSX ? e.metaKey : e.ctrlKey;
      // if (e.altKey && e.keyCode === 67) {
      //   this.errPromptBox(this.$t('account.ccupied'),'is-danger');
      //   return
      // };
      if ((e.shiftKey && ctrlKey) || e.shiftKey || ctrlKey || e.altKey) {
        if (e.keyCode >= 65 && e.keyCode <= 90) {
          if (ctrlKey) key = this.$is.isOSX ? "Command+" : "Ctrl+";
          if (e.shiftKey) key = "Shift+";
          if (e.altKey) key = "Alt+";
          if (e.shiftKey && e.altKey) key = "Shift+Alt+";
          if (e.ctrlKey && e.altKey)
            key = this.$is.isOSX ? "Command+Alt+" : "Ctrl+Alt+";
          if (e.shiftKey && ctrlKey)
            key = this.$is.isOSX ? "Shift+Command+" : "Shift+Ctrl+";
          this.screenshotsKey = key + String.fromCharCode(e.keyCode);
          console.log(this.screenshotsKey);
        }
      }
    },
    /**
     * 检测快捷键占用
     */
    // checkOccupancy() {
    //   let combKey = {

    //   }
    // },
    /**
     * 设置快捷截屏
     */
    setWindowShow_Key(){
      if(this.eKeyCode === 229) {  //如果输入的为汉字，则屏蔽调
        this.windowshow_key = this.getWindowshowKey();
        return;
      }
      if(this.windowshow_key!==""){
        let lastKey = this.windowshow_key.split("+").pop();
        if (lastKey.length !== 1) {
          this.errPromptBox("请使用组合键设置", "is-danger");
          this.windowshow_key = this.getWindowshowKey();
          return;
        }
      }
      console.log('this.windowshow_key:',this.windowshow_key);
      this.$ConfigIni.setConfig({key:'windowshowKey',value:this.windowshow_key?this.windowshow_key:'emptyKey'});
      this.$ipc.send('globalRegisterKey',{key:'register-windowshow',value:this.windowshow_key})
    },
    setScreenshotKey() {
      if(this.eKeyCode === 229) {  //如果输入的为汉字，则屏蔽调
        this.screenshotsKey = this.user_localConfig.screenshot_key;
        return;
      }
      let lastKey = this.screenshotsKey.split("+").pop();
      console.log("lastKey:::", lastKey);
      if (lastKey.length !== 1) {
        this.errPromptBox(this.$t('account.keyCom'),'is-danger');
        this.screenshotsKey = this.user_localConfig.screenshot_key
        return
      }
      if(isOSX){
        this.$ipc.send('globalRegisterKey',{key:'register-shortcuts',value:this.screenshotsKey})
      }
      else{
        this.$Service.config.setScreenShotHotKey({key:this.screenshotsKey},resp=>{
          if(resp.code ===0){
             this.$store.commit('SET_USER_LOCALCONFIG', { key: "screenShotKeyConflict", value: false });
          }
          else{
            this.$store.commit('SET_USER_LOCALCONFIG', { key: "screenShotKeyConflict", value: true });
          }
        });
      }
      this.setUserConfigForDatabase(
        this.user_localConfig.isScreenshotKey,
        "screenshot_key",
        this.screenshotsKey,
        "isScreenshotKey"
      );
    },
    /***
     * 配置截屏时是否隐藏主窗口
     */
    setScreenDisplay() {
      let val = this.isScreenDisplay ? config.prtSc.normal : config.prtSc.hide;
      this.setUserConfigForDatabase(
        this.user_localConfig.isScreenDisplay,
        "screen_display",
        val,
        "isScreenDisplay"
      );
      //向截图程序设置快捷键截图时是否隐藏窗口
      if(isOSX){
        this.$ipc.send("globalRegisterKey", {
          key: "register-shortcuts-hideWindow",
          value: val === "HIDE"
        });
      }
      else{
        //向截图程序设置快捷键截图时是否隐藏窗口
        this.$Service.config.setScreenDisplay({hide:val === "HIDE"});
      }
    },
    /**
     * 恢复默认设置（删除本地配置，初始化vuex中用户本地配置字段）
     */
    resetUserLocalConfig() {
      console.log("config:::", config);
      this.windowshow_key = 'Alt+C'
      this.$ConfigIni.setConfig({key:'windowshowKey',value:this.windowshow_key});
      this.$ipc.send('globalRegisterKey',{key:'register-windowshow',value:this.windowshow_key})
      let key = this.$is.isOSX ? config.prtSc.osx : config.prtSc.windows;
      if(isOSX){
        this.$ipc.send('globalRegisterKey',{key:'register-shortcuts',value:key})
      }
      else{
        this.$Service.config.setScreenShotHotKey({key:key},resp=>{
          if(resp.code ===0){
             this.$store.commit('SET_USER_LOCALCONFIG', { key: "screenShotKeyConflict", value: false });
          }
          else{
            this.$store.commit('SET_USER_LOCALCONFIG', { key: "screenShotKeyConflict", value: true });
          }
        });
      }
      this.$Service.user.deleteLocalSetting(config.restUserConfig, resp => {
        console.log(resp, "deleteLocalSetting all");
        if (resp.code == 0) {
          this.screenshotsKey = key;
          this.isScreenDisplay = false;
          this.$store.commit("RESET_USERCONFIG");
        }
      });
    }
  }
};
</script>
<style lang="scss" scoped>
.hot-key-radio {
  padding: 2px 0;
  margin: 0;
  width: 200px;
}
.hot-key-input {
  height: 30px;
  width: 170px;
  border: 0;
  border-radius: $--border-radius-base;
  outline: none;
  background: #d3d3d3;
  padding-left: 10px;
  font-size: $--font-size-small;
  display: block;
  margin-bottom: 10px;
  ime-mode: disabled;
}
.screenshot-setting{
    display: flex;
    .hot-key-input {
      height: 30px;
      width: 170px;
      border: 0;
      border-radius: $--border-radius-base;
      outline: none;
      background: #d3d3d3;
      padding-left: 10px;
      font-size: $--font-size-small;
      display: block;
      margin-bottom: 10px;
      ime-mode: disabled;
    }
    .screenshot-setting-tip{
      padding-top: 2px;
      padding-left: 2px;
      color: red;
    }
}
.clear-chart-btn {
  margin-top: 10px;
}
</style>
