<template>
  <div class="msg-type-unknow">
    <p :class="{'font-color':message.messageObject.senderId === user_account.userId}">{{$t('msgType.1005')}}</p>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
export default {
  props: {
    message: Object
  },
  computed: {
    ...mapGetters([ 'user_account' ])
  },
  created () {
    console.log('in unknow');
  }
};
</script>
<style lang="scss" scoped>
.msg-type-unknow{
  padding: 8px;
}
</style>
