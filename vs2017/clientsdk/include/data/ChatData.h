#pragma once
#include <string>
#include <vector>
#include <map>
#include "interface/Defines.h"
#include "data/UserData.h"
namespace data{

	#define  SYSMSG_ID   10000
	const int64  MSGMEMSIZE = 256;


	///������Ϣ
	struct SnapshotInfo
	{
		int64 msgId;			//��ϢID
		int64 snapshotId;		//Ⱥ����ID
	};
	struct MsgUnreadCounter
	{
		int64 messageId;
		int32 unreadCount;
		///�����Ϣδ����
		int32 maxUnreadCount;
		///Ⱥ����ID
		int64 snapshotId;
	};

	///��������
	enum ChatType
	{
		CHAT_INIT=0,
		BUDDY_CHAT = 1,        ///<��������
		GROUP_CHAT = 2,        ///<Ⱥ������
		APP_CHAT = 3,		   ///<���ں�
		SYSTEM_MSG = 4,        ///<ϵͳ��Ϣ
		STRANGER_CHAT = 5,     ///<İ��������
		ENT_USER_CHAT = 6,     ///<��ҵ��Ա����
		PHONE_CHAT = 7,        ///<�ҵ��豸
		ENT_CHAT,				///<��ҵ��
		APPLICATION_CHAT,		///<Ӧ�ú�
	};
	enum MSGTYPE{
		MSG_TYPE_TEXT = 2,			///<�ı���Ϣ
		MSG_TYPE_AUDIO,				///<������Ϣ
		MSG_TYPE_POSITION,			///<λ����Ϣ
		MSG_TYPE_IMG,				///<ͼƬ��Ϣ
		MSG_TYPE_FILE,				///<�ļ���Ϣ
		MSG_TYPE_CARD,				///<��Ƭ��Ϣ
		MSG_TYPE_TIP,				///<����ʾ��Ϣ
		MSG_TYPE_WEB,				///<��ҳ������Ϣ
		MSG_TYPE_PICTEXT = 12,		///<ͼ����Ϣ
		MSG_TYPE_COMBINE,           ///<�����Ϣ
		MSG_TYPE_REVOKE = 18,		///<��ִ��Ϣ
		MSG_TYPE_DYNEXPRESSION,		///<��̬������Ϣ
		MSG_TYPE_VOICE = 16,///<���l��Ϣ
		MSG_TYPE_VIDEIO = 14,///<ҕ�l��Ϣ
		MSG_TYPE_CONFER = 15,///<ҕ�l������Ϣ
		MSG_TYPE_TASK = 17,///<������Ϣ
		MSG_TYPE_TEMPL = 26,    ///<ģ����Ϣ
		MSG_TYPE_MINIVEDIO= 89,///<΢��Ƶ��Ϣ
		MSG_TYPE_NINEBLOCK = 28,///<9ͼ��Ϣ
		MSG_TYPE_DYNEXPRESSION2 = 27, ///<�¶�̬����
		MSG_TYPE_MAIL = 31, ///<�ʼ���Ϣ
		MSG_TYPE_UNREADSTATE = 34, ///<δ��״̬��Ϣ
		MSG_TYPE_UNIVERSAL = 64,   ///<������Ϣ�����忴subMsgType
		MSG_TYPE_REDPACKET = 88,///<�����Ϣ
		MSG_TYPE_SYS = 100,	///<ϵͳ��Ϣ
	};
	
	///��Ϣ������
	enum SubMessageType
	{
		sub_groupAnnouncement = 1,     //Ⱥ��������msgType64����Ϣ��subMsgtype=1
		sub_buddyApply = 201,				//��������֪ͨ
		sub_agreeBuddyApply = 202,			//ͬ���������֪ͨ
		sub_rejectBuddyApply = 203,			//�ܾ���������֪ͨ
		sub_groupApply = 301,				//������Ⱥ
		sub_adminAgreeGroupAplly = 302,     //����Աͬ����Ⱥ
		sub_adminRejectGroupAplly = 303,    //����Ա�ܾ���Ⱥ
		sub_inviteEnterGroup = 401,			//������Ⱥ
		sub_agreeEnterGroup = 402,			//�û�ͬ����Ⱥ
		sub_rejectEnterGroup = 403,        //�û��ܾ���Ⱥ
		sub_adminKickMember = 501,			//����Ա�߳�Ⱥ��Ա
		sub_dissolveGroup = 503,			//��ɢȺ
		sub_groupMemberExit = 504,         //Ⱥ��Ա�˳�
	};
	///��Ϣ״̬
	enum MSGSTATE
	{
		MSG_TYPEX_UPLOAD_FAILED = 0x100,	///< ������Դʧ��
		MSG_TYPEX_SEND_ERROR = 0x200,		///< ������Ϣʧ��
		MSG_TYPEX_DOWNLOAD_FAILED = 0x400,  ///< ����ʧ��
		MSG_TYPEX_SENDING = 0x1000,			///< ���ڷ�����Ϣ
		MSG_TYPEX_UPLOADING = 0x2000,		///< �����ϴ�����
	};

