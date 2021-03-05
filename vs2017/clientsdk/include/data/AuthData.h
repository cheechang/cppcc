#pragma once

#include "interface/Defines.h"
#include <string>
#include "data/Optional.h"


namespace data{
	class AuthInfo {
	public:
		AuthInfo() : isRemberPwd(false), isAutoLogin(false), userId(0)
			, server(""), name(""), pwd(""), avatar(""), nation(""), account(""),curType(1)
		{}
		virtual ~AuthInfo() {}
	public:
		bool isRemberPwd;	///<是否记住密码
		bool isAutoLogin;	///<自动登录
		
		std::string server;	///<服务器
		std::string name;	///<用户名
		std::string pwd;	///<密码
		std::string avatar;	///<头像
		std::string nation;	///<国家码
		std::string account;///登录账号(nickID)
        int   curType;
        int64 userId;		///<用户id
        std::string phone;					///<绑定的手机
        std::string email;					///<绑定的邮箱
		std::string VerifyNum;         ///验证码
	};

	struct LoginType{
		int type_num;
		std::string type_name;
	};
};