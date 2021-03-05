<template>
  <div class="auth">
    <!-- 禁止操作遮罩层 -->
    <div class="is-operating" v-if="isOperating"></div>
    <!-- 登陆界面主题毛玻璃效果 -->
    <div class="theme-frosted-glass"></div>
    <!-- 顶部最窗口控制按钮 -->
    <views-contorl v-if="viewControlShow"></views-contorl>
    <!-- 登录页面正文 -->
    <div class="auth-router-view-box" :class="{'is-drag': isNodrag}">
      <transition name="zoom-in-center" mode="out-in">
        <keep-alive include="register">
          <router-view
            class="router-view boxshadow-0"
            @is-shading="getIsShading"
            @is-nodrag="e => isNodrag = e"
          ></router-view>
        </keep-alive>
      </transition>
    </div>
    <!-- 更多设置,包含跳转到高级设置、忘记密码 -->
    <div class="more-settings" v-if="this.$route.name !== 'Prelogin'&& this.$route.flag !== 'register'&&this.$route.name !== 'PhoneVerify'">
      <div class="left">
        <!-- 返回按钮 -->
        <a @click="goback" v-if="isGoBack">{{$t('auth.goBack')}}</a>
        <!-- 分隔符 -->
        <span class="txt-padding" v-if="clientConfig_auth.openHighSetting&&isGoBack && this.$route.name !== 'Advanced'">|</span>
        <span v-if="$route.name !== 'Advanced' && $route.name !== 'Activate'">
          <!-- 高级设置按钮 -->
          <a @click="toAdvanced" v-if="clientConfig_auth.openHighSetting&&$route.name === 'LoginInitPage'">{{$t('auth.moreSettting')}}</a>
          <!-- 忘记密码按钮 -->
          <a
            v-if="clientConfig_auth.openForgetPwd&&$route.name !== 'Register' && !auth_loginByForgetPwd.isForgetPwdLogin"
            @click="forgetPassword"
          >
            <span class="txt-padding" v-if="$route.name !== 'Login'">|</span>
            <span class="forget-hover">{{$t('auth.forgetpwd')}}</span>
          </a>
        </span>
        <v-button v-if="isForgetpwdLoading" class="forgetpwd-loading" :type="'is-loading'" :ripple="false"></v-button>
      </div>
      <div class="right" v-show="false">
        <span v-if="isCurrentServerTip">{{$t('auth.currentServer')}}: {{auth_server}}</span>
      </div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import ViewsContorl from "../Common/ViewsControl";

