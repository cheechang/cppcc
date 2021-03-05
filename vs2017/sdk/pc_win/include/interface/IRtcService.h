#pragma once

//#include "../model/LoginInfo.h"
#include "../extModel/rtcpacket.h"
#include "../extModel/mrtcpacket.h"
#include "../model/Msg.h"
#include "IService.h"
//#include "../model/Packet.h"

#include <string>

#define VER_IRTC INTERFACE_VERSION(1,0)
static const VRVIID IID_IRtcSrvice = { 0x92d87e83, 0x46ac, 0x4b66, 0x8a, 0xf5, 0x28, 0xaf, 0xe7, 0x45, 0xac, 0xf };

namespace service{

	class IRtcService :public IService{
	public:
		virtual ~IRtcService(){}

		/*****************************************注册通知回调*******************************************/
		/**
		*注册音视频事件回调
		* @param[out] _1 rtc事件 见model::channelEvent注释
		*/
		virtual	 void regChannelEventCb(SFunction <void(model::channelEvent&)> cb) = 0;

		/**
		*注册声网推送房间成员
		* @param[out] _1 声网房间成员消息
		*/
		virtual	 void regRoomMemCb(SFunction< void(SSharedPtr<Msg>) > cb) = 0;

		/**
		*注册版本不同事件回调
		* @param[out] _1 rtc事件 见model::channelEvent注释
		*/
		virtual	 void regExtraEventNotifyCb(SFunction <void(int8, std::string&, std::string&)> cb) = 0;

		/*****************************************请求接口*******************************************/

		/**
		* 邀请成员加入音视频会议
		* @param[in] channelRequest 邀请信息 见channelRequest 注释
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void createChannel(channelRequest&, SFunction<void(ErrorInfo)> cb) = 0;
		/**
		*接受或拒绝音视频会议邀请
		* @param[in] rejectOrAccept 接收或拒绝请求信息 见rejectOrAccept 注释
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void acceptOrReject(rejectOrAccept&, SFunction<void(ErrorInfo)> cb) = 0;
		/*
		* 关闭音视频会议
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void leaveChannel(SFunction<void(ErrorInfo)> cb) = 0;
		/*
		*请求加入音视频会议
		* @param[in] joinChl 加入会议请求信息 见joinChl 注释
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void joinChannel(joinChl&, SFunction<void(ErrorInfo)> cb) = 0;
		/*
		*设置会议信息
		* @param[in] setConfer 设置会议信息 见setConfer 注释
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void setConferenceInfo(setConfer&, SFunction<void(ErrorInfo)> cb) = 0;
		/*
		* 获取会议信息
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void getConferenceInfo(SFunction<void(ErrorInfo, getConfer&)> cb) = 0;
		/*
		* 音视频切换
		* @param[in]  type 要切换的类型 1:音频 2:视频
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void switchChannel(int type,SFunction<void(ErrorInfo)> cb) = 0;
		/*
		* 获取打洞服务地址
		* @param[out] cb 传入接收结果回调  _1错误信息 _2打洞服务器信息 见p2pServerInfo 注释
		*/
		virtual void getStunServer(SFunction<void(ErrorInfo, p2pServerInfo&)> cb) = 0;
		/*
		* AGORA声网相关服务接口
		* @param type 1,认证 2.呼叫 3.接听 4.重新申请subKey,5.outChat,6,updataID
		* @param channnelID channelID
		* @param chatTime 通话时间 当type = 5时需要写
		* @param uuid 声网id type = 6时填
		* @param[out] cb  _1 subkey _2 vendorKey
		*/
		virtual void getAgoraFunc(int8 type, int64 channnelID, int64 chatTime, int64 uuid, SFunction<void(ErrorInfo, int, std::string&, std::string&)> cb) = 0;
		/*
		* 获取打洞服务地址 同步接口 见getStunServer注释
		*/
		virtual void getStunServerSync(p2pServerInfo&)= 0;

		/**
		* \brief 获取打洞服务地址列表 （同步接口）
		* @param[out]  stunList 打洞信息;
		*/
		virtual void getStunServerList(std::vector<p2pServerInfo> &stunList) = 0;

		/*
		* 创建四人会议
		* @param[in]  presenterID 四人会议id 
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void makePresenter(int64 presenterID, SFunction<void(ErrorInfo)> cb) = 0;

		/*
		*通用事件call
		*@param[in] eventType 事件类型
		*@param[in] reserveJson 保留字段
		*@param[in] strInfo   信息描述
		*@param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void extraEventCall(int8 eventType, const std::string& reserveJson, const std::string& strInfo, SFunction<void(ErrorInfo)> cb) = 0;


		/*
		* 获取通用信息
		* @param[in] command 信息类型命令
		* @param[out] cb ErrorInfo 传入接收结果回调  _1错误信息
		* @param[out] cb string 返回command要求的信息
		*/
		virtual void getCommonInfo(const std::string& command, SFunction<void(ErrorInfo, std::string&)> cb) = 0;


		/*****************************************注册多点通知回调*******************************************/
		/**
		* 注册多点事件回调
		* @param[out] _1 multi_rtc事件 见model::multiRtcEvent注释
		*/
		virtual	void regMultiEventCb(SFunction<void(model::multiRtcEvent&)> cb) = 0;


		/*****************************************请求多点接口*******************************************/

		/**
		* 获取多点服务信息
		* @param[out] multiServer 服务信息 multiServer.turnAddr存放服务地址,取不到则返回空
		*/
		virtual void getMultiServerSync(p2pServerInfo& multiServer) = 0;

		/**
		* 多点请求
		* @param[in] multiRequest 呼叫信息 见multiRequest 注释
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void multiTalkRequest(multiRequest&, SFunction<void(ErrorInfo)> cb) = 0;
		/**
		* 扩展请求
		* @param[in] type 请求类型
		* @param[in] cmdJson 请求数据
		* @param[in] extendJson 扩展数据
		* @param[out] cb 传入接收结果回调  _1错误信息
		*/
		virtual void multiExtraRequest(int8 type, const std::string& cmdJson, const std::string& extendJson, SFunction<void(ErrorInfo)> cb) = 0;

	};



}