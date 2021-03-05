#pragma once

#include "../extModel/packet.h"

namespace model
{
    struct AVRequest {
        AVRequest() :targetId(0), type(2), hungUp(false), videoType(1){}
        int64 targetId;//目标Id

#ifdef _WIN32
        HWND local;
        HWND remote;
#else
        long local;
        long remote;
#endif

        std::string channelId;///<房间号 唯一
        int8 type; ///<1，语音  2，视频
        bool hungUp;///true 挂断
        int8 videoType;///<视频回话类型 1:单人 2:多人
    };

    struct AVRejectOrAccept {
        AVRejectOrAccept() : targetId(0), type(1), videoType(0), local(0), remote(0){}
        int64 targetId;//目标Id

#ifdef _WIN32
        HWND local;
        HWND remote;
#else
        long local;
        long remote;
#endif

        int8 type;//1,接受 2，拒绝
        std::string channelId;///<房间号 唯一
        int8 videoType;///<视频回话类型 1:单人 2:多人
        std::string path;               ///< P2P时代表另存为路径

    };
}