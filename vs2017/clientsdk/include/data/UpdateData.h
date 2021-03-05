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
	//������Ϣ
	class UpdateInfo
	{
	public:
		UpdateInfo(void):ischeckupdate(0), force(0), url(""), fullurl(""),patchurl(""), dependurl(""), version(""), versionname(""), platform(""), svnVersion(""),
		md5(""),fullMd5(""),patchMd5(""),dependMd5(""),systemDbMd5(""),desc(""){
			info.clear();
			vip.clear();
		}
		int ischeckupdate;					//	1��ʾ�Ǽ����´���
		int force;							//	0�������� 1ǿ������ 
		std::string url;					//	���°�����
		std::string fullurl;				//	ȫ����url
		std::string patchurl;				//	����������
		std::string dependurl;				//	�����������
		std::string version;				//	�����汾 V0.2.2
		std::string versionname;			//  �����汾����
		std::string platform;				//  ƽ̨��Ϣ
		std::string svnVersion;				//  svn�汾��
		std::string md5;					//  mar����md5ֵ
		std::string fullMd5;				//  ȫ��mar��md5
		std::string patchMd5;				//  ����mar��md5
		std::string dependMd5;				//  ����mar��md5
		std::string systemDbMd5;		    //  ���md5ֵ
		std::string desc;					//  ������Ϣ
		std::vector<std::string> info;		//	������Ϣ��������;�ָ�
		std::vector<std::string> vip;	    //	mac��ַ�б�
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