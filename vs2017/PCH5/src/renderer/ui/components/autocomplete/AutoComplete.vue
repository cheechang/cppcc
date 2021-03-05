<template>
  <div class="autocomplete control" :class="{'is-expanded': expanded}">
    <v-input class="v-input" v-model="newValue" ref="input" :inputPadding="inputPadding" :inputLineSite="inputLineSite" :isAuth="isAuth" :size="size" :loading="loading" :rounded="rounded"
      :icon="icon" :icon-pack="iconPack" :maxlength="maxlength" autocomplete="off" v-bind="$attrs" @focus="focused" @blur="onBlur" @keyup.native.esc.prevent="isActive = false"
      @keydown.native.tab="tabPressed" @keydown.native.enter.prevent.stop="enterPressed" @keydown.native.up.prevent="keyArrows('up')" @keydown.native.down.prevent="keyArrows('down')" :placeholder="placeholder"/>
    <transition name="zoom-in-top">
      <div class="dropdown-menu" :class="{ 'is-opened-top': !isListInViewportVertically }" v-if="isActive" ref="dropdown">
        <div class="dropdown-content" :class="{ 'no-item': haveItem }">
          <div v-if="hasHeaderSlot" class="dropdown-item">
            <slot name="header"/>
          </div>
          <!-- 默认只显示文本,如果需要加载cardList组件，可以使用scope/slot-scope属性 -->
          <a v-show="isActive" v-for="(option, index) in computedOptions" :key="index" class="dropdown-item" :class="{ 'is-hovered': option === hovered }" @click="setSelected(option, true,index)" @keyup.enter='setSelected(option, true,index)'>
            <slot v-if="hasDefaultSlot" :option="option" :index="index"/>
            <span v-else v-html="getValue(option, true)"/>
          </a>
          <div  v-if="data.length === 0 && hasEmptySlot" class="dropdown-item is-disabled">
            <slot name="empty"/>
          </div>
        </div>
      </div>
    </transition>
  </div>
</template>

<script>
import FormElementMixin from "../../utils/FormElementMixin";
import Input from "../input/Input";

