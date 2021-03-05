#pragma once

#include "../extModel/packet.h"

namespace model
{
    // 外部企业节点信息
    struct AppNodeInfo{
        std::string nodeID;                 ///< 节点ID（唯一）
        Optional<std::string> nodeName;     ///< 节点名
        Optional<std::string> productType;  ///< 企业类型
    };

    // 三卡审计操作
    struct ThreeCardOper
    {
        int64 userID;                   ///< 用户ID
        std::string userName;           ///< 用户名称
        std::string idcard;             ///< 身份证
        std::string certificateNo;      ///< 证书编号
        std::string tfSerialNumber;     ///< tf卡序列号
        std::string iccid;              ///< 主SIM卡iccid
        std::string equipmentID;        ///< 设备ID
        std::string appID;              ///< 应用ID
        std::string mobileIP;           ///< 移动端IP
        std::string mobileMac;          ///< 移动端物理地址
        int32 operType;                 ///< 操作类型  1登录2登出
        int32 operResult;               ///< 操作结果   1成功2失败
        int64 id;                       ///< 主键id
        std::string operTime;           ///< 操作时间
    };
}