import LoginMixins from './Login/LoginMixins';
export default {
  mixins: [LoginMixins], 
  data() {
    return {
      isOperating: false,
      isNodrag: false,
      isForgetpwdLoading:false
    };
  },
  components: {
    ViewsContorl
  },
  computed: {
    ...mapGetters(['auth_loginByForgetPwd', 'auth_server','clientConfig_auth','clientConfig_system']),
    isGoBack() {
      return this.$route.name === 'Advanced'||
             this.$route.name === 'LoginInitPage'
    },
    isCurrentServerTip() {
      return this.$route.name !== 'Register'&&this.$route.name !== 'PhoneVerify';
    },
    viewControlShow() {
      return !this.$is.isWeb() && !this.$is.isOSX;
    }
  },
  created() {
    //  判断是否是首次登录，如果是首次登录则跳转至预登录页面
    this.initData();
    // 获取用户头像目录
    this.$Service.config.headImgPath(null, resp => {this.$store.commit("SET_HEADIMG_PATH", resp.path);});
    
    this.$Service.config.getLoginInfos(null, this._getLoginHistoryHandler);
    
    // 获取本地app
    // this.getLocalApp();
  },
  methods: {
    // 路由返回
    goback() {
      /**
       * 当从忘记密码登录界面跳转到高级设置后，再返回到忘记密码界面。
       * 避免初始化忘记密码登录的两个标识字段
       */
      if (this.$route.name === 'Advanced' && this.auth_loginByForgetPwd.isForgetPwdLogin) {
        this.$router.go(-1);
        return
      }
      /**
       * 当再首次登录界面，点击忘记密码后，因为不存在跳转路由
       * 此时只是更新了忘记密码标识 loginInitForget 的状态
       * 避免在返回时直接跳转路由到上一个界面
       */
      console.log(JSON.stringify(this.auth_loginByForgetPwd.loginInitForget));
      if (!this.auth_loginByForgetPwd.loginInitForget) {
        this.$router.go(-1);
      }
      /**
       * 用于判断是否是忘记密码登录 isForgetPwdLogin 的状态
       * 此处设置延迟，是为了处理在点击返回后，路由还未完全结束时
       * isForgetPwdLogin 状态以初始化，导致界面随即更新，
       * 出现路由跳转前的一个闪烁情况
       */
      setTimeout(() => {
        this.$store.commit('INIT_LOGIN_BY_FORGETPWD');
      }, 100);
      // 初始化是否是从首次登录界面切换到忘记密码登录状态
    },
    /**
     * 显示遮罩层
     * 避免点击登录时，界面还可以在操作
     */
    getIsShading(e) {
      this.isOperating = e
    },
    // 跳转到高级设置
    toAdvanced() {
      this.$router.push({ path: '/Advanced'})
    },

    //  初始化数据
    initData() {
      this.$store.commit('SET_NATIONCODE', this.$Service.config.getSystemNationCode());
      this.$store.commit('SET_SERVER', this.$config.clientConfig.auth.server);
    },

    _getLoginHistoryHandler(resp) {
      console.log('历史登录信息:::', resp);
      // 首次登录，跳转至预登录页面
      let routePath = {path: '/Prelogin'};
      if(this.clientConfig_auth.openUnicomAuth){
        routePath = {path: '/Login'};
      }
      if (resp.LoginInfos !== undefined && resp.LoginInfos.length !== 0) {
        // 有登录历史则跳转到二次登录
        routePath.path = '/Login';
        console.log('in logined page',resp.LoginInfos);
        let historyData = [];
        resp.LoginInfos.forEach((item, index) => {
          if (item.account.indexOf('0086') === 0 || item.account.indexOf('0060') === 0) {
            item.account = item.account.slice(4);
          }
          // 解析server和elogo
          let serverArray = item.server.split(';');
          item.server = serverArray[0];
          if(serverArray.length > 1){
            item.elogo = serverArray[1];
          }
          historyData.push(item);
        })
        this.$store.commit('SET_LOGININFOS', historyData);
        console.log(resp.LoginInfos);
      }
      console.log('route path: ', routePath.path);
      this.$router.push(routePath);
    },

    // 忘记密码
    forgetPassword() {
      this.isForgetpwdLoading = true;
      this.$Service.auth.prelogin({ server: this.auth_server },resp=>{
        if (resp.code !== 0 || resp === undefined || resp.json === undefined || resp.json === '') {
          this.$toast.open({message: getErrorMsg(resp.code), type: 'is-danger'});
          console.log(this.isErrorBox);
          return;
        }
        let obj = JSON.parse(resp.json);
        let canFindPhone = false;
        let canFindEmail = false;
        obj.accounts.forEach((element,index) => {
          if(Object.keys(element)[0] === '1') {
            canFindPhone = true;
          }
          if(Object.keys(element)[0] === '3') {
            canFindEmail = true;
          }
        })
        if(canFindPhone){  //跳转至手机修改密码界面
          this.isForgetpwdLoading =false;
          this.changePwdhandOut()
          return;
        }
        if(canFindEmail){ //跳转至网页邮箱修改密码
           this.openSecUrl(this.auth_server)
           return;
        }
        this.isForgetpwdLoading = false;
        this.$toast.open({message: this.$t('auth.contactAdmin'), type: 'is-danger'});
      })   
    },

    // 查找本地app
    // getLocalApp() {
    //   if (this.$is.isWeb()) {
    //     //  如果是web环境则不执行
    //     return;
    //   }
    //   console.log('local static path:::', this.$AppPath.staticPath());
    //   let appPath = `${this.$AppPath.staticPath()}/plugins/localApp/`;
    //   let titleReg = /<loacl-app-info\s+app-info='([^']*)'/; // 获取本地应用信息
    //   console.log('local apps path:::', appPath);
    //   if (!this.$fs.existsSync(appPath)) {
    //     // 判断如果没有这个目录则创建 ?
    //     this.$fs.mkdirSync(appPath); 
    //   }

    //   this.$fs.readdir(appPath, (err, files) => {
    //     console.log('in this.$fs.readdir：：：', files);
    //     if (err) {
    //       console.log('加载本地应用：：：读取目录信息失败：：：', err);
    //       return
    //     };
    //     console.log(files);
    //     files.forEach(filename => {
    //       // 读取本地应用index.html中应用信息标签<loacl-app-info>,匹配查询应用信息
    //       let localAppPath = appPath + filename;
    //       console.log('localAppPath: ', localAppPath);
    //       this.$fs.readFile(`${localAppPath}/index.html`,
    //         (err, data) => {
    //           console.log('data: ', data);
    //           let appInfo = JSON.parse(titleReg.exec(data.toString('utf-8'))[1])[0];
    //           console.log('i get appInfo: ', appInfo);
    //           let appIcon = `${localAppPath}/static/img/appIcon.png`;
    //           this.$store.commit(
    //             'SET_LOCALAPP',
    //             {
    //               isApp: true,
    //               isLocalApp: true,
    //               isTop: 0,
    //               hasInstall: 1,
    //               appID: appInfo.appID.toString(),
    //               appIcon: appIcon,
    //               appName: this.getAppNameById(appInfo.appID.toString(), appInfo.appName),
    //               //appName: appInfo.appName,
    //               mainUrl: `${localAppPath}/index.html`
    //             }
    //           )
    //         }
    //       )
    //     })
    //   });

    //   console.log('end of getLocalApp...');
    // }
  }
};
</script>
<style lang="scss" scoped>
@import './_auth';
.auth {
  width: 100%;
  height: 100%;
  // position: relative;
  @include theme_image($--background-img-primary);
  .auth-router-view-box{
    position: absolute;
    width: 100%;
    height: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    .router-view{
      -webkit-app-region: no-drag;
      background: #fff;
      padding: 15px;
      font-size: $--font-size-mid;
      border-radius: $--border-radius-base;
    }
  }
  .is-drag{
    -webkit-app-region: no-drag;
  }
  .more-settings {
    width: 100%;
    height: auto;
    position: absolute;
    bottom: 0;
    padding: 0 33px 33px 33px;
    font-size: $--font-size-mid;
    display: flex;
    justify-content: space-between;
    .left {
      -webkit-app-region: no-drag;
      display: flex;
      align-items: center;
      .forgetpwd-loading{
          color: transparent !important;
          pointer-events: none;
          background-color: transparent;
          height: 21px;
      }
      a {
        // color: #4368b8;
        color: $--color-text-bg;
        &:hover {
          color: $--color-white;
        }
      }
      .txt-padding{
        padding: 0 6px;
      }
      span {
        // color: #4368b8;
        color: $--color-text-bg;
        cursor: pointer;
        .forget-hover{
          &:hover{
            color: $--color-white;
          }
        }
      }
    }
    .right{
      // color: #4368b8;
      color: $--color-text-bg;
    }
  }
  .theme-frosted-glass{
    @include z-index(none);
    @include theme_image($--background-img-primary);
  }
  .is-operating{
    position: absolute;
    @include z-index(modal);
    width: 100%;
    height: 100%;
    -webkit-app-region: no-drag;
  }
}
</style>
