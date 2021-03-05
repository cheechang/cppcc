//
//  1 chunck = 16000Byte = 15Kb
//
//  在chunck前/后加入4字节记录block与chunck信息，block:chunck=26：6
//
//

//
// file.rtccfg储存文件信息
// 8字节：文件大小
// 4字节：block—index
//
const fs = require('fs');
import Logger from '../Logger'
const logger = new Logger('rtcfile');
import {
  RtcParam,
  Rtcsdk,
  RTC_PEER_TYPE
} from '../../rtc/rtcsdk/rtcsdk'
import {
  OptionType,
  RtcStatus,
  FileStatus,
  RtcMethod
} from './constant'
const {
  clipboard,
  remote
} = require('electron');
const Service = remote.getGlobal('service')
const CHUNCK_PER_BLOCK = 64;
const CHUNCK_SIZE = 16000;
const BLOCK_SIZE = CHUNCK_PER_BLOCK * CHUNCK_SIZE;
const CFG_SIZE = 12;

let rtcfile_self = null;

export class Rtcfile {
  constructor(rtcCallback, fileCallback) {
    rtcfile_self = this;
    this.sendList = []; // 发送列表
    this.receiveList = []; // 接收列表 正在接收或已点击接收
    this.rtcCallback = rtcCallback;
    this.fileCallback = fileCallback;
    this.start_time_ = 0;

    // this._channelId = '';
    // transitFile = '' // 传输中的文件信息
    // this._isSender() = is_sender;

    this.rtcplugin_state_ = -1; // 记录rtcplugin的状态

    this.last_percent_time = 0; // 记录上次向UI推送百分比的时间，用于计算即时传输速度

    this.state_ = 'close'; // 'close', 'open', 'failed'


    this.remote_info_ = {
      userId: null
    };
    this.rtcplugin_ = remote.getGlobal('service')['rtcplugin'];
    //this.rtcplugin_.regChannelEventCb(this._OnRtcpluginMsg);
    logger.debug('constructor', this.rtcplugin_);
    this.rtcplugin_.regRtcFileCb(this._OnRtcpluginMsg.bind(this));
    this.rtcsdk_ = null;

    this.file_info_ = {
      percent: 0, // 发送或接收方的进度
      outgoing: {
        fileId: -1,
        fd: null,
        filename: null, // path + name
        filesize: 0,
        blocks_per_file: 0,
        block_index: 0,
        chunck_index: 0,
        chuncks_in_lastblock: 0,
        data_buf: new Uint8Array(BLOCK_SIZE), // 一次从文件中读取的block
        chunck_to_send: new Uint8Array(CHUNCK_SIZE + 4), // 一次发送的chunck，包含4字节额外信息
        last_chunck_size: CHUNCK_SIZE,
        filepath: null
      },
      incoming: {
        fileId: -1,
        fd: null,
        filename: null, // 路径+名字
        filesize: 0,
        blocks_per_file: 0,
        block_index: 0,
        chunck_index: 0,
        chuncks_in_lastblock: 0,
        last_chunck_size: 0,
        block_to_write: new Uint8Array(BLOCK_SIZE),
        chuncks_map: new Map(),
        block_to_request: 0,
        filepath: null,
        realfilename: null, // 真正的文件名
      }
    };

    this.jsonrpc_ = {
      filesender: {},
      filereceiver: {
        id: 0,
        method: null
      }
    }
    this._checkTimeOut(false, 5000);
  }

  // 发送方保存所有的发送文件
  _addSendFile(fileInfo) {
    logger.debug('_addSendFile', fileInfo);
    if (fileInfo) {
      this.sendList.push(fileInfo);
    }
  }

  _checkTimeOut(cancel, interval) {
    if (cancel) {
      window.clearInterval();
    } else {
      window.setInterval(() => {
        this.sendList.forEach(file => {
          if (file.sendTime + file.timeout + 5000 < new Date().getTime()) {
            logger.debug('_checkTimeOut::', file.sendTime + file.timeout + 5000, new Date().getTime(), file.sendTime + file.timeout + 5000 - new Date().getTime());
            this.fileCallback(file, FileStatus.TIMEOUT);
            this._removeSendFile(-1, file.fileId);
          }
        });
      }, interval);
    }
  }

  // 接收方保存正在传输的文件
  _addReceiveFile(fileInfo) {
    logger.debug('_addReceiveFile', fileInfo);
    if (fileInfo) {
      this.receiveList.push(fileInfo);
    }
    this._AcceptFile(fileInfo);
  }
  // 发送方保存正在传输的文件
  _addSendingFile(fileId, position = -1) {
    logger.debug('_addSendingFile', fileId);
    for (let i = 0; i < this.sendList.length; i++) {
      let file = this.sendList[i];
      if (file.fileId === fileId) {
        if (this.receiveList.indexOf(file) === -1) {
          if (position === -1) {
            this.receiveList.push(file);
          } else {
            this.receiveList.splice(position, 0, file);
          }
          this.sendList.splice(i, 1); // 移除 发送中的文件，剩余文件循环检查 超时
        }
      }
    }

    // this.sendList.forEach(file => {
    //   if (file.fileId === fileId) {
    //     if (this.receiveList.indexOf(file) === -1) {
    //       if (position === -1) {
    //         this.receiveList.push(file);
    //         this.sendList.splice();
    //       } else {
    //         this.receiveList.splice(position, 0, file);
    //       }
    //     }
    //   }
    // });
  }
  _getSendFileList() {
    return this.sendList;
  }

