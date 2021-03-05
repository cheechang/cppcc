#include "TitleWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../controls/PushButton.h"
#include "../controls/ToolButton.h"
#include "../controls/UnreadMsgLabel.h"
#include "AvatarArea.h"
#include "log.h"
#include "./systemsetting/SystemSetting.h"
#include "./suggestion/SuggestionFeedbackDialog.h"
#include "./suggestion/SuggestionFeedbackSend.h"
#include "./chat/MsgManagerWidget.h"
#include "common/Common.h"
#include "ScreenShot.h"
#include "globalshortcut/qxtglobalshortcut.h"
#include <QMessageBox>
#include "qtimer.h"
QString gCutScrenToolTips = transfer("屏幕截图 Alt+D");

namespace ui{
TitleWidget::TitleWidget(QWidget *parent)
	: QWidget(parent)
    ,m_ismax(false)
    ,m_userInfo(NULL)
    ,m_hotKeyHasConflict(CONFLICT_NONE)
{
    m_userControl = USERCONTROL;
	m_pAvatarArea = new AvatarArea(this);
	m_globalShortcut = CNull;
	menu_button   = new PushButton(this);
  
	menu_button->setPicName(QString(":/title/set"));

  	connect(m_pAvatarArea, SIGNAL(click(QPoint)), this, SLOT(showUserInfo(QPoint)));
	connect(menu_button, SIGNAL(clicked()), this, SLOT(showMenu()));

	/////setMinimumSize(712, 500);
	//设置按钮菜单
	mNemu = new QMenu(this);
	mActionSet = new QAction(this);
	mNemu->addAction(mActionSet);
//	m_actionLog = new QAction(this);
///	mNemu->addAction(m_actionLog);
	mMsgManager = new QAction(this);
	mNemu->addAction(mMsgManager);
	mSetWin = new SystemSetting(this);
   	mSetWin->setMinimumSize(700,500);

    connect(mSetWin,SIGNAL(signalHotKeySetting(QString,QString)),this,SLOT(hotKeySetting(QString,QString)));
    connect(mSetWin,SIGNAL(setSendMsgHotKey(int)),this,SLOT(onSendMsgSetting(int)));
    connect(this,SIGNAL(setHotKeyHasConflict(int)),mSetWin,SIGNAL(hotKeyHasConflict(int)));
    connect(this,SIGNAL(setMsgSoundState(bool)),mSetWin,SIGNAL(setMsgSoundState(bool)));
    connect(mSetWin,SIGNAL(signalPlaySound(bool)),this,SIGNAL(signalPlaySound(bool)));

	connect(this, SIGNAL(setHotKeySuccess()), mSetWin, SIGNAL(hotKeySuccess()));  // 2019-6-10 bxy


	connect(mActionSet,SIGNAL(triggered(bool)),this,SLOT(onShowSetWin()));
 	connect(mMsgManager, SIGNAL(triggered(bool)),this,SLOT(onShowMsgManagerWin()));

    QHBoxLayout *title_layout = new QHBoxLayout();
 
	title_layout->addStretch(1);
	title_layout->addWidget(menu_button, 0, Qt::AlignVCenter);
 
	title_layout->addStretch(1);
 	title_layout->setContentsMargins(0, 0, 10, 10);

	menu_button->setFixedHeight(15);
	menu_button->setFixedWidth(20);
 
	QStringList string_list;
	string_list << ":/title/home" << ":/title/chat" << ":/title/contact" << ":/title/user";

	QVBoxLayout *button_layout = new QVBoxLayout();
	button_layout->setSpacing(25);
	button_layout->setContentsMargins(25, 2, 0, 0);
	QSignalMapper *signal_mapper = new QSignalMapper(this);
	for(int i=0; i<string_list.size(); i++)
	{
		PushButton *tool_button = new PushButton();
		tool_button->setPicName(string_list.at(i));
		tool_button->setCheckable(true,false);
		button_list.append(tool_button);
		connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
		signal_mapper->setMapping(tool_button, QString::number(i, 10));
		button_layout->addWidget(tool_button);
		button_layout->setSpacing(25);
	}

	PushButton *tool_button = button_list.at(1);
	mUnreadMsgCount = new UnreadMsgLabel(tool_button);
	mUnreadMsgCount->setVisible(false);
	mUnreadMsgCount->move(4,0);

	connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(turnPage(QString)));
	
 
	main_layout = new QVBoxLayout();
	////main_layout->setSpacing(5);
 	main_layout->addWidget(m_pAvatarArea);
	m_pAvatarArea->setContentsMargins(10, 20, 0,40);
	///m_pAvatarArea->setFixedWidth(58);
	////main_layout->addStretch();
	//main_layout->setSpacing(50);
	main_layout->addLayout(button_layout);
	main_layout->addStretch(4);


