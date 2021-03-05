#pragma once
#include "User.h"
#include "Msg.h"
#include "TinyGroup.h"
#include <vector>
#include <string>
#include <map>

namespace model
{ 
class Msg;
struct AppInfo
{
	AppInfo() :deviceType(1)
	{}	
	std::string appVersion;		//应用版本号，如"1.5.0"  *必须设置
	int deviceType;				//设备类型 1：PC；2：手机；3：pad；4：网页  *必须设置
	std::string deviceInfo;		//设备信息 如"pc-windows"  *必须设置
	std::string appName;		//应用信息 需与应用名保持一致 *必须设置
	std::string netType;		//网络信息 如"wifi"  可选
	std::string mac;			//mac地址  windows,mac,linux平台会自动获取，其它平台需手动设置
	std::string mark;			//应用标示 可选
};

///用户设置
struct UserSetting
{
	UserSetting() :isonline(0), issearchbybean(0), issearchbyphone(0), issearchbymail(0),
					isshareupdate(0), isnewmsgtip(0), ismultiservmsgtip(0), ismultiservfrdtip(0), 
					ismultiservpersontip(0)
	{
	}

	int8 isonline;				///<否显示在线信息 0显示 1不显示 默认0
	int8 issearchbybean;		///<豆豆号查找  0允许 1不允许 默认0
	int8 issearchbyphone;		///<手机号查找  0允许 1不允许 默认0
	int8 issearchbymail;		///<邮箱号查找 0允许 1不允许 默认0
	int8 issearchbynewfriend;	/// 通过新朋友查找  0允许 1不允许 默认0
	int8 isshareupdate;			///<分享更新   0提示更新 1不提示更新 默认0
	int8 isnewmsgtip;			///<新消息通知是否提醒0提醒 1不提醒 默认0
	int8 ismultiservmsgtip;		///<多服务新消息通知是否提醒0不始终提示 1始终提示 默认0
	int8 ismultiservfrdtip;		///<多服务设置V标好友始终提醒 0不始终提示 1始终提示 默认
	int8 ismultiservpersontip;	///<多服务设置设置@相关人始终提醒0不始终提示 1始终提示 默认0
};

///本地配置条目
struct LocalSetting
{
	LocalSetting(){}
	LocalSetting(const std::string &k, const std::string &v) :key(k), val(v)
	{}
	std::string key; ///<标识
	std::string val; ///<值
};

///个人配置项
struct PersonalData
{
	PersonalData(){}
	PersonalData(int16 t, int16 v) :type(t), val(v)
	{}
	int16 type; ///<标识
	int16 val; ///<值
};
///好友验证方式返回
struct ContactVerifyType
{
	ContactVerifyType() :userid(0), type(0)
	{}
	int64 userid;
	int8  type;   ///<验证类型1需要验证信息:2:不允许任何人添加,3:允许任何人添加
};
///在线状态
struct  OnlineState
{
	OnlineState() :userID(0), connectID(0), deviceType(0), flag(0)
	{}
	int64 userID;   ///<用户ID
	int64 connectID;
	int8 deviceType;  ///<在线设备类型  1：PC；2：手机；3：pad；4：网页
	int8 flag;        ///<在线状态 -1：离线，1:在线；2 : 隐身, 3 : 忙碌, 4 : 离开, 5 : 请勿打扰, 6 : 想聊天
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
	std::vector<SSharedPtr<Msg> > msgs; ///<保存所有消息内容信息
};

struct UploadShareImageProperty
{
	std::string thumbImg;		///< 缩略图
	std::string srcImg;			///< 原图
	std::string encryptkey;		///< 加密秘钥
	std::string loginfoPath;	///< 登录信息保存路径
};

///< 上传文件附件类型(对应UploadFileProperty中的type, 只上传文件，不发送文件消息时使用)
enum UploadType
{
	eFileType_app = 10020,	
};

struct UploadFileProperty
{
	UploadFileProperty() :isP2p(0), isJS(0), localid(0), targetid(0), type(0), noStore(0),isResume(false){}
	int64 targetid;			///<对方的targetId(人或群)
	int64 localid;			///<标示文件的唯一localId 通过time()生成
	int16 type;				///<附件类型
	std::string localPath;	///<上传文件的本地路径
	std::string dirPath;	///<文件夹本地路径，上传文件夹时使用
	std::string msg;		///<用于存储自定义信息
	std::string encryptKey; ///<秘钥  ///断点上传的key必须一致
	int8  isP2p;            ///<是否点对点 0 否， 1 是.
	int8   isJS;             ///< 是否JS上传图片,0 否， 1 是
	int8	  noStore;		///< 是否不存消息和文件信息到数据库0 否， 1 是
	bool  isResume;         ///<是否断点上传 
};

struct DownloadFileProperty
{
	DownloadFileProperty() :bisP2P(false), bIsResume(true), localId(0), fromUserId(0), threadCount(1){}
	int64 msgid;				///<文件的消息ID
	int64 targetId;				///<个人文件为发送者用户ID，群文件为群ID
	int64 localId;				///<标示文件的唯一localId
	int64 fromUserId;			///<发送者ID，个人文件时和targetId相同	
	std::string fileName;		// 文件名
	std::string localPath;		///<本地保存地址
	std::string url;			///<服务器地址
	std::string encryptKey;      ///<加密KEY
	bool        bisP2P;	 ///< 是否接收局域网直传文件.
	bool        bIsResume;///<是否断点续传下载
	int			threadCount;	///< 下载的线程数量 bIsResume为true且threadCount>1时生效 最大允许5个线程
};

struct Fileinfo
{
	Fileinfo() :fileid(0), userid(0), targetid(0), size(0), time(0)
	{}
	int64 fileid;                 ///<文件ID
	int64 userid;                 ///<发送者ID
	int64 targetid;               ///<目标ID,可以是群,也可以是用户
	int64 size;                   ///<文件大小
	int64 time;                   ///<上传时间
	std::string path;             ///<本地路径
	std::string name;             ///<文件名
	std::string url;              ///<文件url
	std::string encrypt_key;      ///<加密KEY
};

struct OfflineMsg
{
	OfflineMsg() :offline_type(0), count(0)
	{}
	int offline_type;  ///<1未读消息 2设备已读消息
	int count;      ///<数量
	SSharedPtr<model::Msg> msg;
};

struct stupdateInfo
{
	/*该字段决定预登陆是否该缓存升级服务器的安装包;
	0，代表不缓存，返回给客户端运维服务器的安装包下载地址;
	1，代表预登陆缓存到本地，返回给客户端本地服务器的安装包下载地址
	*/
	std::string nocache;
	std::string url;///<升级服务器安装包下载地址
	std::string descr;///<安装包描述信息
	std::string fileSize;    ///<安装包大小
	std::string signCode;///<安装包签名
	std::string htmlDowmload;///<是否 当前下载包给web端
	std::string ext;///<透传信息
};

///版本升级信息
struct UpgradeInfo
{
	std::string hasCode;	///< 升级包的HAXI值
	int8 gradeType;			///< 升级类型 0建议升级,1强制升级 gradeType.
	std::string version;    ///< 服务器版本号 version.
	std::string updateAddr; ///< 升级的地址
	std::vector<stupdateInfo> upAddr;///<新预登录信息
	std::string desc;		///< 升级描述信息
	std::string clientInfo; ///< 客户端信息
};


/// 企业信息(搜索中使用)

struct EntInfo
{
	EntInfo() :
	enterpriseID(0){}

