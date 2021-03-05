<template>
  <div
    class="control"
    :class="[iconPosition, {
        'is-expanded': expanded,
        'is-loading': loading,
        'is-clearfix': !hasMessage
       }]"
  >
    <label
      class="input-label"
      :class="{'label-is-focused':value||hasFocus == 1}"
      v-if="hasLabel"
    >{{label}}</label>
    <div
      class="input-line"
      :class="{'line-is-focused': hasFocus==1, 'line-is-blur': hasFocus==0}"
      v-if="hasLine"
      :style="{bottom: authInputLineSite}"
    ></div>
    <slot v-if="isAuth" name="auth"></slot>
    <div v-if="open&&test"></div>
    <div v-show="selectPwdShow&&CapsLockTip" class="promptCapsLock">{{$t('setting.capsOpen')}}</div>
    <input
      v-if="type !== 'textarea'"
      ref="input"
      class="input auth-font loginPasswd"
      :style="{border: isAuth ? 'none !important': '', paddingLeft: inputPadding}"
      :class="[statusType, size, customType, mobileType]"
      :type="newType"
      :autocomplete="newAutocomplete"
      :maxlength="maxlength"
      :value="newValue"
      :disabled="disable"
      v-bind="$props"
      :placeholder="placeholder"
      @keyup.down="onDown"
      @keyup.up="onUp"
      @keydown="onKeyDown"
      @input="onInput"
      @blur="onBlur"
      @focus="onFocus"
      @keyup.esc="onEsc"
      @keyup.enter="onEnter"
      @keypress="onPress"
      @keyup.20="onCapsLock"
    />
    <textarea
      v-else
      class="textarea"
      :class="[statusType, size]"
      ref="textarea"
      :name="name"
      :placeholder="placeholder"
      :disabled="disabled"
      :readonly="readonly"
      :required="required"
      :maxlength="maxlength"
      :minlength="minlength"
      :rows="rows"
      :value="newValue"
      @input="onInput"
      @blur="onBlur"
      @focus="onFocus"
    ></textarea>
    <span class="icon is-clickable" :class="[iconClass]" v-if="$slots.expand">
      <slot name="expand"></slot>
    </span>
  </div>
</template>

<script type="text/ecmascript-6">
/**
 * Created by lpy on 2017/10/24.
 */
import config from "../../utils/config";
import { isWindows, isOSX, isWinXp } from "../../../../comm/is";
import FormElementMixin from "../../utils/FormElementMixin";
import { truncate, truncateSync } from "fs";

