<template>
  <div class="sett">
    <span class="sett-loading">
      <i class="icon loading-start" v-if="isLoading">&#xe6ac;</i>
      <i class="icon loading-success" v-if="!isLoading">&#xe632;</i>
    </span>
  </div>
</template>
<script>
export default {
  data() {
    return {};
  },
  props: ["isLoading"]
};
</script>
<style lang="scss" scoped>
.sett {
  display: inline;
  margin-left: 5px;
  .sett-loading {
    width: 16px;
    height: 16px;
    color: $--color-success;
    display: inline-flex;
    .icon {
      height: 16px;
    }
    .loading-start {
      font-size: $--font-size-primary;
      color: $--color-danger;
      animation: suerSettLoading 0.7s linear infinite;
      transform-origin: 8px 7px;
    }
    .loading-success {
      height: 16px;
      width: 16px;
    }
  }
}
</style>
