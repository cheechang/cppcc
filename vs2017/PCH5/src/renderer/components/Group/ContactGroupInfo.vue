<template>
  <div class="contact-group-info router-detail">
    <card-lists
      :lists="groupInfoItem"
      :img="groupInfo.avatar&&groupInfo.avatar.replace(/\\/g, '\\\\')"
      :name="groupInfo.groupName"
      :gender="4"
      :qrcode="qrcode"
      :dialList="dialList"
      @click-button="handleButtonClick"
    >
      <template slot-scope="data">
        <!-- 分组标题 开始 -->
        <div
          v-if="isShowTitle(data.index)"
          class="edit-info-title"
          :style="{'padding-top':data.index === 0 ? '0px':'10px'}"
        >{{getTitle(data.index)}}</div>
        <!-- 分组标题 结束 -->
        <!-- 内容主体 开始 -->
        <div
          class="edit-info-item"
          v-if="data.index !== 8"
          :class="data.index === 7?'clear-msg':''"
        >
          <!-- 内容详情 开始 -->
          <div class="info-item-content">
            <!-- 内容标题 开始 -->
            <div class="content-title">
              {{data.item.title}}
              <i
                class="icon"
                v-if="(data.index===4 || ( data.index === 0 && !data.item.disabled ))"
                @click.self.stop="editInfo(data.index, data.item)"
              >&#xe67c;</i>
              <sett-loading
                class="sett-loading" 
                v-if="loadingList[data.index] && loadingList[data.index].isShow"  
                :isLoading="loadingList[data.index] && loadingList[data.index].isLoading"
              ></sett-loading>
              <!-- v-if="loadingList[data.index] && loadingList[data.index].isShow" -->
            </div>
            <!-- 内容标题 结束 -->
            <!-- 内容详情 开始 -->
            <div
              v-if="data.index !== 7"
              class="content-data edit-Content-Data"
              :ref="'contentGroup'+data.index"
              :class="{'edit-style': data.item.isEdit && data.index !== 1,'list-content': data.item.hasOwnProperty('subContent')}"
              :contenteditable="data.item.isEdit && (data.index === 0 || data.index === 4)"
              :title="data.index !== 7?data.item.content:getGroupBeepTone"
              @keydown="editBoxEvent"
              @input="editText"
            >
              <v-checkbox
                class="item-checked"
                v-if="data.item.hasOwnProperty('hasChecked') && data.item.hasChecked"
                v-model="data.item.checked"
                :disabled="data.item.disabled"
                @change="checkItem(data.index , data.item)"
              ></v-checkbox>
              <span class="item-content">{{data.index !== 7?data.item.content:getGroupBeepTone }}</span>
              <i
                v-if="data.item.hasOwnProperty('subContent') && data.item.subContent.length && !data.item.disabled"
                class="icon"
                :class="[
                    {'scale-xe678': showList[data.index]}
                  ]"
                @click.self.stop="openList(data.index + '', data.item)"
              >&#xe77a;</i>
            </div>
            <!-- 内容详情 结束 -->
            <!-- 选项列表 开始 -->
            <list
              class="list"
              :listData="data.item.subContent"
              :isShow="showList[data.index]&&data.item.hasOwnProperty('subContent')"
              @select-item="selectItem"
              @close-select-list="closeList(data.index)"
            ></list>
            <!-- 选项列表 结束 -->
            <!-- 清除聊天记录 开始 -->
            <div class="clear-msg-content" v-if="data.index === 7">
              <div class="group-button clear-msg-button" @click="deleteMessageById">{{data.item.title}}</div>
            </div>
            <!-- 清除聊天记录 结束 -->
          </div>
          <!-- 内容详情 结束 -->
          <!-- 右侧icon 开始 -->
          <div class="right" v-if="data.item.isEdit">
            <i 
            class="icon" 
            :class="[data.item.animation]" 
            v-html="data.item.icon.right"  
            @click.self.stop="updateInfo(data.index, data.item)"
            ></i>
          </div>
          <!-- 右侧icon 结束 -->
        </div>
        <!-- 内容主体 结束 -->
        <div class="leave-group" v-else-if="!data.item.isHidden">
          <div class="group-button leave-button" @click="quitGroup">{{data.item.title}}</div>
        </div>
      </template>
    </card-lists>
    <!-- 分享群 选择页 -->
    <chat-search-list
      v-if="isShare"
      type="card"
      :shareId="expectedId"
      :hasShare="true"
      @close="isShare=false"
    ></chat-search-list>
    <!-- 群头像设置页 -->
    <img-cropper
      v-if="isCropAvatarShow"
      :from="1"
      :gender="4"
      :avatar="groupInfo.avatar"
      :id="groupInfo.groupId"
      @close="isCropAvatarShow=false"
    ></img-cropper>
  </div>
