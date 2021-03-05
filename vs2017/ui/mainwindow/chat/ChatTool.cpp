#include "ChatTool.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QSignalMapper>
#include <QFileDialog>
#include <QDesktopServices>
#include <log.h>
#include "controls/PushButton.h"
#include "common/Controlptr.h"
#include "SendCardSelectContactWin.h"
#include "SetSecretChatDialog.h"
#include "../../common/Common.h"
namespace ui{
	ChatTool::ChatTool(QWidget*parent):QWidget(parent),
	m_btnfont(CNull),m_btnemoji(CNull),m_btnimage(CNull),m_mainlayout(CNull)
	,m_toolspliter(CNull),m_contentlayout(CNull),SetPasswordIsOpen(false),bAssertChick(false)
	{
	     m_btnfont = CMakePtr<PushButton>(this);
	     m_btnemoji = CMakePtr<PushButton>(this);
		 m_btnimage = CMakePtr<PushButton>(this);
		 m_btnfile  = CMakePtr<PushButton>(this);
		 m_screenshot  = CMakePtr<PushButton>(this);
		// m_btnSecretChat = CMakePtr<PushButton>(this);
		 m_toolspliter = CMakePtr<QWidget>(this);
		 m_btnCard = CMakePtr<PushButton>(this);
		 m_btnBurn= CMakePtr<PushButton>(this);
		 m_btntool  = CMakePtr<PushButton>(this);
		 m_btnShake  = CMakePtr<PushButton>(this);
		// m_btnRecord = std::make_shared<PushButton>(this);
		 m_btnDelayMsg = std::make_shared<PushButton>(this);
		// m_btnChickFeatherMsg = std::make_shared<PushButton>(this);
		 m_btnCloseOtherSession = CMakePtr<PushButton>(this);
		 m_btnCloseOtherSession->hide();
		 m_btnChatHistory = CMakePtr<PushButton>(this);
		 m_btnReceipt = CMakePtr<PushButton>(this);

		 m_screenshot->setUseCutScreen(true);
		 m_btnBurn->setCheckable(true,false);
		 m_btnReceipt->setCheckable(true, false);
		 m_toolspliter->setFixedHeight(1);
		 m_toolspliter->setObjectName("spliter");
		 
		 m_btnfont->setPicName(QString(":/chat/font"));
		 m_btnemoji->setPicName(QString(":/chat/emoji"));
		 m_btnimage->setPicName(QString(":/chat/picbtn"));
		 m_btnfile->setPicName(QString(":/chat/file"));
		 m_screenshot->setPicName(QString(":/chat/screenshot"));
		 m_btnCard->setPicName(QString(":/chat/card"));
		 m_btnBurn->setPicName(QString(":/chat/burn"));
		 m_btntool->setPicName(QString(":/chat/appMenus"));
		 m_btnShake->setPicName(QString(":/chat/shake"));
		 m_btnReceipt->setPicName(QString(":/chat/send-receipt"));
		 m_btnChatHistory->setPicName(QString(":/chat/msghis"));
		// m_btnSecretChat->setPicName(QString(":/chat/privateChatBtn"));
		// m_btnRecord->setPicName(QString(":/chat/record"));
		 m_btnDelayMsg->setPicName(":/chat/delayMsg");
		// m_btnChickFeatherMsg->setPicName(":/chat/Chick");
		 m_btnCloseOtherSession->setPicName(":/chat/CloseSession");
		 //m_btnChatHistory->setText(transfer("消息记录"));
		// m_btnChatHistory->setStyleSheet(tr("QPushButton{background:transparent;}"));
		// m_btnSecretChat->setCheckable(true,false);
		 m_btnDelayMsg->setCheckable(true,false);
		 m_btnfont->setVisible(false);
		 m_btntool->setVisible(false);

		 connect(m_btnBurn.get(), SIGNAL(clicked()), this, SLOT(onBtnBurnClicked()));
		 connect(m_screenshot.get(),SIGNAL(clicked()),this,SLOT(onBtnScreenShotClicked()));
		 connect(m_btnimage.get(),SIGNAL(clicked()),this,SLOT(onBtnImageClicked()));
		 connect(m_btnfile.get(),SIGNAL(clicked()),this,SLOT(onBtnFileClicked()));
		 connect(m_btnemoji.get(),SIGNAL(clicked()),this,SLOT(onBtnEmojiClicked()));
		 connect(m_btnCard.get(),SIGNAL(clicked()),this,SLOT(onBtnSendCard()));
		 connect(m_btnShake.get(),SIGNAL(clicked()),this,SLOT(onBtnShake()));
		 connect(m_btntool.get(),SIGNAL(clicked()),this,SIGNAL(signalViewMenus()));
		 //connect(m_btnRecord.get(),SIGNAL(clicked()),this,SLOT(onBtnRecordClicked()));
		 connect(m_btnDelayMsg.get(),SIGNAL(clicked()),this,SLOT(onBtnDelayMsgClicked()));
		 connect(m_btnChatHistory.get(), SIGNAL(clicked()), this, SLOT(onSerbtnChatHis()));
		 //connect(m_btnChickFeatherMsg.get(), SIGNAL(clicked()),this, SLOT(onBtnChickFeatherClicked()));

		// connect(m_btnSecretChat.get(),SIGNAL(clicked()),this,SLOT(onBtnSetSecretChat()));
		 connect(this,SIGNAL(signalSetSecretIsvisible(bool,bool)), this, SLOT(onSerSetSecretIsvisible(bool,bool)));
		 connect(m_btnCloseOtherSession.get(),SIGNAL(clicked()), this, SLOT(onSerCloseSession()));
		 connect(this,SIGNAL(signalSerbtnCloseSession(bool)), this, SLOT(onSerbtnCloseSession(bool)));

		 m_contentlayout = new QHBoxLayout();
		 m_contentlayout->addWidget(m_screenshot.get());
		 m_contentlayout->addWidget(m_btnfont.get());
		 m_contentlayout->addWidget(m_btnemoji.get());
		 m_contentlayout->addWidget(m_btnimage.get());
		 m_contentlayout->addWidget(m_btnfile.get());
		 m_contentlayout->addWidget(m_btnCard.get());
		 m_contentlayout->addWidget(m_btnBurn.get());
		 //m_contentlayout->addWidget(m_btnRecord.get());
		 m_contentlayout->addWidget(m_btnDelayMsg.get());
		// m_contentlayout->addWidget(m_btnSecretChat.get());
		 m_contentlayout->addWidget(m_btnShake.get());
		// m_contentlayout->addWidget(m_btnChickFeatherMsg.get());
		 m_contentlayout->addWidget(m_btnReceipt.get());
		 m_contentlayout->addWidget(m_btnChatHistory.get());

		 m_contentlayout->addStretch();
		 m_contentlayout->addWidget(m_btntool.get());
		 m_contentlayout->addWidget(m_btnCloseOtherSession.get());
		

		 m_contentlayout->setContentsMargins(10,0,10,0);
		 m_contentlayout->setSpacing(10);


		 m_mainlayout = CMakePtr<QVBoxLayout>(this);
		 m_mainlayout->addWidget(m_toolspliter.get());
		 m_mainlayout->addLayout(m_contentlayout);
		 m_mainlayout->setSpacing(2);
		 m_mainlayout->setContentsMargins(0,0,0,0);

		 setLayout(m_mainlayout.get());
		// m_btnSecretChat->setStyleSheet("hover:{background: url(:/chat/privateChatBtn_hover);}");
		 translateLanguage();
	}
	ChatTool::~ChatTool(){
		if (CNull != m_contentlayout)
		{
			m_contentlayout->deleteLater();
			m_contentlayout = CNull;
		}
	}

