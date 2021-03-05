#pragma once

#include "../extModel/packet.h"

//多点请求结构
namespace model
{
	/*
	* 多点请求
	* 
	* [参数需求]:
	*  1.reqType=1: groupId/roomId/roomName/members
	*  2.reqType=2: groupId/roomId/members
	*  3.reqType=3: groupId/roomId/members
	*  4.reqType=4: groupId/roomId
	*  5.reqType=5: groupId/roomId/annotation="click/busy/..."
	*/
	struct multiRequest {
		multiRequest() : reqType(0), groupId(0) {}
		int8 reqType;					///< 请求类型(1.call 2.invite 3.intoroom 4.join 5.hungup 6.keepalive)
		std::string annotation;			///< 请求注释
		int64 groupId;					///< 群Id
		std::string	roomId;				///< 房间Id
		std::string roomName;			///< 房间名称
		std::vector<int64> members;		///< 成员列表
		std::string extendJson;			///< 扩展Json
	};
}
