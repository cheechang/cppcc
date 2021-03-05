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
    bool FunctionConfig::m_isChangeUserName  = false; //�����Ƿ���޸ģ�falseΪ���޸ģ�
	bool FunctionConfig::m_isOnPrivateChat   = true;  //��ʾ˽�����ã�trueΪ��ʾ��
	bool FunctionConfig::m_isShowTitleAddBtn = true;  //��ʾ���˻Ự��Ӱ�ť��trueΪ��ʾ��
    bool FunctionConfig::m_isCreatGroup      = true;  //��Ӱ�ť����Ⱥ���ã�trueΪ��ʾ��
    bool FunctionConfig::m_isShowFeedback    = true;  //��ʾ���������trueΪ��ʾ��
	bool FunctionConfig::m_isTransferGroup   = true;  //ת��Ⱥ���ã�trueΪ��ʾ��
	bool FunctionConfig::m_isOrgsTree        = false; //��֯�ܹ�ȫչ����trueΪ��ʾ��

	std::string FunctionConfig::m_strDefaultSer = "vrv";//"u2test";
	std::map<int,std::string> FunctionConfig::m_loginTypeMap;//{1,"hah"};//={ { 1, "�ֻ���"}, { 3,"����" }, { 6, "�����˺�" }, { 7,"�Զ����˺�" } };
	
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
	* ��Ϣ��������
	* param[in]: true-������false-�ر�
	*/
	void FunctionConfig::setMsgRoming(bool val){
		m_isMsgRoming = val;
	}
	/*
	* �ж��Ƿ�����Ϣ����
	* return: true-������false-�ر�
	*/
	bool FunctionConfig::isMsgRoming(void){
		return m_isMsgRoming;
	}

    /*
    * �����Ƿ�����USB��½
    * param[in]: true-������false-�ر�
    */
    void FunctionConfig::setStartFromUSB(bool val){
        m_isStartFromUsb = val;
    }
    /*
    * ��ȡUSB��½״̬
    * return: true-������false-�ر�
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
		m_loginTypeMap[1]="�ֻ���";
		m_loginTypeMap[3]="����";
		m_loginTypeMap[6]="�����˺�";
		m_loginTypeMap[7]="�Զ����˺�";
	}

}