	ex_col_button = new PushButton(this);
	ex_col_button->setPicName(QString(":/title/collapse"));
	m_curWebWindowState = 0;

	connect(ex_col_button, SIGNAL(clicked()), this, SLOT(slotAdjustWebWindow()));

	main_layout->addWidget(ex_col_button,0,Qt::AlignRight);

	ex_col_button->setVisible(false);

	main_layout->addStretch(1);
	main_layout->addLayout(title_layout);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0,0, 0,0);
	///setStyleSheet("background:rgb(39,104,194)");
	this->translateLanguage();
	setFixedWidth(60);
	///setMaximumWidth(60);
    setLayout(main_layout);



	///
	///
	/////timer = new QTimer(this);
  	//connect(timer, SIGNAL(timeout()), this, SLOT(slotClicked()));

 
}

void TitleWidget::slotAdjustWebWindow()
{
	emit signalAdjustWebWindow(m_curWebWindowState);
	// 0 展开  1 收起
	if (m_curWebWindowState==0) m_curWebWindowState = 1;
	else m_curWebWindowState = 0; 
	ex_col_button->setPicName((m_curWebWindowState == 0) ? QString(":/title/collapse") : QString(":/title/expand"));
}


void TitleWidget::slotClicked()
{
	////timer->stop();
	//QMessageBox::information(NULL, QString::fromLocal8Bit("Click"),
	////	QString::fromLocal8Bit("This is click."), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);


}
 

void TitleWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
////	timer->stop();
	/*QMessageBox::information(NULL, QString::fromLocal8Bit("DoubleClick"),
		QString::fromLocal8Bit("This is DoubleClick."), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);*/
	emit maxWiget();
}
 

void TitleWidget::translateLanguage()
{
///	min_button->setToolTip(transfer("最小化"));
///	max_button->setToolTip(transfer("最大化"));
////	close_button->setToolTip(transfer("关闭"));
	button_list.at(0)->setText(transfer("首页"));
	button_list.at(1)->setText(transfer("消息"));
	button_list.at(2)->setText(transfer("联系人"));
	button_list.at(3)->setText(transfer("我的"));

	button_list.at(0)->setToolTip(transfer("首页"));
	button_list.at(1)->setToolTip(transfer("消息"));
	button_list.at(2)->setToolTip(transfer("联系人"));
	button_list.at(3)->setToolTip(transfer("我的"));
	menu_button->setToolTip(transfer("主菜单"));
	mActionSet->setText(transfer("设置"));
	///m_actionLog->setText(transfer("意见反馈"));
	mMsgManager->setText(transfer("消息管理"));
}

void TitleWidget::turnPage(QString current_page)
{
	bool ok;  
	int current_index = current_page.toInt(&ok, 10);

	for(int i=0; i<button_list.count(); i++)
	{
		PushButton *tool_button = button_list.at(i);
		if(current_index == i)
		{
			tool_button->setCheckable(true,true);
		}
		else
		{
			tool_button->setCheckable(true,false);
		}
	}
	emit turnPage(current_index);
	this->update();
}
void TitleWidget::onTurnPage(int current_page){
	turnPage(QString::number(current_page));
}
void TitleWidget::onMaxWiget(){
	m_ismax = !m_ismax;
/*	if ( m_ismax)
	{
		max_button->setPicName(QString(":/title/restore"));
	}
	else{
	    max_button->setPicName(QString(":/title/max"));
	}
	*/
	emit maxWiget();
}

TitleWidget::~TitleWidget()
{

}

