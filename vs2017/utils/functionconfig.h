 #pragma once
#include <string>
#include <map>
namespace utils
{
	class FunctionConfig{
	public:
		FunctionConfig();
		virtual ~FunctionConfig();
	public:
		static bool IsOnPrivateChat();
		static bool IsOnShowTitleAddBtn();
		static bool IsOnCreatGroup();
		static bool IsOnOrgsTree();
		static bool IsOnTransferGroup();
		static void TurnOnTelNet(bool isOn);
		static bool IsOnTelNet();
		static void setVideoChatState(bool isEnable);
		static bool IsEnableVideoChat(void);
		static void SetTrayHide(bool isHide);
		static bool IsHideTray(void);
		static void SetLoginWindowHide(bool isHide);
		static bool IsHideLoginWindow(void);
		static void SetMainWindowHide(bool isHide);
		static bool IsHideMainWindow(void);
		static bool IsHideTaskIcon();
		static void SetTaskIconHide(bool isHide);
		static bool isOnShowMsgReadStatus();
		/*
		* ��Ϣ��������
		* param[in]: true-������false-�ر�
		*/
		static void setMsgRoming(bool val);
		/*
		* �ж��Ƿ�����Ϣ����
		* return: true-������false-�ر�
		*/
		static bool isMsgRoming(void);

        /*
        * �����Ƿ�����USB��½
        * param[in]: true-������false-�ر�
        */
        static void setStartFromUSB(bool val);
        /*
        * ��ȡUSB��½״̬
        * return: true-������false-�ر�
        */
        static bool isStartFromUSB(void);

        /*
        * �����Ƿ������޸�����
        * param[in]: true-������false-�ر�
        */
        static void setChangeUserName(bool val);
        /*
        * ��ȡ����״̬
        * return: true-������false-�ر�
        */
        static bool isChangeUserName(void);

        /*
        * �����Ƿ���ʾ�������
        * param[in]: true-������false-�ر�
        */
        static void setFeedback(bool val);
        /*
        * ��ȡ�����Ƿ���ʾ�������
        * return: true-������false-�ر�
        */
        static bool isFeedback(void);

		static std::string getDefaultServer();

		/*
        * ��ȡ��¼��ʽ
        * return: ��¼��ʽ�б�
        */
		static std::map<int,std::string> getLoginType();

		static void initLoginType();
	private:
		static bool m_isOnTelnet;
		static bool m_isEnableVideoChat;
		static bool m_isHideTray;
		static bool m_isHideLoginWindow;
		static bool m_isHideMainWindow;
		static bool m_isHideTaskIcon;
		static bool m_isMsgRoming;
        static bool m_isStartFromUsb;
		
        static bool m_isChangeUserName;
		static bool m_isShowTitleAddBtn;
		static bool m_isOnPrivateChat;
        static bool m_isCreatGroup;  //��Ӱ�ť����Ⱥ���ã�trueΪ��ʾ��
        static bool m_isShowFeedback;
		static bool m_isTransferGroup; //ת��Ⱥ���ã�trueΪ��ʾ��
		static bool m_isOrgsTree;

		static std::string m_strDefaultSer;     //Ĭ�Ϸ�����
		static std::map<int,std::string> m_loginTypeMap;  //��¼����map
    };
}