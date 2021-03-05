#pragma  once
#include <QWidget>
#include <memory>
#include "interface/Defines.h"
#include "common/Common.h"
#include "data/UserData.h"
#include "AppMenuButton.h"

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
namespace ui{
	#define APP_MENU_HEIGHT 50 

	class ExpressionWindow;
	class SendMsgButton;
	class ChatEdit;
	class ChatTool;
	class ChatEditWidget:public QWidget{
		Q_OBJECT
	public:
		explicit ChatEditWidget(QWidget*parent = CNull);
		virtual ~ChatEditWidget();
		void setTargetInfo(TargetInfo info);
		void clearMenus();
		bool resetBurnState();
		void restDelayState();
		bool ReturnChickFeatherStat();
		void initSendMsgHotKey();
		void SetNotSpeak(bool istrue, int type=0);
		void SetBtnIsCicked(bool isCanClicked);
		void setHistoryMsgVisible(bool isVisble);
		void setAtListWidgetVisible(bool isVis);
	signals:
		void SendMsg(QString,QStringList,QStringList,std::vector<int64>,bool,bool,bool);
		void signalScreenShot(int flag);
        void signalSendMsgShot(int key);
		void SendCard(int64 cardId,bool isburn,bool isdelay,bool isreceipt);
		void sendDnyMsg(QString fileName);
		void signalSerGetAppInfo(int, data::EntAppinfo&);
		void signalSetPrivateKey(QString&);
		void signalSetSecretIsvisible(bool, bool);
		void openUrl(std::string url);
		void signalShakeWin();
		void showRecordWin();
		void signalSerCloseSession(int type);
		void signalSerbtnCloseSession(bool);
		void signalSerbtnChatHis();
	public slots:
		void onSendMsgHotKeyUpdate(int key);
		void onStopRecord();
		void onOpenUrl(std::string url);
		void onShowAppMenus();
		void onSerGetAppInfo(int, data::EntAppinfo&);
		void onNoticeInputEditFocus();
		void onSendImage(const QString& path);
		void onSendFile(const QString&path);
		void onSendEmoji();
		void onEmojiClicked(int type,QString path);
		void onSendCard(int64 id);
		void onSendMsg(QString text,QStringList imagelist,QStringList filelist,std::vector<int64> atlist,bool isburn,bool isdelay,bool isreceipt);
		void onSerRecallEdit(QString&);
	protected:
		virtual void paintEvent(QPaintEvent *e);
	private:
		CSharedPtr<ChatTool> m_chattool; //聊天工具条
		CSharedPtr<ChatEdit> m_chatedit;
		CSharedPtr<QLabel> m_tip;
		CSharedPtr<SendMsgButton> m_chatsendmsg;
		CSharedPtr<QVBoxLayout> m_mainlayout;
		QHBoxLayout* m_btnlayout;
		ExpressionWindow* mExpWin;
		TargetInfo mTargetInfo;

		QWidget*mAppMenus;
		QMap<AppMenuButton*,int> mMapAppMenus;
		QHBoxLayout* mAppMenuBtnLayout;
		//AppWebView mWebView;
	};
}