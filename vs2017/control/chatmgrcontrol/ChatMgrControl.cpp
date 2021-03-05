#include "ChatMgrControl.h"
#include <json.h>
#include "interface/IMClient.h"
#include "IControl.h"
#include "log.h"
#include "data/ChatData.h"
#include "ParseJsonData.h"
#include "../utils/common.h"
#include "ChineseInfos.hpp"
#include "EncryptKey.h"
#include "IDRangeJuge.hpp"
const char * filename = 0;
int line = 0;

namespace control{
	service::IMClient* g_client =CNull;
	template<class  T,class Y>
	T GetCallBackFucPtr(int64 localid,Y y){
		T cb = CNull;
		Y::iterator itr;
		for( itr = y.begin(); itr != y.end(); ++itr){
			if ( localid == itr->first)
			{
				cb = itr->second;
				return cb;
			}
		}
		return cb;
	}

	template<class Y>
	void RemoveCallBackFucPtr(int64 localid,Y y){
		Y::iterator itr;
		for( itr = y.begin(); itr != y.end();){
			if ( localid == itr->first)
			{
				itr = y.erase(itr);
				break;
			}
			else{
				++itr;
			}
		}
	}
	ChatMgrControl::ChatMgrControl(const std::string &strName):m_chatservice(CNull),m_pluginname(strName),
	m_downloadimagecb(CNull),m_msgstauscb(CNull),m_configservice(CNull),m_userservice(CNull){
	BEGIN;
	END;
	}
	ChatMgrControl::~ChatMgrControl(){
	BEGIN;
	END;
	}
	/***********************************************
	* @brief 返回带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string ChatMgrControl::GetName(){
	BEGIN;
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
	END;
		return result;
	}
	/***********************************************
	* @brief 返回不带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string ChatMgrControl::GetDisplayName(){
	BEGIN;
	END;
		return m_pluginname;
	}
	/***********************************************
	* @brief 设置sdk客户端实例对象
	* @param[in]无
	***********************************************/
    void ChatMgrControl::SetSdkClientObj(void* obj){
	BEGIN;
		g_client =static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK客户端对象指针失败");
			return;
		}
		m_chatservice = CHATSERVICE;
		m_fileservice = FILESERVICE;
		m_searchservice = SEARCHSERVICE;
		m_configservice = CONFIGSERVICE;
		m_userservice   = USERSERVICE;
		m_contactservice = CONTACTSERVICE;
		m_groupservice   = GROUPSERVICE;
	END;
	}

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
	void ChatMgrControl::RegChatListNotify(CFunction< void(int, std::vector<CSharedPtr<data::ChatData>>&)> cb){
		BEGIN;
		AddLog(LOG_LEV_INFO, "Into RegChatListNotify");
		  m_chatlistnotifycb = cb;
		  m_userservice->getAccountInfo(m_account);
		  m_chatservice->regRecontactCb(CBind(&ChatMgrControl::OnChatListNotify,this,CPlaceholders  _1,CPlaceholders  _2));
		END;
	}
	/*********************************************************************************************************
	* @brief 获取最近会话列表接口
	* @param[out] chatlist 传出会话列表
	************************************************************************************************************/
	void ChatMgrControl::GetChatList(std::vector<CSharedPtr<data::ChatData>> &chatlist){
		BEGIN;
		  std::vector<CSharedPtr<model::Chat>>chat;
		  m_chatservice->getChatList(chat);
		  chatlist = DataListConvert(chat);
		END;
	}

	/**********************************************************************************************************
	*brief 监听最近回话头像更新推送
	*@param[out] cb _1 传入目标ID，人或者群  _2 传入头像
	**********************************************************************************************************/
	void ChatMgrControl::RegChatListHeadUpdate(CFunction < void(int64, const std::string&)> cb){
		BEGIN;
		     m_chatservice->regChatHeadImgUpdateCb(cb);
		END;
	}
	/**********************************************************************************************************
	*brief 设置监听新聊天消息的回调
	*@param[in] cb _1 消息结构的智能指针
	**********************************************************************************************************/
	void ChatMgrControl::RegRecvMsgNotice(CFunction< void(CSharedPtr<data::Msg>)>cb){
		BEGIN;
		    m_recvmsgcb = cb;
		    m_chatservice->regMsgNoticeCb(CBind(&ChatMgrControl::OnRecvMsgNotice,this,CPlaceholders  _1));
		END;
	} 
	/**********************************************************************************************************
	*brief 设置监听图片消息更新推送
	*@param[in] cb _1 消息结构的智能指针
	**********************************************************************************************************/
	void ChatMgrControl::RegImgMsgNotice(CFunction< void(CSharedPtr<data::Msg>)> cb){
		BEGIN;
		    m_downloadimagecb = cb;
		END;
	}
	/**********************************************************************************************************
	*brief 设置监听消息发送状态更新推送
	*@param[out] err 错误值  localid界面唯一标示符  time消息时间  targetid目标id externd图片消息则是 
	**********************************************************************************************************/
	void ChatMgrControl::RegMsgStatusNotice(CFunction< void(CSharedPtr<data::MsgStatus>)>cb){
		BEGIN;
		    m_msgstauscb = cb;
		END;
	}
	/**********************************************************************************************************
	*brief 设置进度监听回调
	*@param[out] _1 进度对应的文件的localId _2 进度标示 _3进度 _4文件当前传入大小/文件总大小
	**********************************************************************************************************/
	void ChatMgrControl::RegProcessCb(int64 localid,CFunction<void(int64, int32, int32, const std::string&)> cb){
		BEGIN;
			std::map<int64, ProgressPtr>::iterator iter = m_procbmap.find(localid);
			if (iter == m_procbmap.end())
			{
				m_procbmap.insert(std::pair<int64,ProgressPtr>(localid,cb));
			}
			else
			{
				m_procbmap[localid] = cb;
			}
		END;
	}

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
	void ChatMgrControl::GetMessages(int64 targetId, int64 msgId, int count, int flag, CFunction<void(int,int64,std::vector<CSharedPtr<data::Msg>>&)>cb){
		BEGIN;
		    m_getmessagecb = cb;
			m_chatservice->getMessages(targetId,msgId,count,flag,
				CBind(&ChatMgrControl::OnGetMessagesCb,
				this,
				CPlaceholders  _1,
				CPlaceholders  _2,
				CPlaceholders  _3));
		END;
	}
	void ChatMgrControl::OnGetMessagesCb(service::ErrorInfo err,int64 sessionid,std::vector<MsgPtr>&msglist){
		BEGIN;
		     if ( CNull != m_getmessagecb)
		     {
				 AddLog(LOG_LEV_DEBUG,"err=%d,sessionId=%lld",err,sessionid);
				 m_getmessagecb(err,sessionid,DataListConvert(msglist));
		     }
		END;
	}

	/***************************************************************************************
	* @brief 发送消息，返回localid
	* @param[in] msg 传入消息
	* @param[out] cb  传入接收结果回调 _1 错误信息 _2 发送时间 _3消息ID
	****************************************************************************************/
	int64 ChatMgrControl::SendMessage(CSharedPtr<data::Msg>&msg,CFunction<void(int,int64,int64)>cb){
		int64 msglocalid = 0;
		CSharedPtr<model::Msg> sendmsg = DataConvert(msg);
		if(sendmsg->isPrivateMsg == 2){
			sendmsg->isPrivateMsg = 1;
		}
		m_sendmsgcbmap.insert(std::pair<int64,SendMsgCallBackPtr>(sendmsg->localId,cb));
		if ( (data::MSG_TYPE_IMG == sendmsg->msgType || data::MSG_TYPE_FILE == sendmsg->msgType || data::MSG_TYPE_AUDIO == sendmsg->msgType) && msg->UpFileFlag == 0)
		{
			m_chatservice->sendAppendixMessage(*sendmsg,
											    CBind(
												&ChatMgrControl::OnSendMsgCb,
												this,
												CPlaceholders  _1,
												CPlaceholders  _2,
												CPlaceholders  _3,
												CPlaceholders  _4,
												sendmsg->msgType,
												sendmsg->targetId,
												sendmsg->localId),
												CBind(
												&ChatMgrControl::onProgressCb,
												this,
												CPlaceholders  _1,
												CPlaceholders  _2,
												CPlaceholders  _3,
												sendmsg->localId
												));
		}
		else{
			msglocalid = m_chatservice->sendMessage(
												*sendmsg,
												CBind(&ChatMgrControl::OnSendMsgCb,
												this,
												CPlaceholders  _1,
												CPlaceholders  _2,
												CPlaceholders  _3,
												CPlaceholders  _4,
												sendmsg->msgType,
												sendmsg->targetId,
												sendmsg->localId));
		}
	
		return msglocalid;
	}
	void ChatMgrControl::OnSendMsgCb(int err,int64 time,int64 msgid,model::BadWord&bad,int msgtype,int64 tagetid,int64 localid){
		BEGIN;
		    AddLog(LOG_LEV_DEBUG,"err=%d,time=%ld,msgid=%ld",err,time,msgid);
		    if ( CNull != m_msgstauscb)
		    {
				CSharedPtr<data::MsgStatus> msgstatus = CMakePtr<data::MsgStatus>();
				msgstatus->err = err;
				msgstatus->localid = localid;
				msgstatus->msgtime = time;
				msgstatus->msgtype = msgtype;
				msgstatus->targetid = tagetid;
				m_msgstauscb(msgstatus);
		    }
			SendMsgCallBackPtr sendmsgcb = GetCallBackFucPtr<SendMsgCallBackPtr,std::map<int64,SendMsgCallBackPtr>>(localid,m_sendmsgcbmap);
			if ( CNull != sendmsgcb)
			{
				sendmsgcb(err,time,msgid);
				RemoveCallBackFucPtr<std::map<int64,SendMsgCallBackPtr>>(localid, m_sendmsgcbmap);
			}
		END;
	}
	/*************************************************************************************************
	* @brief 设置消息已读
	* @param[in] targetid 传入会话对应的ID，群或者人
	* @param[in] msgId 需要设置的消息ID 比如设置为100, 比100小的所有消息都为已读
	***************************************************************************************************/
	void ChatMgrControl::setMessageRead(int64 targetId, int64 msgId){
		BEGIN;
		    AddLog(LOG_LEV_DEBUG,"targetId=%lld,msgId=%lld",targetId,msgId);
			m_chatservice->setMessageRead(targetId,msgId);
		END;
	}
	/************************************************************************************************************************
	* @brief 移除会话
	* @param[in] targetid 传入会话对应的ID，群或者人 0为删除全部联系人
	***************************************************************************************************************************/
	void ChatMgrControl::RemoveChat(int64 targetId){
		BEGIN;
		   AddLog(LOG_LEV_DEBUG,"targetId=%lld",targetId);
		   m_chatservice->removeChat(targetId,CBind(&ChatMgrControl::OnRemoveChat,this,CPlaceholders  _1));
		END;
	}
	/************************************************************************************************************************
	* brief 下载图片接口
	* @param[in] targetid 传入会话对应的ID，群或者人 0为删除全部联系人
	* @param[out] err 错误值 imgName图片名需要+USERIMAGE  tarid 对方id
	***************************************************************************************************************************/
    void ChatMgrControl::DownLoadImage(int64 targetid,std::string&url,CFunction<void(int err,const std::string&imgName,int64 tarid)>cb){
		BEGIN;
		    AddLog(LOG_LEV_DEBUG,"targetId=%lld,url=%s",targetid,url.c_str());
		    m_fileservice->downloadImage(targetid,url,cb);
		END;
	}
	/************************************************************************************************************************
	* brief 下载文件接口
	* @param[in] download 穿入下载文件所需信息
	* @param[out] 传入接收结果回调 _1错误信息  _2接收成功后文件路径 localPath _3发送者ID
	***************************************************************************************************************************/
	void ChatMgrControl::DownLoadFile(CSharedPtr<data::DownLoadFile>&download, 
		CFunction<void(int err,const std::string&fileName, int64 targetId)>cb,
		CFunction<void(int32, int32, const std::string&)> pro){
	   BEGIN;
	       model::DownloadFileProperty downFileInfo;
		   downFileInfo.bisP2P = download->bisP2P;
		   downFileInfo.bIsResume = download->bIsResume;
		   downFileInfo.encryptKey = download->encryptKey;
		   downFileInfo.fileName = download->fileName;
		   downFileInfo.fromUserId = download->fromUserId;
		   downFileInfo.localId = download->localId;
		   downFileInfo.localPath = download->localPath;
		   downFileInfo.msgid = download->msgid;
		   downFileInfo.targetId = download->targetId;
		   downFileInfo.url = download->url;
		   m_fileservice->downloadFile(downFileInfo,cb,
									   CBind(&ChatMgrControl::onProgressCb,
									   this,
									   CPlaceholders  _1,
									   CPlaceholders  _2,
									   CPlaceholders  _3,
									   downFileInfo.localId
									   ));
	   END;
	}
	/*********************************************************************************************************************
	* brief 解密文件
	* @param[in] encryptkey 传入解密密码
	* @param[in] srcpath 传入原图路径
	* @param[in] destpath 传入解密后图片路径
	********************************************************************************************************************/
	bool ChatMgrControl::decryptFile(const std::string &encryptkey, const std::string &srcpath, const std::string &destpath){
		 BEGIN;
		      return m_fileservice->decryptFile(encryptkey,srcpath,destpath);
		 END;
	}

	/**
		* \brief 设置私信秘钥
		* @param[in] targetId 目标ID，个人或群
		* @param[in] passwd  私信秘钥  为空代表清除私信密码.
		* @param[in] cb  传入接收结果回调 _1 错误信息 
	*/
	void ChatMgrControl::setPrivateKey(int64 targetId, const std::string &passwd)
	{
		BEGIN;
			//AddLog(LOG_LEV_INFO,"SetPrivateKey Info TargetId %d, PrivateKey %s",targetId, passwd);
			m_chatservice->setPrivateKey(targetId, passwd, CBind(&ChatMgrControl::onGetSetPrivateKey,this,CPlaceholders  _1));
		END;
	}

	/**
		* \brief 通过消息ID解密消息
		* @param[in] targetId 目标ID，个人或群
		* @param[in] msgIds  要解密的消息ID集合
		* @param[in] cb  传入接收结果回调 _1 错误信息 _2 解密消息的targetId _3已解密的消息
		*/
	void ChatMgrControl::decryptMsg(int64 targetId, std::vector<int64> &msgIds, CFunction<void(int, int64, std::vector<CSharedPtr<data::Msg>>&)> cb)
	{
		BEGIN;
			mDecryptmsgPtr = cb;
			m_chatservice->decryptMsg(targetId, msgIds, CBind(&ChatMgrControl::onGetDecryptMsgCb, this, CPlaceholders  _1,CPlaceholders  _2,CPlaceholders  _3));
		END;
	}

	void ChatMgrControl::onGetSetPrivateKey(service::ErrorInfo pErrorCode)
	{
		BEGIN;
			AddLog(LOG_LEV_ERROR,"SetPrivateKey Failed,ErrorCode %d",pErrorCode);
		END;
	}

	void ChatMgrControl::DownLoadImage(int64 targetid,int64 localid,std::string&url,int& docid,std::string&encryptkey){
		BEGIN;
		    //AddLog(LOG_LEV_DEBUG,"targetId=%lld,localId=%lld,url=%s,docid=%d,encryptkey=%s",targetid,localid,url.c_str(),docid,encryptkey.c_str());
		    m_fileservice->downloadImage(
				targetid,
				url,
				CBind(& ChatMgrControl::onDownLoadImage,
				this,
				CPlaceholders  _1,
				CPlaceholders  _2,
				CPlaceholders  _3,
				localid,
				docid,
				encryptkey));
		END;
	}
	void ChatMgrControl::onDownLoadImage(service::ErrorInfo err,const std::string&localpath, int64 targetid,int64 localid,int docid, std::string encrptkey){
		BEGIN;
		    std::string imgpath("");
		    if (!err)
		    {
				IConfigService_Ptr config = CONFIGSERVICE;
				std::string path = config->userImgPath()+localpath;
				bool bret = utils::FileIsExist(path);
				if ( bret && docid)
				{
					imgpath = config->userImgPath()+"cache/"+utils::GetFileName(path);
					bret = m_fileservice->decryptFile(encrptkey,path,imgpath);
					if ( !bret)
					{
						AddLog(LOG_LEV_ERROR,"decryptFile Failed,localpath=%s,destPath=%s",localpath,imgpath);
					}
				}
				
		    }
			if ( CNull != m_recvmsgcb)
			{
				CSharedPtr<data::MsgImg> imgMsg= CMakePtr<data::MsgImg>();
				imgMsg->targetId = targetid;
				imgMsg->localId = localid;
				imgMsg->thumbPath = ParseJsonData::char2utf8(imgpath);
				m_downloadimagecb(imgMsg);
			}
		END;
	}
	void ChatMgrControl::onProgressCb(int32 extra_req ,int32 process,const std::string& info,int64 localid){
		ProgressPtr ptr = GetCallBackFucPtr<ProgressPtr,std::map<int64,ProgressPtr>>(localid,m_procbmap);
		if ( CNull != ptr)
		{
			ptr(localid,extra_req,process,info);
		}
	}
	std::vector<CSharedPtr<data::ChatData>> ChatMgrControl::DataListConvert(std::vector<CSharedPtr<model::Chat>>&chat){
		std::vector<CSharedPtr<data::ChatData>>chatlist;
		for (size_t index=0; index<chat.size(); ++index)
		{
			CSharedPtr<data::ChatData> chatdata = CMakePtr<data::ChatData>();
			*chatdata = DataConvert(*(chat.at(index).get()));
			AddLog(LOG_LEV_DEBUG,"last_msg_time=%lld",chatdata->msgTime);
			AddLog(LOG_LEV_DEBUG,"realUnReadCnt=%d",chatdata->unReadCnt);
			chatlist.push_back(chatdata);

			int msgType = chatdata->msgType &0xff00;
			if (msgType == 0)
			{
				
			}
		}
		return chatlist;
	}
	std::vector<CSharedPtr<data::Msg>>ChatMgrControl::DataListConvert(std::vector<CSharedPtr<model::Msg>>&msglist){
		std::vector<CSharedPtr<data::Msg>>msglist_res;
		for (size_t index=0; index<msglist.size(); ++index)
		{
			CSharedPtr<model::Msg> msg = msglist.at(index);
			int realMsgType = msg->msgType & 0xff00;
			if (msg->msgType == 15 || msg->msgType == 14 ||realMsgType == 0x100 || realMsgType == 0x200 || realMsgType == 0x400)
			{
				continue;
			}
			if (msg->msgType == MSG_TYPE_TIP) {
				model::MsgTip* dataTip = (model::MsgTip*)(msg.get());
				if (dataTip->tipType == 12 && dataTip->operType == 0) {
					continue;
				}
			}
			if (msg->activeType == 1 &&!( msg->fromId !=m_account.id.value()?true:false))
			{
				continue;
			}
			
			if (msg->msgType == MSG_TYPE_COMBINE)
			{
				model::MsgCombine* msgCom = (model::MsgCombine*)msg.get();
				CSharedPtr<data::MsgCombine> msgData = CMakePtr<data::MsgCombine>();
				for (int i=0;i<msgCom->mVt_msg.size();++i)
				{
					CSharedPtr<data::Msg> curMsg = CNull;
					if (msgCom->mVt_msg.at(i)->msgType == MSG_TYPE_NINEBLOCK)
					{
						curMsg =ConvertNineBlockMsg(msgCom->mVt_msg.at(i));
					}else{
						curMsg = DataConvert(msgCom->mVt_msg.at(i));
					}
					std::string context = ParseJsonData::char2utf8("{\"body\":\"")+msgCom->mVt_msg.at(i)->body+ParseJsonData::char2utf8("\"}");
					curMsg->context = ParseJsonData::ParaseJson(msgCom->mVt_msg.at(i)->msgType,msgCom->mVt_msg.at(i)->activeType,context,msgCom->mVt_msg.at(i)->msgProperties);
					msgData->mVt_msg.push_back(curMsg);
				}
				static CSharedPtr<data::Msg> msgBase = CNull;
				msgBase = msgData;
				msgBase->isPrivateMsg = msg->isPrivateMsg;
				msgBase->isFeather = msg->isFeather;
				msgBase->relatedUsers = msg->relatedUsers;
				msgBase->deviceType = msg->deviceType;
				msgBase->fromId =msg->fromId;
				msgBase->isBurn = (msg->activeType == 0x01);
				msgBase->lastMsgId = msg->lastMsgId;
				msgBase->localId = msg->msgId;
				msgBase->msgId = msg->msgId;
				msgBase->targetId = msg->targetId;
				msgBase->time = msg->time;
				msgBase->toId = msg->toId;
				msgBase->isRecvMsg = msg->fromId !=m_account.id.value()?true:false;
				msgBase->isGroup   = IS_MSG_GROUP(msg->targetId);
				msgBase->isUser    = IS_MSG_USER(msg->targetId);
				msgBase->userId    = m_account.id.value();
				msgBase->isDeviceMsg = (msg->fromId==m_account.id.value() && 2==msg->deviceType)?true:false;
				msglist_res.push_back(msgBase);
			}else if(msg->msgType == MSG_TYPE_NINEBLOCK)
			{
				msglist_res.push_back(ConvertNineBlockMsg(msg));
			}else{
				msglist_res.push_back(DataConvert(msg));
			}
		}
		return msglist_res;
	}
	void ChatMgrControl::OnChatListNotify(int flag,std::vector<CSharedPtr<model::Chat>>&chatlist){
		BEGIN;
		     AddLog(LOG_LEV_DEBUG,"flag=%0X",flag);
			 if (CNull != m_chatlistnotifycb)
			 {
				 std::vector<CSharedPtr<model::Chat>> chatv = onFilterChatMsg(chatlist);
				 m_chatlistnotifycb(flag, DataListConvert(chatv));
			 }
		END;
	}

	std::vector<CSharedPtr<model::Chat>> ChatMgrControl::onFilterChatMsg(std::vector<CSharedPtr<model::Chat>>& chatlist)
	{
		std::vector<CSharedPtr<model::Chat>> listv;
		for (int i = 0; i < chatlist.size();i++)
		{
			if (chatlist.at(i)->chatType == 2 && (chatlist.at(i)->msgType == 18))
			{
				continue;
			}
			listv.push_back(chatlist.at(i));
		}
		return listv;
	}

	void ChatMgrControl::OnRecvMsgNotice(CSharedPtr<model::Msg> msg){
		BEGIN;
		   if ( CNull != m_recvmsgcb)
		   {
			   if (msg->msgType == 15 /*|| msg->msgType == MSG_TYPE_UNREADSTATE*/ || msg->msgType == 14) {

				   return;
			   }
			   if (msg->msgType == MSG_TYPE_TIP) {
				   model::MsgTip* dataTip = (model::MsgTip*)(msg.get());
				   if (dataTip->tipType == 12 && dataTip->operType == 0) {
					   return;
				   }
			   }
			   if (msg->msgType == MSG_TYPE_COMBINE)
			   {
				   model::MsgCombine* msgCom = (model::MsgCombine*)msg.get();
				   CSharedPtr<data::MsgCombine> msgData = CMakePtr<data::MsgCombine>();
				   for (int i=0;i<msgCom->mVt_msg.size();++i)
				   {
					   CSharedPtr<data::Msg> curMsg =CNull;
					   if (msgCom->mVt_msg.at(i)->msgType == MSG_TYPE_NINEBLOCK)
					   {
						  curMsg = ConvertNineBlockMsg(msgCom->mVt_msg.at(i));
					   }else{
						     curMsg = DataConvert(msgCom->mVt_msg.at(i));
					   }
					   std::string context = "{\"body\":\""+msgCom->mVt_msg.at(i)->body+"\"}";
					   curMsg->context = ParseJsonData::ParaseJson(msgCom->mVt_msg.at(i)->msgType,msgCom->mVt_msg.at(i)->activeType,context,msgCom->mVt_msg.at(i)->msgProperties);
					   msgData->mVt_msg.push_back(curMsg);
				   }
				   static CSharedPtr<data::Msg> msgBase = CNull;
				   msgBase = msgData;
				   msgBase->isPrivateMsg = msg->isPrivateMsg;
				   msgBase->relatedUsers = msg->relatedUsers;
				   msgBase->deviceType = msg->deviceType;
				   msgBase->fromId =msg->fromId;
				   msgBase->isBurn = (msg->activeType == 0x01);
				   msgBase->lastMsgId = msg->lastMsgId;
				   msgBase->localId = msg->msgId;
				   msgBase->msgId = msg->msgId;
				   msgBase->targetId = msg->targetId;
				   msgBase->time = msg->time;
				   msgBase->toId = msg->toId;
				   msgBase->isRecvMsg = msg->fromId !=m_account.id.value()?true:false;
				   msgBase->isGroup   = IS_MSG_GROUP(msg->targetId);
				   msgBase->isUser    = IS_MSG_USER(msg->targetId);
				   msgBase->userId    = m_account.id.value();
				   msgBase->isDeviceMsg = (msg->fromId==m_account.id.value() && 2==msg->deviceType)?true:false;
				   m_recvmsgcb(msgBase);
			   }else if(msg->msgType == MSG_TYPE_NINEBLOCK)
			   {
				   m_recvmsgcb(ConvertNineBlockMsg(msg));
			   }
			   else{
				   m_recvmsgcb(DataConvert(msg));
			   }
			   
		   }
		END;
	}
	void ChatMgrControl::OnRemoveChat(service::ErrorInfo err){
		BEGIN;
		   AddLog(LOG_LEV_DEBUG,"err=%d",err);
		END;
	}
	data::ChatData ChatMgrControl::DataConvert(model::Chat& data){

		int msgMindType  = data.msgRemindMode & 0x0F;
		
		int type = data.msgType & 0x00ff;

		data::ChatData res;
		res.avatar = data.avatar.value();
		res.avatarUrl = data.avatarUrl.value();
		res.thumbAvatar =utils::GetHeadPath(data.gender.value(),data.thumbAvatar.value());
		res.thumbAvatarUrl = data.thumbAvatarUrl.value();


		res.name    = data.name.value();
		
		res.timeZone =data.timeZone.value();
		res.extends = data.extends.value();
		res.gender  = data.gender.value();
		res.id      = data.id.value();
		if ((data.operType == 1) && (type == MSG_TYPE_IMG || type == MSG_TYPE_TEXT|| type == MSG_TYPE_AUDIO))
		{
			res.lastMsg = ParseJsonData::char2utf8(BURN_MSG_TIP);
		}else{
			res.lastMsg = ParseJsonData::ParaseJson(data.msgType,data.operType,data.lastMsg,data.msgProp);
		}
		res.msgTime = data.msgTime;
		res.msgType = data.msgType;
		res.chatType = data.chatType;
		res.realUnReadCnt = data.realUnReadCnt;
		res.unReadCnt = data.unreadCount;
		res.sendUserId = data.sendUserId;
	    res.msgProp = data.msgProp;
		res.operType =data.operType;
		res.lastMsgId = data.lastMsgId;
		res.lastAtMsgID = data.lastAtMsgID;
		res.disturbSet = data.disturbSet;
		res.subType = data.subType;
		res.msgRemindMode = data.msgRemindMode&0x0F;
		
		std::string temp = res.lastMsg;
		std::string wheretemp = data.whereFrom.empty()||GROUP_CHAT !=res.chatType?std::string(""):data.whereFrom+std::string(":");
		AddLog(LOG_LEV_DEBUG,"where from =%s",wheretemp.c_str());
		res.lastMsg = wheretemp+res.lastMsg;
		utils::string_replace(res.lastMsg,"\n","");

		if ( APP_CHAT ==res.chatType && res.name.value().empty())
		{
			m_userservice->getAppInfo(res.id.value(),CBind(&ChatMgrControl::onGetAppInfo,this,CPlaceholders  _1,CPlaceholders  _2,res));
		}
		else if(GROUP_CHAT ==res.chatType && res.name.value().empty())
		{
			model::Group groupinfo;
			m_groupservice->getGroupInfo(res.id.value(),groupinfo);
			res.avatar = groupinfo.info.value().avatar.value();
			res.name= groupinfo.info.value().groupName.value();
		}
		else if(res.name.value().empty()){
			model::Contact contact;
			m_contactservice->getContactInfo(res.id.value(),contact);
			res.avatar = contact.avatar.value();
			res.thumbAvatar = utils::GetHeadPath(contact.gender.value(),contact.thumbAvatar.value());
			res.name= contact.name.value();
		}
		return res;
	}
	void ChatMgrControl::onGetAppInfo(service::ErrorInfo err,model::EntAppinfo&appinfo,data::ChatData chatdata){
		if ( !err)
		{
			std::vector<CSharedPtr<data::ChatData>>chatlist;
			CSharedPtr<data::ChatData> data=CNull;
			data = CMakePtr<data::ChatData>();
			chatdata.avatar = utils::GetHeadPath(4,appinfo.appIcon);

			chatdata.name   = appinfo.appName;
			if (CNull != m_chatlistnotifycb)
			{
				*data = chatdata;
				chatlist.push_back(data);
				m_chatlistnotifycb(0x08,chatlist);
			}
		}
	}

	CSharedPtr<model::Msg> ChatMgrControl::DataConvert(CSharedPtr<data::Msg>&data){
		static CSharedPtr<model::Msg> msg = CNull;
		switch(data->msgType){
		case MSG_TYPE_DYNEXPRESSION:
			{
				CSharedPtr<model::MsgDynExpression> msgDny = CMakePtr<model::MsgDynExpression>();
				data::MsgDynExpression* dataDny = (data::MsgDynExpression* )(data.get());
				msgDny->body = data->body;
				msg = msgDny;
				break;
			}
		case MSG_TYPE_AUDIO:
			{
				CSharedPtr<model::MsgAudio> msgAudio = CMakePtr<model::MsgAudio>();
				data::MsgAudio* dataAudio = (data::MsgAudio* )(data.get());
				msgAudio->encryptKey = m_encrptkey.get_key();
				msgAudio->fileName = dataAudio->fileName;
				msgAudio->localPath = dataAudio->localPath;
				msgAudio->isOld = false;
				msgAudio->mediaTime = dataAudio->mediaTime;
				msg = msgAudio;
				break;
			}
		case MSG_TYPE_CARD:
			{
				CSharedPtr<model::MsgCard> msgCard = CMakePtr<model::MsgCard>();
				data::MsgCard* dataCard = (data::MsgCard* )(data.get());
				msgCard->mediaUrl = dataCard->mediaUrl;
				msg = msgCard;
				break;
			}
		case MSG_TYPE_TEXT:
			{
				CSharedPtr<model::MsgText> msgText = CMakePtr<model::MsgText>();
				msgText->body = ParseJsonData::emojisenddeal(data->body);
				msgText->isRbtMsg = data->isRbtMsg;
				msgText->isDelay = data->isDelay;
				msgText->delayTime = data->delayTime;
				msgText->isReceipt = data->isReceipt;
				msgText->isReceiptAll = data->isReceiptAll;
				msg = msgText;
				break;
			}
		case MSG_TYPE_REVOKE:
			{
				CSharedPtr<model::MsgRevoke> msgRevoke = CMakePtr<model::MsgRevoke>();
				data::MsgRevoke* dataRevoke = (data::MsgRevoke* )(data.get());
				msgRevoke->revokeMsgId = dataRevoke->revokeMsgId;
				msgRevoke->body = dataRevoke->body;
				msgRevoke->revokedBody = dataRevoke->body;
				msg = msgRevoke;
				Log(LOG_LEV_INFO, LOG_FILE,"msgRevoke-msgbody=%s", msg->body.c_str());
				break;
			}
		case MSG_TYPE_TIP:
		{
				CSharedPtr<model::MsgTip> msgtip = CMakePtr<model::MsgTip>();
				data::MsgTip* datatip = (data::MsgTip*)data.get();
				msgtip->tipType = datatip->tipType;
				msgtip->relatedMsgId = data->relatedMsgId;
				msgtip->msgType = data->msgType;
				msgtip->operType = datatip->operType;
				msgtip->tipTime = datatip->tipTime;
				msgtip->operUser = datatip->operUser;
				msgtip->userInfo = datatip->userInfo;
				msg = msgtip;

				break;
			}
		case MSG_TYPE_WEB:
			{
				CSharedPtr<model::MsgWeb> msgWeb = CMakePtr<model::MsgWeb>();
				data::MsgWeb* dataWeb = (data::MsgWeb* )(data.get());
				
				//std::string title;	 ///<网页内容标题
				//std::string url;	 ///<网页链接地址
				//std::string img;	 ///<网页内容第一张图片
				//std::string desc;	 ///<网页内容摘要
				msgWeb->title = dataWeb->title;
				msgWeb->url = dataWeb->url;
				msgWeb->img = dataWeb->img;
				msgWeb->desc = dataWeb->desc;
				msg = msgWeb;
				break;
			}
		case MSG_TYPE_IMG:
			{
				CSharedPtr<model::MsgImg> msgImg = CMakePtr<model::MsgImg>();
				data::MsgImg* dataimg = (data::MsgImg* )(data.get());
				msgImg->docID = 1;
				msgImg->encryptKey = m_encrptkey.get_key();
				msgImg->fileName =dataimg->fileName;
				msgImg->thumBbinary = dataimg->thumBbinary;
				msgImg->thumbPath = dataimg->thumbPath;
				msgImg->mainPath = dataimg->mainPath;
				msgImg->width = dataimg->width;
				msgImg->height = dataimg->height;
				msg = msgImg;
				break;
			}
		case MSG_TYPE_FILE:
			{
				CSharedPtr<model::MsgFile> msgFile = CMakePtr<model::MsgFile>();
				data::MsgFile* dataFile = (data::MsgFile* )(data.get());
				msgFile->docID = 1;
				msgFile->encryptKey = m_encrptkey.get_key();
				msgFile->fileName =dataFile->fileName;
				msgFile->filePath = dataFile->filePath;
				msgFile->fileId = dataFile->fileId;
				msgFile->isFolder = dataFile->isFolder;
				msgFile->isResume = dataFile->isResume;
				msgFile->states   = dataFile->states;
				msgFile->url      = dataFile->url;
				msgFile->size	  = dataFile->size;
				msg = msgFile;
				break;
			}
		default:
			{
				msg = CMakePtr<model::MsgText>();
				msg->body = "";
				break;
			}
		}
		msg->fromId =data->fromId;
		msg->activeType = data->isBurn?0x01:0;
		msg->lastMsgId = data->lastMsgId;
		msg->localId = data->localId;
		msg->msgId = data->msgId;
		msg->targetId = data->targetId;
		msg->time = data->time;
		msg->toId = data->toId;
		msg->relatedMsgId = data->relatedMsgId;
		msg->isFeather = data->isFeather;
		//msg->activeType = msg->isBurn;
		msg->isPrivateMsg = data->isPrivateMsg;
		msg->relatedUsers = data->relatedUsers;
		if (data->isBurn || data->isRbtMsg)
		{
			msg->noStore = 1;
		}
		return msg;
	}
	CSharedPtr<data::Msg> ChatMgrControl::DataConvert(CSharedPtr<model::Msg>&data){
		static CSharedPtr<data::Msg> msg = CNull;
		switch(data->msgType){
		case MSG_TYPE_TASK:
			{
				CSharedPtr<data::MsgTask> msgTask = CMakePtr<data::MsgTask>();
				model::MsgTask* dataTask = (model::MsgTask* )(data.get());
				msgTask->body = ParseJsonData::emojideal(dataTask->body,false);
				msgTask->timeTask = dataTask->timeTask;
				msgTask->isFinish = dataTask->isFinish;
				msgTask->isTask = dataTask->isTask;
				msgTask->isRead = dataTask->isRead;
				msg = msgTask;
				break;
		    }
		case MSG_TYPE_AUDIO:
			{
				CSharedPtr<data::MsgAudio> msgAudio = CMakePtr<data::MsgAudio>();
				model::MsgAudio* dataAudio = (model::MsgAudio* )(data.get());
				msgAudio->encryptKey = dataAudio->encryptKey;
				msgAudio->fileName = dataAudio->fileName;
				msgAudio->localPath = dataAudio->localPath;
				msgAudio->mediaTime = dataAudio->mediaTime;
				msgAudio->meidaUrl = dataAudio->meidaUrl;
				msg = msgAudio;
				break;
			}
		case MSG_TYPE_DYNEXPRESSION:
			{
				CSharedPtr<data::MsgDynExpression> msgDny = CMakePtr<data::MsgDynExpression>();
				model::MsgDynExpression* dataDny = (model::MsgDynExpression* )(data.get());
				msgDny->body = data->body;
				msg = msgDny;
				break;
			}
		case MSG_TYPE_CARD:
			{
				CSharedPtr<data::MsgCard> msgCard = CMakePtr<data::MsgCard>();
				model::MsgCard* dataCard = (model::MsgCard* )(data.get());
				msgCard->mediaUrl = dataCard->mediaUrl;
				msg = msgCard;
				break;
			}
		case MSG_TYPE_TEXT:
			{
				msg = CMakePtr<data::MsgText>();
				model::MsgText* textMsg = (model::MsgText* )(data.get());
				msg->body = ParseJsonData::emojideal(data->body,false);
				msg->EraserType = ParseJsonData::dealEraserType(data->body);
				msg->relatedUsers = textMsg->relatedUsers;
				msg->isDelay = textMsg->isDelay;
				msg->delayTime = textMsg->delayTime;
				msg->isReceipt = textMsg->isReceipt;
				msg->isReceiptAll = textMsg->isReceiptAll;
				break;
			}
		case MSG_TYPE_REVOKE:
			{
				CSharedPtr<data::MsgRevoke> msgRevoke = CMakePtr<data::MsgRevoke>();
				model::MsgRevoke* dataRevoke = (model::MsgRevoke* )(data.get());
				msgRevoke->revokeMsgId = dataRevoke->revokeMsgId;
				msgRevoke->body = dataRevoke->body;
				msg = msgRevoke;
				break;
			}
		case MSG_TYPE_WEB:
			{
				CSharedPtr<data::MsgWeb> msgWeb = CMakePtr<data::MsgWeb>();
				model::MsgWeb* dataWeb = (model::MsgWeb* )(data.get());

				//std::string title;	 ///<网页内容标题
				//std::string url;	 ///<网页链接地址
				//std::string img;	 ///<网页内容第一张图片
				//std::string desc;	 ///<网页内容摘要
				msgWeb->title = dataWeb->title;
				msgWeb->url = dataWeb->url;
				msgWeb->img = dataWeb->img;
				msgWeb->desc = dataWeb->desc;
				msg = msgWeb;
				break;
			}
		case MSG_TYPE_IMG:
			{
				CSharedPtr<data::MsgImg> msgImg = CMakePtr<data::MsgImg>();
				model::MsgImg* dataimg = (model::MsgImg* )(data.get());
				msgImg->docID = dataimg->docID;
				msgImg->encryptKey = dataimg->encryptKey;
				msgImg->fileName =dataimg->fileName;
				msgImg->thumBbinary = dataimg->thumBbinary;
				msgImg->thumbPath = dataimg->thumbPath;
				msgImg->mainPath = dataimg->mainPath;
				msgImg->thumbUrl = dataimg->thumbUrl;
				msgImg->mainUrl  = dataimg->mainUrl;
				msgImg->width = dataimg->width;
				msgImg->height = dataimg->height;
				msgImg->localId = dataimg->msgId;
				msgImg->imageContents = dataimg->imageContents;
				msg = msgImg;
				break;
			}
		case MSG_TYPE_FILE:
			{
				CSharedPtr<data::MsgFile> msgFile = CMakePtr<data::MsgFile>();
				model::MsgFile* dataFile = (model::MsgFile* )(data.get());
				msgFile->docID = dataFile->docID;
				msgFile->encryptKey = dataFile->encryptKey;
				msgFile->fileName =dataFile->fileName;
				msgFile->filePath = dataFile->filePath;
				msgFile->fileId = dataFile->msgId;
				msgFile->isFolder = dataFile->isFolder;
				msgFile->isResume = dataFile->isResume;
				msgFile->states   = dataFile->states;
				msgFile->url      = dataFile->url;
				msgFile->size	  = dataFile->size;
				IsSaveAsFile(msgFile);
				msg = msgFile;
				break;
			}
		case MSG_TYPE_TIP:
			{
				CSharedPtr<data::MsgTip> msgTip = CMakePtr<data::MsgTip>();
				model::MsgTip* dataTip = (model::MsgTip* )(data.get());
				msgTip->tipType = dataTip->tipType; ///<tip 类型
				msgTip->operType = dataTip->operType;///<操作类型
				msgTip->tipTime = dataTip->tipTime;///<时间
				msgTip->operUser = dataTip->operUser;///<操作userId
				msgTip->userInfo = dataTip->userInfo;///<用户信息
				msgTip->fileInfo = dataTip->fileInfo;///<文件信息
				msg = msgTip;
				break;
			}
		case MSG_TYPE_PICTEXT:
			{
				CSharedPtr<data::MsgPicWithText> msgPicTxt = CMakePtr<data::MsgPicWithText>();
				model::MsgPicWithText* dataPicTxt = (model::MsgPicWithText* )(data.get());
				for ( size_t index=0 ;index<dataPicTxt->vtPtBean.size();++index)
				{
					data::MsgPicWithText::picTextBean data;
					data.index = dataPicTxt->vtPtBean[index].index;
					data.picUrl = dataPicTxt->vtPtBean[index].picUrl;
					data.title = dataPicTxt->vtPtBean[index].title;
					data.url = dataPicTxt->vtPtBean[index].url;
					data.dsc = dataPicTxt->vtPtBean[index].dsc;
					msgPicTxt->vtPtBean.push_back(data);
				}
				msg = msgPicTxt;
				break;
			}
		case MSG_TYPE_TEMPL:
			{
				CSharedPtr<data::MsgMasterplate> msgTemplate = CMakePtr<data::MsgMasterplate>();
				model::MsgMasterplate* dataTemplate = (model::MsgMasterplate* )(data.get());
				msgTemplate->createTime=dataTemplate->createTime;
				msgTemplate->content=dataTemplate->content;
				msgTemplate->detailUrl=dataTemplate->detailUrl;
				msgTemplate->title=dataTemplate->title;
				msgTemplate->toUsers=dataTemplate->toUsers;
				msgTemplate->status=dataTemplate->status;
				msgTemplate->statColor=dataTemplate->statColor;
				msgTemplate->titleColor=dataTemplate->titleColor;
				msgTemplate->type=dataTemplate->type;
				msgTemplate->titleBGColor=dataTemplate->titleBGColor;
				msgTemplate->fields=ParseFields(dataTemplate->fields);
				msgTemplate->creator=dataTemplate->creator;
				msg = msgTemplate;
				break;
			}
		case MSG_TYPE_UNREADSTATE:
		case MSG_TYPE_SYS:
		//case MSG_TYPE_UNIVERSAL:
		{
			msg = CMakePtr<data::Msg>();
			msg->msgType = data->msgType;
			msg->body = data->body;
			break;
		}
		case MSG_TYPE_MINIVEDIO: //微视频
			{
				CSharedPtr<data::MsgMiniVedio> VedioMsg = CMakePtr<data::MsgMiniVedio>();
				model::MsgMiniVedio* dataVedio = (model::MsgMiniVedio* )(data.get());
				VedioMsg->brustFlag = dataVedio->brustFlag;
				VedioMsg->preImgPath = dataVedio->preImgPath;
				VedioMsg->vedioFileName = dataVedio->vedioFileName;
				VedioMsg->localPreImgPath = dataVedio->localPreImgPath;
				VedioMsg->localVedioPath = dataVedio->localVedioPath;
				VedioMsg->vedioHight = dataVedio->vedioHight;
				VedioMsg->vedioLenth = dataVedio->vedioLenth;
				VedioMsg->vedioWideth = dataVedio->vedioWideth;
				VedioMsg->vedioSize = dataVedio->vedioSize;
				VedioMsg->encryptKey = dataVedio->encryptKey;
				VedioMsg->docID = dataVedio->docID;
				VedioMsg->validity = dataVedio->validity;
				msg = VedioMsg;
				break;
			}
		default:
			{
				msg = CMakePtr<data::MsgText>();
				msg->body = ParseJsonData::char2utf8(UNDEFINE_MSG_TIP);
				break;
			}
		}
		msg->isPrivateMsg = data->isPrivateMsg;
		msg->relatedUsers = data->relatedUsers;
		msg->deviceType = data->deviceType;
		msg->fromId =data->fromId;
		msg->isBurn = (data->activeType == 0x01);
		msg->lastMsgId = data->lastMsgId;
		msg->localId = data->msgId;
		msg->msgId = data->msgId;
		msg->targetId = data->targetId;
		msg->time = data->time;
		msg->toId = data->toId;
		msg->relatedMsgId = data->relatedMsgId;
		msg->isFeather = data->isFeather;
		msg->isRecvMsg = msg->fromId !=m_account.id.value()?true:false;
		msg->isGroup   = IS_MSG_GROUP(msg->targetId);
		msg->isUser    = IS_MSG_USER(msg->targetId);
		msg->userId    = m_account.id.value();
		msg->isDeviceMsg = (msg->fromId==m_account.id.value() && 2==msg->deviceType)?true:false;
		if (msg->isDeviceMsg){
			if (data->targetId == m_account.id.value()){
				msg->isRecvMsg = true;
			}
		}
		msg->unReadCount = data->unReadCount;
		msg->maxUnReadCount = data->maxUnReadCount;
		msg->snapshotId = data->snapshotId;
		msg->subType = data->subType;
		msg->msgProperties = data->msgProperties;
		msg->userName = data->userName;
		msg->userPic = data->userPic;
		return msg;
	}
	void ChatMgrControl::IsSaveAsFile(CSharedPtr<data::MsgFile>&msg){
		std::vector<int64> idlist;
		std::map<int64, Fileinfo>files;
		std::map<int64, Fileinfo>::iterator itr;

		idlist.push_back(msg->fileId);
		m_fileservice->getFilesInfo(idlist,files);
		for ( itr = files.begin(); itr !=files.end(); ++itr)
		{
			if ( itr->first == msg->fileId)
			{
				msg->filePath = itr->second.path;
				std::string path = itr->second.path;
				msg->isSaveAs = (-1 == path.find(m_configservice->userFilePath())&& (msg->fromId != m_account.id.value()))?true:false;
				break;
			}
		}
	}
	std::map<std::string,std::string>ChatMgrControl::ParseFields(std::string json){
	  BEGIN;
		int ret = 0;
		Json::Reader reader;
		Json::Value root,fieldsarry;
		std::map<std::string,std::string>res;

		if ( -1 != json.find("fields"))
		{
			json = "{" + json + "}";
		}
		ret = reader.parse(json, root);
		if (!ret)
		{
			AddLog(LOG_LEV_ERROR,"json parse filed,err=%d,json=%s",ret,json.c_str());
			return res;
		}
		fieldsarry = root["fields"];
		if (!fieldsarry.isNull()&& fieldsarry.isArray())
		{
			for (Json::Value::iterator itr = fieldsarry.begin(); itr != fieldsarry.end(); itr++)
			{
				Json::Value::Members member;
				member = (*itr).getMemberNames();
				for (Json::Value::Members::iterator iter = member.begin(); iter != member.end(); iter++)
				{
					std::string val = (*itr)[(*iter)].asString();
					res.insert(std::pair<std::string,std::string>(member.at(0),val));
				}
			}
		}
	 END;
	   return res;
	}
	void ChatMgrControl::onGetUserInfo(int code, model::User& user,int64 msgid)
	{
		data::UserData out;
		out.id = user.id.value();
		out.gender = user.gender.value();
		out.name = user.name.value();
		out.entExtends = user.entExtends.value();
		out.thumbAvatar  = utils::GetHeadPath(user.gender.value(),user.thumbAvatar.value());
		if(msgid == 0)
		{
			std::map<int64,GetUserInfoCallBackPtr>::iterator iter = m_getuserinfocb.find(user.id.value());
			if (iter != m_getuserinfocb.end())
			{
				iter->second(code, out);
				m_getuserinfocb.erase(iter);
			}
		}
		else
		{
			std::map<int64,GetUserInfoCallBackPtr>::iterator iter = m_getuserinfocb.find(msgid);
			if (iter != m_getuserinfocb.end())
			{
				iter->second(code, out);
				m_getuserinfocb.erase(iter);
			}
		}
		
	}

	void ChatMgrControl::getUserInfo( int64 userid, int64 msgid,CFunction<void(int, data::UserData&)> cb )
	{
		if(m_searchservice){
			if(msgid != 0)
			{
				m_getuserinfocb[msgid] = cb;
			}
			else
			{
				m_getuserinfocb[userid] = cb;
			}
			if (IS_MSG_APP(userid))
			{
				m_userservice->getAppInfo(userid,CBind
					(&ChatMgrControl::onGetAppInfoByID,this,CPlaceholders  _1,CPlaceholders  _2,msgid));
			}else{
				m_searchservice->getUserInfo(userid,CBind
					(&ChatMgrControl::onGetUserInfo,this,CPlaceholders  _1,CPlaceholders  _2,msgid));
			}
		}
	}

	std::string ChatMgrControl::userCachePath()
	{
		return m_configservice->userCachePath();
	}

	void ChatMgrControl::onGetAppInfoByID( service::ErrorInfo err,model::EntAppinfo&appinfo,int64 msgid )
	{
		data::UserData out;
		out.avatar = appinfo.appIcon;
		out.name   = appinfo.appName;
		out.id = appinfo.appID;
		out.thumbAvatar = utils::GetHeadPath(4,appinfo.appIcon);
		out.thumbAvatarUrl = appinfo.appHomeUrl;
		if(msgid == 0)
		{
			std::map<int64,GetUserInfoCallBackPtr>::iterator iter = m_getuserinfocb.find(appinfo.appID);
			if (iter != m_getuserinfocb.end())
			{
				iter->second(err, out);
				m_getuserinfocb.erase(iter);
			}
		}
		else
		{
			std::map<int64,GetUserInfoCallBackPtr>::iterator iter = m_getuserinfocb.find(msgid);
			if (iter != m_getuserinfocb.end())
			{
				iter->second(err, out);
				m_getuserinfocb.erase(iter);
			}
		}
		
		//m_getuserinfocb();
	}

	void ChatMgrControl::getImgMsg( int64 targetId, CFunction<void(int, std::map<int64,data::MsgImg>)> cb )
	{
		if (targetId != 0)
		{
			m_ImgMsgcb = cb;
			m_chatservice->getImgMsg(targetId,CBind(&ChatMgrControl::onGetImgMsg,this,targetId,CPlaceholders _1,CPlaceholders _2));
		}
	}

	void ChatMgrControl::onGetImgMsg( int64 targetId,service::ErrorInfo err,std::vector<model::MsgPtr>&msgs )
	{
		//下载图片
		std::vector<CSharedPtr<data::Msg>> msgList = DataListConvert(msgs);
		std::map<int64,data::MsgImg>mapImgMsgs;
		std::map<int64,std::string> needs;
		for (int i=0;i<msgList.size();++i)
		{
			int msgType = msgList.at(i)->msgType & 0xff;
			if (msgType != data::MSG_TYPE_IMG)
			{
				AddLog(LOG_LEV_INFO,"getImgMsg msgType:%d",msgType);
				continue;
			}
			data::MsgImg msgImg;
			data::MsgImg* dataimg = (data::MsgImg*)msgList.at(i).get();

			msgImg.docID = dataimg->docID;
			msgImg.encryptKey = dataimg->encryptKey;
			msgImg.fileName =dataimg->fileName;
			msgImg.thumBbinary = dataimg->thumBbinary;
			msgImg.thumbPath = dataimg->thumbPath;
			msgImg.mainPath = dataimg->mainPath;
			msgImg.thumbUrl = dataimg->thumbUrl;
			msgImg.mainUrl  = dataimg->mainUrl;
			msgImg.width = dataimg->width;
			msgImg.height = dataimg->height;
			msgImg.msgId = dataimg->msgId;
			msgImg.targetId = dataimg->targetId;
	
			IConfigService_Ptr config = CONFIGSERVICE;
			std:: string imgpath = config->userImgPath()+"cache/"+utils::GetFileName(m_fileservice->getNameByUrl(dataimg->mainUrl));
			bool bret = utils::FileIsExist(imgpath);
			if (!bret)
			{
				needs[msgImg.msgId] = msgImg.encryptKey;
			}else{
				msgImg.mainPath = imgpath;
			}
			mapImgMsgs[msgImg.msgId] = msgImg;
			
		}
		//遍历下载图片
		std::map<int64,std::string>::iterator iter = needs.begin();
		if(iter != needs.end()){
			data::MsgImg img = mapImgMsgs[iter->first];
			m_fileservice->downloadImage(img.targetId,img.mainUrl,CBind(&ChatMgrControl::onDownloadBigImages,this,
				needs,mapImgMsgs,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3));
		}else{
			m_ImgMsgcb(0,mapImgMsgs);
		}
	}

	void ChatMgrControl::onGetDecryptMsgCb(int Rcode, int64 DecryptMsgId, std::vector<MsgPtr>& DecryMsgList)
	{
		std::vector<CSharedPtr<data::Msg>> msglist = DataListConvert(DecryMsgList);
		mDecryptmsgPtr(Rcode, DecryptMsgId,msglist);
	}

	void ChatMgrControl::onDownloadBigImages( std::map<int64,std::string>& needs,std::map<int64,data::MsgImg>&mapImgMsgs,service::ErrorInfo err, const std::string&localpath, int64 targetId )
	{
		IConfigService_Ptr config = CONFIGSERVICE;
		std::string path = config->userImgPath()+localpath;
		bool bret = utils::FileIsExist(path);

		std::map<int64,std::string>::iterator iter = needs.begin();
		data::MsgImg img = mapImgMsgs[iter->first];
		if ( bret && img.docID)
		{
			std:: string imgpath = config->userImgPath()+"cache/"+utils::GetFileName(path);
			if (!iter->second.empty())
			{
				bret = m_fileservice->decryptFile(iter->second,path,imgpath);
				if ( !bret)
				{
					AddLog(LOG_LEV_ERROR,"decryptFile Failed,localpath=%s,destPath=%s",localpath,imgpath);
				}else{
					img.mainPath = imgpath;
					mapImgMsgs[iter->first] = img;
				}
			}else{
				img.mainPath = path;
				mapImgMsgs[iter->first] = img;
			}
		}
		//判断是否有下一项
		needs.erase(iter);
		iter = needs.begin();
		if(iter != needs.end()){
			img = mapImgMsgs[iter->first];
			m_fileservice->downloadImage(img.targetId,img.mainUrl,CBind(&ChatMgrControl::onDownloadBigImages,this,
				needs,mapImgMsgs,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3));
		}else{
			m_ImgMsgcb(0,mapImgMsgs);
		}
	}

	void ChatMgrControl::forwardMessage( int64 fromTargetId, int64 toTargetId, int64 messageId, CFunction<void(int,int64,int64)> cb )
	{
		mForwardmsgCb = cb;
		m_chatservice->forwardMessage(fromTargetId,toTargetId,messageId,CBind(&ChatMgrControl::onForwardMsg,this,toTargetId,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3,CPlaceholders _4));
	}

	void ChatMgrControl::onForwardMsg(int64 toTargetId,service::ErrorInfo code,int64 time,int64 msgId,model::BadWord&word )
	{
		if (code != 0)
		{
			AddLog(LOG_LEV_ERROR,"forward msg err:%d",code);
		}else{
			m_chatservice->getMessages(toTargetId,msgId,1,0,CBind(&ChatMgrControl::OnGetMessageByMsgIdCb,this,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3));
		}
		mForwardmsgCb(code,time,msgId);
	}

	void ChatMgrControl::OnGetMessageByMsgIdCb( service::ErrorInfo err,int64 sessionid,std::vector<MsgPtr>&msglist )
	{
		if (err == 0 && msglist.size()>0)
		{
			OnRecvMsgNotice(msglist.at(0));
		}
	}

	void ChatMgrControl::getUrlInfo( const std::string &url, std::string& loginfoPath, CFunction<void(int, const std::string&, const std::string&, const std::string&, const std::string&)> cb )
	{
		if (m_chatservice)
		{
			m_chatservice->getUrlInfo(url,loginfoPath,cb);
		}
	}

	void ChatMgrControl::deleteMessageById( int64 targetId, std::vector<int64> &msgIds, CFunction<void(int)> cb )
	{
		if(m_chatservice){
			m_chatservice->deleteMessageById(targetId,msgIds,cb);
		}
	}

    void ChatMgrControl::deleteAllMessage( bool clearChatList, CFunction<void(int)> cb )
    {
        if (m_chatservice)
        {
           m_chatservice->deleteAllMessage(clearChatList,cb);
        }
    }

	/**
	* \brief 删除时间段消息
	* @param[in] targetid 传入会话对应的ID，群或者人 targetId为0，则针对所有用户
	* @param[in] beginTime 起始时间
	* @param[in] endTime 结束时间
	* @param[in] cb  结果回调 _1错误信息
	*/
	void ChatMgrControl::deleteMessageByTime(int64 targetId, int64 beginTime, int64 endTime, CFunction<void(int)> cb)
	{
		if (m_chatservice)
		{
			m_chatservice->deleteMessageByTime(targetId, beginTime, endTime,cb);
		}
	}

	void ChatMgrControl::chatTop( int64 targetId, bool isTop, CFunction<void(int)> cb )
	{
		if (m_chatservice)
		{
			m_chatservice->chatTop(targetId,isTop,cb);
		}
	}

	void ChatMgrControl::setUserNoDisturbMode( int64 targetId, int value, CFunction<void(int)> cb )
	{
		if (m_userservice)
		{
			if (isGroup(targetId))
			{ m_groupservice->setGroupMsgRemindType(targetId,value,cb);

			}else if(isUser(targetId)){
				m_userservice->setUserNoDisturbMode(targetId,value,cb);
				/*
				model::Contact con;
				con.id = targetId;
				con.disturbSet = value;
				m_contactservice->updateContactInfo(con,cb);*/
			}
			
		}
	}

	void ChatMgrControl::getUserNoDisturbMode( int64 targetId, CFunction<void(int, int64, int8)> cb )
	{
			if (isGroup(targetId))
			{ 
				mGetUserNoDisturbModeCb = cb;
				m_groupservice->getGroupMsgRemindType(targetId,CBind(&ChatMgrControl::onGetGroupMsgRemindType,this,CPlaceholders _1,CPlaceholders _2,targetId));
			}else if(isUser(targetId)){
				m_userservice->getUserNoDisturbMode(targetId,cb);
			}
	}

	void ChatMgrControl::onGetGroupMsgRemindType( service::ErrorInfo code, int8 msgMindType,int64 targetId )
	{
		mGetUserNoDisturbModeCb(code,targetId,msgMindType);
	}

	std::string ChatMgrControl::userAudioPath()
	{
		return m_configservice->userAudioPath();
	}

	data::MsgImg ChatMgrControl::DataConvert( model::MsgImg&dataimg )
	{
		data::MsgImg msgImg;

		msgImg.docID = dataimg.docID;
		msgImg.encryptKey = dataimg.encryptKey;
		msgImg.fileName =dataimg.fileName;
		msgImg.thumBbinary = dataimg.thumBbinary;
		msgImg.thumbPath = dataimg.thumbPath;
		msgImg.mainPath = dataimg.mainPath;
		msgImg.thumbUrl = dataimg.thumbUrl;
		msgImg.mainUrl  = dataimg.mainUrl;
		msgImg.width = dataimg.width;
		msgImg.height = dataimg.height;
		msgImg.localId = dataimg.msgId;

		msgImg.isPrivateMsg = dataimg.isPrivateMsg;
		msgImg.relatedUsers = dataimg.relatedUsers;
		msgImg.deviceType = dataimg.deviceType;
		msgImg.fromId =dataimg.fromId;
		msgImg.isBurn = (dataimg.activeType == 0x01);
		msgImg.lastMsgId = dataimg.lastMsgId;
		msgImg.localId = dataimg.msgId;
		msgImg.msgId = dataimg.msgId;
		msgImg.targetId = dataimg.targetId;
		msgImg.time = dataimg.time;
		msgImg.toId = dataimg.toId;
		msgImg.isRecvMsg = dataimg.fromId !=m_account.id.value()?true:false;
		msgImg.isGroup   = IS_MSG_GROUP(dataimg.targetId);
		msgImg.isUser    = IS_MSG_USER(dataimg.targetId);
		msgImg.userId    = m_account.id.value();
		msgImg.isDeviceMsg = (dataimg.fromId==m_account.id.value() && 2==dataimg.deviceType)?true:false;

		return msgImg;
	}

	model::MsgSearchProperty ChatMgrControl::DataConvert(data::MsgSearchProperty msg)
	{
		model::MsgSearchProperty modelmsg;
		modelmsg.msgtype = msg.msgtype;
		modelmsg.targetid = msg.targetid;
		modelmsg.count = msg.count;
		modelmsg.start_time = msg.start_time;
		modelmsg.end_time = msg.end_time;
		return modelmsg;
	}

	data::MsgSearchResult ChatMgrControl::DataConvert(model::MsgSearchResult modelmsg)
	{
		data::MsgSearchResult msg;
		msg.nextTargetId = modelmsg.nextTargetId;
		for(int i=0; i<modelmsg.infos.size(); i++)
		{
			data::MsgSearchResult::info Tinfo;
			Tinfo.count = modelmsg.infos.at(i).count;
			Tinfo.targetId = modelmsg.infos.at(i).targetId;
			Tinfo.simpleInfo.name = modelmsg.infos.at(i).simpleInfo.name;
			Tinfo.simpleInfo.flag = modelmsg.infos.at(i).simpleInfo.flag;
			Tinfo.simpleInfo.avatarUrl = modelmsg.infos.at(i).simpleInfo.avatarUrl;
			Tinfo.simpleInfo.avatar = modelmsg.infos.at(i).simpleInfo.avatar;
			if (Tinfo.simpleInfo.avatar.empty()) {
				if (isUser(Tinfo.targetId)) {
					Tinfo.simpleInfo.avatar = ":/base/default_head";
				}
				else if (isGroup(Tinfo.targetId)) {
					Tinfo.simpleInfo.avatar = ":/base/group_head";
				}
				else {
					Tinfo.simpleInfo.avatar = ":/base/app_default";
				}
			}
			msg.infos.push_back(Tinfo);
		}

		return msg;
	}

	data::MsgDetailSearchResult ChatMgrControl::DataConvert(model::MsgDetailSearchResult modelmsg)
	{
		data::MsgDetailSearchResult DetailMsg;
		DetailMsg.nextMsgId = modelmsg.nextMsgId;
		for(int i=0;i<modelmsg.msgs.size(); i++)
		{
			CSharedPtr<data::Msg> msg = CMakePtr<data::Msg>();
			msg = DataConvert(modelmsg.msgs.at(i));
			DetailMsg.msgs.push_back(msg);
		}
		return DetailMsg;
	}

	std::vector<CSharedPtr<model::Msg>> ChatMgrControl::DataListConvert(std::vector<CSharedPtr<data::Msg>>&msglist)
	{
		std::vector<CSharedPtr<model::Msg>>msglist_res;

		for (size_t index=0; index<msglist.size(); ++index)
		{
			CSharedPtr<data::Msg> msg = msglist.at(index);
			CSharedPtr<model::Msg> modelmsg = CMakePtr<model::Msg>();

				modelmsg->isPrivateMsg = msg->isPrivateMsg;
				modelmsg->isFeather = msg->isFeather;
				modelmsg->relatedUsers = msg->relatedUsers;
				modelmsg->deviceType = msg->deviceType;
				modelmsg->fromId =msg->fromId;
				//modelmsg->isBurn = (msg->activeType == 0x01);
				modelmsg->lastMsgId = msg->lastMsgId;
				modelmsg->localId = msg->msgId;
				modelmsg->msgId = msg->msgId;
				modelmsg->targetId = msg->targetId;
				modelmsg->time = msg->time;
				modelmsg->toId = msg->toId;
				modelmsg->relatedMsgId = msg->relatedMsgId;
				/*modelmsg->isRecvMsg = msg->fromId !=m_account.id.value()?true:false;
				modelmsg->isGroup   = IS_MSG_GROUP(msg->targetId);
				modelmsg->isUser    = IS_MSG_USER(msg->targetId);
				modelmsg->userId    = m_account.id.value();
				modelmsg->isDeviceMsg = (msg->fromId==m_account.id.value() && 2==msg->deviceType)?true:false;*/
				msglist_res.push_back(modelmsg);
		}
		return msglist_res;
	}

	CSharedPtr<data::Msg>  ChatMgrControl::ConvertNineBlockMsg( CSharedPtr<model::Msg> &msg )
	{
		model::MsgNineBlock* msgMine = (model::MsgNineBlock*)msg.get();
		CSharedPtr<data::MsgNineBlock> msgData = CMakePtr<data::MsgNineBlock>();
		msgData->validity = msgMine->validity;
		for (int i=0;i<msgMine->nine.size();++i)
		{
			msgData->nine.push_back(DataConvert(msgMine->nine.at(i)));
		}
		static CSharedPtr<data::Msg> msgBase = CNull;
		msgBase = msgData;
		msgBase->isPrivateMsg = msg->isPrivateMsg;
		msgBase->relatedUsers = msg->relatedUsers;
		msgBase->deviceType = msg->deviceType;
		msgBase->fromId =msg->fromId;
		msgBase->isBurn = (msg->activeType == 0x01);
		msgBase->lastMsgId = msg->lastMsgId;
		msgBase->localId = msg->msgId;
		msgBase->msgId = msg->msgId;
		msgBase->targetId = msg->targetId;
		msgBase->time = msg->time;
		msgBase->toId = msg->toId;
		msgBase->isRecvMsg = msg->fromId !=m_account.id.value()?true:false;
		msgBase->isGroup   = IS_MSG_GROUP(msg->targetId);
		msgBase->isUser    = IS_MSG_USER(msg->targetId);
		msgBase->userId    = m_account.id.value();
		msgBase->isDeviceMsg = (msg->fromId==m_account.id.value() && 2==msg->deviceType)?true:false;
		return msgBase;
	}

	void ChatMgrControl::updateMsg(std::vector<CSharedPtr<data::Msg>> &msgs)
	{
		std::vector<MsgPtr> Dmsgs = DataListConvert(msgs);
		m_chatservice->updateMsg(Dmsgs, std::bind(&ChatMgrControl::OnRemoveChat,this, std::placeholders::_1));
	}

	void ChatMgrControl::updateMsg(CSharedPtr<data::Msg> &msg)
	{
		CSharedPtr<model::Msg> modelmsg = DataConvert(msg);
		m_chatservice->updateMsg(*modelmsg.get(), std::bind(&ChatMgrControl::OnRemoveChat,this, std::placeholders::_1));
	}
	/**
	* \brief 全局查找消息
	* @param[in] key	   传入查找关键字
	* @param[in] msgProperty  传入查找的附加属性
	* @param[in] cb     传入接收结果回调  _1错误信息  _2消息搜索结果集合
	*/
	void ChatMgrControl::searchMessage(const std::string &key, data::MsgSearchProperty &msgProperty,CFunction<void(int, data::MsgSearchResult&)> cb)
	{
		BEGIN;
			if(m_searchservice)
			{
				m_messageserchcb = cb;
				MsgSearchProperty modelmsg = DataConvert(msgProperty);
				m_searchservice->searchMessage(key, modelmsg, std::bind(&ChatMgrControl::onSerMsgGlogalSerch,this, std::placeholders::_1, std::placeholders::_2));
			}
		END;
	}

	void ChatMgrControl::onSerMsgGlogalSerch(int code, model::MsgSearchResult& SerchResMsg)
	{
		if(m_messageserchcb)
		{
			data::MsgSearchResult msg = DataConvert(SerchResMsg);
			m_messageserchcb(code, msg);
		}	
	}

	void ChatMgrControl::searchDetailMessage(const std::string &key, data::MsgDetailSearchProperty &msgDetailProperty,CFunction<void(int, data::MsgDetailSearchResult&)> cb)
	{
		if(m_searchservice)
		{
			m_msgdetailserchcb = cb;
			model::MsgDetailSearchProperty moddetailmsg;
			moddetailmsg.msgtype = msgDetailProperty.msgtype;
			moddetailmsg.targetid = msgDetailProperty.targetid;
			moddetailmsg.start_time = msgDetailProperty.start_time;
			moddetailmsg.end_time = msgDetailProperty.end_time;
			moddetailmsg.count = msgDetailProperty.count;
			moddetailmsg.messageId = msgDetailProperty.messageId;
			m_searchservice->searchDetailMessage(key, moddetailmsg, std::bind(&ChatMgrControl::onSerMsgDetailSerch, this, std::placeholders::_1, std::placeholders::_2));
		}	
	}

	void ChatMgrControl::onSerMsgDetailSerch(int code, model::MsgDetailSearchResult& detailmsg)
	{
		if(m_msgdetailserchcb)
		{
			data::MsgDetailSearchResult msg = DataConvert(detailmsg);
			m_msgdetailserchcb(code, msg);
		}
	}

	int64 ChatMgrControl::uploadFile(data::UploadFileProperty &fileProperty, CFunction<void(int, int64, const std::string&)> cb, CFunction<void(int32, int32, const std::string&)> pro /*= SNull*/)
	{
		if (m_fileservice)
		{
			if (m_fileservice)
			{
				model::UploadFileProperty fileinfo;
				fileinfo.localid = fileProperty.localid;
				fileinfo.dirPath = fileProperty.dirPath;
				fileinfo.encryptKey = m_encrptkey.get_key();
				fileinfo.isP2p = fileProperty.isP2p;
				fileinfo.localPath = fileProperty.localPath;
				fileinfo.msg = fileProperty.msg;
				fileinfo.targetid = fileProperty.targetid;
				fileinfo.type = fileProperty.type;
				fileinfo.isJS = fileProperty.isJS;
				fileinfo.isResume = fileProperty.isResume;
				fileinfo.noStore = fileProperty.noStore;

				m_pFileUpResultCb[fileProperty.localid] = cb;
				m_pFileUpProgressCb[fileProperty.localid] = pro;
				fileProperty.encryptKey = fileinfo.encryptKey;
				m_fileInfoMap[fileProperty.localid] = fileProperty;
				return m_fileservice->uploadFile(fileinfo,
					std::bind(&ChatMgrControl::onSerUpFileResult, this, std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3,
					fileProperty.localid),
					std::bind(&ChatMgrControl::onSerUpfileProgress, this, std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3, fileProperty.localid));
			}
		}
	}

	void ChatMgrControl::onSerUpFileResult(int error, int64 targetid, const std::string& pjson, int64 localid)
	{
		if (error == 0)
		{
			if (m_pFileUpResultCb[localid])
			{
				m_pFileUpResultCb[localid](error, targetid, pjson);
				onSerSendMessage(pjson, localid);
				m_pFileUpResultCb.erase(localid);
			}
		}
		else
		{
			m_pFileUpResultCb[localid](error, targetid, pjson);
			m_pFileUpResultCb.erase(localid);
		}
	}

	void ChatMgrControl::onSerUpfileProgress(int32 extra_req, int32 progress, const std::string& result, int64 localid)
	{
		if (m_pFileUpProgressCb[localid])
		{
			m_pFileUpProgressCb[localid](extra_req, progress, result);
			if (progress == 100)
			{
				std::string pjson = m_jsonMap[localid];
				/*onSerSendMessage(pjson,localid);
				m_jsonMap.erase(localid);*/
				m_pFileUpProgressCb.erase(localid);
			}
		}
	}

	void ChatMgrControl::onSerSendMessage(std::string fjson, int64 filelocalid)
	{
		//std::map<int64, data::UploadFileProperty>::iterator iter = m_fileInfoMap.begin();
		if (m_fileInfoMap.find(filelocalid) == m_fileInfoMap.end())
		{
			return;
		}
		data::UploadFileProperty  fileinfo = m_fileInfoMap[filelocalid];

		CSharedPtr<data::Msg> msgptr = CNull;
		CSharedPtr<data::MsgFile> filemsg = CMakePtr<data::MsgFile>();
		filemsg->encryptKey = fileinfo.encryptKey;
		filemsg->filePath = fileinfo.localPath;
		filemsg->fileName = fileinfo.filename;
		filemsg->targetId = fileinfo.targetid;
		filemsg->url = Getvalue(fjson);
		filemsg->size = fileinfo.filesize;
		msgptr = filemsg;

		msgptr->status = 1;
		msgptr->isGroup = true;
		msgptr->isPrivateMsg = 0;
		msgptr->fromId = m_account.id.value();


		CSharedPtr<model::Msg> msg = DataConvert(msgptr);
		model::MsgFile* tempmsg = (model::MsgFile*)msg.get();
		tempmsg->encryptKey = fileinfo.encryptKey;

		model::Msg* sendmsg = tempmsg;
		int64 msglocalid = m_chatservice->sendMessage(
			*sendmsg,
			CBind(&ChatMgrControl::onSerSendMessageCb,
			this,
			CPlaceholders  _1,
			CPlaceholders  _2,
			CPlaceholders  _3,
			CPlaceholders  _4,
			sendmsg->msgType,
			sendmsg->targetId,
			sendmsg->localId,
			msg));

		m_fileInfoMap.erase(filelocalid);
	}

	void ChatMgrControl::onSerSendMessageCb(int err, int64 time, int64 msgid, model::BadWord&bad, int msgtype, int64 tagetid, int64 localid, CSharedPtr<model::Msg>& msg)
	{
		msg->msgId = msgid;
		OnRecvMsgNotice(msg);
	}

	void ChatMgrControl::getGroupMsgUnreadInfo(int64 groupId, data::SnapshotInfo &info, CFunction<void(int, std::vector<int64>&, std::vector<int64>&)> cb)
	{
		model::SnapshotInfo out;
		out.msgId = info.msgId;
		out.snapshotId = info.snapshotId;
		if (m_chatservice)
		{
			m_chatservice->getGroupMsgUnreadInfo(groupId, out, cb);
		}
	}

	void ChatMgrControl::getGroupMsgReadState(int64 targetId, int64 msgId, GetGroupMsgReadStateCb cb)
	{
		if (m_chatservice) {
			m_chatservice->getGroupMsgReadState(targetId, msgId, 
				CBind(&ChatMgrControl::onGetGroupMsgReadState,this,CPlaceholders _1,
					CPlaceholders _2,cb));
		}
	}

	void ChatMgrControl::onGetGroupMsgReadState(service::ErrorInfo code, std::map<std::string, std::vector<int64> >&states, GetGroupMsgReadStateCb& cb)
	{
		std::vector<int64> reads;
		std::vector<int64> unreads;
		std::vector<int64> unPushCounts;
		std::map<std::string, std::vector<int64>>::iterator iter = states.begin();
		while (iter != states.end()) {
			std::string key = iter->first;
			if (key == "readCount") {
				reads = iter->second;
			}
			else if(key == "unReadCount"){
				unreads = iter->second;
			}
			else if(key == "unPushCount"){
				unPushCounts = iter->second;
			}
			iter++;
		}
		for (int i = 0; i < unPushCounts.size(); ++i) {
			unreads.push_back(unPushCounts.at(i));
		}
		cb(code, reads, unreads);

	}

	void ChatMgrControl::getGroupMsgUnreadCounter(int64 groupId, std::vector<data::SnapshotInfo> &infos, CFunction<void(int, std::vector<data::MsgUnreadCounter>&)> cb)
	{
		std::vector<model::SnapshotInfo>snaps;
		for (int i = 0; i < infos.size(); ++i)
		{
			data::SnapshotInfo info = infos.at(i);
			model::SnapshotInfo snap;
			snap.msgId = info.msgId;
			snap.snapshotId = info.snapshotId;
			snaps.push_back(snap);
		}
		if (m_chatservice)
		{
			m_chatservice->getGroupMsgUnreadCounter(groupId, snaps, CBind(&ChatMgrControl::onGetGroupMsgUnreadCounter, this, CPlaceholders _1, CPlaceholders _2, cb));
		}
	}

	void ChatMgrControl::onGetGroupMsgUnreadCounter(service::ErrorInfo err, std::vector<model::MsgUnreadCounter>&list, GetGroupMsgUnreadCounterPtr&cb)
	{
		std::vector<data::MsgUnreadCounter>snaps;
		for (int i = 0; i < list.size(); ++i)
		{
			model::MsgUnreadCounter info = list.at(i);
			data::MsgUnreadCounter snap;
			snap.maxUnreadCount = info.maxUnreadCount;
			snap.messageId = info.messageId;
			snap.snapshotId = info.snapshotId;
			snap.unreadCount = info.unreadCount;
			snaps.push_back(snap);
		}
		if (cb) {
			cb(err, snaps);
		}

	}

	void ChatMgrControl::getContractMaxReadId(int64 targetId, CFunction<void(int, int64)> cb)
	{
		if (m_chatservice)
		{
			m_chatservice->getContractMaxReadId(targetId, cb);
		}
	}
	std::string ChatMgrControl::parceEmojiDeal(const std::string msg)
	{
		//return ParseJsonData::emojideal(msg);
		return ParseJsonData::emojisenddeal(msg);
	}
	std::string ChatMgrControl::Getvalue(std::string fjson)
	{

		std::string  strurl = "";
		Json::Reader reader;
		Json::Value root, fieldsarry, mJvalue;
		int ret = reader.parse(fjson, root);

		if (!ret)
			return "";
		if (root["files"].isArray())
		{
			int count = root["files"].size();
			for (int i = 0; i<count; i++)
			{
				mJvalue = root["files"][i];
				if (mJvalue["url"].isString())
				{
					strurl = mJvalue["url"].asString();
				}
			}
		}
		return strurl;
	}

	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance(){
	BEGIN;
		IControl* instance = NULL;
		instance = new ChatMgrControl();
	END;
		return  instance;
	}
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance){
	BEGIN;
		if(NULL != instance){
			delete instance;
			instance = NULL;
		}
	END;
	}
}