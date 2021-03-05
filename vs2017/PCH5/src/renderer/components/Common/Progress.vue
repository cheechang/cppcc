<template>
<div class="v-circle" v-bind:style="circleStyle">
  <div class="mask full" v-bind:style="[maskStyle, transitionStyle, rotateStyle]">
    <div class="fill" v-bind:style="[fillStyle, transitionStyle, rotateStyle]"></div>
  </div>
  <div class="mask half" v-bind:style="[maskStyle]">
    <div class="fill" v-bind:style="[fillStyle, transitionStyle, rotateStyle]"></div>
    <div class="fill fix" v-bind:style="[fillStyle, fixStyle, transitionStyle]"></div>
  </div>
  <div class="pv" v-bind:style="pvStyle" @click="$emit('click')">
    <!-- <span class="progress" v-bind:style="progressTextStyle">
      {{ pv || 0 }}
    </span> -->
    <i class="icon icon-progress" v-html="isPause?'&#xe671;':'&#xe670;'"></i>
  </div>
</div>
</template>

<style lang="scss" scoped>
  .v-circle {
    border-radius: $--border-radius-circle;
    position: relative;
    border-width: 1px !important;
    width: 21px !important;
    height: 21px !important;
    // border-color: #fff !important;

    .mask, .fill {
      position: absolute;
      border-radius: $--border-radius-circle;
      backface-visibility: hidden;
    }

    .pv {
      position: absolute;
      top: 0;
      left: 0;
      bottom: -1px;
      right: -1px;
      margin: auto;
      @include z-index(btn);
      border-radius: $--border-radius-circle;
      text-align: center;

      .progress {
        margin: 0;
        padding: 0;
        font-family: 'Impact';
      }
      
      .icon-progress {
        font-size: 19px;
        left: -3px;
        top: -2px;
        bottom: 0px;
        color: #000;
      }
    }

  }
</style>

<script>
const DEFAULT_WIDTH = 150
    , DEFAULT_BOLD = 5
    , DEFAULT_FONT_SIZE = 64
    , DEFAULT_BORDER_COLOR = '#bdc3c7'
    , DEFAULT_TEXT_COLOR = '#bdc3c7'
    , DEFAULT_FILL_COLOR = '#2ecc71'
    , DEFAUTL_BG_COLOR = '#f9f9f9'
    , DEFAUTL_TEXT_BG_COLOR = '#333333'

export default {
  methods: {
    setClip(t, r, b, l) {
      return `rect(${t}px, ${r}px, ${b}px, ${l}px)`
    },
    setTransformStyle(pv, type) {
      let deg = Math.floor((pv / 100) * 180)
      if(type === 'fix') {
        // remove the gap between two half circles
        return `rotate(${deg * 2}deg)`
      }
      return `rotate(${deg}deg)`
    },
    setTransitionStyle(t) {
      return `transform ${t}s`
    },
    setPv(value) {
      // this.pv = ~~(Math.random(0, 100) * 100)
      let types = ['fix', 'rotate']

      // map styles
      types.map((type) => {
        this[type + 'Style'] = {
          transform: this.setTransformStyle(value, type)
        }
      })
    }
  },
  watch: {
    pv(newVal, oldVal) {
      this.setPv(newVal);
    }
  },
  props: [
    'color',
    'width',
    'fontSize',
    'pv',
    'textColor',
    'bold',
    'textBgColor',
    'borderColor',
    'during',
    'bgColor',
    'isPause'
  ],

  data() {
    let transformStyleValue = this.setTransformStyle(this.pv)
      , innerCircleWidth = ((this.width || DEFAULT_WIDTH)
                           - 2 * (this.bold || DEFAULT_BOLD))
                           + 'px'

      , fixTransformStyleValue = this.setTransformStyle(this.pv, 'fix')
      , transitionStyleValue = this.setTransitionStyle(this.during || 0.8)

    return {
      // 环形样式
      circleStyle: {
        borderColor: (this.borderColor || DEFAULT_BORDER_COLOR),
        borderStyle: 'solid',
        borderWidth: DEFAULT_BOLD + 'px',
        width: (this.width || DEFAULT_WIDTH) + 'px',
        height: (this.width || DEFAULT_WIDTH) + 'px',
        backgroundColor: (this.bgColor || DEFAUTL_BG_COLOR)
      },

      // 进度文字样式
      progressTextStyle: {
        fontSize: (this.fontSize || DEFAULT_FONT_SIZE) + 'px',
        color: this.textColor || DEFAULT_TEXT_COLOR
      },

      fillStyle: {
        backgroundColor: this.color || DEFAULT_FILL_COLOR,
        width: (this.width || DEFAULT_WIDTH) + 'px',
        height: (this.width || DEFAULT_WIDTH) + 'px',
        clip: this.setClip(0, this.width / 2, this.width, 0)
      },

      rotateStyle: {
        transform: transformStyleValue,
        webkitTransform: transformStyleValue,
        msTransform: transformStyleValue,
        oTransform: transformStyleValue,
        mozTransform: transformStyleValue
      },

      transitionStyle: {
        transition: transitionStyleValue,
        webkitTransition: transitionStyleValue,
        mozTransition: transitionStyleValue,
        oTransition: transitionStyleValue,
        msTransition: transitionStyleValue
      },

      maskStyle: {
        width: (this.width || DEFAULT_WIDTH) + 'px',
        height: (this.width || DEFAULT_WIDTH) + 'px',
        clip: this.setClip(0, this.width, this.width, this.width / 2)
      },

      pvStyle: {
        backgroundColor: this.textBgColor || DEFAUTL_TEXT_BG_COLOR,
        width: innerCircleWidth,
        height: innerCircleWidth,
        lineHeight: innerCircleWidth
      },

      fixStyle: {
        transform: fixTransformStyleValue,
        webkitTransform: fixTransformStyleValue,
        mozTransform: fixTransformStyleValue,
        oTransform: fixTransformStyleValue,
        msTransform: fixTransformStyleValue
      }
    }
  }
}
</script>
