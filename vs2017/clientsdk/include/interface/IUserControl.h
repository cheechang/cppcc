#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include <interface/IUserService.h>
namespace data{
  class UserBasicData;
  class UserData;
  class AccountInfo;
  struct EntAppinfo;
  struct PersonalData;
  struct UserLocalSetting;
  struct UserInfoSetData;
  struct UploadFileProperty;
  struct ZXSearchParam;
  struct ZxTopInformation;
}
namespace control{
	class IUserControl:public IControl{
	public:
		/***********************************************
		* @brief 用户信息获取接口
		* @param[out]servername 服务器名
		***********************************************/
		virtual CSharedPtr<data::AccountInfo> GetAccountInfo()=0;

		/**********************************************************************************************************
		*brief 监听最近回话头像更新推送
		*@param[out] cb _1目标ID，人或者群  _2 头像
		**********************************************************************************************************/
		virtual void RegHeadUpdate(CFunction < void(int64, const std::string&)> cb) = 0;

		virtual void uploadUserHead(std::string src, std::string thumb, CFunction < void(int, const std::string&, const std::string&)>cb) = 0;
		virtual void updateAccountInfo(data::AccountInfo& user,  CFunction < void(int)> cb) = 0;

		/**
		* \brief 通过应用ID获取应用信息
		* @param[in] appId 应用程序ID
		* @param[out] cb 传入接收结果回调  _1错误信息  _2应用信息
		*/
		virtual void getAppInfo(int64 appId, CFunction<void(int, data::EntAppinfo&)> cb) = 0;
		
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
	virtual void setSetting(int8 flag, int type) = 0;

	/**
	* \brief 获取账号设置项
	* @param[in] type 传入获取的设置项类型
	* type为1，则返回值为value_i64第一位 如果type=0,返回所有字段，每个字段所占的位于type相对应\n
	* @param[out] cb 传入接收结果回调  _1错误信息  _2用户设置
	*/
	virtual void getUserSetting(int type, CFunction<void(int,data::UserInfoSetData&)> cb) = 0;
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
	virtual void setPersonalData(std::vector<data::PersonalData> items, CFunction<void(int)> cb) = 0;
	virtual void getPersonalData(std::vector<int16> &types, CFunction<void(int, std::vector<data::PersonalData>&)> cb) = 0;
		/**
		* \brief 设置监听用户信息更新的回调，服务器推送
		* @param[out] cb 注册的推送回调 _1 用户信息
		*/
	virtual void regOperateUserCb(CFunction<void(data::AccountInfo&)> cb) = 0;

    /**
	* \brief 获取本地配置
	* @param[out] result,本地配置
	*/
    virtual bool  getLocalSettingSync( std::vector<std::string> &keys, std::vector<data::UserLocalSetting> &result )= 0;
	
   /**
	* \brief 增加本地配置，以键值对方式保存(同步接口)
	* @param[in] items  配置信息集合
	*/
	virtual bool addLocalSettingSync(std::vector<data::UserLocalSetting> &items) = 0;

    /**
	* \brief 更新本地配置(同步接口)
	* @param[in] newItems 插入的新的配置信息集合
	*/
	virtual bool updateLocalSettingSync(std::vector<data::UserLocalSetting> &newItems) = 0;

    /**
	* \brief 获取全局勿扰模式
	* @param[out] cb 传入接收结果回调  _1错误信息 _2起始时间  _3结束时间  _4是否打开
	*/
	virtual void getGlobalNoDisturbMode(CFunction<void(int, int32, int32, bool)> cb) = 0;

        /**
	* \brief 设置全局勿扰模式
	* @param[in] startTime  起始时间
	* @param[in] endTime 结束时间
	* @param[in] isOpen 是否打开
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setGolbalNoDisturbMode(int32 startTime, int32 endTime, bool isOpen, CFunction<void(int)> cb) = 0;
    /**
    * \brief 获取服务器时间(同步接口)
    * @param[out] _1服务器时间，单位毫秒
    */
    virtual bool getServerTimeSync(int64& serverTime) = 0;

	/**
	* \brief 获取服务器时间
	* @param[in] cb 传入接收结果回调  _1错误信息   _2服务器时间，单位毫秒
	*/
	virtual void getServerTime(CFunction<void(int, int64)> cb) = 0;

	 /**
    * \brief 政协定制查询接口
    *@Param[in] pageSize 分页大小   
    *@Param[in] page 查询页码    
    *@Param[in] param 查询条件    
    *@Param[out] cb 传入接口结果回调，_1错误信息 _2总页数  _3查询结果
    */
    virtual void cppccSearch(int32 pageSize, int32 page, data::ZXSearchParam param, CFunction<void(int, int32, std::vector<data::UserBasicData>&)> cb) = 0;
   
	/**
	* \brief 政协消息置顶接口
	*@Param[in] info 置顶消息（见packet.h）
	*@Param[in] type 操作类型  5.新增 6.修改 7.删除  这个type是服务端给出的
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2错误描述
	*/
	virtual void cppccTopInformation(data::ZxTopInformation info, int type, CFunction<void(int, const std::string&)> cb) = 0;
	/**
	* \brief 政协分页查询置顶消息接口
	*@Param[in] groupId 置顶消息的群ID
	*@Param[in] pageNum 查询页
	*@Param[in] pageSize 单页消息数量
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2总页数 _3总记录数  _4查询结果
	*/
	virtual void cppccGetTopInfo(int64 groupId, int32 pageNum, int32 pageSize, CFunction<void(int, int32, int32, std::vector<data::ZxTopInformation>&)> cb) = 0;

	 };

	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}