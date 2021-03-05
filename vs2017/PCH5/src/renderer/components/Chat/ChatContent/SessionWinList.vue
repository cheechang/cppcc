<template>
  <div>
    <div class="session-win"
                             v-for="(i, index) in chat_chatContent"
                             v-show="index === $route.query.id"
                             :key="index">
      <SessionWin :data='i' :isWinFocus="isWinFocus" :isOpen ="index === $route.query.id" :remindMsgSeconds='remindMsgSeconds'  :rtcFile="chat_rtc_file_list[index]" :id="index" :inputState='inputStateList[index]'></SessionWin>
    </div>
  <canvas id="cv" width="220" height="50" style="display:none"></canvas>
  </div>
</template>
<script>
import { msgStructure } from '../Msg';
import MsgMxin from '../msgMixin';
import { mapGetters } from 'vuex';
export default {
  data() {
    return {
      sessionType: {},
      remindMsgSeconds: 0,
      inputStateList: {},
      isWinFocus: false
    };
  },
  mixins: [MsgMxin],
  beforeDestroy() {
    this.$ipc.removeAllListeners(['insertMsgFromDDIO']);
    this.$signalMonitor.$off('countDownRemind')
    this.$signalMonitor.$off('updateInputeState')
  },
  computed: {
    ...mapGetters(['chat_chatList'])
  },
  components: {
    SessionWin: resolve => require(['./index'], resolve)
  },
  beforeDestroy() {
    this.$ipc.removeListener('window-focus', this.windowFocus) 
  },
  mounted() {
    this.$ipc.on('window-focus', this.windowFocus)
    this.$ipc.on('insertMsgFromDDIO', (event, message)=> {
      console.log('insertMsgFromDDIO::',message);
      if (!this.chat_chatContent[message.targetId]) return
      this.setMsgFromMainProcess(message);
    });
    this.$store.commit('SET_CHATCONTENT', {targetId: this.$route.query.id, msgs:{}})
    /** 监听追一追倒计时 */
    this.$signalMonitor.$on('countDownRemind', () => {this.countDownRemind()})

    this.$signalMonitor.$on('updateInputeState', clearId => {this.clearInputState(clearId)})
    /**
     * 监听用户输入状态
     */
    this.$Service.chat.regMessageInputStateCb(null, resp => {
        console.log('regMessageInputStateCb:::', resp)
        /** 防止维护的数据越来越大 即时清理 */
        if (this.inputStateList && this.inputStateList[resp.targetId] && resp.status === 1) {
          this.clearInputState(resp.targetId)
          return
        }
        this.$set(this.inputStateList, resp.targetId, resp)
    })
  },
  
  methods: {
    /** 追一追倒计时功能 */
    countDownRemind() {
      this.remindMsgSeconds = 300 
      let timer = setInterval(()=> {
          this.remindMsgSeconds--;
          if (this.remindMsgSeconds < 0) {
            this.remindMsgSeconds = 0;
            clearInterval(timer);
          }
      }, 1000);
    },

    /** 清除输入状态 */
    clearInputState(id) {
      console.log('clearInputState::', id)
      this.$delete(this.inputStateList, id)
    },
    windowFocus(e, isWinFocus) {
      this.isWinFocus = isWinFocus
      let currentItem = this.chat_chatList[this.$route.query.id]
      if ((this.$route.name === 'ChatRightArea'||this.$route.name === 'ChatSystem') && currentItem && currentItem.unreadCount) {
        console.log('==========should read',currentItem)
        if(currentItem.msgType !== 100){
         this.setMessageRead(currentItem.id)
        }else{
          let param ={
            type:currentItem.chatType,
            msgs:[currentItem.lastMsgId]
          }
          console.log('setMessagRead',param)
          this.$Service.sysMsg._sysmsg.setMessagRead(param,res =>{
          this.$Service.log(`setMessageRead:::::::    ${JSON.stringify(res)}`)
          })
        }
      }
    }
  },
  watch: {
    $route(to, from) {
      if (this.$route.name !== 'ChatRightArea') return;
      // 删除对应联系人中的文件缓存文件
      this.delFileCache()
      this.$store.dispatch('REDUCE_CACHE_CONTENT', from.query.id)
      if (this.chat_chatContent[this.$route.query.id]) return
      this.$store.commit('SET_CHATCONTENT', {targetId: this.$route.query.id, msgs:{}})
      console.log('sessionWin change');
    }
  }
};
</script>

<style lang="scss" scoped>
  .session-win {
    flex: 1;
    height: 100%;
    display: flex;
    flex-direction: column;
    #cv{
      display: none
    }
  }
</style>
