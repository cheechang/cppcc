<template>
  <label
    class="d-checkbox checkbox"
    :class="[size, { 'is-disabled': disabled }]"
    ref="label"
    :disabled="disabled"
    @click="focus"
    @keydown.prevent.enter="$refs.label.click()"
  >
    <div class="d-check_ripple" v-if="ripple">
      <d-ripple></d-ripple>
    </div>
    <input
      v-model="computedValue"
      type="checkbox"
      ref="input"
      @click.stop
      :disabled="disabled"
      :required="required"
      :name="name"
      :value="nativeValue"
      :true-value="trueValue"
      :false-value="falseValue"
    />
    <span class="check" :class="[`is-${size}`,`d-checkbox-${type}`]"/>
    <span class="control-label">
      <slot />
    </span>
  </label>
</template>

<script>
import DRipple from '../ripple/Ripple.vue';

export default {
  name: 'd-checkbox',
  components: {
    [DRipple.name]: DRipple,
  },
  props: {
    value: [String, Number, Boolean, Function, Object, Array],
    nativeValue: [String, Number, Boolean, Function, Object, Array],
    type: {
      type: String,
      default: 'primary',
      validator(val) {
        return ['danger', 'warning', 'info', 'success', 'primary'].includes(val);
      }
    },
    ripple: {
      type: Boolean,
      default: false
    },
    disabled: Boolean,
    required: Boolean,
    name: String,
    size: {
      type: String,
      validator(val) {
        return ['small', 'medium', 'large'].includes(val);
      }
    },
    trueValue: {
      type: [String, Number, Boolean, Function, Object, Array],
      default: true
    },
    falseValue: {
      type: [String, Number, Boolean, Function, Object, Array],
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
     * When v-model change, set internal value.
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
