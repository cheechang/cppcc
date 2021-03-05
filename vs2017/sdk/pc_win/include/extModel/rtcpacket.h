#pragma once

#include "../extModel/packet.h"

namespace model
{
    struct channelRequest {
        channelRequest() : reject(false), videoType(2){}
        int64 targetId;//目标Ids
        int operType;                 ///< 0，普通呼叫 1，innercall,2,声网呼叫
        bool reject;  ///< true  代表用于拒绝申请加入会议
        int8 videoType;                 ///< 1，语音  2，视频 3,多人UI语音 4,多人UI视频
        std::string firstSdp;
        bool isGroup;
        std::vector<int64> members;
    };

    struct joinChl{
        joinChl() :channelId(0){}
        int64 channelId; ///请求加入的房间号
        std::string  addition;///附加信息
    };
    struct setConfer{
        int64 m_vtMembers;///<需要操作的用户列表 （删除）
    };
    struct p2pServerInfo{

		p2pServerInfo() {}
		p2pServerInfo(std::string saddr, std::string sport, std::string acot, std::string pw) {
			stunAddr = saddr;
			stunPort = sport;
			account = acot;
			password = pw;
		}

        std::string stunAddr;
        std::string stunPort;
        std::string turnAddr;
        std::string turnPort;
        std::string account;
        std::string password;
    };
    struct getConfer{
        std::string m_strTheme;///<会议议题
        p2pServerInfo info;///<打洞服务器信息
        std::vector<int64> m_vtMembers;///<成员
    };
    struct rejectOrAccept {

        rejectOrAccept() : targetId(0), type(0), channelId(0), videoType(2){}

        int64 targetId;                 ///< 目标Id
        int8 type;                      ///< 1,接受 2，拒绝,3,声网接受 4,声网拒绝
        int64 channelId;          ///< 房间号 唯一
        int8 videoType;                 ///< 视频类型 1:音频 2:视频
        //std::string path;               ///< P2P时代表另存为路径(不传为默认路径)
        std::string  sdps;///<针对多点音视频，讲多个sdp useid对传下来
    };

}