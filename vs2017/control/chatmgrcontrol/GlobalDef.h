#pragma once
#include <string>
#include <vector>
#include "IDRangeJuge.hpp"

const int buffersize = 10000;
//表情匹配符
#define EMOJI_IMAGE   "[4f072095e2574b66aa0c6c09acfb3f3e]"
#define EMOJI_REG       "(\\[4f072095e2574b66aa0c6c09acfb3f3e\\](.*?)\\[4f072095e2574b66aa0c6c09acfb3f3e\\])"

//发送的最大文件限制
#define 	MAX_FILE_LIMIT   128*1024*1024 
#define		SYS_MSG_ID -5
#define		SUBSCRIPTION_NUM_ID -6  //会话列表订阅号ID
#define		APP_TMP_ITEM_ID -4
#define		VIDEO_MSG_TYPE 254
#define     ENTAPP_TMP_ITEM_ID  -7
#define     CIRCLE_OF_COLLEAGUES_ID 1 //朋友圈ID

//会话 群 联系人 企业 加载一次标示符定义
#define    CHAT_FLAG     0x01
#define    CONTACT_FLAG  0x02
#define    GROUP_FLAG    0x04
#define    ENTPRISE_FLAG 0x08

//消息类型
//1:html 2:文本，3:音频 4:位置 5:图片6:文件 7:名片 8:弱提示
enum MsgType{
	MEDIA_MSG_HTML = 1,										//HTML文件
	MEDIA_MSG_TEXT = 2,										//文本文件
	MEDIA_MSG_AUDIO = 3,									//语音消息
	MEDIA_MSG_POS = 4,										//位置
	MEDIA_MSG_PIC = 5,										//图片
	MEDIA_MSG_FILE = 6,										//文件
	MEDIA_MSG_CARD = 7,										//名片
	MEDIA_MSG_TIP = 8,										//弱提示
	MEDIA_MSG_WEBLINK = 9,                                //网页链接消息
	MEDIA_MSG_IMAGETXT = 12,                        //图文消息
	MEDIA_MSG_MULTIMSG = 13,								//组合消息
	MEDIA_MSG_VIDEO = 14,									//视频消息
	MEDIA_MSG_AUDIOONLINE = 15,                   //音频消息
	MEDIA_MSG_TASK = 17,                 //任务消息
	MEDIA_MSG_REVOKE = 18,									//撤回消息
	MEDIA_MSG_DYNAMIC_EMOJI = 19,							//动态表情
	MEDIA_MSG_TEMPLATE=26,									//模板消息
	MEDIA_MSG_MOREPIC  =28,							   //九宫格消息
	MEDIA_MSG_RED_PARKET = 88,								//红包
	MEDIA_MSG_MICRO_VIDEO = 89,
	MEDIA_MSG_SUPER = 0xFF									//文件直传
};
//音视频消息扩展类型
enum VedioMsgExtendMsg{
	VEDIO_REQUEST= 201,		 //呼叫
	VEDIO_REQUEST_CANCEL = 202,    //呼叫取消
	VEDIO_REQUEST_REFUSE = 203,    //呼叫拒绝
	VEDIO_USER_BUSY = 204,		 //用户正在通话中
	VEDIO_CALLCLOSED = 205,        //用户挂断
	VEDIO_CALLBACK_SDP = 207,      //回调sdp
};

//应用类型定义
enum AppType{
	APP_H5=1,//1(H5应用), 2(IOS应用), 3(Android应用), 4(内部应用), 5(快捷应用)
	APP_IOS,
	APP_ANDROID,
	APP_INNER,
	APP_QUICK,
};


