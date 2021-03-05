#pragma once
#include <IGroupMgrControl.h>
#include "ServiceDefine.h"
#include <vector>
namespace service{
	class IMClient;
}
namespace control{
	class GroupMgrControl:public IGroupMgrControl{
	public:
		typedef CFunction< void(int8, const data::Group&) > GroupRefreshCallBackPtr;
		typedef CFunction< void(int64 , const std::string&, int64 , const std::string&)> TransferGroupCallBackPtr;
		typedef CFunction< void(int64 , const data::Member&)> GrpMemInfoRefreshCallBackPtr;
		typedef CFunction< void(int , int64 , std::vector<CSharedPtr<data::Member> >&)> GrpMemRefreshCallBackPtr;
		typedef CFunction< void(int , std::vector<CSharedPtr<data::Member> >&)> GetGrpMemListCallBackPtr;
		typedef CFunction< void(std::vector<CSharedPtr<data::TinyGroup> >&)> GroupListCallBackPtr;
		typedef CFunction< void(int, std::vector<CSharedPtr<data::Member> >&)>GetMemberListCallBackPtr;
		typedef CFunction< void(int, std::vector<CSharedPtr<data::FileInfo>>&)> GetFlieListCallBackPtr;
		typedef CFunction< void (int, int64) > GroupMemCountChangePtr;
		typedef CFunction<void(int32, int32, const std::string&)> FileUpProgressCallBackPtr;
		typedef CFunction<void(int, int64, const std::string&)> FileUpResultCallBackPtr;
		typedef CFunction< void (int)> GroupNoticeCallBackPtr;
		typedef CFunction< void (int)> GroupFileDelCallBackPtr;
		typedef CFunction< void(int)> GroupFileCancelCallBackPtr;
		typedef CFunction<void(int, data::Member&)> GetGroupMemCb;
		typedef CFunction<void(int, std::vector<CSharedPtr<data::Member> >&)> GetBatchMemberByIDCb;
		GroupMgrControl(const std::string &strName=std::string("groupmgrcontrol"));
		virtual ~GroupMgrControl();
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

		/**********************************************************************************************************
		*brief ��������ػ�ͷ���������
		*@param[out] cb _1Ŀ��ID���˻���Ⱥ  _2 ͷ��
		**********************************************************************************************************/
		virtual void RegGroupHeadImgUpdateCb(CFunction < void(int64 targetId, const std::string&head)>cb);

		/**
		* \brief ����Ⱥ��Աͷ�����
		* @param[in] _1 ����Ŀ��ID���˻���Ⱥ
		* @param[in] _2	  ����ͷ��
		*/
		virtual void RegMemberHeadImgUpdateCb(CFunction < void(int64 targetId, const std::string&head) > cb);

		/**
		* \brief ����Ⱥ��������
		* @param[in] _1 ����Ŀ��ID���˻���Ⱥ
		* @param[in] _2	  ����ͷ��
		*/
		virtual void RegGroupBackImgUpdateCb(CFunction < void(int64 targetId, const std::string&head) > cb);

		/**
		* \brief ���ü���Ⱥ��Ϣ���µĻص�
		* @param[in] _1 �������� 1.��� 2.���£�31.��ɢ 32.�Ƴ� 33.�˳�
		* @param[in] _2 Ⱥ��Ϣ
		*/
		virtual void RegGroupRefreshCb(CFunction< void(int8 type, const data::Group&groupInfo) > cb);

		/**
		* \brief ���ü���Ⱥ�����µĻص�
		* @param[in] _1 Ⱥ��ID
		* @param[in] _2 Ⱥ����
		* @param[in] _3 ȺID
		* @param[in] _4 Ⱥ��
		*/
		virtual void RegTransferGroupCb(CFunction< void(int64 creatorId, const std::string&creatorName, int64 groupId, const std::string&groupName) > cb);
	
		/**
		* \brief ���ü���Ⱥ��Ա��Ϣ���µĻص�
		* @param[in] _1 ȺID
		* @param[in] _2 Ⱥ��Ա��Ϣ
		*/
		virtual void RegGrpMemInfoRefreshCb(CFunction< void(int64 groupId, const data::Member&memberInfo) > cb);

