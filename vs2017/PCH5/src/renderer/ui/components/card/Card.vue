<template>
  <div class="card" :class="[cardClass, mediaClass]" @dblclick="handleDbClick"  @click="handleClick" @mouseover.stop="handleMouseOver" @mouseout.stop="handleMouseOut" @mouseleave.self.stop="handleMouseLeave" @mouseenter.self.stop="handleMouseEnter" @contextmenu="menuClick">
    <div class="card-content default-content v-ripple" ref="card">
      <slot name="extra"></slot>
      <div class="media" >
        <div class="media-left" v-if="showLeft">
          <slot name="left"></slot>
          <slot name="leftAvatar"></slot>
        </div>
        <div class="media-content">
          <p class="title">
            <span class="title-main">
              <v-tooltip class="card-tip" type="is-light" :active="isTipActive" position="is-bottom" :lable="title" always></v-tooltip>
              {{title}}
            </span>
            <slot name="after"></slot>
          </p>
          <p v-if="subtitle" class="subtitle">
            <slot name="subBefore"></slot>
            <span  class="contents" :title='subtitle' v-text="subtitle"></span>
            <slot name="subAfter"></slot>
          </p>
          <slot></slot>
        </div>
         <div class="media-right" v-if="showRight">
          <slot name="right"></slot>
          <slot name="rightAvatar"></slot>
         </div>
      </div>
    </div>
  </div>
</template>
<script>
export default {
  name: 'vCard',
  data() {
    return {
      menuClickNum: Number,
      active: false,
      timer: null
    };
  },
  props: {
    index: Number | String,
    title: String | Number,
    subtitle: String,
    inset: String,
    isTipActive: {
      type: Boolean,
      default: false
    },
    isSelected: {
      type: Boolean,
      default: false
    },
    isFirstBreakpoint: {
      type: Boolean,
      default: false
    },
    isSecondBreakpoint: {
      type: Boolean,
      default: false
    },
    // 防抖属性
    debounced: {
      type: Boolean,
      default: false
    }
  },
  created() {
    this.$signalMonitor.$on('change-active', this.handleChange)
    if (!this.$parent.$data._isCard) {
      this.$destroy();
      throw new Error('You should wrap card');
    }
    this.$parent.cardLists.push(this);
  },
  beforeDestroy() {
    this.$signalMonitor.$off('change-active', this.handleChange)
  },
  computed: {
    cardClass() {
      return {
        'theme-list-items-active': this.active
      }
    },
    mediaClass() {
      return {
        'screen-max-width-801': this.isSecondBreakpoint,
        'screen-max-width-914': this.isFirstBreakpoint
      }
    },
    showLeft() {
      return (
        this.$slots &&
        ((this.$slots.left && this.$slots.left.length > 0) ||
          (this.$slots.leftAvatar && this.$slots.leftAvatar.length > 0))
      );
    },
    showRight() {
      return (
        this.toggleNested ||
        (this.$slots &&
          ((this.$slots.right && this.$slots.right.length > 0) ||
            (this.$slots.rightAvatar && this.$slots.rightAvatar.length > 0)))
      );
    }
  },
  methods: {
    handleChange(active) {
      this.active = active == this.index;
    },
    handleClick(e) {
      if (this.debounced) {
        if (this.timer) {
          window.clearTimeout(this.timer);
          this.timer = null;
        }
        this.timer = window.setTimeout(() => {
          this.$emit('click', e);
          if (this.$parent.handleItemClick) this.$parent.handleItemClick(this);
        }, 250);
      } else {
        this.$emit('click', e);
        if (this.$parent.handleItemClick) this.$parent.handleItemClick(this);
      }
    },
    menuClick() {
      this.$emit('contextmenu', this.index);
      this.$parent.num = this.index;
    },
    handleDbClick(e) {
      if (this.debounced && this.timer) {
        window.clearTimeout(this.timer);
        this.timer = null;
      }
      this.$emit('dbClick', e);
      if (this.$parent.handleItemDbClick) this.$parent.handleItemDbClick(this);
    },
    handleMouseEnter(e){
      this.$emit('mouse-enter',e,this.index);
    },
    handleMouseLeave(e){
      this.$emit('mouse-leave',e,this.index);
    },
    handleMouseOver(e){
      this.$emit('mouseover',e,this.index);
    },
    handleMouseOut(e){
      this.$emit('mouseout',e,this.index);
    }
  }
};
</script>