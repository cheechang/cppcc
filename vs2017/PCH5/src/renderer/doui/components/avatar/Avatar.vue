<!-- add by hanxing 2019/8/28 -->
<template>
  <span :class="getAvatarClasses" :style="getAvatarStyle" ref="avatar">
    <img v-if="src" :src="src" @error="handleError" :style="getImgStyle" draggable="false">
    <d-icon v-else-if="icon && !$slots.icon" :icon="icon" size="inherit"></d-icon>
    <slot v-else-if="$slots.icon" name="icon"></slot>
    <span v-else ref="text" :style="getTextStyle" class="d-avatar-text"><slot></slot></span>
    <d-ripple v-if="ripple"></d-ripple>
  </span>
</template>

<script>
import DIcon from '../icon/Icon';
import DRipple from '../ripple/Ripple';

const prefixCls = 'd-avatar';

export default {
  name: 'd-avatar',
  components: {
    [DIcon.name]: DIcon,
    [DRipple.name]: DRipple
  },
  inheritAttrs: false,
  props: {
    // 形状
    shape: {
      type: String,
      default: 'circle',
      validator(val) {
        return ['circle', 'square'].includes(val);
      }
    },
    // 大小
    size: {
      type: [String, Number],
      default: 'default',
      validator(val) {
        return ['small', 'large', 'default'].includes(val) || /^[0-9]+$/.test(val);
      }
    },
    // 图片路径
    src: String,
    // Icon
    icon: String,
    // 背景颜色
    bgColor: String,
    // 字体颜色
    color: String,
    // 图片适应
    fit: {
      type: String,
      default: 'cover',
      validator(val) {
        return ['fill', 'contain', 'cover', 'none', 'scale-down'].includes(val);
      }
    },
    // 水波纹
    ripple: {
      type: Boolean,
      default: false
    }
  },
  data() {
    return {
      scale: 1,
      textWidth: 0
    };
  },
  computed: {
    getAvatarClasses() {
      let hasCorrectSize = ['small', 'large', 'default'].includes(this.size);
      return [
        `${prefixCls}`,
        `${prefixCls}-${this.shape}`,
        {
          [`${prefixCls}-size-${this.size}`]: hasCorrectSize,
          [`${prefixCls}-image`]: !!this.src,
          [`${prefixCls}-icon`]: !!this.icon || !!this.$slots.icon
        }
      ];
    },
    getAvatarStyle() {
      let styleArray = [];
      if (this.size && /^[0-9]+$/.test(this.size)) {
        styleArray.push({
          width: `${this.size}px`,
          height: `${this.size}px`,
          'line-height': `${this.size}px`
        });
      }
      styleArray.push({
        'background-color': (!this.src && this.bgColor) && this.bgColor,
        color: (!this.src && this.color) && this.color
      });
      return styleArray;
    },
    getImgStyle() {
      return { 'object-fit': this.fit };
    },
    getTextStyle() {
      let style = {};
      if (!this.src && !this.icon) {
        style = {
          transform: `scale(${this.scale})`,
          left: `calc(50% - ${Math.round(this.textWidth / 2)}px)`
        };
      }
      return style;
    }
  },
  watch: {},
  mounted() {
    this.setScale();
  },
  updated() {
    this.setScale();
  },
  methods: {
    handleError() {
      this.$emit('error');
    },
    setScale() {
      if (!this.src && !this.icon && this.$refs.text) {
        this.textWidth = this.$refs.text.offsetWidth;
        const avatarWidth = this.$refs.avatar.getBoundingClientRect().width;
        if (avatarWidth - 8 < this.textWidth) {
          this.scale = (avatarWidth - 8) / this.textWidth;
        } else {
          this.scale = 1;
        }
      }
    }
  }
};

</script>
<style lang='scss' scoped>
</style>
