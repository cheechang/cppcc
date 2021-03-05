#pragma once

#include "SDKTypes.h"
#include "Optional.h"
#include <string>

namespace model
{
///用户信息
class User 
{
public:
	User() : gender(0), timeZone(0), id(0)
	{}
	virtual ~User(){}
	virtual void init(){}

public:
	Optional<int> gender;					///<性别:1男2女0保密
	Optional<int> timeZone;					///<时区
	Optional<int64> id;						///<id
	Optional<std::string> name;				///<名称
	Optional<std::string> avatar;			///<原图图像
	Optional<std::string> extends;			///<扩展字段
	Optional<std::string> entExtends;        ///<企业扩展信息
	Optional<std::string> thumbAvatar;		///<缩略图
	Optional<std::string> avatarUrl;		///<原图url
	Optional<std::string> thumbAvatarUrl;	///<缩略图url
};

typedef SSharedPtr<User> UserPtr;


} /*namespace model*/
