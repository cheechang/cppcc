<template>
  <div class="pre-login">
    <v-avatar class="logo boxshadow-1" :sex="6" :shape="'round'" :src="avatar"></v-avatar>
    <v-tip
      :tipLabelMsg="errorMsg"
      :isLabelTip="isErrorBox"
      :tipPosition="'is-top'"
      @close="isErrorBox = false"
    >
      <!-- <v-input
        class="inputs auth-input"
        hasLine
        hasLabel  
        v-model="server"
        :isAuth="true"
        :inputLineSite="'-1px'"
        :customType="'input-size'"
        :isBorder="false"
        :isBulma="false"
        :maxlength="50"
        :placeholder="$t('auth.server')"
      >
      </v-input> -->
    <v-auto-complete 
      class="inputs auth-input selectServer"
      :inputLineSite="'-1px'"
      :customType="'input-size'"
      :isBulma="false"
      ref="vautocomplete"
      :originArray="serverHistory"
      hasLine
      hasLabel
      v-model="server"
      :isBorder="false"
      :isAuth="true"
      :openOnFocus="true"
      :menuCanShow='isServerShow'
      :maxlength="50"
      @change="active => isServerShow = !active"
      @select="selectedServer"
      :placeholder="$t('auth.server')"
    >
      <template slot-scope="serverHistory">
        <div class="server-info">
          <div :style="{color:serverHistory.option === server?'#2196F3':'#000'}">
            {{serverHistory.option}}
          </div>
          <i class="icon icon-bingo"  v-if="serverHistory.option === server">&#xe81f;</i>
        </div>
      </template> 
    </v-auto-complete>
    <i class="icon icon-option" :class="{'scale-icon':!isServerShow}" @click.self.stop='isServerShow=!isServerShow'>&#xe77a;</i>
    </v-tip>
    <v-btn
      class="auth-button"
      :size="'v-button--max_width'"
      :disable="isDisable"
      :type="lodingState"
      @click="next"
    >{{$t('auth.next')}}</v-btn>
    <div class="more-button-layout" v-if="clientConfig_auth.openRegister||clientConfig_auth.openForgetPwd">
      <span class="txt-link" @click="signup" v-if="clientConfig_auth.openRegister">{{$t('auth.register')}}</span>
      <span class="vertical-line" v-if="clientConfig_auth.openRegister&&clientConfig_auth.openForgetPwd"></span>
      <span class="txt-link" @click="forgetPassword" v-if="clientConfig_auth.openForgetPwd">{{$t('auth.forgetpwd')}}</span>
    </div>
    <div class="auth-description" v-if="clientConfig_auth.openServerIntro">
      <p>{{$t('auth.getServiceWay')}}</p>
      <p>{{$t('auth.enterprise')}}</p>
      <p>{{$t('auth.individual')}}</p>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import vBtn from '../common/button.vue';
