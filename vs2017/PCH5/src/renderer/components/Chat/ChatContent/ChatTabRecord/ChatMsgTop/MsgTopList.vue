<template>
  <div class="msg-top-list">
    <msg-list
      :messageList="getContentList"
      :isOpen="isOpen"
      :userInfo="userInfo"
      :id="id"
      :chatType='chatType'
      :cancelGroupMsgTop="true"
      :openMsgUnread='false'
    ></msg-list>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import MsgList from '../../../Msg/MsgList'
export default {
  props: {
    id: String,
    isOpen: Boolean,
    chatType: Number | String,
    userInfo: Object
  },
  data() {
    return {
      chatTopMsgList: {}
    }
  },
  components: {
    MsgList
  },
  computed: {
    ...mapGetters(['chat_chatContentTop']),
    getContentList(){
          /**
     * 【消息置顶】
     * 直接可以参照ChatImageRecord组件，基本一致
     * 这里的数据仅作为测试展示，数据格式即chat_chatContent里对应的id对象
     * 这里的测试数据是全部消息，真实的数据只有文本类型的消息
     * 进入会话获取置顶消息列表：1.跑马灯需要通过获取置顶数据展示 2.存入vuex后这里再获取展示
     */
    console.log('chat_chatContentTop:::::', JSON.stringify(this.chat_chatContentTop))
    this.chatTopMsgList = {};
    _.forEach(this.chat_chatContentTop, (e, i) => {
      let element = Object.assign({}, e)
      element.msgType = 2
      element.topListSign = true; //作为取消置顶时标识，以区分是否对relatedMsgId进行操作
      try {
        element.body = JSON.parse(element.topContent).content
        element.fromId = element.createUserId
        element.time = element.createTime
        element.topId = element.id
        element = { 'messageObject': element}
        this.$set(this.chatTopMsgList, i, element)
      } catch (error) {
        console.log('topmsg:::error:', error)
      }
    })
    console.log('chatTopMsgList:::::', this.chatTopMsgList)
    return this.chatTopMsgList
    },
  },
  created() {
  }  
}
</script>
<style lang="scss">
.msg-top-list {
  display: flex;
  width: 100%;
}
</style>
