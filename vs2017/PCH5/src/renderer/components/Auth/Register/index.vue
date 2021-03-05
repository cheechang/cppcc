<template>
  <div class="register">
    <keep-alive>
      <router-view @is-nodrag="e => $emit('is-nodrag', e)"></router-view>
    </keep-alive>
  </div>
</template>

<script>
export default {
  name: 'register',
  created() {
    //this.$router.push({path: '/first'});
  },
}
</script>

<style lang="scss">
  .register{
    display: flex;
    flex-direction: column;
    width: 280px;
    height: auto;
    position: relative;
    .auth-tip {
      width: 100%;
      margin: 5px 0;
      border-bottom: 1px solid $--border-color-blue;
    }
    // .input-border {
    //   //border-bottom: none !important;
    // }
    .input-line{
      bottom: -1px;
    }
    input {
      font-size: $--font-size-mid;
      border:0px !important;
      //border-bottom: 1px solid #aec8d4 !important;
      box-shadow: none !important;
    }
  }
</style>