		/**
		* \brief  ����Ⱥ��Ա�б���µĻص�
		* @param[in] _1 ��������  1 ��ӣ� 32 �Ƴ��� 33 �˳�
		* @param[in] _2 ȺID
		* @param[in] _3 �����Ⱥ��Ա����
		*/
		virtual void RegGrpMemRefreshCb(CFunction< void(int type, int64 groupId, std::vector<CSharedPtr<data::Member> >&members) > cb);

		/**
		* \brief  ���û�ȡȺ��Ա�б�Ļص�
		* @param[in] _1 ������Ϣ����ʹ�ã�ֻ��Ϊ�˺�getMemberList�ص�����һ��
		* @param[in] _2 Ⱥ��Ա�б�
		*/
		virtual void RegGetGrpMemListCb(CFunction<void(int code, std::vector<CSharedPtr<data::Member> >&members)> cb);
	
		/**
		* \brief  ����Ⱥ�б�ˢ��
		* @param[in] _1 Ⱥ�б�
		*/
		virtual void RegGroupListCb(CFunction< void(std::vector<CSharedPtr<data::TinyGroup> >&groups) > cb);

		/**
		* \brief ����Ⱥ
		* @param[in] level ����Ⱥ�ȼ� 1.��ʱȺ��2.��ͨȺ
		* @param[in] name ����Ⱥ����
		* @param[in] members   ����Ⱥ��Ա
		* @param[in] cb  ������ս���ص�  _1������Ϣ  _2ȺID
		*/
		virtual void CreateGroup(int level, const std::string &name, std::vector<int64> &members, CFunction<void(int, int64)> cb);

		/**
		* \brief ��Ⱥ
		* @param[in] groupid ����Ⱥid
		* @param[in] verify_info ������֤��Ϣ
		* @param[in] cb  ������ս���ص�  _1������Ϣ
		*/
		virtual void AddGroup(int64 groupid, const std::string &verify_info, CFunction<void(int)> cb);

		/**
		* \brief ��ɢȺ
		* @param[in] type ����������� 1 Ⱥ����ɢȺ��2 Ⱥ��Ա��Ⱥ
		* @param[in] groupid ����Ⱥid
		* @param[in] cb  ������ս���ص�  _1������Ϣ
		*/
		virtual void RemoveGroup(int type, int64 groupid, CFunction<void(int)> cb);

		/**
		* \brief ת��Ⱥ
		* @param[in] groupid ����Ⱥid
		* @param[in] userid ������Ⱥ����id
		* @param[in] cb  ������ս���ص�  _1������Ϣ
		*/
		virtual void TransferGroup(int64 groupid, int64 userid, CFunction<void(int)> cb);

		/**
		* \brief ��ȡȺ����
		* @param[in] groupid ����Ⱥid
		* @param[in] cb  ������ս���ص�  _1������Ϣ \n
		*    _2  ��֤����: 1.�������κ������, 2.��Ҫ��֤��Ϣ, 3.�����κ������.\n
		*	 _3	 �Ƿ�����Ⱥ��Ա������Ѽ���Ⱥ: 1.���� 2.������.
		*/
		virtual void GetGroupSet(int64 groupid, CFunction<void(int, int8, int8)> cb);

		/**
		* \brief ����Ⱥ����
		* @param[in] groupid ����Ⱥid
		* @param[in] verify_type ������֤���� 1:�������κ������,2����Ҫ��֤��Ϣ,3�������κ������
		* @param[in] is_allow �����Ƿ������Ա�����û� 1,���� 2,������ isAllow
		* @param[in] cb  ������ս���ص�  _1������Ϣ 
		*/
		virtual void SetGroupSet(int64 groupid, int8 verify_type, int8 is_allow, CFunction<void(int)> cb);

		/**
		* \brief ��ȡȺ��Ϣ ��ͬ���ӿڣ�
		* @param[in] groupid ����Ⱥid
		* @param[out] groupInfo Ⱥ��Ϣ
		*/
		virtual void GetGroupInfo(int64 groupid, data::Group& groupInfo);

