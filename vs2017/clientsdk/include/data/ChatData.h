#pragma once
#include <string>
#include <vector>
#include <map>
#include "interface/Defines.h"
#include "data/UserData.h"
namespace data{

	#define  SYSMSG_ID   10000
	const int64  MSGMEMSIZE = 256;


	///快照信息
	struct SnapshotInfo
	{
		int64 msgId;			//消息ID
		int64 snapshotId;		//群快照ID
	};
	struct MsgUnreadCounter
	{
		int64 messageId;
		int32 unreadCount;
		///最大消息未读数
		int32 maxUnreadCount;
		///群快照ID
		int64 snapshotId;
	};

	///聊天类型
	enum ChatType
	{
		CHAT_INIT=0,
		BUDDY_CHAT = 1,        ///<好友聊天
		GROUP_CHAT = 2,        ///<群组聊天
		APP_CHAT = 3,		   ///<公众号
		SYSTEM_MSG = 4,        ///<系统消息
		STRANGER_CHAT = 5,     ///<陌生人聊天
		ENT_USER_CHAT = 6,     ///<企业成员聊天
		PHONE_CHAT = 7,        ///<我的设备
		ENT_CHAT,				///<企业号
		APPLICATION_CHAT,		///<应用号
	};
	enum MSGTYPE{
		MSG_TYPE_TEXT = 2,			///<文本消息
		MSG_TYPE_AUDIO,				///<语言消息
		MSG_TYPE_POSITION,			///<位置消息
		MSG_TYPE_IMG,				///<图片消息
		MSG_TYPE_FILE,				///<文件消息
		MSG_TYPE_CARD,				///<名片消息
		MSG_TYPE_TIP,				///<弱提示消息
		MSG_TYPE_WEB,				///<网页链接消息
		MSG_TYPE_PICTEXT = 12,		///<图文消息
		MSG_TYPE_COMBINE,           ///<组合消息
		MSG_TYPE_REVOKE = 18,		///<回执消息
		MSG_TYPE_DYNEXPRESSION,		///<动态表情消息
		MSG_TYPE_VOICE = 16,///<音頻消息
		MSG_TYPE_VIDEIO = 14,///<視頻消息
		MSG_TYPE_CONFER = 15,///<視頻会议消息
		MSG_TYPE_TASK = 17,///<任务消息
		MSG_TYPE_TEMPL = 26,    ///<模版消息
		MSG_TYPE_MINIVEDIO= 89,///<微视频消息
		MSG_TYPE_NINEBLOCK = 28,///<9图消息
		MSG_TYPE_DYNEXPRESSION2 = 27, ///<新动态表情
		MSG_TYPE_MAIL = 31, ///<邮件消息
		MSG_TYPE_UNREADSTATE = 34, ///<未读状态消息
		MSG_TYPE_UNIVERSAL = 64,   ///<万能消息，具体看subMsgType
		MSG_TYPE_REDPACKET = 88,///<红包消息
		MSG_TYPE_SYS = 100,	///<系统消息
	};
	
	///消息子类型
	enum SubMessageType
	{
		sub_groupAnnouncement = 1,     //群公告推送msgType64号消息，subMsgtype=1
		sub_buddyApply = 201,				//好友申请通知
		sub_agreeBuddyApply = 202,			//同意好友申请通知
		sub_rejectBuddyApply = 203,			//拒绝好友申请通知
		sub_groupApply = 301,				//申请入群
		sub_adminAgreeGroupAplly = 302,     //管理员同意入群
		sub_adminRejectGroupAplly = 303,    //管理员拒绝入群
		sub_inviteEnterGroup = 401,			//邀请入群
		sub_agreeEnterGroup = 402,			//用户同意入群
		sub_rejectEnterGroup = 403,        //用户拒绝入群
		sub_adminKickMember = 501,			//管理员踢出群成员
		sub_dissolveGroup = 503,			//解散群
		sub_groupMemberExit = 504,         //群成员退出
	};
	///消息状态
	enum MSGSTATE
	{
		MSG_TYPEX_UPLOAD_FAILED = 0x100,	///< 附加资源失败
		MSG_TYPEX_SEND_ERROR = 0x200,		///< 发送消息失败
		MSG_TYPEX_DOWNLOAD_FAILED = 0x400,  ///< 下载失败
		MSG_TYPEX_SENDING = 0x1000,			///< 正在发送消息
		MSG_TYPEX_UPLOADING = 0x2000,		///< 正在上传附件
	};

