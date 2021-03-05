#pragma once

#include "../model/LoginInfo.h"
//#include "../model/Packet.h"
//#include "../model/Account.h"
#include "IService.h"

#include <string>

#define VER_IAUTH INTERFACE_VERSION(1,0)
static const VRVIID IID_IKssService = { 0x3271f2c2, 0xb755, 0x4234, 0x8f, 0x8b, 0x4d, 0x26, 0xd0, 0x6a, 0x2c, 0xb8 };

namespace service 
{

class IKssService : public IService
{
public:
		
	virtual ~IKssService(){};

	/*****************************************注册通知回调*******************************************/

	/**
	* \brief kss自定义消息回调
	* @param[out]  cb _1 接收到的kss消息
	*/
	virtual	 void regOnKssMsgCb(SFunction < void(std::string&) > cb) = 0;

	/*****************************************请求接口*******************************************/

	/**
	* \brief 发送kss音视频自定义消息
	* @param[in]    req  json形式消息
	* @param[out]   cb   传入接收结果回调 _1错误信息
	*/
	virtual void sendKssJsonMsg(std::string& req, SFunction<void(ErrorInfo)> cb) = 0;

};

} /*namespace service*/