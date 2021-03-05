#include "DecryptSetPassChatDialog.h"
#include "controls/PushButton.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../../../common/Common.h"
namespace ui{
	DecryptSetPassChatDialog::DecryptSetPassChatDialog(QWidget *parent):BaseWindow(parent)
	{
		this->setFixedSize(350,210);
		__super::setTitle(transfer("设置密聊密码"));
		connect(this,SIGNAL(closeClicked()),this,SLOT(close()));
		Init();
	}

	void DecryptSetPassChatDialog::Init()
	{
		SetPasswordLayout = CMakePtr<QHBoxLayout>();
		m_PasswordEdit = CMakePtr<QLineEdit>();
		m_PlainOrcipher = CMakePtr<PushButton>();
		m_WarningMsg = CMakePtr<QLabel>();
		m_AckBtn = CMakePtr<QPushButton>();
		m_CancelBtn = CMakePtr<QPushButton>();
		m_btnlayout = CMakePtr<QHBoxLayout>();
		m_Warninglayout = CMakePtr<QHBoxLayout>();
		m_Reslayout = CMakePtr<QVBoxLayout>();
		
		m_AckBtn->setObjectName("sendbtn");
		m_CancelBtn->setObjectName("sendbtn");
		m_AckBtn->setMinimumSize(80,25);
		m_CancelBtn->setMinimumSize(80,25);
		m_PasswordEdit->setPlaceholderText(transfer("请输入密码..."));
		m_PasswordEdit->setEchoMode(QLineEdit::Password);
		m_PasswordEdit->setFixedSize(252, 35);
		m_PlainOrcipher->setPicName(QString(":/chat/showPassword"));
		m_PlainOrcipher->setFixedSize(27,18);
		SetPasswordLayout->addWidget(m_PasswordEdit.get());
		SetPasswordLayout->addWidget(m_PlainOrcipher.get());
		SetPasswordLayout->setSpacing(0);
		SetPasswordLayout->setContentsMargins(40,30,40,0);

		m_WarningMsg->setText(transfer("提示：密码不少于6位"));
		m_WarningMsg->setEnabled(false);
		m_WarningMsg->setStyleSheet("color:red");
		m_Warninglayout->addWidget(m_WarningMsg.get());
		m_Warninglayout->setContentsMargins(10,0,0,5);

		m_AckBtn->setText(QString(transfer("确认")));
		m_CancelBtn->setText(QString(transfer("取消")));
		m_btnlayout->addWidget(m_AckBtn.get());
		m_btnlayout->addWidget(m_CancelBtn.get());
		m_btnlayout->setContentsMargins(80,30,90,10);
		m_btnlayout->setSpacing(40);

		mMainLayout->addLayout(SetPasswordLayout.get());
		mMainLayout->addLayout(m_btnlayout.get());
		mMainLayout->addLayout(m_Warninglayout.get());
		mMainLayout->addStretch();

		connect(m_PlainOrcipher.get(),SIGNAL(clicked()),this, SLOT(onPlainOrcipher()));
		connect(m_AckBtn.get(),SIGNAL(clicked()),this, SLOT(onAckBtnClicked()));
		connect(m_CancelBtn.get(),SIGNAL(clicked()),this, SLOT(onCancelBtnClicked()));
	}

	DecryptSetPassChatDialog::~DecryptSetPassChatDialog()
	{
	
	}

	void DecryptSetPassChatDialog::onPlainOrcipher()
	{
		if(QLineEdit::Password == m_PasswordEdit->echoMode())
		{
			m_PlainOrcipher->setCheckable(true,true);
			m_PasswordEdit->setEchoMode(QLineEdit::Normal);
		}
		else
		{
			m_PlainOrcipher->setCheckable(true,false);
			m_PasswordEdit->setEchoMode(QLineEdit::Password);
		}
	}

	void DecryptSetPassChatDialog::onAckBtnClicked()
	{
		QString Tpassword = m_PasswordEdit->text();
		emit signalSetDecryptKey(Tpassword);
		accept();
	}

	void DecryptSetPassChatDialog::onCancelBtnClicked()
	{
		accept();
	}
}