  _setSendFileList(list) {
    this.sendList = list;
  }

  _getReceiveFileList() {
    return this.receiveList;
  }

  _setReceiveFileList(list) {
    this.receiveList = list;
  }

  _setFileState(state) {
    this.sendList.forEach(file => {
      this.fileCallback(file, state);
    });
    this.receiveList.forEach(file => {
      this.fileCallback(file, state);
    })
  }

  // 移除发送方文件
  _removeSendFile(index = -1, fileId = -1) {
    logger.debug('_removeSendFile', index, fileId);
    if (index == 0) {
      this.sendList.shift();
    } else if (fileId != -1) {
      for (let i = 0; i < this.sendList.length; i++) {
        if (this.sendList[i].fileId == fileId) {
          this.sendList.splice(i, 1);
        }
      }
    } else {
      this.sendList = [];
    }
  }
  // 移除传输中的文件
  _removeReceiveFile(index = -1, fileId = -1) {
    logger.debug('_removeReceiveFile', index, fileId);
    if (index == 0) {
      this.receiveList.shift();
    } else if (fileId != -1) {
      for (let i = 0; i < this.receiveList.length; i++) {
        if (this.receiveList[i].fileId == fileId) {
          this.receiveList.splice(i, 1);
        }
      }
    } else {
      this.receiveList = [];
    }
  }

  _getChannelId() {
    return this._channelId;
  }

  _SendPercent(block_index, is_sender) {
    logger.debug('_SendPercent ', block_index, is_sender);
    let blocks_in_file;
    if (is_sender) { // 发送
      blocks_in_file = this.file_info_.outgoing.blocks_per_file;
    } else {
      blocks_in_file = this.file_info_.incoming.blocks_per_file;
    }
    let last_percent = this.file_info_.percent;
    let percent = block_index * 1.0 / blocks_in_file;
    if (percent - last_percent < 0.01)
      return;
    else {
      this.file_info_.percent = percent;
      let file_size = null; // Byte
      if (this._isSender())
        file_size = this.file_info_.outgoing.filesize;
      else
        file_size = this.file_info_.incoming.filesize;
      let cur_time = new Date().getTime(); // 毫秒
      let usedTime = (cur_time - this.last_percent_time) / 1000.0; //两个时间戳相差的秒数 
      this.last_percent_time = cur_time;
      let rate = (percent - last_percent) * file_size / usedTime; // Byte/s
      let timeleft = (1 - percent) * file_size / rate;
      let per = {
        percent: percent, // 接收/发送百分比
        rate: rate, // 即时速度，单位KB/s
        timeleft: timeleft // 剩余时间,单位秒
      };
      logger.debug('_SendPercent', `file_size=${file_size}, usedTime=${usedTime}, per=${per}`);
      this.fileCallback(this.receiveList[0], per);
    }
  }

  _OnRtcsdkMsg(peer_id, msg_type, msg, data_size) {
    logger.debug('_OnRtcsdkMsg():', `peer_id:${peer_id}, msg_type:${msg_type},msg:${msg}, data_size:${data_size}`);
    // if (this.rtcplugin_state_ == 4)
    //   return;
    let weakSelf = rtcfile_self;
    switch (msg_type) { // kOffer
      case 103:
        logger.file('_OnRtcsdkMsg', msg);
        if (msg == 'host') {
          weakSelf._setFileState(FileStatus.HOST);
        } else if (msg == 'srflx') {
          weakSelf._setFileState(FileStatus.SRFLX);
        } else if (msg == 'prflx') {
          weakSelf._setFileState(FileStatus.PRFLX);
        } else {
          weakSelf._setFileState(FileStatus.RELAY);
        }
        break;
      case 101: // kOffer
        weakSelf.rtcCallback(RtcStatus.OFFER);
        let request = {
          targetId: peer_id,
          reject: false,
          videoType: '7',
          firstSdp: msg,
          operType: 0
        };
        weakSelf.rtcplugin_.createChannel(
          request, res => {
            logger.file('createChannel():', `101 res:${res.code}`);
            if (res.code !== 0) {
              weakSelf.rtcCallback(RtcStatus.ERROR_OFFER);
              weakSelf._setFileState(FileStatus.ERROR_OFFER);
              weakSelf.Close();
            }
          }
        )
        break;
      case 102: // kAnswer
        weakSelf.rtcCallback(RtcStatus.ANSWER);
        let request1 = {
          // channelId: parseInt(peer_id),
          // targetId: parseInt(peer_id), /// < 目标Id 创建/邀请
          channelId: peer_id,
          targetId: peer_id, /// < 目标Id 创建/邀请
          videoType: '7', /// < 1，语音  2，视频
          secondSdp: msg, /// < 生成第二次sdp
          type: 1
        };
        weakSelf.rtcplugin_.acceptOrReject(
          request1, res => {
            logger.file('acceptOrReject():', `102 res:${res.code}`);
            if (res.code !== 0) {
              weakSelf.rtcCallback(RtcStatus.ERROR_ANSWER);
              weakSelf._setFileState(FileStatus.ERROR_ANSWER);
              weakSelf.Close();
            }
          }
        )
        break;
      case 105: // 网络断开
        logger.fileError('_OnRtcsdkMsg', '105');
        weakSelf.rtcCallback(RtcStatus.ERROR_NET);
        weakSelf._setFileState(FileStatus.ERROR_NET);
        weakSelf.sendList = [];
        weakSelf.receiveList = [];
        weakSelf.Close();
        break;
      case 301: // kDataChannelOpen
        // data_size 表示通道编号 0，1，2，3.。。。
        weakSelf.rtcCallback(RtcStatus.CONNECTION);
        weakSelf.state_ = 'open'; // 'close', 'open', 'failed'
        logger.file('_OnRtcsdkMsg', `301 datachannel opened`);
        weakSelf._OnDataChannelOpen(true);
        weakSelf._Start();
        break;
      case 'kData':
        // data_size 表示通道编号 0，1，2，3.。。。
        weakSelf._OnData(msg);
        break;
      case 'failed':
        logger.fileError('_OnRtcsdkMsg', 'failed');
        weakSelf.rtcCallback(RtcStatus.ERROR);
        weakSelf.state_ = 'failed';
        weakSelf._setFileState(FileStatus.ERROR_RTC);
        weakSelf.sendList = [];
        weakSelf.receiveList = [];
        weakSelf.Close();
        break;
      default:
        break;
    }
  }

