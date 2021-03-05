<template>
  <div
    class="settings-list"
    :style="{animation: listAnimation+'0.3s cubic-bezier(0.4, 0, 0.2, 1)'}"
  >
    <div class="theme-frosted-glass">
      <div class="theme-left-bgc"></div>
    </div>
    <div class="account-title">
      <i class="icon theme-txt">&#xe695;</i>
      <span class="theme-left-txt title-spacing">{{$t('user.personalCenter')}}</span>
      <i class="icon returnButton" @click="returnClick" :title="$t('auth.goBack')">&#xe6b5;</i>
    </div>
    <!-- 父列表组件 开始 -->
    <div
      class="control-list"
      v-for="(item,index) in dashboardItem"
      :key="index"
      @click.stop="showContent(item)"
    >
      <div
        class="control-list-title theme-list-items theme-left-txt"
        :class="{'theme-list-items-active': item.key === pressKey}"
      >
        <i
          class="icon icon-pos"
          :class="{'theme-txt':item.key === pressKey }"
          v-html="item.icon"
        ></i>
        <span class="txt-spacing">{{ item.title }}</span>
        <i v-if="item.children" class="icon icon-pos arrowpos" :class="showChild?'arrow-open':''">&#xe77a;</i>
        <span
          v-if="item.key ==='systemSettings'&&auth_loginByForgetPwd.isForgetPwdLogin"
          class="forget-pwd-tip"
        ></span>
      </div>
      <!-- 子列表组件 开始 -->
      <div v-if="item.children" >
        <transition name="slide" >
          <div class="item-child" v-show="showChild" :class="showChild?'open-list':''">
            <div
              class="list-item control-list-title theme-list-items theme-left-txt "
              v-for="(childrenItem,index) in item.children"
              :key="index"
              @click.stop="openChild(childrenItem)"
              :class="childrenItem.key === pressKey ? 'theme-list-items-son-active':''"
            >
              <span class="txt-spacing">{{childrenItem.title}}</span>
              <span
                v-if="childrenItem.key === 'security'&&auth_loginByForgetPwd.isForgetPwdLogin"
                class="forget-pwd-security-tip"
              ></span>
            </div>
          </div>
        </transition>
      </div>
      <!-- 子列表组件 结束 -->
    </div>
    <!-- 父列表组件 结束 -->
  </div>