	int64 enterpriseID;         ///< 企业ID enterpriseID.
	std::string fullName;       ///< 企业全称 fullName.
	std::string shortName;      ///< 企业简称 shortName.
	std::string keyWords;       ///< 企业关键字 keyWords.
	std::string phone;          ///< 企业电话 phone.
};


struct OrGroupinfo
{
	OrGroupinfo() :
	groupid(0),
	orderid(0){}

	int64    groupid;
	int32    orderid;
	std::string groupname;
	std::string orgname;
};


/**
* \struct st_orgUserinfo
* \brief  组织用户信息（搜索中使用）
*/
struct OrgUserinfo
{
	OrgUserinfo() :
	userid(0){}

	int64   userid; 	                        ///< 用户ID      userid.
	std::string name;                           ///< 用户名称 	 name.
	//std::vector<std::string>  phonenumbers;     ///< 电话号码清单 phonenumbers.
	//std::vector<std::string>  emails;           ///< 电子邮件清单 emails.
	std::string orgname;                        ///< orgname 组织名称.
	std::string userHead;                        ///< 头像.
};


/**
* \struct st_entAppinfo
* \brief 应用信息
*/
struct  EntAppinfo
{
	std::string appSign;///< 应用标识
	std::string appName;///< 应用名称
	std::string appIcon;///< 应用图标
	std::string appIconUrl; ///服务器应用图标全路径
	int64 appID;        ///< 应用ID
	std::string appHomeUrl;///< 应用主页
	int64 entID;           ///< entID
	std::string entName;   ///< 应用名称
	std::map<std::string, std::string>  configItems; ///< 客户端配置
	std::string appSecret; ///< 应用密钥
	std::string appToken;  ///< 应用TOKEN
	std::string appMenus;  ///< 应用菜单
	int8	openIDEncoded; ///< openID是否编码，0:不编码，1:编码
	std::string subAccount;///< 应用子账号
	///子类型  1 H5应用，2 移动应用
	int8 appSubType;
	///推荐 1 是 ，2 否
	int8 recommend;
	/// 默认安装 1 是 ，2 否
	int8 defaultInstall;
	///扩展字段 json 格式，mainUrl H5首页，adminUrl 后台管理地址，myUrl 个人中心地址
	std::string extend;
	///设备类型 1(iPhone_E), 2(iPad_E), 3(iPhone), 4(iPad), 5(androidPhone), 6(androidPad)
	std::string deviceTypes;
	///消息历史地址
	std::string messageHistoryUrl;
	///是否启用自定义菜单   1 启用  0停用
	std::string menuOpen;
	///是否启用自定义菜单响应事件  1启用 0停用
	std::string replyMenuOpen;
	///智能开关 2
	int8 appType;
	///公众号状态
	int8 status;
	///1:订阅号2：企业号
	int8 subOrAppType;
	///应用功能介绍
	std::string appFunctintroduce;
	///公众号介绍
	std::string appDescription;
	///公众号创建者id  可能是appid也可能是userid
	int64 ownerId;
	///应用是否需要强制授权1需要，0不需要
	int8 forceGrant;
	///授权介绍
	std::string grantIntroduce;
};

struct SearchResult
{
	std::vector<model::User> users;
	std::vector<model::TinyGroup> groups;

