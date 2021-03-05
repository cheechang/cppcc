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
		* 消息漫游设置
		* param[in]: true-开启，false-关闭
		*/
		static void setMsgRoming(bool val);
		/*
		* 判断是否开启消息漫游
		* return: true-开启，false-关闭
		*/
		static bool isMsgRoming(void);

        /*
        * 设置是否启用USB登陆
        * param[in]: true-开启，false-关闭
        */
        static void setStartFromUSB(bool val);
        /*
        * 获取USB登陆状态
        * return: true-开启，false-关闭
        */
        static bool isStartFromUSB(void);

        /*
        * 设置是否允许修改名称
        * param[in]: true-开启，false-关闭
        */
        static void setChangeUserName(bool val);
        /*
        * 获取设置状态
        * return: true-开启，false-关闭
        */
        static bool isChangeUserName(void);

        /*
        * 设置是否显示意见反馈
        * param[in]: true-开启，false-关闭
        */
        static void setFeedback(bool val);
        /*
        * 获取设置是否显示意见反馈
        * return: true-开启，false-关闭
        */
        static bool isFeedback(void);

		static std::string getDefaultServer();

		/*
        * 获取登录方式
        * return: 登录方式列表
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
        static bool m_isCreatGroup;  //添加按钮创建群设置（true为显示）
        static bool m_isShowFeedback;
		static bool m_isTransferGroup; //转让群设置（true为显示）
		static bool m_isOrgsTree;

		static std::string m_strDefaultSer;     //默认服务器
		static std::map<int,std::string> m_loginTypeMap;  //登录类型map
    };
}