  _OnRtcpluginMsg(req) {
    logger.file('_OnRtcpluginMsg():', req.type)
    // this.rtcplugin_state_ = req.type;
    this._channelId = req.channelId;
    switch (req.type) {
      case 1: //  接收方
        this.remote_info_ = req;
        let sdp = req.sdp;
        this._createAnswer(req.userId, sdp)
        // 存在对呼，不处理        
        break;
      case 2: // 成员离开
        if (this.state_ === 'open') { // 'close', 'open', 'failed'
          //if (this.is_active_ === true) { // 对方取消
        }
        break;
      case 3: //  对方拒绝
        // this.rtcplugin_.resetCallback();
        break;
      case 4: // 对方忙
        this.rtcCallback(RtcStatus.BUSY);
        this._setFileState(FileStatus.BUSY);
        // this.sendList = [];
        this.receiveList = [];
        this.Close();
        break;
      case 5: // 超时
        this.rtcCallback(RtcStatus.TIMEOUT);
        logger.debug('_OnRtcpluginMsg():', 'timeout');
        this._setFileState(FileStatus.TIMEOUT);
        this.sendList = [];
        this.receiveList = [];
        this.Close();
        // this.rtcplugin_.resetCallback();
        break;
      case 6: // 对方取消
        this.rtcCallback(RtcStatus.CANCEL);
        break;
      case 7: // 对方
        break;
      case 9: // 其他端处理
        //RTCP2P_self.hangUp();    
        break;
      case 11: // 发送方 
        this.remote_info_ = req;
        this.rtcsdk_.SetRemoteSDP(req.userId, req.sdp);
        break;
      case 13: // 房主离开
        break;
      case 20: // 视频转音频
        break;
      default:
        break;
    }
  }

  _syncReceiveFile() {
    this.receiveList.forEach(fileInfo => {
      this._AcceptFile(fileInfo);
    });
  }

  _AcceptFile(fileInfo) {
    logger.file('_AcceptFile', fileInfo.fileId, this.state_);
    if (this.state_ === 'failed') {
      this.fileCallback(fileInfo, FileStatus.ERROR_RTC);
    } else {
      this.fileCallback(fileInfo, FileStatus.ACCEPT);
      if (this.state_ === 'open') {
        let json_msg = this._MakeJsonRpc(true, RtcMethod.ACCEPT, {
          'fileId': fileInfo.fileId,
          'fileCount': this.receiveList.length
        });
        this._SendData(json_msg);
      }
    }
  }

  _OnDataChannelOpen(isFirst) {
    logger.debug('_OnDataChannelOpen', this.sendList, this.receiveList, this._channelId, this.remote_info_.userId);
    if (!this._isSender()) {
      if (isFirst) {
        this._syncReceiveFile();
      }

      let json_msg = this._MakeJsonRpc(true, RtcMethod.FILE_INFO, {});
      // logger.file(`_OnDataChannelOpen(): --> ${JSON.stringify(json_msg)}`);
      // // SendData（peer_id, label, data）  // label 表示0，1，2，3，4 .。。。。
      this._SendData(json_msg);
    }
  }

  _requestFirst4Bytes() {
    let json_msg = this._MakeJsonRpc(true, RtcMethod.FIRST4BYTES, {});
    logger.file('_requestFirst4Bytes():', `<-- ${json_msg}`);
    this._SendData(json_msg);
  }

