#pragma once
#include <string>
#include "interface/Defines.h"
#include "data/Optional.h"
namespace data{
	class UserBasicData{
	public:
		UserBasicData():classification(0),id(0),name(""),thumbAvatar(""){
		}
		Optional<int64> id;						///<id
		Optional<std::string> name;				   ///<名称
		Optional<std::string> thumbAvatar;	       ///<缩略图
		int classification;                          ///<密级
		Optional<std::string> extends;			///<扩展字段
	};
  class UserData{
  public:
	  UserData():gender(0),timeZone(0),id(0),name(""),avatar(""),extends(""),thumbAvatar(""),avatarUrl(""),thumbAvatarUrl(""){
	  }
	  virtual ~UserData(){}
  public:
	  Optional<int> gender;					    ///<性别:1男2女0保密
	  Optional<int> timeZone;					///<时区
	  Optional<int64> id;						///<id
	  Optional<std::string> name;				///<名称
	  Optional<std::string> avatar;			    ///<原图图像
	  Optional<std::string> extends;			///<扩展字段
	  Optional<std::string> entExtends;        ///<企业扩展信息
	  Optional<std::string> thumbAvatar;		///<缩略图
	  Optional<std::string> avatarUrl;		    ///<原图url
	  Optional<std::string> thumbAvatarUrl;	    ///<缩略图url
  };

  ///账号信息
  class AccountInfo:public UserData 
  {
  public:
	  AccountInfo():nickId(""),phone(""),email(""),entExtends(""){}
  public:
	  Optional<std::string> nickId;			     ///<豆豆号
	  Optional<std::string> phone;              ///<手机号
	  Optional<std::string> email;              ///<邮箱号
	  Optional<std::string> entExtends;         ///<企业扩展信息
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

  ///本地配置条目
struct UserLocalSetting
{
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

  struct UserInfoSetData
  {
	  UserInfoSetData():isSearchByDoodNum(0),isSearchByPhoneNum(0),isSearchByMailNum(0){}
	  int8 isSearchByDoodNum;       ///通过豆豆号查找
	  int8 isSearchByPhoneNum;      ///通过电话号查找
	  int8 isSearchByMailNum;       ///通过邮箱查找
	  //  int8 issearchbynewfriend;	/// 通过新朋友查找  0允许 1不允许 默认0
	  //  int8 isshareupdate;			///<分享更新   0提示更新 1不提示更新 默认0
	  //  int8 isnewmsgtip;			///<新消息通知是否提醒0提醒 1不提醒 默认0
	  //  int8 ismultiservmsgtip;		///<多服务新消息通知是否提醒0不始终提示 1始终提示 默认0
	  //  int8 ismultiservfrdtip;		///<多服务设置V标好友始终提醒 0不始终提示 1始终提示 默认
	  //  int8 ismultiservpersontip;	///<多服务设置设置@相关人始终提醒0不始终提示 1始终提示 默认0
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
  };

  struct ZxTopInformation
  {
	  ZxTopInformation() : id(0), createUserId(0), groupId(0),
	  createTime(0), topUserId(0), updataTime(0), status(0), topType(0)
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
}