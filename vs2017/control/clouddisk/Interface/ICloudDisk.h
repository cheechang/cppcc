#pragma once
#include "Exports.h"
#include <string>
#ifdef _WIN32
   #include <Windows.h>
#endif
class ICloudDisk{
public:
	/**********************************************
	* @brief 初始化云盘模块
	* @param[in] serviceclient sdk服务层客户端指针对象
	***********************************************/
	virtual void InitCloudDisk(void*serviceclient, void* appInstance) = 0;
#ifdef _WIN32

	/**********************************************
	* @brief 显示云盘UI
	* @param[in] parent 传入父窗口句柄
	***********************************************/
	virtual void ShowCloudDisk(HWND parent) = 0;

	/**********************************************
	* @brief 显示云盘选择上传目录窗口
	* @param[in] parent 传入父窗口句柄
	* @param[in] encrptkey 加密密钥
	* @param[in] filePath 传入文件路径
	***********************************************/
	virtual void ShowSelectUploadDirWnd(HWND parent, std::string&encrptkey,std::string&filePath) = 0;
#endif
};
extern "C" CLOUDDISK_EXPORT_API ICloudDisk* GetInstance();
extern "C" CLOUDDISK_EXPORT_API void        ReleaseInstance(ICloudDisk* obj);