	enum TIPTYPE
	{
		MSG_TYPE_CHICK = 1, ///鸡毛信
		MSG_TYPE_TIP_READED = 10,   ///已读
		MSG_TYPE_TIP_NOREAD = 11     
	};
	
   ///会话列表信息
  class ChatData:public UserData{
 public:
	 ChatData() :operType(0), msgType(0), chatType(0), realUnReadCnt(0), msgTime(0), sendUserId(0), lastMsgId(0), msgProp(""), lastMsg(""), lastAtMsgID(0), unReadCnt(0){}
	  ~ChatData(){}
  public:
	  int		   operType;          ///<活动类型
	  int          msgType;		     ///<消息类型;1：HTML, 2:TEXT, 3：AUDIO, 4：POSITION, 5：IMG, 6：FILE, 7：CARD,  8：TIP
	  int		   chatType;	         ///<聊天类型  1人，2群，3公众号，4企业号
	  int32        realUnReadCnt;     ///< 真正的未读消息数量 = unReadCnt+弱提示消息数量+其它端同步的设备消息数量，客户端每次拉取未读用这个字段，当realUnReadCnt为0时，表示所有消息在当前设备客户端都已经看过了
	  int32		   unReadCnt;		//未读消息数
	  int64		   msgTime;           ///<消息时间
	  int64        sendUserId;	     ///< 发送者Id
	  int64		   lastMsgId;        ///最后一条消息ID
	  std::string  msgProp;		     ///<消息属性
	  std::string  lastMsg;           ///<最后一条消息
	  int64 lastAtMsgID;	  ///<最后一条@消息ID
	  int subType;          ///<子操作类型标示,置顶等其他操作
	  int8 disturbSet;		///<免打扰 1为接收提醒, 2表示不提醒仅显示数字, 3为免打扰
	  int8 msgRemindMode;
  };

  ///////发起会话
  class ChatInfo{
     public:
	 ChatInfo():isStartChat(false),unreadcount(0),chatType(CHAT_INIT),targetid(0),msgid(0),msgtime(0){
		 name = avatar =lastMsg= "";
		 isStartChat = false;
		 unreadcount = 0;
	 }
    ~ChatInfo(){};
	 public:
	  bool        isStartChat;		 //是否是发起会话
	  int         unreadcount;		 //未读数
	  int64		  targetid;			 ///目标id
	  int64       msgid;             ///最后一条消息ID
	  int64       msgtime;           ///消息时间
	  ChatType    chatType;	         ///<聊天类型  1人，2群，3公众号，4企业
	  std::string lastMsg;          ///最后一条消息内容
	  std::string name;				///名称
	  std::string avatar;			// 头像
  };

  
///消息基类
class Msg 
{
public:
	Msg() :isBurn(false),isRbtMsg(false),isDelay(false),isReceipt(false),isReceiptAll(false),isDeviceMsg(false),isRecvMsg(false),isUser(false),isGroup(false),status(0),
	deviceType(0),msgType(0), delayTime(0),msgId(0), targetId(0),localId(0),fromId(0), toId(0),lastMsgId(0),isFeather(0),
	time(0), userId(0), isPrivateMsg(0), UpFileFlag(0), EraserType(0),body(""), context("")
	{
	  relatedUsers.clear();
	  limitRange.clear();
	  unReadCount = maxUnReadCount = snapshotId;
    }
	virtual ~Msg() {}
	int16 unReadCount;		///<未读数量
	int16 maxUnReadCount;     ///<最大未读数量
	int64 snapshotId;		///<群快照ID
	int subType;	///< 消息子类型
	std::string msgProperties;		///<消息属性
	std::string userName;///<用户名 组合消息和系统新消息使用
	std::string userPic;///<用户头像 组合消息和系统消息使用 群系统消息时，为群头像 

