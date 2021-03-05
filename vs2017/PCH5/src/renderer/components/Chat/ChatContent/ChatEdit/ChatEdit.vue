<template>
  <div  :date-type="computedEncrypt"  :class="[switchMode, `editContainer_${id}`]" ref="editContainer">
    <!-- 操作区域 文件上传 开始视频会议 -->
    <div class="content-area" :class="contentAreaClass">
      <!-- //<div class="edit-drag-line" @mousedown="bindResize"></div> -->
       <!-- <v-button v-if="id!== user_account.userId && chatType!==3" :ripple='false' class="edit-more-operate theme-hover-bgc_font"  @click="isShowEditBox=!isShowEditBox">
       <v-tooltip class="tool-tips" type="is-primary" position="is-top"  :lable="$t('chat.more')" always></v-tooltip>
       <i class="icon" v-html="editMoreIcon"></i>
      </v-button> -->
      <div class="edit-drag-line" @mousedown="bindResize"></div>
      <div  class="edit-more-operate theme-hover-bgc_font" v-show="showTool">
        <i class="icon more-icon" v-html="editMoreIcon" @click.self.stop="isShowEditBox=!isShowEditBox"></i>
        <v-tooltip class="tool-tips" type="is-primary" position="is-top"  :lable="$t('chat.more')" always></v-tooltip>
      </div>
    <!-- 编辑框 -->
    <div class="chat-input-area" @click="handleEditAreaFocus">
      <at class="input-area" @keydown.native="handleWinPosOffset"  @mounteds ="editMounted" @insertAt="insertAt" :chatType='chatType'  :members="isShowList&&chatType === 2?orderedPinYin:[]" name-key="remark"  :isShowList="isShowList" @change-relatedUsers="changeRelatedUsers"  @handleDeleteAll="_handleDeleteAll"  @hasAt="hasAt">
        <div class="edit-textarea"
            id='edit-box'
            ref="editArea"
            contenteditable="true"
            @keydown="keyChange"
            @input="editInput"
            @click.right="computedClipboardPos"
            @paste="editClipboard"
            v-show="showTool">
        </div>
        <div v-show="!showTool">{{eidtips}}</div>
      <!-- <div id="edit-box" style="width: 400px;height: 200px;"     @click.right="computedClipboardPos" ref="editArea" @keyup="deletes" :contenteditable="true"></div> -->
      </at>
    </div>
     <!-- 发送按钮 -->
      <div class="input-operate-area" v-show="showTool">
        <!-- 发送表情 -->
         <div class="input-operate-btn">
           <v-tooltip class="tool-tips" type="is-primary" position="is-top"  :lable="$t('chat.sendEmoji')" always></v-tooltip>
           <i class="icon emoji-btn" ref="emoji" @click.self.stop="clickEmoji" >&#xe70b;</i>
        </div>
          <!-- 发送文件 -->
         <div class="input-operate-btn" >  
           <v-tooltip class="tool-tips" type="is-primary" position="is-top"  :lable="$t('chat.sendFile')" always></v-tooltip>
           <i class="icon upload-file"  >&#xe66e;<input class="upload" type="file"  title=" " @change='upload($event)' /></i>
          </div>
        <!-- 截图 -->
         <div class="input-operate-btn screen-shot-btn" v-if='chatType!==3' @mouseenter.stop="isShowScreenList=true" :title='getScreenShotkey' @mouseover.stop="isShowScreenList=true" @mouseout.stop="isShowScreenList=false">
           <!-- <v-tooltip class="tool-tips" type="is-primary" position="is-top"  lable="截图" always></v-tooltip> -->
           <i class="icon capture-btn" @click.stop="newSubWindowScreenShot('AUTO')" >&#xe78e;</i>
           <ul class="screen-opera-list" ref="screenlist" title=''>
             <li class="screen-opera-item" @click.stop="newSubWindowScreenShot('NORMAL')" title=''>{{$t('chat.screenshot')}}</li>
             <li class="screen-opera-item" @click.stop="newSubWindowScreenShot('HIDE')" title=''>{{$t('chat.hideWindow')}}</li>
           </ul>
         </div>

         <div class="input-operate-btn" v-if="chatType===3">
           <v-tooltip class="tool-tips" type="is-primary" position="is-top"  :lable="$t('chat.switch')" always></v-tooltip>
           <i class="icon" @click="$emit('changeEditType')" >&#xe67b;</i>
         </div>
      </div>
        
    </div>
    <!-- 表情列表 v-if="isShowEmoji"-->
    <transition name="emoji-slide-up">
      <Emoji v-if="isShowEmoji" v-click-outside="onClickOutside" :isEncryptMsg="isEncryptMsg" class="v-emoji" @select="selectEmoji"  :targetId="id"></Emoji>
      <!-- <create-meeting  v-if="isShowCreateMeeting" v-click-outside="onClickOutside" class="v-meeting" :membersInfo="userInfo" :myId="user_account.userId" :groupId="this.$route.query.id" @close="isShowCreateMeeting=false" :groupName="this.$route.query.name"></create-meeting> -->
    </transition>
    <!-- 空消息提示区域 -->
    <div  class="message-prompt-area">
        <p v-show="isMsgtip" class="empty-message-prompt">{{msgTip}}</p>
        <p class="change-send-way" v-text="computedSendMsgKey"></p>
    </div>
    <div class="classic-send-area">
       <p v-show="isMsgtip" class="empty-message-prompt">{{msgTip}}</p>
       <v-button   v-show="showTool" class="btn-send" @click="checkMsg" :title="computedSendMsgKey">{{$t('contacts.send')}}</v-button>
    </div>
    <ul v-if="isShowEditBox" @click="isShowEditBox = false"  class="edit-more-operate-list" v-click-outside="onClickOutside">
      <div class="edit-menu">
        <!-- <li :class="item.class" v-for="item in chatEditMenu" :key="item.type" @mouseover.passive="isSubMenuShow=item.type==='submenu'">
          <i class="icon" v-html="item.icon"></i><span>{{ item.text }}</span>
        </li> -->
        <!-- 参阅材料 -->
      <li class="theme-hover-bgc_font" v-if="chatType === 2 && this.groupInfo.groupType == 'eid' && !isShowBook " @click="referMaterials" >
        <i class="icon" >&#xe6a8;</i><span>{{$t('cppcc.referMaterials')}}</span>
      </li>
        <!-- 发言汇编 -->
      <li class="theme-hover-bgc_font" v-if="chatType === 2 && this.groupInfo.groupType == 'eid'  && !isShowBook" @click="speeches">
        <i class="icon" >&#xe6ad;</i><span>{{$t('cppcc.compilationSpeeches')}}</span>
      </li>
      <!-- 发言统计 -->
      <li class="theme-hover-bgc_font" v-if="chatType === 2 && this.groupInfo.groupType == 'eid' && isShowCountSketch && !isShowBook" @click="speechCount" >
          <i class="icon" >&#xe6a7;</i><span>{{$t('cppcc.speechCount')}}</span>
      </li>
      <!-- 发言综述 -->
      <li class="theme-hover-bgc_font" v-if="chatType === 2 && this.groupInfo.groupType == 'eid' && isShowCountSketch && !isShowBook" @click="speechSketch">
          <i class="icon" >&#xe6b0;</i><span>{{$t('cppcc.speechSketch')}}</span>
      </li>
      <!-- 读书群参阅材料 -->
      <li class="theme-hover-bgc_font" v-if="chatType === 2 && this.groupInfo.groupType == 'eid' && isShowBook" @click="book('readingDocument')" >
          <i class="icon" >&#xe6a8;</i><span>{{$t('cppcc.readingDocument')}}</span>
      </li>
      <!-- 读书群精华区 -->
      <li class="theme-hover-bgc_font" v-if="chatType === 2 && this.groupInfo.groupType == 'eid' && isShowBook" @click="book('essenceArea')" >
          <i class="icon" >&#xe635;</i><span>{{$t('cppcc.essenceArea')}}</span>
      </li>
      <!-- 历史记录 -->
      <li class="theme-hover-bgc_font" v-if="chatType === 2 && this.groupInfo.groupType == 'eid'" @click="MsgHistory">
        <i class="icon" >&#xe61f;</i><span>{{$t('chat.msgRecord')}}</span>
      </li>
        <!-- 视频会议消息  -->
      <li class="theme-hover-bgc_font"  v-if="!platformIsLinux && chatType===2 && !isWinXpVersion" @click="HandleMeeting">
        <i class="icon" >&#xe631;</i><span>{{$t('groups.videoCon')}}</span>
      </li>
        <!-- 音视频入口  -->
        <li class="theme-hover-bgc_font muti-media" v-if="!platformIsLinux && chatType===1">
          <i class="icon" >&#xe669;</i><span>多媒体</span>
      
          <video-call-menu class="sub-menu-hover" :isBurn="isBurn"></video-call-menu>
        </li>
        <!-- 密聊消息 isLock 1 为加密消息 2 为加密但处理过的消息 -->
        <!-- <li class="theme-hover-bgc_font" v-if="isAllowPrivate" :class="{'secrected-msg' : isEncryptMsg}" @click="setPrivateMsg">
          <i class="icon" v-html="isEncryptMsg? '&#xe610;': '&#xe657;'"></i><span>{{$t('chat.EncryptedMessage')}}</span>
        </li> -->
        <!-- 抖一抖 isFlash -->
        <li class="theme-hover-bgc_font" :class="{'disable-direct': isDisableDirectMsg}"  v-if="chatType===1" @click="sendShakeMsg">
          <i class="icon" >&#xe65a;</i><span>{{$t('chat.shake')}}</span>
        </li>
        <!-- 延迟消息 isDelay -->
        <li class="theme-hover-bgc_font" :class="{'delay-msg':isDelay, 'disable-direct': isDisableDirectMsg}" v-if="chatType!==3" @click="switchDealyMode">
          <i class="icon" >&#xe65c;</i><span>{{$t('chat.delayMessage')}}</span>
        </li>
        <!-- 阅后即焚消息 isBurn -->
        <li class="theme-hover-bgc_font"  :class="{'burned-msg':isBurn, 'disable-direct': isDisableDirectMsg}" v-if="chatType!==3 && chatType!== 2" @click="switchBurnMode">
          <i class="icon" >&#xe635;</i><span>{{$t('groups.burnChat')}}</span>
        </li>
        <!-- 阅后回执 -->
        <li class="theme-hover-bgc_font"  :class="{'receipt-msg':isReceipt, 'disable-direct': isDisableDirectMsg}" v-if="chatType!==3" @click="switchReceiptMode">
          <i class="icon" >&#xe6bd;</i><span>{{$t('chat.receiptMessage')}}</span>
        </li>
        <!-- 名片消息  -->
        <li class="theme-hover-bgc_font"  v-if="chatType!==3" @click="sendCardMsg">
          <i class="icon" >&#xe6b1;</i><span>{{$t('chat.cardMessage')}}</span>
        </li>            
        <!-- 位置消息  -->
        <li class="theme-hover-bgc_font" v-if="clientConfig_chat.openSendLocationMsg" @click="openWindowMap">
          <i class="icon" >&#xe622;</i><span>位置消息</span>
        </li>
        <!-- 潜水者名单  -->
        <!-- <li class="theme-hover-bgc_font"  v-if="isDividerShow" @click="getDiverList">
          <i class="icon" >&#xe6b1;</i><span>潜水者名单</span>
        </li>  -->
      </div>     
    </ul>

    <!-- 延迟消息 -->
     <v-modal v-if="isShowDelayBox" cardSize="delay-msg-box"  @close="isShowDelayBox= false">
      <msgTypeDelay @sendDelayMsg="sendDelayMsg" @close="isShowDelayBox= false" @cancel="cancelSendDelay"></msgTypeDelay>
     </v-modal>
    
      <v-menu v-if="isShowCopyClipboard"
              :menuList="[$t('chat.paste')]" 
              :currentPos="currentPos"
              @close="isShowCopyClipboard = false" 
              @selectItem="rightClickCopy" >
      </v-menu>
      <cppcc-speeches :id="id" v-if="isSpeeches" @closeSpeack='isSpeeches = false'></cppcc-speeches>
      <cppcc-refer-materials :id="id" v-if="isReferMaterials" @closeRefer='isReferMaterials = false'></cppcc-refer-materials>
      <cppcc-speech-count :id="id" :lastSendTime="lastSendTime" v-if="isSpeechCount" @closeCount='isSpeechCount = false'></cppcc-speech-count>
      <cppcc-speech-sketch :id="id" :lastSendTime="lastSendTime" v-if="isSpeechSketch" @closeSketch='isSpeechSketch = false'></cppcc-speech-sketch>
      <cppcc-book :id="id" :pageType="pageType" v-if="isBook" @closeBook='isBook = false'></cppcc-book>
      <cppcc-msg-history v-if="isHistory" :id="id" @closeHistory='isHistory = false'></cppcc-msg-history>
      <chat-search-list v-if="isCard||isReadReceipt" :id="id" :type="isReadReceipt?'receipt':'card'" :isEncryptMsg ="isEncryptMsg" :isBurn='isBurn' @close="isCard=false,isReadReceipt=false,isReceipt=false" @at-someone="handleAtSome"></chat-search-list>
      <create-group-meeting v-if="isMeeting" :isInviteMember="false" :isBurn="isBurn" :groupInfo="groupInfo" @close="isMeeting=false"></create-group-meeting>  
      <chat-divider-list v-if="isDivider" :id="id" :dividerIdListIds="dividerIdListIds" @close="isDivider=false"></chat-divider-list>
  </div>
