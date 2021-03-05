#pragma once
#include <IUpdateControl.h>
#include "ServiceDefine.h"
namespace service{
	class IMClient;
}
namespace control{
	class UpdateControl:public IUpdateControl{
	public:
		typedef CFunction<void(data::UpdateInfo&update)> UpdateNoticeCallBack;
		UpdateControl(const std::string &strName=std::string("updatecontrol"));
		virtual ~UpdateControl();
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
	public:
		/******************************************************************
		* @brief ����������Ϣ����
		* @param[out] update ������Ϣ�ṹ�� 
		******************************************************************/
		virtual void RegUpdateInfoNotice(CFunction<void(data::UpdateInfo&update)>cb);

		/******************************************************************
		* @brief �������������ݴ��Ŀ¼
		* @param[in] dirpath �������ݱ���Ŀ¼·��
		******************************************************************/
		virtual void SetUpdateDataDir(std::string&dirpath);

		/******************************************************************
		* @brief ������
		* @param[in] url     ������Ϣ�����ص�ַ
		* @param[out] update ������Ϣ�ṹ�� 
		******************************************************************/
		virtual void CheckUpdate(std::string&url);

		/******************************************************************
		* @brief ���߼�����
		* @param[in] servername  ��������
		******************************************************************/
		virtual int CheckUpdateOnline(std::string&servername);

		/******************************************************************
		* @brief �����������ӿ�
		* @param[in] localpath  ����������·��
		* @param[in] url  ������url��ַ
		* @param[out] cb  ����ֵ
		* @param[out] pro ���ؽ������ͻص�
		* @return ÿ���ļ���Ӧ��ΨһlocalID
		******************************************************************/
		virtual int64 DownLoadUpdateFile(std::string&localpath,std::string&url,CFunction<void(int)>cb,CFunction<void(int32, int32, const std::string&)>pro=CNull);

		/******************************************************************
		* @brief ȡ�������������ӿ�
		* @param[in] localpath  ����������·��
		* @return ÿ���ļ���Ӧ��ΨһlocalID
		******************************************************************/
		virtual void CancelDownLoadUpdateFile(int64 filelocalid,CFunction<void(int)>cb);
   protected:
		void  CheckLocalUpdate(std::string& httpurl);
		int   GetUpdateInfo(std::string jsonPath, data::UpdateInfo& info);
		int   ParseUpdateJson(std::string json,data::UpdateInfo& info);
		int   IsNeedUpdate(std::string curver, std::string servrver);
		int   Compare_Value(int val1, int val2);
		int   CompareUpdateVer(char* szVer1, char* szVer2);
		void  Split(std::string src, data::UpdateVer& Ver);
		int   ParseClientDefJsonInfo(std::string&json, data::UpdateInfo& info);
		void  ParsePreLoginJson(std::string&json, data::UpdateInfo& info);
		bool  IsSamePlatForm(std::string& pt);
		void  PushUpdateNotify(data::UpdateInfo&info);
	protected:
		void  onDownloadUpdateJson(int err);
		void  onSerCheckUpdate(model::UpgradeInfo& update);
	private:
		std::string			m_pluginname;		//�������������׺�ģ�
		std::string			m_datadirpath;		//������Ŀ¼·��
		std::string			m_updatejsonpath;	//������Ϣupdate.json·��
		UpdateNoticeCallBack m_noticecb;
	private:
		IConfigService_Ptr  m_configservice;	
		IAuthService_Ptr	m_authservice;
		IFileService_Ptr	m_fileservice;
	};
}