	bool  isBurn;			///<是否是阅后即焚消息
	bool  isRbtMsg;         ///<是否是机器人消息
	bool  isDelay;			///<是否延迟消息
	bool  isReceipt;		///<是否阅后回执
	bool  isReceiptAll;		///<消息是抖一抖或阅后回执，且此消息体最后是英文小于号<结尾的
    bool  isDeviceMsg;		/// 是否是设备同步消息
	bool  isRecvMsg;	    /// 是否是接收消息
	bool  isGroup;          
	bool  isUser;
    int8  status;           ///消息状态
	int8  deviceType;       ///设备类型
	int8 isPrivateMsg;		///<是否是私信   0不是 1是
	int   msgType;			///<消息类型
	int64 delayTime;        ///<延迟时间
	int64 msgId;			///<消息ID
	int64 targetId;			///<会话者ID（群或用户等）
	int64 localId;			///<本地ID
	int64 fromId;			///<发送者ID
	int64 toId;				///<接收者ID
	int64 relatedMsgId;		///<关联消息ID
	int64 lastMsgId;		///<上一条消息ID
	int64 time;				///<消息发送的时间
	int64 userId;			///用户id
	std::string body;		///<消息内容 limitRange
	std::vector<int64> relatedUsers; ///<@人员列表
	std::vector<int64> limitRange;
	std::string context;//会话显示内容
	int  isFeather;  //鸡毛信0. 不是鸡毛信 1、表示原始消息 10表示已读 11表示未读已发送短信
	int UpFileFlag;   //上传文件标志  0：不上传   1：上传
	int EraserType; //橡皮擦消息 0：非橡皮擦消息 1:删除今天的消息 2：删除全部的消息
};  
  ///文本消息
class MsgText : public Msg 
{
public:
	MsgText()
	{ 
		msgType = MSG_TYPE_TEXT; 
	}
	~MsgText(){}
};
//任务消息
class MsgTask :public Msg{
public:
	MsgTask(){
		msgType = MSG_TYPE_TASK;
		timeTask.resize(MSGMEMSIZE);
		isFinish.resize(MSGMEMSIZE);
		isTask.resize(MSGMEMSIZE);
		isRead.resize(MSGMEMSIZE);
	}
	~MsgTask(){}
	std::string timeTask;
	std::string isFinish;
	std::string isTask;
	std::string isRead;
};

//图片消息
class MsgImg: public Msg{
public:
	MsgImg():width(0),height(0),docID(0)
	{ 
	    thumbUrl=mainUrl=thumbPath=mainPath=encryptKey=fileName=imageContents=thumBbinary="";
		msgType = MSG_TYPE_IMG; 
	}
	~MsgImg(){}
	int width;				///<图像宽度
	int height;				///<图像高度
	int32  docID;       	///是否加密
	std::string thumbUrl;	///<缩略图URL 一步发送消息时不赋值
	std::string mainUrl;	///<大图URL  一步发送消息时不赋值
	std::string thumbPath;	///<缩略图本地地址 一步发送消息时使用
	std::string mainPath;	///<大图本地地址 一步发送消息时使用
	std::string encryptKey;///<加密KEY
	std::string fileName;   ///<文件名  
	std::string imageContents;///<图片描述
	std::string thumBbinary;  ///缩略图二进制
};
//文件消息
class MsgFile: public Msg{
public:
	MsgFile():isSaveAs(false),isResume(false),isFolder(0),states(0),docID(0),size(0),fileId(0)
	{ 
		msgType = MSG_TYPE_FILE; 
		fileName = filePath = encryptKey = url="";
	}
	~MsgFile(){}

