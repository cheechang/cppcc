#pragma once

#include "../model/SDKTypes.h"
#include <string>
#include <vector>
#include "../model/Optional.h"
#include <map>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN ///��ֹ�ظ�����
#include <Windows.h>
#else
//
#endif

namespace model
{

    // ��������
    struct MsgProperties {
        MsgProperties() {}

        std::string timeZone;       ///< ʱ��
        std::string timeTask;       ///< ����ʱ��
        std::string isFinish;       ///< �Ƿ����     0��δ��� 1�����
        std::string isTask;         ///< ������     0�������� 1������
        std::string isRead;         ///< �Ƿ��Ѷ�     0��δ��   1���Ѷ�
    };

    // task
    struct Task
    {
        Task() :fromeUserID(0), sendTime(0), msgID(0), top(0), targetID(0)
        {
        }

        int64 fromeUserID;                  ///< �Լ����͵�����ֶ���0
        int64 sendTime;                     ///< ����ʱ��
        std::string body;                   ///< ��Ϣ��
        int64 msgID;                        ///< ����ID
        MsgProperties msgProperties;
        std::string relatedUsers;           ///< ��������Ⱥȫ���Ա������ȺID�������Բ����ˣ������˵�ID����
        std::vector<int64> vt_relatedUsers; ///< ���ص�ʱ����
        int32 badwordType;                  ///< ���˴�����
        std::vector<std::string> vt_badword;///< ���˴�
        int8 top;                           ///< �Ƿ��ö�   0�����ö� 1���ö�
        int64 targetID; 		            ///< �����ߣ�����ΪȺ������
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///����
    struct room
    {
        room() :roomID(0), top(0)
        {}

        int roomID;                         ///< ����ID
        std::string roomName;               ///< ������
        std::string roomMember;             ///< �����Ա
        std::vector<int64> vt_roomMember;   ///< ���ص�ʱ����
        int8 top;                           ///< �Ƿ��ö�   0�����ö� 1���ö�
        std::string portraitURL;            ///< ͷ��
    };
    /////////////////////////////////////////////////////////////////////////

    /// ��ҵ��Ϣ
    struct entpriseInfo
    {
        entpriseInfo() :
        enterpriseID(0),
        sector(0),
        sectorDetail(0),
        type(0),
        provinceID(0),
        cityID(0),
        areaID(0),
        status(0),
        creationDate(0),
        updatedDate(0){}

        int64 enterpriseID;         ///< ��ҵID enterpriseID.
        std::string fullName;       ///< ��ҵȫ�� fullName.
        std::string shortName;      ///< ��ҵ��� shortName.
        std::string keyWords;       ///< ��ҵ�ؼ��� keyWords.
        int64 sector;               ///< ��ҵ������ҵ sector.
        int64 sectorDetail;         ///< ��ҵ������ҵ�ľ�����һ�� sectorDetail.
        int8 type;                  ///< ��ҵ���� type.
        int64 provinceID;           ///< ��ҵ����ʡ�� provinceID.
        int64 cityID;               ///< ��ҵ������ cityID.
        int64 areaID;               ///< ��ҵ�������� areaID.
        std::string address;        ///< ��ҵ��ַ address.
        std::string postcode;       ///< ��ҵ�ʱ� postcode.
        std::string phone;          ///< ��ҵ�绰 phone.
        std::string fax;            ///< ��ҵ���� fax.
        std::string email;          ///< ��ҵ���� email.
        std::string homepage;       ///< ��ҵ��ҵ homepage.
        std::string introduction;   ///< ��ҵ��� introduction.
        std::string logUrl;         ///< ��ҵlogURL��ַ logUrl.
        int8 status;                ///< ��ҵ״̬��1:���ͨ����2��δ��ˣ�3�����δͨ�� status.
        int64 creationDate;         ///< ע��ʱ�� creationDate.
        int64 updatedDate;          ///< �޸�ʱ�� updatedDate.
    };


    /// ��֯��Ϣ
    struct OrganizationInfo
    {
        OrganizationInfo() :
        orgID(0),
        enterpriseID(0),
        leaf(0),
        parentOrgID(0),
        orderNum(0),
        branchID(0),
        departLevel(0),
        subOrgNum(0),
        subUserNum(0),
        isHidden(0),
        provinceID(0),
        cityID(0),
        areaID(0) {}