void TitleWidget::onUnreadMsgCountNotify( int count )
{
 
	if(count >0){
		QString cnt = count>99?"99+":QString::number(count);
		mUnreadMsgCount->setText(cnt);
		mUnreadMsgCount->setVisible(true);
		mUnreadMsgCount->move(4, 0);
	}else{
		mUnreadMsgCount->setVisible(false);
		mUnreadMsgCount->move(6, 0);
	}
}
void TitleWidget::setSupportStretch(bool isSupportStretch){
	this->setMouseTracking(isSupportStretch);
	// 这里对子控件也进行了设置，是因为如果不对子控件设置，当鼠标移动到子控件上时，不会发送mouseMoveEvent事件，也就获取不到当前鼠标位置，无法判断鼠标状态及显示样式了。
	QList<QWidget*> widgetList = this->findChildren<QWidget*>();
	for each (QWidget* widget in widgetList)
	{
		widget->setMouseTracking(isSupportStretch);
	}
}
void TitleWidget::mousePressEvent(QMouseEvent *event){
	
	if ( Qt::LeftButton == event->button())
	{
		emit moveWindow(true);
		event->ignore();
 	}
	/////timer->start(1000);

}
void TitleWidget::mouseReleaseEvent(QMouseEvent *event){
	if ( Qt::LeftButton == event->button())
	{
		emit moveWindow(false);
		event->ignore();
	}
}
void TitleWidget::showUserInfo(QPoint pos)
{
	BEGIN;
	if (m_userInfo == NULL)
	{
		m_userInfo = new UserInfoWidget;
		connect(m_userInfo, SIGNAL(signalWinClose()), this, SLOT(onUserWinClose()));
		connect(m_userInfo, SIGNAL(signalUserHeadSucc(QString)), this, SLOT(onUserHeadSucc(QString)),Qt::QueuedConnection);
	}
	//AddLog(LOG_LEV_INFO,"====x:%d---y:%d",this->mapToGlobal(QPoint(this->x(),this->y())).x(),this->mapToGlobal(QPoint(this->x(),this->y())).y());
	//int x = this->mapToGlobal(QPoint(this->x(),this->y())).x();
	//int y = this->mapToGlobal(QPoint(this->x(),this->y())).y();
	m_userInfo->resize(HEAD_WIDTH,HEAD_HEIGTH);
	m_userInfo->move(pos.x()+310, pos.y()+52);
	m_userInfo->setFocus();
	m_userInfo->ShowInfo();
	END;
}
void TitleWidget::onUserWinClose()
{
	BEGIN;
    m_userInfo->close();
	END;
}
void TitleWidget::onUserHeadSucc(QString headImg)
{
	Log(LOG_LEV_INFO, LOG_FILE, "avatar path:%s", headImg.toStdString().c_str());
	m_pAvatarArea->setAvatarPath(headImg);
}

void TitleWidget::showMenu()
{
	QPoint pos =QCursor::pos();
	pos.setY(pos.y()-40);
	pos.setX(pos.x()+20);
 
 	mNemu->exec(pos);
}

void TitleWidget::onShowSetWin()
{
	mSetWin->showWin(m_hotKeyHasConflict);
}

void TitleWidget::onShowLogWin()
{
	//SuggestionFeedbackDialog suggestion;
	//connect(&suggestion, SIGNAL(ShowSuggestionDialog(QString&)),this, SLOT(onShowSuggesSendWin(QString&)));
	///suggestion.exec();
}

void TitleWidget::onShowSuggesSendWin(QString& filepath)
{
	SuggestionFeedbackSendDialog mSuggestionSend;
	mFilePath = filepath;
	connect(&mSuggestionSend, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SLOT(onShowSendFile(CSharedPtr<data::ChatInfo>&)));
	mSuggestionSend.exec();
}

void TitleWidget::onShowSendFile(CSharedPtr<data::ChatInfo>& chat)
{
	emit startChat(chat, mFilePath);
}