	enum TIPTYPE
	{
		MSG_TYPE_CHICK = 1, ///��ë��
		MSG_TYPE_TIP_READED = 10,   ///�Ѷ�
		MSG_TYPE_TIP_NOREAD = 11     
	};
	
   ///�Ự�б���Ϣ
  class ChatData:public UserData{
 public:
	 ChatData() :operType(0), msgType(0), chatType(0), realUnReadCnt(0), msgTime(0), sendUserId(0), lastMsgId(0), msgProp(""), lastMsg(""), lastAtMsgID(0), unReadCnt(0){}
	  ~ChatData(){}
  public:
	  int		   operType;          ///<�����
	  int          msgType;		     ///<��Ϣ����;1��HTML, 2:TEXT, 3��AUDIO, 4��POSITION, 5��IMG, 6��FILE, 7��CARD,  8��TIP
	  int		   chatType;	         ///<��������  1�ˣ�2Ⱥ��3���ںţ�4��ҵ��
	  int32        realUnReadCnt;     ///< ������δ����Ϣ���� = unReadCnt+����ʾ��Ϣ����+������ͬ�����豸��Ϣ�������ͻ���ÿ����ȡδ��������ֶΣ���realUnReadCntΪ0ʱ����ʾ������Ϣ�ڵ�ǰ�豸�ͻ��˶��Ѿ�������
	  int32		   unReadCnt;		//δ����Ϣ��
	  int64		   msgTime;           ///<��Ϣʱ��
	  int64        sendUserId;	     ///< ������Id
	  int64		   lastMsgId;        ///���һ����ϢID
	  std::string  msgProp;		     ///<��Ϣ����
	  std::string  lastMsg;           ///<���һ����Ϣ
	  int64 lastAtMsgID;	  ///<���һ��@��ϢID
	  int subType;          ///<�Ӳ������ͱ�ʾ,�ö�����������
	  int8 disturbSet;		///<����� 1Ϊ��������, 2��ʾ�����ѽ���ʾ����, 3Ϊ�����
	  int8 msgRemindMode;
  };

  ///////����Ự
  class ChatInfo{
     public:
	 ChatInfo():isStartChat(false),unreadcount(0),chatType(CHAT_INIT),targetid(0),msgid(0),msgtime(0){
		 name = avatar =lastMsg= "";
		 isStartChat = false;
		 unreadcount = 0;
	 }
    ~ChatInfo(){};
	 public:
	  bool        isStartChat;		 //�Ƿ��Ƿ���Ự
	  int         unreadcount;		 //δ����
	  int64		  targetid;			 ///Ŀ��id
	  int64       msgid;             ///���һ����ϢID
	  int64       msgtime;           ///��Ϣʱ��
	  ChatType    chatType;	         ///<��������  1�ˣ�2Ⱥ��3���ںţ�4��ҵ
	  std::string lastMsg;          ///���һ����Ϣ����
	  std::string name;				///����
	  std::string avatar;			// ͷ��
  };

  
///��Ϣ����
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
	int16 unReadCount;		///<δ������
	int16 maxUnReadCount;     ///<���δ������
	int64 snapshotId;		///<Ⱥ����ID
	int subType;	///< ��Ϣ������
	std::string msgProperties;		///<��Ϣ����
	std::string userName;///<�û��� �����Ϣ��ϵͳ����Ϣʹ��
	std::string userPic;///<�û�ͷ�� �����Ϣ��ϵͳ��Ϣʹ�� Ⱥϵͳ��Ϣʱ��ΪȺͷ�� 