	std::vector<EntInfo> vtent;     	            ///< 企业列表 vtent.
	std::vector<OrGroupinfo> vtOrgroup;     	    ///< 企业组织列表 vtOrgroup.
	std::map<std::string, std::vector<OrgUserinfo> > mporgUser;///< 组织用户列表 vtorgUser
	std::vector<EntAppinfo> vtEntApp;       	    ///< 企业应用列表 vtEntApp

};

struct QueryMarketApplication{

	QueryMarketApplication() :pageNum(0), pageSize(0), deviceType(0), userID(0){}

	int32 pageNum;                 ///<页码
	int32 pageSize;                ///<页长
	int32 deviceType;              ///<类型 2（IOS），3（Android）
	int64 userID;                 ///<用户ID，预留类型，暂时不用输入
	std::string appName;  ///<应用名称 模糊查询用


};
///查询标签
struct queryTag
{
	int32 key;
	std::string value;
};
///应用市场信息
struct SmallMarketAppInfo
{
	SmallMarketAppInfo() :appID(0), entID(0), ownerId(0), status(0), appType(0), defaultInstall(0), showInMy(0){}
	int64 appID;                   ///<应用ID
	int64 entID;                   ///<企业ID
	int64 ownerId;                 ///<所有者id
	int8 status;                   ///<状态 1启用，2停用，3删除
	int8 appType;                  ///<类型：1(H5应用), 2(IOS应用), 3(Android应用), 4(内部应用), 5(快捷应用)
	int8 defaultInstall;            ///<默认安装 1 是 ，2 否
	int8 showInMy;                 ///<个人安全中心是否展示 1 是 ，2 否
	std::string appSign;            ///<应用标识
	std::string appName;            ///<应用名称
	std::string appIcon;            ///<应用图标		
	std::string appFunctintroduce;   ///<应用功能介绍
	std::string version;            ///<版本号	
	std::string mainUrl;            ///<H5首页
	std::string adminUrl;           ///<后台管理地址
	std::string myUrl;              ///<个人中心地址
	std::string packageName;         ///<包名
	std::string downloadUrl;         ///<下载地址
	std::string urlScheme;           ///<urlScheme
	std::string quickUrl;            ///<快捷应用地址
	std::string extend;              ///<扩展字段
	std::string activityName;         ///<activity
	std::vector<queryTag> tags; ///< 查询标签
	int8 sourceType;               ///< 应用来源 1：后台管理应用 2：开放平台应用
	int64 vestAppID;               ///< 应用对应的应用号id 
	int64 appTypeID;               ///< 应用分类id
	std::string appTypeName;       ///< 应用分类名称
};
///应用市场分页查询
struct SmallMarketAppPage{
	SmallMarketAppPage() : pageNum(0), pageSize(0), count(0), totalPage(0)
	{
		appInfoList.clear();
	}
	int32 pageNum;                               ///<页码
	int32 pageSize;                              ///<页长
	int32 count;                                 ///<总数
	int32 totalPage;                             ///<总页数
	std::vector<SmallMarketAppInfo> appInfoList;  ///<应用列表
};

struct EnterpriseDictionary
{
	int32 id;                ///<组织ID
	int32 parentId;          ///<父组织ID
	std::string dicValue;    ///<字段的名字
	std::string dickey;      ///<字段的键值
	/** 扩展字段，格式为{"isEdit":0,"isFriend":0,"isInput":0,"isLogin":0,"isShow":0,"isStrange":0},
	isEdit:是否客户端可编辑;
	isFriend:客户端是否好友可见;
	isInput:是否必填字段;
	isLogin:是否登录项字段;
	isShow:客户端组织架构是否可见;
	isStrange:客户端是否陌生人可见*/
	std::string extend;      
};

///通讯录
class  PhoneBookContact
{
public:
	PhoneBookContact() :source(0)
	{}

public:
	std::string contactNum;   ///<联系人号码
	std::string name;         ///<联系人姓名
	int8 source;              ///<数据来源 1：手机通讯录； 2：qq好友；
    int8 area;                ///<号码归属地 1：国内； 2：国际；
};

///本地通讯录
class  localPhoneBook
{
public:
	localPhoneBook() :userId(0), flag(0)
	{}

public:
	std::string phone;   ///<联系人号码
	int64 userId;         ///<联系人ID
	int8 flag;            ///<标示
	std::string phoneName; ///<手机通讯录里的名称
	std::string userName; ///< 用户名称
	std::string userHead; ///< 用户头像
};

///上传通讯录后的推荐者
class RecommendContact
{
public:
	RecommendContact() :isBuddy(0){}
	PhoneBookContact pbContact;	//上传的联系人
	User contact;				//联系人信息
	User recommend;				//推荐者信息
	int8 isBuddy;               ///< 是否是好友标识，1表示是好友关系，2表示不是好友关系, 3表示等待验证
};

struct transferLocalData{
	transferLocalData() :version("0.0.1"), year(0), mon(0), day(0){};
	std::string filePath;///<要导入或导出文件的存放路径 

