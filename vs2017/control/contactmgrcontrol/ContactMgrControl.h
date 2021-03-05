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
	* \brief 监听联系人头像更新
	* @param[out]  cb _1 传入目标ID，人或者群;  _2	  传入头像;
	*/
	virtual void RegContactHeadImgUpdateCb(CFunction < void(int64 id, const std::string&head) > cb);
	
	/**
	* \brief 设置监听在线状态更新的回调
	* @param[out] cb _1 在线状态 见packet.h
	*/
	virtual void RegPresentCb(CFunction< void(const data::OnlineState&states) > cb);

	/**
	*  \brief 设置好友信息更新的回调
	* @param[out] cb _1 传入操作类型  1: 增加 2: 更新，3: 删除; _2  传入变更的联系人; 
	*/
	virtual void RegOperateBuddyCb(CFunction< void(int, const data::Contact&contacts) > cb);

	/**
	* \brief 监听好友刷新
	* @param[out] cb _1 传入操作类型 \n
	* 0x01 包含此标识，清空ＵＩ列表插入下面列表项 \n
	* 0x02　包含此标识，ＵＩ列表尾部添加下面列表项 \n
	* 0x04 包含此标识，所有好友添加完毕 \n
	* 0x08 包含此标识，从当前ＵＩ列表中更新下面列表项　不和其他标识组合 \n
	* 0x10 包含此标识，从当前ＵＩ列表中删除下面列表项　不和其他标识组合 \n
	* [in] _2	  传入变更的联系人
	*/
	virtual void RegBuddyListCb(CFunction< void(int, std::vector<data::Contact>&contacts) > cb);


	/*****************************************请求接口*******************************************/

	/**
	* \brief 获取黑名单
	* @param[out] cb 传入接收结果回调  _1错误信息 _2黑名单ID集合
	*/
	virtual void getBlackList(CFunction<void(int,data::UserBasicData)> cb);

	/**
	* \brief 添加黑名单
	* @param[in] id 要加入的黑名单的ID
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void addBlackList(int64 id, CFunction<void(int)> cb);

    /**
	* \brief 删除黑名单
	* @param[in] ids 要删除的黑名单对象ID集合，为空则删除所有黑名单用户
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void removeBlackList(std::vector<int64> &ids, CFunction<void(int)> cb);

	/**
	* \brief 添加联系人
	* @param[in] userid 传入联系人ID
	* @param[in] remark 传入联系人备注，可以为空
	* @param[in] info   传入验证信息
	* @param[out] cb  传入接收结果回调 _1错误信息
	*/
	virtual void AddContact(int64 userid, const std::string &remark, const std::string &info, 
							CFunction<void(int code)> cb);

	/**
	* \brief 直接添加联系人，不需要验证
	* @param[in] userid 传入联系人ID
	* @param[in] remark 传入联系人备注，可以为空
	* @param[in] info   传入验证信息
	* @param[out] cb  传入接收结果回调 _1错误信息
	*/
	virtual void AddContactNoVerify(int64 userid, const std::string &remark, const std::string &info,
				CFunction<void(int code)> cb) ;

	/**
	* \brief 获取联系人验证方式
	* @param[in] userid 传入联系人ID
	* @param[out] cb  传入接收结果回调 _1 错误信息 _2验证方式
	*/
	virtual void GetVerifyType(int64 userid, CFunction<void(int, data::ContactVerifyType&type)> cb);

	/**
	* \brief 删除联系人
	* @param[in] userid 传入联系人ID
	* @param[out] cb  传入接收结果回调 _1 错误信息
	*/
	virtual void RemoveContact(int64 userid, CFunction<void(int code)> cb);

	/**
	* \brief 更新联系人信息（星标&V标&备注）
	* @param[in] info 传入联系人信息 见contact.h
	* @param[out] cb  传入接收结果回调 _1错误信息
	*/
	virtual void UpdateContactInfo(data::Contact &info, CFunction<void(int code)> cb);

	/**
	* \brief 获取联系人列表 （同步接口）
	* @param[out]  contacts 所有的联系人信息;
	*/
	virtual void GetContactList(std::vector< CSharedPtr<data::Contact> > &contacts, bool isSort = false, bool isFilterApp = true);

	/**
	* \brief 获取联系人在线状态
	* @param[in] users 传入联系人集合 如果为空则查所有联系人状态
	* @param[out] cb  传入接收结果回调 _1 错误信息; _2 在线状态
	*/
	virtual void GetContactOnline(std::vector<int64> &users, CFunction<void(int, std::vector<data::OnlineState>&)> cb);

	/**
	* \brief 获取联系人信息 ( 同步接口 )
	* @param[in] userid 用户ID
	* @param[out] contact  联系人信息
	* @return 操作结果
	*/
	virtual bool GetContactInfo(int64 userid, data::Contact& contact);

	/**
	* \brief 判断联系人与自己是否是好友关系 ( 同步接口 )
	* @param[in] userid 用户ID
	* @return true为好友  false非好友
	*/
	virtual bool ContactIsBuddy(int64 userId);

		/**
	* \brief 根据条件查询拓展字段信息 根据dicKey和parentId共同查询拓展字段.
	* @param[in] dicKey 要查询的字段
	* @param[in] parentID 父组织ID 当parentId为-1时表示查询所有的拓展字段;当parentId为-2 时按dicKey查询
	* @param[out] cb 传入接收结果回调  _1错误信息 _2返回的查询信息
	*/
	virtual void queryExtendedField(const std::string &dicKey,int64 parentID, CFunction< void(int, std::vector<data::EnterpriseDictionary>&)> cb);
    
	/**
	*\brief从网络获取好友信息
	*/
	virtual void GetBuddyInfoFromNet(int64 userId,CFunction<void(int,data::Contact&)> cb);

	/**
	* \brief 通过用户ID获取详细信息(同步接口)
	* @param[in] userid 传入用户ID
	* @param[in] info 具体信息
	*/
	virtual void getUserInfoSync(int64 userid, data::Contact& info);

	/**
	* \brief 从本地数据库进行查找
	* @param[in] key 传入关键字
	* @param[in] cb 传入接收结果回调  _1错误信息  _2搜索结果
	*/
	virtual void searchFromLocal(const std::string &key, CFunction<void(int, std::vector<data::ChatInfo>&)> cb);

	/**
	* \brief 从网络进行查找
	* @param[in] key 传入关键字
	* @param[in] cb 传入接收结果回调  _1错误信息  _2搜索结果
	*/
	virtual void searchFromNet(const std::string &key, CFunction<void(int, std::vector<data::SearchResultInfo>&)> cb);

	/**
	* \brief 获取好友扩展信息
	* @param[out] cb _1 
	*/
	virtual void GetBuddyExtendsInfo(int64 userId,CFunction<void(std::vector<data::EnterpriseDictionary>&)>cb);

	/**
	* \brief 根据用户id分页获取企业号
	* @param[in] req 分页获取条件（页码，每页大小）
	* @param[out] cb 传入接收结果回调 _1错误信息 _2获取结果集合
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

		std::string							m_pluginname; //插件名（不带后缀的）
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