<template>
  <div class="msg-status-list">
    <v-modal cardSize="msg-status-class" @close="$emit('close')">
      <v-tabs
        position="is-centered"
        v-model="currentTab"
        class="block member-list"
        size="contact-tab"
        @change="changeTab"
      >
        <div class="tab-list" v-for="(tabItem, index) in tabList" :key="index">
          <v-tab-item :label="tabItem.tabName">
            <!-- 已读/未读 tab -->
            <div class="read-list" ref="readlistbox" @scroll.passive.stop="handleScroll">
              <v-card-list class="status-list-box">
                <v-card
                  v-for="(item, index) in tabItem.list"
                  :key="index"
                  :title="item.remark || item.name"
                >
                  <v-avatar
                    size="is-small"
                    :src="item.thumbAvatar"
                    :sex="item.gender"
                    :offline="false"
                    shape="round"
                    slot="leftAvatar"
                  ></v-avatar>
                  <!-- <i class="icon has-at" v-if="isAt(item)" slot="rightAvatar">&#xe69e;</i>
                   -->
                   <div slot="rightAvatar" class="read-list-right-area">
                    <i class="icon has-at" v-if="isAt(item)">&#xe69e;</i>
                    <v-checkbox v-if="currentTab ===0 && isSelectMore" @change="isSelect => addItem(isSelect, item)" ></v-checkbox>
                   </div>
                </v-card>
              </v-card-list>
            </div>
          </v-tab-item>
        </div>
      </v-tabs>
      <!-- 按钮 追一下 -->
      <div class="modal-card-foot" slot="footer-bottom">
        <div v-if="!remindMsgSeconds">
          <!-- <v-button type="is-primary" v-if='isShowNudge' @click="remindMember" v-html="nudgeBtnContent"></v-button> -->
          <v-button @click="$emit('close')">{{$t('common.close')}}</v-button>
        </div>
        <div v-else class="count-down-time" v-html="getCountTime"></div>
      </div>
    </v-modal>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
