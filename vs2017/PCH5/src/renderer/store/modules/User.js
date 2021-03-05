import Vue from "vue";
// import config from 'vrv-static/data/config.json';
import config from './../../../comm/config.js';
import {
  isOSX
} from '../../../comm/is.js';
const user = {
  state: {
    /**
     * 用户账户信息
     */
    account: {
      userId: '',
      name: '',
      email: '',
      avatar: '',
      nickId: '',
      phone: '',
      sign: '',
      gender: '',
      birthday: '',
      address: '',
      job: '',
      department: '',
      themeId: ''
    },
    /**
     * 用户水印
     */
    userWatermark: '',
    /**
     * 开启暗水印
     */
    userDarkWaterMark: false,
    /**
     * 用户聊天图片保存路径
     */
    userImgPath: '',
    /**
     * 用户聊天文件保存路径
     */
    userFilePath: '',
    /**
     * 用户语音聊天文件保存路径
     */
    userAudioPath: '',
    userVideoPath: '',
    userWebLinkParse: '',
    /**
     * 用户网络状态
     */
    userNetstat: true,
    /**
     * 用户服务状态
     */
    userServerstat: true,
    /**
     * 用户登录信息
     */
    userLoginInfo: {},
    /**
     * 升级服务地址
     */
    updateAddr: '',
    /**
     * 是否检测升级
     */
    isCheckUpgrade: true,
    /**
     * 多通道/预登录地址
     */
    httpHead: {
      appUrl: ''
    },
    /**
     * 密码规则
     */
    pwdRule: {},
    /**
     * 敏感词模式
     * '0' 不过滤 '1' *星号替换  '2' 不允许发送
     */
    badKeyMode: '',
    /**
     * 用户本地配置集合
     */
    userLocalConfigData: {
      userServer_for_auth_request: '', // 用户当前的登录服务器
      thirdParty_authRequestInfo: '', // 第三方请求授权

      isSendMsgKey: false, // 判断本地数据库是否配置发送消息快捷键
      send_msg_key: 'ENTER', // 默认发送消息快捷键

      isMsgRemind: false, // 判断本地数据库是否配置消息提醒
      msg_remind: 0, // 0: '接受消息并提醒', 1: 不通知仅显示数字 2：免打扰

      isSoundRemind: false, // 判断本地数据库是否配置消息声音提醒
      sound_remind: 'OPEN', // OPEN: 开启声音；CLOSE: 关闭提醒

      isTrayTip: false,     // 判断本地数据库是否配置托盘消息通知
      tray_tip: 'CLOSE',     // OPEN: 开启通知；CLOSE: 关闭通知

      isOnlineRemind: false, // 判断本地数据库是否配置好友上线提心
      online_Remind: true, // 默认还有上线声音提醒

      screenShotKeyConflict: false, //截屏快捷键冲突
      isScreenshotKey: false, // 判断本地数据库是否配置截屏快捷键
      screenshot_key: isOSX ? config.prtSc.osx : config.prtSc.windows, // 默认截屏快捷键

      isTopApp: false, // 判断本地是否有设置app置顶记录
      top_apps: [],

      isMediaRemind: false, // 判断本地是否配置有音视频消息提醒设置
      media_remind: 'on',

      editBox_mode: config.chat.edit.mode[0].key, // 会话编辑框模式
      isEditBoxMode: false, // 判断本地是否配置了此选项

      screen_display: 'NORMAL', // 截屏时是否隐藏豆豆窗口 NORMAL：正常；HIDE：隐藏
      isScreenDisplay: false // 判断本地是否配置过此项，用户在设置时判断调用更新接口还是设置接口；
    },
    userSystemConfig: '',
    defaultPage: '', //首页不显示时，记录后台配置的默认页
    usever: '',
    serverHost: '',
    apHost: '', // 预登录返回的apHost
    userFieldName: '', //  豆豆号名称，由预登录返回的登录类型配置获取
    groupToneList: null, // 用户群提示音列表
  },

  mutations: {
    CHECK_UPGRADE_STATUS: (state, data) => {
      state.isCheckUpgrade = data;
    },
    SET_USER_FIELD_NAME: (state, data) => {
      state.userFieldName = data;
    },
    CLEAR_ACCOUNT_INFO: (state, data) => {
      state.userLoginInfo = data
    },
    SET_SYSTEM_CONFIG: (state, data) => {
      state.userSystemConfig = data;
    },
    SET_DEFAULTPAGE: (state, data) => {
      state.defaultPage = data;
    },
    SET_PRELOGIN_USEVER: (state, data) => {
      state.usever = data;
    },
    SET_PRELOGIN_SERVERHOST: (state, data) => {
      state.serverHost = data;
    },
    SET_PRELOGIN_APHOST: (state, data) => {
      state.apHost = data;
    },
    SET_UPDATE_ADDRESS: (state, data) => {
      state.updateAddr = data
    },
    SET_PWDRULE: (state, data) => {
      state.pwdRule = data;
    },
    SET_NETSTATE: (state, code) => {
      state.userNetstat = code === 0;
    },
    SET_SERVERSTATE: (state, code) => {
      state.userServerstat = code === 0;
    },
    SET_ACCOUNT: (state, data) => {
      data.phone = data.phone.substring(4);
      state.account = data;
      state.account.userId = data.id;
    },
    UPDATE_ACCOUNT: (state, data) => {
      state.account = {
        ...state.account,
        thumbAvatar: data.haedpath
      };
    },
    UPDATE_WATER_MARK: (state, data) => {
      state.userWatermark = data;
    },
    UPDATE_DARK_WATER_MARK: (state, data) => {
      state.userDarkWaterMark = data;
    },
    UPDATE_IMG_PATH: (state, data) => {
      state.userImgPath = data;
    },
    UPDATE_FILE_PATH: (state, data) => {
      state.userFilePath = data;
    },
    UPDATE_AUDIO_PATH: (state, data) => {
      state.userAudioPath = data;
    },
    UPDATE_VIDEO_PATH: (state, data) => {
      state.userVideoPath = data;
    },

    SET_WEB_LINK_PARSE: (state, data) => {
      console.log('data:::', data)
      state.userWebLinkParse = data;
    },

    SET_LOGININFO: (state, data) => {
      state.userLoginInfo = Object.assign({}, data);
      console.log(state.userLoginInfo, 'SET_LOGININFO in user vuex');
    },
    SET_HTTPHEAD: (state, data) => {
      state.httpHead = Object.assign(state.httpHead, data);
    },
    /**
     * 设置敏感词模式
     * @param {string} mode '0' 不过滤 '1' *星号替换  '2' 不允许发送
     */
    SET_BAD_KEY_MODE: (state, mode) => {
      state.badKeyMode = mode;
    },
    SET_USER_LOCALCONFIG: (state, data) => {
      if (data.value == 'false') data.value = false;
      if (data.value == 'true') data.value = true;
      if (data.key === 'editBox_mode' && config.chat.edit.mode.length === 1) return;
      Vue.set(state.userLocalConfigData, data.key, data.value);
    },
    /**
     * 切换账号初始化配置字段
     */
    CLEAR_USER_LOCALCONFIG: (state) => {
      state.userLocalConfigData.isSendMsgKey = false;
      state.userLocalConfigData.send_msg_key = 'ENTER';
      state.userLocalConfigData.isMsgRemind = false;
      state.userLocalConfigData.msg_remind = 0;
      state.userLocalConfigData.isSoundRemind = false;
      state.userLocalConfigData.sound_remind = 'OPEN';
      state.userLocalConfigData.isTrayTip = false;  
      state.userLocalConfigData.tray_tip = 'CLOSE';
      state.userLocalConfigData.isOnlineRemind = true;
      state.userLocalConfigData.online_Remind = true;
      state.userLocalConfigData.isScreenshotKey = false;
      state.userLocalConfigData.screenShotKeyConflict = false;
      state.userLocalConfigData.screenshot_key = isOSX ? config.prtSc.osx : config.prtSc.windows;
      state.userLocalConfigData.isMediaRemind = false;
      state.userLocalConfigData.media_remind = 'on';
      state.userLocalConfigData.isTopApp = false;
      state.userLocalConfigData.top_apps = [];
      state.userLocalConfigData.editBox_mode = config.chat.edit.mode[0].key;
      state.userLocalConfigData.isEditBoxMode = false;
      state.userLocalConfigData.screen_display = 'NORMAL';
      state.userLocalConfigData.isScreenDisplay = false;
      state.userWatermark = '';
      state.userServerstat = true;
      state.userNetstat = true
    },
    /**
     * 个人中心恢复默认
     */
    RESET_USERCONFIG: (state) => {
      state.userLocalConfigData.screen_display = 'NORMAL';
      state.userLocalConfigData.isScreenDisplay = false;
      state.userLocalConfigData.isSendMsgKey = false;
      state.userLocalConfigData.send_msg_key = 'ENTER';
      state.userLocalConfigData.isScreenshotKey = false;
      state.userLocalConfigData.screenShotKeyConflict = false;
      state.userLocalConfigData.screenshot_key = isOSX ? config.prtSc.osx : config.prtSc.windows
    },
    /**
     * 清除用户账户信息
     */
    CLEAR_USER_ACCOUNT: (state) => {
      for (let key in state.account) state.account[key] = '';
    },
    /**
     * 设置群提示音列表
     */
    SET_GROUPTONE: (state, data) => {
      console.log("更新的列表为：", data);
      state.groupToneList = JSON.parse(JSON.stringify(data));
    }
  },
  actions: {
    SET_GROUPTONES: (context, resp) => {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit('SET_GROUPTONE', resp);
          resolve();
        }, 0);
      })
    }
  }
};

export default user;
