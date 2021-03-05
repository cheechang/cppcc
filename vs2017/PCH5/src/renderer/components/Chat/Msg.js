
function getServerTime() {
  try {
    let time = this.$Service.user.getServerTimeSync({})
    console.log('time', time)
    return time || new Date().getTime().toString()
  } catch (e) {
    console.log('getServerTime error：' + e);
    return new Date().getTime().toString()
  }
}

function getUID() { // 获取唯一值
  console.log('getUID:::::')
  return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
    let v = 0;
    var r = Math.random()*16|0;
    v = c == 'x' ? r : (r&0x3|0x8);
    return v.toString(16);
  });
}

function isJson(str) {
  if (typeof str === 'string') {
    try {
      let obj = JSON.parse(str);
      return true;
    } catch (e) {
      console.log('error：' + str + '!!!' + e);
      return false;
    }
  }else if(typeof str === 'object'){
    return true;
  }else{
    return false;
  }
}

const MsgDecorator = Sup => class extends Sup {
  // constructor (...args) {
  //   super(...args);
  // }
};

class Msg {
  constructor(msgbase, msgType = 2) {
    this.messageObject = {
         targetId: msgbase.targetId,
         fromId: msgbase.fromId,
         msgProperties: msgbase.msgProperties ? msgbase.msgProperties : '',
         msgType: msgbase.msgType ? msgbase.msgType : msgType,
         msgId: msgbase.msgId ? msgbase.msgId : '',
         time: msgbase.time ? msgbase.time : getServerTime(),
         isPrivateMsg: msgbase.isPrivateMsg ? msgbase.isPrivateMsg : 0,
         localId: msgbase.localId ? msgbase.localId : new Date().getTime().toString(),
         activeType: msgbase.activeType ? msgbase.activeType : 0,
         deviceType: msgbase.deviceType ? msgbase.deviceType : 1,
         timeZone: msgbase.timeZone? msgbase.timeZone : -4*(new Date().getTimezoneOffset()/60),
         noStore : msgbase.noStore || 0,
         unReadCount: msgbase.unReadCount ? msgbase.unReadCount : 0,
         maxUnReadCount: msgbase.maxUnReadCount? msgbase.maxUnReadCount : 0,
         snapshotId: msgbase.snapshotId ?  msgbase.snapshotId : 0,
         isNeedHandleUnread: msgbase.isNeedHandleUnread || false,
         deal: msgbase.deal || false,
         uuid: getUID(),
         relatedUsers: msgbase.relatedUsers || [],
         limitRange: msgbase.limitRange || []
    };
  }
}

class MsgTxt extends MsgDecorator(Msg) {
  constructor(msgbase,  flag = 0) {
    super(msgbase, 2);
    this.flag = flag;
    if (msgbase.hasRead) this.isRepeat = true;
    this.markId = msgbase.markId ? msgbase.markId : '';
    this.messageObject.isRbtMsg = msgbase.isRbtMsg|| false;
    this.messageObject.isReceipt = msgbase.isReceipt || false;
    this.messageObject.isDelay =  msgbase.isDelay || false;
    this.messageObject.delayTime = msgbase.delayTime || '';
    this.messageObject.body = msgbase.body ? msgbase.body : '';
  }
}

class MsgAudio extends MsgDecorator(Msg) {
  constructor(msgbase, flag = 0) {
    super(msgbase, 3);
    this.messageObject.url = msgbase.meidaUrl||msgbase.url;
    this.messageObject.mediaTime = msgbase.mediaTime;
    this.messageObject.fileName = msgbase.fileName;
    this.messageObject.encryptKey = msgbase.encryptKey;
    this.flag = flag;
  }
}
/**
 * msgBase (msgId senderId targetId sendTime property)
 * flag 0接收 1发送
 * thumbUrl 缩略图地址
 * mediaUrl 大图地址
 * encryptKey 加密密码
 * width 图片宽度
 * height 图片高度
 */
class MsgImg extends MsgDecorator(Msg) {
  constructor(msgbase, flag = 0) {
    super(msgbase, 5);
    this.flag = msgbase.flag || flag;
    this.messageObject.fileName = msgbase.fileName;
    this.messageObject.thumbUrl = msgbase.thumbUrl || '';
    this.messageObject.thumbPath = msgbase.thumbPath || '';
    this.messageObject.mainUrl = msgbase.mainUrl || '';
    this.messageObject.mainPath = msgbase.mainPath;
    this.messageObject.encryptKey = msgbase.encryptKey;
    this.messageObject.width = msgbase.width || '';
    this.messageObject.height = msgbase.height || '';
    this.messageObject.thumBbinary = msgbase.thumBbinary || '';
    this.messageObject.docID = msgbase.docID || 1;
  }
}
/**
 * msgBase (msgId senderId targetId sendTime property)
 * flag 0接收 1发送
 * fileName 文件名称
 * mediaUrl 文件地址
 * fileSize 文件尺寸
 * encryptKey 文件加密密码
 * progress 进度 下载或上传
 */
