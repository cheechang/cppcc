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
		* @brief ����������Ϣ����
		* @param[out] update ������Ϣ�ṹ�� 
		******************************************************************/
		virtual void RegUpdateInfoNotice(CFunction<void(data::UpdateInfo&update)>cb) = 0;

		/******************************************************************
		* @brief �������������ݴ��Ŀ¼
		* @param[in] dirpath �������ݱ���Ŀ¼·��
		******************************************************************/
		virtual void SetUpdateDataDir(std::string&dirpath)=0;

		/******************************************************************
		* @brief ������
		* @param[in] url     ������Ϣ�����ص�ַ
		******************************************************************/
		virtual void CheckUpdate(std::string&url)=0;

		/******************************************************************
		* @brief ���߼�����
		* @param[in] servername  ��������
		******************************************************************/
		virtual int CheckUpdateOnline(std::string&servername)=0;

		/******************************************************************
		* @brief �����������ӿ�
		* @param[in] localpath  ����������·��
		* @param[in] url  ������url��ַ
		* @param[out] cb  ����ֵ
		* @param[out] pro ���ؽ������ͻص�
		* @return ÿ���ļ���Ӧ��ΨһlocalID
		******************************************************************/
		virtual int64 DownLoadUpdateFile(std::string&localpath,std::string&url,CFunction<void(int)>cb,CFunction<void(int32, int32, const std::string&)>pro=CNull)=0;

		/******************************************************************
		* @brief ȡ�������������ӿ�
		* @param[in] localpath  ����������·��
		* @return ÿ���ļ���Ӧ��ΨһlocalID
		******************************************************************/
		virtual void CancelDownLoadUpdateFile(int64 filelocalid,CFunction<void(int)>cb)=0;
	};
	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}