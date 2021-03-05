#pragma  once
#include <memory>
#include <QWidget>
#include "common/Common.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "UserInfoWidget.h"
#include "common/Controlptr.h"
#include <QMenu>
#include <QAction>

class QLabel;
class ScreenShot;
class QxtGlobalShortcut;

namespace ui{
class PushButton;
class ToolButton;
class AvatarArea;
class UnreadMsgLabel;
class SystemSetting;
class SuggestionFeedbackDialog;
class SuggestionFeedbackSendDialog;
enum HOTKEYTYPE{
    KEY_NONE,    
    KEY_SCREEN,  //截图
    KEY_MOREMSG  //拉取消息
};
class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);

	virtual ~TitleWidget();
    void InitSetting();
	void translateLanguage();
	void setSupportStretch(bool isSupportStretch);

/// 双击响应处理
public:
	QTimer *timer;   //定时器
signals:
	void clicked();
public slots:
	void slotClicked();     //槽函数

void mouseDoubleClickEvent(QMouseEvent * event);
	//双击

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

signals:
    void setMsgSoundState(bool isOpen); //设置UI
    void signalPlaySound(bool isOpen);
	void startChat(CSharedPtr<data::ChatInfo>&, QString&);
    void showMin();
	void closeWidget();
	void maxWiget();
	void turnPage(int current_page);
	void moveWindow(bool);
    void startScreenShotProcess();
    void signalSendMsgShot(int key);
    void setHotKeyHasConflict(int conflict);
    void showMsgWidget();
	void sendMsgHotKeyUpdate(int);
	void addContactOrCreateGroup(int type);
	void setHotKeySuccess(); ///2019-6-10  bxy
public slots:
	void showUserInfo(QPoint pos);
	void onUserHeadSucc(QString headImg);
	void onUserWinClose();
	void turnPage(QString current_page);
	void onTurnPage(int current_page);
	void onMaxWiget();
	void onUnreadMsgCountNotify(int count);
	void showMenu();
	void onShowSetWin();
	void onShowLogWin();
	void onShowMsgManagerWin();
	//heyaofeng
	void onShowSuggesSendWin(QString&);
	void onShowSendFile(CSharedPtr<data::ChatInfo>&);

    void onStartScreenShot();
    void onPushMsg();

    void setScreenHotKey(QString key,bool isInit = false);
    void setPushMsgHotKey(QString key,bool isInit = false);

    void onSendMsgSetting(int);
    void hotKeySetting(QString screen, QString msg);

	void onBtnCreateGroup();
	void onBtnAddFrindOrGroup();
	void onSHowAddContactMenu();
protected:
	//声明
	////void mouseDoubleClickEvent(QMouseEvent*);
    void initHotKey();
    void initNotify();
    bool setHotKey(QString key, int type);  //true 成功 false 失败
    void updateLocalSetting(std::string key, std::string val);
private:
	bool m_ismax;
    QPoint press_point;//鼠标按下去的点
	
	AvatarArea* m_pAvatarArea;
///    PushButton *min_button;		//最小化
///	PushButton *max_button;     //最大化按钮
///    PushButton *close_button;	//关闭
	PushButton *menu_button;	//主菜单
	UnreadMsgLabel* mUnreadMsgCount;//未读消息数目
	QList<PushButton *> button_list;
	QVBoxLayout *main_layout;
	ToolButton* mBtnAddContact;
	UserInfoWidget* m_userInfo;

	QMenu* mNemu;
	QAction* m_actionLog;
	QAction* mActionSet;
	QAction* mMsgManager;
	SystemSetting* mSetWin;

	//文件路径
	QString mFilePath;
    /***************以下热键设置*********************/
    CSharedPtr<QxtGlobalShortcut>   m_globalShortcut;
    CSharedPtr<QxtGlobalShortcut>   m_globalMoreMsg;
    CSharedPtr<ScreenShot>          m_screenprocess;
    IUserControl_Ptr               m_userControl;
    int                            m_hotKeyHasConflict;
    bool                           m_bSoundOpen;

	//添加联系人
	CSharedPtr<QMenu>      m_menuMain;
	CSharedPtr<QAction>    m_actionCreateGroup;
	CSharedPtr<QAction>    m_actionAddGroupOrFriend;

	public:
		int m_curWebWindowState; // 当前web窗口状态,  0 展开, 1, 收起
		PushButton *ex_col_button;
	public slots:
	    void slotAdjustWebWindow();
	signals:
		void signalAdjustWebWindow(int action); // 0 展开 1 收起


};
}
