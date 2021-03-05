#include "ParseJsonData.h"
#include "data/ChatData.h"
#include "interface/jsonToolExport.h"
#include "interface/jsonTransTool.h"
#include "EmojiExpress.h"
#include "InstructExpress.h"
#include "ChineseInfos.hpp"
#include "../utils/common.h"
#include "GlobalDef.h"
namespace control{
	ParseJsonData::ParseJsonData(){

	}
	ParseJsonData::~ParseJsonData(){

	}
	std::string ParseJsonData::emojideal(std::string text,bool isdealInstuct){
		std::string hex("");
		std::string content("");

		content = text;

		/*utils::string_replace(content,"&:delete|today",char2utf8(INSTRUCT_EMOJI_TIP+ERASER_TIP));
		utils::string_replace(content,"&:delete|all",char2utf8(INSTRUCT_EMOJI_TIP+ERASER_TIP));*/

		utils::string_replace(content, "&:delete|today", char2utf8(ERASER_TIP));
		utils::string_replace(content, "&:delete|all", char2utf8(ERASER_TIP));

		if ( isdealInstuct)
		{
			EmojiExpress::EmojiParseFrom(content, hex,char2utf8(EMOJI_TIP));
			content = hex;
			//指令表情容错
			utils::string_replace(content,"&:flash",char2utf8(INSTRUCT_EMOJI_TIP+SHAKE_TIP));
	/*		utils::string_replace(content,"&:delete|today",char2utf8(INSTRUCT_EMOJI_TIP+ERASER_TIP));
			utils::string_replace(content,"&:delete|all",char2utf8(INSTRUCT_EMOJI_TIP+ERASER_TIP));
*/
			utils::string_replace(content, "&:delete|today", char2utf8(ERASER_TIP));
			utils::string_replace(content, "&:delete|all", char2utf8(ERASER_TIP));
		}
		else{
			EmojiExpress::EmojiParseFrom(content, hex);
			content = hex;
			InstructExpress::InstructParseFrom(content, hex);
			content = hex;
		}
		return content;
	}

	int ParseJsonData::dealEraserType(std::string text)
	{
		std::string tmarkstr = "&:delete|today";
		std::string amarkstr = "&:delete|all";
		std::string::size_type pos = 0;
		pos = text.find(tmarkstr, pos);
		if (pos != std::string::npos){
			return 1;
		}

		pos = 0;
		pos = text.find(amarkstr, pos);
		if (pos != std::string::npos){
			return 2;
		}

		return 0;
	}

