#pragma once

#include "../model/SDKTypes.h"
//#include "../model/Packet.h"
//#include "../model/Msg.h"
#include "IService.h"
#include "../extModel/avpacket.h"

#include <string>
#include <vector>

#define VER_AV INTERFACE_VERSION(1,0)
static const VRVIID IID_IAVService = { 0x92d88e4f, 0x441c, 0x2226, 0x8a, 0xff, 0x31, 0x1a, 0xf7, 0x56, 0x43, 0x5 };

namespace service
{

class IAvService : public IService{
public:
	virtual ~IAvService(){}
	/*****************************************注册通知回调*******************************************/

	/**
	* \brief 注册音视频事件回调
	* @param[out]  cb 传入接收结果回调  _1见packet.h
	*/
	virtual	 void regAvEventCb(SFunction < void(model::AVEvent) > cb) = 0;

	/*****************************************请求接口*******************************************/

	/**
	* \brief 请求或挂断音视频
	* @param[in]  req 请求参数 见packet.h
	* @param[out]  cb 传入接收结果回调  _1错误信息
	*/
	virtual void sendAvRequestOrHungUp(AVRequest& req, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 接受或拒绝回话请求
	* @param[in]  req 请求参数 见packet.h
	* @param[out]  cb 传入接收结果回调  _1错误信息
	*/
	virtual void acceptOrReject(AVRejectOrAccept& req, SFunction<void(ErrorInfo)> cb) = 0;

	/**
	* \brief 打开或关闭音视频
	* @param[in]  onOrOff 1.打开 2.关闭
	* @param[out]  cb 传入接收结果回调  _1错误信息
	*/
	virtual void turnOnOrOff(int8 onOrOff, SFunction<void(ErrorInfo)> cb) = 0;
		
};


};