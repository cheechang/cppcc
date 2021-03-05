#pragma once
#include <QMetaType>
#include <memory>
#include <vector>
#include <map>
#include "data/ChatData.h"
#include "data/AppData.h"
#include "data/GroupData.h"
#include "data/ContactData.h"
#include "data/entpriseInfo.h"
#include "data/UserData.h"
#include "data/UpdateData.h"
#include "data/SearchData.h"
#define VRV_REG_METATYPE(T) qRegisterMetaType<T>( #T); qRegisterMetaType<T>( #T"&" );
class ServiceInfos
{
public:
    /// todo:
    static void Init()
    {
		VRV_REG_METATYPE(int);
		VRV_REG_METATYPE(int8);
		VRV_REG_METATYPE(int16);
		VRV_REG_METATYPE(int32);
		VRV_REG_METATYPE(int64);
		VRV_REG_METATYPE(std::string);
		VRV_REG_METATYPE(std::vector<CSharedPtr<data::ChatData>>);
		VRV_REG_METATYPE(std::vector<CSharedPtr<data::ChatInfo>>);
		VRV_REG_METATYPE(CSharedPtr<data::ChatInfo>);
		VRV_REG_METATYPE(CSharedPtr<data::Msg>);
		VRV_REG_METATYPE(std::vector<CSharedPtr<data::Msg>>);
		VRV_REG_METATYPE(std::vector<data::AppInfo>);
		VRV_REG_METATYPE(std::vector<CSharedPtr<data::TinyGroup>>);
		VRV_REG_METATYPE(data::Group);
		VRV_REG_METATYPE(std::vector<CSharedPtr<data::Member>>);
		VRV_REG_METATYPE(CSharedPtr<data::MsgStatus>);
		VRV_REG_METATYPE(std::vector<int64>);
		VRV_REG_METATYPE(std::vector<data::Contact>);
		VRV_REG_METATYPE(data::Contact);
		VRV_REG_METATYPE(std::vector<data::OrgAndUserInfo>);
		VRV_REG_METATYPE(data::OrgAndUserInfo);
		VRV_REG_METATYPE(std::vector<data::EnterpriseDictionary>);
		VRV_REG_METATYPE(data::EntAppinfo);
		VRV_REG_METATYPE(data::UserData);
		VRV_REG_METATYPE(std::vector<data::ChatInfo>); 
		VRV_REG_METATYPE(CSharedPtr<data::ChatInfo>);
		VRV_REG_METATYPE(data::UpdateInfo);
		VRV_REG_METATYPE(data::SysMsg);
		VRV_REG_METATYPE(std::vector<data::SysMsg>);
		VRV_REG_METATYPE(std::vector<data::SearchResultInfo>);
		VRV_REG_METATYPE(data::SearchResultInfo);
		VRV_REG_METATYPE(data::ContactVerifyType);
		VRV_REG_METATYPE(data::AccountInfo);
		VRV_REG_METATYPE(data::OnlineState);
		VRV_REG_METATYPE(std::vector<data::PersonalData>);
		VRV_REG_METATYPE(std::vector<data::EnterpriseAccount>);
		VRV_REG_METATYPE(data::EnterpriseAccount);
		VRV_REG_METATYPE(data::Member);
        VRV_REG_METATYPE(data::UserBasicData);
		VRV_REG_METATYPE(std::vector<data::UserBasicData>);
		VRV_REG_METATYPE(data::UserInfoSetData);
		VRV_REG_METATYPE(std::vector<CSharedPtr<data::FileInfo>>);
		VRV_REG_METATYPE(data::MsgSearchResult);
		VRV_REG_METATYPE(data::MsgDetailSearchResult);
		VRV_REG_METATYPE(data::ZxTopInformation);
		VRV_REG_METATYPE(std::vector<data::ZxTopInformation>);
		VRV_REG_METATYPE(MemberPtr);
		VRV_REG_METATYPE(MsgDataPtr);
		VRV_REG_METATYPE(std::vector<MsgDataPtr>); 
		VRV_REG_METATYPE(std::vector<data::MsgUnreadCounter>);
		VRV_REG_METATYPE(data::MsgUnreadCounter);
		VRV_REG_METATYPE(std::vector<MemberPtr>);
		//VRV_REG_METATYPE(std::map<std::string, std::vector<int64>>);
		qRegisterMetaType<std::map<int64,data::MsgImg>>("std::map<int64,data::MsgImg>");
		qRegisterMetaType<std::map<std::string,std::vector<int64>>>("std::map<std::string,std::vector<int64>>");
	}
};	 
