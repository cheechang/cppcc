

#ifndef KSSPLUGIN_CMD_EXPORT_H_
#define KSSPLUGIN_CMD_EXPORT_H_

#include "cmdReqDef.h"
#include "cmdComDef.h"

using namespace imsdk;

namespace imsdkkss{

/**
 * 导出业务类消息号，各个平台的ＡＰＩ层要统一
 * ** [in] 标识输入参数
 * ** [out] 标识返回参数
 * ** 只有[out]没有[in] 标识该消息ＳＤＫ纯推送，只有reponse没有request
 */
enum {	
	/// [in]               [out]            
	rtc_logic_cmd_sendJsonMsgToKss = 17001,               

	/// [in] NULL                     [out] 
	rtc_logic_cmd_onKssJsonMsg = 17002,         

	rtc_logic_cmd_max	                            /// 最大的命令标识，标识命令个数，无特殊业务意义
};

//	sendJsonMsgToKss参数
struct req_kssJsonMsg : public _sdkcmd_base {

	std::string json_msg;
	
	CMD_SIZE();
};


}	// namespace imsdkkss

#endif	// KSSPLUGIN_CMD_EXPORT_H_