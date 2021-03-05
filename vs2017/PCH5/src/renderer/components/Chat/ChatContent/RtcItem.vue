<template>
  <div class="rtc-file">
   
    <div class="rtc-file-area">
      <!-- 文件左侧区域 文件类型图片 -->
      <div class="file-left">
        <img :src="fileImg"/>
      </div>
      <!-- 文件右侧区域 文件信息展示 -->
      <div class="file-right">
        <!-- 文件名称显示 -->
        <div class="file-info">
          <span class="file-names" :title="rtcFile.messageObject.fileName" v-html="rtcFile.messageObject.fileName"></span>
          <!-- 文件尺寸显示 -->
          <span class="file-size" v-html="filesizeCompute"></span>
          <!-- <i class="icon" v-if="isShowRelay" :title="rtcState">&#xe63a;</i> -->
          <span class="" :title="rtcStateTip">{{rtcState}}</span>
        </div>
         <!-- 文件进度显示 -->
        <div class="file-process" v-if="isShowProgress">
          <p class="process-box">
            <span ref="process" :style="{width:progress+'px'}">
              <div v-if="speed" class="flare"></div>
            </span>
          </p>
          <div v-if="speed" class="file-transmiss-info">
            <span class="file-transmiss-speed">{{speed +'MB/s'}}</span>
            <span class="file-transmiss-time">{{timeLeft}}</span>
          </div>
        </div>
        <!-- 动态加载文件操作区域 文件下载 另存为 打开 打开所在位置 重新上传 重新下载 -->
       <rtc-item-operate :operateComponent='operateComponent' v-if="operateComponent"  @receiveEvent="receiveEvent"></rtc-item-operate>
      </div>
    </div>
     <!-- 文件提示 尤指rtc 文件的提示 -->
     <div class='file-tip' v-if="rtcErrorTip"><p class="tip-content" v-text="rtcErrorTip"></p></div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import { encryptionPassword } from '../../../../comm/util.js'
