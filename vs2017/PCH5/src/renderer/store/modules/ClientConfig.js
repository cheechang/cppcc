import Vue from 'vue';
const clientConfig = {
  state: {
    auth: {
        openLanguageSet:false,
        openForgetPwd:false,
        openRegister:false,
        openHighSetting:false,
        openAutoLogin:false,
        openRemeberPwd:false,
        openServerIntro:false,
    },
    user:{
      openNickId:false,
      openTrayTip:false
    },
    system:{
      openSpecialTheme:false, // 是否开启特殊主题
      disableWebview:false, // 是否禁用加载webview(首页/工作台)
    },
    chat:{
      openSendLocationMsg:false, //是否开启发送位置消息
    },
  },
  mutations: {
    SET_CLIENTCONFIG_AUTH(state, data) {
        Vue.set(state.auth, data.key, data.value);
    },
    SET_CLIENTCONFIG_USER(state, data) {
      Vue.set(state.user, data.key, data.value);
    },
    SET_CLIENTCONFIG_SYSTEM(state, data) {
      Vue.set(state.system, data.key, data.value);
    },
    SET_CLIENTCONFIG_CHAT(state, data) {
      Vue.set(state.chat, data.key, data.value);
    },
  }
};

export default clientConfig;
