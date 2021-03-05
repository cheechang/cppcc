#pragma once

#include "interface/Defines.h"
#include <string>
namespace data{
	enum ORG_NODE_STATUS{
		ORG_STATUS_NORMAL,
		ORG_STATUS_CAN_CHAT,
		ORG_STATUS_CANNOT_CHAT
	};
	struct OrgAndUserInfo{
		OrgAndUserInfo(){
			userID = enterpriseID = orgID = parentOrgID = 0;
			extend =head = orgName = enName = duty = enMail = enMobile = orgCode = remark = "";
			leaf = false;
			canChat = true;
			status = ORG_STATUS_NORMAL;
		};

		ORG_NODE_STATUS   status;   

		int64  userID;               ///< 用户ID userID.
		int64  enterpriseID;         ///< 企业ID enterpriseID.
		int64  orgID;                ///< 组织机构ID orgID.
		int64  parentOrgID;         ///< 父节点 parentOrgID.

		std::string head;			///< 头像
		std::string orgName;		///< 组织名 orgName.
		std::string enName;         ///< 企业内用户名称 enName.
		std::string duty;           ///< 企业内用户职位 duty.
		std::string enMail;         ///< 企业内用户email enMail.
		std::string enMobile;       ///< 企业内用户手机号 enMobile.

		std::string orgCode;        ///< 组织机构内码 orgCode.
		bool        leaf;                  ///< 是否叶节点 leaf.
		std::string remark;         ///< 备注 remark.
		std::string extend;
		bool canChat;
	};
};