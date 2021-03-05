#pragma once
#include "../model/SDKTypes.h"
#include "IService.h"
#include "../extModel/mailpacket.h"

#include <string>
#include <vector>

#define VER_MAIL INTERFACE_VERSION(1,0)
static const VRVIID IID_IMailService = { 0x92dc7e53, 0x4a7c, 0x4436, 0xac, 0x5e, 0x29, 0x2f, 0xe8, 0x66, 0xbd, 0x2 };

namespace service
{
	class IMailService : public IService
	{
	public:

		virtual ~IMailService(){}
		/**
		* \brief 监听邮箱拉取推送
		* @param[out] cb  传入接收结果回调  _1 邮箱账号; _2 推送的信息类型 0,邮箱文件夹信息 1,邮箱邮件信息; _3 邮件; _4 邮箱文件夹; 
		*/
		virtual void regAutoFetchMailCb(SFunction<void(std::string&, int, std::vector<mail>&, std::vector<mailFolder>&) > cb) = 0;
		/**
		* \brief 获取邮箱帐号
		* @param[in] type 0 获取所有帐号 1，获取指定帐号
		* @param[in] Account 若type = 1，获取指定帐号
		* @param[in] verify_info 传入验证信息
		* @param[out] cb  传入接收结果回调  _1错误信息
		*/
		virtual void getMailAccount(int type, std::string&Account, SFunction<void(ErrorInfo, std::vector<mailSetting>&)> cb) = 0;
		/**
		* \brief 删除邮箱账号
		* @param[in] account 要删除的账号
		* @param[out] cb  传入接收结果回调  _1错误信息
		*/
		virtual void delMailAccount(std::string& account, SFunction<void(ErrorInfo)> cb) = 0;
		/**
		* \brief 新增邮箱账号
		* @param[in] account 新增的账号信息
		* @param[out] cb  传入接收结果回调  _1错误信息
		*/
		virtual void addMailAccount(mailSetting& account, SFunction<void(ErrorInfo)> cb) = 0;
		/**
		* \brief 更新邮箱账号信息
		* @param[in] account 更新的账号信息
		* @param[out] cb  传入接收结果回调  _1错误信息
		*/
		virtual void updateMailAccount(mailSetting& account, SFunction<void(ErrorInfo)> cb) = 0;

		/**
		* \brief 获取本地邮件
		* @param[in] account 账号信息
		* @param[in] folder 邮箱文件夹
		* @param[out] cb  传入接收结果回调  _1错误信息 _2 邮件
		*/
		virtual void getlocalMail(std::string& account, std::string& folder, SFunction<void(ErrorInfo, std::vector<mail>&)> cb) = 0;
		/**
		* \brief 获取邮箱文件夹信息
		* @param[in] account 账号信息
		* @param[out] cb  传入接收结果回调  _1错误信息 _2 邮件文件夹
		*/
		virtual void getMailFolder(std::string& account, SFunction<void(ErrorInfo, std::vector<mailFolder>&)> cb) = 0;
		/**
		* \brief 获取邮箱头信息
		* @param[in] account 账号信息
		* @param[in] folder 邮箱文件夹
		* @param[in] type 拉新邮件 0; 拉旧邮件 1
		* @param[in] num  拉旧邮件时需要填  拉取数目
		* @param[out] cb  传入接收结果回调  _1错误信息 _2 邮件
		*/
		virtual void fetchMailHeader(std::string& account, std::string& folder, int type, int num, SFunction<void(ErrorInfo, std::vector<mail>&)> cb) = 0;
		/**
		* \brief 获取邮箱头信息
		* @param[in] mail 要发送的邮件信息 见stsendMail注释
		* @param[out] cb  传入接收结果回调  _1错误信息 
		*/
		virtual void sendMail(stsendMail& mail, SFunction<void(ErrorInfo)> cb) = 0;
		/**
		* \brief 删除邮件
		* @param[in] account 账号信息
		* @param[in] folder 邮箱文件夹
		* @param[in] UID  邮件UID
		* @param[out] cb  传入接收结果回调  _1错误信息
		*/
		virtual void delMail(std::string& account, std::string& folder,std::string& UID, SFunction<void(ErrorInfo)> cb) = 0;
		/**
		* \brief 分段拉取邮件内容
		* @param[in] account 账号信息
		* @param[in] folder 邮箱文件夹
		* @param[in] UID  邮件UID
		* @param[in] sectionNum  内容编号
		* @param[out] cb  传入接收结果回调  _1错误信息 _2 邮件
		* @param[out] pro  拉取进度回调   _1 额外的请求信息 _2 进度百分比 progess _3 描述信息 info.
		*/
		virtual void fetchMailSection(std::string& account, std::string& folder, std::string& UID, int sectionNum, SFunction<void(ErrorInfo, mail&)> cb, SFunction<void(int32, int32, const std::string&)> pro = NULL) = 0;
	};
}