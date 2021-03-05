#pragma once
#include <memory>
#include <string>
#include <interface/Exports.h>
#include <interface/Defines.h>
namespace service{
	class IMClient;
}
namespace control{
    class IAuthControl;
	class IEntMgrControl;
	class IChatMgrControl;
	class IUserControl;
	class IAppMgrControl;
	class IGroupMgrControl;
	class IContactMgrControl;
	class IUpdateControl;
	class ISysMsgMgrControl;
	class IControlClient{
public:
	/***********************************************
	* @brief 初始化客户端
	* @param[in]appdatadir 应用程序数据保存目录
	* @RETRUN bool类型 true 成功 false失败
	***********************************************/
	virtual bool InitClient(std::string& appdatadir)=0;

	/**********************************************
	* \brief    获取头像保存的目录路径
	* @return   头像目录路径
	***********************************************/
	virtual std::string headImgPath() = 0;

	/************************************************
	* \brief    获取该用户聊天中图片信息的保存目录路径 
	* @return   图片信息的保存路径 
	***********************************************/
	virtual std::string userImgPath() = 0;

	/**************************************************
	* brief     获取该用户聊天中音频信息的保存目录路径 
	* @return   音频信息的保存目录路径 
	*************************************************/
	virtual std::string userAudioPath() = 0;

	/**************************************************
	* brief <U>获取该用户聊天中视频信息的保存目录路径
	* @return   视频信息的保存目录路径
	***************************************************/
	virtual std::string userVideoPath() = 0;

	/**************************************************
	* brief    获取该用户聊天中cache目录路径
	* @return   用户聊天中cache目录路径
	***************************************************/
	virtual std::string userCachePath() = 0;

	/**************************************************
	* brief     获取该用户聊天中文件信息的保存目录路径
	* @return   文件信息的保存目录路径
	***************************************************/
	virtual std::string userFilePath() = 0;

	/***************************************************
	* brief     获取该用户表情中文件的保存目录路径
	* @return   用户表情的保存目录路径
	***************************************************/
	virtual std::string userEmotionPath() = 0;

	/***********************************************
	* @brief 获取sdk客户端指针对象
	***********************************************/
	virtual CSharedPtr<service::IMClient> sdkClient() = 0;

   /***********************************************
	* @brief 获取登陆业务逻辑插件对象
	***********************************************/
    virtual CSharedPtr<IAuthControl> authControl() = 0;

	/***********************************************
	* @brief 获取用户模块插件对象
	***********************************************/
    virtual CSharedPtr<IUserControl> userControl() =0;

	/***********************************************
	* @brief 获取企业管理模块对象
	***********************************************/
    virtual CSharedPtr<IEntMgrControl> entmgrControl() = 0;

	/***********************************************
	* @brief 获取聊天管理模块对象
	***********************************************/
    virtual CSharedPtr<IChatMgrControl> chatmgrControl() = 0;

	/***********************************************
	* @brief 获取应用管理模块对象
	***********************************************/
    virtual CSharedPtr<IAppMgrControl> appMgrControl() = 0;

	/***********************************************
	* @brief 获取群模块对象
	***********************************************/
    virtual CSharedPtr<IGroupMgrControl> groupmgrControl() = 0;

	/***********************************************
	* @brief 获取好友模块对象
	***********************************************/
	virtual CSharedPtr<IContactMgrControl> contactmgrControl() = 0;

	/***********************************************
	* @brief 获取升级模块对象
	***********************************************/
	virtual CSharedPtr<IUpdateControl> updateControl() = 0;
		/***********************************************
	* @brief 获取系统消息模块对象
	***********************************************/
	virtual CSharedPtr<ISysMsgMgrControl> sysMsgControl() = 0;
};
	typedef CSharedPtr<IControlClient> ControlClientPtr;
	CONTROL_EXPORT_API CSharedPtr<IControlClient>getControlClient();
}
