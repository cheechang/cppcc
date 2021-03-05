import Vue from 'vue';
import { mapGetters } from 'vuex';
import { getErrorMsg } from '../../../utils/utils.js';
/**
 * 登录模块 公共变量、方法、vuex数据
 */ 
const FIELD_NAME_KEY = '6';
const mixin = {
  data() {
    return {
      isLoading: false,
      isCodeLoading: false,
      isAutoLogin: 0,
      isRemberPass: 0,
      account: '',
      password: '',
      isActivateModal: false,
      isVerfyShow: false,
      errorMsg: '',
      isErrorBox: false,
      isSuccess: false,
      regCode: this.$t('auth.getVerifyCode'),
      isCodeSend: false,
      clock: null,
      verifyImg: '',
      loginRespCode:0,
      info: {
        user: '',
        pwd: '',
        server: '',
        userType: 1,
        nation: '0086',
        userId: '',
      },
      // 本地配置的登录方式，以前在配置文件config.js中
      localLoginTypes:[
        {way: this.$t('user.phone'), type: 1},
        {way: this.$t('user.email'), type: 3},
        {way: this.$t('user.dou'), type: 6},
        {way: this.$t('user.customize'), type: 7},
        {way: this.$t('auth.VerCodeLogin'), type: 96}
      ]
    }
  },
  created(){
    // 初始化oauth
    this.initOauth();
  },
  computed: {
    ...mapGetters([
      'auth_nationCode',
      'auth_server',
      'auth_loginByForgetPwd',
      'auth_loginInfos'
    ]),
    /**
     * 禁用登录按钮
     * @returns - 是/否 只有当用户名和密码输入栏全部有值时，才会返回false，否则返回true
     */
    isDisable() {
      return this.account === '' || this.password === '' || !this.invalidNationCode;
    },
    /**
     * 国家码是否合法
     */
    invalidNationCode() {
      if (this.currentInfo || this.auth_loginByForgetPwd.isForgetPwdLogin) {
        return true; // 有当前信息时 为二次登陆 或 忘记密码/更换设备 返回true
      };
      // 首次登陆 验证返回
      return (this.nationCode === `+${this.nationCodeText.replace(/\b(0+)/gi,'')}`) && (JSON.stringify(this.$i18n.messages[`${this.$i18n.locale}`].AreaCode).indexOf(this.nationCodeText) > -1);
    },
    // 登录等待动画
    lodingState() {
      return this.isLoading ? 'is-loading' : '';
    },

    // 获取验证码等待动画
    codelodingState() {
      return this.isCodeLoading ? 'is-loading' : '';
    },

    // 获取验证码按钮能否点击
    isCodeDisabled() {
      return this.account != '' && !this.isCodeSend;
    }
  },
  watch: {
    // 当选中自动登录后，记住密码按钮置为选中状态
    isAutoLogin(val) {
      if (val === 1) this.isRemberPass = 1
    },
    // 取消记住密码后，自动登录按钮置为空
    isRemberPass(val) {
      if (val === 0) this.isAutoLogin = 0
    },
    // 当用户清空账号时，清空已填写的密码
    // account() {
    //   set
    //   this.password = ''
    // }
  },
  methods: {
    clearPwd() {
      this.password = ''
    },
    
    /**
     * 登录
     * @param {*} info - 登录信息，详见/render/IpcHandler/interface.ts定义
     */
    login(param) {
      console.log('登录参数:::', this.info);
      if (this.invalidMobile(this.info.userType, this.info.user)) return;
      if (this.nationCode && this.invalidMobile(this.info.userType, this.nationCode.slice(1))) return;
      this.isLoading = true;
      this.$emit('is-shading', true); //  开启遮罩，防止触发回车操作
      if (param === undefined) {
        console.log('in login::', this.info);
        let logData = Object.assign({}, this.info);
       // this.$delete(logData, 'pwd');
        this.$Service.log(`认证:::手动登录入参:::${JSON.stringify(logData)}`);
        if (this.info.userType === 94) {
          console.log('JSON.stringify(this.info):', JSON.stringify(this.info))
          // 进行oauth请求
          this.$oauth.call({type:1,json: JSON.stringify(this.info)});
        } else {
          this.$Service.auth.login(this.info, this._loginHandler);
        }
        return;
      }
      this.$Service.log(`认证:::自动登录入参:::${JSON.stringify(param)}`);
      this.$Service.auth.autoLogin(param, this._loginHandler);
    },

    /**
     * 登录结果回调
     * @param {*} resp - 调用SDK登录接口返回信息，详见/render/IpcHandler/interface.ts定义
     */
    _loginHandler(resp) {
      this.$Service.log(`认证:::登录返回:::${JSON.stringify(resp)}`);
      console.log(resp);
      //多服务的子服务器登录
      if(this.$serversLoginParam){
        let key = null;
        if(resp.code === 0){
          key = `${resp.userId}@${this.info.server}`;
        }
        this.$mutipleServers.postLoginResult(resp.code,key);
      }
      // resp.code = 1303;
      if (resp.code !== 0 && resp.code !==1303) {
        //if(resp.code !== 1303){
          this.isLoading = false;
        //}
        this.$emit('is-shading', false);
        this._loginFailedHandler(resp);
        return;
      }
      // 存储登录返回值,处理账号(1303)激活
      this.loginRespCode = resp.code; 
      document.onkeydown = null;
      this._loginSuccessedHandler(resp.userId);
    },
    _onEnterEvent(handler) {

      document.onkeydown = e => {
        if (this.isLoading || this.isVerfyShow || this.isDisable) {
          //  登录或这弹出验证码时则不响应
          return;
        }
        if (e.keyCode !== 13) {
          return;
        }
        handler();
      }
    },

    /**
     * 登录失败处理
     * @param {*} code - 登录错误值
     */
    _loginFailedHandler(resp) {
      // this.LoginInfos[this.currentIndex].isRemberPass = 0;
      // this.LoginInfos[this.currentIndex].isAutoLogin = 0;
      // console.log('this.LoginInfos',this.LoginInfos)
      // this.$store.commit('SET_LOGININFOS', this.LoginInfos);
      if (resp.code !== 1303) {
        this.password = '';
      }
      if (resp.code === 117 || resp.code === 1102) {
        this.isVerfyShow = true;
        console.log('get img::', resp.img);
        this.verifyImg = resp.img;
        return
      }
      if (resp.code === 100001575 && this.info.userType === 1) {
        this.$store.commit('SET_LOGIN_BY_FORGETPWD', {
          flag: 0,
          val: true
        })
        this.$router.push({
          path: '/LoginInitPage',
          query: {
            pcChange: true
          }
        });
        this.$toast.open({
          message: getErrorMsg(resp.code),
          type: 'is-danger'
        });
        return;
      }
      if (resp.code === 1303) {
        this.$Service.config.setLoginInfo(tempObj, resp => { 
          console.log(`切换账号重置为非自动登陆:${resp.ret}`);

          // this.$Service.auth.prelogin(this.info.server, resp=>{
            this.$Service.contact.queryExtendedField({parentId:68,dicKey:'accountActivate'},resp=>{
              let obj = JSON.parse(resp.EnterpriseDictionarys[0].extend)
              console.log('queryExtendedField',obj)
            this.password = '';
            this.isLoading = false;
            this.$Service.config.getLoginInfos(null, LoginInfosResp=>{  //更新VUEX 的登录历史数据
              console.log('登录历史:',LoginInfosResp);
              let historyData = [];
              LoginInfosResp.LoginInfos.forEach((item, index) => {
                if (item.account.indexOf('0086') === 0 || item.account.indexOf('0060') === 0) {
                  item.account = item.account.slice(4);
                }
                historyData.push(item);
              })
              this.$store.commit('SET_LOGININFOS', historyData);
           });
          }); 
         });
        return;
      }
      this.isSuccess = false;
      this.isErrorBox = true;
      this.errorMsg = getErrorMsg(resp.code);
    },

    _setSectorOpen(){
      this.$Service.contact.queryExtendedField({parentId:-2,dicKey:'nameSector'}, resp=>{
        if(resp.EnterpriseDictionarys.length>0){
          this.$store.commit('SET_SECTOROPEN',resp.EnterpriseDictionarys[0].extend === '1');
        }
      })
    },
    /**
       * 获取用户聊天图片储存地址
       * 获取用户聊天文件存储地址
       * 获取用户聊天音频存储地址
       * 获取用户聊天微视频存储地址
     */
    _setDataPath(userid){
      let path = `${this.$AppPath.userCachePath()}/${userid}/`
      console.log('_setDataPath',path);
      this.$Service.config.userImgPath(null, resp => {
        this.$store.commit('UPDATE_IMG_PATH',path+'image/');
      });
      this.$Service.config.userFilePath(null, resp => {
        this.$store.commit('UPDATE_FILE_PATH',path+'file/');
      });
      this.$Service.config.userAudioPath(null, resp => {
        this.$store.commit('UPDATE_AUDIO_PATH',path+'audio/');
      });
      this.$Service.config.userVideoPath(null, resp => {
        this.$store.commit('UPDATE_VIDEO_PATH',path+'video/');
      });
    },
    /**
     * 登录成功处理
     * @param {*} userid - 登录成功后返回的用户ID
     */
    _loginSuccessedHandler(userid) {
      this._setSectorOpen();
      //  将登录信息存入数据库
      this._setLoginInfo(userid);
      this._setDataPath(userid);
      //将userid传入_setLoginInfo（）中
      // 获取服务首页/应用配置
      let lastPreLoginResp = this.$Service.config.getLastPreLoginData({userId: userid})
      this._handlePreLogin(lastPreLoginResp)
      // this.$Service.auth.prelogin(this.info.server, this._handlePreLogin);

      //  先将登录信息存入vuex中，等待获取到用户信息后统一存入数据库
      this.$store.commit('SET_USER_LOCALCONFIG', {
        key: 'userServer_for_auth_request',
        value: this.info.server
      });
      this.$ipc.send('login-successed');
      Vue.prototype.$userver = this.info.server;
    },

    _setLoginInfo(userid) {
      let info = {
        userId: userid,
        account: this.account,
        isAutoLogin: this.isAutoLogin,
        isRemberPass: this.isRemberPass,
        nation: this.info.nation,
        userType: this.auth_loginByForgetPwd.isForgetPwdLogin ? 1 : this.info.userType,
        server: this.info.server,
        last_login_time: new Date().getTime().toString(),
        name: '',
        user_icon: '',
        pwd:this.isRemberPass?this.password:''
      };
      this.$store.commit('SET_LOGININFO', Object.assign({}, info));
    },

    _handlePreLogin({json}) {

      console.log('_handlePreLogin', json)
      
      this.isLoading = false;
      this.$emit('is-shading', false);
      let obj = json && JSON.parse(json);
      this.getDouName(obj);
      let serverVersion = obj.ServerVersion || obj.serverVersion;
      this.$store.commit('SET_SERVERVERSION', serverVersion);
      //let isNewServer = versionCompire(serverVersion, '3.6.1');
      let systemConfig = 16;
      if (obj && obj.hasOwnProperty('systemConfig')) {
        systemConfig = obj.systemConfig
      }
      this.$Service.log(`systemConfig:::${systemConfig}`)
      console.log('_handlePreLogin_obj::::', obj)
      console.log('_handlePreLogin_systemConfig::::', systemConfig)
      // 保存二维码所需的usever(elogo)和serverhost数据
      /*let idReg = /^[1-9]\d*\,\d*|[1-9]\d*$/
      let serverhost = obj.preList.find(element => {
        if (!idReg.test(element)) {
          return element;
        }
      });
      this.$Service.log(`serverhost:::${obj.serverhost}`)
      if (!serverhost) {
        if (obj.preList && obj.preList.length > 0) {
          serverhost = obj.preList[0]
        }
      }*/
      let serverhost = obj.serverhost;
      this.$store.commit('SET_PRELOGIN_USEVER', obj.elogo)
      this.$store.commit('SET_PRELOGIN_SERVERHOST', serverhost)
      this.$store.commit('SET_PRELOGIN_APHOST', obj.serverhost && obj.serverhost.apHost)
      this.$store.commit('SET_WEB_LINK_PARSE', obj.dmark || '');
      this.$store.commit('SET_SYSTEM_CONFIG', systemConfig);
      // 给主进程传递apHost,方便ddio调用
      if (obj.serverhost && obj.serverhost.apHost) {
        this.$setApHost(obj.serverhost.apHost);
      }
      // 判断"首页"是否 未开启 
      if ( (systemConfig & 4) != 1 << 2){
        this.$store.commit('SET_DEFAULTPAGE', obj.clientDefaultPage);
      }
      if (this.$route && this.$route.query && this.$route.query.pcChange) // 更换设备进行手机验证，此时登录上去之后不需要修改密码
      {
        this.$store.commit('SET_LOGIN_BY_FORGETPWD', {
          flag: 0,
          val: false
        })
      }
      console.log('Code::::::::',this.loginRespCode)
      this.$router.push({path: '/Main',query: {loginCode:this.loginRespCode}});
    },

    // getDouName({accounts}) {
    //   console.log({accounts})
    //   // 给主进程传递apHost,方便ddio调用
    //   let setApHost = remote.getGlobal('setApHost');
    //   setApHost(obj.serverhost.apHost);
    //   this.$router.push({path: '/Main'});
    // },
    getDouName({
      accounts
    }) {
      let loginType = accounts && accounts.find((val, index, arr) => FIELD_NAME_KEY in val);
      console.log('find 6::', loginType);
      let fieldName = '';
      if (loginType !== undefined) {
        fieldName = loginType[FIELD_NAME_KEY];
      } else {
        console.log('未配置豆豆号字段');
        //  读取本地配置
        let tempType = this.localLoginTypes.find((val, index, arr) => FIELD_NAME_KEY === val.type);
        fieldName = tempType === undefined ? this.$t('user.dou') : tempType.way;
      }
      console.log('getLoginExData::', fieldName);
      this.$store.commit('SET_USER_FIELD_NAME', fieldName);
    },

    getLoginAccount(account, nation) {
      let user = (this.info.userType === 1 || this.info.userType === 96) ? nation + account : account;
      return user;
    },

    // 验证手机号是否合法
    invalidMobile(type, user) {
      let reg = /^[0-9]*$/;
      if (type !== 1) return false;
      if (!reg.test(user) ) {
        this.isSuccess = false;
        this.isErrorBox = true;
        this.errorMsg = this.$t('auth.phoneEmpty');
        return true
      }
      return false
    },
    /**
     * 注册按钮事件响应函数
     * @param {*} server - 传入需要注册的服务器地址
     */
    register(server) {
      console.log('server::', server);
      this.$router.push({
        path: '/first',
        query: {
          server: server
        }
      });
    },
    preLoginForRegister(server) {
      this.registerLoading = true;
      this.$Service.auth.prelogin({
        server: server
      }, resp => {
        this.registerLoading = false;
        if (resp.code !== 0 || resp === undefined || resp.json === undefined || resp.json === '') {
          this.errorMsg = getErrorMsg(resp.code);
          this.isErrorBox = true;
          console.log(this.isErrorBox);
          return;
        }
        let obj = JSON.parse(resp.json);
        if ((obj.systemConfig & 1) === 1) { //该服务器允许注册
          this.register(server);
        } else {
          this.errorMsg = this.$t('auth.notAllowed');
          this.isErrorBox = true;
        }
      })
    },

    // 清除定时器
    clearCountDown() {
      clearInterval(this.clock);
      this.regCode = this.$t('auth.getVerifyCode');
      this.isCodeSend = false;
    },

    // 获取安全中心地址（修改密码适配旧服务）
    openSecUrl(server) {
      let getSecUrlParam = {
        server: server
      };
      this.$Service.log(`获取安全中心地址入参:::${getSecUrlParam.server}`);
      this.$Service.auth.getSecUrl(
        getSecUrlParam,
        this._getSecUrlHandler
      )
    },
    _getSecUrlHandler(resp) {
      this.isForgetpwdLoading = false;
      console.log('in securl callback ', resp);
      if (resp.code !== 0) {
        console.log('this.auth_loginByForgetPwd', this.auth_loginByForgetPwd);
        this.errorMsg = this.$t('auth.serverOrNetError');
        this.isErrorBox = true;
        this.isSuccess = false;
        return
      }
      this.$ipc.send('new-window-weburl', resp.value + '/server-securitycenter/password/goAccountCheck.vrv');
    },

    /***
     * 忘记密码
     * 新服务：跳转到验证码登录
     * 就服务：打开安全中心网页
     */
    changePwdhandOut(server) {
      console.log('this.account:::', this.account);
      this.respPrelogin(0, 0);
    },
    // 修改密码-获取预登陆信息
    respPrelogin(resp, server) {
      if (this.$route.path == '/LoginInitPage') {
        console.log('首次登录界面点击忘记密码');
        this.$store.commit('SET_LOGIN_BY_FORGETPWD', {
          flag: 1,
          val: true
        })
      };
      this.opneRegCodePage()
    },
    // 新服务跳转验证码登录传参
    opneRegCodePage() {
      this.$store.commit('SET_LOGIN_BY_FORGETPWD', {
        flag: 0,
        val: true
      })
      this.$router.push({
        path: '/LoginInitPage'
      })
    },

    // 验证码登陆--获取验证码
    regCodeLogin(info) {
      this.isCodeLoading = true;
      this.isCodeSend = true;
      let getRegCodeParam = {
        account: info.account,
        type: 2,
        server: info.server
      };
      this.$Service.log(`验证码登录:获取验证入参:${JSON.stringify(getRegCodeParam)}`);
      this.$Service.auth.getRegCode(
        getRegCodeParam,
        this._getRegCodeHandler
      )
    },
    _getRegCodeHandler(resp) {
      this.isCodeLoading = false;
      this.$Service.log(`验证码登录:获取验证码返回:${JSON.stringify(resp)}`);
      if (resp.code === 0) {
        this.clock = setInterval(() => {
          resp.time--;
          this.regCode = `${resp.time}s`;
          if (resp.time < 1) {
            this.clearCountDown();
          }
        }, 1000);
        this.errorMsg = this.$t('auth.verCodeSent');
        this.isErrorBox = true;
        this.isSuccess = true;
      } else {
        this.isCodeSend = false;
        this.errorMsg = getErrorMsg(resp.code);
        this.isErrorBox = true
      }
    },
    initOauth(){
      if(this.$oauth){
        // 注册oauth回调
        this.$oauth.init(null, this._regOAuthHandle);
      }
    },
    _regOAuthHandle(resp) {
      if (resp.code === 0) {
        if (resp.type === 1) { //需要登录
          console.log('oauth.login:resp:', JSON.parse(resp.json));
          let loginExData = Object.assign({}, this.info);
          loginExData.thirdParam = JSON.stringify(JSON.parse(resp.json));
          console.log('loginExData:', loginExData)
          this.$Service.auth.loginEx(loginExData, this._loginHandler);
        }
        else if (resp.type === 2) { //透传
          //将oauth的透传信息传给sdk
          this.$Service.auth.beforeLogin(JSON.parse(resp.json), beforeLoginResp => {
            //将结果透传给oauth
            this.$oauth.call({ type: 2, json: JSON.stringify(beforeLoginResp) });
          });
        }
      }
    }
  }
};
export default mixin;
