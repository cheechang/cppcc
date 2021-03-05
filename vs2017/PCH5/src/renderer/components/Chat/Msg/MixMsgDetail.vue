<template>
  <v-modal cardSize="mix-msg-class" @close="$emit('close')">
    <div class="modal-card-head mix-msg-head" slot="header-top">
      <!-- <p class="modal-card-title mix-msg-title">{{chat_chatList[id].name}}</p> -->
      <p class="modal-card-title mix-msg-title">{{$t('chat.compositionMsg')}}</p>
      <i class="icon" @click="$emit('close')">&#xe603;</i>
    </div>
    <div class="mix-msg-session">
      <div class="msg-detail-item" v-for="(item, index) in orderByItemTime" :key="index">
        <div class="item-head">
          <v-avatar :src="getCurrentAvatar(item)" :sex="item.userSex||0" shape="round" size="is-small"></v-avatar>
          <p class="item-head-name">{{item.userName}}</p>
          <p class="item-head-time">{{getMsgTime(item)}}</p>
        </div>
        <div class="msg-body">
          <component :is="currentViews(item)" class="item-content" :message='getMsgItem(item)' :id="item.toID+''" :isMixMsg="true" :mixMsgId="mixMsgId" :mixTargetId='id'></component>
        </div>
      </div>
    </div>
  </v-modal>
</template>
<script>
import { mapGetters } from 'vuex';
import { getDateDiff } from '../../../../comm/time';
import { msgStructure } from '../Msg';
// import _ from 'lodash';
import {
  MsgTypeText,
  MsgTypeMap,
  MsgTypeImage,
  MsgTypeUnknow,
  MsgTypeFile,
  MsgTypeTemplate,
  MsgTypeImgtext,
  MsgTypeWeak,
  MsgTypeWebLink,
  // MsgTypeForward,
  MsgTypeRetract,
  MsgTypeMixText,
  MsgTypeAudio,
  MsgTypeCard,
  MsgDynamicExp,
  MsgTypeVideo,
  MsgTypeMicroVideo,
  MsgTypeNineImgs,
  MsgTypeRemind

} from './index'
export default {
  props: {
    msgItem: Array,
    id: Number|String,
    mixMsgId: String,
  },
  data() {
    return {
      mixList: {}
    }
  },
  computed: {
    ...mapGetters(['contact_contactList']),
    orderByItemTime() {
      return _.orderBy(this.msgItem,['time'],['asc']);
    }
  },
  methods: {
    getCurrentAvatar({fromId}) {
      if (!this.contact_contactList[fromId]) {
        this.$Service.search.getUserInfo({ userId: fromId }, resp=>{
          this.$set(this.mixList, fromId, resp.users.thumbAvatar)
        })
      } else {
        this.$set(this.mixList, fromId, this.contact_contactList[fromId].thumbAvatar)
      }
      return this.mixList[fromId]
    },
    getMsgTime({time}) {
      return getDateDiff(parseInt(time));
    },
    /**
     * 对组合消息的每条消息进行重构
     */
    getMsgItem(msgItem) {
      // msgItem.flag = 2;
      let result = msgStructure(msgItem);
      return result;
    },
    currentViews(item) {
      let type = item.msgType & 0x00ff ? item.msgType & 0x00ff : item.msgType & 0xff00;
      switch (type) {
        case 2: {
          return MsgTypeText
          break
        }
        case 3: {
          return MsgTypeAudio
          break
        }
        case 4: {
          return MsgTypeMap
          break
        }
        case 5: {
          return MsgTypeImage
          break
        }
        case 7: {
          return MsgTypeCard
          break
        }
        case 6: {
          return MsgTypeFile
          break
        }
        case 9: {
          return MsgTypeWebLink
          break
        }
        case 12: {
          return MsgTypeImgtext
          break
        }
        case 14: {
          return MsgTypeVideo
          break
        }
        case 18: {
          return MsgTypeRetract
          break
        }
        case 19: {
          return MsgDynamicExp
          break
        }
        case 26: {
          return MsgTypeTemplate
          break
        }
        case 28: {
          return MsgTypeNineImgs
          break
        }
        case 89: {
          return MsgTypeMicroVideo
          break
        }
        case 256: {
          return MsgTypeFile
          break
        }
        default: {
          return MsgTypeUnknow
          break
        }
      }
      if(type === 26 && item.subType === 1){
        return MsgTypeRemind
      }
    }
  },
  components: {
    MsgTypeText,
    MsgTypeMap,
    MsgTypeImage,
    MsgTypeUnknow,
    MsgTypeFile,
    MsgTypeWeak,
    MsgTypeTemplate,
    MsgTypeNineImgs,
    MsgTypeImgtext,
    MsgTypeWebLink,
    // MsgTypeForward,
    MsgTypeRetract,
    MsgDynamicExp,
    MsgTypeVideo,
    MsgTypeRemind
  }
}
</script>
<style lang="scss">
.mix-msg-class {
  height: 500px;
  width: 530px;
  border-radius: $--border-radius-base;
  overflow: hidden;
  background: #ffffff;
  .mix-msg-head {
    height: 20px;
    background: #f0f0f0;
    border-bottom: none;
    .mix-msg-title {
      font-size:$--font-size-mid;;
      color: #000;
    }
    .icon {
      font-size:$--font-size-mid;;
      margin-right: -15px;
    }
  }
  .mix-msg-session {
    height: 100%;
    color: #363636;
    padding: 10px 30px;
    overflow-y: auto;
    background: #fff;
    .msg-detail-item {
      border-bottom: 1px solid $--border-color-grey-lighten;
      margin-top: 15px;
      .item-head {
        display: flex;
        align-items: center;
        .item-head-name {
          margin-left: 8px;
          display: flex;
          align-items: center;
        }
        .item-head-time {
          text-align: right;
          flex: 1;
        }
        p {
          font-size:$--font-size-mid;;
        }
      }
      .msg-body {
        display: flex;
        .item-content {
          margin: 15px 48px;
          background: #f5f5f7 100%;
          color: #000;
          box-shadow:$--box-shadow-rd;
          max-width: 400px;
          min-width: 60px;
          display: flex;
          justify-content: center;
          word-wrap: break-word;
          word-break: break-all;
          position: relative;
          border-radius: $--border-radius-msg;
          font-weight: 500;
          font-size: 0.85rem;
        }
      }
    }
  }
}
</style>

