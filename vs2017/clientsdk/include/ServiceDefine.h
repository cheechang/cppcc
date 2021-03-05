#pragma once
#include <memory>
#include <interface/IMClient.h>
#include <interface/IAuthService.h>
#include <interface/IChatService.h>
#include <interface/IConfigService.h>
#include <interface/IContactService.h>
#include <interface/IFileService.h>
#include <interface/IGroupService.h>
#include <interface/IExtService.h>
#include <interface/ISearchService.h>
#include <interface/ISysMsgService.h>
#include <interface/IUserService.h>
#include <interface/IAvService.h>
#include <interface/ITclService.h>
#include <interface/ICloudService.h>

extern service::IMClient* g_client;
#define AUTHSERVICE		SERVICE_GET(service::IAuthService, g_client, IID_IAuthSrvice, VER_IAUTH)
#define CONTACTSERVICE	SERVICE_GET(service::IContactService, g_client, IID_IContactService, VER_CONTACT)
#define GROUPSERVICE	SERVICE_GET(service::IGroupService, g_client, IID_IGroupService, VER_GROUP)
#define USERSERVICE		SERVICE_GET(service::IUserService, g_client, IID_IUserService, VER_USER)
#define CHATSERVICE		SERVICE_GET(service::IChatService, g_client, IID_IChatService, VER_IChatService)
#define CONFIGSERVICE	SERVICE_GET(service::IConfigService, g_client, IID_IConfigService, VER_CONFIG)
#define FILESERVICE		SERVICE_GET(service::IFileService, g_client, IID_IFileService, VER_FILE)
#define LDDSERVICE		SERVICE_GET(service::IExtService, g_client, IID_IExtService, VER_EXT)
#define SEARCHSERVICE	SERVICE_GET(service::ISearchService, g_client, IID_ISearchService, VER_SEARCH)
#define SYSMSGSERVICE	SERVICE_GET(service::ISysMsgService, g_client, IID_ISysMsgService, VER_SYSMSG)
#define AVSERVICE		SERVICE_GET(service::IAvService, g_client, IID_IAVService, VER_AV)
#define TCLSERVICE		SERVICE_GET(service::ITclService, g_client, IID_ITclService, VER_ITCL)
#define CLOUDSERVICE	SERVICE_GET(service::ICloudService, g_client, IID_ICloudService, VER_ICLOUD)

typedef CSharedPtr<service::IAuthService>    IAuthService_Ptr;
typedef CSharedPtr<service::IContactService> IContactService_Ptr;
typedef CSharedPtr<service::IGroupService>   IGroupService_Ptr;
typedef CSharedPtr<service::IUserService>    IUserService_Ptr;
typedef CSharedPtr<service::IChatService>    IChatService_Ptr;
typedef CSharedPtr<service::IConfigService>  IConfigService_Ptr;
typedef CSharedPtr<service::IFileService>    IFileService_Ptr;
typedef CSharedPtr<service::IExtService>     ILddService_Ptr;
typedef CSharedPtr<service::ISearchService>  ISearchService_Ptr;
typedef CSharedPtr<service::ISysMsgService>  ISysMsgService_Ptr;
typedef CSharedPtr<service::IAvService>       IAVService_Ptr;
typedef CSharedPtr<service::ICloudService>    ICloudService_Ptr;