export default {
  data() {
    return {
      currentTab: 0,
      tabList: [{ tabName: "未读", list: [] }, { tabName: "已读", list: [] }],
      readList: [],
      unreadList: [],
      readListIds: [],
      unReadListIds:[],
      relatedUsers: [],
      initLength: 10,
      isSelectMore:false,
      nudgeList: []
    };
  },

  mounted() {
    this.getRelateUsers() // 获取相关@人员列表
    this.getMsgUnreadInfo() // 获取消息已读未读信息
  },

  methods: {
    // * 获取相关@人员列表
    getRelateUsers() {
      if (this.selectActive.relatedUsers && this.selectActive.relatedUsers.length) {
        this.relatedUsers = this.selectActive.relatedUsers;
      }
    },

    /**
     * 获取消息已读未读状态
     * @param {String} msgId 该消息的Id
     * @param {String} snapshotId 该消息的快照Id
     */
    getMsgUnreadInfo() {
      let getGroupMsgUnreadInfoParam = {
        groupId: this.id,
        snapShotInfo: {
          msgId: this.selectActive.msgId,
          snapshotId: this.selectActive.snapshotId
        }
      };
      this.$Service.chat.getGroupMsgUnreadInfo(
        getGroupMsgUnreadInfoParam,
        resp => {
          console.log("getGroupMsgUnreadInfo", resp);
          this.$Service.log(`getGroupMsgUnreadInfo groupId:::${this.id} read.length ${resp.readIds.length}  unRead.length${resp.unReadIds.length}`);
          this.readListIds = resp.readIds;
          this.unReadListIds =  resp.unReadIds;

          // * 特殊处理 部分服务器已读列表包含自己
          if (this.readListIds.includes(this.user_account.userId)) {
             this.$Service.log( `readIds has own `);
             let index = _.findIndex(this.readListIds, id => {return id === this.user_account.userId} )
             this.readListIds.splice(index, 1)
          }
          // * 特殊处理 部分服务器维度列表包含自己
          if (this.unReadListIds.includes(this.user_account.userId)) {
             this.$Service.log( `unReadListIds has own `);
             let unReadindex = _.findIndex(this.unReadListIds, id => {return id === this.user_account.userId} )
             this.unReadListIds.splice(unReadindex, 1)
          }

          console.time("unReadIds start:::");
          this.unReadListIds.forEach(element => {
            if (this.userInfo[element]) {
              this.unreadList.push(this.userInfo[element]);
            } else {
              this.$Service.log( `getGroupMsgUnreadInfo no this members ${element}`);
            }
          });
          console.timeEnd("unReadIds start:::");
          
          this.tabList[0].list = this.unreadList.slice(0, this.initLength);
          this.tabList[0].tabName = `${this.$t("chat.unRead")}( ${this.unReadListIds.length} )`;
          this.tabList[1].tabName = `${this.$t("chat.read")}( ${this.readListIds.length} )`;
        }
      );
    },

    // * 监听滚动条
    handleScroll(e) {
      if (this.isScrollToBottom(this.$refs.readlistbox[this.currentTab])) { // 滚动条置底部
        console.log("to bottom");
        this.loadMoreList();
      }
    },

    // * 加载更多列表
    loadMoreList() {
      let currentList = this.currentTab === 0 ? this.unreadList : this.readList;
      if (this.initLength >= currentList.length) return;
      let num = 20;
      if (this.initLength + num > currentList.length) {
        num = currentList.length - this.initLength;
      }
      this.initLength += num;
      console.log("this.initLength", this.initLength);
      this.tabList[this.currentTab].list = currentList.slice(0, this.initLength);
    },

    /**
     * 判断滚动条滚动到底部
     * @param {*} el - 绑定的dom元素
     * @returns - 是/否
     */
    isScrollToBottom(el) {
      let [scrollTop, offsetHeight, scrollHeight] = [el.scrollTop, el.offsetHeight, el.scrollHeight];
      return !(scrollTop + offsetHeight < scrollHeight);
    },

    /**
     * 判断是否@了该成员
     * @param {Object} item 列表的每一项
     */
    isAt(item) {
      if (!this.relatedUsers.length) return;
      return this.relatedUsers.includes(item.id);
    },

    /**
     * 切换已读消息、未读消息
     * @param {Number} value - 当前切换的tab页
     */
    changeTab(value) {
      if (!this.readListIds.length) return;
      this.initLength = this.tabList[value].list.length;
      if (value === 1 && !this.tabList[1].list.length) {
        this.initLength = 10;
        console.time("readListIds start:::");
        this.readListIds.forEach(element => {
          // console.log('element::', this.userInfo[element], element)
          if (this.userInfo[element]) {
            this.readList.push(this.userInfo[element]);
          } else {
            this.$Service.log(`getGroupMsgUnreadInfo readlist no this members ${element}`);
          }
        });
        console.timeEnd("readListIds start:::");
        this.tabList[1].list = this.readList.slice(0, this.initLength);
      }
    },

    /** 追一追功能 */
    remindMember() {
      if (this.currentTab) return
      if (this.nudgeList.length) {
        this.$dialog.confirm({
          title: this.$t("chat.nudge"),
          confirmText: this.$t("common.sure"),
          cancelText: this.$t("common.close"),
          message: this.$t("chat.sendMessage"),
          onConfirm: () => {
            console.log("this.unreadList", this.nudgeList);
            this.$Service.chat.sendShortMessage(this.nudgeList, resp => {
              console.log("sendShortMessage", resp);
              this.$Service.log(`sendShortMessage code::${resp.code}`)
              if (resp.code === 0) {
                this.$signalMonitor.$emit("countDownRemind");
              }
            });
          }
        });
      } else {
        this.isSelectMore = true
      }
     
      // this.$dialog.confirm({
      //   title: this.$t("chat.nudge"),
      //   confirmText: this.$t("common.sure"),
      //   cancelText: this.$t("common.cancel"),
      //   message: this.$t("chat.sendMessage"),
      //   onConfirm: () => {
      //     this.$Service.chat.sendShortMessage(this.unreadList, resp => {
      //       console.log("this.unreadList", this.unreadList);
      //       console.log("resp", resp);
      //       if (resp.code === 0) this.$signalMonitor.$emit("countDownRemind");
      //     });
      //   }
      // });
    },

    // * 添加追一下成员
    addItem(isChecked, item) {
      if (isChecked) {
        this.nudgeList.push(item.id)
      } else {
        this.nudgeList = this.nudgeList.filter(id => id !== item.id)
      }
    }
  },
  computed: {
    getCountTime() {
      let minute = parseInt(this.remindMsgSeconds / 60);
      let second = parseInt(this.remindMsgSeconds % 60);
      return this.$t('chat.msgTimeStatus', {
        min: minute,
        sec: second
      }) 
    },

    // * 是否显示追一下
    isShowNudge() {
      return this.user_webLinkParse && this.user_webLinkParse !== 'ol' && this.currentTab === 0
    },

    nudgeBtnContent() {
      return !this.isSelectMore ? this.$t('chat.nudge') : this.$t('contacts.send')
    },
    ...mapGetters([
      "contact_contactList",
      "contact_groupList",
      "user_account",
      "chat_chatContent",
      "chat_chatList",
      'user_webLinkParse'
    ])
  },
  props: {
    selectActive: Object,
    userInfo: Object,
    remindMsgSeconds: Number,
    id: String
  }
};
</script>
<style lang="scss" >
.msg-status-class {
  width: 270px;
  height: 450px;
  display: flex;
  .tabs {
    margin-top: 6px;
  }
  .member-list {
    flex: 1;
    display: flex;
    flex-direction: column;
    background: whitesmoke;
    .tab-content {
      margin-top: 6px;
      height: 340px;
      // overflow: auto;
    }
    .read-list {
      height: 340px;
      overflow-x: hidden;
      overflow-y: auto;
      .read-list-right-area {
       display: flex;
        width: 45px;
        position: relative;
        justify-content: flex-end;
        align-items: center;
      }
        .has-at {
          position: absolute;
          left: 0px;
          top: 1px;
          height: 100%;
          display: flex;
          align-items: center;
          align-self: center;
          color: #FF5252;
          font-size: 16px;
          /* justify-content: flex-end; */
          /* width: 100%; */
          margin-right: 3px;
        }
    }
    .card {
      &:hover {
        background: none;
      }
    }
  }
  // .msg-status-footer{
  //   height: 50px;
  //   display: flex;
  //   justify-content: center;
  //   padding: 0px 40px;
  //   margin-bottom: 15px;
  //  .status-option-btn{
  //    flex: 1;
  //    .cancel{
  //      border:  solid 1px #000!important;
  //    }
  //  }
  // }

  .modal-card-foot {
    width: 100%;
    border: none;
    border-top: solid 1px $--border-color-grey;
    display: flex;
    // background: #fff;
    padding: 15px 20px;
    justify-content: center;
    .button {
      width: 90px;
      height: 30px;
    }
    .button:not(:last-child) {
      margin-right: 30px;
    }
    .count-down-time {
      font-size: $--font-size-small;
      color: $--color-msg-prompt-danger;
    }
  }
  .modal-card-body {
    flex: 1;
    overflow: hidden;
    padding: 10px;
  }
}
</style>
