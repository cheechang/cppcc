#include <regex>
#include <iosfwd>
#include <strstream>
#include <string.h>
#include <time.h>
#include "common.h"
#include  <io.h>
#ifdef _WIN32
#include <tlhelp32.h>
#include <Shlwapi.h>
#   pragma comment(lib, "Shlwapi.lib")
#	pragma comment(lib, "version.lib")
#elif  defined(__linux__) || defined(__APPLE__)
#include <stdio.h>  
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
extern std::string  g_accountname;
#else
#endif
#if defined(__APPLE__)
#define  MAX_PATH 260  
#include <unistd.h>  
#include <limits.h>
#include <fcntl.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <stdarg.h>  
extern  std::string  g_appPath;
#endif 
#define  BUF_SIZE 1024
namespace utils
{

	//0失败， 手机 1，  qq 2 ， 邮箱 3 ，豆豆号 4， 身份证 7 , 6 豆豆账号 
	int getUserType( std::string userName, bool bIsPhone)
	{
		std::regex regMail("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
		std::regex regPhone("(^(\\d{8}|\\d{9}|\\d{10}|\\d{11})$)");
		std::regex regPhoneInt("(^(\\d{10}|\\d{11}|\\d{12}|\\d{13}|\\d{14}|\\d{15})$)");
		std::regex regUserID("(^[0-9]{1,10}$)");
		std::regex regCardID("(^(\\d{15,15}|\\d{14,14}x|\\d{14,14}X|\\d{18,18}|\\d{17,17}x|\\d{17,17}X)$)");//|\\d{15,15}暂时去除15位身份证号的判断
		//	boost::regex regDoodID("([a-zA-Z][a-zA-Z0-9_-]{5,19})+/([a-zA-Z]*)");            //{5-19} 是定义后面[a-zA-Z0-9_-]的数量
		std::regex regDoodID("([a-zA-Z][a-zA-Z0-9_-]{5,19})");            //{5-19} 是定义后面[a-zA-Z0-9_-]的数量
		bool	retMatch = false;
		int		retCode = 0;
		std::string firstStr("");
		try
		{
			if (userName.empty()){
				retCode = -1;
				goto _exit_;
			}
			firstStr = userName.c_str()[0];
			//	判断是否为手机
			//retMatch = boost::regex_match(userName.c_str(), regPhone);
			//if (retMatch)
			//{
			//	retCode = 1;
			//	goto _exit_;
			//}
			retMatch = std::regex_match(userName.c_str(), regPhoneInt);
			if (retMatch && firstStr == "0" && bIsPhone)
			{
				retCode = 1;
				goto _exit_;
			}

			//	判断是否为身份证登录
			retMatch = std::regex_match(userName.c_str(), regCardID);
			if (retMatch && firstStr != "0")
			{
				retCode = 7;
				goto _exit_;
			}

			//	判断是否为邮箱
			retMatch = std::regex_match(userName.c_str(), regMail);
			if (retMatch)
			{
				retCode = 3;
				goto _exit_;
			}
			//	判断是否为userID
			retMatch = std::regex_match(userName.c_str(), regUserID);
			if (retMatch)
			{
                retCode = 4;
				goto _exit_;
			}

			//判断是否是豆豆号
			retMatch = std::regex_match(userName.c_str(), regDoodID);
			if (retMatch)
			{
				retCode = 6;
				goto _exit_;
			}
		}
		catch (...)
		{
		}
		
	_exit_:
		return retCode;
	}
	int hexcharToInt(char c)
	{
		if (c >= '0' && c <= '9') return (c - '0');
		if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
		if (c >= 'a' && c <= 'f') return (c - 'a' + 10);
		return 0;
	}
	void hexstringToBytes(char* hexstring, char* bytes)
	{
        for (size_t i = 0; i < strlen(hexstring); i += 2)
		{
			bytes[i / 2] = (char)((hexcharToInt(hexstring[i]) << 4) | hexcharToInt(hexstring[i + 1]));
		}
	}
	void bytesToHexstring(char* bytes, int bytelength, char *hexstring, int hexstrlength)
	{
		char str2[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
		for (int i = 0, j = 0; i < bytelength, j < hexstrlength; i++, j++)
		{
			int b;
			b = 0x0f & (bytes[i] >> 4);
			char s1 = str2[b];
			hexstring[j] = s1;
			b = 0x0f & bytes[i];
			char s2 = str2[b];
			j++;
			hexstring[j] = s2;
		}
	}
	std::string Hex2Emoji(std::string hexer)
	{
		int	src_len = 0;
		char*	sz_bytes = NULL;

		std::string bytes("");

		sz_bytes = new char[hexer.size() / 2];
		memset(sz_bytes, 0, sizeof(char)*(hexer.size() / 2));
		hexstringToBytes((char*)hexer.c_str(), sz_bytes);
        for (size_t i = 0; i < hexer.size() / 2; ++i)
		{
			bytes += sz_bytes[i];
		}

		if (NULL != sz_bytes)
		{
			delete[]sz_bytes;
			sz_bytes = NULL;
		}
		return bytes;
	}

	std::string Emoji2Hex(std::string emoji)
	{
		char* phex = NULL;
		std::string	hex("");

		phex = new char[emoji.size() * 2];
		memset(phex, 0, emoji.size() * 2);
		bytesToHexstring((char*)emoji.c_str(), emoji.size(), phex, emoji.size() * 2);
        for (size_t i = 0; i < emoji.size() * 2; ++i)
		{
			hex += phex[i];
		}
		return hex;

	}
	int char2utf8(const char *szIn, char *szOut){
		int		nResult = -1;
#ifdef _WIN32
		int		nLen = 0;
		int		nUnicodeLen = 0;
		wchar_t	*pUnicode = NULL;
		BYTE	*pTragetData = NULL;
		int		nTragetLen = 0;

		//	校验参数有效性
		if (NULL == szIn)
		{
			//	参数错误
			goto _exit_;
		}

		//	转换为unicode
		nLen = lstrlenA(szIn);
		nUnicodeLen = ::MultiByteToWideChar(CP_ACP, 0, szIn, -1, NULL, 0);
		if (nUnicodeLen == 0)
		{
			//	获取unicode缓存长度失败
			goto _exit_;
		}

		pUnicode = new wchar_t[nUnicodeLen + 1];
		ZeroMemory(pUnicode, (nUnicodeLen + 1)*sizeof(wchar_t));

		nResult = ::MultiByteToWideChar(CP_ACP, 0, szIn, -1, (LPWSTR)pUnicode, nUnicodeLen);
		if (0 == nResult)
		{
			//	将源字符串转为unicode字符串失败
			nResult = -1;
			goto _exit_;
		}

		//	转为UTF-8
		nTragetLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)pUnicode, -1, (char*)pTragetData, 0, NULL, NULL);
		if (0 == nTragetLen)
		{
			//	获取UTF-8缓存大小失败
			nResult = -1;
			goto _exit_;
		}

		//	判断此操作是否是获取缓存大小
		if (NULL == szOut)
		{
			//	返回大小
			nResult = nTragetLen + 1;
			goto _exit_;
		}
		pTragetData = new BYTE[nTragetLen + 1];
		ZeroMemory(pTragetData, sizeof(BYTE)*(nTragetLen + 1));

		nResult = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)pUnicode, -1, (char *)pTragetData, nTragetLen, NULL, NULL);
		if (0 == nResult)
		{
			//	将unicode字符串转为utf-8字符串失败
			nResult = -1;
			goto _exit_;
		}

		pTragetData[nTragetLen] = '\0';
		lstrcpyA(szOut, (char*)pTragetData);

		nResult = nTragetLen + 1;

	_exit_:

		if (NULL != pUnicode)
		{
			delete[] pUnicode;
			pUnicode = NULL;
		}

		if (NULL != pTragetData)
		{
			delete[] pTragetData;
			pTragetData = NULL;
		}
