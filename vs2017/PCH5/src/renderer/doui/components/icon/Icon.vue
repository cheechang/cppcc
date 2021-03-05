<template>
    <i class="d-icon" :class="iconClass" :style="iconStyle" @click="handleClick">{{ iconText }}</i>
</template>
<script>
export default {
  name: 'd-icon',
  props: {
    pack: {
      type: String,
      default: 'iconfont',
    },
    icon: {
      type: String,
      default: '',
    },
    color: {
      type: String,
      default: '',
    },
    size: {
      type: [String, Number],
      validator(val) {
        if (['mini', 'small', 'medium', 'large', 'inherit'].includes(val) || /^[0-9]+$/.test(val)) {
          return true;
        }
        return false;
      }
    },
    type: {
      type: String,
      default: 'className'
    }
  },
  data() {
    return {};
  },
  computed: {
    iconStyle() {
      let style = {};
      // 绑定 自定义颜色样式
      style.color = this.color || '';
      // 绑定 自定义大小样式
      if (this.size && (/^[0-9]+$/.test(this.size))) {
        style['font-size'] = this.size + 'px';
      }
      return style;
    },
    iconClass() {
      let classList = [];
      // 绑定icon包
      classList.push(this.pack);
      // 绑定icon
      if (this.type !== 'text') {
        classList.push(this.icon);
      }
      // 判断是否绑定了 点击事件 处理 移入鼠标显示
      if (Object.prototype.hasOwnProperty.call(this.$listeners, 'click')) {
        classList.push('d-icon-click');
      }
      // 绑定 预设大小类名
      if (this.size && ['mini', 'small', 'medium', 'large', 'inherit'].includes(this.size)) {
        classList.push(`d-icon-size-${this.size}`);
      }
      return classList;
    },
    iconText() {
      return this.type === 'text' ? this.icon : '';
    }
  },
  methods: {
    handleClick(event) {
      this.$emit('click', event);
    }
  },
};

</script>