        int64 orgID;                ///< ��֯����ID orgID.
        int64 enterpriseID;         ///< ��ҵID enterpriseID.
        std::string orgName;        ///< ��֯�������� orgName.
        std::string orgCode;        ///< ��֯�������� orgCode.
        int8 leaf;                  ///< �Ƿ�Ҷ�ڵ� leaf.
        int64 parentOrgID;          ///< ���ڵ� parentOrgID.
        std::string remark;         ///< ��ע remark.
        int64 orderNum;             ///< ���� orderNum.
        int64 branchID;             ///< �칫��ID branchID.
        std::string departID;       ///< ɾ�� departID.
        int8 departLevel;           ///< ��֯���� departLevel.
        int64 subOrgNum;            ///< �ݹ���������¼���֯�� subOrgNum.
        int64 subUserNum;           ///< �ݹ���������¼���Ա�� subUserNum.
        int8 isHidden;              ///< �Ƿ�����, 1�Ա����Ź��� 2�����в��Ź�����3�Բ��ֲ��Ź��� isHidden.
        int64 provinceID;           ///< ʡ��ID provinceID.
        std::string provinceName;   ///< ʡ������ provinceName.
        int64 cityID;               ///< ��ID cityID.
        std::string cityName;       ///< ������ cityName.
        int64 areaID;               ///< ��ID areaID.
        std::string areaName;       ///< ������ areaName.
        std::string orgNamePinyin;  ///< ƴ�� orgNamePinyin.
    };

    /// ��ҵ��Ա��Ϣ
    struct EntpriseUserInfo
    {
        EntpriseUserInfo() :
        userID(0),
        enterpriseID(0),
        orgID(0),
        roleID(0),
        status(0),
        orderNum(0),
        newOrgID(0){}

        int64 userID;               ///< �û�ID userID.
        int64 enterpriseID;         ///< ��ҵID enterpriseID.
        int64 orgID;                ///< ��֯����ID orgID.
        int64 roleID;               ///< ��ɫID roleID.
        std::string enName;         ///< ��ҵ���û����� enName.
        std::string duty;           ///< ��ҵ���û�ְλ duty.
        std::string enMail;         ///< ��ҵ���û�email enMail.
        std::string enMobile;       ///< ��ҵ���û��ֻ��� enMobile.
        int8 status;                ///< ��ҵ�˺��Ƿ�ͣ�� 1������ 2��ͣ�� status.
        int64 orderNum;             ///< ��Ա���� orderNum.
        int64 newOrgID;             ///< �û��޸���֯����ʹ�ã���ʾ�û�����֯���������޸�ʱ���û�������֯����ʱ��ʹ��newOgrID������orgID newOrgID.
        std::string orgName;        ///< ��֯�� orgName.
        std::string extend;         ///< ��չ��Ϣ extend.
        std::string accountName;    ///< �˺����� accountName.
        std::string enNamePy;       ///< ƴ�� enNamePy.
        int8  bizStatus;            ///< ҵ��״̬ ҵ��״̬��1����ʼ״̬��2���ڸ߹�Ⱥ
        std::string userHead;       ///< ͷ��
        std::string userHeadUrl;    ///<ͷ��ȫ·��
        std::string power;         ///< Ȩ��
    };

    /// �Ŷ��û���ѯ����
    struct EnterpriseUserQueryInfo
    {
        EnterpriseUserQueryInfo() :
        entID(0),
        entOrgID(0),
        pageNo(0),
        pageSize(100),
        entUserID(0),
        bizStatus(0),
        status(0){}

        std::string username; 	    ///< �û����� username.
        int64 entID; 			    ///< ��ҵID entID.
        int64 entOrgID; 		    ///< ��֯�ܹ�ID entOrgID.
        int32 pageNo; 			    ///< ��ҳҳ�� pageNo.
        int32 pageSize; 		    ///< ��ҳÿҳ��С pageSize.
        int64 entUserID; 		    ///< ��ҵ�û�ID.
        int8 bizStatus;             ///< ҵ��״̬��1��Ĭ�ϣ�2���ڸ߹ܲ�.
        int8 status;                ///< ��ҵ�û�״̬.
    };

    /// note
    struct _BaseNoteinfo__isset
    {
        _BaseNoteinfo__isset() :id(false), lastChgTime(false), sendUserId(false), targetId(false), type(false),
        content(false), title(false), key(false), isReminder(false), rmdTime(false), isArchive(false)
        {}
        bool id;						    ///���±�Ψһ��ʶ
        bool lastChgTime;					///����޸�ʱ��,����
        bool sendUserId;					///���͵���
        bool targetId;						///��Դ �˻���Ⱥ		
        bool type;
        bool content;						///����     �4096���ַ�	
        bool title;							///����     �128�ַ�
        bool key;							///�ؼ���(��ǩ),  ������ �128�ַ� ,����Ϊ��
        bool isReminder;					///�Ƿ�������
        bool rmdTime;						///����ʱ��
        bool isArchive;						///�Ƿ�鵵
    };
    ///���±�
    struct BaseNoteInfo
    {
        BaseNoteInfo() :isNet(false), id(0), lastChgTime(0), sendUserId(0), targetId(0), type(0), isReminder(0), rmdTime(0), isArchive(0){}

