#pragma once
#include <functional>
#include <interface/IControl.h>
#include <vector>
#include <list>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include "data/AuthData.h"
namespace control {
class IAuthControl:public IControl {
public:
		/**
	* \brief ������������״̬
	* @param[out] cb 0��������ϣˣ������������쳣
	*/
	virtual void regNetChangedCb(CFunction< void(int) > cb) = 0;

		/**
	* \brief ���µ�¼ʱ����
	* @param[out] cb  _1 �����ʾ,  _2�û�ID
	*/
	virtual void regReLoginCb(CFunction< void(int, int64) > cb) = 0;

	/***********************************************
	* @brief �û���½�ӿ�
	* @param[in]servername ��������
	* @param[in]username   �û���
	* @param[in]pwd ����
	* @param[out] cb ������ս���ص� _1������Ϣ  _2 �û�Id  _3 �ʺű�����ʣ��ʱ��  _4 ����1102����ʱ����֤��·��
	***********************************************/
	virtual void Login(data::AuthInfo& authInfo,
					   CFunction<void(int, int64, const std::string&)> cb) = 0;

	/***********************************************
	* @brief ��ȡ��¼��Ϣ�ӿ�
	* @return ��¼��Ϣ�ص�����
	***********************************************/
	virtual std::vector<data::AuthInfo> getLoginInfos(void) = 0;

	/***********************************************
	* \brief <U>���õ�½��Ϣ
	* @param[in] ���õĵ�¼��Ϣ
	* @return   ���ý��
	***********************************************/
	virtual void setLoginInfo(data::AuthInfo) = 0;
	
	/***********************************************
	* @brief ��ȡ��ȫ����URL
	* @param[in] server ������ҵ������
	* @param[out] cb ������ս���ص� _1 url
	***********************************************/
	virtual void getSecUrl(const std::string &server,
		CFunction<void(const std::string&)> cb) = 0;

	/***********************************************
	* @brief �ǳ�
	* @param[out] cb ������ս���ص�  _1������Ϣ
	***********************************************/
	virtual void logout(CFunction<void(int)> cb) = 0;

	/***********************************************
	* @brief ע��
	* @param[out] cb ������ս���ص�  _1������Ϣ
	***********************************************/
	virtual void logoff() = 0;

	/***********************************************
	* @brief ȡ����¼
	* @param[in] operateid �����Ӧ��¼������ID
	* @param[out] cb ������ս���ص�  _1������Ϣ
	***********************************************/
	virtual void abortLogin(CFunction<void(int)> cb) = 0;

	/**************************
	 * @brief ��ȡԤ��¼��Ϣ
	 */
	virtual void getLoginExtData(std::list<data::LoginType>& list,std::string ser ) = 0;

	/**
	* \brief ��ȡע����֤��
	* @param[in] server ������
	* @param[in] account ����ע���˺� ������ֻ��˻���ʽΪ��0086********��
	* @param[out] cb ������ս���ص� _1������Ϣ  _2��ʱ
	*/
	virtual void getRegCode(const std::string& server, const std::string &account, CFunction<void(int, int/*��ʱ*/)> cb) = 0;

	/**
	* \brief ע���û�
	* @param[in] regCode ��֤��
	* @param[in] user    �����û���������ʹ����ʵ����
	* @param[in] pwd	 ����ע������
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void signup(const std::string& regCode, const std::string &user, const std::string &pwd, CFunction<void(int,int)> cb) = 0;

	/**
	* \brief ��֤��¼��֤����߻�ȡ��һ����֤��
	* @param[[in] account �����¼�˺�
	* @param[[in] code	 ������֤������ codeΪ�����ȡ��һ����֤��
	* @param[[out] cb ������ս���ص� _1������Ϣ  _2 ��һ����֤ͼƬ
	*/
	virtual void verifyImgCode(const std::string& account, const std::string& code, 
							CFunction<void(int, const std::string&)> cb) = 0;
    /**
	* \brief ��ȡ���븴�Ӷ�
	* @param[in] cb ������ս���ص� _1������Ϣ
	*  _2�������: 
	*	��8λ������С����
	*	��8λ���������λ��ʼ�����δ���:(1������룬0 ��ʾ��ѡ)
	*	1. �Ƿ����������
	*	2. �Ƿ������Сд��ĸ
	*	3. �Ƿ�����д�д��ĸ
	*	4. �Ƿ������Ӣ����ĸ
	*	5. �Ƿ�������ַ�(�����ַ�)
	*	6. �Ƿ�����ע��(1����0������)
	*/
	virtual void getPasswordRule(CFunction<void(int, int)> cb) = 0;

    /**
	* \brief �޸�����
	* @param[in] oldPw ���������
	* @param[in] newPw ����������
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void changePassword(const std::string &oldPw, const std::string &newPw, CFunction<void(int)> cb) = 0;

	/**
	* \brief <U>��������
	*/
	virtual bool setIsRoming(int32 isRoming) = 0;

	/**
	* \brief <U>��ȡ��������
	*/
	virtual bool getIsRoming() = 0;

	/**
	* \brief <U>��ȡ������ip
	*/
	virtual std::string getServerIp() = 0;
};
extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}

