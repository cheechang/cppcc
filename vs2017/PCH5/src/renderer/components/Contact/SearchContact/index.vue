<template>
  <div class="modal-search">
    <v-modal cardSize="search-class" @close="$emit('close')">
      <div class="modal-card-head" slot="header-top">
        <p class="modal-card-title">{{ $t('search.find') }}</p>
        <i class="icon" @click="$emit('close')">&#xe603;</i>
      </div>
      <div class="search-session">
        <search-list @close="$emit('close')"></search-list>
      </div>
    </v-modal>
  </div>
</template>
<script>
import SearchList from './SearchList.vue';
export default {
  components: {
    SearchList
  }
};
</script>
<style lang="scss">
.modal-search {
  .search-class {
    height: 500px;
    width: 530px;
    border-radius: $--border-radius-base;
    overflow: hidden;
    background: #ffffff;
    .modal-card-head {
      height: 20px;
      background: #f0f0f0;
      border-bottom: none;
      .modal-card-title {
        font-size: 14px;
      }
      .icon {
        font-size: 14px;
        margin-right: -15px;
      }
    }
    .search-session {
      height: 100%;
      padding: 10px 10px 10px 30px;
      overflow-y: hidden;
      overflow-x: hidden;
      background: #fff;
    }
  }
}
</style>
