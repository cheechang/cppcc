<template>
  <span 
      :data-label="lable"
      :class="[newType, position, size, {
          'tooltip': active,
          'is-square': square,
          'is-animated': newAnimated,
          'is-always': always,
          'is-multiline': multilined,
          'is-dashed': dashed
      }]">
      <slot></slot>
  </span>
</template>

<script>
export default {
  name: 'vTooltip',
  props: {
    active: {
      type: Boolean,
      default: true
    },
    type: String,
    lable: String,
    position: {
      type: String,
      default: 'is-top',
      validator(value) {
        return (
          ['is-top', 'is-bottom', 'is-left', 'is-right'].indexOf(value) > -1
        );
      }
    },
    always: Boolean,
    animated: Boolean,
    square: Boolean,
    dashed: Boolean,
    multilined: Boolean,
    size: {
      type: String,
      default: 'is-medium'
    }
  },
  data() {
    return {
      newType: this.type || 'is-primary',
      newAnimated: this.animated || false
    };
  }
};
</script>
