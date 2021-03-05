<template>

  <div class="chat-content" >
    <i class="icon btn-expend" :class="{'theme-txt':isIconHover, 'expend-icon': !isExpend}" v-if="currentShowState()" :title="!isExpend ? $t('chat.expandSetting'): $t('chat.closeSetting')" @click="showExpend" @mouseenter="isIconHover=true" @mouseleave="isIconHover=false">&#xe6a9;</i>
    
    <!-- 会话标题 展示消息者名称 -->
    <chat-title  :chatType="chatType" :inputState='inputState' @updateName="updateName" :name="name" :currentActive="currentActive" :id="id" @changeTab="changeTab" ></chat-title>
    <!-- 消息列表展示区域 -->
    <div class="content-area" v-show="_isShowChat">
      <!-- 【消息置顶】组件引入 -->
      <msg-top-marquee v-if="showTopMarquee&&isGroupOfEid" :id="id" :chatType="2" :isOpen="isOpen" :userInfo="userInfo" @openChatMsgTop='changeTab' @closeTopMsg="hideMarquee=true"></msg-top-marquee>
      <div class="chat-detail">
        <!-- 消息列表展示区域 -->
        <chat-msg-list-area draggable="false" :isOpenAction="isOpenAction" :isActionForward="isActionForward" :isExpendSidebar="isExpend" :chatType="chatType" :isOpen="isOpen" :isWinFocus="isWinFocus" :messageObject="data" :userInfo="userInfo" :id="id" :remindMsgSeconds='remindMsgSeconds'  @handleActionBoxShow="handleActionBoxShow" @msgSelectLength="msgSelectLength" @reEdit="reEditMsg" @hasAtInList='handleRightAt' :hasMixMsgDelete="hasMixMsgDelete" @open-chat-top="isOpenChatTop=true" @openChatGroupNotice="changeTab" @showMsgRemind="showMsgRemind"></chat-msg-list-area>
        <!-- 更多消息操作 -->
        <chat-msg-action v-if="isOpenAction" :id="id" :isExpendSidebar="isExpend" :isExitSelectItems="isExitSelectItems" @forward="isActionForward=isExitSelectItems" @close="closeAction" @handleMixMsgDelete='handleMixMsgDelete' ></chat-msg-action>
        <!-- 消息编辑区域 （含手机、PC） -->
        <chat-edit-area :isOpen="isOpen" @updateEncryptMsg='_updateEncryptMsg' @updateDelayMsg="_updateDelayMsg" @updateBurnMsg="_updateBurnMsg" :isBurn="isBurn" :isDelay="isDelay" :isEncryptMsg ="isEncryptMsg" :rewriteText="rewriteText" :chatType="chatType" :userInfo="userInfo" :id="id"  :rightAtId="rightAtId"></chat-edit-area>
      </div>
      <!-- 群成员信息展示区域（包含群成员、群信息） -->
      <chat-group-info v-if="chatType===2&&isExpend" :isLoadFinished="isLoadFinished" :id="id" :userInfo="userInfo"></chat-group-info>
      <!-- 单聊会话设置页 -->
      <chat-single-aside  v-if="chatType===1" :rtcFile='rtcFile' @close="showExpend" @changeExpends="changeExpends" :isExpend="isExpend" :id="id" ></chat-single-aside>
    </div>
    
    <!-- 群公告 -->
    <!-- <chat-group-notice v-if="_isShowNotice" :id="id"></chat-group-notice> -->

    <!-- 群文件展示区域 -->
    <!-- <chat-group-file v-show="_isShowGroupFile" :id="id"></chat-group-file> -->
    
    <!-- 聊天记录 -->
    <!-- <chat-msg-record v-if="_isShowMsgRecord" :isOpen="isOpen" :userInfo="userInfo" :id="id" :chatType="chatType" ></chat-msg-record> -->
    <!-- 视频会议 -->
    <!-- <chat-muti-video v-if="_isShowMutiVideo"></chat-muti-video> -->

    <div class="tab-view-item"  v-for="(item, value,index) in tabViewArray" :key="index"  v-show="item.view === currentView">
        <component :is='item.components' :isOpen="isOpen" :userInfo="userInfo" :id="id" :chatType="chatType"></component>
    </div>
    <!-- 拖拽区域 -->
    <div class="drop-area" ref="dropArea" :class="{'drop-box':isDragging}">
      <span class="drop-notify">{{ $t('chat.selectDrop', {value: this.name})}}</span>
    </div>
    <!-- 消息提醒时间选择 -->
    <Add-remind v-if="isAddRemind" @closeAddRemind='isAddRemind = false' :msgBody='showMsgRemindBody' @settingSuccess="settingMethods"></Add-remind>
    <!-- <MsgTypeRemind></MsgTypeRemind> -->
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import ChatEditArea from './ChatEdit/index';
import ChatMsgListArea from './ChatMsgListArea';
import ChatGroupInfo from '../../Group/ChatGroupInfo';
import ChatGroupFile from '../../Group/ChatGroupFile.vue';
import ChatGroupNotice from '../../Group/ChatGroupInfo/ChatGroupNotice';
import ChatTitle from './ChatTitle';
import ChatMsgAction from './ChatMsgAction';
import ChatSingleAside from './ChatSingleAside'
import ChatMutiVideo from './ChatMutiVideo'
import ChatTabFile from './ChatTabFile'
import ChatMsgRecord from './ChatTabRecord/ChatMsgRecord'
import ChatTabRecord from './ChatTabRecord'
import MsgTopMarquee from './ChatTabRecord/ChatMsgTop/MsgTopMarquee.vue'
import MsgMxin from '../msgMixin'
import { isOSX } from '../../../../comm/is'
import { versionCompirePro } from "../../../utils/utils.js";
import pkg from '../../../../../package.json'
import AddRemind from './AddRemind';
// import MsgTypeRemind from '../Msg/MsgTypeRemind.vue';

