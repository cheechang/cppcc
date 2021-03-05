#include "HotKeySetting.h"
#include "common/Common.h"
#include "controls/HotKeyLineEdit.h"
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QTimer>

namespace ui{
	HotKeySetting::HotKeySetting(QWidget* parent): TWidget(parent),m_curMsgKey(""),m_curScreenKey("")
	{
        setObjectName("groupinfobackground");
        InitWidgets();
	}


	HotKeySetting::~HotKeySetting(void)
	{

	}

    void HotKeySetting::InitWidgets()
    {
        m_labMsg = CMakePtr<QLabel>(this);

        m_radioCtrlEnter = CMakePtr<QRadioButton>(transfer("按Ctrl+Enter键"),this);
        m_radioEnter     = CMakePtr<QRadioButton>(transfer("按Enter键     "),this);
        m_radioGroup     = CMakePtr<QButtonGroup>(this);

        m_ErrTip = CMakePtr<TipWidget>(this);
        m_ErrTip->setVisible(false);
        m_ErrTip->setTime(3);  //显示3s
        m_ErrTip->setTipSize(QSize(350,25));
        m_ErrTip->move(310,100);
		
        m_editScreenShot = CMakePtr<HotKeyLineEdit>(this);
        m_editPushMsg    = CMakePtr<HotKeyLineEdit>(this);
        m_formLayout = CMakePtr<QFormLayout>();

        m_btnSetDefault = CMakePtr<QPushButton>(this);

        m_btnOk = CMakePtr<QPushButton>(this);
        m_btnCancel = CMakePtr<QPushButton>(this);

        m_labMsg->setText(transfer("会话窗口发送消息:"));
        m_labMsg->setMinimumWidth(220);

        m_radioCtrlEnter->setCheckable(true);
        m_radioCtrlEnter->setMinimumWidth(220);
        m_radioEnter->setCheckable(true);

        m_radioEnter->setMinimumWidth(220);
        m_radioEnter->setChecked(true);

        connect(m_radioCtrlEnter.get(),SIGNAL(clicked()),this,SLOT(onRadioButtonClicked()));
        connect(m_radioEnter.get(),SIGNAL(clicked()),this,SLOT(onRadioButtonClicked()));

        m_editPushMsg->setFixedSize(150,28);
        m_editPushMsg->setObjectName("HotKey");
        m_editScreenShot->setFixedSize(150,28);
        m_editScreenShot->setObjectName("HotKey");
        m_editPushMsg->setVisible(true);

        m_formLayout->addRow(transfer("截屏快捷键： "),m_editScreenShot.get());
        m_formLayout->addRow(transfer("显示主窗口: "), m_editPushMsg.get());

        m_btnSetDefault->setText(transfer("恢复默认设置"));
        m_btnSetDefault->setFixedSize(QSize(180,26));
        m_btnSetDefault->setObjectName("HotKey");

        m_btnOk->setText(transfer("进行热键设置"));
        m_btnOk->setObjectName("sendbtn");
        m_btnOk->setFixedSize(QSize(180,26));
        connect(m_btnOk.get(),SIGNAL(clicked()),this,SLOT(onOKBtnClicked()));

        m_btnCancel->setText(transfer("取消"));
        m_btnCancel->setObjectName("sendbtn");
        m_btnCancel->setFixedSize(68,26);
        m_btnCancel->setVisible(false);
        connect(m_btnCancel.get(),SIGNAL(clicked()),this,SLOT(onCancelBtnClicked()));

        connect(m_btnSetDefault.get(),SIGNAL(clicked()),SLOT(onDefaultSettingClicekd()));
        m_mainLayout = CMakePtr<QVBoxLayout>(this);
        m_mainLayout->setSpacing(5);
        m_mainLayout->addWidget(m_labMsg.get(),0,Qt::AlignCenter);
        m_mainLayout->addWidget(m_radioCtrlEnter.get(),0,Qt::AlignCenter);
        m_mainLayout->addWidget(m_radioEnter.get(),0,Qt::AlignCenter);
        QWidget* widget = new QWidget(this);
        widget->setLayout(m_formLayout.get());
        m_mainLayout->addWidget(widget,0,Qt::AlignCenter);
        m_mainLayout->addWidget(m_btnSetDefault.get(), 0 ,Qt::AlignCenter);
         m_mainLayout->addWidget(m_btnOk.get(),0,Qt::AlignCenter);

        m_mainLayout->setContentsMargins(20,20,20,20);
       // m_mainLayout->addStretch();
        this->setLayout(m_mainLayout.get());

        m_radioGroup->addButton(m_radioCtrlEnter.get(), 0);
        m_radioGroup->addButton(m_radioEnter.get(), 1);

    }

