#pragma once
#include <IAppMgrControl.h>

#include "ServiceDefine.h"
#include "data/AppData.h"
#include "json.h"

namespace service{
	class IMClient;
}

namespace control{
	class AppMgrControl:public IAppMgrControl{
	public:
		AppMgrControl(const std::string &strName=std::string("appmgrcontrol"));
		virtual ~AppMgrControl();

	/***********************************************
	* @brief ���ش���׺�Ĳ����
	* @param[in]��
	***********************************************/
    virtual std::string GetName();
	/***********************************************
	* @brief ���ز�����׺�Ĳ����
	* @param[in]��
	***********************************************/
    virtual std::string GetDisplayName();

	/***********************************************
	* @brief ����sdk�ͻ���ʵ������
	* @param[in]��
	***********************************************/
    virtual void SetSdkClientObj(void* obj);

	/**********************************************
	* @brief ��ѯӦ���г�Ӧ����Ϣ
	* @param[out] cb ������ս���ص� _1���ص�Ӧ����Ϣ
	***********************************************/
	virtual void getAllApplication(CFunction<void(std::vector<data::AppInfo>)> cb);
	
	/**********************************************
	* @brief ��ȡ�Ѱ�װ��Ӧ��
	* @param[out] cb ������ս���ص� _1���ص�Ӧ����Ϣ
	***********************************************/
	virtual void getInstalledApplication(CFunction<void(std::vector<data::AppInfo>)> cb);

	/**********************************************
	* @brief ɾ�����Ӧ��
	* @param[in] type ����Ĳ������ͣ�true��ӣ�falseɾ��
	* @param[in] appID ������appID
	* @param[out] cb ������ս���ص� _1������Ϣ
	***********************************************/
	virtual void addOrDeleteApplication(bool operType, int64 appID, CFunction<void(int)> cb);

	/**********************************************
	* @brief ��ȡ�û���ϢJson��
	* @return �û���ϢJson��
	***********************************************/
	virtual std::string getAccountInfoJson(void);

	/**********************************************
	* @brief ��ȡ�û�������ϢJson��
	* @return �û���ϢJson��
	***********************************************/
	virtual std::string getContactListJson(void);

	/**********************************************
	* @brief ��ȡ��֯������ϢJson��
	* @param[in] uuid ����Ĳ���Json���Խ�����֯ID
	* @param[out] cb ������ս���ص� _1��֯������ϢJson��
	***********************************************/
	virtual void getOrganizationJson(std::string uuid, CFunction<void(std::string)> cb);

	/**********************************************
	* @brief ��ȡ�û�Ⱥ��ϢJson��
	* @return �û���ϢJson��
	***********************************************/
	virtual std::string getGroupListJson(void);

	/**********************************************
	* @brief ��ȡȺ��Ա��ϢJson��
	* @param[in] uuid ����Ĳ���Json���Խ���ȺID
	* @param[out] cb ������ս���ص� _1Ⱥ��Ա��ϢJson��
	***********************************************/
	virtual void getGroupMembersJson(std::string uuid, CFunction<void(std::string)> cb);

	/**********************************************
	* @brief ��ȡ����ͼƬJson��
	* @param[in] vec �����ͼƬ���ص�ַ
	* @param[out] cb ������ս���ص� _1�ϴ���ͼƬJson���ص� _2�ϴ�ʧ�ܵ�ͼƬ�ص�
	***********************************************/
	virtual void getLocalPhotosJson(std::vector<std::string> images, CFunction<void(std::string)> cb, CFunction<void(std::string)> pro = CNull);

	/**********************************************
	* @brief ��ȡ�����ļ�Json��
	* @param[in] vec ������ļ����ص�ַ
	* @param[out] cb ������ս���ص� _1�ϴ����ļ�Json���ص� _2�ϴ�ʧ�ܵ��ļ��ص�
	***********************************************/
	virtual void getLocalFilesJson(std::vector<std::string> files, CFunction<void(std::string)> cb, CFunction<void(std::string)> pro = CNull);

	/**********************************************
	* @brief ��ȡ����������Json��
	* @return ����������Json
	***********************************************/
	virtual std::string getServerNameJson(void);

	protected:
		void onQueryMarketApplication(service::ErrorInfo err,
			SmallMarketAppPage& page);
		void onInstalledAppsRetrieve(service::ErrorInfo err,
			std::vector<SmallMarketAppInfo>& vecInstalledAppsInfo,
			std::vector<SmallMarketAppInfo>& vecAllAppsInfo);
		void onGetInstalledApplication(service::ErrorInfo err,
			std::vector<SmallMarketAppInfo>& appsInfo);
		void onAddOrDeleteApplication(service::ErrorInfo err);
		void onSerGetGroupMembers(service::ErrorInfo err, 
			std::vector<CSharedPtr<Member>>& members);
		void onSerGetVisibleOrgUsers(service::ErrorInfo err, int8 allowChat, 
			int8 contactVisiable, std::vector<model::OrganizationInfo>& orgs,
			std::vector<model::EntpriseUserInfo>& users);
		void onSerSendImage(service::ErrorInfo err, int64 targetId,
			const std::string& srcJson, const std::string& thumpJson,
			std::vector<std::string> images, Json::Value arrImages, 
			unsigned int time);
		void onSerSendFile(service::ErrorInfo err, int64 targetId,
			const std::string& fileJson, std::vector<std::string> files,
			Json::Value arrFiles, unsigned int time);

	private:
		std::string m_pluginname; //�������������׺�ģ�
		IUserService_Ptr m_pUserService;
		IContactService_Ptr m_pContactService;
		ILddService_Ptr m_pLddService;
		IGroupService_Ptr m_pGroupService;
		IFileService_Ptr m_pFileService;
		IConfigService_Ptr m_pConfigService;

		CFunction<void(std::vector<data::AppInfo>)> m_funcGetAllApplicationCB;
		CFunction<void(std::vector<data::AppInfo>)> m_funcGetInstalledApplicationCB;
		CFunction<void(int)> m_funcAddOrDeleteApplicationCB;
		CFunction<void(std::string)> m_funcGetGroupMembersJsonCB;
		CFunction<void(std::string)> m_funcGetOrganizationJsonCB;
		CFunction<void(std::string)> m_funcGetLocalPhotosJsonCB;
		CFunction<void(std::string)> m_funcGetLocalFilesJsonCB;
		CFunction<void(std::string)> m_funcFileUploadFailureCB;
	};
}