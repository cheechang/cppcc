<template>
  <div class="chat-muti-video" ref="videoList"   :class="{'chat-muti-bg': !this.videoMsgList.length}" @scroll.passive.stop="handleScroll">
    <transition name="slide-fade">
      <v-card-list class="record-meeting">
        <v-card  class="record-meeting-item" v-for="(item,index) in videoMsgList" :key="index" :title="getMeetingTitle(item)" :subtitle="item.title">
          <v-avatar :src="meetingAvatar" size='is-small' slot="leftAvatar"></v-avatar>
            <div class="meeting-info" slot="subAfter">
             <span> {{getTimes(item.time)}} </span>
             <span class="meeting-creator"> {{creator(item.creator)}} </span>
            </div>
            <i class="icon video-item-btn" slot="rightAvatar">&#xe641;</i>
        </v-card>
      </v-card-list>
    </transition>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import { getDateDiff } from '../../../../comm/time';
import commMxin from '../Mixins/common.js'
export default {
  mixins: [commMxin],
  data() {
    return {
      videoMsgList:[],
      meetingAvatar:require('vrv-static/resources/images/message/vidio.png'),
      initLength:10
    }
  },
  methods: {
    getMessage(msgId=0) {
     
      // 获取历史消息传入的参数 targetId msgId count flag
      let msg = {
        targetId: this.$route.query.id, // 传入会话对应的ID，群或者人
        msgId: msgId, // 传入查询消息的起始ID，将从该消息的下一条消息开始查询
        count: 15, // 传入查询消息总数
        msgType: [26],
        flag: 0 // 传入上一页还是下一页 向上偏移 0；向下偏移 1
      };
      console.log('msg', msg.msgId)
      this.$Service.chat.getMessages(msg, resp=> {
        console.log('getMessages', resp)
        let msg = _.orderBy( resp.msgs,['time'], ['desc'])
        msg.forEach(element => {
          try {
            let detailUrl = JSON.parse(element.detailUrl)
            if (detailUrl && detailUrl.subType === 14) {
              console.log('element', element)
              this.videoMsgList.push(element)
            }
          } catch (error) {
            console.log('muti-video', error)
          }
        });
      });
    },
    getTimes(time) {
      return getDateDiff(parseInt(time))
    },
    getMeetingTitle(item) {
      return item.relatedUsers&&item.relatedUsers.length ? `${item.content} (${item.relatedUsers.length}人)`: item.content
    },
    handleScroll(e) {
       if (this.isScrollToBottom(this.$refs.videoList)) { // 滚动条置底部
       let minMsgData = this.videoMsgList[this.videoMsgList.length-1];
       console.log('time', this.videoMsgList)
       console.log('minMsgData', minMsgData)
       this.getMessage((minMsgData.msgId - 1).toString())
      }
    },
    creator(creator) {
      return `发起人: ${creator}`
    }
  },
  mounted() {
    this.getMessage()
  },
  computed: {
    videoMsgLists() {
      return this.videoMsgList.slice(0, this.initLength)
    }
  },
};
</script>

<style lang="scss" >
.chat-muti-video {
  flex: 1;
  overflow: auto;
  &.chat-muti-bg {
    background: url('~vrv-static/resources/images/common/nocontent.png') #fff 43% 43% no-repeat;
    background-size: 200px;
  }
  .record-meeting-item {
    .contents {
      width: 70px;
    }
  }
  .meeting-info {
    display: flex;
    .meeting-creator {
      margin-left: 10px;
    }
  }
  .video-item-btn {
    display: flex;
    align-items: center;
    font-size: 24px;
  }
}
</style>