	std::string ParseJsonData::emojisenddeal(std::string text){
		std::string hex("");
		std::string content("");
		content = text;
		EmojiExpress::EmojiParseTo(content, hex);
		content = hex;
		InstructExpress::InstructParseTo(content, hex);
		content = hex;
		return content;
	}
	std::string ParseJsonData::ParaseJson(int msgtype,int acivetype,std::string json,std::string msgprop){
		std::string content("");
		int realMsgType = 0;
			
		realMsgType=msgtype&0xFF;
		service::jst_SubMsgProperties subMsgPro;
		service::logic_jsonTransToStruct(service::json_DeviceType, msgprop, &subMsgPro);
		if (msgtype != data::MSG_TYPE_REVOKE && (1 == subMsgPro.isPrivateMsg || 2 == subMsgPro.isPrivateMsg))
		{
			//私信消息
			content = char2utf8(RRIVATE_MESSAGE);
		}
		else{
			switch(realMsgType){
				case data::MSG_TYPE_NINEBLOCK:
					{
						content = char2utf8(IMAGE_MSG_TIP);
						break;
					}
				case data::MSG_TYPE_DYNEXPRESSION:
					{
						content = char2utf8(DYNAMIC_EMOJI_MSG);
						break;
					}
				case data::MSG_TYPE_TASK:
					{
						content = char2utf8(TASK_MSG);
						break;
					}
				case data::MSG_TYPE_TEXT:
					{
						service::jst_TextMsg textMsg;
						service::logic_jsonTransToStruct(service::json_txtMsg,json, &textMsg);
						content = emojideal(textMsg.textMsg);
						break;
					}
				case data::MSG_TYPE_COMBINE:
					{
						content = char2utf8(COMBIN_MSG_TIP);
						break;
					}
				case data::MSG_TYPE_AUDIO:
					{
						content = char2utf8(AUDIO_MSG_TIP);
					    break;
					}
				case data::MSG_TYPE_MINIVEDIO:
					{
						content = char2utf8(IMAGE_MSG_MICRO_VIDEO);
						break;
					}
				case data::MSG_TYPE_CARD:
					{
						content = char2utf8(CARD_MSG_TIP);
						break;
					}
				case data::MSG_TYPE_REVOKE:
					{
						content = char2utf8(RECALL_TIP_MSG);
						break;
					}
				case data::MSG_TYPE_IMG:
					{
						content = char2utf8(IMAGE_MSG_TIP);
						break;
					}
				case data::MSG_TYPE_FILE:
					{
						content = char2utf8(FILE_MSG_TIP);
						break;
					}
				case data::MSG_TYPE_TIP:
					{
						content = char2utf8(PROMPT_MSG_TIP);
						break;
					}
				case data::MSG_TYPE_PICTEXT:
					{
						//解析图文消息标题显示
						service::jst_picWithTextMsg picTxtMsg;
						service::logic_jsonTransToStruct(service::json_PicWithText, json, &picTxtMsg);
						if (picTxtMsg.vtMsgs.size() > 0)
						{
							content = picTxtMsg.vtMsgs.at(0).title;
						}
						if (content.empty())
						{
							content = char2utf8(IMAGE_TXT_MSG);
						}
						break;
					}
				case data::MSG_TYPE_TEMPL:
					{
						content = char2utf8(TEMPLATE_MSG_TIP);
						break;
					}
				case data::MSG_TYPE_WEB:
					{
						content = char2utf8(WEBLINK_MSG);
						break;
					}
//暂时屏蔽其他消息类型解析仅支持文本消息，后期支持了再逐个放开
//			case data::MSG_TYPE_VIDEIO://视频消息
//			case data::MSG_TYPE_CONFER://视频会议消息
//				{
//					service::jst_TextMsg  picTxtMsg;
//					service::logic_jsonTransToStruct(service::json_conference, json, &picTxtMsg);
//#ifdef _WIN32
//					if ((picTxtMsg.conferType == 1) || (picTxtMsg.conferType == 3))
//					{
//						content = convert2utf8(MSG_AUDIOONLINE_TIP);
//					}
//
//					if ((picTxtMsg.conferType == 2) || ((picTxtMsg.conferType == 4)))
//					{
//						content = convert2utf8(MSG_VIDEOONLINE_TIP);
//					}
//#else
//					content = convert2utf8(MAC_NOT_MSG_AUDIO_TIP);
//#endif
//					break;
//				}
//			case data::MSG_TYPE_AUDIO:
//				{
//					content = convert2utf8(AUDIO_MSG_TIP);
//					break;
//				}
//			case data::MSG_TYPE_CARD:
//				{
//					content = convert2utf8(CARD_MSG_TIP);
//					break;
//				}
//			case data::MSG_TYPE_COMBINE:
//				{
//					content = convert2utf8(COMBIN_MSG_TIP);
//					break;
//				}
//			case data::MSG_TYPE_POSITION:
//				{
//					content = convert2utf8(POSITION_MSG_TIP);
//					break;
//				}
//			case data::MSG_TYPE_REVOKE:
//				{
//					content = convert2utf8(RECALL_TIP_MSG);
//					break;
//				}
//			case data::MSG_TYPE_DYNEXPRESSION:
//				{
//					content = convert2utf8(DYNAMIC_EMOJI_MSG);
//					break;
//				}
//			case data::MSG_TYPE_WEB:
//				{
//					content = convert2utf8(WEBLINK_MSG);
//					break;
//				}
//			case data::MSG_TYPE_TASK:
//				{
//					content = convert2utf8(TASK_MSG);
//					break;
//				}
//			case data::MSG_TYPE_NINEBLOCK:
//				{
//					content = convert2utf8(IMAGE_MSG_TIP);
//					break;
//				}
//			case data::MSG_TYPE_MINIVEDIO:
//				{
//					content = convert2utf8(IMAGE_MSG_MICRO_VIDEO);
//					break;
//				}
//			case data::MSG_TYPE_VOICE://音频消息
//				{
//#ifdef _WIN32
//					content = convert2utf8(MSG_AUDIOONLINE_TIP);
//#else
//					content = convert2utf8(MAC_NOT_MSG_AUDIO_TIP);
//#endif
//					break;
//				}
			default:
				{
					content = char2utf8(UNDEFINE_MSG_TIP);
					break;
				}
			}

		}
		return content;
	}
	std::string ParseJsonData::char2utf8(std::string src){
		std::string result("");
		char szutf8[buffersize] = {0};
		utils::char2utf8(src.c_str(),szutf8);
		result = std::string(szutf8);
		return result;
	}
	std::string ParseJsonData::utf82char(std::string src){
		std::string result("");
		char szchar[buffersize] = {0};
		utils::utf82char(src.c_str(),szchar);
		result = std::string(szchar);
		return result;
	}

}