  _sendFirst4Bytes(obj) {
    let fd = this.file_info_.outgoing.fd;
    let buf = Buffer.allocUnsafe(4);
    let bytesread = fs.readSync(fd, buf, 0, 4, 0);
    let json_msg = this._MakeJsonRpc(false, RtcMethod.FIRST4BYTES, buf, obj.id);
    this._SendData(json_msg);
  }
  _writeFirst4Bytes(byte) {
    let buf = Buffer.allocUnsafe(4);
    let bytes = byte.data;
    buf[0] = bytes[0];
    buf[1] = bytes[1];
    buf[2] = bytes[2];
    buf[3] = bytes[3];
    let fd = this.file_info_.incoming.fd;
    fs.writeSync(fd, buf, 0, 4, 0);
    this._CloseFile(true);
    this._End();
  }

  _OnFileData(msg) {
    msg = new Uint8Array(msg);
    let chunck_index = msg[3];
    let block_index = msg[0] << 16;
    block_index += msg[1] << 8;
    block_index += msg[2];

    let chuncks_map = this.file_info_.incoming.chuncks_map;
    let blocks_in_file = this.file_info_.incoming.blocks_per_file;
    let chuncks_in_lastBlock = this.file_info_.incoming.chuncks_in_lastblock;
    let last_chunck_size = this.file_info_.incoming.last_chunck_size;
    let last_block_size = (chuncks_in_lastBlock - 1) * CHUNCK_SIZE + last_chunck_size;
    let recvd_percent = this.file_info_.incoming.recvd_percent;

    msg = msg.slice(4, msg.byteLength);
    chuncks_map.set(chunck_index, msg);

    let chuncks_recvd = chuncks_map.size;
    if (block_index === blocks_in_file - 1 && chuncks_recvd === chuncks_in_lastBlock) { // 文件结束,整个文件的最后一个chunck
      let length = last_block_size;
      let position = block_index * BLOCK_SIZE;
      this._WriteData(length, position, block_index); // 写最后一个block到文件中

      //this._End();
      this._requestFirst4Bytes(); // 请求前4个字节
    } else if (chuncks_recvd === CHUNCK_PER_BLOCK) { // 当前block接收完成
      let length = BLOCK_SIZE;
      let position = block_index * BLOCK_SIZE;
      this._WriteData(length, position, block_index); // 写一个block到文件中
      this._RequestBlock(++block_index);

      this._SendPercent(block_index, false); // 接收进度，每1%推送到界面
    }
  }

  _isSender() {
    return this.receiveList.length === 0 || this.receiveList[0].isSender
  }

