<template>
  <div class="nav-navbar">
    <span v-if="auth_loginByForgetPwd.isForgetPwdLogin" class="forget-pwd-tip"></span>
    <v-navbar
      :tabList="tabList"
      :avatar="user_account.thumbAvatarUrl == ''?'':user_account.thumbAvatar"
      :activeIndex="$route.query.activeIndex"
      :isTabNameShow="isTabNameShow"
      :isTabTitleShow="isTabTitleShow"
      @menu-click="$emit('is-add-menu')"
      @server-list-click="$emit('server-list-click')"
      @show-account="showAccount"
      @changeTab="switchTab"
      @animation-start="$emit('animation-start')"
      @closeAccountCenter="$emit('closeAccountCenter')"
    >
      <v-badge
        v-if="computeUnread && user_localConfig.msg_remind !== 2"
        :value="computeUnread"
        class="unread-count-nav"
        slot="labelTip"
      ></v-badge>
      <i
        v-if="user_localConfig.msg_remind === 2"
        class="icon not-disturb-nav"
        slot="labelTip"
      >&#xe74c;</i>
      <i
        class="icon open-topApp"
        slot="labelOption"
        @click.stop="isTopAppList = !isTopAppList"
        :class="{'scale-xe678': isTopAppList}"
      >&#xe77a;</i>
    </v-navbar>
    <!-- 最大/最小化 -->
    <views-control v-if="getTitleVisiable && !$is.isOSX" @window-size="windowSize"></views-control>
    <!-- 置顶app列表 -->
    <top-apps v-if="isTopAppList" @close-appList="isTopAppList=false"></top-apps>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import ViewsControl from "../Account/ViewsControl.vue";
