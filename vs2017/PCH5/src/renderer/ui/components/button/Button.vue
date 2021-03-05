<template>
  <div class="button" :class="[buttonClass,type,size]"  @click="handleClick">
    <span class="button-label" :class="labelClass" v-if="label && labelPosition === 'before'">{{label}}</span>
    <icon v-if="icon"></icon>
    <slot></slot>
    <span class="button-label" :class="labelClass" v-if="label && labelPosition === 'after'">{{label}}</span>
  </div>
</template>

<script type="text/ecmascript-6">
/**
   * Created by lpy on 2017/10/25.
   */
export default {
  name: 'vButton',
  props: {
    type: {
      type: [String, Array, Object],
      default: ''
    },
    label: {
      type: String
    },
    labelPosition: {
      type: String,
      default: 'after'
    },
    labelClass: {
      type: [String, Array, Object],
      default: ''
    },
    icon: {
      type: Boolean,
      default: false
    },
    disable: {
      type: Boolean,
      default: false
    },
    ripple: {
      type: Boolean,
      default: true
    },
    size:String
  },
  computed: {
    buttonClass() {
      return {
        'label-before': this.labelPosition === 'before',
        'no-label': !this.label,
        'v-button-text': this.type === 'text',
        'v-button-disable': this.disable,
        'v-ripple': this.ripple
      };
    }
  },
  methods: {
    handleClick(e) {
      if (this.disable) return; 
      this.$emit('click', e);
    }
  }
};
</script>