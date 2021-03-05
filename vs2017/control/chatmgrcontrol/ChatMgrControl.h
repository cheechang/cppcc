#pragma once
#include <IChatMgrControl.h>
#include "ServiceDefine.h"
#include "EncryptKey.h"
#include <map>
namespace service{
	class IMClient;
}
namespace data{
	class MsgFile;
	class MsgImg;
}
namespace control{
	class ChatMgrControl:public IChatMgrControl{
	public:
		ChatMgrControl(const std::string &strName=std::string("chatmgrcontrol"));
		virtual ~ChatMgrControl();
		typedef CFunction<void(int, data::UserData&)> GetUserInfoCallBackPtr;
		typedef CFunction< void(int, std::vector<CSharedPtr<data::ChatData>>&)>CallBackPtr;
		typedef CFunction< void(CSharedPtr<data::Msg>)>MsgCallBackPtr;
		typedef CFunction<void(int,int64,std::vector<CSharedPtr<data::Msg>>&)>GetMessageCallBackPtr;
		typedef CFunction<void(int,int64,int64)> SendMsgCallBackPtr;
		typedef CFunction<void(CSharedPtr<data::MsgStatus>)> MsgStatusCallBackPtr;
		typedef CFunction<void(int64, int32, int32, const std::string&)> DownloadCallBackPtr;
		typedef CFunction<void(int64, int32, int32, const std::string&)> ProgressPtr;
		typedef CFunction<void(int, std::map<int64,data::MsgImg>)> GetImgMsgPtr;
		typedef CFunction<void(int,int64,int64)> ForwardmsgPtr;
		typedef CFunction<void(int, int64, int8)> GetUserNoDisturbModePtr;
		typedef CFunction<void(int, int64, std::vector<CSharedPtr<data::Msg>>&)> DecryptmsgPtr;
		typedef CFunction<void(int, data::MsgSearchResult&)> MessageGlobalSerchCallBackPtr;
		typedef CFunction<void(int, data::MsgDetailSearchResult&)> MessageDetailSerchCallBackPtr;
		typedef CFunction<void(int, std::vector<data::MsgUnreadCounter>&)> GetGroupMsgUnreadCounterPtr;
		typedef CFunction<void(int32, int32, const std::string&)> FileUpProgressCallBackPtr;
		typedef CFunction<void(int, int64, const std::string&)> FileUpResultCallBackPtr;
		typedef CFunction<void(int, std::vector<int64>&, std::vector<int64>&)>  GetGroupMsgReadStateCb;
	public:
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

		/*********************************************************************************************************
		* brief �����Ự�б����֪ͨ
		* @param[in] cb _1 �����б��־ _2 ����Ự����
		* ȫ������:
		*	0x01����һ����,���� ��Ҫ����ԭ��������
		*	0x02  �м�İ���������ԭ�������ݺ���׷��
		*	0x04  ���İ�����������Ự�������
		* ���ָ���:
		*   0x08  ����
		*	0x10  ����
		*	0x20  ɾ��
		* ȫ��ɾ��
		*   0x40 ɾ�����������ϵ��
		************************************************************************************************************/
		virtual void RegChatListNotify(CFunction< void(int, std::vector<CSharedPtr<data::ChatData>>&)> cb);


		/*********************************************************************************************************
		* @brief ��ȡ����Ự�б�ӿ�
		* @param[out] chatlist �����Ự�б�
		************************************************************************************************************/
		virtual void GetChatList(std::vector<CSharedPtr<data::ChatData> > &chatlist);

		/**********************************************************************************************************
		*brief ��������ػ�ͷ���������
		*@param[out] cb _1 ����Ŀ��ID���˻���Ⱥ  _2 ����ͷ��
		**********************************************************************************************************/
		virtual void RegChatListHeadUpdate(CFunction < void(int64, const std::string&)> cb);

		/**********************************************************************************************************
		*brief ���ü�����������Ϣ�Ļص�
		*@param[in] cb _1 ��Ϣ�ṹ������ָ��
		**********************************************************************************************************/
		virtual void RegRecvMsgNotice(CFunction< void(CSharedPtr<data::Msg>)>cb);   

