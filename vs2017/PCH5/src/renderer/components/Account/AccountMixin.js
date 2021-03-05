import {
  mapGetters
} from 'vuex';

import {
  resolve,
  join
} from 'path';
import MultipleServersMixin from '../Servers/multipleServersMixin'
const mixin = {
  mixins:[MultipleServersMixin],
  data() {
    return {
      isContinue: true
    }
  },
  computed: {
    ...mapGetters([
      'user_filePath',
      'user_audioPath',
      'user_videoPath',
      'user_loginInfo',
      'user_account',
      'user_usever'
    ]),
    themeDir() {
      let themeDir = this.$is.isDev ?
        (this.$is.isOSX ? `file://${this.$osxDirPath}/` + 'node_modules/vrv-static/plugins/themes' : resolve(__dirname, './../../../../node_modules/vrv-static/plugins/themes/', '')) :
        join(__dirname, '/node_modules/vrv-static/plugins/themes/')
      return themeDir
    }
  },
  methods: {
    /**
     * 退出登陆时删除用户临时文件、退出禅道
     */
    delTempFiles() {
      let accountJson = this.makeAccountsJson();
      this.$store.commit('CLEAR_ZENTAO'); // 删除禅道信息  CLEAR_USER_ACCOUNT
      this.$store.commit('CLEAR_USER_ACCOUNT'); // 删除用户账户信息
      this.$store.commit('CLEAR_USER_LOCALCONFIG'); // 删除用户个人中心本地配置信息
      this.$store.commit('EMPTY_ALL_DATA_CACHE', null); // 删除临时文件
      this.$store.commit('CLEAR_CONTACT_DATA'); // 删除联系人数据
      this.$store.commit('CLEAR_APPINFO_LIST'); // 删除应用数据
      this.$store.commit('INIT_LOGIN_BY_FORGETPWD'); // 重置忘记密登录标识
      this.$store.commit('SET_ONLINE_STATUS', -1); // 设置在线状态
      this.$store.commit('SET_MULTIPLE_SERVER',{flag: 0,val:[]}); //清空多服务器信息
      let tempObj = Object.assign({}, this.user_loginInfo);
      tempObj.isAutoLogin = 0;
      tempObj.isRemberPass = 0;
      tempObj.email = accountJson;
      tempObj.server = `${tempObj.server};${this.user_usever}`;
      console.log('tempObj:::', tempObj);
      this.$Service.config.setLoginInfo(tempObj, resp => {
        this.$Service.log(`切换账号重置为非自动登陆:${resp.ret}`);
      });
      this.$store.commit('CLEAR_ACCOUNT_INFO', {})
      setTimeout(() => { // 删除数据库临时文件、音频、视频
        let delFiles = this.$Service.file.fileOperate({
          filepath: `${this.user_filePath}cache`,
          type: 2
        });
        let delAudios = this.$Service.file.fileOperate({
          filepath: `${this.user_audioPath}cache`,
          type: 2
        });
        let delVideos = this.$Service.file.fileOperate({
          filepath: `${this.user_videoPath}cache`,
          type: 2
        });
      });
    },
    makeAccountsJson(){
      let json = '';
      for(let i =0;i<this.user_account.accounts.length;++i){
        if(json){
          json=json+';';
        }
        json =`${json}${this.user_account.accounts[i].type},${this.user_account.accounts[i].accounts}`
      }
      return json;
    },
    // 设置用户登录历史信息
    setUserLoginInfo(resp) {
      console.log('in setUserLoginInfo');
      console.log(JSON.stringify(this.user_loginInfo));
      let tempInfos = {};
      tempInfos.phone = resp.phone;
      tempInfos.name = this.user_loginInfo.account;
      tempInfos.user_icon = resp.thumbAvatarUrl.replace(/\//g, function(item) {
        return '_';
      });
      let newInfos = Object.assign({}, this.user_loginInfo);
      this.$store.commit('SET_LOGININFO', Object.assign(newInfos, tempInfos));
      this.$ipc.send('tray-username', {
        name: resp.name,
        server: newInfos.server,
        userId:resp.userId
      });
      this.$Service.log(`存入数据库的用户信息:头像:${newInfos.user_icon}`);
      let sdkLoginInfoObj = Object.assign({}, newInfos);
      // 设置登录历史中server存入界面显示的服务器字段以及elogo字段
      sdkLoginInfoObj.server = `${sdkLoginInfoObj.server};${this.user_usever}`;
      sdkLoginInfoObj.email = this.makeAccountsJson();
      this.$Service.config.setLoginInfo(
        sdkLoginInfoObj,
        resp => {
          console.log('设置历史登陆信息:sdkLoginInfoObj:',sdkLoginInfoObj,'  resp:',resp);
          this.$store.commit('INIT_LOGININFOS', newInfos)
        }
      );
    },
    /**
     * 顶部提示气泡
     */
    errPromptBox(m, t) {
      this.$toast.open({
        duration: 3000,
        message: m,
        position: 'is-top',
        type: t
      });
    },
    /**
     * 用户设置数据库时，判断调用添加配置还是更新配置
     * @param { Boolean } isUpdate    - 传入 true 调用更新本地配置，反之调用添加本地配置
     * @param { String }  key         - 调用本设置本地配置接口时的入参 key
     * @param { String }  val         - 调用本设置本地配置接口时的入参 val
     * @param { String }  status      - 传入vuex use 模块中 userLocalConfigData下的判断本地知否有过设置记录的字段
     *                                  当第一次设置某项配置后，则更新vuex use 模块中 userLocalConfigData对象中对应的字段，再次设置是使用次字段来判断调用更新配置/添加配置
     */
    setUserConfigForDatabase(isUpdate, key, val, status) {
      console.log();
      isUpdate
        ?
        this.updateLocalSetting(key, val) :
        this.addLocalSetting(key, val, status);
    },
    /**
     * 添加本地配置
     */
    addLocalSetting(key, val, j) {
      if (key === 'top_apps') val = JSON.stringify(val);
      this.$Service.log(`高级设置添加本地配置${key}入参:::${key},${val}`);
      this.$Service.user.addLocalSetting(
        [{
          key: key,
          value: val.toString()
        }],
        resp => {
          this.$Service.log(`高级设置添加本地配置${key}返回:::${JSON.stringify(resp)}`)
          if (resp.code === 0 && key !== 'top_apps') {
            this.$store.commit("SET_USER_LOCALCONFIG", {
              key: key,
              value: val
            });
            this.$store.commit("SET_USER_LOCALCONFIG", {
              key: j,
              value: true
            });
          }
          this.getUserLocalSetting([key]);
        }
      )
    },
    /**
     * 更新本地配置
     */
    updateLocalSetting(key, val) {
      if (key === 'top_apps') val = JSON.stringify(val);
      this.$Service.log(`高级设置更新本地配置${key}入参:::${key},${val}`);
      this.$Service.user.updateLocalSetting({
          settings: [{
            key: key,
            value: val.toString()
          }]
        },
        resp => {
          this.$Service.log(`高级设置更新本地配置${key}返回:::${JSON.stringify(resp)}`);
          if (resp.code === 0 && key !== 'top_apps') {
            this.$store.commit("SET_USER_LOCALCONFIG", {
              key: key,
              value: val
            });
          }
          this.getUserLocalSetting([key]);
        }
      )
    },
    getUserLocalSetting(param) {
      this.$Service.user.getLocalSetting(
        param,
        resp => {
          console.log(resp, '查看本地配置后的结果');
        }
      )
    },
    // 加载主题
    setDoodTheme(key) {
      if (key === 'theme-default' || !key || (key.indexOf('theme') === -1)) {
        return window.document.documentElement.removeAttribute('data-theme')
      }
      window.document.documentElement.setAttribute('data-theme', key)
    },

    async logout() {
      console.log('this.isContinue', this.isContinue)
      if (!this.isContinue) return
      this.isContinue = false
      console.log('isTransmitting', this.$Service.file.isTransmitting())
      if (this.$Service.file.isTransmitting()) {
        await this.isTransmitting()
      }
      this.$dialog.confirm({
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        message: this.$t('user.confirmLogout') + '?',
        onConfirm: () => {
          this._exitMultipleServers(); //退出其他服务器
          console.log('send close-all-subWin');
          this.$ipc.send('close-all-subWin');
        },
        onCancle: () => {
          this.isContinue = true
        },
        onClickOutside: () => {
          this.isContinue = true
        }
      });
    },

    isTransmitting() {
      return new Promise((reslove) => {
        this.$dialog.confirm({
          confirmText: this.$t('common.confirm'),
          cancelText: this.$t('common.cancel'),
          message: this.$t('account.sendTerPrompt'),
          onConfirm: () => {
            this.$Service.file.cancelAllTransfer(null, resp => {
              console.log('cancelAllTransfer', resp)
              if (resp.code === 0) {
                reslove()
              }
            })
          },
          onCancle: () => {
            this.isContinue = true
          },
          onClickOutside: () => {
            this.isContinue = true
          }
        });
      })
    },

    async quit() {
      if (!this.isContinue) return
      this.isContinue = false
      console.log('isTransmitting', this.$Service.file.isTransmitting())
      if (this.$Service.file.isTransmitting()) {
        await this.isTransmitting()
      }
      this.$dialog.confirm({
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        message: this.$t('user.confirmExit') + '?',
        onConfirm: () => {
          this._exitMultipleServers(); //退出其他服务器
          this.$Service.log(`exit-app:before:${new Date().getTime()}`);
          this.$ipc.send('exit-app');
          this.isContinue = true
        },
        onCancle: () => {
          this.isContinue = true
        },
        onClickOutside: () => {
          this.isContinue = true
        }
      });
    }
  }
};
export default mixin;
