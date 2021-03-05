<template>
  <div class="spinner" :class="{'spinner-min' : size === 'small' }" :style="{top:loadTop+'px'}">
    <div class="bounce1"></div>
    <div class="bounce2"></div>
    <div class="bounce3"></div>
    <p class="spinner-text" v-if="isShowText">正在加载数据</p>
  </div> 
</template>
<script>
export default {
  props: {
    loadTop: {
      type:Number | String,
      default: 0
    },
    isShowText: {
      type: Boolean,
      default: true
    },
    text: {
      type: String,
      default: '正在加载数据'
    },
    size: {
      type: String,
      default: 'normal'
    }
  }
};
</script>

<style lang="scss" scoped>
.spinner-min {
  div {
    width: 4px!important;
    height: 4px!important;
  }
}
.spinner {
  margin: 0 auto;
  width: 226px;
  text-align: center;
  position: absolute;
  top: 60px;
  .spinner-text {
    font-size: 14px;
    margin-top: 6px;
    color: #8f8fb6;
  }
}

.spinner > div {
  width: 15px;
  height: 15px;
  background-color: #8f8fb6;

  border-radius: $--border-radius-circle;
  display: inline-block;
  -webkit-animation: bouncedelay 1.4s infinite ease-in-out;
  animation: bouncedelay 1.4s infinite ease-in-out;
  /* Prevent first frame from flickering when animation starts */
  -webkit-animation-fill-mode: both;
  animation-fill-mode: both;
}
.spinner .bounce1 {
  -webkit-animation-delay: -0.32s;
  animation-delay: -0.32s;
}

.spinner .bounce2 {
  -webkit-animation-delay: -0.16s;
  animation-delay: -0.16s;
}

@-webkit-keyframes bouncedelay {
  0%,
  80%,
  100% {
    -webkit-transform: scale(0);
  }
  40% {
    -webkit-transform: scale(1);
  }
}

@keyframes bouncedelay {
  0%,
  80%,
  100% {
    transform: scale(0);
    -webkit-transform: scale(0);
  }
  40% {
    transform: scale(1);
    -webkit-transform: scale(1);
  }
}
</style>


