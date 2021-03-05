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
		* @brief 返回带后缀的插件名
		* @param[in]无
		***********************************************/
		virtual std::string GetName();
		/***********************************************
		* @brief 返回不带后缀的插件名
		* @param[in]无
		***********************************************/
		virtual std::string GetDisplayName();

		/***********************************************
		* @brief 设置sdk客户端实例对象
		* @param[in]无
		***********************************************/
		virtual void SetSdkClientObj(void* obj);
	public:
		/******************************************************************
		* @brief 设置升级信息推送
		* @param[out] update 升级信息结构体 
		******************************************************************/
		virtual void RegUpdateInfoNotice(CFunction<void(data::UpdateInfo&update)>cb);

		/******************************************************************
		* @brief 设置升级包数据存放目录
		* @param[in] dirpath 升级数据保存目录路径
		******************************************************************/
		virtual void SetUpdateDataDir(std::string&dirpath);

		/******************************************************************
		* @brief 检查更新
		* @param[in] url     更新信息的下载地址
		* @param[out] update 升级信息结构体 
		******************************************************************/
		virtual void CheckUpdate(std::string&url);

		/******************************************************************
		* @brief 在线检查更新
		* @param[in] servername  服务器名
		******************************************************************/
		virtual int CheckUpdateOnline(std::string&servername);

		/******************************************************************
		* @brief 下载升级包接口
		* @param[in] localpath  升级包保存路径
		* @param[in] url  升级包url地址
		* @param[out] cb  错误值
		* @param[out] pro 下载进度推送回调
		* @return 每个文件对应的唯一localID
		******************************************************************/
		virtual int64 DownLoadUpdateFile(std::string&localpath,std::string&url,CFunction<void(int)>cb,CFunction<void(int32, int32, const std::string&)>pro=CNull);

		/******************************************************************
		* @brief 取消下载升级包接口
		* @param[in] localpath  升级包保存路径
		* @return 每个文件对应的唯一localID
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
		std::string			m_pluginname;		//插件名（不带后缀的）
		std::string			m_datadirpath;		//升级包目录路径
		std::string			m_updatejsonpath;	//升级信息update.json路径
		UpdateNoticeCallBack m_noticecb;
	private:
		IConfigService_Ptr  m_configservice;	
		IAuthService_Ptr	m_authservice;
		IFileService_Ptr	m_fileservice;
	};
}