  _OnJsonString(msg) {
    logger.debug(`_OnJsonString(): msg${msg}`);
    let obj = JSON.parse(msg);
    if (obj.method === RtcMethod.ACCEPT) {
      let fileId0 = obj.params.fileId;
      if (this._channelId === this.remote_info_.userId) { // 文件发送方
        if (this.receiveList.length > 0) {
          this._addSendingFile(fileId0);
        } else {
          this._addSendingFile(fileId0, this.receiveList.length - 1);
        }
      } else { // 接收方
        this._addSendingFile(fileId0);
      }
      let fileInfo0 = this.receiveList.filter(file => {
        return file.fileId === fileId0
      });
      this.fileCallback(fileInfo0[0], FileStatus.ACCEPT)
      // if (this._isSender()) {
      //   this._setSendFileInfo(this.receiveList[0]);
      //   this.fileCallback(this.receiveList[0], FileStatus.BEGIN);
      //   let json_msg = this._MakeJsonRpc(false, RtcMethod.FILE_INFO, {}, obj.id);
      //   this._SendData(json_msg);
      // }
      return
    }
    if (!this._isSender()) { // 接收端
      // if(this.receiveList && this.receiveList[0].isSender){
      // logger.fileError('rtcfile::_OnJsonString==> ', obj.id, this.jsonrpc_.filereceiver.id);
      //logger.file(`_OnJsonString(): --> ${msg}`);
      switch (obj.method) { // this.jsonrpc_.filereceiver.method
        case RtcMethod.FILE_INFO:
          let fileInfo = this.receiveList[0]; //this._getSendingFile(obj.result.fileId);
          this.fileCallback(fileInfo, FileStatus.BEGIN);
          if (this._ReceiverSetFileinfo(fileInfo) === -1) {
            this.fileCallback(fileInfo, FileStatus.ERROR_NOSPACE);
            return
          };
          this._RequestBlock(this.file_info_.incoming.block_to_request);
          break;
        case RtcMethod.REQUEST:
          break;
        case RtcMethod.FIRST4BYTES:
          this._writeFirst4Bytes(obj.result);
          break;
        case RtcMethod.CANCEL:
          let fileId = obj.params.fileId;
          let fileInfo1 = this.receiveList.filter(file => {
            return file.fileId === fileId
          });
          this.fileCallback(fileInfo1[0], FileStatus.CANCEL)
          this._removeReceiveFile(-1, fileId);
          this._CloseFile(false);
          this._RequestNextFile(fileId);
          break
        case RtcMethod.CLOSE:
          this.state_ = 'close'; // 'close', 'open', 'failed'
          this.rtcCallback(RtcStatus.CLOSE);
          this.Close();
          break;
        default:
          // error
          break;
      }
    } else { // 发送端
      switch (obj.method) {
        case RtcMethod.FILE_INFO: {
          logger.debug('_OnJsonString::FILE_INFO==>2 ', this._channelId, this.remote_info_.userId, this._isSender(), this.receiveList);
          // this._addSendingFile(obj.params.fileId);
          this._setSendFileInfo(this.receiveList[0]);
          this.fileCallback(this.receiveList[0], FileStatus.BEGIN);
          let json_msg = this._MakeJsonRpc(false, RtcMethod.FILE_INFO, {}, obj.id);
          this._SendData(json_msg);
          break;
        }
        case RtcMethod.REQUEST: {
          this._ReadBlock(obj.params.block);
          // let json_msg = this._MakeJsonRpc(false, RtcMethod.REQUEST, {}, obj.id);
          //logger.file(`_OnJsonString(): <-- ${json_msg}`);
          // this._SendData( json_msg);
          this._SendBlock(obj.params.block);
          break;
        }
        case RtcMethod.RECVALL: // 接收端接收完毕
        {
          logger.debug(`_OnJsonString(): RecvAll`);
          this._End();
          break;
        }
        case RtcMethod.FIRST4BYTES: {
          logger.debug(`_OnJsonString() RtcMethod.FIRST4BYTES: --> ${obj}`);
          this._sendFirst4Bytes(obj);
          break;
        }
        case RtcMethod.ACCEPT:
          let fileId0 = obj.params.fileId;
          let fileCount = obj.params.fileCount;
          this._addSendingFile(fileId0);
          let fileInfo0 = this.receiveList.filter(file => {
            return file.fileId === fileId0
          });
          this.fileCallback(fileInfo0[0], FileStatus.ACCEPT)
          // if(filein)
          // let json_msg = this._MakeJsonRpc(true, RtcMethod.ACCEPT_DONE, {
          //   'fileId': fileInfo.fileId,
          //   'fileCount': this.receiveList.length
          // });
          // this._SendData(json_msg);
          break;
        case RtcMethod.CANCEL:
          let fileId = obj.params.fileId;
          let fileInfo1 = this.receiveList.filter(file => {
            return file.fileId === fileId
          });
          this.fileCallback(fileInfo1[0], FileStatus.CANCEL)
          this._removeReceiveFile(-1, fileId);
          this._CloseFile(false);
          this._RequestNextFile(fileId);
          break
        case RtcMethod.CLOSE:
          // this.state_ = 'close'; // 'close', 'open', 'failed'
          // this.rtcCallback(RtcStatus.CLOSE);
          // this.Close();
          break;
        default:
          // error
          break;
      }
    }
  }

  _OnData(msg) {
    logger.debug('_OnData', msg);
    // datachannel数据类型：USVString, Blob, ArrayBuffer, ArrayBufferView.
    if (msg.byteLength !== undefined) { // ArrayBuffer
      this._OnFileData(msg);
    } else { // json string
      this._OnJsonString(msg);
    }
  }

  _Start() {
    logger.debug('_Start');
    //this.is_active_ = true;
    this.start_time_ = new Date().getTime();
    this.last_percent_time = this.start_time_;
  }

  _End() {
    logger.debug('_End', this.receiveList);
    this.fileCallback(this.receiveList[0], FileStatus.END);
    let file_size;
    if (this._isSender())
      file_size = this.file_info_.outgoing.filesize / 1024;
    else
      file_size = this.file_info_.incoming.filesize / 1024;
    let usedTime = new Date().getTime() - this.start_time_; //两个时间戳相差的毫秒数 
    logger.debug('_End():', ` filesize:${file_size}Kb, totaltime:${usedTime / 1000}s, averagespeed:${file_size / (usedTime / 1000)}Kb/s`);
    if (!this._isSender()) { // 接收方
      let json_msg = this._MakeJsonRpc(true, RtcMethod.RECVALL, {});
      this._SendData(json_msg);
    }
    let fileId = this.receiveList[0].fileId;
    this._removeReceiveFile(0);
    this._RequestNextFile(fileId);
  }

  _RequestNextFile(fileId) {
    logger.debug('_RequestNextFile(): ', `<-- ${this._isSender()} ${this.receiveList}`);
    if (this.receiveList.length > 0) {
      if (!this._isSender()) {
        this._OnDataChannelOpen(false);
        this._Start();
      } else {
        this._removeSendFile(-1, fileId);
      }
    } else {
      let json_msg = this._MakeJsonRpc(true, RtcMethod.CLOSE, {
        'fileId': fileId
      });
      this._SendData(json_msg);
      this.state_ = 'close'; // 'close', 'open', 'failed'
      this.rtcCallback(RtcStatus.CLOSE);
      this.Close();
    }
  }