	void ChatTool::onSerbtnChatHis()
	{
		emit signalSerbtnChatHis();
	}

	//设置密聊密码
	void ChatTool::onBtnSetSecretChat()
	{
		if(!SetPasswordIsOpen)
		{
			m_SecretChatDialog = CMakePtr<SetSecretChatDialog>();
			connect(m_SecretChatDialog.get(), SIGNAL(signalSetPrivateKey(QString&)),this, SLOT(onGetPasswordSend(QString&)));
			connect(m_SecretChatDialog.get(), SIGNAL(signalCancelSet()), this, SLOT(onSerSetCancelSet()));
			connect(m_SecretChatDialog.get(),SIGNAL(signalclose()),this,SLOT(onSerDialogClose()));
			m_SecretChatDialog->exec();
		}
		else
		{
			SetPasswordIsOpen = false;
			//m_btnSecretChat->setCheckable(true,false);
			//m_btnSecretChat->setPicName(QString(":/chat/privateChatBtn"));
			QString TPassword("");
			emit signalSetPrivateKey(TPassword);
		}
	}

	void ChatTool::onGetPasswordSend(QString& pPassword)
	{
		SetPasswordIsOpen = true;
		emit signalSetPrivateKey(pPassword);
		//m_btnSecretChat->setPicName(QString(":/chat/privateChatBtn"));
		//m_btnSecretChat->setCheckable(true,true);
	}

