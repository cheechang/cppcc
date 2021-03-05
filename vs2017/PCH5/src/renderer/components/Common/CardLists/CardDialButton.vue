<template>
  <transition name="scale-transition">
    <div v-if="isShow" :class="`v-dial-list v-dial-direction-${offsetDirection}-${selfDirection}`" :style="computedWidth">
      <button class="v-btn v-btn-float v-ripple" v-if="!item.isHidden" :style="{background: item.color}" :title="item.tooltip" v-for="(item, index) in dialList" :key="index" @click="$emit('click', index)">
        <div class="v-btn-content">
          <i :class="`icon button-icon icon-${item.id}`" v-html="item.icon"></i>
        </div>
      </button>
    </div>
  </transition>
</template>
<script>

import {isWinXp} from '../../../../comm/is'
export default {
  props: {
    dialList: Array,
    /**悬浮按钮相对于触发按钮的方向: top/bottom/left/right */
    offsetDirection: {
      type: String,
      default: 'bottom'
    },
    /**悬浮按钮横向竖向: horizonal/vertical */
    selfDirection: {
      type: String,
      default: 'horizonal'
    },
    isShow: [ Array , Boolean ]
  },
  computed: {
    computedWidth() {
      return {
        width: this.dialList.length * 56 + 'px',
        left:-(this.dialList.length-1)*56/2 +'px'
      }
    }
  }
}
</script>
<style lang="scss">
@mixin top {
  // left: 0;
  width: 100%;
  bottom: 100%;
}
@mixin bottom {
  // left: 0;
  top: 100%;
  width: 100%;
}
@mixin left {
  top: 0;
  right: 100%;
  height: 100%;
}
@mixin right {
  top: 0;
  left: 100%;
  height: 100%;
}
.v-dial-direction-top-horizonal {
  @include top;
}
.v-dial-direction-top-vertical {
  @include top;
  flex-direction: column-reverse;
}

.v-dial-direction-bottom-horizonal {
  @include bottom;
}
.v-dial-direction-bottom-vertical {
  @include bottom;
  flex-direction: column;
}

.v-dial-direction-left {
  @include left;
}
.v-dial-direction-left-horizontal {
  @include left;
  flex-direction: row-reverse;
}

.v-dial-direction-right {
  @include right;
}
.v-dial-direction-right-horizontal {
  @include right;
  flex-direction: row;
}

.v-dial-list {
  display: flex;
  align-items: center;
  justify-content: center;
  position: absolute;
  width: 100%;
  .v-btn {
    align-items: center;
    border-radius: $--border-radius-base;
    display: inline-flex;
    height: 36px;
    flex: 0 0 auto;
    font-size: 14px;
    font-weight: 500;
    justify-content: center;
    margin: 6px 8px;
    min-width: 88px;
    outline: 0;
    text-transform: uppercase;
    text-decoration: none;
    transition: 0.3s cubic-bezier(0.25, 0.8, 0.5, 1), color 1ms;
    position: relative;
    vertical-align: middle;
    -webkit-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    cursor: pointer;
    @include z-index(btn);
    .v-btn-content {
      align-items: center;
      border-radius: inherit;
      color: inherit;
      display: flex;
      flex: 1 0 auto;
      justify-content: center;
      margin: 0 auto;
      position: relative;
      transition: 0.3s cubic-bezier(0.25, 0.8, 0.5, 1);
      white-space: nowrap;
      width: inherit;
      flex: 1 1 auto;
      margin: 0;
      height: 100%;
      .button-icon {
        width: 100%;
        height: 100%;
        color: #fff;
      }
      .icon-edit {
        font-size: 20px;
      }
      .icon-delete {
        font-size: 24px;
      }
      .icon-avatar {
        font-size: 24px;
      }
      .icon-share {
        font-size: 28px;
        margin-top: 2px;
      }
    }
  }
  .v-btn-float {
    border: none;
    border-radius: $--border-radius-circle;
    min-width: 0;
    padding: 0;
    height: 40px;
    width: 40px;
    position: relative;
    box-shadow: $--box-shadow-lr;
    &:hover {
      opacity: 0.88;
      box-shadow: $--box-shadow-elevation-hover;
    }
  }
}
</style>

