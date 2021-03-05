<template>
  <nav class="dood-navbar is-transparent" ref="nav">
    <div class="dood-navbar-brand">
      <div class="navbar-left">
        <i
          class="icon online-icon"
          v-if="showOnlineStatus"
          :title="onlineStatusInfo.name"
          v-html="onlineStatusInfo.icon"
          :style="{color:onlineStatusInfo.color,'font-size':onlineStatusInfo.key===4?'14px':'16px'}"
          @click="isShowUserMenu=!isShowUserMenu"
        ></i>
        <v-avatar
          class="avatar-account"
          size="is-small"
          :sex="user_account.gender"
          :src="avatar"
          :offline="false"
          shape="round"
          @icon-click="isShowUserMenu=!isShowUserMenu"
        ></v-avatar>
        <!-- <v-avatar class="avatar-account" :class="{'avatar-account-hide': !isAvatar}" size="is-small" :sex="user_account.gender" :src="avatar" :offline="false" shape="round" @icon-click="isShowUserMenu=!isShowUserMenu">
        </v-avatar>-->
        <account-menu
          v-if="isShowUserMenu"
          @animation-start="$emit('animation-start')"
          @close="isShowUserMenu=false"
          @show-account="showAccount"
        ></account-menu>
        <div v-if="!isAvatar" class="search-list" ref="searchs">
          <div class="search-background" @click="reback"></div>
          <local-search
            v-model="inputSearch"
            :hoverIndex="hoverIndex"
            :direction="direction"
            :height="searchListHeight"
            :openChat="openChat"
            @updateList="setSearchData"
            @close="reback"
            @closeAccountCenter="$emit('closeAccountCenter')"
          ></local-search>
        </div>
        <div class="search-box" @click="handleSearch" v-if="this.$route.name==='Contact'|| this.$route.name==='MyDevice' || this.$route.name==='OfficialAccounts'|| this.$route.name==='EntAppInfo'|| this.$route.name==='GroupInfo'">
          <v-input
            v-model="inputSearch"
            maxlength="24"
            :placeholder="$t('chat.contactAndGroup')"
            class="is-hidden-mobile"
            size="is-border"
            position="right"
            ref="inputs"
            @keydown="navigateSearchList"
            @keyup-esc="reback"
            @focus="changeStyle"
          >
            <i
              class="icon del-btn"
              slot="expand"
              @click.stop="closeSearch"
              v-if="inputSearch"
            >&#xe650;</i>
          </v-input>
        </div>
        <!-- <div class="search-box" @click="changeStyle" :style="{'max-width':hasFinished?'20px':'216px'}">
          <v-input v-model="inputSearch" class="is-hidden-mobile" size='is-border' :position="hasFinished?'left':'right'" @keydown="navigateSearchList" @keyup-esc="reback" @focus="changeStyle" ref="inputs">
            <i v-if="hasFinished" class="icon search-btn" slot="expand">&#xe696;</i>
            <i v-else class="icon del-btn" slot="expand" @click.stop="closeSearch">&#xe650;</i>
          </v-input>
        </div>-->
        <!-- <div class="group-menu" @click="$emit('menu-click',$event)">
          <i class="icon icon-circle-hover">&#xe62c;</i>
        </div> -->
        <div class="group-menu mul-server-menu"  v-if="showServerListIcon" @click="$emit('server-list-click',$event)">
          <i class="icon icon-circle-hover icon-mult-server">&#xe6cd;</i>
          <div class="mult-server-msg-icon" v-if="showUnReadMultServersMsg">
          </div>
        </div>
      </div>
      <div @click="reback" class="navbar-center">
      <!--<div @click="reback" class="navbar-center" :style="{width: 70*navTabList.length+'px'}">-->
        <div
          class="navbar-item has-dropdown is-hoverable"
          :class="{'navbar-item-active':active==item.index}"
          v-for="item in navTabList"
          :key="item.index"
          :title="isTabTitleShow?item.label:''"
          @click="tabSwitch(item)"
        >
          <div class="navbar-click">
            <slot v-if="item.isDot" name="labelTip"></slot>
            <i
              v-if="!isTabNameShow"
              class="icon navbar-icon"
              :class="{active:active==item.index, 'contact-icon':item.index==2||item.index==0}"
              v-html="item.icon"
            ></i>
            <p v-else :class="{active:active==item.index}">{{item.label}}</p>
          </div>
          <!-- <div class="navbar-option" :class="{active:active==item.index}">
            <slot v-if="item.isDropdown" name="labelOption"></slot>
          </div> -->
        </div>
      </div>
      <div @click="reback" class="navbar-right" :style="computedSkin">
        <!--<i class="icon icon-circle-hover" @click.self.stop="changeLangEvent">&#xe697;</i>-->
        <i class="icon icon-circle-hover" @click.self.stop="openSkin">&#xe697;</i>
      </div>
      <!-- 用户选择主题下拉框 -->
      <theme-menu
        class="skin-menu"
        :openSkin="isOpenSkin"
        @close-theme="isOpenSkin = false"
        @click.native="closeSelectionTheme"
      ></theme-menu>
    </div>
  </nav>
