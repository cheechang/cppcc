#pragma once
#include <string>
#include <IControlClient.h>
namespace service{
	class IMClient;
	class IConfigService;
}
namespace control{
	class ControlManager;
	class ControlClient:public IControlClient{
	public:
		ControlClient();
		virtual ~ControlClient();
	public:
		/***********************************************
		* @brief 初始化客户端
		* @param[in]appdatadir 应用程序数据保存目录
		* @RETRUN bool类型 true 成功 false失败
		***********************************************/
		virtual bool InitClient(std::string& appdatadir);

		/**********************************************
		* \brief    获取头像保存的目录路径
		* @return   头像目录路径
		***********************************************/
		virtual std::string headImgPath();

		/************************************************
		* \brief    获取该用户聊天中图片信息的保存目录路径 
		* @return   图片信息的保存路径 
		***********************************************/
		virtual std::string userImgPath();

		/**************************************************
		* brief     获取该用户聊天中音频信息的保存目录路径 
		* @return   音频信息的保存目录路径 
		*************************************************/
		virtual std::string userAudioPath();

		/**************************************************
		* brief <U>获取该用户聊天中视频信息的保存目录路径
		* @return   视频信息的保存目录路径
		***************************************************/
		virtual std::string userVideoPath();

		/**************************************************
		* brief    获取该用户聊天中cache目录路径
		* @return   用户聊天中cache目录路径
		***************************************************/
		virtual std::string userCachePath();

		/**************************************************
		* brief     获取该用户聊天中文件信息的保存目录路径
		* @return   文件信息的保存目录路径
		***************************************************/
		virtual std::string userFilePath();

		/***************************************************
		* brief     获取该用户表情中文件的保存目录路径
		* @return   用户表情的保存目录路径
		***************************************************/
		virtual std::string userEmotionPath();

		/***********************************************
		* @brief 获取sdk客户端指针对象
		***********************************************/
		virtual CSharedPtr<service::IMClient> sdkClient();

		/***********************************************
		* @brief 获取登陆业务逻辑插件对象
		***********************************************/
        virtual CSharedPtr<IAuthControl> authControl();

		/***********************************************
		* @brief 获取用户模块插件对象
		***********************************************/
        virtual CSharedPtr<IUserControl> userControl();

		/***********************************************
		* @brief 获取组织架构业务逻辑插件对象
		***********************************************/
		virtual CSharedPtr<IEntMgrControl> entmgrControl();

		/***********************************************
		* @brief 获取聊天管理模块对象
		***********************************************/
		virtual CSharedPtr<IChatMgrControl> chatmgrControl();

		/***********************************************
		* @brief 获取应用管理模块对象
		***********************************************/
		virtual CSharedPtr<IAppMgrControl> appMgrControl();

		/***********************************************
		* @brief 获取群模块对象
		***********************************************/
		virtual CSharedPtr<IGroupMgrControl> groupmgrControl();

		/***********************************************
		* @brief 获取好友模块对象
		***********************************************/
		virtual CSharedPtr<IContactMgrControl> contactmgrControl();

		/***********************************************
		* @brief 获取升级模块对象
		***********************************************/
		virtual CSharedPtr<IUpdateControl> updateControl();
		/***********************************************
		* @brief 获取升级模块对象
		***********************************************/
		virtual CSharedPtr<ISysMsgMgrControl> sysMsgControl();
	public:
		static service::IMClient* GetSdkClient();
	private:
		static CSharedPtr<service::IMClient> m_sdkclient;
		CSharedPtr<service::IConfigService>  m_configservice;
		CSharedPtr<IAuthControl> m_authcontrol;
		CSharedPtr<IUserControl> m_usercontrol;
		CSharedPtr<IEntMgrControl> m_entcontrol;
		CSharedPtr<IChatMgrControl> m_chatmgrcontrol;
		CSharedPtr<IAppMgrControl> m_appmgrcontrol;
		CSharedPtr<IGroupMgrControl> m_groupmgrcontrol;
		CSharedPtr<IContactMgrControl> m_contactmgrcontrol;
		CSharedPtr<IUpdateControl> m_updatecontrol;
		CSharedPtr<ISysMsgMgrControl> m_sysmsgcontrol;
	};
}
