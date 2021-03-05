#pragma once

#include "../model/Msg.h"
#include "../model/Packet.h"
#include "../extModel/packet.h"
#include "../model/SDKTypes.h"
#include "../model/Chat.h"
#include "IService.h"

#include <string>

#define VER_IChatService INTERFACE_VERSION(1,0)
static const VRVIID IID_IChatService = { 0x76fb3792, 0xc171, 0x4ebe, 0xac, 0x3f, 0xa0, 0x8c, 0x2a, 0x5c, 0x16, 0xfc };

namespace service 
{

class IChatService : public IService
{

public:

	virtual ~IChatService(){}

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief 监听最近回话头像更新
	* @param[out] cb _1 传入目标ID，人或者群  _2 传入头像
	*/
	virtual void regChatHeadImgUpdateCb(SFunction < void(int64, const std::string&) > cb) = 0;

	/**
	* \brief 设置监听新聊天消息的回调
	* @param[out] cb _1 消息结构的智能指针
	*/
	virtual void regMsgNoticeCb(SFunction< void(SSharedPtr<Msg>) > cb) = 0;

	/**
	* \brief 设置监听新透传消息的回调
	* @param[in] cb _1 消息结构的智能指针
	*/
	virtual void regTransMsgNoticeCb(SFunction< void(SSharedPtr<Msg>) > cb) = 0;

	/**
	* \brief 设置监听消息输入状态的回调
	* @param[out] cb _1 targetId, _2 发送时间 _3输入标识 0.开始输入 1.结束输入
	*/
	virtual void regMessageInputStateCb(SFunction< void(int64, int64, int8) > cb) = 0;
	
	/**
	* \brief 设置监听离线消息的回调
	* @param[out] cb _1 离线消息集合
	*/
	virtual void regOfflineMsgCb(SFunction< void(std::vector<OfflineMsg>&) > cb) = 0;

	/**
	* \brief 监听会话列表更新通知
	* @param[in] cb _1 传入列表标志
	 * 全部更新:
	*	0x01　第一个包,　　 需要清理原来的数据
	*	0x02  中间的包，　　在原来的数据后面追加
	*	0x04  最后的包，　　最近会话发送完毕
	* 部分更新:
	*   0x08  更新
	*	0x10  新增
	*	0x20  删除
	* 全部删除
	*   0x40 删除所有最近联系人
	*  _2 传入会话集合
	*/
	virtual void regRecontactCb(SFunction< void(int, std::vector<SSharedPtr<Chat> >&) > cb) = 0;
	/**
	 * \brief  消息游标推送
	 * @param[out] cb 
	 * _1 userID int64 userID;  ///<本人用户ID
	 * _2 int64 targetID;///<目标ID(单聊人ID,群聊群组ID)
	 * _3 int64 maxReadID;///<所有设备中最大的消息已读ID
	 */
	virtual void regMessageCursorCb(SFunction< void(int64,int64,int64) > cb) = 0;

	/*****************************************请求接口*******************************************/

	/**
	* \brief 获取会话列表(同步接口)
	*/
	virtual void getChatList(std::vector<SSharedPtr<Chat> > &recontacts) = 0;