</template>
<script>
import LocalSearch from "../../../components/Account/LocalSearch.vue";
import AccountMenu from "./../../components/../../components/Account/AccountMenu";
import vClickOutside from "../../../../renderer/components/Chat/v-click-outside/index";
import { getOnlineStatusInfo } from "../../../utils/utils.js";
import { getConfig } from '../../../../comm/util';
import { mapGetters } from "vuex";
export default {
  name: "vNavbar",
  data() {
    return {
      active: "",
      isAvatar: true,
      inputSearch: "",
      hoverIndex: -1,
      searchListNum: "",
      direction: 40,
      searchListHeight: 0,
      openChat: false,
      isOffline: false,
      hasFinished: true,
      isShowUserMenu: false,
      isFocus: false,
      showOnlineStatus: false, // this.$config.account.openOnlineStatus,
      onlineStatusInfo: {
        key: 1,
        name: this.$t("user.online"),
        icon: "&#xe62f;",
        color: "#57E26D"
      },
      isOpenSkin: false,
      // closeAccountCenter:Boolean,
    };
  },
  directives: {
    clickOutside: vClickOutside.directive
  },
  computed: {
    ...mapGetters([
      "user_netstat",
      "user_account",
      "auth_onlineStatus",
      'auth_multipleServers'
    ]),
    showUnReadMultServersMsg(){
      let multipleServers = Object.values(this.auth_multipleServers);
      return multipleServers.some((el,index)=>{
        return el.isOnline && el.isMsg
      })
    },
    showServerListIcon(){
      if(Object.values(this.auth_multipleServers).length>1){
        return true;
      }
        return false;
    },
    computedSkin() {
      // if (process.platform === "darwin") {
      //   return { paddingRight: "10px" };
      // } else {
      //   return { paddingRight: "110px" };
      // }
    },
    navTabList() {
      return this.tabList.filter(e => !e.isHidden);
    }
  },
  watch: {
    $route(e) {
      this.$signalMonitor.$on("toChatPage", resp => {
        this.active = 1;
      });
    },
    auth_onlineStatus(value) {
      this.onlineStatusInfo = Object.assign({}, getOnlineStatusInfo(value));
    },
    // 监听输入内容改变，hover恢复初始值
    inputSearch(value) {
      this.hoverIndex = -1;
    },
    // searchListNum(value) {
    //   this.fitSearchBoxHeight(value)
    // }
  },
  props: {
    tabList: Array,
    isTabNameShow: Boolean,
    activeIndex: Number | String,
    avatar: String,
    isTabTitleShow: Boolean
  },
  components: {
    LocalSearch,
    AccountMenu,
    ThemeMenu: resolve =>
      require(["../../../components/Theme/index.vue"], resolve)
  },
  created() {
    window.onresize = () => this.fitSearchBoxHeight();
    this.active = this.getActive();
    // this.$ipc.on('start-local-search', this.focusInput)
  },
  beforeDestroy() {
    // this.$ipc.removeListener('start-local-search', this.focusInput)
  },
  methods: {
    fitSearchBoxHeight(value=0) {
      console.log('fitSearchBoxHeight...', value)
      if (!this.isFocus && this.isAvatar) {
        if (!this.$refs.searchs) return;
        this.$refs.searchs.style.height = '';
        this.searchListHeight = 0;
      } else {
        this.$nextTick(() => {
          this.$refs.searchs.style.height =(document.body.clientHeight - 56) + 'px';
        })
        this.searchListHeight = document.body.clientHeight - 56;
        console.log("当前高度为：", this.searchListHeight);
      }
    },
    // 关闭主题列表
    closeSelectionTheme(e) {
      let skinMenuBox = document.getElementsByClassName("skin-menu")[0];
      if (!skinMenuBox.contains(e.target)) this.isOpenSkin = false;
    },
    // Ctrl+F搜索
    focusInput() {
      this.isFocus = true;
      if (!this.isAvatar)
        // 取消
        this.reback();
      // 搜索
      else this.$route.name==='Contact'&&this.$refs.inputs.$refs.input.focus();
    },
    // 删除标签上的style样式
    delAccountStyle() {
      if (document.getElementsByClassName("menu-user-info")[0].style)
        document
          .getElementsByClassName("menu-user-info")[0]
          .removeAttribute("style");
    },
    // tab下拉菜单点击事件
    handleClick(index, key) {
      this.$emit("clickEvent", index, key);
    },
    // tab路由跳转
    tabSwitch(item) {
      this.active = item.index;
      this.$emit("changeTab", { item: item });
    },
    // 右键菜单点击回调
    selectItem(index) {
      console.log(this.menuList[index]);
    },
    handleIconClick() {
      this.$emit("icon-click");
    },
    handleSearch() {
      if (this.isFocus) {
        return
      }
      this.isFocus = true;
      this.changeStyle();
    },
    changeStyle() {
      if (!this.isFocus) return;
      this.$nextTick(() => {
        this.isAvatar = false;
        // this.hasFinished = false;
        this.fitSearchBoxHeight()
        this.$route.name==='Contact'&&this.$refs.inputs.$refs.input.focus();
      });
    },
    closeSearch() {
      this.isFocus = false;
      this.$route.name==='Contact'&&this.$refs.inputs.$refs.input.focus();
      (this.inputSearch === "" && this.reback()) || this.clearResult();
    },
    clearResult() {
      this.inputSearch = "";
      this.searchListNum = "";
      this.hoverIndex = -1;
      this.isAvatar = true;      
      this.$nextTick(() => {
        this.$route.name==='Contact'&&this.$refs.inputs.$refs.input.blur();
      })
    },
    reback() {
      new Promise(resolve => {
        this.$nextTick(() => {
          this.clearResult();
          this.isFocus = false;
          // this.$refs.inputs.$refs.input.style.background = 'none';
          this.$route.name==='Contact'&&this.$refs.inputs.$refs.input.blur();
          resolve();
        });
      }).then(() => {
        this.isAvatar = true;
      });
    },
    navigateSearchList(e) {
      this.openChat = false;
      if (e.keyCode === 13 && this.hoverIndex !== -1) {
        e.preventDefault();
        e.stopPropagation();
        this.openChat = true;
      }
      if (e.keyCode !== 38 && e.keyCode !== 40) return;
      if (this.searchListNum === 0) return;
      this.direction = e.keyCode;
      if (e.keyCode === 40) {
        if (this.searchListNum - 1 > this.hoverIndex) this.hoverIndex++;
      } else if (this.hoverIndex > 0) {
        this.hoverIndex--;
      }
    },
    setSearchData(len) {
      this.searchListNum = len;
    },
    openSkin() {
      this.isOpenSkin = !this.isOpenSkin;
      // this.$emit('open-skin', this.isOpenSkin);
    },
    showAccount(e) {
      this.$emit("show-account", e);
    },
    changeLangEvent() {
      this.$dialog.confirm({
        confirmText: "确定",
        cancelText: "取消",
        message: `确定切换语言吗（当前：${this.$i18n.locale}）`,
        onConfirm: () => {
          console.log("this.$i18n.locale:::", this.$i18n.locale);
          if (this.$i18n.locale === "zh-CN") {
            this.$i18n.locale = "en-US";
          } else {
            this.$i18n.locale = "zh-CN";
          }
        }
      });
    },
    getActive() {
      let page = this.$route.name;
      console.log("当前page：：：",page)
      let index = 1;
      switch (page) {
        case "HomePage":
          index = 0;
          break;
        case "Chat":
          index = 1;
          break;
        case "Contact":
          index = 2;
          break;
        case "MyApp":
          index = 3;
          break;
        default:
          index = 1;
          break;
      }
      return index;
    }
  }
};
</script>
