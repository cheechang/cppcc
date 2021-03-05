<template>
  <div class="login-init">
    <!-- 用户头像 -->
    <v-avatar class="logo boxshadow-1" :src="avatar" :shape="'round'"></v-avatar>
    <!-- 地区码/账号 -->
    <v-input
      class="inputs auth-input"
      hasLine
      hasLabel
      v-model="account"
      :isAuth="true"
      :customType="'input-size'"
      :isBorder="false"
      :placeholder="placeholder"
      @input="clearPwd"
      :maxlength="isNationCode?18:50"
    >
      <div slot="auth" v-if="isNationCode" class="auth-icon" :class="{'icon-account': isNationCode}">
        <span class="nation-code-ban" v-if="auth_loginByForgetPwd.isForgetPwdLogin">
          +{{auth_nationCode.replace(/\b(0+)/gi,'')}} 
        </span>
        <div v-else style="width: 100%">
          <v-auto-complete
          class="nation-code"
          ref="vautocomplete"
          v-model="nationCode"
          :data="filteredOptionsArray"
          :originArray="nationArray"
          :placeholder="codePlaceholder"
          hasLine
          :isBorder="false"
          :openOnFocus="true"
          :menuCanShow="isNationShow"
          :isAuth="true"
          @change="active => isNationShow = !active"
          @select="selectedNation"
          >
          </v-auto-complete>
          <i class="icon icon-option" :class="{'scale-icon': !isNationShow}" @click.self.stop="isNationShow=!isNationShow">&#xe77a;</i>
        </div>
      </div>
    </v-input>
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
        :type="userType==96?'text':'password'"
        :isAuth="true"
        :maxlength="20"
        :inputLineSite="'-1px'"
        :customType="'input-size'"
        :isBorder="false"
        :position="'right'"
        :placeholder="pwdPlacehold"
        :selectPwdShow='true'
        @keyup.enter='onlogin'
      >
        <v-button
          slot="expand"
          v-if="96 === userType"
          class="ver-code"
          :disable="!isCodeDisabled"
          :ripple="false"
          :type="codelodingState"
          @click="onGetVerifyCode"
        >{{regCode}}</v-button>
      </v-input>
    </v-tip>
    <div
      class="checkbox-group"
      v-if="!auth_loginByForgetPwd.isForgetPwdLogin"
    >
      <!-- 记住密码 -->
      <v-checkbox @checked="e => isRemberPass = e" class="remember-pwd" :value="isRemberPass" v-if="clientConfig_auth.openRemeberPwd&&userType!==94">{{$t('auth.rememberPwd')}}</v-checkbox>
      <!-- 自动登陆 -->
      <v-checkbox @checked="e => isAutoLogin = e" class="auto-login" :value="isAutoLogin" v-if="clientConfig_auth.openAutoLogin&&userType!==94">{{$t('auth.autoLogin')}}</v-checkbox>
    </div>
    <v-btn
      class="auth-button"
      :size="'v-button--max_width'"
      :disable="isDisable"
      :type="lodingState"
      @click="onlogin"
    >{{auth_loginByForgetPwd.isForgetPwdLogin? $t('auth.next'): $t('auth.signin')}}</v-btn>
    <div
      class="more-button-layout other-login"
      v-if="!auth_loginByForgetPwd.isForgetPwdLogin"
    >
      <v-button
        v-if="registerLoading"
        class="register-loading"
        :type="'is-loading'"
        :ripple="false"
      ></v-button>
      <span class="txt-link register" v-if="clientConfig_auth.openRegister" @click="preLoginForRegister(auth_server)">{{$t('auth.register')}}</span>
      <span class="txt-link login-type" @click.self.stop="chooseLoginType" v-if="this.auth_loginType.length>1">
        {{$t('auth.otherLoginWay')}}
        <i class="icon xe678" :class="{'scale-xe678': isExpend}">&#xe678;</i>
      </span>
      <list
        :listData="auth_loginType"
        :isShow="isExpend"
        :selectedIndex="userType"
        @close-select-list="closeSelscList"
        @select-item="selectItem"
        class="list-size"
      ></list>
    </div>
    <!-- 验证码弹框 -->
    <div v-if="isVerfyShow">
      <verfy-code
        :nation="auth_nationCode"
        :account="account"
        :userType="info.userType"
        :img="verifyImg"
        @verfy="isVerfyShow=false"
      ></verfy-code>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import vBtn from './../common/button.vue';
