#pragma once
#include "interface/IControlClient.h"
#include "interface/IEntMgrControl.h"
#include "interface/IAuthControl.h"
#include "interface/IChatMgrControl.h"
#include "interface/IUserControl.h"
#include "interface/IAppMgrControl.h"
#include "interface/IGroupMgrControl.h"
#include "interface/IContactMgrControl.h"
#include "interface/IUpdateControl.h"
#include "interface/ISysMsgMgrControl.h"
#include "common/connect.h"
#ifdef CLOUDDISK_ON
#include "../../control/clouddisk/Interface/ICloudDisk.h"
#endif
//自定义全局业务层对象指针
extern CSharedPtr<control::IControlClient> g_controlclient;

typedef CSharedPtr<control::IAuthControl>      IAuthControl_Ptr;
typedef CSharedPtr<control::IUserControl>      IUserControl_Ptr;
typedef CSharedPtr<control::IEntMgrControl>    IEntMgrControl_Ptr;
typedef CSharedPtr<control::IChatMgrControl>   IChatMgrControl_Ptr;
typedef CSharedPtr<control::IAppMgrControl>	IAppMgrControl_Ptr;
typedef CSharedPtr<control::IGroupMgrControl>  IGroupMgrControl_Ptr;
typedef CSharedPtr<control::IContactMgrControl>IContactMgrControl_Ptr;
typedef CSharedPtr<control::IUpdateControl>    IUpdateControl_Ptr;  
typedef CSharedPtr<control::ISysMsgMgrControl>    ISysMsgMgrControl_ptr;
#ifdef CLOUDDISK_ON
typedef CSharedPtr<ICloudDisk> ICloudDiskControl_ptr;
#endif
	 
#define AUTHCONTROL	    (IAuthControl_Ptr(g_controlclient->authControl()))
#define USERCONTROL	    (IUserControl_Ptr(g_controlclient->userControl()))
#define ENTMGRCONTROL	(IEntMgrControl_Ptr(g_controlclient->entmgrControl()))
#define CHATMGRCONTROL  (IChatMgrControl_Ptr(g_controlclient->chatmgrControl()))
#define APPMGRCONTROL	(IAppMgrControl_Ptr(g_controlclient->appMgrControl()))
#define GROUPMGRCONTROL (IGroupMgrControl_Ptr(g_controlclient->groupmgrControl()))
#define CONTACTMGRCONTROL (IContactMgrControl_Ptr(g_controlclient->contactmgrControl()))
#define UPDATECONTROL     (IUpdateControl_Ptr(g_controlclient->updateControl()))
#define SYSMSGCONTROL     (ISysMsgMgrControl_ptr(g_controlclient->sysMsgControl()))
#ifdef CLOUDDISK_ON
#define CLOUDDISKCONTROL   ((ICloudDiskControl_ptr)GetInstance())
#endif

#define USERIMGPATH     ((g_controlclient->userImgPath()).c_str())
#define USERFILEPATH    ((g_controlclient->userFilePath()).c_str())
#define USERAUDIOPATH   ((g_controlclient->userAudioPath()).c_str())
#define USERVIDEOPATH   ((g_controlclient->userVideoPath()).c_str())
#define USERHEADIMGPATH ((g_controlclient->headImgPath()).c_str())

#define CURENTUSERID	((g_controlclient->userControl()->GetAccountInfo()->id.value()))
typedef std::shared_ptr<data::Msg> MsgDataPtr;
typedef std::shared_ptr<data::ChatInfo> ChatInfoPtr;
typedef std::shared_ptr<data::Member> MemberPtr;