		/**********************************************************************************************************
		*brief ���ü���ͼƬ��Ϣ��������
		*@param[in] cb _1 ��Ϣ�ṹ������ָ��
		**********************************************************************************************************/
		virtual void RegImgMsgNotice(CFunction< void(CSharedPtr<data::Msg>)> cb);

		/**********************************************************************************************************
		*brief ���ü�����Ϣ����״̬��������
		*@param[out] err ����ֵ  localid����Ψһ��ʾ��  time��Ϣʱ��  targetidĿ��id externdͼƬ��Ϣ���� 
		**********************************************************************************************************/
		virtual void RegMsgStatusNotice(CFunction< void(CSharedPtr<data::MsgStatus>)>cb);

		/**********************************************************************************************************
		*brief ���ý��ȼ����ص�
		*@param[out] _1 ���ȶ�Ӧ���ļ���localId _2 ���ȱ�ʾ _3���� _4�ļ���ǰ�����С/�ļ��ܴ�С
		**********************************************************************************************************/
		virtual void RegProcessCb(int64 localid,CFunction<void(int64, int32, int32, const std::string&)> cb);

		/*********************************************************************************************************
		* @brief ��ȡ��Ϣ
		* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������
		* @param[in] msgid �����ѯ��Ϣ����ʼID�����Ӹ���Ϣ����һ����Ϣ��ʼ��ѯ
		* @param[in] count �����ѯ��Ϣ����
		* @param[in] flag  ������һҳ������һҳ ����ƫ�� 0������ƫ�� 1
		*                  ���msgBeginID������ʶ����Ϣ�Ƿ���ʧ�ܵ���Ϣ�������0xF0�����ݵ�SDK��
						   ����Ӵ�Сƫ�ƣ�����msgBeginID��ʶ����Ϣ�Ƿ���ʧ�ܵ���Ϣ��
						   �� offsetFlag = 0 | 0xF0.
		* @param[out] cb  ������ս���ص� _1 ������Ϣ _2�ỰID�� _3��Ϣ����
		************************************************************************************************************/
	    virtual void GetMessages(int64 targetId, int64 msgId, int count, int flag, CFunction<void(int,int64,std::vector<CSharedPtr<data::Msg>>&)>cb);

		/***************************************************************************************
		* @brief ������Ϣ������localid
		* @param[in] msg ������Ϣ
		* @param[out] cb  �������SendMessage����ص� _1 ������Ϣ _2 ����ʱ�� _3��ϢID
		****************************************************************************************/
		virtual int64 SendMessage(CSharedPtr<data::Msg>&msg,CFunction<void(int,int64,int64)>cb);

		/*************************************************************************************************
		* @brief ������Ϣ�Ѷ�
		* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������
		* @param[in] msgId ��Ҫ���õ���ϢID ��������Ϊ100, ��100С��������Ϣ��Ϊ�Ѷ�
		***************************************************************************************************/
		virtual void setMessageRead(int64 targetId, int64 msgId);

		/************************************************************************************************************************
		* @brief �Ƴ��Ự
		* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������ 0Ϊɾ��ȫ����ϵ��
		***************************************************************************************************************************/
		virtual void RemoveChat(int64 targetId);

		/************************************************************************************************************************
		* brief ����ͼƬ�ӿ�
		* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������ 0Ϊɾ��ȫ����ϵ��
		* @param[out] err ����ֵ imgNameͼƬ����Ҫ+USERIMAGE  tarid �Է�id
		***************************************************************************************************************************/
		virtual void DownLoadImage(int64 targetid,std::string&url,CFunction<void(int err,const std::string&imgName,int64 tarid)>cb);

		
		/************************************************************************************************************************
		* brief �����ļ��ӿ�
		* @param[in] download ���������ļ�������Ϣ
		* @param[out] ������ս���ص� _1������Ϣ  _2���ճɹ����ļ�·�� localPath _3������ID
		***************************************************************************************************************************/
		virtual void DownLoadFile(CSharedPtr<data::DownLoadFile>&download, CFunction<void(int err,const std::string&fileName, int64 targetId)>cb,
								CFunction<void(int32, int32, const std::string&)> pro = CNull);

