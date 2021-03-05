<template>
  <div class="chat-config" :data-type="chatUserInfo">
     <!-- 创建群聊 -->
    <div class="create-group-chat">
      <div class="invite-friend" v-if="contact_contactList[id]">
        <i class="icon add-icon" @click="isCreateGroup=true">&#xe66d;</i>
        <p>{{$t('chat.add')}}</p>
      </div>
      <div class="about-me">
        <v-avatar class="single-chat-avatar" size='is-small' :src='info.thumbAvatar' :sex="info.gender" :offline="false" shape="round" slot="leftAvatar"></v-avatar>
        <p class="nick-name">{{info.remark || info.name}}</p>
      </div>
    </div>
    <create-group v-if="isCreateGroup" :preSelectMemberIds="id" :isInviteMember="false" @close="isCreateGroup=false"></create-group>
    <!-- 分割线 -->
    <div class="row-divider"></div>
    <!-- 修改昵称 -->
    <div class="update-remark">
      <p class="nick-name">{{$t('chat.remark')}}</p>
      <input class="input is-primary remark-input" size="is-small" maxlength="20" type="text" :disabled="!contact_contactList[id]" v-model="chatNickName" @keyup.enter="modifyRemark" @blur="modifyRemark">
      <div class="suer-sett-loading" :style="{visibility:isEditLoading?'visible':'hidden'}">
        <i class="icon loading-start" v-if="!isEditFinished">&#xe6ac;</i>
        <i class="icon loading-success" v-else>&#xe632;</i>
      </div>
    </div>
    <!-- 分割线 -->
    <div class="row-divider"></div>
    <!-- 消息免打扰 -->
    <div class="block receive-chat" v-if="contact_contactList[id]">
      <v-switch class="disturb-switch" v-model="chatDisturbStatus">{{$t('groups.noDistrub')}}</v-switch>
    </div>
    <!-- 消息置顶 -->
    <div class="block chat-top" v-if="contact_contactList[id]">
      <v-switch class="top-switch" v-model="chatTopStatus">{{$t('groups.chatTop')}}</v-switch>
    </div>
    <div class="add-friend operation-button-box" v-else>
      <v-button class="theme-botton add-friend-button operation-button" type="is-primary" @click="addFriend">+ {{$t('contacts.buddy')}}</v-button>
    </div>

     <div class="clear-msg operation-button-box">
      <v-button class="clear-msg-button operation-button" type="is-primary" @click="clearMsg">{{$t('chat.clearMessage')}}</v-button>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import CreateGroup from '../../Group/CreateGroup'
