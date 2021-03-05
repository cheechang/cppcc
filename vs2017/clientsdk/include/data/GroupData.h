#pragma once 
#include <string>
#include "interface/Defines.h"
#include "data/Optional.h"
#include "data/UserData.h"
namespace data{
	///群组信息
	class TinyGroup
	{
	public:
		TinyGroup() :level(0), type(0), createrId(0), cantExit(true), groupId(0)
		{}
		virtual ~TinyGroup(){}
		virtual void init(){}

		bool operator == (const TinyGroup& rhs) const
		{
			return (level == rhs.level) && (cantExit == rhs.cantExit) && (createrId == rhs.createrId) &&
				(groupId == rhs.groupId) && (groupName == rhs.groupName) && (avatar == rhs.avatar) &&
				(pinyin == rhs.pinyin) && (server == rhs.server) && (avatarUrl == rhs.avatarUrl);
		}
		bool operator > (const TinyGroup& rhs) const
		{
			return pinyin.value()>rhs.pinyin.value();
		}
	public:
		Optional<int> level;				///<群等级（1,2,3,4)1是临时群，2是普通群
		Optional<int> type;					///<群类型（1,2)1是组织群，2是企业群
		Optional<bool> cantExit;			///<是否允许退群
		Optional<bool> isVSign;				///<是否为v标群
		Optional<int64> createrId;			///<创建者ID
		Optional<int64> groupId;			///<群ID
		Optional<std::string> groupName;	///<群名
		Optional<std::string> avatar;		///<群头像
		Optional<std::string> avatarUrl;	///<群头像url
		Optional<std::string> pinyin;		///<名称拼音
		Optional<std::string> server;		///<服务器
		Optional<std::string> groupType;	///<群分类
	};
	///群组
	class Group 
	{
	public:
		Group() :createTime(0), relatedGroupId(0), relatedEntId(0), memberNums(0), isSearch(false),
			groupMessageContentMode(0)
		{}
		bool operator == (const Group &rhs) const
		{
			return (brief == rhs.brief) && (bulletin == rhs.bulletin) && (extend == rhs.extend) && 
				(createTime == rhs.createTime) && (relatedGroupId == rhs.relatedGroupId) &&
				(relatedEntId == rhs.relatedEntId) && (memberNums == rhs.memberNums) &&
				(isSearch == rhs.isSearch) && (groupMessageContentMode == rhs.groupMessageContentMode) &&
				(privateMsgPwd == rhs.privateMsgPwd) && (info == rhs.info);
		}
	public:
		Optional<std::string> brief;			///<群简介
		Optional<std::string> bulletin;			///<群公告
		Optional<std::string> extend;			///<群扩展字段
		Optional<int64> createTime;				///<创建时间
		Optional<int64> relatedGroupId;			///<关联群ID
		Optional<int64> relatedEntId;			///<关联企业ID，存在此ID则属于企业群
		Optional<int> memberNums;				///<群成员数量
		Optional<bool> isSearch;				///<是否允许被搜索
		Optional<int8> groupMessageContentMode; ///<群消息通知详情: 1、开启(显示详情)  2、关闭(显示通知源，隐藏内容)  默认开启 groupMessageContentMode.
		Optional<int8> personalMessageContentMode; ///<个人群消息通知详情: 1、通知详情  2、通知源，隐藏内容  3、完全隐藏
		Optional<std::string> privateMsgPwd;	///<私信密码 
		Optional<std::string> chatImage;		///<群聊背景 
		Optional<TinyGroup> info;				///<群信息
	};

	///群更新
	class GroupUpdate
	{
	public:
		GroupUpdate() :groupSearch(0), groupMessageContentMode(0)
		{}

		Optional<std::string> groupName;				///<群名称
		Optional<std::string> groupIcon;				///<群图标
		Optional<std::string> groupBrief;				///<群简介
		Optional<std::string> groupBulletin;			///<群公告
		Optional<std::string> groupBackgroundURL;		///<群背景图片
		Optional<int8> groupSearch;						///<群是否可以被外部检索 1可以 2不可以
		Optional<int8> groupMessageContentMode;			///<群消息通知详情: 1、开启(显示详情)  2、关闭(显示通知源，隐藏内容)  默认开启
		/**群扩展字段,以json形式,目前：
		* 警种ID： policeTypeID
		* 地域---省份ID：provinceID
		* 地域---市ID： cityID
		* 私信模式：privateMsg：1为开启私信   0表示不允许私信
		*/
		Optional<std::string> extendProperties;
	};
	///群成员
	class Member : public UserData 
	{
	public:
		Member() :groupId(0), team(0), memberType(0), isApp(false)
		{}
		virtual void init(){}

		bool operator == (const Member& rhs) const
		{
			return (groupId == rhs.groupId) && (team == rhs.team) && (isApp == rhs.isApp) &&
				(memberType == rhs.memberType) && (remark == rhs.remark);
		}
	public:
		Optional<int64> groupId;		///<群id
		Optional<int>  team;			///<分组
		Optional<int8> memberType;		///<成员类型：1.普通 2.管理员 3.超级管理员
		Optional<bool> isApp;			///<是否为机器人
		Optional<std::string> remark;   ///<群备注
		Optional<std::string> pingyin;			///<拼音
		Optional<std::string> sector;
	};

	///群文件
	class FileInfo
	{
	public:
		FileInfo() : fileid(0), userid(0), time(0)
		{}
		
		int64 fileid;				///<文件id
		int64 userid;				///<上传者id
		std::string size;			///<文件大小
		int64 time;					///<上传时间
		std::string name;			///<文件名
		std::string auther;			///<上传者
		std::string url;			///<文件url
		std::string path;			///<文件本地路径
		std::string encrypt_key;	///<加密KEY
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
		std::string filename;
		int64 filesize;
	};
}