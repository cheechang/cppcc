#pragma once
#include "controls/TWidget.h"
#include <common/Controlptr.h>
#include "../../loginwindow/TipWidget.h"
class QRadioButton;
class QLabel;
class QLineEdit;
class QPushButton;
class QFormLayout;
class QVBoxLayout;
class QButtonGroup;
class QHBoxLayout;

namespace ui{
    class HotKeyLineEdit;
    class TipWidget;
	class HotKeySetting :  	public TWidget
	{
        Q_OBJECT
	public:
		HotKeySetting(QWidget* parent);
		~HotKeySetting(void);
        void SetDefaultValue(int type, QString screen, QString msg);
        void setHotKeyUIDefault();
    public slots:
        void onRadioButtonClicked();
        void onDefaultSettingClicekd();
        void onOKBtnClicked();
        void onCancelBtnClicked();
        void showConflictErr(int hasConfilct);
		void onSetHotKeySuccess();
signals:
        void signalSendMsgHotKey(int key);
        void signalHotKeySetting(QString scren, QString msg);
        void signalCloseWin();
    protected:
        void InitWidgets();
	private:
		CSharedPtr<QLabel>		  m_labMsg;

		CSharedPtr<QRadioButton>  m_radioCtrlEnter;
		CSharedPtr<QRadioButton>  m_radioEnter;
        CSharedPtr<QButtonGroup > m_radioGroup;

        CSharedPtr<HotKeyLineEdit>     m_editScreenShot;
        CSharedPtr<HotKeyLineEdit>     m_editPushMsg;

        CSharedPtr<QPushButton>   m_btnSetDefault;
        CSharedPtr<QFormLayout>    m_formLayout;
        CSharedPtr<QVBoxLayout>    m_mainLayout;
        CSharedPtr<QPushButton>    m_btnOk;
        CSharedPtr<QPushButton>    m_btnCancel;
        CSharedPtr<TipWidget>      m_ErrTip;

        QString m_curScreenKey;
        QString m_curMsgKey;
	};
}