		/*********************************************************************************************************************
		* brief �����ļ�
		* @param[in] encryptkey �����������
		* @param[in] srcpath ����ԭͼ·��
		* @param[in] destpath ������ܺ�ͼƬ·��
		********************************************************************************************************************/
		virtual bool decryptFile(const std::string &encryptkey, const std::string &srcpath, const std::string &destpath);

		/**
		* \brief ͨ���û�ID��ȡ��ϸ��Ϣ
		* @param[in] userid �����û�ID
		* @param[in] cb ������ս���ص�  _1������Ϣ  _2�û���Ϣ
		*/
		virtual void getUserInfo(int64 userid, int64 msgid,CFunction<void(int, data::UserData&)> cb);

		/**
		* \brief <U>��ȡ���û�������cache
		* @return   �û�������cache
		*/
		virtual std::string userCachePath();

		/**
		* \brief <U>��ȡ���û���������Ƶ��Ϣ�ı���·��
		* @return   ��Ƶ��Ϣ�ı���·��
		*/
		virtual std::string userAudioPath();

		/**
		* \brief ��ȡͼƬ��Ϣ
		* @param[in] targetid ���˻�ȺID
		* @param[in] cb  ������ս���ص� _1 ������Ϣ  _2��Ϣ����
		*/
		virtual void getImgMsg(int64 targetId, CFunction<void(int, std::map<int64,data::MsgImg>)> cb);

		/**
		* \brief ת����Ϣ
		* @param[in] fromTaregetId ת������Ϣ�ĵ�ǰtargetId
		* @param[in] toTargetId ת������Ϣ�Ľ���targetId
		* @param[in] messageId ת������ϢID
		* @param[out] cb  _1  ������ս���ص� _1 ������Ϣ _2 ����ʱ�� _3��ϢID _4���д�
		*/
		virtual void forwardMessage(int64 fromTargetId, int64 toTargetId, int64 messageId, CFunction<void(int,int64,int64)> cb);

		/**
		* \brief ��ȡURL����ϸ��Ϣ
		* @param[in] url  ��ַ
		* @param[in] cb  ������ս���ص� _1 ������Ϣ  _2��ַ  _3����  _4ͼƬ�ĵ�ַ  _5ժҪ
		*/
		virtual void getUrlInfo(const std::string &url, std::string& loginfoPath, CFunction<void(int, const std::string&, const std::string&, const std::string&, const std::string&)> cb);
	
		/**
		* \brief ͨ��msgIdɾ����Ϣ
		* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������
		* @param[in] msgs ����Ҫɾ������ϢID���� msgsΪ�գ���ն�ӦtargetId��������Ϣ
		* @param[in] cb  ����ص� _1������Ϣ
		*/
		virtual void deleteMessageById(int64 targetId, std::vector<int64> &msgIds, CFunction<void(int)> cb);

   /**
	* \brief ɾ��������Ϣ
	* @param[in] clearChatList �Ƿ������ϵ���б�
	* @param[in] cb  ����ص� _1������Ϣ
	*/
	virtual void deleteAllMessage(bool clearChatList, CFunction<void(int)> cb);


		/**
		* \brief ɾ��ʱ�����Ϣ
		* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������ targetIdΪ0������������û�
		* @param[in] beginTime ��ʼʱ��
		* @param[in] endTime ����ʱ��
		* @param[in] cb  ����ص� _1������Ϣ
		*/
		virtual void deleteMessageByTime(int64 targetId, int64 beginTime, int64 endTime, CFunction<void(int)> cb);
		
		/**
		* \brief �ö��Ự
		* @param[in] targetid �ö���Ŀ��ID
		* @param[in] isTop  �Ƿ��ö� 
		* @param[in] cb  ������ս���ص� _1 ������Ϣ 
		*/
		virtual void chatTop(int64 targetId, bool isTop, CFunction<void(int)> cb);

