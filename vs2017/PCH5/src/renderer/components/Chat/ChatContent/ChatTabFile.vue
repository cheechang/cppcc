<template>
  <chat-tab-items :isOpen="isOpen" :userInfo="userInfo" :id="id" :chatType="chatType" :tabList="msgTypeList" @changeTab="changeTab"></chat-tab-items>
</template>
<script>
import { mapGetters } from 'vuex';
import ChatTabItems from '../../Common/ChatTabItems.vue'
export default {
  data() {
    return {
      msgTypeList: [
        {icon: '&#xe6b0;', tabName: this.$t('chat.file'), iconTitle: this.$t('chat.chat'), view: 'chat', tabView:  resolve => require(['../../Group/ChatGroupFile.vue'], resolve), isLoad: true}, 
        {icon: '&#xe6a7;', tabName: this.$t('chat.image'), iconTitle: this.$t('chat.msgRecord'), view: 'msgRecord', tabView:  resolve => require(['./ChatImageRecord'], resolve), isLoad: false}  
      ]
    }
  },
  props: {
    userInfo: Map | Function,
    id: String,
    chatType: Number,
    isOpen: Boolean
  },
  methods: {
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
