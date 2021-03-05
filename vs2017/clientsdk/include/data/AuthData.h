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
		bool isRemberPwd;	///<�Ƿ��ס����
		bool isAutoLogin;	///<�Զ���¼
		
		std::string server;	///<������
		std::string name;	///<�û���
		std::string pwd;	///<����
		std::string avatar;	///<ͷ��
		std::string nation;	///<������
		std::string account;///��¼�˺�(nickID)
        int   curType;
        int64 userId;		///<�û�id
        std::string phone;					///<�󶨵��ֻ�
        std::string email;					///<�󶨵�����
		std::string VerifyNum;         ///��֤��
	};

	struct LoginType{
		int type_num;
		std::string type_name;
	};
};