#else
		strcpy(szOut, szIn);
#endif// _DEBUG
		return nResult;
	}
	int utf82char(const char *szIn, char *szOut){
		int		nResult = -1;
#ifdef _WIN32
		int		wcsLen = 0;
		int		ansLen = 0;
		char	*szAnsi = NULL;
		wchar_t	*wszString = NULL;
		char    *pszansi = NULL;
		//	判断参数有效性
		if (NULL == szIn){
			//	参数错误
			goto _exit_;
		}
		//	获取所需要的空间大小
		wcsLen = ::MultiByteToWideChar(CP_UTF8, 0, szIn, strlen(szIn), NULL, 0);
		if (0 == wcsLen){
			//	获取UTF-8缓存长度失败
			goto _exit_;
		}

		//	分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
		wszString = new wchar_t[wcsLen + 1];
		ZeroMemory(wszString, sizeof(wchar_t)*(wcsLen + 1));

		//	转换为unicode
		nResult = ::MultiByteToWideChar(CP_UTF8, 0, szIn, strlen(szIn), wszString, wcsLen);
		if (0 == nResult){
			//	将UTF-8转换为unicode失败
			nResult = -1;
			goto _exit_;
		}

		//	最后加上'\0'
		wszString[wcsLen] = '\0';

		//	转换为ansi
		//	获取ansi长度
		ansLen = ::WideCharToMultiByte( /*CP_ACP*/936, 0, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
		if (0 == ansLen){
			//	获取ANSI缓存长度失败
			nResult = -1;
			goto _exit_;
		}

		//	判断是否获取缓存长度
		if (NULL == szOut){
			nResult = ansLen + 1;
			goto _exit_;
		}

		//	同上，分配空间要给'\0'留个空间
		szAnsi = new char[ansLen + 1];
		ZeroMemory(szAnsi, sizeof(char)*(ansLen + 1));

		//	转换
		nResult = ::WideCharToMultiByte( /*CP_ACP*/936, 0, wszString, wcslen(wszString), szAnsi, ansLen, NULL, NULL);
		if (0 == nResult){
			//	将UNICODE转换为ANSI失败
			goto _exit_;
		}

		//	最后加上'\0'
		szAnsi[ansLen] = '\0';

		lstrcpy(szOut, szAnsi);
		nResult = ansLen + 1;

	_exit_:
		if (NULL != wszString){
			delete[] wszString;
			wszString = NULL;
		}
		if (NULL != szAnsi){
			delete[] szAnsi;
			szAnsi = NULL;
		}
#else
	    strcpy(szOut, szIn);
#endif //_DEBUG
		return nResult;
	}
	void string_replace(std::string& strBig, const std::string & strsrc, const std::string &strdst)
	{

		std::string::size_type pos = 0;
		pos = strBig.find(strsrc, pos);
		while (pos!= std::string::npos)
		{
			strBig.replace(pos, strsrc.length(), strdst);
			pos += strdst.length();
			pos = strBig.find(strsrc, pos);
		}

	}
	void write_emojimap(){
#ifdef _MSC_VER
		//std::string dir = std ::initial_path<boost::filesystem::path>().string();
		//string_replace(dir, "\\", "/");
		//std::string filePath = dir + "/service/EmojiFaceMap.h";
		//std::string emojiDir = dir + "/ui/image/smilies/emoji_face";
		//std::ofstream fout(filePath);
		//bool bret = fout.is_open();
		//if (!bret)
		//{
		//	return;
		//}
		//fout << "#pragma  once"<<std::endl;
		//fout << "#include <string>" << std::endl;
		//fout << "#include <map>"<<std::endl;
		//fout << "namespace service {" << std::endl;
		//fout << "std::map<std::string,std::string>g_EmojiMap;"<< std::endl;
		////枚举文件
		//boost::filesystem::directory_iterator	item_begin(emojiDir);
		//boost::filesystem::directory_iterator	item_end;
		//int index = 0;
		//for (;item_begin != item_end; ++item_begin)
		//{
		//	std::string hex("");
		//	std::string temp("");
		//	std::strstream ss;
		//	std::string number("");

		//	ss << index;
		//	ss >> number;
		//	hex = item_begin->path().stem().string();
		//	temp = "g_EmojiMap.insert(std::pair<std::string,std::string>(\"";
		//	temp += number;
		//	temp += "\",\"";
		//	temp += hex;
		//	temp += "\"));";
		//	fout << temp << std::endl;
		//	index++;
		//}
		//fout << "}" << std::endl;
		//fout.close();
#else
#endif
	}
	bool is_same_account_login(std::string account){
#ifdef _WIN32
		//创建进程互斥体Sample07
        g_hAccountMutex = CreateMutex(NULL, TRUE, account.data());
		if (NULL == g_hAccountMutex)
		{
			return false;
		}
		//如果程序已经存在并且正在运行
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			/*HWND hProgramWnd = ::FindWindow(NULL, "Linkdood");
			if (hProgramWnd)
			{
				WINDOWPLACEMENT* pWndpl = NULL;
				WINDOWPLACEMENT   wpm;
				pWndpl = &wpm;
				GetWindowPlacement(hProgramWnd, &wpm);
				if (pWndpl)
				{
					//将运行的程序窗口还原成正常状态
					pWndpl->showCmd = SW_SHOWNORMAL;
					::SetWindowPlacement(hProgramWnd, pWndpl);
					SetWindowPos(hProgramWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
				}
			}*/
			//关闭进程互斥体
			CloseHandle(g_hAccountMutex);
			g_hAccountMutex = NULL;
			return true;
		}
		return false;
#else
		//std::string tempPath(g_accountname);
		//tempPath.append("/");
		//tempPath.append(account);
		////判断文件是否存在
		//if (!access((char*)tempPath.data(), F_OK))
		//{
  //          g_strAccount = tempPath;
		//	return true;
		//}
		//else{
		//	int fd =open((char*)tempPath.data(),O_WRONLY|O_CREAT,S_IRWXU);
		//	if ( -1 != fd)
		//	{
		//		g_strAccount = tempPath;
		//		close(fd);
		//	}
		//	return false;
		//}
		//return  false;
#endif // !_WIN32
	}
     void is_same_account_ReleaseMutex()
     {
  #ifdef _WIN32 
         if (NULL != g_hAccountMutex)
         {
             CloseHandle(g_hAccountMutex);
             g_hAccountMutex = NULL;
         }
  #else
         //if (!access((char*)g_strAccount.data(), F_OK))
         //{
         //    remove((char*)g_strAccount.data());
         //    g_strAccount = "";
         //}
  #endif
     }


	 std::string get_client_info(ClientInfoType type){
		 std::string version("");
#ifdef _WIN32
		 AppVersionInfo verinfo;
		 bool bRet = false;
		 int pos = -1;
		 char* lpData = NULL;
		 UINT uLen = 0;
		 UINT cbTranslate = 0;
		 char SubBlock[100] = { 0 };
		 char szversion[100] = { 0 };
		 LPVOID lpBuffer = NULL;
		 unsigned int uiSize = 0;
		 unsigned long dwSize = 0;
		 unsigned long dwDummy = 0;
		 VS_FIXEDFILEINFO *lpffi = NULL;
		 struct LANGANDCODEPAGE {
			 WORD wLanguage;
			 WORD wCodePage;
		 } *lpTranslate;
		 char szPath[256] = { 0 };

		 ::GetModuleFileNameA(NULL, szPath, 256);
		 ::PathRemoveFileSpecA(szPath);
		 std::string AppName(szPath);
		 AppName.append("\\CPPCC.exe");
		 dwSize = GetFileVersionInfoSizeA(AppName.c_str(), &dwDummy);
		 if (0 == dwSize){
			 return version;
		 }

		 //	获取版本信息
		 lpData = new char[dwSize + 1];
		 if (NULL == lpData){
			 return version;
		 }
		 memset(lpData, 0, dwSize + 1);

		 GetFileVersionInfoA(AppName.c_str(), 0, dwSize, lpData);
		 VerQueryValueA(lpData, "\\", (LPVOID *)&lpffi, &uiSize);
		 sprintf_s(szversion, "%d.%d.%d.%d", HIWORD(lpffi->dwFileVersionMS), LOWORD(lpffi->dwFileVersionMS), HIWORD(lpffi->dwFileVersionLS), LOWORD(lpffi->dwFileVersionLS));
		 verinfo.version = std::string(szversion);

		 //查询产品版本信息
		 // Read the list of languages and code pages. //Comments	InternalName	ProductName CompanyName	LegalCopyright	ProductVersion FileDescription	LegalTrademarks	PrivateBuild  FileVersion	OriginalFilename	SpecialBuild
		 VerQueryValueA(lpData, "\\VarFileInfo\\Translation", (LPVOID*)&lpTranslate, &cbTranslate);
		 for (size_t i = 0; i < (cbTranslate / sizeof(struct LANGANDCODEPAGE)); ++i){
			 sprintf_s(SubBlock, "\\StringFileInfo\\%04x%04x\\", lpTranslate[i].wLanguage, lpTranslate[i].wCodePage);
		 }

		 std::string	 strKeyName("");
		 strKeyName = std::string(SubBlock) + std::string("ProductVersion");
		 VerQueryValueA(lpData, strKeyName.data(), &lpBuffer, &uLen);
		 verinfo.product_version = (char*)lpBuffer;

		 strKeyName.clear();
		 strKeyName = std::string(SubBlock) + std::string("ProductName");
		 VerQueryValueA(lpData, strKeyName.data(), &lpBuffer, &uLen);
		 verinfo.product_name = (char*)lpBuffer;

		 strKeyName.clear();
		 strKeyName = std::string(SubBlock) + std::string("serverMinVer");
		 VerQueryValueA(lpData, strKeyName.data(), &lpBuffer, &uLen);
		 verinfo.server_minversion = (char*)lpBuffer;

		 
		 strKeyName.clear();
		 strKeyName = std::string(SubBlock) + std::string("serverAdvVer");
		 VerQueryValueA(lpData, strKeyName.data(), &lpBuffer, &uLen);
		 verinfo.server_advversion = (char*)lpBuffer;

		 strKeyName.clear();
		 strKeyName = std::string(SubBlock) + std::string("Mark");
		 VerQueryValueA(lpData, strKeyName.data(), &lpBuffer, &uLen);
		 verinfo.mark = (char*)lpBuffer;

		 strKeyName.clear();
		 strKeyName = std::string(SubBlock) + std::string("SvnVersion");
		 VerQueryValueA(lpData, strKeyName.data(), &lpBuffer, &uLen);
		 verinfo.svnverison = (char*)lpBuffer;

		 switch (type)
		 {
			 case utils::CLIENTINFO_TYPE_VERSION:
			 {
					pos = verinfo.version.find_first_of(".");
					if (-1 != pos){
						verinfo.version.replace(0, pos + 1, "");
						version = verinfo.version;
					}
					break;
			 }
			 case utils::CLIENTINFO_TYPE_PRODUCTID:
			 {
					version = verinfo.productId;
					break;
			 }
			 case utils::CLIENTINFO_TYPE_MARK:
			 {
					version = verinfo.mark;
					break;
			 }
			 case utils::CLIENTINFO_TYPE_SVNVER:
			 {
					version = verinfo.svnverison;
					break;
			 }
			 default:
			 {
				break;
			 }
		 }
#else
		 switch (type)
		 {
			 case utils::CLIENTINFO_TYPE_VERSION:
			 {
					version = APPVERSION;
					break;
			 }
			 case utils::CLIENTINFO_TYPE_PRODUCTID:
			 {
				   version = APP_PRODUCT_ID;
				   break;
			 }
			 case utils::CLIENTINFO_TYPE_MARK:
			 {
				  version = APP_MARK;
				  break;
			 }
			 default:
			 {
				 break;
			 }
		 }
#endif
	  return version;
	 }
	 int DeleteDir( std::string dir)
	 {
		 int	retCode = 0;
		 retCode = remove(dir.c_str());
		 return retCode;
	 }
	 //打开链接地址
	 bool OpenLinkAddress(std::string &url){
		 bool bret = false;
		 int pos = -1;

		 pos = url.find_first_of("@");
		 if (-1 != pos)
		 {
			 url = "mailto:" + url;
		 }
#ifdef WIN32
		 bret = ShellExecute(NULL, "open", "IEXPLORE.EXE", url.c_str(), NULL, SW_SHOWNORMAL)>(HINSTANCE)31;
#endif // WIN32
		 return bret;
	 }
	 //获取当前系统时间
	 int64 getCurrentTime(){
		 int64 t = time(0)*1000;
		 return t;
	 }
	//从INI文件读取字符串类型数据 
	char* GetIniKeyString(char *title,char *key,char *filename)
	{
		FILE *fp;   
	    char szLine[1024];  
	  
	    if((fp = fopen(filename, "r")) == NULL)   
	    {   
	        printf("hasnofile \n");  
	        return "";   
	    }  
	    //Log(LOG_LEV_INFO, LOG_FILE, "title: %s", title);
	    while(!feof(fp))   
	    {   
	        fgets(szLine,1024,fp);
	        //Log(LOG_LEV_INFO, LOG_FILE, "line: %s", szLine);
			static char tmp[128] = {0};
	        lstrcat(tmp,"[");
	        lstrcat(tmp,title);
	        lstrcat(tmp,"]");
	        if (strstr(szLine,tmp) != NULL)
	        {
	        	fgets(szLine,1024,fp);
	        	//Log(LOG_LEV_INFO, LOG_FILE, "url: %s", szLine);
	        	char* p = strstr(szLine,"=");
	        	if(p != NULL)
	        	{
	        		char*pt = szLine;
	        		memset(tmp,0,128);
	        		while(pt<p)
	        		{
	        			strncat_s(tmp,pt,1);
	        			pt++;
	        		}
	       
	        		if (strcmp(tmp,key)==0)
	        		{
	        			 fclose(fp); 
	        			 lstrcpy(tmp,(p+1));
	        			// Log(LOG_LEV_INFO, LOG_FILE, "tmp: %s,key:%s,url:%s", tmp,key,p+1);
	        			 return tmp;
	        		}
	        	}
	        }
	    }  
	    fclose(fp);   
	    return "";   
	}
	PassWordStipulate AnalysisPwdRule(int16 stipulate){
		PassWordStipulate pwdrule;
		int16 low8 = 0x003F;

		//高8位
		pwdrule.minLength = ((stipulate & 0xFF00) >> 8);
		//低8位
		low8 = stipulate & low8;
		pwdrule.digital = (((low8 & 0x1) == 0x1) ? true : false);
		pwdrule.low_alp = (((low8 & 0x2) == 0x2) ? true : false);
		pwdrule.up_alp = (((low8 & 0x4) == 0x4) ? true : false);
		pwdrule.alp = (((low8 & 0x8) == 0x8) ? true : false);
		pwdrule.spec_alp = (((low8 & 0x10) == 0x10) ? true : false);
		pwdrule.can_register = (((low8 & 0x20) == 0x20) ? true : false);
		return pwdrule;
	}

	std::vector<std::string> splitWithStl(const std::string &str,const std::string &pattern)
	{
		std::vector<std::string> resVec;

		if ("" == str)
		{
			return resVec;
		}
		//方便截取最后一段数据
		std::string strs = str + pattern;

		size_t pos = strs.find(pattern);
		size_t size = strs.size();

		while (pos != std::string::npos)
		{
			std::string x = strs.substr(0,pos);
			resVec.push_back(x);
			strs = strs.substr(pos+1,size);
			pos = strs.find(pattern);
		}
		return resVec;
	}

	bool FileIsExist(const std::string path){
#ifdef WIN32
		return (-1 != _access(path.c_str(),0))?true:false;
#else
		struct stat info;
		stat(path.c_str(), &info);
		return (!S_ISDIR(info.st_mode) && (access(path.c_str(), R_OK) == 0));
#endif
	}
	void EnumAllFiles(const std::string&dirPath,std::vector<std::string>&files){
		_finddata_t fd;
		intptr_t handle;
		int pf=0;

		pf = handle= _findfirst(dirPath.c_str(),&fd);
		while (-1 != pf)
		{
			printf("%s\n",fd.name);
			files.push_back(std::string(fd.name));
			memset(&fd,0,sizeof(fd));
			pf=_findnext(handle,&fd);
		}
		_findclose(handle);
	}
	std::string GetModulePath(){
		std::string rootPath("");
#ifdef _WIN32
		char szPath[256] = { 0 };
		::GetModuleFileNameA(NULL, szPath, 256);
		::PathRemoveFileSpecA(szPath);
		rootPath = std::string(szPath);
		string_replace(rootPath, "\\", "/");
#endif
		return rootPath;
	}
	std::string GetFileName(std::string&filepath){
		std::string result("");
		int pos = filepath.rfind("/");
		result = filepath.substr(pos+1,filepath.length());
		return result;
	}
