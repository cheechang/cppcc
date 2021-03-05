#include "ChatEditWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QTextDocumentFragment>
#include <QPalette>
#include "expression/ExpressionWindow.h"
#include "controls/ChatEdit.h"
#include "controls/SendMsgButton.h"
#include "common/Connect.h"
#include "common/Controlptr.h"
#include "common/Common.h"
#include "ChatTool.h"
#include "json.h"
#include "AppMenuButton.h"
#include <QDebug>
namespace ui{
	ChatEditWidget::ChatEditWidget(QWidget*parent):QWidget(parent),m_chatedit(CNull),m_chatsendmsg(CNull)
	,m_mainlayout(CNull),m_btnlayout(CNull),m_tip(CNull),m_chattool(CNull){

		m_chattool  = CMakePtr<ChatTool>(this);
		m_chatedit = CMakePtr<ChatEdit>(this);
		m_chatsendmsg = CMakePtr<SendMsgButton>(this);
		m_tip = CMakePtr<QLabel>(this);
		m_mainlayout  = CMakePtr<QVBoxLayout>(this);

		mAppMenus = new QWidget(this);
		mAppMenus->setFixedSize(this->width(),APP_MENU_HEIGHT);
		mAppMenus->setVisible(false);
		mAppMenuBtnLayout = new QHBoxLayout(mAppMenus);
		mAppMenuBtnLayout->setContentsMargins(0,0,0,0);
		mAppMenuBtnLayout->setSpacing(0);
		mAppMenus->setLayout(mAppMenuBtnLayout);

		mExpWin = new ExpressionWindow(this);
		connect(mExpWin,SIGNAL(signalEmojiClicked(int,QString)),this,SLOT(onEmojiClicked(int,QString)));
		QPalette color;
		color.setColor(QPalette::Text,Qt::gray);
		m_tip->setPalette(color);

		m_chatsendmsg->setFixedSize(65,25);
		m_chatsendmsg->setText(transfer("·¢ËÍ"));
		m_tip->setVisible(false);

		m_chatedit->setAcceptDrops(true);


		connect(m_chattool.get(),SIGNAL(signalSendImage(const QString)),this,SLOT(onSendImage(const QString)));
		connect(m_chattool.get(),SIGNAL(signalSendFile(const QString)),this,SLOT(onSendFile(const QString)));
		connect(m_chattool.get(),SIGNAL(signalScreenShot(int)),this,SIGNAL(signalScreenShot(int)));
		connect(m_chattool.get(),SIGNAL(signalEmoji()),this,SLOT(onSendEmoji()));
		connect(m_chattool.get(),SIGNAL(signalSendCard(int64)),this,SLOT(onSendCard(int64)));
		connect(m_chattool.get(),SIGNAL(signalViewMenus()),this,SLOT(onShowAppMenus()));
		connect(m_chattool.get(),SIGNAL(signalSetPrivateKey(QString&)),this,SIGNAL(signalSetPrivateKey(QString&)));
		connect(m_chattool.get(),SIGNAL(signalShakeWin()),this,SIGNAL(signalShakeWin()));
		connect(this,SIGNAL(signalSetSecretIsvisible(bool,bool)),m_chattool.get(),SIGNAL(signalSetSecretIsvisible(bool,bool)));
		connect(m_chattool.get(),SIGNAL(signalStartRecord()),this,SIGNAL(showRecordWin()));
		connect(m_chattool.get(),SIGNAL(signalSerCloseSession(int)),this,SIGNAL(signalSerCloseSession(int)));
		connect(m_chattool.get(), SIGNAL(signalSerbtnChatHis()), this, SIGNAL(signalSerbtnChatHis()));
		connect(this,SIGNAL(signalSerbtnCloseSession(bool)),m_chattool.get(), SIGNAL(signalSerbtnCloseSession(bool)));

		CONNECT_SERVICE(GetAppInfo(int, data::EntAppinfo&));
		CONNECT_CTRL(m_chatedit,m_chatedit,clicked(),SendMsg());
		CONNECT_CTRL(m_chatedit,m_chatedit,textChanged(),textChanged());
		CONNECT_CTRL(m_chatsendmsg,m_chatedit,clicked(),SendMsg());
		connect(m_chatsendmsg.get(),SIGNAL(signalSetSendShorcut(int&)),m_chatedit.get(),SLOT(onSetSendMsgShorcut(int&)));
        connect(this,SIGNAL(signalSendMsgShot(int)),m_chatedit.get(),SLOT(onSetSendMsgShorcut(int)));
		connect(m_chatedit.get(),
			SIGNAL(SendMsg(QString,QStringList,QStringList,std::vector<int64>,bool,bool,bool)),
			this,
			SLOT(onSendMsg(QString,QStringList,QStringList,std::vector<int64>,bool,bool,bool)));

		m_chattool->setMinimumSize(600,40);
		m_chattool->setMaximumHeight(40);
		m_chatedit->setMinimumHeight(60);

		m_btnlayout = new QHBoxLayout(this);
		m_btnlayout->addStretch();
		m_btnlayout->addWidget(m_tip.get());
		m_btnlayout->addWidget(m_chatsendmsg.get());
		m_btnlayout->setSpacing(10);
		m_btnlayout->setContentsMargins(0,0,10,10);

		m_mainlayout->addWidget(m_chattool.get());
		m_mainlayout->addWidget(m_chatedit.get());
		m_mainlayout->addLayout(m_btnlayout);
		m_mainlayout->addWidget(mAppMenus);
		m_mainlayout->setSpacing(0);
		m_mainlayout->setContentsMargins(0,0,0,0);
		setLayout(m_mainlayout.get());
		initSendMsgHotKey();
	}
	ChatEditWidget::~ChatEditWidget(){
		if ( CNull != m_btnlayout)
		{
			m_btnlayout->deleteLater(); 
		}
		clearMenus();
	}
	void ChatEditWidget::onNoticeInputEditFocus(){
		m_chatedit->setFocus();
	}
	void ChatEditWidget::onSendImage(const QString& path){
		m_chatedit->insertImage(path); 
	}
	void ChatEditWidget::onSendFile(const QString&path){
		m_chatedit->insertFile(path);
	}

