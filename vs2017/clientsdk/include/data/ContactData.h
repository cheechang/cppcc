#pragma  once
#include "data/UserData.h"
#include <vector>
namespace data{
	///��ϵ��
	class Contact : public UserData 
	{
	public:
		Contact() :isStar(0), isApp(0), birthday(0), isHidden(0)
		{}

		void init(){}

		bool operator == (const Contact & rhs) const
		{
			return (isStar == rhs.isStar) && (isApp == rhs.isApp) && (pinyin == rhs.pinyin) && 
				(acountName == rhs.acountName) && (remark == rhs.remark) && (server == rhs.server) && 
				(birthday == rhs.birthday) && (emails == rhs.emails) && (phones == rhs.phones) &&
				(chatImg == rhs.chatImg) && (privateMsgPwd == rhs.privateMsgPwd) &&
				(sign == rhs.sign) && (area == rhs.area) && (isHidden == rhs.isHidden);
		}

	public:
		Optional<int8> isStar;					 ///<�Ǳ���ѣ�1.�Ǳ���ѣ�2.�����Ǳ�
		Optional<int8> isApp;					 ///<�Ƿ���Ӧ�� 1.��,  2.��
		Optional<int8> isHidden;				 ///<�Ƿ������غ��� 1.��,  2.��
		Optional<bool> isTop;					 ///<�Ƿ��ö�
		Optional<std::string> pinyin;			 ///<����ƴ��
		Optional<std::string> acountName;		 ///<�����˺�
		Optional<std::string> remark;			 ///<��ע
		Optional<std::string> server;			 ///<������
		Optional<int64> birthday;				 ///<����
		Optional<std::string> chatImg;			 ///<���챳��
		Optional<std::string> sign;				///<ǩ��
		Optional<std::string> area;				///<����
		Optional<std::string> privateMsgPwd;	 ///<˽����Կ
		Optional<std::vector<std::string> > emails;	 ///<�ʼ�
		Optional<std::vector<std::string> > phones;	 ///<�绰
		Optional<std::string> mydevice; ///�ҵ��豸
	};
	///����״̬
	struct  OnlineState
	{
		OnlineState() :userID(0), connectID(0), deviceType(0), flag(0)
		{}
		int64 userID;   ///<�û�ID
		int64 connectID;
		int8 deviceType;  ///<�����豸����  1��PC��2���ֻ���3��pad��4����ҳ
		int8 flag;        ///<����״̬ -1�����ߣ�1:���ߣ�2 : ����, 3 : æµ, 4 : �뿪, 5 : �������, 6 : ������
	};
	///������֤��ʽ����
	struct ContactVerifyType
	{
		ContactVerifyType() :userid(0), type(0)
		{}
		int64 userid;
		int8  type;   ///<��֤����1��Ҫ��֤��Ϣ:2:�������κ������,3:�����κ������
	};

	struct EnterpriseDictionary{
		int32 id;                ///<��֯ID
		int32 parentId;          ///<����֯ID
		std::string dicValue;    ///<�ֶε�����
		std::string dickey;      ///<�ֶεļ�ֵ
		std::string dicRealValue;///��չ�ֶζ�Ӧ����ʵֵ
		/** ��չ�ֶΣ���ʽΪ{"isEdit":0,"isFriend":0,"isInput":0,"isLogin":0,"isShow":0,"isStrange":0},*/
		bool isEdit;//:�Ƿ�ͻ��˿ɱ༭;
		bool isFriend;//:�ͻ����Ƿ���ѿɼ�;
		bool isInput;//:�Ƿ�����ֶ�;
		bool isLogin;//:�Ƿ��¼���ֶ�;
		bool isShow;//:�ͻ�����֯�ܹ��Ƿ�ɼ�;
		bool isStrange;//:�ͻ����Ƿ�İ���˿ɼ�*/
		std::string extend; 
	};

	class EnterpriseAccount : public Contact
	{
	};
}