	void ChatTool::onBtnImageClicked(){
		 QString file = QFileDialog::getOpenFileName(this, transfer("发送图片"),QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),transfer("图像文件(*.bmp;*.jpg;*.jpeg;*.png;*.gif)"));
		 if (!file.isEmpty())
		 {
			 emit signalSendImage(file);
		 }
	}
	void ChatTool::onBtnFileClicked(){
		QString file = QFileDialog::getOpenFileName(this, transfer("发送文件"),QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),transfer("所有文件(*.*)"));
		if (!file.isEmpty())
		{
			emit signalSendFile(file);
		}
	}
	void ChatTool::onBtnScreenShotClicked(){
		emit signalScreenShot(0);
	}
	void ChatTool::translateLanguage(){
		m_btnfont->setToolTip(transfer("字体选择工具栏"));
		m_btnemoji->setToolTip(transfer("选择表情"));
		m_btnimage->setToolTip(transfer("发送图片"));
		m_btnfile->setToolTip(transfer("发送文件"));
		m_screenshot->setToolTip(transfer("屏幕截图 Alt+D"));
		m_btnCard->setToolTip(transfer("发送名片"));
		m_btnBurn->setToolTip(transfer("阅后即焚"));
		m_btnReceipt->setToolTip(transfer("阅后回执"));
		m_btntool->setToolTip(transfer("公众号菜单"));
	   // m_btnSecretChat->setToolTip(transfer("设置密聊"));
		m_btnShake->setToolTip(transfer("抖一抖"));
		//m_btnRecord->setToolTip(transfer("语音消息"));
		m_btnDelayMsg->setToolTip(transfer("延迟消息"));
		//m_btnChickFeatherMsg->setToolTip(transfer("鸡毛信"));
		m_btnCloseOtherSession->setToolTip(transfer("关闭对方聊天"));
		m_btnChatHistory->setToolTip(transfer("消息记录"));
	}

	void ChatTool::onBtnEmojiClicked()
	{
		emit signalEmoji();
	}

	void ChatTool::onBtnSendCard()
	{
		SendCardSelectContactWin win;
		connect(&win,SIGNAL(signalSendId(int64)),this,SIGNAL(signalSendCard(int64)));
		win.showWin();
	}

	bool ChatTool::resetBurnState()
	{
		bool state = m_btnBurn->checkedStatus();
		if (state)
		{
			m_btnBurn->setCheckable(true,false);
		}
		return state;
	}

	bool ChatTool::resetReceiptState(){
		bool state = m_btnReceipt->checkedStatus();
		if (state)
		{
			m_btnReceipt->setCheckable(true, false);
		}
		return state;
	}
	void ChatTool::setToolBtnVisible( bool show )
	{
		m_btntool->setVisible(show);
		m_btnfont->setVisible(!show);
		m_btnemoji->setVisible(!show);
		m_btnimage->setVisible(!show);
		m_btnfile->setVisible(!show);
		m_screenshot->setVisible(!show);
		m_btnCard->setVisible(!show);
		m_btnBurn->setVisible(!show);
		m_btnReceipt->setVisible(!show);
		//m_btnSecretChat->setVisible(!show);
		m_btnShake->setVisible(!show);
		//m_btnRecord->setVisible(!show);
		m_btnDelayMsg->setVisible(!show);
		m_btnChatHistory->setVisible(!show);
		//m_btnChickFeatherMsg->setVisible(!show);
	}

	void ChatTool::setHistoryMsgVisible(bool isVisble)
	{
		m_btnChatHistory->setVisible(isVisble);
		if (isVisble) {
			m_btnBurn->hide();
			m_btnDelayMsg->hide();
			m_btnShake->hide();
			m_btnReceipt->hide();
		}
	}

	void ChatTool::onSerSetSecretIsvisible(bool pIsvisible, bool pIsSecret)
	{
		if(pIsvisible)
		{
			//m_btnSecretChat->setVisible(true);
			if(pIsSecret)
			{
				//m_btnSecretChat->setCheckable(true, true);
				SetPasswordIsOpen = true;
			}
		}
		else
		{
			//m_btnSecretChat->setVisible(false);
		}
	}

	void ChatTool::onSerSetCancelSet()
	{
		//m_btnSecretChat->setCheckable(true,false);
	}

	void ChatTool::showLevelBtns( bool show )
	{;
		m_btnfont->setVisible(show);
		m_btnemoji->setVisible(show);
		m_btnimage->setVisible(show);
		m_btnfile->setVisible(show);
		m_screenshot->setVisible(show);
		m_btnCard->setVisible(show);
		m_btnBurn->setVisible(show);
		m_btnReceipt->setVisible(show);
		//m_btnSecretChat->setVisible(show);
		//m_btnRecord->setVisible(show);
		m_btnDelayMsg->setVisible(show);
		m_btnDelayMsg->setVisible(show);
		//m_btnChickFeatherMsg->setVisible(show);
	}

	void ChatTool::onBtnShake()
	{
		//ReturnChickFeatherState();
		emit signalShakeWin();
	}

	void ChatTool::hideShakeBtn()
	{
		m_btnShake->setVisible(false);
		//m_btnChickFeatherMsg->setVisible(false);
	}

	void ChatTool::onBtnRecordClicked()
	{
		 emit signalStartRecord();
	}

	void ChatTool::onBtnDelayMsgClicked()
	{
		if (m_btnBurn) {
			resetBurnState();
		}
	}

	void ChatTool::onBtnBurnClicked() {
		ResetDelayState();
	}
	bool ChatTool::getDelayMsgButtonStatu()
	{
		return m_btnDelayMsg->checkedStatus();;
	}

	void ChatTool::ResetDelayState() const
	{
		m_btnDelayMsg->setCheckable(true,false);
	}

	void ChatTool::onBtnChickFeatherClicked()
	{
		if(bAssertChick)
		{		
			//m_btnChickFeatherMsg->setCheckable(true, false);
			bAssertChick = false;
		}
		else
		{
			//m_btnChickFeatherMsg->setCheckable(true, true);
			bAssertChick = true;
		}
	}

	bool ChatTool::ReturnChickFeatherState()
	{
		bool state = true;
		/*bool state = m_btnChickFeatherMsg->checkedStatus();
		if (state)
		{
			bAssertChick = false;
			m_btnChickFeatherMsg->setCheckable(false,false);
		}*/
		return state;
	}

	void ChatTool::onSerDialogClose()
	{
	//	m_btnSecretChat->setCheckable(true,false);
	}

	void ChatTool::SetBtnIsCicked(bool isCanClicked)
	{
		m_btnfont->setEnabled(isCanClicked);
		m_btnemoji->setEnabled(isCanClicked);
		m_btnimage->setEnabled(isCanClicked);
		m_btnfile->setEnabled(isCanClicked);
		m_screenshot->setEnabled(isCanClicked);
		m_btnCard->setEnabled(isCanClicked);
		m_btnBurn->setEnabled(isCanClicked);
		m_btnReceipt->setEnabled(isCanClicked);
		//m_btnSecretChat->setEnabled(isCanClicked);
		//m_btnRecord->setEnabled(isCanClicked);
		m_btnDelayMsg->setEnabled(isCanClicked);
		//m_btnChickFeatherMsg->setEnabled(isCanClicked);
		//m_btnCloseOtherSession->setEnabled(isCanClicked);
		//m_btnChatHistory->setEnabled(isCanClicked);
	}

	void ChatTool::onSerbtnCloseSession(bool isVisible)
	{
		//m_btnCloseOtherSession->setVisible(false);
	}
	

	void ChatTool::onSerCloseSession()
	{
		emit signalSerCloseSession(1);
	}

}