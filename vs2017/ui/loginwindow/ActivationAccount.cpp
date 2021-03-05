#include "ActivationAccount.h"
#include <core/BaseDialog.h>
#include "TipWidget.h"
#include "log.h"
#include "../utils/Error.h"
#include <common/ChineseInfos.hpp>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxlayout>
#include <QHBoxLayout>
#include "../common/Common.h"

namespace ui{

    ActivationAccount::ActivationAccount(void)
    {
        m_authServer = AUTHCONTROL;
        this->setTitle(QString::fromLocal8Bit("账号激活"));
        this->setFixedSize(QSize(320,240));
        IninWidgets();
        m_errTip->raise();
        connect(this,SIGNAL(signalSerGetPasswordRule(int,int)),this,SLOT(onSerGetPasswordRule(int,int)));
        connect(this,SIGNAL(signalSerChangePasswordResult(int)),this,SLOT(onSerChangePasswordResult(int)));
        connect(this,SIGNAL(signalLoginOut(int)),this,SLOT(onLoginOut(int)));
        if (m_authServer)
        {
             m_authServer->getPasswordRule(CBind(&ActivationAccount::signalSerGetPasswordRule,this,std::placeholders::_1,std::placeholders::_2));
        }
    }


    ActivationAccount::~ActivationAccount(void)
    {
    }

    void ActivationAccount::IninWidgets()
    {
        m_curPassword = CMakePtr<QLineEdit>(this);
        m_newPassword = CMakePtr<QLineEdit>(this);
        m_cofPaaaword = CMakePtr<QLineEdit>(this);
        m_labRule     = CMakePtr<QLabel>(this);
        m_btnOK       = CMakePtr<QPushButton>(this);

        m_formLayout = CMakePtr<QFormLayout>();
        m_mainLayout = CMakePtr<QVBoxLayout>(this);

        m_errTip = CMakePtr<TipWidget>(this);
        m_errTip->setTime(3);
        m_errTip->setTipSize(QSize(300,25));
        m_errTip->move(10,40);
        m_errTip->setVisible(false);

        m_labRule->adjustSize();
        m_labRule->setGeometry(QRect(210,70, 260, 30*4));  //四倍行距

        m_labRule->setWordWrap(true);
        m_labRule->setAlignment(Qt::AlignTop);

        m_curPassword->setFixedHeight(28);
        m_curPassword->setContextMenuPolicy(Qt::NoContextMenu);
        m_curPassword->setEchoMode(QLineEdit::Password);
        m_newPassword->setFixedHeight(28);
        m_newPassword->setContextMenuPolicy(Qt::NoContextMenu);
        m_newPassword->setEchoMode(QLineEdit::Password);
        m_cofPaaaword->setFixedHeight(28);
        m_cofPaaaword->setContextMenuPolicy(Qt::NoContextMenu);
        m_cofPaaaword->setEchoMode(QLineEdit::Password);

        m_btnOK->setText(transfer("确定"));
        m_btnOK->setObjectName("sendbtn");
        m_btnOK->setFixedSize(QSize(60,26));
        connect(m_btnOK.get(),SIGNAL(clicked()),this,SLOT(onBtnOkClicked()));

        m_formLayout->setContentsMargins(20,20,20,0);
        m_formLayout->setVerticalSpacing(5);
        m_formLayout->addRow(transfer("当前密码:"),m_curPassword.get());
        m_formLayout->addRow(transfer("新密码："),m_newPassword.get());
        m_formLayout->addRow(transfer("确认密码:"),m_cofPaaaword.get());

        QWidget* tmp = new QWidget(this);
        tmp->setLayout(m_formLayout.get());

        mMainLayout->addWidget(tmp);
        QHBoxLayout* labLayout = new QHBoxLayout();
        labLayout->addWidget(m_labRule.get());
        labLayout->setContentsMargins(15,5,10,0);
        mMainLayout->addLayout(labLayout);

        m_btnOK->move(225,195);
        m_btnOK->raise();

        mMainLayout->addStretch();
    }

    void ActivationAccount::onSerGetPasswordRule( int err, int rule )
    {
        utils::PassWordStipulate result= utils::AnalysisPwdRule(rule);
        if (!err)
        {
            QString rul = GetPasswordString(result);
            m_labRule->setText(rul);
        }
        this->show();
    }