		/**
		* \brief �������Ŀ���û�������ģʽ
		* @param[in] targetId  �û�ID
		* @param[in] value ���õ�ֵ:  1Ϊ�������� 2��ʾ�����ѽ���ʾ���� 3:Ϊ�����, Ĭ��1
		* @param[out] cb ������ս���ص�  _1������Ϣ
		*/
		virtual void setUserNoDisturbMode(int64 targetId, int value, CFunction<void(int)> cb);

		/**
		* \brief ��ȡ���Ŀ���û�������ģʽ
		* @param[in] targetId  �û�ID
		* @param[out] cb ������ս���ص�  _1������Ϣ  _2�û�ID  _3���õ�ֵ:  1Ϊ�������� 2��ʾ�����ѽ���ʾ���� 3:Ϊ�����
		*/
		virtual void getUserNoDisturbMode(int64 targetId, CFunction<void(int, int64, int8)> cb);


		/*brief ����˽����Կ
		* @param[in] targetId Ŀ��ID�����˻�Ⱥ
		* @param[in] passwd  ˽����Կ  Ϊ�մ������˽������.
		* @param[in] cb  ������ս���ص� _1 ������Ϣ 
		*/
		virtual void setPrivateKey(int64 targetId, const std::string &passwd);
		
		/**
		* \brief ͨ����ϢID������Ϣ
		* @param[in] targetId Ŀ��ID�����˻�Ⱥ
		* @param[in] msgIds  Ҫ���ܵ���ϢID����
		* @param[in] cb  ������ս���ص� _1 ������Ϣ _2 ������Ϣ��targetId _3�ѽ��ܵ���Ϣ
		*/
		virtual void decryptMsg(int64 targetId, std::vector<int64> &msgIds, CFunction<void(int, int64, std::vector<CSharedPtr<data::Msg>>&)> cb);

		/**
		* \brief ���¶�ӦtargetId����Ϣ��ֻ�ܸ�����Ϣ���property
		* @param[in] targetId Ŀ��ID�����˻�Ⱥ
		* @param[in] msgs  Ҫ���µ���Ϣ����
		* @param[in] cb  ������ս���ص� _1 ������Ϣ
		*/
		virtual void updateMsg(std::vector<CSharedPtr<data::Msg>> &msgs);
		virtual void updateMsg(CSharedPtr<data::Msg> &msg);

		/**
		* \brief ȫ�ֲ�����Ϣ
		* @param[in] key	   ������ҹؼ���
		* @param[in] msgProperty  ������ҵĸ�������
		* @param[in] cb     ������ս���ص�  _1������Ϣ  _2��Ϣ�����������
		*/
		virtual void searchMessage(const std::string &key, data::MsgSearchProperty &msgProperty,CFunction<void(int, data::MsgSearchResult&)> cb);
	
		/**
		* \brief ������ӦtargetID����ϸ��Ϣ
		* @param[in] key	   ������ҹؼ���
		* @param[in] msgDetailProperty  ������ҵĸ�������
		* @param[in] cb     ������ս���ص�  _1������Ϣ  _2��Ϣ�����������
		*/
		virtual void searchDetailMessage(const std::string &key, data::MsgDetailSearchProperty &msgDetailProperty,CFunction<void(int, data::MsgDetailSearchResult&)> cb);
		
		/**
		* \brief �ϴ��ļ�  ///���ϵ��ϴ�,key����һ��
		* @param[in] targetId �˻�Ⱥ��id
		* @param[in] cb  ������ս���ص� _1������Ϣ _2Ŀ��Id _3���������ص�json
		* @param[in] pro  ���Ȼص� _1 extra_req  _2process
		* @return ÿ���ļ���Ӧ��ΨһlocalID
		*/
		virtual int64 uploadFile(data::UploadFileProperty &fileProperty, CFunction<void(int, int64, const std::string&)> cb,
			CFunction<void(int32, int32, const std::string&)> pro = SNull);

		virtual std::string parceEmojiDeal(const std::string msg);

