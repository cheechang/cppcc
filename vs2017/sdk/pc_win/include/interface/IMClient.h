#pragma once

#include <string>
#include "IService.h"

#ifdef   SERVICE_EXPORTS
#ifdef _WIN32
#define  SERVICE_API   _declspec( dllexport )
#else
#define SERVICE_API 
#endif
#else
#ifdef _WIN32
#define  SERVICE_API   _declspec( dllimport )
#else
#define SERVICE_API 
#endif
#endif

#define VER_IMCLIENT INTERFACE_VERSION(1,0)
static const VRVIID IID_IMClient = {};

namespace model
{
struct AppInfo;
}

namespace service 
{

class IAuthService;
class IUserService;
class IContactService;
class ISearchService;
class IFileService;
class IGroupService;
class IChatService;
class ISysMsgService;
class IExtService;
class IConfigService;
class IFaceToFaceService;
class IRtcService;
class IMailService;
class IKssService;
class ICloudService;
class IGaService;
class IGaInterService;
//class ILoggingService;

class SERVICE_API IMClient
{
public:
	IMClient() {};
	virtual ~IMClient() {};
	//IMClient(const IMClient&) = delete;
	//IMClient& operator = (const IMClient&) = delete;

	/**
	* \brief 初始化客户端
	* @param[in] dataPath 数据存储路径
	* @param[in] certPath 证书路径
	* @param[in] appName 应用名
	* @return clientId
	*/
	virtual int init(const std::string &dataPath, const std::string& certPath, AppInfo &info) = 0;

	/**
	* \brief 反初始化客户端
	*/
	virtual void uninit() = 0;

	/**
	* \brief 清除所有通知回调
	*/
	virtual void clearAllNotifyCb() = 0;

	/**
	* \brief 日志打印
	* @param[in] lvl 日志等级 0:debug 1:trace 2:notice 3: warn 4: err
	* @param[in] info 日志内容，不超过1k大小
	*/
	virtual void loglog(int lvl, const std::string &info) = 0;

#ifdef _WIN32
	virtual SSharedPtr<service::IService>  _stdcall queryInterface(const VRVIID &Guid, unsigned int nQueryVer) = 0;
#elif __linux__
	virtual SSharedPtr<service::IService>  __attribute__((stdcall)) queryInterface(const VRVIID &Guid, unsigned int nQueryVer) = 0;
#elif __APPLE__
	virtual SSharedPtr<service::IService>  __attribute__((stdcall)) queryInterface(const VRVIID &Guid, unsigned int nQueryVer) = 0;
#endif

#ifdef SDK_FOR_ANDROID

	//提供给安卓的非版本控制的service的方法
	virtual bool getReponse() = 0;		//安卓获取回调的方式，需要循环调用

	virtual SSharedPtr<IAuthService> authService() = 0;
	virtual SSharedPtr<IUserService> userService() = 0;
	virtual SSharedPtr<IContactService> contactService() = 0;
	virtual SSharedPtr<ISearchService> searchService() = 0;
	virtual SSharedPtr<IFileService> fileService() = 0;
	virtual SSharedPtr<IGroupService> groupService() = 0;
	virtual SSharedPtr<IChatService> chatService() = 0;
	virtual SSharedPtr<ISysMsgService> sysMsgService() = 0;
	virtual SSharedPtr<IExtService> extService() = 0;
	virtual SSharedPtr<IConfigService> configService() = 0;
	virtual SSharedPtr<IFaceToFaceService> faceToFaceService() = 0;
	virtual SSharedPtr<IRtcService> rtcService() = 0;
	virtual SSharedPtr<IMailService> MailService() = 0;
	virtual SSharedPtr<ICloudService> cloudService() = 0;
	virtual SSharedPtr<IKssService> kssService() = 0;
    virtual SSharedPtr<IGaService> gaService() = 0;
    virtual SSharedPtr<IGaInterService> gaInterService() = 0;
	//virtual SSharedPtr<ILoggingService> loggingService() = 0;
#endif

};

SERVICE_API SSharedPtr<IMClient> getClient();

} /*namespace service */

