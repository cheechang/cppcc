<!-- add by hanxing 2019/9/4 -->
<template>
  <div 
    :class="[prefixCls, size ? `${prefixCls}-${size}` : '']"
    @click.stop="toggleList"
    v-clickoutside="handleClose"
    @keydown.down.prevent="navigateOptions('next')"
    @keydown.up.prevent="navigateOptions('prev')"
    @keydown.enter.prevent="selectOption"
    >
    <d-input
    v-model="selectedValue"
    readonly
    :placeholder="placeholder"
    :disabled="disabled"
    :size="size"
    outlined
    ref="trigger"
    :prefix-icon="prefixIcon"
    >
      <slot name="prefix" slot="prefix"></slot>
      <d-icon slot="suffix" :class="expandClasses" icon="d-icon-caret-bottom" size="inherit"></d-icon>
    </d-input>
    <transition name="dou-zoom-in-top">
      <d-select-dropdown v-show="visible" ref="popover" :filterable="filterable">
        <div :class="[`${prefixCls}-filterable`]" v-if="filterable" slot="filterable">
          <!-- 阻止input点击事件,防止冒泡 -->
          <d-input 
            @click.native.stop 
            :placeholder="filterPlaceholder" 
            :size="size"
            v-model="filterValue"
            ref="filter"
            @input="filterData"
            ></d-input>
        </div>
        <template v-if="filterable && filterOptionCount <= 0" slot="empty">
          <slot name="empty" v-if="$slots.empty"></slot>
          <p :class="[`${prefixCls}-no-data`]" v-else>{{ noDataText }}</p>
        </template>
        <ul :class="[`${prefixCls}-dropdown-list`]">
          <slot></slot>
        </ul>
      </d-select-dropdown>
    </transition>
  </div>
</template>

<script>
const prefixCls = 'd-select';
import Emitter from '../../mixins/emitter'
import DInput from '../input'
import DIcon from '../icon';
import Clickoutside from '../../utils/clickoutside';
import DSelectDropdown from './SelectDropdown';
import DOption from './Option';
import { filter } from 'minimatch';

