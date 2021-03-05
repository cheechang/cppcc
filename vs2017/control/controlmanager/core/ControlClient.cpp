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
	* @brief ��ʼ���ͻ���
	* @param[in]appdatadir Ӧ�ó������ݱ���Ŀ¼
	* @RETRUN bool���� true �ɹ� falseʧ��
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
			AddLog(LOG_LEV_ERROR,"��ʼ��sdkʧ��");
			return false;
		}
		model::AppInfo appInfo;
		appInfo.appVersion = utils::get_client_info();  //Ӧ�ð汾�ţ���"1.5.0"  *��������
		appInfo.deviceType = 1;					//�豸���� 1��PC��2���ֻ���3��pad��4����ҳ  *��������
#if defined(_WIN32)
		appInfo.deviceInfo = "pc-xp";			 	/* �豸��Ϣ, ��pc-window7,an-xiaomei2,ios-iphone4s */
#elif  defined(__linux__)
		appInfo.deviceInfo = GetLinuxSysInfo().toStdString().c_str();/* �豸��Ϣ, ��pc-window7,an-xiaomei2,ios-iphone4s */
#elif  defined(__APPLE__)
		appInfo.deviceInfo = "pc-osx";			 	/* �豸��Ϣ, ��pc-window7,an-xiaomei2,ios-iphone4s */
#endif
		appInfo.appName = "CPPCC";		//Ӧ����Ϣ ����Ӧ��������һ�� *��������	
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
		//appdatadir = "C:\\Users\\cheng\\AppData\\Local\\��Դ����\\";
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
	* \brief    ��ȡͷ�񱣴��Ŀ¼·��
	* @return   ͷ��Ŀ¼·��
	***********************************************/
    std::string ControlClient::headImgPath(){
		return m_configservice->headImgPath();
	}

	/************************************************
	* \brief    ��ȡ���û�������ͼƬ��Ϣ�ı���Ŀ¼·�� 
	* @return   ͼƬ��Ϣ�ı���·�� 
	***********************************************/
	std::string ControlClient::userImgPath(){
		return m_configservice->userImgPath();
	}

	/**************************************************
	* brief     ��ȡ���û���������Ƶ��Ϣ�ı���Ŀ¼·�� 
	* @return   ��Ƶ��Ϣ�ı���Ŀ¼·�� 
	*************************************************/
	std::string ControlClient::userAudioPath(){
		return m_configservice->userAudioPath();
	}

	/**************************************************
	* brief <U>��ȡ���û���������Ƶ��Ϣ�ı���Ŀ¼·��
	* @return   ��Ƶ��Ϣ�ı���Ŀ¼·��
	***************************************************/
	std::string ControlClient::userVideoPath(){
		return m_configservice->userVideoPath();
	}

	/**************************************************
	* brief    ��ȡ���û�������cacheĿ¼·��
	* @return   �û�������cacheĿ¼·��
	***************************************************/
	std::string ControlClient::userCachePath(){
		return m_configservice->userCachePath();
	}

	/**************************************************
	* brief     ��ȡ���û��������ļ���Ϣ�ı���Ŀ¼·��
	* @return   �ļ���Ϣ�ı���Ŀ¼·��
	***************************************************/
	std::string ControlClient::userFilePath(){
		return m_configservice->userFilePath();
	}

	/***************************************************
	* brief     ��ȡ���û��������ļ��ı���Ŀ¼·��
	* @return   �û�����ı���Ŀ¼·��
	***************************************************/
	std::string ControlClient::userEmotionPath(){
		return m_configservice->userEmotionPath();
	}

		/***********************************************
	* @brief ��ȡsdk�ͻ���ָ�����
	***********************************************/
	CSharedPtr<service::IMClient> ControlClient::sdkClient(){
		return m_sdkclient;
	}

	/***********************************************
	* @brief ��ȡ��½ҵ���߼��������
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
	* @brief ��ȡ�û�ģ��������
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
	* @brief ��ȡ��ҵ����ģ�����
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
	* @brief ��ȡ�������ģ�����
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
	* @brief ��ȡӦ�ù���ģ�����
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
	* @brief ��ȡ����ģ�����
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
	* @brief ��ȡϵͳ��Ϣģ�����
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
	//�����ӿں���
	CONTROL_EXPORT_API CSharedPtr<IControlClient>getControlClient(){
		return CMakePtr<ControlClient>();
	}
}/*namespace control */