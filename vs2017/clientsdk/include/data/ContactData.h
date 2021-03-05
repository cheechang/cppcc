#pragma  once
#include "data/UserData.h"
#include <vector>
namespace data{
	///联系人
	class Contact : public UserData 
	{
	public:
		Contact() :isStar(0), isApp(0), birthday(0), isHidden(0)
		{}

		void init(){}

		bool operator == (const Contact & rhs) const
		{
			return (isStar == rhs.isStar) && (isApp == rhs.isApp) && (pinyin == rhs.pinyin) && 
				(acountName == rhs.acountName) && (remark == rhs.remark) && (server == rhs.server) && 
				(birthday == rhs.birthday) && (emails == rhs.emails) && (phones == rhs.phones) &&
				(chatImg == rhs.chatImg) && (privateMsgPwd == rhs.privateMsgPwd) &&
				(sign == rhs.sign) && (area == rhs.area) && (isHidden == rhs.isHidden);
		}

	public:
		Optional<int8> isStar;					 ///<星标好友：1.星标好友，2.不是星标
		Optional<int8> isApp;					 ///<是否是应用 1.是,  2.否
		Optional<int8> isHidden;				 ///<是否是隐藏好友 1.是,  2.否
		Optional<bool> isTop;					 ///<是否置顶
		Optional<std::string> pinyin;			 ///<名称拼音
		Optional<std::string> acountName;		 ///<豆豆账号
		Optional<std::string> remark;			 ///<备注
		Optional<std::string> server;			 ///<服务器
		Optional<int64> birthday;				 ///<生日
		Optional<std::string> chatImg;			 ///<聊天背景
		Optional<std::string> sign;				///<签名
		Optional<std::string> area;				///<地区
		Optional<std::string> privateMsgPwd;	 ///<私信秘钥
		Optional<std::vector<std::string> > emails;	 ///<邮件
		Optional<std::vector<std::string> > phones;	 ///<电话
		Optional<std::string> mydevice; ///我的设备
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
	///好友验证方式返回
	struct ContactVerifyType
	{
		ContactVerifyType() :userid(0), type(0)
		{}
		int64 userid;
		int8  type;   ///<验证类型1需要验证信息:2:不允许任何人添加,3:允许任何人添加
	};

	struct EnterpriseDictionary{
		int32 id;                ///<组织ID
		int32 parentId;          ///<父组织ID
		std::string dicValue;    ///<字段的名字
		std::string dickey;      ///<字段的键值
		std::string dicRealValue;///扩展字段对应的真实值
		/** 扩展字段，格式为{"isEdit":0,"isFriend":0,"isInput":0,"isLogin":0,"isShow":0,"isStrange":0},*/
		bool isEdit;//:是否客户端可编辑;
		bool isFriend;//:客户端是否好友可见;
		bool isInput;//:是否必填字段;
		bool isLogin;//:是否登录项字段;
		bool isShow;//:客户端组织架构是否可见;
		bool isStrange;//:客户端是否陌生人可见*/
		std::string extend; 
	};

	class EnterpriseAccount : public Contact
	{
	};
}