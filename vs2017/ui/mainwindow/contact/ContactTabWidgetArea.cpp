#include "ContactTabWidgetArea.h"
#include "../enterprise/EnterpriseWidget.h"
#include "group/GroupListWidget.h"
#include "friend/FriendListWidget.h"
#include <QPainter>
#include <QStyleOption>
#include "../../common/Common.h"
#include  "controls/PushButton.h"
namespace ui{
	ContactTabWidgetArea::ContactTabWidgetArea(QWidget *parent)
		: m_friendListWidget(CNull),m_groupListWidget(CNull)/*,m_enterpriseWidget(CNull)*/,QWidget(parent)
	{
		m_tabWidget = CMakePtr<QTabWidget>(this);
        m_mainLayout = CMakePtr<QVBoxLayout>(this);

	 	m_mainLayout->addWidget(m_tabWidget.get());
		m_mainLayout->setContentsMargins(0,0,0,0);
		m_tabWidget->setMovable(false);

		initFriendWidget();
		initGroupWidget();
		initEnterpriseWidget();
		setLayout(m_mainLayout.get());
	}

	ContactTabWidgetArea::~ContactTabWidgetArea()
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

	void ContactTabWidgetArea::initEnterpriseWidget()
	{
		m_enterpriseWidget = new EnterpriseWidget(this,CNull);
		connect(m_enterpriseWidget,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_enterpriseWidget,SIGNAL(showOrgUserInfor(data::OrgAndUserInfo)),this,SIGNAL(showOrgUserInfoPage(data::OrgAndUserInfo)));
		m_enterpriseWidget->setVisible(false);
		//m_tabWidget->addTab(m_enterpriseWidget,transfer("联络联系"));
	}

	void ContactTabWidgetArea::initGroupWidget()
	{
		m_groupListWidget = new GroupListWidget(this);
		connect(m_groupListWidget,SIGNAL(showGroupInforPage(int64)),this,SIGNAL(showGroupInforPage(int64)));
		connect(m_groupListWidget,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		m_tabWidget->addTab(m_groupListWidget,transfer("群"));
	}

	void ContactTabWidgetArea::paintEvent( QPaintEvent *event )
	{
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

	void ContactTabWidgetArea::initFriendWidget()
	{
		m_friendListWidget = new FriendListWidget(this);
		connect(m_friendListWidget,SIGNAL(showContactInfoPage(data::Contact)),this,SIGNAL(showContactInfoPage(data::Contact)));
		connect(m_friendListWidget,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		m_tabWidget->addTab(m_friendListWidget,transfer("好友"));
	}

}
