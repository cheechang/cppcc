#include "RegisterWindow.h"
#include <QRegExpValidator>
#include <QHBoxLayout> 
#include "TipWidget.h"
#include <data/AuthData.h>
#include <QTimer>
#include <utils/Error.h>
#include "log.h"
#include <QPixmap>
#include <qsize.h>
#include "../common/Common.h"
const char * filename = 0;
int line = 0;

namespace ui{
	const int TIME = 1000;
	const int PIXSIZE_WIDTH = 25;
	const int PIXSIZE_HEIGTH = 25;
	const int LINEEDIT_HEIGTH = 30;
	RegisterWindow::RegisterWindow(void):
		m_editServer(nullptr),
		m_labServer(nullptr),
		m_editUserName(nullptr),
		m_labUserName(nullptr),
		m_editPassword(nullptr),
		m_labPassword(nullptr),
		m_editConfirm(nullptr),
		m_labConfirm(nullptr),

		m_btnGetCode(nullptr),
		m_btnSingUp(nullptr),
		m_editPhone(nullptr),
		m_labPhone(nullptr),
		m_formLayout(nullptr),
		m_btnCancel(nullptr),
		m_MainLayoutWidget(nullptr),
		m_loginResultTip(nullptr),
		m_editVerifyCode(nullptr),
		m_comContryArea(nullptr),
		m_getCodeLayout(nullptr),
		m_qTimer(nullptr),
		m_time(60)
	{
		m_authcontrol = AUTHCONTROL;
		this->setTitle(QString::fromLocal8Bit("注册"));
		this->setFixedSize(QSize(260,370));
		initUI();
		this->show();
	}

