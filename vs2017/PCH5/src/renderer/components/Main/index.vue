<template>
  <div class="main">
    <!-- 导航栏 -->
    <nav-bar
      class="nav-bar"
      :isAddMenu="isAddMenu"
      :lastRouteId="lastRouteId"
      @animation-start="animationStart"
      @show-account="showAccount"
      @closeAccountCenter="hideAccountCenter"
      @updateLastRouteId="updateLastRouteId"
      @is-add-menu="getAddMenu"
      @server-list-click="showServerList"
    ></nav-bar>
    <div :class="['msglist-watermark',{'dark-watermark':user_darkWaterMark}]" v-if="user_waterMark && showWatermark">
      <div  class="msglist-area-watermark-bg" :style="computedWaterMark"></div>
    </div>
    <public-notice
      v-if="isShowNotify"
      :notifyContent="notifyContent"
      :notifyMsg="notifyMsg"
      @closeNotify="isShowNotify=false"
    ></public-notice>
    <!-- 会话/通讯录/应用 -->
    <keep-alive exclude="contact,userInfo,zenTao,ChatSystem,HomePage">
      <router-view style="-webkit-app-region: no-drag;"></router-view>
    </keep-alive>

    <div :class="getThemeImage"></div>
    <!-- <div class="theme-bg-box" ></div> -->
    <!-- 多服务器列表及子服务器添加-->
    <add-server v-if="isAddServer" :loginAccoutInfo="loginAccoutInfo" @close="isAddServer = false" @switchToServer="switchToServer"></add-server>
    <server-list  v-if="isServerList" :showTransition="serverListTransition" @close="showServerList" @switchToServer="switchToServer" @loginServer="loginServer"></server-list>
    <!-- 查找添加好友/创建群 -->
    <group-add-menu v-if="isAddMenu" :currentPos="currentPos" @close="isAddMenu = false" @showAddServer="showAddServer"></group-add-menu>
    <!-- 转发会话消息 -->
    <chat-search-list
      v-if="isOpenForward"
      :dbPath="dbPath"
      :zipFileSize="zipFileSize"
      :isPermitSend="isPermitSend"
      :type="handleType"
      :imgPreviewParam="imgPreviewParam"
      @close="isOpenForward=false"
    ></chat-search-list>
    <!-- 第三方授权 -->
    <auth-request
      v-if="isShowOAuth&&authRequestInfo"
      @responseRequest="responseOAuth"
      @close="refuseAuth"
      :thirdParty_authRequest="authRequestInfo"
    ></auth-request>
    <!-- 消息声音提醒 -->
    <audio ref="ring" id="audio" :src="audio"></audio>
    <!-- 语音通话视频通话远程协助声音提醒 -->
    <audio ref="rtcring" id="audioPlugin" :src="audioPlugin" loop></audio>
    <!-- 语音通话视频通话远程协助声音结束提醒 -->
    <audio ref="rtchangup" id="audioPluginEnd" :src="audioPluginEnd"></audio>
    <!-- 个人中心 -->
    <account-center
      v-if="isAccountCenter"
      :desigComponent.sync="desigComponent"
      @hide-account="[isAccountCenter=false, isAnimationStart=false]"
      :isAnimationStart="isAnimationStart"
      @isAccountCenter='hideAccountCenter'
      :defaultLeftTab="defaultLeftTab"
    ></account-center>
    <activate v-if="isActivate"></activate>
  </div>
</template>

<script>
import { mapGetters } from "vuex";
import NavBar from "./Navbar";
import MainMixin from './mixins/mainmixin';
import { resolve } from 'url';
export default {
  name: "Mains",
  components: {
    NavBar,
    activate: resolve => require(['../Activate/index.vue'], resolve),
    PublicNotice: resolve => require(['./publicNotice'], resolve),
    GroupAddMenu: resolve => require(["../Group/GroupAddMenu"], resolve),
    ChatSearchList: resolve => require(["../Chat/Msg/ChatSearchList"], resolve),
    AuthRequest: resolve => require(["../Auth/authRequest"], resolve),
    AccountCenter: resolve => require(["./../Account/index"], resolve),
    ServerList: resolve => require(["../Servers/ServerList/index"], resolve),
    AddServer: resolve => require(["../Servers/AddServer/index"], resolve)
  },
  mixins: [MainMixin],
  data() {
    return {
      isShowNotify: false,      //  是否显示公告
      notifyContent: "",
      notifyMsg: {},
    };
  },
  created() {
    this.afterCreated();
  },
  mounted() {
    this.afterMounted();
  },
  beforeDestroy() {
    this.removeEvent(); 
  },
  computed: {
  },

  methods: {
    /**
     * 更新最后一次会话路由ID
     * 便于其他模块返回会话模块时 定位于之前的会话
     */
    updateLastRouteId(id) {
      this.lastRouteId = id;
    }
  }
}; 
</script>

<style lang="scss" rel="stylesheet/scss" >
.main {
  display: flex;  
  /*flex-direction: column;*/
  height: 100%;
  .dark-watermark{
     opacity: 0.07 !important;
  }
  .msglist-watermark {
    pointer-events: none;
    width: 100%;
    height: calc(100% - 55px);
    position: absolute;
    left: 0px;
    top: 55px;
    opacity: 0.3;
    z-index: 99999;
    overflow: hidden;
    .msglist-area-watermark-bg {
      width: 127%;
      height: 200%;
      transform: rotate(-15deg);
      position: absolute;
      left: -71px;
      top: -378px;
    }
  }
  .nav-bar {
    min-height: 55px !important;
    .dood-navbar {
      @include navbar_bgs($--color-primary);
      background-size: 100% 100%;
      background-repeat: no-repeat;
    }
  }
  .input:focus {
    box-shadow: none !important;
  }
}
</style>

