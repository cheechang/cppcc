#include "ContactMgrControl.h"
#include "interface/IMClient.h"
#include "IControl.h"
#include "log.h"
#include "data/ContactData.h"
#include "data/UserData.h"
#include <json.h>
#include "../utils/common.h"
const char * filename = 0;
int line = 0;

namespace control{
  service::IMClient* g_client =CNull;

  bool PinyinCmp(const CSharedPtr<data::Contact>& lhs, const CSharedPtr<data::Contact>& rhs){
	  return !lhs->pinyin.value().empty() && !rhs->pinyin.value().empty() && (lhs->pinyin.value().at(0)<rhs->pinyin.value().at(0));
  }
  bool PinyinCmpDesc(const  CSharedPtr<data::Contact>& lhs, const  CSharedPtr<data::Contact> &rhs){
	  return !lhs->pinyin.value().empty() && !rhs->pinyin.value().empty() && (lhs->pinyin.value().at(0)>rhs->pinyin.value().at(0));
  }

  bool SpecialCharCount(const  CSharedPtr<data::Contact>& lhs){
	  return !lhs->pinyin.value().empty() && (lhs->pinyin.value().at(0)<97 || lhs->pinyin.value().at(0)>122);
  }
  bool IsSameOnlineId(const data::OnlineState& lhs, const data::OnlineState& rhs){
	  return lhs.userID == rhs.userID;
  }

