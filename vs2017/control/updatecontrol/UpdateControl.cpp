#include "UpdateControl.h"
#include "log.h"
#include "../../utils/common.h"
#include "../../utils/Hardware.h"
#include "../../ui/Resources/versionctrl/ver.h"
#include <json.h>
#include <iostream>  
#include <fstream> 
#include <algorithm>
const char * filename = 0;
int line = 0;

namespace control{
	service::IMClient* g_client =CNull;
	UpdateControl::UpdateControl(const std::string &strName):m_datadirpath(""),m_updatejsonpath(""),m_pluginname(strName),
		m_configservice(CNull),m_fileservice(CNull),m_authservice(CNull){
		BEGIN;
			
		END;
	}
	UpdateControl::~UpdateControl(){
		BEGIN;
		END;
	}
	/***********************************************
	* @brief 返回带后缀的插件名
	* @param[in]无
	***********************************************/
	std::string UpdateControl::GetName(){
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
		return result;
	}
	/***********************************************
	* @brief 返回不带后缀的插件名
	* @param[in]无
	***********************************************/
	std::string UpdateControl::GetDisplayName(){
		return m_pluginname;
	}

	/***********************************************
	* @brief 设置sdk客户端实例对象
	* @param[in]无
	***********************************************/
	void UpdateControl::SetSdkClientObj(void* obj){
	BEGIN;
		g_client =static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK客户端对象指针失败");
			return;
		}
		m_configservice = CONFIGSERVICE;
		m_authservice	= AUTHSERVICE;
		m_fileservice	= FILESERVICE;
	END;
	}
	/******************************************************************
	* @brief 设置升级信息推送
	* @param[out] update 升级信息结构体 
	******************************************************************/
	void UpdateControl::RegUpdateInfoNotice(CFunction<void(data::UpdateInfo&update)>cb){
		BEGIN;
		    m_noticecb = cb;
		END;
	}
	/******************************************************************
	* @brief 设置升级包数据存放目录
	* @param[in] _1 传入目标ID，人或者群
	******************************************************************/
	void UpdateControl::SetUpdateDataDir(std::string&dirpath){
		BEGIN;
		    utils::string_replace(dirpath,"\\","/");
			m_datadirpath = dirpath;
		END;
	}
	/******************************************************************
	* @brief 检查更新
	* @param[in] url     更新信息的下载地址
	* @param[out] update 升级信息结构体 
	******************************************************************/
	void UpdateControl::CheckUpdate(std::string&url){
		BEGIN;
			m_authservice->regUpgrageCb(CBind(&UpdateControl::onSerCheckUpdate, this, CPlaceholders  _1));
		    CheckLocalUpdate(url);
		END;
	}
	/******************************************************************
	* @brief 在线检查更新
	* @param[in] servername  服务器名
	******************************************************************/
	int UpdateControl::CheckUpdateOnline(std::string&servername){
		//在线检查更新
		data::UpdateInfo info;
		std::string json =m_configservice->getLoginExData(servername);
		Log(LOG_LEV_DEBUG, LOG_FILE, "json=%s", json.c_str());
		ParsePreLoginJson(json,info);
		//推送检查结果
	    PushUpdateNotify(info);
        return info.force;
	}

	/******************************************************************
	* @brief 下载升级包接口
	* @param[in] localpath  升级包保存路径
	* @param[in] url  升级包url地址
	* @param[out] cb  错误值
	* @param[out] pro 下载进度推送回调
	******************************************************************/
	int64 UpdateControl::DownLoadUpdateFile(std::string&localpath,std::string&url,CFunction<void(int)>cb,CFunction<void(int32, int32, const std::string&)>pro){
		int64 fileid = 0;
	  BEGIN;
		    AddLog(LOG_LEV_DEBUG,"localpath=%s,url=%s",localpath.c_str(),url.c_str());
			fileid = m_fileservice->downloadExternalFile(localpath,url,0,cb,pro);
	  END;
	     return fileid;
	}

	/******************************************************************
	* @brief 取消下载升级包接口
	* @param[in] localpath  升级包保存路径
	* @return 每个文件对应的唯一localID
	******************************************************************/
	void UpdateControl::CancelDownLoadUpdateFile(int64 filelocalid,CFunction<void(int)>cb){
		BEGIN;
			  int type =3;//1upload  2download 3.extern download
		      m_fileservice->cancelTransfer(filelocalid,type,cb);
		END;
	}

	void UpdateControl::onSerCheckUpdate(model::UpgradeInfo& update){
	 BEGIN;
		data::UpdateInfo info;
		info.force = update.gradeType;
		info.version = update.version;

		AddLog(LOG_LEV_DEBUG,"************updateInfo.upAddr size=%d", update.upAddr.size());
		for (int index=0; index<update.upAddr.size();++index)
		{
			std::string url("");
			data::PACK_TYPE type = data::PACK_INIT;

			url = update.upAddr[index].url;
			AddLog(LOG_LEV_INFO, "nocache=%s,url=%s,descr=%s,filesize=%s,signCode=%s,htmlDowmload=%s,ext=%s",
				update.upAddr[index].nocache.c_str(), update.upAddr[index].url.c_str(), update.upAddr[index].descr.c_str(), update.upAddr[index].fileSize.c_str(), update.upAddr[index].signCode.c_str(),
				update.upAddr[index].htmlDowmload.c_str(), update.upAddr[index].ext.c_str());

			if (std::string::npos != url.find(".exe"))
			{
				continue;
			}
			else if ( std::string::npos != url.find("patch.mar"))
			{
				type = data::PACK_PATCH;
				info.patchurl = url;
			}
			else if (std::string::npos != url.find("full.mar"))
			{
				type = data::PACK_FULL;
				info.fullurl = url;
			}
			else if (std::string::npos != url.find("dependlib.mar"))
			{
				type =data::PACK_DEPEND;
				info.dependurl = url;
			}
			else{
				info.url = url;
				info.dependurl = url;
				info.patchurl = url;
				Log(LOG_LEV_INFO, LOG_FILE, "unknow update packet,url=%s", update.upAddr[index].url.c_str());
			}
		}
		if (info.versionname.empty())
		{
			info.versionname =std::string("V") + info.version;
		}
		//取增量包地址
		info.url = info.patchurl;
		ParseClientDefJsonInfo(update.clientInfo, info);
	 END;
		//推送升级通知
	    PushUpdateNotify(info);
	}
	void UpdateControl::CheckLocalUpdate(std::string& httpurl){
		char szuf8[MAX_PATH] = {0};
		m_updatejsonpath = m_datadirpath + std::string("/update.json");
		AddLog(LOG_LEV_DEBUG,"updatejson localFileUrl=%s, Path=%s", httpurl.c_str(), m_updatejsonpath.c_str());
		utils::char2utf8(m_updatejsonpath.data(),szuf8);
		m_fileservice->downloadExternalFile(szuf8, httpurl, 0, CBind(&UpdateControl::onDownloadUpdateJson, this, CPlaceholders  _1), CNull);
	}
	void UpdateControl::onDownloadUpdateJson(int err){
		if (!err)
		{
			int res = -1;
			data::UpdateInfo info;
			std::string version("");

			version = utils::get_client_info();
			if (!utils::FileIsExist(m_updatejsonpath))
			{
				AddLog(LOG_LEV_ERROR,"update.json file not exist!,filePath=%s",m_updatejsonpath.data());
				return;
			}
			if (GetUpdateInfo(m_updatejsonpath,info) != 0)
			{
				AddLog(LOG_LEV_ERROR,"prase update info  from update.json file failed");
				return;
			}
			//judge in vip list
			if (info.vip.size())
			{
				std::string mac = utils::Hardware::mac();//"F8:1E:DF:ED:D3:2A";
				auto itr = std::find(info.vip.begin(), info.vip.end(), mac);
				if (itr == info.vip.end()){
					res = 0;
					AddLog(LOG_LEV_ERROR, LOG_FILE, "[-----VIP list not found-----]");
					return;
				}
				AddLog(LOG_LEV_ERROR,"[-----VIP user update-----]");
			}

			//delelte update.json
			if (utils::FileIsExist(m_updatejsonpath)){
				int err = remove(m_updatejsonpath.c_str());
				if (-1 == err)
				{
					AddLog(LOG_LEV_ERROR,"[-----update json delete failed,err=%d-----]",err);
				}
			}

			AddLog(LOG_LEV_INFO,"[version:%s,info.version=%s]", version.c_str(),info.version.c_str());
			res = IsNeedUpdate(version,info.version);
			if ( -1 != res)
			{
				for (size_t index=0; index<info.info.size(); ++index)
				{
					info.desc.append(info.info.at(index));
					info.desc.append(";");
				}
				//推送升级通知
				PushUpdateNotify(info);
			}
		}
		else{
			AddLog(LOG_LEV_DEBUG,"updatejson download failed,errcode=%d", err);
		}
	}
	int UpdateControl::GetUpdateInfo(std::string jsonPath, data::UpdateInfo& info)
	{
	BEGIN;
		int ret = -1;
		char * buffer = 0;  
		long size = 0;  
		std::string srcjson("");
		std::ifstream in(jsonPath, std::ios::in|std::ios::binary|std::ios::ate);
		size = in.tellg();  
		in.seekg (0, std::ios::beg);  
		buffer = new char [size];  
		in.read (buffer, size);  
		in.close(); 
		srcjson = std::string(buffer);
		AddLog(LOG_LEV_DEBUG,"srcjson=%s",srcjson.c_str());
		delete[] buffer; 
		ret = ParseUpdateJson(srcjson, info);
	END;
		return ret;
	}

	int  UpdateControl::ParseUpdateJson(std::string json,data::UpdateInfo& info){
	   int ret = 0;
	   Json::Reader reader;
	   Json::Value root,arrayobj;
	   ret = reader.parse(json, root);
	   if (!ret)
	   {
		   AddLog(LOG_LEV_ERROR,"json parse filed,err=%d,json=%s",ret,json.c_str());
		   return ret;
	   }
	   if (!root["version"].isNull()&& root["version"].isString())
	   {
		   info.version = root["version"].asString();
	   }
	   if (!root["versionname"].isNull()&& root["versionname"].isString())
	   {
		   info.versionname = root["versionname"].asString();
	   }
	   if (!root["revision"].isNull()&& root["revision"].isString())
	   {
		   info.svnVersion = root["revision"].asString();
	   }
	   if (!root["versionType"].isNull()&& root["versionType"].isString())
	   {
		   info.platform = root["versionType"].asString();
	   }
	   if (!root["force"].isNull()&& root["force"].isInt())
	   {
		   info.force = root["force"].isInt();
	   }
	   if (!root["vip"].isNull()&& root["vip"].isString())
	   {
		   std::string vip_value = root["vip"].asString();
		   info.vip = utils::splitWithStl(vip_value,";");
	   }
	   if (!root["content"].isNull()&& root["content"].isString())
	   {
		   std::string content = root["content"].asString();
		   info.info = utils::splitWithStl(content,";");
	   }
	   if (!root["files"].isNull()&& root["files"].isArray())
	   {
		   arrayobj = root["files"];
		   int iSize = arrayobj.size();
		   for ( int nIndex = 0;nIndex < iSize;++ nIndex )  
		   {  
			   std::string url("");
			   std::string hashcode("");
			   data::PACK_TYPE type; 
			   if (arrayobj[nIndex].isMember("fileType")&& arrayobj[nIndex]["fileType"].isString())  
			   {  
				   type = (data::PACK_TYPE)atoi(arrayobj[nIndex]["fileType"].asString().data());
			   }
			   if (arrayobj[nIndex].isMember("fileUrl")&& arrayobj[nIndex]["fileUrl"].isString())  
			   {  
				   url = arrayobj[nIndex]["fileUrl"].asString();
			   }
			   if (arrayobj[nIndex].isMember("hashCode")&& arrayobj[nIndex]["fileUrl"].isString())  
			   {  
				   hashcode = arrayobj[nIndex]["hashCode"].asString();
			   }
			   if (arrayobj[nIndex].isMember("systemDbHashcode")&& arrayobj[nIndex]["systemDbHashcode"].isString())  
			   {  
				   info.systemDbMd5 = arrayobj[nIndex]["systemDbHashcode"].asString();
			   }
#ifdef _WIN32
			   switch(type){
			   case data::PACK_FULL:
				{
					 info.fullurl = url;
					 info.fullMd5 = hashcode;
				     break;
				}
			   case data::PACK_PATCH:
				   {
					   info.patchurl = url;
					   info.patchMd5 = hashcode;
					   break;
				   }
			   case data::PACK_DEPEND:
				   {
					   info.dependurl = url;
					   info.dependMd5 = hashcode;
					   break;
				   }
			  default:
				   {
					   break;
				   }
			   }
#else
			   info.url = url;
			   info.dependurl=url;
			   info.patchurl=url;
#endif
		   }
	   }
	   if (info.versionname.empty())
	   {
		   info.versionname =std::string("V") + info.version;
	   }
	   //取增量包地址
	   info.url = info.patchurl;
	   info.md5 = info.patchMd5;
	   ret=0;
	   return ret;
	}
	int UpdateControl::ParseClientDefJsonInfo(std::string&json, data::UpdateInfo& info){
		BEGIN;
		 int ret = 0;
		 Json::Reader reader;
		 Json::Value root;

		 ret = reader.parse(json, root);
		 if (!ret)
		 {
			 AddLog(LOG_LEV_ERROR,"json parse filed,err=%d,json=%s",ret,json.c_str());
			 return ret;
		 }
		 if (!root["describe"].isNull()&& root["describe"].isString())
		 {
			 info.info = utils::splitWithStl(root["describe"].asString(),";");
		 }
		 if (!root["dependMd5"].isNull()&& root["dependMd5"].isString())
		 {
			 info.dependMd5 = root["dependMd5"].asString();
		 }
		 if (!root["patchMd5"].isNull()&& root["patchMd5"].isString())
		 {
			 info.patchMd5 = root["patchMd5"].asString();
		 }
		 if (!root["fullMd5"].isNull()&& root["fullMd5"].isString())
		 {
			 info.fullMd5 = root["fullMd5"].asString();
		 }
		 if (!root["systemDbHashcode"].isNull()&& root["systemDbHashcode"].isString())
		 {
			 info.systemDbMd5 = root["systemDbHashcode"].asString();
		 }
		 if (!root["versionType"].isNull()&& root["versionType"].isString())
		 {
			 info.platform = root["versionType"].asString();
		 }
		 for (int index=0;index<info.info.size();++index)
		 {
			 info.desc.append(info.info.at(index));
			 info.desc.append(";");
		 }
		END;
			info.md5 = info.patchMd5;//存在此宏定义说明是新版升级新版本
		 return ret;
	}
	void UpdateControl::ParsePreLoginJson(std::string&json, data::UpdateInfo& info){
		int ret = 0;
		Json::Reader reader;
		Json::Value root;

		ret = reader.parse(json, root);
		if (!ret)
		{
			AddLog(LOG_LEV_ERROR,"json parse filed,err=%d,json=%s",ret,json.c_str());
			return;
		}
		if (!root["resType"].isNull()&& root["resType"].isString())
		{
			std::string restype = root["resType"].asString();
			std::transform(restype.begin(), restype.end(), restype.begin(), ::tolower);
			if (std::string("forceup") == restype){
				info.force = data::FORCE_UPDATE;
			}
			else if (std::string("adviceup") == restype){
				info.force = data::ADVICE_UPDATE;
			}
			else{
				info.force = data::NONEED_UPDATE;
				return;
			}
		}

		//不需要升级
		if (root["upd"].isNull())
		{
			info.force = data::NONEED_UPDATE;
			return;
		}
		else{
			Json::Value updobj = root["upd"];
			if (updobj.isNull())
			{
				info.force = data::NONEED_UPDATE;
				return;
			}

			if (!updobj["clientDefInfo"].isNull()&& updobj["clientDefInfo"].isString())
			{
				std::string clientInfo = updobj["clientDefInfo"].asString();
				AddLog(LOG_LEV_DEBUG, LOG_FILE, "clientInfo=%s", clientInfo.data());
				//解析出了describe dependMd5  patchMd5 fullMd5 platform 字段
				ParseClientDefJsonInfo(clientInfo, info);
			}

			if (!updobj["version"].isNull()&& updobj["version"].isString())
			{
				info.version = updobj["version"].asString();
			}

			if (!updobj["versionName"].isNull()&& updobj["versionName"].isString())
			{
				info.versionname = updobj["versionName"].asString();
			}

			if (!updobj["files"].isNull()&& updobj["files"].isArray())
			{
				Json::Value filearray = updobj["files"];
				int iSize = filearray.size();
				for ( int nIndex = 0;nIndex < iSize;++ nIndex )  
				{  
					if (filearray[nIndex].isMember("url")&& filearray[nIndex]["url"].isString())  
					{  
						data::PACK_TYPE type = data::PACK_INIT;
						std::string url = filearray[nIndex]["url"].asString();
						if (std::string::npos != url.find(".exe"))
						{
							continue;
						}
						else if (std::string::npos != url.find("patch.mar"))
						{
							type = data::PACK_PATCH;
							info.patchurl = url;
						}
						else if (std::string::npos != url.find("full.mar"))
						{
							type = data::PACK_FULL;
							info.fullurl = url;
						}
						else if (std::string::npos != url.find("dependlib.mar"))
						{
							type = data::PACK_DEPEND;
							info.dependurl = url;
						}
						else{
							info.url = url;
							info.dependurl = url;
							info.patchurl = url;
							Log(LOG_LEV_INFO, LOG_FILE, "unknow update packet,url=%s",url.data());
						}
					}
				}
			}
			//取增量包地址
			info.url = info.patchurl;
		}
		info.ischeckupdate = 1;
		//推送升级通知
	    PushUpdateNotify(info);
	}
	int UpdateControl::IsNeedUpdate(std::string curver, std::string servrver){
		BEGIN;
		int res = 0;
		if (CompareUpdateVer((char*)curver.c_str(), (char*)servrver.c_str()) < 0)
		{
			Log(LOG_LEV_INFO, LOG_FILE, " Need Update,curver=%s,info.version=%s", curver.c_str(), servrver.c_str());
			res = 1;
			goto _exit_;
		}
		Log(LOG_LEV_INFO, LOG_FILE, "Not Need Update,curver=%s,info.version=%s", curver.c_str(), servrver.c_str());
		res = -1;
	_exit_:
		END;
		return res;
	}
	int UpdateControl::CompareUpdateVer(char* szVer1, char* szVer2)
	{
	BEGIN;
		int ret = 0;
		int tmp = 0;  // 可判断版本号是否相同
		data::UpdateVer ver1;
		data::UpdateVer ver2;
		int svnver=0;

		Split(szVer1, ver1);
		Split(szVer2, ver2);

		ret = Compare_Value(ver1.ver1, ver2.ver1);
		if (ret != 0)
		{
			return ret;
		}
		tmp += ++ret;
		ret = Compare_Value(ver1.ver2, ver2.ver2);
		if (ret != 0)
		{
			return ret;
		}
		tmp += ++ret;
		ret = Compare_Value(ver1.ver3, ver2.ver3);
		if (ret != 0)
		{
			return ret;
		}
		tmp += ++ret;

		svnver = atoi(utils::get_client_info(utils::CLIENTINFO_TYPE_SVNVER).c_str());
		AddLog(LOG_LEV_INFO,"APP_SVN_VER=%d,ver2.ver4=%d",svnver,ver2.ver4);
		if (tmp == 3 && ver2.ver4 != 0){
			AddLog(LOG_LEV_INFO,"APP_SVN_VER=%d,ver2.ver4=%d",svnver,ver2.ver4);
			return Compare_Value(svnver,ver2.ver4);
		}
		END;
		return ret;
	}
	int UpdateControl::Compare_Value(int val1, int val2)
	{
	  BEGIN;
		if (val1 > val2)
			return 1;
		else if (val1 < val2)
			return -1;
		else if (val1 == val2)
			return 0;
	   END;
		return 0;
	}
	void UpdateControl::Split(std::string src, data::UpdateVer& Ver)
	{
	   BEGIN;
		std::vector<std::string> verval;
		if (src.empty())return;
		verval = utils::splitWithStl(src,std::string("."));
		if(verval.size()==3)
		{
			Ver.ver1 = atoi(verval.at(0).c_str());
			Ver.ver2 = atoi(verval.at(1).c_str());
			Ver.ver3 = atoi(verval.at(2).c_str());
		}
		else if(verval.size() == 4){
			Ver.ver1 =atoi(verval.at(0).c_str());
			Ver.ver2 =atoi(verval.at(1).c_str());
			Ver.ver3 =atoi(verval.at(2).c_str());
			Ver.ver4 =atoi(verval.at(3).c_str());
		}
	END;
	}
	bool UpdateControl::IsSamePlatForm(std::string& pt){
		bool bret = false;
		std::string platform("");
	#if defined(_WIN32)
		platform = std::string("pc-xp");			 	/* 设备信息, 如pc-window7,an-xiaomei2,ios-iphone4s */
	#elif  defined(__linux__)
		platform = GetLinuxSysInfo();/* 设备信息, 如pc-window7,an-xiaomei2,ios-iphone4s */
	#elif  defined(__APPLE__)
		platform = std::string("pc-osx");/* 设备信息, 如pc-window7,an-xiaomei2,ios-iphone4s */
	#endif
		bret = (platform == pt) ? true : false;
		AddLog(LOG_LEV_INFO,"platform=%s,m_update.platform=%s,bret=%d", platform.data(),pt.data(),bret);
		return bret;
	}
	void UpdateControl::PushUpdateNotify(data::UpdateInfo&info){
		if (nullptr != m_noticecb && IsSamePlatForm(info.platform))
		{
			m_noticecb(info);
		}
	}
	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance(){
		BEGIN;
		IControl* instance = NULL;
		instance = new UpdateControl();
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
