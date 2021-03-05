
#pragma once

#include "../model/SDKTypes.h"
#include "../extModel/gaInterpacket.h"
#include "IService.h"


// {888D0CC8-B73E-4411-9B08-008A40C023F3}
#define VER_GAINTER INTERFACE_VERSION(1,0)
static const VRVIID IID_IGaInterService = { 0x888d0cc8, 0xb73e, 0x4411, 0x9b, 0x8, 0x0, 0x8a, 0x40, 0xc0, 0x23, 0xf3};

namespace service
{

    class IGaInterService : public IService
    {
    public:

        virtual ~IGaInterService() {}

        /**
        * @brief 获取外部节点信息
        * @param[out] cb  传入接收结果回调 _1 错误号 _2外部企业节点信息
        */
        virtual void getAppNodeServers(SFunction<void(ErrorInfo, std::vector<AppNodeInfo>&)> cb) = 0;

        /**
        * @brief 添加三卡审计操作
        * @param[in] oper  三卡审计操作
        * @param[out] cb  传入接收结果回调 _1 错误号
        */
        virtual void addThreeCardOper(ThreeCardOper& oper, SFunction<void(ErrorInfo)> cb) = 0;

        /**
        * @brief 获取授权码
        * @param[in] appID  应用ID号
        * @param[in] clientKey  临时票据
        * @param[out] cb  传入接收结果回调 _1 错误号 _2授权码
        */
        virtual void getAuthCode(int64 appId, const std::string& clientKey, SFunction<void(ErrorInfo, const std::string&)> cb) = 0;
    };

} /*namespace service*/
