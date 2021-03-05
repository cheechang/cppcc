<template>
  <div>
    <v-menu 
            v-if="isShowMenu"
            :menuList="menuList" 
            :currentPos="currentPos"
            :headDivider='headDivider'
            :footerDivider ='footerDivider' 
            @close="closeMenu" 
            @headItemClick ='headItemClick'
            @footerItemClick ='footerItemClick'
            @selectItem="selectItem">
    </v-menu>
    <!-- 消息转发弹出框 -->
    <chat-search-list v-if="isActionForward||isForward" @close="clearCache" :selectActive="selectActive" :mixTextMessage='mixTextMessage' :type='handleType' ></chat-search-list>
    <group-member-info @close="closeMenu"></group-member-info>
    <msg-status-list v-if="isMsgStatusList" :id="id"  :userInfo="userInfo" :selectActive="selectActive"  :remindMsgSeconds ='remindMsgSeconds' @close="isMsgStatusList = false,$emit('closeRightMenu')"></msg-status-list>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import { msgStructure, MsgRetract } from '../Msg'
import { getDateDiff } from '../../../../comm/time'
import ChatSearchList from '../Msg/ChatSearchList'
import { encryptionPassword } from '../../../../comm/util'
import MsgMxin from '../msgMixin'
import FileMixin from '../Mixins/FileMixins'
import ImgMixins from '../Mixins/ImgMixins'
import MsgStatusList from '../Msg/MsgStatusList';
import CommonMixin from '../Mixins/common.js'
import GroupMemberInfo from '../../Group/ChatGroupInfo/ChatMemberInfo'
import vClickOutside from '../v-click-outside/index.js';
const { clipboard } = require('electron')
import {  removeHtml } from '../Emoji/emoji'
import { getErrorMsg } from '../../../utils/utils.js'
import i18n from '../../../../comm/i18n'


