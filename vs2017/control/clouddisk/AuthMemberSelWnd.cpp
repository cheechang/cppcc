#include "AuthMemberSelWnd.h"
#include "Controls/TitleBar.h"
#include "ContactListWidget.h"
#include "OrgListWidget.h"
#include <QIcon>
#include <QTabWidget>
#include <qlayout.h>
#include <QPainter>
#include <qpushbutton.h>
#include <log.h>
namespace ui{
	AuthMemberSelWnd::AuthMemberSelWnd(QVector<qint64>&memberlist, QWidget*parent) :QDialog(parent),
		m_titleBar(nullptr),
		m_tabWidget(nullptr),
		m_mainLayout(nullptr),
		m_contactList(nullptr)
	{
		//LOG_METHOD("AuthMemberSelWnd::AuthMemberSelWnd", LOG_FILE);
		setWindowFlags(Qt::FramelessWindowHint);
		setFixedSize(400, 500);

		m_titleBar = std::make_shared<TitleBar>(this,true,false,true);
		installEventFilter(m_titleBar.get());

		setWindowTitle(tr("添加授权成员"));
		setWindowIcon(QIcon(":/img/logo"));


		m_contactList = std::make_shared<ContactListWidget>(memberlist,this);
		m_orgList = std::make_shared<OrgListWidget>(memberlist,this);
		m_tabWidget = std::make_shared<QTabWidget>(this);

		m_tabWidget->addTab(m_contactList.get(), tr("联系人"));
		m_tabWidget->addTab(m_orgList.get(), tr("组织架构"));
		m_tabWidget->setCurrentIndex(0);

		m_contentLayout = new QVBoxLayout();
		m_contentLayout->setAlignment(Qt::AlignTop);
		m_contentLayout->setSpacing(0);
		m_contentLayout->setContentsMargins(0,15, 0, 0);
		m_contentLayout->addWidget(m_tabWidget.get());

		m_okBtn = std::make_shared<QPushButton>(this);
		m_cancelBtn = std::make_shared<QPushButton>(this);
		m_btnLayout = new QHBoxLayout();

		m_okBtn->setObjectName("blueButton");
		m_cancelBtn->setObjectName("grayButton");

		m_okBtn->setText(tr("确定"));
		m_cancelBtn->setText(tr("取消"));

		m_okBtn->setFixedSize(65, 25);
		m_cancelBtn->setFixedSize(65, 25);

		m_btnLayout->setAlignment(Qt::AlignRight);
		m_btnLayout->setContentsMargins(0, 10, 10, 10);
		m_btnLayout->setSpacing(10);
		m_btnLayout->addWidget(m_okBtn.get());
		m_btnLayout->addWidget(m_cancelBtn.get());

		m_mainLayout = new QVBoxLayout(this);
		m_mainLayout->setAlignment(Qt::AlignTop);
		m_mainLayout->setSpacing(0);
		m_mainLayout->setContentsMargins(0, 0, 0, 0);
		m_mainLayout->addWidget(m_titleBar.get());
		m_mainLayout->addLayout(m_contentLayout);
		m_mainLayout->addLayout(m_btnLayout);
		setLayout(m_mainLayout);

		connect(m_okBtn.get(),SIGNAL(clicked()),this,SLOT(onOkBtnClicked()));
		connect(m_cancelBtn.get(), SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
		connect(m_contactList.get(), SIGNAL(signalChecked(qint32, qint64, bool)), this, SLOT(onChecked(qint32, qint64, bool)));
		connect(m_orgList.get(), SIGNAL(signalChecked(qint32, qint64, bool)), this, SLOT(onChecked(qint32, qint64, bool)));
	}
	AuthMemberSelWnd::~AuthMemberSelWnd(){
		//LOG_METHOD("AuthMemberSelWnd::~AuthMemberSelWnd", LOG_FILE);
		if (nullptr != m_contentLayout){
			m_contentLayout->deleteLater();
		}
		if (nullptr != m_btnLayout){
			m_btnLayout->deleteLater();
		}
	}
	void AuthMemberSelWnd::onOkBtnClicked(){
		//LOG_METHOD("AuthMemberSelWnd::onOkBtnClicked", LOG_FILE);
		QVector<model::EntpriseUserInfo>members;
		QVector<model::Contact>contacts;
		std::vector<model::TeamMemberInfo> authmembers;
		m_contactList->getSelectedMember(contacts);
		m_orgList->getSelectedMember(members);
		for (int j = 0; j < contacts.size(); ++j){
			model::TeamMemberInfo info;
			info.userId = contacts.at(j).id.value();
			info.userName = contacts.at(j).name.value();
			info.headImg = contacts.at(j).thumbAvatar.value();
			authmembers.push_back(info);
		}
		for (int k = 0; k < members.size(); ++k){
			model::TeamMemberInfo info;
			info.userId = members.at(k).userID;
			info.userName = members.at(k).enName;
			info.headImg = members.at(k).userHead;
			authmembers.push_back(info);
		}
		if (authmembers.size()>0){
			emit signalAuthMembers(authmembers);
		}
		this->close();
	}
	void AuthMemberSelWnd::onCancelBtnClicked(){
		//LOG_METHOD("AuthMemberSelWnd::onCancelBtnClicked", LOG_FILE);
		this->close();
	}
	void AuthMemberSelWnd::paintEvent(QPaintEvent *event)
	{
		//LOG_METHOD("AuthMemberSelWnd::paintEvent", LOG_FILE);
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		p.setBrush(QBrush(Qt::white));
		p.setPen(Qt::gray);  //边框色
		p.drawRect(QRect(0, 0, this->width(), this->height()));
		QDialog::paintEvent(event);
	}
	void AuthMemberSelWnd::onChecked(qint32 type, qint64 id, bool ischecked){
		if (1 == type){
			m_orgList->updateItemState(id,ischecked);
		}
		else{
			m_contactList->updateItemState(id, ischecked);
		}
	}
}