	void ChatEditWidget::onSendEmoji()
	{
		mExpWin->showWin();
	}

	void ChatEditWidget::paintEvent( QPaintEvent *e )
	{
		if (mExpWin != CNull)
		{
			QPoint pt(m_chattool->x(),m_chattool->y()-mExpWin->height());
			pt = this->mapToGlobal(pt);
			mExpWin->move(pt);
		}
	    if (mMapAppMenus.size()>0)
	    {
			mAppMenus->setFixedSize(this->width(),APP_MENU_HEIGHT);
			if (!mAppMenus->isVisible())
			{
				int h = m_chattool->height()+m_chatedit->height()+m_chatsendmsg->height()+m_btnlayout->spacing();
				this->setFixedHeight(h);
			}else{
				this->setFixedHeight(APP_MENU_HEIGHT);
			}
	    }
		QWidget::paintEvent(e);
	}

	void ChatEditWidget::onEmojiClicked( int type,QString path )
	{
		if (type == 1)
		{
			QString html="<img src="+path+" width=\"24\" height=\"24\"/>";
			m_chatedit->insertEmoji(html);
		}else{
			emit sendDnyMsg(path);
		}
	}

	void ChatEditWidget::setTargetInfo( TargetInfo info )
	{
		mTargetInfo = info;
		m_chatedit->setTargetInfo(info);
		if (info.chattype == data::ENT_CHAT || info.chattype == data::APP_CHAT)
		{
			IUserControl_Ptr userCtrl = USERCONTROL;
			if (userCtrl)
			{
				userCtrl->getAppInfo(info.targetId,CBind(&ChatEditWidget::signalSerGetAppInfo,this,CPlaceholders _1,CPlaceholders _2));
			}
		}
		if (info.chattype == data::GROUP_CHAT || info.chattype == data::ENT_CHAT || info.chattype == data::APP_CHAT)
		{
			m_chattool->hideShakeBtn();
		}
	}

	void ChatEditWidget::onSendCard( int64 id )
	{
		bool isburn = m_chattool->resetBurnState();
		emit SendCard(id, isburn, false, false);
	}

