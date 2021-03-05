#include "AuthMemberListWnd.h"
#include "Controls/PushButton.h"
#include "Controls/DefaultWidget.h"
#include "Controls/TitleBar.h"
#include <QStackedWidget>
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include "AuthMemListWidget.h"
#include <log.h>
namespace ui{
	AuthMemberListWnd::AuthMemberListWnd(model::CloudFileInfo&info, QWidget*parent) :QDialog(parent),
	m_authMemList(nullptr),
	m_mainlayout(nullptr),
	m_addMember(nullptr),
	m_ok(nullptr),
	m_buttonlayout(nullptr),
	m_titleBar(nullptr),
	m_cancelBtn(nullptr)
	
	{
		//LOG_METHOD("AuthMemberListWnd::AuthMemberListWnd",LOG_FILE);
		setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowStaysOnTopHint*/);
		resize(400, 500);	

		m_titleBar = new TitleBar(this, true, false, true);
		installEventFilter(m_titleBar);

		setWindowTitle(tr("授权成员列表"));
		setWindowIcon(QIcon(":/img/logo"));

		m_authMemList = new AuthMemListWidget(info,this);
		m_mainlayout = new QVBoxLayout(this);
		m_addMember=new PushButton(this);
		m_ok=new QPushButton(this);

		m_ok->setObjectName("blueButton");
		m_cancelBtn=new QPushButton(this);
		m_cancelBtn->setObjectName("grayButton");
		m_title=new QLabel(this);
		m_buttonlayout = new QHBoxLayout(this);
		m_authMemList->setFixedSize(400,400);
		m_addMember->setFixedSize(100,50);
		m_addMember->setToolTip(tr("添加授权成员"));
		m_addMember->setPicName(QString(":/img/addauhor"));
		m_addMember->setObjectName("addMembutton");
		m_ok->setFixedSize(65, 25);
		m_ok->setText(tr("确定"));
		m_cancelBtn->setText(tr("取消"));
		m_cancelBtn->setFixedSize(65, 25);
		
		m_buttonlayout->setContentsMargins(10, 10, 10, 10);
		m_buttonlayout->setSpacing(10);
		m_buttonlayout->addStretch();
		m_buttonlayout->addWidget(m_ok);
		m_buttonlayout->addSpacing(10);
		m_buttonlayout->addWidget(m_cancelBtn);
		
		m_btnAddLayout = new QHBoxLayout(this);
		m_btnAddLayout->setAlignment(Qt::AlignRight);
		m_btnAddLayout->setContentsMargins(5, 5, 10, 5);
		m_btnAddLayout->addStretch();
		m_btnAddLayout->addWidget(m_addMember);

		m_mainlayout->setSpacing(0);
		m_mainlayout->setContentsMargins(0, 0, 0, 5);
		m_mainlayout->setAlignment(Qt::AlignTop);
		m_mainlayout->addWidget(m_titleBar);
		m_mainlayout->addLayout(m_btnAddLayout);
		m_mainlayout->addWidget(m_authMemList);
		m_mainlayout->addLayout(m_buttonlayout);
		m_mainlayout->addStretch();
		setLayout(m_mainlayout);

		connect(m_ok, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
		connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
		connect(m_addMember, SIGNAL(clicked()), this, SLOT(onAddMemClicked()));
		connect(this, SIGNAL(signalAuthMembers(std::vector<model::TeamMemberInfo>&)), m_authMemList, SLOT(onAuthMembers(std::vector<model::TeamMemberInfo>&)));
		connect(this, SIGNAL(signalConfirm()), m_authMemList, SLOT(onConfirm()));
		connect(m_authMemList, SIGNAL(signalClose()), this, SLOT(onClose()));
	}

	AuthMemberListWnd::~AuthMemberListWnd(){
		//LOG_METHOD("AuthMemberListWnd::~AuthMemberListWnd", LOG_FILE);
	}
	QVector<qint64> AuthMemberListWnd::getMemberList(){
		//LOG_METHOD("AuthMemberListWnd::getMemberList", LOG_FILE);
		return m_authMemList->getMemberList();
	}
	void AuthMemberListWnd::onCancelBtnClicked(){
		//LOG_METHOD("AuthMemberListWnd::onCancelBtnClicked", LOG_FILE);
		this->close();
	}
	void AuthMemberListWnd::onOkBtnClicked(){
		//LOG_METHOD("AuthMemberListWnd::onOkBtnClicked", LOG_FILE);
		emit signalConfirm();
	}
	void AuthMemberListWnd::onAddMemClicked(){
		//LOG_METHOD("AuthMemberListWnd::onAddMemClicked", LOG_FILE);
		emit signalAddMember();
	}
	void AuthMemberListWnd::onClose(){
		//LOG_METHOD("AuthMemberListWnd::onClose", LOG_FILE);
		this->close();
	}
	void AuthMemberListWnd::paintEvent(QPaintEvent *event)
	{
		//LOG_METHOD("AuthMemberListWnd::paintEvent", LOG_FILE);
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		p.setBrush(QBrush(Qt::white));
		p.setPen(Qt::gray);  //边框色
		p.drawRect(QRect(0, 0, this->width(), this->height()));
		QDialog::paintEvent(event);
	}
}