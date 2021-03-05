/*
 * rtccmdExport.h
 *
 *  Created on: 2016年12月22日
 *      Author: corning
 */

#ifndef rtcCMDEXPORT_H_
#define rtcCMDEXPORT_H_

#include "cmdReqDef.h"
#include "cmdComDef.h"

#define RTCMSGTYPE 15
#define RTCCALLMSGTYPE 14

using namespace imsdk;

namespace imsdkrtc{

/**
 * 导出业务类消息号，各个平台的ＡＰＩ层要统一
 * ** [in] 标识输入参数
 * ** [out] 标识返回参数
 * ** 只有[out]没有[in] 标识该消息ＳＤＫ纯推送，只有reponse没有request
 */
enum {	
	/// [in] req_request              [out]resp_commonResult            
	rtc_logic_cmd_rtcRequest = 13001,               /// 发起/邀请成员加入音视频

    /// [in] req_rejectOrAccept  	  [out]resp_commonResult
    rtc_logic_cmd_rtcRejectOrAccept = 13002,        /// 接收 或 拒绝接口（音频，视频，P2P）

	/// [in] req_joinChannel          [out]resp_commonResult      
	rtc_logic_cmd_joinChannel = 13003,              /// 主动加入音视频

    /// [in] NULL                     [out] resp_RTCEvent
    rtc_logic_cmd_rtcEventNotify = 13004,           /// 音频，视频，P2P 推送

	///[in] NULL                      [out]resp_commonResult  
	rtc_logic_cmd_lertceChannel = 13005,            /// 断开音视频

	///[in] NULL                      [out] resp_getConferInfo
	rtc_logic_cmd_getChannnelInfo = 13006,          /// 获取会议信息

	///[in] req_setConferenceInfo     [out] resp_commonResult
	rtc_logic_cmd_setConferInfo = 13007,            /// 设置会议信息

	///[in] req_rtcSwitch                      [out]resp_commonResult  
	rtc_logic_cmd_switchtoAudio = 13008,            /// 切换会议到音频（房主功能）

	///[in] req_makePresenter                     [out]resp_commonResult
	rtc_logic_cmd_makePresenter = 13009,			/// 使某人成为会议主讲人（房主功能）

	///[in] req_extraEvent                        [out]resp_commonResult
	rtc_logic_cmd_extraEventCall = 13010,          ///附加事件调用处理

	///[out] resp_extraEvent
	rtc_logic_cmd_extraEventNotify = 13011,        ///附加事件回调处理

	rtc_logic_cmd_max	                            /// 最大的命令标识，标识命令个数，无特殊业务意义
};

/// =========================================================================================

struct st_serResult {	
	std::string stunAddr;
	std::string stunPort;
	std::string turnAddr;
	std::string turnPort;
	std::string account;
	std::string password;
};

struct resp_rtcEvent : public _sdkrespcmd_base {
    resp_rtcEvent() : userId(0), type(0), channelId(0), videoType(0) {
        members.clear();
    }

	int64 userId;
    int64 targetId;
	int8 type;                      ///< 事件类型 1,请求 2,挂断 3,请求被拒 4,对方忙 5,超时 6,取消7,连接成功,8,连接断开,9,其他端已接受,10,P2P完成,11,收到accept 消息 现在需要调用createAnswer 12,收到responce 代表现在要调用setRemoteDescrption
	int64 channelId;                ///< 房间号 唯一
	int8 videoType;                 ///< 1，音频 2，视频，3，P2P
    std::string fileName;           ///< P2P时传输的文件名
	std::string sdp;                ///< 收到call/accept时 讲sdp交给上层
	int8 version;                   ///< rtc = 0 声网 =1
	std::vector<int64> members;     ///< 主叫方发过来的用户列表
    bool isGroup;
    CMD_SIZE();
	COPY_OTHER(resp_rtcEvent);
};

struct resp_getConference : public _sdkrespcmd_base {
    resp_getConference() {
        m_vtMembers.clear();
    }

	std::string m_strTheme;         ///< 会议议题
	st_serResult info;              ///< 打洞服务器信息
	std::vector<int64> m_vtMembers; ///< 成员
    CMD_SIZE();
    COPY_OTHER(resp_getConference);
};

struct req_joinChannel : public _sdkcmd_base {
	req_joinChannel() : channelId(0) {}

	int64 channelId;                /// 请求加入的房间号
	std::string  addition;          /// 附加信息
    CMD_SIZE();
};

struct req_rtcRequest : public _sdkcmd_base {
	req_rtcRequest() :  targetId(0), videoType(2), reject(false), isGroup(false){}

	int64 targetId;                 ///< 目标Id 创建/邀请
	std::string firstSdp;			///< 生成第一次sdp
	bool reject;                    ///< true  代表用于拒绝申请加入会议//保留
	int operType;                 ///< 0，普通呼叫 1，innercall 2,声网
	int8 videoType;                 ///< 1:音频 2:视频,3多人UI语音 ,4多人UI视频 ,5四人广播音频  6四人广播视频, 7 h5文件直传 9远程控制 
    bool isGroup;
    std::vector<int64> members;
    CMD_SIZE();
};


struct req_rtcRejectOrAccept : public _sdkcmd_base {
	req_rtcRejectOrAccept() : targetId(0), type(0), channelId(0), videoType(2) {}

	int64 targetId;                 ///< 目标Id
	int8 type;                      ///< 1,接受 2，拒绝,3,声网接受 4,声网拒绝
	int64 channelId;                ///< 房间号 唯一
	int8 videoType;                 ///< 视频类型 1:音频 2:视频,3多人UI语音 ,4多人UI视频 ,5四人广播音频  6四人广播视频, 7 h5文件直传 9远程控制 
	std::string SecondSdps;		    ///< 第二次sdp
    CMD_SIZE();
};

struct req_rtcSwitch : public _sdkcmd_base {
	req_rtcSwitch() : type(0) {}

	int type;///< 视频类型 1:音频 2:视频
	CMD_SIZE();
};

struct req_setConferenceInfo : public _sdkcmd_base {
	req_setConferenceInfo() :m_Members(0){
	}	

	int64 m_Members; ///< 需要操作的用户列表 （删除）
    CMD_SIZE();
};

struct req_makePresenter : public _sdkcmd_base {

	req_makePresenter() : presenterID(0){}
             
	int64 presenterID; 

	CMD_SIZE();
};

struct req_extraEvent : public _sdkcmd_base {

	req_extraEvent() : eventType(0){}

	int8  eventType;   //事件类型
	std::string reserveJson; //保留字段
	std::string strInfo;  //信息描述

	CMD_SIZE();
};

struct resp_extraEvent : public _sdkrespcmd_base {

	resp_extraEvent() : eventType(0){}

	int8  eventType;   //事件类型
	std::string reserveJson; //保留字段
	std::string strInfo;  //信息描述

	CMD_SIZE();
};

}

#endif