	/**
	* \brief 移除会话
	* @param[in] targetid 传入会话对应的ID，群或者人 0为删除全部联系人
	* @param[out] cb  传入接收结果回调
	*/
	virtual void removeChat(int64 targetId, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 发送消息，返回localid
	* @param[in] msg 传入消息
	* @param[out] cb  传入接收结果回调 _1 错误信息 _2 发送时间 _3消息ID _4敏感词
	* @param[out] pro  进度回调 参照fileService
	*/
	virtual int64 sendMessage(Msg &msg, SFunction<void(ErrorInfo, int64, int64, BadWord&)> cb, SFunction<void(int32, int32, const std::string&)> pro = SNull) = 0;

	/**
	* \brief 直接发送附件消息 支持文件，图片，九宫格。发送失败时，重发消息的localId和失败消息localId要一致,断点续传的话 一个文件的加密key要一致
	*
	*		 失败文件信息存在在消息的body中，格式为:
	*		[
			{
				"localPath": "",		//此字段总是存在且有值
				"remotePath" : "",		//此字段总是存在，为空时代表上传失败
				"srcLocalPath" : "",	//上传图片时，存在此字段
				"srcRemotePath" : ""	//上传图片时，存在此字段
			}
			]
			重发时，用户可以从两个localPath中获取上次发送的文件本地路径，不需要关心remotePath字段
	*
	* @param[in] msg 附件 MsgFileEx文件, MsgImgEx图片, MsgNineBlockEx九宫格
	* @param[out] cb  传入接收结果回调 _1 错误信息 _2 发送时间 _3消息ID _4敏感词
	* @param[out] pro  进度回调 参照fileService
	*/
	virtual void sendAppendixMessage(Msg &msg, SFunction<void(ErrorInfo, int64, int64, BadWord&)> cb, SFunction<void(int32, int32, const std::string&)> pro = SNull) = 0;

	/**
	* \brief 插入消息
	* @param[in] msg 插入的消息结构体
	* @param[out] cb  传入接收结果回调 _1 错误信息 
	*/
	virtual void insertMessage(Msg &msg, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 透传发送消息
	* @param[in] msg 传入消息
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2 发送时间 _3敏感词
	*/
	virtual void transferMessage(Msg &msg, SFunction<void(ErrorInfo, int64, BadWord&)> cb) = 0;

	/**
	* \brief 转发消息
	* @param[in] fromTaregetId 转发的消息的当前targetId
	* @param[in] toTargetId 转发的消息的接收targetId
	* @param[in] messageId 转发的消息ID
	* @param[out] cb  _1  传入接收结果回调 _1 错误信息 _2 发送时间 _3消息ID _4敏感词
	*/
	virtual void forwardMessage(int64 fromTargetId, int64 toTargetId, int64 messageId, SFunction<void(ErrorInfo,int64,int64,BadWord&)> cb) = 0;

	/**
	* \brief 删除所有消息
	* @param[in] clearChatList 是否清空联系人列表
	* @param[in] cb  结果回调 _1错误信息
	*/
	virtual void deleteAllMessage(bool clearChatList, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 通过msgId删除消息
	* @param[in] targetid 传入会话对应的ID，群或者人
	* @param[in] msgs 传入要删除的消息ID集合 msgs为空，清空对应targetId的所有消息
	* @param[in] cb  结果回调 _1错误信息
	*/
	virtual void deleteMessageById(int64 targetId, std::vector<int64> &msgIds, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 删除时间段消息
	* @param[in] targetid 传入会话对应的ID，群或者人 targetId为0，则针对所有用户
	* @param[in] beginTime 起始时间
	* @param[in] endTime 结束时间
	* @param[in] cb  结果回调 _1错误信息
	*/
	virtual void deleteMessageByTime(int64 targetId, int64 beginTime, int64 endTime, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 设置消息已读
	* @param[in] targetid 传入会话对应的ID，群或者人
	* @param[in] msgs 需要设置的消息ID 比如设置为100, 比100小的所有消息都为已读
	*/
	virtual void setMessageRead(int64 targetId, int64 msgId) = 0;

	/**
	* \brief 设置消息未读 
	* @param[in] targetId 目标ID，个人或群,如果targetID等于0表示设置的是系统消息
	* @param[in] cb  传入接收结果回调 _1 错误信息
	*/
	virtual void setMessageUnRead(int64 targetId, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取消息
	* @param[in] targetid 传入会话对应的ID，群或者人
	* @param[in] msgid 如果是按消息Id查询传入查询消息的起始消息ID，如果是按消息时间查询传入查询消息的起始时间。返回的结果会包含这条消息。
	* @param[in] count 传入查询消息总数
	* @param[in] flag  传入上一页还是下一页 
					   偏移标志 0.消息Id由大到小偏移 1.消息Id由小到大偏移 offsetFlag 2.按msgId精准查询
					   如果msgId代表的是消息时间的话，或上0xF0,如果是消息ID的话就不用或上0xF0
	* @param[in] fromUserId 发送者ID,表示只查询某一些人发的消息，默认为空，表示查询所有人的消息，最多查询10个人的消息。
	* @param[in] msgType 消息类型,表示查询某一些类型的消息，默认为空,表示查询所有类型的消息,最多查询5种类型的消息。
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2会话放ID， _3消息集合
	*/
	virtual void getMessages(int64 targetId, int64 msgId, int count, int flag, std::vector<int64> &fromUserId, std::vector<int32>& msgType, SFunction<void(ErrorInfo, int64, std::vector<MsgPtr>&)> cb) = 0;
	virtual void getMessages(int64 targetId, int64 msgId, int count, int flag, SFunction<void(ErrorInfo, int64, std::vector<MsgPtr>&)> cb) = 0;

	/**
	* \brief 置顶会话
	* @param[in] targetid 置顶的目标ID
	* @param[in] isTop  是否置顶 
	* @param[in] cb  传入接收结果回调 _1 错误信息 
	*/
	virtual void chatTop(int64 targetId, bool isTop, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 获取图片消息
	* @param[in] targetid 个人或群ID
	* @param[in] cb  传入接收结果回调 _1 错误信息  _2消息集合
	*/
	virtual void getImgMsg(int64 targetId, SFunction<void(ErrorInfo, std::vector<MsgPtr>&)> cb) = 0;

	/**
	* \brief 获取URL的详细信息
	* @param[in] url  网址
	* @param[in] cb  传入接收结果回调 _1 错误信息  _2网址  _3标题  _4图片的地址  _5摘要
	*/
	virtual void getUrlInfo(const std::string &url, std::string& loginfoPath, SFunction<void(ErrorInfo, const std::string&, const std::string&, const std::string&, const std::string&)> cb) = 0;

	/**
	* \brief 设置私信秘钥
	* @param[in] targetId 目标ID，个人或群
	* @param[in] passwd  私信秘钥  为空代表清除私信密码.
	* @param[in] cb  传入接收结果回调 _1 错误信息 
	*/
	virtual void setPrivateKey(int64 targetId, const std::string &passwd, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 通过消息ID解密消息
	* @param[in] targetId 目标ID，个人或群
	* @param[in] msgIds  要解密的消息ID集合
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2 解密消息的targetId _3已解密的消息
	*/
	virtual void decryptMsg(int64 targetId, std::vector<int64> &msgIds, SFunction<void(ErrorInfo, int64, std::vector<MsgPtr>&)> cb) = 0;

	/**
	* \brief 更新对应targetId的消息，只能更新消息体和property
	* @param[in] targetId 目标ID，个人或群
	* @param[in] msgs  要更新的消息集合
	* @param[in] cb  传入接收结果回调 _1 错误信息
	*/
	virtual void updateMsg(std::vector<MsgPtr> &msgs, SFunction<void(ErrorInfo)> cb) = 0;
	virtual void updateMsg(Msg &msg, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 上传消息计数
	* @param[in] msg 见Packet.h
	* @param[in] cb  传入接收结果回调 _1 错误信息 
	*/
	virtual void upMsgCount(upMsgCt &msg,SFunction<void(ErrorInfo)> c) = 0;

	/**
	* \brief 增加最近联系人
	* @param[in] recontact 最近联系人对象
	* @param[in] cb  传入接收结果回调 _1 错误信息
	*/
	virtual void addRecontact(Chat chat, SFunction<void(ErrorInfo)> cb) = 0;
	/**
	 *\brief 获取对象聊天时间数组
	 *@param[in] targetId 对象id
	 *@param[in] belately 是否最近 0是最近 非零是要查询的年份
	 */
	virtual void getMsgDays(int64 targetId, int16 belately, SFunction<void(ErrorInfo, std::vector<model::YMD>&,std::vector<int32>&)> cb) = 0;
	/**
	* \brief 根据日期获取消息
	*@param[in] targetId 对象id
	*@param[in] msgId 搜索的起始的msgId,首次搜索，传0
	*@param[in] count 一次搜索的数量，如果为0，代表搜索全部
	*@param[in] belately 是否最近 0 是最近，非零的话要设置 YMD
	*@param[in] ymd  年月日
	*/
	virtual void getMsgFromDay(int64 targetId, int64 msgId, int32 count, int16 belately, model::YMD &ymd,SFunction<void(ErrorInfo, std::vector<MsgPtr>&)> cb) = 0;

	/**
	* \brief 获取所有消息数目
	* @param[in] targetId  目标id, 为0代表获取所有消息数目，否则代表获取相应targetId消息数目。
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2消息数
	*/
	virtual void getAllMsgCount(int64 targetId, SFunction<void(ErrorInfo, int32)> cb) = 0;

	/**
	* \brief 发送短信
	* @param[in] userIds  接收短信的目标id集合
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2失败的用户ID及失败原因
	*/
	virtual void sendShortMessage(std::vector<int64> userIds, SFunction<void(ErrorInfo, std::map<int64, std::string>&)> cb) = 0;

	/**
	* \brief 获取群内消息的读取状态
	* @param[in] targetId  目标targetId
	* @param[in] msgId  消息id
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2表示返回对应类型的消息的已读，未读，未推送userID列表
	*/
	virtual void getGroupMsgReadState(int64 targetId, int64 msgId, SFunction<void(ErrorInfo, std::map<std::string, std::vector<int64> >&)> cb) = 0;

	/**
	* \brief .获取一批消息的未读数计数器
	* @param[in] groupId  群ID
	* @param[in] infos  消息id快照id信息
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2表示返回所有消息的未读状态
	*/
	virtual void getGroupMsgUnreadCounter(int64 groupId, std::vector<SnapshotInfo> &infos, SFunction<void(ErrorInfo, std::vector<MsgUnreadCounter>&)> cb) = 0;

	/**
	* \brief .统计消息已读、未读数量详细信息
	* @param[in] groupId  群ID
	* @param[in] info  消息id快照id信息
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2已读userID列表 _3未读userID列表
	*/
	virtual void getGroupMsgUnreadInfo(int64 groupId, SnapshotInfo &info, SFunction<void(ErrorInfo, std::vector<int64>&, std::vector<int64>&)> cb) = 0;

	/**
	* \brief .获取联系人最大已读ID
	* @param[in] targetId 联系人ID
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2最大已读ID
	*/
	virtual void getContractMaxReadId(int64 targetId, SFunction<void(ErrorInfo, int64)> cb) = 0;
	
	/**
	* \brief 获取不同类型的未读消息数量 (同步接口)
	* @param[in] type  1.未读V标消息数量 2.未读@消息数量 3.未读V标@消息数量
	* @param[in] return  未读消息数量
	*/
	virtual int getUnReadMsgCountByType(int type) = 0;

	/**
	* \brief 发送消息输入状态
	* @param[in] flag 0.开始输入 1.结束输入  
	* @param[in] cb  传入接收结果回调 _1 错误信息
	*/
	virtual void sendMsgInputState(int64 targetId, int8 flag, SFunction<void(ErrorInfo)> cb) = 0;
	/*
	*\brief 获取@我的消息 或者 我@别人的消息
	*@param[in]  req 见getReqAtMsg 注释
	*@param[in] cb 传入结果回调 _1 错误信息 _2会话放ID， _3消息集合
	*/
	virtual void getAtMessage(getReqAtMsg& req, SFunction<void(ErrorInfo, int64, std::vector<MsgPtr>&)> cb) = 0;
	/*
	*\brief 批量设置已读
	*@param[in] cb 传入结果回调 _1 错误信息 
	*/
	virtual void  setMsgReads(SFunction<void(ErrorInfo)> cb) = 0;
	
	virtual void MakeCombineMsg(MsgCombine & msg, std::string &json) = 0;
	
	virtual bool ParseCombineMsg(std::string& cmbJson, MsgCombine& msg) = 0;

	virtual SSharedPtr<MsgCombine> toCombineMsg(Msg *baseMsg) = 0;



};

} /*namespace service */