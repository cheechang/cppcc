 #pragma once
#include <iostream>
#include <sstream>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
typedef __int64   int64 ;
typedef   short   int16 ;
#elif  defined(__linux__)
#include <stdint.h>
typedef   int64_t    int64;
typedef   int16_t    int16  ;
#elif  defined(__APPLE__)
typedef   int64_t    int64;
typedef   int16_t    int16;
#endif // _WIN32

#if defined(_WIN32)
const std::string APPNAME = "CPPCC.exe";
#else
const std::string APPNAME = "CPPCC";
#endif
#if defined(_WIN32)
const std::string SCREENSHOTAPPNAME = "screenshot.exe";
#else
const std::string SCREENSHOTAPPNAME = "screenshot";
#endif
const std::string  SIGNLESERVERNAME = "singlelogin.exe";
namespace utils
{
	struct AppVersionInfo
	{
		std::string	version; //版本号
		std::string	product_version; //产品版本
		std::string	product_name;//产品名
		std::string server_minversion; //服务器最小版本
		std::string server_advversion; //服务器端建议版本
		std::string mark; //mark标示
		std::string productId;//产品id
		std::string svnverison;//svn版本号
	};
	struct PassWordStipulate
	{
		int  minLength;     //密码最短长度
		bool digital;       //true必须数字，false可选
		bool low_alp;       //小写字母
		bool up_alp;        //大写字母
		bool alp;           //英文字母
		bool spec_alp;      //特殊字符
		bool can_register;  //允许注册
		PassWordStipulate(){
			minLength = 8;
			digital = false;
			low_alp = false;
			up_alp = false;
			alp = false;
			spec_alp = false;
			can_register = false;
		}
	};
	enum ClientInfoType{
		CLIENTINFO_TYPE_INIT,
		CLIENTINFO_TYPE_VERSION, //客户端版本
		CLIENTINFO_TYPE_PRODUCTID,//获取产品ID
		CLIENTINFO_TYPE_MARK,//获取mark值
		CLIENTINFO_TYPE_SVNVER,//获取svn版本号
	};
	//判断用户类型
	int getUserType(std::string userName, bool bIsPhone = false);

	//16进制转换成int
	int hexcharToInt(char c);

	//16进制字符串转换成字节
	void hexstringToBytes(char* hexstring, char* bytes);

	//字节数转换成字符串
	void bytesToHexstring(char* bytes, int bytelength, char *hexstring, int hexstrlength);

	//16进制转换成字符表情编码
	std::string  Hex2Emoji(std::string hexer);

	//字符表情编码转换成16进制
	std::string Emoji2Hex(std::string emoji);

	//字符转换成utf8编码
	int char2utf8(const char *szIn, char *szOut);

	//utf8转换成字符
	int utf82char(const char *szIn, char *szOut);

	//字符串替换函数
	void string_replace(std::string& strBig, const std::string & strsrc, const std::string &strdst);

	void write_emojimap();

	//相同账号登录判断
	bool is_same_account_login(std::string account);

    //释放锁
    void is_same_account_ReleaseMutex();

	//获取客户端版本号 type 0获取客户端版本号 1获取ProductID
	std::string get_client_info(ClientInfoType type = CLIENTINFO_TYPE_VERSION);

	//删除目录
	int DeleteDir(std::string dir);

	//打开链接地址
	bool OpenLinkAddress(std::string &url);

	//获取当前系统时间
	int64 getCurrentTime();

	//从INI文件读取字符串类型数据 
	char* GetIniKeyString(char *title,char *key,char *filename);  

	PassWordStipulate AnalysisPwdRule(int16 stipulate);

	std::vector<std::string> splitWithStl(const std::string &str,const std::string &pattern);

	bool FileIsExist(const std::string path);

	bool KillProcess(std::string name, bool isterminate=true, bool isquery=false);

	//枚举文件下的所有文件 dirpath要按照如下格式给定例如："E:\*.*"
	void EnumAllFiles(const std::string&dirPath,std::vector<std::string>&files); 

	std::string GetModulePath();
	std::string GetFileName(std::string&filepath);

	// 文件大小转字符串
	std::string convert2ReadableSize(double size);

	//获取默认头像地址
	std::string GetHeadPath(int type,std::string headPath);
	template <class T>
	std::string ConvertToString(T value) {
		std::stringstream ss;
		ss << value;
		return ss.str();
	}
#ifdef _WIN32
	BOOL DeleteDbPatch(std::string dirPath);
	extern HANDLE  g_hAccountMutex;
#else
    extern std::string g_strAccount;
#endif // _WIN32

}