    QString ActivationAccount::GetPasswordString( utils::PassWordStipulate pwdStil )
    {
        QString tmp;
        QString msg("");
        tmp.clear();

        tmp.append(PWD_REQUIRE);
        if (pwdStil.minLength != 0)
        {
            QString cur;
            cur = cur.sprintf("%d", pwdStil.minLength);
            if (!pwdStil.digital &&!pwdStil.alp && !pwdStil.low_alp
                &&!pwdStil.up_alp &&!pwdStil.spec_alp)
            {
                tmp.append(cur + PWD_BIT);
            }
            else
            {
                tmp.append(cur + PWD_BITIN);
            }

            m_pswdStrategy.minLength = pwdStil.minLength;
        }

        //数字
        if (pwdStil.digital)
        {
            tmp.append(PWD_DITIGAL);
            m_pswdStrategy.digital = true;
        }
        else
        {
            m_pswdStrategy.digital = false;
        }

        //小写字母
        if (pwdStil.low_alp)
        {
            tmp.append(PWD_LOWER);
            m_pswdStrategy.low_alp = true;
        }
        else
        {
            m_pswdStrategy.low_alp = false;
        }

        //大写字母
        if (pwdStil.up_alp)
        {
            tmp.append(PWD_UPPER);
            m_pswdStrategy.up_alp = true;
        }
        else
        {
            m_pswdStrategy.up_alp = false;
        }

        //英文字母
        if (!pwdStil.low_alp && !pwdStil.up_alp &&pwdStil.alp)
        {
            tmp.append(PWD_CHARACTER);
            m_pswdStrategy.alp = true;
        }
        else
        {
            m_pswdStrategy.alp = false;
        }

        //特殊字符
        if (pwdStil.spec_alp)
        {
            tmp.append(PWD_SPECIAL_CHAR);
            m_pswdStrategy.spec_alp = true;
        }
        else
        {
            m_pswdStrategy.spec_alp = false;
        }

        msg = tmp.left(tmp.length() - 1);
        msg.append(PWD_NOTPURE_CHAR);

        return msg;
    }

    void ActivationAccount::onBtnOkClicked()
    {
        QString newPswd = m_newPassword->text();

        if (m_curPassword->text().isEmpty())
        {
            m_errTip->setTipText(transfer("当前密码不能为空"));
            m_errTip->ErrShow();
            return;
        }

        if (newPswd.isEmpty())
        {
            m_errTip->setTipText(transfer("新密码不能为空"));
            m_errTip->ErrShow();
            return;
        }

        if (m_cofPaaaword->text().isEmpty())
        {
             m_errTip->setTipText(transfer("请输入确认密码"));
             m_errTip->ErrShow();
             return;
        }

        if (m_cofPaaaword->text() != newPswd )
        {
            m_errTip->setTipText(transfer("两次输入的密码不一致，请重新输入"));
            m_errTip->ErrShow();
            return;
        }

        if ( (m_pswdStrategy.digital ? !newPswd.contains(QRegExp("[0-9]+")) : newPswd.contains(QRegExp("[0-9]+")))
            || (m_pswdStrategy.alp ? !newPswd.contains(QRegExp("[a-z]+|[A-Z]+")) : (!m_pswdStrategy.up_alp&&!m_pswdStrategy.low_alp&&newPswd.contains(QRegExp("[a-z]+|[A-Z]+"))))
            || (m_pswdStrategy.low_alp ? !newPswd.contains(QRegExp("[a-z]+")) : (!m_pswdStrategy.alp&&newPswd.contains(QRegExp("[a-z]+"))))
            || (m_pswdStrategy.up_alp ? !newPswd.contains(QRegExp("[A-Z]+")) : (!m_pswdStrategy.alp&&newPswd.contains(QRegExp("[A-Z]+"))))
            || (m_pswdStrategy.spec_alp ? !(newPswd.contains(QRegExp("[`~!@#$%^&*()\\{}|;\':\",./<>?[ ]+")) || newPswd.contains("]")) : (newPswd.contains(QRegExp("[`~!@#$%^&*()\\{}|;\':\",./<>?[ ]+")) || newPswd.contains("]"))))
        {
            //不符合密码策略规则
            m_errTip->setTipText(transfer("输入的密码不符合规则，请重新输入"));
            m_errTip->ErrShow();
            return;
        }

        if (m_authServer)
        {
            m_authServer->changePassword(m_curPassword->text().toStdString(),newPswd.toStdString(),CBind(&ActivationAccount::signalSerChangePasswordResult,this,std::placeholders::_1));
        }

    }

    void ActivationAccount::onSerChangePasswordResult( int result )
    {
        if (!result)
        {
            m_authServer->logout(CBind(&ActivationAccount::signalLoginOut,this,std::placeholders::_1));
            emit signalHasChanged(m_newPassword->text());
            this->close();
        }else{
            utils::Error::InitErrInfo(true);
            std::string strErr = utils::Error::GetErrMsg(result);
            m_errTip->setTipText(QString::fromLocal8Bit(strErr.data()));
        }
    }

    void ActivationAccount::onLoginOut(int err)
    {
        AddLog(LOG_LEV_INFO,LOG_FILE,"onLoginOut err = %d",err);
    }

}