	bool  isBurn;			///<�Ƿ����ĺ󼴷���Ϣ
	bool  isRbtMsg;         ///<�Ƿ��ǻ�������Ϣ
	bool  isDelay;			///<�Ƿ��ӳ���Ϣ
	bool  isReceipt;		///<�Ƿ��ĺ��ִ
	bool  isReceiptAll;		///<��Ϣ�Ƕ�һ�����ĺ��ִ���Ҵ���Ϣ�������Ӣ��С�ں�<��β��
    bool  isDeviceMsg;		/// �Ƿ����豸ͬ����Ϣ
	bool  isRecvMsg;	    /// �Ƿ��ǽ�����Ϣ
	bool  isGroup;          
	bool  isUser;
    int8  status;           ///��Ϣ״̬
	int8  deviceType;       ///�豸����
	int8 isPrivateMsg;		///<�Ƿ���˽��   0���� 1��
	int   msgType;			///<��Ϣ����
	int64 delayTime;        ///<�ӳ�ʱ��
	int64 msgId;			///<��ϢID
	int64 targetId;			///<�Ự��ID��Ⱥ���û��ȣ�
	int64 localId;			///<����ID
	int64 fromId;			///<������ID
	int64 toId;				///<������ID
	int64 relatedMsgId;		///<������ϢID
	int64 lastMsgId;		///<��һ����ϢID
	int64 time;				///<��Ϣ���͵�ʱ��
	int64 userId;			///�û�id
	std::string body;		///<��Ϣ���� limitRange
	std::vector<int64> relatedUsers; ///<@��Ա�б�
	std::vector<int64> limitRange;
	std::string context;//�Ự��ʾ����
	int  isFeather;  //��ë��0. ���Ǽ�ë�� 1����ʾԭʼ��Ϣ 10��ʾ�Ѷ� 11��ʾδ���ѷ��Ͷ���
	int UpFileFlag;   //�ϴ��ļ���־  0�����ϴ�   1���ϴ�
	int EraserType; //��Ƥ����Ϣ 0������Ƥ����Ϣ 1:ɾ���������Ϣ 2��ɾ��ȫ������Ϣ
};  
  ///�ı���Ϣ
class MsgText : public Msg 
{
public:
	MsgText()
	{ 
		msgType = MSG_TYPE_TEXT; 
	}
	~MsgText(){}
};
//������Ϣ
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

//ͼƬ��Ϣ
class MsgImg: public Msg{
public:
	MsgImg():width(0),height(0),docID(0)
	{ 
	    thumbUrl=mainUrl=thumbPath=mainPath=encryptKey=fileName=imageContents=thumBbinary="";
		msgType = MSG_TYPE_IMG; 
	}
	~MsgImg(){}
	int width;				///<ͼ����
	int height;				///<ͼ��߶�
	int32  docID;       	///�Ƿ����
	std::string thumbUrl;	///<����ͼURL һ��������Ϣʱ����ֵ
	std::string mainUrl;	///<��ͼURL  һ��������Ϣʱ����ֵ
	std::string thumbPath;	///<����ͼ���ص�ַ һ��������Ϣʱʹ��
	std::string mainPath;	///<��ͼ���ص�ַ һ��������Ϣʱʹ��
	std::string encryptKey;///<����KEY
	std::string fileName;   ///<�ļ���  
	std::string imageContents;///<ͼƬ����
	std::string thumBbinary;  ///����ͼ������
};
//�ļ���Ϣ
class MsgFile: public Msg{
public:
	MsgFile():isSaveAs(false),isResume(false),isFolder(0),states(0),docID(0),size(0),fileId(0)
	{ 
		msgType = MSG_TYPE_FILE; 
		fileName = filePath = encryptKey = url="";
	}
	~MsgFile(){}

    bool  isSaveAs;			///�Ƿ������Ϊ�ļ�
	bool  isResume;			///<�Ƿ�ϵ��ϴ�(һ������Ϣʱʹ��)
	int8  isFolder;			///<�Ƿ����ļ��� 0,���� 1,��
	int   states;           ///<�ļ�״̬
	int32 docID;			///�Ƿ����
	int64 size;				///<�ļ���С  
	int64 fileId;			///<�ļ�ID
	std::string fileName;	///<�ļ���  
	std::string filePath;	///<�ļ�����·��  
	std::string encryptKey; ///<����KEY
	std::string url;	    ///<�ļ�URL	 һ��������Ϣʱ����ֵ
};