	void RegisterWindow::initUI()
	{
		m_loginResultTip = new TipWidget(this);
		m_loginResultTip->setVisible(false);
		m_loginResultTip->setTipText(transfer("测试错误信息"));
		m_loginResultTip->setTipSize(QSize(210,28));
        m_loginResultTip->setTime(3);
		m_loginResultTip->move(20,26);

		m_MainLayoutWidget = new QWidget(this);

		m_labServer = new QLabel(this);
		m_labServer->setFixedSize(PIXSIZE_WIDTH,PIXSIZE_HEIGTH);
		m_labServer->setScaledContents(true);
		m_labServer->setPixmap(QPixmap(":/login/reg_server"));

		m_editServer = new QLineEdit(this);
		m_editServer->setFixedHeight(LINEEDIT_HEIGTH);
		m_editServer->setPlaceholderText(QString::fromLocal8Bit("服务器"));

		m_labPhone = new QLabel(this);
		m_labPhone->setFixedSize(PIXSIZE_WIDTH,PIXSIZE_HEIGTH);
		m_labPhone->setScaledContents(true);
		m_labPhone->setPixmap(QPixmap(":/login/reg_phone"));

		m_editPhone = new QLineEdit(this);
		m_editPhone->setFixedSize(120,LINEEDIT_HEIGTH);
		//m_editPhone->setFixedHeight(LINEEDIT_HEIGTH);
		m_editPhone->setPlaceholderText(QString::fromLocal8Bit("请输入手机号码"));

		m_labPassword = new QLabel(this);
		m_labPassword->setFixedSize(PIXSIZE_WIDTH,PIXSIZE_HEIGTH);
		m_labPassword->setScaledContents(true);
		m_labPassword->setPixmap(QPixmap(":/login/reg_password"));

		m_editPassword = new QLineEdit(this);
		m_editPassword->setFixedHeight(LINEEDIT_HEIGTH);
		m_editPassword->setPlaceholderText(QString::fromLocal8Bit("请输入密码"));
		m_editPassword->setContextMenuPolicy(Qt::NoContextMenu);
		m_editPassword->setEchoMode(QLineEdit::Password);
		m_editConfirm = new QLineEdit(this);


		m_labConfirm = new QLabel(this);
		m_labConfirm->setFixedSize(PIXSIZE_WIDTH,PIXSIZE_HEIGTH);
		m_labConfirm->setScaledContents(true);
		m_labConfirm->setPixmap(QPixmap(":/login/reg_password"));

		m_editConfirm->setFixedHeight(LINEEDIT_HEIGTH);
		m_editConfirm->setPlaceholderText(QString::fromLocal8Bit("请再次输入密码"));
		m_editConfirm->setContextMenuPolicy(Qt::NoContextMenu);
		m_editConfirm->setEchoMode(QLineEdit::Password);

		m_labUserName  = new QLabel(this);
		m_labUserName->setFixedSize(PIXSIZE_WIDTH,PIXSIZE_HEIGTH);
		m_labUserName->setScaledContents(true);
		m_labUserName->setPixmap(QPixmap(":/login/reg_contact"));

		m_editUserName = new QLineEdit(this);
		m_editUserName->setFixedHeight(LINEEDIT_HEIGTH);
		m_editUserName->setPlaceholderText(QString::fromLocal8Bit("请输入用户名"));

		m_comContryArea = new QComboBox(this);
		m_comContryArea->setFixedSize(QSize(60,LINEEDIT_HEIGTH));
		m_comContryArea->addItem(transfer("中  国"));

		m_getCodeLayout = new QHBoxLayout(this);
		m_editVerifyCode = new QLineEdit(this);
		m_editVerifyCode->setFixedSize(QSize(214,LINEEDIT_HEIGTH));
		m_btnGetCode = new QPushButton(this);
		QFont font;
		font.setPixelSize(14);
		m_btnGetCode->setFont(font);
		m_btnGetCode->setText(transfer("获取验证码"));
		m_btnGetCode->setFixedSize(QSize(74,LINEEDIT_HEIGTH));
		m_btnGetCode->move(this->width() - 100, this->y() + 258);
		m_btnGetCode->setObjectName("InnerLineEdit");
		connect(m_btnGetCode,SIGNAL(clicked()),this, SLOT(onGetVerifyCodeClicked()));
		connect(this, SIGNAL(signalGetVerifyCode(int,int)),this,SLOT(onGetVerifyCode(int,int)));

		m_btnSingUp =new QPushButton(this);
		m_btnSingUp->setText(transfer("注册"));
		m_btnSingUp->setFixedSize(QSize(200,30));
		m_btnSingUp->setObjectName("sendbtn");

		connect(m_btnSingUp, SIGNAL(clicked()), this, SLOT(onBtnSingUPClicked()));
		connect(this, SIGNAL(signalRegisterResult(int,int)),this,SLOT(onRegisterResult(int,int)));
		m_btnCancel = new QPushButton(this);
		m_btnCancel->setText(transfer("返回"));
		connect(m_btnCancel, SIGNAL(clicked()), this, SIGNAL(closeClicked()));
		m_btnCancel->setFixedSize(QSize(35,25));
		m_btnCancel->setObjectName("blueButton");

		m_formLayout = new QFormLayout();
		m_editPhone->setPlaceholderText(transfer("手机号"));
		m_editPhone->setMaxLength(11);
		m_editPhone->setContextMenuPolicy(Qt::NoContextMenu);
		QRegExp regx("[0-9]+$");
		QValidator *validator = new QRegExpValidator(regx, m_editPhone);
		m_editPhone->setValidator(validator);

		m_formLayout->setContentsMargins(15,5,5,5);
		m_formLayout->addRow(m_labServer,m_editServer);
		QHBoxLayout* com = new QHBoxLayout();
		com->setSpacing(0);
		com->addWidget(m_comContryArea);
		com->addWidget(m_editPhone);

		m_formLayout->addRow(m_labPhone,com);

		m_formLayout->addRow(m_labPassword,m_editPassword);
		m_formLayout->addRow(m_labConfirm,m_editConfirm);
		m_formLayout->addRow(m_labUserName,m_editUserName);

		m_formLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
		m_formLayout->setLabelAlignment(Qt::AlignCenter);
		
		m_formLayout->setSpacing(10);
		m_formLayout->setMargin(10);

		m_MainLayoutWidget->setLayout(m_formLayout);
		mMainLayout->addSpacing(8);
		mMainLayout->addWidget(m_MainLayoutWidget,0, Qt::AlignLeft);
		mMainLayout->addWidget(m_editVerifyCode,1,Qt::AlignHCenter);
		mMainLayout->addSpacing(10);
		mMainLayout->addWidget(m_btnSingUp,2,Qt::AlignHCenter);
		mMainLayout->addWidget(m_btnCancel,3,Qt::AlignHCenter);
		
		mMainLayout->addStretch();

	}

	bool RegisterWindow::validityChecking()
	{
		if(m_editServer->text().isEmpty())
		{
			m_loginResultTip->setVisible(true);
			m_loginResultTip->setTipText(transfer("请输入服务器地址"));
			return false;
		}

		if(m_editPhone->text().isEmpty())
		{
			m_loginResultTip->setVisible(true);
			m_loginResultTip->setTipText(transfer("请输入手机号"));
			return false;
		}

		if(m_editUserName->text().isEmpty())
		{
			m_loginResultTip->setVisible(true);
			m_loginResultTip->setTipText(transfer("请输入用户名"));
			return false;
		}
		if(m_editPassword->text().isEmpty())
		{
			m_loginResultTip->setVisible(true);
			m_loginResultTip->setTipText(transfer("请输入密码"));
			return false;
		}

		if(m_editConfirm->text().isEmpty())
		{
			m_loginResultTip->setVisible(true);
			m_loginResultTip->setTipText(transfer("请确认密码"));
			return false;
		}

		if(m_editPassword->text() != m_editConfirm->text())
		{
			m_loginResultTip->setVisible(true);
			m_loginResultTip->setTipText(transfer("两次密码不一致，请确认输入密码"));
			return false;
		}
		return true;
	}

