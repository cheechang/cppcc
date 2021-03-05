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
	virtual void RegChatListNotify(CFunction< void(int, std::vector<CSharedPtr<data::ChatData>>&)> cb) = 0;


    /**********************************************************************************************************
	*brief ��������ػ�ͷ���������
	*@param[out] cb _1 ����Ŀ��ID���˻���Ⱥ  _2 ����ͷ��
	**********************************************************************************************************/
	virtual void RegChatListHeadUpdate(CFunction < void(int64, const std::string&)> cb) = 0;


	/**********************************************************************************************************
	*brief ���ü�����������Ϣ�Ļص�
	*@param[in] cb _1 ��Ϣ�ṹ������ָ��
	**********************************************************************************************************/
    virtual void RegRecvMsgNotice(CFunction< void(CSharedPtr<data::Msg>)> cb) = 0;    


	/**********************************************************************************************************
	*brief ���ü���ͼƬ��Ϣ��������
	*@param[in] cb _1 ��Ϣ�ṹ������ָ��
	**********************************************************************************************************/
	virtual void RegImgMsgNotice(CFunction< void(CSharedPtr<data::Msg>)> cb)=0;


	/**********************************************************************************************************
	*brief ���ü�����Ϣ����״̬��������
	*@param[out] err ����ֵ  localid����Ψһ��ʾ��  time��Ϣʱ��  targetidĿ��id externdͼƬ��Ϣ���� 
	**********************************************************************************************************/
	virtual void RegMsgStatusNotice(CFunction< void(CSharedPtr<data::MsgStatus>)>cb)=0;


	/**********************************************************************************************************
	*brief ���ý��ȼ����ص�
	*@param[out] _1 ���ȶ�Ӧ���ļ���localId _2 ���ȱ�ʾ _3���� _4�ļ���ǰ�����С/�ļ��ܴ�С
	**********************************************************************************************************/
	virtual void RegProcessCb(int64 localid,CFunction<void(int64, int32, int32, const std::string&)> cb)=0;


	/*********************************************************************************************************
	* @brief ��ȡ����Ự�б�ӿ�
	* @param[out] chatlist �����Ự�б�
	************************************************************************************************************/
	virtual void GetChatList(std::vector<CSharedPtr<data::ChatData> > &chatlist)=0;


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
	virtual void GetMessages(int64 targetId, int64 msgId, int count, int flag, CFunction<void(int,int64,std::vector<CSharedPtr<data::Msg>>&)> cb)=0;

	/***************************************************************************************
	* @brief ������Ϣ������localid
	* @param[in] msg ������Ϣ
	* @param[out] cb  ������ս���ص� _1 ������Ϣ _2 ����ʱ�� _3��ϢID
	****************************************************************************************/
	virtual int64 SendMessage(CSharedPtr<data::Msg>&msg,CFunction<void(int,int64,int64)>cb)=0;

	/**********************************************************************************************************************************
	* @brief ������Ϣ�Ѷ�
	* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������
	* @param[in] msgId ��Ҫ���õ���ϢID ��������Ϊ100, ��100С��������Ϣ��Ϊ�Ѷ�
	***********************************************************************************************************************************/
	virtual void setMessageRead(int64 targetId, int64 msgId) = 0;

     
    /************************************************************************************************************************
	* \brief �Ƴ��Ự
	* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������ 0Ϊɾ��ȫ����ϵ��
	***************************************************************************************************************************/
	virtual void RemoveChat(int64 targetId)=0;

	/************************************************************************************************************************
	* brief ����ͼƬ�ӿ�
	* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������ 0Ϊɾ��ȫ����ϵ��
	* @param[out] err ����ֵ imgNameͼƬ����Ҫ+USERIMAGE  tarid �Է�id
	***************************************************************************************************************************/
	virtual void DownLoadImage(int64 targetid,std::string&url,CFunction<void(int err,const std::string&imgName,int64 tarid)>cb)=0;


	/************************************************************************************************************************
	* brief �����ļ��ӿ�
	* @param[in] download ���������ļ�������Ϣ
	* @param[out] ������ս���ص� _1������Ϣ  _2���ճɹ����ļ�·�� localPath _3������ID
	***************************************************************************************************************************/
	virtual void DownLoadFile(CSharedPtr<data::DownLoadFile>&download, CFunction<void(int err,const std::string&fileName, int64 targetId)>cb,
							CFunction<void(int32, int32, const std::string&)> pro = CNull)=0;

	/**
	* \brief �����ļ�
	* @param[in] encryptkey �����������
	* @param[in] srcpath ����ԭͼ·��
	* @param[in] destpath ������ܺ�ͼƬ·��
	*/
	virtual bool decryptFile(const std::string &encryptkey, const std::string &srcpath, const std::string &destpath) = 0;

	/**
	* \brief ͨ���û�ID��ȡ��ϸ��Ϣ
	* @param[in] userid �����û�ID
	* @param[in] msgid ��Ϣid,û��ʱ��ֵ0
	* @param[in] cb ������ս���ص�  _1������Ϣ  _2�û���Ϣ
	*/
	virtual void getUserInfo(int64 userid, int64 msgid,CFunction<void(int, data::UserData&)> cb) = 0;

	/**
	* \brief <U>��ȡ���û�������cache
	* @return   �û�������cache
	*/
	virtual std::string userCachePath() = 0;

		/**
	* \brief <U>��ȡ���û���������Ƶ��Ϣ�ı���·��
	* @return   ��Ƶ��Ϣ�ı���·��
	*/
	virtual std::string userAudioPath() = 0;

	/**
	* \brief ��ȡͼƬ��Ϣ
	* @param[in] targetid ���˻�ȺID
	* @param[in] cb  ������ս���ص� _1 ������Ϣ  _2��Ϣ����
	*/
	virtual void getImgMsg(int64 targetId, CFunction<void(int, std::map<int64,data::MsgImg>)> cb) = 0;

	/**
	* \brief ת����Ϣ
	* @param[in] fromTaregetId ת������Ϣ�ĵ�ǰtargetId
	* @param[in] toTargetId ת������Ϣ�Ľ���targetId
	* @param[in] messageId ת������ϢID
	* @param[out] cb  _1  ������ս���ص� _1 ������Ϣ _2 ����ʱ�� _3��ϢID _4���д�
	*/
	virtual void forwardMessage(int64 fromTargetId, int64 toTargetId, int64 messageId, CFunction<void(int,int64,int64)> cb) = 0;

	/**
	* \brief ��ȡURL����ϸ��Ϣ
	* @param[in] url  ��ַ
	* @param[in] cb  ������ս���ص� _1 ������Ϣ  _2��ַ  _3����  _4ͼƬ�ĵ�ַ  _5ժҪ
	*/
	virtual void getUrlInfo(const std::string &url, std::string& loginfoPath, CFunction<void(int, const std::string&, const std::string&, const std::string&, const std::string&)> cb) = 0;

	/**
	* \brief ͨ��msgIdɾ����Ϣ
	* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������
	* @param[in] msgs ����Ҫɾ������ϢID���� msgsΪ�գ���ն�ӦtargetId��������Ϣ
	* @param[in] cb  ����ص� _1������Ϣ
	*/
	virtual void deleteMessageById(int64 targetId, std::vector<int64> &msgIds, CFunction<void(int)> cb) = 0;
    /**
	* \brief ɾ��������Ϣ
	* @param[in] clearChatList �Ƿ������ϵ���б�
	* @param[in] cb  ����ص� _1������Ϣ
	*/
	virtual void deleteAllMessage(bool clearChatList, CFunction<void(int)> cb) = 0;

	/**
	* \brief ɾ��ʱ�����Ϣ
	* @param[in] targetid ����Ự��Ӧ��ID��Ⱥ������ targetIdΪ0������������û�
	* @param[in] beginTime ��ʼʱ��
	* @param[in] endTime ����ʱ��
	* @param[in] cb  ����ص� _1������Ϣ
	*/
	virtual void deleteMessageByTime(int64 targetId, int64 beginTime, int64 endTime,CFunction<void(int)> cb) = 0;

	/**
	* \brief �ö��Ự
	* @param[in] targetid �ö���Ŀ��ID
	* @param[in] isTop  �Ƿ��ö� 
	* @param[in] cb  ������ս���ص� _1 ������Ϣ 
	*/
	virtual void chatTop(int64 targetId, bool isTop, CFunction<void(int)> cb) = 0;

	/**
	* \brief �������Ŀ���û�������ģʽ
	* @param[in] targetId  �û�ID
	* @param[in] value ���õ�ֵ:  1Ϊ�������� 2��ʾ�����ѽ���ʾ���� 3:Ϊ�����, Ĭ��1
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void setUserNoDisturbMode(int64 targetId, int value, CFunction<void(int)> cb) = 0;

	/**
	* \brief ��ȡ���Ŀ���û�������ģʽ
	* @param[in] targetId  �û�ID
	* @param[out] cb ������ս���ص�  _1������Ϣ  _2�û�ID  _3���õ�ֵ:  1Ϊ�������� 2��ʾ�����ѽ���ʾ���� 3:Ϊ�����
	*/
	virtual void getUserNoDisturbMode(int64 targetId, CFunction<void(int, int64, int8)> cb) = 0;

	/*brief ����˽����Կ
	* @param[in] targetId Ŀ��ID�����˻�Ⱥ
	* @param[in] passwd  ˽����Կ  Ϊ�մ������˽������.
	* @param[in] cb  ������ս���ص� _1 ������Ϣ 
	*/
	virtual void setPrivateKey(int64 targetId, const std::string &passwd) = 0;

		/**
	* \brief ͨ����ϢID������Ϣ
	* @param[in] targetId Ŀ��ID�����˻�Ⱥ
	* @param[in] msgIds  Ҫ���ܵ���ϢID����
	* @param[in] cb  ������ս���ص� _1 ������Ϣ _2 ������Ϣ��targetId _3�ѽ��ܵ���Ϣ
	*/
	virtual void decryptMsg(int64 targetId, std::vector<int64> &msgIds, CFunction<void(int, int64, std::vector<CSharedPtr<data::Msg>>&)> cb) = 0;
	
	/**
	* \brief ���¶�ӦtargetId����Ϣ��ֻ�ܸ�����Ϣ���property
	* @param[in] targetId Ŀ��ID�����˻�Ⱥ
	* @param[in] msgs  Ҫ���µ���Ϣ����
	* @param[in] cb  ������ս���ص� _1 ������Ϣ
	*/
	virtual void updateMsg(std::vector<CSharedPtr<data::Msg>> &msgs) = 0;
	virtual void updateMsg(CSharedPtr<data::Msg> &msg) = 0;

	/**
	* \brief ȫ�ֲ�����Ϣ
	* @param[in] key	   ������ҹؼ���
	* @param[in] msgProperty  ������ҵĸ�������
	* @param[in] cb     ������ս���ص�  _1������Ϣ  _2��Ϣ�����������
	*/
	virtual void searchMessage(const std::string &key, data::MsgSearchProperty &msgProperty,CFunction<void(int, data::MsgSearchResult&)> cb) = 0;

	/**
	* \brief ������ӦtargetID����ϸ��Ϣ
	* @param[in] key	   ������ҹؼ���
	* @param[in] msgDetailProperty  ������ҵĸ�������
	* @param[in] cb     ������ս���ص�  _1������Ϣ  _2��Ϣ�����������
	*/
	virtual void searchDetailMessage(const std::string &key, data::MsgDetailSearchProperty &msgDetailProperty,CFunction<void(int, data::MsgDetailSearchResult&)> cb) = 0;
	
	/**
	* \brief �ϴ��ļ�  ///���ϵ��ϴ�,key����һ��
	* @param[in] targetId �˻�Ⱥ��id
	* @param[in] cb  ������ս���ص� _1������Ϣ _2Ŀ��Id _3���������ص�json
	* @param[in] pro  ���Ȼص� _1 extra_req  _2process
	* @return ÿ���ļ���Ӧ��ΨһlocalID
	*/
	virtual int64 uploadFile(data::UploadFileProperty &fileProperty, CFunction<void(int, int64, const std::string&)> cb,
		CFunction<void(int32, int32, const std::string&)> pro = CNull) = 0;

	virtual std::string parceEmojiDeal(const std::string msg)=0;
	/**
* \brief .��ȡһ����Ϣ��δ����������
* @param[in] groupId  ȺID
* @param[in] infos  ��Ϣid����id��Ϣ
* @param[in] cb  ������ս���ص� _1 ������Ϣ _2��ʾ����������Ϣ��δ��״̬
*/
	virtual void getGroupMsgUnreadCounter(int64 groupId, std::vector<data::SnapshotInfo> &infos, CFunction<void(int, std::vector<data::MsgUnreadCounter>&)> cb) = 0;

	/**
	* \brief .��ȡ��ϵ������Ѷ�ID
	* @param[in] targetId ��ϵ��ID
	* @param[in] cb  ������ս���ص� _1 ������Ϣ _2����Ѷ�ID
	*/
	virtual void getContractMaxReadId(int64 targetId, CFunction<void(int, int64)> cb) = 0;

	/**
	* \brief .ͳ����Ϣ�Ѷ���δ��������ϸ��Ϣ
	* @param[in] groupId  ȺID
	* @param[in] info  ��Ϣid����id��Ϣ
	* @param[in] cb  ������ս���ص� _1 ������Ϣ _2�Ѷ�userID�б� _3δ��userID�б�
	*/
	virtual void getGroupMsgUnreadInfo(int64 groupId, data::SnapshotInfo &info, CFunction<void(int, std::vector<int64>&, std::vector<int64>&)> cb) = 0;

	/**
	* \brief ��ȡȺ����Ϣ�Ķ�ȡ״̬
	* @param[in] targetId  Ŀ��targetId
	* @param[in] msgId  ��Ϣid
	* @param[in] cb  ������ս���ص� _1 ������Ϣ _2��ʾ���ض�Ӧ���͵���Ϣ���Ѷ���δ����δ����userID�б�
	*/
	virtual void getGroupMsgReadState(int64 targetId, int64 msgId, CFunction<void(int, std::vector<int64>&, std::vector<int64>&)> cb) = 0;
};
extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}