  _Cancel(fileId) { // 先判断是否正在发送方 
    logger.debug('_Cancel', fileId);
    if (this.receiveList.length && this.receiveList[0].fileId === fileId) { // 正在传输的文件
      this.fileCallback(this.receiveList[0], FileStatus.CANCEL);
      let json_msg = this._MakeJsonRpc(true, RtcMethod.CANCEL, {
        'fileId': fileId
      });
      this._SendData(json_msg);
      this._CloseFile(false);
      this._removeReceiveFile(-1, fileId);
      this._RequestNextFile(fileId);
    } else {
      return -1;
    }
  }

  //
  // NodeJs文件系统
  //

  // 取消的文件不更改名字。
  _CloseFile(isFinish = false) {
    logger.debug('_CloseFile', isFinish);
    if (this._isSender()) {
      fs.closeSync(this.file_info_.outgoing.fd);
    } else {
      if (isFinish) {
        fs.ftruncateSync(this.file_info_.incoming.fd, this.file_info_.incoming.filesize);
        fs.renameSync(this.file_info_.incoming.filename + '.rtc', this.file_info_.incoming.filename)
      }
      fs.closeSync(this.file_info_.incoming.fd);
    }
  }

  // 每次读64个块，每个块16000Byte==15KB
  _ReadData(length, position) {
    let fd = this.file_info_.outgoing.fd;
    let buf = this.file_info_.outgoing.data_buf;
    let bytesread = fs.readSync(fd, buf, 0, length, position);
  }

  _WriteData(length, position, block_index) {

    let fd = this.file_info_.incoming.fd;
    let block_to_write = this.file_info_.incoming.block_to_write;
    let chuncks_map = this.file_info_.incoming.chuncks_map;
    let chuncks_recvd = chuncks_map.size;
    let i;
    // logger.debug('rtcfile::_WriteData => ',length, position, block_index,block_to_write,chuncks_map,chuncks_recvd);
    for (i = 0; i < chuncks_recvd; ++i) {
      block_to_write.set(chuncks_map.get(i), i * CHUNCK_SIZE);
    }
    chuncks_map.clear();

    fs.writeSync(fd, block_to_write, 0, length, position);

    const buf = Buffer.allocUnsafe(4);
    buf.writeUIntBE(block_index, 0, 4);
    fs.writeSync(fd, buf, 0, 4, 0); // 将续传信息写到文件起始处，所有block接收完毕后需要重传第一个block
  }

  //
  // JsonRpc
  //
  _MakeJsonRpc(request, method, params, id = -1) {
    if (this.receiveList && this.receiveList.length > 0 && method !== RtcMethod.FIRST4BYTES) {
      let fileInfo = this.receiveList[0];
      params = Object.assign({
        'fileId': fileInfo.fileId
      }, params);
    }
    if (request) { // 请求
      return JSON.stringify({
        'request': true,
        'method': method,
        'params': params,
        'id': ++this.jsonrpc_.filereceiver.id
      });
    } else { // 响应
      return JSON.stringify({
        'response': true,
        'method': method,
        'result': params,
        'id': id
      });
    }
  }

  // 发送方传输文件前设置文件信息
  _setSendFileInfo(fileInfo) {
    logger.debug('_setSendFileInfo', fileInfo);
    if (fileInfo) {
      let path = fileInfo.filePath;

      this.file_info_.outgoing.fd = fs.openSync(path, 'r'); // 读

      this.file_info_.percent = 0;
      this.file_info_.outgoing.filename = fileInfo.filename;
      this.file_info_.outgoing.filesize = fileInfo.size;
      this.file_info_.outgoing.blocks_per_file = fileInfo.blocks_per_file;
      this.file_info_.outgoing.block_index = 0;
      this.file_info_.outgoing.chunck_index = 0;
      this.file_info_.outgoing.chuncks_in_lastblock = fileInfo.chuncks_in_lastblock;
      this.file_info_.outgoing.last_chunck_size = fileInfo.last_chunck_size;
    }
  }
  //
  // 发送方 获取文件信息
  _SenderGetFileinfo(filePath) {
    logger.debug('_SenderGetFileinfo():', filePath);
    let file_info = this._SenderOpenFile(filePath, true);
    if (file_info === -1) {
      logger.fileError('_SenderGetFileinfo', 'file_info is null');
      return;
    }
    let filesize = file_info.size;
    let blocks_per_file = Math.ceil(filesize / BLOCK_SIZE);
    let last_block_size = filesize % BLOCK_SIZE;
    let chuncks_in_lastblock = Math.ceil(last_block_size / CHUNCK_SIZE);
    let last_chunck_size = last_block_size % CHUNCK_SIZE;
    // file_info.filePath = filePath
    let params = {
      'fileId': file_info.fileId,
      'size': filesize,
      'filename': file_info.name,
      'blocks_per_file': blocks_per_file,
      'chuncks_in_lastblock': chuncks_in_lastblock,
      'chunck_size': CHUNCK_SIZE,
      'chuncks_per_block': CHUNCK_PER_BLOCK,
      'last_chunck_size': last_chunck_size
    };
    // this._addSendFile(file_info);
    return params;
  }
  _ReceiverSetFileinfo(obj) {
    let filepath = obj.filePath;
    let filesize = obj.size;
    let block_index = this._ReceiverOpenFile(filepath, filesize);
    logger.debug('_ReceiverSetFileinfo==> ', obj, filepath, block_index);
    if (block_index === -1)
      return -1;
    this.file_info_.percent = 0;
    this.file_info_.incoming.fileId = obj.fileId;
    this.file_info_.incoming.block_to_request = block_index;
    this.file_info_.incoming.filename = filepath;
    this.file_info_.incoming.filesize = filesize;
    this.file_info_.incoming.filepath = filepath;
    this.file_info_.incoming.realfilename = obj.filename;

    this.file_info_.incoming.blocks_per_file = obj.blocks_per_file;
    this.file_info_.incoming.chuncks_in_lastblock = obj.chuncks_in_lastblock;
    this.file_info_.incoming.last_chunck_size = obj.last_chunck_size;
  }

