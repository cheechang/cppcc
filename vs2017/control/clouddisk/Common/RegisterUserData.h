#pragma once
#include <QMetaType>
#include <model/Packet.h>
#include <extModel/extpacket.h>
#include <interface/IService.h>
#define VRV_REG_METATYPE(T) qRegisterMetaType<T>( #T); qRegisterMetaType<T>( #T"&" );
class RegisterUserData
{
public:
	/// todo:
	static void Init()
	{
		VRV_REG_METATYPE(int32);
		VRV_REG_METATYPE(int64);
		VRV_REG_METATYPE(int8);
		VRV_REG_METATYPE(std::string);
		VRV_REG_METATYPE(model::CloudAddFileInfo);
		VRV_REG_METATYPE(model::CloudFileInfo);
		VRV_REG_METATYPE(std::vector<model::CloudFileInfo>);
		VRV_REG_METATYPE(model::CloudPermission);
		VRV_REG_METATYPE(service::ErrorInfo); 
		VRV_REG_METATYPE(model::OrganizationInfo);
		VRV_REG_METATYPE(model::EntpriseUserInfo);
		VRV_REG_METATYPE(std::vector<model::TeamMemberInfo>);
		VRV_REG_METATYPE(std::vector<model::CloudRoleInfo>);
	}
};