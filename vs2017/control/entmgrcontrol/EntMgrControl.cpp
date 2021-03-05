#include "EntMgrControl.h"
#include "../controlmanager/core/ControlManager.h"
#include "interface/IMClient.h"
#include "../../utils/common.h"
#include "IControl.h"
#include "log.h"
const char * filename = 0;
int line = 0;

namespace control{
  service::IMClient* g_client =CNull;
  EntMgrControl::EntMgrControl(const std::string &strName):m_pluginname(strName),m_entservice(CNull),m_isLoaded(false){
BEGIN;
END;
  }

  EntMgrControl::~EntMgrControl(){
BEGIN;
END;
  }

std::string EntMgrControl::GetName(){
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
		return result;
	}

std::string EntMgrControl::GetDisplayName(){
		return m_pluginname;
	}

void EntMgrControl::SetSdkClientObj(void* obj){
BEGIN;
		g_client=static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK客户端对象指针失败");
			return;
		}
		m_entservice = LDDSERVICE;
END;
	}

void EntMgrControl::getVisibleOrgUsers( int64 orgId,CFunction<void(int code,std::vector<data::OrgAndUserInfo>)> cb )
{
BEGIN;
	//m_funcGetVisibleOrgUsers = cb;
	m_funcGetVisibleOrgUsers.push_back(cb);
	AddLog(LOG_LEV_INFO,"=====orgId:%ld",orgId);
	if (m_entservice)
	{
		if (m_isLoaded == false)
		{
			m_entservice->regEntUpdateFinishCb(CBind(&EntMgrControl::onUpdateFinished,this,CPlaceholders  _1,orgId));
			return;
		}
		m_entservice->getVisibleOrgUsers(0,0,orgId,CBind(&EntMgrControl::onGetVisibleOrgUsers,this,CPlaceholders  _1,
			CPlaceholders  _2,CPlaceholders  _3,CPlaceholders  _4,CPlaceholders  _5));
	}
END;
}

void EntMgrControl::onUpdateFinished(int err, int orgId)
{
BEGIN;
	m_isLoaded = true;
	m_entservice->getVisibleOrgUsers(0,0,orgId,CBind(&EntMgrControl::onGetVisibleOrgUsers,this,CPlaceholders  _1,
		CPlaceholders  _2,CPlaceholders  _3,CPlaceholders  _4,CPlaceholders  _5));
END;
}

void EntMgrControl::regEntUpdateFinishCb(CFunction<void(int)> cb)
{
BEGIN;
	if (m_entservice)
	{
		m_entservice->regEntUpdateFinishCb(cb);
	}
END;
}
void EntMgrControl::getOrgInfo(int8 flag, int64 orgId, CFunction<void(int, data::OrgAndUserInfo&)> cb)
{
	BEGIN;
	if (m_entservice)
	{
		m_getOrgInfoCallBack = cb;
		m_entservice->getOrgInfo(flag, orgId, CBind(&EntMgrControl::onGetOrgInfo,this,CPlaceholders  _1,
		CPlaceholders  _2));
	}
	END;
}
void EntMgrControl::onGetOrgInfo(int code, model::OrganizationInfo& orgInfo)
{
	BEGIN;
	data::OrgAndUserInfo info;
	info.remark = orgInfo.remark;
	m_getOrgInfoCallBack(code, info);
	END;
}
void EntMgrControl::onGetVisibleOrgUsers( service::ErrorInfo code, int8 canChat, int8 canVisible, std::vector<OrganizationInfo>&orgs, std::vector<EntpriseUserInfo>&users )
{
BEGIN;
	std::vector<data::OrgAndUserInfo> orgAndUsers;
	int i=0;

	AddLog(LOG_LEV_INFO,"code:%d,canChat:%d,canVisiblie:%d,orgs size:%d,users size:%d",code,canChat,canVisible,orgs
		.size(),users.size());
	for(i=0;i<users.size();++i){
		model::EntpriseUserInfo user = users.at(i);
		data::OrgAndUserInfo node = parceOrgAndUserInfo(user);
		node.status = (canChat == data::ORG_STATUS_CAN_CHAT)?data::ORG_STATUS_CAN_CHAT:data::ORG_STATUS_CANNOT_CHAT;
		orgAndUsers.push_back(node);
	}

	for(i=0;i<orgs.size();++i){
		model::OrganizationInfo org = orgs.at(i);
		data::OrgAndUserInfo node = parceOrgAndUserInfo(org);
		node.status = (canChat == data::ORG_STATUS_CAN_CHAT)?data::ORG_STATUS_CAN_CHAT:data::ORG_STATUS_CANNOT_CHAT;
		orgAndUsers.push_back(node);
	}

	for (int i = 0; i < m_funcGetVisibleOrgUsers.size(); i++)
	{
		GetOrgUserCallBackPtr cb = m_funcGetVisibleOrgUsers.at(i);
		cb(code,orgAndUsers);
	}
	m_funcGetVisibleOrgUsers.clear();
END;
}

