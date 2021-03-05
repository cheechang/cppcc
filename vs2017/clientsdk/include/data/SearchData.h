#pragma  once

#include <vector>
namespace data{
	///��������
	enum SearchResultType
	{
		USER_TYPE = 1,        //����
		GROUP_TYPE = 2,        ///Ⱥ
		APP_TYPE = 3,		   ///<���ں�
	};
	enum BuddyType {
		IS_NOTBUDDY = 0,   //���Ǻ���
		IS_BUDDY,                 //�Ǻ���
		IS_MYSELF                //���Լ�
	};
	///////������ϵ��Ⱥ�ȷ��ص�����
	class SearchResultInfo{
	public:
		SearchResultInfo():resultType(USER_TYPE),targetid(0),buddyType(IS_NOTBUDDY),isGroupMem(false){
			name = avatar = "";
		}
		~SearchResultInfo(){};
	public:
		int64			 targetid;			 ///Ŀ��id
		std::string		 name;				///����
		std::string		 avatar;			// ͷ��
		SearchResultType    resultType;	     ///<�������  1�ˣ�2Ⱥ��3���ں�
		BuddyType  buddyType;
		bool isGroupMem;
	};
}