    bool  isSaveAs;			///是否是另存为文件
	bool  isResume;			///<是否断点上传(一步发消息时使用)
	int8  isFolder;			///<是否是文件夹 0,不是 1,是
	int   states;           ///<文件状态
	int32 docID;			///是否加密
	int64 size;				///<文件大小  
	int64 fileId;			///<文件ID
	std::string fileName;	///<文件名  
	std::string filePath;	///<文件本地路径  
	std::string encryptKey; ///<加密KEY
	std::string url;	    ///<文件URL	 一步发送消息时不赋值
};

//弱提示消息
class MsgTip : public Msg 
{
public:
	MsgTip() :tipType(0), operType(0)
	{ 
		msgType = MSG_TYPE_TIP; 
	    tipTime=operUser=userInfo=fileInfo="";
	}
	~MsgTip(){}
	int tipType; ///<tip 类型
	int operType;///<操作类型
	std::string tipTime;///<时间
	std::string operUser;///<操作userId
	std::string userInfo;///<用户信息
	std::string fileInfo;///<文件信息
};

//图文消息
class MsgPicWithText :public Msg{
public:
	///图文消息
	struct picTextBean{
		picTextBean():index(0){
			picUrl = title = url = dsc;
		}
		int32 index;
		std::string picUrl;///<图片url
		std::string title;///<标题
		std::string url;///<url
		std::string dsc;///<描述
	};
	MsgPicWithText(){
		msgType = MSG_TYPE_PICTEXT;
	}
	~MsgPicWithText(){}
	 std::vector<picTextBean> vtPtBean;///<消息集合
};
//模板消息
class MsgMasterplate :public Msg{
public:
	MsgMasterplate() :createTime(0){
		msgType = MSG_TYPE_TEMPL;
		content=detailUrl=title=toUsers=status=statColor=titleColor=type=titleBGColor=creator="";
		fields.clear();
	}
	int64		 createTime;
	std::string  content;
	std::string  detailUrl;
	std::string  title;
	std::string  toUsers;
	std::string  status;
	std::string  statColor;
	std::string  titleColor;
	std::string  type;
	std::string  titleBGColor;
	std::string  creator;
	std::map<std::string,std::string>fields;
};
///网页消息
class MsgWeb : public Msg
{
public:
	MsgWeb()
	{
		msgType = MSG_TYPE_WEB;
		title.resize(MSGMEMSIZE);
		url.resize(MSGMEMSIZE);
		img.resize(MSGMEMSIZE);
		desc.resize(MSGMEMSIZE*2);
	}
	MsgWeb(Msg& msg) :Msg(msg)
	{
		msgType = MSG_TYPE_WEB;
	}
	~MsgWeb(){}
	bool operator == (const MsgWeb& rhs) const
	{
		return (title == rhs.title) && (url == rhs.url) && (img == rhs.img) && (desc == rhs.desc);
	}

	std::string title;	 ///<网页内容标题
	std::string url;	 ///<网页链接地址
	std::string img;	 ///<网页内容第一张图片
	std::string desc;	 ///<网页内容摘要
};
///回执消息
class MsgRevoke : public Msg 
{
public:
	MsgRevoke() :revokeMsgId(0)
	{ 
		msgType = MSG_TYPE_REVOKE; 
	}
	MsgRevoke(Msg& msg) :Msg(msg),revokeMsgId(0)
	{
		msgType = MSG_TYPE_REVOKE;
	}
	~MsgRevoke(){}

	bool operator == (const MsgRevoke& rhs) const 
	{
		if (revokeMsgId != rhs.revokeMsgId)
			return false;

		return true;
	}
public:
	int64 revokeMsgId;///<id
};

class MsgCard : public Msg
{
public:
	MsgCard() :isDelay(false), delayTime(0), isReceipt(false)
	{
		msgType = MSG_TYPE_CARD;
		mediaUrl.resize(MSGMEMSIZE*2);
	}
	MsgCard(Msg& msg) :Msg(msg), isDelay(false), delayTime(0), isReceipt(false)
	{
		msgType = MSG_TYPE_CARD;
	}
	~MsgCard(){}

