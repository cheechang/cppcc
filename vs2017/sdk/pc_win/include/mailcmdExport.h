#ifndef MAIL_CMDEXPORT_H
#define  MAIL_CMDEXPORT_H
#include <string>
#include <string.h>
#include <vector>
#include "config.h"
#include "cmdComDef.h"
namespace imsdkmail{
	enum{
		mail_logic_cmd_first = 14000,

		/*[in]  NULL                    [out] resp_autofetch     自动拉取邮件推送*/
		mail_logic_cmd_autoFetchNotify,

		/*[in] req_fetchMail            [out] resp_fetchMail      拉取新邮件*/
		mail_logic_cmd_fetchMail,

		/*[in] 	req_fetchMailSection    [out] resp_fetchMailSection    拉取邮件内容*/
		mail_logic_cmd_fetchMailSection,

		/*[in] req_fetchFolder          [out] resp_fetchFolder          获取邮箱文件夹信息*/
		mail_logic_cmd_fetchFolderStatus,

		/*[in] req_sendMail             [out]resp_commonResult           发送邮件*/
		mail_logic_cmd_sendMail,

		/*[in] req_delMail              [out]resp_commonResult           删除邮件*/
		mail_logic_cmd_delMail,

		/*[in] req_getAccount           [out] resp_getAccount          获取帐号*/
		mail_logic_cmd_getAccount,

		/*[in] req_delAccount            [out] resp_commonResult         删除帐号 */
		mail_logic_cmd_delAccount,

		/*[in] req_addOrUpdateAccount    [out] resp_commonReseult       增加或跟新帐号*/
		mail_logic_cmd_addorUpdateAccount,

		/*[in] req_getMail               [out] resp_getMail              获取本地邮件 */
		mail_logic_cmd_getAllMail,

		mail_logic_cmd_max
	};

	struct  st_mailReContact
	{
		st_mailReContact() :id(0), flag(0){}
		std::string name;///名字
		std::string mailAddr;///
		int64 id;//工号之类
		std::string org;
		int8  flag;     ///垃圾邮件 0 y,非0 s
		std::string belong;//来源帐号
	};
	struct st_mailSection
	{
		st_mailSection(){
			sn = 0;
			type = 0;
			format = 0;
			tsfEncode = 0;
			oriEncode = 0;
			isAttach = 0;
			sectionSize = 0;
		}
		int sn;//<编号
		int type;//< text image
		int format;//< html jpeg;
		int tsfEncode; //<传输编码方式  base64
		int oriEncode; //<明文编码 utf-8
		int8 isAttach;//0, 文本正文 1,附件 2,其他内嵌资源 3,html正文

		std::string sectionName;
		std::string sectionPath;//附件用
		int64       sectionSize;
	};
	struct  mailDate
	{
		mailDate() :year(0), mon(0), day(0), weekDay(0){}
		int year;
		int mon;
		int day;
		int hour;
		int min;
		int sec;
		int weekDay;
		std::string timeZone;
	};
	struct st_mailHeader{
		st_mailHeader() :status(0x00), time(0){
			INIT_ISSET(subject);
			INIT_ISSET(from);
			INIT_ISSET(cc);
			INIT_ISSET(recv);
			INIT_ISSET(status);
			INIT_ISSET(time);
			INIT_ISSET(name);
			INIT_ISSET(attach);
			INIT_ISSET(charset);
			INIT_ISSET(tsfEncodeType);
		}
		
		std::string UID;
		IS_SET(std::string, subject)
		IS_SET(std::string, from)
		IS_SET(std::string, name)
		IS_SET(std::vector<std::string>, cc)
		IS_SET(std::vector<std::string>, recv)
		IS_SET(int64, time)
		IS_SET(int8, status)
		IS_SET(std::string, charset)
		IS_SET(std::string, tsfEncodeType)
		IS_SET(std::vector<st_mailSection>, attach)
		mailDate date;
		int64 totalSize;
	};
	struct st_mail :public st_mailHeader
	{
		st_mail() :isNew(true){
			INIT_ISSET(body);
			INIT_ISSET(digst);
		}
		st_mail(st_mailHeader& h){
			UID = h.UID;
			subject = h.subject;
			from = h.from;
			name = h.name;
			cc = h.cc;
			recv = h.recv;
			time = h.time;
			status = h.status;
			attach = h.attach;
			date = h.date;
			totalSize = h.totalSize;
		}
		IS_SET(std::string, body)
		IS_SET(std::string, digst)
		bool isNew;//标记是否是新邮件还是已经删除的邮件 界面
		std::string floderName;
	};
	struct st_setting
	{
		st_setting() :storedays(0), fetchTimeVal(0), SMTPSSL(0), fetchProt(0), FetchSSL(0){
			INIT_ISSET(passwd)
			INIT_ISSET(name)
			INIT_ISSET(storedays)
			INIT_ISSET(fetchTimeVal)
			INIT_ISSET(SMTPAddr)
			INIT_ISSET(SMTPPort)
			INIT_ISSET(SMTPSSL)
			INIT_ISSET(fetchProt)
			INIT_ISSET(FetchAddr)
			INIT_ISSET(FetchPort)
			INIT_ISSET(FetchSSL)
			INIT_ISSET(attachPath)
			INIT_ISSET(floderName)
		}
		std::string account;
		IS_SET(std::string, passwd)	
		IS_SET(std::string, name)
		IS_SET(int, storedays)
		IS_SET(int, fetchTimeVal)
		IS_SET(std::string, SMTPAddr)
		IS_SET(std::string, SMTPPort)
		IS_SET(int8, SMTPSSL)
		IS_SET(int8, fetchProt)
		IS_SET(std::string, FetchAddr)
		IS_SET(std::string, FetchPort)
		IS_SET(int8, FetchSSL)
		IS_SET(std::string, attachPath)
		IS_SET(std::vector<std::string>,floderName)
	};
	struct st_mailFolder{
		st_mailFolder() :unReadNum(0), totalNum(0), flagNum(0){}
		std::string folderName; ///<文件夹名
		int64 unReadNum;///<未读邮件数目
		int64 totalNum;///<总邮件数目
		int64 flagNum;///<星标数目
	};
	struct st_getMailParam{
		st_getMailParam() :num(0), isAsc(false){}
		std::string  begin;
		int64  num;
		bool   isAsc;
	};

