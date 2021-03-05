<template>
  <div class="chat-group-config" v-if="isGroupSetExpend">
    <slot></slot>
    <!-- 消息免打扰 -->
    <div class="block">
      <v-switch :title="$t('groups.noDistrub')" :value="chatDisturbStatus" :disabled="isDisturbDisabled" @input="args=>handleSwitch(args, 0)">{{ $t('groups.noDistrub') }}</v-switch>
      <load-animal :style="{visibility:chatDisturbLoadStart?'visible':'hidden'}" :loadFinished="chatDisturbLoadFinished"></load-animal>
    </div>
    <!-- 消息置顶 -->
    <div class="block">
      <v-switch :title="$t('groups.chatMsgTop')" :value="chatTopStatus" :disabled="isTopDisabled" @input="args=>handleSwitch(args, 1)">{{ $t('groups.chatMsgTop') }}</v-switch>
      <load-animal :style="{visibility:chatTopLoadStart?'visible':'hidden'}" :loadFinished="chatTopLoadFinished"></load-animal>
    </div>
    <!-- 阅后即焚（群主3/管理员2）Y（普通成员1）N -->
    <!-- <div class="block" v-if="selfInfo.memberType!==1">
      <v-switch :title="$t('groups.allowBurn')" :value="chatBurnStatus" :disabled="isBurnDisabled" @input="args=>handleSwitch(args, 2)">{{ $t('groups.allowBurn') }}</v-switch>
      <load-animal :style="{visibility:chatBurnLoadStart?'visible':'hidden'}" :loadFinished="chatBurnLoadFinished"></load-animal>
    </div> -->
    <!-- 密聊（群主3/管理员2）Y（普通成员1）N  -->
    <!-- <div class="block" v-if="selfInfo.memberType!==1">
      <v-switch :title="$t('groups.allowPrivate')" :value="chatPrivateStatus" :disabled="isPrivateDisabled" @input="args=>handleSwitch(args, 3)">{{ $t('groups.allowPrivate') }}</v-switch>
      <load-animal :style="{visibility:chatPrivateLoadStart?'visible':'hidden'}" :loadFinished="chatPrivateLoadFinished"></load-animal>
    </div> -->
    <!-- 私聊（群主3/管理员2）Y（普通成员1）N  -->
    <!-- <div class="block" v-if="selfInfo.memberType!==1">
      <v-switch :title="$t('groups.noChatInGroup')" :value="chatStrangerStatus" :disabled="isStrangerDisabled" @input="args=>handleSwitch(args, 4)">{{$t('groups.noChatInGroup')}}</v-switch>
      <load-animal marginClass="load-style" :style="{visibility:chatStrangerLoadStart?'visible':'hidden'}" :loadFinished="chatStrangerLoadFinished"></load-animal>
    </div> -->
    <!-- 群允许被搜索（群主3/管理员2）Y（普通成员1）N  -->
    <div class="block" v-if="selfInfo.memberType!==1">
      <v-switch :title="$t('groups.allwoSearched')" :value="groupSearchedStatus" :disabled="isSearchedDisabled" @input="args=>handleSwitch(args, 5)">{{$t('groups.allwoSearched')}}</v-switch>
      <load-animal marginClass="load-style" :style="{visibility:chatSearchedLoadStart?'visible':'hidden'}" :loadFinished="chatSearchedLoadFinished"></load-animal>
    </div>
    <div class="clear-msg">
      <v-button class="clear-msg-button" type="is-primary" @click="clearMsg">{{$t('chat.clearMessage')}}</v-button>
    </div>
    <div class="quit-group">
      <v-button class="quit-group-button" type="is-primary" v-if="canQuitGroup" @click="quitGroup">{{groupOperation}}</v-button>
    </div>

  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import LoadAnimal from './LoadAnimal';
