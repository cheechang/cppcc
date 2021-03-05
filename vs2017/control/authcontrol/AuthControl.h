#pragma once
#include <IAuthControl.h>
#include <memory>
#include "ServiceDefine.h"
namespace service{
	class IMClient;
}
namespace control{
	class AuthControl:public IAuthControl{
	public:
		AuthControl(const std::string &strName=std::string("authcontrol"));
		virtual ~AuthControl();
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

	/***********************************************
	* @brief �û���½�ӿ�
	* @param[in]servername ��������
	* @param[in]username   �û���
	* @param[in]pwd ����
	* @param[out] cb������Ϣ�ص�����
	***********************************************/
	virtual void Login(data::AuthInfo& authInfo,
					   CFunction<void(int, int64, const std::string&)> cb);

	/***********************************************
	* @brief �ǳ�
	* @param[out] cb ������ս���ص�  _1������Ϣ
	***********************************************/
	virtual void logout(CFunction<void(int)> cb);

	/***********************************************
	* @brief ע��
	* @param[out] cb ������ս���ص�  _1������Ϣ
	***********************************************/
	virtual void logoff();

	/***********************************************
	* @brief ȡ����¼
	* @param[in] operateid �����Ӧ��¼������ID
	* @param[out] cb ������ս���ص�  _1������Ϣ
	***********************************************/
	virtual void abortLogin(CFunction<void(int)> cb);

	/***********************************************
	* @brief ��ȡ��¼��Ϣ�ӿ�
	* @return ��¼��Ϣ
	***********************************************/
	virtual std::vector<data::AuthInfo> getLoginInfos(void);

	/***********************************************
	* \brief <U>���õ�½��Ϣ
	* @param[in] ���õĵ�¼��Ϣ
	* @return   ���ý��
	***********************************************/
	virtual void setLoginInfo(data::AuthInfo info);
	
	/***********************************************
	* @brief ��ȡ��ȫ����URL
	* @param[in] server ������ҵ������
	* @param[out] cb ������ս���ص� _1 url
	***********************************************/
	virtual void getSecUrl(const std::string &server,
		CFunction<void(const std::string&)> cb);

	/* \brief ������������״̬
	* @param[out] cb 0��������ϣˣ������������쳣
	*/
	virtual void regNetChangedCb(CFunction< void(int) > cb);

		/**
	* \brief ���µ�¼ʱ����
	* @param[out] cb  _1 �����ʾ,  _2�û�ID
	*/
	virtual void regReLoginCb(CFunction< void(int, int64) > cb);


	/**************************
	 * @brief ��ȡԤ��¼��Ϣ
	 * @param[in out] ��ȡ�����б�   
	 * @parma[in] ������
	 */
	virtual void getLoginExtData(std::list<data::LoginType>& list,std::string server);

		/**
	* \brief ��ȡע����֤��
	* @param[in] server ������
	* @param[in] account ����ע���˺� ������ֻ��˻���ʽΪ��0086********��
	* @param[out] cb ������ս���ص� _1������Ϣ  _2��ʱ
	*/
	virtual void getRegCode(const std::string& server, const std::string &account, CFunction<void(int, int/*��ʱ*/)> cb);
	
		/**
	* \brief ע���û�
	* @param[in] regCode ��֤��
	* @param[in] user    �����û���������ʹ����ʵ����
	* @param[in] pwd	 ����ע������
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void signup(const std::string& regCode, const std::string &user, const std::string &pwd, CFunction<void(int,int)> cb);
	
		/**
	* \brief ��֤��¼��֤����߻�ȡ��һ����֤��
	* @param[[in] account �����¼�˺�
	* @param[[in] code	 ������֤������ codeΪ�����ȡ��һ����֤��
	* @param[[out] cb ������ս���ص� _1������Ϣ  _2 ��һ����֤ͼƬ
	*/
	virtual void verifyImgCode(const std::string& account, const std::string& code, 
							CFunction<void(int, const std::string&)> cb);

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
	virtual void getPasswordRule(CFunction<void(int, int)> cb);

        /**
	* \brief �޸�����
	* @param[in] oldPw ���������
	* @param[in] newPw ����������
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void changePassword(const std::string &oldPw, const std::string &newPw, CFunction<void(int)> cb);

	/**
	* \brief <U>��������
	*/
	virtual bool setIsRoming(int32 isRoming);

	/**
	* \brief <U>��ȡ��������
	*/
	virtual bool getIsRoming();

	/**
	* \brief <U>��ȡ������ip
	*/
	virtual std::string getServerIp();
protected:
	   void onLogout(int err);
	   void onAbortLogin(int err);
	   void onLoginRet(int err, int64 userid, int64 locktime,
		   const std::string& verifypng, const data::AuthInfo authInfo);
	   void onGetSecUrl(int err, const std::string& url);
       void onUserInfoRet(model::Account& user, data::AuthInfo info);
	protected:
		void setAutoLogin(bool isreset=false);
	private:
		std::string m_pluginname; //�������������׺�ģ�
		IAuthService_Ptr m_authservice;
		IConfigService_Ptr m_configservice;
		IUserService_Ptr m_userservice;
		int64 m_iOperateid;
		int64 m_userid;
		std::string m_serverIp;
		CFunction<void(const int)> m_funcLogoutCB;
		CFunction<void(const int)> m_funcAbortLoginCB;
		CFunction<void(int, int64, const std::string&)> m_funcLoginReturnCB;
		CFunction<void(const std::string&)> m_funcGetSecUrlCB;
	};
}