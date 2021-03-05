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
		std::string name;			///<app名称
		std::string icon;			///<app图标
		std::string introduction;	///<app简介
		std::string url;			///<app地址
		bool isInstalled;			///<是否已安装
	};
};