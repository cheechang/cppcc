#pragma once
#include <vector>
#include "User.h"
#include "../extModel/packet.h"
namespace model 
{
///账号信息

class Account : public User 
{
public:
	Account() :birthday(0)
	{}
	void init(){}

public:

	Optional<int64> birthday;                 ///<生日
	Optional<std::string> nickId;			  ///<豆豆号
	Optional<std::string> phone;              ///<手机号
	Optional<std::string> email;              ///<邮箱号
	Optional<std::vector<std::string> > phones;   ///<手机号
	Optional<std::vector<std::string> > emails;   ///<邮箱号
	Optional<std::string> sign;               ///<签名
	Optional<std::string> area;              ///<地区
	Optional<std::vector<model::AccountType> > accounts;        ///<账号
};

} /*namespace model */
