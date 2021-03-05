<template>
  <div class="login-page">
    <!-- 头像 -->
    <v-avatar class="logo boxshadow-1" :src="avatar" :sex="6" :shape="'round'"></v-avatar>
    <!-- 账号 -->
    <v-field class="fields">
      <div class="auth-icon" :class="{'icon-account': isNationCode}">
        <!--<i class="icon">&#xe683;</i> -->
        <span v-if="isNationCode" class="nation-code">
          +{{currentInfo.nation.replace(/\b(0+)/gi,'')}}
        </span>
      </div>
      <v-auto-complete
        ref="vautocompleteaccount"
        v-model="account"
        hasLine
        :placeholder="actPlacehold"
        :data="filteredOptionsInfo"
        :originArray="optionAccounts"
        :isBorder="false"
        :menuCanShow="isOptionShow"
        :isAuth="true"
        :openOnFocus="true"
        :maxlength="isNationCode?18:50"
        :inputPadding="isNationCode? '55px':'calc(0.625em - 1px)'"
        @change="active => isOptionShow = !active"
        @select="selected"
        @input="onAccountpInput"
      >
        <template slot-scope="data">
          <div class="account-card">
            <v-avatar
              size="is-small"
              :src="user_headImgPath +data.option.user_icon"
              :sex="6"
              :offline="false"
              shape="round"
            ></v-avatar>
            <div class="account-info">
              <div class="account-title">
                {{data.option.account}}
              </div>
              <div
                class="account-server"
                :title="data.option.name+'@'+data.option.server"
              >{{data.option.name}}@{{data.option.server}}</div>
            </div>
            <!-- <i class="icon del-account" @click="delHistoryAccount({index:data.index, option:data.option}, $event)">&#xe694;</i> -->
          </div>
        </template>
      </v-auto-complete>
      <i class="icon icon-option" :class="{'scale-icon': !isOptionShow}" @click.self.stop="isOptionShow=!isOptionShow">&#xe77a;</i>
    </v-field>
    <!-- 密码 -->
    <v-tip
      :isSuccess="isSuccess"
      :tipLabelMsg="errorMsg"
      :isLabelTip="isErrorBox"
      @close="isErrorBox = false"
      class="position-corr"
    >
      <v-input
        class="inputs auth-input"
        hasLine
        hasLabel
        v-model="password"
        :maxlength="20"
        :type="currentInfo.userType==96?'text':'password'"
        :isAuth="true"
        :inputLineSite="'-1px'"
        :customType="'input-size'"
        :isBorder="false"
        :placeholder="pwdPlacehold"
        :position="'right'"
        @input="onPasswordInput"
        :selectPwdShow='true'
      >
        <v-button
          slot="expand"
          v-if="96 === currentInfo.userType"
          class="ver-code"
          :disable="!isCodeDisabled"
          :ripple="false"
          :type="codelodingState"
          @click="onGetVerifyCode"
        >{{regCode}}</v-button>
      </v-input>
    </v-tip>
    <!-- 记住密码/自动登录 -->
    <div class="checkbox-group">
      <!-- 记住密码 -->
      <v-checkbox @checked="e => isRemberPass = e" class="remember-pwd" v-if="clientConfig_auth.openRemeberPwd&&currentInfo.userType!==94" :value="isRemberPass">{{$t('auth.rememberPwd')}}</v-checkbox>
      <!-- 自动登陆 -->
      <v-checkbox @checked="e => isAutoLogin = e" class="auto-login" v-if="clientConfig_auth.openAutoLogin&&currentInfo.userType!==94" :value="isAutoLogin">{{$t('auth.autoLogin')}}</v-checkbox>
    </div>
    <!-- 登录按钮 -->
    <v-btn
      class="auth-button"
      :size="'v-button--max_width'"
      :disable="isDisable"
      :type="lodingState"
      @click="onlogin"
    >{{$t('auth.signin')}}</v-btn>
    <!-- 注册/其他登录方式 -->
    <div class="more-button-layout other-login">
      <v-button
        v-if="registerLoading"
        class="register-loading"
        :type="'is-loading'"
        :ripple="false"
      ></v-button>
      <span class="txt-link register" v-if="clientConfig_auth.openRegister" @click="jump(currentInfo.server)">{{$t('auth.register')}}</span>
      <span class="txt-link new-account" v-if="!clientConfig_auth.openUnicomAuth" @click="toPreLogin">{{$t('auth.newAccount')}}</span>
      <span class="txt-link new-helpPhone" v-if="clientConfig_auth.openUnicomAuth">{{phone}}</span>
    </div>
    <!-- 验证码弹框 -->
    <div v-if="isVerfyShow">
      <verfy-code
        :nation="auth_nationCode"
        :account="account"
        :userType="info.userType"
        :img="verifyImg"
        @verfy="isVerfyShow=false"
        @codeVerfy="codeVerfy"
      ></verfy-code>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import vBtn from './../common/button.vue';
