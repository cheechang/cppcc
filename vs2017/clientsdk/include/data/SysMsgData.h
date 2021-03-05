#pragma once
#include <string>
#include "interface/Defines.h"
namespace data{
	///ϵͳ��Ϣ����
	enum SysOperType
	{
		eSysIgnore = 1,	///<����
		eSysAgree,		///<ͬ��
		eSysRefuse,		///<�ܾ�
		eSysRefuseForever,	///<�ܾ����������ٴ�����
	};
	class MsgProData {
	public:
		MsgProData() {
			applicationId = groupId = sendUserId = receiveUserId = 0;
			receiveUserName = sendUserName = sendUserPicture = groupName = portraitURL = "";
			msgType = 0;
		}
		int64 applicationId;
		int64 groupId;
		int64 sendUserId;
		int64 receiveUserId;
		int  msgType;
		std::string sendUserName;
		std::string sendUserPicture;
		std::string groupName;
		std::string portraitURL;
		std::string receiveUserName;
	};

	///ϵͳ��Ϣ
	struct SysMsg
	{
		SysMsg() :msgId(0), userId(0), groupId(0), time(0), msgType(0), isResponse(0), isRead(0), operType(0), subType(0) {}
		int64 msgId;       ///<��ϢID
		int64 userId;		///<�û�ID
		int64 groupId;     ///<ȺID Ⱥ�����Ϣ��ֵ
		int64 time;        ///<ʱ��
		int   msgType;     ///<��Ϣ����
		int   isResponse;  ///<�Ƿ��Ӧ
		int   isRead;      ///<�Ƿ��Ѷ�
		int   operType;    ///<�����
		int   subType;     ///<�Ӳ������ͱ�ʾ,  msgType=1ʱ 1:��Ӻ���,2:��ע   msgType=3	ʱ 1:����, 2:�������
		std::string userName;  ///<�û�����
		std::string groupName; ///<Ⱥ���� Ⱥ�����Ϣ��ֵ
		std::string avatar;///<��Ϣ��Դͷ��
		std::string info;  ///<��Ϣ����
	};
}