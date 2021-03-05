#include "AuthControl.h"
#include "interface/IMClient.h"
#include "IControl.h"
#include "log.h"
#include "../utils/Error.h"
#include "../utils/common.h"
#include "../utils/functionconfig.h"
#include <json.h>
#include <time.h>
#include <sstream>
const char * filename = 0;
int line = 0;

namespace control{
  service::IMClient* g_client =CNull;
  AuthControl::AuthControl(const std::string &strName)
	  : m_pluginname(strName)
	  , m_authservice(CNull)
	  , m_configservice(CNull)
	  , m_userservice(CNull)
	  , m_iOperateid(0)
  {
BEGIN;
END;
  }
  AuthControl::~AuthControl(){
BEGIN;
END;
  }
	/***********************************************
	* @brief ���ش���׺�Ĳ����
	* @param[in]��
	***********************************************/
    std::string AuthControl::GetName(){
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
		return result;
	}
	/***********************************************
	* @brief ���ز�����׺�Ĳ����
	* @param[in]��
	***********************************************/
    std::string AuthControl::GetDisplayName(){
		return m_pluginname;
	}
	/***********************************************
	* @brief ����sdk�ͻ���ʵ������
	* @param[in]��
	***********************************************/
    void AuthControl::SetSdkClientObj(void* obj){
BEGIN;
		g_client =static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK�ͻ��˶���ָ��ʧ��");
			return;
		}
		AddLog(LOG_LEV_INFO, "test-test:SDK�ͻ��˶���ָ��ok");
		m_authservice = AUTHSERVICE;
		m_configservice = CONFIGSERVICE;
		m_userservice = USERSERVICE;
		m_configservice->setMsgParserMode(true);
END;
	}
	/***********************************************
	* @brief �û���½�ӿ�
	* @param[in]servername ��������
	* @param[in]username   �û���
	* @param[in]pwd ����
	* @param[out] cb������Ϣ�ص�����
	***********************************************/
	void AuthControl::Login(data::AuthInfo& authInfo,
					   CFunction<void(int, int64, const std::string&)> cb)
	{
		BEGIN;
		AddLog(LOG_LEV_INFO, "server = %s, nation = %s, phone = %s,\
							 isAutoLogin = %d, isRemberPass = %d",
			authInfo.server.c_str(), authInfo.nation.c_str(),
			authInfo.account.c_str(), authInfo.isAutoLogin, authInfo.isRemberPwd);

		   m_funcLoginReturnCB = cb;
           std::string login = authInfo.account;
           if (authInfo.curType == 1)
           {
               login.insert(0,authInfo.nation);
           }
           
           std::stringstream stream;  
           stream << authInfo.curType;  
           login.append(":");
           login.append(stream.str());

		   m_iOperateid = m_authservice->login(login,
			   authInfo.pwd, authInfo.server,
			   CBind(&AuthControl::onLoginRet, this, CPlaceholders  _1,
			   CPlaceholders  _2, CPlaceholders  _3,
			   CPlaceholders  _4, authInfo));
		END;
	}

	void AuthControl::onLoginRet(int err, int64 userid, int64 locktime, 
		const std::string& verifypng, const data::AuthInfo authInfo)
	{
		BEGIN;
		AddLog(LOG_LEV_INFO, "err=%d, userid=%d", err, userid);

		m_iOperateid = 0;

		utils::Error::InitErrInfo(true);
		std::string strErr = utils::Error::GetErrMsg(err);
		m_funcLoginReturnCB(err, userid, strErr);
		
		// ���õ�¼��Ϣ
		if (err == 0)
		{
			m_userid = userid;
			if (m_userservice != CNull)
			{
                m_userservice->regGetMyselfCb(CBind(&AuthControl::onUserInfoRet,this,CPlaceholders _1, authInfo));
			}
		}
		END;
	}

	/***********************************************
	* @brief �ǳ�
	* @param[out] cb ������ս���ص�  _1������Ϣ
	***********************************************/
	void AuthControl::logout(CFunction<void(int)> cb)
	{
		BEGIN;
		m_funcLogoutCB = cb;
		setAutoLogin(true);
		m_authservice->logout(
			CBind(&AuthControl::onLogout, this,
			CPlaceholders  _1));
		END;
	}

	void AuthControl::onLogout(int err)
	{
		BEGIN;
		AddLog(LOG_LEV_INFO, "err = %d", err);
		m_funcLogoutCB(err);
		END;
	}
	
	/***********************************************
	* @brief ע��
	* @param[out] cb ������ս���ص�  _1������Ϣ
	***********************************************/
    void AuthControl::logoff(){
	  BEGIN;
	    setAutoLogin();
	  END;
	}

	/***********************************************
	* @brief ȡ����¼
	* @param[in] operateid �����Ӧ��¼������ID
	* @param[out] cb ������ս���ص�  _1������Ϣ
	***********************************************/
	void AuthControl::abortLogin(CFunction<void(int)> cb)
	{
		BEGIN;
		m_funcAbortLoginCB = cb;
		m_authservice->abortLogin(m_iOperateid,
			CBind(&AuthControl::onAbortLogin, this, CPlaceholders  _1));
		END;
	}

	void AuthControl::onAbortLogin(int err)
	{
		BEGIN;
		AddLog(LOG_LEV_INFO, "err = %d", err);
		m_funcAbortLoginCB(err);
		END;
	}

	/***********************************************
	* @brief ��ȡ��¼��Ϣ�ӿ�
	* @param[out] cb ��¼��Ϣ�ص�����
	***********************************************/
	std::vector<data::AuthInfo> AuthControl::getLoginInfos()
	{
		BEGIN;

		std::vector<data::AuthInfo> authInfos;
		std::vector<LoginInfo> loginInfos = m_configservice->getLoginInfos();
		for (int i = 0; i < loginInfos.size(); i++)
		{
			AddLog(LOG_LEV_INFO, "userid = %lld, server = %s, name = %s,\
								 avatar = %s, nation = %s, phone = %s,\
								 isAutoLogin = %d, isRemberPass = %d",
				loginInfos[i].userId, loginInfos[i].server.c_str(),
				loginInfos[i].name.c_str(), loginInfos[i].user_icon.c_str(),
				loginInfos[i].nation.c_str(), loginInfos[i].phone.c_str(),
				loginInfos[i].isAutoLogin, loginInfos[i].isRemberPass);

			data::AuthInfo info;
			info.isAutoLogin = loginInfos[i].isAutoLogin == 1 ? true : false;
			info.isRemberPwd = loginInfos[i].isRemberPass == 1 ? true : false;
			info.userId = loginInfos[i].userId;
			info.server = loginInfos[i].server;
			info.name = loginInfos[i].name;
			info.pwd = loginInfos[i].pwd;
			info.avatar = utils::GetHeadPath(1,loginInfos[i].user_icon);
			info.nation = loginInfos[i].nation;
			info.phone = loginInfos[i].phone;
            info.email = loginInfos[i].email;
            info.account = loginInfos[i].account;
            info.curType = loginInfos[i].userType;

			authInfos.push_back(info);
		}
		return authInfos;

		END;
	}

	void AuthControl::setLoginInfo(data::AuthInfo info)
	{
		BEGIN;
		// ���õ�¼��Ϣ
		//std::vector<model::LoginInfo> infos = m_configservice->getLoginInfos();
		/*model::LoginInfo currentUser;
		for (size_t index=0; index<infos.size();++index)
		{
			if (infos[index].userId == m_userid )
			{
				currentUser = infos[index];
				break;
			}
		}
		time_t t = time(CNull);
		currentUser.last_login_time = t;
		if (!info.avatar.empty())
		{
			currentUser.user_icon = info.avatar;
			AddLog(LOG_LEV_DEBUG, "avatar path:%s",currentUser.user_icon.c_str());
		}
		else
		{
			AddLog(LOG_LEV_WARN, "avatar had not been set");
		}*/

		model::LoginInfo currentUser;
		currentUser.account = info.account;
		currentUser.email = info.email;
		currentUser.isAutoLogin = info.isAutoLogin;
		currentUser.isRemberPass = info.isRemberPwd;
		currentUser.name = info.name;
		currentUser.nation = info.nation;
		currentUser.phone = info.phone;
		currentUser.pwd = info.pwd;
		currentUser.server = info.server;
		currentUser.userId = info.userId;
		currentUser.userType = info.curType;

		time_t t = time(CNull);
		currentUser.last_login_time = t;
		if (!info.avatar.empty())
		{
			currentUser.user_icon = info.avatar;
			AddLog(LOG_LEV_DEBUG, "avatar path:%s", currentUser.user_icon.c_str());
		}
		else
		{
			AddLog(LOG_LEV_WARN, "avatar had not been set");
		}

		bool ret = m_configservice->setLoginInfo(currentUser);
		AddLog(LOG_LEV_INFO, "setLoginInfo ret = %d", ret);
		END;
	}

	/***********************************************
	* @brief ��ȡ��ȫ����URL
	* @param[in] server ������ҵ������
	* @param[out] cb ������ս���ص� _1 url
	***********************************************/
	void AuthControl::getSecUrl(const std::string &server,
		CFunction<void(const std::string&)> cb)
	{
		BEGIN;
		AddLog(LOG_LEV_INFO, "server=%s", server.c_str());
		m_funcGetSecUrlCB = cb;
		m_authservice->getSecUrl(server, CBind(&AuthControl::onGetSecUrl,
			this, CPlaceholders  _1, CPlaceholders  _2));
		END;
	}

	void AuthControl::onGetSecUrl(int err, const std::string& url)
	{
		BEGIN;
		AddLog(LOG_LEV_INFO, "err=%d, url=%s", err, url);
		if (err == 0)
		{
			m_funcGetSecUrlCB(url);
		}
		END;
	}
	void AuthControl::setAutoLogin(bool isreset){
		// ��ȡһ����ʷ��¼
		// �����µĵ�¼��Ϣ����Ϊȡ���Զ���¼
		std::vector<model::LoginInfo> infos = m_configservice->getLoginInfos();
		model::LoginInfo currentUser;
		for (size_t index=0; index<infos.size();++index)
		{
			if (infos[index].userId == m_userid )
			{
				currentUser = infos[index];
				break;
			}
		}
		AddLog(LOG_LEV_DEBUG,"[m_userid=%lld  currentUser.account = %s currentUser.userId = %lld]", m_userid,currentUser.account.c_str(),currentUser.userId);
		if (infos.empty()){
			return;
		}
		if (isreset){
			if ( 3 == currentUser.isAutoLogin )
			{
				currentUser.isAutoLogin = 1;
			}
		}
		else{
			if ( 1 == currentUser.isAutoLogin )
			{
				currentUser.isAutoLogin = 3;
			}
		}
		currentUser.last_login_time = time(CNull);
		m_configservice->setLoginInfo(currentUser);
	}

	void AuthControl::regNetChangedCb( CFunction< void(int) > cb )
	{
		m_authservice->regNetChangedCb(cb);
	}

	void AuthControl::regReLoginCb( CFunction< void(int, int64) > cb )
	{
		m_authservice->regReLoginCb(cb);
	}

	

	void AuthControl::getRegCode( const std::string& server, const std::string &account, CFunction<void(int, int/*��ʱ*/)> cb )
	{
		 if (m_authservice)
		 {
			 m_authservice->getRegCode(server,account,cb);
		 }
	}

	void AuthControl::signup( const std::string& regCode, const std::string &user, const std::string &pwd, CFunction<void(int,int)> cb )
	{
		  if (m_authservice)
		  {
			  m_authservice->signup(regCode,user,pwd,cb);
		  }
	}

	void AuthControl::getLoginExtData(std::list<data::LoginType>& list, std::string  server)
	{
		AddLog(LOG_LEV_INFO, "test-history:flag0");
		//LOG_METHOD("GetDefaultServerTypeFromServer", LOG_FILE);
		std::vector<LoginInfo> loginHis;
		std::string  historyServer = server;

		std::shared_ptr<service::IConfigService> configSer = CONFIGSERVICE;
		loginHis = configSer->getLoginInfos();

		if (loginHis.size() > 0)
		{
			historyServer = loginHis.at(0).server;
		}

		std::string stdExt = m_configservice->getLoginExData(historyServer);
		char  extData[1600] = {};

		int len = utils::utf82char(stdExt.data(), extData);
		//�����ɼ����ֶ�
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(extData, root);
		if (!ret)
		{
			AddLog(LOG_LEV_ERROR, "json parse filed,json len =%d", len);
			return;
		}

		Json::Value jsAccount = root["accounts"];


		if (jsAccount.isArray())
		{
			int nArraySize = jsAccount.size();
			for (int i = 0; i<nArraySize; i++)
			{
				data::LoginType tmp;
				Json::Value elmet = jsAccount[i];

				Json::Value::Members members(elmet.getMemberNames());
				for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
				{
					std::string key = *it;
					tmp.type_name = elmet[key].asString();
					tmp.type_num = atoi(key.data());
				}

				list.push_back(tmp);
			}
		}

		Json::Value jsObject = root["Serverhost"];
		AddLog(LOG_LEV_INFO, "test-history:serverhost");
		if (jsObject.isObject())
		{
			AddLog(LOG_LEV_INFO, "test-history:flag1");
			if (jsObject["OutterIP"].isString())
			{

				m_serverIp = jsObject["OutterIP"].asString();
				AddLog(LOG_LEV_INFO, "test-history:OutterIP=", m_serverIp);
			}
		}
	}

	/**
	* \brief <U>��ȡ������ip
	*/
	std::string AuthControl::getServerIp()
	{
		return m_serverIp;
	}

	void AuthControl::verifyImgCode( const std::string& account, const std::string& code, CFunction<void(int, const std::string&)> cb )
	{
		if (m_authservice)
		{
			m_authservice->verifyImgCode(account,code,cb);
		}
	}

    void AuthControl::getPasswordRule( CFunction<void(int, int)> cb )
    {
        if (m_authservice)
        {
            m_authservice->getPasswordRule(cb);
        }
    }

    void AuthControl::changePassword( const std::string &oldPw, const std::string &newPw, CFunction<void(int)> cb )
    {
        if (m_authservice)
        {
            m_authservice->changePassword(oldPw,newPw,cb);
        }
    }

    void AuthControl::onUserInfoRet( model::Account& user, data::AuthInfo auth)
    {
        BEGIN;
        model::LoginInfo info;
        info.isRemberPass = auth.isRemberPwd ? 1 : 0;
        info.isAutoLogin = auth.isAutoLogin ? 1 : 0;
        info.userId = user.id.value();
        info.server = auth.server;
        info.pwd = auth.pwd;
        info.nation = auth.nation;
        info.userType = auth.curType;

        time_t t = time(CNull);
        info.last_login_time = t;
        
        if (user.name.isSet())
        {
            info.name = user.name.value();
        }
        else
        {
            AddLog(LOG_LEV_WARN, "name had not been set");
        }

        if (user.avatar.isSet())
        {
            info.user_icon = user.avatar.value();
        }
        else
        {
            AddLog(LOG_LEV_WARN, "avatar had not been set");
        }

        if (user.nickId.isSet())
        {
            info.account = user.nickId.value();
        }
        else
        {
            AddLog(LOG_LEV_WARN, "nickId had not been set");
        }

        if (user.email.isSet())
        {
            info.email = user.email.value();
        }
        else
        {
            AddLog(LOG_LEV_WARN, "account.email had not been set");
        }

        if (user.phone.isSet())
        {
            std::string substr = user.phone.value();
            info.phone = substr.replace(0,auth.nation.length(),"");
        }
        else
        {
            AddLog(LOG_LEV_WARN, "account.phone had not been set");
        }


        bool ret = m_configservice->setLoginInfo(info);
        AddLog(LOG_LEV_INFO, "setLoginInfo ret = %d", ret);

    }

		/**
	* \brief <U>��������
	*/
	bool AuthControl::setIsRoming(int32 isRoming)
	{
		if(m_configservice)
		{
			return m_configservice->setIsRoming(isRoming);
		}

		return false;
	}

	
	/**
	* \brief <U>��ȡ��������
	*/
	bool AuthControl::getIsRoming()
	{
		if(m_configservice)
		{
			return m_configservice->getIsRoming();
		}
		return false;
	}

	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance(){
		IControl* instance = NULL;
		instance = new AuthControl();
		return  instance;
	}

    extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance){
		if(NULL != instance){
			delete instance;
			instance = NULL;
		}
	}
}