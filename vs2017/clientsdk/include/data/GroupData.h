#pragma once 
#include <string>
#include "interface/Defines.h"
#include "data/Optional.h"
#include "data/UserData.h"
namespace data{
	///Ⱥ����Ϣ
	class TinyGroup
	{
	public:
		TinyGroup() :level(0), type(0), createrId(0), cantExit(true), groupId(0)
		{}
		virtual ~TinyGroup(){}
		virtual void init(){}

		bool operator == (const TinyGroup& rhs) const
		{
			return (level == rhs.level) && (cantExit == rhs.cantExit) && (createrId == rhs.createrId) &&
				(groupId == rhs.groupId) && (groupName == rhs.groupName) && (avatar == rhs.avatar) &&
				(pinyin == rhs.pinyin) && (server == rhs.server) && (avatarUrl == rhs.avatarUrl);
		}
		bool operator > (const TinyGroup& rhs) const
		{
			return pinyin.value()>rhs.pinyin.value();
		}
	public:
		Optional<int> level;				///<Ⱥ�ȼ���1,2,3,4)1����ʱȺ��2����ͨȺ
		Optional<int> type;					///<Ⱥ���ͣ�1,2)1����֯Ⱥ��2����ҵȺ
		Optional<bool> cantExit;			///<�Ƿ�������Ⱥ
		Optional<bool> isVSign;				///<�Ƿ�Ϊv��Ⱥ
		Optional<int64> createrId;			///<������ID
		Optional<int64> groupId;			///<ȺID
		Optional<std::string> groupName;	///<Ⱥ��
		Optional<std::string> avatar;		///<Ⱥͷ��
		Optional<std::string> avatarUrl;	///<Ⱥͷ��url
		Optional<std::string> pinyin;		///<����ƴ��
		Optional<std::string> server;		///<������
		Optional<std::string> groupType;	///<Ⱥ����
	};
	///Ⱥ��
	class Group 
	{
	public:
		Group() :createTime(0), relatedGroupId(0), relatedEntId(0), memberNums(0), isSearch(false),
			groupMessageContentMode(0)
		{}
		bool operator == (const Group &rhs) const
		{
			return (brief == rhs.brief) && (bulletin == rhs.bulletin) && (extend == rhs.extend) && 
				(createTime == rhs.createTime) && (relatedGroupId == rhs.relatedGroupId) &&
				(relatedEntId == rhs.relatedEntId) && (memberNums == rhs.memberNums) &&
				(isSearch == rhs.isSearch) && (groupMessageContentMode == rhs.groupMessageContentMode) &&
				(privateMsgPwd == rhs.privateMsgPwd) && (info == rhs.info);
		}
	public:
		Optional<std::string> brief;			///<Ⱥ���
		Optional<std::string> bulletin;			///<Ⱥ����
		Optional<std::string> extend;			///<Ⱥ��չ�ֶ�
		Optional<int64> createTime;				///<����ʱ��
		Optional<int64> relatedGroupId;			///<����ȺID
		Optional<int64> relatedEntId;			///<������ҵID�����ڴ�ID��������ҵȺ
		Optional<int> memberNums;				///<Ⱥ��Ա����
		Optional<bool> isSearch;				///<�Ƿ���������
		Optional<int8> groupMessageContentMode; ///<Ⱥ��Ϣ֪ͨ����: 1������(��ʾ����)  2���ر�(��ʾ֪ͨԴ����������)  Ĭ�Ͽ��� groupMessageContentMode.
		Optional<int8> personalMessageContentMode; ///<����Ⱥ��Ϣ֪ͨ����: 1��֪ͨ����  2��֪ͨԴ����������  3����ȫ����
		Optional<std::string> privateMsgPwd;	///<˽������ 
		Optional<std::string> chatImage;		///<Ⱥ�ı��� 
		Optional<TinyGroup> info;				///<Ⱥ��Ϣ
	};

	///Ⱥ����
	class GroupUpdate
	{
	public:
		GroupUpdate() :groupSearch(0), groupMessageContentMode(0)
		{}

		Optional<std::string> groupName;				///<Ⱥ����
		Optional<std::string> groupIcon;				///<Ⱥͼ��
		Optional<std::string> groupBrief;				///<Ⱥ���
		Optional<std::string> groupBulletin;			///<Ⱥ����
		Optional<std::string> groupBackgroundURL;		///<Ⱥ����ͼƬ
		Optional<int8> groupSearch;						///<Ⱥ�Ƿ���Ա��ⲿ���� 1���� 2������
		Optional<int8> groupMessageContentMode;			///<Ⱥ��Ϣ֪ͨ����: 1������(��ʾ����)  2���ر�(��ʾ֪ͨԴ����������)  Ĭ�Ͽ���
		/**Ⱥ��չ�ֶ�,��json��ʽ,Ŀǰ��
		* ����ID�� policeTypeID
		* ����---ʡ��ID��provinceID
		* ����---��ID�� cityID
		* ˽��ģʽ��privateMsg��1Ϊ����˽��   0��ʾ������˽��
		*/
		Optional<std::string> extendProperties;
	};
	///Ⱥ��Ա
	class Member : public UserData 
	{
	public:
		Member() :groupId(0), team(0), memberType(0), isApp(false)
		{}
		virtual void init(){}

		bool operator == (const Member& rhs) const
		{
			return (groupId == rhs.groupId) && (team == rhs.team) && (isApp == rhs.isApp) &&
				(memberType == rhs.memberType) && (remark == rhs.remark);
		}
	public:
		Optional<int64> groupId;		///<Ⱥid
		Optional<int>  team;			///<����
		Optional<int8> memberType;		///<��Ա���ͣ�1.��ͨ 2.����Ա 3.��������Ա
		Optional<bool> isApp;			///<�Ƿ�Ϊ������
		Optional<std::string> remark;   ///<Ⱥ��ע
		Optional<std::string> pingyin;			///<ƴ��
		Optional<std::string> sector;
	};

	///Ⱥ�ļ�
	class FileInfo
	{
	public:
		FileInfo() : fileid(0), userid(0), time(0)
		{}
		
		int64 fileid;				///<�ļ�id
		int64 userid;				///<�ϴ���id
		std::string size;			///<�ļ���С
		int64 time;					///<�ϴ�ʱ��
		std::string name;			///<�ļ���
		std::string auther;			///<�ϴ���
		std::string url;			///<�ļ�url
		std::string path;			///<�ļ�����·��
		std::string encrypt_key;	///<����KEY
	};

	struct UploadFileProperty
	{
		UploadFileProperty() :isP2p(0), isJS(0), localid(0), targetid(0), type(0), noStore(0),isResume(false){}
		int64 targetid;			///<�Է���targetId(�˻�Ⱥ)
		int64 localid;			///<��ʾ�ļ���ΨһlocalId ͨ��time()����
		int16 type;				///<��������
		std::string localPath;	///<�ϴ��ļ��ı���·��
		std::string dirPath;	///<�ļ��б���·�����ϴ��ļ���ʱʹ��
		std::string msg;		///<���ڴ洢�Զ�����Ϣ
		std::string encryptKey; ///<��Կ  ///�ϵ��ϴ���key����һ��
		int8  isP2p;            ///<�Ƿ��Ե� 0 �� 1 ��.
		int8   isJS;             ///< �Ƿ�JS�ϴ�ͼƬ,0 �� 1 ��
		int8	  noStore;		///< �Ƿ񲻴���Ϣ���ļ���Ϣ�����ݿ�0 �� 1 ��
		bool  isResume;         ///<�Ƿ�ϵ��ϴ�
		std::string filename;
		int64 filesize;
	};
}