class MsgFile extends MsgDecorator(Msg) {
  constructor(msgbase, flag = 0) {
    super(msgbase, 6);
    this.flag = flag;
    this.body = msgbase.body || ''
    this.messageObject.fileName = msgbase.fileName || '';
    this.messageObject.url = msgbase.url || '';
    this.messageObject.isResume = msgbase.isResume || true;
    this.messageObject.filePath = msgbase.filePath || '';
    this.messageObject.encryptKey = msgbase.encryptKey || '';
    this.messageObject.size = msgbase.size || '';
    this.messageObject.preDefined = msgbase.preDefined ? msgbase.preDefined : '';
  }
}
/**
 * 弱提示消息
 * msgBase (msgId senderId targetId sendTime property)
 * weakBody 弱提示body 类型
 * weakInfo 弱提示信息
 */
class MsgWeak extends MsgDecorator(Msg) {
  constructor(msgbase) {
    super(msgbase, 8);
    this.messageObject.body = msgbase.body;
    this.messageObject.tipType = msgbase.tipType
    this.messageObject.operType = msgbase.operType
    this.messageObject.userInfo = msgbase.userInfo;
    this.messageObject.operUser = msgbase.operUser;
    this.messageObject.tipTime = msgbase.tipTime;
    this.messageObject.fileInfo = msgbase.fileInfo;
  }
}
/**
 * 网页链接消息
 * msgBase (msgId senderId targetId sendTime property)
 * linkUrl  链接地址
 * linkTitle 链接标题
 * description 网页描述
 * linkImg 链接图片
 * flag 0 接收 1 发送
 */
class MsgWebLink extends MsgDecorator(Msg) {
  constructor(msgbase, flag = 0) {
    super(msgbase, 9);
    this.messageObject.url = msgbase.url;
    this.messageObject.title = msgbase.title;
    this.messageObject.desc = msgbase.desc;
    this.messageObject.img = msgbase.img;
    this.flag = flag;
  }
}
/**
 * 图文消息
 * msgBase (msgId senderId targetId sendTime property)
 * imgText 图片文字信息
 */
class MsgImgText extends MsgDecorator(Msg) {
  constructor(msgbase, imgText) {
    super(msgbase, 12);
    this.messageObject.body = msgbase.body;
    this.messageObject.vtPtBean = msgbase.vtPtBean
  }
}
/**
 * 位置消息
 */
class MsgMap extends MsgDecorator(Msg) {
  constructor(msgbase, flag = 0) {
    super(msgbase, 4);
    this.messageObject.body = msgbase.body;
    this.messageObject.latitude = msgbase.latitude;
    this.messageObject.longitude = msgbase.longitude;
    this.messageObject.name = msgbase.name;
    this.flag = flag;
  }
}
/**
 * 模板消息
 * msgBase (msgId senderId targetId sendTime property)
 * templateTitle 模板标题
 * templateTitleColor 模板标题字体颜色
 * templateTitleBg 模板标题背景色
 * templateContent 模板内容
 * templateFields 模板类型
 * templateDetailUrl 模板详细地址
 */
class MsgImgTemplate extends MsgDecorator(Msg) {
  constructor(msgbase, flag = 0) {
    super(msgbase, 26);
    if (msgbase.subType !== 1) {
      this.messageObject.body = msgbase.body;
      this.messageObject.title = msgbase.title;
      this.messageObject.titleColor = msgbase.titleColor;
      this.messageObject.titleBGColor = msgbase.titleBGColor;
      this.messageObject.content = msgbase.content;
      this.messageObject.fields = msgbase.fields;
      this.messageObject.detailUrl = msgbase.detailUrl;
      this.messageObject.limitRange = msgbase.limitRange;
      this.messageObject.creator = msgbase.creator;
      this.messageObject.relatedUsers = msgbase.relatedUsers;
      this.messageObject.body = msgbase.body;
      this.flag = flag;
    } else {
      this.messageObject.body = msgbase.body;
      this.messageObject.userName = msgbase.userName;
      this.messageObject.subType = msgbase.subType;
    }
  }
}

class MsgNineImgs extends MsgDecorator(Msg) {
  constructor(msgbase, pictureCollection) {
    super(msgbase, 26);
    this.messageObject.nine = msgbase.nine;
  }
}

class MsgGroupNotice extends MsgDecorator(Msg) {
  constructor(msgbase) {
    super(msgbase, 64);
    this.messageObject.body = msgbase.body;
  }
}