#ifdef _WIN32
BOOL DeleteDbPatch(std::string dirPath){
	WIN32_FIND_DATA wfd = { 0 };
	HANDLE Find = INVALID_HANDLE_VALUE;
	BOOL bret = FALSE;

	std::string file(dirPath);
	file += std::string("\\*.*");
	Find = FindFirstFileA(file.c_str(), &wfd);
	if (Find == INVALID_HANDLE_VALUE)
		return bret;
	while (FindNextFileA(Find, &wfd))
	{
		if (wfd.cFileName[0] == '.')
		{
			continue;
		}
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string filePath(dirPath);
			filePath += std::string("\\");
			filePath += wfd.cFileName;
			DeleteDbPatch(filePath);
		}
		std::string filePath(dirPath);
		filePath += "\\";
		filePath += wfd.cFileName;
		if (!lstrcmp("dbpatch", wfd.cFileName))
		{
			bret = DeleteFile(filePath.c_str());
			if (!bret)
			{
				return bret;
			}
		}
	}
	FindClose(Find);
	bret = TRUE;
	return bret;
}
#endif

bool KillProcess(std::string name, bool isterminate, bool isquery){
	bool result = false;
#ifdef _WIN32
	std::string str1("");
	DWORD pid = 0;
	HANDLE hSnapShot = NULL;
	PROCESSENTRY32 pInfo;

	pInfo.dwSize = sizeof(pInfo);
	pid = GetCurrentProcessId();
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapShot)
	{
		goto _Exit_;
	}
	if (Process32First(hSnapShot, &pInfo)){
		do
		{
			str1 = std::string(pInfo.szExeFile);
			if (str1 == name)
			{
				if (isquery)
				{
					result = true;
					goto _Exit_;
				}
				if (pid != pInfo.th32ProcessID)
				{
					int ID = pInfo.th32ProcessID;
					HANDLE hProcess;
					// 现在我们用函数 TerminateProcess()终止进程：
					// 这里我们用PROCESS_ALL_ACCESS
					hProcess = OpenProcess(PROCESS_TERMINATE, false, ID);
					if (hProcess == NULL)
					{
						goto _Exit_;
					}
					if (isterminate)
					{
						result =TerminateProcess(hProcess, 0);
						if (!result)
						{
							//Log(LOG_LEV_ERROR, LOG_FILE, "===End Process(%s) Failed,ErrCode=%d", str1.toLocal8Bit().data(), GetLastError());
						}
					}
					CloseHandle(hProcess);
				}
			}
		} while (Process32Next(hSnapShot, &pInfo));
	}
	CloseHandle(hSnapShot);
