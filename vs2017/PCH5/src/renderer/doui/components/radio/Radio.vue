<template>
  <label
    class="d-radio radio"
    ref="label"
    :class="[{ 'd-disabled': disabled },`d-radio-${type}`]"
    :disabled="disabled"
    @click="focus"
    @keydown.prevent.enter="$refs.label.click()"
    @keydown.space.stop.prevent="$refs.label.click()"
    >
      <div class="d-check_ripple" v-if="ripple">
        <d-ripple ></d-ripple>
      </div>
    <input
      v-model="computedValue"
      type="radio"
      ref="input"
      @click.stop
      :disabled="disabled"
      :name="name"
      :value="nativeValue"
    >
    <span class="check" :class="[`d-radio-size-${size}`]"></span>
    <span class="control-label" :class="[`d-radio-fontSize-${size}`]"><slot/></span>
  </label>
</template>
<script>
import DRipple from '../ripple/Ripple.vue';

export default {
  name: 'd-radio',
  components: {
    [DRipple.name]: DRipple
  },
  props: {
    value: [String, Number, Boolean, Function, Object, Array],
    nativeValue: [String, Number, Boolean, Function, Object, Array],
    type: {
      type: String,
      default: 'primary',
      validator(val) {
        return ['primary', 'success', 'warning', 'danger', 'info'].includes(val);
      }
    },
    disabled: Boolean,
    name: String,
    size: {
      type: String,
      default: 'small',
      validator(val) {
        return ['medium', 'mini', 'small'].includes(val);
      }
    },
    ripple: {
      type: Boolean,
      default: false
    }
  },
  data() {
    return {
      newValue: this.value
    };
  },
  computed: {
    computedValue: {
      get() {
        return this.newValue;
      },
      set(value) {
        this.newValue = value;
        this.$emit('input', value);
      }
    }
  },
  watch: {
    /**
     * 当 v-model 改变时 设置内部的value
     */
    value(value) {
      this.newValue = value;
    }
  },
  methods: {
    focus() {
      // MacOS FireFox and Safari do not focus when clicked
      this.$refs.input.focus();
    }
  }
};
</script>
