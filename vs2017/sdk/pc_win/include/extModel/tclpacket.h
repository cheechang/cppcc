#pragma once

#include "../extModel/packet.h"

namespace model
{
struct tclRequest {
    tclRequest() : targetId(0), ctrlType(2), isControl(false){}

    int64 targetId;			    ///< 目标ID
    int8 ctrlType;			    ///< 远程控制类型 1-可视，2-可控
    bool isControl;			    ///< 是否控制方，true-请求、房间号为targetID，false-邀请、房间号为MyselfID
    std::vector<std::string> vecIPAddr;     ///< 受控方IP地址列表，邀请时有效
};
struct tclRejectOrAccept {
    tclRejectOrAccept() : targetId(0), type(0), channelId(0), ctrlType(2) {}

    int64 targetId;                 ///< 目标Id
    int8 type;                      ///< 1,接受 2，拒绝
    int64 channelId;                ///< 房间号 唯一
    int8 ctrlType;                  ///< 远程控制类型 1-可视，2-可控
    std::vector<std::string> vecIPAddr;     ///< 受控方IP地址列表，接受时有效
};
struct tclSwitch {
    tclSwitch() : targetId(0), ctrlType(0) {}
    int64 targetId;					///< 目标ID
    int8 ctrlType;					///< 远程控制类型 1-可视，2-可控
};
struct tclHungUp{
    tclHungUp() :targetId(0), isCancel(false){}

    int64 targetId;					///< 目标ID
    bool isCancel;                  ///< 是否取消通话 true-cancel, false-hungUp
};
struct tclResponse {
    tclResponse() : targetId(0), ctrlType(2){}
    int64 targetId;			    ///< 目标ID
    int8 ctrlType;			    ///< 远程控制类型 1-可视，2-可控
    std::vector<std::string> vecIPAddr;     ///< IP地址列表
};

}