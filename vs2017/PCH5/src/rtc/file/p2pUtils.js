import {
    Rtcfile
  } from './rtcfile';
  import {
    RtcStatus,
    SubType,
    FileStatus,
  } from './constant'
  // src/renderer/components/Chat/Msg.js
  import {
    MsgWeak
  } from '../../renderer/components/Chat/Msg'
  const {
    clipboard,
    remote
  } = require('electron');
  const Service = remote.getGlobal('service')
  import Logger from '../Logger';
  const logger = new Logger('p2pUtils');
  // const Service = window.requestAnimationFrame
  // let rtc;
  // // let rtcplugin_;
  // let _rtcCallback_ = null;
  // // let _fileCallback_ = null;
  // let _rtcStatus = RtcStatus.NORMAL;
  // let _fileCallbackMap = new Map();
  
  export class p2pUtils {
    constructor() {
  
      this.rtc = new Rtcfile(this._rtcCallback.bind(this), this._fileCallback.bind(this));
      this._rtcStatus = RtcStatus.NORMAL;
      this._fileStatus = FileStatus.NORMAL;
  
      this._fileCallbackMap = new Map(); // 文件状态回调
  
      this._waitSendFileMap = new Map(); // 等待发送列表
      this._waitReceiveFileMap = new Map(); // 等待接收列表
      this.currTargetId = null;
      this.userId = null;
    }
  
    /**
     * 注册 rtc 通道状态
     * @param {*} rtcCallback 
     */
    regRtcCallback(rtcCallback) {
      logger.debug('regRtcCallback');
      this._rtcCallback_ = rtcCallback;
    }
  
    // /**
    //  * 注册 文件状态
    //  * @param {*} fileCallback 
    //  */
    // regFileCallback(fileCallback) {
    //   _fileCallback_ = fileCallback;
    // }
  
    _rtcCallback(res) {
      logger.file('_rtcCallback==> ', res);
      this._rtcStatus = res;
      if (this._rtcCallback_) {
        this._rtcCallback_(res);
      }
      if (res === RtcStatus.DISCONNECT) {
        this._autoSendNextFile();
      }
    }
  
    _autoSendNextFile() {
      logger.debug('_autoSendNextFile');
      if (this._waitSendFileMap.size > 0) {
        this._waitSendFileMap.forEach((v, k) => {
          this.currTargetId = k;
          for (let i = 0; i < v.length; i++) {
            const { targetId, fromId, fileInfo, fileCallback, msgCallback, timeout } = v[i];
            this._sendFile(targetId, fromId, fileInfo, fileCallback, msgCallback, timeout);
          }
          this._waitSendFileMap.delete(k);
          return;
        });
      }
    }
  
    _fileCallback(fileInfo, res) {
      logger.debug('_fileCallback==> ', fileInfo, res);
      this._fileStatus = res;
      if (res === FileStatus.TIMEOUT) {
        this._sendPromptMsg(this.currTargetId, this.userId, SubType.TIMEOUT, fileInfo, res => { });
      }
      if (this._fileCallbackMap && fileInfo) {
        let callback = this._fileCallbackMap.get(fileInfo.fileId);
        if (callback) {
          callback(res);
        }
      }
    }
  
    /**
     * 发送p2p文件消息
     * @param {*} targetId  目标id
     * @param {*} fromId    自己id
     * @param {*} filePath  文件路径
     * @param {*} fileCallback 文件进度回调
     * @param {*} msgCallback 文件发送回调
     * @param {*} timeout   超时时间  默认 20分钟 用法：当消息发送后20分钟不允许操作
     */
    sendFile(targetId, fromId, filePath, fileCallback, msgCallback, timeout = 5 * 60 * 1000) { // targetId fromId filePath timeout
      logger.debug('sendFile', targetId, fromId, filePath)
      this.userId = fromId;
      let fileInfo = this.rtc._SenderGetFileinfo(filePath);
      if (!fileInfo) {
        logger.fileError('sendFile','文件打开失败');
        return
      }
      fileInfo.filePath = filePath;
      fileInfo.isSender = true;
      fileInfo.timeout = timeout;
      fileInfo.sendTime = new Date().getTime();
      if (fileCallback) {
        this._fileCallbackMap.set(fileInfo.fileId, fileCallback)
      }
      console.log("zxj::sendFile====>",this.currTargetId , targetId , this.rtc._getSendFileList().length );
      if (this.currTargetId && this.currTargetId !== targetId && this.rtc._getSendFileList().length > 0) {
        this._addWaitSendFile(targetId, fromId, fileInfo, fileCallback, msgCallback, timeout);
      } else {
        this.currTargetId = targetId;
        this._sendFile(targetId, fromId, fileInfo, fileCallback, msgCallback, timeout);
      }
    }
  
    _sendFile(targetId, fromId, fileInfo, fileCallback, msgCallback, timeout) { // targetId fromId filePath timeout
      logger.debug('_sendFile', targetId, fromId, fileInfo)
      let msgbody = {
        'VideoStatus': 'file',
        'subType': SubType.SEND, // p2pfile
        'fileInfo': fileInfo,
        'timeout': timeout // 默认超时时间 20分钟
      }
      let msgbase = {
        fromId: fromId,
        targetId: targetId,
        body: JSON.stringify(msgbody),
        time: new Date().getTime().toString(),
        localId: new Date().getTime().toString(),
        deviceType: 1,
        msgType: 14,
        isOri: true
      };
      this._sendMessage(msgbase, resp => {
        resp.body = msgbase.body;
        let resData = Object.assign({}, fileInfo)
        resData.msgId = resp.msgId
        resData.code = resp.code
        logger.debug('resData', resData)
  
        fileInfo.msgId = resp.msgId;
        this.rtc._addSendFile(fileInfo);
        msgCallback(resData);
      });
    }
  
    _addWaitSendFile(targetId, fromId, fileInfo, fileCallback, msgCallback, timeout = 5 * 60 * 1000) {
      logger.debug('_addWaitSendFile', targetId, fromId, fileInfo);
      let array = this._waitSendFileMap.get(targetId) || [];
      array.push({
        targetId,
        fromId,
        fileInfo,
        fileCallback,
        msgCallback,
        timeout
      });
      this._waitSendFileMap.set(targetId, array);
      let resData = Object.assign({}, fileInfo)
      resData.msgId = new Date().getTime().toString();
      resData.code = -3;
      logger.debug('resData', resData)
      msgCallback(resData);
    }
  
    getWaitSendFileList(targetId) {
      logger.debug('getWaitSendFileList', targetId);
      return this._waitSendFileMap.get(targetId) || [];
    }
  
    removeWaitSendFile(targetId, fileId) {
      logger.debug('removeWaitSendFile', targetId, fileId);
      if (this._waitSendFileMap.has(targetId)) {
        let array = this._waitSendFileMap.get(targetId) || [];
        for (let i = 0; i < array.length; i++) {
          const file = array[i];
          if (fileId === file.fileId) {
            array.splice(i, 1);
            if (array.length === 0) {
              this._waitSendFileMap.delete(targetId);
            }
          }
        }
      }
    }
  
    /**
     * 添加 待显示的 接收文件列表
     * @param {*} targetId 
     * @param {*} fromId 
     * @param {*} fileInfo 
     */
    addWaitReceiceFile(targetId, fromId, fileInfo) {
      logger.debug('addWaitReceiceFile', targetId, fromId, fileInfo);
      let array = this._waitReceiveFileMap.get(targetId) || [];
      array.push({
        targetId,
        fromId,
        fileInfo
      });
      this._waitReceiveFileMap.set(targetId, array);
    }
  
    removeWaitReceiceFile(targetId, fileId) {
      logger.debug('removeWaitReceiceFile', targetId, fileId);
      if (this._waitReceiveFileMap.has(targetId)) {
        let array = this._waitReceiveFileMap.get(targetId) || [];
        for (let i = 0; i < array.length; i++) {
          const file = array[i];
          if (fileId === file.fileId) {
            array.splice(i, 1);
            if (array.length === 0) {
              this._waitReceiveFileMap.delete(targetId);
            }
          }
        }
      }
    }
  
    /**
     * 获取 待显示的 接收文件列表,并删除 获取的值
     * @param {*} targetId 
     */
    getWaitReceiveFileList() {
      logger.debug('getWaitReceiveFileList');
      let array = [];
      this._waitReceiveFileMap.forEach((v, k) => {
        array = v || [];
        this._waitReceiveFileMap.delete(k);
        return
      });
      return array;
    }
  
    /**
     * 接收或拒绝文件
     * @param {*} userId    自己id
     * @param {*} targetId  对方id
     * @param {*} fileInfo  文件信息
     * @param {*} isAccept  是否接收
     * @param {*} savePath  保存路径
     * @param {*} fileCallback 文件进度回调
     */
    // acceptOrReject(targetId, userId, fileInfo, isAccept, savePath, fileCallback, msgCallback) { // fileID  operate
    //   logger.debug('acceptOrReject', userId, targetId, JSON.stringify(fileInfo), isAccept, savePath, this._rtcStatus)
    //   if (isAccept) {
    //     // _fileCallback_ = fileCallback;
    //     if (fileCallback) {
    //       this._fileCallbackMap.set(fileInfo.fileId, fileCallback)
    //     }
    //     fileInfo.filePath = savePath + fileInfo.filename;
    //     fileInfo.isSender = false;
    //     this.rtc._addReceiveFile(fileInfo);
    //     if (this._rtcStatus == RtcStatus.NORMAL || this._rtcStatus == RtcStatus.DISCONNECT || this._rtcStatus == RtcStatus.CANCEL) {
    //       this._rtcStatus = RtcStatus.BEGIN;
    //       this.rtc._createOffer(targetId);
    //     }
    //     // this.rtc._AcceptFile(fileInfo);
    //   } else {
    //     this._sendPromptMsg(targetId, userId, SubType.REFUSE, fileInfo, msgCallback); //userId, targetId, type, msgId, fileInfo, msgCallback
    //   }
    // }
  
    acceptOrReject(targetId, userId, fileInfo, isAccept, savePath, fileCallback, msgCallback, refuseType = SubType.REFUSE) { // fileID  operate
      logger.debug('acceptOrReject', userId, targetId, JSON.stringify(fileInfo), isAccept, savePath, this._rtcStatus)
      if (isAccept) {
        // _fileCallback_ = fileCallback;
        if (fileCallback) {
          this._fileCallbackMap.set(fileInfo.fileId, fileCallback)
        }
        fileInfo.filePath = savePath + fileInfo.filename;
        fileInfo.isSender = false;
        this.rtc._addReceiveFile(fileInfo);
        if (this._rtcStatus == RtcStatus.NORMAL || this._rtcStatus == RtcStatus.DISCONNECT || this._rtcStatus == RtcStatus.CANCEL || this._rtcStatus == RtcStatus.ERROR) {
          this._rtcStatus = RtcStatus.BEGIN;
          this.rtc._createOffer(targetId);
        }
        // this.rtc._AcceptFile(fileInfo);
      } else {
        fileCallback(FileStatus.CANCEL);
        this._sendPromptMsg(targetId, userId, refuseType, fileInfo, msgCallback); //userId, targetId, type, msgId, fileInfo, msgCallback
      }
    }
  
    /**
     * 取消发送 [传输中，发送方或接收方取消] 当批量关闭时，循环调用
     * @param {*} fileId  文件id
     */
    cancel(targetId, userId, isSender, fileInfo, msgCallback) { // fileID 
      logger.debug('cancel', targetId, userId, fileInfo, this._waitSendFileMap)
      if (this.rtc._Cancel(fileInfo.fileId) === -1) {
        if (fileInfo.isSender) {
          this._fileCallback(fileInfo, FileStatus.CANCEL);
          if(this._waitSendFileMap.has(targetId)){
            this.removeWaitSendFile(targetId, fileInfo.fileId);
          }else{
            this.rtc._removeSendFile(-1, fileInfo.fileId);
            this.rtc._removeReceiveFile(-1, fileInfo.fileId);
          }
          this._sendPromptMsg(targetId, userId, SubType.CANCEL_SENDER, fileInfo, msgCallback);
        } else {
          // this.removeWaitReceiceFile(targetId,fileInfo.fileId);
          this._fileCallback(fileInfo, FileStatus.CANCEL);
          this.rtc._removeReceiveFile(-1, fileInfo.fileId);
          this._sendPromptMsg(targetId, userId, SubType.CANCEL_RECEIVER, fileInfo, msgCallback);
        }
      } else { // 单纯弱提示，不需要上层处理
        if (fileInfo.isSender) {
          // this.removeWaitSendFile(targetId,fileInfo.fileId);
          this.rtc._removeSendFile(-1, fileInfo.fileId);
          this._sendPromptMsg(targetId, userId, SubType.CANCEL_SENDER, fileInfo, msgCallback);
        } else {
          // this.removeWaitReceiceFile(targetId,fileInfo.fileId);
          this._sendPromptMsg(targetId, userId, SubType.CANCEL_RECEIVER, fileInfo, msgCallback);
        }
      }
      this._fileCallbackMap.delete(fileInfo.fileId);
    
      if (this.rtc._getReceiveFileList().length === 0 && this.rtc._getSendFileList().length === 0) {
        this.close();
        // this._autoSendNextFile();
      }
    }
  
    // cancelAll(targetId, userId, isSender, msgCallback) {
    //   logger.debug('cancelAll', targetId, userId, isSender, msgCallback);
    //   let array;
    //   if (isSender) {
    //     if (this._waitSendFileMap.has(targetId)) {
    //       array = this.getWaitSendFileList(targetId);
    //       this._waitSendFileMap.delete(targetId);
    //     } else {
    //       array = this.rtc._getSendFileList();
    //       // this.rtc._setSendFileList([]);
    //       this.close();
    //     }
    //   } else {
    //     array = this.getWaitReceiveFileList(targetId);
    //     this._waitReceiveFileMap.delete(targetId);
    //     this.close();
    //   }
    //   array.forEach(fileInfo => {
    //     this.cancel(targetId, userId, isSender, fileInfo, msgCallback);
    //   });
    // }
  
    /**
     * 响应取消
     * @param {*} isSender 是否发送方
     * @param {*} fileInfo 文件信息
     */
    responseCancel(targetId, isSender, fileInfo) {
      logger.debug('responseCancel', targetId, fileInfo);
      this._fileCallback(fileInfo, FileStatus.CANCEL);
      if (fileInfo.isSender) {
        // if (this._waitSendFileMap.has(targetId)) { // 处理取消，发送方 应该不会出现
        //   this.removeWaitSendFile(targetId, fileInfo.fileId);
        // } else {
        this.rtc._removeSendFile(-1, fileInfo.fileId);
        this.rtc._removeReceiveFile(-1, fileInfo.fileId);
        // }
      } else {
        if (this._waitReceiveFileMap.has(targetId)) {
          this.removeWaitReceiceFile(targetId, fileInfo.fileId);
        } else {
          this.rtc._removeReceiveFile(-1, fileInfo.fileId);
        }
      }
      this._fileCallbackMap.delete(fileInfo.fileId);
      if (this.rtc._getReceiveFileList().length === 0) { // 传输的文件 == 0 
        this.rtc.Close();
        // this._fileCallbackMap.clear();
      }
    }
  
  
  
  
    /**
     * 发送或接收成功后调用 向对方发送弱提示
     * @param {*} targetId 
     * @param {*} userId 
     * @param {*} isSender 
     * @param {*} fileInfo 
     * @param {*} msgCallback 
     */
    success(targetId, userId, isSender, fileInfo, msgCallback) {
      logger.debug('success', targetId, userId, fileInfo);
      this._fileCallbackMap.delete(fileInfo.fileId);
      if (fileInfo.isSender) {
        // this.removeWaitSendFile(targetId,fileInfo.fileId);
      } else {
        // this.removeWaitReceiceFile(targetId,fileInfo.fileId);
        this._sendPromptMsg(targetId, userId, fileInfo.isSender ? SubType.SUCCESS_SEND : SubType.SUCCESS_RECEIVE, fileInfo, msgCallback);
      }
      // this.addDiscMsg(targetId, userId, isSender, fileInfo, msgCallback);
    }
  
    /**
     * 插入断开弱提示
     * @param {*} targetId 
     * @param {*} userId 
     * @param {*} isSender 
     * @param {*} fileInfo 
     * @param {*} msgCallback 
     */
    addDiscMsg(targetId, userId, isSender, fileInfo, rtcState ,msgCallback) {
      logger.debug('addDiscMsg', targetId, userId, fileInfo.isSender, fileInfo);
      let body = `您终止了【${fileInfo.filename}】的发送`;
      switch(rtcState){
        case FileStatus.ERROR_NET:
        body = `网络异常,【${fileInfo.filename}】取消传输`;
        break
        case FileStatus.ERROR_RTC:
        body = `通道连接失败,【${fileInfo.filename}】取消传输`;
        break
      }
      let msgbase = {
        fromId: userId,
        targetId: targetId,
        body,
        tipType: 12,
        operType: fileInfo.isSender ? SubType.DISCONNECTION_SENDER : SubType.DISCONNECTION_RECEIVER,
        userInfo: userId,
        operUser: targetId,
        tipTime: new Date().getTime().toString(),
        fileInfo: JSON.stringify(fileInfo)
      };
      let msgWeak = new MsgWeak(msgbase)
      Service.chat.insertMessage(msgWeak.messageObject, res => {
        logger.debug('p2pUtils::addDiscMsg==> ', res);
      });
    }
  
    close() { // 
      logger.debug('close');
      this.rtc.sendList = [];
      this.rtc.receiveList = [];
      this.rtc.Close();
      // this._fileCallbackMap.clear();
    }
  
    getSendFileList() {
      logger.debug('getSendFileList');
      return this.rtc._getSendFileList();
    }
  
    getReceiveFileList() {
      logger.debug('getReceiveFileList');
      return this.rtc._getReceiveFileList();
    }
    // type 10 成功 15拒绝  16 发送方取消  17 接收方取消
    _sendPromptMsg(targetId, userId, type, fileInfo, msgCallback) {
      logger.debug('_sendPromptMsg', targetId, userId, type, fileInfo);
      let body = '';
      switch (type) {
        case SubType.SUCCESS_SEND:
        case SubType.SUCCESS_RECEIVE:
          body = `文件【${fileInfo.filename}】传输成功`
          break
        case SubType.REFUSE:
          body = `文件【${fileInfo.filename}】被接收方拒绝了`
          break
        case SubType.BUSY_RECEIVER:
          body = `接收方正在文件直传`;
          break;
        case SubType.CANCEL_SENDER:
          body = `文件【${fileInfo.filename}】被发送方取消`
          break
        case SubType.CANCEL_RECEIVER:
          body = `文件【${fileInfo.filename}】被接收方取消`
          break
        case SubType.TIMEOUT:
          body = `接收方长时间未响应，文件【${fileInfo.filename}】被取消`
          break
      }
      let msgbase = {
        fromId: userId,
        targetId: targetId,
        body: body,
        tipType: 12,
        operType: type,
        userInfo: userId,
        operUser: targetId,
        tipTime: new Date().getTime().toString(),
        fileInfo: JSON.stringify(fileInfo)
      };
      let msgWeak = new MsgWeak(msgbase)
      this._sendMessage(msgWeak.messageObject, msgCallback);
    }
  
    _sendMessage(msgbase, callback) {
      logger.debug('_sendMessage', JSON.stringify(msgbase));
      Service.chat.sendMessage(msgbase, resp => {
        logger.debug('_sendMessage', resp);
        if (callback) {
          callback(resp);
        }
      });
    }
  }
  