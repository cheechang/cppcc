#pragma once
#include <IContactMgrControl.h>
#include "ServiceDefine.h"
#include <data/ChatData.h>
#include <data/SearchData.h>
#include <data/ContactData.h>
#include <vector>
#include <map>
namespace service{
	class IMClient;
}
namespace control{
	class ContactMgrControl:public IContactMgrControl{
	public:
		typedef CFunction< void(int, std::vector<data::Contact>&)>  BuddyListCallBackPtr;
		typedef CFunction< void(int, const data::Contact&contacts)> OperateBuddyCallBackPtr;
		typedef CFunction<void(int, std::vector<data::ChatInfo>&)> SearchFromLocalCallBackPtr;
		typedef CFunction<void(int, std::vector<data::SearchResultInfo>&)> SearchFromNetCallBackPtr;
		typedef CFunction<void(int, data::ContactVerifyType&)>ContactVerifyTypeCallBackPtr;
		typedef CFunction< void(const data::OnlineState&states) >  RegPresentCbCallBackPtr;
		typedef CFunction<void(int, std::vector<data::EnterpriseDictionary>&)>ContactDictionaryCallBackPtr;
		typedef CFunction<void(int, std::vector<data::OnlineState>&)> GetOnlineStateCallBackPrt;
		typedef CFunction<void(int, std::vector<int64>&)> GetBackListBackPtr;
		typedef CFunction<void(std::vector<data::EnterpriseDictionary>&)> GetBuddyExtendsInfoBackPtr;
		typedef CFunction<void(int, std::vector<data::EnterpriseAccount>&)> GetEntAccountCallBackPtr;
        typedef CFunction<void(int,data::UserBasicData)> getUserInfoByCallBackPtr;
        typedef CFunction<void(int, data::Contact&)> GetBuddyInfoFromNetCallBackPtr;
		typedef CFunction <void(int64 id, const std::string&head)> BuddyHeadUpdataCallBackPtr;

		ContactMgrControl(const std::string &strName=std::string("contactmgrcontrol"));
		virtual ~ContactMgrControl();
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
	* \brief ������ϵ��ͷ�����
	* @param[out]  cb _1 ����Ŀ��ID���˻���Ⱥ;  _2	  ����ͷ��;
	*/
	virtual void RegContactHeadImgUpdateCb(CFunction < void(int64 id, const std::string&head) > cb);
	
	/**
	* \brief ���ü�������״̬���µĻص�
	* @param[out] cb _1 ����״̬ ��packet.h
	*/
	virtual void RegPresentCb(CFunction< void(const data::OnlineState&states) > cb);

	/**
	*  \brief ���ú�����Ϣ���µĻص�
	* @param[out] cb _1 �����������  1: ���� 2: ���£�3: ɾ��; _2  ����������ϵ��; 
	*/
	virtual void RegOperateBuddyCb(CFunction< void(int, const data::Contact&contacts) > cb);

	/**
	* \brief ��������ˢ��
	* @param[out] cb _1 ����������� \n
	* 0x01 �����˱�ʶ����գգ��б���������б��� \n
	* 0x02�������˱�ʶ���գ��б�β����������б��� \n
	* 0x04 �����˱�ʶ�����к��������� \n
	* 0x08 �����˱�ʶ���ӵ�ǰ�գ��б��и��������б������������ʶ��� \n
	* 0x10 �����˱�ʶ���ӵ�ǰ�գ��б���ɾ�������б������������ʶ��� \n
	* [in] _2	  ����������ϵ��
	*/
	virtual void RegBuddyListCb(CFunction< void(int, std::vector<data::Contact>&contacts) > cb);


	/*****************************************����ӿ�*******************************************/

	/**
	* \brief ��ȡ������
	* @param[out] cb ������ս���ص�  _1������Ϣ _2������ID����
	*/
	virtual void getBlackList(CFunction<void(int,data::UserBasicData)> cb);

	/**
	* \brief ��Ӻ�����
	* @param[in] id Ҫ����ĺ�������ID
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void addBlackList(int64 id, CFunction<void(int)> cb);

    /**
	* \brief ɾ��������
	* @param[in] ids Ҫɾ���ĺ���������ID���ϣ�Ϊ����ɾ�����к������û�
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void removeBlackList(std::vector<int64> &ids, CFunction<void(int)> cb);

	/**
	* \brief �����ϵ��
	* @param[in] userid ������ϵ��ID
	* @param[in] remark ������ϵ�˱�ע������Ϊ��
	* @param[in] info   ������֤��Ϣ
	* @param[out] cb  ������ս���ص� _1������Ϣ
	*/
	virtual void AddContact(int64 userid, const std::string &remark, const std::string &info, 
							CFunction<void(int code)> cb);