import MsgMixin from '../../Chat/msgMixin';
import GroupMixin from '../../Group/GroupMixin';
export default {
  props: {
    id: String,
    selfInfo: Object
  },
  components: {
    LoadAnimal
  },
  mixins: [MsgMixin, GroupMixin],
  data() {
    return {
      isGroupSetExpend: false,
      /**
       * 为了禁止用户同时点击操作123开关按钮
       * 1.阅后即焚 2.密聊 3.陌生人聊天
       * 快速操作多个开关按钮时由于执行结果回调顺序问题导致数据紊乱
       */
      isBurnDisabled: false,
      isPrivateDisabled: false,
      isStrangerDisabled: false,
      isSearchedDisabled: false,

      isDisturbDisabled: false,
      isTopDisabled: false,
      // 免打扰动画
      chatDisturbLoadStart: false,
      chatDisturbLoadFinished: false,
      // 置顶动画
      chatTopLoadStart: false,
      chatTopLoadFinished: false,
      // 阅后即焚动画
      chatBurnLoadStart: false,
      chatBurnLoadFinished: false,
      // 密聊动画
      chatPrivateLoadStart: false,
      chatPrivateLoadFinished: false,
      // 陌生人禁止私聊动画
      chatStrangerLoadStart: false,
      chatStrangerLoadFinished: false,
      // 群允许被搜索动画
      chatSearchedLoadStart: false,
      chatSearchedLoadFinished: false,
      canQuitGroup: true,
    }
  },
  computed: {
    ...mapGetters([
      'chat_chatList',
      'contact_groupExtension',
      'contact_groupList',
      'contact_groupSearchingList'
    ]),
    groupOperation() {
      return this.selfInfo.memberType===3?this.$t('groups.disband'):this.$t('groups.leave')
    },
    // 免打扰
    chatDisturbStatus() {
      return this.chat_chatList[this.id].disturbSet === 3
    },
    // 置顶
    chatTopStatus() {
      return this.chat_chatList[this.id].isTop === 1
    },
    // 阅后即焚
    chatBurnStatus() {
      return (
        this.contact_groupExtension[this.id] &&
        this.contact_groupExtension[this.id].burnMsg &&
        this.contact_groupExtension[this.id].burnMsg === '1'
      )
    },
    // 密聊
    chatPrivateStatus() {
      return (
        this.contact_groupExtension[this.id] &&
        this.contact_groupExtension[this.id].privateMsg &&
        this.contact_groupExtension[this.id].privateMsg.toString() === '1'
      )
    },
    // 私聊
    chatStrangerStatus() {
      return (
        this.contact_groupExtension[this.id] &&
        this.contact_groupExtension[this.id].disallowStrangerChat &&
        this.contact_groupExtension[this.id].disallowStrangerChat.toString() !== '0'
      )
    },
    // 群允许被搜索状态
    groupSearchedStatus() {
      return this.contact_groupSearchingList[this.id] || false;
    }
  },
  beforeDestroy() {
    this.$signalMonitor.$off('expendGroupSet', this.setExpend)
  },
  created() {
    this.$signalMonitor.$on('expendGroupSet', this.setExpend)
    let extend = this.contact_groupExtension[this.id]
    if (extend && extend.privateMsg && extend.isSelfDestruct && extend.disallowStrangerChat) return
    this.getIsPrivateMode()
  },
  methods: {
    handleSwitch(isCheck, index) {
      let chatStatus = {
        0: () => setTimeout(() => {this.setChatDistrub(isCheck)}, 0),
        1: () => setTimeout(() => {this.setChatTop(isCheck)}, 0),
        2: () => setTimeout(() => {this.setChatBurn(isCheck)}, 0),
        3: () => setTimeout(() => {this.setChatPrivate(isCheck)}, 0),
        4: () => setTimeout(() => {this.setChatStranger(isCheck)}, 0),
        5: () => setTimeout(() => {this.setAllowSearched(isCheck)}, 0)
      }
      chatStatus[index].call(this)
    },
    /**
     * 设置群免打扰
     */
    setChatDistrub(newValue) {
      console.log("chat_list:::",this.chat_chatList[this.id])
      // 避免vuex改变时，数据同步更新，会调用接口重复设置群信息
      let isRepeat =
        (newValue ? 3 : 1) == this.chat_chatList[this.id].disturbSet
      if (isRepeat) return
      this.chatDisturbLoadStart = true
      this.chatDisturbLoadFinished = false
      this.setDisabled(true)
      let setGroupMsgRemindTypeParam = {
        groupId: this.id,
        mode: newValue ? 3 : 1
      }
      this.$Service.group.setGroupMsgRemindType(
        setGroupMsgRemindTypeParam,
        resp => {
          this.chatDisturbLoadFinished = true
          setTimeout(() => {
            this.chatDisturbLoadStart = false
            this.setDisabled(false)
          }, 800);
          if (resp.code === 0)
            this.$store.dispatch('UPDATE_CHATLIST', {
              id: this.id,
              disturbSet: setGroupMsgRemindTypeParam.mode,
              disturbStatus: setGroupMsgRemindTypeParam.mode
            })
        }
      )
    },
    /**
     * 设置群置顶
     */
    setChatTop(newValue) {
      let isRepeat = (newValue ? 1 : 0) === this.chat_chatList[this.id].isTop;
      if (isRepeat) return
      this.chatTopLoadStart = true
      this.chatTopLoadFinished = false
      this.setDisabled(true)
      let chatTopParam = {
        targetId: this.id,
        isTop: newValue
      }
      this.$Service.chat.chatTop(chatTopParam, resp => {
        this.chatTopLoadFinished = true
        setTimeout(() => {
          this.chatTopLoadStart = false
          this.setDisabled(false)
        }, 800);
        if (this.chat_chatList[this.id].delSign === '')
          this.chat_chatList[this.id].isTop = newValue ? 1 : 0
      })
    },
    /**
     * 设置群阅后即焚
     */
    setChatBurn(newValue) {
      let isRepeat =
        (newValue ? '1' : '0') == this.contact_groupExtension[this.id].burnMsg
      if (isRepeat) return
      this.chatBurnLoadStart = true
      this.chatBurnLoadFinished = false
      this.setDisabled(true)
      let groupInfoParma = {
        groupId: this.id,
        extendProperties: JSON.stringify({
          isSelfDestruct: newValue ? '1' : '0',
          privateMsg: this.chatPrivateStatus ? '1' : '0',
          disallowStrangerChat: this.chatStrangerStatus ? '1': '0'
        })
      }
      this.$Service.group.setGroupInfo(groupInfoParma, resp => {
        this.chatBurnLoadFinished = true
        setTimeout(() => {
          this.chatBurnLoadStart = false
          this.setDisabled(false)
        }, 800);
        if (resp.code !== 0) {
          let errorInfo = this.$t(`ErrorCode.${resp.code}`)
          this.$toast.open({
            message: `${this.$t('groups.editGroupSettings')}: ` + errorInfo,
            type: 'is-danger'
          })
        }
      })
    },
    /**
     * 设置群密聊
     */
    setChatPrivate(newValue) {
      let isRepeat =
        (newValue ? '1' : '0') ==
        this.contact_groupExtension[this.id].privateMsg
      if (isRepeat) return
      this.chatPrivateLoadStart = true
      this.chatPrivateLoadFinished = false
      this.setDisabled(true)
      let groupInfoParma = {
        groupId: this.id,
        extendProperties: JSON.stringify({
          privateMsg: newValue ? '1' : '0',
          isSelfDestruct: this.chatBurnStatus ? '1' : '0',
          disallowStrangerChat: this.chatStrangerStatus ? '1': '0'
        })
      }
      this.$Service.group.setGroupInfo(groupInfoParma, resp => {
        this.chatPrivateLoadFinished = true
        setTimeout(() => {
          this.chatPrivateLoadStart = false
          this.setDisabled(false)
        }, 800);
        if (resp.code !== 0) {
          let errorInfo = this.$t(`ErrorCode.${resp.code}`)
          this.$toast.open({
            message: `${this.$t('groups.editGroupSettings')}: ` + errorInfo,
            type: 'is-danger'
          })
        }
      })
    },
    /**
     * 设置群内陌生人禁止聊天
     */
    setChatStranger(newValue) {
      let isRepeat =
        (newValue ? '1' : '0') ==
        this.contact_groupExtension[this.id].disallowStrangerChat
      if (isRepeat) return
      this.chatStrangerLoadStart = true
      this.chatStrangerLoadFinished = false
      this.setDisabled(true)
      let groupInfoParma = {
        groupId: this.id,
        extendProperties: JSON.stringify({
          disallowStrangerChat: newValue ? '1' : '0',
          isSelfDestruct: this.chatBurnStatus ? '1' : '0',
          privateMsg: this.chatPrivateStatus ? '1' : '0',
        })
      }
      this.$Service.group.setGroupInfo(groupInfoParma, resp => {
        this.chatStrangerLoadFinished = true
        setTimeout(() => {
          this.chatStrangerLoadStart = false
          this.setDisabled(false)
        }, 800);
        if (resp.code !== 0) {
          let errorInfo = this.$t(`ErrorCode.${resp.code}`)
          this.$toast.open({
            message: `${this.$t('groups.editGroupSettings')}: ` + errorInfo,
            type: 'is-danger'
          })
        }
      })
    },
    // 设置群是否允许被搜索
    setAllowSearched(newValue) {
      let isRepeat = this.contact_groupSearchingList[this.id] && newValue === this.contact_groupSearchingList[this.id];
      if (isRepeat) {
        return;
      }
      this.chatSearchedLoadStart = true;
      this.chatSearchedLoadFinished = false;
      this.setDisabled(true);
      let groupInfoParma = {
        groupId: this.id,
        groupSearch: newValue ? 1 : 2
      }
      console.log('setGroupInfo param', groupInfoParma);
      this.$Service.group.setGroupInfo(groupInfoParma, resp => {
        console.log('setGroupInfo-searching-resp', resp);
        this.chatSearchedLoadFinished = true
        setTimeout(() => {
          this.chatSearchedLoadStart = false
          this.setDisabled(false)
        }, 800);
        if (resp.code !== 0) {
          let errorInfo = this.$t(`ErrorCode.${resp.code}`)
          this.$toast.open({
            message: `${this.$t('groups.editGroupSettings')}: ` + errorInfo,
            type: 'is-danger'
          })
        } else {
          this.$store.commit('SET_GROUPSEARCHING', {id: this.id, status: newValue});
        }
      })
    },
    setDisabled(status) {
      this.isDisturbDisabled = status;
      this.isTopDisabled = status;
      this.isBurnDisabled = status;
      this.isPrivateDisabled = status;
      this.isStrangerDisabled = status;
      this.isSearchedDisabled = status;
    },
    setExpend() {
      this.isGroupSetExpend = !this.isGroupSetExpend;
    },
    getIsPrivateMode() {
      console.log('getIsPrivateMode method......')
      this.$Service.group.getGroupInfo({ groupId: this.id }, resp => {
        console.log('getIsPrivateMode',resp);
        let groupInfoExtends = resp.info;
        if(groupInfoExtends.groupType == 'eid' || groupInfoExtends.groupType == 'org'){
          console.log('议政群，org禁止退群')
          this.canQuitGroup = false
        }
        // let extendJson = resp.extend && JSON.parse(resp.extend);
        // let [isPrivateMsg, isBurnMsg, isDisallowStrangerChat] = [
        //   (extendJson && extendJson.privateMsg) || '0',
        //   (extendJson && extendJson.isSelfDestruct) || '0',
        //   (extendJson && extendJson.disallowStrangerChat) || '0'
        // ]
        this.$store.commit('SET_GROUP_EXTENSION', {
          id: this.id,
          extendInfo: { 
            burnMsg: '0', 
            privateMsg: '0', 
            disallowStrangerChat: '0' 
          }
        })
      })
    },
    clearMsg() {
      this.deleteMessageById(this.id)
    },
    quitGroup() {
      let isOwner = this.selfInfo.memberType===3; // 群主(y)/成员(n)
      this.$dialog.confirm({
        message: isOwner 
          ? this.$t('groups.toDisband', {value: this.contact_groupList[this.id].groupName})
          : this.$t('groups.toLeave', {value: this.contact_groupList[this.id].groupName}),
        confirmText: isOwner ? this.$t('groups.disband') : this.$t('groups.leave'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          let removeGroupParam = { groupId: this.id, type: isOwner ? 1 : 2 }
          this.$Service.group.removeGroup(removeGroupParam, resp => {
            console.log('removeGroup', resp)
            if (resp.code !== 0) {
              let errorInfo = this.$t(`ErrorCode.${resp.code}`)
              this.$toast.open({
                message: `${isOwner ? this.$t('groups.disband') : this.$t('groups.leave')}${this.$t('groups.group')}：` + errorInfo,
                type: 'is-danger'
              })
            }else{
              this.deleteGroupLocalTone(removeGroupParam.groupId);
            }
          })
        }
      })
    }
  }
}
</script>
<style lang="scss">
.chat-group-config {
  .block {
    width: 100%;
    font-size: 14px;
    margin-bottom: 15px;
    display: flex;
    white-space: nowrap;
    align-items: center;
    &:last-child {
      margin-bottom: 0px;
    }
    .load-style {
      margin: 0px -1px;
    }
  }
  .switch {
    margin-left: 0px;
    display: flex;
    &[disabled] {
      opacity: 1;
      color:#4a4a4a;
    }
  }
  .quit-group {
    .quit-group-button {
      width: 100%;
      font-size:  $--font-size-small;
      background: #ff2500;
    }
  }
  .clear-msg {
    margin-bottom: 8px;
    .clear-msg-button {
      width: 100%;
      font-size:  $--font-size-small;
      background: #ff2500;
    }
  }
}
</style>