export default {
  name: "vAutoComplete",
  components: {
    [Input.name]: Input
  },
  mixins: [FormElementMixin],
  inheritAttrs: false,
  props: {
    isAuth: Boolean,
    inputLineSite: String,
    inputPadding: String,
    value: [Number, String],
    data: {
      type: Array,
      default: () => []
    },
    originArray: {
      type: Array,
      default: () => []
    },
    field: {
      type: String,
      default: "value"
    },
    keepFirst: Boolean,
    clearOnSelect: Boolean,
    openOnFocus: Boolean,
    rounded: {
      type: Boolean,
      default: false
    },
    menuCanShow: {
      type: Boolean,
      default: false
    },
    placeholder: String
  },
  data() {
    return {
      selected: null,
      hovered: null,
      isActive: false,
      newValue: this.value,
      isListInViewportVertically: true,
      hasFocus: false,
      _isAutocomplete: true,
      _elementRef: "input",
      isFirstFocus: false
    };
  },
  computed: {
    computedOptions() {
      if (this.isActive)
        if (!this.hasFocus||this.isFirstFocus) return this.originArray
      return this.data
    },
    /**
     * 点击input或dropdown时不去关闭下拉框
     */
    whiteList() {
      const whiteList = [];
      whiteList.push(this.$refs.input.$el.querySelector("input"));
      whiteList.push(this.$refs.dropdown);
      if (this.$refs.dropdown !== undefined) {
        const children = this.$refs.dropdown.querySelectorAll("*");
        for (const child of children) {
          whiteList.push(child);
        }
      }
      return whiteList;
    },
    hasDefaultSlot() {
      return !!this.$scopedSlots.default;
    },
    hasEmptySlot() {
      return !!this.$slots.empty;
    },
    hasHeaderSlot() {
      return !!this.$slots.header;
    },
    haveItem() {
      return !(this.computedOptions.length > 0) && !this.hasHeaderSlot && !(this.data.length === 0 && this.hasEmptySlot);
    }
  },
  watch: {
    /**
     * 控制下拉框显示或隐藏
     */
    isActive(active) {
      this.$emit("change", active);
      if (active) {
        this.calcDropdownInViewportVertical();
      } else {
        this.$nextTick(() => this.setHovered(null));
        setTimeout(() => {
          this.calcDropdownInViewportVertical();
        }, 100);
      }
    },
    newValue(value) {
      this.$emit("input", value);
      const currentValue = this.getValue(this.selected);
      if (currentValue && currentValue !== value) {
        this.setSelected(null, false);
      }
      if (this.hasFocus && (!this.openOnFocus || value)) {
      this.isFirstFocus = false;
        this.isActive = !!value;
      }
    },
    value(value) {
      this.newValue = value;
      !this.isValid && this.$refs.input.checkHtml5Validity();
    },
    /**
     * 默认选中第一个
     */
    data(value) {
      this.keepFirst && this.selectFirstOption(value);
    },
    /**
     * 自定义按钮实现下拉框显示和隐藏
     */
    menuCanShow(value) {
      this.$nextTick(() => {
        this.isActive = !value;
      });
    }
  },
  methods: {
    /**
     * 选中状态
     */
    setHovered(option) {
      if (option === undefined) return;
      this.hovered = option;
    },
    /**
     * 更新input内容并关闭下拉框
     */
    setSelected(option, closeDropdown = true, index=-1) {
      if(index!=-1) option = this.computedOptions[index]
      else if(option === undefined) return
      this.selected = option
      // if (option === undefined) return;
      // this.selected = option;
      this.$emit("select", {val:this.selected, index: this.computedOptions.indexOf(option)});
      // if (this.selected !== null) {
      //   this.newValue = this.clearOnSelect ? '' : this.getValue(this.selected)
      // }
      closeDropdown &&
        this.$nextTick(() => {
          this.isActive = false;
        });
    },
    /**
     * 默认选中第一个option
     */
    selectFirstOption(options) {
      this.$nextTick(() => {
        if (options.length) {
          if (
            this.openOnFocus ||
            (this.newValue !== "" && this.hovered !== options[0])
          ) {
            this.setHovered(options[0]);
          }
        } else {
          this.setHovered(null);
        }
      });
    },
    /**
     * 监听回车事件
     */
    enterPressed() {
      if (this.hovered === null) return;
      this.setSelected(this.hovered);
    },
    /**
     * 监听Tab键修改选中状态·
     */
    tabPressed() {
      if (this.hovered === null) {
        this.isActive = false;
        return;
      }
      this.setSelected(this.hovered);
    },
    /**
     * 点击input区域外则关闭下拉框
     */
    clickedOutside(event) {
      if (this.whiteList.indexOf(event.target) < 0) this.isActive = false;
    },
    escapeRegExpChars(value) {
      if (!value) return value;
      return value.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, "\\$&");
    },
    getValueByPath(obj, path) {
      const value = path.split(".").reduce((o, i) => o[i], obj);
      return value;
    },
    /**
     * 选中文本的样式
     */
    getValue(option, isHighlight = false) {
      if (!option) return;
      const value =
        typeof option === "object"
          ? this.getValueByPath(option, this.field)
          : option;
      const escapedValue =
        typeof this.newValue === "string"
          ? this.escapeRegExpChars(this.newValue)
          : this.newValue;
      const regex = new RegExp(`(${escapedValue})`, "gi");
      return isHighlight ? value.replace(regex, "<b>$1</b>") : value;
    },
    /**
     * 激活时下拉框状态
     */
    calcDropdownInViewportVertical() {
      this.$nextTick(() => {
        if (this.$refs.dropdown === undefined) return;
        const rect = this.$refs.dropdown.getBoundingClientRect();
        this.isListInViewportVertically =
          rect.top >= 0 &&
          rect.bottom <=
            (window.innerHeight || document.documentElement.clientHeight);
      });
    },
    /**
     * 上下键监听.
     */
    keyArrows(direction) {
      const sum = direction === "down" ? 1 : -1;
      if (this.isActive) {
        let data = this.isFirstFocus ? this.originArray : this.data;
        let index = data.indexOf(this.hovered) + sum;
        index = index > data.length - 1 ? data.length : index;
        index = index < 0 ? 0 : index;
        this.setHovered(data[index]);
        const list = this.$refs.dropdown.querySelector(".dropdown-content");
        const element = list.querySelectorAll(
          ".dropdown-item:not(.is-disabled)"
        )[index];
        if (!element) return;
        const visMin = list.scrollTop;
        const visMax =
          list.scrollTop + list.clientHeight - element.clientHeight;
        if (element.offsetTop < visMin) {
          list.scrollTop = element.offsetTop;
        } else if (element.offsetTop >= visMax) {
          list.scrollTop =
            element.offsetTop - list.clientHeight + element.clientHeight;
        }
      } else {
        this.isActive = true;
      }
    },

    /**
     * 获取焦点
     */
    focused(event) {
      this.isFirstFocus = true;
      if (this.isActive) this.isActive = false;
      if (this.getValue(this.selected) === this.newValue) {
        this.$el.querySelector("input").select();
      }
      if (this.openOnFocus) {
        this.isActive = true;
        if (this.keepFirst) {
          this.selectFirstOption(this.data);
        }
      }
      this.hasFocus = true;
      this.$emit("focus", event);
    },

    /**
     * 失去焦点
     */
    onBlur(event) {
      setTimeout(() => {
        if (this.isActive) this.isActive = false;
        this.hasFocus = false;
        this.isFirstFocus = false;
        this.$emit("blur", event);
      }, 200);
    }
  },
  created() {
    if (typeof window !== "undefined") {
      document.addEventListener("click", this.clickedOutside);
      window.addEventListener("resize", this.calcDropdownInViewportVertical);
    }
  },
  beforeDestroy() {
    if (typeof window !== "undefined") {
      document.removeEventListener("click", this.clickedOutside);
      window.removeEventListener("resize", this.calcDropdownInViewportVertical);
    }
  }
};
</script>

