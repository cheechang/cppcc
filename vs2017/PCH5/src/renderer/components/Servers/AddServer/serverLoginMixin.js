import { mapGetters } from "vuex";
import { getErrorMsg } from '../../../utils/utils.js';
/**
 * @mixin
 */
const mixin = {
  data() {
    return {
        userType:1,
        account:'',
        isLoading: false,
        placeholder: '',
        avatar: require('vrv-static/resources/images/common/logo.png'),
        nationCode: '', // 地区码：+86
        nationCodeText: '', // 地区原码：0086
        codePlaceholder: this.$t('auth.nationCode'),
        isNationShow: true,
        password:'',
        errorMsg: '',
        isErrorBox: false,
        isSuccess: false,
        isExpend:false,
        isCodeSend: false,
        isCodeLoading: false,
        regCode: this.$t('auth.getVerifyCode'),
        verifyImg: '',
        isVerfyShow: false,
    }
  },
  created(){
    console.log('this.loginAccoutInfo:',this.loginAccoutInfo)
    let areaCode = this.auth_nationCode === '' ? this.$Service.config.getSystemNationCode() : this.auth_nationCode;
    if(this.loginAccoutInfo){
        this.userType = this.loginAccoutInfo.type;
        this.account = this.loginAccoutInfo.account;
        this.placeholder = this.$t(`loginType.${this.userType}`)
        if(this.loginAccoutInfo.avatar){
            console.log('this.loginAccoutInfo:::',this.loginAccoutInfo)
            this.avatar = this.loginAccoutInfo.avatar;
            console.log('this.avatar',this.avatar)
        }
        if(this.userType === 1){
            areaCode = JSON.parse(this.loginAccoutInfo.remark).nation;
        }

    }
    else{
        //  初始化登录类型
        this.placeholder = this.loginTypes[0].val;
        this.userType = this.loginTypes[0].type;
    }
    console.log('code:::', areaCode);
    this.initNationOption(areaCode);
  },
  computed:{
    ...mapGetters(['user_loginInfo','user_account','auth_multipleServers'])
  },
  methods:{
    login(){
        console.log('login:::');
        if (this.isLoading|| this.isVerfyShow || this.isDisable) {
            return;
        }
        if (this.invalidMobile(this.userType, this.getLoginAccount(this.account,this.nationCodeText))) return;
        this.isLoading = true;
        this.$emit('is-shading',true);
        let loginParam = {
            userType:this.userType,
            account:this.account,
            nation:this.nationCodeText,
            server:this.server,
            pwd:this.password
        }
        console.log('loginParam:',loginParam);
        this.$mutipleServers.serverLogin(loginParam,resp=>{
            console.log('this.$mutipleServers.serverLogin:',resp)
            this.isLoading = false;
            this.$emit('is-shading',false);
            if(resp.code !== 0 ){
                this.$toast.open({
                    message: getErrorMsg(resp.code),
                    type: 'is-danger'
                });
                if(resp.code === 112){
                  // 账号密码错误
                    this.password='';
                }
                if(resp.code === 100001575 && this.userType === 1){
                  // 更换了设备，需要验证码激活
                  this.password='';
                  this.userType = 96;
                  // 减低组件高度，隐藏更多登录方式
                  this.$emit('reduceHeight');
                }
                if (resp.code === 117 || resp.code === 1102) {
                  //账号密码错误次数过多,需要进行验证码验证
                  this.password='';
                  this.isVerfyShow = true;
                  console.log('get img::', resp.img);
                  this.verifyImg = resp.img;
                }
                return;
            }
            let arr = resp.senderKey.split('@');
            if(this.auth_multipleServers.hasOwnProperty(arr[0])){
                //服务器列表有此项
                let newInfo = Object.assign({},this.auth_multipleServers[arr[0]]);
                newInfo.isOnline = true;
                this.$store.commit('SET_MULTIPLE_SERVER', {flag: 1, val: newInfo})
                let param = {
                    key:resp.senderKey,
                    info:Object.values(this.auth_multipleServers)
                }
                //console.log('param:::',param);
                 this.$emit('switchToServer',param);
                 return;
                //this.$Service.config.setSubServerInfo({infos:this.auth_multipleServers});
            }
            else{
                let serverInfo={};
                serverInfo.server = this.server;
                serverInfo.elogo = this.elogo;
                serverInfo.addr = `${this.server}@${this.elogo}`;
                serverInfo.type = this.userType === 96 ? 1 : this.userType;
                serverInfo.userId = arr[0];
                serverInfo.avatar = '';
                if(serverInfo.type === 1){
                    serverInfo.remark = JSON.stringify({nation:this.nationCodeText});
                }
                serverInfo.account = this.account;
                serverInfo.isOnline = true;
                console.log('serverInfo:',serverInfo);
                this.$store.commit('SET_MULTIPLE_SERVER', {flag: 1, val: serverInfo})
                this.$Service.config.setSubServerInfo({infos:Object.values(this.auth_multipleServers)});
            }
            this.$toast.open({
                message: this.$t('auth.serverLoginSucc'),
                type: 'is-success'
            });
            this.$emit('close'); 
        })
    },
    onGetVerifyCode(){
      if (this.invalidMobile(this.userType, this.getLoginAccount(this.account,this.nationCodeText))) return;
      this.isCodeLoading = true;
      this.isCodeSend = true;
      let param = {
        account: this.getLoginAccount(this.account, this.auth_nationCode),
        server: this.server,
        type:2
      }
      this.$Service.auth.getRegCode(
        param,
       this. _getRegCodeHandle
      )
    },
    _getRegCodeHandle(resp){
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
    // 清除定时器
    clearCountDown() {
      clearInterval(this.clock);
      this.regCode = this.$t('auth.getVerifyCode');
      this.isCodeSend = false;
    },
    selectedNation({val, index}) {
        if (val) {
            this.nationCodeText = this.$i18n.messages[`${this.$i18n.locale}`].AreaCode[val];
            this.nationCode = `+${this.nationCodeText.replace(/\b(0+)/gi,'')}` ;
            this.$Service.log(`选择国家码:::${this.nationCode}`);
            console.log('国家码:', this.nationCode);
        }
    },
    initNationOption(areaCode) {
        _.filter(this.$i18n.messages[`${this.$i18n.locale}`].AreaCode,(code,name) => {
            if(name.indexOf(areaCode) >= 0||code.indexOf(areaCode) >= 0) {
            this.nationCodeText = areaCode;
            this.nationCode = `+${this.nationCodeText.replace(/\b(0+)/gi,'')}`;
            }
        })
    },
    // 其他登录方式
    chooseLoginType() {
        console.log(this.loginTypes);
        this.isExpend = !this.isExpend;
        this.$emit('is-nodrag', this.isExpend);
    },
    // 关闭选择登录方式表
    closeSelscList() {
        this.isExpend = false;
        this.$emit('is-nodrag', false);
    },
    selectItem(type, val) {
        console.log(type, val);
        this.userType = type;
        this.placeholder = this.userType === 96 ? this.$t(`loginType.96`) : val;
        this.account = '';
        this.password = '';
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
    getLoginAccount(account, nation) {
      let user = (this.userType === 1 || this.userType === 96) ? nation + account : account;
      return user;
    },
  },
  computed:{
    ...mapGetters([
        'auth_nationCode',
        'auth_loginByForgetPwd',
        'auth_multipleServers'
    ]),
    // 界面的账户信息及登录方式等是否可以改变
    infoCanChange(){
      return !this.loginAccoutInfo && this.userType !== 96;
    },
        // 获取验证码等待动画
    codelodingState() {
      return this.isCodeLoading ? 'is-loading' : '';
    },
    // 获取验证码按钮能否点击
    isCodeDisabled() {
      return this.account != '' && !this.isCodeSend;
    },
    /**
     * 国家码是否合法
     */
    invalidNationCode() {
        return (this.nationCode === `+${this.nationCodeText.replace(/\b(0+)/gi,'')}`) && (JSON.stringify(this.$i18n.messages[`${this.$i18n.locale}`].AreaCode).indexOf(this.nationCodeText) > -1);
    },
    /**
     * 禁用登录按钮
     * @returns - 是/否 只有当用户名和密码输入栏全部有值时，才会返回false，否则返回true
     */
    isDisable() {
        return this.account === '' || this.password === '' || !this.invalidNationCode;
    },
    lodingState() {
        return this.isLoading ? "is-loading" : "";
    },
    isNationCode() {
        return this.userType === 1 || this.userType === 96;
    },
    pwdPlacehold() {
        return 96 === this.userType ? this.$t('auth.verifyCode') : this.$t('auth.pwd');
    },
    filteredOptionsArray() {
        // 获取对应语言状态下的 Object => {'area': 'code'}
        let areaCode = this.$i18n.messages[`${this.$i18n.locale}`].AreaCode;
        let optionsArray = [];
        if (!this.nationCode) return;
        _.filter(areaCode, (code, name) => {
            if(name.toUpperCase().indexOf(this.nationCode.toUpperCase()) >= 0 || code.replace(/\b(0+)/gi,'').indexOf(this.nationCode) >= 0) {
            optionsArray.push(name);
            }
        })
        console.log('nation :::', optionsArray);
        return optionsArray;
    },
    // 国家码列表
    nationArray() {
        return Object.keys(this.$i18n.messages[`${this.$i18n.locale}`].AreaCode);
    }
  }
};

export default mixin;