	bool isDelay;			///<是否延迟消息
	int64 delayTime;        ///<延迟时间
	bool isReceipt;			///<是否阅后回执
	std::string mediaUrl;	///<名片url
};

///动态表情
class MsgDynExpression : public Msg 
{
public:
	MsgDynExpression()
	{ 
		msgType = MSG_TYPE_DYNEXPRESSION; 
	}
	MsgDynExpression(Msg& msg) :Msg(msg)
	{
		msgType = MSG_TYPE_DYNEXPRESSION;
	}
	~MsgDynExpression(){}
};

///音频消息
class MsgAudio :public Msg{
public:
	MsgAudio() :mediaTime(0), status(0), isOld(false), validity(0){
		msgType = MSG_TYPE_AUDIO;
		fileName.resize(MSGMEMSIZE);
		meidaUrl.resize(MSGMEMSIZE);
		encryptKey.resize(MSGMEMSIZE);
		localPath.resize(MSGMEMSIZE);
	}
	MsgAudio(Msg& msg) :Msg(msg), mediaTime(0), status(0), isOld(false), validity(0){
		msgType = MSG_TYPE_AUDIO;
	}
	bool operator == (const MsgAudio& rhs) const
	{
		return (mediaTime == rhs.mediaTime) && (fileName == rhs.fileName) && (meidaUrl == rhs.meidaUrl) && (status == rhs.status);
	}
	~MsgAudio(){};

	int32 mediaTime;			///<时长
	std::string fileName;    ///<文件名
	std::string meidaUrl;      ///<路径
	std::string encryptKey;///<加密KEY
	int status;    ///<ui层用，标志是否需要显示小红点 0、不需要 1、需要 
	std::string localPath;		//音频本地路径 
	int64       validity;      ///附件有效期

	bool isOld;      ///<是否是老的消息(非一步发送)
};

///组合消息
class MsgCombine :public Msg{
public:
	MsgCombine(){
		msgType = MSG_TYPE_COMBINE;
	}
	~MsgCombine(){}
	std::vector<CSharedPtr<data::Msg> > mVt_msg;	
};

class MsgMiniVedio : public Msg{
public:
	MsgMiniVedio() :buddyId(0), brustFlag(0), vedioHight(0), vedioLenth(0), vedioWideth(0), vedioSize(0), validity(0){
		msgType = MSG_TYPE_MINIVEDIO;
		preImgPath.resize(MSGMEMSIZE);
		vedioFileName.resize(MSGMEMSIZE);
		localPreImgPath.resize(MSGMEMSIZE);
		localVedioPath.resize(MSGMEMSIZE);
		encryptKey.resize(MSGMEMSIZE);
	}
	int64 buddyId;					///< 接收人ID
	int8 brustFlag;					///< 是否阅后即焚
	std::string preImgPath;			///< 预览图片服务器地址  一步发送消息时不赋值
	std::string vedioFileName;		///< 视频服务器地址	 一步发送消息时不赋值
	std::string localPreImgPath;	///< 本地预览图片路径 一步发送消息时使用
	std::string localVedioPath;		///< 本地视频路径	一步发送消息时使用
	int64 vedioHight;				///< 视频分辨率高
	int64 vedioLenth;				///< 视频长, （毫秒）
	int64 vedioWideth;				///< 视频分比率宽
	int64 vedioSize;				///< 视频大小（Byte）
	std::string encryptKey;         ///<加密KEY
	int32       docID;              ///< 是否加密
	int64       validity;           ///<附件有效期
};

//////延时消息///////////
class DelayMsg: public Msg
{
public:
	DelayMsg(): deal(true),delayTime(0)
	{}