export default {
  name: "nav-bar",
  data() {
    return {
      listPosition: "",
      isTopAppList: false,
      platform:
        process.platform === "darwin" ||
        this.$router.path === "/RTCP2P" ||
        this.$router.path !== "/RemoteControl",
      isTabNameShow: false,
      isTabTitleShow: true,
      unreadCount: [],
      MaxWindow: false,
      openSkin: false,
      tabList: [
        {
          name: "HomePage",
          label: this.$t("navbar.home"),
          icon: "&#xe69d;",
          path: "/HomePage",
          index: 0
        },
        {
            name: "duty",
            label: this.$t("navbar.duty"),
            icon: "&#xe6bf;",
            // dropList: ["duty"],
            path: "/duty",
            index: 5
        },
        {
            name: "news",
            label: this.$t("navbar.news"),
            icon: "&#xe6a8;",
            // dropList: ["news"],
            path: "/news",
            index: 6
        },
        {
          name: "chat",
          label: this.$t("navbar.chat"),
          icon: "&#xe6b7;",
          dropList: ["chat", "test-chat"],
          path: "/chat",
          isDot: true,
          index: 1
        },
        {
          name: "contact",
          label: this.$t("navbar.contacts"),
          icon: "&#xe623;",
          dropList: ["contact"],
          path: "/contact",
          index: 2
        },
        {
          name: "work",
          label: this.$t("navbar.work"),
          icon: "&#xe683;",
          dropList: ["work"],
          path: "/work",
          index: 3,
          isDropdown: true
        },
        // {
        //   name: "Tasks",
        //   label: this.$t("navbar.tasks"),
        //   icon: "&#xe765;",
        //   dropList: ["Tasks"],
        //   path: "/Tasks",
        //   index: 4
        // }
      ]
    };
  },
  components: {
    ViewsControl,
  },
  props: {
    lastRouteId: String
  },
  computed: {
    ...mapGetters([
      "chat_chatList",
      "chat_chatContent",
      "user_account",
      "user_filePath",
      "user_localConfig",
      "http_head",
      "user_systemConfig",
      "user_defaultPage",
      "work_storeApps",
      "auth_loginByForgetPwd",
      "clientConfig_system",
      'chat_is_loopend'
    ]),
    computeUnread() {
      /**
       * 如果最近回话列表存在未读数 则显示
       * msg_remind 2 为全局免打扰状态
       *  */
      if (!this.chat_is_loopend) return
      if (!Object.keys(this.chat_chatList).length) return;
      if (this.user_localConfig.msg_remind === 2) return;
      /**
       * 获取最近会话列表中 含有未读消息的会话集合
       * 当没有未读选项时  不显示未读
       * 当仅仅只有一个未读选项时 而且此时该会话处于激活状态时 不显示未读
       * */
      // this.unreadCount = _.values(this.chat_chatList).filter(
      //   value => value.unreadCount > 0 && value.disturbSet !== 3
      // );
      this.setUnreadCount();
      if (
        !this.unreadCount.length ||
        (this.unreadCount.length === 1 &&
          this.unreadCount[0].id === this.$route.query.id)
      )
        return;

      return _.sumBy(this.unreadCount, function(o) {
        return o.unreadCount;
      });
    },
    getTitleVisiable() {
      return !(
        process.platform === "darwin" ||
        this.$route.path === "/RTCP2P" ||
        this.$route.path === "/RemoteControl"
      );
    }
  },
  created() {
    console.log(this.user_systemConfig & 4, this.user_systemConfig & 16);
    // 首页开关
    this.tabList[0].isHidden = false;
    // 工作台开关
    this.tabList[3].isHidden = this.clientConfig_system.disableWebview;
   // this.tabList[3].isHidden = (this.user_systemConfig & 16) != 1 << 4;
    // 注释任务模块
    this.tabList[4].isHidden = false;
    let page = "";
    if (!this.tabList[0].isHidden) {
      // 首页开启
      page = this.$Service.user.getLocalSettingSync(["defaultPage"]);
      if (page.length !== 0) {
        console.log("当前页为：：：", page[0]["value"]);
        if (page[0]["value"] !== "appOpenIndex") {
          this.jumpPage("linkdood", true);
        } else {
          this.jumpPage("appOpenIndex", true);
        }
      } else {
        // 首次登录
        this.jumpPage("appOpenIndex", true);
        this.$Service.user.addLocalSetting(
          [{ key: "defaultPage", value: "appOpenIndex" }],
          resp => {
            if (resp.code === 0) {
              console.log("首次登录，存储默认页信息成功");
              this.$Service.log("首次登录，存储默认页信息成功");
            }
          }
        );
      }
    } else {
      // 首页未开启
      page = this.user_defaultPage;
      this.jumpPage(page, false);
    }
  },
  methods: {
    setUnreadCount() {
      console.log('setUnreadCount')
      this.unreadCount = _.values(this.chat_chatList).filter(value => {
        return value.unreadCount > 0 && value.disturbSet !== 3
      });
    },

    windowSize(e) {
      console.log(e, "窗口尺寸");
      this.MaxWindow = e;
      console.log(this.MaxWindow);
    },
    /** 切换tab文件 */
    switchTab(data) {
      if (!this.tabList[0].isHidden) {
        let value = data.item.index !== 0 ? "linkdood" : "appOpenIndex";
        this.$Service.user.updateLocalSetting(
          { settings: [{ key: "defaultPage", value }] },
          resp => {
            console.log("更新默认页成功");
          }
        );
      }
      console.log("animation-start");
      this.$emit("animation-start");
      if (data.item.name === 'chat') {
        if (this.unreadCount.length) {
          let item = _.orderBy(
            this.unreadCount,
            ["isTop", "msgTime"],
            ["desc", "desc"]
          )[0];
          this.setMessageRead(item);
          item.id === "10000" // 10000 为系统消息
            ? (this.$router.replace({
                path: "/ChatSystem",
                query: { id: item.id, name: item.name }
              }),
              (item.unreadCount = 0))
            : this.$router.push({
                path: "/ChatRightArea",
                query: { id: item.id, name: item.name, chatType: item.chatType }
              });
        } else {
          if (this.$route.name !== "ChatRightArea") {
            this.lastRouteId
              ? this.$router.push({
                  path: "/ChatRightArea",
                  query: { id: this.lastRouteId }
                })
              : this.$router.push({
                  path: data.item.path,
                  query: {
                    name: data.item.name,
                    activeIndex: data.item.index,
                    title: data.item.label
                  }
                });
          }
        }
      } else {
        if (this.$route.name === "ChatRightArea") {
          this.$emit("updateLastRouteId", this.$route.query.id);
        }
        this.$router.push({
          path: data.item.path,
          query: {
            name: data.item.name,
            activeIndex: data.item.index,
            title: data.item.label
          }
        });
      }
    },

    /** 设置消息已读 */
    setMessageRead(item) {
      let setMessageReadParam = {
        targetId: item.id,
        msgId: "0"
      };
      this.$Service.chat.setMessageRead(setMessageReadParam);
    },
    showAccount(e) {
      this.$emit("show-account", e);
    },
    /**
     * 调转路由
     * page    路由页       string
     * isIndex 首页是否开启 boolean
     */
    jumpPage(page, isIndex) {
      let path = "/Chat";
      if (isIndex) {
        path = page === "appOpenIndex" ? "/HomePage" : "/HomePage";
      } else {
        if (page === "linkdood" || page === "attention" || page === "myself") {
          path = "/Chat";
        } else if (page === "buddy") {
          path = "/Contact";
        } else if (page === "tools") {
          path = "/work";
        }
      }
      this.$router.push({ path });
    }
  }
};
</script>

<style lang="scss" rel="stylesheet/scss" scoped>
.nav-navbar {
  /*position: relative;*/
  @include z-index(navigation);
  box-shadow: $--box-shadow-navbar;
  .open-topApp {
    padding-top: 6px;
    transition: 0.3s;
    font-size: 16px !important;
    width: 24px;
    height: 24px;
    @include z-index(btn);
    &::before {
      width: initial;
    }
  }
  .scale-xe678 {
    transform: rotate(180deg);
    transform-origin: 12px 14px;
  }
  .forget-pwd-tip {
    top: 34px;
    left: 42px;
    z-index: 1;
  }
}
</style>
