/*
 * avcmdExport.h
 *
 *  Created on: 2016年12月22日
 *      Author: corning
 */

#ifndef AVCMDEXPORT_H_
#define AVCMDEXPORT_H_

#include "cmdReqDef.h"
#include "cmdComDef.h"

using namespace imsdk;

namespace imsdkav{

/**
 * 导出业务类消息号，各个平台的ＡＰＩ层要统一
 * ** [in] 标识输入参数
 * ** [out] 标识返回参数
 * ** 只有[out]没有[in] 标识该消息ＳＤＫ纯推送，只有reponse没有request
 */
enum {	
	/// [in] req_AVRequest          [out]resp_commonResult            
    av_logic_cmd_AVRequest = 12001,           /// 申请音频，视频通话 或 挂断 音频，视频电话，取消P2P传输文件

	/// [in] req_AVRejectOrAccept	[out]resp_commonResult
    av_logic_cmd_AVRejectOrAccept = 12002,    /// 接收 或 拒绝接口（音频，视频，P2P）

	/// [in] req_AVOnOrOffVedio		[out]resp_commonResult
    av_logic_cmd_AVOnOrOffVedio = 12003,      /// 打开或关闭视频接口

	/// [in] NULL                   [out] resp_AVEvent
    av_logic_cmd_AVEventNotify = 12004,       /// 音频，视频，P2P 推送


	av_logic_cmd_max	                      /// 最大的命令标识，标识命令个数，无特殊业务意义
};

/// =========================================================================================

struct resp_AVEvent : public _sdkrespcmd_base {
    resp_AVEvent() : userId(0), type(0), videoType(0), avStatus(0), fileSize(0) {}

	int64 userId;
	int8 type;                      ///< 事件类型 1,请求 2,挂断 3,请求被拒 4,对方忙 5,超时 6,取消7,连接成功,8,连接断开,9,其他端已接受,10,P2P完成
	std::string channelId;          ///< 房间号 唯一
	int8 videoType;                 ///< 视频回话类型 1:单人 2:多人
    int8 avStatus;                  ///< 1，音频 2，视频，3，P2P
    std::string fileName;           ///< P2P时传输的文件名
    int64 fileSize;                 ///< 文件大小
    CMD_SIZE();
    COPY_OTHER(resp_AVEvent);
};

struct req_AVOnOrOffVedio : public _sdkcmd_base {
	int8 onOrOff;                   ///<1,打开；2，关闭
    CMD_SIZE();
};

struct req_AVRequest : public _sdkcmd_base {
	req_AVRequest() : targetId(0), type(2), hungUp(false), videoType(1){}

#ifdef _WIN32
	HWND local;
	HWND remote;
#else
	long local;
	long remote;
#endif

	int64 targetId;                 ///< 目标Id
	std::string channelId;          ///< 房间号 唯一
	int8 type;                      ///< 1，语音  2，视频
	bool hungUp;                    ///< true 挂断(挂断只需要设置这一个参数即可)
	int8 videoType;                 ///< 视频回话类型 1:单人 2:多人
    CMD_SIZE();
};

struct req_AVRejectOrAccept : public _sdkcmd_base {
	req_AVRejectOrAccept() : targetId(0), type(1), videoType(0){}

#ifdef _WIN32
	HWND local;
	HWND remote;
#else
	long local;
	long remote;
#endif

	int64 targetId;                 ///< 目标Id
	int8 type;                      ///< 1,接受 2,拒绝
	std::string channelId;          ///< 房间号 唯一
	int8 videoType;                 ///< 视频回话类型 1:单人 2:多人
    std::string path;               ///< P2P时代表另存为路径(不传为默认路径)
    CMD_SIZE();
};

}

#endif