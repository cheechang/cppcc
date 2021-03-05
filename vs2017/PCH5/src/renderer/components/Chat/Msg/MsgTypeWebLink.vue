<template>
  <div class="web-link" >
    <div class="web-container" :class="webClass">
      <a class="links" @click="openNew(message.messageObject.url)" :title="message.messageObject.url" v-html="message.messageObject.url"></a>
      <div class="web-info">
        <img class="web-img" :src="defaultImg" />
        <div class="web-content" :class="{'web-content-mine': message.messageObject.fromId === user_account.userId}">
          <div class="web-title" v-if="message.messageObject.title" v-html="message.messageObject.title" :title="message.messageObject.title"></div>
          <div class="web-description" v-if="message.messageObject.desc" v-html="message.messageObject.desc" :title="message.messageObject.desc"></div>
        </div>
      </div>
      <a class="open-link" @click="openNew(message.messageObject.url)">{{$t('chat.open')}}</a>
      <i v-if="state ===-1 " class="icon" :class="{'msg-fail-self': message.messageObject.fromId === user_account.userId }" @click="sendLink">&#xe7fb;</i>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
export default {
  props: {
    message: Object,
    id: String,
    isMixMsg: Boolean
  },
  mounted () {
    if (this.message.flag === 1) {
      this.message.flag = 0;
      this.sendLink();
    } else {
      this.getMsgState()
    }
  },
  computed: {
     ...mapGetters(['user_account']),
    webImg () {
      return (this.message.messageObject.img === '' ? defaultImg: this.message.messageObject.img);
    },
    webClass () {
      if (this.id !== this.user_account.userId ) {
        if (this.message.messageObject.fromId === this.user_account.userId && !this.isMixMsg ) {
          return 'web-container-self'
        }
      } else {
        if (this.message.messageObject.deviceType === 1) {
            return 'web-container-self'
        }
      }
    }
  },
  methods: {
    getMsgState() {
      let msgType = this.message.messageObject.msgType
      if (msgType === 521) {
        this.state = -1;
        this.$emit('disableRightClick')
      }
    }, 
    openNew (arg) {
      this.$ipc.send('new-window-weburl', arg)
    },

    sendLink () {
       if (this.state !== 0) this.state = 0; // 防止消息发送失败 导致多次点击  多次发送 
       if (this.message.messageObject.msgType !== 9) {
         this.message.messageObject.msgType = 9
       }
       this.$Service.chat.sendMessage(this.message.messageObject, resp => {
        if (resp.code === 0) {
          const preMsgId = this.message.messageObject.msgId
          this.$store.commit('UPDATE_MSGID', { id: this.id, preMsgId: preMsgId, msgId: resp.msgId, isFail: this.isFail, time: resp.time })
          this.$emit('hasRead', resp.msgId)
          // if (this.message.messageObject.activeType === 1)  this.$emit('hasRead',  resp.msgId)
        } else { 
          // this.message.messageObject.localId = this.localId;
          this.state = -1; // code 不为0  消息发送失败  将其状态变为-1
          if (!this.isFail) {
            this.isFail = true;
          }
          if (this.$route.query.id !== this.message.messageObject.targetId) {
            this.$store.dispatch('CHANGE_CHAT_LIST_STATE', {id: this.message.messageObject.targetId, type: 2} )
          }
        }
      });
    }
  },
  data () {
    return {
      state: 0,
      defaultImg:  require('vrv-static/resources/images/message/web.png'),
      localId: 0,
      isFail: false
    };
  }
};
</script>
<style lang="scss" scoped>
@mixin ellipsis {
  overflow: hidden;
  text-overflow: ellipsis;
  -webkit-text-overflow: ellipsis;
  white-space: nowrap;
}
  .web-container-self {
    color: #fff!important;
      .web-title {
        color: #fff!important;
      }
      .web-description {
        color: #fff!important;
      }
  }
.web-container {
  width: 300px;
  height: 150px;
  display: flex;
  justify-content: center;
  flex-direction: column;
  padding: 10px;
  color: get-blue-color(accent-3);
  .links {
    width: 280px;
    // color: get-blue-color(accent-3);
    color: inherit;
    text-decoration: underline;
    @include ellipsis;
  }
  .web-info {
    flex: 1;
    display: flex;
    padding: 6px;
    border-bottom: solid 1px $--border-color-grey;
    .web-img {
      width: 70px;
      height: 70px;
    }
    .web-content {
      margin-left: 10px;
      flex: 1;
      display: flex;
      flex-direction: column;
      .web-title {
        width: 150px;
        @include ellipsis;
        color: #000;
      }
      .web-description {
        color:get-grey-color(base);
        font-size: $--font-size-small;
        width: 150px;
        max-height: 52px;
        display:-webkit-box;
        -webkit-line-clamp:3;
        -webkit-box-orient:vertical;
        overflow:hidden;
      }
    }
    // .web-content-mine{
    //   .web-title {
    //     color: #fff;
    //   }
    //   .web-description {
    //     color: #fff;
    //   }
    // }
  }
  .open-link {
    color: inherit;
    display: flex;
    justify-content: flex-end;
  }
}
</style>
