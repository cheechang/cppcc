<template>
  <div class="entapp-list">
    <div class="entapp-info">
      <v-avatar size='is-big' class="entapp-avatar" :src='$route.query.item.appIcon' :sex="3" :offline="false" shape="round" slot="leftAvatar"></v-avatar>
      <div class="entapp-content">
        <p>{{ $t('contacts.enterpriseID')+'：' }}</p>
        <p>{{ $route.query.item.appSign }}</p>
      </div>
    </div>
    <div class="entapp-chat">
      <v-button type="is-primary" class="btn-entapp"  @click="startChat($route.query.item, 3)">{{ $t('contacts.startChat') }}</v-button>
    </div>
  </div>
</template>
<script>
import ContactMixin from './ContactMixin.js'
export default {
  mixins: [ContactMixin]
}
</script>
<style lang="scss">
.entapp-list {
  flex: 1;
  display: flex;
  flex-direction: column;
  border-radius: 3px;
  height: 100%;
  overflow-y: auto;
  background: #fff;
  margin: 10px;
  height: calc(100% - 20px);
  .entapp-info {
    flex: 1;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    .entapp-content {
      display: flex;
      position: absolute;
      top: 53%;
      width: calc(100% - 246px);
      justify-content: center;
    }
    .entapp-avatar {
      width: 130px;
      height: 130px;
    }
  }
  .entapp-chat {
    height: 200px;
    display: flex;
    justify-content: center;
    .btn-entapp {
      width: 200px;
      box-shadow: $--box-shadow-lr;
    }
  }
}
</style>
