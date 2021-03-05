<template>
  <div class="chat-single-aside">
     <!-- 单聊会话设置页 -->
   
    <!-- 文件直传展示 -->
    <chat-rtc-box v-if='showRtcFileArea' :isDelAllRtcFile="isDelAllRtcFile" @close="$emit('close')"  :id="id" @changeExpend="$emit('changeExpends', false)" :isExpendSidebar="isExpend"  :rtcFile='chat_rtc_file_list[id]' >
    </chat-rtc-box>
    <chat-single-config v-else-if='isExpend' :id="id"></chat-single-config>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import ChatRtcBox from './ChatRtcBox'
import ChatSingleConfig from './ChatSingleConfig';
export default {
  props: {
    currentActive: Number,
    id: String,
    chatType: Number,
    isExpend: Boolean,
    rtcFile: {
      type: Object
    },
    isDelAllRtcFile: Boolean
  },
  computed: {
    showRtcFileArea() {
      if (this.rtcFile && Object.keys(this.rtcFile).length) {
        this.$emit('changeExpends', true)
        return true
      } 
    },
     ...mapGetters(['chat_rtc_file_list'])
  },
  components: {
    ChatRtcBox,
    ChatSingleConfig
  }
};
</script>

<style lang="scss" scope>
.chat-single-aside {
  /* fit xp */
  display: flex;
  flex-direction: column;
}
</style>
