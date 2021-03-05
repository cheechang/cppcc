#pragma once
#include "controls/TWidget.h"
#include <common/Controlptr.h>
#include <utils/common.h>
class QLineEdit;
class QLabel;
class QPushButton;
class QFormLayout;
class QVBoxLayout;
class QHBoxLayout;

namespace ui{
    class ContactBlacklistWin;
    class PasswordReset :    public TWidget
    {
        Q_OBJECT
    public:
        PasswordReset(QWidget* parent);
        ~PasswordReset(void);
       
signals:
        void signalSerGetPasswordRule(int err, int rule);
        void signalSerChangePasswordResult(int result);
        void signalCloseWin();
public slots:
        void onSerGetPasswordRule(int err, int rule);
        void onSerChangePasswordResult(int result);
        void onBtnOkClicked();
        void onBtnBlackListClicked();
    protected:
         void InitWidgets();
         QString GetPasswordString(utils::PassWordStipulate rule);
    private:

        CSharedPtr<QLabel>     m_labShowMsg;
        CSharedPtr<QLineEdit>  m_editOldPassword;
        CSharedPtr<QLineEdit>  m_editNewPassword;
        CSharedPtr<QLineEdit>  m_editConfirmWord;

        CSharedPtr<QLabel>     m_labPasswordRule;

        CSharedPtr<QPushButton> m_btnRestWord;
        CSharedPtr<QPushButton> m_btnCancel;
        CSharedPtr<QFormLayout> m_passLayout;
        CSharedPtr<QVBoxLayout> m_mainLayout;
         CSharedPtr<QPushButton> m_btnBlacklist;
        CSharedPtr<ContactBlacklistWin> m_BlacklistWin;
        IAuthControl_Ptr       m_authServer;
        utils::PassWordStipulate  m_pswdStrategy;	//ÃÜÂë²ßÂÔ
    };
}


