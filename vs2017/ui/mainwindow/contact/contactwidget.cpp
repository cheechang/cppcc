#include "contactwidget.h"
#include "common/controlptr.h"
#include "../enterprise/EnterpriseWidget.h"
#include "../controls/DefaultWidget.h"
#include "../enterprise/enterpriseinfowidget.h"
#include "ContactTabWidgetArea.h"
#include "group/GroupInforWidget.h"
#include "friend/FriendInfoWidget.h"
#include "friend/AppInfoWidget.h"
#include "friend/EnterpriseAccountList.h"
#include "friend/AppAccountList.h"
#include "searchcontact/SearchContactWindow.h"
#include "createGroup/CreateGroupWindow.h"
#include <QHBoxLayout>
#include <QSize>
#include <QResizeEvent>
#include "common/Common.h"
namespace ui{
	ContactWidget::ContactWidget(QWidget *parent)
		: QWidget(parent)
	{
		
		m_mainLayout = CMakePtr<QHBoxLayout>(this);
		//this->setObjectName("BgWidget");
		//this->setStyleSheet("QWidget#BgWidget{background:#e5e7ec;}");

		m_leftTabWidgetArea = CMakePtr<ContactTabWidgetArea>(this);
		m_leftTabWidgetArea->setMinimumWidth(LeftContentWidth);
		m_leftTabWidgetArea->setMaximumWidth(LeftContentWidth);
		m_leftTabWidgetArea->setObjectName("bg_fa");
		m_defaultWidget = CMakePtr<ui::DefaultWidget>(this);
		m_defaultWidget->setMinimumWidth(RightContentWidth);

		m_enterpriseInfoWidget = CMakePtr<EnterpriseInfoWidget>(this);
		m_enterpriseInfoWidget->setMinimumWidth(RightContentWidth);
		m_enterpriseInfoWidget->setVisible(false);
		m_enterpriseInfoWidget->setObjectName("enterpriseInfoWidget");

		m_groupInforWidget = CMakePtr<GroupInforWidget>(this);
		m_groupInforWidget->setMinimumWidth(RightContentWidth);
		m_groupInforWidget->setVisible(false);
		m_groupInforWidget->setObjectName("enterpriseInfoWidget");

		m_contactInfoWidget = CMakePtr<FriendInfoWidget>(this);
		m_contactInfoWidget->setMinimumWidth(RightContentWidth);
		m_contactInfoWidget->setVisible(false);
		//m_contactInfoWidget->setObjectName("enterpriseInfoWidget");

		m_appInfoWidget = CMakePtr<AppInfoWidget>(this);
		m_appInfoWidget->setMinimumWidth(RightContentWidth);
		m_appInfoWidget->setVisible(false);
		m_appInfoWidget->setObjectName("enterpriseInfoWidget");

		m_enterpriseAccountList = CMakePtr<EnterpriseAccountList>(this);
		m_enterpriseAccountList->setMinimumWidth(RightContentWidth);
		m_enterpriseAccountList->setVisible(false);

		m_appAccountList = CMakePtr<AppAccountList>(this);
		m_appAccountList->setMinimumWidth(RightContentWidth);
		m_appAccountList->setVisible(false);

	///	QVBoxLayout *left_layout = new QVBoxLayout();
		m_mainLayout->addWidget(m_leftTabWidgetArea.get());

	///	QHBoxLayout *right_layout = new QHBoxLayout();
		m_mainLayout->addWidget(m_defaultWidget.get());
		m_mainLayout->addWidget(m_enterpriseInfoWidget.get());
		m_mainLayout->addWidget(m_groupInforWidget.get());
		m_mainLayout->addWidget(m_contactInfoWidget.get());
		m_mainLayout->addWidget(m_appInfoWidget.get());
		m_mainLayout->addWidget(m_enterpriseAccountList.get());
		m_mainLayout->addWidget(m_appAccountList.get());



		m_mainLayout->setSpacing(0);
		m_mainLayout->setContentsMargins(0,0,0,0);

		this->setLayout(m_mainLayout.get());
		//this->setStyleSheet("QWidget{background:red;}");
		m_btnAddContact = CMakePtr<ToolButton>(":/group/addGroup",this,false);
		m_btnAddContact->move(160,450);
		m_btnAddContact->setVisible(false);
		m_menuMain = CMakePtr<QMenu>(m_btnAddContact.get());
		m_actionAddGroupOrFriend = CMakePtr<QAction>(transfer("加好友/加群"),this);
		m_actionCreateGroup = CMakePtr<QAction>(transfer("创建群"),this);
		m_menuMain->addAction(m_actionCreateGroup.get());
		m_menuMain->addAction(m_actionAddGroupOrFriend.get());
	
		mWinCreateGroup = new CreateGroupWindow(this);
		mWinCreateGroup->setFixedSize(320,550);
		mWinCreateGroup->hide();
		mWinCreateGroup->setTitle(transfer("创建群"));
		connect(mWinCreateGroup,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(mWinCreateGroup,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),mWinCreateGroup,SLOT(close()));

		connect(m_actionAddGroupOrFriend.get(),SIGNAL(triggered(bool)),this,SLOT(onBtnAddFrindOrGroup()));
		connect(m_actionCreateGroup.get(),SIGNAL(triggered(bool)),this,SLOT(onBtnCreateGroup()));
		connect(m_btnAddContact.get(),SIGNAL(clicked(bool)),this,SLOT(onBtnAddClicked()));
		connect(m_leftTabWidgetArea.get(),SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_leftTabWidgetArea.get(),SIGNAL(showContactInfoPage(data::Contact)),this,SLOT(onShowContactInfoPage(data::Contact)));
		connect(m_leftTabWidgetArea.get(),SIGNAL(showGroupInforPage(int64)),this,SLOT(onShowGroupInforPage(int64)));
		connect(m_leftTabWidgetArea.get(),SIGNAL(showOrgUserInfoPage(data::OrgAndUserInfo)),this,SLOT(onShowOrgUserInfoPage(data::OrgAndUserInfo)));
		connect(m_enterpriseInfoWidget.get(),SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_groupInforWidget.get(),SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_groupInforWidget.get(),SIGNAL(signalSerDelUiFile(int64,int64)), this, SIGNAL(signalSerDelUiFile(int64,int64)));
		connect(m_contactInfoWidget.get(),SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_appInfoWidget.get(),SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_enterpriseAccountList.get(),SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_appAccountList.get(),SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));

	}

	ContactWidget::~ContactWidget()
	{

	}

	void ContactWidget::onShowOrgUserInfoPage( data::OrgAndUserInfo user )
	{
		m_contactInfoWidget->setVisible(false);
		m_defaultWidget->setVisible(false);
		m_enterpriseInfoWidget->setVisible(true);
		m_groupInforWidget->setVisible(false);
		m_appInfoWidget->setVisible(false);
		m_enterpriseAccountList->setVisible(false);
		m_appAccountList->setVisible(false);
		m_enterpriseInfoWidget->updateData(user);
	}
	void ContactWidget::onShowUserInfo(int64 uid)
	{

	}
	void ContactWidget::onShowGroupInforPage( int64 groupId )
	{
		if(groupId == 0){
			m_defaultWidget->setVisible(true);
			m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(false);
			m_contactInfoWidget->setVisible(false);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(false);
			m_appAccountList->setVisible(false);
		}else{
			m_defaultWidget->setVisible(false);
			m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(true);
			m_groupInforWidget->updateData(groupId);
			m_contactInfoWidget->setVisible(false);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(false);
			m_appAccountList->setVisible(false);
		}
	}

	void ContactWidget::resizeEvent( QResizeEvent *e )
	{
	//	m_btnAddContact->move(m_leftTabWidgetArea->size().width()- m_btnAddContact->width()-20,
	//			m_leftTabWidgetArea->size().height()- m_btnAddContact->height()-20);

		QWidget::resizeEvent(e);
	}

	void ContactWidget::onBtnAddClicked()
	{
		QPoint pos(m_btnAddContact->x()-m_menuMain->width(),m_btnAddContact->y());
		pos = mapToGlobal(pos);
		m_menuMain->exec(pos);
	}

	void ContactWidget::onBtnCreateGroup()
	{
		mWinCreateGroup->showWin();
	}

	void ContactWidget::onBtnAddFrindOrGroup()
	{
		m_searchContactWin = CMakePtr<SearchContactWindow>();
		m_searchContactWin->show();
	}

	void ContactWidget::onShowContactInfoPage( data::Contact contact)
	{
		if(contact.id.value() == 0){
			m_defaultWidget->setVisible(true);
			m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(false);
			m_contactInfoWidget->setVisible(false);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(false);
			m_appAccountList->setVisible(false);
		}
		else if(contact.id.value() == ENTERPRISE_ACCOUNT_ID){
			m_defaultWidget->setVisible(false);
			m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(false);
			m_contactInfoWidget->setVisible(false);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(true);
			m_appAccountList->setVisible(false);
		}
		else if(contact.id.value() == APP_ACCOUNT_ID){
			m_defaultWidget->setVisible(false);
			m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(false);
			m_contactInfoWidget->setVisible(false);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(false);
			m_appAccountList->setVisible(true);
		}
		else if (contact.mydevice.value() == MYDEVICE_SIGN)
		{
			m_defaultWidget->setVisible(true);
			m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(false);
			m_contactInfoWidget->setVisible(false);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(false);
			m_appAccountList->setVisible(false);
		}else{
			if(contact.isApp.value() == 1){
				m_defaultWidget->setVisible(false);
				m_enterpriseInfoWidget->setVisible(false);
				m_groupInforWidget->setVisible(false);
				m_contactInfoWidget->setVisible(false);
				m_appInfoWidget->setVisible(true);
				m_enterpriseAccountList->setVisible(false);
				m_appAccountList->setVisible(false);
				m_appInfoWidget->updateData(contact.id.value());
			}
			else{
				m_defaultWidget->setVisible(false);
				m_enterpriseInfoWidget->setVisible(false);
				m_groupInforWidget->setVisible(false);
				m_contactInfoWidget->setVisible(true);
				m_appInfoWidget->setVisible(false);
				m_enterpriseAccountList->setVisible(false);
				m_appAccountList->setVisible(false);
				m_contactInfoWidget->updateData(contact);
			}
		}
	}

	void ContactWidget::onShowAddContactOrCreateGroup( int type )
	{
		if (type == 1)
		{
			onBtnAddFrindOrGroup();
		}else{
			onBtnCreateGroup();
		}
	}

}