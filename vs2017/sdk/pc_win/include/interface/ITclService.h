#pragma once

#include "../extModel/tclpacket.h"
#include "IService.h"

#include <string>

#define VER_ITCL INTERFACE_VERSION(1,0)
static const VRVIID IID_ITclService = { 0xa2e5a99b, 0xdf56, 0x460c, 0x9d, 0x4b, 0xd1, 0x54, 0x7, 0x9, 0x38, 0x6a };

namespace service{

	class ITclService :public IService{
	public:
		virtual ~ITclService(){}

		/*****************************************注册通知回调*******************************************/
		/**
		*注册远程连接事件回调
		*/
		virtual	 void regTclEventCb(SFunction <void(model::tclEvent&)> cb) = 0;

		/*****************************************请求接口*******************************************/

		/**
		* 请求或邀请远程连接
        *@Param[in] req 远程连接呼叫请求，详见结构体定义
        *@Param[out] cb 传入接收结果回调 _1错误信息
		*/
		virtual void tclCallOrRequest(tclRequest&, SFunction<void(ErrorInfo)> cb) = 0;
		/**
		*接受或拒绝音视频会议邀请
        *@Param[in] req 远程连接呼叫回应，详见结构体定义
        *@Param[out] cb 传入接收结果回调 _1错误信息
		*/
		virtual void tclAcceptOrReject(tclRejectOrAccept&, SFunction<void(ErrorInfo)> cb) = 0;
		/*
		* 挂断或取消远程连接
        *@Param[in] req 远程连接挂断请求，详见结构体定义
        *@Param[out] cb 传入接收结果回调 _1错误信息
		*/
		virtual void tclHungUpOrCancel(tclHungUp&, SFunction<void(ErrorInfo)> cb) = 0;
		/*
		* 切换远程连接状态
        *@Param[in] req 切换状态请求，详见结构体定义
        *@Param[out] cb 传入接收结果回调 _1错误信息
		*/
		virtual void switchCtrl(tclSwitch&, SFunction<void(ErrorInfo)> cb) = 0;
        /*
        * 受控方回发响应建立连接
        *@Param[in] req 回发响应请求，只在受控方邀请控制并收到确认后调用
        *@Param[out] cb 传入接收结果回调 _1错误信息
        */
        virtual void tclResponce(tclResponse&, SFunction<void(ErrorInfo)> cb) = 0;

	};



}