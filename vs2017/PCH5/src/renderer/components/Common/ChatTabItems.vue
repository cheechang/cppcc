<template>
  <div class="msg-type-tab theme-table" >
      <v-tabs position="is-centered"  class="block msg-type-tab-list"   v-model="currentTab"  @change="changeTab">
        <v-tab-item v-for="(tabs, index) in tabList" :label="tabs.tabName" :key="index" class="tab-type-item"   :iconTitle="tabs.iconTitle">
        <div class="tab-component" v-if="tabs.isLoad">
          <component v-show="currentTab===index" :is="tabs.tabView" v-bind="$attrs"></component>
        </div>
        </v-tab-item>
      </v-tabs>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
export default {
  data() {
    return {
      currentTab: 0
    }
  },
  props: {
    tabList: Array
  },
  methods: {
    changeTab(value) {
      console.log('changeTab:::::', value)
      this.currentTab = value
      this.$emit('changeTab', value)
    }
  }
};
</script>

<style lang="scss" >
.msg-type-tab{
  width: 100%;
  height: 100%;
  display: flex;
  flex:1;  //fit xp
  flex-direction: column; //fit xp
  .msg-type-tab-list {
    height: 100%;
    flex: 1;
    display: flex;
    flex-direction: column;
    .tab-type-item{
      height: 100%;
      display: flex;
      flex: 1; //fit xp
      flex-direction: column; //fit xp
      overflow: auto;
      .tab-component{
        // overflow: hidden;
        display: flex;
        flex: 1; //fit xp
        flex-direction: column; //fit xp
        width: 100%;
      }
    }
    .tab-content {
      flex: 1;
      height: 100%;
      // overflow: auto;
      flex:1;  //fit xp
      flex-direction: column; //fit xp
      display: flex; //fit xp
    }
  }
}
</style>
