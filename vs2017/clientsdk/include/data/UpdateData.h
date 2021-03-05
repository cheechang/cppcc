#pragma once
#include <string>
#include <vector>
#include "interface/Defines.h"
namespace data{
	enum PACK_TYPE{
		PACK_INIT = 0,
		PACK_SETUP,
		PACK_PATCH,
		PACK_FULL,
		PACK_DEPEND
	};
	enum UPDATE_TYPE{
		NONEED_UPDATE=-1,
		ADVICE_UPDATE,
		FORCE_UPDATE,
	};
	//升级信息
	class UpdateInfo
	{
	public:
		UpdateInfo(void):ischeckupdate(0), force(0), url(""), fullurl(""),patchurl(""), dependurl(""), version(""), versionname(""), platform(""), svnVersion(""),
		md5(""),fullMd5(""),patchMd5(""),dependMd5(""),systemDbMd5(""),desc(""){
			info.clear();
			vip.clear();
		}
		int ischeckupdate;					//	1标示是检查更新触发
		int force;							//	0建议升级 1强制升级 
		std::string url;					//	更新包链接
		std::string fullurl;				//	全量包url
		std::string patchurl;				//	增量包链接
		std::string dependurl;				//	依赖库包链接
		std::string version;				//	升级版本 V0.2.2
		std::string versionname;			//  升级版本名称
		std::string platform;				//  平台信息
		std::string svnVersion;				//  svn版本号
		std::string md5;					//  mar包的md5值
		std::string fullMd5;				//  全量mar包md5
		std::string patchMd5;				//  增量mar包md5
		std::string dependMd5;				//  依赖mar包md5
		std::string systemDbMd5;		    //  库的md5值
		std::string desc;					//  描述信息
		std::vector<std::string> info;		//	升级信息，多条以;分隔
		std::vector<std::string> vip;	    //	mac地址列表
	};
	class UpdateVer
	{
	public:
		UpdateVer(void) :ver1(0), ver2(0), ver3(0), ver4(0){}
		int ver1;
		int ver2;
		int ver3;
		int ver4;
	};

}