</template>
<script>
  import axios from 'axios';
import { mapGetters } from 'vuex'
import { encryptionPassword, signalMonitor} from '../../../../../comm/util'
import { isWindows,isOSX,isWinXp,isLinux } from '../../../../../comm/is'
import { toUnicode, utf16toEntities, removeHtml, escapeEmoji, escapeHTMLString } from '../../Emoji/emoji'
import { placeCaretAtEnd, insertNode,   insertAtCursor, getTextWidth, canvasText} from '../../At/at.js'
import { MsgTxt, MsgImg, MsgFile, MsgWebLink, MsgMap } from '../../Msg'
import VideoCallMenu from './VideoCallMenu.vue'
import ChatSearchList from '../../Msg/ChatSearchList.vue'
import CreateGroupMeeting from './../../../Group/CreateGroupMeeting.vue';
import MsgMxin from '../../msgMixin'
import msgTypeDelay from '../../Msg/MsgTypeDelay.vue'
import vClickOutside from '../../v-click-outside/index.js';
import CppccSpeeches from '../CppccSpeeches.vue';
import CppccReferMaterials from '../CppccReferMaterials.vue';
import CppccSpeechCount from '../CppccSpeechCount';
import CppccSpeechSketch from '../CppccSpeechSketch';
import CppccBook from '../CppccBook';
import CppccMsgHistory from '../CppccMsgHistory.vue'
import { stringify } from 'querystring';