//����ʾ��Ϣ
class MsgTip : public Msg 
{
public:
	MsgTip() :tipType(0), operType(0)
	{ 
		msgType = MSG_TYPE_TIP; 
	    tipTime=operUser=userInfo=fileInfo="";
	}
	~MsgTip(){}
	int tipType; ///<tip ����
	int operType;///<��������
	std::string tipTime;///<ʱ��
	std::string operUser;///<����userId
	std::string userInfo;///<�û���Ϣ
	std::string fileInfo;///<�ļ���Ϣ
};

//ͼ����Ϣ
class MsgPicWithText :public Msg{
public:
	///ͼ����Ϣ
	struct picTextBean{
		picTextBean():index(0){
			picUrl = title = url = dsc;
		}
		int32 index;
		std::string picUrl;///<ͼƬurl
		std::string title;///<����
		std::string url;///<url
		std::string dsc;///<����
	};
	MsgPicWithText(){
		msgType = MSG_TYPE_PICTEXT;
	}
	~MsgPicWithText(){}
	 std::vector<picTextBean> vtPtBean;///<��Ϣ����
};
//ģ����Ϣ
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
///��ҳ��Ϣ
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

	std::string title;	 ///<��ҳ���ݱ���
	std::string url;	 ///<��ҳ���ӵ�ַ
	std::string img;	 ///<��ҳ���ݵ�һ��ͼƬ
	std::string desc;	 ///<��ҳ����ժҪ
};
///��ִ��Ϣ
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

	bool isDelay;			///<�Ƿ��ӳ���Ϣ
	int64 delayTime;        ///<�ӳ�ʱ��
	bool isReceipt;			///<�Ƿ��ĺ��ִ
	std::string mediaUrl;	///<��Ƭurl
};

///��̬����
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

///��Ƶ��Ϣ
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

	int32 mediaTime;			///<ʱ��
	std::string fileName;    ///<�ļ���
	std::string meidaUrl;      ///<·��
	std::string encryptKey;///<����KEY
	int status;    ///<ui���ã���־�Ƿ���Ҫ��ʾС��� 0������Ҫ 1����Ҫ 
	std::string localPath;		//��Ƶ����·�� 
	int64       validity;      ///������Ч��

	bool isOld;      ///<�Ƿ����ϵ���Ϣ(��һ������)
};

///�����Ϣ
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
	int64 buddyId;					///< ������ID
	int8 brustFlag;					///< �Ƿ��ĺ󼴷�
	std::string preImgPath;			///< Ԥ��ͼƬ��������ַ  һ��������Ϣʱ����ֵ
	std::string vedioFileName;		///< ��Ƶ��������ַ	 һ��������Ϣʱ����ֵ
	std::string localPreImgPath;	///< ����Ԥ��ͼƬ·�� һ��������Ϣʱʹ��
	std::string localVedioPath;		///< ������Ƶ·��	һ��������Ϣʱʹ��
	int64 vedioHight;				///< ��Ƶ�ֱ��ʸ�
	int64 vedioLenth;				///< ��Ƶ��, �����룩
	int64 vedioWideth;				///< ��Ƶ�ֱ��ʿ�
	int64 vedioSize;				///< ��Ƶ��С��Byte��
	std::string encryptKey;         ///<����KEY
	int32       docID;              ///< �Ƿ����
	int64       validity;           ///<������Ч��
};

//////��ʱ��Ϣ///////////
class DelayMsg: public Msg
{
public:
	DelayMsg(): deal(true),delayTime(0)
	{}

	~DelayMsg(){}
	bool deal;
	int64 delayTime;
};

///9ͼ��Ϣ
class MsgNineBlock :public Msg{
public:
	MsgNineBlock():validity(0){
		msgType = MSG_TYPE_NINEBLOCK;
	}
	std::vector<data::MsgImg> nine;
	int64   validity; ///������Ч��
};

