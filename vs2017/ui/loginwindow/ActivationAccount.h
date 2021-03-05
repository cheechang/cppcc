#pragma once
#include "../contact/createGroup/BaseWindow.h"
#include <common/Controlptr.h>
#include <utils/common.h>
class QLineEdit;
class QLabel;
class QPushButton;
class QFormLayout;
class QVBoxLayout;

namespace ui{
    class TipWidget;
    class ActivationAccount :  public BaseWindow
    {
        Q_OBJECT
    public:
        ActivationAccount();
        ~ActivationAccount(void);
    signals:
        void signalSerGetPasswordRule(int err, int rule);
        void signalHasChanged(QString pwd);

        void signalSerChangePasswordResult(int result);
        void signalLoginOut(int err);
    public slots:
        void onSerGetPasswordRule(int err, int rule);
        void onSerChangePasswordResult(int result);
        void onBtnOkClicked();
        void onLoginOut(int err);
    protected:
        void IninWidgets();
        QString GetPasswordString(utils::PassWordStipulate rule);
    private:

        CSharedPtr<QLineEdit>   m_curPassword;
        CSharedPtr<QLineEdit>   m_newPassword;
        CSharedPtr<QLineEdit>   m_cofPaaaword;
        CSharedPtr<QPushButton> m_btnOK;
        CSharedPtr<QLabel>      m_labRule;
        CSharedPtr<QFormLayout> m_formLayout;
        CSharedPtr<QVBoxLayout> m_mainLayout;
        CSharedPtr<TipWidget>   m_errTip;
        IAuthControl_Ptr       m_authServer;
        utils::PassWordStipulate  m_pswdStrategy;	//ÃÜÂë²ßÂÔ
    };
}


