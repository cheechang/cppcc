<template>
  <div class="search-msg-record"  :class="{'msg-record-bg': !objectValues(this.messageList).length}">
    <msg-record-context v-if="isViewContext" :selectActive="selectActive" :chatType="chatType" :userInfo="userInfo" :isOpen="isOpen" :msgId="selectActive.msgId" :id="id" @close="isViewContext=false"></msg-record-context>
    <div class="search-msg-list" v-if="objectValues(this.messageList).length" ref="searchMsg">
      <div class="load-more-history-message" v-if=" isLoadHistoryMsg">
        <i class="timeicon icon">&#xe61f;</i>
        <a class="load-more-msg-btn" @click="$emit('LoadMoreMsg')">{{$t('chat.searchHistory')}}</a>
      </div>
      <div
        :class="`search-msg-list-item id_${isViewContext?'0':item.messageObject.msgId}`"
        v-for="(item, value, index) in messageList"
        :key="item.messageObject.time"
      >
        <!-- 消息发送时间 5分钟之内发送 不显示  -->
        <v-message
          :msgItem="item"
          round="round"
          :isSelectBg="item.messageObject.msgId==selectBgId"
          :isOpen="isOpen"
          :userInfo="userInfo"
          :id="id"
          :chatType="chatType"
          @rightClick="addMenu(item, $event)"
          :lastMsg="index!==0&&messageList[Object.keys(messageList)[index-1]]"
          :openMsgUnread="openMsgUnread"
        ></v-message>
      </div>
    </div>

    <msg-menu-operate
      v-if="isShowRightMenu"
      :selectActive="selectActive"
      :menuList="menuList"
      :id="id"
      :userInfo="userInfo"
      :currentPos="currentPos"

      :footerDivider ='footerDivider'
      :headDivider="headDivider"
      @view-content="setIsViewContext"
      @clearMenuList="menuList = []"
      @closeRightMenu="closeRightMenu"
      @deleteMsg="deleteMsgs"></msg-menu-operate>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import { msgStructure } from "../Msg";
import MsgMenuOperate from "../ChatContent/RightMenu";