	std::string version;///<当前0.0.1
	/**导出时选择从那天开始 */
	int year;
	int mon;
	int day;
	int8 type;///<0:导出;1:导入;2:南京数据迁移
};

///p2p传文件请求
struct P2pSendFileReq
{
	P2pSendFileReq() :fileType(0), fileSize(0), fileSign(0), sendUserID(0){}
	int8        fileType; ///1:文件, 2:目录
	std::string fileName; ///文件名称
	int64       fileSize; ///文件大小
	/**
	* 发送文件的标识,响应的时候需要回传回去
	*/
	int64       fileSign; ///发送标识
	int64       sendUserID;///发送者ID
};

///p2p对象
struct p2pUser
{
	p2pUser() :userid(0), flag(0){}
	int64 userid; ///<用户ID
	int8  flag; ///<PC 0x01，移动 0x02
};

struct downloadFileInfo {
	downloadFileInfo() {
		fileType = 1;
		size = 0;
		finished = 0;
	}

	int8   fileType; /* 1:文件, 2:文件夹 */
	int64  size;    /* 当前文件大小, http上传时是总分片数 */
	int64  finished; /* 完成量, http上传时是已上传的分片数 */
	std::string   remotePath; /* 远端路径 */
	std::string   localPath;  /* 本地路径 */
};
//子账号信息
struct SubServerInfo 
{
	SubServerInfo() :userId(0), type(0){}
	std::string  addr;		///< 服务器地址
	int64        userId;	///< 用户ＩＤ
	std::string  name;		///< 登录账号名称
	std::string  avatar;	///< 头像
	std::string  account;	///< 账号
	std::string remark;		///< 备注
	int8         type;		///< 账号类型
};
 struct upMsgCt {
	upMsgCt() :type(0){}
	int8 type;
	std::string PackName;///<包名
	std::string UserName;///<用户名
	std::string MsgNum;///<消息数
	std::string devtype;///<设备类型
};