data::OrgAndUserInfo EntMgrControl::parceOrgAndUserInfo( model::EntpriseUserInfo& user )
{
	data::OrgAndUserInfo node;
	node.duty = user.duty;
	node.enMail = user.enMail;
	node.enMobile = user.enMobile;
	node.enName = user.enName;
	node.enterpriseID = user.enterpriseID;
	node.head = user.userHead;
	node.leaf = true;
	node.orgID = user.orgID;
	node.orgName = user.orgName;
	node.userID = user.userID;
	node.extend = user.extend;
	utils::string_replace(node.enMobile,"0086","");
	return node;
}

data::OrgAndUserInfo EntMgrControl::parceOrgAndUserInfo( model::OrganizationInfo& org )
{
	data::OrgAndUserInfo node;
	node.enterpriseID = org.enterpriseID;
	node.parentOrgID = org.parentOrgID;
	node.leaf = false;
	node.orgID = org.orgID;
	node.orgName = org.orgName;
	node.remark = org.remark;
	return node;
}

void EntMgrControl::regOrgMemHeadImgUpdateCb( CFunction < void(int64 userId, const std::string&headUrl) > cb )
{
	m_funcOrgMemHeadImgUpdate = cb;
	m_entservice->regOrgMemHeadImgUpdateCb(CBind
		(&EntMgrControl::onRegOrgMemHeadImgUpdateCb,this,CPlaceholders  _1,CPlaceholders  _2));
}

void EntMgrControl::onRegOrgMemHeadImgUpdateCb( int64 userId, const std::string&headUrl )
{
	AddLog(LOG_LEV_INFO,"onRegOrgMemHeadImgUpdateCb:%d,head:%s",userId,headUrl.c_str());
	m_funcOrgMemHeadImgUpdate(userId,headUrl);
}

void EntMgrControl::onQueryEntUserOneById( int code, std::vector<model::EntpriseUserInfo>&orgUsers )
{
	std::vector<data::OrgAndUserInfo> outs;
	for (int i=0;i<orgUsers.size();++i)
	{
		data::OrgAndUserInfo data= parceOrgAndUserInfo(orgUsers.at(i));
		outs.push_back(data);
	}
	m_funcqueryEntUseCallBack(code,outs);
}

void EntMgrControl::queryEntUserOneById( int64 userId, CFunction<void(int, std::vector<data::OrgAndUserInfo>&)> cb )
{
	m_funcqueryEntUseCallBack = cb;
	if(m_entservice){
		m_entservice->queryEntUserOneById(0,userId,CBind(&EntMgrControl::onQueryEntUserOneById,this,
			CPlaceholders  _1,CPlaceholders  _2));
	}
}

extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance(){
		IControl* instance = NULL;
		instance = new EntMgrControl();
		return  instance;
	}

extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance){
		if(NULL != instance){
			delete instance;
			instance = NULL;
		}
	}
}