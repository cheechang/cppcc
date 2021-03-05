#include "ControlClient.h"
#include <interface/IMClient.h>
#include <interface/IConfigService.h>
#include <IAuthControl.h>
#include <IUserControl.h>
#include <IEntMgrControl.h>
#include <IChatMgrControl.h>
#include <IAppMgrControl.h>
#include <IGroupMgrControl.h>
#include <IContactMgrControl.h>
#include <IUpdateControl.h>
#include <ISysMsgMgrControl.h>
#include <log.h>
#include "ControlManager.h"
#include "model/Packet.h"
#include "../utils/common.h"
#include "../utils/Hardware.h"
#include "ServiceDefine.h"
const char * filename = 0;
int line = 0;

#pragma comment(lib,"serviced.lib")
namespace control{
	service::IMClient* g_client =CNull;
	CSharedPtr<service::IMClient> ControlClient::m_sdkclient = CNull;
	ControlClient::ControlClient():m_configservice(CNull),m_authcontrol(CNull),m_chatmgrcontrol(CNull),m_entcontrol(CNull),m_usercontrol(CNull){
BEGIN;
	m_groupmgrcontrol = CNull;
	m_contactmgrcontrol = CNull;
	m_updatecontrol = CNull;
	m_sysmsgcontrol = CNull;
END;
	}
	ControlClient::~ControlClient(){
BEGIN;
		ControlManager::GetInstance()->UnLoadAll();
END;
	}
	/***********************************************
	* @brief 初始化客户端
	* @param[in]appdatadir 应用程序数据保存目录
	* @RETRUN bool类型 true 成功 false失败
	***********************************************/
	bool ControlClient::InitClient(std::string& appdatadir){
BEGIN;
		bool bret = false;
		std::string certPath("");
		int clientId = 0;
		char szUtf8[1024] = {0};

	    m_sdkclient = service::getClient();
		if (CNull == m_sdkclient)
		{
			AddLog(LOG_LEV_ERROR,"初始化sdk失败");
			return false;
		}
		model::AppInfo appInfo;
		appInfo.appVersion = utils::get_client_info();  //应用版本号，如"1.5.0"  *必须设置
		appInfo.deviceType = 1;					//设备类型 1：PC；2：手机；3：pad；4：网页  *必须设置
#if defined(_WIN32)
		appInfo.deviceInfo = "pc-xp";			 	/* 设备信息, 如pc-window7,an-xiaomei2,ios-iphone4s */
#elif  defined(__linux__)
		appInfo.deviceInfo = GetLinuxSysInfo().toStdString().c_str();/* 设备信息, 如pc-window7,an-xiaomei2,ios-iphone4s */
#elif  defined(__APPLE__)
		appInfo.deviceInfo = "pc-osx";			 	/* 设备信息, 如pc-window7,an-xiaomei2,ios-iphone4s */
#endif
		appInfo.appName = "CPPCC";		//应用信息 需与应用名保持一致 *必须设置	
		appInfo.mac = utils::Hardware::mac();
		appInfo.mark = utils::get_client_info(utils::CLIENTINFO_TYPE_MARK);
		Log(LOG_LEV_DEBUG, LOG_FILE, "[version:%s,mac:%s,mark:%s,deviceinfo:%s]", appInfo.appVersion.c_str(), appInfo.mac.c_str(), appInfo.mark.c_str(), appInfo.deviceInfo.c_str());
		auto iplist = utils::Hardware::getlocalip();
		for ( size_t index=0; index<iplist.size(); ++index)
		{
			Log(LOG_LEV_DEBUG, LOG_FILE, "[ip:%s]",iplist[index].c_str());
		}
		certPath = utils::GetModulePath()+ "/linkdood.crt";
		appdatadir.append("/");
		utils::string_replace(appdatadir,"\\","/");
		AddLog(LOG_LEV_DEBUG,"appdatadir=%s,certPath=%s", appdatadir.c_str(),certPath.c_str());
		utils::char2utf8(certPath.c_str(),szUtf8);
		char logUtf8[1024] = { 0 };
		//appdatadir = "C:\\Users\\cheng\\AppData\\Local\\信源豆豆\\";
		utils::char2utf8(appdatadir.c_str(), logUtf8);
		clientId = m_sdkclient->init(logUtf8,szUtf8,appInfo);
		if (clientId<=0){
			AddLog(LOG_LEV_ERROR,"init client failed,clientId=%d", clientId);
			return bret;
		}
		ControlManager::GetInstance()->LoadAll();
		g_client = m_sdkclient.get();
		m_configservice = CONFIGSERVICE;
		m_configservice->setMessageBox(0);
		m_configservice->setIsRoming(1);
END;
		return bret;
	}
	/**********************************************
	* \brief    获取头像保存的目录路径
	* @return   头像目录路径
	***********************************************/
    std::string ControlClient::headImgPath(){
		return m_configservice->headImgPath();
	}

