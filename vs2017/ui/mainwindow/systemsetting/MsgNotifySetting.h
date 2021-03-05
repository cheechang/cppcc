#pragma once
#include <QWidget>
#include "controls/TWidget.h"
#include <interface/Defines.h>
#include "common/Controlptr.h"

class QRadioButton;
class QCheckBox;
class QLabel;
class QButtonGroup;

class QVBoxLayout;
class QFormLayout;
class QGridLayout;
namespace ui{
    class MsgNotifySetting : public TWidget
    {
        Q_OBJECT
    public:
        MsgNotifySetting(QWidget* parent);
        ~MsgNotifySetting(void);

        signals:
            void signalSerSetVResult(int result);
            void signalSerSetAtResult(int result);

            void signalSoundReminder(bool isSound);
            void signalSerGetNoDisturb(int err, int32 begintime, int32 endtime, bool flag);
            void signalSerSetDisturbResult(int result);
        public slots:
            void onMsgSoundReminderClicked(int state);
            void onMsgMuteNotifyClicekd(int state);
            void onVMsgButtonGorupClicekd(int state);
            void onAtMegButtonGroupClicked(int state);

            void onSerSetVResult(int result);
            void onSerSetAtResult(int result);
       
            void onMsgSoundUISet(bool);
            void onSerGetNoDisturb(int err, int32 begintime, int32 endtime, bool flag);
            void onSerSetDisturbResult(int result);
    protected:
        void initWidgets();
    private:
        CSharedPtr<QCheckBox>  m_cheBoxMsgSoundReminder;
        CSharedPtr<QCheckBox>  m_cheBoxMsgMuteNotify;
        QFormLayout*           m_formCheBoxLayout;

        CSharedPtr<QLabel>      m_labSpline;

        CSharedPtr<QLabel>       m_labVNotify;
        CSharedPtr<QRadioButton> m_vAlwaysSound;
        CSharedPtr<QRadioButton> m_vAlWaysMute;
        CSharedPtr<QRadioButton> m_vDoClassify;
        CSharedPtr<QButtonGroup> m_vButtonGroup;

        CSharedPtr<QLabel>       m_labAtNotify;
        CSharedPtr<QRadioButton> m_atAlwaysSound;
        CSharedPtr<QRadioButton> m_atAlWaysMute;
        CSharedPtr<QRadioButton> m_atDoClassify;
        CSharedPtr<QButtonGroup> m_atButtonGroup;


        QGridLayout*             m_gridLayout;
        CSharedPtr<QVBoxLayout>  m_mainLayout;

        IUserControl_Ptr         m_userServer;
    };
}


