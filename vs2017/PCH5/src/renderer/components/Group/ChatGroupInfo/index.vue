<template>
  <!-- <div> -->
  <div class="chat-group-info">
    <d-skeleton >
      <div class="container" v-if="isLoadFinished">
        <div class="group-notice" :style="getPadding">
          <div
            class="notice-title"
            @click="isGroupSetExpend=!isGroupSetExpend;$signalMonitor.$emit('expendGroupSet')"
          >
            <p>{{ $t('groups.groupSet') }}</p>
            <i
              class="icon theme-txt groupset-icon"
              :class="{'expend-icon': isGroupSetExpend}"
            >&#xe6a9;</i>
          </div>
          <chat-group-config :id="id" :selfInfo="selfInfo">
            <!-- <div class="profile">
                <group-notice v-if="isShowGroupNotice" :id="id" :isGroupLeader="selfInfo.memberType==2||selfInfo.memberType==3" :noticeContent="noticeContent" @close="setGroupNotice"></group-notice>
                <div class="notice-edit" @click="isShowGroupNotice=!isShowGroupNotice">
                  <i class="icon notice-icon">&#xe6b9;</i>
                  <p class="notice-brief" :title="noticeContent" v-html="noticeNewContent"></p>
                </div>
            </div>-->
            <div class="row-divider"></div>
            <config-input :id="id" :isGroupLeader="selfInfo.memberType==2||selfInfo.memberType==3"></config-input>
            <div class="row-divider"></div>
            <!-- <group-sound
              :toneInfo="getCurrentToneInfo"
              @setSound="setSound"
              :toneTopLoadStart="toneTopLoadStart"
              :toneLoadFinished="toneLoadFinished"
            ></group-sound> -->
            <!-- <div class="row-divider"></div> -->
          </chat-group-config>
        </div>
        <div class="group-drawer">
          <div class="group-member-search">
            <v-input
              v-model="memberSearch"
              :placeholder="$t('groups.search')"
              size="is-small"
              :position="memberSearch==''?'left':'right'"
              @input="searchGroupMember"
            >
              <i v-if="memberSearch==''" class="icon icon-search" slot="expand">&#xe68c;</i>
              <i v-else class="icon right" slot="expand" @click="clearSearch">&#xe650;</i>
            </v-input>
          </div>
          <div class="add-member">
            <span class="member-info">{{ $t('groups.members',{value: chatObject.length}) }}</span>
            <!-- <span class="member-btn" v-if="isPermitInvite">
              <i class="icon" @click="isAddFriendModal=true">&#xe8a1;</i>
            </span> -->
          </div>
          <invite-group-member
            v-if="isAddFriendModal"
            :isInviteMember="true"
            :groupInfo="groupInfo.info"
            @close="isAddFriendModal=false"
          ></invite-group-member>
          <group-member-info></group-member-info>
          <div
            class="group-list"
            ref="box"
            @scroll.passive.stop="showPosition"
            v-if="isSearchFinished"
          >
          <d-skeleton>
            <v-card-list
              class="group-item"
              @menuClick="groupMenuClick"
              :menuList="groupMenu"
              size="menu-size"
              itemSize="35"
              v-if="isShowList"
            >
              <v-card
                class="card-item"
                v-for="(value,index) in searchChatObject&&searchChatObject.slice(0, searchPageNum)||chatObject.slice(0, pageNum)"
                :index="value.id"
                :key="index"
                :title="getRealName(value)"
                @mouse-enter="(e, index)=>extraUserInfoCard(e, index, value)"
                @mouse-leave="activeIndex==-1"
                @dbClick="isStartChat(value, 1)"
                @contextmenu="setGroupMemberMenu(value)"
              >
                <group-info-card slot="extra" class="user-card" :userId="value.id"></group-info-card>
                <v-avatar
                  slot="leftAvatar"
                  class="group-avatar"
                  size="is-small"
                  :src="value.thumbAvatar"
                  :sex="value.gender"
                  :offline="false"
                  shape="round"
                ></v-avatar>
                <lazy-scroll v-if="root" :viewport="root" slot="left">
                  <!-- <online :onlineItem="groupOnlineList[value.id]"></online> -->
                   <online :itemId="value.id"></online>
                </lazy-scroll>
                <i
                  slot="after"
                  class="icon member-icon"
                  v-if="memberTypeIcon[value.memberType]"
                  v-html="memberTypeIcon[value.memberType]"
                ></i>
              </v-card>
            </v-card-list>
            <chat-group-skeleton slot="skeleton" type="list"></chat-group-skeleton>
          </d-skeleton>
            <!-- <v-button class="is-loading is-large" :ripple="false" v-else></v-button> -->
          </div>
        </div>
      </div>
      <chat-group-skeleton slot="skeleton" type="info"></chat-group-skeleton>
    </d-skeleton>

    <!-- <v-button class="is-loading is-large" :ripple="false" v-else></v-button> -->
  </div>
  <!-- </div> -->
