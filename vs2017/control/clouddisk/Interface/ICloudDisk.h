#pragma once
#include "Exports.h"
#include <string>
#ifdef _WIN32
   #include <Windows.h>
#endif
class ICloudDisk{
public:
	/**********************************************
	* @brief ��ʼ������ģ��
	* @param[in] serviceclient sdk�����ͻ���ָ�����
	***********************************************/
	virtual void InitCloudDisk(void*serviceclient, void* appInstance) = 0;
#ifdef _WIN32

	/**********************************************
	* @brief ��ʾ����UI
	* @param[in] parent ���븸���ھ��
	***********************************************/
	virtual void ShowCloudDisk(HWND parent) = 0;

	/**********************************************
	* @brief ��ʾ����ѡ���ϴ�Ŀ¼����
	* @param[in] parent ���븸���ھ��
	* @param[in] encrptkey ������Կ
	* @param[in] filePath �����ļ�·��
	***********************************************/
	virtual void ShowSelectUploadDirWnd(HWND parent, std::string&encrptkey,std::string&filePath) = 0;
#endif
};
extern "C" CLOUDDISK_EXPORT_API ICloudDisk* GetInstance();
extern "C" CLOUDDISK_EXPORT_API void        ReleaseInstance(ICloudDisk* obj);