        bool isNet;                             ///�Ƿ�ʹ������ӿ�
        Optional<int64> id;						///<���±�Ψһ��ʶ     �ղ�ID
        Optional<int64> lastChgTime;		    ///<����޸�ʱ��,����  ����ʱ��
        Optional<int64> sendUserId;				///<���͵���           ��Ϣ��ԴId  
        Optional<int64> targetId;				///<��Դ �˻���Ⱥ      ȺId
        /**
        *  ��8λ ���� 1. �ı���2��ͼƬ��3����Ƶ��4����Ƶ��5��URL
        *  ��8λ 1. ���أ� 0. ����
        */
        Optional<int8> type;
        Optional<int16> netType;
        /**
        �����ļ�����
        1. �ı���URL ֱ�Ӵ洢���ݡ�
        2. ���ı����ͣ��洢������ַ�������ַ�ͱ��ص�ַ���ɡ�
        */
        Optional<std::string> content;		///<���� �4096���ַ�	    �ղ���Ϣ

        //��Щ���Ǳ��ؼ��±��ֶ�
        Optional<std::string> title;		///<���� �128�ַ�
        Optional<std::string> key;			///<�ؼ���(��ǩ),  ������ �128�ַ� ,����Ϊ��
        Optional<int8> isReminder;			///<�Ƿ�������
        Optional<int64> rmdTime;			///<����ʱ��
        Optional<int8> isArchive;			///<�Ƿ�鵵

        //�����������ղ��ֶ�
        Optional<std::string> msgProperties;	///<��Ϣ����
        Optional<std::string> fileName;		    ///<�ļ���
        Optional<std::string> exts;			    ///<��չ�ֶ�
    };
    struct searchNoteInfo{
        searchNoteInfo() :isNet(false), beginID(0), offset(0), offsetFlag(0), type(0){}

        bool isNet;         ///< �Ƿ�ʹ������ӿ�  
        int64 beginID;      ///< ��ʼ��ϢID, offsetFlag = 0 beginID = 0ʱ�������������ϢId���в���  
        int32 offset;       ///< ��ѯ������(��ֵΪ0�����ѯȫ��) 
        int8  offsetFlag;   ///< ƫ�Ʊ�־��0.��ϢId�ɴ�Сƫ�� 1.��ϢId��С����ƫ�� offsetFlag.

        int16 type;         ///< 0:��ѯ����; 1:����msgType; 2:������Ϣ���� 3:�����ļ���;
        /**
        * ����3���ֶ�ÿ��ֻ�ܸ�һ���ֶθ�ֵ��ʣ��2���ֶβ��ø�ֵ
        */
        int8 is_all;        ///< 1:��ȡȫ��.
        int8 is_archive;    ///< 1:��ȡδ�鵵 2:��ȡ�Ѿ��鵵  
		std::string key;    ///< ���ݹؼ��ʲ��� 

        /**
          * �����ѯ����������key������ѯ
          * collectUserId   �ղ���Id���ش�
          * messageType     ������Ϣ���Ͳ�ѯ
          * message         ������Ϣ���ݲ�ѯ
          * fileName        �����ļ����Ʋ�ѯ
          * startTime       ������ʼʱ��
          * endTime         ��������ʱ��
        **/
        std::map<std::string, std::string> params;  ///< �����ѯ���� 
    };

    struct OrgAndUserSearchIn {
        OrgAndUserSearchIn() :
        type(0),
        userID(0),
        pageNum(0),
        pageSize(0) {
            orgIDs.clear();
        }

        int8  type;                                 /// 4����֯����ģ������ 5��������Ա�ӿ�
        int64 userID;                               /// �û�ID
        std::string name;                           /// ����
        int32 pageNum;                              /// ҳ��
        int32 pageSize;                             /// ҳ��	
        std::vector<int64> orgIDs;                  /// ѡ��Ĳ���ID����(type=5ʱ��ֵ)
    };

    struct OrgSearchUserInfo{
        EntpriseUserInfo uBean;
        std::string oPower;
    };
}