  _RequestBlock(block_index) {
    let json_msg = this._MakeJsonRpc(true, RtcMethod.REQUEST, {
      'block': block_index,
    });
    //logger.file(`_RequestBlock(): --> ${json_msg}`);
    this._SendData(json_msg);
  }

  _ReadBlock(block_index) {
    let is_last_block = false;
    let blocks_per_file = this.file_info_.outgoing.blocks_per_file; // 当前文件的block总数
    let position = block_index * BLOCK_SIZE; // 当前block在file中的位置
    let length; // 当前block的长度

    if (block_index === blocks_per_file - 1) { // 最后一个block
      length = this.file_info_.outgoing.chuncks_in_lastblock * CHUNCK_SIZE;
    } else {
      length = BLOCK_SIZE;
    }

    this._ReadData(length, position);
  }

  _SendBlock(block_index) {
    let chunck_index; // 当前chunck的编号
    let start; // 一个block中chunk的起始位置
    let end; // 一个block中chunk的结束位置
    let chunck_to_send = this.file_info_.outgoing.chunck_to_send;
    let blocks_per_file = this.file_info_.outgoing.blocks_per_file; // 当前文件的block总数
    let chuncks_to_send;
    if (block_index === blocks_per_file - 1) { // 最后一个block
      chuncks_to_send = this.file_info_.outgoing.chuncks_in_lastblock;
    } else {
      chuncks_to_send = CHUNCK_PER_BLOCK;
    }

    chunck_to_send[2] = block_index;
    chunck_to_send[1] = block_index >> 8;
    chunck_to_send[0] = block_index >> 16;

    for (chunck_index = 0; chunck_index < chuncks_to_send - 1; ++chunck_index) {
      start = chunck_index * CHUNCK_SIZE;
      end = start + CHUNCK_SIZE;
      let chunk = this.file_info_.outgoing.data_buf.slice(start, end);
      chunck_to_send[3] = chunck_index;
      chunck_to_send.set(chunk, 4);
      this._SendData(chunck_to_send);
    }

    // 该block的最后一个chunck
    start = chunck_index * CHUNCK_SIZE;
    chunck_to_send[3] = chunck_index;


    let last_chunck_to_send;
    if (block_index === blocks_per_file - 1) {
      end = start + this.file_info_.outgoing.last_chunck_size;
      last_chunck_to_send = this.file_info_.outgoing.data_buf.slice(start, end);
      chunck_to_send.set(last_chunck_to_send, 4);
      this._SendData(chunck_to_send.slice(0, 4 + this.file_info_.outgoing.last_chunck_size));
    } else {
      end = this.file_info_.outgoing.data_buf.length;
      last_chunck_to_send = this.file_info_.outgoing.data_buf.slice(start, end);
      chunck_to_send.set(last_chunck_to_send, 4);
      this._SendData(chunck_to_send);

      this._SendPercent(block_index, true); // 发送进度，每1%推送到界面
    }
  }

  _SendData(data) {
    this.rtcsdk_.SendData(this.remote_info_.userId, '0', data);
  }

  _SenderOpenFile(file) {
    logger.debug('_SenderOpenFile', file);
    let fd = fs.openSync(file, 'r'); // 读
    let file_size = fs.fstatSync(fd).size;
    let temp = file.split('\\');
    if (file.indexOf('/') != -1) {
      temp = file.split('/');
    }
    let file_name = temp[temp.length - 1];
    return {
      fileId: this._Random(),
      size: file_size,
      name: file_name
    };
  }

