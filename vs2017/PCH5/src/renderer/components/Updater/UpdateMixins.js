/**
 * Create by lpy 2019.7.4
 * 升级业务的公共方法
 */
import { mapGetters } from 'vuex';
import config from '../../../comm/config.js';
import {isWinXp } from '../../../comm/is'
// const fs = require("fs");
// const yaml = require('js-yaml');
import fs from 'fs';
import yaml from 'js-yaml';

export default {
  data() {
    return {
      updateDescribe: '',
      isUpdateShow: false,
      updateInfo: {},
      updateUrl: '',
      isWaitCheck: true,
      isDownloadFinished: false,
      //defaultDownloadLocalUrl: `${homedir}/AppData/Roaming/Linkdood/`,  update.json及升级文件存放到dbpath中
      defaultDownloadLocalUrl: `${this.$dbPath}update/`,
      updateInfoTemp: {},
      updateTootip: {
        updateChecking: this.$t('upgrade.checking'),
        updateAvailable: this.$t('upgrade.checkAvaible'),
        updateNotAvailable: this.$t('upgrade.checkNotAvaible')
      },
    }
  },
  computed: {
    ...mapGetters([
      'user_updateAddr',
      'user_isCheckUpgrade',
      'contact_groupList'
    ]),
  },
  methods: {
    /**
     * 是否是web环境
     */
    _isWeb() {
      let agent = navigator.userAgent.toLowerCase();
      return agent.indexOf("electron") === -1;
    },
    /**
     * 监听检查更新事件
     * @bref: 主要用于监听“关于”页面触发的检查更新操作,以及注册SDK推送的升级信息回调
     */
    checkUpdateListener() {
      // 创建update文件夹，为下载升级配置文件做准备
      this.$Service.file.fileOperate({ filepath: `${this.$dbPath}update/`, type: 1 });
      // 监听用户点击“关于”升级
      this.$signalMonitor.$on('check-for-update', this._checkForUpdateHandler);
      // 监听服务升级推送
      // this.$Service.auth.regUpgrageCb(null, yml => this._regUpgrageCbHandler(yml, 'beijing'));
    },

    _checkForUpdateHandler() {
      //  设置当前正在检查更新，避免重复操作
      this.$store.commit('CHECK_UPGRADE_STATUS', true);

      /**
       * 判断是否是西安的版本，如果不是西安版本则调用预登录检测
       * 需要优化成通过Jenkins配置是否开启本地更新检测，不再通过是否是西安包来检测
       */
      if (this.$pkg.checkUpgrade || this.contact_groupList.hasOwnProperty('4336927693')) {
        console.log('开始西安升级检测')
        this._checkUpdateFromLocal().then(resps => {
          if (!resps) {
            //  如果失败则继续检查北京的升级
            this._checkUpdateFromNet().then(resp => {
              this._replayCheckUpdateState(resp);
            });
          }
        });
      } else {
        console.log('开始北京升级检测')
        this._checkUpdateFromNet().then(resp => {
          this._replayCheckUpdateState(resp);
        });
      }
    },

    /**
     * 由预登录的返回信息来判断是否需要更新
     */
    _checkUpdateFromNet() {
      if (this._isWeb()) {
        return new Promise;
      }
      return new Promise((resolve, reject) => {
        this.$Service.auth.prelogin({ server: this.auth_server }, resp => {
          this.$Service.log(`开始检测北京升级${resp.code}`);
          // setTimeout(() => {
          //   this._replayCheckUpdateState();
          // }, 10000);
          // if (resp.code !== 0) {
            resolve(resp);
            // return;
          // }
        });
      });
    },

    /**
     * 本地升级检测
     */
    _checkUpdateFromLocal() {
      return new Promise((resolve, reject) => {
        //  判断本地升级模式是否开启，后面优化为从pkg中读取开启开关，通过Jenkins配置控制
        // if (!this.$pkg.checkUpgrade) {
        //   //  关闭则需要检测北京升级
        //   resolve(true);
        //   return false;
        // }
        console.log('dbPath: ', this.$dbPath);
        //  下载升级描述文件
        this.isUpdateShow = false;
        this.updateInfo = null;
        let type = isWinXp ?"xplinkdood":"linkWork";
        this.updateUrl = `http://192.168.139.250/linkdood/${type}/`;
        let downloadParam = {
          flag: 0,
          url: `${this.updateUrl}update.json`,
          localPath: `${this.defaultDownloadLocalUrl}update.json`
        };
        console.log('download local update.json: ', downloadParam);
        this.$Service.file.downloadExternalFile(downloadParam, resp => {
          if (resp.code !== 0) {
            this.$Service.log(`升级描述文件下载失败：${resp.code}`);
            resolve(false);
            return;
          }
          this._downloadExternalFileHandler(resp, resolve);
        }, progress => {
          console.log('downloadExternalFile=======>progress', progress);
        });
      });
    },

    _downloadExternalFileHandler(resp, resolve) {
      console.log('in _downloadExternalFileHandler: ', resp);
      fs.readFile(`${this.defaultDownloadLocalUrl}update.json`, 'utf-8', (err, yml) => {
        //  如果失败
        if (err) {
          console.log('error=====>', err);
          this.$Service.log(`读取update.json文件内容：${JSON.stringify(err)}`)
          resolve(false);
          return;
        }
        yml = yaml.load(yml);

        this.$Service.log(`update.json文件内容：version:${yml.version},isForceUpdate:${yml.force}`);

        let updateVersion = yml.version && yml.version.split('.');
        let pkgVersion = this.$pkg.version.split('.');
        console.log(updateVersion, pkgVersion);
        let isUpdate = this._compareVersion(updateVersion, pkgVersion);
        // yml.ClientDefInfoStr = yml.ClientDefInfoStr.replace(/\;/g, '<br/>');
        if (isUpdate!==1) {
          resolve(false);
          return;
        }
        console.log('isUPdate:::', isUpdate)
        let hasChecked = this._regUpgrageCbHandler(yml, 'xian')
        resolve(hasChecked!==false)

        // this.updateInfo = yml;
        // this.updateInfo.version = 'V' + yml.version
        // this.updateInfo.message = yml.ClientDefInfoStr
        // this.updateInfo.isForceUpdate = yml.force === 1;
        // this.updateInfo.downloadNetUrl = this.updateUrl + yml.files[0].fileName;
        // this.updateInfo.downloadLocalUrl = this.defaultDownloadLocalUrl + yml.files[0].fileName;

        // // 如果已经下载过了，不需要重新下载，直接提示重启更新
        // let downloadParam = { filepath: this.updateInfo.downloadLocalUrl, type: 0 }
        // if (this.$Service.file.fileOperate(downloadParam)) {
        //   console.log('has been downloaded', this.updateInfo.downloadLocalUrl)
        //   this.isDownloadFinished = true
        // } else {
        //   console.log('need to download')
        //   this.isDownloadFinished = false
        // }
        // this.isUpdateShow = true;
        // this.$store.commit('CHECK_UPGRADE_STATUS', false);
        // resolve(true);
      });
    },

    _regUpgrageCbHandler(resp, pos) {
      console.log('升级推送:::', resp, this.user_isCheckUpgrade, pos);
      this.$Service.log(`升级推送: \n 
        地址：${resp.updateAddr}\n 
        升级类型：${resp.gradeType}\n 
        升级版本：${resp.version}\n 
        upAddr：${resp.upAddr && resp.upAddr.length}\n
        西安/北京升级：${pos}\n
        升级状态：${this.user_isCheckUpgrade}`);
      
      // 避免更新被吐槽多次提示升级，预登录只处理一次，但“关于”里的升级总是处理，重启后重置状态,用户点击稍后更新后，不再处理推送
      if (!this.user_isCheckUpgrade) {
        return false;
      }
      this.isUpdateShow = false;
      this.updateInfo = {};

      let resultUrl = '';
      resp.upAddr.forEach(element => {
        let index = -1;
        index = element.url && element.url.lastIndexOf('\/');
        if (index === -1) return false;
        this.$Service.log(`packageName:${element.url.substr(index + 1)}  ${pos}`);
        let packageName = element.url.substr(index + 1);
        if (this.$is.isWindows) {
          /**
           * 由于windows的安装包和升级包不是同一个，所以需要单独判断
           */
          if (packageName.indexOf('Update') === -1) {
            //  校验包名是否正确
            return false;
          }
        }

        /**
         * 由于预登录返回的下载地址有可能不是全路径（可能是考虑多通道环境）
         * 如果不是下载地址全路径，则需要单独拼接
         */
        let httpHead = '';
        if (element.url.indexOf('http') === -1) {
          httpHead = resp.updateAddr;
        }
        resultUrl = httpHead + element.url;
        console.log('resultUrl:::', resultUrl, pos);
        this.$store.commit('SET_UPDATE_ADDRESS', resultUrl);

        //  获取升级信息
        if (!resp.clientInfo) {
          return false;
        }
        console.log('i get clientInfo: ',resp.clientInfo, pos);
        try {
          let info = resp.clientInfo;
          if(typeof(resp.clientInfo) === 'string'){
            info = JSON.parse(resp.clientInfo);
          }
          console.log('info->',info, pos)
          if (info && info.ClientDefInfoStr) {
            console.log('ClientDefInfoStr->',info.ClientDefInfoStr, pos)
            let descr = info.ClientDefInfoStr;
            if(typeof(info.ClientDefInfoStr) === 'string'){
              info.ClientDefInfoStr = info.ClientDefInfoStr.replace(/\\/g, '').replace(/\n/g, '<br/>');
              descr = JSON.parse(info.ClientDefInfoStr);
            }
            console.log('descr->',descr, pos)
            this.updateDescribe = descr && descr.describe;
          }
        } catch (error) {
          console.log('error::::', error);
          return false;
        }

        this.updateInfoTemp = {
          message: this.updateDescribe || 'no message',
          version: resp.version,
          downloadNetUrl: resultUrl,
          isForceUpdate: resp.gradeType === 1,
          downloadLocalUrl: this.defaultDownloadLocalUrl + packageName
        }

        this.$Service.log(`downloadLocalUrl:::${this.updateInfoTemp.downloadLocalUrl} ${pos}`);
        let downloadParam = { filepath: this.updateInfoTemp.downloadLocalUrl, type: 0 };
        this.isDownloadFinished = this.$Service.file.fileOperate(downloadParam);
        
        if (!this.isUpdateShow) {
          this._replayCheckAboutFinished('')
          this.updateInfo = this.updateInfoTemp;
          this.isUpdateShow = true;
          this.$Service.log(`CHECK_UPGRADE_STATUS:::false:::avoid upgrade for repeat while prelogin ${pos}`)
          this.$store.commit('CHECK_UPGRADE_STATUS', false)
          return true
        }
        return false
      });
    },

    /**
     * 通知更新检测完毕
     */
    _replayCheckUpdateState(resp) {
      console.log('prelogin:::::resp:::::', resp)
      try {
        if (resp.code===0&&JSON.parse(resp.json).upd) {
          this._replayCheckAboutFinished(this.updateTootip.updateAvailable)
        } else {
          this._replayCheckAboutFinished(this.updateTootip.updateNotAvailable)
        }
      } catch (error) {
        this._replayCheckAboutFinished(this.updateTootip.updateNotAvailable)
      }
    },

    _replayCheckAboutFinished(msg) {
      this.$signalMonitor.$emit('update-finished', msg);
    },

    /**
     * 对比版本号，判断是否需要升级
     * @param: ver1 待判断的第一个版本号
     * @param: ver2 待判断的第二个版本号
     * @return: -1: ver1 < ver2, 0: ver1 == ver2, 1: ver1 > ver2 
     */
    _compareVersion(ver1, ver2) {
      let minLength = Math.min(ver1.length, ver2.length);
      for (let i = 0; i < minLength; i++) {
        if (parseInt(ver1[i]) > parseInt(ver2[i])) { 
          return 1;
        } else if (parseInt(ver1[i]) < parseInt(ver2[i])) { 
          return -1
        } else { // 相等则继续比较
          continue;
        }
      }
      return 0;
    }
  }
};
