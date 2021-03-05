#pragma  once

#include <vector>
namespace data{
	///聊天类型
	enum SearchResultType
	{
		USER_TYPE = 1,        //个人
		GROUP_TYPE = 2,        ///群
		APP_TYPE = 3,		   ///<公众号
	};
	enum BuddyType {
		IS_NOTBUDDY = 0,   //不是好友
		IS_BUDDY,                 //是好友
		IS_MYSELF                //是自己
	};
	///////查找联系人群等返回的数据
	class SearchResultInfo{
	public:
		SearchResultInfo():resultType(USER_TYPE),targetid(0),buddyType(IS_NOTBUDDY),isGroupMem(false){
			name = avatar = "";
		}
		~SearchResultInfo(){};
	public:
		int64			 targetid;			 ///目标id
		std::string		 name;				///名称
		std::string		 avatar;			// 头像
		SearchResultType    resultType;	     ///<结果类型  1人，2群，3公众号
		BuddyType  buddyType;
		bool isGroupMem;
	};
}