import vTip from './../common/tooltip.vue';
import VerfyCode from './../Verfy/VerfyCode.vue'
import LoginMixins from './LoginMixins';
import UnicomAuthMixins from './UnicomAuthMixins';
import { setTimeout } from 'timers';
export default {
  components: {
    vBtn,
    vTip,
    VerfyCode
  },
  mixins: [LoginMixins,UnicomAuthMixins],
  data() {
    return {
      flag:true,
      isOptionShow: true,
      LoginInfos: [],
      currentIndex: 0,
      currentInfo: null,
      isPasswordChanged: false,
      isIconPath: true,
      isSwitch: false,
      registerLoading:false,
      phone:this.$t('auth.helpPhone'),
      isVerfyShow:false,
      verfycode:''
    }
  },
  computed: {
    ...mapGetters([ 'auth_loginInfos', 'user_headImgPath', 'auth_nationCode','clientConfig_auth', 'auth_loginServers']),
    accountList() {
      let arr = []
      this.auth_loginInfos.forEach(element => {
        arr.push(element.account)
      });
      return arr
    },
    avatar() {
      return this.isIconPath ? this.userIcon : this.$config.clientConfig.avatar.logo;
    },
    userIcon() {
      console.log('this.user_headImgPath + this.currentInfo.user_icon');
      return this.user_headImgPath + this.currentInfo.user_icon;
    },
    isNationCode() {
      return this.currentInfo.userType === 1 || this.currentInfo.userType === 96;
    },
    // 不同登录类型密码框显示提示文本
    pwdPlacehold() {
      return 96 === this.currentInfo.userType ? this.$t('auth.verifyCode') : this.$t('auth.pwd');
    },
    actPlacehold(){
      return this.$t('auth.userName');
    },
    optionAccounts(){
      let optionsArray = [];
      this.auth_loginInfos.filter((item, index) => {
        if(item.account !==''){
          optionsArray.push(item)
        }
      })
      return optionsArray;
    },
    filteredOptionsInfo() {
      let optionsArray = [];
      this.auth_loginInfos.filter((item, index) => {
        if(item.account.indexOf(this.account) >= 0){
          optionsArray.push(item)
        }
      })
      console.log('filteredOptionsInfo',optionsArray)
      return optionsArray;
    },
    // isRemberPass() {
    //   return this.auth_loginInfos[this.currentIndex].isRemberPass;
    // }
  },
  watch: {
    isOptionShow(val) {
      val ? this.$emit('is-nodrag', false) : this.$emit('is-nodrag', true)
    },
    'currentInfo.account': {
      handler: function() {
        this.account = this.currentInfo.account;
        console.log('watch currentInfo.account', this.account);
      }
    }
  },
  created() {
    if(this.clientConfig_auth.openUnicomAuth){
      this.getPhone(ph => {
        this.phone = this.$t('auth.helpPhone')+ph;
      })
    }
    if(this.$serversLoginParam){
      //多服务器启动参数
      this.$ipc.on('serversLogin',(event,param)=>{
        this.onMultipleServersLogin(param);
      })
      this.onMultipleServersLogin(this.$serversLoginParam);
      return;
    }
    this.LoginInfos = this.auth_loginInfos;
    console.log('in created::', this.LoginInfos);
    if (this.LoginInfos.length === 0) {
      //  历史记录异常
      let info = {
        userId:'',
        account:'',
        isAutoLogin:false,
        isRemberPass: false,
        nation: '0086',
        userType: 10,
        server:this.clientConfig_auth.server,
        last_login_time: new Date().getTime().toString(),
        name: '',
        user_icon: '',
        pwd:''
      };
      this.LoginInfos.push(info);
      //return;
    }
    this.currentInfo = this.LoginInfos[this.currentIndex]
    //     console.log('this.currentInfo.isRemberPass',this.currentInfo.isRemberPass)
    // console.log('this.currentInfo.isAutoLogin',this.currentInfo.isAutoLogin)
    console.log('currentInfo=', this.currentInfo);
    this.account = this.currentInfo.account;
    /**
     * 当 当前选中的登录用户为手机号登录时，忘记密码登录模式下才自动填写表单，
     * 避免当用户使用其他登录方式跳转到忘记密码时，非手机号站好自动填写到表单
     */
    if (this.currentInfo.userType === 1 || this.currentInfo.userType === 96) {
      this.$store.commit('SET_LOGIN_BY_FORGETPWD', {flag: 2, val: this.currentInfo.account})
    }
    if (this.currentInfo.isRemberPass) {
      this.password = this.currentInfo.pwd;
      this.isRemberPass = 1;
      this.isAutoLogin = this.currentInfo.isAutoLogin;
      if (this.isAutoLogin) {
        //  自动登录
        this.autoLogin();
      }
    }
    

    this._onEnterEvent(this.onlogin);
    // 更新vuex中的server、nation字段。
    this.$store.commit('SET_SERVER', this.currentInfo.server);
    this.$store.commit('SET_NATIONCODE', this.currentInfo.nation);
  },
  mounted() {
    console.log('loginInitLogoPage this.account', this.account);
  },
  methods: {
    jump(data){
      if(!this.flag) {
        return;
      }
      console.log("触发了一次");
      this.flag = false;
      this.preLoginForRegister(data)
      setTimeout(()=>{
        this.flag = true;
      },5000)
    },
    onAccountpInput() {
      console.log('in onAccountpInput::', this.account);
      console.log('in onAccountpInput::', this.LoginInfos);
      console.log('in isswitch::', this.isSwitch);
      if (!this.isSwitch) {
        this.clearPwd();
      }
      
      /**
       * 当 当前选中的登录用户为手机号登录时，忘记密码登录模式下才自动填写表单，
       * 避免当用户使用其他登录方式跳转到忘记密码时，非手机号站好自动填写到表单
       */
      if (this.currentInfo.userType === 1 || this.currentInfo.userType === 96) {
        this.$store.commit('SET_LOGIN_BY_FORGETPWD', {flag: 2, val: this.account});
      }
      for (let i = 0; i < this.LoginInfos.length; i++) {
        this.isIconPath = false
        if (this.account === this.LoginInfos[i].account && this.currentInfo.server === this.LoginInfos[i].server) {
          this.isIconPath = true
          this.currentInfo = this.LoginInfos[i];
          console.log('is switch');
          return;
        }
      }
      console.log('this.isIconPath:::', this.isIconPath);
    },
    getDelHistoryIndex(arr, obj) {
      let index = null;
      let key = Object.keys(obj)[0];
      arr.every(function(value, i) {
        if (value[key] === obj[key]) {
            index = i;
            return false;
        }
        return true;
      });
      return index;
    },
    selected({val, index}) {
      console.log('选择历史登录账号:::', val, index);
      let [Account, indexof] = this.getSelectAccount(val);
      console.log('select history account index:::', indexof);
      console.log('select history account obj:::', Account);
      if (indexof === -1 || Account === null) {
        return;
      }
      this.isSwitch = true; //  是否是选择账号标识
      this.isIconPath = true; //  需要更新头像
      console.log('this.isIconPath', this.isIconPath);
      this.currentInfo = Account;
      this.setCurrentInfo();
    },
    codeVerfy(param){
      console.log('codeVerfy',param.code)
      this.verfycode = param.code
      this.isVerfyShow = false
    },
    onlogin() {
      if (!this.isOptionShow) return;
      console.log('in onlogin');
      console.log('isPasswordChanged::', this.isPasswordChanged);
      // if (this.isRemberPass && (!this.isPasswordChanged)) {
      //   // 记住密码则需要
      //   this.autoLogin();
      //   return;
      // }
      console.log('currentInfo=', this.currentInfo);
      this.info.userType = this.currentInfo.userType;
      this.info.user = this.getLoginAccount(this.account, this.currentInfo.nation);
      this.info.pwd = this.password;
      this.info.server = this.currentInfo.server;
      this.info.nation = this.currentInfo.nation;
      this.info.code = this.verfycode;
      console.log('in onlogin::', this.info);
      
      if(this.clientConfig_auth.openUnicomAuth){
        //  开启遮罩，防止触发回车操作
        this.isLoading = true;
        this.$emit('is-shading', true); 
        this.unicomLogin(this.info,resp =>{
          if(resp.code !== 0){
            this.isLoading = false;
            this.$emit('is-shading', false);
            if(resp.code === 412){
              this.isVerfyShow = true
            }
            this.$toast.open({
              message: resp.msg,
              type: 'is-danger',
              duration:6000
            });
          }else{
            this.login();
          }
        });
      }else{
        this.login();
      }
    },
    onMultipleServersLogin(param){
      this.info.userType = param.userType;
      this.account = param.account;
      this.info.pwd = param.pwd;
      this.info.server = param.server;
      this.info.user = this.getLoginAccount(param.account, param.nation);
      this.info.nation = param.nation;
      this.login();
    },
    onGetVerifyCode() {
      let param = {
        account: this.getLoginAccount(this.account, this.currentInfo.nation),
        server: this.currentInfo.server
      }
      this.regCodeLogin(param);
    },
    autoLogin() {
      console.log('in autoLogin for merge');
      this.info.elogo = this.currentInfo.elogo||this.currentInfo.server;
      this.info.server = this.currentInfo.server;
      this.info.userType = this.currentInfo.userType;
      this.info.nation = this.currentInfo.nation;
      this.info.userId = this.currentInfo.userId;
      this.login(this.info);
    },
    // 其他登录方式
    toPreLogin() {
      // let server = this.auth_loginServers.length > 0 ? this.auth_loginServers[0] : this.currentInfo.server;
      // this.$router.push({path: '/PreLogin', query: {server}});
      this.$router.push({path: '/PreLogin', query: {server: this.currentInfo.server}});
    },
    /**
     * 删除登录历史
     * @param {number} index 选中数据的索引
     */
    delHistoryAccount({index, option}, e) {
      e.stopPropagation();

      console.log('del history account option:::', option);
      let [delObj, indexof] = this.getSelectAccount(option);
      // indexof = this.auth_loginInfos.findIndex((val, index, arr) => {
      //   return val.userId === option.userId;
      // });
      console.log('del history account index:::', indexof);
      console.log('del history account obj:::', delObj);
      if (indexof === -1 || delObj === null) {
        return;
      }
      //  调用接口删除
      this.$Service.log(`认证:::删除登录历史userId:::${delObj.userId}`);
      let isDel = this.$Service.config.delLoginInfo({userId: delObj.userId});
      this.$Service.log(`认证:::删除登录历史返回:::${isDel}`);
      if (!isDel) {
        console.log('del history account failed:::', delObj.userId);
        return;
      }
      if (delObj.userId === this.currentInfo.userId) {
        //  判断是否只有一条
        if (this.auth_loginInfos.length === 1) {
          //  删除唯一一条之后跳转至预登录页面，重新输入
          this.auth_loginInfos.splice(indexof,1);
          this.$router.push({path: '/Prelogin'});
          return;
        }
        //  判断是否存在下一条
        if (indexof < this.auth_loginInfos.length - 1) {
          //  存在下一条则改为下一条
          this.currentInfo = this.auth_loginInfos[indexof + 1];
          this.setCurrentInfo();
          this.auth_loginInfos.splice(indexof,1);
        }
        else {
          //  判断是否是第一条，不是则当前信息改为上一条
          if (indexof !== 0) {
            this.currentInfo = this.auth_loginInfos[indexof - 1];
            this.setCurrentInfo();
            this.auth_loginInfos.splice(indexof,1);
          } 
        }
      } else {
        this.auth_loginInfos.splice(indexof,1);
      }
      
    },
    onPasswordInput(event) {
      console.log('in onPasswordInput');
      if (this.isSwitch) {
        //  如果是切换账号引起的pwd输入框事件触发，则认为并未修改密码，仍然需要走自动登录
        this.isPasswordChanged = false;
        this.isSwitch = false;
        return;
      }
      this.isPasswordChanged = true;
    },
    setCurrentInfo() {
      this.account = this.currentInfo.account;
      console.log('account::', this.currentInfo);
      this.isRemberPass = this.currentInfo.isRemberPass;
      this.isAutoLogin = this.currentInfo.isAutoLogin;
      this.password = this.currentInfo.pwd;
      // this.password = this.isRemberPass ? '******' : '';
      // if (this.isRemberPass) {
      //   this.password = '******';
      // }
      console.log('password: ', this.password);
      this.$store.commit('SET_SERVER', this.currentInfo.server);
      this.$store.commit('SET_NATIONCODE', this.currentInfo.nation);
      if (this.currentInfo.userType === 1 || this.currentInfo.userType === 96) {
        this.$store.commit('SET_LOGIN_BY_FORGETPWD', {flag: 2, val: this.currentInfo.account})
      }
    },
    getSelectAccount(option) {
      let index = this.auth_loginInfos.findIndex((val, index, arr) => {
        return val.userId === option.userId && val.server === option.server;
      });
      if (index < 0) {
        return [null, -1];
      }
      return [this.auth_loginInfos[index], index];
    }
  }
}
</script>
<style lang="scss" scoped>
@import './../_auth';
.login-page{
  display: flex;
  flex-direction: column;
  width: 280px;
  height: auto;
  padding-top: 85px!important;
  position: relative;
  /deep/ input{
    font-size: $--font-size-mid;
    line-height: 2.0;
    height: 36px;
    border: none !important;
  }
  /deep/ .input-line{
    bottom: -3px;
  }
  
  .fields {
    margin-bottom: 0;
    height: 39px;
    position: relative;
    border-bottom: 1px solid $--border-color-blue !important;
    display: inline-flex;
    .auth-icon{
      position: absolute;
      padding-top: 12px;
      padding-left: 9px;
      @include z-index(image);
      // background: red;
      .nation-code{
        // padding-left: 14px;
        font-size: $--font-size-mid;
        color: get-grey-color(base);
        font-family: '\5FAE\8F6F\96C5\9ED1', 'Microsoft YaHei', Arial, Helvetica, sans-serif, '\5B8B\4F53'
      }
    }
    .icon-option {
      position: absolute;
      right: 0;
      top: 11px;
      @include z-index(btn);
    }
  }
  .input-tip:not(:last-child){
    margin-bottom: 0;
  }
  .other-login{
    position: relative;
    justify-content: space-between;
    .register-loading{
      position: absolute;
      top: 8px;
      left: 55px;
    }
    //justify-content: space-between;
    .register{
      width: 100%;
      display: flex;
      justify-content: flex-start;
    }
    .new-account{
      width: 100%;
      display: flex;
      justify-content: flex-end;
    }
    .new-helpPhone{
      width: 100%;
      display: flex;
      justify-content: center;
      font-size: 12px;
    }
  }
  .account-card{
    width: 100%;
    height: 40px;
    display: flex;
    justify-content: flex-start;
    .account-info{
      padding-left: 10px;
      .include-input{
        color: $--color-black;
        font-weight: 600;
      }
      .account-server{
        font-size: $--font-size-small;
        color: get-grey-color(adrken-1);
        width: 145px;
        overflow: hidden;
        white-space: nowrap;
        text-overflow: ellipsis;
      }
      .account-title{
        width: 145px;
        overflow: hidden;
        white-space: nowrap;
        text-overflow: ellipsis;
      }
    }
    .del-account{
      align-self: center;
      position: absolute;
      right: 10px;
      font-size: $--font-size-mid;
      @include z-index(btn);
      &:hover{
        color: $--color-danger;
      }
    }
  }
  .auth-input{
    background: $--color-danger;
    /deep/ .is-right{
      width: auto !important;
    }
  
    .ver-code{
      font-size: $--font-size-mid;
      display: inline-block;
      padding-right: 5px;
      background: $--color-white;
      font-family: '\5FAE\8F6F\96C5\9ED1', 'Microsoft YaHei', Arial, Helvetica, sans-serif, '\5B8B\4F53';
      &:hover{
        background: $--color-white;
      }
    }
  }
}

</style>
