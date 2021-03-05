#include "PasswordReset.h"
#include "log.h"
#include <common/ChineseInfos.hpp>
#include <QMessageBox>
#include "common/Common.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include "ContactBlacklistWin.h"

namespace ui{
    PasswordReset::PasswordReset(QWidget* parent): TWidget(parent)
    {
        m_authServer = AUTHCONTROL;
        setObjectName("groupinfobackground");
        InitWidgets();
        connect(this,SIGNAL(signalSerGetPasswordRule(int,int)),this,SLOT(onSerGetPasswordRule(int,int)));
        connect(this,SIGNAL(signalSerChangePasswordResult(int)),this,SLOT(onSerChangePasswordResult(int)));
        if (m_authServer)
        {
            m_authServer->getPasswordRule(CBind(&PasswordReset::signalSerGetPasswordRule,this,std::placeholders::_1,std::placeholders::_2));
        }

    }


    PasswordReset::~PasswordReset(void)
    {
    }

    void PasswordReset::InitWidgets()
    {
        m_labShowMsg      = CMakePtr<QLabel>(this);
        m_editOldPassword = CMakePtr<QLineEdit>(this);
        m_editNewPassword = CMakePtr<QLineEdit>(this);
        m_editConfirmWord = CMakePtr<QLineEdit>(this);
        m_labPasswordRule = CMakePtr<QLabel>(this);

        m_btnRestWord = CMakePtr<QPushButton>(this);
        m_btnCancel = CMakePtr<QPushButton>(this);
        m_btnBlacklist = CMakePtr<QPushButton>(this);

        m_passLayout = CMakePtr<QFormLayout>();
        m_mainLayout = CMakePtr<QVBoxLayout>(this);

        m_editOldPassword->setFixedSize(180,28);
        m_editOldPassword->setObjectName("HotKey");
        m_editOldPassword->setMaxLength(32);
        m_editOldPassword->setContextMenuPolicy(Qt::NoContextMenu);
        m_editOldPassword->setEchoMode(QLineEdit::Password);
        m_editOldPassword->setPlaceholderText(transfer("�����뵱ǰ����"));
        m_passLayout->addRow(transfer("��ǰ����: "),m_editOldPassword.get());

        m_editNewPassword->setFixedSize(180,28);
        m_editNewPassword->setObjectName("HotKey");
        m_editNewPassword->setMaxLength(32);
        m_editNewPassword->setContextMenuPolicy(Qt::NoContextMenu);
        m_editNewPassword->setEchoMode(QLineEdit::Password);
        m_editNewPassword->setPlaceholderText(transfer("������������"));
        m_passLayout->addRow(transfer("�����룺"),m_editNewPassword.get());

        m_editConfirmWord->setFixedSize(180,28);
        m_editConfirmWord->setObjectName("HotKey");
        m_editConfirmWord->setMaxLength(32);
        m_editConfirmWord->setContextMenuPolicy(Qt::NoContextMenu);
        m_editConfirmWord->setEchoMode(QLineEdit::Password);
        m_editConfirmWord->setPlaceholderText(transfer("��ȷ��������"));
        m_passLayout->addRow(transfer("ȷ������:"),m_editConfirmWord.get());

        m_labShowMsg->setText(QString::fromLocal8Bit("���룺Ϊ�������˺Ű�ȫ���붨���޸�����"));
        m_labShowMsg->setMinimumWidth(240);
        m_labShowMsg->setAlignment(Qt::AlignRight);

        m_btnRestWord->setText(QString::fromLocal8Bit("ȷ ��"));
        m_btnRestWord->setObjectName("sendbtn");
        m_btnRestWord->setFixedSize(QSize(68,26));
        connect(m_btnRestWord.get(), SIGNAL(clicked()),this,SLOT(onBtnOkClicked()));
        connect(m_btnCancel.get(),SIGNAL(clicked()),this,SIGNAL(signalCloseWin()));

        m_btnCancel->setText(QString::fromLocal8Bit("ȡ ��"));
        m_btnCancel->setVisible(false);
        m_btnCancel->setObjectName("sendbtn");
        m_btnCancel->setFixedSize(QSize(80,26));

        m_btnBlacklist->setText(QString::fromLocal8Bit("ͨѶ¼������"));
        m_btnBlacklist->setFixedSize(QSize(180,28));
        connect(m_btnBlacklist.get(),SIGNAL(clicked()),this,SLOT(onBtnBlackListClicked()));

        m_mainLayout->setSpacing(10);
        m_mainLayout->addWidget(m_labShowMsg.get(),0,Qt::AlignHCenter);
        QWidget* widget = new QWidget(this);
        widget->setLayout(m_passLayout.get());
        m_mainLayout->addWidget(widget,0,Qt::AlignHCenter);
        m_mainLayout->addWidget(m_labPasswordRule.get(),0,Qt::AlignHCenter);
        m_mainLayout->addWidget(m_labPasswordRule.get(), 0, Qt::AlignHCenter);

        m_mainLayout->addWidget(m_btnRestWord.get(),0,Qt::AlignHCenter);
        m_mainLayout->addSpacing(15);
        m_mainLayout->addWidget(m_btnBlacklist.get(),0,Qt::AlignCenter);
        m_mainLayout->setContentsMargins(20,20,20,20);
        m_mainLayout->addStretch();
        this->setLayout(m_mainLayout.get());
    }

