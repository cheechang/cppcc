#include "UserControl.h"
#include "interface/IMClient.h"
#include "IControl.h"
#include "log.h"
#include "data/UserData.h"
#include "../../utils/common.h"
const char * filename = 0;
int line = 0;

namespace control{
  service::IMClient* g_client =CNull;
  UserControl::UserControl(const std::string &strName):m_pluginname(strName),m_userservice(CNull),m_userinfo(CNull){
BEGIN;
END;
  }
  UserControl::~UserControl(){
BEGIN;
END;
  }
	/***********************************************
	* @brief ���ش���׺�Ĳ����
	* @param[in]��
	***********************************************/
    std::string UserControl::GetName(){
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
		return result;
	}
	/***********************************************
	* @brief ���ز�����׺�Ĳ����
	* @param[in]��
	***********************************************/
    std::string UserControl::GetDisplayName(){
		return m_pluginname;
	}
	/***********************************************
	* @brief ����sdk�ͻ���ʵ������
	* @param[in]��
	***********************************************/
    void UserControl::SetSdkClientObj(void* obj){
BEGIN;
		g_client =static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK�ͻ��˶���ָ��ʧ��");
			return;
		}
		m_userservice = USERSERVICE;
		m_fileservice = FILESERVICE;
END;
	}

	/***********************************************
	* @brief �û���Ϣ��ȡ�ӿ�
	* @param[out]servername ��������
	***********************************************/
	CSharedPtr<data::AccountInfo> UserControl::GetAccountInfo(){
	BEGIN;
		   if ( CNull == m_userinfo)
		   {
			   m_userinfo = CMakePtr<data::AccountInfo>(); 
		   }
		   model::Account acc;
		   m_userservice->getAccountInfo(acc);
		   if (acc.id.value() != 0)
		   {
			   *m_userinfo = DataConvert(acc);
		   }
	END;
	   return m_userinfo;
	}
	/**********************************************************************************************************
	*brief ��������ػ�ͷ���������
	*@param[out] cb _1Ŀ��ID���˻���Ⱥ  _2 ͷ��
	**********************************************************************************************************/
	void UserControl::RegHeadUpdate(CFunction < void(int64, const std::string&)>cb){
		BEGIN;
		  m_userservice->regUserHeadImgUpdateCb(cb);
		  m_userservice->regUserHeadImgUpdateCb(CBind(&UserControl::onUserHeadUpdate,this,CPlaceholders  _1,CPlaceholders  _2));
		END;
	}

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
	**/
	void UserControl::setSetting(int8 flag, int type)
	{
		BEGIN;
			if(m_userservice != NULL)
				m_userservice->setSetting(flag, type, CBind(&UserControl::onBackResult, this, std::placeholders::_1));
		END;
	}

	void UserControl::getUserSetting(int type, CFunction<void(int, data::UserInfoSetData&)> cb)
	{
		BEGIN;
		mGetUserSetInfoCb = cb;
		if(m_userservice)
			m_userservice->getSetting(type, CBind(&UserControl::onGetUserSetInfo, this, std::placeholders::_1, std::placeholders::_2));
		END;
	}

	/**
	* \brief ���ü����û���Ϣ���µĻص�������������
	* @param[out] cb ע������ͻص� _1 �û���Ϣ
	*/
	void UserControl::regOperateUserCb(CFunction<void(data::AccountInfo&)> cb)
	{
	BEGIN;
		if (m_userservice != NULL)
		{
			m_pRegOperateUserCb.push_back(cb);
			m_userservice->regOperateUserCb(CBind(&UserControl::onGetUserAccount,
				this, CPlaceholders  _1));
			m_userservice->regGetMyselfCb(CBind(&UserControl::onGetUserAccount,
				this, CPlaceholders  _1));
		}
	END;
	}

	/**
    * \brief ��Э���Ʋ�ѯ�ӿ�
    *@Param[in] pageSize ��ҳ��С   
    *@Param[in] page ��ѯҳ��    
    *@Param[in] param ��ѯ����    
    *@Param[out] cb ����ӿڽ���ص���_1������Ϣ _2��ҳ��  _3��ѯ���
    */
	void UserControl::cppccSearch(int32 pageSize, int32 page, data::ZXSearchParam param, CFunction<void(int, int32, std::vector<data::UserBasicData>&)> cb)
	{
		m_ZxUserInfoResultCb = cb;
		model::ZXSearchParam modelZxdata;
		
		modelZxdata.sector = param.sector;              
		modelZxdata.name = param.name;                
		modelZxdata.nation = param.nation;              
		modelZxdata.gender = param.gender;              
		modelZxdata.currentPosition = param.currentPosition;     
		modelZxdata.group = param.group;               
		modelZxdata.specialCommittee = param.specialCommittee;    
		modelZxdata.specialCommitteeDuty = param.specialCommitteeDuty; 
		modelZxdata.CPPCCPosition = param.CPPCCPosition;        
		modelZxdata.myLocation = param.myLocation;          
		m_userservice->cppccSearch(pageSize, page, modelZxdata,std::bind(&UserControl::onSerZxSerchResult, this, std::placeholders::_1, std::placeholders::_2,std::placeholders::_3));
	}

	void UserControl::onSerZxSerchResult(int code, int32 page, std::vector<model::User>& userdata)
	{
		if(m_ZxUserInfoResultCb)
		{
			std::vector<data::UserBasicData>   userinfo;
			for(int i=0; i<userdata.size();i++)
			{
				data::UserBasicData tdata;
				tdata.id = userdata.at(i).id.value();
				tdata.name = userdata.at(i).name.value();
				tdata.thumbAvatar = userdata.at(i).thumbAvatar.value();
				tdata.extends = userdata.at(i).entExtends.value();
				userinfo.push_back(tdata);
			}
			m_ZxUserInfoResultCb(code,page,userinfo);
		}
	}

	/**
	* \brief ��Э��Ϣ�ö��ӿ�
	*@Param[in] info �ö���Ϣ����packet.h��
	*@Param[in] type ��������  5.���� 6.�޸� 7.ɾ��  ���type�Ƿ���˸�����
	*@Param[out] cb ����ӿڽ���ص���_1������Ϣ _2��������
	*/
	void UserControl::cppccTopInformation(data::ZxTopInformation info, int type, CFunction<void(int, const std::string&)> cb)
	{
		BEGIN;
		model::ZxTopInformation data;
		data.id = info.id;
		data.createUserId = info.createUserId;
		data.groupId = info.groupId;
		data.createTime = info.createTime;
		data.topUserId = info.topUserId;
		data.topContent = info.topContent;
		data.updataTime = info.updataTime;
		data.status = info.status;
		data.topType = info.topType;
		data.msgId = info.msgId;
		if (m_userservice)
		m_userservice->cppccTopInformation(data, type, CBind(&UserControl::onSerMsgTopResult,this,cb,CPlaceholders  _1,CPlaceholders  _2));
		END;
	}

	void UserControl::onSerMsgTopResult(ZxTopMsginfoCallBackPtr cb,int code, const std::string strInfo)
	{
		if (cb)
			cb(code, strInfo);
	}

	/**
	* \brief ��Э��ҳ��ѯ�ö���Ϣ�ӿ�
	*@Param[in] groupId �ö���Ϣ��ȺID
	*@Param[in] pageNum ��ѯҳ
	*@Param[in] pageSize ��ҳ��Ϣ����
	*@Param[out] cb ����ӿڽ���ص���_1������Ϣ _2��ҳ�� _3�ܼ�¼��  _4��ѯ���
	*/
	void UserControl::cppccGetTopInfo(int64 groupId, int32 pageNum, int32 pageSize, CFunction<void(int, int32, int32, std::vector<data::ZxTopInformation>&)> cb)
	{
		if (m_userservice)
			m_userservice->cppccGetTopInfo(groupId, pageNum, pageSize, CBind(&UserControl::onSerGetTopMsg,this,cb,CPlaceholders  _1,
			CPlaceholders  _2, CPlaceholders  _3, CPlaceholders  _4));
	}

	void UserControl::onSerGetTopMsg(ZxGetTopMsginfoCallBackPtr cb, int code, int32 tallPage, int32 tallCount, std::vector<ZxTopInformation>& TopInfoResult)
	{
		if (cb)
		{
			std::vector<data::ZxTopInformation> datav;
			for (int i = 0; i < TopInfoResult.size(); i++)
			{
				data::ZxTopInformation data;
				data.id = TopInfoResult.at(i).id;
				data.createUserId = TopInfoResult.at(i).createUserId;
				data.groupId = TopInfoResult.at(i).groupId;
				data.createTime = TopInfoResult.at(i).createTime;
				data.topUserId = TopInfoResult.at(i).topUserId;
				data.topContent = TopInfoResult.at(i).topContent;
				data.updataTime = TopInfoResult.at(i).updataTime;
				data.status = TopInfoResult.at(i).status;
				data.topType = TopInfoResult.at(i).topType;
				data.msgId = TopInfoResult.at(i).msgId;
				datav.push_back(data);
			}
			cb(code, tallPage, tallCount, datav);
		}
	}

	void UserControl::onGetUserAccount(Account& account)
	{
	BEGIN;
		if ( CNull == m_userinfo)
		{
			m_userinfo = CMakePtr<data::AccountInfo>();
		}
		*m_userinfo = DataConvert(account);
		for(int i=0;i<m_pRegOperateUserCb.size();++i){
			RegOperateUserCallBackPtr cb = m_pRegOperateUserCb.at(i);
			cb(*m_userinfo);
		}
		
	END;
	}


	void UserControl::uploadUserHead(std::string src, std::string thumb, CFunction < void(int, const std::string&, const std::string&)>cb){
		BEGIN;
		m_fileservice->uploadAvatar(src,cb);
		END;
	}
	void UserControl::updateAccountInfo(data::AccountInfo& user, CFunction <void(int)> cb)
	{
		BEGIN;
		model::Account acc;
		if (user.name.isSet())
		{
			acc.name = user.name.value();
		}

		if (user.nickId.isSet())
		{
			acc.nickId = user.nickId.value();
		}

		if (user.gender.isSet())
		{
			acc.gender = user.gender.value();
		}

        if (user.avatar.isSet())
        {
            acc.avatar = user.avatar.value();
        }

        if (user.thumbAvatar.isSet())
        {
            acc.thumbAvatar = user.thumbAvatar.value();
        }
		m_userservice->updateAccountInfo(acc,cb);
		END;
	}

	data::AccountInfo UserControl::DataConvert(model::Account& data){
	BEGIN;
	      data::AccountInfo res;
		  res.avatar = data.avatar.value();
		  res.avatarUrl =data.avatarUrl.value();
		  res.email = data.email.value();
		  res.entExtends = data.entExtends.value();
		  res.extends = data.extends.value();
		  res.gender =data.gender.value();
		  res.id = data.id.value();
		  res.nickId = data.nickId.value();
		  res.name = data.name.value();
		  res.phone = data.phone.value();
		  res.thumbAvatar = utils::GetHeadPath( data.gender.value(),data.thumbAvatar.value());
		  res.thumbAvatarUrl = data.thumbAvatarUrl.value();
		  res.timeZone = data.timeZone.value();
	END;
	      return res;
	}

	void UserControl::DataConvert( const model::EntAppinfo&in,data::EntAppinfo&out )
	{
		out.appIcon =utils::GetHeadPath( 4,in.appIcon);
		out.appID =in.appID;
		out.appName =in.appName;
		out.appSign =in.appSign;
		out.appSubType =in.appSubType;
		out.appMenus = in.appMenus;
		out.appSecret = in.appSecret;
		out.appHomeUrl = in.appHomeUrl;
		out.appToken = in.appToken;
		out.appType = in.appType;
		out.entID = in.entID;
		out.subOrAppType = in.subOrAppType;
		out.messageHistoryUrl =in.messageHistoryUrl;
	}
	void UserControl::setPersonalData(std::vector<data::PersonalData> items, CFunction<void(int)> cb)
	{
		std::vector<model::PersonalData> outs;
		for (int i=0;i<items.size();++i)
		{
			model::PersonalData item;
			data::PersonalData out = items.at(i);
			item.type = out.type;
			item.val = out.val;
			outs.push_back(item);
		}
		m_userservice->setPersonalData(outs, cb);

	}
	void UserControl::getAppInfo( int64 appId, CFunction<void(int, data::EntAppinfo&)> cb )
	{
		if(m_userservice){
			mGetAppInfoCb = cb;
			m_userservice->getAppInfo(appId,CBind
				(&UserControl::onGetAppInfo,this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	void UserControl::onGetAppInfo( int code, model::EntAppinfo&app )
	{
		 data::EntAppinfo out;
		 DataConvert(app,out);
		 mGetAppInfoCb(code,out);
	}

	void UserControl::onUserHeadUpdate( int64 id, const std::string& avatar )
	{
		if(id == m_userinfo->id.value()){
			(*m_userinfo).thumbAvatar = avatar;
			for(int i=0;i<m_pRegOperateUserCb.size();++i){
				RegOperateUserCallBackPtr cb = m_pRegOperateUserCb.at(i);
				cb(*m_userinfo);
			}
		}
	}

	void UserControl::getPersonalData( std::vector<int16> &types, CFunction<void(int, std::vector<data::PersonalData>&)> cb )
	{
		mPersonalDataCb = cb;
		m_userservice->getPersonalData(types,CBind
			(&UserControl::onGetPersonalData,this,CPlaceholders  _1,CPlaceholders  _2));
	}

	void UserControl::onGetPersonalData( service::ErrorInfo code, std::vector<model::PersonalData>&items )
	{
		std::vector<data::PersonalData> outs;
		for (int i=0;i<items.size();++i)
		{
			data::PersonalData item;
			model::PersonalData out = items.at(i);
			item.type = out.type;
			item.val = out.val;
			outs.push_back(item);
		}
		mPersonalDataCb(code,outs);
	}

    bool UserControl::getLocalSettingSync( std::vector<std::string> &keys, std::vector<data::UserLocalSetting> &result )
    {
        std::vector< model::LocalSetting> tmp;
        bool isGet = true;

        if (m_userservice)
        {
           isGet =  m_userservice->getLocalSettingSync(keys,tmp);
        }

        if (isGet)
        {
            std::vector<model::LocalSetting>::iterator it = tmp.begin();
            for (it; it != tmp.end(); it++)
            {
                data::UserLocalSetting ret;
                ret.key= it->key;
                ret.val = it->val;
                result.push_back(ret);
            }
        }
      
        return isGet;
    }

    bool UserControl::addLocalSettingSync( std::vector<data::UserLocalSetting> &items )
    {
        std::vector<model::LocalSetting> tmp;
        bool retVal= true;

        std::vector<data::UserLocalSetting>::iterator it = items.begin();
        for(it; it != items.end(); it++)
        {
            model::LocalSetting inset;
            inset.key = it->key;
            inset.val = it->val;
            tmp.push_back(inset);
        }

        if (m_userservice)
        {
            retVal = m_userservice->addLocalSettingSync(tmp);
        }

        return retVal;
    }

    bool UserControl::updateLocalSettingSync( std::vector<data::UserLocalSetting> &items )
    {
        std::vector<model::LocalSetting> tmp;
        bool retVal= true;

        std::vector<data::UserLocalSetting>::iterator it = items.begin();
        for(it; it != items.end(); it++)
        {
            model::LocalSetting inset;
            inset.key = it->key;
            inset.val = it->val;
            tmp.push_back(inset);
        }

        if (m_userservice)
        {
            retVal = m_userservice->updateLocalSettingSync(tmp);
        }

        return retVal;
    }

    void UserControl::getGlobalNoDisturbMode( CFunction<void(int, int32, int32, bool)> cb )
    {
        if (m_userservice)
        {
            m_userservice->getGlobalNoDisturbMode(cb);
        }
    }

    void UserControl::setGolbalNoDisturbMode( int32 startTime, int32 endTime, bool isOpen, CFunction<void(int)> cb )
    {
        if (m_userservice)
        {
            m_userservice->setGolbalNoDisturbMode(startTime,endTime,isOpen,cb);
        }
    }

	bool UserControl::getServerTimeSync( int64& serverTime )
	{
		if (m_userservice)
		{
			return m_userservice->getServerTimeSync(serverTime);
		}
	}

	void UserControl::getServerTime( CFunction<void(int, int64)> cb )
	{
		if (m_userservice)
		{
			m_userservice->getServerTime(cb);
		}
	}

	void UserControl::onBackResult(int code)
	{

	}

	void UserControl::onGetUserSetInfo(int code, model::UserSetting& SetInfo)
	{
		BEGIN;
		if(code == 0)
		{
			if(mGetUserSetInfoCb != NULL)
			{
				data::UserInfoSetData UserSetInfo;
				UserSetInfo.isSearchByDoodNum = SetInfo.issearchbybean;
				UserSetInfo.isSearchByMailNum = SetInfo.issearchbymail;
				UserSetInfo.isSearchByPhoneNum = SetInfo.issearchbyphone;

				mGetUserSetInfoCb(code, UserSetInfo);
			}
		}		
		END;
	}

	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance(){
		IControl* instance = NULL;
		instance = new UserControl();
		return  instance;
	}
    extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance){
		if(NULL != instance){
			delete instance;
			instance = NULL;
		}
	}
}