 ///敏感词
 struct BadWord
 {
	 BadWord() : badWordType(0){}
	 int8 badWordType;     ///< 0不过滤 1使用*号 2禁止发送
	 std::vector<std::string> badWordList;   ///< 敏感词列表
 };
 struct reqEntAppInfo{
	 reqEntAppInfo() :pageNum(0), pageSize(0), type(0){}
	 int8  type;             ///< 1.企业号 2.应用号
	 int32 pageNum;          ///< 页码
	 int32 pageSize;         ///< 每页大小
 };

 struct oauthReq{
	 std::string appID;            ///< 应用ID
	 std::string userID;           ///< 用户ID
	 std::string accountType;      ///< 账户类型
	 Optional< std::string> account; ///< 账户
	 Optional< std::string> password;///< 密码
 };

 struct qVerifyCodes
 {
	 qVerifyCodes() :type(0), isSetUserIDs(false){}
	 Optional<int8> type;  ///< 类型 1.根据用户ID向用户发送短信(只根据语言发送，不处理内容)
	 std::vector<int64> userIDs; ///< 用户ID集合
	 bool               isSetUserIDs;
 };
 struct AuthUserBean 
 {
	 AuthUserBean() :userID(0), sex(0), year(0), month(0), day(0)
	 {
		 name = "";
		 area = "";
		 school = "";
		 portraitURL = "";
		 phoneNums.clear();
		 emails.clear();
	 }
	 int64 userID;                              ///用户ID
	 std::string name;                          ///用户名
	 int8 sex;                                  ///性别
	 std::string area;                          ///区域
	 int16  year;                               ///生日
	 int8   month;
	 int8   day;
	 std::string school;                        ///毕业学校
	 std::string portraitURL;                   ///头像地址
	 std::vector<std::string> phoneNums;        ///电话号码清单
	 std::vector<std::string> emails;           ///邮箱清单
 };


 /*******************cloudService begin***********************/

 //云盘上传信息
 struct CloudUploadFileInfo
 {
	 CloudUploadFileInfo() : pid(0),fileSize(0), isResume(false)
	 {}
	 int64 pid;						//云盘父目录id 如果没有父目录，传0。
	 std::string fileCode;			///< 云盘父目录code
	 int64 fileSize;					//文件大小
	 int64 localId;					//唯一标识ID
	 std::string encryptKey;		//加密key
	 std::string  localPath;		///<本地文件地址
	 bool	isResume;				///<是否支持断点续传
 };


//云盘添加文件信息
 struct CloudAddFileInfo
 {
	 CloudAddFileInfo() : pid(0), ownerId(0), encryptFileSize(0),
						 fileSize(0), fileType(0), fileId(0)
	 {}
	 int64 pid;						//云盘父目录id 如果没有父目录，传0。
	 int64 ownerId;					//拥有者id
	 int64 uploaderId;				//上传者id
	 std::string uploaderName;		//上传者名字
	 int64 encryptFileSize;			//加密文件大小
	 int64 fileId;					//文件ID
	 std::string fileCode;			//文件code
	 std::string fileName;			//文件名
	 std::string filePath;			//文件路径
	 std::string fileRemark;		//文件备注
	 std::string fileClass;			//文件分类
	 int64 fileSize;					//文件大小
	 std::string fileSuffix;		//文件后缀名
	 int8 fileType;					//类型 1.文件  2.文件夹  3.团队文件夹  4 特殊文件夹
	 std::string md5Hash;			//md5码	
	 std::string encryptKey;		//加密key
 };

 //云盘文件信息
 struct CloudFileInfo : public CloudAddFileInfo
 {
	 CloudFileInfo() : createTime(0), updateTime(0),image(false),validity(0)
	 {}
	 int64 createTime;				//创建时间
	 int64 updateTime;				//更新时间
	 bool image;					//是否为图片
	 int64 validity;					//有效性 天
     int64 roleId;
 };

