#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include "data/AppData.h"
namespace control{
class IAppMgrControl:public IControl{
public:
	/**********************************************
	* @brief ��ѯӦ���г�Ӧ����Ϣ
	* @param[out] cb ������ս���ص� _1���ص�Ӧ����Ϣ
	***********************************************/
	virtual void getAllApplication(CFunction<void(std::vector<data::AppInfo>)> cb) = 0;

	/**********************************************
	* @brief ��ȡ�Ѱ�װ��Ӧ��
	* @param[out] cb ������ս���ص� _1���ص�Ӧ����Ϣ
	***********************************************/
	virtual void getInstalledApplication(CFunction<void(std::vector<data::AppInfo>)> cb) = 0;

	/**********************************************
	* @brief ɾ�����Ӧ��
	* @param[in] type ����Ĳ������ͣ�true��ӣ�falseɾ��
	* @param[in] appID ������appID
	* @param[out] cb ������ս���ص� _1������Ϣ
	***********************************************/
	virtual void addOrDeleteApplication(bool type, int64 appID, CFunction<void(int)> cb) = 0;

	/**********************************************
	* @brief ��ȡ�û���ϢJson��
	* @return �û���ϢJson��
	***********************************************/
	virtual std::string getAccountInfoJson(void) = 0;

	/**********************************************
	* @brief ��ȡ�û�������ϢJson��
	* @return �û�������ϢJson��
	***********************************************/
	virtual std::string getContactListJson(void) = 0;

	/**********************************************
	* @brief ��ȡ��֯������ϢJson��
	* @param[in] uuid ����Ĳ���Json���Խ�����֯ID
	* @param[out] cb ������ս���ص� _1��֯������ϢJson��
	***********************************************/
	virtual void getOrganizationJson(std::string uuid, CFunction<void(std::string)> cb) = 0;

	/**********************************************
	* @brief ��ȡ�û�Ⱥ��ϢJson��
	* @return �û���ϢJson��
	***********************************************/
	virtual std::string getGroupListJson(void) = 0;

	/**********************************************
	* @brief ��ȡȺ��Ա��ϢJson��
	* @param[in] uuid ����Ĳ���Json���Խ���ȺID
	* @param[out] cb ������ս���ص� _1Ⱥ��Ա��ϢJson��
	***********************************************/
	virtual void getGroupMembersJson(std::string uuid, CFunction<void(std::string)> cb) = 0;

	/**********************************************
	* @brief ��ȡ����ͼƬJson��
	* @param[in] vec �����ͼƬ���ص�ַ
	* @param[out] cb ������ս���ص� _1�ϴ���ͼƬJson���ص� _2�ϴ�ʧ�ܵ�ͼƬ�ص�
	***********************************************/
	virtual void getLocalPhotosJson(std::vector<std::string> images, CFunction<void(std::string)> cb, CFunction<void(std::string)> pro = CNull) = 0;

	/**********************************************
	* @brief ��ȡ�����ļ�Json��
	* @param[in] vec ������ļ����ص�ַ
	* @param[out] cb ������ս���ص� _1�ϴ����ļ�Json���ص� _2�ϴ�ʧ�ܵ��ļ��ص�
	***********************************************/
	virtual void getLocalFilesJson(std::vector<std::string> files, CFunction<void(std::string)> cb, CFunction<void(std::string)> pro = CNull) = 0;

	/**********************************************
	* @brief ��ȡ����������Json��
	* @return ����������Json
	***********************************************/
	virtual std::string getServerNameJson(void) = 0;
};
extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}