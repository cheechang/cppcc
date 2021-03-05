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
	* @brief 获取组织信息
	* @param[in] flag 一般都传 0, 只有离线登陆的时候传 1
	* @param[in] orgId 组织Id
	* @param [in] cb  传入接收结果回调 _1 错误号;_2 组织信息;
	*/
	virtual void getOrgInfo(int8 flag, int64 orgId, CFunction<void(int, data::OrgAndUserInfo&)> cb) = 0;
	
	virtual void getVisibleOrgUsers(int64 orgId,CFunction<void(int code,std::vector<data::OrgAndUserInfo>)> cb) = 0;

	/**
	* @brief 查询企业用户信息
	* @param[in] userId  用户id
	* @param [in] cb  传入接收结果回调 _1 错误号;_2 返回企业用户信息;
	*/
	virtual void queryEntUserOneById(int64 userId, CFunction<void(int, std::vector<data::OrgAndUserInfo>&)> cb) = 0;
};
extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}