/////��Ϣ����//////////////////////////
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
///�����ļ���Ϣ//////////////
class DownLoadFile{
public:
	DownLoadFile():bisP2P(false),bIsResume(false),msgid(0),targetId(0),
	localId(0),fromUserId(0){
	   fileName = localPath = url = encryptKey = "";
    }
	~DownLoadFile(){}
	bool        bisP2P;	        ///< �Ƿ���վ�����ֱ���ļ�.
	bool        bIsResume;      ///<�Ƿ�ϵ���������
	int64		msgid;			///<�ļ�����ϢID
	int64		targetId;		///<�����ļ�Ϊ�������û�ID��Ⱥ�ļ�ΪȺID
	int64		localId;		///<��ʾ�ļ���ΨһlocalId
	int64		fromUserId;		///<������ID�������ļ�ʱ��targetId��ͬ	
	std::string fileName;		//�ļ���
	std::string localPath;		///<���ر����ַ
	std::string url;			///<��������ַ
	std::string encryptKey;     ///<����KEy
};

///���ںŲ˵�
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

///��Ϣ��ѯ
struct  MsgSearchProperty 
{
	MsgSearchProperty() :msgtype(2), count(0), targetid(0), start_time(0), end_time(0)
	{}
	int msgtype; ///<��Ϣ���� ��ǰֻ֧��2�ı�
	int count;   ///<��Ϣ����
	/**
	* ��targetIdΪ�û�Id��ȺId����count�ֶι�ͬ���������ķ�ʽ�������¼�����ϣ�
	*   targetId !=0, count = 1:����ָ����targetId�������¼��Ŀ��
	* ��targetId = 0,count > 1: ����С��targetId��ʼ����������¼����������count��ƥ���targetIdΪֹ��
	*   targetId !=0, count >1: ��ָ����targetId��ʼ����������¼����������count��ƥ���targetIdΪֹ��
	*   count = 0Ϊƥ��ȫ����Ϣ�����ƥ��10000��
	*/
	int64 targetid;
	int64 start_time;///<��ʼʱ��
	int64 end_time;  ///<����ʱ��  ��ʼ�ͽ���ʱ��ȫ��Ϊ0��������ȫ��ʱ���
};

///��ѯ�ṹ��
struct SimpleSearchInfo
{
	SimpleSearchInfo() :flag(0){}
	int8  flag;			///<0x01�У�0x02Ů, 0x08ΪȺ��0x10, 0 ���з�ŮΪ����
	std::string name;	///<Ŀ������
	std::string avatar;	///<Ŀ��ͷ��
	std::string avatarUrl;
};

///��Ϣ��ѯ���
struct  MsgSearchResult
{
	MsgSearchResult() :nextTargetId(0)
	{}
	struct info
	{
		info() :count(0), targetId(0){}
		int64 targetId;			///<�����������targetId
		int count;			    ///<��Ϣ����
		SimpleSearchInfo simpleInfo; 
	};

	std::vector<info> infos;  ///<����������Ϣ��Ϣ����
	int64 nextTargetId;	    ///<�������ҵ�targetId��0����������ȫ����Ϣ
};

struct MsgDetailSearchProperty
{
	MsgDetailSearchProperty() :msgtype(2), messageId(0), targetid(0), count(0), start_time(0), end_time(0)
	{}
	int msgtype;	///<��Ϣ���� ��ǰֻ֧��2�ı�
	int64 targetid; ///<Ŀ��Id
	int messageId;  ///<��ʼmsgId��0Ϊ���������Ϣ��������
	int count;		///<һ��ƥ�䵽������Ϣ����,0Ϊƥ��ȫ����Ϣ,���ƥ��100000��
	int64 start_time;///<��ʼʱ��
	int64 end_time;  ///<����ʱ��  ��ʼ�ͽ���ʱ��ȫ��Ϊ0��������ȫ��ʱ���
};

struct  MsgDetailSearchResult
{
	MsgDetailSearchResult() :nextMsgId(0){}
	int64 nextMsgId;  ///<�������ҵ���ϢID��0����������ȫ����Ϣ
	std::map<int64, SimpleSearchInfo> senderInfos; ///<��Ŵ˴���������е����з�������Ϣ,keyΪsenderUserId
	std::vector<CSharedPtr<data::Msg> > msgs; ///<����������Ϣ������Ϣ
};
}