		/**
		* \brief .��ȡһ����Ϣ��δ����������
		* @param[in] groupId  ȺID
		* @param[in] infos  ��Ϣid����id��Ϣ
		* @param[in] cb  ������ս���ص� _1 ������Ϣ _2��ʾ����������Ϣ��δ��״̬
		*/
		virtual void getGroupMsgUnreadCounter(int64 groupId, std::vector<data::SnapshotInfo> &infos, CFunction<void(int, std::vector<data::MsgUnreadCounter>&)> cb);

		/**
		* \brief .��ȡ��ϵ������Ѷ�ID
		* @param[in] targetId ��ϵ��ID
		* @param[in] cb  ������ս���ص� _1 ������Ϣ _2����Ѷ�ID
		*/
		virtual void getContractMaxReadId(int64 targetId, CFunction<void(int, int64)> cb);

		/**
		* \brief .ͳ����Ϣ�Ѷ���δ��������ϸ��Ϣ
		* @param[in] groupId  ȺID
		* @param[in] info  ��Ϣid����id��Ϣ
		* @param[in] cb  ������ս���ص� _1 ������Ϣ _2�Ѷ�userID�б� _3δ��userID�б�
		*/
		virtual void getGroupMsgUnreadInfo(int64 groupId, data::SnapshotInfo &info, CFunction<void(int, std::vector<int64>&, std::vector<int64>&)> cb);

		/**
		* \brief ��ȡȺ����Ϣ�Ķ�ȡ״̬
		* @param[in] targetId  Ŀ��targetId
		* @param[in] msgId  ��Ϣid
		* @param[in] cb  ������ս���ص� _1 ������Ϣ _2��ʾ���ض�Ӧ���͵���Ϣ���Ѷ���δ����δ����userID�б�
		*/
		virtual void getGroupMsgReadState(int64 targetId, int64 msgId, CFunction<void(int, std::vector<int64>&, std::vector<int64>&)> cb);
	protected:
		void onGetGroupMsgReadState(service::ErrorInfo code, std::map<std::string, std::vector<int64> >&states,GetGroupMsgReadStateCb& cb);
		void onSerMsgDetailSerch(int, model::MsgDetailSearchResult&);
		void onSerMsgGlogalSerch(int, model::MsgSearchResult&);
		void onGetSetPrivateKey(service::ErrorInfo pErrorCode);
		void onGetUserInfo(int code, model::User&user,int64 msgid);
		void OnChatListNotify(int flag,std::vector<CSharedPtr<model::Chat>>&chatlist);
		void OnRecvMsgNotice(CSharedPtr<model::Msg> msg);
		void OnGetMessagesCb(service::ErrorInfo err,int64 sessionid,std::vector<MsgPtr>&msglist);
		void OnSendMsgCb(int err,int64 time,int64 msgid,model::BadWord&bad,int,int64,int64);
		void OnRemoveChat(service::ErrorInfo err);
		void onDownLoadImage(service::ErrorInfo err,const std::string&localpath, int64 targetid,int64 localid,int docid, std::string encrptkey);
		void onProgressCb(int32 extra_req ,int32 process,const std::string& info,int64 localid);
		void onGetAppInfo(service::ErrorInfo err,model::EntAppinfo&appinfo,data::ChatData chatdata);
		void onGetAppInfoByID(service::ErrorInfo err,model::EntAppinfo&appinfo,int64 msgid);
		void onGetImgMsg(int64 targetId,service::ErrorInfo err,std::vector<model::MsgPtr>&msg);
		void onDownloadBigImages(std::map<int64,std::string>& needs,std::map<int64,data::MsgImg>&mapImgMsgs,service::ErrorInfo err, const std::string&localPath, int64 targetId);
		void onForwardMsg(int64 toTargetId,service::ErrorInfo code,int64 time,int64 msgId,model::BadWord&word);
		void OnGetMessageByMsgIdCb(service::ErrorInfo err,int64 sessionid,std::vector<MsgPtr>&msglist);
		void onGetGroupMsgRemindType(service::ErrorInfo code, int8 msgMindType,int64 targetId);
   		void onGetDecryptMsgCb(int Rcode, int64 DecryptMsgId, std::vector<MsgPtr>& DecryMsgList);
		void onGetGroupMsgUnreadCounter(service::ErrorInfo err, std::vector<model::MsgUnreadCounter>&list, GetGroupMsgUnreadCounterPtr&cb);
		
