#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include "data/AppData.h"
namespace control{
class IAppMgrControl:public IControl{
public:
	/**********************************************
	* @brief 查询应用市场应用信息
	* @param[out] cb 传入接收结果回调 _1返回的应用信息
	***********************************************/
	virtual void getAllApplication(CFunction<void(std::vector<data::AppInfo>)> cb) = 0;

	/**********************************************
	* @brief 获取已安装的应用
	* @param[out] cb 传入接收结果回调 _1返回的应用信息
	***********************************************/
	virtual void getInstalledApplication(CFunction<void(std::vector<data::AppInfo>)> cb) = 0;

	/**********************************************
	* @brief 删除添加应用
	* @param[in] type 传入的操作类型，true添加，false删除
	* @param[in] appID 操作的appID
	* @param[out] cb 传入接收结果回调 _1错误信息
	***********************************************/
	virtual void addOrDeleteApplication(bool type, int64 appID, CFunction<void(int)> cb) = 0;

	/**********************************************
	* @brief 获取用户信息Json串
	* @return 用户信息Json串
	***********************************************/
	virtual std::string getAccountInfoJson(void) = 0;

	/**********************************************
	* @brief 获取用户好友信息Json串
	* @return 用户好友信息Json串
	***********************************************/
	virtual std::string getContactListJson(void) = 0;

	/**********************************************
	* @brief 获取组织机构信息Json串
	* @param[in] uuid 传入的参数Json，以解析组织ID
	* @param[out] cb 传入接收结果回调 _1组织机构信息Json串
	***********************************************/
	virtual void getOrganizationJson(std::string uuid, CFunction<void(std::string)> cb) = 0;

	/**********************************************
	* @brief 获取用户群信息Json串
	* @return 用户信息Json串
	***********************************************/
	virtual std::string getGroupListJson(void) = 0;

	/**********************************************
	* @brief 获取群成员信息Json串
	* @param[in] uuid 传入的参数Json，以解析群ID
	* @param[out] cb 传入接收结果回调 _1群成员信息Json串
	***********************************************/
	virtual void getGroupMembersJson(std::string uuid, CFunction<void(std::string)> cb) = 0;

	/**********************************************
	* @brief 获取本地图片Json串
	* @param[in] vec 传入的图片本地地址
	* @param[out] cb 传入接收结果回调 _1上传的图片Json串回调 _2上传失败的图片回调
	***********************************************/
	virtual void getLocalPhotosJson(std::vector<std::string> images, CFunction<void(std::string)> cb, CFunction<void(std::string)> pro = CNull) = 0;

	/**********************************************
	* @brief 获取本地文件Json串
	* @param[in] vec 传入的文件本地地址
	* @param[out] cb 传入接收结果回调 _1上传的文件Json串回调 _2上传失败的文件回调
	***********************************************/
	virtual void getLocalFilesJson(std::vector<std::string> files, CFunction<void(std::string)> cb, CFunction<void(std::string)> pro = CNull) = 0;

	/**********************************************
	* @brief 获取服务器名称Json串
	* @return 服务器名称Json
	***********************************************/
	virtual std::string getServerNameJson(void) = 0;
};
extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}