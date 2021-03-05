#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include <map>
#include <vector>
#include "data/ChatData.h"
#include "data/GroupData.h"
namespace data{
	struct SnapshotInfo;
	struct MsgUnreadCounter;
	class ChatData;
	class MsgStatus;
	class Msg;
	class UserData;
	class MsgImg;
	class DownLoadFile;
	struct MsgSearchProperty;
	struct MsgSearchResult;
	struct MsgDetailSearchProperty;
	struct  MsgDetailSearchResult;
}
namespace control{
class IChatMgrControl:public IControl{
public:
	/*********************************************************************************************************
	* brief 监听会话列表更新通知
	* @param[in] cb _1 传入列表标志 _2 传入会话集合
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
	************************************************************************************************************/
	virtual void RegChatListNotify(CFunction< void(int, std::vector<CSharedPtr<data::ChatData>>&)> cb) = 0;


    /**********************************************************************************************************
	*brief 监听最近回话头像更新推送
	*@param[out] cb _1 传入目标ID，人或者群  _2 传入头像
	**********************************************************************************************************/
	virtual void RegChatListHeadUpdate(CFunction < void(int64, const std::string&)> cb) = 0;


	/**********************************************************************************************************
	*brief 设置监听新聊天消息的回调
	*@param[in] cb _1 消息结构的智能指针
	**********************************************************************************************************/
    virtual void RegRecvMsgNotice(CFunction< void(CSharedPtr<data::Msg>)> cb) = 0;    


	/**********************************************************************************************************
	*brief 设置监听图片消息更新推送
	*@param[in] cb _1 消息结构的智能指针
	**********************************************************************************************************/
	virtual void RegImgMsgNotice(CFunction< void(CSharedPtr<data::Msg>)> cb)=0;


	/**********************************************************************************************************
	*brief 设置监听消息发送状态更新推送
	*@param[out] err 错误值  localid界面唯一标示符  time消息时间  targetid目标id externd图片消息则是 
	**********************************************************************************************************/
	virtual void RegMsgStatusNotice(CFunction< void(CSharedPtr<data::MsgStatus>)>cb)=0;


	/**********************************************************************************************************
	*brief 设置进度监听回调
	*@param[out] _1 进度对应的文件的localId _2 进度标示 _3进度 _4文件当前传入大小/文件总大小
	**********************************************************************************************************/
	virtual void RegProcessCb(int64 localid,CFunction<void(int64, int32, int32, const std::string&)> cb)=0;


	/*********************************************************************************************************
	* @brief 获取最近会话列表接口
	* @param[out] chatlist 传出会话列表
	************************************************************************************************************/
	virtual void GetChatList(std::vector<CSharedPtr<data::ChatData> > &chatlist)=0;


	/*********************************************************************************************************
	* @brief 获取消息
	* @param[in] targetid 传入会话对应的ID，群或者人
	* @param[in] msgid 传入查询消息的起始ID，将从该消息的下一条消息开始查询
	* @param[in] count 传入查询消息总数
	* @param[in] flag  传入上一页还是下一页 向上偏移 0；向下偏移 1
	*                  如果msgBeginID的所标识的消息是发送失败的消息，则或上0xF0，传递到SDK。
					   比如从大到小偏移，并且msgBeginID标识的消息是发送失败的消息。
					   则： offsetFlag = 0 | 0xF0.
	* @param[out] cb  传入接收结果回调 _1 错误信息 _2会话ID， _3消息集合
	************************************************************************************************************/
	virtual void GetMessages(int64 targetId, int64 msgId, int count, int flag, CFunction<void(int,int64,std::vector<CSharedPtr<data::Msg>>&)> cb)=0;

	/***************************************************************************************
	* @brief 发送消息，返回localid
	* @param[in] msg 传入消息
	* @param[out] cb  传入接收结果回调 _1 错误信息 _2 发送时间 _3消息ID
	****************************************************************************************/
	virtual int64 SendMessage(CSharedPtr<data::Msg>&msg,CFunction<void(int,int64,int64)>cb)=0;

	/**********************************************************************************************************************************
	* @brief 设置消息已读
	* @param[in] targetid 传入会话对应的ID，群或者人
	* @param[in] msgId 需要设置的消息ID 比如设置为100, 比100小的所有消息都为已读
	***********************************************************************************************************************************/
	virtual void setMessageRead(int64 targetId, int64 msgId) = 0;

     
    /************************************************************************************************************************
	* \brief 移除会话
	* @param[in] targetid 传入会话对应的ID，群或者人 0为删除全部联系人
	***************************************************************************************************************************/
	virtual void RemoveChat(int64 targetId)=0;