		void onSerUpFileResult(int, int64, const std::string&, int64);
		void onSerUpfileProgress(int32, int32, const std::string&, int64);
		void onSerSendMessage(std::string fjson, int64 filelocalid);
		std::string Getvalue(std::string fjson);
		void onSerSendMessageCb(int err, int64 time, int64 msgid, model::BadWord&bad, int msgtype, int64 tagetid, int64 localid, CSharedPtr<model::Msg>& msg);
		std::vector<CSharedPtr<model::Chat>> onFilterChatMsg(std::vector<CSharedPtr<model::Chat>>& chatlist);
protected:
	    void  DownLoadImage(int64 targetid,int64 localid,std::string&url,int& docid,std::string&encryptkey);
		void  IsSaveAsFile(CSharedPtr<data::MsgFile>&msg);
		std::map<std::string,std::string> ParseFields(std::string json);
	private:
		CSharedPtr<data::Msg> ConvertNineBlockMsg( CSharedPtr<model::Msg> &msg );
		data::ChatData DataConvert(model::Chat& data);
		CSharedPtr<model::Msg>DataConvert(CSharedPtr<data::Msg>&data);
		CSharedPtr<data::Msg>DataConvert(CSharedPtr<model::Msg>&data);
		data::MsgImg DataConvert(model::MsgImg&data);
		std::vector<CSharedPtr<data::ChatData>>DataListConvert(std::vector<CSharedPtr<model::Chat>>&chatlist);
		std::vector<CSharedPtr<data::Msg>>DataListConvert(std::vector<CSharedPtr<model::Msg>>&msglist);
		std::vector<CSharedPtr<model::Msg>>DataListConvert(std::vector<CSharedPtr<data::Msg>>&msglist);
		model::MsgSearchProperty DataConvert(data::MsgSearchProperty msg);
		data::MsgSearchResult DataConvert(model::MsgSearchResult);
		data::MsgDetailSearchResult DataConvert(model::MsgDetailSearchResult);
private:
		std::map<int64,GetUserInfoCallBackPtr> m_getuserinfocb;
		GetMessageCallBackPtr m_getmessagecb; //��ȡ��Ϣ����
		MsgCallBackPtr m_recvmsgcb;           //������Ϣ���ͻص�
		MsgCallBackPtr m_downloadimagecb;	  //ͼƬ��Ϣ����
		CallBackPtr    m_chatlistnotifycb;	  //�Ự�б����ͻص�
		MsgStatusCallBackPtr m_msgstauscb;
		MessageGlobalSerchCallBackPtr m_messageserchcb; // ��Ϣ��ѯȫ�ֲ�ѯ�ص�
		MessageDetailSerchCallBackPtr m_msgdetailserchcb; //��Ϣ��ϸ��Ϣ��ѯ�ص�
		std::string m_pluginname;			  //�������������׺�ģ�
		IChatService_Ptr m_chatservice;
		IFileService_Ptr m_fileservice;
		IConfigService_Ptr m_configservice;
		ISearchService_Ptr m_searchservice;
		IUserService_Ptr   m_userservice;
		IGroupService_Ptr  m_groupservice;
		IContactService_Ptr m_contactservice;
		EncryptKey m_encrptkey;
		model::Account m_account;
		std::map<int64,ProgressPtr> m_procbmap;
		std::map<int64,SendMsgCallBackPtr> m_sendmsgcbmap;
		GetImgMsgPtr m_ImgMsgcb;
		ForwardmsgPtr mForwardmsgCb;
		GetUserNoDisturbModePtr mGetUserNoDisturbModeCb;
		DecryptmsgPtr mDecryptmsgPtr;

		std::map<int64, FileUpProgressCallBackPtr> m_pFileUpProgressCb;
		std::map<int64, FileUpResultCallBackPtr> m_pFileUpResultCb;

		std::map<int64, data::UploadFileProperty> m_fileInfoMap;
		std::map<int64, std::string> m_jsonMap;
	};
}