  ContactMgrControl::ContactMgrControl(const std::string &strName):m_pluginname(strName),m_contactservice(CNull){
BEGIN;
	
END;
  }
  ContactMgrControl::~ContactMgrControl(){
BEGIN;
END;
  }
	/***********************************************
	* @brief 返回带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string ContactMgrControl::GetName(){
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
		return result;
	}
	/***********************************************
	* @brief 返回不带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string ContactMgrControl::GetDisplayName(){
		return m_pluginname;
	}
	/***********************************************
	* @brief 设置sdk客户端实例对象
	* @param[in]无
	***********************************************/
    void ContactMgrControl::SetSdkClientObj(void* obj){
BEGIN;
		g_client =static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK客户端对象指针失败");
			return;
		}
		m_contactservice = CONTACTSERVICE;
		m_searchservice = SEARCHSERVICE;
		m_userservice = USERSERVICE;
		m_groupservice = GROUPSERVICE;
		m_entservice = LDDSERVICE;
END;
	}

	void ContactMgrControl::RegContactHeadImgUpdateCb( CFunction < void(int64 id, const std::string&head) > cb )
	{
		if(m_contactservice){
			m_BuddyHeadUpCb.push_back(cb);
			m_contactservice->regContactHeadImgUpdateCb(CBind(&ContactMgrControl::onBuddyHeadUpData,this,
				CPlaceholders  _1, CPlaceholders  _2));
		}
	}

	void ContactMgrControl::onBuddyHeadUpData(int64 id, const std::string& head)
	{
		for (int i = 0; i < m_BuddyHeadUpCb.size();i++)
		{
			if (m_BuddyHeadUpCb.at(i))
				m_BuddyHeadUpCb.at(i)(id, head);
		}
	}

	void ContactMgrControl::RegPresentCb( CFunction< void(const data::OnlineState&states) > cb )
	{
		if(m_contactservice){
			mRegPresentCb.push_back(cb);
			m_contactservice->regPresentCb(CBind(&ContactMgrControl::onRegPresentCb,this,
				CPlaceholders  _1));
		}
	}

	void ContactMgrControl::RegOperateBuddyCb( CFunction< void(int type, const data::Contact&contacts) > cb )
	{
		mOperateBuddyCb.push_back(cb);
		m_contactservice->regOperateBuddyCb(CBind(&ContactMgrControl::onOperateBuddyCb,this,
			CPlaceholders  _1,CPlaceholders  _2));
	}

	void ContactMgrControl::RegBuddyListCb( CFunction< void(int type, std::vector<data::Contact>&contacts) > cb )
	{
		AddLog(LOG_LEV_INFO,"======RegBuddyListCb========");

		mBuddyListCb = cb;
		m_contactservice->regBuddyListCb(CBind(&ContactMgrControl::onBuddyListCb,this,
			CPlaceholders  _1,CPlaceholders  _2));
	}

	void ContactMgrControl::AddContact( int64 userid, const std::string &remark, const std::string &info, CFunction<void(int code)> cb )
	{
		m_contactservice->addContact(userid, remark, info, cb);
	}

	void ContactMgrControl::AddContactNoVerify( int64 userid, const std::string &remark, const std::string &info, CFunction<void(int code)> cb )
	{

	}

	void ContactMgrControl::GetVerifyType( int64 userid, CFunction<void(int, data::ContactVerifyType&type)> cb )
	{
		mContactVerifyTypeCb = cb;
		m_contactservice->getVerifyType(userid, CBind(&ContactMgrControl::onGetVerifyType,this,
			CPlaceholders  _1,CPlaceholders  _2));
	}

	void ContactMgrControl::RemoveContact( int64 userid, CFunction<void(int code)> cb )
	{
		if(m_contactservice){
			m_contactservice->removeContact(userid,cb);
		}
	}

	void ContactMgrControl::UpdateContactInfo( data::Contact &info, CFunction<void(int code)> cb )
	{
		if(m_contactservice){
			model::Contact out;
			DataConvert(info,out);
			m_contactservice->updateContactInfo(out,cb);
		}
	}

	void ContactMgrControl::GetContactList(std::vector< CSharedPtr<data::Contact> > &contacts, bool isSort, bool isFilterApp)
	{
		if(m_contactservice != CNull){
			std::vector< SSharedPtr<model::Contact> > ins;
			m_contactservice->getContactList(ins);
			AddLog(LOG_LEV_INFO,"contacts:%d",ins.size());
			int size = ins.size();
			if (isSort)
			{
				for (int i = 0; i<ins.size(); ++i)
				{
					//过滤app
					if (ins.at(i)->isApp.value() == 1){
						continue;
					}
					CSharedPtr<data::Contact> out = CMakePtr<data::Contact>();;
					DataConvert(ins.at(i), *out.get());
					contacts.push_back(out);
				}
				std::sort(contacts.begin(), contacts.end(), PinyinCmp);//根据Pinyin升序排序
				int32 specialCharCount = std::count_if(contacts.begin(), contacts.end(), SpecialCharCount);//统计特殊分组个数
				std::sort(contacts.begin(), contacts.end(), PinyinCmpDesc);//根据Pinyin降序排序
				if (contacts.size()>specialCharCount){
					std::sort(contacts.begin(), contacts.end() - specialCharCount, PinyinCmp);//根据Pinyin升序排序
				}
			}
			else{
				for (int i = 0; i<ins.size(); ++i)
				{
					CSharedPtr<model::Contact> in = ins.at(i);
					CSharedPtr<data::Contact>out = CMakePtr<data::Contact>();
					out->isApp = in->isApp.value();
					out->extends = in->extends.value();
					out->id = in->id.value();
					out->thumbAvatar = utils::GetHeadPath(in->isApp.value() == 1 ? 4 : in->gender.value(), in->thumbAvatar.value().c_str());
					out->name = in->name.value();
					if (in->remark.value().empty())
					{
						out->remark = in->name.value();
					}
					else{
						out->remark = in->remark.value();
					}
					contacts.push_back(out);
				}
			}
		}
	}

	void ContactMgrControl::DataConvert(const CSharedPtr<model::Contact>& in, data::Contact&out)
	{
		if (in->gender.isSet()){
			out.gender = in->gender.value();
		}
		if (in->isApp.isSet()){
			out.isApp = in->isApp.value();
		}
		if (in->isStar.isSet()){
			out.isStar = in->isStar.value();
		}
		if (in->remark.isSet()){
			out.remark = in->remark.value();
		}
		if (in->thumbAvatar.isSet()){
			out.thumbAvatar = utils::GetHeadPath(in->isApp.value() == 1 ? 4 : in->gender.value(), in->thumbAvatar.value().c_str());
		}
		if (in->name.isSet()){
			out.name = in->name.value();
		}
		if (in->emails.isSet()){
			out.emails = in->emails.value();
		}
		if (in->pinyin.isSet()){
			out.pinyin = in->pinyin.value();
		}
		if (in->extends.isSet())
		{
			out.extends = in->extends.value();
		}
		if (in->phones.isSet()){
			out.phones = in->phones.value();
		}
		if (in->privateMsgPwd.isSet()){
			out.privateMsgPwd = in->privateMsgPwd.value();
		}
		Log(LOG_LEV_INFO, LOG_FILE, "========================emails:%d,phones:%d,extends:%s,pinyin:%s,isApp=%d", in->emails.value().size(), in->phones.value().size(), in
			->extends.value().c_str(), out.pinyin.value().c_str(), out.isApp.value());
		out.id = in->id.value();
	}

	void ContactMgrControl::GetContactOnline( std::vector<int64> &users, CFunction<void(int, std::vector<data::OnlineState>&)> cb )
	{
		if (m_contactservice != CNull)
		{
			mOnlineCb = cb;
			m_contactservice->getContactOnline(users,CBind(&ContactMgrControl::onGetContactOnline,this,
				CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	bool ContactMgrControl::GetContactInfo( int64 userid, data::Contact& contact )
	{
		bool ret = false;
		if (m_contactservice != CNull)
		{
			model::Contact in;
			ret = m_contactservice->getContactInfo(userid, in);
			DataConvert(in, contact);
			if (contact.thumbAvatar.value().empty())
			{
				contact.thumbAvatar = utils::GetHeadPath(contact.isApp.value()==1?4:contact.gender.value(),contact.thumbAvatar.value().c_str());
			}
		}
		return ret;
	}

	bool ContactMgrControl::ContactIsBuddy( int64 userId )
	{
		if (m_contactservice != CNull){
			return m_contactservice->contactIsBuddy(userId);
		}
		return false;
	}
	
	void ContactMgrControl::queryExtendedField(const std::string &dicKey,int64 parentID, CFunction<void(int, std::vector<data::EnterpriseDictionary>&)> cb)
	{
		mDictCb = cb;
		
		m_contactservice->queryExtendedField(dicKey, parentID, CBind(&ContactMgrControl::onQueryExtendedField,
				this,CPlaceholders  _1,CPlaceholders  _2));
	}
	void ContactMgrControl::onQueryExtendedField(int code, std::vector<EnterpriseDictionary>& dict)
	{
		std::vector<EnterpriseDictionary>::iterator iter = dict.begin();
		std::vector<data::EnterpriseDictionary> dataDicts;
		while (iter != dict.end())
		{
			data::EnterpriseDictionary dictTmp;

			dictTmp.dickey = iter->dickey;
			dictTmp.dicValue = iter->dicValue;
			dictTmp.extend = iter->extend;
			dictTmp.id = iter->id;
			dictTmp.parentId = iter->parentId;
			dataDicts.push_back(dictTmp);
			iter++;
		}
		mDictCb(code, dataDicts);
	}

	void ContactMgrControl::onSerQueryExtendedField( std::vector<std::string>&keys,std::map<std::string,std::string>&mapKeys,std::vector<data::EnterpriseDictionary>&outResults,service::ErrorInfo code, std::vector<model::EnterpriseDictionary>&dics )
	{
		std::string key = keys.at(0);
		for (int i=0;i<dics.size();++i)
		{
			model::EnterpriseDictionary dic = dics.at(i);
			data::EnterpriseDictionary out;
			out.dicRealValue = mapKeys[key];
			out.id = dic.id;
			out.parentId = dic.parentId;
			out.dickey = dic.dickey;
			out.dicValue = dic.dicValue;
			out.extend = dic.extend;
			//解析可见性字段
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(dic.extend,root);
			if(ret){
				if (dic.extend.find("isEdit")>0)
				{
					out.isEdit = root["isEdit"].asInt();
				}else  if (dic.extend.find("isFriend")>0)
				{
					out.isFriend = root["isFriend"].asInt();
				}else  if (dic.extend.find("isInput")>0)
				{
					out.isInput = root["isInput"].asInt();
				}
				else  if (dic.extend.find("isLogin")>0)
				{
					out.isLogin = root["isLogin"].asInt();
				}
				else  if (dic.extend.find("isShow")>0)
				{
					out.isShow = root["isShow"].asInt();
				}
			}else{
				AddLog(LOG_LEV_INFO,"err---------------------parse:%s",dic.extend.c_str());
			}
			outResults.push_back(out);
		}
		//删除一查询项目
		 std::vector<std::string>::iterator iter = keys.begin();
		 keys.erase(iter);
		 if (keys.size()>0)//还有查询项
		 {
			 m_contactservice->queryExtendedField(keys.at(0), -2, CBind(&ContactMgrControl::onSerQueryExtendedField,
				 this,keys,mapKeys,outResults,CPlaceholders  _1,CPlaceholders  _2));
		 }else{
			 mGetBuddyExtendsInfoCb(outResults);
		 }
	}



	void ContactMgrControl::GetBuddyInfoFromNet(int64 userId, CFunction<void(int, data::Contact&)> cb)
	{
		if (m_contactservice != CNull)
		{
			if (m_getBuddyInfoFromNetCbMap.find(userId) == m_getBuddyInfoFromNetCbMap.end())
			{
				m_getBuddyInfoFromNetCbMap[userId] = cb;
			}
			m_contactservice->getBuddyInfoFromNet(userId, CBind(&ContactMgrControl::onGetBuddyInfoFromNet,
				this, CPlaceholders  _1, CPlaceholders  _2, userId));
		}
	}

	void ContactMgrControl::onGetBuddyInfoFromNet(service::ErrorInfo code, model::Contact& contact,int64 id)
	{
		if (m_getBuddyInfoFromNetCbMap.find(id) != m_getBuddyInfoFromNetCbMap.end())
		{
			data::Contact out;
			DataConvert(contact, out);
			if(out.thumbAvatar.value().empty()){
				out.thumbAvatar = utils::GetHeadPath(out.isApp.value()==1?4:out.gender.value(),out.thumbAvatar.value().c_str());
			}
			m_getBuddyInfoFromNetCbMap[id](code, out);
			m_getBuddyInfoFromNetCbMap.erase(id);
		}
	}

	void ContactMgrControl::onBuddyListCb( int type, std::vector<model::Contact>&contacts )
	{
		AddLog(LOG_LEV_INFO,"type:%d,size:%d",type,contacts.size());
		std::vector<data::Contact>outs;
		for(int i=0;i<contacts.size();++i){
			data::Contact out;
			DataConvert(contacts.at(i),out);
			

			model::Contact extends;
			m_searchservice->getUserInfoSync(out.id.value(), extends);
			if(extends.extends.isSet()){
				out.extends = extends.extends.value();
			}
			if(extends.phones.isSet()){
				out.phones = extends.phones.value();
			}
			if(extends.emails.isSet()){
				out.emails = extends.emails.value();
			}

			if (extends.entExtends.isSet())
			{
				out.entExtends = extends.entExtends.value();
			}
			outs.push_back(out);
		}
		mBuddyListCb(type,outs);
	}

	void ContactMgrControl::DataConvert( const model::Contact& in,data::Contact&out )
	{
		if(in.gender.isSet()){
			out.gender = in.gender.value();
		}
		if(in.isApp.isSet()){
			out.isApp = in.isApp.value();
		}
		if(in.isStar.isSet()){
			out.isStar = in.isStar.value();
		}
		if(in.remark.isSet()){
			out.remark = in.remark.value();
		}
		if(in.thumbAvatar.isSet()){
			out.thumbAvatar = utils::GetHeadPath(in.isApp.value()==1?4:in.gender.value(),in.thumbAvatar.value().c_str());
		}

		if(in.name.isSet()){
			out.name = in.name.value();
		}
		if(in.emails.isSet()){
			out.emails = in.emails.value();
		}
		if(in.pinyin.isSet()){
			out.pinyin = in.pinyin.value();
		}
		if(in.phones.isSet()){
			out.phones = in.phones.value();
		}
		if(in.privateMsgPwd.isSet()){
			out.privateMsgPwd = in.privateMsgPwd.value();
		}

		if (in.extends.isSet())
		{
			out.extends = in.extends.value();
		}

		if (in.entExtends.isSet())
		{
			out.entExtends = in.entExtends.value();
		}
		AddLog(LOG_LEV_INFO,"========================emails:%d,phones:%d,extends:%s,pinyin:%s,isApp=%d",in.emails.value().size(),in.phones.value().size(),in
			.extends.value().c_str(),out.pinyin.value().c_str(),out.isApp.value());
		out.id = in.id.value();
	}

	void ContactMgrControl::DataConvert( const data::Contact &in,model::Contact& out )
	{
		if(in.isApp.isSet()){
			out.isApp = in.isApp.value();
		}
		if(in.isStar.isSet()){
			out.isStar = in.isStar.value();
		}
		if(in.remark.isSet()){
			out.remark = in.remark.value();
		}
		if(in.thumbAvatar.isSet()){
			out.thumbAvatar = in.thumbAvatar.value();
		}
		if(in.name.isSet()){
			out.name = in.name.value();
		}
		if(in.emails.isSet()){
			out.emails = in.emails.value();
		}
		if(in.pinyin.isSet()){
			out.pinyin = in.pinyin.value();
		}
		if(in.phones.isSet()){
			out.phones = in.phones.value();
		}
		if(in.privateMsgPwd.isSet()){
			out.privateMsgPwd = in.privateMsgPwd.value();
		}
		AddLog(LOG_LEV_INFO,"========================emails:%d,phones:%d,extends:%s",in.emails.value().size(),in.phones.value().size(),in
			.extends.value().c_str());
		out.id = in.id.value();
	}

	void ContactMgrControl::getUserInfoSync( int64 userid, data::Contact& in )
	{
		if(m_searchservice){
			model::Contact out;
			m_searchservice->getUserInfoSync(userid, out);
			DataConvert(out,in);
		}
	}

	void ContactMgrControl::onOperateBuddyCb( int type,const model::Contact&contacts )
	{
		data::Contact out;
		DataConvert(contacts,out);

		model::Contact extends;
		m_searchservice->getUserInfoSync(out.id.value(), extends);
		if(extends.extends.isSet()){
			out.extends = extends.extends.value();
		}
		if(extends.phones.isSet()){
			out.phones = extends.phones.value();
		}
		if(extends.emails.isSet()){
			out.emails = extends.emails.value();
		}
		if (extends.entExtends.isSet())
		{
			out.entExtends = extends.entExtends.value();
		}
		for (int i=0;i<mOperateBuddyCb.size();++i)
		{
			mOperateBuddyCb.at(i)(type,out);
		}
	}
	void ContactMgrControl::onGetVerifyType(service::ErrorInfo code, model::ContactVerifyType& type)
	{
		data::ContactVerifyType dataInfo;
		dataInfo.userid = type.userid;
		dataInfo.type = type.type;

		mContactVerifyTypeCb(code, dataInfo);

	}
	void ContactMgrControl::searchFromLocal( const std::string &key, CFunction<void(int, std::vector<data::ChatInfo>&)> cb )
	{
		if(m_searchservice){
			mSearchFromLocalCb = cb;
			m_searchservice->searchFromLocal(key,CBind(&ContactMgrControl::onSearchFromLocal,
				this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	/*CHAT_INIT=0,
		BUDDY_CHAT = 1,        ///<好友聊天
		GROUP_CHAT = 2,        ///<群组聊天
		APP_CHAT = 3,		   ///<公众号
		SYSTEM_MSG = 4,        ///<系统消息
		STRANGER_CHAT = 5,     ///<陌生人聊天
		ENT_USER_CHAT = 6,     ///<企业成员聊天
		PHONE_CHAT = 7,        ///<我的设备
		ENT_CHAT,				///<企业号
		APPLICATION_CHAT,		///<应用号
*/
	void ContactMgrControl::onSearchFromLocal( service::ErrorInfo code, SearchResult&res )
	{
		std::vector<data::ChatInfo> outs;
		if(res.users.size()>0){
			insertTeamItem(outs,data::BUDDY_CHAT);
		}
		for(int i=0;i<res.users.size();++i){
			model::User user = res.users.at(i);
			data::ChatInfo data;
			data.avatar = utils::GetHeadPath(user.gender.value(),user.thumbAvatar.value().c_str());
			data.name = user.name.value();
			data.targetid = user.id.value();
			data.chatType = data::BUDDY_CHAT;

			outs.push_back(data);
		}
		
		if(res.groups.size()>0){
			insertTeamItem(outs,data::GROUP_CHAT);
		}
		for(int i=0;i<res.groups.size();++i){
			model::TinyGroup user = res.groups.at(i);
			data::ChatInfo data;
			data.avatar = utils::FileIsExist(user.avatar.value()) ? user.avatar.value() : ":/base/group_head";
			data.name = user.groupName.value();
			data.targetid = user.groupId.value();
			data.chatType = data::GROUP_CHAT;

			outs.push_back(data);
		}
		std::map<std::string, std::vector<OrgUserinfo> > mporgUser = res.mporgUser;
		std::map<std::string, std::vector<OrgUserinfo>>::iterator it;
		if(res.mporgUser.size()>0){
			insertTeamItem(outs,data::ENT_USER_CHAT);
		}
		for(it=mporgUser.begin();it!=mporgUser.end();++it)
		{
			std::vector<OrgUserinfo> orgs = it->second;
			for(int i=0;i<orgs.size();++i){
				model::OrgUserinfo user = orgs.at(i);
				data::ChatInfo data;
				data.avatar = utils::GetHeadPath(0,user.userHead.c_str());
				data.name = user.name;
				data.targetid = user.userid;
				data.chatType = data::ENT_USER_CHAT;
				data.lastMsg = user.orgname;
				outs.push_back(data);
			}
		}

		if(res.vtEntApp.size()>0){
			insertTeamItem(outs,data::ENT_CHAT);
		}
		for(int i=0;i<res.vtEntApp.size();++i){
			model::EntAppinfo user = res.vtEntApp.at(i);
			data::ChatInfo data;
			data.avatar = utils::GetHeadPath(4,user.appIcon.c_str());
			data.name = user.appName;
			data.targetid = user.appID;
			data.chatType = data::ENT_CHAT;

			outs.push_back(data);
		}

		mSearchFromLocalCb(code,outs);
	}
	void ContactMgrControl::searchFromNet( const std::string &key, CFunction<void(int, std::vector<data::SearchResultInfo>&)> cb )
	{
		if(m_searchservice){
			mSearchFromNetCb = cb;
			m_searchservice->searchFromNet(key,CBind(&ContactMgrControl::onSearchFromNet,
				this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}
	void ContactMgrControl::onSearchFromNet( service::ErrorInfo code, SearchResult&res )
	{
		model::Account accountInfo;
		m_userservice->getAccountInfo(accountInfo);

		std::vector<data::SearchResultInfo> outs;
		for(int i=0;i<res.users.size();++i){
			model::User user = res.users.at(i);
			data::SearchResultInfo data;
			data.avatar = utils::GetHeadPath(user.gender.value(),user.thumbAvatar.value().c_str());
			data.name = user.name.value();
			data.targetid = user.id.value();
			data.resultType = data::USER_TYPE;
			data.buddyType = user.id.value() == accountInfo.id.value() ? data::IS_MYSELF : ( m_contactservice->contactIsBuddy(user.id.value()) ? data::IS_BUDDY : data::IS_NOTBUDDY);
			outs.push_back(data);
		}

		for(int i=0;i<res.groups.size();++i){
			model::TinyGroup user = res.groups.at(i);
			data::SearchResultInfo data;
			data.avatar = user.avatar.value();
			data.name = user.groupName.value();
			data.targetid = user.groupId.value();
			data.resultType = data::GROUP_TYPE;
			data.isGroupMem = m_groupservice->isInGroup(user.groupId.value(), accountInfo.id.value());
			outs.push_back(data);
		}
		for(int i=0;i<res.vtEntApp.size();++i){
			model::EntAppinfo user = res.vtEntApp.at(i);
			data::SearchResultInfo data;
			data.avatar = utils::GetHeadPath(4,user.appIcon.c_str());
			data.name = user.appName;
			data.targetid = user.appID;
			data.resultType = data::APP_TYPE;
			data.buddyType = m_contactservice->contactIsBuddy(user.appID) ?data::IS_BUDDY : data::IS_NOTBUDDY;
			outs.push_back(data);
		}

		mSearchFromNetCb(code,outs);
	}
	void ContactMgrControl::insertTeamItem( std::vector<data::ChatInfo> &outs ,data::ChatType type)
	{
		data::ChatInfo data;
		data.chatType =type;
		data.targetid = -1;
		outs.push_back(data);
	}

	void ContactMgrControl::onRegPresentCb( const model::OnlineState&onlineState )
	{
		data::OnlineState out;
		out.flag = onlineState.flag;
		out.connectID = onlineState.connectID;
		out.deviceType = onlineState.deviceType;
		out.userID = onlineState.userID;
		for (int i=0;i<mRegPresentCb.size();++i)
		{
			mRegPresentCb.at(i)(out);
		}
		
	}

	void ContactMgrControl::onGetContactOnline( service::ErrorInfo code, std::vector<model::OnlineState>& datas )
	{
		std::vector<data::OnlineState> outs;
		for (int i=0;i<datas.size();++i)
		{
			model::OnlineState in = datas.at(i);
			data::OnlineState out;
			out.userID = in.userID;
			out.flag = in.flag;
			out.deviceType = in.deviceType;
			out.connectID = in.connectID;
			outs.push_back(out);
		}
		mOnlineCb(code,outs);
	}

	void ContactMgrControl::getBlackList( CFunction<void(int,data::UserBasicData)> cb )
	{
        m_getUserInfoBuIDCb = cb;
		if (m_contactservice != CNull)
		{
			m_contactservice->getBlackList(CBind(&ContactMgrControl::onGetBackList,this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	void ContactMgrControl::onGetBackList( service::ErrorInfo code,std::vector<int64>&list )
	{
		if (code != 0 || list.empty() || !m_searchservice)
		{
            return;
		}

        for(int i=0; i< list.size(); ++i)
        {
             m_searchservice->getUserInfo(list.at(i),CBind(&ContactMgrControl::onGetUserInfoByIDCb,this,CPlaceholders _1,CPlaceholders _2));
        }
	}

    void ContactMgrControl::onGetUserInfoByIDCb( service::ErrorInfo code, model::User& result )
    {
        data::UserBasicData user;
        if (code == 0)
        {
            user.id = result.id.value();
            user.name = result.name.value();
            user.thumbAvatar = utils::GetHeadPath(result.gender.value(),result.thumbAvatar.value().c_str());
        }

        m_getUserInfoBuIDCb(code,user);
    }

	void ContactMgrControl::GetBuddyExtendsInfo( int64 userId,CFunction<void(std::vector<data::EnterpriseDictionary>&)>cb )
	{
		mGetBuddyExtendsInfoCb = cb;
		if (m_entservice)
		{
			m_entservice->queryEntUserOneById(0,userId,CBind(&ContactMgrControl::onReqEntUserById,this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	void ContactMgrControl::parceUserExtendsJson( std::string ext,std::vector<std::string>&keys,std::map<std::string,std::string>&mapKeys )
	{
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(ext,root);
		if(ret){
			Json::Value::Members mems = root.getMemberNames();
			for (Json::Value::Members::iterator i=mems.begin(); i!=mems.end(); i++)
			{
				std::string key = *i;
				std::string value = root[key].asString();
				keys.push_back(key);
				mapKeys[key] = value;
			}
		}
	}

	void ContactMgrControl::onReqEntUserById( service::ErrorInfo code, std::vector<model::EntpriseUserInfo>&users )
	{
		if (code != 0 ||users.size() == 0)
		{
			std::vector<data::EnterpriseDictionary>list;
			mGetBuddyExtendsInfoCb(list);
		}else{
			std::map<std::string,std::string> mapKeys;
			std::vector<std::string>keys;
			parceUserExtendsJson(users.at(0).extend,keys,mapKeys);
			if (keys.size() == 0)
			{
				std::vector<data::EnterpriseDictionary>list;
				mGetBuddyExtendsInfoCb(list);
			}else{
				std::vector<data::EnterpriseDictionary>outResults;
				m_contactservice->queryExtendedField(keys.at(0),-2,CBind(&ContactMgrControl::onSerQueryExtendedField,this,keys,mapKeys,outResults,CPlaceholders _1,CPlaceholders _2));
			}
		}
	}
	
	void ContactMgrControl::getEntAccount(CFunction<void(int, std::vector<data::EnterpriseAccount>&)> cb)
	{
	BEGIN;
		m_getEntAccountCb = cb;
		if (m_userservice != CNull)
		{
			reqEntAppInfo req;
			req.type = 1;
			req.pageNum = 1;
			req.pageSize = 100;
			m_userservice->getEntAppInfo(req, CBind(&ContactMgrControl::onGetEntAccount,
				this, CPlaceholders _1, CPlaceholders _2, CPlaceholders _3, CPlaceholders _4));
		}
		else
		{
			AddLog(LOG_LEV_INFO,"m_userservice = null");
		}
	END;
	}

	void ContactMgrControl::onGetEntAccount(service::ErrorInfo code, int64 amount, 
		int64 pageAmount, std::vector<model::EntAppinfo>& ents)
	{
	BEGIN;
		std::vector<data::EnterpriseAccount> entAccounts;
		if (code == 0)
		{
			AddLog(LOG_LEV_INFO,"size = %d", ents.size());
			for (int i = 0; i < ents.size(); i++)
			{
				AddLog(LOG_LEV_INFO,"ent id = %lld, name = %s, icon = %s",
					ents[i].entID, ents[i].entName.data(), ents[i].appIcon.data());
				model::EntAppinfo in = ents.at(i);
				data::EnterpriseAccount entAccount;
				entAccount.id = ents[i].appID;
				entAccount.name = ents[i].appName;
				entAccount.thumbAvatar = utils::GetHeadPath(4,ents[i].appIcon);
				entAccounts.push_back(entAccount);
			}
		}
		else
		{
			AddLog(LOG_LEV_WARN,"err = %d", code);
		}
		m_getEntAccountCb(code, entAccounts);
	END;
	}

    void ContactMgrControl::addBlackList(int64 id, CFunction<void(int)> cb)
    {
        if (m_contactservice)
        {
			std::vector<int64> ids;
			ids.push_back(id);
            m_contactservice->addBlackList(ids, cb);
        }
    }

    void ContactMgrControl::removeBlackList( std::vector<int64> &ids, CFunction<void(int)> cb )
    {
        if (m_contactservice)
        {
            m_contactservice->removeBlackList(ids,cb);
        }
    }


	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance(){
		IControl* instance = NULL;
		instance = new ContactMgrControl();
		return  instance;
	}
    extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance){
		if(NULL != instance){
			delete instance;
			instance = NULL;
		}
	}
}