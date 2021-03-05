<template>
  <div class="modal-search">
    <v-modal cardSize="search-class" @close="$emit('close')">
      <div class="modal-card-head" slot="header-top">
        <p class="modal-card-title">正在进行视频会话</p>
        <i class="icon" @click="$emit('close')">&#xe603;</i>
      </div>
      <div class="search-session">
        <video id="myVideoFull" :src="myVideoSrc"></video>
      </div>
    </v-modal>
    </div>
</template>
<script>
export default {
  created() {},
  props: {
    myVideoSrc: {},
    hisVideoSrc: {}
  },
  components: {}
};
</script>
<style lang="scss">
.modal-search {
  .search-class {
    height: 438px;
    width: 530px;
    border-radius: $--border-radius-base;
    overflow: hidden;
    background: black;
    .modal-card-head {
      height: 20px;
      background: #f0f0f0;
      border-bottom: none;
      .modal-card-title {
        //background:black;
        font-size:$--font-size-mid;;
      }
      .icon {
        font-size:$--font-size-mid;;
        margin-right: -15px;
      }
    }
    .search-session {
      height: 100%;
      background: black;
      //padding: 10px 10px;
      overflow-y: hidden;
    }
  }
}
</style>
