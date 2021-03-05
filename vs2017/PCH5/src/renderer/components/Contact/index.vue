<template>
  <div class="contact-area default-bg">
    <!-- <Animates v-else loadTop="200"></Animates> -->
    <div class="contact-list theme-left-bgc theme-table">
      <div class="theme-frosted-glass">
        <div class="theme-left-bgc"></div>
      </div>
      <contact-tab></contact-tab>
    </div>
    <div class="home-detail-content">
      <div :class="{'home-detail-top-win':!$is.isOSX}"></div>
      <div class="contact-detail" :style="{height:!$is.isOSX? 'calc(100% - 27px)':'100%'}">
        <router-view></router-view>
      </div>
    </div>
  </div>
</template>
<script>
// import Animates from '../Common/Animate.vue';
import ContactTab from './ContactTab';
export default {
  name: 'contact',
  components: {
    // Animates,
    ContactTab
  }
};
</script>
<style lang="scss">
.contact-area {
  width: 100%;
  overflow: hidden;
  display: flex;
  height: 100%;
  background: url('~vrv-static/resources/images/common/default_bg.png') 60% 40% no-repeat;
  background-size: 160px;
  .contact-list {
    width: 226px;
    height: 100%;
    background: #fafafa;
    overflow-x: hidden;
    overflow-y: hidden;
    position: relative;
    z-index: 1;
    padding-top: 50px;
    .contact-item {
      overflow: hidden;
      &:hover {
        overflow-y: auto;
      }
    }
  }
  .home-detail-top-win{
    width: calc(100% - 100px);
    height: 27px;
    -webkit-app-region: drag;
  }
  .home-detail-content{
    width: calc(100% - 227px);
  }
  .contact-detail {
    display: flex;
    flex: 1;
    justify-content: center;
    align-items: center;
    height: 100%;
    .router-detail {
      margin: 10px;
      background: #fff;
      width: 100%;
      height: calc(100% - 20px);
      display: flex;
      align-items: center;
      justify-content: center;
      border-radius: $--border-radius-base;
    }
  }
}
</style>


