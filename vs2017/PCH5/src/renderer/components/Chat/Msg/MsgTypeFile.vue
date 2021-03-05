<template>
  <div class="type-file">
    <div class="file-area">
      <!-- 文件左侧区域 文件类型图片 -->
      <div class="file-left">
        <img :src="fileImg"/>
      </div>
      <!-- 文件右侧区域 文件信息展示 -->
      <div class="file-right">
          <!-- 文件名称显示 -->
          <div class="file-names" :title="fileName" v-html="fileName"></div>
          <div class="file-extra-info">
          <!-- 文件尺寸显示 -->
           <div class="file-size" v-html="filesizeCompute"></div>
           <div v-if="fileExtension" class="file-extension" >{{fileExtension}}</div>
           


          </div> 
         <!-- 文件进度显示 -->
        <div class="file-process" v-if="operateComponent === 2" >
          <p class="process-box">
            <span ref="process" :style="{width:progress+'px'}"></span>
          </p>
          <!-- 文件上传取消按钮 -->
          <i class="icon cancel-opera" @click.stop="cancelOpera">&#xe650;</i>
        </div>
        <div class="file-readonly" v-if='isReadOnly' :title="readOnlyTip">
          {{$t('chat.readOnly')}}
        </div>
      </div>
      <!-- 文件状态显示 -->
      <i v-if="state===-1" class="icon msg-state" @click="send_File()">&#xe63b;</i>
    </div>
    <!-- 动态加载文件操作区域 文件下载 另存为 打开 打开所在位置 重新上传 重新下载 -->
    <div class="file-operate-area">
      <div class="file-transmiss-info" v-if="speed">
        <span class="file-transmiss-speed">{{speed}}</span>
        <span class="file-transmiss-time">{{timeLeft}}</span>
        <!-- <span class="file-transmiss-speed">{{'62.13kb'}}</span>
        <span class="file-transmiss-time">{{'00:00:00'}}</span> -->
      </div>
      <file-operate v-if="operateComponent && operateComponent !== 2"  :operateComponent = operateComponent :isEcrypted='isEcrypted'   @receiveEvent="receiveEvent"></file-operate>
    </div>
  </div>
