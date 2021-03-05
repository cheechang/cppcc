#pragma once

#include "IService.h"
#include"../model/Packet.h"
#include <string>

#define VER_ILOGGING INTERFACE_VERSION(1,0)
static const VRVIID IID_ILoggingService = { 0x45daff8, 0x61c5, 0x4da4, 0xab, 0xcb, 0x5c, 0x30, 0xd1, 0x56, 0x40, 0xb8 };

namespace service
{

class ILoggingService :public IService
{
public:
	virtual ~ILoggingService(){}


	/**
	* \brief 创建日志，写日之前，必须执行此步骤; 创建日志后，会主动开始记录
	* @param[in] tag 日志头信息
	* @param[in] flushInterval 刷新日志到文件的间隔 毫秒
	* @param[in] uploadInterval 上传日志到服务器的时间间隔 秒 -1代表不上传到服务器
	*/
	virtual void createLog(LogHeadTag &tag, int flushInterval = 3000, int uploadInterval = 300) = 0;

	/**
	* \brief 主动变更日志文件
	* @param[in] tag 日志头信息
	*/
	virtual void changeLogFile(LogHeadTag &tag) = 0;

	/**
	* \brief 写入日志
	* @param[in] log 日志map，下层转化为json串保存
	*/
	virtual void log(std::map<std::string, std::string> &log) = 0;

	/// 主动上传日志到服务器
	virtual void uploadLog() = 0;

	/// 开始记录日志
	virtual void start() = 0;

	/// 停止记录日志
	virtual void stop() = 0;
};



}