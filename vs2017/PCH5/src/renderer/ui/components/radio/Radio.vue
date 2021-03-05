<template>
  <div class="container">
    <label class="radio">
       <!-- :style="value==lable? activeStyle : null" -->
      <span class="radio_inner" :class="{'theme-button':value==lable, 'theme-border':value==lable}"></span>
      <input type="radio" :disabled="disabled" @click="handleChange">{{lable}}
    </label>
    <slot name="show-more"></slot>
  </div>
</template>
<script>
export default {
  name: 'vRadio',
  props: {
    lable: String,
    fill: String,
    value: String,
    disabled: Boolean,
    index: Number
  },
  computed: {
    activeStyle() {
      return {
        backgroundColor: this.fill || '#384970',
        borderColor: this.fill || '#384970',
        color: this.textColor || ''
      };
    }
  },
  methods: {
    handleChange() {
      this.$emit('change', this.index, this.lable);
    }
  }
};
</script>
<style lang="scss" scoped>
.container {
  flex: 1;
  width: 100%;
  .radio {
    font-size: 14px;
    input {
      margin-right: 6px;
      display: none;
    }
    .radio_inner {
      border: 1px solid #bfcbd9;
      width: 18px;
      height: 18px;
      border-radius: $--border-radius-circle;
      position: relative;
      cursor: pointer;
      background: #fff;
      display: inline-block;
      box-sizing: border-box;
      top: 3px;
      &:hover {
        @include border($--color-primary, 1px, border);
      }
      &:after {
        transform: translate(-50%, -50%) scale(1);
        width: 6px;
        height: 6px;
        border-radius: $--border-radius-circle;
        background-color: #fff;
        content: '';
        position: absolute;
        left: 50%;
        top: 50%;
      }
    }
    .theme-button {
      @include bg_color($--color-primary, 'normal');
    }
    .theme-border {
      @include border($--color-primary, 1px, border);
    }
  }
}
</style>