<template>
  <transition :name="zoomInTop? 'zoom-in-top': 'zoom-in-bottom'">
    <div
      class="select-list"
      v-if="isShow"
      v-click-outside="onClickOutside"
    >
      <div
        class="item"
        v-for="(item, index) in listData"
        :key="index"
        v-if="selectedIndex != item.type"
        @click="selectItem(item.type, item)"
      >
        <span>{{item.val}}</span>
      </div>
    </div>
  </transition>
</template>
<script>
import vClickOutside from './../../Chat/v-click-outside/index.js';
export default {
  props:{
    isShow: Boolean,
    listData: Array | Object,
    selectedIndex: Number | String,
    zoomInTop:{
      default:true,
      type:Boolean
    }
  },
  directives: {
    clickOutside: vClickOutside.directive
  },
  methods: {
    // 点击外部区域关闭登录方式选择框
    onClickOutside() {
      this.$emit('close-select-list')
    },
    // 选中当前条目
    selectItem(type, item) {
      this.$emit('select-item', type, item.val , item);
      this.$emit('close-select-list');
    }
  }
}
</script>
<style lang="scss" scoped>
.select-list{
  height: auto;
  background: #ffffff;
  display: flex;
  min-width: 98px;
  flex-direction: column;
  position: absolute;
  right: 0;
  top: 45px;
  @include z-index(none);
  border-radius: $--border-radius-base;
  box-shadow: 0 0 1px #3b3939;
  overflow: hidden;
  -webkit-app-region: no-drag;
  &::-webkit-scrollbar-thumb {
    background-color: #bdbdbd;
    border-radius: 3px;
  }
  .item {
    padding: 3px 10px;
    transition: none;
    cursor: pointer;
    span{
      transition: inherit;
    }
    &:hover {
      background: rgb(45, 117, 250);
      color: $--color-white;
    }
  }
}
</style>

