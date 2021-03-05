import { mapGetters } from 'vuex';
import { encryptionPassword, computeFileSize } from '../../../comm/util';
// import { toFileImg } from '../../../comm/images'
import { SubType } from  '../../../rtc/file/constant'
import {
  MsgImg,
  MsgFile,
  msgStructure,
  MsgWeak
} from './Msg';
import { insertNode } from './At/at.js'

const mixin = {
  data() {
    return {
      maxReadId: '',
      earseArray: [],
    }
  },
  computed: {
    ...mapGetters(['user_account', 'chat_rtc_file_list', 'chat_chatContent', 'chat_objectInfo', 'user_filePath', 'user_audioPath', 'chat_pendingMsg', 'contact_contactList', 'contact_hiddenContactIds', 'chat_rtc_file_size'])
  },
  methods: {
    /**
     * 判断是否主题议政群
     * @param {String} id 
     */
    isEidGroup(id,cb){
      this.$Service.group.getGroupInfo({
        groupId:id
      },resp => {
        console.log('isEidGroup',resp)
        cb(resp.info.groupType === 'eid');
      })
    },

    /**
     * 设置消息已读
     * @param {string} targetId 聊天对象Id
     * @param {string} msgId 0为全部设置
     */
    setMessageRead(targetId) {
      let setMessageReadParam = { targetId: targetId, msgId: '0' }
      this.$Service.chat.setMessageRead(setMessageReadParam)
    },

    /*
     *获取历史聊天消息
     *targetid 传入会话对应的ID，群或者人
     *msgid 传入查询消息的起始ID，将从该消息的下一条消息开始查询
     *count 传入查询消息总数
     *flag  传入上一页还是下一页 向上偏移 0；向下偏移 1
     *cb
     */
    getHistoryMsg(targetId, unreadCount, msgId = 0, isDown = false) {
      return new Promise(resolve => {
        if ([...this.contact_hiddenContactIds].includes(this.$route.query.id)) {
          this.$Service.log(`当前会话已被隐藏，不需要拉取历史记录:::${this.$route.query.id}`)
          resolve([])
          this.isPauseScroll = false
          this.isLoadHistoryMsg = false
          this.isShowLoad = false
          return
        }
        console.log('get historyMsg...')
        // 获取历史的条数
        let chatUnreadCount;
        if (isDown) {
          chatUnreadCount = unreadCount
        } else {
          chatUnreadCount = unreadCount ? unreadCount > 10 ? 10 : unreadCount : 5
        }
        console.log('chatUnreadCount', chatUnreadCount)

        // 获取历史消息传入的参数 targetId msgId count flag
        let msg = {
          targetId: targetId, // 传入会话对应的ID，群或者人
          msgId: msgId || 0, // 传入查询消息的起始ID，将从该消息的下一条消息开始查询
          count: chatUnreadCount, // 传入查询消息总数
          flag: 0 // 传入上一页还是下一页 向上偏移 0；向下偏移 1
        };
        // 获取历史消息回调
        let getMessagesCb = resp => {
          console.log('historyMsg::', resp);
          this.earseArray = []
          this.isShowLoad = false
          console.log('this.isLoadHistoryMsg', this.isLoadHistoryMsg)
          let historyMsg = Object.assign({}, resp)
          if (!historyMsg.msgs.length) {
            this.isPauseScroll = false
            this.isLoadHistoryMsg = false
            return
          } 
          this.$Service.log(`getHistoryMsg: ${historyMsg.targetId} :::  ${historyMsg.msgs[historyMsg.msgs.length - 1].msgId}`)
          console.log('historyMsg.msgs.length', historyMsg.msgs.length, chatUnreadCount)
          this.isLoadHistoryMsg = historyMsg.msgs.length >= chatUnreadCount;
          let obj = {};

          historyMsg.msgs.forEach(element => {
            let isMyMsg = element.fromId === this.user_account.id
            /**
             * 文件直传消息 需在下次拉取历史时转换为对应的文件消息
             */
            if (element.msgType === 15 && element.body !=='') {
              console.log('element.body',element.body)
              let msgBase = JSON.parse(element.body)
              if (msgBase.VideoType == 7) return
              if (element.comment !== "p2p_file") return
              element.fileName = msgBase.filename;

              element.filePath = msgBase.filepath;
              element.size = msgBase.filesize;
              element.msgType = 6;
              element.preDefined = JSON.stringify({RtcFile: true});
              if (msgBase.isOwner == 'false') {
                let fromId = element.fromId;
                element.fromId = element.targetId;
                element.targetId = fromId;
              }
            }

            if (element.msgType === 14 && element.videostatus=== 'file') {
              console.log('JSONfileMsg', element)
              let msgBase = JSON.parse(element.body)
              if (msgBase.subType === SubType.SEND ) {
                console.log('msgBase::', msgBase)

                element.fileName = msgBase.fileInfo.filename;
                element.filePath = msgBase.fileInfo.filePath;
                element.size = msgBase.fileInfo.size;
                element.msgType = 6;
                element.preDefined = JSON.stringify({RtcFile: true});
                console.log('element::', element)
                if (!msgBase.isdeal) {
                  if (new Date().getTime() - element.time < 300000) {
                    console.log('is time out', new Date().getTime() - element.time < 300000) 
                    element.preDefined = JSON.stringify({ RtcFile: true })
                    let msg = msgStructure(element);
                    this.$store.commit('SET_RTC_FILE', msg)
                    return
                  } else {
                    console.log('element', element)
                    element.msgType = 14;
                    element.isTimeOut = true
                  }
                } 
              }
            }
            
            // * 上层特殊 unReadCount === 0 && maxUnReadCount === 0 同步过来自己的消息为携带任何未读状态
            if (historyMsg.targetType === 2 && isMyMsg && (element.unReadCount > 0 || (element.unReadCount === 0 && element.maxUnReadCount ===0 ))) {
              this.$Service.log(`historyMsg has unReadCount   msgId::: ${element.msgId}`)
              if (!this.unreadArray) this.unreadArray = [];
              this.unreadArray.push({msgId:element.msgId, snapshotId: element.snapshotId})
              this.$Service.log(`unreadArray push success:::${element.msgId}`)
            }

          
            /** 个人情况下加载更多消息 
             *  减少调取接口 手动比较直接处理已读未读 
             *  避免过多渲染
             * */
            if (historyMsg.targetType === 1 && isMyMsg && !element.maxUnReadCount && msgId && this.userMaxReadId) {
              if (element.msgId < this.userMaxReadId) {
                console.log('element::', JSON.stringify(element))
                element.maxUnReadCount = 1
              }
            }

            this.$set(obj, `id_${element.msgId}`, msgStructure(element)) //构建不同的消息类型
          
            /**
             * 如果拉取的消息是未读消息 并且拉取的消息中存在撤回消息
             * 在撤回消息中找到要撤回的消息Id 过滤掉不显示
             * 之后异步 调取删除消息ID 删掉数据库中存在的要撤回的消息
             */
            if (chatUnreadCount && element.msgType === 18) {
              let delMsgId = element.revokeMsgId // 找到要删除的msgId
              if (obj[`id_${delMsgId}`]) {
                this.$delete (obj, `id_${delMsgId}`)
                this.delMsg(element.targetId, delMsgId) // 删除数据库中要撤回的消息
              }
            } 

            /** 存在发送失败的撤回消息 */
            if (element.msgType === 530 || element.msgType === 520) {
              this.$delete (obj, `id_${element.msgId}`)
              this.delMsg(element.targetId, element.msgId)
            }
            
            // * 删除阅后即焚的消息
            if (element.deviceType === 2 && element.activeType === 1 && element.fromId === this.user_account.userId) {
              this.$Service.log(`has own burn msg  ${element.msgId}`)
              this.$delete (obj, `id_${element.msgId}`)
              this.delMsg(element.targetId, element.msgId) // 删除数据库中要撤回的消息
            }

            this.isEarseMsg(element, obj) // 处理橡皮擦消息 

          });


          let msgObject = {
            targetId: historyMsg.targetId,
            msgs: obj,
            isHistory: true
          }
          this.$store.commit('ADD_CHATCONTENT', {message: msgObject, isDown: isDown})
          if (!msgId) {
            this.reduceSession()
          }
          resolve(historyMsg.msgs)
        };
        this.$Service.chat.getMessages(msg, getMessagesCb);
      })
    },

    /**
     * 删除消息
     * @param {string} targetId 传入会话对应的ID，群或者人
     * @param {string} msgId 传入要删除的消息ID集合
     */
    delMsg(targetId, msgId) {
      let deleteMessageByIdParam = {
          targetId: targetId, // 传入会话对应的ID，群或者人 this.selectActive.targetId
          msgIds: [msgId] // 传入要删除的消息ID集合 msgs为空，清空对应targetId的所有消息 this.selectActive.msgId
      };
      let deleteMessageByIdCb = deleteCb => {
        if (deleteCb.code === 0) this.$store.commit('DEL_MESSAGE', {targetId:targetId, msgId : msgId})
      };
      this.$Service.chat.deleteMessageById(deleteMessageByIdParam, deleteMessageByIdCb);
    },

    /**
     * sendImg 发送图片消息
     *  @param {string} name 图片名称 
     *  @param {string} path 图片路径
     *  @param {string} time 发送多图经常会相同造成key紊乱 
     **/
    sendImg(name, path) {
      let msgbase = {
        fromId: this.user_account.userId,
        targetId: this.$route.query.id,
        fileName: decodeURI(name),
        mainPath: decodeURI(path),
        isPrivateMsg: this.isEncryptMsg ? 1 : 0,
        encryptKey: encryptionPassword().toString(),
        activeType: this.isBurn ? 1 : 0,
        msgId: encryptionPassword().toString()
      };
      let msgImg = new MsgImg(msgbase, 1);
      this.$store.dispatch('SET_CHATCONTENT', msgImg);
    },

    /**
     * uploadFile 发送文件消息
     *  @param {string} name 文件名称 
     *  @param {string} path 文件路径
     *  @param {string} size 文件大小 
     **/
    uploadFile(name, path, size, isP2PFile = false) {
      let msgbase = {
        fromId: this.user_account.userId,
        targetId: this.$route.query.id,
        fileName: decodeURI(name),
        filePath: decodeURI(path),
        isPrivateMsg: this.isEncryptMsg ? 1 : 0,
        encryptKey: !isP2PFile ? encryptionPassword().toString() : '',
        size: parseInt(size),
        msgId: encryptionPassword(),
        preDefined: this.chatType === 1 && isP2PFile ? JSON.stringify({ RtcFile: true }) : ''
      };
      let msgFile = new MsgFile(msgbase, 1);
      console.log('msgFile:::', msgFile)
      isP2PFile && this.chatType === 1 ? this.$store.commit('SET_RTC_FILE', msgFile) : this.$store.dispatch('SET_CHATCONTENT', msgFile)
    },


    /**
     * 文件上传
     * @param {event} evt 
     * @param {Object} file 
     */
    upload(evt, file) {
      console.log('evt.target', evt)
      console.log('file', file)
      let fileInfo = file || evt.target.files[0]; // 获取文件或者图片的信息
      let fileType = fileInfo.path.substr(fileInfo.path.lastIndexOf('.') + 1)
      console.log('fileInfo:', fileInfo,'fileType:',fileType)
      this.$fs.stat(fileInfo.path, (err,stat) => {
        if (err) {
          console.error(err);
          throw err;
        }
        // * 检测是否为空文件 
        if (!fileInfo.size) {
          // return this.showDialogeTip('不能发送空文件')
          return this.showDialogeTip(this.$t('chat.emptyFiles'))
        }

        if (stat.isDirectory()) {
          return this.showDialogeTip('不能发送文件夹')
        }
        /**
         * 判断是否为直传文件
         * 直传文件同一会话最多发送5个文件
         * 直传文件最多发送两个人
         */
        let isP2PFile = false  // 文件大小为0默认正常文件发送
        if (this.chat_rtc_file_size !== 0) {
          isP2PFile = fileInfo.size >= this.chat_rtc_file_size * 1024 * 1024;
        }
        if (isP2PFile) {
          let p2pFile = this.chat_rtc_file_list
          if (this.chatType === 1 && p2pFile && !p2pFile[this.$route.query.id] && Object.keys(p2pFile).length > 1) {
            return this.showDialogeTip(this.$t('chat.directFileLimit'))
          }

          if (p2pFile[this.$route.query.id] && Object.keys(p2pFile[this.$route.query.id]).length > 4) {
            // return this.showDialogeTip('同一会话最多发送5个直传文件')
            return this.showDialogeTip(this.$t('chat.maxDirectCount'))
          }
        } 

        // * 延时消息只支持文本消息 
        if (this.isDelay) {
          evt && evt.type === 'drop' ? this.isDelay = false : this.$emit('updateDelayMsg', false)  
          this.$toast.open({duration: 3000, message: this.$t('chat.delayFileTip'), position: 'is-top', type: 'is-warning'});
        }

        // * 拖拽上传 直接发送文件 
        if (evt && evt.type === 'drop') {
          if (this.isBurn) {
            this.$toast.open({duration: 3000, message: this.$t('chat.burnFileTip'), position: 'is-top', type: 'is-warning'});
          }

          this.uploadFile(fileInfo.name, fileInfo.path, fileInfo.size, isP2PFile)
          evt.target.value = ''
          return evt.target.value;
        }

        let isImg = fileType.match(/jpg|jpeg|png|JPG|PNG|gif|GIF/g)
        if (isImg) {
          let source = '<img class="edit-image" type="img" alt="img" title="' + fileInfo.name + '" src="' + fileInfo.path + '">'
          insertNode(this.$refs.editArea, source)
          setTimeout(() => { // 处理编辑框内图片监听查看大图
            this.handleClickEditImg(fileInfo.name)
          }) 	
        } else { // 文件消息
          if (this.isBurn) { 
            this.$toast.open({duration: 3000, message: this.$t('chat.burnFileTip'), position: 'is-top', type: 'is-warning'}); 
          }
          if(this.$is.isWinXp){
              //获取图标
              var cv =document.getElementById('cv')
              let name = fileInfo.name.length < 14 ? fileInfo.name : `${fileInfo.name.slice(0, 14)}...`
              let size = computeFileSize(fileInfo.size)
              let icon = this.$Service.file.getFileIcon({'filepath':fileInfo.path})
              this.$images.toFileImg(cv, icon,  name, size).then(imgUrl => {
                let source = '<img class="edit-file-image" type="file" alt="img" title="' + fileInfo.name + '"  path="'+fileInfo.path + '" isP2PFile="'+ isP2PFile + '" size="'+fileInfo.size + '" src="' + imgUrl + '">'
                insertNode(this.$refs.editArea, source);
                this.$fs.unlinkSync(icon);
              })
          }
          else{
              this.$getFileIcon(fileInfo.path, icon => {
                var cv =document.getElementById('cv')
                let name = fileInfo.name.length < 14 ? fileInfo.name : `${fileInfo.name.slice(0, 14)}...`
                let size = computeFileSize(fileInfo.size)
                this.$images.toFileImg(cv, icon,  name, size).then(imgUrl => {
                  let source = '<img class="edit-file-image" type="file" alt="img" title="' + fileInfo.name + '"  path="'+fileInfo.path + '" isP2PFile="'+ isP2PFile + '" size="'+fileInfo.size + '" src="' + imgUrl + '">'
                  insertNode(this.$refs.editArea, source)
                })
              })
         }
        }
        if(evt) {
          evt.target.value = ''
          return evt.target.value;
        }
      })
    },
    setMsgFromMainProcess(msg) {
      let templateMsg = msgStructure(msg)
      templateMsg.messageObject.isNeedHandleUnread = true
      this.$store.commit('SET_CHATCONTENT', templateMsg);
    },

    showDialogeTip(msg) {
      this.$dialog.alert({
        message: msg,
        onfirmText: '确认',
        onConfirm: () => {}
      });
    }, 


    // * 减少会话缓存
    reduceSession() {
      if (Object.keys(this.chat_chatContent).length < 10) return
        for (let i in this.chat_chatContent) {
          let isTransmittingInTarget = this.$Service.file.isTransmittingInTarget({targetId: i})
          if (!this.chat_rtc_file_list[i] && !isTransmittingInTarget && i!== this.$route.query.id) {
            this.$store.commit('DEL_CHATCONTENT_BYID', i)
            this.$store.commit('DEL_CHAT_OBJECT', i)
            return 
          }
      }
    },

    // * 更新已打开会话 自己的头像
    updateSessionUserHeadImg(headImg, isfocus=false) { 
      if (!isfocus && headImg === this.user_account.thumbAvatar) return
      let fileOperateParam = {
        filepath: headImg,
        type: 0
      }
      if (!this.$Service.file.fileOperate(fileOperateParam)) {
        return
      }
      console.log('updateSessionUserHeadImg:::::')
      for (let i in this.chat_chatContent) {
        this.$Service.log(`updateSessionUserHeadImg::: id>>>>>  ${i}`)
        let type = this.$Service.config.getUserTypeById({ targetId:  i })
        console.log('type::', type)
        if (type === 1) {
          this.$store.commit('UPDATE_MEMBER_AVATAR', {id:i, avatar: headImg, userId: this.user_account.userId})
        }
      }
    },
    
    // * 删除文件缓存
    delFileCache() {
      setTimeout(() => {
        let delFiles = this.$Service.file.fileOperate({ filepath: `${this.user_filePath}cache`, type: 2 });
      });
    },

    // * 是否是橡皮擦消息
    isEarseMsg(element, historyMsg) {
      try {
        if (element.msgType === 2 && element.body.includes('&:delete|')) {
          this.earseArray.push(element)
          if (this.earseArray.length && this.earseArray.length > 1) {
            for (let i = 0; i <= this.earseArray.length - 2; i++ ) {
              historyMsg[`id_${this.earseArray[i].msgId}`].messageObject.deal = true
              this.$Service.chat.updateMsg(historyMsg[`id_${this.earseArray[i].msgId}`].messageObject, resp => {
                console.log('updateMsg::', resp)
              })
            }
          }
        }
      } catch (error) {
        console.log('isEarseMsg', error)
      }
    },

    /**
     * handleReceiptWeak 处理绘制弱提示
     * @param {*} tipType 4 阅后回执 5 橡皮擦  
     * @param {*} operType 1 同意 2 拒绝
     * @param {*} isStore  1 存储数据库 0 不存储数据库  
     */
    handleReceiptWeak(receipt) {
      let weakObj = {
        tipType : receipt.tipType,
        operType: receipt.operType,
        fromId: this.user_account.userId,
        targetId: this.id,
        msgId: encryptionPassword(),
        userInfo: receipt.userInfo||'',
        operUser: receipt.operUser||'',
        noStore: receipt.isStore || 0,
        relatedUsers:receipt.relatedUsers|| [],
        limitRange: receipt.limitRange || [],
        tipTime:  receipt.tipTime || '',
        fileInfo: receipt.fileInfo || '',
        body: receipt.body || ''
      }
      let msgWeak = new MsgWeak(weakObj);
      console.log('msgWeak', msgWeak)
      this.$Service.chat.sendMessage(msgWeak.messageObject, resp => {
        console.log('msgWeak:::', msgWeak)
        this.$Service.log(`sendWeak code:::${resp.code}`)
        if (resp.code === 0 && !weakObj.noStore) {
          msgWeak.messageObject.msgId = resp.msgId
          msgWeak.messageObject.time = resp.time
          this.$store.dispatch('SET_CHATCONTENT', msgWeak)
        }
      })  
    },

    // * 更行消息deal 字段
    updateMsgDeal(msg) {
      console.log('msg', msg)
      let updateMsg = Object.assign({}, msg)
      updateMsg.deal = true
      this.$Service.chat.updateMsg(updateMsg, resp => {
        console.log('updateMsg::', resp)

      })
    },

    delMsgFromDay(id, time) {
      return new Promise((resolve) => {
        let date =  new Date(parseInt(time)).toLocaleDateString().split('/')
        let getMsgFromDay = {
          targetId: id, 
          belately: 1,
          count: 0,
          msgId: '0',
          year: parseInt(date[0]),
          month: parseInt(date[1]),
          day:parseInt(date[2])
        }
        console.log('getMsgFromDay:::', getMsgFromDay)
        this.$Service.chat.getMsgFromDay(getMsgFromDay, resp => {
          console.log('getMsgFromDay', resp)
          let deletMsgArray = []
          resp.msgs.forEach(e => {
            deletMsgArray.push(e.msgId)
            if (this.chat_chatContent[id])
              this.$store.commit('DEL_MESSAGE', {targetId:id, msgId : e.msgId})
          })
          let deleteMessageByIdParam = {
            targetId: id, // 传入会话对应的ID，群或者人 this.selectActive.targetId
            msgIds: deletMsgArray // 传入要删除的消息ID集合 msgs为空，清空对应targetId的所有消息 this.selectActive.msgId
          };
          console.log('deleteMessageByIdParam:::', deleteMessageByIdParam)
          let deleteMessageByIdCb = deleteCb => {
            this.$Service.log(`deleteMessageByIdCb code:::${deleteCb.code}`)
            console.log('deleteCb', deleteCb)
            resolve()
            // this.handleWeak(1)
            // * tipType 5 橡皮擦 operType 操作类型 1 同意 isStore 1 不储存 0 储存
            // this.handleReceiptWeak({tipType: 5, operType: 1, isStore:1,  operUser: this.user_account.name,  userInfo:userName, limitRange: [msg.msgObj.fromId]}) 
          };
          this.$Service.chat.deleteMessageById(deleteMessageByIdParam, deleteMessageByIdCb);
        })
      })
    },

    // * 通过消息Id 删除消息
    deleteMessageById(deleteId) {
      return new Promise(resolve => {
        let deleteMsgObj = {
          targetId: deleteId,
          endTime: '0',
          beginTime: new Date().getTime().toString()
        }  
        this.$Service.chat.deleteMessageByTime(deleteMsgObj, resp => {
          console.log('deleteMessageByTime', resp)
          if (resp.code === 0) {
            this.$Service.log(`deleteMessageById:::    deleteId: ${deleteId}`)
            if (this.chat_chatContent[deleteId]) {
              this.chat_chatContent[deleteId] = {}
              resolve()
            }
          }
        })
      })
    },

   openBuddyMeeting(roomID,displayName,userID,startTime,members, serverUrl, serverPort) {
      let templateStatic="vrv-static/plugins";
      const mediadood=templateStatic+"/mediadood/index.html";
      let url=`${mediadood}?roomId=${roomID}&serverUrl=${serverUrl}&serverPort=${serverPort}&displayName=${displayName}&userID=${userID}&startTime=${startTime}&members=${members}`;
      let winType="mediadood";
      let winTitle=this.$t("chat.douShipin");
      console.log("openDoodMeeting::url:",url);
      return this.$ipc.send("new-window",{
        winUrl: url,
        winType: winType,
        winTitle: winTitle,
        shapeType: "normal"
      });
    }
  }
};
export default mixin;