import vTip from './../common/tooltip.vue';
import List from './../common/list.vue';
import VerfyCode from './../Verfy/VerfyCode.vue';
import LoginMixins from './LoginMixins';
export default {
  components: {
    vBtn,
    List,
    vTip,
    VerfyCode
  },
  mixins: [LoginMixins],
  data() {
    return {
      placeholder: '', // {{$t('auth.getVerifyCode')}}
      isLoading: false,
      isExpend: false,
      avatar: this.$config.clientConfig.avatar.logo,
      userType: 0,
      patrn: /^[0-9]*$/,
      registerLoading:false,
      isNationShow: true,
      nationCode: '', // 地区码：+86
      nationCodeText: '', // 地区原码：0086
      codePlaceholder: this.$t('auth.nationCode')
    }
  },
  computed: {
    ...mapGetters([
      'auth_loginType',
      'auth_server',
      'auth_nationCode',
      'auth_loginByForgetPwd',
      'clientConfig_auth'
    ]),
    isNationCode() {
      return this.userType === 1 || this.userType === 96;
    },
    // 不同登录类型密码框显示提示文本
    pwdPlacehold() {
      return 96 === this.userType ? this.$t('auth.verifyCode') : this.$t('auth.pwd');
    },
    // 过滤当前国家国家码
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
  },
  created() {
    // 以忘记密码方式跳转到首次登录界面，初始化一下字段
    if (this.auth_loginByForgetPwd.isForgetPwdLogin) {
      this.initForgetPwdLoginData()
      /**
       * 这里设置验证传递的参数是否为纯数字，如果包含非法字符，则不自动填充表单
       * 因为涉及国际化，所以未作手机号格式匹配
       */
      this.account = this.patrn.test(this.auth_loginByForgetPwd.account) ? this.auth_loginByForgetPwd.account : '';
      return;
    }
    //  初始化登录类型
    this.placeholder = this.auth_loginType[0].val;
    this.userType = this.auth_loginType[0].type;
    this._onEnterEvent(this.onlogin);

    let areaCode = this.auth_nationCode === '' ? this.$Service.config.getSystemNationCode() : this.auth_nationCode;
    console.log('code:::', areaCode);
    this.initNationOption(areaCode);
  },
  watch: {
    
    /***
     * 首次登陆界面，不需要跳转路由，页面不会重新创建，导致一下字段状态无法更新。
     * 监听忘记密码登录标识，更新一下字段状态。
     */
    'auth_loginByForgetPwd.isForgetPwdLogin': {
      handler: function() {
        let recordObj = {
          placeholder: this.placeholder,
          userType: this.userType,
          account: this.account
        }
        if (this.auth_loginByForgetPwd.isForgetPwdLogin) {
          this.password = '';
          /**
           * 首次登录页面和忘记密码登录页面共享同一个文件，所以不存在路由跳转
           * 当从首次登录页面转到忘记密码登录页面，此时将跳转前的数据保存起来，
           * 如果用户在忘记密码页面点返回时，恢复首次登录页面信息，避免数据被清空，造成该用户重新输入
           */
          localStorage.setItem('record-account', JSON.stringify(recordObj));
          /***
           * 设置延迟：为了避免localStorage没设置成时，原数据被修改，导致最终设置成了修改后的数据
           */
          setTimeout(() => {
            /**
             * 登录类型判断：因为忘记密码时以手机验证码登录的，
             *             当用户选择以手机号登录时，跳转到忘记密码才自动填充表单，
             *             如果非手机号登录方式则不
             *             因为涉及国际化，所以未作手机号格式匹配
             */
            if (recordObj.userType === 1 || recordObj.userType === 96) {
              this.account = this.patrn.test(this.account) ? this.account : '';
            } else {
              this.account = ''
            }
            this.initForgetPwdLoginData()
          }, 50)
        } else {
          /**
           * 首次登录页面从忘记密码返回到登录页面时，恢复用户之前的表单输入数据。
           */
          recordObj = JSON.parse(localStorage.getItem('record-account'));
          this.placeholder = recordObj.placeholder;
          this.userType = recordObj.userType;
          this.info.userType = recordObj.userType;
          this.account = recordObj.account;
        }
      }
    }
  },
  methods: {
    loginEvent(){
      this.onlogin();
    },
    initForgetPwdLoginData() {
      this.placeholder = this.$t('auth.phone');
      this.userType = 96;
      this.info.userType = 96;
    },

    onlogin() {
      console.log('触发一次');
      this.info.userType = this.userType;
      // 首次登录 使用设置的码,更换设别/忘记密码使用vuex中的数据
      this.info.user = this.getLoginAccount(this.account, this.auth_nationCode);
      this.info.pwd = this.password;
      this.info.server = this.auth_server;
      this.info.nation = this.auth_nationCode;
      this.login();
    },

    onGetVerifyCode() {
      if (this.invalidMobile(1, this.account)) return;
      let param = {
        account: this.getLoginAccount(this.account, this.auth_nationCode),
        server: this.auth_server
      }
      this.regCodeLogin(param);
    },

    // 其他登录方式
    chooseLoginType() {
      console.log(this.auth_loginType);
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
    selectedNation({val, index}) {
      if (val) {
        this.nationCodeText = this.$i18n.messages[`${this.$i18n.locale}`].AreaCode[val];
        this.nationCode = `+${this.nationCodeText.replace(/\b(0+)/gi,'')}` ;
        this.$Service.log(`选择国家码:::${this.nationCode}`);
        //将当前地区码存入vuex
        this.$store.commit('SET_NATIONCODE', this.nationCodeText);
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
  }
}
</script>
<style lang="scss">
@import './../_auth';
.login-init{
  display: flex;
  flex-direction: column;
  width: 280px;
  height: auto;
  padding-top: 85px!important;
  position: relative;
  .hidden-item{
    visibility: hidden;
  }
  .input-line{
    bottom: -1px;
  }
  .other-login{
    position: relative;
    //justify-content: space-between;
    .list-size{
      max-height: 108px;
      overflow-y: auto;
    }
    .register-loading{
      position: absolute;
      top: 8px;
      left: 55px;
    }
    .register{
      width: 100%;
      display: flex;
      justify-content: flex-start;
    }
    .login-type{
      width: 100%;
      display: flex;
      justify-content: flex-end;
    }
  }
  .auth-font{
    font-size: $--font-size-mid;
    line-height: 2.0;
  }
  .avatar.is-medium {
    width: 110px;
    height: 110px;
  }
  .icon-account{
    min-width: 45px;
    max-width: 100px;
    position: relative;
    display: inline-flex;
    align-items: center;
    .nation-code-ban{
      position: absolute;
      left: 9px;
      top: 8px;
      font-size: $--font-size-mid;
      color: get-grey-color(base);
    }
    .nation-code{
      top: 0px!important;
      left: 0px!important;
      font-size: $--font-size-mid;
      color: get-grey-color(base);
      font-family: '\5FAE\8F6F\96C5\9ED1', 'Microsoft YaHei', Arial, Helvetica, sans-serif, '\5B8B\4F53';
      /deep/ .control .input{
        width: 100px;
        padding: calc(0.375em - 1px) calc(0.625em - 4px)!important;
        color: get-grey-color(base)!important;
      }
      /deep/ .dropdown-menu{
        max-width: 300%!important;
        .dropdown-item{
          padding: 0.375rem 1rem;
        }
      }
    }
    .icon-option{
      position: absolute;
      right: 0px;
      height: 100%;
      width: auto;
      @include z-index(btn);
      transition: .5s;
      pointer-events: auto;
      &.scale-icon{
        transform: rotate(180deg);
        transform-origin: 50% 50%;
        transition: 0.3s;
      }
      &:hover{
        cursor: pointer;
      }
    }
  }
  .is-right{
    width: auto !important;
  }
  .ver-code{
    font-size: $--font-size-mid;
    display: inline-block;
    padding-right: 5px;
    color: get-grey-color(darken-3);
    background: $--color-white;
    font-family: '\5FAE\8F6F\96C5\9ED1', 'Microsoft YaHei', Arial, Helvetica, sans-serif, '\5B8B\4F53';
    &:hover{
      background: $--color-white;
      color: get-grey-color(darken-3);
    }
  } 
}
</style>