</template>
<script>
import { mapGetters } from "vuex";
import CardLists from "../Common/CardLists/index.vue";
import imgCropper from "./../Common/ImgCropper/index.vue";
import mixin from "../Contact/ContactMixin.js";
import GroupMixin from '../Group/GroupMixin';
import ChatSearchList from "../Chat/Msg/ChatSearchList";
import List from "./../Auth/common/list";
import { placeCaretAtEnd, insertNode } from "../Chat/At/at.js";
import SettLoading from "./../Account/Settings/Privacy/SettLoading";
export default {
  components: {
    CardLists,
    imgCropper,
    ChatSearchList,
    List,
    SettLoading
  },
  mixins: [mixin, GroupMixin],
  props: {
    isNotAllowMsg: {
      type: Boolean,
      default: false
    },
    qrcodeId: String
  },
  data() {
    return {
      showList: {},
      loadingList: {},
      isPermitManage: false,
      isMaster: false,
      updateMsg:'',
      openedEditIndex:0,
      updateParam: {},
      openListIndex:0,
      groupInfoItem: [
        // 群名
        { index: 0, title: this.$t("groups.name"), content: "", isEdit: false, icon: { right: "&#xe81f;" }, disabled: false, animation:''},
        // V标群设置
        { index: 1, title: this.$t("groups.vipSetting"), content: this.$t("groups.addVip"), hasChecked: true, checked: false},
        // 允许被搜索  (功能未开启，暂时隐藏，若开启index + 1)
        // { index: 2, title: this.$t("groups.search"), content: this.$t("groups.groupBeSearch"), hasChecked: true, checked: false, disabled: true},
        // 允许群成员邀请入群
        { index: 2, title: this.$t("groups.power"), content: this.$t("groups.allowInvite"), hasChecked: true, checked: false, disabled: true },
        // 身份认证
        { index: 3, title: this.$t("groups.addGroup"), content: this.$t("groups.toVerfiy"), type:1,
          subContent: [
            { index: 0, val: this.$t("groups.noAllow"), type: 0},
            { index: 1, val: this.$t("groups.toVerfiy"), type: 1 },
            { index: 2, val: this.$t("groups.allowAdd"), type: 2 }
          ],
          subIcon: { right: "&#xe77a;" }, hasChecked: false, isRow: false, disabled: true},
        // 个人群名片
        { index: 4, title: this.$t("groups.groupPersonalIDCard"), content: "", isEdit: false, icon: { right: "&#xe81f;" }, animation:'' },
        // 会话置顶
        { index: 5, title: this.$t("groups.chatTop"), content: this.$t("groups.chatMsgTop"), hasChecked: true, checked: false },
        // 消息通知设置
        { index: 6, title: this.$t("groups.messageSetting"), content: this.$t("groups.messageSettingModeOne"),type: 0,
          subContent: [
            { index: 0, val: this.$t("groups.messageSettingModeOne"), type: 0},
            // { index: 1, val: this.$t("groups.messageSettingModeTwo") },       // 功能暂无
            { index: 2, val: this.$t("groups.messageSettingModeThree"), type: 2}
          ]
        },
        // 消息提示音
        // { index: 7, title: this.$t("groups.groupBeepTone"), content: this.$t("groups.push6"), toneInfo: 'push6', type: 5,
        //   subContent: [
        //     { index: 0, val: this.$t("groups.push1"), toneInfo: "push1", type: 0},
        //     { index: 1, val: this.$t("groups.push2"), toneInfo: "push2", type: 1},
        //     { index: 2, val: this.$t("groups.push3"), toneInfo: "push3", type: 2},
        //     { index: 3, val: this.$t("groups.push4"), toneInfo: "push4", type: 3},
        //     { index: 4, val: this.$t("groups.push5"), toneInfo: "push5", type: 4},
        //     { index: 5, val: this.$t("groups.push6"), toneInfo: "push6", type: 5},
        //   ]
        // },
        // 禁止私聊
         //{ index: 8, title: this.$t("groups.privateChat"), content: this.$t("groups.noChatInGroup"), hasChecked: true, checked: false, disabled: true },
        // 密聊模式
        //{ index: 9, title: this.$t("groups.privateMode"), content: this.$t("groups.allowPrivate"), hasChecked: true, checked: false, disabled: true },
        // 单次阅读
        //{ index: 10, title: this.$t("groups.burnChat"), content: this.$t("groups.allowBurn"), hasChecked: true, checked: false, disabled: true },
        // 清空聊天记录
        { index: 7, title: this.$t("setting.clearChat"), content: this.$t("setting.clearChat"), icon: { right: "&#xe6bb;" } },
        // 退出/转让
        { index: 8, title: "", content: "", hasButton: true ,isHidden:false }
      ],
      dialList: [
        { id: "msg", icon: "&#xe68d;", color: "#4caf50", tooltip: this.$t("contacts.message") },
        { id: "edit", icon: "&#xe67c;", color: "#3f51b5", tooltip: this.$t("groups.editName") },
        { id: "avatar", icon: "&#xe691;", color: "#ff7d00", tooltip: this.$t("groups.editProfile") },
        { id: "share", icon: "&#xe6d9;", color: "#009688", tooltip: this.$t("contacts.share")}
      ],
      qrcode: {},
      isCropAvatarShow: false,
      isShare: false,
      titleList: [
        { index: 0, title: this.$t("groups.groupInfo") },
        { index: 4, title: this.$t("groups.groupIDCard") },
        { index: 5, title: this.$t("groups.groupMsg") }
      ],
      toneInfoList: null,  //群提示音列表
      audioGroupToneNode: null,
      oldIdCard:null,
      expectedId: '' // 期望的id：传入的id或者当前路由id
    };
  },
  computed: {
    ...mapGetters([
      "contact_groupList",
      "contact_groupExtension",
      "http_head",
      "user_usever",
      "user_serverHost",
      "user_account",
      "chat_chatList",
      "chat_chatContent",
      "chat_objectInfo",
      "user_netstat",
      "user_groupToneList",
      'contact_enterpriseDicValues'
    ]),
    groupInfo() {
      console.log('groupInfo::::', this.contact_groupList[this.expectedId])
      return this.contact_groupList[this.expectedId];
    },
    getGroupBeepTone(){
      console.log('user_groupToneList',this.user_groupToneList,
      this.expectedId,
      )
      if(this.user_groupToneList === null){
        return this.$t('groups.push6')
      }
      let toneInfo = this.user_groupToneList[this.expectedId] && this.formatToneInfo(this.user_groupToneList[this.expectedId]);
      switch (toneInfo) {
        case 'push1': return this.$t('groups.push1')
          break;
        case 'push2': return this.$t('groups.push2')
          break;
        case 'push3': return this.$t('groups.push3')
          break;
        case 'push4': return this.$t('groups.push4')
          break;
        case 'push5': return this.$t('groups.push5')
          break;
        default: return this.$t('groups.push6')
      };
      console.log("当前群的提示音为：", toneInfo, this.$t(`groups.${toneInfo}`));
      // return this.$t(`groups.${(this.user_groupToneList[this.$route.query.id] && this.formatToneInfo(this.user_groupToneList[this.$route.query.id]) )|| "push6"}`);
    }
  },
  watch: {
    $route: {
      handler: "getGroupDetail",
      immediate: true
    }
  },
  mounted() {
    this.$nextTick(() => {
      this.audioGroupToneNode = document.getElementById("audioGroupTone");
    })
  },
  methods: {
    getGroupDetail() {
      this.expectedId = this.qrcodeId || this.$route.query.id;
      this.isPermitManage = false;
      // 获取群操作权限/个人群名片
      this.getMemberInfo();
      // 加群方式/是否允许邀请入群
      this.getGroupSet();
      // 是否V标群/允许被搜索/群消息置顶/密聊/阅后即焚
      this.getGroupInfo();
      // 消息通知设置
      this.getGroupMsgRemindType();
      // 从SDK获取群提示音的信息
      this.getGroupSoundFromSDK(this.expectedId);
      // 设置群名称内容
      this.$set(this.groupInfoItem[0], 'content', this.groupInfo.groupName);
      this.qrcode = {
        id: this.groupInfo.groupId,
        gender: 4,
        host: this.contact_enterpriseDicValues.isLocalHost,
        elogo: this.user_usever, 
        serverhost: this.user_serverHost,
        type: 2
      };
    },
    getMemberInfo() {
      // 获取成员列表信息
      if (!this.isNotAllowMsg && !this.chat_objectInfo.hasOwnProperty(this.groupInfo.groupId)) {
        new Promise(resolve => {
          this.$Service.group.getMemberList(
            { groupId: this.groupInfo.groupId },
            resp => {
              resolve(resp);
            }
          );
        }).then(resp => {
          let memberList = Object.assign({}, resp);
          console.log("memberList", resp);
          this.$Service.log(
            `getMemberList:::  groupId:${this.groupInfo.groupId} length:${
              memberList.members.length
            }     `
          );
          this.$store.commit("SET_CHAT_OBJECT", {
            id: memberList.members[0][1].groupId,
            chatObject: memberList.members
          });
          this.getMemberdetailedInfo();
        });
      } else {
        this.dialList[3].isHidden = this.dialList[0].isHidden = true;
        this.getMemberdetailedInfo();
      }
    },
    getMemberdetailedInfo() {
      this.$Service.group.getMemberInfo(
        {
          groupId: this.groupInfo.groupId,
          userId: this.user_account.userId
        },
        resp => {
          console.log(
            "获取群权限",
            `groupId:${resp.groupId} | memberType:${resp.memberType}`,
            resp
          );
          // 获取个人群名片
          this.$set(this.groupInfoItem[4], 'content', resp.remark || resp.name);
          if (
            resp.memberType &&
            (resp.memberType === 3 || resp.memberType === 2)
          ) {
            this.isMaster = resp.memberType === 3;
            this.isPermitManage = true;
            if(this.groupInfoItem[8]){
              this.$set(this.groupInfoItem[8], 'title', resp.memberType === 3? this.$t("groups.disband"): this.$t("groups.leave"));
            }
            // this.groupInfoItem[12].title = resp.memberType === 3? this.$t("groups.disband"): this.$t("groups.leave");
          } else {
            this.isPermitManage = false;
            // this.groupInfoItem[12].title = this.$t("groups.leave");
            this.$set(this.groupInfoItem[8], 'title', this.$t("groups.leave"));
          }
          this._handleGroupShow();
        }
      );
    },
    _handleGroupShow() {
      _.forEach(this.groupInfoItem, element => {
        if (element.index !== 1 && element.index !== 5 && element.index !== 6 && element.index !== 7) {
          element.disabled = !this.isPermitManage;
        }
      });
      this.dialList[1].isHidden = this.dialList[2].isHidden = !this.isPermitManage;
    },
    // 获取群设置
    getGroupSet() {
      this.$Service.group.getGroupSet(
        { groupId: this.groupInfo.groupId },
        resp => {
          console.log("防骚扰:", resp);
          if (resp.code !== 0) return;
          // 加群方式
          this.$set(this.groupInfoItem[3], 'content', this.groupInfoItem[3].subContent[resp.verify_type - 1].val);
          // 是否允许邀请入群
          this.$set(this.groupInfoItem[2], 'checked', resp.is_allow === 1);
        }
      );
    },
    // 获取群信息
    getGroupInfo() {
      this.$Service.group.getGroupInfo(
        { groupId: this.groupInfo.groupId },
        resp => {
          console.log("是否V标群/允许密聊/阅后即焚/私聊:", resp);
          // 获取群拓展字段信息 包含     允许密聊/阅后即焚/私聊
          //let extend = resp.extend && JSON.parse(resp.extend);
          let info = resp.info;
          if (info) {
            this.$set(this.groupInfoItem[1], 'checked', info && info.isVSign); // V标群
            this.$set(this.groupInfoItem[5], 'checked', info && info.isTop); // 群消息置顶
          }
            console.log('this.isMaster', this.isMaster)
          // if(this.isMaster === false){
          //   console.log('不是群主')
            this.$set(this.groupInfoItem[8], 'isHidden', false);
            if(info.groupType == 'eid' || info.groupType == 'org'){
            console.log('议政群，组织群')
            console.log('info.groupType',this.groupInfoItem[8])
              this.$set(this.groupInfoItem[8], 'isHidden', true);
            }
          //}
          // if (extend) {
          //   this.$set(this.groupInfoItem[8], 'checked', extend.disallowStrangerChat && extend.disallowStrangerChat === "1"); // 是否允许群内私聊
          //   this.$set(this.groupInfoItem[9], 'checked', extend.privateMsg && extend.privateMsg === "1"); // 是否开启密聊
          //   this.$set(this.groupInfoItem[10], 'checked', extend.isSelfDestruct && extend.isSelfDestruct === "1"); // 是否开启单次阅读
          // }
          this.$store.dispatch("SET_GROUP_EXTENSIONS", {
            id: this.groupInfo.groupId,
            extendInfo: {
              privateMsg: '0',
              burnMsg: '0',
              disallowStrangerChat: '0'
            }
          });
        }
      );
    },
    // 获取消息通知模式
    getGroupMsgRemindType() {
      this.$Service.group.getGroupMsgRemindType(
        { groupId: this.groupInfo.groupId },
        resp => {
          if (resp.code === 0) {
            // this.groupInfoItem[6].content = this.groupInfoItem[6].subContent[
            //   resp.mode - 1
            // ].val; // 消息通知设置
            this.groupInfoItem[6].content = this.groupInfoItem[6].subContent.find((element) => (element.index === (resp.mode -1))).val;    // 功能缺失，暂时使用该方法
          }
        }
      );
    },
    // 弹出框修改群名称
    changeRemark() {
      this.$dialog.prompt({
        confirmText: this.$t("common.sure"),
        cancelText: this.$t("common.cancel"),
        inputAttrs: {
          placeholder: this.groupInfo.groupName,
          maxlength: 20,
          value: this.groupInfo.groupName
        },
        required: true,
        onConfirm: value => {
          if (value === this.groupInfo.groupName) return;
          this.updateParam = { groupName: value };
          this.updateGroupInfo();
        }
      });
    },
    handleButtonClick(index) {
      let groupActions = {
        0: () => this.startChat(this.groupInfo, 2),
        1: () => this.changeRemark(),
        2: () => (this.isCropAvatarShow = true),
        3: () => (this.isShare = true)
      };
      groupActions[index].call(this);
    },
    // 判断是否显示标题
    isShowTitle(position) {
      return this.titleList.some((element, index) => {
        //console.log('element',element,'position:',position)
        if (element.index === position) return true;
      });
    },
    //  获取标题
    getTitle(position) {
      let title = "";
      this.titleList.some((element, index) => {
        if (element.index === position) {
          title = element.title;
          return true;
        }
      });
      return title;
    },
    // 阻止contenteditable文本域回车事件
    editBoxEvent(e) {
      if (e.keyCode === 13) {
        e.preventDefault();
      }
    },
    // 输入框填写的文本
    editText(e) {
      if (e.target.innerText.length > 20) {
        e.target.innerText = e.target.innerText.slice(0, 20);
        e.target.focus(); //解决ff不获取焦点无法定位问题
        var range = window.getSelection(); //创建range
        range.selectAllChildren(e.target); //range 选择obj下所有子内容
        range.collapseToEnd(); //光标移至最后
      }
      this.updateMsg = e.target.innerText;
    },
    // 激活编辑框
    editInfo(index, item) {
      console.log("index::",index,"item::",item)
      this.updateMsg = "";
      this.openedEditIndex = index;
      this.groupInfoItem[index].isEdit = true;
      this.oldIdCard = index === 4?item.content:null;
      this.groupInfoItem.forEach((element, i) => {
        if (element.hasOwnProperty("isEdit") && i !== index) {
          element.isEdit = false;
        }
      });
      document.addEventListener("click", this.clickOutsideAccount);
      let el = this.$refs["contentGroup" + index];
      setTimeout(() => {
        // 获取焦点
        placeCaretAtEnd(el);
      }, 100);
    },
     // 更新输入框信息
    updateInfo(index, item) {
      // 显示完成图片倒计时未结束时，不可点击。
      let lis = document.getElementsByClassName("edit-Content-Data");
      // 内容未改变不处理
      if (lis[index].innerText === this.groupInfoItem[index].content) {
        this.groupInfoItem[index].isEdit = false;
        this.updateMsg = "";
        return;
      }
      // 动画未完成不允许点击
      if (item.icon.right === "&#xe632;" || item.icon.right === "&#xe6ac;"){
         return;
      }
      if (index === 0 || index === 4) {
        console.log("修改群名称");
        this.updateMsg = this.updateMsg.trim(); //去除字符串两头的空格
        let nameReg = /^.{1,20}$/;
        if (!nameReg.test(this.updateMsg)) {
          this.$toast.open({
            duration: 3000,
            message: this.$t("user.userNameLimit"),
            position: 'is-top',
            type: "is-danger"
          });
          return;
        }
        // 开启设置动画
        this.groupInfoItem[index].icon.right = "&#xe6ac;";
        this.groupInfoItem[index].animation = "loading-start";
        if(index === 0){
          this.updateParam = { groupName: this.updateMsg };
          this.updateGroupInfo(index);
        }else{
          this.updateParam = { remark: this.updateMsg };
          this.updateMemberInfo(index);
        }
        console.log("更新的信息为：：",this.updateParam);
      }
    },
    // 点击外部区域关闭编辑框
    clickOutsideAccount(e) {
      let el = this.$refs["contentGroup" + this.openedEditIndex].parentNode.parentNode;
      if (!el.contains(e.target)) {
        this.updateMsg = "";
        this.$nextTick(() => {
          if(this.openedEditIndex === 0){
            this.$refs["contentGroup0"].innerText = this.groupInfo.groupName;
          }else if(this.openedEditIndex === 4){
            this.$refs['contentGroup4'].innerText = this.oldIdCard;
          }
        })
        this.$set(this.groupInfoItem[this.openedEditIndex], 'isEdit', false);
        document.removeEventListener("click", this.clickOutsideAccount);
      }
    },
    // 更新群信息
    updateGroupInfo(index){
      if (!this.user_netstat) {
        this.$toast.open({ message: this.$t('groups.connectionErr'), type: 'is-danger'});
        return;
      }
      if (!this.isPermitManage) return;
      this.$set(this.updateParam,"groupId",this.groupInfo.groupId)
      console.log("更新群信息参数:",this.updateParam);
      this.$Service.group.setGroupInfo (
        this.updateParam,
        resp => {
          if(resp.code === 0){
            this.setDoneCb(index);
            if(index === 0){
              this.$set(this.groupInfoItem[0], 'content', this.updateMsg);
              this.updateMsg = "";
              this.groupInfoItem[index].icon.right = "&#xe632;";
              this.groupInfoItem[index].animation = "loading-success";
              setTimeout(() => {
                this.$set(this.groupInfoItem[0], 'isEdit', false);
                this.groupInfoItem[index].icon.right = "&#xe81f;";
                this.groupInfoItem[index].animation = "";
              }, 1000);
            }else{
              console.log("设置成功",index)
              if(index === undefined){
                // 处理弹出框编辑群名称情况
                console.log('弹出框编辑群名片')
                this.$set(this.groupInfoItem[0], 'content', this.updateParam.groupName);    
              } 
            }
          }else{
            if(index !== 0){
              this.groupInfoItem[index].checked = !this.groupInfoItem[index].checked;
            }
          }
        }
      );
    },
    // 更新群成员信息
    updateMemberInfo(index){
      this.$set(this.updateParam,"groupId",this.groupInfo.groupId);
      this.$set(this.updateParam,"id",this.user_account.userId);
      this.$Service.group.setMemberInfo(
        this.updateParam,
        resp => {
          console.log("更新群成员信息的回调", resp )
          if(resp.code === 0){
            this.$set(this.groupInfoItem[index], 'content', this.updateMsg);
            if(index === 4){
              this.oldIdCard = this.updateMsg;
            }
            this.updateMsg = "";
            this.groupInfoItem[index].icon.right = "&#xe632;";
            this.groupInfoItem[index].animation = "loading-success";
            setTimeout(() => {
              this.groupInfoItem[index].isEdit = false;
              this.groupInfoItem[index].icon.right = "&#xe81f;";
              this.groupInfoItem[index].animation = "";
            }, 1000);
          }else{
              let errorInfo = this.$t(`ErrorCode.${resp.code}`);
              let message = this.$t('groups.groupPersonalIDCard') + "：" + errorInfo;
              this.$toast.open({message, type: 'is-danger'});
              this.updateMsg = "";
              this.groupInfoItem[index].isEdit = false;
              this.groupInfoItem[index].icon.right = "&#xe81f;";
              this.groupInfoItem[index].animation = "";
          }
        }
      );
    },
    // 勾选框勾选
    checkItem(index, item) {
      console.log("勾选了",item);
      item.checked = !item.checked;
      this.$set(this.loadingList,item.index,{});
      this.$set(this.loadingList[item.index],"isShow",true);
      this.$set(this.loadingList[item.index],"isLoading",true);
      let checkStatus = {
        1: () => setTimeout(() => {this.setVip(item)}, 0),            // 设置Vip
        // 2: () => setTimeout(() => {this.setChatBurn(item)}, 0),       // 允许被搜索   (功能暂无)
        2: () => setTimeout(() => {this.setInvite(item)}, 0),    // 允许邀请入群
        5: () => setTimeout(() => {this.setChatTop(item)}, 0),   // 置顶本群消息
        8: () => setTimeout(() => {this.setChatStranger(item)}, 0),   // 禁止私聊
        9: () => setTimeout(() => {this.setChatPrivate(item)}, 0),  // 密聊模式
        10: () => setTimeout(() => {this.setChatBurn(item)}, 0)   // 单次阅读
      }
      checkStatus[index].call(this);
    },
    // 下拉列表选择
    selectItem(type, value, item){
      console.log("当前打开列表index:",this.openListIndex)
      console.log("当前打开列表项:",this.groupInfoItem[this.openListIndex])
      console.log("当前选择项:",item)
      if(this.openListIndex !== '7' && this.groupInfoItem[this.openListIndex].content === item.val){
        return;
      }
      console.log('this.user_groupToneList',this.user_groupToneList,this.expectedId)
      if( this.user_groupToneList && item.val === this.user_groupToneList[this.expectedId]){
        return;
      }
      this.$set(this.loadingList,this.openListIndex,{});
      this.$set(this.loadingList[this.openListIndex],"isShow",true);
      this.$set(this.loadingList[this.openListIndex],"isLoading",true);
      if(this.openListIndex === "3"){
        // 身份认证
        let param = { groupId : this.groupInfo.groupId, verify_type: item.index + 1};
        this.setGroupSet(param , this.groupInfoItem[this.openListIndex]);
      }else if(this.openListIndex === "6"){
        // 消息通知方式
        let param = { groupId: this.groupInfo.groupId , mode : item.index + 1 };
        this.setGroupMsgRemindType(param, item.val, this.groupInfoItem[this.openListIndex]);
      }
      // else if(this.openListIndex === "7"){
      //   // 群提示音
      //   this.setGroupBeepTone(this.groupInfo.groupId, item.toneInfo, this.groupInfoItem[this.openListIndex]);
      // }
    },
    // 设置V标群
    setVip(item){
      let param = { groupId : this.groupInfo.groupId, vSign: item.checked};
      this.setGroupExtraInfo(param , item);
    },
    // 设置群成员邀请入群
    setInvite(item){
      let param = { groupId : this.groupInfo.groupId, is_allow: item.checked?1:2};
      this.setGroupSet(param , item);
    },
    // 消息置顶
    setChatTop(item){
      let param = { targetId: this.groupInfo.groupId , isTop: item.checked };
      this.$Service.chat.chatTop( param, resp => {
        if(resp.code !== 0){
          let errorInfo = this.$t(`ErrorCode.${resp.code}`);
          let message = this.$t('groups.chatTop') + "：" + errorInfo;
          this.$toast.open({message, type: 'is-danger'});
          if(item.hasChecked){
            item.checked = !item.checked;
          }
        }
        this.setDoneCb(item.index);
        console.log("chatList::",this.chat_chatList)
        console.log("id::",this.groupInfo.groupId)
        if(this.chat_chatList[this.groupInfo.groupId]){
          // this.chat_chatList[this.groupInfo.groupId].isTop = item.checked ? 1 : 0;
          this.$set(this.chat_chatList[this.groupInfo.groupId], 'isTop', item.checked ? 1 : 0)
        }else{
          this.addChat()
        } 
      })
    },
    // 设置消息模式和V标
    setGroupExtraInfo(param, item){
      this.$Service.group.setGroupExtraInfo( param , resp => {
        console.log('设置V标群、群消息通知回调：' + JSON.stringify(resp));
        if (resp.code !== 0) {
          let errorInfo = this.$t(`ErrorCode.${resp.code}`);
          let message = item.index === 1?this.$t('groups.addVip'):this.$t('groups.messageSetting');
          message = message + "：" + errorInfo;
          this.$toast.open({message, type: 'is-danger'});
          item.checked = !item.checked;
        }
        this.setDoneCb(item.index);
      })
    },
    // 设置群成员邀请，加群方式
    setGroupSet(param, item){
      this.$Service.group.setGroupSet( param , resp => {
        console.log('设设置群成员邀请，加群方式回调：' + JSON.stringify(resp));
        if (resp.code !== 0) {
          let errorInfo = this.$t(`ErrorCode.${resp.code}`);
          let message = item.index === 2?this.$t('groups.allowInvite'):this.$t('groups.addGroup');
          message = message + "：" + errorInfo;
          this.$toast.open({message, type: 'is-danger'});
          if(item.hasChecked){
            item.checked = !item.checked;
          }
        }else{
          if(!item.hasChecked){
            this.$set(item, 'content', item.subContent[param.verify_type - 1].val)
            // item.content = item.subContent[param.verify_type - 1].val;
            this.closeList(item.index);
          }
          this.setDoneCb(item.index);
        }
      })
    },
    // 设置群消息接收模式
    setGroupMsgRemindType(param, value, item){
      this.$Service.group.setGroupMsgRemindType(
        param,
        resp => {
          if (resp.code === 0)
            // item.content = item.subContent[param.mode - 1].val;      // 缺失第二功能所以暂时弃用，使用以下方法
            item.content = value;
            this.$store.dispatch('UPDATE_CHATLIST', {
              id: this.groupInfo.groupId,
              disturbSet: param.mode,
              disturbStatus: param.mode
            })
            this.setDoneCb(this.openListIndex);
            console.log("设置群消息接收模式成功：",param);
        }
      )
    },
    // 设置群提示音
    setGroupBeepTone(groupId, toneInfo, item){
      this.audioGroupToneNode.src = require(`vrv-static/resources/audio/${
        toneInfo
      }.mp3`);
      this.$nextTick(() => {
        this.audioGroupToneNode.play();
      });
      if(toneInfo === this.user_groupToneList[groupId]){
        this.setDoneCb(this.openListIndex);
        return
      }
      this.setGroupTone(groupId, toneInfo)
        .then(() => {
          this.setDoneCb(this.openListIndex);
          let toneInfoList = {...this.user_groupToneList};
          this.$set(toneInfoList, groupId, toneInfo);
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
    // 设置禁止群内私聊
    setChatStranger(item) {
      this.updateParam = {
        extendProperties: JSON.stringify({
          disallowStrangerChat: item.checked ? '1' : '0',
          privateMsg: this.contact_groupExtension[this.groupInfo.groupId].privateMsg || '0',
          isSelfDestruct: this.contact_groupExtension[this.groupInfo.groupId].burnMsg || '0'
        })
      }
      this.updateGroupInfo(item.index);
    },
    // 设置群内密聊
    setChatPrivate(item){
      this.updateParam = {
        extendProperties: JSON.stringify({
          privateMsg: item.checked ? '1' : '0',
          disallowStrangerChat: this.contact_groupExtension[this.groupInfo.groupId].disallowStrangerChat || '0',
          isSelfDestruct: this.contact_groupExtension[this.groupInfo.groupId].burnMsg || '0'
        })
      }
      this.updateGroupInfo(item.index);
    },
    // 设置单次阅读
    setChatBurn(item) {
      this.updateParam = {
        extendProperties: JSON.stringify({
          isSelfDestruct: item.checked ? '1' : '0',
          privateMsg: this.contact_groupExtension[this.groupInfo.groupId].privateMsg || '0',
          disallowStrangerChat: this.contact_groupExtension[this.groupInfo.groupId].disallowStrangerChat || '0'
        })
      }
      this.updateGroupInfo(item.index);
    },
    // 清空聊天记录
    deleteMessageById() {
      this.$dialog.confirm({
        message: this.$t('groups.toClearMsg', {value: this.contact_groupList[this.groupInfo.groupId].groupName}),
        confirmText: this.$t('common.confirm') ,
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          return new Promise(resolve => {
            let deleteMsgObj = {
              targetId: this.groupInfo.groupId,
              endTime: '0',
              beginTime: new Date().getTime().toString()
            }  
            console.log('deleteMsgObj', deleteMsgObj)
            this.$Service.chat.deleteMessageByTime(deleteMsgObj, resp => {
              console.log('deleteMessageByTime', resp)
              if (resp.code === 0) {
                this.$Service.log(`deleteMessageById:::    deleteId: ${this.groupInfo.groupId}`)
                if (this.chat_chatContent[this.groupInfo.groupId]) {
                  this.chat_chatContent[this.groupInfo.groupId] = {}
                  resolve()
                }
              }
            })
          })
        }
      })
    },
    // 退出/解散群
    quitGroup(){
      this.$dialog.confirm({
        message: this.isMaster 
          ? this.$t('groups.toDisband', {value: this.contact_groupList[this.groupInfo.groupId].groupName})
          : this.$t('groups.toLeave', {value: this.contact_groupList[this.groupInfo.groupId].groupName}),
        confirmText: this.isMaster ? this.$t('groups.disband') : this.$t('groups.leave'),
        cancelText: this.$t('common.cancel'),
        onConfirm: () => {
          let removeGroupParam = { groupId: this.groupInfo.groupId , type: this.isMaster ? 1 : 2 }
          this.$Service.group.removeGroup(removeGroupParam, resp => {
            console.log('removeGroup', resp)
            if (resp.code !== 0) {
              let errorInfo = this.$t(`ErrorCode.${resp.code}`)
              this.$toast.open({
                message: `${this.isMaster ? this.$t('groups.disband') : this.$t('groups.leave')}${this.$t('groups.group')}：` + errorInfo,
                type: 'is-danger'
              })
            }else{
              this.deleteGroupLocalTone(removeGroupParam.groupId);
            }
          })
        }
      })
    },
    // 消息列添加消息
    addChat(){
      let item = this.groupInfo;
      let itemParams = {
        id:  item.groupId ,
        name:  item.groupName ,
        chatType: 2,
        thumbAvatar: item.avatar,
        gender: 0,
        subType: 1,
        msgType: 2,
        lastMsg: '',
        delSign: '',
        whereFrom: '',
        isTop: 1,
      };
      let time = this.$Service.user.getServerTimeSync({}) || new Date().getTime()
      itemParams.msgTime = itemParams.startTime = time
      console.log('itemParams::', itemParams)
      this.$store.commit('PUSH_CHATLIST', itemParams);
    },
    // 打开下拉列表
    openList(index, item) {
      if(this.showList[index]){
        this.showList[index] = false;
        this.openListIndex = 0;
        return
      }
      if (Object.keys(this.showList).length > 0) {
        for (let key in this.showList) {
          this.$set(this.showList, key, false);
        }
        this.$set(this.showList, index, true);
      } else {
        this.$set(this.showList, index, true);
      }
      this.openListIndex = index;
    },
    // 关闭下拉列表
    closeList(index) {
      this.$set(this.showList, index, false);
    },
    // 设置完成的回调 操作动画
    setDoneCb(index){
      if(this.loadingList[index]){
        this.$set(this.loadingList[index],"isLoading",false);
        setTimeout(() => {
          this.$set(this.loadingList[index],"isShow",false);
        }, 300);
      }
    }
  },
  beforeDestroy() {
    document.removeEventListener("click", this.clickOutsideAccount);
  }
};
</script>
<style lang="scss">
.contact-group-info {
  flex: 1;
  display: flex;
  justify-content: center;
  .v-lists-content {
    .v-divder{
      margin-right: 7px;
    }
  }
}
.edit-info-title {
  padding: 10px 0px 5px 15px;
  //color: rgb(129,126,121);
  color: rgba(0, 0, 0, 0.38);
  font-size: 13px;
}
.edit-info-item {
  padding: 5px 30px 0.5rem 48px;
  display: flex;
  justify-content: flex-start;
  .right {
    width: 40px;
    height: 45px;
    display: flex;
    justify-content: center;
    align-items: center;
    padding-top: 20px;
    .icon {
      font-size: 22px;
      transition: 0.3s;
      color: rgba(0, 0, 0, 0.38);
    }
    .loading-start {
      font-size: 16px;
      color: red;
      animation: suerSettLoading 0.7s linear infinite;
      transform-origin: 12px 11px;
    }
    .loading-success {
      color: #388e3c;
    }
    &.clearMsg {
      .icon:hover {
        color: red;
      }
    }
  }
  .info-item-content {
    width: 206px;
    height: 45px;
    margin-bottom: 0;
    padding: 0 5px;
    display: flex;
    position: relative;
    flex-direction: column;
    .content-title {
      color: rgba(0, 0, 0, 0.38);
      font-size: 0.75rem;
      margin-bottom: 0.3rem;
      .icon {
        width: 19px;
        height: 19px;
        vertical-align: baseline !important;
      }
      .sett-loading{
        // float: right!important;
        // margin-right: 50px!important;
        // float: left!important;
        margin-left: 10px!important;
      }
    }
    .content-data {
      display:flex;
      align-items: center;
      align-self: flex-start;
      overflow: hidden;
      width: 100%;
      white-space: nowrap;
      text-overflow: ellipsis;
      position: relative;
      font-size: 0.8rem;
      .scale-xe678 {
        transform: rotate(180deg);
        transform-origin: 12px 12px;
      }
      .icon {
        font-size: 22px;
        transition: 0.3s;
        color: rgba(0, 0, 0, 0.38);
      }
      .item-checked {
        margin-right: 6px;
        height: 24px;
        .v-checkbox-inner {
          width: 15px !important;
          height: 15px !important;
          &::after {
            width: 3px !important;
            height: 6px !important;
          }
        }
      }
      .item-content{
        display: inline-block;
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap;
      }
      &.list-content{
        .icon{
          margin-left: 10px;
        }
      }
    }
    .tip-msg {
      color: get-grey-color(lighten-1);
      height: 24px;
    }
    .edit-style {
      outline: none;
      text-overflow: ellipsis;
    }
    .list {
      z-index: 999;
      left: 0;
      top: 50px;
      right: auto;
      font-size: 12px;
      box-shadow: 1px 2px 10px #888888;
      &:hover {
        z-index: 999;
      }
    }
  }
}
.clear-msg {
  padding: 0px;
  display: flex;
  justify-content: flex-start;
  .info-item-content {
    width: 100%;
    height: 80px;
    padding: 5px 0px 0px 0px;
    .content-title {
      padding: 0 48px;
    }
    .clear-msg-content {
      display: flex;
      align-items: center;
      justify-content: center;
      padding-bottom: 10px;
      padding-top: 5px;
      .clear-msg-button {
        background-color: #5cbbf6;
        &:hover {
          background-color: #3ba2f4;
        }
      }
    }
  }
}
.leave-group {
  display: flex;
  align-items: center;
  justify-content: center;
  padding-bottom: 10px;
  padding-top: 15px;
  .leave-button {
    background: #FF5252;
    &:hover {
      background: #FF6666;
    }
  }
}
.group-button {
  width: 64%;
  border-width: 0px;
  border-radius: 3px;
  cursor: pointer;
  outline: none;
  color: white;
  font-size: $--font-size-small;
  text-align: center;
  padding: 5px 0px;
}
</style>