	/************************************************
	* \brief    获取该用户聊天中图片信息的保存目录路径 
	* @return   图片信息的保存路径 
	***********************************************/
	std::string ControlClient::userImgPath(){
		return m_configservice->userImgPath();
	}

	/**************************************************
	* brief     获取该用户聊天中音频信息的保存目录路径 
	* @return   音频信息的保存目录路径 
	*************************************************/
	std::string ControlClient::userAudioPath(){
		return m_configservice->userAudioPath();
	}

	/**************************************************
	* brief <U>获取该用户聊天中视频信息的保存目录路径
	* @return   视频信息的保存目录路径
	***************************************************/
	std::string ControlClient::userVideoPath(){
		return m_configservice->userVideoPath();
	}

	/**************************************************
	* brief    获取该用户聊天中cache目录路径
	* @return   用户聊天中cache目录路径
	***************************************************/
	std::string ControlClient::userCachePath(){
		return m_configservice->userCachePath();
	}

	/**************************************************
	* brief     获取该用户聊天中文件信息的保存目录路径
	* @return   文件信息的保存目录路径
	***************************************************/
	std::string ControlClient::userFilePath(){
		return m_configservice->userFilePath();
	}

	/***************************************************
	* brief     获取该用户表情中文件的保存目录路径
	* @return   用户表情的保存目录路径
	***************************************************/
	std::string ControlClient::userEmotionPath(){
		return m_configservice->userEmotionPath();
	}

		/***********************************************
	* @brief 获取sdk客户端指针对象
	***********************************************/
	CSharedPtr<service::IMClient> ControlClient::sdkClient(){
		return m_sdkclient;
	}

	/***********************************************
	* @brief 获取登陆业务逻辑插件对象
	***********************************************/
     CSharedPtr<IAuthControl> ControlClient::authControl(){
		 if ( CNull == m_authcontrol)
		 {
			 IControl* pInstance = CNull;
			 pInstance = ControlManager::GetInstance()->GetPlugin(std::string("authcontrol"));
			 m_authcontrol = CSharedPtr<IAuthControl>(dynamic_cast<IAuthControl*>(pInstance));
		 }
		return m_authcontrol;
	}

	/***********************************************
	* @brief 获取用户模块插件对象
	***********************************************/
    CSharedPtr<IUserControl> ControlClient::userControl(){
		if ( CNull == m_usercontrol)
		{
			IControl* pInstance = CNull;
			pInstance = ControlManager::GetInstance()->GetPlugin(std::string("usercontrol"));
			m_usercontrol = CSharedPtr<IUserControl>(dynamic_cast<IUserControl*>(pInstance));
		}
		return m_usercontrol;
	}
	/***********************************************
	* @brief 获取企业管理模块对象
	***********************************************/
	CSharedPtr<IEntMgrControl> ControlClient::entmgrControl()
	{
		if ( CNull == m_entcontrol)
		{
			IControl* pInstance = CNull;
			pInstance = ControlManager::GetInstance()->GetPlugin(std::string("entmgrcontrol"));
			m_entcontrol = CSharedPtr<IEntMgrControl>(dynamic_cast<IEntMgrControl*>(pInstance));
		}
		return m_entcontrol;
	}

