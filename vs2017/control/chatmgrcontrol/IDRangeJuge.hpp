#ifndef IDRANGEJUGE__HPP
#define IDRANGEJUGE__HPP
#include <model/SDKTypes.h>
#include <vector>
//��ҵ����
enum EntType{
	ENT_TYPE_INIT=0,
	ENT_TYPE_A,
	ENT_TYPE_B,
	ENT_TYPE_C,
	ENT_TYPE_OTHER
};

//��������
enum ObjType{
	OBJ_TYPE_INIT = 0,
	OBJ_TYPE_APP,
	OBJ_TYPE_USER,
	OBJ_TYPE_GROUP,
	OBJ_TYPE_ENTAPP,
	OBJ_TYPE_OTHER
};

//��ȡ��ҵ����
inline EntType GetEntType(int64 EntID){
	//����56λ�ȼ���java�е��޷������������>>>
	uint64 entSign = ((uint64)EntID>>56);
	if(0<=entSign && entSign<31)//����ֽ�0~31
		return ENT_TYPE_A;
	else if(64<=entSign && entSign<71)//����ֽ�64~71
		return ENT_TYPE_B;
	else if( 127 == entSign)
		return ENT_TYPE_C;//����ֽ�127
	else
		return ENT_TYPE_OTHER;//�������
}
//����targetid��ȡentID
inline int64 GetObjectEntID(int64 targetID){
	int64 entID = 0;
	EntType entType = ENT_TYPE_INIT;
	
	//��ȡ��ҵ����
	entType = GetEntType(targetID);
	switch(entType){
	case ENT_TYPE_A:
		{
		   entID = ((uint64)targetID>>24);//ǰ5���ֽ�Ϊ��ҵID
		   break;
		}
	case ENT_TYPE_B:
		{
		   entID = ((uint64)targetID>>32)<<8;//ǰ4���ֽ�Ϊ��ҵID���֣�Ȼ��һ���ֽڣ�Ϊ��ҵID
		   break;
		}
	case ENT_TYPE_C:
	   {
		   entID=((uint64)targetID>>40)<<16;//ǰ3���ֽ�Ϊ��ҵID���֣�Ȼ��2���ֽڣ�Ϊ��ҵID
		   break;
	   }
  }
  return entID;
}
//��ȡ��ҵ����id��Χ
inline std::vector<int64> GetObjetRange(int64 objectID,ObjType objType)
{
	std::vector<int64> range;
	//Ӧ�á��û���ȺID��Χ����һ���ֽ���ԭ�ֽڷ�Χ��*256�������ֽڷ�Χ�������ֽڷ�Χ��*256��Ϊ���ֽڷ�Χ
	EntType entType= GetEntType(objectID<<24);//��ҵID��ֻռ5�ֽڣ���3�ֽڴ�8�ֽ�ȥ�ж���ҵ���͡�
	int64 begin = 0;
	int64 end   = 0;
	int64 minAppId=0x15F90;//90000
    int64 maxAppId = 0x1869F;//99999
    int64 maxUserId = 0x7FFFFF;//8388607
    int64 maxGroupId = 0xFFFFFF;//1677721

	switch(entType){
		case ENT_TYPE_A:
	    {
			//��ҵID�������ֽڣ�ռ5�ֽڣ� + ԭʼ��Χ
			if(objType == OBJ_TYPE_APP){
				begin =(objectID<<24)+minAppId;
				end  =(objectID<<24)+maxAppId;
			}else if(objType == OBJ_TYPE_USER){
				begin =(objectID<<24)+maxAppId+1;
				end =(objectID<<24)+maxUserId;
			}else if(objType == OBJ_TYPE_GROUP){
				begin =(objectID<<24)+maxUserId+1;
				end =(objectID<<24)+maxGroupId;
			}
			break;
		}
		case ENT_TYPE_B:
		{
			//��ҵID����һ�ֽڣ�ȥһ�ֽڣ�������4�ֽڣ�ռ4�ֽڣ� + ԭʼ��Χ����1�ֽ�
			if( objType == OBJ_TYPE_APP){
				begin =((objectID>>8)<<32)+(minAppId<<8);
				end   =((objectID>>8)<<32)+(maxAppId<<8);
			}else if(objType==OBJ_TYPE_USER){
				begin =((objectID>>8)<<32)+(maxAppId<<8)+1;
				end   =((objectID>>8)<<32)+(maxUserId<<8);
			}else if(objType==OBJ_TYPE_GROUP){
				begin =((objectID>>8)<<32)+(maxUserId<<8)+1;
				end   =((objectID>>8)<<32)+(maxGroupId<<8);
			}
			break;
		}
		case ENT_TYPE_C:
		{
			//��ҵID����2�ֽڣ�ȥ2�ֽڣ�������5�ֽڣ�ռ3�ֽڣ� + ԭʼ��Χ����2�ֽ�
			if(objType==OBJ_TYPE_APP){
				begin =((objectID>>16)<<40)+(minAppId<<16);
				end =((objectID>>16)<<40)+(maxAppId<<16);
			}else if(objType==OBJ_TYPE_USER){
				begin =((objectID>>16)<<40)+(maxAppId<<16)+1;
				end   =((objectID>>16)<<40)+(maxUserId<<16);
				//begin = 9151315548882010113;
				//end   = 9151316092084224000;
			}else if(objType==OBJ_TYPE_GROUP){
				begin =((objectID>>16)<<40)+(maxUserId<<16)+1;
				end   =((objectID>>16)<<40)+(maxGroupId<<16);
			}
			break;
		}
	}
	range.push_back(begin);
	range.push_back(end);
	return range;
}
inline bool JudgeRange(int64 targetID,ObjType objType){
		bool inside = false;
		int64 entID= GetObjectEntID(targetID);
		std::vector<int64> range = GetObjetRange(entID,objType);
		if(targetID>=range[0] && targetID <= range[1]){
			inside = true;
		}
		return inside;
	}
inline bool isUser(int64 targetID){
	return JudgeRange(targetID,OBJ_TYPE_USER);
}

inline bool isGroup(int64 targetID){
	return JudgeRange(targetID,OBJ_TYPE_GROUP);
}

inline bool isApp(int64 targetID){
	return JudgeRange(targetID,OBJ_TYPE_APP);
}

inline bool isSameEnterpriseUser(int64 userID, int64 targetID){
	return (GetObjectEntID(userID) == GetObjectEntID(targetID));
}

#define	IS_MSG_USER		isUser
#define IS_MSG_GROUP	isGroup
#define IS_MSG_APP		isApp
#define IS_MSG_ENTAPP   isEntApp
#define IS_SAME_ENTERUSER isSameEnterpriseUser
#endif