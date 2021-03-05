<template>
  <chat-tab-items :isOpen="isOpen" :userInfo="userInfo" :id="id" :chatType="chatType" :tabList="msgTypeList" @changeTab="changeTab"></chat-tab-items>
</template>
<script>
import { mapGetters } from 'vuex';
import ChatTabItems from '../../../Common/ChatTabItems'
export default {
  data() {
    return {
      msgTypeList: [
        {icon: '&#xe6a7;', tabName: "置顶", iconTitle: this.$t('chat.msgRecord'), view: 'msgRecord', tabView:  resolve => require(['./ChatMsgTop/MsgTopList'], resolve), isLoad: true},
        {icon: '&#xe6a7;', tabName: "聊天", iconTitle: this.$t('chat.msgRecord'), view: 'msgRecord', tabView:  resolve => require(['./ChatMsgRecord/index.vue'], resolve), isLoad: false}  
      ]
    }
  },
  props: {
    userInfo: Map | Function,
    id: String,
    chatType: Number,
    isOpen: Boolean,
  },
  methods: {
    /**
     *【消息置顶】
     * 消息置顶Tab封装了一个组件，群文件和图片的tab也改成同样组件
     */
    changeTab(value) {
      console.log('vaule:::::', value)
      console.log('this.msgTypeList[value]:::::', this.msgTypeList[value].isLoad)
      if (value === 1 && !this.msgTypeList[value].isLoad) {
        // this.msgTypeList[value].isLoad = true
        this.$set(this.msgTypeList[value], 'isLoad', true)
      }
    }
  },
  components: {
    ChatTabItems
  }
};
</script>

<style lang="scss" >

</style>
