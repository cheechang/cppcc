<template>
  <div class="d-card" :class="[shadow ? 'is-' + shadow + '-shadow' : 'is-always-shadow']" :style="radiusStyle">
    <div class="d-card__header" v-if="$slots.header || header" :style="headerStyle">
      <slot name="header">{{ header }}</slot>
    </div>
    <div class="d-card__body" :style="bodyStyle">
      <slot></slot>
    </div>
  </div>
</template>

<script>
export default {
  name: 'd-card',
  props: {
    header: {},
    bodyStyle: {},
    headerStyle: {},
    radiusStyle: {},
    shadow: {
      type: String
    },
  }
};
</script>
