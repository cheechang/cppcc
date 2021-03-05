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
		* @brief ��ʼ���ͻ���
		* @param[in]appdatadir Ӧ�ó������ݱ���Ŀ¼
		* @RETRUN bool���� true �ɹ� falseʧ��
		***********************************************/
		virtual bool InitClient(std::string& appdatadir);

		/**********************************************
		* \brief    ��ȡͷ�񱣴��Ŀ¼·��
		* @return   ͷ��Ŀ¼·��
		***********************************************/
		virtual std::string headImgPath();

		/************************************************
		* \brief    ��ȡ���û�������ͼƬ��Ϣ�ı���Ŀ¼·�� 
		* @return   ͼƬ��Ϣ�ı���·�� 
		***********************************************/
		virtual std::string userImgPath();

		/**************************************************
		* brief     ��ȡ���û���������Ƶ��Ϣ�ı���Ŀ¼·�� 
		* @return   ��Ƶ��Ϣ�ı���Ŀ¼·�� 
		*************************************************/
		virtual std::string userAudioPath();

		/**************************************************
		* brief <U>��ȡ���û���������Ƶ��Ϣ�ı���Ŀ¼·��
		* @return   ��Ƶ��Ϣ�ı���Ŀ¼·��
		***************************************************/
		virtual std::string userVideoPath();

		/**************************************************
		* brief    ��ȡ���û�������cacheĿ¼·��
		* @return   �û�������cacheĿ¼·��
		***************************************************/
		virtual std::string userCachePath();

		/**************************************************
		* brief     ��ȡ���û��������ļ���Ϣ�ı���Ŀ¼·��
		* @return   �ļ���Ϣ�ı���Ŀ¼·��
		***************************************************/
		virtual std::string userFilePath();

		/***************************************************
		* brief     ��ȡ���û��������ļ��ı���Ŀ¼·��
		* @return   �û�����ı���Ŀ¼·��
		***************************************************/
		virtual std::string userEmotionPath();

		/***********************************************
		* @brief ��ȡsdk�ͻ���ָ�����
		***********************************************/
		virtual CSharedPtr<service::IMClient> sdkClient();

		/***********************************************
		* @brief ��ȡ��½ҵ���߼��������
		***********************************************/
        virtual CSharedPtr<IAuthControl> authControl();

		/***********************************************
		* @brief ��ȡ�û�ģ��������
		***********************************************/
        virtual CSharedPtr<IUserControl> userControl();

		/***********************************************
		* @brief ��ȡ��֯�ܹ�ҵ���߼��������
		***********************************************/
		virtual CSharedPtr<IEntMgrControl> entmgrControl();

		/***********************************************
		* @brief ��ȡ�������ģ�����
		***********************************************/
		virtual CSharedPtr<IChatMgrControl> chatmgrControl();

		/***********************************************
		* @brief ��ȡӦ�ù���ģ�����
		***********************************************/
		virtual CSharedPtr<IAppMgrControl> appMgrControl();

		/***********************************************
		* @brief ��ȡȺģ�����
		***********************************************/
		virtual CSharedPtr<IGroupMgrControl> groupmgrControl();

		/***********************************************
		* @brief ��ȡ����ģ�����
		***********************************************/
		virtual CSharedPtr<IContactMgrControl> contactmgrControl();

		/***********************************************
		* @brief ��ȡ����ģ�����
		***********************************************/
		virtual CSharedPtr<IUpdateControl> updateControl();
		/***********************************************
		* @brief ��ȡ����ģ�����
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
