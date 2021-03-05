#include "MsgNotifySetting.h"
#include "log.h"
#include "common/Common.h"
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
namespace ui{
    
    MsgNotifySetting::MsgNotifySetting(QWidget* parent):TWidget(parent)
    {
        setObjectName("groupinfobackground");
        m_userServer = USERCONTROL;
        
        initWidgets();
        CONNECT_SERVICE(SetVResult(int));
        CONNECT_SERVICE(SetAtResult(int));
        CONNECT_SERVICE(GetNoDisturb(int, int32, int32, bool));
        CONNECT_SERVICE(SetDisturbResult(int));
        if (m_userServer)
        {
            m_userServer->getGlobalNoDisturbMode(CBind(&MsgNotifySetting::signalSerGetNoDisturb,this, CPlaceholders _1,CPlaceholders _2, CPlaceholders _3, CPlaceholders _4));
        }
    }


    MsgNotifySetting::~MsgNotifySetting(void)
    {
    }

    void MsgNotifySetting::initWidgets()
    {
        m_cheBoxMsgMuteNotify = CMakePtr<QCheckBox>(transfer("开启免打扰"),this);
        m_cheBoxMsgSoundReminder = CMakePtr<QCheckBox>(transfer("开启消息声音提醒"),this);
        m_labSpline              = CMakePtr<QLabel>(this);

        m_labVNotify      = CMakePtr<QLabel>(transfer("V标通知方式"),this);
        m_vAlwaysSound    = CMakePtr<QRadioButton>(transfer("始终有声音"),this);
        m_vAlWaysMute     = CMakePtr<QRadioButton>(transfer("始终静音"),this);
        m_vDoClassify     = CMakePtr<QRadioButton>(transfer("按普通联系人/群处理"));

        m_labAtNotify      = CMakePtr<QLabel>(transfer("@我通知方式"),this);
        m_atAlwaysSound    = CMakePtr<QRadioButton>(transfer("始终有声音"),this);
        m_atAlWaysMute     = CMakePtr<QRadioButton>(transfer("始终静音"),this);
        m_atDoClassify     = CMakePtr<QRadioButton>(transfer("按普通联系人/群处理"));

        m_labSpline->setObjectName("SpliteLine");
        m_labSpline->setFixedSize(QSize(660,1));

        m_vButtonGroup = CMakePtr<QButtonGroup>(this);
        m_atButtonGroup = CMakePtr<QButtonGroup>(this);

        m_formCheBoxLayout = new QFormLayout();
        m_gridLayout       = new QGridLayout();
        m_mainLayout       = CMakePtr<QVBoxLayout>(this);

        connect(m_cheBoxMsgSoundReminder.get(),SIGNAL(stateChanged(int)),this,SLOT(onMsgSoundReminderClicked(int)));
        connect(m_cheBoxMsgMuteNotify.get(),SIGNAL(stateChanged(int)),this,SLOT(onMsgMuteNotifyClicekd(int)));
        connect(m_vButtonGroup.get(),SIGNAL(buttonClicked(int)),this,SLOT(onVMsgButtonGorupClicekd(int)));
        connect(m_atButtonGroup.get(),SIGNAL(buttonClicked(int)),this, SLOT(onAtMegButtonGroupClicked(int)));
       
        m_formCheBoxLayout->addRow(transfer("通知提醒:"),m_cheBoxMsgSoundReminder.get());
        m_formCheBoxLayout->addRow(transfer("免打扰设置:"),m_cheBoxMsgMuteNotify.get());
        m_formCheBoxLayout->setLabelAlignment(Qt::AlignRight);
        m_formCheBoxLayout->setFormAlignment(Qt::AlignLeft);
        m_formCheBoxLayout->setSpacing(20);

        QWidget* formWidget = new QWidget(this);
        formWidget->setLayout(m_formCheBoxLayout);  

        m_formCheBoxLayout->setVerticalSpacing(10);
        m_formCheBoxLayout->setContentsMargins(0,10,0,0);
        m_gridLayout->setColumnMinimumWidth(1,100);
        m_gridLayout->setColumnMinimumWidth(2,100);
        m_gridLayout->addWidget(m_labVNotify.get(),0,0,1,1,Qt::AlignRight);
        m_gridLayout->addWidget(m_vAlwaysSound.get(),0,1,1,1,Qt::AlignCenter);
        m_gridLayout->addWidget(m_vAlWaysMute.get(),0,2,1,1,Qt::AlignCenter);
        m_gridLayout->addWidget(m_vDoClassify.get(),0,3,1,1,Qt::AlignLeft);

        m_gridLayout->addWidget(m_labAtNotify.get(),1,0,1,1,Qt::AlignRight);
        m_gridLayout->addWidget(m_atAlwaysSound.get(),1,1,1,1,Qt::AlignCenter);
        m_gridLayout->addWidget(m_atAlWaysMute.get(),1,2,1,1,Qt::AlignCenter);
        m_gridLayout->addWidget(m_atDoClassify.get(),1,3,1,1,Qt::AlignLeft);

        m_gridLayout->setHorizontalSpacing(5);
        m_gridLayout->setVerticalSpacing(10);
        m_gridLayout->setContentsMargins(0,0,50,0);
        m_mainLayout->addWidget(formWidget,0,Qt::AlignCenter);
        m_mainLayout->addSpacing(10);
        m_mainLayout->addWidget(m_labSpline.get(),0,Qt::AlignCenter);
        m_mainLayout->addSpacing(10);
        m_mainLayout->addLayout(m_gridLayout);
        m_mainLayout->addStretch();

        m_vAlwaysSound->setChecked(true);
        m_vButtonGroup->addButton(m_vAlwaysSound.get(),MSG_ALWAYS);
        m_vButtonGroup->addButton(m_vAlWaysMute.get(),MSG_MUTE);
        m_vButtonGroup->addButton(m_vDoClassify.get(),MSG_CLASSIFY);

        m_atAlwaysSound->setChecked(true);
        m_atButtonGroup->addButton(m_atAlwaysSound.get(),MSG_ALWAYS);
        m_atButtonGroup->addButton(m_atAlWaysMute.get(),MSG_MUTE);
        m_atButtonGroup->addButton(m_atDoClassify.get(),MSG_CLASSIFY);

        this->setLayout(m_mainLayout.get());
    }

