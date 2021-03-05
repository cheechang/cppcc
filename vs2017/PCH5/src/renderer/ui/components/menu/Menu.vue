<template>
  <div class="dropdown is-active">
    <div class="dropdown-background" @click="clickOut" @contextmenu="$emit('close',true)"></div>
    <div class="triangle-down" v-if="!hasOverlay"></div>
    <div class="dropdown-menu" :style="currentPos" v-if="menuList.length">
      <div class="dropdown-content" :class="[size]">
         <a href="#" class="dropdown-item" v-if="headDivider" @click.stop="$emit('headItemClick')" @dragstart.prevent>
          {{headDivider}}
         </a>
        <hr class="dropdown-divider" v-if="headDivider">
        <a href="#" class="dropdown-item" v-for="(item,index) in menuList" :key="index" @click.stop="clickEvent(index)" @dragstart.prevent>
          <p>{{item}}</p>
        </a>
        <hr class="dropdown-divider" v-if="footerDivider">
        <a href="#" class="dropdown-item" v-if="footerDivider"  @click.stop="$emit('footerItemClick')" @dragstart.prevent>
          {{footerDivider}}
        </a>
      </div>
    </div>
  </div>
</template>
<script>
export default {
  name: 'vMenu',
  props: {
    menuList: Array,
    currentPos: Object,
    isDivider: Boolean,
    size: String,
    hasOverlay: {
      type: Boolean,
      default: true
    },
    headDivider: {
      type : String,
      default: ''
    },
    footerDivider: {
      type : String,
      default: ''
    }
  },
  methods: {
    clickEvent(index) {
      this.$emit('selectItem', index);
    },
    clickOut() {
      console.log('clickOut:::::')
      this.$emit('close')
    }
  },
  created() {
    console.log('headDivider:::::::', this.headDivider)
  }
};
</script>
<style lang="scss" scoped>
.dropdown {
  position: fixed;
  z-index: 101;
  top: 0;
  left: 0;
  .triangle-down {
    width: 14px;
    height: 14px;
    position: absolute;
    left: 37px;
    top: 20px;
    background: #fff;
    border: 1px solid #ccc;
    border-top: none;
    border-right: none;
    @include z-index(menu);
    transform: rotate(135deg);
  }
  .dropdown-background {
    position: fixed;
    width: 100%;
    height: 100%;
    // -webkit-app-region: no-drag;
  }
  .dropdown-divider {
    margin: 0;
  }
  .dropdown-menu {
    min-width: 5rem;
    width: inherit;
    border-radius: $--border-radius-base;
    padding: 0;
    box-shadow: $--box-shadow-elevation;
    -webkit-app-region:no-drag;      // 解决导航栏拖拽后，菜单触发不了鼠标事件
    .dropdown-item {
      padding-right: 1rem;
    }
  }
}
</style>