#else
	DIR *dir;
	struct dirent *ptr;
	FILE *fp;
	char  filepath[50];//大小随意，能装下cmdline文件的路径即可
	char  cur_task_name[50];//大小随意，能装下要识别的命令行文本即可
	char  task_name[100];
	char  buf[BUF_SIZE];
	pid_t currentpid = getpid();
	dir = opendir("/proc"); //打开路径
	if (NULL != dir)
	{
		while ((ptr = readdir(dir)) != NULL) //循环读取路径下的每一个文件/文件夹
		{
			//如果读取到的是"."或者".."则跳过，读取到的不是文件夹名字也跳过
			if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
				continue;
			if (DT_DIR != ptr->d_type)
				continue;

			sprintf(filepath, "/proc/%s/status", ptr->d_name);//生成要读取的文件的路径
			fp = fopen(filepath, "r");//打开文件
			if (NULL != fp)
			{
				if (fgets(buf, BUF_SIZE - 1, fp) == NULL){
					fclose(fp);
					continue;
				}
				sscanf(buf, "%*s %s", cur_task_name);
				//如果文件内容满足要求则打印路径的名字（即进程的PID）
				strcpy(task_name, (char*)name.data());
				if (!strcmp(task_name, cur_task_name))
				{
					printf("PID:%s\n", ptr->d_name);
					if (isquery)
					{
						result = true;
						goto _Exit_;
					}
					int pid = atoi(ptr->d_name);
					if (pid != currentpid)
					{
						if (isterminate)
						{
							char szcommand[100] = { 0 };
							sscanf(szcommand, "kill -9  %d", pid);
							system(szcommand);
						}
					}
				}
				fclose(fp);
			}

		}
		closedir(dir);//关闭路径
	}
