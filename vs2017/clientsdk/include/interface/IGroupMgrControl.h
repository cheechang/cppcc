#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include "data/GroupData.h"

namespace control{
	class IGroupMgrControl:public IControl{
	public:
			/**
	* \brief 监听群头像更新
	* @param[in] _1 传入目标ID，人或者群
	* @param[in] _2	  传入头像
	*/
	virtual void RegGroupHeadImgUpdateCb(CFunction < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 监听群成员头像更新
	* @param[in] _1 传入目标ID，人或者群
	* @param[in] _2	  传入头像
	*/
	virtual void RegMemberHeadImgUpdateCb(CFunction < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 监听群背景更新
	* @param[in] _1 传入目标ID，人或者群
	* @param[in] _2	  传入头像
	*/
	virtual void RegGroupBackImgUpdateCb(CFunction < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 设置监听群信息更新的回调
	* @param[in] _1 操作类型 1.添加 2.更新，31.解散 32.移除 33.退出
	* @param[in] _2 群信息
	*/
	virtual void RegGroupRefreshCb(CFunction< void(int8, const data::Group&) > cb) = 0;

	/**
	* \brief 设置监听群主更新的回调
	* @param[in] _1 群主ID
	* @param[in] _2 群主名
	* @param[in] _3 群ID
	* @param[in] _4 群名
	*/
	virtual void RegTransferGroupCb(CFunction< void(int64, const std::string&, int64, const std::string&) > cb) = 0;
	
	/**
	* \brief 设置监听群成员信息更新的回调
	* @param[in] _1 群ID
	* @param[in] _2 群成员信息
	*/
	virtual void RegGrpMemInfoRefreshCb(CFunction< void(int64, const data::Member&) > cb) = 0;

	/**
	* \brief  设置群成员列表更新的回调
	* @param[in] _1 操作类型  1 添加， 32 移除， 33 退出
	* @param[in] _2 群ID
	* @param[in] _3 变更的群成员集合
	*/
	virtual void RegGrpMemRefreshCb(CFunction< void(int, int64, std::vector<CSharedPtr<data::Member> >&) > cb) = 0;

	/**
	* \brief  设置获取群成员列表的回调
	* @param[in] _1 错误信息，不使用，只是为了和getMemberList回调函数一致
	* @param[in] _2 群成员列表
	*/
	virtual void RegGetGrpMemListCb(CFunction<void(int, std::vector<CSharedPtr<data::Member> >&)> cb) = 0;
	
	/**
	* \brief  监听群列表刷新
	* @param[in] _1 群列表
	*/
	virtual void RegGroupListCb(CFunction< void(std::vector<CSharedPtr<data::TinyGroup> >&) > cb) = 0;


	/*****************************************请求接口*******************************************/


	/**
	* \brief 创建群
	* @param[in] level 传入群等级 1.临时群，2.普通群
	* @param[in] name 传入群名称
	* @param[in] members   传入群成员
	* @param[in] cb  传入接收结果回调  _1错误信息  _2群ID
	*/
	virtual void CreateGroup(int level, const std::string &name, std::vector<int64> &members, CFunction<void(int, int64)> cb) = 0;

	/**
	* \brief 加群
	* @param[in] groupid 传入群id
	* @param[in] verify_info 传入验证信息
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void AddGroup(int64 groupid, const std::string &verify_info, CFunction<void(int)> cb) = 0;

	/**
	* \brief 解散群
	* @param[in] type 传入操作类型 1 群主解散群，2 群成员退群
	* @param[in] groupid 传入群id
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void RemoveGroup(int type, int64 groupid, CFunction<void(int)> cb) = 0;

	/**
	* \brief 转让群
	* @param[in] groupid 传入群id
	* @param[in] userid 传入新群主的id
	* @param[in] cb  传入接收结果回调  _1错误信息
	*/
	virtual void TransferGroup(int64 groupid, int64 userid, CFunction<void(int)> cb) = 0;

	/**
	* \brief 获取群设置
	* @param[in] groupid 传入群id
	* @param[in] cb  传入接收结果回调  _1错误信息 \n
	*    _2  验证类型: 1.不允许任何人添加, 2.需要验证信息, 3.允许任何人添加.\n
	*	 _3	 是否允许群成员邀请好友加入群: 1.允许 2.不允许.
	*/
	virtual void GetGroupSet(int64 groupid, CFunction<void(int, int8, int8)> cb) = 0;

	/**
	* \brief 设置群设置
	* @param[in] groupid 传入群id
	* @param[in] verify_type 传入验证类型 1:不允许任何人添加,2：需要验证信息,3：允许任何人添加
	* @param[in] is_allow 传入是否允许成员邀请用户 1,允许 2,不允许 isAllow
	* @param[in] cb  传入接收结果回调  _1错误信息 
	*/
	virtual void SetGroupSet(int64 groupid, int8 verify_type, int8 is_allow, CFunction<void(int)> cb) = 0;

	/**
	* \brief 获取群信息 （同步接口）
	* @param[in] groupid 传入群id
	* @param[out] groupInfo 群信息
	*/
	virtual void GetGroupInfo(int64 groupid, data::Group& groupInfo) = 0;

	/**
	* \brief 设置群信息
	* @param[in] groupId 设置的群ID
	* @param[in] group  可设置的群信息
	* @param[in] cb  传入接收结果回调  _1错误信息 
	*/
	virtual void SetGroupInfo(int64 groupId, data::GroupUpdate &group, CFunction<void(int)> cb) = 0;

	/**
	* \brief 获取群列表 （同步接口）
	* @param[in] cb  传入接收结果回调  _1群信息集合;
	*/
	virtual void GetGroupList(std::vector<CSharedPtr<data::TinyGroup> > &groups) = 0;

	/**
	* \brief 邀请群成员
	* @param[in] groupid 传入群id
	* @param[in] members 传入成员名单
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void InviteMember(int64 groupid,std::vector<int64> &members,CFunction<void(int)> cb) = 0;

	/**
	* \brief 移除群成员
	* @param[in] groupid 传入群id
	* @param[in] userid 传入需要移除的成员id
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void RemoveMember(int64 groupid, int64 userid, CFunction<void(int)> cb) = 0;

	/**
	* \brief 批量移除群成员
	* @param[in] groupid 传入群id
	* @param[in] userids 传入需要移除的成员id集合
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void RemoveMembers(int64 groupid, std::vector<int64> userids, CFunction<void(int)> cb) = 0;

	/**
	* \brief 设置群成员信息
	* @param[in] member 传入成员信息
	* @param[in] cb  传入接收结果回调
	*/
	virtual void SetMemberInfo(data::Member &member, CFunction<void(int)> cb) = 0;

	/**
	* \brief 判断用户是否在群里 (同步接口)
	* @param[in] groupid 传入群id
	* @param[in] userid 传入成员id
	* @return false代表不是群成员
	*/
	virtual bool IsInGroup(int64 groupId, int64 userId) = 0;

	/**
	* \brief 获取群成员信息 (同步接口)
	* @param[in] groupid 传入群id
	* @param[in] userid 传入成员id
	* @param[out] member返回成员信息
	* @return false代表没有此信息
	*/
	virtual bool GetMemberInfo(int64 groupid, int64 userid, data::Member &member) = 0;

	/**
	* \brief  获取群成员列表
	* @param[in] groupid 传入群id
	* @param[in] cb  传入接收结果回调   _1错误信息  _2群成员信息集合
	*/
	virtual void GetMemberList(int64 groupid, CFunction<void(int, std::vector<CSharedPtr<data::Member> >&)> cb) = 0;

	/**
	* \brief 获取群文件列表
	* @param[in] groupid 传入群id
	* @param[in] beginid 传入起始id
	* @param[in] count 传入数量
	* @param[in] flag 传入偏移标志0为向上1为向下
	* @param[in] cb  传入接收结果回调   _1错误信息 _2文件信息集合
	*/
	virtual void getGroupFileList(int64 groupid, CFunction<void(int, std::vector<CSharedPtr<data::FileInfo>>&)> cb) = 0;

	/**
	* \brief 删除群文件
	* @param[in] files 传入群文件id
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void DeleteGroupFile(std::vector<int64> &files, int64 groupId,CFunction<void(int)> cb) = 0;

	/**
	* \brief 获取个人群聊背景图片
	* @param[in] groupId 群ID
	* @param[in] cb  传入接收结果回调   _1错误信息   _2图片URL
	*/
	virtual void GetPersonalGroupImg(int64 groupId, CFunction<void(int, const std::string&)> cb) = 0;

	/**
	* \brief 设置个人群聊背景图片
	* @param[in] groupId 群ID
	* @param[in] imgUrl 图片URL
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void SetPersonalGroupImg(int64 groupId, const std::string &imgUrl, CFunction<void(int)> cb) = 0;

	/**
	* \brief 设置群消息免打扰模式
	* @param[in] groupId 群ID
	* @param[in] mode 提醒模式 1：提示并接收消息；2：不提示，接收仅显示数目；3：屏蔽消息
	* @param[in] cb  传入接收结果回调   _1错误信息
	*/
	virtual void SetGroupMsgRemindType(int64 groupId, int8 mode , CFunction<void(int)> cb) = 0;

	/**
	* \brief 获取群消息免打扰模式
	* @param[in] groupId 群ID
	* @param[in] cb  传入接收结果回调   _1错误信息 _2提醒模式 1：提示并接收消息；2：不提示，接收仅显示数目；3：屏蔽消息
	*/
	virtual void GetGroupMsgRemindType(int64 groupId, CFunction<void(int, int8)> cb) = 0;

	/**
	* \brief 设置群消息内容模式和V标
	* @param[in] groupId 群ID
	* @param[in] vSign 群V标 0为非v标群，1为v标群 -1为不设置
	* @param[in] msgContentMode 群通知消息内容模式: 1、通知详情  2、通知源，隐藏内容  3、完全隐藏   -1为不设置
	* @param[in] cb  传入接收结果回调   _1错误信息 _2提醒模式
	*/
	virtual void SetGroupExtraInfo(int64 groupId, int8 vSign, int8 msgContentMode, CFunction<void(int)> cb) = 0;
	
	/*
	* \brief 设置群成员数据变化
	*  @param[in] targetid
	*/
	virtual void SetGroupMemCountCb(int64 id,CFunction<void(int, int64)>cb) = 0;
	
	/**
	* \brief 上传文件  ///若断点上传,key必须一致
	* @param[in] targetId 人或群的id
	* @param[in] cb  传入接收结果回调 _1错误信息 _2目标Id _3服务器返回的json
	* @param[in] pro  进度回调 _1 extra_req  _2process 
	* @return 每个文件对应的唯一localID
	*/
	virtual int64 uploadFile(data::UploadFileProperty &fileProperty, CFunction<void(int, int64, const std::string&)> cb,
		CFunction<void(int32, int32, const std::string&)> pro = CNull) = 0;

	/**
	* \brief 取消文件上传或下载
	* @param[in] localId 文件的localId
	* @param[in] type  1.上传 2.下载 3.外部下载
	*/
	virtual void cancelTransfer(int64 localId, int type, CFunction<void(int)> cb) = 0;
	virtual void getGroupMemberFromNet(int64 groupId, int64 memberID, CFunction<void(int, data::Member&)> cb) = 0;
	/**
	* \brief 批量获取群成员
	* @param[in] groupId 群ID
	* @param[in] memberIDs 群成员id集合
	* @param[in] cb  传入接收结果回调   _1错误信息 _2成员信息集合
	*/
	virtual void getBatchMemberByID(int64 groupId, std::vector<int64>& memberIDs, CFunction<void(int, std::vector<CSharedPtr<data::Member> >&)> cb) = 0;
};
	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}