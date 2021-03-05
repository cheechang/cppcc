#include "SysMsgMgrControl.h"
#include "interface/IMClient.h"
#include "IControl.h"
#include "log.h"
#include "data/ContactData.h"
const char * filename = 0;
int line = 0;
namespace control{
  service::IMClient* g_client =CNull;
  SysMsgMgrControl::SysMsgMgrControl(const std::string &strName):m_pluginname(strName),m_sysmsgservice(CNull){
BEGIN;
	
END;
  }
  SysMsgMgrControl::~SysMsgMgrControl(){
BEGIN;
END;
  }
	/***********************************************
	* @brief 返回带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string SysMsgMgrControl::GetName(){
		std::string result("");
		result.append(m_pluginname);
		result.append(".dll");
		return result;
	}
	/***********************************************
	* @brief 返回不带后缀的插件名
	* @param[in]无
	***********************************************/
    std::string SysMsgMgrControl::GetDisplayName(){
		return m_pluginname;
	}
	/***********************************************
	* @brief 设置sdk客户端实例对象
	* @param[in]无
	***********************************************/
    void SysMsgMgrControl::SetSdkClientObj(void* obj){
BEGIN;
		g_client =static_cast<service::IMClient*>(obj);
		if (CNull == g_client)
		{
			AddLog(LOG_LEV_ERROR,"SDK客户端对象指针失败");
			return;
		}
		m_sysmsgservice = SYSMSGSERVICE;
END;
	}

	/**
	* \brief 设置监听系统消息的回调
	* @param[out] cb 收到系统消息回调 _1系统消息结构
	*/
	void SysMsgMgrControl::regSysMsgCb(CFunction<void(const  data::SysMsg&)> cb)
	{
		BEGIN;
		m_sysmsgservice->regSysMsgCb(CBind(&SysMsgMgrControl::onRegSysMsgCb, this,cb, CPlaceholders  _1));
		END;
	}

	void SysMsgMgrControl::onRegSysMsgCb(SysMsgCallBackPtr cb, const model::SysMsg&msg)
	{
		BEGIN;
		data::SysMsg out;
		DataConvert(msg, out);
		if (cb)
			cb(out);
		END;
	}

	void SysMsgMgrControl::regLastSysMsgCb(CFunction<void(const  data::SysMsg&, int)> cb)
	{
		mRecvSysMsgCb.push_back(cb);
		if(m_sysmsgservice){
		//	m_sysmsgservice->regSysMsgCb(CBind(&SysMsgMgrControl::onRecvSysMsgCb,this,
		//		CPlaceholders  _1,1));
			m_sysmsgservice->regLastSysMsgCb(CBind(&SysMsgMgrControl::onRecvSysMsgCb,this,
				CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	void SysMsgMgrControl::respToAddBuddy(int64 userId, int64 msgId,  data::SysOperType operType, const std::string &remark, 
		const std::string &refuseReason, CFunction<void(int)> cb)
	{
		model::SysOperType type = (model::SysOperType)operType;
		m_sysmsgservice->respToAddBuddy(userId, msgId, type, remark,refuseReason, cb);
	}

	void SysMsgMgrControl::respToEnterGroup(int64 groupId, int64 msgId,  data::SysOperType operType, const std::string &refuseReason, CFunction<void(int)> cb)
	{
		model::SysOperType type = (model::SysOperType)operType;
		m_sysmsgservice->respToEnterGroup(groupId, msgId,type, refuseReason, cb );
	}

	void SysMsgMgrControl::setMessagRead(int type, std::vector<int64> &msgs, CFunction<void(int)> cb) 
	{
		m_sysmsgservice->setMessagRead(type, msgs, cb);
	}

	void SysMsgMgrControl::getMessages(int type,int count,int64 time,int flag, CFunction<void(int,std::vector< data::SysMsg>&)>cb)
	{
		mGetSysMsgCb = cb;
		m_sysmsgservice->getMessages(type, count, time, flag, CBind(&SysMsgMgrControl::onGetSysMsgCb,this,
			CPlaceholders  _1,CPlaceholders  _2));
	}

	void SysMsgMgrControl:: deleteAllMessage(CFunction<void(int)> cb) 
	{

	}

	void SysMsgMgrControl::deleteMessageByType(int type, std::vector<int64> msgIds, CFunction<void(int)> cb) 
	{
		m_sysmsgservice->deleteMessageByType(type,msgIds ,cb);
	}


	void SysMsgMgrControl::onRecvSysMsgCb(const model::SysMsg& msg, int count)
	{
		AddLog(LOG_LEV_INFO,"onRecvSysMsgCb count = %d",count);
		data::SysMsg out;
		DataConvert(msg, out);

		for (int index=0; index<mRecvSysMsgCb.size(); index++)
		{
			mRecvSysMsgCb.at(index)(out,count);
		}
	}
	void SysMsgMgrControl::onGetSysMsgCb(service::ErrorInfo code,std::vector<model::SysMsg>& vecMsg)
	{
		std::vector<data::SysMsg> outs;
		for (int i=0; i<vecMsg.size(); i++)
		{
			model::SysMsg indata = vecMsg.at(i);
			data::SysMsg outdata;
			DataConvert(indata, outdata);
			outs.push_back(outdata);
		}
		mGetSysMsgCb(code, outs);
	}
	void SysMsgMgrControl::DataConvert( const model::SysMsg& in,data::SysMsg&out )
	{
		out.avatar = in.avatar;
		out.groupId = in.groupId;
		out.groupName = in.groupName;
		out.info = in.info;
		out.isRead = in.isRead;
		out.isResponse = in.isResponse;
		out.msgId = in.msgId;
		out.msgType = in.msgType;
		out.operType = in.operType;
		out.subType = in.subType;
		out.time = in.time;
		out.userId = in.userId;
		out.userName = in.userName;
	}

	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance(){
		IControl* instance = NULL;
		instance = new SysMsgMgrControl();
		return  instance;
	}
    extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance){
		if(NULL != instance){
			delete instance;
			instance = NULL;
		}
	}
}