class MsgMicroVideo extends MsgDecorator(Msg) {
  constructor(msgbase) {
    // 和反上来的消息字段保持一致  反上来的字段多为错误字段
    super(msgbase, 89);
    this.messageObject.encryptKey = msgbase.encryptKey;
    this.messageObject.preImgPath = msgbase.preImgPath;
    this.messageObject.vedioFileName = msgbase.vedioFileName;
    this.messageObject.vedioWideth = msgbase.vedioWideth;
    this.messageObject.vedioHight = msgbase.vedioHight;
    this.messageObject.vedioLenth = msgbase.vedioLenth;
    this.messageObject.vedioSize = msgbase.vedioSize;
  }
}
/**
 * 撤回消息
 */
class MsgRetract extends MsgDecorator(Msg) {
  constructor(msgbase, flag=0) {
    super(msgbase, 18);
    this.flag = flag;
    this.relatedUsers = msgbase.relatedUsers;
    this.msgReEdit = msgbase.msgReEdit;
    this.messageObject.body = msgbase.body;
    this.messageObject.revokeMsgId = msgbase.revokeMsgId;
    // this.messageObject.isSenderRevoke = msgbase.isSenderRevoke || false
  }
}
/**
 * 动态表情消息
 */
class MsgDynamicExp extends MsgDecorator(Msg) {
  constructor(msgbase, flag = 0) {
    super(msgbase, 19);
    this.messageObject.body = msgbase.body;
    this.flag = flag;
  }
}
/**
 * 群名片消息
 */
class MsgMemberCard extends MsgDecorator(Msg) {
  constructor(msgbase, flag = 0) {
    super(msgbase, 7);
    this.messageObject.mediaUrl = msgbase.mediaUrl;
    this.flag = flag;
  }
}
/**
 * 组合消息
 */
class MSGMIXTEXT extends MsgDecorator(Msg) {
  constructor(msgbase) {
    super(msgbase, 13);
    this.messageObject.body = msgbase.body;
    this.messageObject.mVt_msg = msgbase.mVt_msg;
  }
}

class MsgVideo extends MsgDecorator(Msg) {
  constructor(msgbase) {
    super(msgbase, 15);
    this.messageObject.body = msgbase.body;
  }
}

class MsgDivider extends MsgDecorator(Msg) {
  constructor(msgbase, flag = 0) {
    super(msgbase, 37);
    this.messageObject.body = msgbase.body;
    this.flag = flag;
  }
}

/**
 * 应用分享消息
 */
class MsgAppShare extends MsgDecorator(Msg) {
  constructor(msgbase,flag = 0) {
    super(msgbase, 36);
    this.flag = flag;
    this.messageObject.body = msgbase.body;
    if(isJson(msgbase.body)){
      let bodyInfo = JSON.parse(msgbase.body);
      this.messageObject.appID = bodyInfo.appID;
      this.messageObject.appIcon = bodyInfo.appIcon;
      this.messageObject.appName = bodyInfo.appName;
      this.messageObject.appTypeName = bodyInfo.appTypeName;
    }
  }
}
class MsgUnknow extends MsgDecorator(Msg) {
  constructor(msgbase) {
    super(msgbase, msgbase.msgType);
  }
}

const msgType = {
  2 : MsgTxt,
  3 : MsgAudio,
  4: MsgMap,
  5 : MsgImg,
  6 : MsgFile,
  7 : MsgMemberCard,
  8 : MsgWeak,
  9 : MsgWebLink,
  12 : MsgImgText,
  13 : MSGMIXTEXT,
  14 : MsgVideo,
  15 : MsgVideo,
  18 : MsgRetract,
  19 : MsgDynamicExp,
  26 : MsgImgTemplate,
  28 : MsgNineImgs,
  36 : MsgAppShare,
  37 : MsgDivider,
  64 : MsgGroupNotice,
  89 : MsgMicroVideo
};

//定义消息的工厂
function MsgFactory(msgType, options) {
  this.msgClass = msgType 
  return new this.msgClass(options); 
}

const msgStructure = data => {
  let type =
    data.msgType & 0x00ff ?
    data.msgType & 0x00ff :
    data.msgType & 0xff00
  //建造工厂并命名
  let types = msgType[type] !== undefined ?  msgType[type] : MsgUnknow
 
  return new MsgFactory(types, data);
};

export {
  MsgImg,
  MsgFile,
  MsgTxt,
  MsgWebLink,
  MsgRetract,
  msgStructure,
  MsgDynamicExp,
  isJson,
  MsgMemberCard,
  MsgImgTemplate,
  MsgMap,
  MsgWeak,
  MsgAppShare,
  MsgDivider
};