void TitleWidget::initHotKey()
{
    std::vector<std::string> keys;
    keys.push_back("SendMsgKey");
    keys.push_back("PrtScKey");
    keys.push_back("GetMoreMsgKey");

    std::vector<data::UserLocalSetting> retData;
    bool isGet = false;

    QString                    curentScreenShot;
    QString                    curentPushMsg;
    int                        curentSendMsg = ENTER_SEND;

    if (m_userControl)
    {
        isGet = m_userControl->getLocalSettingSync(keys,retData);
    }

    if (retData.empty())
    {
        setScreenHotKey("alt+d",true);
        setPushMsgHotKey("alt+c",true);

        std::vector<data::UserLocalSetting> vec;
        data::UserLocalSetting setPrt;

        setPrt.key = "PrtScKey";
        setPrt.val = "";
        vec.push_back(setPrt);

        setPrt.key = "SendMsgKey";
        vec.push_back(setPrt);

        setPrt.key = "GetMoreMsgKey";
        vec.push_back(setPrt);

        m_userControl->addLocalSettingSync(vec);
    }else{
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

            else if (retData[index].key == std::string("PrtScKey"))
            {
                curentScreenShot = QString::fromUtf8(retData[index].val.data());
                setScreenHotKey(curentScreenShot,true);
            }
            else if (retData[index].key == std::string("GetMoreMsgKey"))
            {
                curentPushMsg = QString::fromUtf8(retData[index].val.data());
                setPushMsgHotKey(curentPushMsg,true);
            }
        }
    }
	emit sendMsgHotKeyUpdate(curentSendMsg);
    mSetWin->setDefaultValue(curentSendMsg, curentScreenShot,curentPushMsg);
}

void TitleWidget::onStartScreenShot()
{
    emit startScreenShotProcess();
}


bool TitleWidget::setHotKey( QString key, int type)
{
    bool bHasConflict = false;
    if (type == KEY_SCREEN)
    {
        //设置热键
		m_globalShortcut.reset();
		m_globalShortcut = CMakePtr<QxtGlobalShortcut>(this);
        bHasConflict = m_globalShortcut->setShortcut(QKeySequence(key)); 
    }

    if (type == KEY_MOREMSG)
    {
        //设置热键
#ifdef _WIN32
        m_globalMoreMsg = CMakePtr<QxtGlobalShortcut>(this);
        bHasConflict = m_globalMoreMsg->setShortcut(QKeySequence(key)); 
        //Linux下"Ctrl+Alt+D"被占用
#elif defined(__APPLE__)
        m_globalMoreMsg.reset(new QxtGlobalShortcut(this));
        bHasConflict = m_globalMoreMsg->setShortcut(QKeySequence("Ctrl+Alt+D"));
        Log(LOG_LEV_INFO, LOG_FILE, "m_globalMoreMsg->setShortcut:%d", bHasConflict);
#else
        m_globalMoreMsg.reset(new QxtGlobalShortcut(QKeySequence("Ctrl+Alt+S"), this));
#endif
    }

    return bHasConflict;
}

void TitleWidget::setScreenHotKey( QString key,bool isInit )
{
	//2019-6-10  bxy
	bool bHasConflict = setHotKey(key, KEY_SCREEN);

	if (!bHasConflict)
	{
		m_hotKeyHasConflict = CONFLICT_PRTSCKEY;
		emit setHotKeyHasConflict(m_hotKeyHasConflict);
		gCutScrenToolTips = transfer("截屏快捷键冲突，请重新设置");
	}
	else{
		updateLocalSetting("PrtScKey", key.toStdString());
		QObject::connect(m_globalShortcut.get(), SIGNAL(activated()), this, SLOT(onStartScreenShot()));
		if (!isInit)
		{
			emit setHotKeySuccess();
		}
		gCutScrenToolTips = transfer("截屏快捷键")+key;
	}
}

void TitleWidget::hotKeySetting( QString screen, QString msg )
{
    if (!screen.isEmpty())
    {
         setScreenHotKey(screen);
    }

    if (!msg.isEmpty())
    {
        setPushMsgHotKey(msg);
    }
}

void TitleWidget::onSendMsgSetting( int val)
{
    std::string strval = val == 2 ? "ctrl+enter" : "enter";
    if (m_userControl)
    {
        data::UserLocalSetting set;
        set.key = "SendMsgKey";
        set.val = strval;

        std::vector<data::UserLocalSetting> vec;
        vec.push_back(set);
        m_userControl->updateLocalSettingSync(vec);
    }
    emit signalSendMsgShot(val);
	emit sendMsgHotKeyUpdate(val);
}

