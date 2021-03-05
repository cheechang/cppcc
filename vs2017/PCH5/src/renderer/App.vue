<template>
    <div id="app" :class="{'app-border': showBorder}">
    <!-- 更新进度 -->
    <updater :isUpdateShow="isUpdateShow" :isDownloadFinished="isDownloadFinished" :updateInfo="updateInfo" @close="isUpdateShow=false" @open-update-info="isUpdateShow=true"></updater>
    <router-view ></router-view>
  </div>
</template>

<script>
import Updater from './components/Main/updater';
import { homedir } from 'os';
import { mapGetters } from 'vuex';
import UpdateMixins from './components/Updater/UpdateMixins';
import ThemeMixins from './components/Theme/mixins';
import { versionCompire } from "./utils/utils.js";
import pkg from '../../package.json';
export default {
  mixins: [UpdateMixins,ThemeMixins],
  data() {
    return {
      isDefaultTheme: ''
    }
  },
  components: {
    Updater
  },
  computed:{
    ...mapGetters([
      'user_localConfig',
    ]),

    showBorder() {
      return !this.$is.isOSX && this.isDefaultTheme;
    }
  },
  created() {
    if(
      this.$route.name==='RTCP2P'||
      this.$route.name==='RemoteControl'||
      this.$route.name==='RtcFile'|| 
      this.$route.name==='MultiMeeting'
    ) {
      return;
    };

    console.log('app create...')
    console.log('get system config: ', this.$config);
    this.update();
    //设置主题
    this.setClientConfig();
    let themeId = this.setTheme();
    this._handleThemeBorder(themeId);
    this.$signalMonitor.$on('change-theme', this._handleThemeBorder);
    
    // 监听切换至该服务器时,主服务发送过来的多服务器信息
    this.$ipc.on('switchToServer',(event,msg)=>{
      this.$store.commit('SET_MULTIPLE_SERVER', {flag: 0, val: msg.serverInfos})
    });

    this.$ipc.on('thirdParty_authRequest', this._handleRequestForThirdParty);
    // 从配置文件读取隐藏/显示窗口快捷键
    this.getWindowShowKey(); 
    // 登录前设置开启隐藏好友(4.7以及高于4.7版本支持)
    let openHideBuddySwitch = versionCompire(pkg.version,'4.7.0');
    if (!openHideBuddySwitch) return;
    console.log('版本高于4.6，手动开启隐藏好友=>flag=0')
    this.$Service.config.setHideBuddySwitch({flag: 0})
  },
  methods: {
    /**
     * 升级相关操作
     */
    update() {
      // 检测西安升级
      this.$ipc.send('check-for-update')
      if (this._isWeb()) return;
      // 启动应用 删除linkdood数据库目录下的update文件夹
      let updateParam = { filepath: `${this.$dbPath}update`, type: 0 }
      if(this.$Service.file.fileOperate(updateParam)) {
        this.$Service.file.fileOperate({ filepath: `${this.$dbPath}update`, type: 2 });
      }
      console.log('start update...');
      this.checkUpdateListener();
      console.log('isCheckUpdate::::::', this.$pkg.checkUpgrade)
      //检测到更新，显示弹框
      this.$ipc.on('updateAvailable', (res)=> {
        this.isUpdateShow = true;
      });
      /**
       * 启动客户端后是否自动检测西安升级
       * Jenkins上通过配置CHECK_UPGRADE，以写文件的方式修改了package.json的checkUpgrade实现
       */
      if (!this.$pkg.checkUpgrade) return;
      this._checkUpdateFromLocal().then(resp => {
        console.log('i get checkUpdateFromLocal result: ', resp);
      });
    },
  
    setClientConfig(){
      // 存储客户端配置至vuex
      Object.keys(this.$config.clientConfig.auth).forEach(e=>{
        this.$store.commit('SET_CLIENTCONFIG_AUTH', { key: e, value: this.$config.clientConfig.auth[e]});
      }),
      Object.keys(this.$config.clientConfig.user).forEach(e=>{
        this.$store.commit('SET_CLIENTCONFIG_USER', { key: e, value: this.$config.clientConfig.user[e]});
      }),
      Object.keys(this.$config.clientConfig.system).forEach(e=>{
        this.$store.commit('SET_CLIENTCONFIG_SYSTEM', { key: e, value: this.$config.clientConfig.system[e]});
      })
      Object.keys(this.$config.clientConfig.chat).forEach(e=>{
        this.$store.commit('SET_CLIENTCONFIG_CHAT', { key: e, value: this.$config.clientConfig.chat[e]});
      })
    },
    getWindowShowKey(){
      let defaultKey = "Alt+C";
      let key = this.$ConfigIni.getConfig({key:'windowshowKey'});
      if(key) {
         defaultKey =key;
      }
      this.$ipc.send('globalRegisterKey',{key:'register-windowshow',value:defaultKey}) //注册窗口快捷键
    },

    _handleRequestForThirdParty(event, message) {
      if(this.user_localConfig.thirdParty_authRequestInfo){
        let data={
          port:message.port,
          code:"-1",
          msg:'user_auth_busy',
          authCode:''
        }
        this.$callPlugin.responseAuthRequest(data);
        return;
      } else {
         this.$store.commit('SET_USER_LOCALCONFIG', { key: 'thirdParty_authRequestInfo', value: message });
      }
    },
    _handleThemeBorder(themeId) {
      this.isDefaultTheme = (themeId === 'theme-default' || !themeId);
    }
  }
}
</script>

<style lang="scss">
@import './ui/scss/vrvui-build.scss';
@import './style/global.scss';
@import './style/common.scss';
</style>
