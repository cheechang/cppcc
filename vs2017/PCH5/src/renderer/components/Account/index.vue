<template>
  <div class="account-center">
    <!-- 主题背景图 theme-bgimg-->
    <div
      class="theme-bg-box"
      :style="{opacity: isAnimationStart?'0':'1'}"
    ></div>
    <!-- 用户中心左侧列表 -->
    <module-tab
      @current-info="currentInfo"
      @isAccountCenter='isAccountCenter'
      :isAnimationStart="isAnimationStart"
      :desigComponent="currentTab"
      :defaultLeftTab="defaultLeftTab"
    ></module-tab>
    <!-- 正文 -->
    <div
      class="content"
      :style="{opacity: isAnimationStart?'0':'1'}"
    >
      <keep-alive>
        <component :is="currentTab"></component>
      </keep-alive>
    </div>
  </div>  
</template>
<script>
import { mapGetters } from 'vuex';
import ModuleTab from './ModuleTab.vue';
import UserInfo from './UserInfo/index.vue';
import SystemSettings from './Settings/SystemSettings/index.vue';
import SecuritySettings from './Settings/SecuritySettings/SecuritySettings.vue';
import InviteFriend from './Settings/InviteFriend/index.vue';
import AboutDood from './Settings/About/About.vue';
import Privacy from './Settings/Privacy/index.vue';
import NewMessageNotification from './Settings/NewMessageNotification/Notice/index.vue';
export default {
  components: {
    ModuleTab,
    UserInfo,
    SystemSettings,
    SecuritySettings,
    InviteFriend,
    AboutDood,
    Privacy,
    NewMessageNotification
  },
  data() {
    return{
      currentTab: 'UserInfo',
      currentComponent: 'UserInfo',
      isReturn: Boolean,
    }
  },
  props: {
    isAnimationStart: Boolean,
    desigComponent: String, // 入口：个人中心
    defaultLeftTab: String  // 入口：jssdk（首页或应用）
  },
  watch: {
    isAnimationStart(val) {
      if (val) {
        setTimeout(() => {
          this.$emit('hide-account')
        }, 150)
      }
    },
    desigComponent(val) {
       if (!val) return;
      this.currentTab = this.desigComponent
      this.$emit('update:desigComponent', '');
    },
  },
  created() {
    this.currentTab = this.defaultLeftTab
    if (this.desigComponent){
      this.currentTab = this.desigComponent;
      this.$emit('update:desigComponent', '');
    }
  },
  methods: {
    currentInfo(index, component) {
      this.currentTab = component;
    },
    isAccountCenter(val) {
      this.isReturn = val
      this.$emit('isAccountCenter',this.isReturn)
      console.log(this.isReturn)
    }
  }
}
</script>
<style lang="scss">
@keyframes gradientIn {
  from {
    opacity: 0;
  }
  to {
    opacity: 1;
  }
}
.account-center{
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  // @include z-index(btn);
  z-index: 70;
  .theme-bg-box{
    background-attachment: fixed;
    transition-delay: 0.1s;
    animation: gradientIn 0.3s cubic-bezier(0.4, 0, 0.2, 1);
    transition: 0.3s cubic-bezier(0.4, 0, 0.2, 1);
  }
  .content{
    display: flex;
    flex: 1;
    height: 100%;
    padding: 10px;
    box-sizing: border-box;
    position: relative;
    overflow: hidden;
    transition-delay: 0.2s;
    animation: gradientIn 0.3s cubic-bezier(0.4, 0, 0.2, 1);
    transition: 0.3s cubic-bezier(0.4, 0, 0.2, 1);
    .clear-chart-btn {
      color: $--color-white;
      display: inline-block;
      padding: 5px 10px;
      text-align: center;
      cursor: pointer;
      border-radius: $--border-radius-base;
    }
    &:hover{
      overflow-y: auto;
    }
    &::-webkit-scrollbar {
      display: none;
    }
  }
}
</style>
