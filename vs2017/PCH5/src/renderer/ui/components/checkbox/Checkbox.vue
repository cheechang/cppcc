<template>
  <div class="v-checkbox">
    <label class="v-checkbox-label">
      <span
        class="v-checkbox-inner "
        :class="{
          'is-checked': newValue,
          'is-indeterminate': indeterminate,
          'is-disabled': disabled
        }"
      >
      </span>
      <input type="checkbox" v-model="newValue" :disabled="disabled" @change="handleChange">{{label}}
      <slot></slot>
    </label>
  </div>
</template>
<script>
export default {
  name: 'vCheckbox',
  props: {
    name: String,
    label: String | Number,
    value: {},
    size: String,
    indeterminate: Boolean,
    disabled: Boolean,
    checked: Boolean
  },
  data() {
    return {
      newValue: this.value
    };
  },
  watch: {
    value(value) {
      // console.log('in watch value:::', value);
      this.newValue = value;
    },

    newValue(value) {
      this.$emit('input', value);
    }
  },
  methods: {
    handleChange(event) {
      this.$emit('change', event.target.checked);
      this.$emit('checked', event.target.checked ? 1 : 0);
    }
  }
};
</script>

