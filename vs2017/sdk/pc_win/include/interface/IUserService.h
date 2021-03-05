#pragma once

#include <string>
#include "../model/Account.h"
#include "../model/Packet.h"
#include "../model/Emoticon.h"
#include "IService.h"

#define VER_USER INTERFACE_VERSION(1,0)
static const VRVIID IID_IUserService = { 0x92d87e13, 0x463c, 0x4406, 0x8d, 0xfd, 0x28, 0x1f, 0xe7, 0x45, 0xac, 0xb };

namespace service 
{

class IUserService : public IService
{
public:
		
	virtual ~IUserService(){};

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief 朋友圈消息推送
	* @param[out] cb 注册的推送回调 _1 类型 1:朋友圈消息未读数量 _2 接收内容json串
	*/
	virtual void regCircleOfFriendNotifyCb(SFunction < void(int32, const std::string&) > cb) = 0;
	/**
	* \brief 监听用户头像更新
	* @param[out] cb 注册的推送回调 _1 头像有更新的UserID，联系人或者群   _2 更新的头像文件
	*/
	virtual void regUserHeadImgUpdateCb(SFunction < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 设置监听用户信息更新的回调，服务器推送
	* @param[out] cb 注册的推送回调 _1 用户信息
	*/
	virtual void regOperateUserCb(SFunction< void(Account&) > cb) = 0;

	/**
	* \brief 监听自己用户信息修改，登录更新后会主动推送
	* @param[out] cb 注册的推送回调 _1 用户信息
	*/
	virtual void regGetMyselfCb(SFunction< void(Account&) > cb) = 0;
	

	/*****************************************请求接口*******************************************/


	/**
	* \brief 获取账户信息，同步接口
	* @param[out] info 用户信息
	*/
	virtual void getAccountInfo(Account& info) = 0;


	/**
	* \brief 更新用户信息
	* @param[in] user 传入用户信息
	* @param[out] cb  更新信息结果回调  _1错误信息
	*/
	virtual void updateAccountInfo(Account& user, SFunction<void(ErrorInfo)> cb) = 0;

	
	/**
	* \brief 设置账号设置项
	* @param[in] flag 传入设置项属性
	* @param[in] type 传入设置项类型
	* @param[out] cb  账号设置结果回调 _1 错误信息
	*
	*  type = 1: 设置是否显示在线信息 flag: 0显示 1不显示 默认0
	*  type = 3: 设置豆豆号查找 flag: 0允许 1不允许 默认0
	*  type = 4: 设置手机号查找 flag: 0允许 1不允许 默认0
	*  type = 5: 设置邮箱号查找 flag: 0允许 1不允许 默认0
	*  type = 6: 设置分享更新   flag: 0提示更新 1不提示更新 默认0
	*  type = 7: 新消息通知是否提醒 flag: 0提醒 1不提醒 默认0
	*  type = 12: 多服务新消息通知是否提醒 flag: 0不始终提示 1始终提示 默认0
	*  type = 13: 多服务设置V标好友始终提醒 flag: 0不始终提示 1始终提示 默认0
	*  type = 14: 多服务设置设置@相关人始终提醒 flag: 0不始终提示 1始终提示 默认0
	*  type = 20: 设置新朋友查找 flag: 0允许 1不允许 默认0
	*/
	virtual void setSetting(int8 flag, int type, SFunction<void(ErrorInfo)> cb) = 0;


	/**
	* \brief 获取账号设置项
	* @param[in] type 传入获取的设置项类型
	* type为1，则返回值为value_i64第一位 如果type=0,返回所有字段，每个字段所占的位于type相对应\n
	* @param[out] cb 传入接收结果回调  _1错误信息  _2用户设置
	*/
	virtual void getSetting(int type, SFunction<void(ErrorInfo, UserSetting&)> cb) = 0;


	/**
	* \brief 通过密码获取隐藏对象(好友或群)
	* @param[in] passwd 之前设置过的密码
	* @param[out] cb 传入接收结果回调  _1错误信息  _2返回对象ID合集  _3 true代表存在此密码，false代表不存在
	*/
	virtual void getHiddenTarget(const std::string &passwd, SFunction<void(ErrorInfo, std::vector<int64>&, bool)> cb) = 0;

	/**
	* \brief 设置隐藏对象(好友或群)
	* @param[in] passwd 设置的密码
	* @param[in] hiddenIDs 设置的隐藏对象ID集合
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setHiddenTarget(const std::string &passwd, std::vector<int64>& hiddenIDs, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 删除隐藏对象(好友或群)
	* @param[in] passwd 密码
	* @param[in] hiddenIDs 要删除的对象ID集合
	* @param[out] cb 传入接收结果回调  _1错误信息 
	*/
	virtual void delHiddenTarget(const std::string &passwd, std::vector<int64>& hiddenIDs, SFunction<void(ErrorInfo)> cb) = 0;


	/**
	* \brief 更改隐藏密码
	* @param[in] oldPwd 旧密码
	* @param[in] newPwd 新密码
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void changeHiddenPasswd(const std::string &oldPwd, const std::string &newPwd, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取全局勿扰模式
	* @param[out] cb 传入接收结果回调  _1错误信息 _2起始时间  _3结束时间  _4是否打开
	*/
	virtual void getGlobalNoDisturbMode(SFunction<void(ErrorInfo, int32, int32, bool)> cb) = 0;

	/**
	* \brief 设置全局勿扰模式
	* @param[in] startTime  起始时间
	* @param[in] endTime 结束时间
	* @param[in] isOpen 是否打开
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setGolbalNoDisturbMode(int32 startTime, int32 endTime, bool isOpen, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取针对目标用户的勿扰模式
	* @param[in] targetId  用户ID
	* @param[out] cb 传入接收结果回调  _1错误信息  _2用户ID  _3设置的值:  1为接收提醒 2表示不提醒仅显示数字 3:为免打扰
	*/
	virtual void getUserNoDisturbMode(int64 targetId, SFunction<void(ErrorInfo, int64, int8)> cb) = 0;

	/**
	* \brief 设置针对目标用户的勿扰模式
	* @param[in] targetId  用户ID
	* @param[in] value 设置的值:  1为接收提醒 2表示不提醒仅显示数字 3:为免打扰, 默认1
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setUserNoDisturbMode(int64 targetId, int8 value, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取针对目标消息的通知模式
	* @param[in] targetId  用户ID
	* @param[out] cb 传入接收结果回调  _1错误信息  _2用户ID _3设置的值:  1.通知详情 2.通知源，隐藏内容 3.完全隐藏 
	*/
	virtual void getMsgNotifyMode(int64 targetId, SFunction<void(ErrorInfo, int64, int8)> cb) = 0;

	/**
	* \brief 设置针对目标消息的通知模式
	* @param[in] targetId  用户ID
	* @param[in] value 设置的值:  1.通知详情 2.通知源，隐藏内容 3.完全隐藏  默认开启模式1
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setMsgNotifyMode(int64 targetId, int8 value, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取服务器时间
	* @param[in] cb 传入接收结果回调  _1错误信息   _2服务器时间，单位毫秒
	*/
	virtual void getServerTime(SFunction<void(ErrorInfo, int64)> cb) = 0;
    /**
    * \brief 获取服务器时间(同步接口)
    * @param[out] _1服务器时间，单位毫秒
    */
    virtual bool getServerTimeSync(int64& serverTime) = 0;
	/**
	* \brief 增加本地配置，以键值对方式保存
	* @param[in] items  配置信息集合
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void addLocalSetting(std::vector<LocalSetting> &items, SFunction<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 增加本地配置，以键值对方式保存(同步接口)
	* @param[in] items  配置信息集合
	*/
	virtual bool addLocalSettingSync(std::vector<LocalSetting> &items) = 0;

	/**
	* \brief 获取本地配置
	* @param[in] keys 获取的配置信息的键集合
	* @param[out] cb 传入接收结果回调  _1错误信息  _2获取的配置信息键值对集合
	*/
	virtual void getLocalSetting(std::vector<std::string> &keys, SFunction<void(ErrorInfo, std::vector<LocalSetting>&)> cb) = 0;
	/**
	* \brief 获取本地配置(同步接口)
	* @param[in] keys 获取的配置信息的键集合
	* @param[out] result 返回的配置信息键值对集合
	*/
	virtual bool getLocalSettingSync(std::vector<std::string> &keys, std::vector<LocalSetting> &result) = 0;

	/**
	* \brief 更新本地配置
	* @param[in] newItems 插入的新的配置信息集合
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void updateLocalSetting(std::vector<LocalSetting> &newItems, SFunction<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 更新本地配置(同步接口)
	* @param[in] newItems 插入的新的配置信息集合
	*/
	virtual bool updateLocalSettingSync(std::vector<LocalSetting> &newItems) = 0;

	/**
	* \brief 删除本地配置
	* @param[in] keys 删除的配置信息的键集合
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void deleteLocalSetting(std::vector<std::string> &keys, SFunction<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 删除本地配置(同步接口)
	* @param[in] keys 删除的配置信息的键集合
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual bool deleteLocalSettingSync(std::vector<std::string> &keys) = 0;


	/**
	* \brief 设置个人设置项\n
    * @param[in] items 个人设置项集合
	*		type: 1 生日，２ 电话，３ 邮件 \n
	* 　　　　　　value:  1：所有人可见 2：仅好友可见 3：仅自己可见，默认1\n
	*		type: 4 好友验证方式 \n
	* 　　　　　　value:   1：需要验证信息, 2:不允许任何人添加, 3:允许任何人添加，默认1\n
	*		type: 5 V标好友消息提示模式\n
	*			value: 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1\n
	*		type: 6 @相关人消息提醒模式\n
	*			value: 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1\n
	*		type: 7 全局通知消息内容展现模式\n
	*           value: 1:通知详情，2：通知源，隐藏内容 3:完全隐藏，默认2\n
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setPersonalData(std::vector<PersonalData> items, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取个人设置项
	* @param[out] cb 传入接收结果回调  _1错误信息  _2个人设置项集合
	*/
	virtual void getPersonalData(std::vector<int16> &types, SFunction<void(ErrorInfo, std::vector<PersonalData>&)> cb) = 0;

	/**
	* \brief 通过应用ID获取应用信息
	* @param[in] appId 应用程序ID
	* @param[out] cb 传入接收结果回调  _1错误信息  _2应用信息
	*/
	virtual void getAppInfo(int64 appId, SFunction<void(ErrorInfo, EntAppinfo&)> cb) = 0;
	/**
	* \brief 查询应用市场应用信息
	* @param[in] qData 传入应用市场分页查询条件
	* @param[out] cb 传入接收结果回调  _1错误信息  _2查询到的结果，应用信息列表
	*/
	virtual void queryMarketApplication(QueryMarketApplication& qData, SFunction<void(ErrorInfo, SmallMarketAppPage&)> cb) = 0;
	/**
	* \brief 删除添加应用
	* @param[in] type 传入的查询类型： 2.添加应用  4.删除应用
	* @param[in] appID 操作的appID
	* @param[out] cb 传入接收结果回调  _1错误信息 
	*/
	virtual void addOrDeleteApplication(int8 type, int64 appID, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取已安装的应用
	* @param[in] deviceType: 2.IOS 3.Android
	* @param[out] cb 传入接收结果回调  _1错误信息 _2应用信息列表
	*/
	virtual void getInstalledApplication(int32 deviceType, SFunction<void(ErrorInfo, std::vector<SmallMarketAppInfo>&)> cb) = 0;
	/**
	* \brief 通过标签查询表情包
	* @param[in] label 表情包标签
	* @param[out] cb  传入接收结果回调  _1错误信息 _2查询表情包结果集合
	*/
	virtual void QueryEmoticonPackageByLabel(std::string label, SFunction<void(ErrorInfo, std::vector<EmoticonPackage>&)> cb) = 0;
	/**
	* \brief 单个表情查询、根据表情包标识查询表情，查询用户自定义表情
	* @param[in] type  1, 单个查询表情 md5Code表示单个表情的md5, 6,根据表情包标识查询所有表情 md5Code表示表情包的md5, 7,查询用户所有自定义表情 这里md5Code不传值
	* @param[in] md5   md5值
	* @param[out] cb 传入接收结果回调  _1错误信息 _2查询的表情结果信息
	*/
	virtual void queryEmoticon(int8 type, std::string md5, SFunction<void(ErrorInfo, std::vector<Emoticon>&)> cb) = 0;
	/**
	* \brief 查询单个表情包
	* @param[in] md5   md5值
	* @param[out] cb 传入接收结果回调  _1错误信息 _2查询表情包结果
	*/
	virtual void singleQueryEmoticonPackage(std::string md5, SFunction<void(ErrorInfo, EmoticonPackage&)> cb) = 0;
	/**
	* \brief 分页查询表情包
	* @param[in] pageNum   页码
	* @param[in] pageSize   页长
	* @param[out] cb 传入接收结果回调  _1错误信息 _2返回的分页查询信息
	*/
	virtual void pageQueryEmoticon(int32 pageNum, int32 pageSize, SFunction<void(ErrorInfo, PageQueryEmoticon&)> cb) = 0;
	/**
	* \brief 增删自定义表情
	* @param[in] type   类型  4 增加， 5删除.
	* @param[in] emot   表情
	* @param[out] cb 传入接收结果回调  _1错误信息 _2resultCode _3结果信息 _4操作成功结果列表 _5操作失败结果列表
	*/
	virtual void addOrDeleteCustomEmoticon(int8 type, Emoticon &emot, SFunction<void(ErrorInfo, int32, const std::string&, std::vector<EmoticonResult>&, std::vector<EmoticonResult>&)> cb) = 0;
	/**
	*\brief 查选单个表情包内的单个表情
	*@param[in] packageCode 表情包md5 
	*@param[in] emotCode  表情md5
    * @param[out] cb 传入接收结果回调  _1错误信息 _2查询表情结果
	*/
	virtual void queryEmotionInPackage(std::string packageCode, std::string emotCode, SFunction<void(ErrorInfo, singleEmoticonResult&)>) = 0;
	/**
	* \brief 本地数据导入导出
	* @param[in] req   导入导出数据的路径等参数信息
	* @param[out] cb 传入接收结果回调  _1错误信息 
	* @param[out] pro _1  进度标示 _2进度 _3 已经导入文件数量/导入文件总数量
	*/
	virtual void transLocalData(transferLocalData &req, SFunction<void(ErrorInfo)> cb, SFunction<void(int32, int32, const std::string&)> pro) = 0;
	/**
	* \brief 设置自定义提示音
	* @param[in] userId   用户ID id为0代表设置自己
	* @param[in] voiceName   声音文件
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setUserDefineVoice(int64 userId, const std::string &voiceName, SFunction<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 获取用户自定义提示音
	* @param[in] userId   用户ID id为0代表获取用户自己
	* @param[out] cb 传入接收结果回调  _1错误信息 _2声音文件
	*/
	virtual void getUserDefineVoice(int64 userId, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;
	/**
	* \brief 通过账号名获取用户ID
	* @param[in] accounts   用户accountName集合
	* @param[out] cb 传入接收结果回调  _1错误信息 _2用户ID集合，key为account value为用户ID
	*/
	virtual void getIdByAccount(std::vector<std::string> &accounts, SFunction<void(ErrorInfo, std::map<std::string, int64>&)> cb) = 0;
	/**
	* \brief 设置在线状态
	* @param[in] flag  1:在线,2:隐身,3:忙碌,4:离开,5:请勿打扰
	* @param[out] cb 传入接收结果回调  _1错误信息 
	*/
	virtual void setOnlineState(int8 flag, SFunction<void(ErrorInfo)> cb) = 0;

	/**************IOS专用接口 begin***************/

	/**
	* \brief IOS设置Token
	* @param[in] appleId  需要设置的appleId
	* @param[in] token  需要设置的token
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
    virtual void setToken(const std::string &appleId, const std::string &token, const std::string& cloudToken, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 设置后台在线状态
	* @param[in] vb1  设置云后台在线(true 在线, false 不在线)
	* @param[in] vb2  设置应用在线(true在线)
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setOnlineStatus(bool vb1,bool vb2, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 设置当前人的会话对象ID（中电科）
	* @param[in] targetId  对象的id 聊天对象，用户ID　或　群ID
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setSessionPeerId(int64 targetId, SFunction<void(ErrorInfo)> cb) = 0;
	/**
	* \brief  批量设置token 
		    传入参数：
	*@param[in]  
				 appID: "XiaoMi"  不能为空，必填，小米可填写"XiaoMi"
				 token:token值  
				 deviceType:"0"苹果 "1"华为 "2"小米 "3"中电科EMM  "4"小米
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setTokens(std::string& appId,std::string& token,std::string& deviceType, SFunction<void(ErrorInfo)> cb) = 0;
	/**
	* \brief ios设置是否推送
	* @param[in] isPush 是否推送
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setPushSwitch(bool isPush, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief  ios设置客户端消息未读数量
	* @param[in] count 未读数量
	* @param[in] appleId  应用id，不同的应用所对应的证书是不一样的.
	* @param[in] token  ios token
	* @param[in] entUnread  设置企业未读数 key：企业ID， value:消息未读数
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setUnReadCount(int count, const std::string &appleId, const std::string &token, std::map<std::string, int32> &entUnread, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief  获取用户应用安装天数
	* @param[out] cb 传入接收结果回调  _1错误信息 _2使用天数
	*/
	virtual void getInstallDays(SFunction<void(ErrorInfo, int32)> cb) = 0;
	
	/**
	*\brief 根据用户id分页获取企业号或应用号
	* @param[in] req 分页获取条件（页码，每页大小）
	*@param[out] cb 传入接收结果回调 _1错误信息 _2总数量 _3总页数 _4 获取结果集合
	*/
	virtual void getEntAppInfo(reqEntAppInfo& req,SFunction<void(ErrorInfo, int64, int64, std::vector<model::EntAppinfo>&)> cb) = 0;

	/**
	*\brief 朋友圈接口
	*@Param[in] reqJson 请求json
	*@Param[in] loginfoPath 登录信息保存路径
	*@Param[out] cb 传入接收结果回调 _1错误信息 _2响应json
	*/
	virtual void circleOfFriend(const std::string& reqJson, std::string &loginfoPath, SFunction<void(ErrorInfo, std::string&)> cb) = 0;

	/**
	* \brief 根据用户账号批量获取userID
	*@Param[in] accounts 帐号名称集合 手机号前加0086
	*@Param[in] type   1.电话号码 3.email 4.userID 6.accountName
	*@Param[in] status 状态  1.启用， 2.禁用, 5.锁定, 6.冻结
	*@Param[in] SDKID 服务器ID  vrv服务器传0
	*@Param[out] cb 传入接收结果回调 _1错误信息 _2批量获取结果(key:type+"-"+contactInfo+"-"+SDKID, value:UserID)
	*/
	virtual void queryUserIDByAccount(std::vector<std::string>& accounts, int8 type, int8 status, int64 SDKID, SFunction<void(ErrorInfo, std::map<std::string,int64>&)> cb) = 0;

	/**
	* \brief 新增更新或者删除在线扩展信息，如客户端的ip，mac地址等，内容是客户端自己设定，通过DDIO获取
	*@Param[in] type 4,新增或更新， 5 删除
	*@Param[in] str
	*@Param[out] cb 传入接口结果回调，_1错误信息
	*/
	virtual void operOnlineExt(int8 type, std::string str, SFunction<void(ErrorInfo)> cb) = 0;
	/**
	* \brief 查询在线扩展信息，不需要入参，返回所有设备设置的在线拓展信息
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2批量查询结果，key是devicetype，value是jsonExt
	*/
	virtual void queryOnlineExt(SFunction<void(ErrorInfo, std::map<std::string, std::string>&)> cb) = 0;

    /**
    * \brief 透传JSON格式请求
    *@Param[in] reqJson  请求Json串
    *@Param[in] type    服务类型  1:调用声网服务 2:原生朋友圈 3:原生云盘
    *@Param[out] cb 传入接口结果回调，_1错误信息 _2批量查询结果，key是devicetype，value是jsonExt
    */
    virtual void queryJson(const std::string& reqJson, int8 type, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;
	/**
	* \brief 意见反馈
	*@Param[in] feedBackParam 反馈信息
	*@Param[out] cb 传入接口结果回调，_1错误信息
	*/
	virtual void feedBack(IssueFeedBack &feedBackParam, SFunction<void(ErrorInfo)> cb) = 0;

    /**
    * \brief 获取工作台轮播图
    *@Param[in] cliType 客户端类型   1：Android 2：iOS
    *@Param[out] cb 传入接口结果回调，_1错误信息 _2轮播图结果
    */
    virtual void getWorkBenchBanners(int32 cliType, SFunction<void(ErrorInfo, std::vector<WorkbenchBanner>&)> cb) = 0;

    /**
    * \brief 获取帮助系统信息
    *@Param[in] cliType 客户端类型   1：PC 2:Android 3:iOS
    *@Param[in] parentId 父帮助ID    获取初始信息传0
    *@Param[out] cb 传入接口结果回调，_1错误信息 _2帮助信息结果
    */
    virtual void getHelpSystemInfo(int32 cliType, int64 parentId, SFunction<void(ErrorInfo, std::vector<HelpSystemInfo>&)> cb) = 0;

    /**
    * \brief 政协定制查询接口
    *@Param[in] pageSize 分页大小   
    *@Param[in] page 查询页码    
    *@Param[in] param 查询条件    
    *@Param[out] cb 传入接口结果回调，_1错误信息 _2总页数  _3查询结果
    */
    virtual void cppccSearch(int32 pageSize, int32 page, ZXSearchParam param, SFunction<void(ErrorInfo, int32, std::vector<User>&)> cb) = 0;
	/**
	* \brief 政协定制收藏接口
	*@Param[in] favo 收藏信息（带*的是必填项）
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2错误描述
	*/
	virtual void cppccAddFavorite(ZxFavorite& favo, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;
	/**
	* \brief 政协删除收藏接口
	*@Param[in] favoId 收藏id
	*@Param[in] favoUserId 收藏者id
	*@Param[in] param 查询条件
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2错误描述
	*/
	virtual void cppccDelFavorite(int64 favoId, int64 favoUserId, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;
	/**
	* \brief 政协查询收藏接口
	*@Param[in] param 查询条件
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2总页数 _3总记录数  _4查询结果
	*/
	virtual void cppccSearchFavorite(ZxFavoriteSearchParam& param, SFunction<void(ErrorInfo, int32, int32, std::vector<ZxFavorite>&)> cb) = 0;
	/**
	* \brief 政协消息置顶接口
	*@Param[in] info 置顶消息（见packet.h）
	*@Param[in] type 操作类型  5.新增 6.修改 7.删除  这个type是服务端给出的
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2错误描述
	*/
	virtual void cppccTopInformation(ZxTopInformation info, int type, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;
	/**
	* \brief 政协分页查询置顶消息接口
	*@Param[in] groupId 置顶消息的群ID
	*@Param[in] pageNum 查询页
	*@Param[in] pageSize 单页消息数量
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2总页数 _3总记录数  _4查询结果
	*/
	virtual void cppccGetTopInfo(int64 groupId, int32 pageNum, int32 pageSize, SFunction<void(ErrorInfo, int32, int32, std::vector<ZxTopInformation>&)> cb) = 0;

	/**
	*\brief 获取应用市场应用分类集合
	*@Param[in] filterCondition 过滤条件，暂时没有过滤条件
	*@Param[out]  _1 int64 应用分类id _2 string 应用分类名称
	*/
	//virtual void getMarketAppSort(std::map<std::string, std::string> &filterCondition, SFunction<void(ErrorInfo, std::vector<smallMarketAppType>&)> cb) = 0;
	/**************IOS专用接口 end***************/

	/**************安卓专用接口 begin***************/
    /**
    *\brief 安卓事件通知
    *@Param[out]  cb 传入接收结果回调 _1错误信息
    */
	virtual void wakeUp(SFunction<void(ErrorInfo)> cb) = 0;
	/**************安卓专用接口 end***************/

};

} /*namespace service*/
