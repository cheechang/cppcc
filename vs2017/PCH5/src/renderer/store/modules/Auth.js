import Vue from 'vue';
const auth = {
  state: {
    loginType: [],
    loginInfos: [],
    loginServers: [],
    server: '',
    serverVersion: '',
    nationCode: '',
    userHeadImgPath: '',
    onlineStatus: -1,
    queryExtendedField:{},
    multipleServers:{},  //多服务器信息
    /**
     * 用于忘记密码登录引导用户修改密码得标识
     */
    loginByForgetPwd: {
      isChangePwd: false,
      isForgetPwdLogin: false,
      loginInitForget: false,
      account: ''
    }
  },
  mutations: {
    SET_MULTIPLE_SERVER(state,data){
      switch (data.flag) {
        case 0: {
          state.multipleServers = {};
          data.val.forEach((element, i) => {
            Vue.set(state.multipleServers, element.userId, element);
          });
          break
        }
        //修改该服务账号
        case 1: {
            Vue.delete(state.multipleServers, data.val.userId);
            Vue.set(state.multipleServers, data.val.userId, data.val);
            break
        }
        //删除该服务账号
        case 2: {
            Vue.delete(state.multipleServers, data.val);
            break
        }
      }
    },
    SET_EXTENDEDFIELD(state, data){
      state.queryExtendedField = data;
    },
    SET_LOGINTYPE(state, data) {
      state.loginType = data;
    },
    SET_SERVER(state, data) {
      state.server = data;
    },
    SET_NATIONCODE(state, data) {
      console.log(data);
      state.nationCode = data;
    },
    SET_LOGININFOS(state, data) {
      state.loginInfos = data;

    },
    SET_LOGINSERVERS(state, data) {
      state.loginServers = [...data];
    },
    INIT_LOGININFOS(state, data) {
      data.isAutoLogin = 0;
      data.isRemberPass = 0;
      Vue.set(state.loginInfos, 0, data)
    },
    SET_HEADIMG_PATH: (state, data) => {
      state.userHeadImgPath = data;
    },
    SET_SERVERVERSION: (state, data) => {
      state.serverVersion = data;
    },
    SET_LOGIN_BY_FORGETPWD: (state, data) => {
      switch (data.flag) {
        case 0: {state.loginByForgetPwd.isForgetPwdLogin = data.val;break}
        case 1: {state.loginByForgetPwd.loginInitForget = data.val;break}
        case 2: {
          console.log(data);
          state.loginByForgetPwd.account = data.val;
          break
        }
        case 3: {
          state.loginByForgetPwd.isChangePwd = data.val;
        }
      }
    },
    // 设置在线状态
    SET_ONLINE_STATUS: (state,data) => {
      state.onlineStatus = data;
    },
    INIT_LOGIN_BY_FORGETPWD: (state) => {
      state.loginByForgetPwd.isForgetPwdLogin = false;
      state.loginByForgetPwd.loginInitForget = false;
      state.loginByForgetPwd.isChangePwd = false
      state.loginByForgetPwd.account = ''
    }
  }
};

export default auth;
