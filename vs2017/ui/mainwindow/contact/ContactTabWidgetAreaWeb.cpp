#include "ContactTabWidgetAreaWeb.h"
#include "../enterprise/EnterpriseWidget.h"
#include "group/GroupListWidget.h"
#include "friend/FriendListWidgetWeb.h"
#include <QPainter>
#include <QStyleOption>
#include "../../common/Common.h"
#include  "controls/PushButton.h"
namespace ui{
	ContactTabWidgetAreaWeb::ContactTabWidgetAreaWeb(QWidget *parent)
		: m_friendListWidget(CNull),m_groupListWidget(CNull)/*,m_enterpriseWidget(CNull)*/,QWidget(parent)
	{
		////m_tabWidget = CMakePtr<QTabWidget>(this);
        m_mainLayout = CMakePtr<QVBoxLayout>(this);

		////m_mainLayout->addWidget(m_tabWidget.get());
		////m_mainLayout->setContentsMargins(0,0,0,0);
		////m_tabWidget->setMovable(false);
		///QWidget *min_button = new QWidget(this);
		////min_button->setFixedHeight(48);

		PushButton *min_button = new PushButton(this);
		min_button->setWindowTitle("Test");
		min_button->setFixedHeight(48);
		m_mainLayout->addWidget(min_button);
		min_button->setContentsMargins(0, 0, 1, 0);
		////m_mainLayout->addWidget(min_button);

		m_friendListWidget = new FriendListWidgetWeb(this);
		m_mainLayout->addWidget(m_friendListWidget);
		m_mainLayout->setContentsMargins(0, 0, 0, 0);


	 
		//connect(m_friendListWidget, SIGNAL(showContactInfoPage(data::Contact)), this, SIGNAL(showContactInfoPage(data::Contact)));
		///connect(m_friendListWidget, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_friendListWidget, SIGNAL(showContactInfoPage(data::Contact)), this, SIGNAL(showContactInfoPage(data::Contact)));
		/////connect(m_friendListWidget, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));


		///initFriendWidget();
		///initGroupWidget();
		////initEnterpriseWidget();
		setLayout(m_mainLayout.get());
		////m_tabWidget->setVisible(false);
	}

	ContactTabWidgetAreaWeb::~ContactTabWidgetAreaWeb()
	{
		if(m_groupListWidget != CNull){
			delete m_groupListWidget;
		}
		if(m_enterpriseWidget != CNull){
			delete m_enterpriseWidget;
		}
		if(m_friendListWidget != CNull){
			delete m_friendListWidget;
		}
	}

	void ContactTabWidgetAreaWeb::initEnterpriseWidget()
	{
		m_enterpriseWidget = new EnterpriseWidget(this,CNull);
		connect(m_enterpriseWidget,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_enterpriseWidget,SIGNAL(showOrgUserInfor(data::OrgAndUserInfo)),this,SIGNAL(showOrgUserInfoPage(data::OrgAndUserInfo)));
		m_tabWidget->addTab(m_enterpriseWidget,transfer("(组织架构)"));
	}

	void ContactTabWidgetAreaWeb::initGroupWidget()
	{
		m_groupListWidget = new GroupListWidget(this);
		connect(m_groupListWidget,SIGNAL(showGroupInforPage(int64)),this,SIGNAL(showGroupInforPage(int64)));
		connect(m_groupListWidget,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		m_tabWidget->addTab(m_groupListWidget,transfer("(群)"));
	}

	void ContactTabWidgetAreaWeb::paintEvent(QPaintEvent *event)
	{
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

	void ContactTabWidgetAreaWeb::initFriendWidget()
	{
		m_friendListWidget = new FriendListWidgetWeb(this);
		connect(m_friendListWidget,SIGNAL(showContactInfoPage(data::Contact)),this,SIGNAL(showContactInfoPage(data::Contact)));
		connect(m_friendListWidget,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		m_tabWidget->addTab(m_friendListWidget,transfer("(好友)"));

	}

}