import vTip from '../common/tooltip.vue';
import { getErrorMsg } from '../../../utils/utils.js';
import LoginMixins from './LoginMixins';
import LoginTypeMixins from './LoginTypeMixins'
export default {
  mixins: [LoginMixins,LoginTypeMixins],
  components: {
    vBtn,
    vTip
  },
  data() {
    return {
      clickItem: '',
      server: '',
      serverHistory: [],
      isServerShow: true,
      isLoading: false,
      isActing: false,
      type: 1,
      errorMsg: '',
      isErrorBox: false,
      avatar: require('vrv-static/resources/images/common/logo.png')
    }
  },
  computed: {
    ...mapGetters(['auth_loginInfos','auth_server','clientConfig_auth', 'auth_loginServers']),
    isDisable() {
      let regexp = /[ \f\n\r\t\v]/;
      return this.server === '' || regexp.test(this.server);
    },
    lodingState() {
      return this.isLoading ? "is-loading" : "";
    }
  },
  watch: {
    isServerShow(val) {
      val ? this.$emit('is-nodrag',false) : this.$emit('is-nodrag', true);
    }
  },
  created() {
    if (this.auth_loginServers.length > 0) {
      this.serverHistory = [...this.auth_loginServers];
      this.server = this.serverHistory[0];
    } else {
      let serverList = [];
      this.auth_loginInfos.forEach(element => {
        serverList.push(element.server);
      });
      this.serverHistory = Array.from(new Set(serverList)) // 去重
      this.server = this.$route.query.server ? this.$route.query.server : this.$config.clientConfig.auth.server;
      this.$store.commit('SET_LOGINSERVERS', this.serverHistory);
    }
    document.onkeydown = e => {
      if (this.isLoading || this.server === '') {
        //  登录中则不响应
        return;
      }
      if (e.keyCode !== 13) {
        return;
      }
      this.next();
    }
    // this.server = this.$route.query.server ? this.$route.query.server : this.$config.clientConfig.auth.server;
  },
  methods: {
    selectedServer({val, index}) {
      this.server = val;
      console.log(val, index);
      this.clickItem = index;
    },
    next() {
      if (this.clickItem !== '') {
        for(var i = 0; i<this.serverHistory.length; i++){
          console.log('当前点击的下标',typeof(this.clickItem))
          if(i == this.clickItem) {
            this.serverHistory.splice(0, 0, this.serverHistory[this.clickItem]);
            this.serverHistory.splice(this.clickItem + 1, 1);
            this.$store.commit('SET_LOGINSERVERS', this.serverHistory);
          }
        }
      }
      if (this.isLoading || this.isActing) {
        return;
      }
      this.isLoading = true;
      this.$emit('is-shading', true);
      this.preLogin(1);
      console.log('this.serverHistory',this.serverHistory)
      
    },
    forgetPassword() {
      if (this.isLoading || this.isActing) {
        return;
      }
      this.acting = true;
      this.preLogin(3);
    },
    signup() {
      if (this.isLoading || this.isActing) {
        return;
      }
      this.acting = true;
      this.preLogin(2);
    },
    preLogin(type){
      if (type < 1 || type > 3) {
        console.log('类型错误');
      }
      this.type = type;
      this.server = this.server.replace(/(^\s+)|(\s+$)/g, '').replace(/\s/g, '');
      this.$Service.auth.prelogin({ server: this.server }, this._preloginHandler);
    },
    _preloginHandler(resp) {
      let funcArray = [this.doNext, this.doRegister, this.doForgetPassword];
      this.$Service.log(`获取预登录信息返回Code:::${resp.code}`);
      this.$Service.log(`获取预登录信息返回json:${resp.json}`);
      console.log('预登录接口返回resp:::', resp);
      this.$emit('is-shading', false);
      if (resp.code !== 0 || resp === undefined || resp.json === undefined || resp.json === '') {
        this.isLoading = false;
        this.isActing = false;
        this.errorMsg = getErrorMsg(resp.code);
        this.isErrorBox = true;
        console.log(this.isErrorBox);
        return;
      }   
      let obj = JSON.parse(resp.json);
      funcArray[this.type - 1](obj);
    },
    doForgetPassword(obj){  //忘记密码
      this.isActing = false;
      let canFindpwd = obj.accounts.some((element,index)=>{
        if(Object.keys(element)[0] ==='1'||Object.keys(element)[0] ==='3'){
          return true;
        }
      })
      console.log('canFindpwd:',canFindpwd);
      /**
       * 预登界面点击忘记密码，直接打开安全中心地址。
       * 并且只有在配置了手机号或邮箱登录时才能打开安全地址
       * 否则提示联系管理员
       */
      if(!canFindpwd) {
        this.errorMsg = this.$t('auth.contactAdmin');
        this.isErrorBox = true;
        return;
      }
      this.openSecUrl(this.server);
    },
    doRegister(obj){   //注册
      console.log('obj::::',obj);
      this.isActing = false;
      if((obj.systemConfig & 1) === 1){   //该服务器允许注册
        this.$router.push({path: '/first', query: {server:this.server}});
      }
      else{
        this.errorMsg = this.$t('auth.notAllowed');
        this.isErrorBox = true;
      }
    },
    doNext(obj){  //下一步
      this.isLoading = false;

      let serverVersion = obj.ServerVersion || obj.serverVersion;
      console.log(serverVersion, '当前服务器版本号');
      this.$store.commit('SET_SERVERVERSION', serverVersion);
      this.$store.commit('SET_SERVER', this.server);
      
      let nationCode = this.$Service.config.getSystemNationCode()
      console.log('this.$Service.config.getSystemNationCode(): ', nationCode);
      this.$store.commit('SET_NATIONCODE', nationCode);

      console.log('obj.accounts:',obj.accounts);
      let loginType = [];
      console.log('this.$oauth:',this.$oauth);
      if(this.$oauth){
        this.$oauth.getLoginType(null, resp=>{
          loginType = this.parseOauthResp(resp,obj);
          this.$store.commit('SET_LOGINTYPE', loginType);
          if (this.server !== this.auth_server) {
            this.$store.commit('SET_SERVER', this.server);
          }
          this.$router.push({path: '/LoginInitPage'})
        })     
      }
      else{
        loginType = this.getLoginTypeByServer(obj);
        this.$store.commit('SET_LOGINTYPE', loginType);
        if (this.server !== this.auth_server) {
          this.$store.commit('SET_SERVER', this.server);
        }
        this.$router.push({path: '/LoginInitPage'})
      }
    }
  }
}
</script>
<style lang="scss" scoped>
@import './../_auth';
@keyframes spin {
  from {
    transform: rotate(0deg);
  }
  to {
    transform: rotate(360deg);
  }
}
.pre-login{
  display: flex;
  flex-direction: column;
  width: 280px;
  height: auto;
  padding-top: 85px!important;
  position: relative;
  .forgetpwd-loading{
    position: absolute;
    top: 9px;
    right: 33px;
  }
  .register-loading{
    position: absolute;
    top: 9px;
    left: 33px;
  }
  .icon-option {
    position: absolute;
    right: 0;
    top: 17px;
    @include z-index(btn);
  }
  .v-input{
    padding-right: 4.25em;
  }
  .selectServer{
    /deep/ .control{
      width: 100%;
    }
    /deep/ .dropdown-item span b {
      color:#2196F3;
    }
    .server-info{
      display: flex;
      width: 100%;
      justify-content: space-between;
      .icon-bingo{
        color: #2196F3;
      }
    }
  }
}
</style>
