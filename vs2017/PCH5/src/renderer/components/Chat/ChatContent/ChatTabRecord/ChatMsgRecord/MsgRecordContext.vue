<template>
  <v-modal cardSize="record-context-class" @close="$emit('close')">
    <div class="modal-card-head record-context-head" slot="header-top">
      <p class="modal-card-title record-context-title">{{$t('chat.chatHistory')}}</p>
      <i class="icon" @click="$emit('close')">&#xe603;</i>
    </div>
    <div class="record-context-session">
      <msg-list
      :messageList="computedMsgContextList"
      :isLoadHistoryMsg="false"
      :isOpen="isOpen"
      :userInfo="userInfo"
      :id="id"
      :chatType='chatType'
      :selectBgId="selectActive.msgId"
      ></msg-list>
    </div>
  </v-modal>
</template>
<script>
import MsgList from '../../../Msg/MsgList'
import { msgStructure } from "../../../Msg";
export default {
  components: {
    MsgList
  },
  data() {
    return {
      msgContextList: {},
      msgContextListTop: {},
      msgContextListBottom: {}
    }
  },
  props: {
    msgId: String,
    id: String,
    userInfo: Map | Function,
    chatType: Number,
    isOpen: Boolean,
    selectActive: Object
  },
  computed: {
    computedMsgContextList() {
      this.msgContextList = Object.assign(this.msgContextListTop, this.msgContextListBottom)
      let list = Object.values(this.msgContextList);
      if (!list||list.length===0) return {}
      // return _.orderBy(this.msgContextList, ['time'] ,['desc'])
      return this.msgContextList
    }
  },
  mounted() {
    let msg = {
      targetId: this.id,
      msgId: this.msgId ? this.msgId : 0,
      count: 30
    }
    // 向上查找30条
    let msgTop = Object.assign({flag: 0}, msg)
    this.getMessages(msgTop, 0)
    // 向下查找30条
    let msgBottom = Object.assign({flag: 1}, msg)
    this.getMessages(msgBottom, 1)
  },
  methods: {
    /**
     * 获取上下文历史消息
     * @param {Object} params - 接口传参
     * @param {Number} flag - 向上/下查找 0:up 1:down
     */
    getMessages(params, flag) {
      this.$Service.chat.getMessages(params, resp => {
        console.log('getMessages::::', resp)
        _.forEach(resp.msgs, element => {
          if (flag === 0)
            this.$set(this.msgContextListBottom, `id_${element.msgId}`, msgStructure(element));
          else 
            this.$set(this.msgContextListTop, `id_${element.msgId}`, msgStructure(element));
        });
      });
    }
  }
}
</script>
<style lang="scss">
.record-context-class {
  height: 500px;
  width: 530px;
  border-radius: $--border-radius-base;
  overflow: hidden;
  background: #ffffff;
  .record-context-head {
    height: 20px;
    background: #f0f0f0;
    border-bottom: none;
    .record-context-title {
      font-size:$--font-size-mid;;
      color: #000;
    }
    .icon {
      font-size:$--font-size-mid;;
      margin-right: -15px;
    }
  }
  .record-context-session {
    height: 100%;
    color: #363636;
    padding: 10px 30px;
    overflow-y: auto;
    background: #fff;
  }
}
</style>

