#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include <interface/IUserService.h>
namespace data{
  class UserBasicData;
  class UserData;
  class AccountInfo;
  struct EntAppinfo;
  struct PersonalData;
  struct UserLocalSetting;
  struct UserInfoSetData;
  struct UploadFileProperty;
  struct ZXSearchParam;
  struct ZxTopInformation;
}
namespace control{
	class IUserControl:public IControl{
	public:
		/***********************************************
		* @brief �û���Ϣ��ȡ�ӿ�
		* @param[out]servername ��������
		***********************************************/
		virtual CSharedPtr<data::AccountInfo> GetAccountInfo()=0;

		/**********************************************************************************************************
		*brief ��������ػ�ͷ���������
		*@param[out] cb _1Ŀ��ID���˻���Ⱥ  _2 ͷ��
		**********************************************************************************************************/
		virtual void RegHeadUpdate(CFunction < void(int64, const std::string&)> cb) = 0;

		virtual void uploadUserHead(std::string src, std::string thumb, CFunction < void(int, const std::string&, const std::string&)>cb) = 0;
		virtual void updateAccountInfo(data::AccountInfo& user,  CFunction < void(int)> cb) = 0;

		/**
		* \brief ͨ��Ӧ��ID��ȡӦ����Ϣ
		* @param[in] appId Ӧ�ó���ID
		* @param[out] cb ������ս���ص�  _1������Ϣ  _2Ӧ����Ϣ
		*/
		virtual void getAppInfo(int64 appId, CFunction<void(int, data::EntAppinfo&)> cb) = 0;
		
		/**
	* \brief �����˺�������
	* @param[in] flag ��������������
	* @param[in] type ��������������
	* @param[out] cb  �˺����ý���ص� _1 ������Ϣ
	*
	*  type = 1: �����Ƿ���ʾ������Ϣ flag: 0��ʾ 1����ʾ Ĭ��0
	*  type = 3: ���ö����Ų��� flag: 0���� 1������ Ĭ��0
	*  type = 4: �����ֻ��Ų��� flag: 0���� 1������ Ĭ��0
	*  type = 5: ��������Ų��� flag: 0���� 1������ Ĭ��0
	*  type = 6: ���÷������   flag: 0��ʾ���� 1����ʾ���� Ĭ��0
	*  type = 7: ����Ϣ֪ͨ�Ƿ����� flag: 0���� 1������ Ĭ��0
	*  type = 12: ���������Ϣ֪ͨ�Ƿ����� flag: 0��ʼ����ʾ 1ʼ����ʾ Ĭ��0
	*  type = 13: ���������V�����ʼ������ flag: 0��ʼ����ʾ 1ʼ����ʾ Ĭ��0
	*  type = 14: �������������@�����ʼ������ flag: 0��ʼ����ʾ 1ʼ����ʾ Ĭ��0
	*  type = 20: ���������Ѳ��� flag: 0���� 1������ Ĭ��0
	*/
	virtual void setSetting(int8 flag, int type) = 0;

	/**
	* \brief ��ȡ�˺�������
	* @param[in] type �����ȡ������������
	* typeΪ1���򷵻�ֵΪvalue_i64��һλ ���type=0,���������ֶΣ�ÿ���ֶ���ռ��λ��type���Ӧ\n
	* @param[out] cb ������ս���ص�  _1������Ϣ  _2�û�����
	*/
	virtual void getUserSetting(int type, CFunction<void(int,data::UserInfoSetData&)> cb) = 0;
		/**
	* \brief ���ø���������\n
    * @param[in] items �����������
	*		type: 1 ���գ��� �绰���� �ʼ� \n
	* ������������value:  1�������˿ɼ� 2�������ѿɼ� 3�����Լ��ɼ���Ĭ��1\n
	*		type: 4 ������֤��ʽ \n
	* ������������value:   1����Ҫ��֤��Ϣ, 2:�������κ������, 3:�����κ�����ӣ�Ĭ��1\n
	*		type: 5 V�������Ϣ��ʾģʽ\n
	*			value: 1:��ʾʼ�����������ѣ�2����ʾʼ������������ 3:��ʼ�����ѣ�Ĭ��1\n
	*		type: 6 @�������Ϣ����ģʽ\n
	*			value: 1:��ʾʼ�����������ѣ�2����ʾʼ������������ 3:��ʼ�����ѣ�Ĭ��1\n
	*		type: 7 ȫ��֪ͨ��Ϣ����չ��ģʽ\n
	*           value: 1:֪ͨ���飬2��֪ͨԴ���������� 3:��ȫ���أ�Ĭ��2\n
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void setPersonalData(std::vector<data::PersonalData> items, CFunction<void(int)> cb) = 0;
	virtual void getPersonalData(std::vector<int16> &types, CFunction<void(int, std::vector<data::PersonalData>&)> cb) = 0;
		/**
		* \brief ���ü����û���Ϣ���µĻص�������������
		* @param[out] cb ע������ͻص� _1 �û���Ϣ
		*/
	virtual void regOperateUserCb(CFunction<void(data::AccountInfo&)> cb) = 0;

