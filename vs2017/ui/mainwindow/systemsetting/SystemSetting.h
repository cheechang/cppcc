#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include "../contact/createGroup/BaseWindow.h"
#include <QTabWidget>
#include "SystemSettingBasicArea.h"
#include "AboutInfo.h"

namespace ui{
	class AboutInfo;
    class HotKeySetting;
    class PasswordReset;
    class MsgNotifySetting;
    class ContactBlacklistWin;
	class SystemSetting : public BaseWindow
	{
		Q_OBJECT

	public:
		SystemSetting(QWidget *parent=CNull);
		~SystemSetting();
		void showWin(int hasConfilct);
        void setDefaultValue(int type, QString screen,QString msg);
    public slots:
        void winClose();
    signals:
        void signalHotKeySetting(QString screen, QString msg);
        void setSendMsgHotKey(int type);
        void hotKeyHasConflict(int conflict);
        void setMsgSoundState(bool);
        void signalPlaySound(bool);
	    void hotKeySuccess();
	protected:
		QTabWidget* mTabWidget;
		SystemSettingBasicArea* mBasicArea;
		AboutInfo*				mAboutArea;
        HotKeySetting*          mHotKeyArea;
       // PasswordReset*          mPasswordReset;
        MsgNotifySetting*       mMsgNotify;
        ContactBlacklistWin*    mBlacklist;
	};
}

#endif // SYSTEMSETTING_H