	~DelayMsg(){}
	bool deal;
	int64 delayTime;
};

///9图消息
class MsgNineBlock :public Msg{
public:
	MsgNineBlock():validity(0){
		msgType = MSG_TYPE_NINEBLOCK;
	}
	std::vector<data::MsgImg> nine;
	int64   validity; ///附件有效期
};

/////消息推送//////////////////////////
class MsgStatus{
public:
	MsgStatus():err(0),msgtype(0),targetid(0),msgtime(0),localid(0)
	{ 
	    path="";
	}
	~MsgStatus(){}
    int   err;
    int   msgtype;
    int64 targetid;
    int64 msgtime;
    int64  localid;   
    std::string path;
};
///下载文件消息//////////////
class DownLoadFile{
public:
	DownLoadFile():bisP2P(false),bIsResume(false),msgid(0),targetId(0),
	localId(0),fromUserId(0){
	   fileName = localPath = url = encryptKey = "";
    }
	~DownLoadFile(){}
	bool        bisP2P;	        ///< 是否接收局域网直传文件.
	bool        bIsResume;      ///<是否断点续传下载
	int64		msgid;			///<文件的消息ID
	int64		targetId;		///<个人文件为发送者用户ID，群文件为群ID
	int64		localId;		///<标示文件的唯一localId
	int64		fromUserId;		///<发送者ID，个人文件时和targetId相同	
	std::string fileName;		//文件名
	std::string localPath;		///<本地保存地址
	std::string url;			///<服务器地址
	std::string encryptKey;     ///<加密KEy
};

///公众号菜单
struct AppMenuData{
	AppMenuData(){
		key = sub_menu = name = url = type = "";
		appId = 0;
		hasSubMenu = false;
	}
	std::string type;
	std::string name;
	std::string sub_menu;
	int64 appId;
	std::string url;
	std::string key;
	bool hasSubMenu;
};

///消息查询
struct  MsgSearchProperty 
{
	MsgSearchProperty() :msgtype(2), count(0), targetid(0), start_time(0), end_time(0)
	{}
	int msgtype; ///<消息类型 当前只支持2文本
	int count;   ///<消息数量
	/**
	* 　targetId为用户Id或群Id，与count字段共同决定搜索的方式，有以下几种组合：
	*   targetId !=0, count = 1:搜索指定的targetId的聊天记录数目。
	* 　targetId = 0,count > 1: 从最小的targetId开始向上搜索记录，共搜索到count个匹配的targetId为止。
	*   targetId !=0, count >1: 从指定的targetId开始向上搜索记录，共搜索到count个匹配的targetId为止。
	*   count = 0为匹配全部消息，最多匹配10000条
	*/
	int64 targetid;
	int64 start_time;///<开始时间
	int64 end_time;  ///<结束时间  起始和结束时间全部为0代表搜索全部时间段
};

///查询结构体
struct SimpleSearchInfo
{
	SimpleSearchInfo() :flag(0){}
	int8  flag;			///<0x01男，0x02女, 0x08为群，0x10, 0 非男非女为保密
	std::string name;	///<目标名称
	std::string avatar;	///<目标头像
	std::string avatarUrl;
};

///消息查询结果
struct  MsgSearchResult
{
	MsgSearchResult() :nextTargetId(0)
	{}
	struct info
	{
		info() :count(0), targetId(0){}
		int64 targetId;			///<搜索到对象的targetId
		int count;			    ///<消息数量
		SimpleSearchInfo simpleInfo; 
	};

	std::vector<info> infos;  ///<搜索到的消息信息集合
	int64 nextTargetId;	    ///<后续查找的targetId，0代表已搜索全部消息
};

struct MsgDetailSearchProperty
{
	MsgDetailSearchProperty() :msgtype(2), messageId(0), targetid(0), count(0), start_time(0), end_time(0)
	{}
	int msgtype;	///<消息类型 当前只支持2文本
	int64 targetid; ///<目标Id
	int messageId;  ///<起始msgId，0为从最早的消息就行搜索
	int count;		///<一次匹配到最大的消息数量,0为匹配全部消息,最多匹配100000条
	int64 start_time;///<开始时间
	int64 end_time;  ///<结束时间  起始和结束时间全部为0代表搜索全部时间段
};

struct  MsgDetailSearchResult
{
	MsgDetailSearchResult() :nextMsgId(0){}
	int64 nextMsgId;  ///<后续查找的消息ID，0代表已搜索全部消息
	std::map<int64, SimpleSearchInfo> senderInfos; ///<存放此次搜索结果中的所有发送者信息,key为senderUserId
	std::vector<CSharedPtr<data::Msg> > msgs; ///<保存所有消息内容信息
};
}