#include "LockoutAccount.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QPixmap>

#include "TipWidget.h"
#include "../utils/Error.h"
#include "../common/Common.h"
 namespace ui
 {
	 LockoutAccount::LockoutAccount(std::string account)
	 {
		 m_authcontrol = AUTHCONTROL;
		 m_strAccount = account;

		 this->setFixedSize(QSize(290,220));
		 this->setTitle(QString::fromLocal8Bit("验证"));
		 InitWidgets();
		 connect(this,SIGNAL(signalSerGetVerifyCode(int,const std::string)),this,SLOT(onSerGetVerifyCode(int,const std::string)));
		 connect(this,SIGNAL(signalDoLockoutResult(int,const std::string)),this,SLOT(onSerLockoutResult(int,const std::string)));
		 if (m_authcontrol)
		 {
			 m_authcontrol->verifyImgCode(account,"",CBind(&LockoutAccount::signalSerGetVerifyCode,this,std::placeholders::_1,std::placeholders::_2));
		 }
		 this->show();
		 this->raise();
	 }


	 LockoutAccount::~LockoutAccount(void)
	 {
	 }

	 void LockoutAccount::InitWidgets()
	 {
		 m_labTitleMsg = CMakePtr<QLabel>(this);
		 m_editCodeInput = CMakePtr<QLineEdit>(this);
		 m_labCodeImage = CMakePtr<QLabel>(this);
		 m_btnNextImage = CMakePtr<QPushButton>(this);
		 m_btnOk = CMakePtr<QPushButton>(this);
		 m_mainLayout = CMakePtr<QVBoxLayout>();
		 m_errTip	  = CMakePtr<TipWidget>(this);

		 QHBoxLayout* hBox = new QHBoxLayout();

		 //m_labCodeImage->setText(QString::fromLocal8Bit(""));
		 m_labCodeImage->setFixedSize(110,35);
		 m_editCodeInput->setFixedSize(130,32);
		 m_editCodeInput->setMaxLength(4);

		 hBox->setSpacing(0);
		 hBox->addStretch();
		
		 hBox->addWidget(m_editCodeInput.get());
		 hBox->addWidget(m_labCodeImage.get());
		 hBox->addStretch();

		 m_btnNextImage->setObjectName("blueButton");
		 m_btnNextImage->setFixedSize(QSize(100,20));
		 m_btnNextImage->setText(QString::fromLocal8Bit("看不清,换一个"));
		 connect(m_btnNextImage.get(),SIGNAL(clicked()),this,SLOT(onSerGetNextImage()));
		 m_labTitleMsg->setFixedSize(160,38);
		 QPalette pa;
		 pa.setColor(QPalette::WindowText,QColor(50,150,225));
		 m_labTitleMsg->setPalette(pa);

		 m_labTitleMsg->setText(QString::fromLocal8Bit("你的账号登录次数过多！  为了账号安全亲输入验证码"));
		 m_labTitleMsg->setWordWrap(true);
		 m_labTitleMsg->setAlignment(Qt::AlignTop);

		 m_btnOk->setFixedSize(240,32);
		 m_btnOk->setObjectName("sendbtn");
		 m_btnOk->setText(QString::fromLocal8Bit("确定"));
		 m_btnOk->setFocus();
		 connect(m_btnOk.get(),SIGNAL(clicked()),this,SLOT(onBtnLockOutClicekd()));

		 m_errTip->setVisible(false);
		 m_errTip->setTipText(transfer("测试错误信息"));
		 m_errTip->setTipSize(QSize(230,30));
		 m_errTip->move(28,132);

		 m_mainLayout->setSpacing(5);
		 m_mainLayout->addSpacing(2);
		 m_mainLayout->addWidget(m_labTitleMsg.get());
		 m_mainLayout->addSpacing(15);
		 m_mainLayout->addLayout(hBox,0);
		 m_mainLayout->addWidget(m_btnNextImage.get(),0,Qt::AlignRight);
		 m_mainLayout->addWidget(m_btnOk.get(),0,Qt::AlignCenter);
		 m_mainLayout->addSpacing(20);
		 m_mainLayout->setContentsMargins(10,10,10,0);
		 mMainLayout->addLayout(m_mainLayout.get());
		 

	 }

	 void LockoutAccount::onSerGetNextImage()
	 {
		 if (m_authcontrol)
		 {
			 m_authcontrol->verifyImgCode(m_strAccount,"",CBind(&LockoutAccount::signalSerGetVerifyCode,this,std::placeholders::_1,std::placeholders::_2));
		 }
	 }


	 void LockoutAccount::onSerGetVerifyCode( int err, const std::string codeUrl )
	 {
		  if (err == 0)
		  {
			  m_labCodeImage->setPixmap(QPixmap(codeUrl.data()));
		  }
	 }

	 void LockoutAccount::DoVerifyCode( std::string account )
	 {

	 }

	 void LockoutAccount::onBtnLockOutClicekd()
	 {
		 std::string code = m_editCodeInput->text().toUtf8().data();
		 if (m_authcontrol)
		 {
			 m_authcontrol->verifyImgCode(m_strAccount,code,CBind(&LockoutAccount::signalDoLockoutResult,this,std::placeholders::_1,std::placeholders::_2));
		 }
	 }

	 void LockoutAccount::onSerLockoutResult( int err, const std::string codeUrl )
	 {
		if (err == 0)
		{
			emit signalLockout();
		}else
		{
			utils::Error::InitErrInfo(true);
			std::string strErr = utils::Error::GetErrMsg(err);
			m_errTip->setTipText(QString::fromStdString(strErr));
			m_errTip->setVisible(true);
			m_errTip->ErrShow();
		}
	 }
 }