		/**
		* \brief ����Ⱥ��Ϣ
		* @param[in] groupId ���õ�ȺID
		* @param[in] group  �����õ�Ⱥ��Ϣ
		* @param[in] cb  ������ս���ص�  _1������Ϣ 
		*/
		virtual void SetGroupInfo(int64 groupId, data::GroupUpdate &group, CFunction<void(int)> cb);

		/**
		* \brief ��ȡȺ�б� ��ͬ���ӿڣ�
		* @param[in] cb  ������ս���ص�  _1Ⱥ��Ϣ����;
		*/
		virtual void GetGroupList(std::vector<CSharedPtr<data::TinyGroup> > &groups);

		/**
		* \brief ����Ⱥ��Ա
		* @param[in] groupid ����Ⱥid
		* @param[in] members �����Ա����
		* @param[in] cb  ������ս���ص�   _1������Ϣ
		*/
		virtual void InviteMember(int64 groupid,std::vector<int64> &members,CFunction<void(int)> cb);

		/**
		* \brief �Ƴ�Ⱥ��Ա
		* @param[in] groupid ����Ⱥid
		* @param[in] userid ������Ҫ�Ƴ��ĳ�Աid
		* @param[in] cb  ������ս���ص�   _1������Ϣ
		*/
		virtual void RemoveMember(int64 groupid, int64 userid, CFunction<void(int)> cb);

		/**
		* \brief �����Ƴ�Ⱥ��Ա
		* @param[in] groupid ����Ⱥid
		* @param[in] userids ������Ҫ�Ƴ��ĳ�Աid����
		* @param[in] cb  ������ս���ص�   _1������Ϣ
		*/
		virtual void RemoveMembers(int64 groupid, std::vector<int64> userids, CFunction<void(int)> cb);

		/**
		* \brief ����Ⱥ��Ա��Ϣ
		* @param[in] member �����Ա��Ϣ
		* @param[in] cb  ������ս���ص�
		*/
		virtual void SetMemberInfo(data::Member &member, CFunction<void(int)> cb);

		/**
		* \brief �ж��û��Ƿ���Ⱥ�� (ͬ���ӿ�)
		* @param[in] groupid ����Ⱥid
		* @param[in] userid �����Աid
		* @return false������Ⱥ��Ա
		*/
		virtual bool IsInGroup(int64 groupId, int64 userId);

		/**
		* \brief ��ȡȺ��Ա��Ϣ (ͬ���ӿ�)
		* @param[in] groupid ����Ⱥid
		* @param[in] userid �����Աid
		* @param[out] member���س�Ա��Ϣ
		* @return false����û�д���Ϣ
		*/
		virtual bool GetMemberInfo(int64 groupid, int64 userid, data::Member &member);

		/**
		* \brief  ��ȡȺ��Ա�б�
		* @param[in] groupid ����Ⱥid
		* @param[in] cb  ������ս���ص�   _1������Ϣ  _2Ⱥ��Ա��Ϣ����
		*/
		virtual void GetMemberList(int64 groupid, CFunction<void(int, std::vector<CSharedPtr<data::Member> >&)> cb);

		/**
		* \brief ��ȡȺ�ļ��б�
		* @param[in] groupid ����Ⱥid
		* @param[in] beginid ������ʼid
		* @param[in] count ��������
		* @param[in] flag ����ƫ�Ʊ�־0Ϊ����1Ϊ����
		* @param[in] cb  ������ս���ص�   _1������Ϣ _2�ļ���Ϣ����
		*/
		virtual void getGroupFileList(int64 groupid, CFunction<void(int, std::vector<CSharedPtr<data::FileInfo>>&)> cb);

		/**
		* \brief ɾ��Ⱥ�ļ�
		* @param[in] files ����Ⱥ�ļ�id
		* @param[in] cb  ������ս���ص�   _1������Ϣ
		*/
		virtual void DeleteGroupFile(std::vector<int64> &files,int64 groupId, CFunction<void(int)> cb);

