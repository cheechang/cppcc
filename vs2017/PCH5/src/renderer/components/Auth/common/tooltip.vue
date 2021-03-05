<template>
  <div class="auth-tip">
    <span
      v-if="isLabelTip"
      class="a-tip"
      :class="[tipPosition, classAttr]"
    >
      <div class="left-icon"><i class="icon icon-size" v-html="typeIcon"></i></div>
      <div class="center-msg">{{tipLabelMsg}}</div>
      <div class="right-icon"><i class="icon icon-close" @click="$emit('close')">&#xe650;</i></div>
    </span>
    <slot></slot>
    <div
      class="light-line"
      :class="isLightLine?'light-line-open':'light-line-close'"
      v-if="hasLine"
    ></div>
  </div>
</template>
<script>
import { clearTimeout } from 'timers';
export default {
  data() {
    return {
      timer: null
    }
  },
  props: {
    tipLabelMsg: String,
    isLabelTip: Boolean,
    isLightLine: {
      type: Boolean,
      default: false
    },
    hasLine: {
      type: Boolean,
      default: false
    },
    tipPosition: {
      type: String,
      default: ''
    },
    isSuccess: Boolean
  },
  computed: {
    classAttr() {
      return {
        'is-success': this.isSuccess
      }
    },
    typeIcon() {
      return this.isSuccess ? '&#xe6a0;' : '&#xe6a1;'
    }
  },
  
  watch: {
    isLabelTip(val) {
      if(val){
        if(this.timer){
          clearTimeout(this.timer)
          this.timer = null;
        }
        this.timer= setTimeout(() => {
        this.$emit('close')
        }, 3000)
      }
    },
  }
}
</script>
<style lang="scss" scoped>
.auth-tip{
  display: inline-block;
  position: relative;
  .a-tip{
    display: flex;
    width: 100%;
    height: auto;
    justify-content: space-between;
    align-items: center;
    position: absolute;
    top: 100%;
    min-height: 40px;
    z-index: 10;
    // @include z-index(image);
    background: #ff5252;
    padding-right:5px;
    cursor: pointer;
    border-top: 4px solid rgba(0,0,0,0.12);
    box-sizing: border-box;
    font-size: $--font-size-mid;
    .left-icon, .right-icon{
      width: 20px;
      font-size: $--font-size-big;
      color: rgba(0,0,0,0.3);
    }
    .center-msg{
      width: 100%;
      padding: 7px 5px;
      color: $--color-white;
      line-height: 14px;
    }
  }
  .is-top{
    bottom: 100%;
    top: unset;
  }
  .is-success{
    background: #4caf50 !important
  }
  .light-line{
    height: 1px;
    position: absolute;
    bottom: -1px;
    width: 100%;
    left: 0;
  }
  .light-line-open {
    background:#1867c0;
    height: 2px;
    -webkit-animation: focus-anim .5s cubic-bezier(0.0, 0.0, 0.2, 1);
  }
  .light-line-close {
    -webkit-animation: blur-anim .5s cubic-bezier(0.0, 0.0, 0.2, 1);
  }
  @-webkit-keyframes focus-anim {
    0% {
      transform: scaleX(0);
    }
    100% {
      transform: scaleX(1);
    }
  }
  @-webkit-keyframes blur-anim {
    0% {
      height: 2px;
      background:#1867c0;
      transform: scaleX(1);
    }
    100% {
      height: 1px;
      transform: scaleX(0);
      background: #aec8d4;
    }
  }
}
</style>
