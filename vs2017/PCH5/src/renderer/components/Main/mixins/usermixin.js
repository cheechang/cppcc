/**
 * @file      Manages the user's infomation for the main page.
 * @author    linpeiyuan <linpeiyuan@vrvmail.com.cn>
 * @copyright Beijing VRV Software Co.,Ltd
 * 
 * @mixin
 */ 
import {mapGetters} from 'vuex';
import PresentTipByFlag from '../../../utils/TipByFlag.js';
import AccountMixin from "../../Account/AccountMixin.js";
import { getTextWidth} from '../../Chat/At/at.js'
import { getCurrentDate } from '../../../utils/utils.js'
// import { makeWatermark } from "../../../../comm/images.js";
const mixin = {
  mixins: [AccountMixin],
  data () {
    return {
      desigComponent: '',
      isAccountCenter: false,   //  是否是个人中心页面
      isAnimationStart: false,  //  个人中心界面出现的动画
      defaultLeftTab: 'UserInfo'  //  个人中心页面默认显示的tab项
    };
  },
  computed: {
    ...mapGetters([
      'user_account',
      'user_serverstat',
      'auth_loginByForgetPwd',
      'user_loginInfo'
    ])
  },
  methods: {
    /**
     * @breif 显示用户中心
     * @param {string} - 
     */
    showAccount(e){
      this.desigComponent = e;
      this.isAccountCenter = true;
    },

    /**
     * @breif 隐藏个人中心，避免无法跳转路由
     */
    hideAccountCenter(){
      this.isAccountCenter=false;
      this.isAnimationStart=false;
    },
    /**
     * @breif 个人中心页面切换动画
     */
    animationStart() {
      if (this.isAccountCenter) {
        this.isAnimationStart = true;
      }
    },
    /**
     * 获取水印
     * @param {Object} - {parentId: -2, dicKey: 'watermarkConfig'}
     */
    getWaterMark() {
      this.$Service.contact.queryExtendedField(
        {parentId: -2, dicKey: 'watermarkConfig'}, this._getWaterMarkHandler);
    },
    _getWaterMarkHandler(resp) {
      //  判断是否开启了水印
      if (!resp.EnterpriseDictionarys[0] || !resp.EnterpriseDictionarys[0].extend) {
        // 兼容旧版本水印开关
        this.oldUpdateWaterMark(this.user_account.name);
        return;
      }
      let configObj = null;
      try {
        configObj = JSON.parse(resp.EnterpriseDictionarys[0].extend);
        if (!configObj) {
          return;
        }
      } catch(error) {
        this.$Service.log(`获取到的明水印配置有误,extend:${resp.EnterpriseDictionarys[0].extend}`);
        return; 
      }

      //  判断是否开启了显示明水印
      if (configObj.isOpen !== 1) {
        this.$Service.log(`后台配置未开启显示明水印:${configObj.isOpen}`);
        return;
      }

      let markInfo = '';
      //  判断是否配置了名称
      if(configObj.name === 1){ //配置显示昵称
        markInfo += this.user_account.name;
      }

      //  判断是否要显示手机号
      if (configObj.phone === 1) {
        //  获取手机号
        let phone = this.user_account.accounts.find((item, index, arr) => {
          return item.type === 1;
        }); 
        if (phone) {
          markInfo += `_${phone.accounts}`;
        }
      }

      //  判断是否需要显示部门
      if (configObj.department === 1) {
        this.$Service.enterprise.queryEntUserOneById({flag:0,userId:this.user_account.id}, resp => {
          if (resp.code !== 0 || resp.users.length === 0) {
            return;
          }

          markInfo += `_${resp.users[0].orgName}`;
          this._setWaterMark(markInfo);
        });
        return;
      }
      this._setWaterMark(markInfo);
    },
    // 兼容旧版本更新用户水印
    oldUpdateWaterMark(name) {
      this.$Service.contact.queryExtendedField(
        { parentId: -2, dicKey: "isOpenWatermark" },
        respOld => {
          console.log(`查询水印旧版本:`, respOld);
          if (
            respOld.EnterpriseDictionarys[0] &&
            respOld.EnterpriseDictionarys[0].extend === "1"
          ) {
            //服务器是否配置了开启水印
            this._setWaterMark(name)
          }
        }
      );
    },
    _setWaterMark(info) {
      let textWidth = getTextWidth('14px','Microsoft YaHei',`${info}`).width;
      let watermark = this.makeWatermark(info,textWidth); //生成水印
      this.$store.commit('UPDATE_WATER_MARK', watermark);
    },
    makeWatermark(name,textWidth){
      let canvas = document.createElement('canvas');
      let canvasWidth = textWidth < 150 ? 150 :textWidth;
      canvas.width= canvasWidth*2;
      canvas.height=150;
      let ctx = canvas.getContext('2d');
      ctx.clearRect(0,0,canvas.width,canvas.height); 
        //    var gradient=ctx.createLinearGradient(0,0,canvas.width,0);
        //    gradient.addColorStop("0","black");
        
        // // Fill with gradient
        //    ctx.fillStyle=gradient;
        //    ctx.fillStyle = "rgba(0, 0, 0,1)";
      ctx.font="normal 14px Microsoft YaHei";
      if(textWidth < 150){
       let leftpadding = (150-textWidth)/2;
       ctx.fillText(name,leftpadding,14); 
       ctx.fillText(name,canvasWidth + leftpadding,88);
      }
      else{
       ctx.fillText(name,0,14); 
       ctx.fillText(name,canvasWidth,88);
      }
      return this.$is.isWinXp?canvas.toDataURL("image/png"):canvas.toDataURL("image/webp");
    },
    /**
     * 个人中心的注销或退出事件响应函数，监听 'logout-or-quit'事件
     * @param {object} e 
     * @param {object} arg 
     */
    logoutOrQuit(e, arg) {
      console.log('arg', arg.type);
      arg.type === 'quit' ? this.quit() : this.logout();  // 在AccountMixin中
    },

    /**
     * 用户模块相关的推送接口注册
     */
    regUserNotify() {
      this.regReLoginCb();
      this.regPresentCb();
      this.regGetMyselfCb();
      this.regOperateUserCb();
      this.regUserHeadImgUpdateCb();
      this.getAccountInfo();
    },

    /**
     * 重新登录通知
     */
    regReLoginCb() {
      this.$Service.auth.regReLoginCb(null, this._regReLoginCbHandler);
    },
    _regReLoginCbHandler(resp) {
      if ([0, -1, -16777165].includes(resp.code)) {
        if (resp.code === -16777165) {
          return;
        }
        if (resp.code === -1 && this.user_serverstat) {
          //  提示用户无法连接服务器
          this.$ipc.send('netChanged', 
          {
            title: this.$t('common.netError'), 
            body: this.$t('common.cantConnSer')
          });
        }

        this.$store.commit('SET_SERVERSTATE', resp.code);
        this.$ipc.send('subWin-netstatus-app', resp.code === 0);
        return;
      }

      //  如果是其他的类型，则需要弹框处理
      //  先判断是否已经存在了提示框
      if (localStorage.hasOwnProperty('is-regDialog')) {  //  防止重复弹框
        return;
      }
      localStorage.setItem('is-regDialog', 'dialog');
      this.$dialog.alert(
        {
          message: getErrorMsg(code),
          confirmText: this.$t('common.confirm'),
          onConfirm: () => {
            this.$ipc.send('close-all-subWin');
          }
        }
      );
    },

    /**
     * 个人头像更新通知
     */
    regUserHeadImgUpdateCb() {
      this.$Service.user.regUserHeadImgUpdateCb(null, this._regUserHeadImgUpdateCbHandler);
    },
    _regUserHeadImgUpdateCbHandler(resp) {
      console.log('_regUserHeadImgUpdateCbHandler:::::', resp)
      if (resp.haedpath === this.user_account.thumbAvatar) {
        return;
      }
      this.$store.commit('UPDATE_ACCOUNT', resp);
    },

    /**
     * 账号状态推送
     * @description - flag -1 被挤下线 7 密码已经修改 10 后台删除了账号 11 后台冻结账号(在reloginHandle进行处理)
     */
    regPresentCb() {
      this.$Service.contact.regPresentCb(null, this._regPresentCbHandler);
    },
    _regPresentCbHandler(resp) {
      if (this.user_account.userId !== resp.userID) {
        this._buddyonlineHandler(resp);
        return;
      }
      //  如果是自己修改密码，则不用提示
      //  TODO: 可以统一命名，该命名有歧义
      if (this.auth_loginByForgetPwd.isChangePwd) {
        return;
      }

      if (resp.flag === 7) {
        this.$store.commit('SET_LOGIN_BY_FORGETPWD', { flag: 3, val: true });
      }
      
      if (
        (resp.flag === -1 && resp.deviceType === 1) || [7, 10, 11, 12, 13].includes(resp.flag)
      ) {
        let getPresentTipByFlag = new PresentTipByFlag();
        this.$dialog.confirm({
          confirmText: this.$t('auth.relogin'),
          cancelText: this.$t('auth.quit'),
          disableClickOutside: true,
          //调用函数
          message: getPresentTipByFlag.getPresentTipByFlag(resp.flag),
          onConfirm: () => {
            this._exitMultipleServers(); //退出其他服务器
            this.$ipc.send('close-all-subWin');
          },
          onCancel: () => {
            this._exitMultipleServers(); //退出其他服务器
            this.delTempFiles(); // 清除缓存数据
            this.$ipc.send('exit-app');
          }
        });
        return;
      }

      if (resp.flag === 14) {
        //  手机控制PC下线
        this.$ipc.send('close-all-subWin');
        this._exitMultipleServers(true); //退出当前服务
        this.$dialog.confirm({
          confirmText: this.$t('common.confirm'),
          disableClickOutside: true,
          canCancel:false,
          message: this.$t('auth.exitByPhone', {value: getCurrentDate()}),
        });
      }
    },

    /**
     * @brief 联系人在线状态更新
     * @param {object} - resp
     */
    _buddyonlineHandler(resp) {
      if (!this.$config.account.openOnlineStatus) {
        return;
      }
      // 处理他人在线状态
      console.log('好友在线状态更新', resp.flag === 1 ? '在线' : '离线');
      // this.$store.dispatch('UPDATE_CONTACT_ONLINES', resp);
      if (resp.flag === -1 || resp.flag === 1) {
        // 处理离线在线情况
        this.$store.dispatch('SET_CONTACTS_STATES', resp);
      }
    },

    /**
     * @brief 调用getMyself接口口后的用户信息推送
     * @return {object} - resp
     */
    regGetMyselfCb() {
      this.$Service.user.regGetMyselfCb(null, this._regGetMyselfCbHandler);
    },
    _regGetMyselfCbHandler(resp) {
      this._operateUserInfo(resp);
    },

    /**
     * @breif 主动拉取用户信息
     * @todo 放至导航栏用户头像组件处
     */
    getAccountInfo() {
      this.$Service.user.getAccountInfo(null, resp => {
        this._operateUserInfo(resp);
      });
    },

    /**
     * @breif 用户信息修改推送通知
     * @todo 放至导航栏头像组件处
     */
    regOperateUserCb() {
      this.$Service.user.regOperateUserCb(null, resp => {
        this._operateUserInfo(resp);
      });
    },
    
    /**
     * @brief 给数据库中的登录信息设置用户具体信息
     * @param {object} - info {account, phone, thumbAvatarUrl}
     */
    _setLoginInfo(info) {
      let avatar = info.thumbAvatarUrl.replace(/\//g, () => {return '_';});
      if (this.user_loginInfo.hasOwnProperty('name')) {
        //  如果存在name属性 说明已经存储过
        if (this.user_loginInfo.name === info.account && 
            this.user_loginInfo.phone === info.phone &&
            this.user_loginInfo.user_icon === avatar) {
          //  数据没有变化，不需要存储
          return;
        }
      }
      let loginInfo = {
        phone: info.phone,
        name: info.account,
        user_icon: avatar
      };

      loginInfo = Object.assign(loginInfo, this.user_loginInfo);
      //  通知托盘显示名称变化
      this.$ipc.send('tray-username', {
        name: info.name,
        server: loginInfo.server
      });
      this.$store.commit('SET_LOGININFO', loginInfo);
      loginInfo.server = `${info.server};${this.user_usever}`;
      loginInfo.email = this._makeAccountsJson();

      //  存入数据库中
      this.$Service.config.setLoginInfo(loginInfo, resp => {
        this.$store.commit('INIT_LOGININFOS', loginInfo);
      });
    },

    /**
     * @breif 获取该账号所有的登录类型及账号信息
     * @return {string} - 返回所有账号信息拼成的字符串，格式为 'usertype1,account1;usertype2,account2'
     */
    _makeAccountsJson() {
      let ret = '';
      for (let account of this.user_account.accounts.values()) {
        if (ret) {
          ret += ';';
        }
        ret += `${account.type},${account.accounts}`;
      }
      return ret;
    },

    _operateUserInfo(info) {
      this.$store.commit('SET_ACCOUNT', info);
      // this._setLoginInfo(info);
      this.setUserLoginInfo(info)
    },

    /**
     * @breif 获取用户本地配置
     */
    getUserLocalConfig() {
      this.$Service.rtcplugin.SetNotifySwitch('on');
      let keys = Object.keys(this.$config.account.localSetting);
      this.$Service.user.getLocalSetting(keys, this._getLocalSettingHandler);
    },
    /**
     * @breif 获取用户本地配置项
     * @param {object} - resp 详见SDK接口说明文档
     */
    _getLocalSettingHandler(resp) {
      console.log('_getLocalSettingHandler::::', resp)
      if (resp.code !== 0 || resp.settings.length === 0) {
        return;
      }

      let settingsObj = {
        top_apps: (obj) => {
          // 兼容原有的本地appid，避免版本更新后原有的置顶信息丢失
          obj.value = obj.value.replace('1000001', '1000000002');
          obj.value = obj.value.replace('1000003', '1000000001');
          obj.value = JSON.parse(obj.value);
        },
        msg_remind: (obj) => { obj.value = Number(obj.value);},
        media_remind: (obj) => { this.$Service.rtcplugin.SetNotifySwitch(obj.value) },
        screenshot_key: (obj) => {
          obj.value = this.$is.isOSX ? obj.value.replace('CommandOrControl', 'Command') : obj.value.replace('CommandOrControl', 'Ctrl');
        }
      };

      for (let i of resp.settings) {
        settingsObj[i.key] && settingsObj[i.key].call(this, i);
        this.$store.commit('SET_USER_LOCALCONFIG', {
          key: i.key,
          value: i.value
        });
        this.$store.commit('SET_USER_LOCALCONFIG', {
          key: this.$config.account.localSetting[i.key],
          value: true
        });
      }
      this._setScreenShotKey();
    },

    /**
     * @breif 设置全局截图快捷键
     */
    _setScreenShotKey() {
      if (this.$is.isOSX) {
        // 在主进程用electron进行截图快捷键注册
        this.$ipc.send('globalRegisterKey', {
          key: 'register-shortcuts',
          value: this.user_localConfig.screenshot_key
        });
        // 在主进程用electron进行截图时,设置是否隐藏当前窗口
        this.$ipc.send('globalRegisterKey', {
          key: 'register-shortcuts-hideWindow',
          value: this.user_localConfig.screen_display === 'HIDE'
        });
        return;
      }

      //  windows && linux
      setTimeout(() => {
        //向截图程序设置快捷键截图时是否隐藏窗口
        this.$Service.config.setScreenDisplay({
          hide: this.user_localConfig.screen_display === 'HIDE'
        });
      }, 500);
      this.$Service.config.setScreenShotHotKey({key: this.user_localConfig.screenshot_key}, resp => {
        this.$store.commit('SET_USER_LOCALCONFIG', {
          key: 'screenShotKeyConflict',
          value: resp.code !== 0
        });
      });
    }
  },
};

export default mixin;