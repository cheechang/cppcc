#include "SystemSetting.h"
#include <QHBoxLayout>
#include "HotKeySetting.h"
#include "PasswordReset.h"
#include "MsgNotifySetting.h"
#include "ContactBlacklistWin.h"
#include "../../common/Common.h"
namespace ui{
	SystemSetting::SystemSetting(QWidget *parent)
		: BaseWindow(parent)
	{
		__super::setTitle(transfer("系统设置"));
		connect(this,SIGNAL(closeClicked()),this,SLOT(winClose()));
		//导航栏
		mTabWidget = new QTabWidget(this);
		mTabWidget->setObjectName("systemSettabbar");
		//mTabWidget->setMinimumHeight(426);
		mMainLayout->addWidget(mTabWidget);
		mMainLayout->addStretch();

		mBasicArea = new SystemSettingBasicArea(this);
		mTabWidget->addTab(mBasicArea,transfer("基本设置"));

        mHotKeyArea = new HotKeySetting(this);
        mTabWidget->addTab(mHotKeyArea,transfer("热键"));
        connect(mHotKeyArea,SIGNAL(signalSendMsgHotKey(int)),this, SIGNAL(setSendMsgHotKey(int)));
        connect(mHotKeyArea,SIGNAL(signalHotKeySetting(QString,QString)),this,SIGNAL(signalHotKeySetting(QString,QString)));
        connect(this,SIGNAL(hotKeyHasConflict(int)),mHotKeyArea,SLOT(showConflictErr(int)));
	    connect(this, SIGNAL(hotKeySuccess()), mHotKeyArea, SLOT(onSetHotKeySuccess()));  /// 2019-6-10 rxy
      //  mPasswordReset = new PasswordReset(this);
        //mTabWidget->addTab(mPasswordReset,transfer("账号"));
       // connect(mPasswordReset,SIGNAL(signalCloseWin()),this,SLOT(winClose()));
		
        mMsgNotify = new MsgNotifySetting(this);
        mTabWidget->addTab(mMsgNotify,transfer("通知"));
        connect(this,SIGNAL(setMsgSoundState(bool)),mMsgNotify,SLOT(onMsgSoundUISet(bool)));
        connect(mMsgNotify,SIGNAL(signalSoundReminder(bool)),this,SIGNAL(signalPlaySound(bool)));
		
        mAboutArea = new AboutInfo(this);
        mTabWidget->addTab(mAboutArea,transfer("关于"));

       // mBlacklist = new ContactBlacklistWin(this);
       // mTabWidget->addTab(mBlacklist,transfer("黑名单"));
	}

	SystemSetting::~SystemSetting()
	{
	}

	void SystemSetting::showWin(int hasConfilct)
	{
        if (CNull != mHotKeyArea )
        {
            mHotKeyArea->setHotKeyUIDefault();
            mHotKeyArea->showConflictErr(hasConfilct);
        }

		mBasicArea->reqVerificationMode();
		showNormal();
	}

    void SystemSetting::setDefaultValue( int type, QString screen,QString msg )
    {
        if (mHotKeyArea != CNull)
        {
            mHotKeyArea->SetDefaultValue(type,screen,msg);
        }
    }

    void SystemSetting::winClose()
    {
        mTabWidget->setCurrentWidget(mBasicArea);
        this->close();
    }

}