export default {
  name: "vInput",
  inheritAttrs: false,
  mixins: [FormElementMixin],
  props: {
    selectPwdShow: "",
    open: false,
    inputLineSite: String,
    inputPadding: String,
    isAuth: {
      type: Boolean,
      default: false
    },
    value: [Number, String],
    type: {
      type: String,
      default: "text"
    },
    iconClass: {
      type: String,
      default: "is-right",
      validator: value => {
        return ["is-left", "is-right"].indexOf(value) > -1;
      }
    },
    position: {
      type: String,
      default: "right"
    },
    passwordReveal: Boolean,
    hasCounter: {
      type: Boolean,
      default: true
    },
    customType: String,
    isBorder: {
      type: Boolean,
      default: true
    },
    disable: {
      type: Boolean,
      default: false
    },
    isAutoFocus: {
      type: Boolean,
      default: false
    },
    label: String,
    hasLabel: {
      type: Boolean,
      default: false
    },
    hasLine: {
      type: Boolean,
      default: false
    },
    placeholder: String
  },
  mounted() {
    if (this.isAutoFocus)
      this.$nextTick(() => {
        this.$refs.input.focus();
      });
  },
  data() {
    return {
      CapsLockTip: false,
      hasFocus: -1,
      newValue: this.value,
      newType: this.type,
      newAutocomplete: this.autocomplete || config.defaultInputAutocomplete,
      isPasswordVisible: false,
      _elementRef: this.type === "textarea" ? "textarea" : "input"
    };
  },
  computed: {
    hasIconRight() {
      return this.passwordReveal || this.loading || this.statusType;
    },
    iconPosition() {
      return this.position === "left" ? "has-icons-left" : "has-icons-right";
    },
    statusTypeIcon() {
      switch (this.statusType) {
        case "is-success":
          return "done";
        case "is-danger":
          return "error";
        case "is-info":
          return "info";
        case "is-warning":
          return "warning";
      }
    },
    hasMessage() {
      return this.$parent.$data._isField && this.$parent.newMessage;
    },
    passwordVisibleIcon() {
      return !this.isPasswordVisible ? "visibility" : "visibility_off";
    },
    valueLength() {
      return this.newValue ? this.newValue.length : 0;
    },
    mobileType() {
      return this.isBorder ? "" : "input-border";
    },
    authInputLineSite() {
      return this.isAuth ? this.inputLineSite : "";
    }
  },
  watch: {
    /**
     * When v-model is changed:
     *   1. Set internal value.
     *   2. If it's invalid, validate again.
     */
    value(value) {
      this.newValue = value;
    },
    type() {
      this.newType = this.type;
    },
    /**
     * Update user's v-model and validate again whenever
     * internal value is changed.
     */
    newValue(value) {
      this.$emit("input", value);
      !this.isValid && this.checkHtml5Validity();
    }
  },
  methods: {
    togglePasswordVisibility() {
      console.log("in icon click");
      this.isPasswordVisible = !this.isPasswordVisible;
      this.newType = this.isPasswordVisible ? "text" : "password";
      this.$nextTick(() => {
        this.$refs.input.focus();
      });
    },
    onIconClick() {
      this.$emit("onIconClick");
    },
    onBlur(event) {
      this.CapsLockTip = false;
      this.hasFocus = 0;
      this.$emit("blur", event);
    },
    onFocus(event) {
      this.hasFocus = 1;
      this.$emit("focus", event);
      if (this.selectPwdShow) {
        this.CapsLockTip = this.$Service.config.getCapsLockStatus();
        console.log("调用了大小写检测接口");
      }
    },
    onInput(event) {
      this.$nextTick(() => {
        this.newValue = event.target.value;
      });
    },
    onEnter() {
      this.$emit("keyup-enter");
      console.log("回车事件触发");
    },
    onDown() {
      this.$emit("keyup-down");
    },
    onUp() {
      this.$emit("keyup-up");
    },
    onEsc() {
      this.$emit("keyup-esc");
    },
    onKeyDown(e) {
      this.$emit("keydown", e);
    },
    onCapsLock(e) {
      if (isWindows) {
        if (e.keyCode === 20 && this.selectPwdShow) {
          console.log(
            "是否开启了大写：",
            this.$Service.config.getCapsLockStatus()
          );
          this.CapsLockTip = this.$Service.config.getCapsLockStatus();
        }
      } else {
        if (e.keyCode === 20 && this.CapsLockTip) {
          this.CapsLockTip = false;
        }
      }
    },
    onPress(e) {
      if (!this.selectPwdShow) {
        return;
      }
      let keyCode = e.keyCode || e.which;
      let isShift = e.shiftKey || keyCode == 16 || false;
      if (
        (keyCode >= 65 && keyCode <= 90 && !isShift) ||
        (keyCode >= 97 && keyCode <= 122 && isShift)
      ) {
        this.CapsLockTip = true;
        console.log("键盘开启了大写", "CapsLockTip=true");
      }
    }
  }
};
</script>
<style lang="scss" scoped>
.promptCapsLock {
  color: #fa6;
  padding: 5px 3px;
  width: 95px;
  border: 1px solid #aec8d4;
  font-size: 12px;
  border-radius: 5px;
  position: absolute;
  top: 35px;
  left: 0px;
  background: #fff;
  z-index: 60;

  &:before {
    content: "";
    height: 0px;
    width: 0px;
    border: 10px solid #aec8d4;
    position: absolute;
    top: -20px;
    left: 10px;
    border-top-color: transparent;
    border-left-color: transparent;
    border-right-color: transparent;
  }

  &:after {
    content: "";
    height: 0px;
    width: 0px;
    border: 10px solid #fff;
    position: absolute;
    top: -19px;
    left: 10px;
    border-top-color: transparent;
    border-left-color: transparent;
    border-right-color: transparent;
  }
}
</style>




