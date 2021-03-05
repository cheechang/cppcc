<template>
<div class="d-input-wrapper" :class="inputClass">
  <div class="d-input-box" :class="[
    outlined ? 'd-input-outline' : 'd-input-single-line',
    {
      'd-input-is-focused': isfocus,
      'd-input-is-disabled': disabled,
      'is-exceed': inputExceed
    }
  ]"
  >
  <!-- 输入框前置插槽 begin -->
    <div class="prefix-slot" v-if="$slots.prepend">
      <slot name="prepend"></slot>
    </div>
  <!-- 输入框前置插槽 end -->
  <!-- 输入框前置Icon begin -->
    <div class="icon slot prefix-slot" v-if="$slots.prefix || prefixIcon">
      <slot name="prefix"></slot>
      <d-icon v-if="prefixIcon" :icon="prefixIcon" size="inherit"></d-icon>
    </div>
  <!-- 输入框前置Icon end -->
  <!-- 输入框 begin -->
    <input
      class="d-input"
      :class="getInputClasses"
      ref="input"
      :name="name"
      :type="getType"
      :value="currentValue"
      :placeholder="placeholder"
      :disabled="disabled"
      :autofocus="autofocus"
      :readonly="readonly"
      :maxlength="maxlength"
      @input="handleInput"
      @focus="handleFocus"
      @blur="handleBlur"
      @keyup.enter.stop="handleEnter"
    >
  <!-- 输入框 end -->
  <!-- 输入框后置Icon begin -->
    <div class="icon slot suffix-slot" v-if="$slots.suffix || suffixIcon">
      <slot name="suffix"></slot>
      <d-icon v-if="suffixIcon" :icon="suffixIcon" size="inherit"></d-icon>
    </div>
  <!-- 输入框后置Icon end -->
  <!-- 密码显示隐藏图标 begin -->
    <div class="icon password-icon" v-if="password && !passwordInvisible && value" @click.stop="handlePasswordVisible">
      <d-icon :icon="takePasswordVisible ? 'd-icon-invisible' : 'd-icon-eye'" @click.stop="handlePasswordVisible"  size="inherit"></d-icon>
    </div>
  <!-- 密码显示隐藏图标 end -->
  <!-- 清空图标 begin -->
    <div class="icon clear-icon" v-if="clearable && value" @click.stop="handleClear">
      <d-icon icon="d-icon-close-button" @click.stop="handleClear" size="inherit"></d-icon>
    </div>
  <!-- 清空图标 end -->
  <!-- 搜索图标 begin -->
    <div class="icon search-icon" v-if="search && value" @click.stop="handleSearch">
      <d-icon :icon="getLoadingState.icon" @click.stop="handleSearch" :class="{ 'loading': getLoadingState.state }" size="inherit"></d-icon>
    </div>
  <!-- 搜索图标 end -->
  <!-- 字符限制提示 begin -->
    <div class="count" v-if="isShowWordLimit">
      <span class="count-word">{{ currentLength }}/{{ maxlength }}</span>
    </div>
  <!-- 字符限制提示 end -->
  <!-- 输入框后置插槽 begin -->
    <div class="suffix-slot" v-if="$slots.append">
      <slot name="append"></slot>
    </div>
  <!-- 输入框后置插槽 end -->
  </div>
</div>
</template>

<script>
import DIcon from '../icon/Icon';

