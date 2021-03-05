<template>
  <div class="msg-record" :class="{'msg-record-bg': !objectValues(this.messageList).length}">
    <div class="msg-record-filed">
      <v-input
        class="msg-record-input"
        hasLine
        isAutoFocus
        :isBorder="false"
        v-model="inputSearch"
        :maxlength="24"
        :placeholder="$t('chat.filterHistory')"
        :position="'right'"
        @keyup-enter="searchFromNet"
      >
        <i v-if="inputSearch==''" class="icon" slot="expand">&#xe68c;</i>
      </v-input>
      <div class="msg-filter-condition" v-if="chatType === 2" :title="!isExpend ? $t('chat.expandFilter'):  $t('chat.closeFilter')" @click="isExpend=!isExpend">
        <i class="icon filter-icon" :class="{'filter-icon-transfer': isExpend}">&#xe69c;</i>
      </div>
    </div>
    <transition name="zoom-in-top">
      <div class="msg-filter-list" v-if="isExpend">
        <div class="msg-filter-item filter-at-msg v-ripple" @click="getAtMessage()">{{$t('chat.atMeMsg')}}</div>
        <div
          class="msg-filter-item filter-contact-msg v-ripple"
          @click.stop.self="openContactList"
        >{{$t('chat.sender')}}
          <tag
            class="filter-contact-msg-tag"
            v-for="(item,index) in selectMemberInfo"
            :key="index"
            :text="item.remark"
            color="#e0e0e0"
            @closetag="delSelectedMember(index, item)"
            :closable="true"
          >
            <v-avatar
              class="avatar-bg"
              size="is-small"
              :offline="false"
              shape="round"
              :src="item.thumbAvatar"
            />
          </tag>
        </div>
        <div class="filter-operate">
          <span class="filter-operate-btn filter-confirm v-ripple" @click="getContactMsg()">{{$t('common.sure')}}</span>
          <div class="column-divder"></div>
          <span class="filter-operate-btn v-ripple" @click="reset">{{$t('chat.resetFilter')}}</span>
        </div>
      </div>
    </transition>
    <msg-list
      :messageList="messageList"
      :isLoadHistoryMsg="isLoadHistoryMsg"
      @LoadMoreMsg="loadMoreHistoryMsg"
      :isOpen="isOpen"
      :userInfo="userInfo"
      :id="id"
      :chatType='chatType'
    ></msg-list>
    <msg-search-list 
      @close="isShowContactList = false"
      @search="searchFromGroupMember"
      @clearSelected="selectMemberIds=[], selectMemberInfo=[]"
      @handleSelectMemberIds="handleSelectMemberIds"
      :selectMemberIds="selectMemberIds"
      @completeSelect="completeSelect"
      v-if="isShowContactList"
      :userInfo="userInfo"
      :searchContactResult ='searchContactResult'
      @clearSearchList ='searchContactResult=[]'
      :memberList="memberList">
    </msg-search-list>
    
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import { msgStructure } from "../../../Msg";
import RecordContact from "../../RecordContact";
import MsgSearchList from '../../../Msg/MsgSearchList.vue'
import tag from "../../tag.vue";
import MsgMenuOperate from "../../RightMenu.vue";
import vClickOutside from '../../../v-click-outside/index.js'
import MsgList from "../../../Msg/MsgList.vue";
const SearchModel = {
  AtMessage: 1,
  SearchNet: 2,
  SearchContact: 3
};
export default {
  data() {
    return {
      inputSearch: "",
      isExpend: false,
      isShowRightMenu: false,
      messageList: {},
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
      isLoadHistoryMsg: false,
      filterModel: 2,
      searchMsgNextId: '',
      footerDivider: '',
      headDivider: '',
      isAutoShowMsgState: false,
      memberList: [],
      searchContactResult: []
      // userMaxReadId: ''
    };
  },
  computed: {
    ...mapGetters(["user_account", "contact_contactList"])
  },
  /**
   * 点击指令
   * 点击除元素自身外的区域 触发事件
   * 目前用于关闭区域
   */
  directives: {
    clickOutside: vClickOutside.directive
  },
  props: {
    userInfo: Map | Function,
    id: String,
    chatType: Number,
    isOpen: Boolean
  },
  components: {
    RecordContact,
    tag,
    MsgMenuOperate,
    MsgList,
    MsgSearchList
  },
  methods: {
    searchFromGroupMember(value) {
      console.log('value::', value)
      let groupSearchMemberParam = {
        groupId:this.$route.query.id,
        key:value
      }
      this.$Service.search.groupSearchMember(groupSearchMemberParam, resp=>{
        console.log('groupSearchMember::', resp)
        if(!resp.members){
          return 
        }
        this.searchContactResult = resp.members
      })
    },
    objectValues(obj) {
      return _.values(obj);
    },
    openContactList() {
      this.isShowContactList = true
      this.memberList = _.orderBy(this.userInfo, ["pinyin"], ["asc"])
    },
    /** 右键删除消息 界面取消 */
    deleteMsgs(arg) {
      this.$delete(this.messageList, `id_${arg.msgId}`)
    },

    /** 
     * 加载更多消息
     * SearchModel AtMessage 加载更多关于我的消息
     * SearchModel SearchNet 加载更多对应关键字历史消息
     * SearchModel contach    加载更多对应联系人历史消息
     * minMsgData 当前消息列表最小数据
     *  */
    loadMoreHistoryMsg() {
      const initNode = this.$el.getElementsByClassName("search-msg-list-item")[0];
      console.log('initNode::', initNode)
      let minMsgData = this.objectValues(this.messageList)[0].messageObject
      if (this.filterModel === SearchModel.AtMessage) {
        this.getAtMessage(minMsgData.time).then(() => {
          if (initNode === undefined) return;
          initNode.scrollIntoViewIfNeeded(false);
        });
      } else if (this.filterModel === SearchModel.SearchNet) {
        this.searchFromNet(this.searchMsgNextId, true).then(() => {
          if (initNode === undefined) return;
          initNode.scrollIntoViewIfNeeded(false);
        });
      } else {
        this.getContactMsg(minMsgData.msgId, true).then(() => {
          this.$nextTick(() => {
            if (initNode === undefined) return;
            initNode.scrollIntoViewIfNeeded(false);
          });
        });
      }
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
      }

      this.isShowRightMenu = true
      let minusWidth = 80

      minusWidth =
        arg.event.clientX + minusWidth < document.body.clientWidth
          ? 0
          : minusWidth + 8

      this.currentPos.left = arg.event.clientX - minusWidth + 'px'
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
      this.isAutoShowMsgState = false
    },
    /**
     * 主动删除
     * @param index 删除已选择列表索引
     * @param item  删除已选择列表数据
     */
    delSelectedMember(index, item) {
      console.log("index::", index, item.id);
      this.selectMemberInfo.splice(index, 1);
      this.selectMemberIds = this.selectMemberIds.filter(e => e != item.id);
      console.log("this.selectMemberIds", this.selectMemberIds);
    },

    handleSelectMemberIds(arg) {
      arg.type === 1
        ? this.selectMemberIds.push(arg.id)
        : this.selectMemberIds.splice(arg.id, 1);
    },

    /** 完成选择联系人 */
    completeSelect() {
      console.log("regSelectMember");
      this.selectMemberInfo = this.objectValues(this.userInfo).filter(
        e => this.selectMemberIds.indexOf(e.id) > -1
      );
    },

    /** 重置按钮 */
    reset() {
      this.messageList = {};
      this.selectMemberInfo = [];
      this.selectMemberIds = [];
      this.isLoadHistoryMsg= false;
      this.searchMsgNextId = ''
      this.inputSearch = ''
    },


    // /** 关闭筛选下拉列表 */
    // closefilterList(e) {
    //   console.log('e::', e)
    //   this.isExpend = false
    // },

    /** 获取联系人对应消息 */
    getContactMsg(msgId = "0", isLoadMore = false) {
      if (this.filterModel !== SearchModel.SearchContact || !isLoadMore) {
        this.messageList = {}
      }
      if (this.inputSearch) {
        this.inputSearch = ''
      }
      return new Promise(resolve => {
        this.filterModel = SearchModel.SearchContact;
        this.isExpend = false;
        if (!this.selectMemberIds.length) return;
        console.log("getContactMsg", this.selectMemberIds);
        let getMessagesParam = {
          targetId: this.id,
          count: 10,
          msgId: msgId,
          flag: 0,
          fromUserId: this.selectMemberIds
        };
        this.$Service.chat.getMessages(getMessagesParam, resp => {
          let contactMsg = Object.assign({}, resp);
        
          let obj = {};
          if (!contactMsg.msgs.length) return
          if (contactMsg.msgs.length < 10) {
            this.isLoadHistoryMsg = false;
          } else {
            this.isLoadHistoryMsg = true;
          }
          let unreadArray = []
          contactMsg.msgs.forEach(element => {
            if (element.unReadCount > 0) {
              this.$Service.log(`historyMsg has unReadCount in filter  msgId::: ${element.msgId}`)
              unreadArray.push({msgId:element.msgId, snapshotId: element.snapshotId})
            }
            this.$set(obj, `id_${element.msgId}`, msgStructure(element)); //构建不同的消息类型
          });
          this.messageList = Object.assign(obj, this.messageList);
          this.getGroupMsgUnreadCount(unreadArray)
          resolve();
          if (msgId === "0") {
            this.$nextTick(() => {
              // this.$refs.searchMsg.scrollTop = this.$refs.searchMsg.scrollHeight;
              let msgBox = this.$el.getElementsByClassName("search-msg-list")[0];
              console.log('msgBox', msgBox)
              msgBox.scrollTop = msgBox.scrollHeight;
            });
          }
        });
      });
    },


    /** 获取索关键字消息 */
    searchFromNet(msgId = '0', isLoadHistoryMsg = false) {
      if (this.inputSearch.trim() === '') {
        if(Object.keys(this.messageList).length) {
          this.messageList = {}
        }
        return 
      }
      
      if (this.filterModel !== SearchModel.SearchNet || !isLoadHistoryMsg) {
        this.messageList = {}
        if (this.selectMemberInfo.length) {
          this.selectMemberInfo = [];
          this.selectMemberIds = [];
        }
        this.searchMsgNextId = ''
        this.filterModel = SearchModel.SearchNet;
      }
      console.log("searchFromNet:::::", this.inputSearch);
      return new Promise(resolve => {
        let searchDetailMessageParam = {
          msgtype: 2,
          targetId: this.id,
          key: this.inputSearch,
          count: 10,
          messageId: msgId,
          start_time: '0',
          end_time: '0',
        };
        console.log("searchDetailMessageParam", searchDetailMessageParam);
        this.$Service.search.searchDetailMessage(
          searchDetailMessageParam,
          resp => {
            console.log("searchDetailMessage", resp);
            this.isExpend = false;
            let searchMsg = Object.assign({}, resp);
            if (!searchMsg.msgSearchResult.msgs.length) return
            this.searchMsgNextId = searchMsg.msgSearchResult.nextMsgId;
            if (searchMsg.msgSearchResult.msgs.length < 10) {
              this.isLoadHistoryMsg = false;
            } else {
              this.isLoadHistoryMsg = true;
            }
            let obj = {};
            let unreadArray = []
            searchMsg.msgSearchResult.msgs.forEach(element => {
              console.log('element', element)
              if (this.chatType === 2 && element.unReadCount > 0) {
                this.$Service.log(`historyMsg has unReadCount in filter  msgId::: ${element.msgId}`)
                unreadArray.push({msgId:element.msgId, snapshotId: element.snapshotId})
              }

              this.$set(obj, `id_${element.msgId}`, msgStructure(element)); //构建不同的消息类型
            });

            if (this.chatType === 1) {
              this.getUserMsgUnreadCount()
            }
            if (this.chatType === 2) {
              this.getGroupMsgUnreadCount(unreadArray)
            }
            this.messageList = Object.assign(obj, this.messageList);
            resolve();
            if (msgId !== '0') return
            this.$nextTick(() => {
              // this.$refs.searchMsg.scrollTop = this.$refs.searchMsg.scrollHeight;
              let msgBox = this.$el.getElementsByClassName("search-msg-list")[0];
              console.log('msgBox', msgBox)
              msgBox.scrollTop = msgBox.scrollHeight;
            });
          }
        );
      });
    },

    /** 获取@我的消息 */
    getAtMessage(endTime = 0) {
      console.log("getAtMessage::::");
      return new Promise(resolve => {
        let end_time = endTime === 0 ?  new Date().getTime().toString() : endTime
        if (this.filterModel !== SearchModel.AtMessage) {   // 清空渲染列表
          this.messageList = {}
          this.filterModel = SearchModel.AtMessage
          this.inputSearch = ''
        } 
        this.isExpend = false;
        // 清空选择列表
        if (this.selectMemberInfo.length) {
          this.selectMemberInfo = [];
          this.selectMemberIds = []
        }

        let getAtMessageParam = {
          atType: 0,
          beginTime: "0",
          endTime: end_time,
          groupID: this.id,
          maxCount: 10
        };

        this.$Service.chat.getAtMessage(getAtMessageParam, resp => {
          console.log("getAtMessage::", resp);
          
          let atMsg = Object.assign([], resp.msgs);
          if (!atMsg.length) return
          if (atMsg.length < 10) {
            this.isLoadHistoryMsg = false;
          } else {
            this.isLoadHistoryMsg = true;
          }
          let obj = {};
          let atMsgResult =  atMsg.reverse()
          atMsgResult.forEach(element => {
            this.$set(obj, `id_${element.msgId}`, msgStructure(element)); //构建不同的消息类型
          });
          this.messageList = Object.assign(obj, this.messageList);
          resolve();
          if (endTime) return
          this.$nextTick(() => {
            // this.$refs.searchMsg.scrollTop = this.$refs.searchMsg.scrollHeight;
            let msgBox = this.$el.getElementsByClassName("search-msg-list")[0];
            console.log('msgBox', msgBox)
            msgBox.scrollTop = msgBox.scrollHeight;
          });
        });
      });
    },

    // * 打开消息状态列表 ( 仅群 )
    openMsgStateList(arg) {
      this.isShowRightMenu = true
      this.isAutoShowMsgState = true 
      this.selectActive = arg
    },

    /**
     * getGroupMsgUnreadCount 获取群内消息已读未读
     * @param {String} groupId 群Id
     * @param {Array} snapShotInfos 消息的快照Id
     */
    getGroupMsgUnreadCount(unreadArray) {
      console.log('unreadArray', unreadArray)
      if (!unreadArray.length) return 
      let getGroupMsgUnreadCounterParam = {
        groupId: this.id,
        snapShotInfos: unreadArray
      }
      console.log('unreadArray', unreadArray)
      this.$Service.log(`getGroupMsgUnreadCounter:::: in filter   id: ${this.id}  length::${unreadArray.length}`)
      this.$Service.chat.getGroupMsgUnreadCounter(getGroupMsgUnreadCounterParam, resp=> {
        console.log('getGroupMsgUnreadCounter::', resp)
        let unReadCounter = Object.assign({}, resp)
        console.log('this.messageList', this.messageList)
          unReadCounter.msgs.forEach(e => {
            console.log('e', e)
            if (this.messageList && this.messageList[`id_${e.messageId}`]) {
              this.messageList[`id_${e.messageId}`].messageObject.maxUnReadCount = e.maxUnreadCount
              this.messageList[`id_${e.messageId}`].messageObject.unReadCount = e.unreadCount
              this.messageList[`id_${e.messageId}`].messageObject.snapshotId = e.snapshotId
            }
          })
      })
    },

    /**
     * getUserMsgUnreadCount 获取个人消息未读
     * @param {String} targetId 用户id
     */
    getUserMsgUnreadCount() {
      this.$Service.chat.getContractMaxReadId({targetId: this.id}, resp => {
        console.log('getContractMaxReadId', resp)
        if (resp.maxReadId === '0') return // 旧服务还不支持已读未读
        this.$Service.log(`userMaxReadId:::  in  filterMsg  ${resp.maxReadId}`)
        _.forEach(this.messageList, element => {
          console.log('element', element)
          if (element.messageObject.fromId === this.user_account.userId && element.messageObject.msgId <= resp.maxReadId && element.messageObject.maxUnReadCount === 0) {
            console.log('maxUnReadCount>>>>>')
            element.messageObject.maxUnReadCount = 1;
          }
        })
      })
    }
  }
};
</script>
<style lang="scss">
.msg-record {
  flex: 1;
  display: flex;
  flex-direction: column;
  margin: 10px;
  padding: 10px 30px;
  height: 70vh;
  // background: #f6f6f6;
  border-radius: 3px;
  overflow: auto;
  height: 100%;
 
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
  .msg-record-filed {
    display: flex;
    align-items: center;
    background: #fff;
    // box-shadow: $--box-shadow-base;
    .msg-record-input {
      flex: 1;
      .input {
        padding-left: 15px;
        font-size: 14px;
        // border: none !important;
      }
    }
    .msg-filter-condition {
      width: 36px;
      display: flex;
      background: #fff;
      height: 36px;
      align-items: center;
      justify-content: center;
      .filter-icon {
        @include font_color($--color-primary, "theme");
        margin-top: 16px;
        position: relative;
        margin-left: 14px;
        font-size: 18px;
        &.filter-icon-transfer {
          &:after {
            transform: rotate(-180deg);
            transition: all 0.2s ease-in 0.1s;
          }
        }
        &:after {
          border-left: 5px solid transparent;
          border-right: 5px solid transparent;
          border-top: 5px solid #ccc;
          content: "";
          position: relative;
          width: 0;
          transform: rotate(0deg);
          transition: all 0.2s ease-in 0.1s;
        }
      }
    }
  }
  .msg-filter-list {
    // border-top: solid 1px #ccc;
    box-shadow: $--box-shadow-base;
    @include z-index(menu);
    padding: 0px 14px 0px 14px;
    background: #fff;
    border-bottom-left-radius: 3px;
    border-bottom-right-radius: 3px;
    .msg-filter-item {
      min-height: 36px;
      display: flex;
      border-bottom: solid 1px #ccc;
      display: flex;
      flex-wrap: wrap;
      align-items: center;
      font-size: 12px;
      padding-left: 20px;
      &:hover {
        background: #f6f6f6;
      }
      &.filter-contact-msg {
        .filter-contact-msg-tag {
          margin: 4px;
          .v-chip__text {
            margin-left: 25px;
          }
          .avatar-bg {
            width: 20px;
            height: 20px;
            position: absolute;
          }
          .v-chip__close {
            font-size: 13px;
          }
        }
      }

    }
    .filter-operate {
      display: flex;
      font-size: 12px;
      padding: 0;
      justify-content: center;
      &:hover {
        background: none;
      }
      .column-divder {
        height: 26px;
        margin-top: 5px;
        width: 1px;
        background: #ccc;
      }
      .filter-operate-btn {
        flex: 1;
        display: flex;
        justify-content: center;
        align-items: center;
        height: 36px;
        &:hover {
          background: #f6f6f6;
        }
        &.filter-confirm {
          //  margin-right: 4px;
        }
      }
      
    }
  }
  // .search-msg-list {
  //   flex: 1;
  //   margin-top: 10px;
  //   overflow: auto;
  //   padding: 4px 16px;
  //   .load-more-contach-message {
  //   }
  // }
}
</style>
