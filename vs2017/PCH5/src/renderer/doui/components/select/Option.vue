<!-- add by hanxing 2019/9/5 -->
<template>
  <li 
    @mouseenter="hoverItem"
    :class="getClasses"
    @click.stop='selectOption'
    v-show="!hidden"
    >
    <slot>
      <span>{{ currentLabel }}</span>
    </slot>
  </li>
</template>

<script>
const prefixClass = 'd-option'
import Emitter from '../../mixins/emitter'

export default {
  name: 'd-option',
  mixins: [Emitter],
  props: {
    disabled: {
      type: Boolean,
      default: false
    },
    value: {
      type: String,
      required: true
    },
    label: String
  },
  data() {
    return {
      hidden: false,
      groupDisabled: false,
    };
  },
  inject: ['select'],
  computed: {
    getClasses() {
      return [
        `${prefixClass}`,
        {
          [`${prefixClass}-disabled`]: this.disabled || this.groupDisabled,
          [`${prefixClass}-selected`]: this.selected,
          [`${prefixClass}-hover`]: this.select.hoverIndex === this.select.options.indexOf(this),
        }
      ];
    },
    currentLabel() {
      return this.label || this.value;
    },
    selected() {
      return this.value === this.select.value;
    }
  },
  watch: {
  },
  created() {
    this.select.options.push(this); // 将本实例存入父组件数组中
    this.$on('handleGroupDisabled', this.handleGroupDisabled); // 触发optionGroup禁用状态
    this.$on('queryChange', this.queryChange);
    this.select.optionsCount++;
    this.select.filterOptionCount++;
  },
  beforeDestroy() {
    this.select.onOptionDestroy(this);
  },
  methods: {
    /**
     * 选中option将事件抛出
     */
    selectOption() {
      if (this.disabled !== true && this.groupDisabled !== true) {
        this.dispatch('d-select', 'handleOptionClick', [this, true]);
      }
    },
    /**
     * 显示搜索文字
     */
    queryChange(val) {
      if (val === '') {
        this.hidden = false;
        return;
      }
      const query = val.replace(/[|\\{}()[\]^$+*?.]/g, '\\$&');
      this.hidden = !new RegExp(query, 'i').test(this.currentLabel);
      if (this.hidden) {
        this.select.filterOptionCount--;
      }
    },
    /**
     * option组禁用
     */
    handleGroupDisabled(val) {
      this.groupDisabled = val;
    },
    hoverItem() {
      if (!this.disabled && !this.groupDisabled && this.select.visible) {
        this.select.hoverIndex = this.select.options.indexOf(this);
      }
    },
  }
}

</script>
