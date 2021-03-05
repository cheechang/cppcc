/*
* json_api_for_pc.h
*
*  Created on: 2016年04月07日
*      Author: corning
*/

#ifndef JSON_JSONTRANSTOOL_H_
#define JSON_JSONTRANSTOOL_H_

#include <config.h>
#include <string>
#include "../model/Msg.h"
#ifdef   SERVICE_EXPORTS
#ifdef _WIN32
#define  SERVICE_API   _declspec( dllexport )
#else
#define SERVICE_API 
#endif
#else
#ifdef _WIN32
#define  SERVICE_API   _declspec( dllimport )
#else
#define SERVICE_API 
#endif
#endif

namespace service
{
	/**
	* \brief 解析消息json
	* @param[in] type  消息类型  
	* @see jsonToolExport.h
	* @param[in] strIn 消息json串
	* @param[out] pOut  解析结果
	* @see jsonToolExport.h
	*/
SERVICE_API bool logic_jsonTransToStruct(uint16 type, std::string & strIn, void * pOut);
/**
* \brief 构造消息json
* @param[in] type  消息类型
* @see jsonToolExport.h
* @param[out] pOut  解析结果
* @see jsonToolExport.h
* @param[in] strIn 消息json串
*/

SERVICE_API bool logic_structTransToJson(uint16 type, void * pIn, std::string & strOut);


SERVICE_API SSharedPtr<model::MsgText> toMsgText(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgSys> toMsgSys(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgVoice> toMsgVoice(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgVedio> toMsgVedio(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgAudio> toMsgAudio(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgPosition> toMsgPosition(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgImg> toMsgImg(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgFile> toMsgFile(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgCard> toMsgCard(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgTip> toMsgTip(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgWeb> toMsgWeb(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgRevoke> toMsgRevoke(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgDynExpression> toMsgDynExpression(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgPicWithText> toMsgPicWithText(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgTask> toMsgTask(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgDynExpression2> toMsgDynExpression2(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgMasterplate> toMsgMasterplate(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgMiniVedio> toMsgMsgMiniVedio(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgNineBlock> toMsgNineBlock(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgConference> toMsgConference(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgMail> toMsgMail(model::Msg *baseMsg);

SERVICE_API SSharedPtr<model::MsgRedPacket> toMsgRedPacket(model::Msg *baseMsg);
}

#endif /* JSON_JSONTRANSTOOL_H_ */