 struct TeamMemberInfo
 {
	 TeamMemberInfo() :fileId(0), createTime(0), updateTime(0), userId(0), roleId(0)
	 {}
	 int64 fileId;			//文件信息
	 std::string headImg;	//头像
	 int64 createTime;		//创建时间
	 int64 updateTime;		//上传时间
	 int64 userId;			//用户id
	 std::string userName;  //用户名
	 int64 roleId;	
	 std::string roleName;	
 };

 struct BaseRoleInfo
 {
	 BaseRoleInfo() :isShow(0), orderNum(0), totalSize(0), uploadSize(0)
	 {}
	 int8 isShow;
	 std::string name;	
	 int64 orderNum;		
	 std::string permission;
	 int64 totalSize;
	 int64 uploadSize;
 };

 struct CloudRoleInfo : public BaseRoleInfo
 {
	 CloudRoleInfo() :createTime(0), roleId(0), roleType(0), status(0), updatedTime(0)
	 {}
	 int64 createTime;	
	 int64 roleId;
	 int8 roleType;
	 int8 status;
	 int64 updatedTime;
 };

 struct CloudPermission
 {
	 CloudPermission() :isCreateTeam(0), isDelete(0), isDownLoad(0), isManager(0),
	 isReName(0), isRead(0), isUpload(0), roleId(0), totalSize(0), uploadSize(0)
	 {
	 }
	 int8 isCreateTeam;
	 int8 isDelete;
	 int8 isDownLoad;
	 int8 isManager;
	 int8 isReName;
	 int8 isRead;
	 int8 isUpload;
	 int64 roleId;
	 int64 totalSize;
	 int64 uploadSize;
 };

 struct smallMarketAppType
 {
	 smallMarketAppType() :appTypeID(0){}
	 int64 appTypeID;         ///< 应用分类id
	 std::string appTypeName; ///< 应用分类名称
 
 };
 

 /*******************cloudService end***********************/

  //日志文件头信息
 struct LogHeadTag
 {
	 int64 id;							
	 std::string project;				
	 std::string deviceType;			
	 std::string os;					
	 std::string osVersion;				
	 std::string appVersion;			
	 std::string sdkVersion;			
	 std::string netType;				
 };
 
 struct getReqAtMsg{
	 getReqAtMsg() :groupID(0), beginTime(0), endTime(0), maxCount(0), atType(0){}

	 int64    groupID;           ///< 群ID
	 int64    beginTime;         ///< 起始时间
	 int64    endTime;           ///< 结束时间
	 int32    maxCount;          ///< 最大返回的消息数量,消息排序按时间倒叙排列。
	 int8     atType;            ///< 0.别人@我，1.我@别人
 };

 struct UserContact
 {
	 UserContact() :type(0), status(0)
	 {}
	 int8 type;			///< 账号类型 1.电话号码 3.email 4.userID 6.accountName
	 std::string name;	///< 帐号名称
	 int8 status;		///< 状态 1.启用， 2.禁用, 5.锁定, 6.冻结 
 };

 ///获取邀请码参数
 struct InviteCodeParam
 {
	 InviteCodeParam() :createUserID(0), digit(0), effectiveSeconds(0), effectiveCount(0){}
	 
	 int64 createUserID;			///< 生成邀请码的用户的userid
	 int32 digit;					///< 生成邀请的位数
	 int64 effectiveSeconds;		///< 有效秒数（默认一个月） 
	 int32 effectiveCount;			///< 有效次数（默认无数次）
	 std::vector<UserContact> consumeAccount; ///< 有效账号 不传时默认任何账号都能使用
 };

 ///意见反馈
 struct IssueFeedBack
 {
	 IssueFeedBack() :id(0), questionID(0), isNecessary(0), operatingSystem(0), feedbackPersonID(0){}
	 ///< 主键ID,可不用设置
	 int id;
	 ///< 问题ID(1：崩溃；2：掉线；3：卡顿；4：其他问题；5：改进建议)
	 int questionID;
	 ///< 问题名称
	 std::string questionName;
	 ///< 问题描述
	 std::string questionDescription;
	 ///< 是否必现 1：是；2：否
	 int8 isNecessary;
	 ///< 操作系统 1:安卓、2:IOS、3:Windows、4:MAC、5:网页
	 int8 operatingSystem;
	 std::string clientVersion;
	 int64 feedbackPersonID;
	 std::string feedbackPersonName;
	 std::string feedbackPersonOrg;
	 ///< 提交时间
	 std::string createDate;
	 ///< 反馈截图 最多四张,以英文分号;隔开
	 std::string screenPic;
	 ///< 日志地址
	 std::string logUrl;
	 ///操作系统版本
	 std::string operatingSystemVersion;
 };