import { msgStructure } from '../Msg'
import RtcFileMixin from '../Mixins/RtcFileMixin.js'
import msgMixin from '../msgMixin'
import Animates from '../../Common/Animate'
import RtcItemOperate from './RtcItemOperate.vue'
import { OptionType, FileStatus, SubType } from '../../../../rtc/file/constant'
import { p2pUtils } from '../../../../rtc/file/p2pUtils.js'
const fileOperateComponent = {
      DOWNLOAD : 1,
      RTCTIP: 2,
      SEND: 3,
      CANCEL: 4
}
const { remote } = require('electron')
const postMsgToRender = remote.getGlobal('postMsgToRender')
export default {
  props: {
    rtcFile: Object | Array,
    id: String
  },
  mixins:[RtcFileMixin, msgMixin],
  data() {
    return {
      fileAvatar: String,
      operateComponent: 0, // 0 下载  1 进度条 2 打开 3重新下载 4重新上传
      progress: Number,
      isShowProgress: true,
      localId: Number,
      fileSizes: 0,
      isMine: Boolean,
      rtcErrorTip:'',
      rtcFilePath: '',
      isRegRtcFile: false,
      isRtcBeGgin: false,
      isReceive: false,
      speed: '',
      timeLeft: '',
      fileId: '',
      fileInfo: {},
      p2pUtils: {},
      isShowRelay: true,
      rtcState:'--',
      rtcStateTip: ''
    }
  },

  beforeDestroy() {
    console.log('beforeDestroy rtcItem')
    console.log('this.chat_rtc_del_model', this.chat_rtc_del_model)
    if (this.chat_rtc_del_model) {
      console.log('cancelOpera', this.chat_rtc_del_model)
      this.cancelOpera()
    }
  },

  mounted() {
    console.log('rtcFile--created', JSON.stringify(this.rtcFile))
    this.isMine = this.rtcFile.messageObject.fromId === this.user_account.userId;
    if (this.rtcFile.flag !== 1) {
      let body = this.rtcFile.body;
      this.fileInfo = JSON.parse(body).fileInfo;
      this.fileInfo.msgId = this.rtcFile.messageObject.msgId;
      // /** 设置rtc 文件传输状态 相当于锁 阻止其他文件发送 */
      this.isShowProgress = true;
      this.operateComponent = fileOperateComponent.DOWNLOAD
      console.log('receiveoperateComponent', this.operateComponent)
    } else {
      /** 发送直传文件 */
      this.send_rtcFile()
    }
  },
  methods: {
    /** 剩余时间格式化 hour : minute : second */
    timeToFormat(times) {
      let result;
      let hour,minute,second
      if (times > 0) {
        hour = Math.floor(times / 3600);
        if (hour < 10) {
          hour = "0" + hour;
        }
        minute = Math.floor((times - 3600 * hour) / 60);
        if (minute < 10) {
          minute = "0" + minute;
        }

        second = Math.floor((times - 3600 * hour - 60 * minute) % 60);
        if (second < 10) {
          second = "0" + second;
        }
        result = hour+':'+minute+':'+second;
      }
      return result;  
    },

    /** rtc 文件发送 */
    send_rtcFile() {
      console.log('send_rtcFile:::', this.rtcFile.messageObject.filePath)
      this.operateComponent = fileOperateComponent.SEND
     
      // /** 文件状态回调 */
      // let fileCallback = fileRes => {
      //   this.handleRtcResult(fileRes)
      // } 

      // /** 文件消息回调 */
      // let fileMsgCallback = msgRes => {
      //   this.fileInfo = msgRes
      //   msgRes.code === 0 ? this.rtcFile.messageObject.msgId =  msgRes.msgId :  console.log('rtc sendFail')
      // }
      this.$p2pUtils.sendFile(this.rtcFile.messageObject.targetId, this.user_account.userId, this.rtcFile.messageObject.filePath, fileRes => {
        this.handleRtcResult(fileRes)
      }, msgRes => {
         this.fileInfo = msgRes
         msgRes.code === 0 ? this.rtcFile.messageObject.msgId =  msgRes.msgId :  console.log('rtc sendFail')
      })
    },

    /** 接收rtc文件 */
    receviceRtcFile(savePath = this.user_filePath) {
      console.log('savePath:::::::::', savePath)
      this.speed = '0';
      this.timeLeft = '00:00:00';
      this.isShowProgress = true;
      /**恢复组件默认值 */
      this.operateComponent = 0;


      console.log('receive_fileInfo', this.fileInfo)
      this.$p2pUtils.acceptOrReject(this.rtcFile.messageObject.targetId, this.user_account.userId, this.fileInfo, true, savePath, acceptFileRes=> {
        this.handleRtcResult(acceptFileRes)
      });
    },

    /** 回调处理 */
    handleRtcResult(res) {
      console.log('handleRtcResult:::', res)
      this.rtcStateTip = res
      switch (res) {
        case FileStatus.HOST:
        case FileStatus.SRFLX:
        case FileStatus.PRFLX:
        case FileStatus.RELAY:
          this.isShowRelay = true;
          this.rtcState = res;
        break;
        case FileStatus.BEGIN :
        // this.$ipc.send('open_webrtc_stats', true);
        if (!this.isMine) {
          this.operateComponent = fileOperateComponent.CANCEL;
        }
        break;

        case FileStatus.CANCEL :
        console.log('delRtcFile::::::::::CANCEL', this.fileInfo)
        this.delRtcFile();
        break

        case FileStatus.TIMEOUT :
        this.delRtcFile();
        if (this.isMine) {
          this.showWeakMsg(`对方长时间未响应， 文件【${this.fileInfo.filename}】被取消`)
        }
        this.delMsg(this.rtcFile.messageObject.targetId, this.fileInfo.msgId)
        break

        case FileStatus.ERROR_NET:
        case FileStatus.ERROR_RTC:
        this.$p2pUtils.addDiscMsg(this.rtcFile.messageObject.targetId, this.user_account.userId, this.isMine, this.fileInfo, res,  res => {
          console.log('addDiscMsg res:::', res)
        })

        this.isShowProgress = false
        this.speed = 0;
        this.timeLeft = 0;
        this.rtcErrorTip = '网络连接异常'
        if (!this.isMine) {
          this.delRtcFile();
          this.showWeakMsg(`您终止了【${this.fileInfo.filename}】的发送`)
        } else {
          this.operateComponent = fileOperateComponent.RTCTIP 
        }
        break

        case FileStatus.ACCEPT :
        console.log('delRtcFile::::::::::FileStatus.ACCEPT')
        break

        case FileStatus.END :
        this.rtcFile.flag = 0;
        this.$store.dispatch('SET_CHATCONTENT', this.rtcFile)
        if (!this.isMine) {
          console.log('commit weak')
          this.showWeakMsg(`文件【${this.fileInfo.filename}】 传输成功`)
        }
        console.log('RtcItem:end')
        let copyFile = Object.assign({}, this.rtcFile.messageObject)
        let body = {
          'VideoStatus':'file',
          'subType': SubType.SEND,
          'isdeal' : true,
          'fileInfo':this.fileInfo
        }
        this.$set(copyFile, 'body', JSON.stringify(body))
        this.$set(copyFile, "msgType", 14)
        this.$set(copyFile, 'isOri', true)
        console.log('fileEnd', copyFile)
        this.$Service.chat.updateMsg(copyFile, resp => {
          console.log('updateMsg', resp)
        })
        this.$p2pUtils.success(this.rtcFile.messageObject.targetId, this.user_account.userId, this.isMine, this.fileInfo, res => {
          console.log('res:::', res)
        })
        this.delRtcFile();
        break

        default:
        this.rtcStateTip = `进度:${Math.floor(res.percent * 100)}%`
        if (this.$refs.process) {
        this.$refs.process.style.width = Math.floor(res.percent * 100)* 1.85 + 'px'
        this.speed = (res.rate / 1000000).toFixed(1)
        this.timeLeft = this.timeToFormat(res.timeleft)
        }
        break
      }
    },

    /** rtc 文件另存为 */
    rtcFileSaveAs() {
      let saveAs = this.$dialogs.showSaveDialog({ defaultPath: this.rtcFile.messageObject.fileName })
      if (saveAs) {
        this.rtcFile.messageObject.filePath = saveAs;
        let path
        if(!this.$is.isOSX) { 
          path = saveAs.slice(0, saveAs.lastIndexOf('\\') + 1)
        } else {
          path = saveAs.slice(0, saveAs.lastIndexOf('\/') + 1)
        }
        this.receviceRtcFile(path)
      }
    },

    send_File() {
      this.cancelOpera();
      let offLineFileMsg = Object.assign({}, this.rtcFile.messageObject)
      offLineFileMsg.preDefined = ''
      offLineFileMsg.msgId = encryptionPassword().toString()
      let fileMsg = {
        flag: 1,
        messageObject: offLineFileMsg
      }
      this.$store.dispatch('SET_CHATCONTENT', fileMsg)
      this.delRtcFile();
    },
    

    rejectRtcFile() {

      this.$p2pUtils.acceptOrReject(this.rtcFile.messageObject.targetId, this.user_account.userId, this.fileInfo, false, this.user_filePath, res => {
        // console.log('RtcItem::receviceRtcFile => ',res);
        this.handleRtcResult(res)
      });
      this.delRtcFile();
    },

    /** 取消文件上传或者下载 */
    cancelOpera() {
      console.log('cancel_file_info', this.fileInfo)
      console.log('this.isMine::', this.isMine)
      let cancelCb = res => {
        console.log('cancel', res)
        if (res.code === 0) {
        //  let msgTip = this.isMine ? '发送方' : '接收方'
         let msgTip = `您取消了【${this.fileInfo.filename}】的${this.fileInfo.isSender?'发送':'接收'}，文件传输失败`
        //  this.showWeakMsg(`文件【${this.fileInfo.filename}】 被${msgTip}取消`)
         this.showWeakMsg(msgTip)
         this.delMsg(this.rtcFile.messageObject.targetId, this.fileInfo.msgId)
        } 
      }
      return this.$p2pUtils.cancel(this.rtcFile.messageObject.targetId, this.user_account.userId, this.isMine, this.fileInfo, cancelCb)
    },

    /** 删除rtcFile */
    delRtcFile() {
      this.$store.commit('DEL_RTC_FILE', {id: this.id, msgId: this.rtcFile.messageObject.time})
      this.$emit('isCloseExpend')
    },

    /**
     * 根据子组件选择 来处理不同的文件操作
     * file_down 文件下载
     * file_open 打开文件
     * file_upload 文件上传
     * file_open_dectionary 打开文件位置
     */
    receiveEvent(opt) {
      switch (this.operateComponent) {
        case fileOperateComponent.DOWNLOAD: // file_down 文件下载
        { 
          if (opt === 0) {
            this.rtcFile.messageObject.filePath = this.user_filePath + this.rtcFile.messageObject.fileName;
            this.receviceRtcFile()
          } else if (opt === 1){
            this.rtcFileSaveAs()
          } else {
           this.rejectRtcFile()
          }
          break;
        }
        case fileOperateComponent.SEND: 
        {
          opt === 1? this.cancelOpera() : this.send_File()
          break;
        }
        case fileOperateComponent.CANCEL:
        {
          this.cancelOpera();
          break;
        }
        case fileOperateComponent.RTCTIP : 
        { 
          if (opt === 0) {
            this.send_rtcFile()
          } else if (opt === 1) {
            this.send_File()
          } else {
            this.cancelOpera();
          }
          break;
        }
      }
    },
    

    // 显示弱提示消息
    showWeakMsg(body) {
      let copyMsg = Object.assign({}, this.rtcFile.messageObject)
      let fileNameJSON = {filename: this.rtcFile.messageObject.fileName}
      let weakMsg = {
          flag:0,
          messageObject : {
            targetId: this.rtcFile.messageObject.targetId,
            fromId: this.user_account.userId,
            msgType: 8,
            body: body,
            tipType: 12,
            time : new Date().getTime().toString(),
            msgId: `${encryptionPassword()}wk`,
            fileInfo: fileNameJSON.toString()
          }
      }
      this.$store.dispatch('SET_CHATCONTENT', weakMsg)
    }

  },
  components: { 
    RtcItemOperate,
    Animates
  },
  computed: {
    fileImg() {
      // 判断文件类型，使用对应的图片
      const fileName = this.rtcFile.messageObject.fileName
      const ext = fileName.substr(fileName.lastIndexOf('.') + 1)
      switch (ext) {
        case 'pdf': return (this.fileAvatar = require('vrv-static/resources/images/message/pdf.png'))
        case 'txt': return (this.fileAvatar = require('vrv-static/resources/images/message/txt.png'))
        case 'xls': return (this.fileAvatar = require('vrv-static/resources/images/message/execl.png'))
        case 'xlsx': return (this.fileAvatar = require('vrv-static/resources/images/message/execl.png'))
        case 'ppt': return (this.fileAvatar = require('vrv-static/resources/images/message/ppt.png'))
        case 'exe': return (this.fileAvatar = require('vrv-static/resources/images/message/install.png'))
        case 'zip': return (this.fileAvatar = require('vrv-static/resources/images/message/package.png'))
        case 'doc': return (this.fileAvatar = require('vrv-static/resources/images/message/word.png'))
        case 'docx': return (this.fileAvatar = require('vrv-static/resources/images/message/word.png'))
        default: return (this.fileAvatar = require('vrv-static/resources/images/message/unknown.png'))
      }
    },
    filesizeCompute() {
      /** 计算文件大小 */
      this.fileSizes = this.rtcFile.messageObject.size

      if (this.fileSizes === 0) return '0 B';
      let k = 1000, 
          sizes = ['B', 'KB', 'MB', 'GB', 'TB', 'PB', 'EB', 'ZB', 'YB'],
          i = Math.floor(Math.log(this.fileSizes) / Math.log(k));
  
      return (this.fileSizes / Math.pow(k, i)).toPrecision(3) + ' ' + sizes[i];
          
    },
    ...mapGetters(['user_filePath', 'user_account',  'chat_chatList', 'chat_P2P_file_state', 'chat_rtc_file_list', 'chat_rtc_del_model'])
  }
}
</script>
<style lang="scss" >
.rtc-file {
  margin-bottom: 10px;
  font-size: $--font-size-small;
    .file-operate {
      // height: 11px;
      line-height: 11px;
      flex: 1;
      display: flex;
      justify-content: flex-end;
      align-items: center;
      // font-size: $--font-size-small;
      color: get-blue-color(darken-1);
      margin-right: 4px;
    .file-operate-btns {
      margin-right: 4px;
      color: get-blue-color(darken-1);
      &:hover {
      cursor: pointer;
      }
    }
  }
  .file-tip {
    text-align: end;
    font-size: 11px;
    color: $--color-msg-prompt-middle;
    margin-right: 2px;
    line-height: 12px;
    margin-top: 2px;
  }
}
.rtc-file-area {
  width: 100%;
  display: flex;
  padding: 4px 4px 0px 4px;
  margin: 2px 2px 0 2px;
  .file-left {
    width: 42px;
    height: 42px;
    margin-right: 4px;
  }
  .file-right {
    flex: 1;
    display: flex;
    flex-direction: column;
    color: #000;
    .file-info{
      width: 100%;
      display: flex;
      height: 18px;
      justify-content: space-between;
      .file-names {
        width: 100px;
        @include ellipsis;
      }
      .file-size {
        display: flex;
        justify-content: flex-start;
        align-items: center;
        font-size: 10px;
        line-height: 16px;
        color: get-grey-color(base);
      }
    }


    .file-process {
      height: 12px;
      display: flex;
      align-items: center;
      position: relative;
      .file-transmiss-info {
        position: absolute;
        left: 0px;
        top: 10px;
        font-size: 11px;
        .file-transmiss-time {
          color: $--color-msg-prompt-middle;
        }
      }
      .process-box {
        height: 3px;
        width: 185px;
        background: #dcdcdc;
        display: flex;
        span {
          width: 0px;
          height: 3px;
          background: $--color-success;
          @include z-index(btn);
          .flare {
            animation-name: barshine;
            animation-duration: 6s;
            animation-direction: normal;
            animation-fill-mode: forwards;
            animation-timing-function: cubic-bezier(.14, .75, .2, 1.01);
            animation-iteration-count: infinite;
            left: 0;
            top: 4px;
            width: 30px;
            height: 3px;
            position: absolute;
            background: radial-gradient(ellipse at center, rgba(255, 255, 255, 0.79) 0%, rgba(255, 255, 255, 0) 87%);
            z-index: 10;
          }
        }
      }
    }
  }
}
@keyframes barshine {
  0% {
    left: 0;
  }
  100% {
    left: calc(100% - 30px);
  }
}
</style>
