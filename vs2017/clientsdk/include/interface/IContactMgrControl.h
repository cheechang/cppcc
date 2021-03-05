#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include "data/ContactData.h"
#include "data/ChatData.h"
#include "data/SearchData.h"
namespace control {
	class IContactMgrControl:public IControl {
	public:
	/**
	* \brief 监听联系人头像更新
	* @param[out]  cb _1 传入目标ID，人或者群;  _2	  传入头像;
	*/
	virtual void RegContactHeadImgUpdateCb(CFunction < void(int64, const std::string&) > cb) = 0;
	
	/**
	* \brief 设置监听在线状态更新的回调
	* @param[out] cb _1 在线状态 见packet.h
	*/
	virtual void RegPresentCb(CFunction< void(const data::OnlineState&) > cb) = 0;

	/**
	*  \brief 设置好友信息更新的回调
	* @param[out] cb _1 传入操作类型  1: 增加 2: 更新，3: 删除; _2  传入变更的联系人; 
	*/
	virtual void RegOperateBuddyCb(CFunction< void(int, const data::Contact&) > cb) = 0;

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
	virtual void RegBuddyListCb(CFunction< void(int, std::vector<data::Contact>&) > cb) = 0;


	/*****************************************请求接口*******************************************/

	/**
	* \brief 添加联系人
	* @param[in] userid 传入联系人ID
	* @param[in] remark 传入联系人备注，可以为空
	* @param[in] info   传入验证信息
	* @param[out] cb  传入接收结果回调 _1错误信息
	*/
	virtual void AddContact(int64 userid, const std::string &remark, const std::string &info, 
							CFunction<void(int)> cb) = 0;

	/**
	* \brief 直接添加联系人，不需要验证
	* @param[in] userid 传入联系人ID
	* @param[in] remark 传入联系人备注，可以为空
	* @param[in] info   传入验证信息
	* @param[out] cb  传入接收结果回调 _1错误信息
	*/
	virtual void AddContactNoVerify(int64 userid, const std::string &remark, const std::string &info,
				CFunction<void(int)> cb) = 0;

	/**
	* \brief 获取联系人验证方式
	* @param[in] userid 传入联系人ID
	* @param[out] cb  传入接收结果回调 _1 错误信息 _2验证方式
	*/
	virtual void GetVerifyType(int64 userid, CFunction<void(int, data::ContactVerifyType&)> cb) = 0;

	/**
	* \brief 删除联系人
	* @param[in] userid 传入联系人ID
	* @param[out] cb  传入接收结果回调 _1 错误信息
	*/
	virtual void RemoveContact(int64 userid, CFunction<void(int)> cb) = 0;

	/**
	* \brief 更新联系人信息（星标&V标&备注）
	* @param[in] info 传入联系人信息 见contact.h
	* @param[out] cb  传入接收结果回调 _1错误信息
	*/
	virtual void UpdateContactInfo(data::Contact &info, CFunction<void(int)> cb) = 0;

	/**
	* \brief 获取联系人列表 （同步接口）
	* @param[out]  contacts 所有的联系人信息;
	*/
	virtual void GetContactList(std::vector< CSharedPtr<data::Contact> > &contacts, bool isSort = false, bool isFilterApp = true) = 0;

	/**
	* \brief 获取联系人在线状态
	* @param[in] users 传入联系人集合 如果为空则查所有联系人状态
	* @param[out] cb  传入接收结果回调 _1 错误信息; _2 在线状态
	*/
	virtual void GetContactOnline(std::vector<int64> &users, CFunction<void(int, std::vector<data::OnlineState>&)> cb) = 0;

	/**
	* \brief 获取联系人信息 ( 同步接口 )
	* @param[in] userid 用户ID
	* @param[out] contact  联系人信息
	* @return 操作结果
	*/
	virtual bool GetContactInfo(int64 userid, data::Contact& contact) = 0;

	/**
	* \brief 判断联系人与自己是否是好友关系 ( 同步接口 )
	* @param[in] userid 用户ID
	* @return true为好友  false非好友
	*/
	virtual bool ContactIsBuddy(int64 userId) = 0;

	/**
	* \brief 根据条件查询拓展字段信息 根据dicKey和parentId共同查询拓展字段.
	* @param[in] dicKey 要查询的字段
	* @param[in] parentID 父组织ID 当parentId为-1时表示查询所有的拓展字段;当parentId为-2 时按dicKey查询
	* @param[out] cb 传入接收结果回调  _1错误信息 _2返回的查询信息
	*/
	virtual void queryExtendedField(const std::string &dicKey,int64 parentID, CFunction< void(int, std::vector<data::EnterpriseDictionary>&)> cb) = 0;
    
	/**
	* \brief 获取黑名单
	* @param[out] cb 传入接收结果回调  _1错误信息 _2黑名单ID集合
	*/
	virtual void getBlackList(CFunction<void(int,data::UserBasicData)> cb) = 0;

	/**
	* \brief 添加黑名单
	* @param[in] id 要加入的黑名单的ID
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void addBlackList(int64 id, CFunction<void(int)> cb) = 0;

	/**
	* \brief 删除黑名单
	* @param[in] ids 要删除的黑名单对象ID集合，为空则删除所有黑名单用户
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void removeBlackList(std::vector<int64> &ids, CFunction<void(int)> cb) = 0;


    /**
	* \brief 通过用户ID获取陌生人信息
	* @param[in] userid 传入用户ID
	* @param[in] cb 传入接收结果回调  _1错误信息  _2用户信息
	*/
	//virtual void getUserInfo(int64 userid, CFunction<void(int, data::Contact&)> cb) = 0;

	/**
	*\brief从网络获取好友信息
	*/
	virtual void GetBuddyInfoFromNet(int64 userId,CFunction<void(int,data::Contact&)> cb) = 0;

		/**
	* \brief 从本地数据库进行查找
	* @param[in] key 传入关键字
	* @param[in] cb 传入接收结果回调  _1错误信息  _2搜索结果
	*/
	virtual void searchFromLocal(const std::string &key, CFunction<void(int, std::vector<data::ChatInfo>&)> cb) = 0;
		/**
	* \brief 从网络进行查找
	* @param[in] key 传入关键字
	* @param[in] cb 传入接收结果回调  _1错误信息  _2搜索结果
	*/
	virtual void searchFromNet(const std::string &key, CFunction<void(int, std::vector<data::SearchResultInfo>&)> cb) = 0;

	/**
	* \brief 获取好友扩展信息
	* @param[out] cb _1 
	*/
	virtual void GetBuddyExtendsInfo(int64 userId,CFunction<void(std::vector<data::EnterpriseDictionary>&)>cb) = 0;

	/**
	* \brief 根据用户id分页获取企业号
	* @param[in] req 分页获取条件（页码，每页大小）
	* @param[out] cb 传入接收结果回调 _1错误信息 _2获取结果集合
	*/
	virtual void getEntAccount(CFunction<void(int, std::vector<data::EnterpriseAccount>&)> cb) = 0;

	/**
	* \brief 通过用户ID获取详细信息(同步接口)
	* @param[in] userid 传入用户ID
	* @param[in] info 具体信息
	*/
	virtual void getUserInfoSync(int64 userid, data::Contact& info)=0;
};
	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}