#pragma once
#include <IEntMgrControl.h>
#include <memory>

#include "ServiceDefine.h"
#include "../data/entpriseInfo.h"

namespace service{
	class IMClient;
}
namespace control{
	class EntMgrControl:public IEntMgrControl{
	public:
		typedef CFunction<void(int ,std::vector<data::OrgAndUserInfo>)> GetOrgUserCallBackPtr;
		typedef CFunction<void(int, std::vector<data::OrgAndUserInfo>&)> QueryEntUseCallBackPtr;
		typedef CFunction<void(int, data::OrgAndUserInfo&)> GetOrgInfoCallBackPtr;

		EntMgrControl(const std::string &strName=std::string("entmgrcontrol"));
		virtual ~EntMgrControl();

		void regOrgMemHeadImgUpdateCb(CFunction < void(int64 userId, const std::string&headUrl) > cb);

		void getVisibleOrgUsers(int64 orgId,CFunction<void(int code,std::vector<data::OrgAndUserInfo>)> cb);

		/***********************************************
		* @brief 返回带后缀的插件名
		* @param[in]无
		***********************************************/
		virtual std::string GetName();
		/***********************************************
		* @brief 返回不带后缀的插件名
		* @param[in]无
		***********************************************/
		virtual std::string GetDisplayName();

		/***********************************************
		* @brief 设置sdk客户端实例对象
		* @param[in]无
		***********************************************/
		virtual void SetSdkClientObj(void* obj);

			/**
		* @brief 查询企业用户信息
		* @param[in] userId  用户id
		* @param [in] cb  传入接收结果回调 _1 错误号;_2 返回企业用户信息;
		*/
		virtual void queryEntUserOneById(int64 userId, CFunction<void(int, std::vector<data::OrgAndUserInfo>&)> cb);

		/**
		* @brief 注册企业成员更新完成回调，收到回调代表更新完成
		* @param[out] cb _1 暂无意义
		*/
		virtual void regEntUpdateFinishCb(CFunction<void(int)> cb);
		/**
		* @brief 获取组织信息
		* @param[in] flag 一般都传 0, 只有离线登陆的时候传 1
		* @param[in] orgId 组织Id
		* @param [in] cb  传入接收结果回调 _1 错误号;_2 组织信息;
		*/
		virtual void getOrgInfo(int8 flag, int64 orgId, CFunction<void(int, data::OrgAndUserInfo&)> cb);
	
	protected:
		void onQueryEntUserOneById(int code, std::vector<model::EntpriseUserInfo>&orgUser);
		void onRegOrgMemHeadImgUpdateCb(int64 userId, const std::string&headUrl);
		void onGetVisibleOrgUsers(service::ErrorInfo code, int8 canChat, int8 canVisible, std::vector<OrganizationInfo>&orgs, std::vector<EntpriseUserInfo>&users);
		void onUpdateFinished(int err, int orgId);
		void onGetOrgInfo(int code, model::OrganizationInfo& orgInfo);
	private:
		data::OrgAndUserInfo parceOrgAndUserInfo(model::EntpriseUserInfo& user);
		data::OrgAndUserInfo parceOrgAndUserInfo(model::OrganizationInfo& org);

		std::string m_pluginname; //插件名（不带后缀的）
		ILddService_Ptr m_entservice;

		std::vector<GetOrgUserCallBackPtr> m_funcGetVisibleOrgUsers;
		//GetOrgUserCallBackPtr m_funcGetVisibleOrgUsers;
		CFunction<void(int64 userId, const std::string&headUrl)>   m_funcOrgMemHeadImgUpdate;
		QueryEntUseCallBackPtr m_funcqueryEntUseCallBack;
		GetOrgInfoCallBackPtr m_getOrgInfoCallBack;

		bool m_isLoaded;
	};
}