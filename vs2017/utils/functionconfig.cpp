#include "functionconfig.h"
namespace utils
{
	bool FunctionConfig::m_isOnTelnet        = false;
	bool FunctionConfig::m_isEnableVideoChat = false;
	bool FunctionConfig::m_isHideTray		 = false;
	bool FunctionConfig::m_isHideLoginWindow = false;
	bool FunctionConfig::m_isHideMainWindow	 = false;
	bool FunctionConfig::m_isHideTaskIcon	 = false;
	bool FunctionConfig::m_isMsgRoming		 = false;  
	bool FunctionConfig::m_isStartFromUsb    = false;
    bool FunctionConfig::m_isChangeUserName  = false; //姓名是否可修改（false为可修改）
	bool FunctionConfig::m_isOnPrivateChat   = true;  //显示私聊设置（true为显示）
	bool FunctionConfig::m_isShowTitleAddBtn = true;  //显示个人会话添加按钮（true为显示）
    bool FunctionConfig::m_isCreatGroup      = true;  //添加按钮创建群设置（true为显示）
    bool FunctionConfig::m_isShowFeedback    = true;  //显示意见反馈（true为显示）
	bool FunctionConfig::m_isTransferGroup   = true;  //转让群设置（true为显示）
	bool FunctionConfig::m_isOrgsTree        = false; //组织架构全展开（true为显示）

	std::string FunctionConfig::m_strDefaultSer = "vrv";//"u2test";
	std::map<int,std::string> FunctionConfig::m_loginTypeMap;//{1,"hah"};//={ { 1, "手机号"}, { 3,"邮箱" }, { 6, "豆豆账号" }, { 7,"自定义账号" } };
	
	bool FunctionConfig::isOnShowMsgReadStatus() {
		return true;
	}
	FunctionConfig::FunctionConfig(){
		
	}
	FunctionConfig::~FunctionConfig(){
	};
	void FunctionConfig::TurnOnTelNet(bool isOn){
		m_isOnTelnet = isOn;
	}
	bool FunctionConfig::IsOnTelNet(){
#ifndef _WIN32
		return false;
#endif
		return m_isOnTelnet;
	}
	bool FunctionConfig::IsOnPrivateChat()
	{
		return m_isOnPrivateChat;
	}
	bool FunctionConfig::IsOnShowTitleAddBtn()
	{
		return m_isShowTitleAddBtn;
	}
	bool FunctionConfig::IsOnCreatGroup()
	{
		return m_isCreatGroup;
	}
	bool FunctionConfig::IsOnTransferGroup()
	{
		return m_isTransferGroup;
	}
	bool FunctionConfig::IsOnOrgsTree()
	{
		return m_isOrgsTree;
	}
	void FunctionConfig::setVideoChatState(bool isEnable){		   
		m_isEnableVideoChat = isEnable;
	}
	bool FunctionConfig::IsEnableVideoChat(void) {
		return m_isEnableVideoChat;
	}
	void FunctionConfig::SetTrayHide(bool isHide){
		m_isHideTray = isHide;
	}
	bool FunctionConfig::IsHideTray(void){
		return m_isHideTray;
	}
	void FunctionConfig::SetLoginWindowHide(bool isHide){
		m_isHideLoginWindow = isHide;
	}
	bool FunctionConfig::IsHideLoginWindow(void){
		return m_isHideLoginWindow;
	}
	void FunctionConfig::SetMainWindowHide(bool isHide){
		m_isHideMainWindow = isHide;
	}
	bool FunctionConfig::IsHideMainWindow(void){
		return m_isHideMainWindow;
	}
	bool FunctionConfig::IsHideTaskIcon(){
		return m_isHideTaskIcon;
	}
	void FunctionConfig::SetTaskIconHide(bool isHide){
		m_isHideTaskIcon = isHide;
	}

	/*
	* 消息漫游设置
	* param[in]: true-开启，false-关闭
	*/
	void FunctionConfig::setMsgRoming(bool val){
		m_isMsgRoming = val;
	}
	/*
	* 判断是否开启消息漫游
	* return: true-开启，false-关闭
	*/
	bool FunctionConfig::isMsgRoming(void){
		return m_isMsgRoming;
	}

    /*
    * 设置是否启用USB登陆
    * param[in]: true-开启，false-关闭
    */
    void FunctionConfig::setStartFromUSB(bool val){
        m_isStartFromUsb = val;
    }
    /*
    * 获取USB登陆状态
    * return: true-开启，false-关闭
    */
    bool FunctionConfig::isStartFromUSB(void){
        return m_isStartFromUsb;
    }

    void FunctionConfig::setChangeUserName(bool value)
    {
        m_isChangeUserName = value;
    }

    bool FunctionConfig::isChangeUserName()
    {
        return m_isChangeUserName;
    }

    void FunctionConfig::setFeedback(bool val)
    {
        m_isShowFeedback = val;
    }

    bool FunctionConfig::isFeedback(void)
    {
        return m_isShowFeedback;
    }

	std::string FunctionConfig::getDefaultServer()
	{
		return m_strDefaultSer;
	}

	std::map<int,std::string> FunctionConfig::getLoginType()
	{
		initLoginType();
		return m_loginTypeMap;
	}

	void FunctionConfig::initLoginType()
	{
		m_loginTypeMap[1]="手机号";
		m_loginTypeMap[3]="邮箱";
		m_loginTypeMap[6]="豆豆账号";
		m_loginTypeMap[7]="自定义账号";
	}

}