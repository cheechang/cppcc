<template>
  <div class="official-accounts">
    <div class="accounts-list" @dragstart.prevent>
      <v-menu v-if="isShowMenu" :menuList="menuList" :currentPos="currentPos" @close="isShowMenu = false" @selectItem="selectItem"></v-menu>
      <div class="accounts-item" v-for="(item, index) in contact_appList" :key="index" @contextmenu="setMenu($event,item)" @dblclick="startChat(item, 3)">
        <v-avatar size='is-big' class="item-avatar" :src='item.thumbAvatar' :sex="3" :offline="false" shape="round" slot="leftAvatar"></v-avatar>
        <p class="item-name">{{item.name}}</p>
      </div>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import mixin from './ContactMixin.js';
export default {
  mixins: [mixin],
  data() {
    return {
      isShowMenu: false,
      menuList: [this.$t('contacts.unfollow'), this.$t('contacts.view')],
      currentPos: {
        top: '',
        left: ''
      },
      currentItem: {}
    };
  },
  computed: {
    ...mapGetters(['contact_appList'])
  },
  methods: {
    /**
     * 设置菜单位置
     */
    setMenu(e, item) {
      this.isShowMenu = true;
      this.currentItem = item;
      this.currentPos.left = e.clientX + 'px';
      this.currentPos.top = e.clientY + 'px';
    },
    /**
     * 选择菜单项
     */
    selectItem(index) {
      index === 0
        ? this.cancelFollow(this.currentItem)
        : this.startChat(this.currentItem, 3);
    },
    /**
     * 取消关注
     */
    cancelFollow({id}) {
      this.$Service.contact.removeContact({ userId: id }, resp => {
        console.log('公众号取消关注', resp);
        this.isShowMenu = false;
        this.$store.commit('DELETE_APPLSIT', id);
      });
    }
  }
};
</script>
<style lang="scss">
.official-accounts {
  flex: 1;
  display: flex;
  align-items: flex-start;
  background: #fff;
  border-radius: $--border-radius-base;
  margin: 10px;
  height: calc(100% - 20px);
  overflow-y: auto;
  .accounts-list {
    width: 100%;
    display: flex;
    color: $--color-black;
    flex-wrap: wrap;
    .accounts-item {
      width: 12%;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      margin: 2%;
      pointer-events: all;
      .item-avatar {
        width: 60px;
        height: 60px;
        .imgs {
          justify-content: center;
        }
      }
      .item-name {
        font-size: 14px;
        text-align: center;
        width: 100%;
        height: 20px;
        font-weight: 500;
        margin-top: 10px;
        @include ellipsis;
      }
    }
  }
}
</style>
