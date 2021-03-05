<template>
  <div class="pc-add-menu">
    <v-menu v-if="isMenuShow" :menuList="menuList" :currentPos="currentPos" @close="$emit('close')" @selectItem="selectItem"></v-menu>
    <search-contact v-if="isSearchGroup" @close="$emit('close')"></search-contact>
    <!-- <create-group v-if="isCreateGroup" :isInviteMember="false" @close="$emit('close')"></create-group> -->
  </div>
</template>
<script>
import SearchContact from '../Contact/SearchContact/index';
import CreateGroup from './CreateGroup.vue';
export default {
  name: 'group-add-menu',
  data() {
    return {
      isCreateGroup: false,
      isSearchGroup: false,
      isMenuShow: true,
      isAddServer:false,//,this.$t('auth.addServer'), this.$t('search.createGroup')
      menuList: [this.$t('organizations.addFriend')]
    };
  },
  props: {
    currentPos: Object
  },
  components: {
    SearchContact,
    CreateGroup
  },
  methods: {
    selectItem(index) {
      if(index === 2){
        this.$emit('showAddServer');
        return;
      }
      [this.isMenuShow, this.isSearchGroup, this.isCreateGroup] = [false, index == 0, index == 1];
    }
  }
};
</script>
<style lang="scss">
@mixin add-menu {
  position: fixed;
  top: 40px;
  right: 30px;
  font-size: 16px;
  color: $--color-white;
  z-index: 999;
}
.pc-add-menu {
  @include add-menu;
  .dropdown {
    top: 0;
    left: 0;
  }
}
</style>


