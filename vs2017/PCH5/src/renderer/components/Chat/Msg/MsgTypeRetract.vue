<template>
  <div class="type-retract">
    <span class="retract-text"><i class="icon noice">&#xe7fb;</i>{{retractTetx}}
    <span  v-if="message.msgReEdit" class="msg-reedit" @click="$emit('reEditHandleClick')">{{$t('chat.reEdit')}}</span>
    </span>
    
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import MsgMxin from '../msgMixin';

export default {
  props: {
    message: Object,
    id: String,
    chatType: Number
  },
  mounted() {
    /** flag  为1时 发送撤回消息 */
    console.log('this.message:::', this.message)
    if (this.message.flag === 1) {
      this.sendRetract()
      let revokeMsg = this.chat_chatContent[this.message.messageObject.targetId][`id_${this.message.messageObject.revokeMsgId}`]
      if (revokeMsg && (revokeMsg.messageObject.msgType === 5 || revokeMsg.messageObject.msgType === 28)) {
        let result= this.$isOpenMediaMsgPreivew()
        if (result && result.isOpen && this.message.messageObject.targetId === result.mediaMsgPreivewId) {
          this.$Service.log(`revokeImage>>>   ${this.message.messageObject.revokeMsgId}`)
          // this.$ipc.send('revokeImage',  {type: 2, imgId: this.message.messageObject.revokeMsgId} )
          this.$ipc.send('handleSubWinMediaMsg',  {winType: 'image', operaType: 2, imgId: this.message.messageObject.revokeMsgId} )
        }
      }
      // console.log('this.chat_chatContent[newMsg.targetId]', this.chat_chatContent[newMsg.targetId])
      // let revokeMsg = this.chat_chatContent[newMsg.targetId][`id_${newMsg.revokeMsgId}`]
      // if (revokeMsg && (revokeMsg.messageObject.msgType === 5 || revokeMsg.messageObject.msgType === 28)) {
      //   let result = isOpenMediaMsgPreivew()
      //   if (result && result.isOpen && newMsg.targetId === result.imagePreivewId) {
      //     console.log('isOpen>>>>>')
      //     this.$ipc.send('revokeImage',  {type: 2, imgId: newMsg.revokeMsgId} )
      //   }
      // }
      // this.delMsg(newMsg.targetId, newMsg.revokeMsgId);
    }
  },
  mixins: [MsgMxin],
  computed: {
    ...mapGetters(['user_account', 'chat_chatContent']),
    retractTetx() {
      return this.message.messageObject.fromId === this.user_account.userId ? this.$t('chat.youRecallMsg') :this.$t('chat.recallMsg', {value: this.message.messageObject.body}) ; 
    }
  },
  methods: {
    /** 发送撤回消息 */
    sendRetract() {
      this.$Service.chat.sendMessage(this.message.messageObject, resp => {
        console.log('sendRetract::', resp)
        if (resp.code === 0) {
            let preMsgId = this.message.messageObject.msgId
            this.message.messageObject.msgId = resp.msgId;
            console.log('this.id', this.id, preMsgId, resp.msgId)
            this.$store.commit('UPDATE_MSGID', {id:this.id, preMsgId:preMsgId, msgId: resp.msgId, isFail:false, time: resp.time})
            // if (this.chatType === 2 && ) {

            // }
            // if (this.message.messageObject.isSenderRevoke) {
            //   console.log('id:', )
            //   let deleteGroupFileParam = {
            //     groupId: this.id,
            //     files: [this.message.messageObject.revokeMsgId.toString()]
            //   }
            //   console.log('deleteGroupFileParam::::', deleteGroupFileParam)
            //   this.$Service.group.deleteGroupFile(deleteGroupFileParam, resp => {
            //     console.log('resp:::', resp)
            //   })
            // }
            this.delMsg(this.message.messageObject.targetId, this.message.messageObject.revokeMsgId.toString());
        }
      });
    }
  }
}
</script>
<style lang="scss">
.type-retract{
  display: flex;
  width: 100%;
  justify-content: center;
  align-items: center;
  margin-bottom: 6px;
  .retract-text{
    .icon {
      display: flex;
      align-items: center;
    }
    display: flex;
    align-items: center;
    background: #dcdcdc;
    border-radius: $--border-radius-large;
    padding: 1px 8px;
    font-size: $--font-size-small;
    .msg-reedit{
      padding: 0px 6px;
      color: get-blue-color(accent-3);

      cursor: pointer;
      &:hover{
        text-decoration:underline;        
      }
    }
  }
}
</style>
