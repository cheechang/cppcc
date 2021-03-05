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
		std::string	version; //�汾��
		std::string	product_version; //��Ʒ�汾
		std::string	product_name;//��Ʒ��
		std::string server_minversion; //��������С�汾
		std::string server_advversion; //�������˽���汾
		std::string mark; //mark��ʾ
		std::string productId;//��Ʒid
		std::string svnverison;//svn�汾��
	};
	struct PassWordStipulate
	{
		int  minLength;     //������̳���
		bool digital;       //true�������֣�false��ѡ
		bool low_alp;       //Сд��ĸ
		bool up_alp;        //��д��ĸ
		bool alp;           //Ӣ����ĸ
		bool spec_alp;      //�����ַ�
		bool can_register;  //����ע��
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
		CLIENTINFO_TYPE_VERSION, //�ͻ��˰汾
		CLIENTINFO_TYPE_PRODUCTID,//��ȡ��ƷID
		CLIENTINFO_TYPE_MARK,//��ȡmarkֵ
		CLIENTINFO_TYPE_SVNVER,//��ȡsvn�汾��
	};
	//�ж��û�����
	int getUserType(std::string userName, bool bIsPhone = false);

	//16����ת����int
	int hexcharToInt(char c);

	//16�����ַ���ת�����ֽ�
	void hexstringToBytes(char* hexstring, char* bytes);

	//�ֽ���ת�����ַ���
	void bytesToHexstring(char* bytes, int bytelength, char *hexstring, int hexstrlength);

	//16����ת�����ַ��������
	std::string  Hex2Emoji(std::string hexer);

	//�ַ��������ת����16����
	std::string Emoji2Hex(std::string emoji);

	//�ַ�ת����utf8����
	int char2utf8(const char *szIn, char *szOut);

	//utf8ת�����ַ�
	int utf82char(const char *szIn, char *szOut);

	//�ַ����滻����
	void string_replace(std::string& strBig, const std::string & strsrc, const std::string &strdst);

	void write_emojimap();

	//��ͬ�˺ŵ�¼�ж�
	bool is_same_account_login(std::string account);

    //�ͷ���
    void is_same_account_ReleaseMutex();

	//��ȡ�ͻ��˰汾�� type 0��ȡ�ͻ��˰汾�� 1��ȡProductID
	std::string get_client_info(ClientInfoType type = CLIENTINFO_TYPE_VERSION);

	//ɾ��Ŀ¼
	int DeleteDir(std::string dir);

	//�����ӵ�ַ
	bool OpenLinkAddress(std::string &url);

	//��ȡ��ǰϵͳʱ��
	int64 getCurrentTime();

	//��INI�ļ���ȡ�ַ����������� 
	char* GetIniKeyString(char *title,char *key,char *filename);  

	PassWordStipulate AnalysisPwdRule(int16 stipulate);

	std::vector<std::string> splitWithStl(const std::string &str,const std::string &pattern);

	bool FileIsExist(const std::string path);

	bool KillProcess(std::string name, bool isterminate=true, bool isquery=false);

	//ö���ļ��µ������ļ� dirpathҪ�������¸�ʽ�������磺"E:\*.*"
	void EnumAllFiles(const std::string&dirPath,std::vector<std::string>&files); 

	std::string GetModulePath();
	std::string GetFileName(std::string&filepath);

	// �ļ���Сת�ַ���
	std::string convert2ReadableSize(double size);

	//��ȡĬ��ͷ���ַ
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