  _ReceiverOpenFile(file, size) {
    logger.debug('_ReceiverOpenFile', file, size);
    let is_file_existed = fs.existsSync(file);
    let is_filertc_existed = fs.existsSync(file + '.rtc');
    logger.file('_ReceiverOpenFile():', `is_file_existed:${is_file_existed}, is_filertc_existed:${is_filertc_existed}`);
    if (!is_file_existed && is_filertc_existed) { // 断点续传
      let fd = this.file_info_.incoming.fd = fs.openSync(file + '.rtc', 'r+');
      let buf = Buffer.alloc(4);
      let bytesread = fs.readSync(fd, buf, 0, 4, 0);
      let temp = buf.readUIntBE(0, 4);
      logger.file('_ReceiverOpenFile():', `断点续传 block_index:${temp}`);
      return temp;
    } else {
      if (is_file_existed && is_filertc_existed) {
        fs.unlinkSync(file);
        fs.unlinkSync(file + '.rtc');
      } else if (is_file_existed && !is_filertc_existed) {
        fs.unlinkSync(file);
      }
      this.file_info_.incoming.fd = fs.openSync(file + '.rtc', 'w+');
      if (this.file_info_.incoming.fd) {
        try {
          fs.ftruncateSync(this.file_info_.incoming.fd, size + 4); // 返回值为undefined
        } catch (e) {
          logger.file('_ReceiverOpenFile():', `error:${e}`);
          return -1; // error 失败
        }
        return 0; // 成功
      } else {
        logger.file('_ReceiverOpenFile():', `error openSync`);
        return -1; // error 失败
      }
      // logger.file('_ReceiverOpenFile():', `create new file`);
    }
  }


  _createOffer(peer_id) {
    logger.debug('_createOffer', peer_id);
    this.rtcsdk_ = new Rtcsdk(this._OnRtcsdkMsg);
    let weakSelf = this;
    async function CreateOffer(res) {
      let peer_type = RTC_PEER_TYPE.DATA;
      let rtc_param = new RtcParam();
      rtc_param.ice_server = res['stunList'];
      rtc_param.ice_port = res.stunPort;
      rtc_param.ice_user = res.account;
      rtc_param.ice_pwd = res.password;
      rtc_param.sdp = null;
      rtc_param.call_back = weakSelf._OnRtcsdkMsg;
      rtc_param.local_render = null;
      rtc_param.remote_render = null;
      rtc_param.datachannel = {
        ordered: false,
        max_cnt: 1
      };
      logger.file('CreatePeer()', `peer_id:${peer_id}, peer_type:${peer_type}, rtc_param:${rtc_param}`);
      await weakSelf.rtcsdk_.CreatePeer(peer_id, peer_type, rtc_param);
    }
    this.rtcplugin_.getStunServer(res => {
      logger.file('_createOffer', 'getStunServer==>', res);
      CreateOffer(res);
    });
  }

  _createAnswer(peer_id, sdp) {
    logger.debug('_createAnswer', peer_id, sdp);
    this.rtcsdk_ = new Rtcsdk(this._OnRtcsdkMsg);
    let weakSelf = this;
    async function CreateOffer(res) {
      let peer_type = RTC_PEER_TYPE.DATA;
      let rtc_param = new RtcParam();
      rtc_param.ice_server = res['stunList'];
      rtc_param.ice_port = res.stunPort;
      rtc_param.ice_user = res.account;
      rtc_param.ice_pwd = res.password;
      // let obj = JSON.parse(this.remote_info_.sdp);
      rtc_param.sdp = sdp; //obj.sdp;
      rtc_param.call_back = weakSelf._OnRtcsdkMsg;
      rtc_param.local_render = null;
      rtc_param.remote_render = null;
      rtc_param.datachannel = {
        ordered: false,
        max_cnt: 1
      };
      logger.file('CreatePeer():', `peer_id:${peer_id}, peer_type:${peer_type}, rtc_param:${rtc_param}`);
      await weakSelf.rtcsdk_.CreatePeer(peer_id, peer_type, rtc_param);
    }
    this.rtcplugin_.getStunServer(res => {
      logger.file('_createAnswer', `getStunServer ${res}`);
      CreateOffer(res);
    });
  }

  Close() { // 销毁vue时调用
    const self = this;
    logger.file('Close():', this.state_);
    if (this.state_ === 'open') { // 取消
      if (this.file_info_.incoming.filename !== null) { // 接收端删除已经接收的文件
        if (!this._isSender()) {
          fs.closeSync(this.file_info_.incoming.fd);
          fs.unlinkSync(this.file_info_.incoming.filename + '.rtc');
        }
      }
    } else if (this.state_ === 'failed') { // 网断开
      if (!this._isSender()) {
        fs.closeSync(this.file_info_.incoming.fd);
      } else {
        fs.closeSync(this.file_info_.outgoing.fd);
      }
    } else if (this.state_ === 'close') { // 文件发送完毕
      // if (!this._isSender()) {
      //   fs.closeSync(this.file_info_.incoming.fd);
      // } else {
      //   fs.closeSync(this.file_info_.outgoing.fd);
      // }
    }
    this.rtcplugin_.leaveChannel(res => {
      self.rtcCallback(RtcStatus.DISCONNECT);
      self._checkTimeOut(true, 5000);
      logger.file('leaveChannel():', `res:${JSON.stringify(res)}`);
    });
    // this.rtcplugin_.resetCallback(); // rtcplugin恢复监听
  }

  _Random() {
    let num = '';
    for (let i = 0; i < 4; i++) {
      num = num + Math.floor(Math.random() * 10)
    }
    return num;
  }
};