export default {
  name: 'd-select',
  mixins: [ Emitter ],
  directives: { Clickoutside },
  components: {
    [DInput.name]: DInput,
    [DIcon.name]: DIcon,
    [DSelectDropdown.name]: DSelectDropdown,
    [DOption.name]: DOption,
  },
  props: {
    value: String,
    // 大小
    size: {
      type: String,
      default: 'default',
      validator(val) {
        return ['default', 'small', 'medium', 'large'].includes(val);
      }
    },
    // 禁用
    disabled: {
      type: Boolean,
      default: false
    },
    // 提示文字
    placeholder: String,
    // 搜索栏提示文字
    filterPlaceholder: String,
    // 选项为空时显示的文字;后期国际化顾不赋默认值
    noDataText: {
      type: String,
      default: '无数据'
    },
    // 是否可搜索
    filterable: Boolean,
    // 搜索过滤函数
    filterMethod: Function,
    // 远程搜索模式
    remote: {
      type: Boolean,
      default: false
    },
    // 远程搜索函数
    remoteMethod: Function,
    // 是否正在搜索
    loading: {
      type: Boolean,
      default: false
    },
    // 远程加载时显示的文字;后期国际化顾不赋默认值
    loadingText: {
      type: String,
      default: '加载中'
    },
    // 头部Icon插槽
    prefixIcon: String
  },
  data() {
    return {
      prefixCls: prefixCls,
      selectedValue: '',
      selected: {},
      focusIndex: -1,
      isFocus: false,
      visible: false,
      options: [],
      optionsCount: 0,
      filterOptionCount: 0,
      position: {
        top: 0,
        left: 0
      },
      filterValue: '',
      hoverIndex: -1
    }
  },
  provide() {
    return {
      'select': this
    }
  },
  computed: {
    // 是否只读
    readonly() {
      return !this.filterable;
    },
    // 展开图标样式
    expandClasses() {
      return [
        `${prefixCls}-expand`,
        {
          [`${prefixCls}-is-expand`]: this.visible
        }
      ];
    },
    optionsAllDisabled() {
      return this.options.filter(option => !option.hidden).every(option => option.disabled);
    },
    optionGroupAllDisabled() {
      return this.options.filter(option => !option.hidden).every(option => option.groupDisabled);
    }
  },
  watch:{
    value(val, oldVal){
      if (val !== oldVal) {
        this.setSelected();
      }
      this.handleClose();
    },
    visible(val) {
      if (val) {
        this.setPopoverPosition();
        let filters = this.$refs.filter;
        if (this.filterable && filters) {
          filters.focus();
          this.filterValue = '';
        }
      } else {
        this.isFocus = val;
      }
    },
    filterValue(val) {
      if (val === '') {
        this.filterData(val);
      }
    }
  },
  created() {
    this.$on('handleOptionClick', this.handleOptionClick);
  },
  methods: {
    toggleList() {
      if (this.disabled) {
        return;
      }
      this.visible = !this.visible;
    },
    handleClose(e) {
      if (!this.visible) {
        return;
      }
      this.visible = false;
    },
    /**
     * 设置下拉框定位
     */
    setPopoverPosition() {
      this.$nextTick(() => {
        const popover = this.$refs.popover.$el;
        const trigger = this.$refs.trigger.$el;
        const lists = this.$refs.popover.$el.querySelector(`.${prefixCls}-lists`);
        this.position.left = trigger.offsetLeft - (popover.offsetWidth / 2) + (trigger.offsetWidth / 2);
        this.position.top = trigger.offsetTop + trigger.offsetHeight;
        popover.style.top = `${this.position.top + 5}px`;
        popover.style.left = `${this.position.left}px`;
        // lists.scrollTop = 0; // 列表滚动条置顶
        if (this.hoverIndex !== -1 && this.options[this.hoverIndex]) {
          this.scrollToOption(this.options[this.hoverIndex]);
        }
      })
    },
    /**
     * option点击事件
     */
    handleOptionClick(option) {
      this.$emit('input', option.value); // 抛出input事件修改v-model值
      this.emitChange(option.value); // 判断是否触发change事件
      this.visible = false;
    },
    /**
     * 触发change事件
     */
    emitChange(val) {
      // 当选定值与当前值不同时触发
      if (this.value !== val) {
        this.$emit('change', val, this.selected);
      }
    },
    /**
     * 设置选中项
     */
    setSelected() {
      let option = this.getOption(this.value);
      this.selectedValue = option.currentLabel;
      this.selected = option;

    },
    /**
     * 获取选项信息
     */
    getOption(value) {
      let newOption = {
        value: '',
        currentLabel: ''
      }
      for (let i = this.options.length - 1; i >= 0; i--) {
        if (this.options[i].value === value) {
          newOption.value = value;
          newOption.currentLabel = this.options[i].label || value;
          return newOption;
        }
      }
    },
    /**
     * 处理上下键
     */
    navigateOptions(direction) {
      if (!this.visible) {
        this.visible = true;
        return;
      }
      if (this.options.length === 0) {
        return;
      }
      if (!this.optionsAllDisabled && !this.optionGroupAllDisabled) {
        if (direction === 'next') {
          this.hoverIndex++;
          if (this.hoverIndex === this.options.length) {
            this.hoverIndex = 0;
          }
        } else if (direction === 'prev') {
          this.hoverIndex--;
          if (this.hoverIndex < 0) {
            this.hoverIndex = this.options.length - 1;
          }
        }
        const option = this.options[this.hoverIndex];
        if (option.disabled === true || option.groupDisabled === true || option.hidden === true) {
          this.navigateOptions(direction);
        }
        this.$nextTick(() => this.scrollToOption(option));
      }
    },
    /**
     * 上下键滚动条
     */
    scrollToOption(option) {
      const optionHeight = option.$el.offsetHeight; // option高度
      const optionTop = option.$el.offsetTop; // option距离顶部高度
      const dropdown = this.$refs.popover.$el.querySelector('.d-select-lists'); // 下拉高度
      const optionGroup = this.$refs.popover.$el.querySelector('.d-option-group-title'); // option组
      if (optionTop === 0) {
        dropdown.scrollTop = 0;
        return;
      }
      if (optionGroup && optionTop === (optionGroup.offsetHeight + 5)) {
        dropdown.scrollTop = 0;
        return;
      }
      if (optionHeight + optionTop > dropdown.offsetHeight) {
        dropdown.scrollTop = optionHeight + optionTop - dropdown.offsetHeight;
      }
    },
    /**
     * 回车键选中option
     */
    selectOption() {
      if (this.options[this.hoverIndex]) {
        this.handleOptionClick(this.options[this.hoverIndex]);
      }  
    },
    /**
     * 本地搜索
     */
    filterData(val) {
      if (typeof this.filterMethod === 'function') {
        this.filterMethod(val);
      } else {
        this.filterOptionCount = this.optionsCount;
        this.broadcast('d-option', 'queryChange', val);
        this.broadcast('d-option-group', 'queryChange');
      }
    },
    /**
     * 销毁option实例
     */
    onOptionDestroy(object) {
      let optionIndex = this.options.indexOf(object);
      if (optionIndex > -1) {
        this.optionsCount--;
        this.filterOptionCount--;
        this.options.splice(optionIndex, 1);
      }
    },
  }
};

</script>
