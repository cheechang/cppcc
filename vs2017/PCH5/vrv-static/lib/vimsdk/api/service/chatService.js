/**
 * @file      Manages the chat's api.
 * @author    lixin <lixin1@vrvmail.com.cn>
 * @date      2019.11.19
 * @copyright Beijing VRV Software Co.,Ltd
 */
class ChatService {
  constructor(client, utils) {
    this._chat = client.chatService();
    this._utils = utils;
  }
  // 获取会话列表
  getChatList(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getChatList(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  setMessageRead(param){
    this._chat.setMessageRead(param);
  }
  //添加最近联系人
  addRecontact(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.addRecontact(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //移除会话
  removeChat(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.removeChat(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //注册最近会话头像更新
  regChatHeadImgUpdateCb(param, cb) {
    this._chat.regChatHeadImgUpdateCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
  //注册会话列表更新
  regRecontactCb(param, cb) {
    this._chat.regRecontactCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
  //获取所有消息数目
  getAllMsgCount(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getAllMsgCount(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取@我的消息 或者 我@别人的消息
  getAtMessage(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getAtMessage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取消息
  getMessages(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getMessages(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取对象聊天时间数组
  getMsgDays(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getMsgDays(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //根据日期获取消息
  getMsgFromDay(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getMsgFromDay(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取图片消息
  getImgMsg(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getImgMsg(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取群议题
  getIssueById(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getIssueById(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //拉取议题内历史消息
  getIssueMessages(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getIssueMessages(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取敏感词
  getBadWordList(param) {
    return this._chat.getBadWordList(param);
  }
  //获取敏感词
  getBadWordListAsync(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getBadWordList(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取联系人最大已读ID
  getContractMaxReadId(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getContractMaxReadId(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取群内消息的读取状态
  getGroupMsgReadState(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getGroupMsgReadState(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取一批消息的未读数计数器
  getGroupMsgUnreadCounter(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getGroupMsgUnreadCounter(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //统计消息已读、未读数量详细信息
  getGroupMsgUnreadInfo(param, cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getGroupMsgUnreadInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取不同类型的未读消息数量[同步接口]
  getUnReadMsgCountByType(param) {
    return this._chat.getUnReadMsgCountByType(param);
  }
  //获取不同类型的未读消息数量[异步接口]
  getUnReadMsgCountByTypeAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._chat.getUnReadMsgCountByType(param);
      resolve(result);
    })
  }
  //获取URL的详细信息
  getUrlInfo(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getUrlInfo(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取群置顶消息
  getGroupTopMsgById(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getGroupTopMsgById(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取群中潜水者ID集合
  getGroupDivers(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getGroupDivers(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //分页获取提醒消息
  getReminderMsgByPage(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.getReminderMsgByPage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //发送消息
  sendMessage(param,cb) {
    return this._chat.sendMessage(param, resp => {
      this._utils.makeCallBack(resp, cb);
    })
  }
  /*
   * 发送消息
   * cb 用于接收localId的回调函数
   */
  sendMessageAsync(param,cb) {
    return new Promise((resolve, reject)=>{
      let localId = this._chat.sendMessage(param, resp => {
        this._utils.makeCallBack(resp, null, resolve, reject);
      });
      if(cb){
        cb(localId);
      }
    })
  }
  //发送短信
  sendShortMessage(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.sendShortMessage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //发送附件消息
  sendAppendixMessage(param,cb,pro) {
    return new Promise((resolve, reject)=>{
      this._chat.sendAppendixMessage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      },proResp=>{
        this._utils.makeCallBack(proResp, pro);
      });
    })
  }
  //发送消息输入状态
  sendMsgInputState(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.sendMsgInputState(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //透传发送消息
  transferMessage(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.transferMessage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //插入消息
  insertMessage(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.insertMessage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //转发消息
  forwardMessage(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.forwardMessage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //通过消息ID解密消息
  decryptMsg(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.decryptMsg(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //删除所有消息
  deleteAllMessage(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.deleteAllMessage(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //通过msgId删除消息
  deleteMessageById(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.deleteMessageById(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //删除时间段消息
  deleteMessageByTime(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.deleteMessageByTime(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //更新对应targetId的消息
  updateMsg(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.updateMsg(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //本地查找群议题
  searchIssueLocal(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.searchIssueLocal(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //上传消息计数
  upMsgCount(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.upMsgCount(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //获取是否有群置顶消息[同步]
  isGroupTopMsgSync(param) {
    return this._chat.isGroupTopMsgSync(param);
  }
  //获取是否有群置顶消息[异步]
  isGroupTopMsgAsync(param) {
    return new Promise((resolve, reject)=>{
      let result = this._chat.isGroupTopMsgSync(param);
      resolve(result);
    })
  }
  //删除提醒消息
  deleteReminderMsg(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.deleteReminderMsg(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //会话置顶
  chatTop(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.chatTop(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //设置消息未读
  setMessageUnRead(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.setMessageUnRead(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //批量设置已读
  setMsgReads(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.setMsgReads(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //设置私信秘钥
  setPrivateKey(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.setPrivateKey(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //设置群置顶消息
  setGroupTopMsg(param,cb) {
    return this._chat.setGroupTopMsg(param, resp => {
      this._utils.makeCallBack(resp, cb);
    })
  }
  /*
   * 设置群置顶消息
   * cb 用于接收localId的回调函数
   */
  setGroupTopMsgAsync(param,cb) {
    return new Promise((resolve, reject)=>{
      let localId = this._chat.setGroupTopMsg(param, resp => {
        this._utils.makeCallBack(resp, null, resolve, reject);
      });
      cb(localId);
    })
  }
  //创建提醒消息
  createReminderMsg(param,cb) {
    return new Promise((resolve, reject)=>{
      this._chat.createReminderMsg(param, resp => {
        this._utils.makeCallBack(resp, cb, resolve, reject);
      });
    })
  }
  //消息游标推送
  regMessageCursorCb(param,cb) {
    this._chat.regMessageCursorCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
  //设置监听消息输入状态的回调
  regMessageInputStateCb(param,cb) {
    this._chat.regMessageInputStateCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
  //注册聊天消息的回调
  regMsgNoticeCb(param,cb) {
    this._chat.regMsgNoticeCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
  //设置监听离线消息的回调
  regOfflineMsgCb(param,cb) {
    this._chat.regOfflineMsgCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
  //设置监听新透传消息的回调
  regTransMsgNoticeCb(param,cb) {
    this._chat.regTransMsgNoticeCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
  //注册敏感词更新回调
  regBadWordUpdateCb(param,cb) {
    this._chat.regBadWordUpdateCb(param, resp => {
      this._utils.makeCallBack(resp, cb);
    });
  }
}
module.exports = ChatService;