 ///工作台轮播图实体 返回类型  
 struct WorkbenchBanner
 {
     WorkbenchBanner() : type(0), displayStatus(0), sortNum(0), createTime(0), updateTime(0)
     {}
     std::string id;
     std::string title;         ///< 标题 
     std::string cover;         ///< 封面  只支持jpg、png 
     int32 type;                ///< 类型  1：外链，2:非外链 
     ///< 显示状态  1：显示，2：隐藏. 
     int32 displayStatus;
	 std::string linkUrl;		// 外链地址
     ///< 地址（外链-完整路径；非外-存轮播图详情页的相对地址. 
     std::string detailUrl;
     ///< 富文本内容. 
     std::string content;
     ///< 排序 
     int32 sortNum;     
     int64 createTime;          ///< 创建时间 
     int64 updateTime;          ///< 更新时间 
 };

 ///帮助系统信息 返回类型  
 struct HelpSystemInfo
 {
     HelpSystemInfo() : id(0), parentId(0), helpType(0), linkType(0),
     displayStatus(0), sortNum(0), createTime(0), updateTime(0), status(0)
     {}
     int64 id;               ///< 帮助ID 
     std::string title;      ///< 标题 
     int64 parentId;         ///< 父帮助ID 
     int32 helpType;         ///< 帮助类型 
     int32 linkType;         ///< 外链类型 
     int32 displayStatus;    ///< 显示状态 
     std::string linkUrl;    ///< 外链地址 
     std::string detailUrl;  ///< 细节地址 
     std::string content;    ///< 富文本内容  
     int32 sortNum;          ///< 排序 
     int64 createTime;       ///< 创建时间 
     int64 updateTime;       ///< 更新时间 
     int32 status;           ///< 状态 
 };
 struct ZXSearchParam
 {
     std::string sector;                 ///< 界别
     std::string name;                   ///< 名称
     std::string nation;                 ///< 民族
     std::string gender;                 ///< 性别
     std::string currentPosition;        ///< 职务
     std::string group;                  ///< 组别
     std::string specialCommittee;       ///< 专委会
     std::string specialCommitteeDuty;   ///< 专委会职务
     std::string CPPCCPosition;          ///< 政协职务
     std::string myLocation;             ///< 所在地
	 int8		 isWhite;				 ///< 是否白名单
 };

 struct ZxFavorite
 {
	 int64 favoriteId;		//收藏id
	 int64 groupId;			//*群组id
	 int64 favoUserId;		//收藏人id
	 std::string favoUserName;//收藏人名称 
	 int64 messageUserId;	//*发送人id
	 std::string messageUserName;//*发送人名称 
	 std::string message;	//*收藏内容json字符串 
	 int8 messageType;		//*收藏内容类型包括:文件夹、文件、视频、音乐、等
	 int64 SDKID;			//sdkid
	 std::string sourceID;	//*陌生人单聊时的来源ID，1_groupID表示传的群ID，2_orgID表示传的组织ID
	 std::string title;		//*文件标题,如果是文本,把文本信息直接添加到这个字段
	 std::string favoTime;	//*收藏时间
 };

 struct ZxFavoriteSearchParam
 {
	 int32 pageIndex;
	 int32 pageSize;
	 int64 groupId;
	 int64 favoUserId;
	 std::string title;
 };


 struct ZxTopInformation
 {
	 ZxTopInformation() : id(0), createUserId(0), groupId(0),
		 createTime(0), topUserId(0), updataTime(0), status(0), topType(0), msgId(0)
	 {}
	 int64 id;
	 int64 createUserId;   //置顶人 
	 int64 groupId;        //置顶群ID 
	 int64 createTime;     //置顶时间 
	 int64 topUserId;      //被置顶人 
	 std::string topContent;  //置顶内容 
	 int64 updataTime;     //修改时间 
	 int8 status;        //置顶消息状态 
	 int8 topType;       //置顶消息类型
	 int64 msgId;		 //置顶消息号
 };

} /*namespace service*/
