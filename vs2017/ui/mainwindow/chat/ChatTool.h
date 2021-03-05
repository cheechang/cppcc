#pragma  once
#include <memory>
#include <QWidget>
#include <QPushButton>
#include <interface/Defines.h>
#include "common/controlptr.h"
class QHBoxLayout;
class QVBoxLayout;
namespace ui{
	class PushButton;
	class SetSecretChatDialog;
	class ChatTool:public QWidget{
		 Q_OBJECT
	public:
		explicit ChatTool(QWidget*parent =CNull);
		virtual ~ChatTool();
		void translateLanguage();
		bool resetBurnState();
		bool resetReceiptState();
		bool ReturnChickFeatherState();
		void setToolBtnVisible(bool show);
		void showLevelBtns(bool show);
		void hideShakeBtn();
		bool getDelayMsgButtonStatu();
		void ResetDelayState() const;
		void SetBtnIsCicked(bool isCanClicked);
		void setHistoryMsgVisible(bool isVisble);
	public slots:
		void onBtnImageClicked();
		void onBtnFileClicked();
		void onBtnScreenShotClicked();
		void onBtnEmojiClicked();
		void onBtnSendCard();
		void onBtnSetSecretChat();
		void onGetPasswordSend(QString&);
		void onSerSetSecretIsvisible(bool,bool);
		void onSerSetCancelSet();
		void onBtnShake();
		void onBtnRecordClicked();
		void onBtnDelayMsgClicked();
		void onBtnChickFeatherClicked();
		void onSerDialogClose();
		void onSerCloseSession();
		void onSerbtnCloseSession(bool isVisible);
		void onSerbtnChatHis();
		void onBtnBurnClicked();
	signals:
		void signalSendImage(const QString& path);
		void signalSendFile(const QString& path);
		void signalScreenShot(int flag);
		void signalEmoji();
		void signalSendCard(int64 id);
		void signalViewMenus();
		void signalSetPrivateKey(QString&);
		void signalSetSecretIsvisible(bool, bool);
		void signalShakeWin();
		void signalStartRecord();
		void signalDelayMsg(int64 time);
		void signalSerChickFeather();
		void signalSerCloseSession(int);
		void signalSerbtnCloseSession(bool isVisible);
		void signalSerbtnChatHis();
	private:
		CSharedPtr<PushButton>  m_btnfont;
		CSharedPtr<PushButton>  m_btnemoji;
		CSharedPtr<PushButton>  m_btnimage;
		CSharedPtr<PushButton>  m_btnfile;
		CSharedPtr<PushButton>  m_screenshot;
		CSharedPtr<PushButton>  m_btnCard;
		CSharedPtr<PushButton>  m_btnBurn;
		CSharedPtr<PushButton>  m_btntool;
		//CSharedPtr<PushButton>  m_btnSecretChat;
		CSharedPtr<PushButton>  m_btnShake;
		CSharedPtr<PushButton>  m_btnRecord;
		CSharedPtr<PushButton>  m_btnDelayMsg;
		CSharedPtr<PushButton>  m_btnChickFeatherMsg;
		CSharedPtr<PushButton>  m_btnCloseOtherSession;

		CSharedPtr<PushButton>  m_btnChatHistory;
		CSharedPtr<QWidget> m_toolspliter;
		QHBoxLayout* m_contentlayout;
		CSharedPtr<QVBoxLayout> m_mainlayout;
		CSharedPtr<SetSecretChatDialog> m_SecretChatDialog;
		CSharedPtr<PushButton>  m_btnReceipt;
		bool SetPasswordIsOpen;
		bool bAssertChick;
	};
}
