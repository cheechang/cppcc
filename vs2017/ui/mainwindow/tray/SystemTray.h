#pragma once
#include <QSystemTrayIcon>
#include "common/controlptr.h"
class QWidget;
class QMenu;
class QAction;
class QPushButton;
class QWidgetAction;
class QLabel;
namespace ui{
	class SystemTray : public QSystemTrayIcon
	{
		Q_OBJECT
	public:
		enum TrayIconState
		{
			Online,
			OffLine,
			Unread,
			None
		};
		explicit SystemTray(QWidget *parent = 0);

		void resetMsgTipWinPos();

		~SystemTray();
		void translateLanguage();
		void setIconState(TrayIconState state = Online);
		void logOut();
        void SetTrayToolTip(const std::string name, const std::string ser);
	protected:
		bool eventFilter(QObject *obj, QEvent *event);

	private:
		void createTopAction();
		void createBottomAction();
		void createAction();
		void addActions();
        void UnClockProcess();
	signals:
		void showWidget();
		void signalSerLogout(int);
		void signalExitClient(bool isrestart);
	public slots:
		void onActivated(QSystemTrayIcon::ActivationReason reason);
		void setFlash(bool flash = true);	//设置图标闪烁
		void flash(void);					//图标闪烁动作
		void onSerLogout(int err);
		void onLoginOff();
		void onLoginOut();
		void onMouseEnterIconEvent();
	private:

		QMenu *tray_menu; //托盘菜单
		/*
		QWidget *top_widget;  //顶部菜单项
		QWidgetAction *top_widget_action;  //播放模式：上一首、播放/暂停、下一首
		QLabel *protect_label;  //360已保护电脑...天
		QPushButton *open_button;  //木马防火墙已经开启
		QPushButton *enter_button;  //进入
	
		QWidget *bottom_widget;  //底部菜单项
		QWidgetAction *bottom_widget_action;  //播放模式：上一首、播放/暂停、下一首
		QPushButton *game_mode_button;  //进入游戏模式
		QPushButton *online_mode_button;  //进入网购模式

		QAction *action_open; //打开360安全卫士
		QAction *action_help_center; //求助中心
		QAction *action_kill_mummy; //查杀木马
		QAction *action_clear; //清理垃圾
		QAction *action_optimize; //一键优化
		QAction *action_fireproof; //检查更新
		QAction *action_show_speed; //显示加速球
		QAction *action_soft_manage; //软件管家
		QAction *action_safe_notice; //安全通知
		QAction *action_rise; //升级
		QAction *action_login; //360用户登录
		QAction *action_separate; //隔离沙箱
		*/
		QAction *action_loginoff; //注销
		QAction *action_logout; //退出


		QTimer* m_pTimer;
		QTimer* mMsgTipWinTimer;
	private:
		bool m_isloginoff; //标示是否是注销操作
		IAuthControl_Ptr m_authcontrol;
	};
}