#if  defined(__linux__) || defined(__APPLE__)
	if (!access((char*)g_accountname.data(), F_OK))
	{
		int ret = remove((char*)g_accountname.c_str());
		if (-1 == ret)
		{
			//Log(LOG_LEV_ERROR, LOG_FILE, "delete file[%s] failed", g_accountname.c_str());
		}
	}
#endif
#endif
_Exit_:
	return result;
}

	std::string convert2ReadableSize(double size)
	{
		std::string str[4] = {"KB", "MB", "GB", "TB"};
		std::string unit = "Bytes";

		for (int i = 0; size >= 1024.0 && i < 4; i++)
		{
			unit = str[i];
			size /= 1024.0;
		}
		
		std::string strSize = std::to_string((long double)size);
		
		std::string tmp = strSize.substr(0, strSize.size() - 4);
		if (tmp.at(tmp.length()-1) == '.')
		{
			tmp +="0";
		}
		tmp+= " " + unit;
		return tmp;
	}

	std::string utf82char(std::string src) {
		const int buffersize = 10000;
		std::string result("");
		char szchar[buffersize] = { 0 };
		utils::utf82char(src.c_str(), szchar);
		result = std::string(szchar);
		return result;
	}
	std::string GetHeadPath( int type ,std::string headPath)
	{
		if (headPath != "" && FileIsExist(headPath))
		{
			return headPath;
		}
		std::string path = ":/base/default_unknow_head";
		switch(type){
		case 1://男
			path = ":/base/default_head";
			break;
		case 2://女
			path = ":/base/default_female_head";
			break;
		case 4://公众号
			path = ":/base/app_default";
			break;
		}
		return path;
	}

#ifdef _WIN32
	HANDLE  g_hAccountMutex = NULL;
#else
	std::string g_strAccount = "";
#endif // _WIN32
}
