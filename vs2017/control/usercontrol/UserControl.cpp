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
	* @brief 返回带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string UserControl::GetName(){
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
		return result;
	}
	/***********************************************
	* @brief 返回不带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string UserControl::GetDisplayName(){
		return m_pluginname;
	}
	/***********************************************
	* @brief 设置sdk客户端实例对象
	* @param[in]无
	***********************************************/
    void UserControl::SetSdkClientObj(void* obj){
BEGIN;
		g_client =static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK客户端对象指针失败");
			return;
		}
		m_userservice = USERSERVICE;
		m_fileservice = FILESERVICE;
END;
	}

	/***********************************************
	* @brief 用户信息获取接口
	* @param[out]servername 服务器名
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
	*brief 监听最近回话头像更新推送
	*@param[out] cb _1目标ID，人或者群  _2 头像
	**********************************************************************************************************/
	void UserControl::RegHeadUpdate(CFunction < void(int64, const std::string&)>cb){
		BEGIN;
		  m_userservice->regUserHeadImgUpdateCb(cb);
		  m_userservice->regUserHeadImgUpdateCb(CBind(&UserControl::onUserHeadUpdate,this,CPlaceholders  _1,CPlaceholders  _2));
		END;
	}

	/**
	* \brief 设置账号设置项
	* @param[in] flag 传入设置项属性
	* @param[in] type 传入设置项类型
	* @param[out] cb  账号设置结果回调 _1 错误信息
	*
	*  type = 1: 设置是否显示在线信息 flag: 0显示 1不显示 默认0
	*  type = 3: 设置豆豆号查找 flag: 0允许 1不允许 默认0
	*  type = 4: 设置手机号查找 flag: 0允许 1不允许 默认0
	*  type = 5: 设置邮箱号查找 flag: 0允许 1不允许 默认0
	*  type = 6: 设置分享更新   flag: 0提示更新 1不提示更新 默认0
	*  type = 7: 新消息通知是否提醒 flag: 0提醒 1不提醒 默认0
	*  type = 12: 多服务新消息通知是否提醒 flag: 0不始终提示 1始终提示 默认0
	*  type = 13: 多服务设置V标好友始终提醒 flag: 0不始终提示 1始终提示 默认0
	*  type = 14: 多服务设置设置@相关人始终提醒 flag: 0不始终提示 1始终提示 默认0
	*  type = 20: 设置新朋友查找 flag: 0允许 1不允许 默认0
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
	* \brief 设置监听用户信息更新的回调，服务器推送
	* @param[out] cb 注册的推送回调 _1 用户信息
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
    * \brief 政协定制查询接口
    *@Param[in] pageSize 分页大小   
    *@Param[in] page 查询页码    
    *@Param[in] param 查询条件    
    *@Param[out] cb 传入接口结果回调，_1错误信息 _2总页数  _3查询结果
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
	* \brief 政协消息置顶接口
	*@Param[in] info 置顶消息（见packet.h）
	*@Param[in] type 操作类型  5.新增 6.修改 7.删除  这个type是服务端给出的
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2错误描述
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
	* \brief 政协分页查询置顶消息接口
	*@Param[in] groupId 置顶消息的群ID
	*@Param[in] pageNum 查询页
	*@Param[in] pageSize 单页消息数量
	*@Param[out] cb 传入接口结果回调，_1错误信息 _2总页数 _3总记录数  _4查询结果
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