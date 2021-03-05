<template>
  <div class="type-mix-text">
    <div class="type-mix-box">
    <div class="text-border">
      <div class="text-item" v-for="(value, index) in messageList" :key="index">
        <div class="item-content">
          <v-tooltip type="is-light" position="is-top" :active="index===nameIndex" :lable="value.userName" always>
            <p class="content-left" @mouseenter="nameIndex=index" @mouseleave="nameIndex=-1">{{value.userName}}</p>
          </v-tooltip>
          ：
          <v-tooltip class="text-tip" type="is-light" position="is-top" :active="index===contentIndex" :lable="getMixContent(value)" always>
            <p class="content-right" @mouseenter="contentIndex=index" @mouseleave="contentIndex=-1">{{getMixContent(value)}}</p>
          </v-tooltip>
        </div>
        <div class="item-divider"></div>
      </div>
    </div>
    <div class="text-detail">
      <!-- <p @click="isOpenDetail=true">聊天记录></p> -->
      <p @click="isOpenDetail=true">{{$t('chat.chatHistory')}}</p>
    </div>
    <div @contextmenu.stop>
      <mix-msg-detail v-if="isOpenDetail" :id="message.messageObject.targetId" :msgItem="message.messageObject.mVt_msg" :mixMsgId="message.messageObject.msgId" @close="isOpenDetail=false"></mix-msg-detail>
    </div>
    </div>
  </div>
</template>
<script>
import MixMsgDetail from './MixMsgDetail';
export default {
  data() {
    return {
      isExpendFullName: false,
      nameIndex: -1,
      contentIndex: -1,
      isOpenDetail: false
    };
  },
  props: {
    message: Object
  },
  computed: {
    messageList() {
      return this.message.messageObject.mVt_msg;
    }
  },
  components: {
    MixMsgDetail
  },
  methods: {
    // 指令、语音、微视频、组合消息不能转发
    getMixContent({ msgType, body }) {
      // let msgTypes = {
      //   2: msgType==2&&this._handleFlashText(body),
      //   3: '[音频]',
      //   4: '[位置]',
      //   5: '[图片]',
      //   6: '[文件]',
      //   7: '[名片]',
      //   9: '[网络链接]',
      //   19: '[动态表情]',
      //   28: '[九图消息]',
      //   89: '[微视频]',
      // }
      // return msgTypes[msgType] || '[暂不支持]';
      return this.$t(`msgType.${msgType||'1005'}`);
    },
    // 处理抖一抖消息
    _handleFlashText(body) {
      if (body.includes('&:flash')) { 
        return body.replace('&:flash', '') || this.$t(`msgType.1003`);
      } else {
        return body;
      }
    }
  }
};
</script>
<style lang="scss">
.type-mix-box{
  width: 100%;
  height: 100%;
  border-radius: $--border-radius-large;
  background: #fff;
  padding: 4px;
}
.type-mix-text {
  display: flex;
  flex-direction: column;
  padding: 3px;
  .text-border{
    max-height: 106px;
    overflow-y: hidden;
    color: #000;
  .text-item {
    // padding: 0 2px;
    .item-content {
      display: flex;
      font-size: 0.75rem;
      padding: 0 20px;
      .text-tip {
        max-width: 310px;
      }
      .content-left {
        width: 36px;
        @include ellipsis;
      }
      .content-right {
        flex: 1;
        margin-left: 5px;
        @include ellipsis;
      }
    }
    .item-divider {
      margin: 8px 0;
      height: 1px;
      width: 100%;
      background: #cdcdcd;
    }
  }}
  .text-detail {
    display: flex;
    justify-content: flex-end;
    margin-top: -16px;
    p {
      font-size: 0.75rem;
      color: get-blue-color(darken-4);
      cursor: pointer;
      margin-top: 8px;
    }
  }
}
</style>


