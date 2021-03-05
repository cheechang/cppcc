#pragma once

#include "interface/Defines.h"
#include <string>


namespace data{
	class AppInfo {
	public:
		AppInfo() : appID(0), name(""), icon(""), introduction(""), url("")
			, isInstalled(false) 
		{}
		virtual ~AppInfo() {}
	public:
		int64 appID;				///<app id
		std::string name;			///<app����
		std::string icon;			///<appͼ��
		std::string introduction;	///<app���
		std::string url;			///<app��ַ
		bool isInstalled;			///<�Ƿ��Ѱ�װ
	};
};