#pragma once

/*****************************************************
    NotifyChannel中使用的结构体在此文件中定义
        包括其他Service中用到的结构体

    其他插件中用到的结构体分别在 avpacket.h等 中定义
    添加结构体在插件对应packet中添加  此文件不要轻易修改
******************************************************/

#include "../model/SDKTypes.h"
#include <string>
#include <vector>
#include "../model/Optional.h"
#include <map>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN ///防止重复包含
#include <Windows.h>
#else
//
#endif

namespace model
{
    struct YMD {
        int32 year;                 // 0 不被使用
        int8 month;                 // 从1开始
        int8 day;                   // 从1开始
    };

    struct AccountType{
        bool operator == (const AccountType & rhs) const
        {
            return (type == rhs.type) && (accounts == rhs.accounts) && (mark == rhs.mark);

        }
        int8 type;                  // 账号类型 1：电话, 3：邮箱, 4：userID, 5:身份证, 6：豆豆号, 7:自定义帐号(不做限制)
        std::string accounts;       // 账号
        std::string mark;           // 标识
    };
    struct AVEvent
    {
        AVEvent() :userId(0), type(0), videoType(0), avType(0){}
        int64 userId;
        int8 avType; ///<1，语音  2，视频

        int8 type;//事件类型 1,视频请求 2,挂断消息 3,请求被拒 4,忙 5,超时 6,取消 7,连接 8,断开
        std::string channelId;///<房间号 唯一
        int8 videoType;///<视频回话类型 1:单人 2:多人
        std::string fileName;///<文件名
        int64 fileSize;//<文件大小
    };

    struct channelEvent
    {
        channelEvent() :userId(0), type(0), channelId(0), videoType(2){}
        int64 userId;
        int64 targetId;
        bool isGroup;
        int8 type;                      ///< 事件类型 1,请求 2,挂断 3,请求被拒 4,对方忙 5,超时 6,取消7,连接成功,8,连接断开,9,其他端已接受,10,P2P完成,11,收到accept 消息 现在需要调用createAnswer 12,收到responce 代表现在要调用setRemoteDescrption
        int64 channelId;          ///< 房间号 唯一
		int64 sessionId;				///<SessionId
        int8 videoType;                  ///< 1，音频 2，视频，3,多人UI语音 4,多人UI视频
        std::string fileName;           ///< P2P时传输的文件名
        std::string sdp;                ///<收到accept时 讲sdp交给上层
        int8 version;            ///< 区分声网和rtc  ///< rtc = 0 声网 =1
        std::vector<int64> members;      ///<主叫方发过来的用户列表
		std::string extendJson;			///<扩展Json
    };

	struct multiRtcEvent
	{
		multiRtcEvent() :type(0), groupId(0), onwerId(0) {}
		int64 userId;                   ///< 事件发起者ID
		int8 type;						///< 事件类型(1呼叫 2邀请 3进房 4挂断 5结束 6超时)
		std::string annotation;			///< 事件注解
		int64 groupId;					///< 群ID
		int64 onwerId;					///< 房间主人ID
		std::string	roomId;				///< 房间ID
		std::string roomName;			///< 房间名称
		std::vector<int64> selects;		///< 操作成员(被叫/邀请/超时成员).
		std::vector<int64> members;		///< 全部成员
		std::string extendJson;			///< 扩展Json
	};

    struct tclEvent {
        tclEvent() : userId(0), type(0), channelId(0), ctrlType(0) {}

        int64 userId;                   ///< 对方Id
        int8 type;                      ///< 事件类型 1,请求 2,挂断 3,请求被拒 4,对方忙 5,超时 6,取消 7,接受 8,响应 9,邀请 10,受邀,11,切换屏幕共享 12,切换控制 13,拒绝切换
        int64 channelId;                ///< 房间号 唯一（受控方UserId）
        int8 ctrlType;                  ///< 1-屏幕共享 2-远程操作
        std::vector<std::string> vecIPAddr;     // 受控方IP地址列表
    };

    struct mailFolder{
        mailFolder() :unReadNum(0), totalNum(0), flagNum(0){}
        std::string folderName; ///<文件夹名
        int64 unReadNum;///<未读邮件数目
        int64 totalNum;///<总邮件数目
        int64 flagNum;///<星标数目
    };
    struct  mailDate
    {
        mailDate() :year(0), mon(0), day(0), weekDay(0){}
        int year;
        int mon;
        int day;
        int hour;
        int min;
        int sec;
        int weekDay;
        std::string timeZone;
    };
    struct mailSection
    {
        mailSection(){
            sn = 0;
            type = -1;
            format = -1;
            tsfEncode = -1;
            oriEncode = -1;
            isAttach = 0;
            sectionSize = 0;
        }
        int sn;//<编号
        int type;//< text image
        int format;//< html jpeg;
        int tsfEncode; //<传输编码方式  base64
        int oriEncode; //<明文编码 utf-8
        int8 isAttach;

        std::string sectionName;
        std::string sectionPath;//附件用
        int64       sectionSize;
    };
    struct mailHeader{
        mailHeader() :status(0x00), time(0){
        }
        std::string UID;
        std::string subject;
        std::string from;
        std::string name;
        std::vector<std::string> cc;
        std::vector<std::string> recv;
        int64 time;
        int8 status;
        std::vector<mailSection> attach;
        mailDate date;
        int64 totalSize;
    };
    struct mail :public mailHeader
    {
        mail() :isNew(true){
        }
        std::string body;
        std::string digst;
        std::string charset;//正文编码
        std::string tsfEncodeType;///<传输编码方式
        bool isNew;//标记是否是新邮件还是已经删除的邮件 界面
        std::string floderName;
    };

    struct pushMessage
    {
        pushMessage() :
        previousMsgID(0),
        msgType(0),
        msgID(0),
        createUserID(0),
        fromTeamID(0),
        originalMsgID(0),
        status(0),
        createTime(0),
        operType(0),
        havVaild(0) {}

        int64 previousMsgID;
        /**
        * 11 接收到协查任务
        * 12 接收到协查任务回复
        * 13 接收到通报消息
        * 81 核查对象更改（发起人）
        * 82 核查对象更改（原接收人）
        * 83 通报审核结果
        */
        int8  msgType;
        int64 msgID;
        int64 createUserID;
        int64 fromTeamID;
        std::vector<int64>  targetUserIDs;
        std::string title;
        std::string body;
        std::string format;
        int64 originalMsgID;
        int8 status;
        int64 createTime;
        int8 operType;
        std::string maccode;
        int8 havVaild;
    };
}