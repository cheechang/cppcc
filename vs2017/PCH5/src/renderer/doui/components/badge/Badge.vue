<!-- add by hanxing 2019/8/30 -->
<template>
  <div class="d-badge-box">
    <slot></slot>
    <transition name="d-zoom-in">
      <sup
      v-show="content || content === 0 || dot"
      v-text="content"
      :class="getClass"
      :style="getStyle"
      ></sup>
    </transition>
  </div>
</template>

<script>
const prefixCls = 'd-badge';

export default {
  name: 'd-badge',
  props: {
    // 圆点模式
    dot: {
      type: Boolean,
      default: false
    },
    // 计数模式
    count: {
      type: [String, Number],
      validator(val) {
        return !Number.isNaN(Number(val));
      }
    },
    // 计数最大值
    max: {
      type: [String, Number],
      default: 99,
      validator(val) {
        return !Number.isNaN(Number(val));
      }
    },
    // 文本
    text: {
      type: String,
      default: ''
    },
    // 类型
    type: {
      type: String,
      default: 'normal',
      validator(val) {
        return ['primary', 'success', 'normal', 'info', 'danger', 'warning'].includes(val);
      }
    },
    // 偏移量
    offset: {
      type: Array,
      validator(val) {
        if (val.length > 0) {
          for (let i = 0, len = val.length; i < len; i += 1) {
            if (Number.isNaN(Number(val[i]))) {
              return false;
            }
          }
          return true;
        }
        return false;
      }
    }
  },
  computed: {
    content() {
      if (this.dot) {
        return '';
      }
      if (this.text.trim().length > 0) {
        return this.text.trim();
      }
      if (this.count) {
        const count = parseInt(this.count, 10);
        const max = parseInt(this.max, 10);
        return count > max ? `${max}+` : count;
      }
      return '';
    },
    getStyle() {
      const style = {};
      if (this.offset && this.offset.length > 0) {
        style['margin-right'] = `${-this.offset[0]}px`;
        style['margin-top'] = this.offset.length === 1 ? `${-this.offset[0]}px` : `${-this.offset[1]}px`;
      }
      return style;
    },
    getClass() {
      return [
        `${prefixCls}`,
        `${prefixCls}-${this.type}`,
        {
          [`${prefixCls}-dot`]: this.dot,
          [`${prefixCls}-content`]: !this.dot
        }
      ];
    }
  }
};

</script>
