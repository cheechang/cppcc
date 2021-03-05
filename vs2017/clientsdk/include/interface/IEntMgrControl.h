#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include "../data/entpriseInfo.h"
namespace control{
class IEntMgrControl:public IControl{
public:
	virtual void regOrgMemHeadImgUpdateCb(CFunction < void(int64 userId, const std::string&headUrl) > cb) = 0;
	/**
	* @brief ��ȡ��֯��Ϣ
	* @param[in] flag һ�㶼�� 0, ֻ�����ߵ�½��ʱ�� 1
	* @param[in] orgId ��֯Id
	* @param [in] cb  ������ս���ص� _1 �����;_2 ��֯��Ϣ;
	*/
	virtual void getOrgInfo(int8 flag, int64 orgId, CFunction<void(int, data::OrgAndUserInfo&)> cb) = 0;
	
	virtual void getVisibleOrgUsers(int64 orgId,CFunction<void(int code,std::vector<data::OrgAndUserInfo>)> cb) = 0;

	/**
	* @brief ��ѯ��ҵ�û���Ϣ
	* @param[in] userId  �û�id
	* @param [in] cb  ������ս���ص� _1 �����;_2 ������ҵ�û���Ϣ;
	*/
	virtual void queryEntUserOneById(int64 userId, CFunction<void(int, std::vector<data::OrgAndUserInfo>&)> cb) = 0;
};
extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}

