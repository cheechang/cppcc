<template>
  <div class="is-title">
      <div class="is-left" >
        <slot name="prepend"></slot>
      </div>
      <div class="title-name">{{name}}</div>
      <div class="is-right">
        <slot name="append"></slot>
      </div>
  </div>
</template>
<script>
export default {
  name: 'vTitle',
  props: {
    name: String
  }
}
</script>

<style lang="scss" scoped>
.is-title {
  display: flex;
  background: #394871;
  height: 50px;
  margin: 0;
  width: 100%;
  .is-left {
    height: 100%;
    width: 100px;
    display: flex;
    align-items: center;
    padding-left: 15px;
  }
  .title-name {
    height: 100%;
    @include ellipsis;
    display: flex;
    flex: 1;
    font-size: 18px;
    justify-content: center;
    color: #fff;
    align-items: center;
  }
  .is-right {
    width: 100px;
    height: 100%;
    display: flex;
    align-items: center;
    justify-content: center;
  }
}
</style>