</template>
<script>
import Vue from "vue";
import _ from "lodash";
import { mapGetters } from "vuex";
import inviteGroupMember from "../CreateGroup.vue";
import GroupMemberInfo from "./MemberInfo";
import ContactMixin from "../../Contact/ContactMixin";
import GroupMixin from "../../Group/GroupMixin";
import ChatGroupConfig from "./ChatGroupConfig";
import ConfigInput from "./ConfigInput.vue";
// import GroupSound from "./GroupSound.vue";
import LazyScroll from "../../Common/LazyScroll";
import Online from "../../Common/Online";
import GroupNotice from "./GroupNotice";
import config from "../../../../comm/config.js";
import { converseFullPinYin } from "../../../../comm/pinyin.js";
import { isWinXp } from "../../../../comm/is";
import ChatGroupSkeleton from './ChatGroupSkeleton';
export default {
  mixins: [ContactMixin, GroupMixin],
  data() {
    return {
      // 已废弃
      isPermitSearch: false,
      // 群成员列表
      chatObject: [],
      // 群信息
      groupInfo: {
        info: Object
      },
      // 首次加载群成员个数
      pageNum: 100,
      noticeImg: require("vrv-static/resources/images/contact/notice.png"),
      // isLoadFinished: false,
      // 群右键菜单
      groupMenu: null,
      // 群成员信息
      groupItem: {},
      // 是否邀请群成员/创建群
      isAddFriendModal: false,
      // 卡片位置  已废弃
      position: "",
      // 已废弃
      topValue: 0,
      // 群数据加载完成后显示列表
      isShowList: false,
      // 鼠标滑动选中项
      activeIndex: -1,
      // 已废弃
      isMemberInfoShow: false,
      // 已废弃
      memberItem: {},
      // 是否允许邀请群成员
      isPermitInvite: false,
      // 我的群信息详情
      selfInfo: {},
      // 群搜索内容
      memberSearch: "",
      // 群搜索结果
      searchChatObject: null,
      // 群搜索
      isSearchFinished: true,
      // 首次加载群搜索成员个数
      searchPageNum: 100,
      // 群成员在线状态集合
      groupOnlineList: {},
      // 群成员类型：管理员，群主
      memberTypeIcon: {
        2: "&#xe61b;",
        3: "&#xe748;"
      },
      root: null,
      // 展开群设置
      isGroupSetExpend: true,
      // 编辑群公告
      isShowGroupNotice: false,
      noticeContent: "",
      noticeNewContent: "",
      // 设置提示音动画
      toneTopLoadStart: false,
      toneLoadFinished: false
    };
  },
  props: {
    hasNav: Boolean,
    id: String,
    isLoadFinished: Boolean
  },
  computed: {
    ...mapGetters([
      'chat_objectInfo',
      'chat_sortArrayInfo',
      'chat_objectSortInofObject',
      'chat_shouldUpdate',
      'contact_contactList',
      'contact_groupExtension',
      'contact_groupOnlineStateList',
      'user_groupToneList'
    ]),
    allowChat() {
      let extend = this.contact_groupExtension[this.$route.query.id];
      return (
        extend &&
        extend.disallowStrangerChat &&
        extend.disallowStrangerChat == 0
      );
    },
    // fit xp add by lxy
    getPadding() {
      if (isWinXp) {
        return { padding: "0px 13px" };
      } else {
        return { padding: "13px" };
      }
    },
    //getCurrentToneInfo(){
      // if(this.$route.name === "ChatRightArea" && this.id === this.$route.query.id && this.isGroupSetExpend){
      //   console.log("当前群的提示音为：", this.user_groupToneList[this.$route.query.id] || "push6")
      //   let toneInfo = this.user_groupToneList[this.$route.query.id] && this.formatToneInfo(this.user_groupToneList[this.$route.query.id]);
      //   switch (toneInfo) {
      //     case 'push1': return 'push1'
      //     break;
      //     case 'push2': return 'push2'
      //     break;
      //     case 'push3': return 'push3'
      //     break;
      //     case 'push4': return 'push4'
      //     break;
      //     case 'push5': return 'push5'
      //     break;
      //     default: return 'push6'
      //   }
      // }
    //}
  },
  mounted() {
    setTimeout(() => {
      this.initData(this.id);
      this.getIsPermitInvite(this.id);
      this.getGroupSoundFromSDK(this.id);
      // 暂时不用骨架屏 屏蔽
      if (this.$config.account.openOnlineStatus) {
        this.root = this.$parent.$el;
      }
    }, 0);
  },
  watch: {
    $route(val) {
      if (this.id === this.$route.query.id) {
        this.initData(this.id);
      }
    },
    isShowList(val) {
      val && this.getGroupInfo();
    },
    chat_objectInfo(val) {
      if (this.$route.query.id != this.id && this.$route.query.id != 10000)
        return;
      this.initData(this.id, true);
    }
  },
  components: {
    Online: resolve => require(["../../Common/Online"], resolve),
    LazyScroll,
    GroupMemberInfo,
    inviteGroupMember,
    ChatGroupConfig,
    GroupNotice,
    ConfigInput,
    GroupInfoCard: resolve => {
      require(["./GroupInfoCard.vue"], resolve);
    },
    // GroupSound,
    ChatGroupSkeleton
  },
  methods: {
    initData(id) {
// 现方案
      let isUpdate = Array.from(this.chat_shouldUpdate).includes(this.id);
      console.log('是否需要更新:', isUpdate ? '需要' : '不需要');
      console.time("order>>>");
      console.log('this.chat_objectInfo',this.chat_objectInfo[id])
      if (!isUpdate && this.chat_objectSortInofObject[id] && this.chat_objectSortInofObject[id].length>0) {
        this.chatObject = this.chat_objectSortInofObject[id];
        console.log('群-》群成员',this.chat_objectSortInofObject,id)
        console.log('群成员数组：：：：：：',this.chatObject,this.chat_objectInfo)
      } else {
        console.log('进入重新排序')
        this.chatObject = _.orderBy(//方法库中的排序
          this.chat_objectInfo[id],["memberType",val => {
              return converseFullPinYin(val.pingyin.trim());
            }],["desc", "asc"]
        );
        this.$store.dispatch('SET_CHAR_SORTINFO', {id, sortArray: this.chatObject});
        this.$store.commit('SET_SHOULDUPDATE', this.id);
        console.log('新排序数组存入vuex')
        console.log('this.chat_objectInfo',this.chat_objectInfo[id])
      }
      if( this.chatObject.length>0){
        this.groupInfo.info.createrId = this.chatObject[0].id;
        this.selfInfo = this.chat_objectInfo[this.id][this.user_account.userId];
      }
      this.isShowList = true;
      console.timeEnd("order>>>");
// 原方案
      // console.time("order>>>");
      // this.chatObject = _.orderBy(
      //   this.chat_objectInfo[id],
      //   [
      //     "memberType",
      //     val => {
      //       return converseFullPinYin(val.pingyin.trim());
      //     }
      //   ],
      //   ["desc", "asc"]
      // );
      // console.log("this.chatObject[0]:::", this.chatObject[0]);
      // this.groupInfo.info.createrId = this.chatObject[0].id;
      // this.selfInfo = this.chat_objectInfo[this.id][this.user_account.userId];
      // this.isShowList = true;
      // console.timeEnd("order>>>");
    },
    getIsPermitInvite(id) {
      this.$Service.group.getGroupSet({ groupId: id }, resp => {
        console.log(`群内是否允许邀请好友${JSON.stringify(resp)}`);
        let obj = this.chatObject.filter(e => e.id == this.user_account.userId);
          console.log("memberType:", obj[0].memberType);
        this.isPermitInvite = resp.is_allow === 1 || obj[0].memberType != 1;
      });
    },
    /**
     * 群卡片（这里可能会导致列表滚动卡顿:1.渲染子组件卡顿 2.监听鼠标移入移出时修改子组件数据卡顿）
     */
    extraUserInfoCard(e, index, { remark, thumbAvatar, gender, contactRemark }) {
      // 目前处理卡顿方案：如果scrolltop没改变的话，认为列表正在滚动，不加载卡片
      // if (this.topValue !== 0 && this.topValue === this.$refs.box.scrollTop) {
      //   this.topValue = 0;
      //   return;
      // }
      let position = e.clientY;
      if (e.clientY > document.body.clientHeight - 50)
        position = document.body.clientHeight - 55;
      this.$signalMonitor.$emit("sendPosition", {
        position,
        activeIndex: index,
        remark: (contactRemark && contactRemark.trim()) || remark,
        thumbAvatar,
        gender
      });
      // this.position = e.clientY;
      // this.activeIndex = index;
    },
    //滚动条滚动触发
    showPosition() {
      // if(this.isScrollToBottom(this.$refs.box)) {
      //   if (this.chat_objectInfo[this.$route.query.id].size <= this.pageNum) return;
      //   this.pageNum += 100;
      // }
      if (this.isScrollToBottom(this.$refs.box)) {
        if (!this.searchChatObject) {
          if (
            _.values(this.chat_objectInfo[this.$route.query.id]).length <=
            this.pageNum
          )
            return;
          this.pageNum += 100;
        } else {
          if (this.searchChatObject.length <= this.searchPageNum) return;
          this.searchPageNum += 100;
        }
      }
    },
    // 获取群信息
    getGroupInfo() {
      this.$Service.group.getGroupInfo(
        { groupId: this.$route.query.id },
        resp => {
          console.log("获取群信息：", resp);
          this.groupInfo = resp;
          // 将群允许被搜索状态存入vuex
          this.$store.commit('SET_GROUPSEARCHING', {id: this.$route.query.id, status: resp.isSearch});
          this.noticeContent = this.groupInfo.bulletin || this.$t("groups.noGroupNotice");
          this.handleNoticeUrl();
        }
      );
      if(this.user_groupToneList){
        console.log('state',this.user_groupToneList,this.$route.query.id)
        let  state= this.user_groupToneList[this.$route.query.id];
        console.log('state',state)
        if(!state){
          // 若vuex中没有则调用网络接口去获取
          this.getGroupSoundFromSDK(this.$route.query.id);
        }
      }
    },
    //右键设置事件
    groupMenuClick(menuName, menuIndex, itemIndex) {
      if (menuName === this.$t("groups.alias")) {
        this.changeNickName();
      } else if (menuName.indexOf(this.$t("groups.admin")) > -1) {
        this.setPermission();
      } else if (menuName === this.$t("groups.removeMember")) {
        this.removeMember();
      } else if (menuName === this.$t("groups.ownership")) {
        this.transferGroup();
      }
    },
    /**
     * 根据右键菜单所选Item类型，更新菜单项
     * 右键时获取自己权限，可以同步群成员操作时权限的改变（设置管理员/转让群）
     */
    setGroupMemberMenu(value) {
      this.groupItem = value;
      console.log(this.user_account.userId, value.id);
      if (this.user_account.userId !== value.id) {
        // 不是右键选中自己
        this.groupMenu = null;
        let memberActions = new Map([
          [
            /^3$/,
            () => {
              // 群主：所有权限
              console.log("我是群主......");
              this.groupMenu = [
                this.$t("groups.ownership"),
                this.$t("groups.removeMember"),
                value.memberType == 2
                  ? this.$t("groups.removeAdmin")
                  : this.$t("groups.setAdmin")
              ];
            }
          ],
          [
            /^2$/,
            () => {
              // 管理员：移除普通成员权限
              console.log("我是管理员......");
              if (value.memberType === 1)
                this.groupMenu = [this.$t("groups.removeMember")];
            }
          ],
          [
            /[^2-3]+$/,
            () => {
              // 普通成员：无权限
              console.log("我是普通成员......");
            }
          ]
        ]);
        [...memberActions]
          .filter(([key, value]) => key.test(this.selfInfo.memberType))
          .forEach(([key, value]) => value.call(this));
      } else {
        // 右键选中自己
        this.groupMenu = [this.$t("groups.alias")];
      }
    },
    // 删除群成员
    removeMember() {
      this.$dialog.confirm({
        confirmText: this.$t("common.sure"),
        cancelText: this.$t("common.cancel"),
        message: this.$t("groups.toRemoveMember", {
          value: this.groupItem.remark
        }),
        onConfirm: () => {
          let removeMemberParam = {
            groupId: this.$route.query.id,
            userId: this.groupItem.id
          };
          this.$Service.group.removeMember(removeMemberParam, resp => {
            console.log("成功移除群成员:", resp);
          });
        }
      });
    },
    // 设置管理员
    setPermission() {
      this.$dialog.confirm({
        confirmText: this.$t("common.sure"),
        cancelText: this.$t("common.cancel"),
        message:
          this.groupItem.memberType === 2
            ? this.$t("groups.toRemoveAdmin", { value: this.groupItem.remark })
            : // : '确认设置 ' + this.groupItem.remark + ' 为管理员?',
              this.$t("groups.toSetAdmin", { value: this.groupItem.remark }),
        onConfirm: () => {
          let memberInfo = {
            groupId: this.$route.query.id,
            id: this.groupItem.id,
            memberType: this.groupItem.memberType === 2 ? 1 : 2
          };
          this.$Service.group.setMemberInfo(memberInfo, resp => {
            console.log("管理员设置(撤销)成功:", resp);
          });
        }
      });
    },
    // 修改昵称
    changeNickName() {
      this.$dialog.prompt({
        confirmText: this.$t("common.sure"),
        cancelText: this.$t("common.cancel"),
        inputAttrs: {
          placeholder: this.getRealName(this.groupItem),
          maxlength: 20,
          value: this.getRealName(this.groupItem)
        },
        required: false,
        onConfirm: value => {
          let memberInfo = {
            groupId: this.$route.query.id,
            id: this.groupItem.id,
            remark: value
          };
          this.$Service.group.setMemberInfo(memberInfo, resp => {
            console.log("设置群成员昵称:", resp);
          });
        }
      });
    },
    // 转让群
    transferGroup() {
      this.$dialog.confirm({
        confirmText: this.$t("common.sure"),
        cancelText: this.$t("common.cancel"),
        message: this.$t("groups.toTransferOwner", {
          value: this.groupItem.remark
        }),
        onConfirm: () => {
          let transferGroupParam = {
            groupId: this.$route.query.id,
            userId: this.groupItem.id
          };
          this.$Service.group.transferGroup(transferGroupParam, resp => {
            console.log("转让群成功:", resp);
          });
        }
      });
    },
    /**
     * 群卡片展示
     */
    expendInfoShow(value) {
      this.memberItem = value;
      this.isMemberInfoShow = true;
    },
    /**
     * 群成员搜索
     */
    searchGroupMember(value) {
      if (value.trim() === "") {
        this.searchChatObject = null;
        this.pageNum = 100;
        return;
      }
      this.isSearchFinished = false;
      this.searchPageNum = 100;
      let groupSearchMemberParam = {
        groupId: this.$route.query.id,
        key: value
      };
      this.$Service.search.groupSearchMember(groupSearchMemberParam, resp => {
        console.log("群成员搜索", resp);
        this.searchChatObject = resp.members;
        setTimeout(() => {
          this.isSearchFinished = true;
        }, 0);
      });
    },
    clearSearch() {
      this.memberSearch = "";
    },
    isStartChat(value, type) {
      if (!(this.allowChat || this.contact_contactList[value.id])) return;
      this.startChat(value, type);
    },
    setGroupNotice(notice) {
      this.isShowGroupNotice = false;
      if (!notice) return;
      // this.groupInfo.bulletin = notice;
      this.noticeContent = notice;
      this.handleNoticeUrl();
    },
    handleNoticeUrl() {
      let regUrl = /(http|ftp|https|www):\/\/[\w\-_]+(\.[\w\-_]+)+([\w\-.,@?^=%&:/~+#]*[\w\-@?^=%&/~+#])?/g;
      if (regUrl.test(this.noticeContent)) {
        this.noticeNewContent = this.noticeContent.replace(
          regUrl,
          (a, b, c) =>
            `<a class='notice-url' @click='e=>this.$ipc.send('new-window-weburl', e.target.computedName)'>${a}</a>`
        );
      } else {
        this.noticeNewContent = this.noticeContent;
      }
    },
    setSound(toneInfo) {
      this.toneTopLoadStart = true;
      this.toneLoadFinished = false;
      this.setGroupTone(this.$route.query.id, toneInfo)
        .then(() => {
          this.toneLoadFinished = true;
          setTimeout(() => {
            this.toneTopLoadStart = false;
          }, 800);
          let toneInfoList = {...this.user_groupToneList};
          this.$set(toneInfoList, this.$route.query.id, toneInfo);
          this.$store.dispatch("SET_GROUPTONES", toneInfoList);
          return this.updateGroupToneToLocal(toneInfoList);
        })
        .catch(() => {
          this.$toast.open({
            duration: 3000,
            message: this.$t("groups.setGroupToneFailed"),
            position: "is-top",
            type: "is-error"
          });
        })
    },
    getRealName(value) {
      // 优先级：好友备注>群备注>原名称
      // console.log('name::', value);
      return (value.contactRemark && value.contactRemark.trim()) || value.remark.trim() || value.name;
    }
  }
};
</script>
<style lang="scss">
.chat-group-info {
  width: 200px;
  border-radius: $--border-radius-base;
  background: #ffffff;
  overflow: hidden;
  // height: 100%;
  display: flex;
  flex-direction: column;
  .container {
    width: 100%;
    display: flex; //fit xp
    flex-direction: column;
    flex: 1; //fit xp
    height: 100%;
    margin: 0;
    background: #ffffff;
    border-left: 1px solid $--border-color-grey-lighten;
    .group-notice {
      font-size: 14px;
      padding: 13px;
      border-bottom: 1px solid $--border-color-grey-lighten;
      .notice-title {
        color: $--color-black;
        height: 30px;
        line-height: 30px;
        display: flex;
        align-items: center;
        justify-content: space-between;
        cursor: pointer;
      }
      .groupset-icon {
        font-size: 12px;
        color: #bdbdbd;
        transform: rotate(-90deg);
        transition: 0.5s;
      }

      .expend-icon {
        transform: rotate(90deg);
        transition: 0.5s;
      }
      .profile {
        @include get-grey-color(darken-2);
        height: 76px;
        display: flex;
        align-items: center;
        .profile-img {
          user-select: none;
          -webkit-user-drag: none;
        }
        .notice-edit {
          cursor: pointer;
          max-height: 60px;
          overflow: hidden;
          display: flex;
          height: 100%;
          .notice-icon {
            font-size: 42px;
            margin: 20px 18px 0 8px;
          }
          .notice-brief {
            // display: flex;
            flex-direction: column;
            justify-content: center;
            line-height: 60px;
          }
        }
      }
      .row-divider {
        width: 100%;
        height: 1px;
        background: #eaeaea;
        margin: 15px 0;
      }
      .block {
        width: 100%;
        font-size: 14px;
        margin-bottom: 15px;
        &:last-child {
          margin-bottom: 0px;
        }
      }
      .switch {
        margin-left: 0px;
        display: flex;
      }
    }
    .group-drawer {
      width: 100%;
      height: 100%;
      flex: 1;
      display: flex;
      flex-direction: column;
      .group-member-search {
        height: 25px;
        margin: 13px 18px 0px 13px;
        input {
          border-radius: $--border-radius-large;
          box-shadow: none;
        }
        .icon {
          pointer-events: all;
          height: 25px;
          top: 1px;
          // 之前适配XP时加入18px的margin,影响正常客户端，暂时屏蔽,后续适配时特殊处理
          // margin-right: 18px;
        }
        .right{
          right: 0px;
        }
        .icon-search {
          left: 0px;
        }
      }
      .add-member {
        height: 30px;
        display: flex;
        padding: 21px 13px;
        align-items: center;
        color: $--color-black;
        .member-info {
          // width: 100px;
          width: 142px;
          display: block;
          font-size: 14px;
          @include ellipsis;
        }
        .member-btn {
          flex: 1;
          display: flex;
          justify-content: flex-end;
          align-items: center;
          i {
            @include get-blue-color(lighten-3);
            display: flex;
            justify-content: center;
            font-size: 15px;
            align-items: center;
          }
          .serach {
            font-size: 13px;
            margin-top: 3px;
          }
        }
      }
      .group-list {
        overflow: hidden;
        width: 100%;
        height: 100%;
        .menu-size {
          padding: 0;
          .dropdown-item {
            font-size: 0.75rem;
          }
        }
        .group-item {
          width: 192px;
          .card-item {
            .card-operate {
              top: 3px;
              right: 3px;
              .icon {
                @include get-grey-color(darken-1);
              }
              .send-msg {
                font-size: 18px;
              }
            }
            position: inherit;
            height: 2.9rem;
            &:hover .user-card {
              display: flex;
            }
            .user-card {
              display: none;
            }
            .card-operate {
              top: 3px;
              right: 3px;
              .icon {
                @include get-grey-color(darken-1);
              }
              .send-msg {
                font-size: 18px;
              }
            }
            .default-content {
              height: 2.9rem;
              .title {
                font-size: 0.75rem;
              }
            }
            .group-avatar {
              width: 30px;
              height: 30px;
            }
            .online-icon {
              // right: -5px;
              // bottom: -5px;
              right: -2px;
              bottom: -5px;
              background: none;
            }
            .online-icon-2 {
              width: 14px;
              height: 13px;
            }
            .online-icon-1 {
              width: 12px;
              height: 12px;
            }
            .icon {
              font-size: 12px;
            }
            .member-icon {
              color: gold;
            }
            &:hover {
              background: #ebebeb;
            }
          }
        }
        &:hover {
          overflow-y: auto;
        }
      }
      ::-webkit-scrollbar {
        background: #ffffff;
      }
    }
  }
  .is-loading {
    height: 100%;
    border-left: 1px solid $--border-color-grey;
    display: flex; //fit xp
    flex: 1; //fit xp
  }
  .notice-url {
    text-decoration: underline;
  }
}
</style>