const menuOperate = {
  forWard: '转发',
  delMsg: '删除',
  copy: '复制',
  checkData: '查看资料',
  revoke: '撤回',
  addFriend: '添加好友',
  more: '更多',
  msgStatus: '消息状态',
  saveAs: '另存为',
  silentPlay: '静音播放',
  cancelSlient: '取消静音',
  atUser: '@Ta'
}
export default {
  mixins: [MsgMxin, CommonMixin, FileMixin, ImgMixins],
  props: {
    mixTextMessage: Object,
    isMixText: {
      type:Boolean,
      type: false
    },
    menuList: Array,
    currentPos: Object,
    // isShowMenu : Boolean,
    selectActive: Object,
    isActionForward: {
      type: Boolean,
      default: false
    },
    isOpenAction:{
      type: Boolean,
      default: false
    },
    userInfo: Object | Map,
    remindMsgSeconds:  Number,
    id: String,
    headDivider: String,
    footerDivider: String,
    isAutoShowMsgState: Boolean,
    chatType: Number
    
  },
    components: {
    ChatSearchList,
    GroupMemberInfo,
    MsgStatusList,
  },
  data() {
    return {
      isMemberInfoShow: false,
      isMsgStatusList: false,
      isForward: false, // 是否转发消息
      isShowMenu: true,
      handleType: '',
      addNoteParam: {
        content: '',
        exts: '',
        fileName: '',
        id: '',
        isArchive: 0,
        isNet: true,
        isReminder: 0,
        key: '',
        lastChgTime: new Date().getTime().toString(),
        loginInfo: '',
        msgProperties: '',
        netType: 0,
        rmdTime: '0',
        sendUserId: '',
        targetId: '',
        title: '',
        type: Number
      }
    }
  },
  computed:{
  ...mapGetters([
    'chat_objectInfo'
    ])
  },
  created() {
    console.log('menuList', this.menuList)
    console.log('headDivider:::', this.headDivider)
    if (this.isAutoShowMsgState) {
      this.isMsgStatusList = true
    }
  },
  methods: {
    /**
     * 转发操作后清空选中项、关闭弹出层
     */
    clearCache() {
      this.isForward = false
      this.$emit('handleActionShow', false)
      this.$emit('closeRightMenu')
    },
    
    closeMenu() {
      this.$emit('closeRightMenu')
      this.$emit('clearMenuList')
    },

    /**
     * 右键菜单选择
     */
   async selectItem(index) {
      this.isShowMenu = false
      switch (this.menuList[index]) {
        case this.$t('chat.forward'): {
          console.log('forWard')
          this.isForward = true
          this.handleType = 'forward' 
          break
        }
        case this.$t('chat.silentPlay'): {
          this.$set(this.selectActive, 'mute', true)
          this.$emit('closeRightMenu')
          break
        }
        case this.$t('chat.detail'): {
          this.isMemberInfoShow = true
          let memberInfo = this.contact_contactList[this.selectActive.fromId]
          if (memberInfo) {
            this.memberInfo = memberInfo;
            this.memberInfo.remark = 
              this.userInfo[this.selectActive.fromId]
              && this.userInfo[this.selectActive.fromId].remark;
            this.$signalMonitor.$emit('expendChatMemberInfo', this.memberInfo);
          } else {
            let getUserInfoParam = { userId: this.selectActive.fromId }
            let getUserInfoCb = successRes => {
              this.memberInfo = successRes.users;
              console.log('this.memberInfo', this.memberInfo)
              this.memberInfo.remark = 
                this.userInfo[this.selectActive.fromId]
                && this.userInfo[this.selectActive.fromId].remark;
              this.$signalMonitor.$emit('expendChatMemberInfo', this.memberInfo);
            }
            this.$Service.search.getUserInfo(getUserInfoParam, getUserInfoCb)
          }
          break
        }
        case this.$t('chat.more'): {
          this.$emit('handleActionShow', true)
          this.handleType = 'mixMsg' 
          break
        }
        case this.$t('chat.Recall'): {
          console.log('revoke')
          this.revokeMsg()
          this.$emit('closeRightMenu')
          break
        }
        case this.$t('organizations.addFriend'): {
          console.log('addFriend')
          await this.addFriend(this.selectActive.fromId)
          this.$emit('closeRightMenu')
          break
        }
        case this.$t('chat.msgStatus'): {
          this.isMsgStatusList = true;
          break;
        }
        case this.$t('chat.saveAs'): {
          let saveAs = this.$dialogs.showSaveDialog({ defaultPath: this.selectActive.fileName, filters: this.getExtensionFilter() })
          this.$emit('closeRightMenu')
          if (!saveAs) return  this.$Service.log(`cancel decrypted`)
          console.log('saveAs::', saveAs)
          if (this.selectActive.msgType === 5) { // 图片另存为
            let localImgParam = {
              filepath: this.selectActive.mainPath,
              type: 0
            }
            if (!this.$Service.file.fileOperate(localImgParam)) { // 下载解密另存为
              this.downloadNetImg(saveAs)
            } else { // 读写图片另存为到指定目录
              this.copyLocalImgSaveAs(saveAs)
            }
          } else { // 文件另存为
            this.decrypted(this.selectActive.encryptKey, this.selectActive.defaultPath, saveAs).then(decryptedRes => {
              this.$Service.log(`decrypted SaveAs    ${decryptedRes.result}`)
            })
          }
          break;
        }

        case this.$t('chat.atTa'): {
          console.log('@@@')
          this.$emit('hasAtInList', {id:this.selectActive.fromId} )
          this.$emit('closeRightMenu')
          break
        }

        case this.$t('chat.collection'): {
          this.addNote()
          this.$emit('closeRightMenu')
          break;
        }

        case '置顶': {
          this.setGroupTopMsg(2)
          this.$emit('closeRightMenu')
          break;
        }

        case '取消置顶': {
          this.setGroupTopMsg(3)
          this.$emit('closeRightMenu')
          break;
        }

        case this.$t('account.msgNotification'): {
          // to do
          this.$emit('closeRightMenu')
          this.$emit('showAddRemind',this.selectActive)
          break;
        }

        case this.$t('chat.jump'): {
          console.log('view-content...')
          this.$emit('view-content')
          this.$emit('closeRightMenu')
          break;
        }

        case this.$t('chat.delete'): {
          this.delMsg(this.selectActive.targetId, this.selectActive.msgId)
          this.$emit('deleteMsg', this.selectActive)
          this.$emit('closeRightMenu')
          break;
        }

        default: {
          break
        }
      }
      this.$emit('clearMenuList')
    },
    /**
     * 如果是本地图片，另存为进行读写文件操作
     * @param {String} saveAs - 另存为路径
     */
    copyLocalImgSaveAs(saveAs) {
      let createStream, readStream
      readStream = this.$fs.createReadStream(this.selectActive.mainPath).pipe(createStream = this.$fs.createWriteStream(saveAs))
      readStream.on('close',  () => {
        this.$Service.log(`img 另存为 读取完成::`)
      });
      createStream.on('close', () => {
        this.$Service.log(`img 另存为 下载完成::`)
      });
    },
    /**
     * 如果是网络图片，另存为进行下载-解密操作
     * @param {String} saveAs - 另存为路径
     */
    async downloadNetImg(saveAs) {
      if (!this.selectActive.mainUrl) { // 更新msg
        await this.updateChatMsg().then(result => {
          console.log('updateChatmsg::::', result)
          this.selectActive.mainUrl = result
        })
      }
      let downloadFileParam = {
        localPath: saveAs,
        url: this.selectActive.mainUrl
      };
      console.log('downloadFileParam::::', downloadFileParam);
      this.$Service.file.downloadFile(downloadFileParam, downloadResp => {
        console.log('downloadFile finished:::', downloadResp)
        let reNamePath = `${downloadResp.localPath}.temp`;
        this.decryptImgs(this.selectActive.fileName, this.selectActive.encryptKey, reNamePath, downloadResp.localPath).then(resp => {
          this.$Service.log(`decrypted SaveAs:::img    ${resp.result}`)
          let deleteImgParam = {
            filepath: downloadResp.localPath,
            type: 2
          }
          this.$Service.file.fileOperate(deleteImgParam)

          let reNameImgParam = {
            filepath: reNamePath,
            type: 3,
            newName:downloadResp.localPath
          }
          this.$Service.file.fileOperate(reNameImgParam)
        })
      }, processRes => {
        console.log('downloading:::', processRes)
      })
    },
    /**
     * 上传的本地图片，mainUrl为空，更新msg以确保下载解密成功
     */
    updateChatMsg() {
      return new Promise(resolve => {
        let getMessagesParam = { targetId: this.selectActive.targetId, count: 1, msgId: this.selectActive.msgId, flag: 2}
        this.$Service.chat.getMessages(getMessagesParam, resp => {
          console.log('getMessages', resp)
          resolve(resp.msgs[0].mainUrl)
        });
      })
    },
    /**
     * 解析图片格式
     */
    getExtensionFilter() {
      let fileExtension = this.selectActive.fileName.substr(this.selectActive.fileName.lastIndexOf('.') + 1)
      let extensionFilter = [{ name: 'All Files', extensions: ['*'] }]
      if (fileExtension) {
        extensionFilter.unshift({ name: 'Files', extensions:[fileExtension] })
      }
      return extensionFilter
    },
    /**
     * 历史消息记录查看上下文
     */
    viewContext() {
      console.log('view context...')
      this.$emit('view-content')
    },
    /**
     * 【消息置顶】
     * 设置/取消 消息置顶
     * 2 置顶 _3取消置顶
     */
    setGroupTopMsg(type) {
      console.log('setGroupTopMsg:',type);
      console.log('setGroupTopMsg:msgTemp:::',Object.assign({},this.selectActive));
      let msgTemp = Object.assign({},this.selectActive);
      msgTemp.localId = "0"  
      if(!this.selectActive.hasOwnProperty('topListSign')){
        // 此时直接操作的是原消息体，因此需要设置relatedMsgId
        msgTemp.relatedMsgId = this.selectActive.msgId
      }
      console.log('======xx=',this.chat_objectInfo)
      msgTemp.createUserId = this.user_account.userId
      msgTemp.groupId  = this.id
      msgTemp.topUserId  = msgTemp.fromId
      msgTemp.topContent  = JSON.stringify({
        content:msgTemp.body,
        name:this.userInfo[this.selectActive.fromId].remark,
        jiebie:this.chat_objectInfo[this.id][this.selectActive.fromId].sector
      })

      msgTemp.status = 1
      msgTemp.type = type == 2? 5:7;
      msgTemp.topType = 1
      if(type == 3){
         msgTemp.id = msgTemp.topId
      }else{
        msgTemp.id = ''
      }
      msgTemp.createTime = ''
      msgTemp.updataTime = ''
      if(type == 2){
        msgTemp.createTime = new Date().toString()
      }
      console.log('in setGroupTopMsg:msgTemp:::',Object.assign({},msgTemp));
      this.$Service.chat.setGroupTopMsg(msgTemp, resp => {
        console.log('setGroupTopMsg:::', resp)
        if(resp.code === 0){
          msgTemp.msgId = this.selectActive.msgId
          if(type===2) {
            //this.$store.dispatch('SET_CHATCONTENT_TOP', msgTemp)
            this.updateChatTopMsg()
          } else if(type===3) {
            this.$store.dispatch('DEL_CHATCONTENT_TOP', msgTemp)
          }
        }
        else{
          this.$toast.open({message:resp.strInfo, type: 'is-danger'});
        }
      })
    },
    updateChatTopMsg(){
      let getGroupTopMsgByIdParam = {
        groupId: this.id,
        msgid: 0,
        pageNum: 1,
        pageSize: 100
      };
      this.$Service.chat.getGroupTopMsgById(getGroupTopMsgByIdParam, resp => {
        this.$store.dispatch('CLEAR_CHATCONTENT_TOP',{})
        if(resp.code === 0){
          _.forEach(resp.reminderMsgs, element => {
              this.$store.dispatch('SET_CHATCONTENT_TOP', element)
          })
        }
      })
    },
    /** 撤回消息 */
    revokeMsg() {
      let msgbase = {
        msgId: encryptionPassword(),
        fromId: this.user_account.userId,
        targetId: this.$route.query.id,
        body: `${this.user_account.name}`,
        msgType: 18,
        revokeMsgId: parseInt(this.selectActive.msgId),
        msgReEdit:
          this.selectActive.msgType === 2 ? this.selectActive.body : '',
        relatedUsers: this.selectActive.relatedUsers || []
        // isSenderRevoke: this.chatType === 2 && this.selectActive.msgType === 6 ? true : false
      }
      let msg = new MsgRetract(msgbase, 1)
      this.$store.dispatch('SET_CHATCONTENT', msg)
    },
    
    // * 复制消息
    copyMsg() {
      const range = window.getSelection();
      let text;
      let selectText = range.toString()
      let r = range.getRangeAt(0)
      range.removeAllRanges()
      range.addRange(r)
      if (selectText) { // 复制前 已有选中的文本
        if (r.commonAncestorContainer && r.commonAncestorContainer.parentElement && r.commonAncestorContainer.parentElement.className === 'text-content') { // 排除range 不在气泡上
          this.$Service.log(`copy rangeCenter in bubble`)
          if (range.getRangeAt(0).commonAncestorContainer.childNodes) {
            let container = document.createElement('div');
            let contents = range.getRangeAt(0).cloneContents()
            container.appendChild(contents);
            text =  removeHtml(container, container.innerHTML).content;
            if (text.includes('class="text-url-other"') || text.includes('class="text-url-mine"')) { // 选中有可能存在 <a></a>链接标签
              text = text.replace(/<a\s*[^>]*>(.*?)<\/a>/gi, "$1");
            }
          } else {
            text = selectText;
          }
        } else {
          this.$Service.log(`copy rangeCenter no bubble`)
        }
      }
      clipboard.writeText(text ? text :this.selectActive.body)
    },

    async addNote() {
      console.log('selectActive::::::::', this.selectActive)
      let msgInfo = {
        sendUserId: this.selectActive.fromId,
        type: this.selectActive.msgType,
        content: ''
      }
      switch (this.selectActive.msgType) {
        case 2: { // 文本
          msgInfo.content = {body: this.selectActive.body}
          break;
        }
        case 3: { // 语音
          msgInfo.content = {
            fileName: this.selectActive.fileName,
            mediaUrl: this.selectActive.url,
            mediaTime: this.selectActive.mediaTime,
            enc_dec_key: this.selectActive.encryptKey
          }
          break;
        }
        case 5: { // 图片
          msgInfo.content = {
            enc_dec_key: this.selectActive.encryptKey,
            fileName: this.selectActive.fileName,
            fromID: this.selectActive.fromID,
            height: this.selectActive.height,
            id: this.selectActive.msgId,
            mainPath: this.selectActive.mainPath,
            mediaUrl: this.selectActive.mainUrl,
            thumbPath: this.selectActive.thumbPath,
            thumbUrl: this.selectActive.thumbUrl,
            time: new Date().getTime(),
            width: this.selectActive.width,
          }
          if (!msgInfo.content.mediaUrl) {
            await this.updateChatMsg().then(result => {
              console.log('updateChatmsg::::', result);
              msgInfo.content.mediaUrl = result;
            })
          }
          break
        }    
        case 6: { // 文件
          msgInfo.content = {
            enc_dec_key: this.selectActive.encryptKey,
            fileName: this.selectActive.fileName,
            filePath: this.selectActive.filePath,
            fileSize: this.selectActive.size,
            targetId: this.selectActive.targetId,
            fromID: this.selectActive.fromID,
            id: this.selectActive.msgId,
            mediaUrl: this.selectActive.url,
            time: new Date().getTime(),
          }
          break
        }
        case 9: { // 网页链接
          msgInfo.content = {
            title: this.selectActive.title,
            description: this.selectActive.desc,
            url: this.selectActive.url,
            img: this.selectActive.img
          }
          break
        }
        case 89: { // 视频
          msgInfo.content = {
            videoLength: this.selectActive.vedioLenth,
            videoWidth: this.selectActive.vedioWideth,
            preImgPath: this.selectActive.preImgPath,
            videoFileName: this.selectActive.vedioFileName,
            videoHeight: this.selectActive.vedioHight,
            enc_dec_key: this.selectActive.encryptKey,
            videoSize: this.selectActive.vedioSize,
            targetId: this.selectActive.targetId,
            fromID: this.selectActive.sendUserId
          }
          break
        }
        default:
          break;
      }
      this.addNoteParam.id = '';
      this.addNoteParam.sendUserId = this.user_account.id;
      this.addNoteParam.targetId = this.user_account.id;
      console.log('传入的参数：', msgInfo);
      Object.assign(this.addNoteParam, msgInfo);
      this.addNoteParam.content = JSON.stringify(this.addNoteParam.content);
      console.log(this.addNoteParam, '添加收藏入参Json');
      this.$Service.enterprise.addNote(
        this.addNoteParam,
        resp => {
          console.log(resp, 'add note cb')
          if (resp.code === 0) {
            this.$toast.open({
              message: i18n.t('chat.addCollectionSuccess'),
              type: 'is-success'
            });
          }
        }
      )
    },
    
    headItemClick() {
      console.log('headDivider', this.headDivider)
      if (this.headDivider ===  this.$t('chat.copy')) {
        this.copyMsg()
        this.$emit('closeRightMenu')
      }
    },

    footerItemClick() {
      console.log('this.footerDivider', this.footerDivider)
      if (this.footerDivider === this.$t('chat.delete')) {
        this.delMsg(this.selectActive.targetId, this.selectActive.msgId)
        this.$emit('deleteMsg', this.selectActive)
        this.$emit('closeRightMenu')
      }
    }
  }
}
</script>