export default {
  name: 'MsgList',
  data() {
    return {
      isShowRightMenu: false,
      // messageList: {},
      isShowContactList: false,
      selectMemberInfo: [],
      selectMemberIds: [],
      menuList: [],
      selectActive: {},
      currentPos: {
        // 记录右键列表的横纵坐标
        top: String,
        left: String
      },
      footerDivider: '',
      headDivider: '',
      isViewContext: false
    };
  },
  computed: {
    ...mapGetters(["user_account", "contact_contactList"])
  },
  props: {
    userInfo: Map | Function,
    id: String,
    chatType: Number,
    isOpen: Boolean,
    messageList: Object,
    isLoadHistoryMsg: Boolean,
    cancelGroupMsgTop: {
      type: Boolean,
      default: false
    },
    selectBgId: {
      type: String,
      default: '-1'
    },
    openMsgUnread: {
      default: true,
      type: Boolean
    }
  },
  components: {
    MsgMenuOperate,
    MsgRecordContext: resolve => require(['../ChatContent/ChatTabRecord/ChatMsgRecord/MsgRecordContext'], resolve)
  },
  beforeUpdate() {
    console.log('msglist updated...')
    this.handleScrollIntoView()
  },
  methods: {
    handleScrollIntoView() {
      setTimeout(() => {
        this.$nextTick(() => {
          console.log('this.isViewContext', this.isViewContext)
          if (!this.isViewContext) return;
          _.forEach(this.messageList, (element, index)=> {
            if (element.messageObject.msgId !== this.selectActive.msgId) return
            _.filter(this.$el.getElementsByClassName("search-msg-list-item"), (e, i) => {
              if (e.className.includes(index)) {  
                e.scrollIntoView(true);
              }
            })
          })
        })
      }, 500);
    },
    setIsViewContext() {
      this.isViewContext = true;
    },
    objectValues(obj) {
       return _.values(obj);
    },
    /** 右键删除消息 界面取消 */
    deleteMsgs(arg) {
      this.$delete(this.messageList, `id_${arg.msgId}`)
    },

    /**
     * @param {Number} type 右键类型 1 头像右键菜单 2 消息右键菜单
     * 头像右键菜单 单聊：添加好友（陌生人），查看资料 群聊：添加好友（陌生人），查看资料，@他
     * 消息右键菜单 删除 转发 5分钟之内支持撤回
     */
    addMenu(item, arg) {
      console.log('item', item)
      this.selectActive = item.messageObject
      if (arg.type === 1) { //头像右键菜单
        this.footerDivider = ''
        this.headDivider = ''
        this.menuList.push(this.$t('chat.detail'))  /** 查看资料 */
      
        if (!this.contact_contactList[item.messageObject.fromId]) {  /** 如果此人为陌生人 新增添加好友 */
          this.menuList.push(this.$t('organizations.addFriend'))
        }  
      } else { // 消息右键菜单
        if (this.selectBgId!=='-1') return
        if(!this.cancelGroupMsgTop){
          if (item.messageObject.preDefined && JSON.parse(item.messageObject.preDefined).RtcFile) return //文件直传不显示右键菜单
          if (this.isOpenAction) return // 组合消息
          this.footerDivider = this.$t('chat.delete')  // 尾部分组
          this.selectActive = item.messageObject
          if (this.selectActive.msgType === 2 && !arg.isSpecialMsg) {
            this.headDivider = this.$t('chat.copy')  // 头部分组
          }

          if (this.selectActive.msgType !== 3 && !arg.isSpecialMsg) {
            this.menuList.push(this.$t('chat.forward'))
          }

          if (this.selectActive.msgType === 6 && this.selectActive.defaultPath) {
            this.menuList.push(this.$t('chat.saveAs')); // 文件在默认路径时支持另存为
          }

          let personalInfo = this.userInfo[this.user_account.userId]
          if (this.selectActive.fromId === this.user_account.userId) {
            if (this.chatType === 2) {
              this.menuList.push(this.$t('chat.msgStatus'));
            } 
            console.log('personalInfo.memberType', personalInfo.memberType)
            if (Date.parse(new Date()) - this.selectActive.time < 300000 && personalInfo.memberType !== 2 && personalInfo.memberType !== 3) {
              this.menuList.push(this.$t('chat.Recall'));
            }
          }

          if (personalInfo.memberType === 2 || personalInfo.memberType === 3) {
            this.menuList.push(this.$t('chat.Recall'));
          }
          if (this.selectBgId!=='-1') this.menuList.splice(this.menuList.length, 1)
          else this.menuList.push(this.$t('chat.jump'))
        } else{
          if(this.userInfo[this.user_account.userId].memberType === 2 ||this.userInfo[this.user_account.userId].memberType === 3){
            this.menuList.push('取消置顶');
          }
        }
      }
      if(!this.menuList.length){
        return;
      }
      this.isShowRightMenu = true
      let minusWidth = 102

      console.log(minusWidth, arg.event.clientX + minusWidth, document.body.clientWidth)
      minusWidth =
        arg.event.clientX + minusWidth < document.body.clientWidth
          ? 0
          : minusWidth + 8
      this.currentPos.left = arg.event.clientX - minusWidth + 'px'
      console.log(this.currentPos.left, minusWidth)
      let addHeight = (this.menuList.length) * 33 + 16
      if (this.headDivider) addHeight += 33
      if (this.footerDivider) addHeight += 33
      addHeight =
        addHeight + arg.event.clientY < document.body.clientHeight
          ? 0
          : addHeight + 8

      this.currentPos.top = arg.event.clientY - addHeight + 'px'
    },

    closeRightMenu() {
      this.isShowRightMenu = false
      this.menuList=[]
      this.headDivider = ''
      this.footerDivider = ''
    },



  }
};
</script>
<style lang="scss">
.search-msg-record {
  flex: 1;
  display: flex;
  flex-direction: column;
  margin: 10px;
  // background: #f6f6f6;
  border-radius: 3px;
 
  &.msg-record-bg {
    background: url('~vrv-static/resources/images/common/nocontent.png') #fff 43% 43% no-repeat;
    background-size: 200px;
  }
  .load-more-history-message {
    text-align: center;
    color: get-blue-color(darken-4);
    font-size: $--font-size-small;
    .load-more-msg-btn {
      &:hover {
        text-decoration: underline;
        color: get-blue-color(darken-2);
      }
    }
  }
  .search-msg-list {
    flex: 1;
    margin-top: 10px;
    overflow: auto;
    .load-more-contach-message {
    }
  }
}
</style>
