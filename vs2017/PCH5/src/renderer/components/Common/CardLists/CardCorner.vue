<template>
  <div>
    <div class="is-corner" @mouseenter="qrCodeHover=true" @mouseleave="qrCodeHover=false" @click="$emit('layout',isQrcodeLayout)"></div>
    <i class="icon qrcode-icon" :class="{'qrcode-icon-hover': qrCodeHover}" v-html="isQrcodeLayout?'&#xe683;':'&#xe685;'"></i>
  </div>
</template>
<script>
export default {
  data() {
    return {
      qrCodeHover: false
    }
  },
  props: {
    isQrcodeLayout: Boolean
  }
}
</script>

<style lang="scss">
.is-corner {
  position: absolute;
  right: 0;
  top: 0;
  border-bottom: 60px solid #fff;
  border-right: 60px solid rgba(0, 0, 0, 0.02);
  border-top-right-radius: $--border-radius-base;
  @include z-index(btn);
  cursor: pointer;
  box-shadow: $--box-shadow-elevation;
}
.qrcode-icon {
  position: absolute;
  font-size: 42px;
  color: rgba(0, 0, 0, 0.4);
  @include z-index(negative);
  right: -7px;
  top: -6px;
  width: 66px;
  height: 66px;
  background: #fff;
}
.qrcode-icon-hover {
  // color: #1B89C3;
  color: #000;
}
</style>