    void HotKeySetting::SetDefaultValue( int type, QString screen, QString msg )
    {
        int settype = type;
        if (settype == 0)
        {
            settype = ENTER_SEND;
        }

        if (settype == ENTER_SEND)
        {
            m_radioEnter->setChecked(true);
        }else{
            m_radioCtrlEnter->setChecked(true);
        }

        QString Keys = screen;
        if (screen.isEmpty())
        {
            Keys = "alt+d";
        }
        m_curScreenKey = Keys;
        m_editScreenShot->setText(m_curScreenKey);

        Keys = msg;
        if (Keys.isEmpty())
        {
            msg = "alt+c";
        }

        m_curMsgKey = msg;
        m_editPushMsg->setText(m_curMsgKey);
    }

    void HotKeySetting::onRadioButtonClicked()
    {
        if (m_radioGroup->checkedId() == 0)
        {
            emit signalSendMsgHotKey(CTRLENTER_SEND);
        }else{
            emit signalSendMsgHotKey(ENTER_SEND);
        }
    }

    void HotKeySetting::onDefaultSettingClicekd()
    {
         m_radioEnter->setChecked(true);
        m_editPushMsg->setText("alt+c");
        m_editScreenShot->setText("alt+d");

        emit signalHotKeySetting("alt+d","alt+c");
        emit signalSendMsgHotKey(ENTER_SEND);
    }

    void HotKeySetting::onOKBtnClicked()
    {
        QString screenKey = m_editScreenShot->text();
        QString msgKey = m_editPushMsg->text();
        if (screenKey.isEmpty() || msgKey.isEmpty())
        {
            m_ErrTip->setTipSize(QSize(250,25));
            m_ErrTip->setTipText(transfer("热键不能设置为空,请重新设置"));
            m_ErrTip->ErrShow();
            return;
        }

        screenKey = (screenKey == m_curScreenKey ? "" : screenKey);
        msgKey    = (msgKey == m_curMsgKey ? "" : msgKey);
		if (screenKey.isEmpty() && msgKey.isEmpty())
		{
			 m_ErrTip->setTipText(transfer("您没有修改热键"));
			 m_ErrTip->ErrShow();
		}
        emit signalHotKeySetting(screenKey,msgKey);
    }

    void HotKeySetting::onCancelBtnClicked()
    {
        //emit signalCloseWin();
    }

    void HotKeySetting::showConflictErr( int hasConfilct )
    {
        switch(hasConfilct)
        {
        case CONFLICT_PRTSCKEY:
            {
                m_ErrTip->setTipText(transfer("截图快捷键冲突，请重新设置"));
                m_ErrTip->ErrShow();
                break;
            }
        case CONFLICT_PUSHMSGKEY:
            {
                m_ErrTip->setTipText(transfer("拉去消息快捷键冲突，请重新设置"));
                m_ErrTip->ErrShow();
				break;
            }
        default:
			/*m_ErrTip->setTipText(transfer("热键设置成功"));
			m_ErrTip->ErrShow();*/
            break;
        }
		if (hasConfilct == 0)
		{
			m_curMsgKey = m_editPushMsg->text();
			m_curScreenKey = m_editScreenShot->text();
		}
    }

    void HotKeySetting::setHotKeyUIDefault()
    {
        m_editScreenShot->setText(m_curScreenKey);
        m_editPushMsg->setText(m_curMsgKey);
    }

	void HotKeySetting::onSetHotKeySuccess()
	{
		m_ErrTip->setTipText(transfer("热键设置成功,重新运行程序生效"));
		m_ErrTip->ErrShow();
		m_curScreenKey = m_editScreenShot->text();
	}

}