    void MsgNotifySetting::onMsgSoundReminderClicked(int state)
    {
        BEGIN;
        AddLog(LOG_LEV_INFO,LOG_FILE,"ReminderClicked = %d",state);
        bool isChecked = (state == Qt::Checked ? true :false);
        std::string val= "soundopen";

        if (!isChecked)
        {
            val = "soundoff";
        }

        std::vector<data::UserLocalSetting> vec;
        data::UserLocalSetting setKey;

        setKey.key = "MsgSoundKey";
        setKey.val = val;
        vec.push_back(setKey);

        bool ret =  m_userServer->updateLocalSettingSync(vec);
        AddLog(LOG_LEV_DEBUG,LOG_FILE,"updateLocalSettingSync ret = %d",ret);

        emit signalSoundReminder(isChecked);
        END;
    }

    void MsgNotifySetting::onMsgMuteNotifyClicekd(int state)
    {
        BEGIN;
        AddLog(LOG_LEV_INFO,LOG_FILE,"MuteNotifyClicekd = %d",state);
        bool isOpen = ( state ? Qt::Checked : Qt::Unchecked);
        if (m_userServer)
        {
            m_userServer->setGolbalNoDisturbMode(0,0,isOpen,CBind(&MsgNotifySetting::signalSerSetDisturbResult,this, CPlaceholders _1));
        }
        END;
    }

    void MsgNotifySetting::onVMsgButtonGorupClicekd( int state )
    {
        BEGIN;
        AddLog(LOG_LEV_INFO,LOG_FILE,"MuteNotifyClicekd = %d",state);

        std::vector<data::PersonalData> items;
        data::PersonalData vSet;

        vSet.type = 5;
        vSet.val = state;
        items.push_back(vSet);

        if (m_userServer)
        {
            m_userServer->setPersonalData(items,CBind(&MsgNotifySetting::signalSerSetVResult,this,CPlaceholders _1));
        }
        END;
        
    }

    void MsgNotifySetting::onAtMegButtonGroupClicked( int state )
    {
        BEGIN;
        AddLog(LOG_LEV_INFO,LOG_FILE,"MuteNotifyClicekd = %d",state);

        std::vector<data::PersonalData> items;
        data::PersonalData vSet;

        vSet.type = 6;
        vSet.val = state;
        items.push_back(vSet);

        if (m_userServer)
        {
            m_userServer->setPersonalData(items,CBind(&MsgNotifySetting::signalSerSetAtResult,this,CPlaceholders _1));
        }
        END;
    }

    void MsgNotifySetting::onSerSetVResult( int state)
    {
        AddLog(LOG_LEV_INFO,LOG_FILE,"onSerSetVResult = %d",state);
    }

    void MsgNotifySetting::onSerSetAtResult( int state)
    {
        AddLog(LOG_LEV_INFO,LOG_FILE,"onSerSetAtResult = %d",state);
    }

    void MsgNotifySetting::onMsgSoundUISet( bool isSound)
    {
        AddLog(LOG_LEV_DEBUG,LOG_FILE,"onMsgSoundUISet = %d",isSound);
        Qt::CheckState sate =(isSound ? Qt::Checked : Qt::Unchecked);
        m_cheBoxMsgSoundReminder->setCheckState(sate);
    }

    void MsgNotifySetting::onSerGetNoDisturb( int err, int32 begintime, int32 endtime, bool flag )
    {
        AddLog(LOG_LEV_INFO,LOG_FILE,"onSerGetNoDisturb err = %d",err);
        if (!err)
        {
            Qt::CheckState  state = (flag ? Qt::Checked : Qt::Unchecked);
            m_cheBoxMsgMuteNotify->setCheckState(state);

        }else{
                AddLog(LOG_LEV_ERROR,LOG_FILE,"onSerGetNoDisturb err");
        }
    }

    void MsgNotifySetting::onSerSetDisturbResult( int result )
    {
        BEGIN;
        if (0 != result)
        {
            AddLog(LOG_LEV_DEBUG,LOG_FILE,"onSetDisturbResult  result= %d",result);
        }
        END;
    }

}
