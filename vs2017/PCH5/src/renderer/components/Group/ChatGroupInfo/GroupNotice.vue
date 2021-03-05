<template>
<div class="chat-group-notice">
  <v-modal cardSize="notice-class" @close="$emit('close')">
    <div class="modal-card-head" slot="header-top">
      <p class="modal-card-title">{{$t('groups.groupNotice')}}</p>
      <i class="icon" @click="$emit('close')">&#xe603;</i>
    </div>
    <div class="notice-content">
      <v-input
        class="notice-input"
        type="textarea"
        v-model="noticeInfo"
        :disabled="!isGroupLeader"
        :isBorder="false"
        :maxlength="1000"
      ></v-input>
    </div>
    <div class="notice-publish" v-if="isGroupLeader">
      <v-button class="publish-btn" type="is-primary" @click="publishNotice">{{$t('groups.publishNotice')}}</v-button>
    </div>
  </v-modal>
</div>
</template>
<script>
import { mapGetters } from 'vuex'
import { MsgTxt, msgStructure } from '../../Chat/Msg'
export default {
  data() {
    return {
      noticeInfo: ''
    }
  },
  props: {
    isGroupLeader: Boolean,
    id: String,
    noticeContent: String
  },
  computed: {
    ...mapGetters(['user_account','chat_chatContent'])
  },
  mounted() {
    this.noticeInfo = this.noticeContent;
  },
  methods: {
    publishNotice() {
      this.noticeInfo = (this.noticeInfo && this.noticeInfo.trim());
      if (!this.noticeInfo) return;
      let setGroupInfoParam = {
        groupId: this.id,
        groupBulletin: this.noticeInfo
      };
      this.$Service.group.setGroupInfo(
        setGroupInfoParam,
        resp => {
          if(resp.code!==0) return;
          this.sendMsgAtAll()
        }
      );
    },
    sendMsgAtAll() {
      let msg = {
        targetId: this.id,
        fromId: this.user_account.userId,
        msgType: 2,
        body: `@${this.$t('chat.allMem')} ${this.noticeInfo}`,
        relatedUsers: [this.id],
        // time: new Date().getTime()
      }
      let msgtxt = new MsgTxt(msg, 1)
      this.$Service.chat.sendMessage(msgtxt.messageObject, resp => {
        this.$Service.log(`sendMessage::: ${JSON.stringify(resp)}`)
        msgtxt.messageObject.msgId = resp.msgId;
        let newMsg = msgStructure(msgtxt.messageObject);
        if (this.chat_chatContent[msgtxt.messageObject.targetId]) {
          this.$store.dispatch('SET_CHATCONTENT', newMsg);
        }
        this.$emit('close', this.noticeInfo);
      })
    }
  }
}
</script>
<style lang="scss">
.chat-group-notice {
  .notice-class {
    width: 340px;
  }
  .modal-card-head {
    height: 20px;
    // background: #ffffff;
    border-bottom: none;
    .modal-card-title {
      font-size: 14px;
    }
    .icon {
      font-size: 14px;
      margin-right: -15px;
    }
  }
  .modal-card-body {
    padding: 0 20px 20px !important;
    border-bottom-left-radius: 6px;
    border-bottom-right-radius: 6px;
    .notice-content {
      display: flex;
      flex-direction: column;
      padding: 20px 0 8px;
      .notice-input {
        textarea {
          border: none;
          box-shadow: none;
          min-height: 68px;
          resize: none;
          padding: 0px;
          color: #363636;
          background: #fff;
        }
      }
    }
    
    .notice-publish {
      display: flex;
      justify-content: flex-end;
      .publish-btn {
        background: #87D087;
        height: 30px;
        font-size: 14px;
        width: 68px;
      }
    }
  }
}
</style>

