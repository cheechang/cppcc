<template>
	<div class="system-settings">
    <!-- 自动启动 -->
    <auto-start></auto-start>
    <!-- 声音提醒 -->
    <!-- <notice></notice>   -->
    <!-- 热键设置 -->
    <hot-key></hot-key>
    <!-- 选择语言 -->
    <Lang v-if="clientConfig_auth.openLanguageSet"></Lang>
    <!-- 清除聊天记录 -->
    <clear-chart></clear-chart>
	</div>
</template>
<script>
import { mapGetters } from "vuex";
// import notice from "./../NewMessageNotification/Notice/index.vue";
import hotKey from "./HotKey.vue";
import autoStart from "./AutoSatr";
import clearChart from "./ClearChart";
import Lang from './Lang.vue'
export default {
  computed:{
    ...mapGetters([
      'clientConfig_auth'
    ]),
  },
  components: {
    hotKey,
    autoStart,
    clearChart,
    Lang,
  //  notice
  }
};
</script>
<style lang="scss">
.system-settings {
  width: 100%;
  height: 100%;
  padding: 15px;
  color: get-grey-color(base);
  font-size: $--font-size-mid;
  background: $--color-white;
  box-sizing: border-box;
  overflow: hidden;
  border-radius: $--border-radius-base;
  &:hover {
    overflow-y: auto;
  }
  &::-webkit-scrollbar {
    display: none;
  }
  .various-item {
    color: get-grey-color(darken-3);
    width: 100%;
    .settings-content {
      padding: 10px 0 10px 95px;
    }
  }
}
</style>