const ChatType = {
      user: 1,
      group: 2,
      app: 3
}

const tabView = {
  chat : 'chat',
  notice: 'notice',
  groupFile: 'file',
  msgRecord: 'msgRecord',
  // video: 'video'
}
export default {
  data() {
    return {
      isGroupOfEid:false,
      isExpend: false, // 是否展开
      currentActive: 0, // 0：聊天 1：文件
      currentView: tabView.chat,
      userInfo: {},
      isLoadFinished: false, // 是否已异步存储完成群成员数据，控制群成员加载动画
      isOpenAction: false, // 是否显示更多操作：合并转发、删除
      isActionForward: false, // 是否转发 (这里是右键菜单'更多'里的转发),
      hasMixMsgDelete: false,
      isExitSelectItems: false, // 是否存在转发消息条数
      myDevice:  require('vrv-static/resources/images/common/mydevice.png'),
      rewriteText: '',
      isIconHover: false,
      isDragging: false,
      isEncryptMsg: false, // 是否是密聊
      isBurn: false, // 是否是阅后即焚
      isDelay: false, // 是否是延时消息
      name: '',
      chatType: 0,
      rightAtId: '',
      tabView : {
        chat : 'chat',
        notice: 'notice',
        groupFile: 'file',
        msgRecord: 'msgRecord',
        // video: 'video'
      },
      tabViewArray: {},
      // 首屏渲染完成后再去显示置顶跑马灯
      isOpenChatTop: false,
      hideMarquee:false,
      isAddRemind:false,
      showMsgRemindBody:'',
    };
  },
  mixins: [MsgMxin],
  props: {
    data: {
      type: Array | Object
    },
    isOpen: {
      type: Boolean
    },
    isWinFocus: {
      type: Boolean
    },
    // chatType: {
    //   type: Number
    // },
    rtcFile: {
      type: Object
    },
    remindMsgSeconds: {
      type: Number
    },
    id: String,
    inputState:  {
      type: Object
    }
    
  },
  created(){
    // this.$ipc.on('msgTopChanged',this._handlerMsgTop)
  },
  computed: {
    /**
     * 是否展开文件直传列表
     */
    ...mapGetters([
      'contact_contactList',
      'user_account',
      'chat_chatList',
      'chat_chatContent',
      'chat_P2P_file_state',
      'chat_objectInfo',
      'chat_chatContentTop',
      'user_systemConfig'
    ]),
    showTopMarquee(){
      //服务是否开启了群消息置顶
      this.isMsgTopOnByServer(isEid => {
        this.isGroupOfEid = isEid
        console.log('==========chat changed========',this.isGroupOfEid)
        return this.isGroupOfEid;
      })
      let topsArray = Object.keys(this.chat_chatContentTop);
      let hasTopMsg = false;
      if(topsArray&&topsArray.length > 0){
        hasTopMsg = true;
      }
      /*
       * chatType === 2 是群
       * isOpenChatTop 页面渲染完毕，加载跑马灯
       * hideMarquee 用户手动关闭跑马灯；
       * isExpend 群详情页展开；
       * hasTopMsg 是否有群置顶消息
       */
      return this.chatType===2 && this.isOpenChatTop && (!this.hideMarquee) && (!this.isExpend) && hasTopMsg
    },
    _isShowChat() {
      console.log('_isShowChat::')
      return this.currentView === tabView.chat
    },
    _isShowNotice() {
      console.log('_isShowNotice::')
      return this.currentView === tabView.notice
    },
    _isShowGroupFile() {
      console.log('_isShowGroupFile::')
      return this.currentView === tabView.groupFile
    },
     _isShowMsgRecord() {
      console.log('_isShowMsgRecord::')
      return this.currentView === tabView.msgRecord
    }
  },
  watch: {
    $route: {
      handler: 'getChatBaseInfo',
      immediate: true
    },
  },
  mounted() {
    let dropDom = isOSX ? this.$el : this.$refs.dropArea
    console.log('dropDom', dropDom)
    this.regDropevent(dropDom) 
  },
  components: {
    // ChatEditArea: resolve => require(['./ChatEditArea'], resolve),
    // ChatMsgListArea: resolve => require(['./chatMsgListArea'], resolve),
    // ChatGroupInfo: resolve => require(['../../Group/ChatGroupInfo'], resolve),
    ChatEditArea,
    ChatMsgListArea,
    ChatGroupInfo,
    ChatGroupFile,
    ChatGroupNotice,
    ChatTitle,
    ChatMsgAction,
    ChatSingleAside,
    ChatMutiVideo,
    ChatTabFile,
    ChatTabRecord,
    ChatMsgRecord,
    MsgTopMarquee,
    AddRemind,
    // MsgTypeRemind
  },
  methods: {
    /**
     * 获取当前会话成员，以及消息置顶
     */
    getChatBaseInfo() {
      console.log('getChatBaseInfo:::id:::', JSON.stringify(this.id), this.$route.query.id)
      if(this.chatType === 2){
        this.isEidGroup(this.id,isEid => {
          this.isGroupOfEid = isEid
          console.log('isGroupOfEid:',this.isGroupOfEid)
        } )
      }
      if (this.id!==this.$route.query.id) return;
      if (this.chatType === 0) { // 组件创建时获取会话类型
        this.chatType = this.$Service.config.getUserTypeById({ targetId: this.id })
      }
      if(!this.chat_objectInfo[this.id]) { // 群成员拉取失败，重新拉取
        this.getChatObject(this.id)
      } else {
        this.userInfo = this.chat_objectInfo[this.id];
        this.isLoadFinished = true;
      }
      this.isMsgTopOnByServer(isEid => {
        // 消息置顶没有更新推送，需要每次打开会话后拉取
        this.isGroupOfEid = isEid
          if (isEid) { 
              this.getChatMsgTopList(this.id)
          }
      })
    },
    isMsgTopOnByServer(cb) {
      this.isEidGroup(this.id,cb);
    },
    // * 处理混合消息被删除
    handleMixMsgDelete() {
      this.hasMixMsgDelete = this.isExitSelectItems
    },
    currentShowState() {
      return (this.chatType===1&&this.user_account.userId!==this.id)||this.chatType===2
    },

    // * 拖拽时显示的名称
    updateName(name) {
      this.name = name;
    },
    _handlerMsgTop(event,param){
      console.log('====_handlerMsgTop=======',param,this.id)
      if(param.id === this.id && this.isGroupOfEid){
        this.getChatMsgTopList(this.id)
      }
    },
    /**
     * 更新密聊模式
     */
    _updateEncryptMsg(bool) {
      this.isEncryptMsg = bool;
    },

    /**
     * 更新阅后即焚模式
     */
    _updateBurnMsg(bool) {
     this.isBurn = bool;
    },

    // * 更新延时模式
    _updateDelayMsg(bool) {
      this.isDelay = bool;
    },
    /** 拖拽结束 */
    handleDragEnd(e) {
      this.isDragging = false
    },
    
    /** 拖放文件 */
    handleDrop(e) {
      e.preventDefault();
      this.isDragging = false
      for (let fileNum in e.dataTransfer.files) {
        console.log('fileNum', fileNum)
        if(fileNum > 4) {
          return  this.$toast.open({duration: 3000, message: this.$t('chat.maxDropFileTip'), position: 'is-top', type: 'is-warning'});
        }
        this.upload(e, e.dataTransfer.files[fileNum]) // 发送文件或者图片
      } 
    },

    /** 拖拽离开 */
    handleDragleave(e) {
      this.isDragging = false
    },

    /** 拖拽进入 */
    handleDragEnter(e) {
      console.log('e:::', e)
      this.isDragging = true;
    },

    regDropevent(dom) {
      console.log('dom', dom)
      dom.addEventListener('drop', e => {
        e.preventDefault();
        this.handleDrop(e)
      }, false);
      dom.addEventListener('dragleave', e => {
        e.preventDefault()
        this.handleDragleave()
      }, false);
      dom.addEventListener('dragenter', e => {
        e.preventDefault()
        this.handleDragEnter(e)
      }, false);
      dom.addEventListener('dragover', e => {
        e.preventDefault()
        this.handleDragEnter(e)
      }, false);
    },
    /** 获取聊天对象数据 */
    getChatObject(userId) {
      if (this.chatType === ChatType.user || this.chatType === ChatType.app) {
        //储存对象为人
        let userArray;
        if (userId !== this.user_account.userId) {
          userArray = [[userId, this.contact_contactList[userId] || this.chat_chatList[userId]],[this.user_account.userId, this.user_account]]
        } else { // 我的设备
          userArray = [[userId, { id:userId, thumbAvatar:this.myDevice, name: this.$t('contacts.device') }]]
        }
        this.$store.commit('SET_CHAT_OBJECT', { id: userId, chatObject:  userArray })
        this.userInfo = this.chat_objectInfo[userId];
      } else {
        //此时储存对象为群
        console.log('memberList req', userId)
        this.$Service.group.getMemberList({ groupId: userId }, resp => {
          let memberList = Object.assign({}, resp)
          console.log('memberList', resp)
          this.$Service.log(`getMemberList:::  groupId:${userId} length:${memberList.members.length}     `)
          if (resp.code!==0) return;
          new Promise(resolve => {
            this.$store.commit('SET_CHAT_OBJECT', {id: memberList.members.length && memberList.members[0][1].groupId, chatObject: memberList.members})
            resolve()
          }).then(() => {
            this.userInfo = this.chat_objectInfo[this.id];
            console.log('userInfo:::::', this.userInfo)
            if (this.userInfo) {
              this.isLoadFinished = true;
            }
            if (versionCompirePro(pkg.version, '4.6') !== 0) {
              return;
            }
            console.log('getMemberListFromNet::::')
            this.$Service.group.getMemberListFromNet({groupId: userId}, offlineMemberRes => {
              // 回调返回值 removeMemberIds 删除的群成员id数组    changeMembers更新和新增群成员信息集合
              console.log('offlineMemberRes:::', offlineMemberRes)
              this.$store.dispatch("UPDATE_CHAT_OBJECT_OFFLINE", {groupId: userId, offlineMemberRes}).then(() => {
                this.userInfo = this.chat_objectInfo[this.id];
                this.isLoadFinished = true;
              });
            })
          })
        });
      }
    },
    /**
     * 【消息置顶】
     * 获取消息置顶列表，和getMessages用法一样
     * 进入会话获取置顶消息列表：1.跑马灯需要通过获取置顶数据展示 2.存入vuex后置顶列表详情组件再获取展示
     */
    getChatMsgTopList(id) {
      console.log('id:::::', id)
      this.$store.commit('CLEAR_CHATCONTENT_TOP', {})
      console.log('this.chatType:::::', this.chatType)
      if(this.chatType !== 2){
        return;
      }
      let getGroupTopMsgByIdParam = {
        groupId: id,
        msgid: 0,
        pageNum: 1,
        pageSize: 100
      };
      console.log('getGroupTopMsgByIdParam', JSON.stringify(getGroupTopMsgByIdParam));
      this.$Service.chat.getGroupTopMsgById(getGroupTopMsgByIdParam, resp => {
        // resp.msgs
        console.log('getGroupTopMsgById', resp)
        console.log('getGroupTopMsgById---msgs', resp.msgs&&JSON.stringify(resp.reminderMsgs))
        if(resp.code === 0){
          _.forEach(resp.reminderMsgs, element => {
              this.$store.dispatch('SET_CHATCONTENT_TOP', element)
          })
        }
        else{
          this.$Service.log(`getGroupTopMsgById:${resp.code},id:${id}`);
        }
      })
    },

    handleRightAt(arg) {
      console.log('arg:::', arg)
      this.rightAtId = arg
    },

    changeExpends(arg) {
      console.log('changeExpend', arg)
      this.isExpend = arg;
    },

    /**
     * 回调 选中的转发条数 控制是否显示转发弹出窗
     * @param {Number} size - 选中的转发条数
     */
    msgSelectLength(size) {
      this.isExitSelectItems = size !== 0;
    },

    /**
     * 右键'更多' 控制编辑框是否覆盖显示更多的右键选项
     * @param {Boolean} value - true：打开转发 false：关闭
     */
    handleActionBoxShow(value) {
      this.isActionForward = false;
      this.hasMixMsgDelete = false;
      this.isOpenAction = value;
    },
    
    closeAction() {
      this.isOpenAction = false;
      this.isActionForward = false
      this.hasMixMsgDelete = false
    },

    //* 切换聊天页面tab
    changeTab(arg) {
      this.currentActive = arg.index;
      this.currentView = arg.view
      console.log('is File', this.$Service.file.isTransmittingInTarget({targetId: this.id}))
      if (this.tabViewArray['file'] && this.$Service.file.isTransmittingInTarget({targetId: this.id})) {
        console.log('changeTab one')
        if (this.tabViewArray.msgRecord) {
          this.$delete(this.tabViewArray, 'msgRecord')
        }
      } else {
        console.log('changeTab two')
        this.tabViewArray = {}
      }
   
      if (arg.index) {
        this.$set(this.tabViewArray, arg.view, {view: arg.view, components:arg.components})
      }
      console.log('tabViewArray', this.tabViewArray)
    },

    /** 是否展开群成员列表 */
    showExpend() {
      if (this.rtcFile && Object.keys(this.rtcFile).length) {
        this.$dialog.confirm({
          confirmText: this.$t('common.sure'),
          cancelText: this.$t('common.cancel'),
          message: this.$t('account.sendTerPrompt'),
          onConfirm: () => { 
            this.$store.commit('UPDATE_FILE_DEL_MODE', true)
            this.$store.commit('REMOVE_CHATTER_RTCLIST', this.id) 
            setTimeout(() => {
              this.isExpend = false;
              this.$store.commit('UPDATE_FILE_DEL_MODE', false)
            })
           }
        });
        return
      }
      console.log('currentActive:::',this.currentActive)
      if (this.currentActive!==0) {
        this.currentActive = 0;
        this.currentView = 'chat'
        this.isExpend = true;
      } else {
        this.isExpend = !this.isExpend;
      }
      if(!this.chat_objectInfo[this.id]) {
        this.$Service.log('拉取群成员失败后，展开侧边栏再次拉取数据...')
        this.getChatObject(this.id)
      } else {
        this.userInfo = this.chat_objectInfo[this.id];
        this.isLoadFinished = true;
      }
    },


    reEditMsg(arg) {
     if ( Object.keys(this.rewriteText).length ) {
         this.rewriteText = {}; 
      }
      setTimeout(() => { this.rewriteText = arg })
    },

    clearReeditText() {
      this.rewriteText = {}; 
    },
    showMsgRemind(msgBody) {
      this.isAddRemind = true
      this.showMsgRemindBody = msgBody
      console.log('msgBody',msgBody)
    },
    settingMethods() {
      this.isAddRemind = false;
          this.$toast.open({
            message: this.$t('common.setUpSuccessfully'),
            position: "is-top",
            type: "is-success"
          });
      console.log('接收到触发事件',true);
    }
  }
};
</script>
<style lang="scss" scoped>
.chat-content {
  flex: 1;
  height: 100%;
  display: flex;
  flex-direction: column;
  position: relative;
  
  &:hover .drop-area{
    pointer-events: none;
  }
  .drop-area {
    position: absolute;
    left: 0px;
    top: 0px;
    width: 100%;
    height: 100%;
    opacity: 0;
    z-index:41;
    &.drop-box {
    border:  dashed 2px $--border-color-dark;
    border-radius: 8px;
    background: rgba(255, 255, 255, .8);
    display: flex;
    align-items: center;
    justify-content: center;
     opacity: 1;
      .drop-notify {
        font-weight: bolder;
        font-size:$--font-size-big;
        color: $--border-color-dark;
        pointer-events: none;
        width: 100%;
        text-align: center;
        @include ellipsis;
      }
    }
  }
  .tab-view-item {
     flex: 1;
     display: flex;
     flex-direction: column; //fit xp
     height:0px;//fit xp
   }
  .content-area {
    flex: 1;
    display: flex;
    height: 1px; //fit xp
    overflow: auto;
    .chat-detail {
      flex: 1;
      display: flex;
      flex-direction: column;
      position: relative;
    }
  }
  .btn-expend {
    font-size: 17px;
    position: absolute;
    // @include z-index(btn);
    z-index: 40;
    top: 7px;
    right: -6px;
    text-align: center;
    // color: get-grey-color(darken-1);
    color: #bdbdbd;
    width: 40px;
    cursor: pointer;
    transition: .5s;
  }
  .expend-icon {
    transform: rotate(180deg);
    transition: .5s;
  }
}
</style>