	/***********************************************
	* @brief 获取聊天管理模块对象
	***********************************************/
	CSharedPtr<IChatMgrControl> ControlClient::chatmgrControl(){
		if ( CNull == m_chatmgrcontrol)
		{
			IControl* pInstance = CNull;
			pInstance = ControlManager::GetInstance()->GetPlugin(std::string("chatmgrcontrol"));
			m_chatmgrcontrol = CSharedPtr<IChatMgrControl>(dynamic_cast<IChatMgrControl*>(pInstance));
		}
		return m_chatmgrcontrol;
	}

	/***********************************************
	* @brief 获取应用管理模块对象
	***********************************************/
	CSharedPtr<IAppMgrControl> ControlClient::appMgrControl(){
		if ( CNull == m_appmgrcontrol)
		{
			IControl* pInstance = CNull;
			pInstance = ControlManager::GetInstance()->GetPlugin(std::string("appmgrcontrol"));
			m_appmgrcontrol = CSharedPtr<IAppMgrControl>(dynamic_cast<IAppMgrControl*>(pInstance));
		}
		return m_appmgrcontrol;
	}

	service::IMClient* ControlClient::GetSdkClient(){
		return m_sdkclient.get();
	}

	CSharedPtr<IGroupMgrControl> ControlClient::groupmgrControl()
	{
		if ( CNull == m_groupmgrcontrol)
		{
			IControl* pInstance = CNull;
			pInstance = ControlManager::GetInstance()->GetPlugin(std::string("groupmgrcontrol"));
			m_groupmgrcontrol = CSharedPtr<IGroupMgrControl>(dynamic_cast<IGroupMgrControl*>(pInstance));
		}
		return m_groupmgrcontrol;
	}

	CSharedPtr<IContactMgrControl> ControlClient::contactmgrControl()
	{
		if ( CNull == m_contactmgrcontrol)
		{
			IControl* pInstance = CNull;
			pInstance = ControlManager::GetInstance()->GetPlugin(std::string("contactmgrcontrol"));
			m_contactmgrcontrol = CSharedPtr<IContactMgrControl>(dynamic_cast<IContactMgrControl*>(pInstance));
		}
		return m_contactmgrcontrol;
	}

	/***********************************************
	* @brief 获取升级模块对象
	***********************************************/
	CSharedPtr<IUpdateControl> ControlClient::updateControl(){
		if ( CNull == m_updatecontrol)
		{
			IControl* pInstance = CNull;
			pInstance = ControlManager::GetInstance()->GetPlugin(std::string("updatecontrol"));
			m_updatecontrol = CSharedPtr<IUpdateControl>(dynamic_cast<IUpdateControl*>(pInstance));
		}
		return m_updatecontrol;
	}
		/***********************************************
	* @brief 获取系统消息模块对象
	***********************************************/
	CSharedPtr<ISysMsgMgrControl> ControlClient::sysMsgControl(){
		if ( CNull == m_sysmsgcontrol)
		{
			IControl* pInstance = CNull;
			pInstance = ControlManager::GetInstance()->GetPlugin(std::string("sysmsgmgrcontrol"));
			m_sysmsgcontrol = CSharedPtr<ISysMsgMgrControl>(dynamic_cast<ISysMsgMgrControl*>(pInstance));
		}
		return m_sysmsgcontrol;
	}
	//导出接口函数
	CONTROL_EXPORT_API CSharedPtr<IControlClient>getControlClient(){
		return CMakePtr<ControlClient>();
	}
}/*namespace control */