	void ChatEditWidget::onSendMsg( QString text,QStringList imagelist,QStringList filelist,std::vector<int64> atlist,bool isburn,bool isdelay,bool isreceipt )
	{
		isburn = m_chattool->resetBurnState();
		isreceipt = m_chattool->resetReceiptState();
		isdelay = m_chattool->getDelayMsgButtonStatu();
		emit SendMsg(text,imagelist,filelist,atlist,isburn,isdelay,isreceipt);
	}
	void ChatEditWidget::onSerGetAppInfo( int code, data::EntAppinfo& info)
	{
		clearMenus();

		m_chattool->showLevelBtns(false);
		std::string subMenus = info.appMenus;//QString::fromUtf8(info.appMenus.c_str()).toStdString();
		Json::Reader reader;
		Json::Value obj;
		if (reader.parse(subMenus,obj))
		{
			obj = obj["menu"];
			if (obj.isArray() && obj.size()>0)
			{
			   int count = obj.size();
			   int w = (mAppMenus->width() - APP_MENU_HEIGHT)/count;
			   for (int i=0;i<count;++i)
			   {
				   Json::Value val = obj[i];
				   if (val.isObject())
				   {
					   data::AppMenuData data;
					   data.name = val["name"].asString();
					   data.type = val["type"].asString();
					   data.appId = mTargetInfo.targetId;
					   if (val.isMember("sub_menu"))
					   {
						   data.sub_menu =  val["sub_menu"].toStyledString();
						   data.hasSubMenu = true;
					   }else{
						   data.sub_menu  = "[]";
					   }
					   if (val.isMember("url"))
					   {
						   data.url = val["url"].asString();
					   }
					   if (val.isMember("key"))
					   {
						   data.key = val["key"].asString();
					   }
					   AppMenuButton* btn = new AppMenuButton(mAppMenus);
					   connect(btn,SIGNAL(openUrl(std::string)),this,SLOT(onOpenUrl(std::string)));
					   btn->setData(data);
					   btn->setFixedHeight(APP_MENU_HEIGHT);
					   mAppMenuBtnLayout->addWidget(btn);
					   mMapAppMenus.insert(btn,mMapAppMenus.size());
				   }
			   }
			   AppMenuButton* btn = new AppMenuButton(mAppMenus);
			   data::AppMenuData data;
			   btn->setData(data);
			   btn->setFixedSize(APP_MENU_HEIGHT,APP_MENU_HEIGHT);
			   mAppMenuBtnLayout->addWidget(btn);
			   connect(btn,SIGNAL(clicked(bool)),this,SLOT(onShowAppMenus()));
			   mMapAppMenus.insert(btn,mMapAppMenus.size());
			   m_chattool->setToolBtnVisible(true);
			   onShowAppMenus();
			   update();
			}
		}
	}

	void ChatEditWidget::setHistoryMsgVisible(bool isVisble)
	{
		m_chattool->setHistoryMsgVisible(isVisble);
	}

	void ChatEditWidget::onShowAppMenus()
	{
		bool show = !mAppMenus->isVisible();
		mAppMenus->setVisible(show);
		m_chatedit->setVisible(!show);
		m_chatsendmsg->setVisible(!show);
		m_chattool->setVisible(!show);
	}

	void ChatEditWidget::clearMenus()
	{
		QList<AppMenuButton*> btns = mMapAppMenus.keys();
		for (int i=0;i<btns.count();++i)
		{
			delete btns.at(i);
		}
		mMapAppMenus.clear();
	}

	void ChatEditWidget::onOpenUrl( std::string url )
	{
		//gAppWebView.setUrl(QUrl(url.c_str()));
		//gAppWebView.show();
		emit openUrl(url);
	}

	void ChatEditWidget::onStopRecord()
	{

	}

	bool ChatEditWidget::resetBurnState()
	{
		return m_chattool->resetBurnState();
	}

	void ChatEditWidget::restDelayState()
	{
		m_chattool->ResetDelayState();
	}

	bool ChatEditWidget::ReturnChickFeatherStat()
	{
		//return m_chattool->ReturnChickFeatherState();
		return true;
	}

	void ChatEditWidget::onSendMsgHotKeyUpdate( int key)
	{
		if (key == 2)
		{
			m_chatsendmsg->onCtrlEnterActionClicked(true);
		}else{
			m_chatsendmsg->onEnterActionClicked(true);
		}
	}

	void ChatEditWidget::initSendMsgHotKey()
	{
		std::vector<std::string> keys;
		keys.push_back("SendMsgKey");
		std::vector<data::UserLocalSetting> retData;
		bool isGet = false;
		int  curentSendMsg = ENTER_SEND;
		IUserControl_Ptr userCtrl = USERCONTROL;

		isGet = userCtrl->getLocalSettingSync(keys,retData);
		for (qint16 index = 0; index < retData.size(); ++index)
		{
			if (retData[index].key == std::string("SendMsgKey"))
			{
				QString sdMsg = QString::fromUtf8(retData[index].val.data());
				sdMsg = sdMsg.replace(" ", "");
				sdMsg = sdMsg.toLower();
				if (sdMsg == "enter")
				{
					curentSendMsg = ENTER_SEND;
				}
				else if (sdMsg == "ctrl+enter")
				{
					curentSendMsg = CTRLENTER_SEND;
				}
			}
		}
		emit signalSendMsgShot(curentSendMsg);
		onSendMsgHotKeyUpdate(curentSendMsg);
	}

	void ChatEditWidget::onSerRecallEdit(QString& txt)
	{
		m_chatedit->insertText(txt);
	}

	void ChatEditWidget::SetNotSpeak(bool istrue,int type)
	{
		m_chatedit->SetEditState(istrue, type);
		m_chatsendmsg->setEnabled(!istrue); //2019-5-20 bjx change
	}

	void ChatEditWidget::SetBtnIsCicked(bool isCanClicked)
	{
		m_chattool->SetBtnIsCicked(isCanClicked);
	}

	void ChatEditWidget::setAtListWidgetVisible(bool isVis)
	{
		m_chatedit->setAtListWidgetVisible(isVis);
	}
}