	/************************************************************************************************************************
	* brief 下载图片接口
	* @param[in] targetid 传入会话对应的ID，群或者人 0为删除全部联系人
	* @param[out] err 错误值 imgName图片名需要+USERIMAGE  tarid 对方id
	***************************************************************************************************************************/
	virtual void DownLoadImage(int64 targetid,std::string&url,CFunction<void(int err,const std::string&imgName,int64 tarid)>cb)=0;


	/************************************************************************************************************************
	* brief 下载文件接口
	* @param[in] download 穿入下载文件所需信息
	* @param[out] 传入接收结果回调 _1错误信息  _2接收成功后文件路径 localPath _3发送者ID
	***************************************************************************************************************************/
	virtual void DownLoadFile(CSharedPtr<data::DownLoadFile>&download, CFunction<void(int err,const std::string&fileName, int64 targetId)>cb,
							CFunction<void(int32, int32, const std::string&)> pro = CNull)=0;

	/**
	* \brief 解密文件
	* @param[in] encryptkey 传入解密密码
	* @param[in] srcpath 传入原图路径
	* @param[in] destpath 传入解密后图片路径
	*/
	virtual bool decryptFile(const std::string &encryptkey, const std::string &srcpath, const std::string &destpath) = 0;

	/**
	* \brief 通过用户ID获取详细信息
	* @param[in] userid 传入用户ID
	* @param[in] msgid 消息id,没有时赋值0
	* @param[in] cb 传入接收结果回调  _1错误信息  _2用户信息
	*/
	virtual void getUserInfo(int64 userid, int64 msgid,CFunction<void(int, data::UserData&)> cb) = 0;

	/**
	* \brief <U>获取该用户聊天中cache
	* @return   用户聊天中cache
	*/
	virtual std::string userCachePath() = 0;

		/**
	* \brief <U>获取该用户聊天中音频信息的保存路径
	* @return   音频信息的保存路径
	*/
	virtual std::string userAudioPath() = 0;

	/**
	* \brief 获取图片消息
	* @param[in] targetid 个人或群ID
	* @param[in] cb  传入接收结果回调 _1 错误信息  _2消息集合
	*/
	virtual void getImgMsg(int64 targetId, CFunction<void(int, std::map<int64,data::MsgImg>)> cb) = 0;

	/**
	* \brief 转发消息
	* @param[in] fromTaregetId 转发的消息的当前targetId
	* @param[in] toTargetId 转发的消息的接收targetId
	* @param[in] messageId 转发的消息ID
	* @param[out] cb  _1  传入接收结果回调 _1 错误信息 _2 发送时间 _3消息ID _4敏感词
	*/
	virtual void forwardMessage(int64 fromTargetId, int64 toTargetId, int64 messageId, CFunction<void(int,int64,int64)> cb) = 0;

	/**
	* \brief 获取URL的详细信息
	* @param[in] url  网址
	* @param[in] cb  传入接收结果回调 _1 错误信息  _2网址  _3标题  _4图片的地址  _5摘要
	*/
	virtual void getUrlInfo(const std::string &url, std::string& loginfoPath, CFunction<void(int, const std::string&, const std::string&, const std::string&, const std::string&)> cb) = 0;

	/**
	* \brief 通过msgId删除消息
	* @param[in] targetid 传入会话对应的ID，群或者人
	* @param[in] msgs 传入要删除的消息ID集合 msgs为空，清空对应targetId的所有消息
	* @param[in] cb  结果回调 _1错误信息
	*/
	virtual void deleteMessageById(int64 targetId, std::vector<int64> &msgIds, CFunction<void(int)> cb) = 0;
    /**
	* \brief 删除所有消息
	* @param[in] clearChatList 是否清空联系人列表
	* @param[in] cb  结果回调 _1错误信息
	*/
	virtual void deleteAllMessage(bool clearChatList, CFunction<void(int)> cb) = 0;

	/**
	* \brief 删除时间段消息
	* @param[in] targetid 传入会话对应的ID，群或者人 targetId为0，则针对所有用户
	* @param[in] beginTime 起始时间
	* @param[in] endTime 结束时间
	* @param[in] cb  结果回调 _1错误信息
	*/
	virtual void deleteMessageByTime(int64 targetId, int64 beginTime, int64 endTime,CFunction<void(int)> cb) = 0;

	/**
	* \brief 置顶会话
	* @param[in] targetid 置顶的目标ID
	* @param[in] isTop  是否置顶 
	* @param[in] cb  传入接收结果回调 _1 错误信息 
	*/
	virtual void chatTop(int64 targetId, bool isTop, CFunction<void(int)> cb) = 0;

