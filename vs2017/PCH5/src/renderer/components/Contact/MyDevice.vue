<template>
  <div class="my-device">
    <div class="device-icon-area">
      <img class="device-img" :src="myDeviceIcon"/>
    </div>  
    <div class="device-start-chat">
       <v-button type="is-primary" class="btn-start"  @click="startChat(user_account, 1)">{{ $t('contacts.startChat') }}</v-button>
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
      myDeviceIcon: require('vrv-static/resources/images/common/mydevice.png')
    };
  },
  computed: {
    ...mapGetters(['contact_appList', 'user_account'])
  },
  methods: {
  }
};
</script>
<style lang="scss" scoped>
.my-device {
  flex: 1;
  display: flex;
  flex-direction: column;
  border-radius: $--border-radius-base;
  height: 100%;
  overflow-y: auto;
  background: #fff;
  margin: 10px;
  height: calc(100% - 20px);
  .device-icon-area{
    flex: 1;
    display: flex;
    align-items: center;
    justify-content: center;
    /* padding: 20px; */
    .device-img{
      width: 130px;
    }
  }
  .device-start-chat{
    // flex:1;
    height: 200px;
    display: flex;
    justify-content: center;
    .btn-start {
     width: 200px;
     box-shadow: $--box-shadow-lr;
    }
  }
}
</style>