void TitleWidget::initNotify()
{
    std::vector<std::string> keys;
    keys.push_back("MsgSoundKey");

    std::vector<data::UserLocalSetting> retData;
    bool isGet = false;

    if (m_userControl)
    {
        isGet = m_userControl->getLocalSettingSync(keys,retData);
    }

    if (retData.empty())
    { 
        std::vector<data::UserLocalSetting> vec;
        data::UserLocalSetting setKey;

        setKey.key = "MsgSoundKey";
        setKey.val = "soundopen";
        vec.push_back(setKey);

        m_userControl->addLocalSettingSync(vec);
        m_bSoundOpen = true;
        emit setMsgSoundState(m_bSoundOpen);
    }else{
        for (qint16 index = 0; index < retData.size(); ++index)
        {
            if (retData[index].key == std::string("MsgSoundKey"))
            {
                QString sdMsg = QString::fromUtf8(retData[index].val.data());
                sdMsg = sdMsg.replace(" ", "");
                sdMsg = sdMsg.toLower();
                if (sdMsg == "soundopen")
                {
                    m_bSoundOpen = true;
                    emit signalPlaySound(m_bSoundOpen);
                    emit setMsgSoundState(m_bSoundOpen);
                }
                else if (sdMsg == "soundoff")
                {
                    m_bSoundOpen = false;
                    emit signalPlaySound(m_bSoundOpen);
                    emit setMsgSoundState(m_bSoundOpen);
                }
            }
        }
    }
}

void TitleWidget::InitSetting()
{
    BEGIN;
    initHotKey();
    initNotify();
    END;
}

void TitleWidget::onPushMsg()
{
    BEGIN;
    emit showMsgWidget();
    END;
}

void TitleWidget::setPushMsgHotKey( QString key,bool isInit)
{
	// 2019-6-10 bxy
	bool bHasConflict = setHotKey(key, KEY_MOREMSG);
	if (!bHasConflict)
	{
		m_hotKeyHasConflict = CONFLICT_PUSHMSGKEY;
		emit setHotKeyHasConflict(m_hotKeyHasConflict);

	}
	else{
		if (!isInit)
		{
			emit setHotKeySuccess();
		}
		updateLocalSetting("GetMoreMsgKey", key.toStdString());
		QObject::connect(m_globalMoreMsg.get(), SIGNAL(activated()), this, SLOT(onPushMsg()));
	}
	/*
    bool bHasConflict = setHotKey(key,KEY_MOREMSG);
    if(!bHasConflict)
    {
        if (!isInit)  //修改快捷键，显示
        {
            QMessageBox box(QMessageBox::Critical,APP_NAME,"消息快捷键冲突,设置失败");
            box.exec();
        }else{
            m_hotKeyHasConflict = CONFLICT_PUSHMSGKEY;
            emit setHotKeyHasConflict(m_hotKeyHasConflict);
        }
    }else{
        if (!isInit)
        {
            QMessageBox box(QMessageBox::Information,APP_NAME,"拉取消息快捷键设置成功 ");
            box.exec();
        }
        updateLocalSetting("GetMoreMsgKey", key.toStdString());
        QObject::connect(m_globalMoreMsg.get(), SIGNAL(activated()),this, SLOT(onPushMsg()));
    }*/
}

void TitleWidget::updateLocalSetting( std::string key, std::string val )
{
    if (m_userControl)
    {
        AddLog(LOG_LEV_DEBUG,LOG_FILE,"updateLocalSetting key = %s,val = %s",key.data(),val.data());
        data::UserLocalSetting setPrt;
        setPrt.key = key;
        setPrt.val = val;

        std::vector<data::UserLocalSetting> vec;
        vec.push_back(setPrt);

        m_userControl->updateLocalSettingSync(vec);
    }
}

void TitleWidget::onSHowAddContactMenu()
{
	QPoint pos(mBtnAddContact->x()+20,mBtnAddContact->y()+30);
	pos = mapToGlobal(pos);
	m_menuMain->exec(pos);
}

void TitleWidget::onBtnCreateGroup()
{
	emit addContactOrCreateGroup(2);
}

void TitleWidget::onBtnAddFrindOrGroup()
{
	emit addContactOrCreateGroup(1);
}

void TitleWidget::onShowMsgManagerWin()
{
	MsgManagerWidget msgmanager;
	//connect(&msgmanager, SIGNAL(ShowSuggestionDialog(QString&)),this, SLOT(onShowSuggesSendWin(QString&)));
	msgmanager.exec();
}

}
