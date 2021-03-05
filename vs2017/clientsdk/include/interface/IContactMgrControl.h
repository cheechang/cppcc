#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include "data/ContactData.h"
#include "data/ChatData.h"
#include "data/SearchData.h"
namespace control {
	class IContactMgrControl:public IControl {
	public:
	/**
	* \brief ������ϵ��ͷ�����
	* @param[out]  cb _1 ����Ŀ��ID���˻���Ⱥ;  _2	  ����ͷ��;
	*/
	virtual void RegContactHeadImgUpdateCb(CFunction < void(int64, const std::string&) > cb) = 0;
	
	/**
	* \brief ���ü�������״̬���µĻص�
	* @param[out] cb _1 ����״̬ ��packet.h
	*/
	virtual void RegPresentCb(CFunction< void(const data::OnlineState&) > cb) = 0;

	/**
	*  \brief ���ú�����Ϣ���µĻص�
	* @param[out] cb _1 �����������  1: ���� 2: ���£�3: ɾ��; _2  ����������ϵ��; 
	*/
	virtual void RegOperateBuddyCb(CFunction< void(int, const data::Contact&) > cb) = 0;

	/**
	* \brief ��������ˢ��
	* @param[out] cb _1 ����������� \n
	* 0x01 �����˱�ʶ����գգ��б���������б��� \n
	* 0x02�������˱�ʶ���գ��б�β����������б��� \n
	* 0x04 �����˱�ʶ�����к��������� \n
	* 0x08 �����˱�ʶ���ӵ�ǰ�գ��б��и��������б������������ʶ��� \n
	* 0x10 �����˱�ʶ���ӵ�ǰ�գ��б���ɾ�������б������������ʶ��� \n
	* [in] _2	  ����������ϵ��
	*/
	virtual void RegBuddyListCb(CFunction< void(int, std::vector<data::Contact>&) > cb) = 0;


	/*****************************************����ӿ�*******************************************/

	/**
	* \brief �����ϵ��
	* @param[in] userid ������ϵ��ID
	* @param[in] remark ������ϵ�˱�ע������Ϊ��
	* @param[in] info   ������֤��Ϣ
	* @param[out] cb  ������ս���ص� _1������Ϣ
	*/
	virtual void AddContact(int64 userid, const std::string &remark, const std::string &info, 
							CFunction<void(int)> cb) = 0;

	/**
	* \brief ֱ�������ϵ�ˣ�����Ҫ��֤
	* @param[in] userid ������ϵ��ID
	* @param[in] remark ������ϵ�˱�ע������Ϊ��
	* @param[in] info   ������֤��Ϣ
	* @param[out] cb  ������ս���ص� _1������Ϣ
	*/
	virtual void AddContactNoVerify(int64 userid, const std::string &remark, const std::string &info,
				CFunction<void(int)> cb) = 0;

	/**
	* \brief ��ȡ��ϵ����֤��ʽ
	* @param[in] userid ������ϵ��ID
	* @param[out] cb  ������ս���ص� _1 ������Ϣ _2��֤��ʽ
	*/
	virtual void GetVerifyType(int64 userid, CFunction<void(int, data::ContactVerifyType&)> cb) = 0;

	/**
	* \brief ɾ����ϵ��
	* @param[in] userid ������ϵ��ID
	* @param[out] cb  ������ս���ص� _1 ������Ϣ
	*/
	virtual void RemoveContact(int64 userid, CFunction<void(int)> cb) = 0;

	/**
	* \brief ������ϵ����Ϣ���Ǳ�&V��&��ע��
	* @param[in] info ������ϵ����Ϣ ��contact.h
	* @param[out] cb  ������ս���ص� _1������Ϣ
	*/
	virtual void UpdateContactInfo(data::Contact &info, CFunction<void(int)> cb) = 0;

	/**
	* \brief ��ȡ��ϵ���б� ��ͬ���ӿڣ�
	* @param[out]  contacts ���е���ϵ����Ϣ;
	*/
	virtual void GetContactList(std::vector< CSharedPtr<data::Contact> > &contacts, bool isSort = false, bool isFilterApp = true) = 0;

	/**
	* \brief ��ȡ��ϵ������״̬
	* @param[in] users ������ϵ�˼��� ���Ϊ�����������ϵ��״̬
	* @param[out] cb  ������ս���ص� _1 ������Ϣ; _2 ����״̬
	*/
	virtual void GetContactOnline(std::vector<int64> &users, CFunction<void(int, std::vector<data::OnlineState>&)> cb) = 0;

