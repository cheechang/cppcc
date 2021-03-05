#pragma once
#include <interface/IControl.h>
#include "interface/Exports.h"
#include "data/UpdateData.h"
namespace data{
	class UpdateInfo;
}
namespace control{
	class IUpdateControl:public IControl{
	public:
		/******************************************************************
		* @brief 设置升级信息推送
		* @param[out] update 升级信息结构体 
		******************************************************************/
		virtual void RegUpdateInfoNotice(CFunction<void(data::UpdateInfo&update)>cb) = 0;

		/******************************************************************
		* @brief 设置升级包数据存放目录
		* @param[in] dirpath 升级数据保存目录路径
		******************************************************************/
		virtual void SetUpdateDataDir(std::string&dirpath)=0;

		/******************************************************************
		* @brief 检查更新
		* @param[in] url     更新信息的下载地址
		******************************************************************/
		virtual void CheckUpdate(std::string&url)=0;

		/******************************************************************
		* @brief 在线检查更新
		* @param[in] servername  服务器名
		******************************************************************/
		virtual int CheckUpdateOnline(std::string&servername)=0;

		/******************************************************************
		* @brief 下载升级包接口
		* @param[in] localpath  升级包保存路径
		* @param[in] url  升级包url地址
		* @param[out] cb  错误值
		* @param[out] pro 下载进度推送回调
		* @return 每个文件对应的唯一localID
		******************************************************************/
		virtual int64 DownLoadUpdateFile(std::string&localpath,std::string&url,CFunction<void(int)>cb,CFunction<void(int32, int32, const std::string&)>pro=CNull)=0;

		/******************************************************************
		* @brief 取消下载升级包接口
		* @param[in] localpath  升级包保存路径
		* @return 每个文件对应的唯一localID
		******************************************************************/
		virtual void CancelDownLoadUpdateFile(int64 filelocalid,CFunction<void(int)>cb)=0;
	};
	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}