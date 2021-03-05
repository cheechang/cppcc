#pragma once
#include <string>
#include "interface/Defines.h"
#include "data/Optional.h"
namespace data{
	class UserBasicData{
	public:
		UserBasicData():classification(0),id(0),name(""),thumbAvatar(""){
		}
		Optional<int64> id;						///<id
		Optional<std::string> name;				   ///<����
		Optional<std::string> thumbAvatar;	       ///<����ͼ
		int classification;                          ///<�ܼ�
		Optional<std::string> extends;			///<��չ�ֶ�
	};
  class UserData{
  public:
	  UserData():gender(0),timeZone(0),id(0),name(""),avatar(""),extends(""),thumbAvatar(""),avatarUrl(""),thumbAvatarUrl(""){
	  }
	  virtual ~UserData(){}
  public:
	  Optional<int> gender;					    ///<�Ա�:1��2Ů0����
	  Optional<int> timeZone;					///<ʱ��
	  Optional<int64> id;						///<id
	  Optional<std::string> name;				///<����
	  Optional<std::string> avatar;			    ///<ԭͼͼ��
	  Optional<std::string> extends;			///<��չ�ֶ�
	  Optional<std::string> entExtends;        ///<��ҵ��չ��Ϣ
	  Optional<std::string> thumbAvatar;		///<����ͼ
	  Optional<std::string> avatarUrl;		    ///<ԭͼurl
	  Optional<std::string> thumbAvatarUrl;	    ///<����ͼurl
  };

  ///�˺���Ϣ
  class AccountInfo:public UserData 
  {
  public:
	  AccountInfo():nickId(""),phone(""),email(""),entExtends(""){}
  public:
	  Optional<std::string> nickId;			     ///<������
	  Optional<std::string> phone;              ///<�ֻ���
	  Optional<std::string> email;              ///<�����
	  Optional<std::string> entExtends;         ///<��ҵ��չ��Ϣ
  };

  /**
  * \struct st_entAppinfo
  * \brief Ӧ����Ϣ
  */
  struct  EntAppinfo
  {
	  std::string appSign;///< Ӧ�ñ�ʶ
	  std::string appName;///< Ӧ������
	  std::string appIcon;///< Ӧ��ͼ��
	  std::string appIconUrl; ///������Ӧ��ͼ��ȫ·��
	  int64 appID;        ///< Ӧ��ID
	  std::string appHomeUrl;///< Ӧ����ҳ
	  int64 entID;           ///< entID
	  std::string entName;   ///< Ӧ������
	  std::string appSecret; ///< Ӧ����Կ
	  std::string appToken;  ///< Ӧ��TOKEN
	  std::string appMenus;  ///< Ӧ�ò˵�
	  int8	openIDEncoded; ///< openID�Ƿ���룬0:�����룬1:����
	  std::string subAccount;///< Ӧ�����˺�
	  ///������  1 H5Ӧ�ã�2 �ƶ�Ӧ��
	  int8 appSubType;
	  ///�Ƽ� 1 �� ��2 ��
	  int8 recommend;
	  /// Ĭ�ϰ�װ 1 �� ��2 ��
	  int8 defaultInstall;
	  ///��չ�ֶ� json ��ʽ��mainUrl H5��ҳ��adminUrl ��̨�����ַ��myUrl �������ĵ�ַ
	  std::string extend;
	  ///�豸���� 1(iPhone_E), 2(iPad_E), 3(iPhone), 4(iPad), 5(androidPhone), 6(androidPad)
	  std::string deviceTypes;
	  ///��Ϣ��ʷ��ַ
	  std::string messageHistoryUrl;
	  ///�Ƿ������Զ���˵�   1 ����  0ͣ��
	  std::string menuOpen;
	  ///�Ƿ������Զ���˵���Ӧ�¼�  1���� 0ͣ��
	  std::string replyMenuOpen;
	  ///���ܿ��� 2
	  int8 appType;
	  ///���ں�״̬
	  int8 status;
	  ///1:���ĺ�2����ҵ��
	  int8 subOrAppType;
	  ///Ӧ�ù��ܽ���
	  std::string appFunctintroduce;
	  ///���ںŽ���
	  std::string appDescription;
	  ///���ںŴ�����id  ������appidҲ������userid
	  int64 ownerId;
	  ///Ӧ���Ƿ���Ҫǿ����Ȩ1��Ҫ��0����Ҫ
	  int8 forceGrant;
	  ///��Ȩ����
	  std::string grantIntroduce;
  };

  ///����������Ŀ
struct UserLocalSetting
{
    std::string key; ///<��ʶ
    std::string val; ///<ֵ
};

  ///����������
  struct PersonalData
  {
	  PersonalData(){}
	  PersonalData(int16 t, int16 v) :type(t), val(v)
	  {}
	  int16 type; ///<��ʶ
	  int16 val; ///<ֵ
  };

  struct UserInfoSetData
  {
	  UserInfoSetData():isSearchByDoodNum(0),isSearchByPhoneNum(0),isSearchByMailNum(0){}
	  int8 isSearchByDoodNum;       ///ͨ�������Ų���
	  int8 isSearchByPhoneNum;      ///ͨ���绰�Ų���
	  int8 isSearchByMailNum;       ///ͨ���������
	  //  int8 issearchbynewfriend;	/// ͨ�������Ѳ���  0���� 1������ Ĭ��0
	  //  int8 isshareupdate;			///<�������   0��ʾ���� 1����ʾ���� Ĭ��0
	  //  int8 isnewmsgtip;			///<����Ϣ֪ͨ�Ƿ�����0���� 1������ Ĭ��0
	  //  int8 ismultiservmsgtip;		///<���������Ϣ֪ͨ�Ƿ�����0��ʼ����ʾ 1ʼ����ʾ Ĭ��0
	  //  int8 ismultiservfrdtip;		///<���������V�����ʼ������ 0��ʼ����ʾ 1ʼ����ʾ Ĭ��
	  //  int8 ismultiservpersontip;	///<�������������@�����ʼ������0��ʼ����ʾ 1ʼ����ʾ Ĭ��0
  };

  struct ZXSearchParam
  {
	  std::string sector;                 ///< ���
	  std::string name;                   ///< ����
	  std::string nation;                 ///< ����
	  std::string gender;                 ///< �Ա�
	  std::string currentPosition;        ///< ְ��
	  std::string group;                  ///< ���
	  std::string specialCommittee;       ///< רί��
	  std::string specialCommitteeDuty;   ///< רί��ְ��
	  std::string CPPCCPosition;          ///< ��Эְ��
	  std::string myLocation;             ///< ���ڵ�
  };

  struct ZxTopInformation
  {
	  ZxTopInformation() : id(0), createUserId(0), groupId(0),
	  createTime(0), topUserId(0), updataTime(0), status(0), topType(0)
	  {}
	  int64 id;
	  int64 createUserId;   //�ö��� 
	  int64 groupId;        //�ö�ȺID 
	  int64 createTime;     //�ö�ʱ�� 
	  int64 topUserId;      //���ö��� 
	  std::string topContent;  //�ö����� 
	  int64 updataTime;     //�޸�ʱ�� 
	  int8 status;        //�ö���Ϣ״̬ 
	  int8 topType;       //�ö���Ϣ����
	  int64 msgId;		 //�ö���Ϣ��
  };
}