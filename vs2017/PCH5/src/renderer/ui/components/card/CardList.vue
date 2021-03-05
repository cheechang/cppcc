<template>
  <div @contextmenu="showContextMenu" @scroll.passive.stop="isShowMenu=false">
    <slot></slot>
    <v-menu v-if="menuList&&menuList.length>0&&isShowMenu"
        @close='onCloseMenu' 
        :menuList="menuList" 
        :currentPos="currentPos"
        :size="size"
        @selectItem="selectItem">
    </v-menu>
  </div>
</template>
<script>
export default {
  name: 'vCardList',
  data() {
    return {
      /**
       * 右键菜单定位
       */
      currentPos: {
        top: String,
        left: String
      },
      _isCard: true, // Used internally by TabItem
      isShowMenu: false,
      isCloseMenu: false,
      cardLists: [],
      num: Number | String
    };
  },
  props: {
    type: Number,
    cardList: Object | Array,
    menuList: Array,
    size: String,
    itemSize: {
      type: Number | String,
      default: 46
    }
  },
  methods: {
    // 右键菜单点击回调
    selectItem(index) {
      this.$emit('menuClick', this.menuList[index], index, this.num);
      this.isShowMenu = false;
    },
    delItem(index) {
      console.log('indexName', index);
    },
    handleItemClick(listItem) {
      this.$emit('itemClick', listItem);
      this.$emit('item-click', listItem);
    },
    handleItemDbClick(listItem) {
      this.$emit('itemDbClick', listItem);
      this.$emit('item-db-click', listItem);
    },
    showContextMenu(e) {
      setTimeout(() => {
        if (this.isCloseMenu) {
          this.isCloseMenu = false;
          return;
        }
        let length = (!this.menuList && 3) || this.menuList.length;
        if (!this.menuList || this.menuList.length === 0) {
          this.isShowMenu = false;
        } else {
          this.isShowMenu = !this.isShowMenu;
        }
        this.currentPos.left =
          (e.clientX > 845 ? e.clientX - 100 + 5 : e.clientX + 8) + 'px';
        this.currentPos.top =
          (e.clientY > 465
            ? e.clientY - this.itemSize * length + 8
            : e.clientY + 8) + 'px';
      }, 0);
    },
    onCloseMenu(isCloseMenu) {
      if(isCloseMenu) this.isCloseMenu = true;
      this.isShowMenu = false;
    }
  }
};
</script>