	/**
	* \brief ֱ�������ϵ�ˣ�����Ҫ��֤
	* @param[in] userid ������ϵ��ID
	* @param[in] remark ������ϵ�˱�ע������Ϊ��
	* @param[in] info   ������֤��Ϣ
	* @param[out] cb  ������ս���ص� _1������Ϣ
	*/
	virtual void AddContactNoVerify(int64 userid, const std::string &remark, const std::string &info,
				CFunction<void(int code)> cb) ;

	/**
	* \brief ��ȡ��ϵ����֤��ʽ
	* @param[in] userid ������ϵ��ID
	* @param[out] cb  ������ս���ص� _1 ������Ϣ _2��֤��ʽ
	*/
	virtual void GetVerifyType(int64 userid, CFunction<void(int, data::ContactVerifyType&type)> cb);

	/**
	* \brief ɾ����ϵ��
	* @param[in] userid ������ϵ��ID
	* @param[out] cb  ������ս���ص� _1 ������Ϣ
	*/
	virtual void RemoveContact(int64 userid, CFunction<void(int code)> cb);

	/**
	* \brief ������ϵ����Ϣ���Ǳ�&V��&��ע��
	* @param[in] info ������ϵ����Ϣ ��contact.h
	* @param[out] cb  ������ս���ص� _1������Ϣ
	*/
	virtual void UpdateContactInfo(data::Contact &info, CFunction<void(int code)> cb);

	/**
	* \brief ��ȡ��ϵ���б� ��ͬ���ӿڣ�
	* @param[out]  contacts ���е���ϵ����Ϣ;
	*/
	virtual void GetContactList(std::vector< CSharedPtr<data::Contact> > &contacts, bool isSort = false, bool isFilterApp = true);

	/**
	* \brief ��ȡ��ϵ������״̬
	* @param[in] users ������ϵ�˼��� ���Ϊ�����������ϵ��״̬
	* @param[out] cb  ������ս���ص� _1 ������Ϣ; _2 ����״̬
	*/
	virtual void GetContactOnline(std::vector<int64> &users, CFunction<void(int, std::vector<data::OnlineState>&)> cb);

	/**
	* \brief ��ȡ��ϵ����Ϣ ( ͬ���ӿ� )
	* @param[in] userid �û�ID
	* @param[out] contact  ��ϵ����Ϣ
	* @return �������
	*/
	virtual bool GetContactInfo(int64 userid, data::Contact& contact);

	/**
	* \brief �ж���ϵ�����Լ��Ƿ��Ǻ��ѹ�ϵ ( ͬ���ӿ� )
	* @param[in] userid �û�ID
	* @return trueΪ����  false�Ǻ���
	*/
	virtual bool ContactIsBuddy(int64 userId);

		/**
	* \brief ����������ѯ��չ�ֶ���Ϣ ����dicKey��parentId��ͬ��ѯ��չ�ֶ�.
	* @param[in] dicKey Ҫ��ѯ���ֶ�
	* @param[in] parentID ����֯ID ��parentIdΪ-1ʱ��ʾ��ѯ���е���չ�ֶ�;��parentIdΪ-2 ʱ��dicKey��ѯ
	* @param[out] cb ������ս���ص�  _1������Ϣ _2���صĲ�ѯ��Ϣ
	*/
	virtual void queryExtendedField(const std::string &dicKey,int64 parentID, CFunction< void(int, std::vector<data::EnterpriseDictionary>&)> cb);
    
	/**
	*\brief�������ȡ������Ϣ
	*/
	virtual void GetBuddyInfoFromNet(int64 userId,CFunction<void(int,data::Contact&)> cb);

	/**
	* \brief ͨ���û�ID��ȡ��ϸ��Ϣ(ͬ���ӿ�)
	* @param[in] userid �����û�ID
	* @param[in] info ������Ϣ
	*/
	virtual void getUserInfoSync(int64 userid, data::Contact& info);

	/**
	* \brief �ӱ������ݿ���в���
	* @param[in] key ����ؼ���
	* @param[in] cb ������ս���ص�  _1������Ϣ  _2�������
	*/
	virtual void searchFromLocal(const std::string &key, CFunction<void(int, std::vector<data::ChatInfo>&)> cb);