import MsgMixin from '../msgMixin'
export default {
  data() {
    return {
      info: {},
      isCreateGroup: false,
      isEditLoading: false,
      isEditFinished: false,
      currentNickName: ''
    }
  },
  props: {
    id: String
  },
  mixins: [MsgMixin],
  computed: {
    ...mapGetters(['contact_contactList', 'chat_chatList', 'user_account']),
    /**
     * 会话当前免打扰状态
     * 0 3:免打扰
     */
    chatDisturbStatus: {
      get: function() {
        return this.chat_chatList[this.id].disturbSet === 3
      },
      set: function(newValue) {
        let isRepeat =
          (newValue ? 3 : 1) == this.chat_chatList[this.id].disturbSet
        if (isRepeat) return
        let updateContactInfoParam = {
          id: this.id,
          disturbSet: newValue ? 3 : 1
        }
        this.$Service.contact.updateContactInfo(
          updateContactInfoParam,
          resp => {
            if (resp.code === 0)
              this.$store.dispatch('UPDATE_CHATLIST', {
                id: this.id,
                disturbSet: updateContactInfoParam.disturbSet,
                disturbStatus: updateContactInfoParam.disturbSet
              })
          }
        )
      }
    },
    /**
     * 会话当前置顶状态
     * 0 1:置顶
     */
    chatTopStatus: {
      get: function() {
        return this.chat_chatList[this.id].isTop === 1
      },
      set: function(newValue) {
        let isRepeat = (newValue ? 1 : 0) == this.chat_chatList[this.id].isTop
        if (isRepeat) return
        let chatTopParam = {
          targetId: this.id,
          isTop: newValue
        }
        this.$Service.chat.chatTop(chatTopParam, resp => {
          if (this.chat_chatList[this.id].delSign === '')
            this.chat_chatList[this.id].isTop = newValue ? 1 : 0
        })
      }
    },
    /**
     * 当前会话用户信息（好友/陌生人）
     */
    chatUserInfo() {
      if (!this.contact_contactList[this.id])
        this.$Service.search.getUserInfo({ userId: this.id }, resp => {
          return this.info = resp.users
        })
      else return this.info = this.contact_contactList[this.id]
    },
    /**
     * 当前会话用户备注（无备注显示姓名）
     */
    chatNickName: {
      get: function() {
        return this.info.remark || this.info.name
      },
      set: function(newValue) {
        this.currentNickName = newValue
      }
    }
  },
  components: {
    CreateGroup
  },
  methods: {
    addFriend() {
      this.$dialog.prompt({
        message: this.$t('search.verfication'),
        confirmText: this.$t('common.sure'),
        cancelText: this.$t('common.cancel'),
        inputAttrs: { value:  this.$t('search.iAm') + this.user_account.name, maxlength: 60 },
        required: false, // 验证信息选填
        onConfirm: value => {
          let addContactParam = { userId: this.id, info: value }
          this.$Service.log(`添加好友请求Params${addContactParam}`)
          this.$Service.contact.addContact(addContactParam, resp => {
            this.$Service.log(`添加好友请求：code:${resp.code},id:${this.id}`)
            if (resp.code !== 0) {
              this.$toast.open({
                message: this.$t(`ErrorCode.${resp.code}`),
                type: 'is-danger'
              })
            } else {
              this.$Service.contact.getVerifyType({userId: this.id}, resp => {
                console.log('获取对方好友验证方式', resp)
                let verifyInfo = {
                  1: this.$t('groups.requestSent'),
                  3: this.$t('contacts.chatNow')
                }
                console.log(resp.type,verifyInfo[resp.type])
                this.$toast.open({message: verifyInfo[resp.type], type: 'is-success'})
              })
            }
          })
        }
      })
    },
    modifyRemark() {
      if (
        !this.currentNickName ||
        this.contact_contactList[this.id].remark == this.currentNickName
      )
        return
      this.contact_contactList[this.id].remark = this.currentNickName
      this.isEditLoading = true
      let info = {
        id: this.id,
        remark: this.currentNickName
      }
      this.$Service.contact.updateContactInfo(info, resp => {
        console.log('更新备注返回：' + JSON.stringify(resp))
        if (resp.code === 0) {
          this.isEditFinished = true
          setTimeout(() => {
            this.isEditFinished = false
            this.isEditLoading = false
          }, 1500)
        }
      })
    },

    // * 清空内容
    clearMsg() {
      this.deleteMessageById(this.id)
    }
  }
}
</script>
<style lang="scss">
.chat-config {
  flex:1; // fit xp
  padding: 0 15px;
  width: 200px;
  border-radius: $--border-radius-base;
  overflow: hidden;
  height: 100%;
  display: flex;
  flex-direction: column;
  background: #ffffff;
  align-items: center;
  border-left: 1px solid $--border-color-grey-lighten;
  font-size: $--font-size-mid;
  .row-divider {
    width: 100%;
    height: 1px;
    background: #eaeaea;
    margin: 20px 0;
  }
  .create-group-chat {
    display: flex;
    align-items: center;
    width: 100%;
    margin-top: 30px;
    .invite-friend {
      display: flex;
      flex-direction: column;
      align-items: center;
      .add-icon {
        font-size: 32px;
        height: 29px;
        padding-top: 1px;
        color: #ccc;
      }
    }
    .about-me {
      display: flex;
      flex-direction: column;
      text-align: center;
      margin-left: 15px;
      .single-chat-avatar {
        width: 30px;
        height: 30px;
      }
      .nick-name {
        @include ellipsis;
        width: 42px;
        margin-left: -5px;
      }
    }
  }
  .update-remark {
    width: 100%;
    display: flex;
    align-items: center;
    justify-content: center;
    .nick-name {
      flex: 1;
      display: flex;
      align-items: center;
      margin-right: 10px;
    }
    .remark-input {
      color: $--color-text-primary;
      font-family: inherit;
      outline: none;
      border: 1px solid $--border-color-grey;
      padding: 2px;
      border-radius: $--border-radius-base;
      height: 24px;
      box-sizing: border-box;
      font-size: 13px;
      flex: 2;
      display: flex;
      align-items: center;
    }
    .suer-sett-loading {
      margin: 0 2px;
    }
  }
  .block {
    width: 100%;
    margin-bottom: 0px;
  }
  .chat-top {
    margin-top: 15px;
  }
  .switch {
    margin-left: 0px;
    display: flex;
  }
  .clear-msg {
    margin-top: 10px;
    .clear-msg-button {
      background: #ff2500;
    }
  }
  .operation-button-box {
    width: 100%;
    .operation-button {
      width: 100%;
      font-size:  $--font-size-small;
    }
  }
}
</style>