</template>
<script>
import { mapGetters } from "vuex";
export default {
  name: "userInfo",
  data() {
    return {
      pressKey:'personalInfo',
      presschildIndex:0,
      pressItemIndex: 0,
      translateX: 0,
      dashboardItem: [
        {
          key:'personalInfo',
          title: this.$t("user.personalInfo"),
          icon: "&#xe61b;",
          component: "UserInfo"
        },
        {
          key:'systemSettings',
          title: this.$t('user.systemSettings'),
          icon: "&#xe653;",
          //component:'Setting',
          children: [
            {
              key:'general',
              title: this.$t("setting.general"),
              component: "SystemSettings"
            },
            // {
            //   key:'security',
            //   title: this.$t("user.security"),
            //   component: "SecuritySettings"
            // },
            {
              key:'newMessageNotification',
              title: this.$t("user.newMessageNotification"),
              component: "newMessageNotification"
            },
            // {
            //   key:'privacy',
            //   title: this.$t("user.privacy"),
            //   component: "privacy"
            // }
          ]
        },
        // {
        //   key:'inviteFriend',
        //   title: this.$t("user.inviteFriend"),
        //   icon: "&#xe6c1;",
        //   component: "InviteFriend"
        // },
        {
          key:'about',
          title: this.$t("setting.about"),
          icon: "&#xe692;",
          component: "AboutDood"
        }
      ],
      showChild: false
    };
  },
  props: {
    isAnimationStart: Boolean,
    desigComponent: String,
    defaultLeftTab: String
  },
  computed: {
    ...mapGetters(["auth_loginByForgetPwd"]),
    listAnimation() {
      return this.isAnimationStart ? "slideOutX " : "slideInX ";
    }
  },
  watch: {
    desigComponent() {
      this.setPressItemKey();
    }
  },
  created() {
    this.setPressItemKey();
  },
  methods: {
    // 切换模块
    showContent(item) {
      if (!item.hasOwnProperty("component")) {
        this.showChild = !this.showChild;
        this.pressKey = item.children[0].key;
        this.$emit("current-info", item.children[0].key, item.children[0].component);
        // 跳转push   item.chlidren[0].component
      } else {
        // 正常跳转
        if (item.key === this.pressKey) return;
        this.pressKey = item.key;
        this.showChild = false;
        this.$emit("current-info", item.key, item.component);
      }
    },
    setPressItemKey() {
      if (!this.desigComponent) {
        this.pressKey = 'personalInfo';
        _.filter(this.dashboardItem, (e, i) => {
          if (e.component !== this.defaultLeftTab) return;
          this.pressKey = e.key;
        });
      }
      console.log("this.desigComponent:::", this.desigComponent);
      this.dashboardItem.map((item) => {
        if (item.component === this.desigComponent) {
          this.pressKey = item.key;
          if(!item.hasOwnProperty('children')){
            this.showChild = false;
          }
        }
      });
    },
    openChild(item) {
      // 将当前组件名称传给setting组件
      this.$emit("current-info", item.key, item.component);
      this.pressKey = item.key;
      console.log('this.pressKey',this.pressKey)
      console.log('key',item.key)
      this.pressKey = item.key;
    },
    returnClick(){
      this.$emit('isAccountCenter',false)
    }
  }
}
</script>
<style lang="scss">
@keyframes slideInX {
  from {
    transform: translateX(-100%);
  }
  to {
    transform: translateX(0);
  }
}
@keyframes slideOutX {
  from {
    transform: translateX(0);
  }
  to {
    transform: translateX(-100%);
  }
}
.settings-list {
  width: 226px;
  height: 100%;
  overflow: hidden;
  color: $--color-black;
  position: relative;
  .icon-pos-invite {
    font-size: 24px !important;
  }
  .theme-left-bgc {
    width: 100%;
    height: 100%;
  }
  .txt-spacing {
    padding-left: 30px;
  }
  .forget-pwd-tip {
    top: 13px;
    right: 150px;
  }
  .forget-pwd-security-tip{
    top: 10px;
    right: 150px;
    position: absolute;
    background: red;
    height: 7px;
    width: 7px;
    border-radius: 50%;
  }
   .forget-pwd-security-tip:after{
     content:'';
     display:block;
     height:0px;
     clear:both;
     visibility: hidden;
   }
  .title-spacing {
    padding-left: 22px;
  }
  .theme-txt {
    @include font_color($--color-primary, "theme");
    opacity: 1 !important;
  }
  .theme-left-txt {
    font-weight: 500;
  }
  .account-title {
    padding: 15px 20px;
    border-bottom: 1px solid $--border-color-grey;
    cursor: default;
    i {
      font-size: 25px;
    }
    .returnButton{
      color:#999;
      cursor: pointer;
      font-size: 14px;
      position: absolute;
      top: 18px;
      right: 2px;
      display: inline;
    }
  }
  .control-list {
    font-size: 13px;
    position: relative;
    cursor: default;
    .arrowpos{
      margin-left: 20px;
      transition: 0.5s;
      transform: rotateX(0);
      &.arrow-open{
        transform: rotateX(180deg);
      }
    }
   
    i {
      font-size: 20px;
      opacity: 0.54;
    }
    .control-list-title {
      padding: 14px 20px;
    }
    .item-child {
      overflow: hidden;
      .list-item {
        padding: 10px 50px;
        cursor: pointer;
        position: relative;
      }
    }
    .slide-enter-active {
      animation: slide-in 0.5s;
    }
    .slide-leave-active {
      animation: slide-in 0.2s reverse;
    }
    @keyframes slide-in {
      0% {
        max-height:0px;
      }
      100% {
        max-height:200px;    // 此高度大于组件高度即可 不宜过高
      }
    }
  }
}
</style>