	/**
	* \brief ��ȡ��ϵ����Ϣ ( ͬ���ӿ� )
	* @param[in] userid �û�ID
	* @param[out] contact  ��ϵ����Ϣ
	* @return �������
	*/
	virtual bool GetContactInfo(int64 userid, data::Contact& contact) = 0;

	/**
	* \brief �ж���ϵ�����Լ��Ƿ��Ǻ��ѹ�ϵ ( ͬ���ӿ� )
	* @param[in] userid �û�ID
	* @return trueΪ����  false�Ǻ���
	*/
	virtual bool ContactIsBuddy(int64 userId) = 0;

	/**
	* \brief ����������ѯ��չ�ֶ���Ϣ ����dicKey��parentId��ͬ��ѯ��չ�ֶ�.
	* @param[in] dicKey Ҫ��ѯ���ֶ�
	* @param[in] parentID ����֯ID ��parentIdΪ-1ʱ��ʾ��ѯ���е���չ�ֶ�;��parentIdΪ-2 ʱ��dicKey��ѯ
	* @param[out] cb ������ս���ص�  _1������Ϣ _2���صĲ�ѯ��Ϣ
	*/
	virtual void queryExtendedField(const std::string &dicKey,int64 parentID, CFunction< void(int, std::vector<data::EnterpriseDictionary>&)> cb) = 0;
    
	/**
	* \brief ��ȡ������
	* @param[out] cb ������ս���ص�  _1������Ϣ _2������ID����
	*/
	virtual void getBlackList(CFunction<void(int,data::UserBasicData)> cb) = 0;

	/**
	* \brief ��Ӻ�����
	* @param[in] id Ҫ����ĺ�������ID
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void addBlackList(int64 id, CFunction<void(int)> cb) = 0;

	/**
	* \brief ɾ��������
	* @param[in] ids Ҫɾ���ĺ���������ID���ϣ�Ϊ����ɾ�����к������û�
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void removeBlackList(std::vector<int64> &ids, CFunction<void(int)> cb) = 0;


    /**
	* \brief ͨ���û�ID��ȡİ������Ϣ
	* @param[in] userid �����û�ID
	* @param[in] cb ������ս���ص�  _1������Ϣ  _2�û���Ϣ
	*/
	//virtual void getUserInfo(int64 userid, CFunction<void(int, data::Contact&)> cb) = 0;

	/**
	*\brief�������ȡ������Ϣ
	*/
	virtual void GetBuddyInfoFromNet(int64 userId,CFunction<void(int,data::Contact&)> cb) = 0;

		/**
	* \brief �ӱ������ݿ���в���
	* @param[in] key ����ؼ���
	* @param[in] cb ������ս���ص�  _1������Ϣ  _2�������
	*/
	virtual void searchFromLocal(const std::string &key, CFunction<void(int, std::vector<data::ChatInfo>&)> cb) = 0;
		/**
	* \brief ��������в���
	* @param[in] key ����ؼ���
	* @param[in] cb ������ս���ص�  _1������Ϣ  _2�������
	*/
	virtual void searchFromNet(const std::string &key, CFunction<void(int, std::vector<data::SearchResultInfo>&)> cb) = 0;

	/**
	* \brief ��ȡ������չ��Ϣ
	* @param[out] cb _1 
	*/
	virtual void GetBuddyExtendsInfo(int64 userId,CFunction<void(std::vector<data::EnterpriseDictionary>&)>cb) = 0;

	/**
	* \brief �����û�id��ҳ��ȡ��ҵ��
	* @param[in] req ��ҳ��ȡ������ҳ�룬ÿҳ��С��
	* @param[out] cb ������ս���ص� _1������Ϣ _2��ȡ�������
	*/
	virtual void getEntAccount(CFunction<void(int, std::vector<data::EnterpriseAccount>&)> cb) = 0;

	/**
	* \brief ͨ���û�ID��ȡ��ϸ��Ϣ(ͬ���ӿ�)
	* @param[in] userid �����û�ID
	* @param[in] info ������Ϣ
	*/
	virtual void getUserInfoSync(int64 userid, data::Contact& info)=0;
};
	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}