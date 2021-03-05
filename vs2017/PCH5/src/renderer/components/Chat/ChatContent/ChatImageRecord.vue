<template>
  <div class="chat-img-record" ref="imgRecord" @scroll.passive.stop="handleScroll">
    <msg-list
      ref="imgRecords"
      :messageList="messageList"
      :isLoadHistoryMsg="isLoadHistoryMsg"
      @LoadMoreMsg="loadMoreHistoryMsg"
      :isOpen="isOpen"
      :userInfo="userInfo"
      :id="id"
      :chatType='chatType'
    ></msg-list>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import { getDateDiff } from "../../../../comm/time";
import { msgStructure } from "../Msg";
import MsgList from "../Msg/MsgList";
import commMxin from "../Mixins/common.js";
export default {
  mixins: [commMxin],
  data() {
    return {
      messageList: {},
      isLoadHistoryMsg: false
    };
  },
  props: {
    userInfo: Map | Function,
    id: String,
    chatType: Number,
    isOpen: Boolean
  },
  methods: {
    // handleScroll(e) {
    //    if (this.isScrollToBottom(this.$refs.videoList)) { // 滚动条置底部
    //     // console.log("to bottom");
    //     if (this.initLength >= this.videoMsgList.length) return;
    //     let num = 20;
    //     if (this.initLength + num > this.videoMsgList.length) {
    //       num =this.videoMsgList.length- this.initLength;
    //     }
    //     this.initLength += num;
    //     console.log("this.initLength", this.initLength);
    //   }
    // },
    /**
     * 加载更多消息
     * SearchModel AtMessage 加载更多关于我的消息
     * SearchModel SearchNet 加载更多对应关键字历史消息
     * SearchModel contach    加载更多对应联系人历史消息
     * minMsgData 当前消息列表最小数据
     *  */
    loadMoreHistoryMsg() {
      console.log("loadMoreHistoryMsg::");
      const initNode = this.$el.getElementsByClassName("search-msg-list-item")[0];
      let minMsgData = _.values(this.messageList)[0].messageObject;
      this.getMsg(minMsgData.msgId, true).then(() => {
        if (initNode === undefined) return;
        initNode.scrollIntoViewIfNeeded(false);
      });
    },

    getMsg(msgId = 0, isLoadMore = false) {
      return new Promise(resolve => {
        let msg = {
          targetId: this.$route.query.id, // 传入会话对应的ID，群或者人
          msgId: msgId, // 传入查询消息的起始ID，将从该消息的下一条消息开始查询
          count: 10, // 传入查询消息总数
          msgType: [5],
          flag: 0 // 传入上一页还是下一页 向上偏移 0；向下偏移 1
        };
        this.$Service.chat.getMessages(msg, resp => {
          console.log("getMessages", resp);
          let obj = {};
          if (resp.msgs.length < 10) {
            this.isLoadHistoryMsg = false;
          } else {
            this.isLoadHistoryMsg = true;
          }
          resp.msgs.forEach(element => {
            try {
              this.$set(obj, `id_${element.msgId}`, msgStructure(element)); //构建不同的消息类型
            } catch (error) {
              console.log("muti-video", error);
            }
          });
          this.messageList = Object.assign(obj, this.messageList);
          resolve();
        });
      });
    }
  },
  mounted() {
    // 获取历史消息传入的参数 targetId msgId count flag
   
      this.getMsg().then(() => {
        this.$nextTick(() => {
          let msgBox = this.$el.getElementsByClassName("search-msg-list")[0];
          console.log('msgBox', msgBox)
          msgBox.scrollTop = msgBox.scrollHeight;
        })
      });;
  },
  computed: {},
  components: {
    MsgList
  }
};
</script>

<style lang="scss" scoped>
.chat-img-record {
  // padding: 0px 10px;
  display: flex;
  width: 100%;
}
</style>
