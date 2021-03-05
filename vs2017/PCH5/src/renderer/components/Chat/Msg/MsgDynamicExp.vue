<template>
  <div  class="type-dynamicExp">
   <div class="dynamicExp-img-box">
      <img class="dynamicExp-img" :src="dynamicImg" alt="">
   </div>
   <i v-if="state===-1" class="icon" :class="{'msg-fail-self': message.messageObject.fromId === user_account.userId }" @click="send_DynamicExp()">&#xe63b;</i>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import Emoji from '../Emoji/index.vue';
export default {
  data() {
    return {
      state: 0,
      isFail: false
    }
  },
  props: {
    message: Object,
    id: String
  },
  computed: {
    dynamicImg() {
      return require('vrv-static/resources/images/emoji/text_emoji/' +  this.message.messageObject.body)
    },
    ...mapGetters(['user_account'])
  },
  mounted() {
    if (this.message.flag === 1) {
      this.message.flag === 0;
      this.send_DynamicExp()
    } else {
      this.getMsgState()
    }
  },
  methods: {
    getMsgState() {
      let msgType = this.message.messageObject.msgType
      if (msgType === 531) {
        this.state = -1;
        this.$emit('disableRightClick')
      }
    }, 
    send_DynamicExp() {
      if (this.state !== 0) this.state = 0; // 防止消息发送失败 导致多次点击  多次发送 
      console.log('sendMessage', this.message.messageObject)
      if (this.message.messageObject.msgType !== 19) {
        this.message.messageObject.msgType = 19;
      }
      this.$Service.chat.sendMessage(this.message.messageObject, resp => {
        if (resp.code === 0) {
          let preMsgId = this.message.messageObject.msgId
          this.$store.commit('UPDATE_MSGID', {id:this.id, preMsgId:preMsgId, msgId: resp.msgId, isFail: this.isFail, time: resp.time})
          this.$emit('hasRead', resp.msgId)
        } else {
          this.state = -1;
          if (!this.isFail) {
            this.isFail = true;
          }
          if (this.$route.query.id !== this.message.messageObject.targetId) {
            this.$store.dispatch('CHANGE_CHAT_LIST_STATE', {id: this.message.messageObject.targetId, type: 2} )
          }
        }
      });
    }
  }
}
</script>
<style lang="scss">
.type-dynamicExp{
  width: 120px;
  height: 110px;
  .dynamicExp-img-box {
    width: 100%;
    height: 100%;
    border-radius: 20px;
    overflow: hidden;
    .dynamicExp-img {
      width: 100%;
      height: 100%;
    }
  }
}
</style>
