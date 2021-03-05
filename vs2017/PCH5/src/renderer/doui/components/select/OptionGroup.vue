<!-- add by hanxing 2019/9/5 -->
<template>
  <li class="d-option-group" v-show="hidden">
    <div 
      :class="[`${prefixClass}-title`]"
      @click.stop
      >{{ label }}</div>
    <ul>
      <slot></slot>
    </ul>
  </li>
</template>

<script>
const prefixClass = 'd-option-group'
import Emitter from '../../mixins/emitter'

export default {
  name: 'd-option-group',
  mixins: [ Emitter ],
  components: {},
  props: {
    label: {
      type: String,
      required: true
    },
    disabled: {
      type: Boolean,
      default: false
    }
  },
  data() {
    return {
      prefixClass: prefixClass,
      hidden: true
    };
  },
  watch: {
    /**
     * 动态更新禁用状态
     */
    disabled(val) {
      this.broadcast('d-option', 'handleGroupDisabled', val); 
    }
  },
  created() {
    this.$on('queryChange', this.queryChange);
  },
  mounted() {
    if (this.disabled) {
      this.broadcast('d-option', 'handleGroupDisabled', this.disabled); 
    }
  },
  methods: {
    queryChange() {
      this.hidden = !this.$children || !Array.isArray(this.$children) || this.$children.some(option => option.hidden === false);
    }
  }
}

</script>
<style lang='scss' scoped>
</style>