	struct st_searchMailParam{
		st_searchMailParam():type(0), time(0), status(0x00){}
		int8 type;
		std::string subject;
		int64  time;
		int    status;
	};

	struct st_mailParam{
		std::string floderName;
		std::string accountName;

		st_getMailParam pGet;
		st_searchMailParam pSearch;
	};
	struct st_mailAccount{



	};

	struct pnode{
		pnode(){
			b = 0;
			e = 0;
			o = false;
			cnt = 0;
			pDeep = 0;
			memset(elemt, 0, 1024);
		}
		void setEnd(char* end){
			e = end;
			memcpy(elemt, b, e - b + 1);
			o = true;
		}
		char* b;
		char* e;
		bool o;
		int cnt;
		int pDeep;
		char elemt[1024];
	};

////////////////////////////////////////////////////////////////////////////////////////////
	struct req_fetchMail : public imsdk::_sdkcmd_base
	{
		req_fetchMail() :type(0), num(0){}
		std::string account;//要拉取邮件的帐号
		int type;//向上拉 新 0; 向下拉 旧 1
		int num;//向下拉时需要填  拉取数目
		std::string folder; ///拉取的文件夹
	};

	struct resp_fetchMail : public imsdk::_sdkrespcmd_base
	{
		std::vector<st_mail> mails;///返回的邮件头
	};


	struct req_fetchFolder :public imsdk::_sdkcmd_base
	{
		std::string account;///< 要拉取邮件的帐号
	};

	struct resp_fetchFolder : public imsdk::_sdkrespcmd_base
	{
		resp_fetchFolder(){}
		std::vector<st_mailFolder> ret;
	};

	///mail_logic_cmd_getAccount
	struct req_getAccount :public imsdk::_sdkcmd_base
	{
		int8 type;          ///<0,获取全部 1,获取指定帐号
		std::string account;/// 要获取的帐号 type=1 填写
	};
	///mail_logic_cmd_getAccount
	struct req_addOrUpdateAccount :public imsdk::_sdkcmd_base
	{
		int8       type;///<0,新增 1,更新
		st_setting newAccount;
	};
	struct req_delAccount :public imsdk::_sdkcmd_base
	{
		std::string account;
	};
	struct resp_getAccount :public imsdk::_sdkrespcmd_base
	{
		std::vector<st_setting> account;
	};
	struct req_getMail :public imsdk::_sdkcmd_base
	{
		std::string account;
		std::string folder;
	};
	struct resp_getMail :public imsdk::_sdkrespcmd_base
	{
		std::vector<st_mail> mail;
	};
	struct req_sendMail :public imsdk::_sdkcmd_base
	{
		std::string account;
		std::string myName;
		std::string myMailAddr;
		std::vector<std::string> recvList;
		std::string subject;
		std::string content;
		std::vector<std::string> attches;
	};
	struct req_delMail :public imsdk::_sdkcmd_base
	{
		req_delMail(){}
		std::string account;
		std::string folderName;
		std::string       UID;
	};

	struct req_fetchMailSection :public imsdk::_sdkcmd_base
	{
		req_fetchMailSection() : sectionNum(0){}
		std::string account;
		std::string folderName;
		std::string       UID;
		int         sectionNum;
	};
	struct resp_fetchMailSection :public imsdk::_sdkrespcmd_base
	{
		st_mail mail;
	};

	/*自动拉取的推送*/
	struct resp_autofetch :public imsdk::_sdkrespcmd_base
	{
		std::string account;///帐号
		int type;///0,邮箱的文件夹  1,自动拉取邮件推送
		std::vector<st_mail> mail;///返回的邮件头
		std::vector<st_mailFolder> folder;
	};
	//===============================================================================================
}
#endif