		/**
		* \brief ��ȡ����Ⱥ�ı���ͼƬ
		* @param[in] groupId ȺID
		* @param[in] cb  ������ս���ص�   _1������Ϣ   _2ͼƬURL
		*/
		virtual void GetPersonalGroupImg(int64 groupId, CFunction<void(int, const std::string&)> cb);

		/**
		* \brief ���ø���Ⱥ�ı���ͼƬ
		* @param[in] groupId ȺID
		* @param[in] imgUrl ͼƬURL
		* @param[in] cb  ������ս���ص�   _1������Ϣ
		*/
		virtual void SetPersonalGroupImg(int64 groupId, const std::string &imgUrl, CFunction<void(int)> cb);

		/**
		* \brief ����Ⱥ��Ϣ�����ģʽ
		* @param[in] groupId ȺID
		* @param[in] mode ����ģʽ 1����ʾ��������Ϣ��2������ʾ�����ս���ʾ��Ŀ��3��������Ϣ
		* @param[in] cb  ������ս���ص�   _1������Ϣ
		*/
		virtual void SetGroupMsgRemindType(int64 groupId, int8 mode , CFunction<void(int)> cb);

		/**
		* \brief ��ȡȺ��Ϣ�����ģʽ
		* @param[in] groupId ȺID
		* @param[in] cb  ������ս���ص�   _1������Ϣ _2����ģʽ 1����ʾ��������Ϣ��2������ʾ�����ս���ʾ��Ŀ��3��������Ϣ
		*/
		virtual void GetGroupMsgRemindType(int64 groupId, CFunction<void(int, int8)> cb);

		/**
		* \brief ����Ⱥ��Ϣ����ģʽ��V��
		* @param[in] groupId ȺID
		* @param[in] vSign ȺV�� 0Ϊ��v��Ⱥ��1Ϊv��Ⱥ -1Ϊ������
		* @param[in] msgContentMode Ⱥ֪ͨ��Ϣ����ģʽ: 1��֪ͨ����  2��֪ͨԴ����������  3����ȫ����   -1Ϊ������
		* @param[in] cb  ������ս���ص�   _1������Ϣ _2����ģʽ
		*/
		virtual void SetGroupExtraInfo(int64 groupId, int8 vSign, int8 msgContentMode, CFunction<void(int)> cb);
		
		/*
		* \brief ����Ⱥ��Ա���ݱ仯
		*  @param[in] targetid
		*  @param[in] OprType 0:ע��   1:ɾ��
		*/
		virtual void SetGroupMemCountCb(int64 id,CFunction<void(int, int64)>cb);
		
		
	/**
	* \brief �ϴ��ļ�  ///���ϵ��ϴ�,key����һ��
	* @param[in] targetId �˻�Ⱥ��id
	* @param[in] cb  ������ս���ص� _1������Ϣ _2Ŀ��Id _3���������ص�json
	* @param[in] pro  ���Ȼص� _1 extra_req  _2process 
	* @return ÿ���ļ���Ӧ��ΨһlocalID
	*/
		virtual int64 uploadFile(data::UploadFileProperty &fileProperty, CFunction<void(int, int64, const std::string&)> cb,
		CFunction<void(int32, int32, const std::string&)> pro = SNull);

		static bool sort(CSharedPtr<data::TinyGroup>& first,CSharedPtr<data::TinyGroup>&second);
		//static bool sortMem(CSharedPtr<data::Member>& first,CSharedPtr<data::Member>&second);
	
