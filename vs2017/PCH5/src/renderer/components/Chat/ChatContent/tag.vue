<template>
    <span
      class="v-chip__content"
      :style="{backgroundColor: color}">
      <slot></slot>
      <span  class="v-chip__text">{{text}}</span>
      <i class="icon v-chip__close" v-if="closable"  @click="handleClose">&#xe644;</i>
    </span>
</template>
<script>
  export default {
    name: 'ElTag',
    props: {
      text: String,
      closable: Boolean,
      type: String,
      color: String
    },
    created() {
      console.log('text', this.text)
      console.log('closable',this.closable)
    },
    methods: {
      handleClose(event) {
        this.$emit('closetag', event);
      }
    }
  };
</script>
<style lang="scss" scoped>
.v-chip__content{
  padding: 0 4px 0 4px;
  align-items: center;
  border-radius: 3px;
  cursor: default;
  display: inline-flex;
  height: 28px;
  justify-content: space-between;
  // padding: 0 12px;
  vertical-align: middle;
  white-space: nowrap;
  color: rgba(0,0,0,0.87);
  position: relative;
  z-index: 1;
  .v-chip__text {
    font-size: 12px;
    max-width: 100px;
    @include ellipsis;
  }
  .v-chip__close{
    align-items: center;
    display: flex;
    font-size: 18px;
    margin: 0 2px 0 4px;
    text-decoration: none;
    user-select: none;
    color: inherit;
  }
}
</style>