    void PasswordReset::onSerGetPasswordRule( int err, int rule )
    {
        utils::PassWordStipulate result= utils::AnalysisPwdRule(rule);
        if (!err)
        {
            QString rul = GetPasswordString(result);
            m_labPasswordRule->setText(rul);
        }
    }

    QString PasswordReset::GetPasswordString( utils::PassWordStipulate pwdStil )
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

        //����
        if (pwdStil.digital)
        {
            tmp.append(PWD_DITIGAL);
            m_pswdStrategy.digital = true;
        }
        else
        {
            m_pswdStrategy.digital = false;
        }

        //Сд��ĸ
        if (pwdStil.low_alp)
        {
            tmp.append(PWD_LOWER);
            m_pswdStrategy.low_alp = true;
        }
        else
        {
            m_pswdStrategy.low_alp = false;
        }

        //��д��ĸ
        if (pwdStil.up_alp)
        {
            tmp.append(PWD_UPPER);
            m_pswdStrategy.up_alp = true;
        }
        else
        {
            m_pswdStrategy.up_alp = false;
        }

        //Ӣ����ĸ
        if (!pwdStil.low_alp && !pwdStil.up_alp &&pwdStil.alp)
        {
            tmp.append(PWD_CHARACTER);
            m_pswdStrategy.alp = true;
        }
        else
        {
            m_pswdStrategy.alp = false;
        }

        //�����ַ�
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

    void PasswordReset::onBtnOkClicked()
    {
        QString newPswd = m_editNewPassword->text();
        QString oldPswd = m_editOldPassword->text();

        if (oldPswd.isEmpty())
        {
            QMessageBox box(QMessageBox::Critical,APP_NAME,"��ǰ���벻��Ϊ��");
            box.exec();
            return;
        }

        if (newPswd.isEmpty())
        {
            QMessageBox box(QMessageBox::Critical,APP_NAME,"�����벻��Ϊ��");
            box.exec();
            return;
        }

        if (m_editConfirmWord->text().isEmpty())
        {
            QMessageBox box(QMessageBox::Critical,APP_NAME,"������ȷ������");
            box.exec();
            return;
        }

        if (m_editConfirmWord->text() != newPswd)
        {
            QMessageBox box(QMessageBox::Critical,APP_NAME,"������������벻һ�£�����������");
            box.exec();
            return;
        }

        if ( (m_pswdStrategy.digital ? !newPswd.contains(QRegExp("[0-9]+")) : newPswd.contains(QRegExp("[0-9]+")))
            || (m_pswdStrategy.alp ? !newPswd.contains(QRegExp("[a-z]+|[A-Z]+")) : (!m_pswdStrategy.up_alp&&!m_pswdStrategy.low_alp&&newPswd.contains(QRegExp("[a-z]+|[A-Z]+"))))
            || (m_pswdStrategy.low_alp ? !newPswd.contains(QRegExp("[a-z]+")) : (!m_pswdStrategy.alp&&newPswd.contains(QRegExp("[a-z]+"))))
            || (m_pswdStrategy.up_alp ? !newPswd.contains(QRegExp("[A-Z]+")) : (!m_pswdStrategy.alp&&newPswd.contains(QRegExp("[A-Z]+"))))
            || (m_pswdStrategy.spec_alp ? !(newPswd.contains(QRegExp("[`~!@#$%^&*()\\{}|;\':\",./<>?[ ]+")) || newPswd.contains("]")) : (newPswd.contains(QRegExp("[`~!@#$%^&*()\\{}|;\':\",./<>?[ ]+")) || newPswd.contains("]"))))
        {
            //������������Թ���
            QMessageBox box(QMessageBox::Critical,APP_NAME,"��������벻���Ϲ�������������");
            box.exec();
            return;
        }

        if (m_authServer)
        {
            m_authServer->changePassword(oldPswd.toStdString(),newPswd.toStdString(),CBind(&PasswordReset::signalSerChangePasswordResult,this,std::placeholders::_1));
        }
    }

    void PasswordReset::onSerChangePasswordResult( int err )
    {
        if (err)
        {
            //�޸Ĳ��ɹ�
            QString errMsg = QString::fromLocal8Bit(utils::Error::GetErrMsg(err).c_str());
            QMessageBox msgBox;
            if (errMsg.isEmpty())
            {
                QMessageBox box(QMessageBox::Critical,APP_NAME,"�޸�����ʧ��");
                box.exec();
            }else{
                QMessageBox box(QMessageBox::Critical,APP_NAME,errMsg);
                box.exec();
            }
             return;
        }
        else
        {
            emit signalCloseWin();
        }
    }

    void PasswordReset::onBtnBlackListClicked()
    {
        m_BlacklistWin.reset(new ContactBlacklistWin(this));
        m_BlacklistWin->setMinimumSize(260,380);
        m_BlacklistWin->show();
    }

}