	/**
	* \brief ��������в���
	* @param[in] key ����ؼ���
	* @param[in] cb ������ս���ص�  _1������Ϣ  _2�������
	*/
	virtual void searchFromNet(const std::string &key, CFunction<void(int, std::vector<data::SearchResultInfo>&)> cb);

	/**
	* \brief ��ȡ������չ��Ϣ
	* @param[out] cb _1 
	*/
	virtual void GetBuddyExtendsInfo(int64 userId,CFunction<void(std::vector<data::EnterpriseDictionary>&)>cb);

	/**
	* \brief �����û�id��ҳ��ȡ��ҵ��
	* @param[in] req ��ҳ��ȡ������ҳ�룬ÿҳ��С��
	* @param[out] cb ������ս���ص� _1������Ϣ _2��ȡ�������
	*/
	virtual void getEntAccount(CFunction<void(int, std::vector<data::EnterpriseAccount>&)> cb);

	protected:
        void onGetUserInfoByIDCb(service::ErrorInfo code, model::User& user);

		void onBuddyListCb(int type, std::vector<model::Contact>&contacts);
		void onOperateBuddyCb(int type,const model::Contact&contacts);
		void onSearchFromLocal(service::ErrorInfo code, SearchResult&res);
		void onRegPresentCb(const model::OnlineState&onlineState);
		void onSearchFromNet(service::ErrorInfo code, SearchResult&res);
		void onGetVerifyType(service::ErrorInfo code, model::ContactVerifyType& type);
		void onGetContactOnline(service::ErrorInfo code, std::vector<model::OnlineState>& datas);
		void onQueryExtendedField(int code, std::vector<EnterpriseDictionary>& dict);
	    void onGetBackList(service::ErrorInfo code,std::vector<int64>&list);
		void onReqEntUserById(service::ErrorInfo code, std::vector<model::EntpriseUserInfo>&users);
		void onSerQueryExtendedField(std::vector<std::string>&keys,std::map<std::string,std::string>&mapKeys,std::vector<data::EnterpriseDictionary>&outResults,service::ErrorInfo code, std::vector<model::EnterpriseDictionary>&dics);
		void onGetEntAccount(service::ErrorInfo code, int64 amount, int64 pageAmount, std::vector<model::EntAppinfo>& ents);
		void onGetBuddyInfoFromNet(service::ErrorInfo code, model::Contact& contact, int64 id);
		void onBuddyHeadUpData(int64 id, const std::string& head);
private:
		void DataConvert(const data::Contact &in,model::Contact& out);
		void DataConvert(const model::Contact&,data::Contact&out);
		void DataConvert(const CSharedPtr<model::Contact>& in, data::Contact&out);
		void insertTeamItem( std::vector<data::ChatInfo> &outs ,data::ChatType type);
		void parceUserExtendsJson(std::string ext,std::vector<std::string>&keys,std::map<std::string,std::string>&mapKeys);

		std::string							m_pluginname; //�������������׺�ģ�
		IGroupService_Ptr				m_groupservice;
		IUserService_Ptr				m_userservice;
		IContactService_Ptr					m_contactservice;
		ISearchService_Ptr                 m_searchservice;
		ILddService_Ptr                    m_entservice;

		BuddyListCallBackPtr mBuddyListCb;
		std::vector<OperateBuddyCallBackPtr> mOperateBuddyCb;
		std::vector<BuddyHeadUpdataCallBackPtr> m_BuddyHeadUpCb;
		SearchFromLocalCallBackPtr mSearchFromLocalCb;
		std::vector<RegPresentCbCallBackPtr> mRegPresentCb;
		SearchFromNetCallBackPtr  mSearchFromNetCb;
		ContactVerifyTypeCallBackPtr mContactVerifyTypeCb;
		ContactDictionaryCallBackPtr mDictCb;
		GetOnlineStateCallBackPrt mOnlineCb;
		GetBackListBackPtr mGetBackList;
		GetBuddyExtendsInfoBackPtr mGetBuddyExtendsInfoCb;
		GetEntAccountCallBackPtr m_getEntAccountCb;
        getUserInfoByCallBackPtr m_getUserInfoBuIDCb;
		std::map<int64, GetBuddyInfoFromNetCallBackPtr> m_getBuddyInfoFromNetCbMap;
		//GetBuddyInfoFromNetCallBackPtr m_getBuddyInfoFromNetCb;
	};
}