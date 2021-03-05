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
		* @brief ���ش���׺�Ĳ����
		* @param[in]��
		***********************************************/
		virtual std::string GetName();
		/***********************************************
		* @brief ���ز�����׺�Ĳ����
		* @param[in]��
		***********************************************/
		virtual std::string GetDisplayName();

		/***********************************************
		* @brief ����sdk�ͻ���ʵ������
		* @param[in]��
		***********************************************/
		virtual void SetSdkClientObj(void* obj);

			/**
		* @brief ��ѯ��ҵ�û���Ϣ
		* @param[in] userId  �û�id
		* @param [in] cb  ������ս���ص� _1 �����;_2 ������ҵ�û���Ϣ;
		*/
		virtual void queryEntUserOneById(int64 userId, CFunction<void(int, std::vector<data::OrgAndUserInfo>&)> cb);

		/**
		* @brief ע����ҵ��Ա������ɻص����յ��ص�����������
		* @param[out] cb _1 ��������
		*/
		virtual void regEntUpdateFinishCb(CFunction<void(int)> cb);
		/**
		* @brief ��ȡ��֯��Ϣ
		* @param[in] flag һ�㶼�� 0, ֻ�����ߵ�½��ʱ�� 1
		* @param[in] orgId ��֯Id
		* @param [in] cb  ������ս���ص� _1 �����;_2 ��֯��Ϣ;
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

		std::string m_pluginname; //�������������׺�ģ�
		ILddService_Ptr m_entservice;

		std::vector<GetOrgUserCallBackPtr> m_funcGetVisibleOrgUsers;
		//GetOrgUserCallBackPtr m_funcGetVisibleOrgUsers;
		CFunction<void(int64 userId, const std::string&headUrl)>   m_funcOrgMemHeadImgUpdate;
		QueryEntUseCallBackPtr m_funcqueryEntUseCallBack;
		GetOrgInfoCallBackPtr m_getOrgInfoCallBack;

		bool m_isLoaded;
	};
}