#pragma once
#include <memory>
#include <string>
#include <interface/Exports.h>
#include <interface/Defines.h>
namespace service{
	class IMClient;
}
namespace control{
    class IAuthControl;
	class IEntMgrControl;
	class IChatMgrControl;
	class IUserControl;
	class IAppMgrControl;
	class IGroupMgrControl;
	class IContactMgrControl;
	class IUpdateControl;
	class ISysMsgMgrControl;
	class IControlClient{
public:
	/***********************************************
	* @brief ��ʼ���ͻ���
	* @param[in]appdatadir Ӧ�ó������ݱ���Ŀ¼
	* @RETRUN bool���� true �ɹ� falseʧ��
	***********************************************/
	virtual bool InitClient(std::string& appdatadir)=0;

	/**********************************************
	* \brief    ��ȡͷ�񱣴��Ŀ¼·��
	* @return   ͷ��Ŀ¼·��
	***********************************************/
	virtual std::string headImgPath() = 0;

	/************************************************
	* \brief    ��ȡ���û�������ͼƬ��Ϣ�ı���Ŀ¼·�� 
	* @return   ͼƬ��Ϣ�ı���·�� 
	***********************************************/
	virtual std::string userImgPath() = 0;

	/**************************************************
	* brief     ��ȡ���û���������Ƶ��Ϣ�ı���Ŀ¼·�� 
	* @return   ��Ƶ��Ϣ�ı���Ŀ¼·�� 
	*************************************************/
	virtual std::string userAudioPath() = 0;

	/**************************************************
	* brief <U>��ȡ���û���������Ƶ��Ϣ�ı���Ŀ¼·��
	* @return   ��Ƶ��Ϣ�ı���Ŀ¼·��
	***************************************************/
	virtual std::string userVideoPath() = 0;

	/**************************************************
	* brief    ��ȡ���û�������cacheĿ¼·��
	* @return   �û�������cacheĿ¼·��
	***************************************************/
	virtual std::string userCachePath() = 0;

	/**************************************************
	* brief     ��ȡ���û��������ļ���Ϣ�ı���Ŀ¼·��
	* @return   �ļ���Ϣ�ı���Ŀ¼·��
	***************************************************/
	virtual std::string userFilePath() = 0;

	/***************************************************
	* brief     ��ȡ���û��������ļ��ı���Ŀ¼·��
	* @return   �û�����ı���Ŀ¼·��
	***************************************************/
	virtual std::string userEmotionPath() = 0;

	/***********************************************
	* @brief ��ȡsdk�ͻ���ָ�����
	***********************************************/
	virtual CSharedPtr<service::IMClient> sdkClient() = 0;

   /***********************************************
	* @brief ��ȡ��½ҵ���߼��������
	***********************************************/
    virtual CSharedPtr<IAuthControl> authControl() = 0;

	/***********************************************
	* @brief ��ȡ�û�ģ��������
	***********************************************/
    virtual CSharedPtr<IUserControl> userControl() =0;

	/***********************************************
	* @brief ��ȡ��ҵ����ģ�����
	***********************************************/
    virtual CSharedPtr<IEntMgrControl> entmgrControl() = 0;

	/***********************************************
	* @brief ��ȡ�������ģ�����
	***********************************************/
    virtual CSharedPtr<IChatMgrControl> chatmgrControl() = 0;

	/***********************************************
	* @brief ��ȡӦ�ù���ģ�����
	***********************************************/
    virtual CSharedPtr<IAppMgrControl> appMgrControl() = 0;

	/***********************************************
	* @brief ��ȡȺģ�����
	***********************************************/
    virtual CSharedPtr<IGroupMgrControl> groupmgrControl() = 0;

	/***********************************************
	* @brief ��ȡ����ģ�����
	***********************************************/
	virtual CSharedPtr<IContactMgrControl> contactmgrControl() = 0;

	/***********************************************
	* @brief ��ȡ����ģ�����
	***********************************************/
	virtual CSharedPtr<IUpdateControl> updateControl() = 0;
		/***********************************************
	* @brief ��ȡϵͳ��Ϣģ�����
	***********************************************/
	virtual CSharedPtr<ISysMsgMgrControl> sysMsgControl() = 0;
};
	typedef CSharedPtr<IControlClient> ControlClientPtr;
	CONTROL_EXPORT_API CSharedPtr<IControlClient>getControlClient();
}