</template>
<script>
import { mapGetters } from 'vuex'
import { encryptionPassword } from '../../../../comm/util.js'
import FileMixin from '../Mixins/FileMixins';
import msgMixin from '../msgMixin.js';
import FileOperate from './FileOperate';
const fileOperateComponent = {
      DOWNLOAD : 1,
      PROGRESS: 2,
      OPEN: 3,
      REDOWN: 4,
      REUPLOAD: 5,
      RTCTIP: 6
}
export default {
  props: {
    message: Object,
    id: String,
    chatType: Number | String
  },
  data() {
    return {
      encryptFileSavePath: String, // 加密文件存放位置
      decryptFiles: String, // 解密文件
      operateComponent: 0, // 0 下载  1 进度条 2 打开 3重新下载 4重新上传
      state: 0, // 0 成功 -1发送失败
      progress: Number,
      localId: Number,
      isUpload: false,
      fileName: '',
      rtcFilePath: '',
      isMine: false,
      isShowLoad: false,
      isRtcFile: false,
      isFileAnotherSave: false,
      isFail: false,
      isReadOnly: false,
      readOnlyTip: this.$t('chat.readOnlyTip'),
      last_time: 0,
      last_percent: 0,
      file_size: 0,
      speed: 0,
      timeLeft: 0,
      fileExtension: '', //  文件名扩展字段
      isEcrypted: false,
      dialogCount: 0
    }
  },
  mixins: [FileMixin, msgMixin],
  mounted() {
    /**
     * isRtcFile
     * isMine 是否是自己发送的 后面多次需要判断 
     * flag 1 自己发送的文件 需要上传
     * uploadInfo 文件上传的基本信息
     */
    console.log('message', this.message)
    this.fileName = this.message.messageObject.fileName
    this.isMine = this.message.messageObject.fromId === this.user_account.userId
    this.isRtcFile = this.message.messageObject.preDefined && JSON.parse(this.message.messageObject.preDefined).RtcFile
    this.fileExtension = this.message.messageObject.fileName.substr(this.message.messageObject.fileName.lastIndexOf('.') + 1)
    this.isEcrypted = this.message.messageObject.encryptKey !== ''
    console.log('this.isEcrypted', this.isEcrypted)
    if (this.isRtcFile) { // rtc文件
      this.rtcFilePath = this.message.messageObject.filePath;
      this.$nextTick(() => { this.operateComponent = fileOperateComponent.OPEN })

    } else { // * 非RTC文件消息 
  
      if (this.message.flag === 1) { 
        this.message.flag = 0;
        // * 一键发送文件   
        this.send_File()
      } else {
        // * 获取文件消息状态 可能存在上传失败或者下载失败的消息
        this.getFileState() 

        /** 文件可能直接存在 */
        if (this.message.messageObject.filePath && this.$Service.file.fileOperate({ filepath: this.message.messageObject.filePath, type: 0})) {
          
          this.operateComponent = fileOperateComponent.OPEN
          this.encryptFileSavePath = this.message.messageObject.filePath
          this.$Service.log(`file has --exsist   ${this.encryptFileSavePath}`)
          /** 文件可能为只读文件 */
          if (this.encryptFileSavePath.indexOf(this.user_filePath)!== -1) {
            this.message.messageObject.defaultPath = this.encryptFileSavePath
            this.isReadOnly = true
          }

          console.log('state::', this.state)
          if (this.state === -1) this.operateComponent = fileOperateComponent.REUPLOAD
        } else {
          this.getFileInfo(this.user_filePath, this.message.messageObject.url).then(successResult => { /** 获取文件信息 */
            console.log('successResult', successResult)
            if (this.isExistFile) {
              this.operateComponent = fileOperateComponent.OPEN

              let isDefaultPath = this.encryptFileSavePath.indexOf(this.user_filePath)!== -1

              if (isDefaultPath) {
                this.message.messageObject.defaultPath = this.encryptFileSavePath;
                this.isReadOnly = true
              } 
            } else {
              if (!this.isEcrypted) {
                this.encryptFileSavePath = (this.user_filePath + this.fileName).replace(/\//ig, '\\')
                this.$Service.log(`encryptFileSavePath is not encrypt  ${this.encryptFileSavePath}`)
              }
              console.log('encryptFileSavePath', this.encryptFileSavePath)
              this.operateComponent = fileOperateComponent.DOWNLOAD; // 0 下载  2 打开
              console.log('this.encryptFileSavePath', this.encryptFileSavePath)
            }
            console.log('state::', this.state)
            if (this.state === -1) this.operateComponent = fileOperateComponent.REUPLOAD
          })
        }
      }
    }
  },
  
  methods: {
    
    /**
     * 根据messageType 来判断消息的状态
     * messageType 518 发送失败
     * messageType 262 上传失败
     */
    getFileState() {
      let msgType = this.message.messageObject.msgType
      if (msgType === 518 || msgType === 262) {
        this.state = -1;
        this.$emit('disableRightClick')
      } 
    },

  /**
    * 一键发送文件
    * @param encryptKey 文件加密密码
    * @param fileName   文件名称
    * @param filePath   文件路径
    * @param fromId     发送者Id
    * @param localId    本地Id 本地唯一标识
    * @param msgType    消息类型
    * @param targetId   聊天对象Id
    */
    send_File() {
      if (this.isRtcFile) this.isRtcFile = false; 
      if (this.state !== 0) this.state = 0 // 防止点击多次发送 
      this.$nextTick(() => {
        this.operateComponent = fileOperateComponent.PROGRESS; // 进度条出现
      })
      this.encryptFileSavePath =  this.message.messageObject.filePath;
      this.isUpload = true;
      if(this.message.messageObject.msgType !== 6) this.message.messageObject.msgType = 6; //消息发送失败 重新发送需要修正type

      this.localId = this.message.messageObject.localId
    
      this.$Service.chat.sendAppendixMessage(this.message.messageObject, resp => {
        console.log('sendAppendixMessage', resp)
        this.$Service.log(`sendFile:: ${resp.code}`)
        this.isUpload = false;
        this._initSpeed()
        if (resp.code === 0) {
          let preMsgId = this.message.messageObject.msgId
          console.log('operateComponent', this.id, preMsgId, resp.msgId)
          this.$store.commit('UPDATE_MSGID', {id:this.id, preMsgId:preMsgId, msgId: resp.msgId, isFail: this.isFail, time: resp.time})
         
          this.operateComponent = fileOperateComponent.OPEN
          this.$emit('hasRead', resp.msgId)
        } else {
          this.state = -1 // state -1 为消息发送失败
          if (!this.isFail) {
            this.isFail = true;
          }
          this.operateComponent = fileOperateComponent.REUPLOAD
          if (this.$route.query.id !== this.message.messageObject.targetId) {
            this.$store.dispatch('CHANGE_CHAT_LIST_STATE', {id: this.message.messageObject.targetId, type: 2} )
          }
        }
      }, progress => { 
        console.log('progress', progress)
        this.$nextTick(()=> {
          if (this.$refs.process) {
           this.$refs.process.style.width = progress.process*1.36 + 'px'
           this.getFileSpeed(progress.process)
          }
        })
      })
    },
    
    downLoad() {
      this.isFileAnotherSave = false
      this.operateComponent = fileOperateComponent.PROGRESS// 出现进度条

      let downloadFileParam = {
          targetId: this.message.messageObject.targetId, // 目标ID	有可能是群或者人 targetID
          msgId: this.message.messageObject.msgId, // 消息的msgID
          fromUserId: this.message.messageObject.fromId, // 发送者ID fromID
          localPath: this.encryptFileSavePath, // 文件本地保存路径
          encryptKey: this.message.messageObject.encryptKey,
          url: this.message.messageObject.url, // 远程路径,从消息JSON中解析出来的路径 remotePath
          bIsResume: true, // 是否断点续传
          fileName: this.message.messageObject.fileName,
          localId: this.localId // 本地唯一Id
      }

      console.log('downloadFileParam', downloadFileParam)
       let downloadFileCb = resp => {
          console.log('downloadFileCb', resp)
       
          this.$Service.log(`downLoadFile--resp   ${resp.code}`)
          this._initSpeed()
          if (resp.code === 0) {
            if (!this.isMine&&this.chatType==1) {
              this.handleReceiptWeak({tipType: 8, operType: 1, isStore:1,  operUser: this.user_account.name, fileInfo: this.message.messageObject.fileName}) 
            }
            this.operateComponent = fileOperateComponent.OPEN
            if (this.encryptFileSavePath.includes(this.user_filePath)) {
              this.message.messageObject.defaultPath = this.encryptFileSavePath;
              this.isReadOnly = true
            }


            // * 特殊处理大文件同名文件下载
            if (!this.isEcrypted) {
              let index
              if(!this.$is.isOSX) { 
                index = resp.localPath.lastIndexOf('\\');
              } else {
                index = resp.localPath.lastIndexOf('\/');
              }
              console.log('name', resp.localPath.substr(index + 1))
              this.fileName =  resp.localPath.substr(index + 1)
              this.encryptFileSavePath = resp.localPath
              this.$Service.log(`file is not decrypted  ${this.fileName}`)
            }
          //  /**
          //    * 下载完成后 判断cache 文件夹中是否已经存在解密后的文件（防止前后发送文件相同）
          //    * 如果存在 要删除cache 文件夹中的解密文件
          //    */
          //   let cachePath = `${this.user_filePath}cache/` // 加密文件保存的路径
          //   let createFile = this.$Service.file.fileOperate({ filepath: cachePath, type: 1 })

          //   /** 创建解密缓存文件夹 */
          //   this.decryptFiles = cachePath + this.message.messageObject.fileName 
          //   let fileOperateParam = {
          //       filepath: this.decryptFiles, //解密路径
          //       type: 0 // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
          //   }

          //   /** 如果已经存在相同解密文件 删除处理 */
          //   if (this.$Service.file.fileOperate(fileOperateParam)) {
          //     this.$Service.file.fileOperate({filepath:this.decryptFiles, type:2});
          //   }

          //   /** 如果没有文件密码 则代表文件较大无需解密 手动复制到揭秘文件夹*/
          //   if (this.message.messageObject.encryptKey) return
          //   // this.handleNoPasswordFile(this.encryptFileSavePath, this.user_filePath +'cache/'+ this.message.messageObject.fileName)
          } else { //文件下载失败
            if (resp.code === -16777206) {
              this.$toast.open({duration: 1500, message: this.$t('groups.resourceExpired'), position: 'is-top', type: 'is-danger'});
            }
            this.operateComponent = fileOperateComponent.REDOWN;
            this.$Service.log('downLoadFile fail')
          }
        
       }

       this.localId = this.$Service.file.downloadFile(downloadFileParam, downloadFileCb, processRes => {
          if (this.$refs.process) {
            this.$refs.process.style.width = processRes.progess*1.36 + 'px'
            this.getFileSpeed(processRes.progess)
          }
       })
       console.log('this.localId', this.localId)
    },
    


    showSaveDialog() {
      return new Promise(resolve => {
        /**
         * 文件后缀过滤 
         * 若存在文件后缀 限制保存格式
         * 不存在后缀名称 则支持所有文件类型
         */
        let extensionFilter = [{ name: 'All Files', extensions: ['*'] }]
        // if (this.message.messageObject.fileName.lastIndexOf('.') !== -1) {
          // let fileExtension = this.message.messageObject.fileName.substr(this.message.messageObject.fileName.lastIndexOf('.') + 1)
          if (this.fileExtension) {
            extensionFilter.unshift({ name: 'Files', extensions:[this.fileExtension] })
            console.log('extensionFilter::', extensionFilter)
          }
        // }
        console.log('dialogCount:::::', this.dialogCount)
        if (this.dialogCount >= 1) return
        this.dialogCount++
        this.$dialogs.showSaveDialog({ defaultPath: this.message.messageObject.fileName, filters: extensionFilter }, resp => {
          this.dialogCount--
          resolve(resp)
        })
      })
    },
    /*
     * saveAs 文件另存为
     * dialog.showSaveDialog 返回文件另存路径
     */
    async saveAs(isReDown=false) {
      this.isFileAnotherSave = true
      let saveAs,
          isCover  // 是否覆盖安装
      
      this.$Service.log(`saveAs fileName ${this.message.messageObject.fileName}`)
      if (!isReDown) {
        saveAs = await this.showSaveDialog()
        console.log('saveAs:', saveAs)
        if (saveAs) {
          this.encryptFileSavePath = saveAs;
        }
      }
      console.log('saveAs:::', saveAs)
      if (saveAs||isReDown) {
        // let fileOperateParam = {
        //     filepath: saveAs||this.encryptFileSavePath, //解密路径
        //     type: 0 // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
        // }
        // isCover = this.$Service.file.fileOperate(fileOperateParam)
        // console.log('isCover', isCover)
        // if (isCover) {
        //   this.$Service.file.fileOperate({filepath: saveAs, type:2});
        // }
        // this.encryptFileSavePath = saveAs;
        this.operateComponent = fileOperateComponent.PROGRESS // 出现进度条
        let downLoadFileCb = resp => {
        if (this.$refs.process) {
            this.$refs.process.style.width = resp.progess*1.36 + 'px'
            this.getFileSpeed(resp.progess)
          }
        } 
        this.downLoadFile(downLoadFileCb).then((successResp) => {
          console.log('saveas', successResp)
          this._initSpeed()
          if (successResp.code === 0) {
            if (!this.isMine&&this.chatType==1) {
              this.handleReceiptWeak({tipType: 8, operType: 1, isStore:1,  operUser: this.user_account.name, fileInfo: this.message.messageObject.fileName}) 
            }
            // let index = successResp.localPath.lastIndexOf('\\');
            let index
            if(!this.$is.isOSX) { 
              index = successResp.localPath.lastIndexOf('\\');
            } else {
              index = successResp.localPath.lastIndexOf('\/');
            }
            console.log('name', successResp.localPath.substr(index + 1))
            this.fileName =  successResp.localPath.substr(index + 1)
            this.encryptFileSavePath = successResp.localPath
            let reNamePath = `${successResp.localPath}.temp`;
            this.$Service.log(`reNamePath::: ${reNamePath}`)

              if (!this.message.messageObject.encryptKey) {
                this.operateComponent =  fileOperateComponent.OPEN
                return 
              }

              this.decrypted(this.message.messageObject.encryptKey, this.encryptFileSavePath, reNamePath).then(decryptRes => {
                console.log('decryptRes', decryptRes)
                if (decryptRes.result) {
                  let delRes = this.$Service.file.fileOperate({ filepath:this.encryptFileSavePath, type:2 });
                  console.log('delRes', delRes)
                  let fileOperateParam = {
                    filepath: reNamePath, //路径
                    type: 3, // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
                    newName:this.encryptFileSavePath, //重命名文件全路径  
                  }
                  let renameRes = this.$Service.file.fileOperate(fileOperateParam)
                  this.$Service.log(`renameRes::: ${renameRes}`)
                  this.operateComponent =  fileOperateComponent.OPEN
                } 
              })
          } else {
            this.$Service.log('downLoadFile fail in saveAs')
            return this.operateComponent =  fileOperateComponent.REDOWN;
          }
        })
      }
    },

    /*
     * 打开文件目录
     * 打开之前判断是否需要解密
     */
    openDirectory() {
      if (this.isRtcFile) {
        this.openDirectoryByMain(this.rtcFilePath)
        return 
      }
      if (!this.isEcrypted) {
        this.openDirectoryByMain(this.encryptFileSavePath)
        return
      }
      this.isNeedDecrypt().then(() => {
        this.openDirectoryByMain(this.decryptFiles)
      })
    },
    /**
     * 交由主进程处理，避免渲染进程阻塞
     * @param { String } path -- 文件路径
     */
    openDirectoryByMain(path) {
      this.$ipc.send('open-filedir', path)
    },
    /*
     * 打开文件
     * 打开文件之前同样判断是否需要解密
     */
    open() {
      if (this.isRtcFile) {
        this.openFileOrDir({path: this.rtcFilePath, operType: 1}) // operType 1 打开文件
        return
      } 
      if (!this.isEcrypted) {
        this.openFileOrDir({path: this.encryptFileSavePath, operType: 1}) // operType 1 打开文件
        return
      }
      this.isNeedDecrypt().then(() => {
      this.openFileOrDir({path: this.decryptFiles, operType: 1}) // operType 1 打开文件
        // let fileOperateParam = {
        //   filepath: this.decryptFiles, //路径
        //   type: 7, // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
        //   operType: 1
        // }
        // this.$Service.file.fileOperate(fileOperateParam, openRes => {
        //   console.log('openRes', openRes)
        // })
        // let isOpenSuccess = this.$shell.openItem(this.decryptFiles)
        // if(!isOpenSuccess) this.$dialog.alert({message: this.$t('chat.fileDamage'), confirmText: this.$t('common.sure'), onConfirm: () => {}});
      })
    },

    /**
     * openFileOrDir 打开文件或者打开文件位置
     * @param {String} path  文件路径
     * @param {Number} operType  操作类型 1 打开文件 2 打开文件位置
     */
    openFileOrDir(arg) {
      return new Promise(resolve => {
        let fileOperateParam = {
          filepath:  !this.$is.isOSX ? arg.path: arg.path.replace(/\(/ig, '\\(').replace(/\)/ig, '\\)'), //路径
          type: 7, // 操作类型 0：判断文件或文件夹是否存在 1.创建文件夹 2.删除文件 3.重命名文件
          operType: arg.operType
        }
        console.log('fileOperateParam', fileOperateParam)
        this.$Service.file.fileOperate(fileOperateParam, openRes => {
          this.$Service.log(`openRes :: ${openRes.result}`)
          resolve(openRes)
        })
      }) 
    },

    /**
     * 判断文件是否需要解密
     * saveAs 自己发送的文件 不需要解密/或者已经解密
     * 只读文件点击确定后 打开
     */
    isNeedDecrypt() {
      return new Promise ((resolve) => {
        if (this.encryptFileSavePath === this.user_filePath + this.downName) {
          this.decryptFiles = this.createCachePath(this.user_filePath, this.message.messageObject.fileName, this.message.messageObject.uuid)
            if (!this.message.messageObject.encryptKey) {
              this.handleNoPasswordFile(this.encryptFileSavePath, this.decryptFiles)
              resolve()
              return
            }
            /**
             * @param {String} encryptkey 解密密码
             * @param {String} srcpath 原图路径
             * @param {String} destpath 保存路径
             * @param {Number} flag 是否可读  1 可读可写  2只读 
             */  
            // this.handleDuplicatFile()
            this.decrypted(this.message.messageObject.encryptKey, this.encryptFileSavePath, this.decryptFiles, 2).then(decryptedRes => {
              if (decryptedRes.result) {
                resolve()
              } 
            })
          // }});
        } else {
          this.decryptFiles = this.encryptFileSavePath
          resolve()
        }
      })
    },

    /** 取消文件上传或者下载 */
    cancelOpera() {
      let cancelTransferParam = {
          localId: this.localId,     // 文件的localId
          type: this.isUpload ? 1 : 2         //  1.上传 2.下载 3.外部下载    
      }
     let cancelTransferCb = resp => {
       console.log('cancelTransferCb', resp)
      //  if (resp.code === 0) {
      //    this.operateComponent = this.isUpload ?  fileOperateComponent.REUPLOAD : fileOperateComponent.REDOWN
      //  }
     }
     this.$Service.file.cancelTransfer(cancelTransferParam, cancelTransferCb) 
    },

    /**
     * 处理无密码文件
     * 手动复制到指定位置
     * @param {String} srcpath 源路径
     * @param {String} destpath 目的路径
     */
    handleNoPasswordFile(srcpath, destpath) {
      this.$fs.createReadStream(srcpath).pipe(this.$fs.createWriteStream(destpath))
    },

    getFileSpeed(process) {
      
      let cur_time = new Date().getTime(); // 毫秒
      let usedTime = (cur_time - this.last_time)/1000;  //两个时间戳相差的秒数 
      if (usedTime < 1.5) return
      this.last_time = cur_time; 
      let rate = (process/100 - this.last_percent/100)*this.file_size/usedTime; // Byte/s
      let cur_speed
      if (rate > 1024 * 1024){
        cur_speed = (rate / (1024 * 1024)).toFixed(1) + 'MB/s';
      } else if (rate > 1024) {
        cur_speed = (rate / 1024 ).toFixed(1) + 'KB/s';
      } else {
        cur_speed = rate.toFixed(1) + 'B/s';
      }
      if (parseInt(cur_speed) <= 0) return
      this.speed = cur_speed
      this.last_percent = process
      this.timeLeft = this.timeToFormat((1 - (process/100)) * this.file_size / rate)
    },

    _initSpeed() {
      this.speed = 0;
      this.last_percent = 0;
      this.timeLeft = 0;
    },

    /**
     * 根据子组件选择 来处理不同的文件操作
     * file_down 文件下载
     * file_open 打开文件
     * file_upload 文件上传
     * file_open_dectionary 打开文件位置
     */
    receiveEvent(opt) {
     console.log('this.operateComponent', this.operateComponent)
      switch(this.operateComponent){
        case fileOperateComponent.DOWNLOAD: // file_down 文件下载
        { 
          if (opt === 1) {
             this.isRtcFile ? this.rtcFileSaveAs() : this.saveAs() 
          } else {
            this.isRtcFile ? this.rtcFileDownLoad() : this.downLoad(); 
          }
          break;
        }
        case fileOperateComponent.OPEN: {
          opt === 1 ? this.openDirectory() : this.open();
          break;
        }
        case fileOperateComponent.REUPLOAD : // file_open 打开文件
        {
          this.isRtcFile ?  this.send_rtcFile() : this.send_File()
          break;
        }
        case fileOperateComponent.REDOWN : {
          this.isFileAnotherSave ? this.saveAs(true) : this.downLoad();
          break;
        }
        case fileOperateComponent.RTCTIP : {
          opt === 1 ? this.send_File() : this.send_rtcFile()
          break;
        }
      }
    }
  },
  components: { 
    [FileOperate.name]: FileOperate
    // fileOperate: {
    //   template: "<div class='file-operate'><span class='file-operate-btn' v-if='addOpeate' @click='fileOpera(2)' v-text='addOpeateName'></span><span class='file-operate-btn' @click='fileOpera(1)' v-text='normalOperat'></span></div>",
    //   methods: {
    //     fileOpera(op) { this.$emit('receiveEvent', op) }
    //   },
    //   computed: {
    //     ...mapGetters(['chat_chatDicValue']),
    //     normalOperat() {
    //       if (this.operateComponent === fileOperateComponent.DOWNLOAD) {
    //           this.addOpeate = true;
    //           this.addOpeateName = this.$t('chat.download')
    //          return this.$t('chat.saveAs')
    //       } else if (this.operateComponent === fileOperateComponent.OPEN) {
    //         this.addOpeate = true;
    //         this.addOpeateName = ''
    //         console.log(this.chat_chatDicValue, FILE_DICVALUE)
    //         if (!this.chat_chatDicValue[FILE_DICVALUE]) { // 服务器不支持则默认允许另存为
    //         this.addOpeateName = this.$t('chat.open')
    //         } else if (this.chat_chatDicValue[FILE_DICVALUE] === '1') { // 服务器支持，则获取后台配置是否允许另存为
    //           this.addOpeateName = this.$t('chat.open')
    //         }
    //         return this.$t('chat.openFileLocation')
    //       } else if (this.operateComponent === fileOperateComponent.REDOWN) {
    //          this.addOpeate = false;
    //          this.addOpeateName = ''
    //          return this.$t('chat.download')
    //       } else if (this.operateComponent === fileOperateComponent.REUPLOAD) {
    //          this.addOpeate = false;
    //          this.addOpeateName = ''
    //          return this.$t('chat.reUpload') 
    //       } else if (this.operateComponent === fileOperateComponent.RTCTIP) {
    //          this.addOpeate = true;
    //          this.addOpeateName = this.$t('chat.resend')
    //          return this.$t('chat.sendOffline')
    //       }
    //     }
    //   },
    //   data() {
    //     return {
    //       addOpeate: false,
    //       addOpeateName: ''
    //     }
    //   },
    //   props: {
    //     rtcErrorTip: String,
    //     operateComponent: Number,
    //     isEcrypted: Boolean
        
    //   }  
    // }
  },
  computed: {
    fileImg() {
      // 判断文件类型，使用对应的图片
      const fileName = this.message.messageObject.fileName
      const ext = fileName.substr(fileName.lastIndexOf('.') + 1)
      switch (ext) {
        case 'pdf':
        return (require('vrv-static/resources/images/message/pdf.png'))

        case 'txt': 
        return (require('vrv-static/resources/images/message/txt.png'))

        case 'xls': 
        case 'xlsx': 
        return (require('vrv-static/resources/images/message/execl.png'))

        case 'ppt': 
        case 'pptx': 
        return (require('vrv-static/resources/images/message/ppt.png'))

        case 'exe':
        return (require('vrv-static/resources/images/message/install.png'))

        case 'rar':
        case 'zip': 
        return (require('vrv-static/resources/images/message/package.png'))

        case 'doc':
        case 'docx': return (require('vrv-static/resources/images/message/word.png'))
        default: return (require('vrv-static/resources/images/message/unknown.png'))
      }
    },
    filesizeCompute() {
      /** 计算文件大小 */
      this.file_size = this.message.messageObject.size ? this.message.messageObject.size : this.$Service.file.fileOperate( {filepath: this.message.messageObject.url, type:4} )

       let unitArr = new Array("B","KB","MB","GB","TB","PB","EB","ZB","YB")
       let index = 0
       let srcsize = parseFloat(this.file_size)
       index =  Math.floor(Math.log(srcsize)/Math.log(1024))
       let size = srcsize/Math.pow(1024, index)
       size = size.toFixed(1)
       return size + unitArr[index]
    },
    ...mapGetters(['user_filePath', 'user_account', 'chat_P2P_file_state'])
  }
}
</script>
<style lang="scss">
.type-file{
  padding: 1px;
  flex-direction: column;
}
.file-operate{
  flex: 1;
  display: flex;
  justify-content: flex-end;
  align-items: center;
  font-size: $--font-size-small;
  color:get-blue-color(darken-4);
  padding-right: 12px;
  height: 30px;
  .file-operate-btn{
    margin-right: 4px;
    &:hover {
    cursor: pointer;
    }
  }
}
.file-area {
  width: 250px;
  height: 60px;
  display: flex;
  padding: 7px;
  margin: 2px;
  background: #fff;
  border-radius: 15px 15px 0 0;
  .file-left {
    width: 50px;
    margin-right: 10px;
  }
  .file-right {
    flex: 1;
    display: flex;
    flex-direction: column;
    font-size: $--font-size-small;
    color: #000;
    position: relative;
    .cancel-opera {
          font-size: 14px;
    }
    .file-extra-info{
      flex: 1;
      display: flex;
      align-items: center;
    }
    .file-extension {
      font-size: 10px;
      margin-left: 10px;
    }
    .file-readonly {
      background: #006efe;
      position: absolute;
      width: 34px;
      height: 17px;
      color: #fff;
      right: -12px;
      top: 0px;
      padding-left: 3px;
      &:before {
        content: "";
        display: inline-block;
        position: absolute;
        border: 7px solid transparent;
        border-right-width: 6px;
        border-left-width: 2px;
        right: -8px;
        top: 0;
        border-top-color: #006efe;
        border-left-color: #006efe;
      }
      &:after {
        content: "";
        display: inline-block;
        position: absolute;
        border: 7px solid transparent;
        border-right-width: 6px;
        border-left-width: 2px;
        right: -8px;
        top: 3px;
        border-bottom-color: #006efe;
        border-left-color: #006efe;
      }
    }


    .file-names {
      max-width: 142px;
      @include ellipsis;
    }
    .file-size {
      display: flex;
      justify-content: flex-start;
      align-items: center;
      font-size: 10px;
      line-height: 16px;
      color:get-grey-color(base);
    }
    .file-tip {
      position: relative;
      flex: 1;
      display: flex;
      align-items: center;
      .spinner{
        width: 130px;
        top:22%!important;
      }
      .bounce1,  .bounce2, .bounce3 {
        width: 4px;
        height: 4px;
      }
    }

    .file-process {
      height: 11px;
      line-height: 11px;
      display: flex;
      align-items: center;
      .process-box {
        height: 3px;
        width: 136px;
        background: get-grey-color(lighten-1);
        margin-right: 10px;
        display: flex;
        span {
          width: 0px;
          height: 2px;
          background: #78c06d;
          // z-index
          // @include z-index(btn);
        }
      }
    }


  }

  .msg-state {
    width: 20px;
    align-self: center;
    color: $--color-msg-prompt-danger;
    display: flex;
    align-items: center;
    position: absolute;
    left: -20px;
    top: 35px;
  }
}
.file-operate-area {
  position: relative;
  .file-transmiss-info {
    // position: absolute;
    // position: absolute;
    // left: 84px;
    // top: 9px;
    position: absolute;
    font-size: 11px;
    width: 100%;
    height: 100%;
    display: flex;
    // justify-content: space-around;
    justify-content: flex-end;
    align-items: center;
    color: #000;
    .file-transmiss-time {
      margin: 0px 18px 0px 10px;
      color: $--color-msg-prompt-middle;
    }
  }
  height: 24px;
  display: flex;
  align-items: center;
  background: #fff;
  border-radius: 0 0 15px 15px;
  margin: 0px 2px 2px 2px;
}
</style>
