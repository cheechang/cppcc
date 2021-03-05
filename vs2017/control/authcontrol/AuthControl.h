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
	* @brief 返回带后缀的插件名
	* @param[in]无
	***********************************************/
    virtual std::string GetName();
	/***********************************************
	* @brief 返回不带后缀的插件名
	* @param[in]无
	***********************************************/
    virtual std::string GetDisplayName();

	/***********************************************
	* @brief 设置sdk客户端实例对象
	* @param[in]无
	***********************************************/
    virtual void SetSdkClientObj(void* obj);

	/***********************************************
	* @brief 用户登陆接口
	* @param[in]servername 服务器名
	* @param[in]username   用户名
	* @param[in]pwd 密码
	* @param[out] cb错误信息回调函数
	***********************************************/
	virtual void Login(data::AuthInfo& authInfo,
					   CFunction<void(int, int64, const std::string&)> cb);

	/***********************************************
	* @brief 登出
	* @param[out] cb 传入接收结果回调  _1错误信息
	***********************************************/
	virtual void logout(CFunction<void(int)> cb);

	/***********************************************
	* @brief 注销
	* @param[out] cb 传入接收结果回调  _1错误信息
	***********************************************/
	virtual void logoff();

	/***********************************************
	* @brief 取消登录
	* @param[in] operateid 传入对应登录操作的ID
	* @param[out] cb 传入接收结果回调  _1错误信息
	***********************************************/
	virtual void abortLogin(CFunction<void(int)> cb);

	/***********************************************
	* @brief 获取登录信息接口
	* @return 登录信息
	***********************************************/
	virtual std::vector<data::AuthInfo> getLoginInfos(void);

	/***********************************************
	* \brief <U>设置登陆信息
	* @param[in] 设置的登录信息
	* @return   设置结果
	***********************************************/
	virtual void setLoginInfo(data::AuthInfo info);
	
	/***********************************************
	* @brief 获取安全中心URL
	* @param[in] server 传入企业服务器
	* @param[out] cb 传入接收结果回调 _1 url
	***********************************************/
	virtual void getSecUrl(const std::string &server,
		CFunction<void(const std::string&)> cb);

	/* \brief 监听网络连接状态
	* @param[out] cb 0代表网络ＯＫ，非零是网络异常
	*/
	virtual void regNetChangedCb(CFunction< void(int) > cb);

		/**
	* \brief 重新登录时推送
	* @param[out] cb  _1 错误标示,  _2用户ID
	*/
	virtual void regReLoginCb(CFunction< void(int, int64) > cb);


	/**************************
	 * @brief 获取预登录信息
	 * @param[in out] 获取类型列表，   
	 * @parma[in] 服务器
	 */
	virtual void getLoginExtData(std::list<data::LoginType>& list,std::string server);

		/**
	* \brief 获取注册验证码
	* @param[in] server 服务器
	* @param[in] account 传入注册账号 如果是手机账户格式为“0086********”
	* @param[out] cb 传入接收结果回调 _1错误信息  _2超时
	*/
	virtual void getRegCode(const std::string& server, const std::string &account, CFunction<void(int, int/*超时*/)> cb);
	
		/**
	* \brief 注册用户
	* @param[in] regCode 验证码
	* @param[in] user    传入用户名，建议使用真实姓名
	* @param[in] pwd	 传入注册密码
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void signup(const std::string& regCode, const std::string &user, const std::string &pwd, CFunction<void(int,int)> cb);
	
		/**
	* \brief 验证登录验证码或者获取下一张验证码
	* @param[[in] account 传入登录账号
	* @param[[in] code	 传入验证码内容 code为空则获取下一张验证码
	* @param[[out] cb 传入接收结果回调 _1错误信息  _2 下一张验证图片
	*/
	virtual void verifyImgCode(const std::string& account, const std::string& code, 
							CFunction<void(int, const std::string&)> cb);

   /**
	* \brief 获取密码复杂度
	* @param[in] cb 传入接收结果回调 _1错误信息
	*  _2密码规则: 
	*	高8位代表最小长度
	*	低8位，按照最低位开始，依次代表:(1代表必须，0 表示可选)
	*	1. 是否必须有数字
	*	2. 是否必须有小写字母
	*	3. 是否必须有大写字母
	*	4. 是否必须有英文字母
	*	5. 是否必须有字符(特殊字符)
	*	6. 是否允许注册(1允许，0不允许)
	*/
	virtual void getPasswordRule(CFunction<void(int, int)> cb);

        /**
	* \brief 修改密码
	* @param[in] oldPw 传入旧密码
	* @param[in] newPw 传入新密码
	* @param[out] cb 传入接收结果回调  _1错误信息
	*/
	virtual void changePassword(const std::string &oldPw, const std::string &newPw, CFunction<void(int)> cb);

	/**
	* \brief <U>设置漫游
	*/
	virtual bool setIsRoming(int32 isRoming);

	/**
	* \brief <U>获取漫游设置
	*/
	virtual bool getIsRoming();

	/**
	* \brief <U>获取服务器ip
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
		std::string m_pluginname; //插件名（不带后缀的）
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