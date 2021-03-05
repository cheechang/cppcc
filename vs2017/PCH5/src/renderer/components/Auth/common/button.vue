<template>
  <div class="button v-button" :class="[buttonClass,type,size,{'v-button--cancle': isCancel}]"  @click="handleClick">
    <span class="button-label" :class="labelClass" v-if="label && labelPosition === 'before'">{{label}}</span>
    <icon v-if="icon"></icon>
    <slot></slot>
    <span class="button-label" :class="labelClass" v-if="label && labelPosition === 'after'">{{label}}</span>
  </div>
</template>

<script>
/**
 * Created by lpy on 2017/10/25.
 */
export default {
  name: 'vBtn',
  props: {
    isCancel: Boolean,
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
    size:String
  },
  computed: {
    buttonClass() {
      return {
        'label-before': this.labelPosition === 'before',
        'no-label': !this.label,
        'v-button-text': this.type === 'text',
        'v-button-disable': this.disable
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
<style lang="scss" scoped>
*{
  transition: all .2s;
}
@import './_button.scss';
</style>