export default {
  name: 'd-input',
  components: {
    [DIcon.name]: DIcon
  },
  inheritAttrs: false,
  props: {
    name: String,
    value: [String, Number],
    // 边框模式
    outlined: {
      type: Boolean,
      default: false
    },
    // 提示文字
    placeholder: {
      type: String,
      default: ''
    },
    // 禁止输入
    disabled: {
      type: Boolean,
      default: false
    },
    // 大小
    size: {
      type: String,
      default: 'default',
      validator(val) {
        return val && ['small', 'default', 'medium', 'large'].includes(val);
      }
    },
    // 可清空
    clearable: {
      type: Boolean,
      default: false
    },
    // 自动聚焦
    autofocus: {
      type: Boolean,
      default: false
    },
    // 只读
    readonly: {
      type: Boolean,
      default: false
    },
    // 密码模式
    password: {
      type: Boolean,
      default: false
    },
    // 隐藏显示密码
    passwordInvisible: {
      type: Boolean,
      default: false
    },
    // 搜索模式
    search: {
      type: Boolean,
      default: false
    },
    // 前置Icon
    prefixIcon: {
      type: String,
      default: ''
    },
    // 后置Icon
    suffixIcon: {
      type: String,
      default: ''
    },
    // 显示长度限制提示
    showWordLimit: {
      type: Boolean,
      default: false
    },
    // 搜索完成
    finishSearch: {
      type: Boolean,
      default: true
    },
    // 限制最大长度
    maxlength: {
      type: String,
      validator(val) {
        return val && (Number(val) > 0);
      }
    }
  },
  data() {
    return {
      currentValue: this.value,
      isfocus: false,
      takePasswordVisible: false,
      loading: false
    };
  },
  computed: {
    inputClass() {
      let classList = [];
      // 绑定大小
      classList.push(`d-input-is-${this.size}`);
      return classList;
    },
    /**
     * 获取显示类型
     */
    getType() {
      if (this.password) {
        return this.takePasswordVisible ? 'text' : 'password';
      }
      return 'text';
    },
    /**
     * 是否显示文字长度提示
     */
    isShowWordLimit() {
      return (Number(this.maxlength) > 0) && this.showWordLimit;
    },
    /**
     * 当前长度
     */
    currentLength() {
      return this.value.length;
    },
    /**
     * 超出长度处理
     */
    inputExceed() {
      return this.showWordLimit && (this.currentLength > this.maxlength);
    },
    /**
     * 获取搜索状态
     */
    getLoadingState() {
      if (this.loading) {
        return { icon: 'd-icon-loading-round', state: true };
      }
      return { icon: 'd-icon-search', state: false };
    },
    /** 
     * 获取input类名
     */
    getInputClasses() {
      return [ 'd-input', 
        { 'no-right-padding': this.$slots.append || this.$slots.suffix || this.suffixIcon || this.search || (this.password && !this.passwordInvisible) || this.clearable,
        'no-left-padding': this.$slots.prepend || this.$slots.prefix || this.prefixIcon}
      ]
    }
  },
  watch: {
    value(val) {
      this.setCurrentValue(val);
    },
    finishSearch(val) {
      this.loading = !val;
    }
  },
  methods: {
    /**
     * 设置当前内容
     */
    setCurrentValue(val) {
      if (val === this.currentValue) {
        return;
      }
      this.currentValue = val;
    },
    /**
     * 聚焦事件
     */
    handleFocus(event) {
      this.isfocus = true;
      this.$emit('focus', event);
    },
    /**
     * 失焦事件
     */
    handleBlur(event) {
      this.isfocus = false;
      this.$emit('blur', event);
    },
    /**
     * 清空当前内容
     */
    handleClear() {
      this.setCurrentValue('');
      this.$emit('input', ''); // 触发外部input事件,清空内容
      this.$emit('change', ''); // 触发外部change事件
      this.$emit('clear'); // 触发外部清空事件(自定义)
    },
    /**
     * 输入事件
     */
    handleInput(event) {
      let val = event.target.value;
      this.setCurrentValue(val);
      this.$emit('input', val); // c触发外部事件更新双向绑定数值
      this.$emit('change', val);
    },
    /**
     * 密码框显示
     */
    handlePasswordVisible() {
      this.takePasswordVisible = !this.takePasswordVisible;
    },
    /**
     * 搜索事件
     */
    handleSearch() {
      if (this.loading) {
        return;
      }
      this.loading = true;
      this.$emit('search', this.currentValue);
    },
    /**
     * 回车事件
     */
    handleEnter(event) {
      this.$emit('enter', event);
      if (this.search) {
        this.$emit('search', this.currentValue);
      }
    },
    /**
     * 外部聚焦事件
     */
    focus() {
      this.isfocus = true;
      this.$nextTick(() => {
        this.$refs.input.focus();  
      })
    },
    /**
     * 外部失焦事件
     */
    blur() {
      this.isfocus = false;
      this.$refs.input.blur();  
    }
  },
};

</script>
