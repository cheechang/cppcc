#include "AuthMemListWidget.h"
#include "Controls/ElidedLabel.h"
#include "Controls/headimage.h"
#include "Controls/DefaultWidget.h"
#include "ChangePermissionWindow.h"
#include <qcheckbox.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qcoreapplication.h>
#include <qstackedwidget.h>
#include <qtimer.h>
#include <qscrollbar.h>
#include <QPushButton>
#include <log.h>
#include "Controls/MyMessageBox.h"
namespace ui {
	AuthMemListItem::AuthMemListItem(QString&head, QString&name, QWidget*parent) : QWidget(parent)
	,m_permission(NULL)
	{
		//LOG_METHOD("AuthMemListItem::AuthMemListItem", LOG_FILE);
		m_head = new HeadImage(this,QSize(40,40));
		m_name = new ElidedLabel(this);
		m_spliter = new QLabel(this);
		m_mainLayout = new QHBoxLayout();
		m_changePermission = new QPushButton(this);
		m_deleteMembers = new QPushButton(this);

		m_changePermission->setText(tr("更改权限"));
		m_changePermission->setObjectName("whiteButton");
		m_changePermission->setFixedSize(75, 25);
		m_deleteMembers->setText(tr("删除成员"));
		m_deleteMembers->setFixedSize(75, 25);
		m_deleteMembers->setObjectName("redButton");

		m_spliter->setScaledContents(true);
		m_spliter->setFixedHeight(1);
		m_spliter->setObjectName("spliter");

		m_head->setAvatarPath(head);
		m_name->setTextLimitExpand(name);
		m_name->setFixedSize(250, 30);
		m_mainLayout->setAlignment(Qt::AlignLeft);
		m_mainLayout->setContentsMargins(5, 0, 5, 0);
		m_mainLayout->addWidget(m_head);
		m_mainLayout->addWidget(m_name);
		m_mainLayout->addSpacing(10);
		m_mainLayout->addWidget(m_changePermission);
		m_mainLayout->addSpacing(10);
		m_mainLayout->addWidget(m_deleteMembers);

		m_contentLayout = new QVBoxLayout(this);
		m_contentLayout->setAlignment(Qt::AlignTop);
		m_contentLayout->setContentsMargins(0,0,0,0);
		m_contentLayout->addLayout(m_mainLayout);
		m_contentLayout->addWidget(m_spliter);
		m_contentLayout->addStretch();
		setLayout(m_contentLayout);
		m_cloud = CLOUDSERVICE;
		CONNECT_SERVICE(RolesResult(service::ErrorInfo, std::vector<model::CloudRoleInfo>&));
		connect(m_changePermission, SIGNAL(clicked()), this, SLOT(onChangePermissionClick()));
		connect(m_deleteMembers, SIGNAL(clicked()), this, SLOT(onDeleteMembersClick()));
	}
	AuthMemListItem::~AuthMemListItem(){
		//LOG_METHOD("AuthMemListItem::~AuthMemListItem", LOG_FILE);
		if (nullptr != m_mainLayout){
			m_mainLayout->deleteLater();
		}
		if (nullptr != m_contentLayout){
			m_contentLayout->deleteLater();
		}

	}
	void AuthMemListItem::setItemData(model::TeamMemberInfo&contact){
		//LOG_METHOD("AuthMemListItem::setItemData", LOG_FILE);
		m_contact = contact;
	}
	model::TeamMemberInfo AuthMemListItem::getItemData()const{
		//LOG_METHOD("AuthMemListItem::AuthMemListItem", LOG_FILE);
		return m_contact;
	}
	void AuthMemListItem::setUserData(model::EntpriseUserInfo&user){
		//LOG_METHOD("AuthMemListItem::setUserData", LOG_FILE);
		m_userdata = user;
	}
	model::EntpriseUserInfo AuthMemListItem::getUserData()const{
		//LOG_METHOD("AuthMemListItem::getUserData", LOG_FILE);
		return m_userdata;
	}
	void AuthMemListItem::onChangePermissionClick(){
		//LOG_METHOD("AuthMemListItem::onChangePermissionClick", LOG_FILE);
		m_cloud->getRoles(1, std::bind(&AuthMemListItem::signalSerRolesResult, this, std::placeholders::_1, std::placeholders::_2));
	}
	void AuthMemListItem::onDeleteMembersClick(){
		//LOG_METHOD("AuthMemListItem::onDeleteMembersClick", LOG_FILE);
		emit signalDeleteMems(m_contact);
	}
	void AuthMemListItem::onSerRolesResult(service::ErrorInfo err, std::vector<model::CloudRoleInfo>& info){
		//LOG_METHOD("AuthMemListItem::onSerRolesResult", LOG_FILE);
		if (!err){
			m_permission = std::make_shared<ChangePermissionWindow>(info);
			m_permission->setModal(true);
			m_permission->show();
			m_permission->activateWindow();
			m_permission->raise();
			connect(m_permission.get(), SIGNAL(signalChangePerm(int)), this, SLOT(onChangePerm(int)));
		}
	}
	void AuthMemListItem::onChangePerm(int type){
		//LOG_METHOD("AuthMemListItem::onChangePerm", LOG_FILE);
		if (m_contact.roleId == type){
			return;
		}
		m_contact.roleId = type;
		emit signalChangeMems(m_contact);
	}
	AuthMemList::AuthMemList(QListWidget *parent) :QListWidget(parent){
		//LOG_METHOD("AuthMemList::AuthMemList", LOG_FILE);
		setFocusPolicy(Qt::NoFocus);						 // 去除item选中时的虚线边框  
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭 
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		setSelectionMode(QAbstractItemView::ExtendedSelection);
		m_search = SEARCHSERVICE;
	}
	AuthMemList::~AuthMemList(){
		//LOG_METHOD("AuthMemList::~AuthMemLis", LOG_FILE);
	}
	void AuthMemList::addItem(QString title){
		//LOG_METHOD("AuthMemList::addItem", LOG_FILE);
		QListWidgetItem* item = NULL;
		item = new QListWidgetItem(this);
		item->setSizeHint(QSize(this->width(), 30));
		item->setBackgroundColor(QColor(245,245,245));
		item->setText(title);
		int row = 0;
		row = this->count();
		this->insertItem(row, item);
		//this->setItemWidget(item, itemWidget);	
	}
	void AuthMemList::addItem(model::TeamMemberInfo&contact){
		//LOG_METHOD("AuthMemList::addItem", LOG_FILE);
		QListWidgetItem* item = NULL;
		AuthMemListItem* itemWidget = NULL;
		QString headpath("");
		QString name("");
		QString rolename("");
		int64 roleId;
		int64 userid;
		int row = 0;
		userid = contact.userId;
		model::Contact contactinfo;
		m_search->getUserInfoSync(userid, contactinfo);
		headpath = QString::fromUtf8(contact.headImg.data());
		if (headpath.isEmpty()){
			headpath = QString::fromUtf8(contactinfo.thumbAvatar.value().data());
		}
		
		name = QString::fromUtf8(contactinfo.name.value().data());
		rolename = QString::fromUtf8(contact.roleName.data());
		roleId = contact.roleId;
		
		item = new QListWidgetItem(this);
		item->setSizeHint(QSize(this->width(),45));
		itemWidget = new AuthMemListItem(headpath, name);
		connect(itemWidget, SIGNAL(signalDeleteMems(model::TeamMemberInfo)), this, SIGNAL(signalDeleteMems(model::TeamMemberInfo)));
		connect(itemWidget, SIGNAL(signalChangeMems(model::TeamMemberInfo)), this, SIGNAL(signalChangeMems(model::TeamMemberInfo)));
		row = this->count();
		itemWidget->setItemData(contact);
		this->insertItem(row,item);
		this->setItemWidget(item, itemWidget);
	}
	AuthMemListWidget::AuthMemListWidget(model::CloudFileInfo&info, QWidget*parent) :TWidget(parent), m_contactList(nullptr), m_info(info), m_isChange(0){
		//LOG_METHOD("AuthMemListWidget::AuthMemListWidget", LOG_FILE);
		m_contactList = new AuthMemList((QListWidget*)this);
		m_loadingWidget = new DefaultWidget(this);
		m_defaultAuthmem = new DefaultWidget(QString(":/img/noauthormember"),this);
		m_stackWidget = new QStackedWidget(this);
		m_mainLayout = new QVBoxLayout(this);

		m_stackWidget->addWidget(m_loadingWidget);
		m_stackWidget->addWidget(m_contactList);
		m_stackWidget->addWidget(m_defaultAuthmem);

		m_mainLayout->addWidget(m_stackWidget);
		this->setLayout(m_mainLayout);
		m_stackWidget->setCurrentIndex(0);
		connect(m_contactList, SIGNAL(signalChangeMems(model::TeamMemberInfo)), this, SLOT(onChangeMems(model::TeamMemberInfo)));
		connect(m_contactList, SIGNAL(signalDeleteMems(model::TeamMemberInfo)), this, SLOT(onDeleteMems(model::TeamMemberInfo)));
		CONNECT_SERVICE(TeamMembers(service::ErrorInfo, std::vector<model::TeamMemberInfo>&));
		CONNECT_SERVICE(RolesResult(service::ErrorInfo, std::vector<model::CloudRoleInfo>&));
		CONNECT_SERVICE(ResetMember(service::ErrorInfo));
		m_cloud = CLOUDSERVICE;
		m_cloud->getRoles(1, std::bind(&AuthMemListWidget::signalSerRolesResult, this, std::placeholders::_1, std::placeholders::_2));
		m_user = USERSERVICE;
		m_user->getAccountInfo(m_account);
	}
	AuthMemListWidget::~AuthMemListWidget(){
		//LOG_METHOD("AuthMemListWidget::~AuthMemListWidget", LOG_FILE);
	}
	void AuthMemListWidget::loadData(){
		//LOG_METHOD("AuthMemListWidget::loadData", LOG_FILE);
		m_cloud = CLOUDSERVICE;
		m_memberlist.clear();
		m_cloud->teamMembers(m_info.fileId, std::bind(&AuthMemListWidget::signalSerTeamMembers, this, std::placeholders::_1, std::placeholders::_2));
	}
	void AuthMemListWidget::onSerRolesResult(service::ErrorInfo err, std::vector<model::CloudRoleInfo>& info){
		//LOG_METHOD("AuthMemListWidget::onSerRolesResult", LOG_FILE);
		if (!err){
			m_roles = info;
		}
		QTimer::singleShot(0, this, SLOT(loadData()));
	}
	void AuthMemListWidget::onSerTeamMembers(service::ErrorInfo err, std::vector<model::TeamMemberInfo>& Memberinfo){
		//LOG_METHOD("AuthMemListWidget::onSerTeamMembers", LOG_FILE);
		Log(LOG_LEV_DEBUG,LOG_FILE,"err=%d", err);
		if (!err){
			if (1 == Memberinfo.size() && Memberinfo.at(0).userId == m_account.id.value()){
				m_stackWidget->setCurrentIndex(2);
				m_isChange++;
				m_memberlist.push_back(m_account.id.value());
			}
			else{
				m_members = Memberinfo;
				updateData();
				m_stackWidget->setCurrentIndex(1);
			}
		}
		else{
			showTipMessageBox(err);
		}
	}
	bool sortFunc(model::TeamMemberInfo& item1, model::TeamMemberInfo& item2)
	{
		int number1 = item1.userId;
		int number2 = item2.userId;
		return (number1 - number2)>0;
	}
	bool sortFuncs(model::TeamMemberInfo& item1, model::TeamMemberInfo& item2)
	{
		int number1 = item1.userId;
		int number2 = item2.userId;
		return (number1 - number2)==0;
	}
	bool sortFun(model::TeamMemberInfo& item1, model::TeamMemberInfo& item2)
	{
		int number1 = item1.roleId;
		int number2 = item2.roleId;
		return (number1 - number2)< 0;
	}
	void AuthMemListWidget::onAuthMembers(std::vector<model::TeamMemberInfo>& members){
		//LOG_METHOD("AuthMemListWidget::onAuthMembers", LOG_FILE);
		if (members.size()){		
			std::vector<model::TeamMemberInfo> exchange;
			exchange.insert(exchange.end(), members.begin(), members.end());
			exchange.insert(exchange.end(), m_members.begin(), m_members.end());
				
			std::vector<model::TeamMemberInfo>::iterator vector_iterator;
			std::sort(exchange.begin(), exchange.end(), sortFunc);
			vector_iterator = std::unique(exchange.begin(), exchange.end(), sortFuncs);
			if (vector_iterator != exchange.end()){
				exchange.erase(vector_iterator, exchange.end());
			}
			m_members = exchange;					
			std::vector<model::TeamMemberInfo>::iterator iter;
			for (iter = m_members.begin(); iter != m_members.end(); iter++)
			{
				if (iter->roleId == 0 || iter->fileId == 0){
					iter->roleId = 2;
					iter->fileId = m_info.fileId;
				}			
			}
			updateData();
			m_stackWidget->setCurrentIndex(1);
		}
	}
	void AuthMemListWidget::onDeleteMems(model::TeamMemberInfo memberinfo){
		//LOG_METHOD("AuthMemListWidget::onDeleteMems", LOG_FILE);
		std::vector<model::TeamMemberInfo>::iterator iter;
		for (iter = m_members.begin(); iter != m_members.end(); iter++)
		{
			if (memberinfo.userId == iter->userId){
				m_members.erase(iter);
				break;
			}	
		}
		QVector<qint64>::iterator iterat;
		for (iterat = m_memberlist.begin(); iterat != m_memberlist.end(); iterat++){
			if (memberinfo.userId == *iterat){
				m_memberlist.erase(iterat);
				break;
			}
		}
		updateData();
	}
	void AuthMemListWidget::onChangeMems(model::TeamMemberInfo memberinfo){
		//LOG_METHOD("AuthMemListWidget::onChangeMems", LOG_FILE);
		std::vector<model::TeamMemberInfo>::iterator iter;
		for (iter = m_members.begin(); iter != m_members.end(); iter++)
		{
			if (memberinfo.userId == iter->userId){
				iter->roleId = memberinfo.roleId;
				break;
			}
		}
		updateData();
	}
	void AuthMemListWidget::updateData(){
		//LOG_METHOD("AuthMemListWidget::updateData", LOG_FILE);
		m_contactList->clear();
		m_group.clear();
		m_isChange++;
		std::sort(m_members.begin(), m_members.end(), sortFun);
		std::vector<model::TeamMemberInfo>::iterator iter;
		for (iter = m_members.begin(); iter != m_members.end(); iter++)
		{
			m_memberlist.push_back(iter->userId);
			if (iter->userId == m_account.id.value()){
				continue;
			}
			if (m_group.contains(iter->roleId)){
				m_group[iter->roleId].push_back(*iter);
			}
			else{
				std::vector<model::TeamMemberInfo> members;
				members.push_back(*iter);
				m_group.insert(iter->roleId, members);
			}
			QCoreApplication::processEvents();
		}
		for (int index = 0; index < m_roles.size(); ++index){
			if (m_group.contains(m_roles[index].roleId) && m_group[m_roles[index].roleId].size()>0){
				m_contactList->addItem(QString::fromUtf8(m_roles[index].name.c_str()));
				for (int j = 0; j < m_group[m_roles[index].roleId].size(); ++j){
					m_contactList->addItem(m_group[m_roles[index].roleId].at(j));
					QCoreApplication::processEvents();
				}
			}
			QCoreApplication::processEvents();
		}
	}
	QVector<qint64> AuthMemListWidget::getMemberList(){
		//LOG_METHOD("AuthMemListWidget::getMemberList", LOG_FILE);
		return m_memberlist;
	}
	void AuthMemListWidget::onConfirm(){
		//LOG_METHOD("AuthMemListWidget::onConfirm", LOG_FILE);
		Log(LOG_LEV_INFO,LOG_FILE,"m_isChange = %d", m_isChange);
		if (m_isChange > 1){
			m_cloud->teamResetMember(m_members, std::bind(&AuthMemListWidget::signalSerResetMember, this, std::placeholders::_1));
		}
		emit signalClose();
	}
	void AuthMemListWidget::onSerResetMember(service::ErrorInfo err){
		//LOG_METHOD("AuthMemListWidget::onSerResetMember", LOG_FILE);;
		Log(LOG_LEV_DEBUG, LOG_FILE,"err=%d", err);
		if (!err){
			emit signalClose();
		}
		else{
			showTipMessageBox(err);
		}
	}
	void AuthMemListWidget::showTipMessageBox(int code){
		if (9 == code){
			QString tipinfo(tr("当前文件夹已被删除!"));
			showWarning(nullptr, tr("提示"), tipinfo);
			emit signalClose();
		}
	}
}