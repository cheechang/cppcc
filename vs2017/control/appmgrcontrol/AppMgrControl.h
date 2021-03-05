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
	* @brief 返回带后缀的插件名
	* @param[in]无
	***********************************************/
    virtual std::string GetName();
	/***********************************************
	* @brief 返回不带后缀的插件名
	* @param[in]无
	***********************************************/
    virtual std::string GetDisplayName();

	/***********************************************
	* @brief 设置sdk客户端实例对象
	* @param[in]无
	***********************************************/
    virtual void SetSdkClientObj(void* obj);

	/**********************************************
	* @brief 查询应用市场应用信息
	* @param[out] cb 传入接收结果回调 _1返回的应用信息
	***********************************************/
	virtual void getAllApplication(CFunction<void(std::vector<data::AppInfo>)> cb);
	
	/**********************************************
	* @brief 获取已安装的应用
	* @param[out] cb 传入接收结果回调 _1返回的应用信息
	***********************************************/
	virtual void getInstalledApplication(CFunction<void(std::vector<data::AppInfo>)> cb);

	/**********************************************
	* @brief 删除添加应用
	* @param[in] type 传入的操作类型，true添加，false删除
	* @param[in] appID 操作的appID
	* @param[out] cb 传入接收结果回调 _1错误信息
	***********************************************/
	virtual void addOrDeleteApplication(bool operType, int64 appID, CFunction<void(int)> cb);

	/**********************************************
	* @brief 获取用户信息Json串
	* @return 用户信息Json串
	***********************************************/
	virtual std::string getAccountInfoJson(void);

	/**********************************************
	* @brief 获取用户好友信息Json串
	* @return 用户信息Json串
	***********************************************/
	virtual std::string getContactListJson(void);

	/**********************************************
	* @brief 获取组织机构信息Json串
	* @param[in] uuid 传入的参数Json，以解析组织ID
	* @param[out] cb 传入接收结果回调 _1组织机构信息Json串
	***********************************************/
	virtual void getOrganizationJson(std::string uuid, CFunction<void(std::string)> cb);

	/**********************************************
	* @brief 获取用户群信息Json串
	* @return 用户信息Json串
	***********************************************/
	virtual std::string getGroupListJson(void);

	/**********************************************
	* @brief 获取群成员信息Json串
	* @param[in] uuid 传入的参数Json，以解析群ID
	* @param[out] cb 传入接收结果回调 _1群成员信息Json串
	***********************************************/
	virtual void getGroupMembersJson(std::string uuid, CFunction<void(std::string)> cb);

	/**********************************************
	* @brief 获取本地图片Json串
	* @param[in] vec 传入的图片本地地址
	* @param[out] cb 传入接收结果回调 _1上传的图片Json串回调 _2上传失败的图片回调
	***********************************************/
	virtual void getLocalPhotosJson(std::vector<std::string> images, CFunction<void(std::string)> cb, CFunction<void(std::string)> pro = CNull);

	/**********************************************
	* @brief 获取本地文件Json串
	* @param[in] vec 传入的文件本地地址
	* @param[out] cb 传入接收结果回调 _1上传的文件Json串回调 _2上传失败的文件回调
	***********************************************/
	virtual void getLocalFilesJson(std::vector<std::string> files, CFunction<void(std::string)> cb, CFunction<void(std::string)> pro = CNull);

	/**********************************************
	* @brief 获取服务器名称Json串
	* @return 服务器名称Json
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
		std::string m_pluginname; //插件名（不带后缀的）
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