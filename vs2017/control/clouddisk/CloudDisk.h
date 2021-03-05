#pragma once
#include "Interface/ICloudDisk.h"
#include <memory>
namespace ui{
	class CloudDiskWidget;
}
class CloudDisk :public ICloudDisk{
public:
	CloudDisk();
	~CloudDisk();
	/**********************************************
	* @brief 初始化云盘模块
	* @param[in] serviceclient sdk服务层客户端指针对象
	***********************************************/
	virtual void InitCloudDisk(void*serviceclient,void* appInstance);
#ifdef _WIN32

	/**********************************************
	* @brief 显示云盘UI
	* @param[in] parent 传入父窗口句柄
	***********************************************/
	virtual void ShowCloudDisk(HWND parent);


	/**********************************************
	* @brief 显示云盘选择上传目录窗口
	* @param[in] parent 传入父窗口句柄
	* @param[in] encrptkey 加密密钥
	* @param[in] filePath 传入文件路径
	***********************************************/
	virtual void ShowSelectUploadDirWnd(HWND parent, std::string&encrptkey, std::string&filePath);
#endif
private:
	std::shared_ptr<ui::CloudDiskWidget> m_diskwnd;
};