const fs = require("fs");
const plist = require("plist");
const { clipboard, remote, desktopCapturer } = require('electron')
const screenShotComplete = remote.getGlobal('setScreenShotCb')
const getWindowStatus = remote.getGlobal('getWindowStatus')
/** 敏感词模式 */
const BADWORDMODE = {
  No_FILTER: '0',
  REPLACE_START: '1',
  NOTALLOW_SEND: '2'
}
const SCREENDISPLAY = {
  NORMAL: 'NORMAL',
  HIDE: 'HIDE',
  AUTO: 'AUTO'
}
const EDITMODEL = {
  CLASSIC: 'editBox_classic',
  STANDARD: 'editBox_standard'

}
export default {
  data() {
    return {
      isHistory: false,
      isReferMaterials: false,
      isSpeeches: false,
      isSpeechCount: false,
      isSpeechSketch: false,
      isShowBook: false,
      isBook: false,
      isShowCountSketch: false,
      lastSendTime:'',
      isClassic: false,
      platformIsLinux: isLinux,
      platformIsWin: process.platform === 'win32' ? true:false,
      isShowList: false, // 是否显示@列表
      isShowEmoji: false, // 是否显示表情
      isAllowPrivate: true, //是否群允许密聊
      // isAllowBurn: true, //是否群允许阅后即焚
      isShowEditBox: false, // 是否打开更多操作
      // isShowCreateMeeting: false, // 是否显示创建视频会议
      isShowDelayBox: false, // 是否显示延时消息选择框
      isShowCopyClipboard: false, // 是否显示粘贴板
      // isDelay: false,
      isGetPrivateMsgPwd: false,
      relatedUsers: [], // 存放@相关用户数组
      editArea: null, // 编辑框容器
      chatObject: [],
      isMsgtip: false,
      msgTip: '',
      send_msg_key: '',
      lastShakeMsg: 0,
      delayTimes: 0,
      msgContent: '',
      // lists: [],
      msgAtList: [],
      isCard: false,
      isMeeting: false,
      groupInfo:{
          groupId: this.id
      },
      lastScreenShot: 0,
      currentPos: {
        // 记录右键列表的横纵坐标
        top: String,
        left: String
      },
      isShowScreenList: false,
      editMoreIcon: '',
      isBeginInput: false,
      inputTimer: {},
      isDisableDirectMsg: false,
      isReceipt: false,
      hideMainWindow:false,
      isReadReceipt: false,
      isDivider: false,
      dividerIdListIds: [],
      groupInfo:{},
      showTool:true,
      eidtips:''
    }
  },
  mixins: [MsgMxin],
  watch: {
    isOpen(old, newValue) {
      if (this.isOpen) {
        this.$nextTick(() => {
          this.handleScreenshotComplete();
        })
        placeCaretAtEnd(this.$refs.editArea)
      } 
    },

    /** 重新编辑文本 */
    rewriteText() {
      if (Object.keys(this.rewriteText).length) {
        this.relatedUsers = this.rewriteText.relatedUsers
        this.$refs.editArea.innerHTML = escapeEmoji(this.rewriteText.msgReEdit)
        placeCaretAtEnd(this.$refs.editArea)
      }
    },

    rightAtId() {
      if (Object.keys(this.rightAtId).length) {
        // console.log('rightAtId:::::', this.rightAtId)
        // this.relatedUsers.push(this.rightAtId.id)
        // this.isShowList = true
        // let ramark = this.userInfo[this.rightAtId.id].remark || this.userInfo[this.rightAtId.id].name
        // this.$Service.log(`has@    ${this.rightAtId.id || ''} `)
        // return insertAtCursor(this.$refs.editArea, `@${ramark} `)
        this.insertAt({id: this.rightAtId.id})
      }
    }
  },
  created(){
    let loginInfo =JSON.parse(localStorage.getItem("loginInfoPc"))
    //是否显示发言统计、发言综述
    axios.get(`http://${this.$config.clientConfig.auth.webServer}/cppcc-subjectdiscuss/api/summarize/enterGroup`, {
      params: {
        groupId: this.id ,
        deviceId:loginInfo.deviceId,
        client_id:'',
        deviceModel:'pc',
        deviceType:'pc',
      },
      headers: {
        Authorization:'Bearer '+loginInfo.access_token
      }
    }).then(res=>{
      console.log(res,"是否显示");
      if(res.data.resultCode==200){
        this.isShowCountSketch=res.data.data.houldPullStats;
        this.lastSendTime=res.data.data.lastSendTime;
      }
    }).catch(error=>{
      console.log(error,'是否显示错误');
    })
    //是否读书群
    axios.get(`http://${this.$config.clientConfig.auth.webServer}/cppcc-questionnaire/api/bookDiscuss/isBook`, {
      params: {
        groupId: this.id ,
        deviceId:loginInfo.deviceId,
        client_id:'',
        deviceModel:'pc',
        deviceType:'pc',
        Authorization:`Bearer ${loginInfo.access_token}`
      }
    }).then(res=>{
      console.log(res,"是否读书群");
      if(res.data.resultCode==200){
        this.isShowBook=res.data.groupType==='book';
      }
    }).catch(error=>{
      console.log(error,'是否显示读书群错误');
    })
  },
  /** 获取是否处于密聊模式 */
  mounted() {
    this.$Service.group.getGroupInfo({groupId: this.id},resp =>{
      this.groupInfo = resp.info
      console.log('groupInfo:::::::::',this.groupInfo)
    })
    this.$ipc.on("map-message", this.receiveMapMessage);
    this.$nextTick(() => {
      this.getIsPrivateModel();
      this.handleScreenshotComplete();
    })
  },

  beforeDestroy() {
    this.$ipc.removeListener('map-message', this.receiveMapMessage)
    /**  清空正在输入状态 */
    if (this.chatType === 1) {
      if (this.inputTimer) {
        clearInterval(this.inputTimer)
      }
      this.setInputState(1)
    } 
  },

  /**
   * 点击指令
   * 点击除元素自身外的区域 触发事件
   * 目前用于关闭区域
   */
  directives: {
    clickOutside: vClickOutside.directive
  },

  methods: {
    /**
     * @breif 打开地图插件窗口
     */
    openWindowMap() {
      let mapPath = 'vrv-static/plugins/mappreview/index.html?mode=normal&isSearch=true'
      this.$ipc.send('new-window', { winUrl: mapPath, winType:'MapPreview',  winTitle: '地图详情', shapeType:'normal'}) 
    },
    /**
     * @breif 接收地图插件位置信息，弹框提示用户是否发送位置消息
     * @param {Object} map - 位置详情
     */
    receiveMapMessage(event, map) {
      this.$dialog.confirm({
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        message: '确定发送当前位置消息?',
        onConfirm: () => {
          this.sendMap(map)
        }
      });
    },
    /**
     * @breif 发送位置消息
     * @param {Object} map - 位置详情
     */
    sendMap(map) {
      let msgbase = {
        fromId: this.user_account.userId,
        targetId: this.id,
        localId: new Date().getTime(),
        msgType: 4,
        msgId: encryptionPassword().toString(),
        time: new Date().getTime(),
        latitude: map.lat,
        longitude: map.lng,
        name: map.name
      };
      let msgMap = new MsgMap(msgbase, 1);
      this.$store.dispatch('SET_CHATCONTENT', msgMap)
    },
    /**
     * @breif 获取群潜水者名单
     */
    getDiverList() {
      this.$Service.chat.getGroupDivers({groupId: this.id}, resp => {
        this.isDivider = true
        console.log('resp::::::', resp)
        // 为解决服务不支持该功能的情况，不需要判断code，code不为0也显示空潜水者名单列表
        this.dividerIdListIds = [...resp.userIDs]
      });
    },
    clickEmoji(){
      this.isShowEmoji = !this.isShowEmoji
    },
    handleEditAreaFocus(e) {
      console.log('============>e', e)
      this.$refs.editArea.focus();
    },
    handleAtSome(item) {
      this.isReceipt = false;
      this.isReadReceipt = false;
      this.$refs.editArea.focus();
      var sel = window.getSelection();
      var range = document.createRange();
      range.selectNodeContents(this.$refs.editArea);
      range.collapse(false);
      sel.removeAllRanges();
      sel.addRange(range);
      this.insertAt({id: item.id});
    },
    // 处理截图完成后返回
    handleScreenshotComplete(){
      screenShotComplete((code) => {
        this.$Service.log(`screenShotWinClose id:::${this.id||''}  code:${code}`)
        if(this.hideMainWindow){
          this.$ipc.send('control-main-window',true);
          this.hideMainWindow = false;
          if(!isWindows && (code === 0)){
            this.$Service.log(`隐藏窗口截图完成了,处理剪切版`)
            this.handleClipboard()
            return;
          }
        }
        if(code === 0&&getWindowStatus()){
          this.handleClipboard()
        }
      })
    },
    /**
     * 处理@+PgOn引发的窗口位置偏移，禁用浏览器默认行为
     */
    handleWinPosOffset(e) {
      console.log('keyCode:::', e.keyCode)
      if (e.keyCode === 34 || e.keyCode === 33) {
        e.preventDefault()
        e.stopPropagation()
      }
    },
    insertAt({id}) {
      this.$Service.log(`insertAt    ${id}`)
      let ramark = id === this.id ? this.$t('chat.allMem') : this.userInfo[id].remark || this.userInfo[id].name
      var canvas = document.createElement("canvas");
      // * 计算字符串长度
      let canvansWidth = getTextWidth("14px","微软雅黑",`@${ramark}`).width + 4
      console.log('canvansWidth', canvansWidth)
      canvas.width = canvansWidth
      canvas.height = 18;
      var context = canvas.getContext("2d");
      context.fillStyle = '#fff';  //设置填充的背景颜色
      context.fillRect(0,0,  canvansWidth, 18); //绘制 800*300 像素的已填充矩形：
      // 绘制中文字示例，参数（context对象，要写的字，字体，颜色，绘制的高度）
      canvasText(context, `@${ramark}`+ " ", "14px  微软雅黑", '#1E88E5', canvas.width/2, 12);
      var source = '<img  class="edit-at-image" type="at" alt="img" value="@'+ramark+'  " title="' + id + '" src="' + canvas.toDataURL("image/jpg") + '">'
      insertNode(this.$refs.editArea, source)
      this.isShowList = false;
    },
    /**
     * 表情框 工具框 音视频会议列表 @列表
     * 展开情况下 点击空余地方 关闭
     */
    onClickOutside(event) {
      console.log('Clicked outside. Event: ', event)
      if (this.isShowList) this.isShowList = false
      if (this.isShowEditBox) this.isShowEditBox = false
      if (this.isShowEmoji) this.isShowEmoji = false
      // if (this.isShowCreateMeeting) this.isShowCreateMeeting = false
    },

    /**
     * 编辑框准备就绪
     * 编辑框获取焦点
     */
    editMounted() {
      console.log('Clicked editMounted')
      placeCaretAtEnd(this.$refs.editArea)
    },

    // 处理剪切板文件
    clipboardFile() {
      let fileInfo={};
      if(isOSX){
        if(!clipboard.read('public.file-url')) {
          return false;
        }
        let path = plist.parse(clipboard.read('NSFilenamesPboardType'))[0];
        if(path) {
          fileInfo.path = path;
          let arr = path.split('/');
          fileInfo.name = arr[arr.length-1];         
        }
      }
      else{
        let path = isWinXp?this.$Service.file.readFilePath(null).filePaths[0]:clipboard.readBuffer('FileNameW').toString('ucs2').replace(new RegExp(String.fromCharCode(0), 'g'), '');
        console.log('path',path);
        if(path) {
          fileInfo.path = path;
          let arr = path.split('\\');
          fileInfo.name = arr[arr.length-1];
        }
      }
      if(fileInfo.path){
        fs.stat(fileInfo.path, (err, stats)=> {
          if (err) {
           return console.error(err);
          }
          fileInfo.size = stats.size;
          fileInfo.isClipboardFile = true;
          if(stats.isFile()){
            this.upload(null, fileInfo);       
          }
        });
        return true;
      }
      return false;
    },
    
    rightClickCopy() {
      this.handleClipboard()
      this.isShowCopyClipboard = false;
    },

    /** 编辑框剪贴板 */
    editClipboard(e) {
      e.stopPropagation()
      e.preventDefault() // 取消默认浏览器效果
      this.handleClipboard()
    },

    /** 处理截切板事件 */
    handleClipboard() {
      if(!this.$refs.editArea) return;
      if (this.$refs.editArea.innerText.length > 12000) {
        console.log('extra::::')
        return
      }
      if(this.clipboardFile()) {  /** 处理剪切板文件 */
        return;  
      }
      const sel = window.getSelection();
      const range = sel.getRangeAt(0);
      if (!range) return
      console.log('range', range)
      console.log('text', range.toString())
      // range.deleteContents()
      if (range.commonAncestorContainer && (range.commonAncestorContainer.className === 'edit-textarea' ||  range.commonAncestorContainer.parentElement.className === 'edit-textarea')) {
        range.deleteContents()
      } else {
        console.log('text:::::::::>>>>>>>>>', range)
        placeCaretAtEnd(this.$refs.editArea)
      } 
      /**
       * 处理鼠标选择光标复制
       */
      let clipboardText = clipboard.readText()
      let regs = /[\uD83C|\uD83D|\uD83E][\uDC00-\uDFFF][\u200D|\uFE0F]|[\uD83C|\uD83D|\uD83E][\uDC00-\uDFFF]|[0-9|*|#]\uFE0F\u20E3|[0-9|#]\u20E3|[\u203C-\u3299]\uFE0F\u200D|[\u203C-\u3299]\uFE0F|[\u2122-\u2B55]|\u303D|[\A9|\AE]\u3030|\uA9|\uAE|\u3030/gi;
      let doodReg = /\[[\u4e00-\u9fa5]{1,4}\]/g;
      if (regs.test(clipboardText) || doodReg.test(clipboardText)) {
        let container = document.createElement('div');
        let text = isWinXp?clipboard.readHtml():clipboard.readHTML();
        container.innerHTML = text
        this.handleCopyAtMsg(container)
        if (text) {
          clipboardText = removeHtml(container, container.innerHTML).content
        }
        clipboard.writeText(clipboardText)
        return this.paseteInsetNode(escapeEmoji(clipboardText))
      }

       /**
       * 处理右键+光标复制
       */
      if (clipboardText) {
        console.log('readHTML', isWinXp?clipboard.readHtml():clipboard.readHTML())
        let container = document.createElement('div');
        let text = isWinXp?clipboard.readHtml():clipboard.readHTML();
        container.innerHTML = text
        if ((isWinXp?clipboard.readHtml().indexOf('class="v-text-emoji"') !== -1:clipboard.readHTML().indexOf('class="v-text-emoji"') !== -1)|| 
        (isWinXp?clipboard.readHtml().indexOf('class="edit-image"') !== -1:clipboard.readHTML().indexOf('class="edit-image"') !== -1)){
          text =  removeHtml(container, container.innerHTML).content
          return this.paseteInsetNode(escapeEmoji(text))
        } 
        else {
          console.log('text:::::::::::::::', clipboardText)
          clipboardText = this.handleCopyAtMsg(container)
          return this.paseteInsetNode(escapeHTMLString(clipboardText))
        }
      }

      /**
       * 判断是否有图片
       */
      let isReadImageEmpty = clipboard.readImage().isEmpty()
      console.log('isReadImageEmpty', isReadImageEmpty,clipboard.readImage())
      this.$Service.log(`readImage isEmpty      ${isReadImageEmpty}`)
      if (isReadImageEmpty) return
      let fileName = `clipboardImg${encryptionPassword()}.jpg`
      let thumlSave = `${this.user_imgPath}${fileName}`
      let thumbImageInfo = this.$images.thumbImage(clipboard.readImage().toDataURL(), false)
      this.$fs.writeFileSync(thumlSave, thumbImageInfo.originBuffer)
    
      if (this.isDelay) { // 延时消息不支持发送图片
        this.$toast.open({duration: 3000, message: this.$t('chat.delayFileTip'), position: 'is-top', type: 'is-warning'});
        // this.isDelay = false
        this.$emit('updateDelayMsg', false)
      }
      var source = '<img class="edit-image" type="img" alt="img" title="' + fileName + '" src="' + thumlSave + '">'

      insertNode(this.$refs.editArea, source)
      setTimeout(() => {
        this.handleClickEditImg(fileName)
        if (this.$refs.editArea.scrollTop !== this.$refs.editArea.scrollHeight) {
        this.$refs.editArea.scrollTop = this.$refs.editArea.scrollHeight
        }
      })
    },
    /**
     * 复制的内容包含@群成员，将canvas图片转换为文字
     */
    handleCopyAtMsg(container) {
      if (isWinXp?clipboard.readHtml()&&clipboard.readHtml().indexOf('class="edit-at-image"') !== -1:clipboard.readHTML()&&clipboard.readHTML().indexOf('class="edit-at-image"') !== -1) {
        let images = container.getElementsByTagName('img')
        for (const img of images) {
          let text = clipboard.readText()
          let imgAtValue = img.getAttribute('value')
          clipboard.writeText(text.replace('img', imgAtValue))
        }
      }
      return clipboard.readText()
    },

    // * 处理编辑框内的图片点击事件
    handleClickEditImg(fileName) {
      let editImg = Array.from(this.$el.getElementsByClassName('edit-image')); 
      let currentImgIndex = _.findIndex(editImg, function(o) { return o.title == fileName } )
      editImg[currentImgIndex].ondblclick = () => {
        console.log('editImg>>>>>')
        let editImg = Array.from(this.$el.getElementsByClassName('edit-image')); 
        let currentIndex = _.findIndex(editImg, function(o) { return o.title == fileName } )
        let imgArray = [];
        _.forEach(editImg, function(o) {imgArray.push(o.src) })
        let imgPath = `vrv-static/plugins/imagepreivew/index.html?mode=editImg&thumbImg=${editImg[currentImgIndex].src}&imgs=${JSON.stringify(imgArray)}&currentIndex=${currentIndex}`
        let winUrl = `${imgPath}&hasImgSaveAs=${!this.chat_chatDicValue['isSavePicturesToAlbums'] || this.chat_chatDicValue['isSavePicturesToAlbums'] === '1'}`
        this.$ipc.send('new-window', { winUrl: winUrl, winType:'Imagepreivew',  winTitle:`${this.$t('chat.pictureViewer')}`, shapeType:'normal', targetId:''}) 
      }
    },

    // * 粘贴插入节点
    paseteInsetNode(content) {
      console.log('content:::', content)
      insertNode(this.$refs.editArea, content)
      if (this.$refs.editArea.scrollTop !== this.$refs.editArea.scrollHeight) {
        this.$refs.editArea.scrollTop = this.$refs.editArea.scrollHeight
      }
    },

    /**
     * 计算剪贴板右键位置
     */
    computedClipboardPos(e) {
      this.isShowCopyClipboard = true;
       let minusWidth = 80
    
      minusWidth =
        e.clientX + minusWidth < document.body.clientWidth
          ? 0
          : minusWidth + 8

      this.currentPos.left = e.clientX - minusWidth + 'px'
      let addHeight = 1 * 33 + 16
      addHeight =
        addHeight + e.clientY < document.body.clientHeight
          ? 0
          : addHeight + 8

      this.currentPos.top = e.clientY - addHeight + 'px'
    },

    /**
     * 消息发送前的检测 和 过滤
     * 空消息检测
     * 消息超限检测
     * 标签检测
     * 敏感词检测
     * 延迟消息检测
     * 网址检测
     * */
    checkMsg() {
      this.msgContent = this.$refs.editArea.innerHTML
      console.log('this.msgContent', this.msgContent.length)
      console.log('this.innerText', this.$refs.editArea.innerText.length)
      console.log('checkMsg::::')
      /* 
       * 空消息检测 
       * 长度限制 当长度大于10000时 消息不发送
       * */
      if (
        this.msgContent.replace(/\s+|<br>|&nbsp;/g, '') === '' ||
        this.$refs.editArea.innerText.length > 10000 ||
        !this.user_netstat
      ) {
        let msgTip
        if (!this.user_netstat) {
          // msgTip = '网络出现问题，暂不发送消息' 
           msgTip = this.$t('chat.netError')
        } else {
          msgTip =
            this.$refs.editArea.innerText.length > 10000
              ? this.$t('chat.textLimit')
              : this.$t('chat.unableEmpty')
        }
        this.showMsgTip(msgTip)
        return
      }

      /**
       *  敏感词判断
       *  返回值中的data 如果有长度 则说明包含敏感词
       *  @param {string} user_bad_word_mode '1' : REPLACE_START(替换为*)  '2' : NOTALLOW_SEND(不允许发送)
       */
      let badWordList = this.$Service.chat.getBadWordList({
        text: this.$refs.editArea.innerText
      })
      console.log('badWordList', badWordList)
      if (badWordList.data.length) {
        if (this.user_bad_word_mode === BADWORDMODE.REPLACE_START) {
          badWordList.data.forEach(element => {
            this.msgContent = this.msgContent.replace(
              element.name,
              new Array(element.name.length + 1).join('*')
            )
          })
        } else if (this.user_bad_word_mode === BADWORDMODE.NOTALLOW_SEND) {
          // this.showMsgTip('消息涉及敏感词汇 禁止发送')
          this.showMsgTip(this.$t('chat.badWord'))
          return
        }
      }

            /**去除编辑框中的标签 */
      let date = removeHtml(this.$refs.editArea, this.msgContent)

      this.msgContent = date.content;
      if (date.relatedUsers.length) {
        this.relatedUsers = date.relatedUsers
      }

      /** 编辑框内插入的文件和图片消息 */
      if (date.fileAndImgMsgList.length) {
        // this.$refs.editContainer.style.height = 'auto'
        // this.$refs.editArea.innerHTML = this.msgContent
        let count = 0;
        let timer = setInterval(() => {
          if (!date.fileAndImgMsgList[count]) {
            clearInterval(timer)
          } else {
            this.sendFileOrImgMsg(count, date)
            count++
          }
        }, 10)
      }
     
      console.log('this.msgContent', this.msgContent)
      if (this.msgContent.replace(/\s+|<br>|&nbsp;/g, '') === '') {
        console.log('replace is empty')
        this.$refs.editArea.innerHTML = ''
        this.$refs.editArea.innerText = ''
        this.msgContent = ''
        return 
      }

      /** 如果处于延迟消息模式 显示延迟消息选择时间页面 */
      if (this.isDelay && !this.delayTimes) {
        this.isShowDelayBox = true
        return 
      }

      /** 发送消息 */
      this.sendMsg()
    },

    /** 发送编辑框内的图片和文件消息 */
    sendFileOrImgMsg(index, date) {
      console.log('sendFileOrImgMsg', index, date)
      let type = date.fileAndImgMsgList[index].getAttribute("type")
      console.log('type', type)
      if (type === 'img') {
        let url = date.fileAndImgMsgList[index].src.replace(isOSX?'file://':'file:///', '')
        console.log('is isLinux:::', this.$is.isLinux)
        if (this.$is.isLinux) {
          url = date.fileAndImgMsgList[index].getAttribute("src")
        }
        this.sendImg(date.fileAndImgMsgList[index].title, url)
      } else {
        let fileName = date.fileAndImgMsgList[index].title;
        let path = date.fileAndImgMsgList[index].getAttribute("path");
        let size = date.fileAndImgMsgList[index].getAttribute("size");
        let isP2PFile = date.fileAndImgMsgList[index].getAttribute("isP2PFile");
        this.uploadFile(fileName, path, size,  isP2PFile ==="false" ? false : true)
      }
    },
    /**
     * 发送消息
     * @param {string} msgId
     * @param {string} fromId   用户个人Id
     * @param {string} targetId 会话者Id
     * @param {string} body     发送的消息
     * @param {boolean} isPrivateMsg 是否是密聊模式  1 是 0 不是
     * @param {array} relatedUsers @群成员的id 存在于数组中
     */
    sendMsg() {
      console.log('this.msgContent', this.msgContent.length)
      /** 消息基本体 */
      if (this.isReceipt && this.relatedUsers.length) {
        this.msgContent += '<<<'
      }
      let msgbase = {
        msgId: encryptionPassword(),
        activeType: this.isBurn ? 1 : 0,
        fromId: this.user_account.userId,
        targetId: this.$route.query.id,
        isDelay: this.isDelay,
        delayTime: this.isDelay ? this.delayTimes : '',
        isReceipt: this.chatType === 1 ? this.isReceipt : this.relatedUsers.length ? true : false,
        body: this.msgContent,
        isPrivateMsg: this.isEncryptMsg ? 1 : 0,
        relatedUsers: this.relatedUsers ? this.relatedUsers : [],
        limitRange: this.isReceipt && this.relatedUsers.length && !this.relatedUsers.includes(this.id) ?  this.relatedUsers : []
      }
      console.log('msgbase:::>>>>', JSON.stringify(msgbase))
      this.$Service.log(`relatedUsers:: ${JSON.stringify(this.relatedUsers)}`)
      console.log('sendMsg', msgbase)
      /** 构造消息 界面显示*/
      let msgtxt = new MsgTxt(msgbase, 1)
      this.$store.dispatch('SET_CHATCONTENT', msgtxt)

      /** 清空编辑框状态 */
      if (this.chatType === 1) {
        if (this.inputTimer) {
          clearInterval(this.inputTimer)
        }
        this.setInputState(1)
        this.isBeginInput = false
      }
      this.$refs.editArea.innerHTML = ''
      this.$refs.editArea.innerText = ''
      this.msgContent = ''
      this.relatedUsers = []
      // this.isDelay = false
      if (this.isDelay) {
        this.$emit('updateDelayMsg', false)
      }
      this.delayTimes = ''
      this.isReceipt = false
      /** 如果存在重新编辑的撤回消息 则清空 */
      if ( Object.keys(this.rewriteText).length ) {
        this.$emit('clearReeditText')
      }
    },

    /**
     * 发送抖一抖消息
     * isfirst 是否点击过
     * lastShakeMsg 最后一次震动时间
     * nowTime 当前时间
     * 首次点击不存在 上次震动时间
     * 发送抖一抖消息后 上次抖动时间 为当前时间
     * 抖动时间间隔不能低于5s
     */
    sendShakeMsg() {
      if (this.lastShakeMsg === 0) {
        this.lastShakeMsg = 1
        let body = '&:flash'
        let msgbase = {
          fromId: this.user_account.userId,
          targetId: this.$route.query.id,
          body: body,
          isPrivateMsg: this.isEncryptMsg ? 1 : 0,
          relatedUsers: []
        }
        let msgtxt = new MsgTxt(msgbase, 1)
        this.$store.dispatch('SET_CHATCONTENT', msgtxt)
        // this.$ipc.send('win-shake-event')  主进程存在问题
        setTimeout(() => { this.lastShakeMsg = 0 }, 3000)
      } else {
        this.showMsgTip(this.$t('chat.shakeLimit'))
      }
    },

    /** 延迟消息开关 */
    switchDealyMode() {
      if (this.isBurn) {
        this.$emit('updateBurnMsg', false)
      }
      if (this.isReceipt) {
        this.isReceipt = false
      }
      // this.isDelay = !this.isDelay
      // this.isDelay = !this.isDelay
      this.$emit('updateDelayMsg', !this.isDelay)
    },

    /** 发送延迟消息 */
    sendDelayMsg(time) {
      this.delayTimes = time
      this.sendMsg()
    },

    /** 取消发送延迟消息 */
    cancelSendDelay() {
      this.isShowDelayBox = false
      this.delayTimes = ''
      // this.isDelay = false
      this.$emit('updateDelayMsg', false)
      placeCaretAtEnd(this.$refs.editArea)
    },

    /** 阅后即焚消息开关 */
    switchBurnMode() {
      if (this.isReceipt) {
        this.isReceipt = false
      }
      if (this.isDelay) {
        this.$emit('updateDelayMsg', false)
      }
      this.$emit('updateBurnMsg', !this.isBurn)
    },

    //* 
    switchReceiptMode() {
      this.isReceipt = !this.isReceipt;
      if (this.isReceipt && this.chatType === 2) {
        this.isReadReceipt = true
      }
      if (this.isBurn) {
        this.$emit('updateBurnMsg', false)
      }
      if (this.isDelay) this.isDelay = false
      console.log('isReceipt::', this.isReceipt)
    },
    /** 发生名片消息 */
    sendCardMsg() {
      this.isCard = true
    },
    HandleMeeting(){
      let result = this.$judgePlginSubWinStatus('InternalWindow')
      if (result.busy) {
        this.channelBusyTip();
        return
      }
      this.isMeeting = true
    },

    /**
     * 获取该联系人是否处于密聊模式下
     * privateMsgPwd 存在 个人情况下表示处于密聊模式
     * 群的情况下 查看extend扩展字段 privateMsgPwd 如果存在 则表示处于密聊模式
     */
    getIsPrivateModel() {
      if (this.chatType === 1) {
        // chatType 1 个人
        /** 获取联系人信息回调 */
        let getContactInfoCb = resp => {
          if (resp.privateMsgPwd) {
            this.$emit('updateEncryptMsg', true)
          }
        }
        this.$Service.contact.getContactInfo({ userId: this.id }, getContactInfoCb)
      } else if (this.chatType === 2) {
        // chatType 2 群组
        /** 获取群信息回调 privateMsg 1 为允许密聊 */
        let getGroupInfoCb = resp => {
          console.log('resp',resp)
          if(resp.info.groupType === 'eid'){
            let times = resp.extend.split(',')
            let timestamp=new Date().getTime()
            if(timestamp<times[0]){
              this.showTool = false
              this.eidtips = '主题议政未开始'
            }
            if(timestamp>times[1]){
              this.showTool = false
              this.eidtips = '主题议政已结束'
            }
          }
          //this.$Service.log(`privateMsgPwd:${resp.privateMsgPwd}--extend:${resp.extend}`)
          // if (resp.privateMsgPwd && resp.extend && (JSON.parse(resp.extend).privateMsg).toString() === '1') {
          //   this.$emit('updateEncryptMsg', true)
          // }
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
        }
        this.$Service.group.getGroupInfo({ groupId: this.id }, getGroupInfoCb)
      }
    },

    /** 设置密聊消息 */
    setPrivateMsg() {
      if (this.isEncryptMsg) {
        this.$Service.chat.setPrivateKey({ targetId: this.$route.query.id, passwd: '' }, resp => {
          if (resp.code === 0) {
            this.$emit('updateEncryptMsg', false)
          }
        })
      } else {
        this.$dialog.prompt({
          title: this.$t('chat.setPassword') ,
          confirmText: this.$t('common.sure'),
          cancelText: this.$t('common.cancel'),
          inputAttrs: {
            placeholder: this.$t('chat.passwordRule') ,
            minlength: 6,
            type: 'password'
          },
          required: true,
          onConfirm: value => {
            let setPrivateKeyParam = {
              targetId: this.$route.query.id, // 传入会话对应的ID，群或者人
              passwd: value // 私信秘钥  为空代表清除私信密码
            }
            console.log('setPrivateKeyParam', setPrivateKeyParam)
            this.$Service.chat.setPrivateKey(setPrivateKeyParam, resp => {
              if (resp.code === 0) {
                this.$emit('updateEncryptMsg', true)
              }
            })
          }
        })
      }
    },

    /** 发送消息提示 */
    showMsgTip(msgTip) {
      this.isMsgtip = true
      this.msgTip = msgTip
      setTimeout(() => { this.isMsgtip = false }, 2000)
    },

    channelBusyTip(){
      let toastMsg = {
          message: this.$t('chat.channelBusy'),
          type: 'is-danger'
      }
      this.$toast.open(toastMsg);
    },

    newSubWindowScreenShot(type) {
       let screenList = this.$el.getElementsByClassName('screen-opera-list')[0]
       screenList.style.display="none"
      setTimeout(() => {
        screenList.removeAttribute('style');
      }, 200)
      if (this.lastScreenShot === 0) {
        console.log('NORMAL', SCREENDISPLAY.NORMAL)
        console.log('istrye', this.user_localConfig.screen_display !== SCREENDISPLAY.NORMAL)
        console.log('this.user_localConfig.screen_display', this.user_localConfig.screen_display)
        this.hideMainWindow = false;
        if (( type !== SCREENDISPLAY.NORMAL&&this.user_localConfig.screen_display === SCREENDISPLAY.HIDE) || type === SCREENDISPLAY.HIDE) {
          this.$ipc.send('control-main-window',false)
          this.hideMainWindow = true;
        }
        this.lastScreenShot = 1;
        setTimeout(() => {
          this.$Service.config.screenShot();
          setTimeout(() => { this.lastScreenShot = 0 }, 1000)
        }, this.hideMainWindow?30:0);
      } else {
        this.showMsgTip(this.$t('chat.screenshotLimit'))
      }
    },
    
    /** 选择表情 */
    selectEmoji(emoji) {
      this.isShowEmoji = false

      if (emoji) {
        // 如果传过来emoji 则需要构造表情
        let emojis = require('vrv-static/resources/images/emoji/text_emoji/' + emoji.src + '.png')
        this.$refs.editArea.focus()
        var source = '<img class="v-text-emoji" type="emoji" alt="' +  emoji.alt + '" src="' + emojis + '">'
        insertNode(this.$refs.editArea, source)
      }
    },

    /**
     * 是否触发了At @
     */
    hasAt(isAt) {
      this.isShowList = isAt
    },

    /**
     * 根据@的增加或则删除  更改relatedUsers
     */
    changeRelatedUsers(data) {
      this.$Service.log(`changeRelatedUsers type::${data.oprea} id::${data.id}`)
      data.oprea
        ? this.relatedUsers.push(data.id)
        : (this.relatedUsers = this.relatedUsers.filter(e => e !== data.id))
    },

    /**
     * 监听键盘事件
     * Enter ctrl 换行
     * Enter 发送消息
     * shift 2 @
     */
    keyChange(e) {
      if (e.keyCode === 13 && e.ctrlKey) {
        // 换行
        e.preventDefault()
        e.stopPropagation()
        this.orderConfigSendMsg('ctrl', e)
      } else if (e.keyCode === 13 && !this.isShowList) {
        e.preventDefault()
        e.stopPropagation()
        this.orderConfigSendMsg('enter', e)
      } else if (e.code === 'Digit2' && e.shiftKey && this.chatType === 2) {
        e.stopPropagation()
        console.log('Digit2')
        this.isShowList = true
      } else if (e.altKey && e.code ==='KeyS') {
        e.stopPropagation()
        e.preventDefault()
        this.checkMsg()
      }
    },

    // 处理全选后删除 at relatedUsers 不准的问题
    _handleDeleteAll(text) {
      try {
        _.forEach(this.relatedUsers, id => {
          console.log('_handleDeleteAll', id)
          if( text.includes(this.$t('chat.allMem')) ||text.includes(this.userInfo[id].remark)) {
            this.relatedUsers = this.relatedUsers.filter(i => i !== id)
          }
        });   
      } catch (error) {
        console.log('_handleDeleteAll error')
      }
    },

    editInput() {
      console.log('editInput:::')
      if (this.chatType !== 1) return
      console.log('editInput:::')
      if (this.inputTimer) {
        clearInterval(this.inputTimer)
      }

      /** 停止输入后 5秒钟置为正常状态 */
      let count = 5
      this.inputTimer = setInterval(() => {
        if (count < 1) {
            clearInterval(this.inputTimer)
            this.setInputState(1)
            this.isBeginInput = false
          } else {
            count--
          }
      }, 1000)

      /** 已经开始输入后，无需设置输入状态 */
      if (this.isBeginInput) {
        return
      }
      this.isBeginInput = true
      this.setInputState(0)
    },
    
    /**
     * 设置输入状态
     * @param {Number} status 0 开始输入 1 结束输入
     */
    setInputState(status) {
      let sendMsgInputStateParam = {
        flag: status,
        targetId: this.id
      }
      console.log('sendMsgInputStateParam::', sendMsgInputStateParam)
      this.$Service.chat.sendMsgInputState(sendMsgInputStateParam, resp => {
        console.log('sendMsgInputState::::', resp)
      })
    },

    /** 换行 */
    newLine() {
      this.$refs.editArea.focus()
      let source = '<br/>'
      insertNode(this.$refs.editArea, source)
      if (this.$refs.editArea.scrollTop !== this.$refs.editArea.scrollHeight) {
        this.$refs.editArea.scrollTop = this.$refs.editArea.scrollHeight
      }
    },

    /** 根据配置快捷键 发送消息 */
    orderConfigSendMsg(keys, e) {
      if (this.send_msg_key === keys) {
        this.checkMsg()
      } else {
        let initHieght = e.srcElement.scrollHeight
        this.newLine()
        if (e.srcElement.scrollHeight == initHieght) this.newLine()
      }
    },
    // 绑定需要拖拽改变大小的元素对象
    bindResize(e) {
      let el = this.$refs.editContainer
      console.log('editBox', this.$refs.editContainer.offsetHeight)
      console.log('clientY', e.clientY )
      this.windowHeight = e.clientY + el.offsetHeight + 9;
      el.setCapture
        ? (el.setCapture(), el.onmousemove = ev => { 
            this.mouseMove(ev || event)
          }, el.onmouseup = this.mouseUp)
        : (document.addEventListener('mousemove', this.mouseMove),document.addEventListener('mouseup', this.mouseUp))  
      e.preventDefault();
    },
    mouseMove(e) {
      console.log('e', e)
      let getCilentY = e.clientY;
      console.log('getCilentY::', getCilentY)
      let editCurrentHeight =  this.windowHeight - getCilentY;
      console.log('editCurrentHeight::', editCurrentHeight,'switchMode',this.switchMode)
      if (this.switchMode === EDITMODEL.CLASSIC && editCurrentHeight < 140) {
        return
      }
      if (this.switchMode === EDITMODEL.STANDARD && editCurrentHeight < 84) {
        return
      }
      if (editCurrentHeight > (this.windowHeight - 300)) return
      console.log('editCurrentHeight', editCurrentHeight,this.windowHeight)
      this.$refs.editContainer.style.height = editCurrentHeight + 'px';
    },
    mouseUp(e) {
      let el = this.$refs.editContainer;
      el.releaseCapture 
        ? (el.releaseCapture(),el.onmousemove = el.onmouseup = null) 
        : (document.removeEventListener('mousemove', this.mouseMove),document.removeEventListener('mouseup', this.mouseUp))
    },
    speeches(){
      console.log('打开发言汇编');
      this.isSpeeches = true;
    },
    referMaterials(){
      console.log('打开参阅材料');
      this.isReferMaterials = true;
    },
    speechCount(){
      console.log('打开发言统计');
      this.isSpeechCount = true;
    },
    speechSketch(){
      console.log('打开发言综述');
      this.isSpeechSketch = true;
    },
    book(type){
      console.log(type,'type');
      this.pageType=type;
      this.isBook = true;
    },
    MsgHistory(){
      console.log('打开消息记录');
      this.isHistory = true
    },
  },
  
  computed: {
  // chatEditMenu() {
    //   return [
    //     { icon: '&#xe669;', class: 'theme-hover-bgc_font', text: '音视频', disabled: !this.platformIsLinux && this.chatType===1, type: 'submenu'},
    //     { icon: this.isEncryptMsg? '&#xe610;': '&#xe657;', class: `[theme-hover-bgc_font, {'secrected-msg' : ${this.isEncryptMsg}}]`, text: this.$t('chat.EncryptedMessage'), disabled: this.isAllowPrivate, type: 'encrypted'},
    //     { icon: '&#xe65a;', class: `[theme-hover-bgc_font, {'disable-direct': ${this.isDisableDirectMsg}}]`, text: this.$t('chat.shake'), disabled: this.chatType===1, type: 'shake'},
    //     { icon: '&#xe65c;', class: `[theme-hover-bgc_font, {'delay-msg':${this.isDelay}, 'disable-direct': ${this.isDisableDirectMsg}}]`, text: this.$t('chat.delayMessage'), disabled: this.chatType!==3, type: 'delay'},
    //     { icon: '&#xe635;', class: `[theme-hover-bgc_font, {'burned-msg':${this.isBurn}, 'disable-direct': ${this.isDisableDirectMsg}}]`, text: this.$t('groups.burnChat'), disabled: this.chatType!==3, type: 'burn'},
    //     { icon: '&#xe6bd;', class: "['theme-hover-bgc_font', {'receipt-msg':${this.isReceipt}, 'disable-direct': ${this.isDisableDirectMsg}}]", text: this.$t('chat.receiptMessage'), disabled: this.chatType!==3, type: 'receipt'},
    //     { icon: '&#xe6b1;', class: 'theme-hover-bgc_font', text: this.$t('chat.cardMessage'), disabled: this.chatType!==3, type: 'card'},
    //     { icon: '&#xe622;', class: 'theme-hover-bgc_font', text: '位置消息', disabled: true, type: 'map'},
    //     { icon: '&#xe6b1;', class: 'theme-hover-bgc_font', text: '潜水者名单', disabled: this.isDividerShow, type: 'diver'},
    //   ].filter(e => e.disabled)
    // },
    /**
     * @breif 是否开启潜水者名单入口
     * 条件：拥有权限的群
     */
    // isDividerShow() {
    //   let memberType = this.userInfo[this.user_account.userId].memberType
    //   console.log('member type:::', memberType)
    //   return this.chatType === 2 && (memberType === 2 || memberType === 3)
  // },
    isWinXpVersion(){
      return isWinXp;
    },
    switchMode() {
      if (this.user_localConfig.editBox_mode !== EDITMODEL.STANDARD) {
        this.editMoreIcon = '&#xe604;'
        // * 特殊处理 拖拽过后标准模式 高度太低问题
        // if (this.$refs.editContainer && this.$refs.editContainer.offsetHeight < 140) {
        if (this.$refs.editContainer) {
          this.$refs.editContainer.style.height = 140 + 'px'
          console.log('this.$refs.editContainer.style.height', this.$refs.editContainer.style.height)
          console.log('this.$offsetHeight', this.$refs.editContainer.offsetHeight)
        }
        return  'editBox_classic'
      } else {
        if (this.$refs.editContainer) {
          this.$refs.editContainer.style.height = 'auto'
        }
        this.editMoreIcon = '&#xe62c;'
        return  'editBox_standard'
      }
    },
    getScreenShotkey() {
      console.log('this.user_localConfig.userLocalConfigData', this.user_localConfig.screenshot_key)
       return this.user_localConfig.screenshot_key
    },
    computedSendMsgKey() {
      if (this.user_localConfig.send_msg_key === 'CTRL_ENTER') {
        this.send_msg_key = 'ctrl'
        return this.$t('chat.sendway', {value:'Enter', key: 'Ctrl+Enter'})
      } else {
        this.send_msg_key = 'enter'
        return  this.$t('chat.sendway', {value:'Ctrl+Enter', key: 'Enter'})
      }
    },

    orderedPinYin() {
      if (this.isShowList && this.chatType === 2) {
        console.log('isShowList')
        this.chatObject = []
        for (let i in this.userInfo) {
           if ( this.userInfo[i].id !== this.user_account.userId) {
             this.chatObject.push(this.userInfo[i]); //属性
           }
        }
        let all = {
            id: this.$route.query.id,
            remark: this.$t('chat.allMem'),
            thumbAvatar: '',
            pingyin: 'quantichengyuan',
            genter: 4
        }
        this.chatObject.unshift(all)
      }
      console.log('this.chatObject', this.chatObject)
      return this.chatObject
    },


    computedEncrypt() {
      console.log('enter computedEncrypt...', this.contact_contactList[this.id])
      if (this.chatType === 1) {
        if (!this.contact_contactList[this.id]) {
          this.$emit('updateEncryptMsg', false)
          this.isAllowPrivate = false
        } else {
          this.isAllowPrivate = true
        }
      } else if (this.chatType === 2) {
        if (this.contact_groupExtension[this.id]) {
          if (this.contact_groupExtension[this.id].privateMsg) {
            if (this.contact_groupExtension[this.id].privateMsg.toString() === '1') {
              this.isAllowPrivate = true
            } else {
              // this.isEncryptMsg = false
              this.$emit('updateEncryptMsg', false)
              this.isAllowPrivate = false
            }
          }
          if (this.contact_groupExtension[this.id].burnMsg) {
            if (this.contact_groupExtension[this.id].burnMsg.toString() === '1') {
              console.log('burnMsg :::')
              this.$emit('updateBurnMsg', true)
              this.isDisableDirectMsg = true
            } else {
              this.$emit('updateBurnMsg', false)
              this.isDisableDirectMsg = false
            }
          }
        }
      }
    },

    contentAreaClass() {
      if (this.isEncryptMsg) {
        return 'content-area-encrypt-model'
      } else if (this.isBurn) {
        return 'content-area-burn-model'
      } else if (this.isDelay) {
        return 'content-area-delay-model'
      } else if (this.isReceipt) {
        return 'content-area-receipt-model'
      }
    },

    ...mapGetters([
      'user_account',
      'contact_groupExtension',
      'contact_contactList',
      'chat_objectInfo',
      'user_imgPath',
      'user_netstat',
      'user_localConfig',
      'user_bad_word_mode',
      'chat_chatDicValue',
      'clientConfig_chat',
      'contact_groupList'
    ])
  },
  props: {
    chatDraft: Object,
    isOpen: Boolean,
    isEncryptMsg: Boolean,
    isBurn:Boolean,
    isDelay:Boolean,
    chatType: Number,
    id: String,
    userInfo: Map | Function | Object,
    rewriteText: Object | String,
    rightAtId: Object | String
  },
  components: {
    Emoji: resolve => require(['../../Emoji/index.vue'], resolve),
    At: resolve => require(['../../At/At.vue'], resolve),
    ChatDividerList: resolve => require(['../ChatDividerList.vue'], resolve),
    // CreateMeeting,
    msgTypeDelay,
    ChatSearchList,
    CreateGroupMeeting,
    VideoCallMenu,
    CppccSpeeches,
    CppccReferMaterials,
    CppccSpeechCount,
    CppccSpeechSketch,
    CppccBook,
    CppccMsgHistory
  }
}
</script>

<style lang="scss">
@mixin common {
  .content-area {
    position: relative;
    display: flex;
    height: 100%;
    min-height: 50px;
    .edit-drag-line {
      position: absolute;
      top: 0px;
      left: 0px;
      height: 6px;
      width: 100%;
      background: transparent;
      // z-index: 9999;
      cursor: n-resize;
      // &:hover {
      //   cursor: s-resize;
      // }
    }
    .edit-more-operate {
      display: flex;
      -webkit-box-direction: normal;
      -webkit-box-pack: center;
      justify-content: center;
      align-content: center;
      align-items: center;
      -webkit-box-flex: 0;
      flex: 0 50px;
      -webkit-box-orient: vertical;
      flex-direction: column;
      border-right: inherit;
      border-radius: 3px 0 0 3px;
      color: inherit;
    }
    .chat-input-area {
      flex: 1;
      display: flex;
      .input-area {
        flex: 1;
        display: flex;
        .atwho-panel {
          // bottom: -10px;
          top: 0px;
          transform: translateY(-100%);
          left: 0px;
          width: 100%;
          z-index: 100;
        }
        // padding: 14px 5px 0 14px;
        .edit-textarea {
          width:100%; // fit xp
          height: 100%;  //fit xp
          resize: none;
          font-family: inherit;
          letter-spacing: 0.5px;
          border: none;
          box-shadow: none;
          font-size: $--font-size-mid;
          color: #000;
          font-weight: 500;
          outline: none;
          overflow-y: auto;
          white-space: normal;
          -webkit-user-modify: read-write-plaintext-only;
          // min-height: 34px;
          // max-height: 94px;
          overflow-x: hidden;
          word-break:break-word;
          .v-text-emoji {
            width: 21px;
            height: 21px;
            margin: 0 2px;
            user-select: none;
          }
          .edit-at-image {
            height: 18px;
            margin:0px 2px;
          }
          .edit-image {
            width: 100px;
            margin: 0 4px;
            &:hover {
              cursor: pointer;
            }
          }
          .edit-file-image {
            width: 220px;
            height: 50px;
            margin: 0 4px;
          }
        }
      }
    }

      .input-operate-area {
        display: flex;
        align-items: center;
        justify-content: space-around;
        border-left: none;
        border-radius: 0 4px 4px 0;
        .input-operate-btn {
          width: 32px;
          height: 100%;
          transition: all 0.3s ease;
          display: flex;
          align-items: center;
          justify-content: center;
          margin-right: 4px;
          position: relative;
          .tool-tips {
            position: absolute;
            left: 16px;
            top: 6px;
            display: none;
            @include z-index(btn);
          }
          // .capture-btn {
          //   // height: 100%;
          //   &:hover {
          //     display: block;
          //   }
          // }
          .icon {
            font-size: 20px;
            color: inherit;
          }
          .upload-file {
            position: relative;
            width: 24px;
            height: 24px;
            overflow: hidden;
            transform: rotate(45deg);
            input[type="file"] {
              color: transparent;
            }
            .upload {
              position: absolute;
              width: 21px;
              right: 0;
              top: 0;
              opacity: 0;
              filter: alpha(opacity=0);
              cursor: pointer;
//               input[type="file"] {
//   color: transparent;
// }
              color: transparent;
            }
          }
          &:hover {
            cursor: pointer;
            transform: translateY(-6px);
          }
          &:hover .tool-tips {
            display: block;
          }


        }
        .screen-shot-btn {
          position: relative;
          &:hover .screen-opera-list{
            display: block;

          }
          .screen-opera-list {
            // position: absolute;
            display: none;
            // width: 140px;
            font-size: 13px;
            position: absolute;
            width: 162px;
            left: -122px;
            // width: 160px;
            // left: -100px;
            // top: -90px;
            top: -88px;
            background: #fff;
            box-shadow: $--box-shadow-elevation;
            padding: 10px 0px;
            @include z-index(menu);
            .screen-opera-item {
              height: 36px;
              line-height: 36px;
              color: #000;
              padding: 0 10px;
              
              &:hover {
                background: #dbdbdb;
              }
            }
          }
        }
      }
  }
  .delay-msg-box {
    // height: 200px;
    width: 380px;
    border-radius: $--border-radius-base;
    overflow: hidden;
    display: flex;
    .modal-card-body {
      background: #f3f6f8;
    }
  }

  .edit-more-operate-list {
    position: absolute;
    padding: 10px 0px;
    // width: 120px;
    @include z-index(menu);
    border-radius: $--border-radius-base;
    background-color: #fff;
    box-shadow: $--box-shadow-elevation;
    border: 1px solid #ccc;
    display: flex;
    width: 120px;
    .edit-menu {
      width: 100%;
      .muti-media {
        &:hover {
          .sub-menu-hover {
            display: block;
          }
        }
      }
      .sub-menu-hover {
        display: none;
      }
    }
    li {
      position: relative;
      cursor: pointer;
      line-height: 36px;
      height: 36px;
      font-size:$--font-size-mid;
      color: #000;
      padding: 0 10px;
      white-space: nowrap;
      &:hover {
        color: #fff;
      }
      span {
        margin: 0px 8px;
      }
    }
    .secrected-msg {
      color: $--color-msg-prompt-low;
    }
    .delay-msg {
      color: $--color-msg-prompt-middle;
    }
    .burned-msg {
      color: $--color-msg-prompt-danger
    }
    .receipt-msg {
      color: $--color-msg-prompt-low;
    }
    .disable-direct {
      pointer-events: none;
      opacity: 0.6;
    }
  }

  .v-emoji {
    position: absolute;
    border-radius: $--border-radius-base;
    box-shadow: $--box-shadow-elevation;
  }

  .classic-send-area { 
    display: none;
  }
} 
.editBox_classic {
  // height: auto;
  min-height: 140px;
  max-height: 290px;
  height: 140px;
  position: relative;
  @include common;
  .content-area {
    background: #fff;
    height: 100%;
    flex-direction: column-reverse;
    border-top: solid 1px $--border-color-grey;
    &.content-area-encrypt-model {
      color: $--color-msg-prompt-low;
      border-top: 1px solid $--color-msg-prompt-low;
    }
    &.content-area-burn-model {
      color: $--color-msg-prompt-danger;
       border-top: 1px solid $--color-msg-prompt-danger;
    }
    &.content-area-delay-model {
      color: $--color-msg-prompt-middle;
      border-top:1px solid $--color-msg-prompt-middle;
    }
    &.content-area-receipt-model {
      color: $--color-msg-prompt-low;
      border-top: 1px solid $--color-msg-prompt-low;
    }
    .edit-more-operate {
      top: 0px;
      display: flex;
      justify-content: center;
      position: absolute;
      left: 130px;
      background: none;
      border: none;
      height: 32px !important;
      padding: 0px;
      width: 32px;
      transition: all 0.1s ease-out 0.2s;
      .tool-tips {
        display: none;
        // left: 4px;
        // @include z-index(btn);
        position: absolute;
        left: 16px;
        top: 6px;
        display: none;
        @include z-index(btn);
      }
      &:hover {
        cursor: pointer;
        top: -6px;
        transition: all 0.1s ease-out 0.2s;
        background: none!important;
        color: inherit!important;
        .tool-tips {
          display: block;
        }
      }
    }
  }

  .input-operate-area {
    width: 120px;
    height: 32px;
    margin-left: 10px;
    .screen-opera-list {
      left: -93px!important;
      // width: 162px;
    }
  }
  .input-area {
    flex: 1;
    margin-bottom: 32px;
    margin-left: 16px;
    display: flex;
    height: calc(100% - 32px);
    // .atwho-panel {
    //   // bottom: -10px;
    //   top: 0px;
    //   transform: translateY(-100%);
    //   left: 0px;
    //   width: 100%;
    //   z-index: 100;
    // }
    .edit-textarea {
      height: 67px;
    }
  }
  .classic-send-area {
    display: flex!important;
    justify-content: flex-end;
    position: relative;
    .empty-message-prompt {
      color: $--color-msg-prompt-danger;
      position: absolute;
      left: 6px;
      top: -30px;
      font-size: $--font-size-small;
    }
    .btn-send {
      background: get-grey-color(lighten-4);
      color: get-grey-color(darken-2);
      border-radius: 0px;
      width: 68px;
      height: 26px;
      font-size: 12px;
      border: solid 1px $--border-color-grey;
      margin-right: 20px;
      margin-top: -34px;
      &:hover {
        color:#fff;
        @include bg_color($--color-primary, 'normal');
      }
    }
  }
  .v-emoji {
    left: 6px;
    bottom: 140px;
  }
  .message-prompt-area {
    display: none;
  }

  
  .edit-more-operate-list {
    left: 162px;
    bottom: 116px;
  }
}
.editBox_standard {
  display: flex;
  flex-direction: column;
  width: 100%;
  padding: 10px;
  background: #fff;
  border-radius: $--border-radius-base;
  position: relative;
  padding: 12px 24px;

  @include common;
  .content-area {
    border-radius: $--border-radius-base;
    color: get-grey-color(base);
    border: 1px solid $--border-color-grey;
    &.content-area-encrypt-model {
      color: $--color-msg-prompt-low;
      border: 1px solid $--color-msg-prompt-low;
    }
    &.content-area-burn-model {
      color: $--color-msg-prompt-danger;
      border: 1px solid $--color-msg-prompt-danger;
    }
    &.content-area-delay-model {
      color: $--color-msg-prompt-middle;
      border: 1px solid $--color-msg-prompt-middle;
    }
    &.content-area-receipt-model {
      color: $--color-msg-prompt-low;
      border: 1px solid $--color-msg-prompt-low;
    }
    .input-area {
      flex: 1;
      padding: 16px 5px 0 14px;
      .edit-textarea {
        min-height: 34px;
        max-height: 94px;
      }
    }
    .input-operate-area {
      flex: 0 120px;
    }
  }

  .message-prompt-area {
    display: flex;
    justify-content: space-between;
    color: get-grey-color(lighten-1);
    font-size:$--font-size-small;
    position: relative;
    margin-bottom: 10px;
    .empty-message-prompt {
      color: $--color-msg-prompt-danger;
      position: absolute;
      left: 50px;
    }
    .change-send-way {
      position: absolute;
      right: 2px;
    }
  }
 
  .edit-more-operate {
    min-height: 50px; // fit xp
    .tool-tips {
      display: none;
    }
    .more-icon {
      width: 100%;
      height: 100%;
    }
    .icon {
      margin: 0!important;
    }
    &:hover {
      color: #fff;
    }
  }
  .edit-more-operate-list {
    left: 24px;
    bottom: 80px;
  }

  .v-emoji {
    top: -220px;
    right: 6px;
  }

  .classic-send-area { 
    display: none;
  }
}



.slide-fade-enter-active {
  transition: all 0.5s ease;
}

.slide-fade-leave-active {
  transition: all 0s ease-out;
}

.slide-fade-enter,
.slide-fade-leave-to {
  transform: translateY(10px);
  opacity: 0;
}

.emoji-slide-up-enter-active {
  transition: all 0.6s ease;
}

.emoji-slide-up-leave-active {
  transition: all 0.3s ease-out;
}

.emoji-slide-up-enter,
.emoji-slide-up-leave-to {
  transform: translateY(30px);
  opacity: 0.9;
}



// .input-operate-btn {
//   width: 32px;
//   border: solid 1px #ff4949;
//   span {
//     margin-left: 10px;
//   }
// }

</style>
