#pragma once

#include "../model/SDKTypes.h"
#include "../model/Packet.h"
#include "../model/Contact.h"
#include "IService.h"

#include <string>
#include <vector>

#define VER_CONTACT INTERFACE_VERSION(1,0)
static const VRVIID IID_IContactService = { 0x3de6bc58, 0x3d6f, 0x4b25, 0x8f, 0x36, 0xc5, 0xb, 0x65, 0x76, 0x44, 0xdd };

namespace service
{

class IContactService :public IService
{
public:

	virtual ~IContactService(){}

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief 监听联系人头像更新
	* @param[out]  cb _1 传入目标ID，人或者群;  _2	  传入头像;
	*/
	virtual void regContactHeadImgUpdateCb(SFunction < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 监听联系人聊天背景更新
	* @param[out]  cb _1 传入目标ID，人或者群;  _2	  传入头像;
	*/
	virtual void regContactBackImgUpdateCb(SFunction < void(int64, const std::string&) > cb) = 0;
	
	/**
	* \brief 设置监听在线状态更新的回调
	* @param[out] cb _1 在线状态 见packet.h
	*/
	virtual void regPresentCb(SFunction< void(const OnlineState&) > cb) = 0;

	/**
	*  \brief 设置好友信息更新的回调
	* @param[out] cb _1 传入操作类型  1: 增加 2: 更新，3: 删除; _2  传入变更的联系人; 
	*/
	virtual void regOperateBuddyCb(SFunction< void(int, const Contact&) > cb) = 0;

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
	virtual void regBuddyListCb(SFunction< void(int, std::vector<Contact>&) > cb) = 0;


	/*****************************************请求接口*******************************************/

	/**
	* \brief 添加联系人
	* @param[in] userid 传入联系人ID
	* @param[in] remark 传入联系人备注，可以为空
	* @param[in] info   传入验证信息
	* @param[out] cb  传入接收结果回调 _1错误信息
	*/
	virtual void addContact(int64 userid, const std::string &remark, const std::string &info, 
							SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 直接添加联系人，不需要验证
	* @param[in] userid 传入联系人ID
	* @param[in] remark 传入联系人备注，可以为空
	* @param[in] info   传入验证信息
	* @param[out] cb  传入接收结果回调 _1错误信息
	*/
	virtual void addContactNoVerify(int64 userid, const std::string &remark, const std::string &info,
				SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取联系人验证方式
	* @param[in] userid 传入联系人ID
	* @param[out] cb  传入接收结果回调 _1 错误信息 _2验证方式
	*/
	virtual void getVerifyType(int64 userid, SFunction<void(ErrorInfo, ContactVerifyType&)> cb) = 0;

	/**
	* \brief 删除联系人
	* @param[in] userid 传入联系人ID
	* @param[out] cb  传入接收结果回调 _1 错误信息
	*/
	virtual void removeContact(int64 userid, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 更新联系人信息（星标&V标&备注）
	* @param[in] info 传入联系人信息 见contact.h
	* @param[out] cb  传入接收结果回调 _1错误信息
	*/
	virtual void updateContactInfo(Contact &info, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取联系人列表 （同步接口）
	* @param[out]  contacts 所有的联系人信息;
	*/
	virtual void getContactList(std::vector< SSharedPtr<Contact> > &contacts) = 0;

	/**
	* \brief 获取联系人在线状态
	* @param[in] users 传入联系人集合 如果为空则查所有联系人状态
	* @param[out] cb  传入接收结果回调 _1 错误信息; _2 在线状态
	*/
	virtual void getContactOnline(std::vector<int64> &users, SFunction<void(ErrorInfo, std::vector<OnlineState>&)> cb) = 0;

	/**
	* \brief 获取联系人信息 ( 同步接口 )
	* @param[in] userid 用户ID
	* @param[out] contact  联系人信息
	* @return 操作结果
	*/
	virtual bool getContactInfo(int64 userid, Contact& contact) = 0;

	/**
	* \brief 判断联系人与自己是否是好友关系 ( 同步接口 )
	* @param[in] userid 用户ID
	* @return true为好友  false非好友
	*/
	virtual bool contactIsBuddy(int64 userId) = 0;

	/**
	* \brief 获取黑名单
	* @param[out] cb 传入接收结果回调  _1错误信息 _2黑名单ID集合
	*/
	virtual void getBlackList(SFunction<void(ErrorInfo, std::vector<int64>&)> cb) = 0;

	/**
	* \brief 添加黑名单
	* @param[in] ids 要加入的黑名单对象ID集合
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void addBlackList(std::vector<int64> &ids, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 删除黑名单
	* @param[in] ids 要删除的黑名单对象ID集合，为空则删除所有黑名单用户
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void removeBlackList(std::vector<int64> &ids, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 根据条件查询拓展字段信息 根据dicKey和parentId共同查询拓展字段.
	* @param[in] dicKey 要查询的字段
	* @param[in] parentID 父组织ID 当parentId为-1时表示查询所有的拓展字段;当parentId为-2 时按dicKey查询;-3时dicKey为id,根据id查询
	* @param[out] cb 传入接收结果回调  _1错误信息 _2返回的查询信息
	*/
	virtual void queryExtendedField(const std::string &dicKey,int64 parentID, SFunction<void(ErrorInfo, std::vector<EnterpriseDictionary>&)> cb) = 0;
    
    /**
    * \brief 根据条件查询拓展字段信息（同步接口）
    * @param[in] dicKey 要查询的字段
    * @param[in] parentID 父组织ID 当parentId为-1时表示查询所有的拓展字段;当parentId为-2 时按dicKey查询
    * @param[out] result 查询结果  不会更新本地数据
    */
    virtual bool queryExtendedFieldSync(const std::string &dicKey, int64 parentID, std::vector<EnterpriseDictionary>& result) = 0;

	/**
	* \brief 上传通讯录
	* @param[in] ids 要删除的黑名单对象ID集合，为空则删除所有黑名单用户
	* @param[out] cb 传入接收结果回调  _1错误信息 2,推荐联系人
	*/
	virtual void postContact(std::vector<PhoneBookContact> &pbContacts, SFunction<void(ErrorInfo, std::vector<RecommendContact>&)> cb) = 0;

	/**
	* \brief 获取全部本地通讯录条目(同步方法)
	* @param[out] phoneBooks 返回的通讯录条目集合
	*/
	virtual bool getLocalPhoneBook(std::vector<localPhoneBook> &phoneBooks) = 0;
	/**
	* \brief 增加本地通讯录条目(同步方法)
	* @param[in] phoneBooks 通讯录条目集合
	*/
	virtual bool addLocalPhoneBook(std::vector<localPhoneBook> &phoneBooks) = 0;

	/**
	* \brief 删除本地通讯录条目(同步方法)
	* @param[in] phones 电话号码集合
	*/
	virtual bool deleteLocalPhoneBook(std::vector<std::string> &phones) = 0;
	/**
	* \brief 更新本地通讯录(同步方法)
	* @param[in] phoneBooks 通讯录条目集合
	*/
	virtual bool updateLocalPhoneBook(std::vector<localPhoneBook> &phoneBooks) = 0;
	/**
	*\brief从网络获取好友信息
	*/
	virtual void getBuddyInfoFromNet(int64 userId,SFunction<void(ErrorInfo,Contact&)> cb) = 0;

	/**
	*\brief 是否为单向增减删除好友 (同步方法)
	* @return  true 单向 false 双向
	*/
	virtual bool  oneWayBuddy() = 0;

	/**
	*\brief生成邀请码
	* @param[in] param 生成邀请码的参数
	* @param[out] cb 传入接收结果回调  _1错误信息 _2邀请码
	*/
	virtual void makeVerifyCode(InviteCodeParam &param, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;

	/**
	*\brief是否是合法的邀请码(同步接口)
	* @param[in] inviteCode 邀请码
	* @param[in] serverIP 合法返回服务器IP
	* @param[out] return 合法返回服务器IP 不合法返回空
	*/
	virtual std::string isInviteCode(const std::string &inviteCode) = 0;
	
	/**
	*\brief校验本人是否有权限生成邀请码
	* @param[out] cb 传入接收结果回调  _1错误信息  0有权限 100001717没有权限
	*/
	virtual void canMakeVerifyCode(SFunction<void(ErrorInfo)> cb) = 0;

	/**
	*\brief检查邀请码是否有效
	* @param[in] inviteCode 邀请码
	* @param[in] uc 被邀请用户
	* @param[out] cb 传入接收结果回调  _1错误信息  0有效
	*/
	virtual void verifyCodeValid(const std::string &inviteCode, UserContact &uc, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	*\brief 通过邀请码获取用户ID
	* @param[in] inviteCode 邀请码
	* @param[out] cb 传入接收结果回调  _1错误信息  _2用户ID
	*/
	virtual void getUserIdByInviteCode(const std::string &inviteCode, SFunction<void(ErrorInfo, int64)> cb) = 0;
};

} /*namespace service*/