	/**
	* \brief 设置针对目标用户的勿扰模式
	* @param[in] targetId  用户ID
	* @param[in] value 设置的值:  1为接收提醒 2表示不提醒仅显示数字 3:为免打扰, 默认1
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void setUserNoDisturbMode(int64 targetId, int value, CFunction<void(int)> cb) = 0;

	/**
	* \brief 获取针对目标用户的勿扰模式
	* @param[in] targetId  用户ID
	* @param[out] cb 传入接收结果回调  _1错误信息  _2用户ID  _3设置的值:  1为接收提醒 2表示不提醒仅显示数字 3:为免打扰
	*/
	virtual void getUserNoDisturbMode(int64 targetId, CFunction<void(int, int64, int8)> cb) = 0;

	/*brief 设置私信秘钥
	* @param[in] targetId 目标ID，个人或群
	* @param[in] passwd  私信秘钥  为空代表清除私信密码.
	* @param[in] cb  传入接收结果回调 _1 错误信息 
	*/
	virtual void setPrivateKey(int64 targetId, const std::string &passwd) = 0;

		/**
	* \brief 通过消息ID解密消息
	* @param[in] targetId 目标ID，个人或群
	* @param[in] msgIds  要解密的消息ID集合
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2 解密消息的targetId _3已解密的消息
	*/
	virtual void decryptMsg(int64 targetId, std::vector<int64> &msgIds, CFunction<void(int, int64, std::vector<CSharedPtr<data::Msg>>&)> cb) = 0;
	
	/**
	* \brief 更新对应targetId的消息，只能更新消息体和property
	* @param[in] targetId 目标ID，个人或群
	* @param[in] msgs  要更新的消息集合
	* @param[in] cb  传入接收结果回调 _1 错误信息
	*/
	virtual void updateMsg(std::vector<CSharedPtr<data::Msg>> &msgs) = 0;
	virtual void updateMsg(CSharedPtr<data::Msg> &msg) = 0;

	/**
	* \brief 全局查找消息
	* @param[in] key	   传入查找关键字
	* @param[in] msgProperty  传入查找的附加属性
	* @param[in] cb     传入接收结果回调  _1错误信息  _2消息搜索结果集合
	*/
	virtual void searchMessage(const std::string &key, data::MsgSearchProperty &msgProperty,CFunction<void(int, data::MsgSearchResult&)> cb) = 0;

	/**
	* \brief 查找相应targetID的详细消息
	* @param[in] key	   传入查找关键字
	* @param[in] msgDetailProperty  传入查找的附加属性
	* @param[in] cb     传入接收结果回调  _1错误信息  _2消息搜索结果集合
	*/
	virtual void searchDetailMessage(const std::string &key, data::MsgDetailSearchProperty &msgDetailProperty,CFunction<void(int, data::MsgDetailSearchResult&)> cb) = 0;
	
	/**
	* \brief 上传文件  ///若断点上传,key必须一致
	* @param[in] targetId 人或群的id
	* @param[in] cb  传入接收结果回调 _1错误信息 _2目标Id _3服务器返回的json
	* @param[in] pro  进度回调 _1 extra_req  _2process
	* @return 每个文件对应的唯一localID
	*/
	virtual int64 uploadFile(data::UploadFileProperty &fileProperty, CFunction<void(int, int64, const std::string&)> cb,
		CFunction<void(int32, int32, const std::string&)> pro = CNull) = 0;

	virtual std::string parceEmojiDeal(const std::string msg)=0;
	/**
* \brief .获取一批消息的未读数计数器
* @param[in] groupId  群ID
* @param[in] infos  消息id快照id信息
* @param[in] cb  传入接收结果回调 _1 错误信息 _2表示返回所有消息的未读状态
*/
	virtual void getGroupMsgUnreadCounter(int64 groupId, std::vector<data::SnapshotInfo> &infos, CFunction<void(int, std::vector<data::MsgUnreadCounter>&)> cb) = 0;

	/**
	* \brief .获取联系人最大已读ID
	* @param[in] targetId 联系人ID
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2最大已读ID
	*/
	virtual void getContractMaxReadId(int64 targetId, CFunction<void(int, int64)> cb) = 0;

	/**
	* \brief .统计消息已读、未读数量详细信息
	* @param[in] groupId  群ID
	* @param[in] info  消息id快照id信息
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2已读userID列表 _3未读userID列表
	*/
	virtual void getGroupMsgUnreadInfo(int64 groupId, data::SnapshotInfo &info, CFunction<void(int, std::vector<int64>&, std::vector<int64>&)> cb) = 0;

	/**
	* \brief 获取群内消息的读取状态
	* @param[in] targetId  目标targetId
	* @param[in] msgId  消息id
	* @param[in] cb  传入接收结果回调 _1 错误信息 _2表示返回对应类型的消息的已读，未读，未推送userID列表
	*/
	virtual void getGroupMsgReadState(int64 targetId, int64 msgId, CFunction<void(int, std::vector<int64>&, std::vector<int64>&)> cb) = 0;
};
extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}

