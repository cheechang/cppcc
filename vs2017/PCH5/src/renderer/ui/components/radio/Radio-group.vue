<template>
  <div class="radio-group" v-if="$slots.default">
    <slot></slot>
  </div>
</template>
<script>
export default {
  name: 'vRadioGroup',
  props: {
    value: Array | String
  },
  watch: {
    value(value) {
      console.log('change', value);
    }
  }
};
</script>


