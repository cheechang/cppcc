/*
 * gaIntercmdExport.h
 *
 *  Created on: 2018年4月18日
 *      Author: Liunux
 */

#ifndef GAINTERCMDEXPORT_H_
#define GAINTERCMDEXPORT_H_

#include "cmdReqDef.h"
#include "cmdComDef.h"

using namespace imsdk;

namespace imsdkgaInter
{

/**
 * 导出业务类消息号，各个平台的ＡＰＩ层要统一
 * ** [in] 标识输入参数
 * ** [out] 标识返回参数
 * ** 只有[out]没有[in] 标识该消息ＳＤＫ纯推送，只有reponse没有request
 */
enum {	
	// [in] _sdkcmd_base              [out]resp_appServerNodes            
	gaInter_logic_cmd_getServerNodes = 20001,              // 获取外部服务器节点
    // [in] req_threeCardOper  	    [out]resp_commonResult
    gaInter_logic_cmd_threeCard = 20002,       // 三卡审计
    // [in] req_authCode  	    [out]resp_authCode
    gaInter_logic_cmd_authCode = 20003,       // 获取授权码

	gaInter_logic_cmd_max	                        // 最大的命令标识，标识命令个数，无特殊业务意义
};

// =========================================================================================

struct resp_appServerNodes : public _sdkrespcmd_base
{
    void init() {
        what = "";
        appNodes.clear();
    }

    std::string what;
    std::vector<st_appNodeInfo> appNodes;

    CMD_SIZE();
    COPY_OTHER(resp_appServerNodes);
};

struct req_threeCardOper : public _sdkcmd_base
{
    req_threeCardOper() : userID(0), operType(0), operResult(0), id(0)
    {
        operTime = "";
        userName = "";
        idcard = "";
        certificateNo = "";
        tfSerialNumber = "";
        iccid = "";
        equipmentID = "";
        appID = "";
        mobileIP = "";
        mobileMac = "";
        operTime = "";
    }
    
    int64 userID;
    std::string userName;
    std::string idcard;
    std::string certificateNo;
    std::string tfSerialNumber;
    std::string iccid;
    std::string equipmentID;
    std::string appID;
    std::string mobileIP;
    std::string mobileMac;
    int32 operType;
    int32 operResult;
    int64 id;
    std::string operTime;

    void init() {
        userID = 0;
        operType = 0;
        operResult = 0;
        id = 0;
        operTime = "";
        userName = "";
        idcard = "";
        certificateNo = "";
        tfSerialNumber = "";
        iccid = "";
        equipmentID = "";
        appID = "";
        mobileIP = "";
        mobileMac = "";
        operTime = "";
    }

    CMD_SIZE();
};

struct req_authCode :public _sdkcmd_base
{
    void init(){
        appID = 0;
    }
    int64 appID;    // 应用ID
    std::string clientKey;  // 临时票据

    CMD_SIZE();
};

struct resp_authCode : public _sdkrespcmd_base
{
    void init(){
        isExpired = false;
        what = "";
        authCode = "";
    }

    std::string what;
    bool isExpired;
    std::string authCode;

    CMD_SIZE();
    COPY_OTHER(resp_authCode);
};

}

#endif