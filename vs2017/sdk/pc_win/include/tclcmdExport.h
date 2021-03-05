/*
 * tclcmdExport.h
 *
 *  Created on: 2016年12月22日
 *      Author: Liu.Y
 */

#ifndef tclCMDEXPORT_H_
#define tclCMDEXPORT_H_

#include "cmdReqDef.h"
#include "cmdComDef.h"

#define TCLMSGTYPE 99
using namespace imsdk;

namespace imsdktcl
{

/**
 * 导出业务类消息号，各个平台的ＡＰＩ层要统一
 * ** [in] 标识输入参数
 * ** [out] 标识返回参数
 * ** 只有[out]没有[in] 标识该消息ＳＤＫ纯推送，只有reponse没有request
 */
enum {	
	// [in] req_tclRequest              [out]resp_commonResult            
	tcl_logic_cmd_Request = 15001,              // 请求/邀请进行远程控制

    // [in] req_tclRejectOrAccept  	    [out]resp_commonResult
    tcl_logic_cmd_RejectOrAccept = 15002,       // 接收 或 拒绝接口（屏幕共享，远程操作）

    // [in] NULL                        [out] resp_tclEvent
    tcl_logic_cmd_Event = 15003,                // 响应事件，一般用于回发给响应通道

	// [in] req_tclHungUp               [out]resp_commonResult  
	tcl_logic_cmd_HungUp = 15004,               // 断开远程控制

	// [in] req_tclSwitch           [out]resp_commonResult  
    tcl_logic_cmd_Switch = 15005,           // 切换控制方式（屏幕共享，远程操作）

    // [in] req_tclResponce           [out]resp_commonResult
    tcl_logic_cmd_Responce,                 // 服务方回发响应

	tcl_logic_cmd_max	                        // 最大的命令标识，标识命令个数，无特殊业务意义
};

// =========================================================================================

struct resp_tclEvent : public _sdkrespcmd_base {
    resp_tclEvent() : userId(0), type(0), channelId(0), ctrlType(0) {
    }

	int64 userId;                   // 对方Id
	int8 type;                      // 事件类型 1,请求 2,挂断 3,请求被拒 4,对方忙 5,超时 6,取消 7,接受 8,响应 9,邀请 10,受邀,11,切换屏幕共享 12,切换控制 13,拒绝切换
	int64 channelId;                // 房间号 唯一（受控方UserId）
	int8 ctrlType;                  // 1-屏幕共享 2-远程操作
    std::vector<std::string> vecIPAddr;     // 受控方IP地址列表
    CMD_SIZE();
	COPY_OTHER(resp_tclEvent);
};

struct req_tclRequest : public _sdkcmd_base {
    req_tclRequest() : targetId(0), ctrlType(2), isControl(false){}

    int64 targetId;			    // 目标ID
    int8 ctrlType;			    // 远程控制类型 1-可视，2-可控
    bool isControl;			    // 是否控制方，true-请求、房间号为targetID，false-邀请、房间号为MyselfID
    std::vector<std::string> vecIPAddr;     // IP地址
    CMD_SIZE();
};


struct req_tclRejectOrAccept : public _sdkcmd_base {
    req_tclRejectOrAccept() : targetId(0), type(0), channelId(0), ctrlType(2) {}

	int64 targetId;                 // 目标Id
	int8 type;                      // 1,接受 2，拒绝 3,受邀 4,拒绝切换
	int64 channelId;                // 房间号 唯一
    int8 ctrlType;                  // 远程控制类型 1-可视，2-可控
    std::vector<std::string> vecIPAddr;     // IP地址
    CMD_SIZE();
};

struct req_tclSwitch : public _sdkcmd_base {
    req_tclSwitch() : targetId(0),ctrlType(2) {}
    int64 targetId;					// 目标ID
    int8 ctrlType;					// 远程控制类型 1-可视，2-可控
	CMD_SIZE();
};

struct req_tclHungUp : public _sdkcmd_base {
    req_tclHungUp() :targetId(0),isCancel(false){}

    int64 targetId;					// 目标ID
    bool isCancel;                  // 是否取消通话 true-cancel, false-hungUp
    CMD_SIZE();
};

struct req_tclResponce : public _sdkcmd_base {
    req_tclResponce() : targetId(0),ctrlType(2) {}

    int64 targetId;			    // 目标ID
    int8 ctrlType;                  // 远程控制类型 1-可视，2-可控
    std::vector<std::string> vecIPAddr;     // IP地址
    CMD_SIZE();
};

}

#endif