    /**
	* \brief ��ȡ��������
	* @param[out] result,��������
	*/
    virtual bool  getLocalSettingSync( std::vector<std::string> &keys, std::vector<data::UserLocalSetting> &result )= 0;
	
   /**
	* \brief ���ӱ������ã��Լ�ֵ�Է�ʽ����(ͬ���ӿ�)
	* @param[in] items  ������Ϣ����
	*/
	virtual bool addLocalSettingSync(std::vector<data::UserLocalSetting> &items) = 0;

    /**
	* \brief ���±�������(ͬ���ӿ�)
	* @param[in] newItems ������µ�������Ϣ����
	*/
	virtual bool updateLocalSettingSync(std::vector<data::UserLocalSetting> &newItems) = 0;

    /**
	* \brief ��ȡȫ������ģʽ
	* @param[out] cb ������ս���ص�  _1������Ϣ _2��ʼʱ��  _3����ʱ��  _4�Ƿ��
	*/
	virtual void getGlobalNoDisturbMode(CFunction<void(int, int32, int32, bool)> cb) = 0;

        /**
	* \brief ����ȫ������ģʽ
	* @param[in] startTime  ��ʼʱ��
	* @param[in] endTime ����ʱ��
	* @param[in] isOpen �Ƿ��
	* @param[out] cb ������ս���ص�  _1������Ϣ
	*/
	virtual void setGolbalNoDisturbMode(int32 startTime, int32 endTime, bool isOpen, CFunction<void(int)> cb) = 0;
    /**
    * \brief ��ȡ������ʱ��(ͬ���ӿ�)
    * @param[out] _1������ʱ�䣬��λ����
    */
    virtual bool getServerTimeSync(int64& serverTime) = 0;

	/**
	* \brief ��ȡ������ʱ��
	* @param[in] cb ������ս���ص�  _1������Ϣ   _2������ʱ�䣬��λ����
	*/
	virtual void getServerTime(CFunction<void(int, int64)> cb) = 0;

	 /**
    * \brief ��Э���Ʋ�ѯ�ӿ�
    *@Param[in] pageSize ��ҳ��С   
    *@Param[in] page ��ѯҳ��    
    *@Param[in] param ��ѯ����    
    *@Param[out] cb ����ӿڽ���ص���_1������Ϣ _2��ҳ��  _3��ѯ���
    */
    virtual void cppccSearch(int32 pageSize, int32 page, data::ZXSearchParam param, CFunction<void(int, int32, std::vector<data::UserBasicData>&)> cb) = 0;
   
	/**
	* \brief ��Э��Ϣ�ö��ӿ�
	*@Param[in] info �ö���Ϣ����packet.h��
	*@Param[in] type ��������  5.���� 6.�޸� 7.ɾ��  ���type�Ƿ���˸�����
	*@Param[out] cb ����ӿڽ���ص���_1������Ϣ _2��������
	*/
	virtual void cppccTopInformation(data::ZxTopInformation info, int type, CFunction<void(int, const std::string&)> cb) = 0;
	/**
	* \brief ��Э��ҳ��ѯ�ö���Ϣ�ӿ�
	*@Param[in] groupId �ö���Ϣ��ȺID
	*@Param[in] pageNum ��ѯҳ
	*@Param[in] pageSize ��ҳ��Ϣ����
	*@Param[out] cb ����ӿڽ���ص���_1������Ϣ _2��ҳ�� _3�ܼ�¼��  _4��ѯ���
	*/
	virtual void cppccGetTopInfo(int64 groupId, int32 pageNum, int32 pageSize, CFunction<void(int, int32, int32, std::vector<data::ZxTopInformation>&)> cb) = 0;

	 };

	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}