		/**
		* \brief ȡ���ļ��ϴ�������
		* @param[in] localId �ļ���localId
		* @param[in] type  1.�ϴ� 2.���� 3.�ⲿ����
		*/
		virtual void cancelTransfer(int64 localId, int type, CFunction<void(int)> cb);
		virtual void getGroupMemberFromNet(int64 groupId, int64 memberID, CFunction<void(int, data::Member&)> cb);
		/**
		* \brief ������ȡȺ��Ա
		* @param[in] groupId ȺID
		* @param[in] memberIDs Ⱥ��Աid����
		* @param[in] cb  ������ս���ص�   _1������Ϣ _2��Ա��Ϣ����
		*/
		virtual void getBatchMemberByID(int64 groupId, std::vector<int64>& memberIDs, CFunction<void(int, std::vector<CSharedPtr<data::Member> >&)> cb);
	protected:
		void DataConvert(const model::Group &group, data::Group &groupInfo);
		data::TinyGroup DataConvert(const model::TinyGroup tinyGroup);
		void DataConvert(const data::GroupUpdate data,model::GroupUpdate& outGroupUpdate);
		void DataConvert(CSharedPtr<model::TinyGroup>inTiny,CSharedPtr<data::TinyGroup>&outTiny);
		model::Member  DataConvert(data::Member &inMember);
		void DataConvert(const model::Member &inMember,data::Member &outMember);
		void DataConvert(CSharedPtr<model::Member>inMember,CSharedPtr<data::Member>outMember);
		bool IsNullService();

		void OnGroupRefreshCb(int8 type, const model::Group&group);
		void OnTransferGroupCb(int64 creatorId, const std::string&creatorName, int64 groupId, const std::string&groupName);
		void OnGrpMemInfoRefreshCb(int64 groupId, const model::Member&member);
		void OnGrpMemRefreshCb(int type, int64 groupId, std::vector<SSharedPtr<model::Member> >&mems);
		void OnGetGrpMemListCb(service::ErrorInfo code, std::vector<CSharedPtr<model::Member> >& mems);
		void OnGroupListCb(std::vector<CSharedPtr<model::TinyGroup> >&groups);
		void OnGetMemberListCb(service::ErrorInfo code, std::vector<CSharedPtr<model::Member> >&mems);
		void onGetFileListCb(service::ErrorInfo code, std::vector<Fileinfo>& files);

		void onSerDelFileResult(int code,std::vector<int64>&);
		void onSerSetGroupInfoResult(int code);
		void onSerUpFileResult(int, int64, const std::string&,int64);
		void onSerUpfileProgress(int32, int32, const std::string&,int64);
		void onSerCancelFileResult(int code, int64 filelocalid);
		void onSerGetGroupMemberResult(service::ErrorInfo code, model::Member& mem,GetGroupMemCb cb);
		void onSerGetBatchMemberByID(service::ErrorInfo code, std::vector<SSharedPtr<model::Member> >&mems, GetBatchMemberByIDCb cb);
	private:
		int m_CreateGroupMemCount;
		std::string							m_pluginname; //�������������׺�ģ�
		IGroupService_Ptr					m_groupservice;
		IFileService_Ptr                    m_fileservice;
		ISearchService_Ptr                  m_searchservice;
		GrpMemRefreshCallBackPtr     m_groupMemRefreshCb;//Ⱥ��Ա�б����
		std::vector<GroupRefreshCallBackPtr> m_groupRefreshCb;//Ⱥ��Ϣ����
		TransferGroupCallBackPtr    m_transferGroupCb;//Ⱥ������
		std::vector<GrpMemInfoRefreshCallBackPtr> m_groupMemInfoRefreshCb;//Ⱥ��Ա��Ϣ����
		GetGrpMemListCallBackPtr m_getGroupMemListCb;//��ȡȺ��Ա�б�
		GroupListCallBackPtr     m_groupListCb;//Ⱥ�б�ˢ��
		GetMemberListCallBackPtr m_getMemsListCb;//��ȡȺԱ�б�
		GetFlieListCallBackPtr m_pGetFileListCb;	// ��ȡȺ�ļ��б�
		std::map<int64,FileUpProgressCallBackPtr> m_pFileUpProgressCb;
		std::map<int64,FileUpResultCallBackPtr> m_pFileUpResultCb;
		GroupNoticeCallBackPtr m_groupNoticeResultCb;
		std::map<int64, GroupMemCountChangePtr> m_groupMemCountRefreshCb;
		std::map<int64, GroupFileDelCallBackPtr> m_groupfileDelResultCb;


		std::map<int64, GroupFileCancelCallBackPtr> m_groupfileCancelResultCb;
	};
}