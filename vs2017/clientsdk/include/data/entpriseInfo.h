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

		int64  userID;               ///< �û�ID userID.
		int64  enterpriseID;         ///< ��ҵID enterpriseID.
		int64  orgID;                ///< ��֯����ID orgID.
		int64  parentOrgID;         ///< ���ڵ� parentOrgID.

		std::string head;			///< ͷ��
		std::string orgName;		///< ��֯�� orgName.
		std::string enName;         ///< ��ҵ���û����� enName.
		std::string duty;           ///< ��ҵ���û�ְλ duty.
		std::string enMail;         ///< ��ҵ���û�email enMail.
		std::string enMobile;       ///< ��ҵ���û��ֻ��� enMobile.

		std::string orgCode;        ///< ��֯�������� orgCode.
		bool        leaf;                  ///< �Ƿ�Ҷ�ڵ� leaf.
		std::string remark;         ///< ��ע remark.
		std::string extend;
		bool canChat;
	};
};