	void RegisterWindow::onBtnSingUPClicked()
	{
        BEGIN;
		if(validityChecking())
		{
			if(m_editVerifyCode->text().isEmpty())
			{
				m_loginResultTip->setVisible(true);
				m_loginResultTip->setTipText(transfer("请输入验证码"));
				return ;
			}
			 std::string code = std::string(m_editVerifyCode->text().toUtf8().data());
			 std::string user = std::string(m_editUserName->text().toUtf8().data());
			 std::string pwd  = std::string(m_editPassword->text().toUtf8().data());

			m_authcontrol->signup(code,user,pwd,CBind(&RegisterWindow::signalRegisterResult,this,CPlaceholders _1,CPlaceholders _2));
            END;
		}		
	}

	void RegisterWindow::onGetVerifyCodeClicked()
	{
        BEGIN;
		if(validityChecking())
		{
			m_qTimer = new QTimer(this);
			connect(m_qTimer,SIGNAL(timeout()), this, SLOT(onTimerOut()));
			
			m_btnGetCode->setEnabled(false);

			std::string account = "0086" + m_editPhone->text().toStdString();
			m_authcontrol->getRegCode(m_editServer->text().toStdString(),account,std::bind(&RegisterWindow::signalGetVerifyCode,this,std::placeholders::_1,std::placeholders::_2));
            END;
		}	
	}

	void RegisterWindow::onGetVerifyCode(int code,int time)
	{	
		AddLog(LOG_LEV_INFO, "onGetVerifyCode errCode =%d", code);
		if (code == 0)
		{
			m_qTimer->start(TIME);
			m_time =  time;
		}else{
            utils::Error::InitErrInfo(true);
            std::string err = utils::Error::GetErrMsg(code);
            m_loginResultTip->setTipText(QString::fromStdString(err));
            m_loginResultTip->ErrShow();
            m_btnGetCode->setEnabled(true);
        }
	}
	void RegisterWindow::onRegisterResult(int coode,int code)
	{
        AddLog(LOG_LEV_INFO, "onRegisterResult errCode =%d", coode);
		m_btnSingUp->setEnabled(true);
		if(coode == 0)
		{
			std::string ser = m_editServer->text().toLocal8Bit().data();
			std::string user =  m_editPhone->text().toLocal8Bit().data();
			//std::string user = "0086" + tmp;
			std::string pwd = m_editPassword->text().toLocal8Bit().data();
			emit signalSignResult(ser,user,pwd);
		}else
		{											    
			m_loginResultTip->setVisible(true);
			utils::Error::InitErrInfo(true);
			std::string err = utils::Error::GetErrMsg(coode);
			m_loginResultTip->setTipText(QString::fromStdString(err));
		}
	}

	RegisterWindow::~RegisterWindow(void)
	{
		if(m_editServer != nullptr)
		{
			delete m_editServer;
			m_editServer = nullptr;
		}
		if(m_editPhone != nullptr)
		{
			delete m_editPhone;
			m_editPhone = nullptr;
		}

		if(m_editUserName != nullptr)
		{
			delete m_editUserName;
			m_editUserName = nullptr;
		}
		if(nullptr != m_editPassword)
		{
			delete m_editPassword;
			m_editPassword = nullptr;
		}
		if(nullptr != m_editConfirm)
		{
			delete m_editConfirm;
			m_editConfirm = nullptr;
		}
		if(nullptr != m_editVerifyCode)
		{
			delete m_editVerifyCode;
			m_editVerifyCode = nullptr;
		}

		if(nullptr != m_comContryArea)
		{
			delete m_comContryArea;
			m_comContryArea = nullptr;
		}
			
		if( nullptr != m_btnGetCode)
		{
			delete m_btnGetCode;
			m_btnGetCode = nullptr;
		}

		if( nullptr != m_btnSingUp)
		{
			delete m_btnSingUp;
			m_btnSingUp = nullptr;
		}

		if( nullptr != m_btnCancel)
		{
			delete m_btnCancel;
			m_btnCancel = nullptr;
		}

		if( nullptr != m_loginResultTip)
		{
			delete m_loginResultTip;
			m_loginResultTip = nullptr;
		}
		
		if( nullptr != m_formLayout)
		{
			delete m_formLayout;
			m_formLayout = nullptr;
		}

		if(nullptr != m_MainLayoutWidget)
		{
			delete m_MainLayoutWidget;
			m_MainLayoutWidget = nullptr;
		}
	}

	void RegisterWindow::onTimerOut()
	{
		m_time--;
		QString showTime = QString::fromLocal8Bit("剩余") +QString::number(m_time) + QString::fromLocal8Bit("  秒");
		if(m_time == 0)
		{
			m_time = 60;
			showTime = QString::fromLocal8Bit("获取验证码");
			m_qTimer->stop();
			delete m_qTimer;
			m_qTimer = nullptr;

			m_btnGetCode->setEnabled(true);
		}

		m_btnGetCode->setText(showTime);
	}

}