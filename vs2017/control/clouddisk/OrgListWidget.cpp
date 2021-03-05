#include "OrgListWidget.h"
#include "controls/NoFocusDelegate.h"
#include "ContactListWidget.h"
#include "Controls/ElidedLabel.h"
#include "Controls/headimage.h"
#include "Controls/DefaultWidget.h"
#include <qcheckbox.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qcoreapplication.h>
#include <qstackedwidget.h>
#include <qtimer.h>
#include <qmovie.h>
#include <log.h>
namespace ui {
	QrgTreeItem::QrgTreeItem(QTreeWidget *view, int type) :QTreeWidgetItem(view, type), m_ismember(false){

	}
	QrgTreeItem::QrgTreeItem(QTreeWidgetItem *parent, int type) : QTreeWidgetItem(parent, type),m_ismember(false){

	}
	QrgTreeItem::~QrgTreeItem(){

	}
	void QrgTreeItem::setItemData(model::OrganizationInfo&org){
		m_data = org;
	}
	model::OrganizationInfo QrgTreeItem::getItemData() const{
		return m_data;
	}
	void QrgTreeItem::setItemIsMember(bool ismember){
		m_ismember = ismember;
	}
	bool QrgTreeItem::ItemIsMember()const{
		return m_ismember;
	}
	OrgTreeList::OrgTreeList(QWidget*parent):QTreeWidget(parent){
		//LOG_METHOD("OrgTreeList::OrgTreeList", LOG_FILE);
		this->setColumnCount(1); //设置列数 
		this->setHeaderLabel(tr("组织成员")); //设置头的标题  
		this->setHeaderHidden(true);//隐藏表头
		setItemDelegate(new NoFocusDelegate());

		QPalette p(this->palette());//设置背景色  
		p.setColor(QPalette::Base, QColor(Qt::white));
		this->setPalette(p);
		connect(this, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(onItemPressed(QTreeWidgetItem *, int)));
		connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem *, int)));
	}
	OrgTreeList::~OrgTreeList(){
	}
	void OrgTreeList::getSelectedMember(QVector<model::EntpriseUserInfo>&members){
		//LOG_METHOD("OrgTreeList::OrgTreeList", LOG_FILE);
		ContactListItem* contactWidget = nullptr;
		for (int j = 0; j < m_memberlist.size(); ++j){
			contactWidget = (ContactListItem*)this->itemWidget(m_memberlist.at(j), 0);
			if (nullptr == contactWidget)continue;
			QCheckBox* checkbtn = contactWidget->findChild<QCheckBox*>("checkbtn");
			if (nullptr == checkbtn) continue;
			if (!checkbtn->isChecked())continue;
			bool ischeckable = contactWidget->isCheckable();
			if (ischeckable){
				model::EntpriseUserInfo data = contactWidget->getUserData();
				members.push_back(data);
			}
		}
	}
	int	OrgTreeList::getMemberSize(){
		return m_memberlist.size();
	}
	bool OrgTreeList::setMemberState(qint64 id, bool ischecked){
		bool isfind = false;
		ContactListItem* contactWidget = nullptr;
		for (int j = 0; j < m_memberlist.size(); ++j){
			contactWidget = (ContactListItem*)this->itemWidget(m_memberlist.at(j), 0);
			if (nullptr == contactWidget)continue;
			if (contactWidget->getUserData().userID == id){
				QCheckBox* checkbtn = contactWidget->findChild<QCheckBox*>("checkbtn");
				checkbtn->setChecked(ischecked);
				if (ischecked && !contactWidget->isEnabled()){
					contactWidget->setEnabled(true);
				}
				isfind = true;
				break;
			}
		}
		return isfind;
	}
	void OrgTreeList::onItemPressed(QTreeWidgetItem *item, int column){
		//LOG_METHOD("OrgTreeList::onItemPressed", LOG_FILE);
		QWidget* contactWidget = nullptr;
		if (nullptr == item)return;
		contactWidget = this->itemWidget(item,column);
		if (nullptr == contactWidget)return;
		QCheckBox* checkbtn = contactWidget->findChild<QCheckBox*>("checkbtn");
		if (nullptr == checkbtn) return;
		bool ischeckable = ((ContactListItem*)contactWidget)->isCheckable();
		if (ischeckable){
			checkbtn->setChecked(!checkbtn->isChecked());
		}
	}
	void OrgTreeList::onItemDoubleClicked(QTreeWidgetItem *item, int column){
		//LOG_METHOD("OrgTreeList::onItemDoubleClicked", LOG_FILE);
		if (nullptr == item) return;
		QrgTreeItem* orgItem = dynamic_cast<QrgTreeItem*>(item);
		if (nullptr == orgItem) return;
		int count = orgItem->childCount();
		if (!count && !orgItem->ItemIsMember()&& !item->isExpanded()){
			model::OrganizationInfo org = orgItem->getItemData();
			emit signalGetChildrenOrgItem(item, org);
		}
	}
	void OrgTreeList::addRootOrgItem(model::OrganizationInfo&org){
		//LOG_METHOD("OrgTreeList::addRootOrgItem", LOG_FILE);
		m_item = getOrgItem(nullptr,org);
		//emit signalGetChildrenOrgItem(m_item, org);
	}
	void OrgTreeList::addChildOrgItem(QTreeWidgetItem* parent, model::OrganizationInfo&org){
		//LOG_METHOD("OrgTreeList::addChildOrgItem", LOG_FILE);
		m_item = getOrgItem(parent,org);
		//emit signalGetChildrenOrgItem(m_item, org);
	}
	void OrgTreeList::addChildOrgMemItem(QTreeWidgetItem* parent, model::EntpriseUserInfo&member,bool ischeckable){
		//LOG_METHOD("OrgTreeList::addChildOrgMemItem", LOG_FILE);
		m_item = getOrgMemItem(parent, member, ischeckable);
		parent->addChild(m_item);
	}
	void OrgTreeList::addLoadingItem(QTreeWidgetItem* parent){
		//LOG_METHOD("OrgTreeList::addLoadingItem", LOG_FILE);
		QrgTreeItem* loadingitem = nullptr;
		QLabel* lodinglabel = nullptr;
		QMovie* loadingmovie = nullptr;

		lodinglabel = new QLabel(this);
		loadingmovie = new QMovie(":/img/loading");
		lodinglabel->setMovie(loadingmovie);
		loadingmovie->start();

		loadingitem = new QrgTreeItem(parent);
		loadingitem->setItemIsMember(true);
		loadingitem->setSizeHint(0, QSize(0, 60));
		lodinglabel->setFixedSize(100, 60);
		setItemWidget(loadingitem, 0, lodinglabel);
	}
	void OrgTreeList::addNoItem(QTreeWidgetItem* parent){
		//LOG_METHOD("OrgTreeList::addNoItem", LOG_FILE);
		QrgTreeItem* noItemTip = nullptr;
		noItemTip = new QrgTreeItem(parent);
		noItemTip->setText(0,tr("此部门下没有成员!"));
		noItemTip->setExpanded(false);
		parent->addChild(noItemTip);
	}
	QrgTreeItem* OrgTreeList::getOrgItem(QTreeWidgetItem* parent, model::OrganizationInfo&org){
		//LOG_METHOD("OrgTreeList::getOrgItem", LOG_FILE);
		QString orgname("");
		if (nullptr == parent){
			m_item = new QrgTreeItem(this);
		}
		else{
			m_item = new QrgTreeItem(parent);
		}
		QIcon icon;
		icon.addPixmap(QPixmap(":/img/arrow-down"), QIcon::Normal, QIcon::On);//节点打开状态 
		icon.addPixmap(QPixmap(":/img/arrow"), QIcon::Normal, QIcon::Off);//节点关闭状态　
		m_item->setIcon(0, icon);
		orgname = QString::fromUtf8(org.orgName.c_str());
		m_item->setItemIsMember(false);
		m_item->setSizeHint(0, QSize(0, 30));
		m_item->setText(0, orgname);
		m_item->setItemData(org);

		if (nullptr == parent)
		{
			insertTopLevelItem(0, m_item);
			m_item->setExpanded(false);
		}
		else{
			parent->addChild(m_item);
			parent->setExpanded(false);
		}
		return m_item;
	}
	QrgTreeItem* OrgTreeList::getOrgMemItem(QTreeWidgetItem* parent, model::EntpriseUserInfo&member, bool ischeckable){
		//LOG_METHOD("OrgTreeList::getOrgMemItem", LOG_FILE);
		ContactListItem* itemWidget = nullptr;
		QString headpath("");
		QString name("");

		headpath = QString::fromUtf8(member.userHead.data());
		name = QString::fromUtf8(member.enName.data());

		m_item = new QrgTreeItem(parent);
		itemWidget = new ContactListItem(headpath, name, ischeckable,this);
		connect(itemWidget, SIGNAL(signalChecked(qint32, qint64, bool)), this, SIGNAL(signalChecked(qint32, qint64, bool)));
		m_item->setItemIsMember(true);
		m_item->setSizeHint(0, QSize(0, 60));
		itemWidget->setItemType(2);
		itemWidget->setUserData(member);
		setItemWidget(m_item, 0, itemWidget);
		m_item->setExpanded(false);
		parent->addChild(m_item);
		parent->setExpanded(false);
		m_memberlist.push_back(m_item);
		return m_item;
	}
	OrgListWidget::OrgListWidget(QVector<qint64>&memberlist,QWidget*parent) :TWidget(parent){
		//LOG_METHOD("OrgTreeList::OrgListWidget", LOG_FILE);
		m_orgList = new OrgTreeList(this);
		m_loadingWidget = new DefaultWidget(this);
		m_stackWidget = new QStackedWidget(this);
		m_mainLayout = new QVBoxLayout(this);

		m_stackWidget->addWidget(m_loadingWidget);
		m_stackWidget->addWidget(m_orgList);

		m_mainLayout->addWidget(m_stackWidget);
		this->setLayout(m_mainLayout);
		m_stackWidget->setCurrentIndex(0);

		connect(m_orgList, SIGNAL(signalGetChildrenOrgItem(QTreeWidgetItem*, model::OrganizationInfo&)), this, SLOT(onGetNextOrgItem(QTreeWidgetItem*, model::OrganizationInfo&)));
		connect(m_orgList, SIGNAL(signalChecked(qint32, qint64, bool)), this, SIGNAL(signalChecked(qint32, qint64, bool)));
		m_filterMemList = memberlist;
		m_orgService = LDDSERVICE;
		IUserService_Ptr userservice = USERSERVICE;
		model::Account info;
		userservice->getAccountInfo(info);
		m_userid = info.id.value();
		Log(LOG_LEV_INFO,LOG_FILE,"userid  = %lld", m_userid);
		QTimer::singleShot(0, this, SLOT(loadData()));
	}
	OrgListWidget::~OrgListWidget(){
	}
	void OrgListWidget::loadData(){
		//LOG_METHOD("OrgListWidget::loadData", LOG_FILE);
		m_orgList->clear();
		getOrgs(0);
	}
	void OrgListWidget::onGetNextOrgItem(QTreeWidgetItem*parent, model::OrganizationInfo&org){
		//LOG_METHOD("OrgListWidget::onGetNextOrgItem", LOG_FILE);
		getOrgs(org.orgID,parent);
	}
	void OrgListWidget::getOrgs(qint64 orgid, QTreeWidgetItem*parent){
		//LOG_METHOD("OrgListWidget::getOrgs", LOG_FILE);
		std::vector<OrganizationInfo>orgs;
		std::vector<EntpriseUserInfo>members;
		int orgscount = 0;

		Log(LOG_LEV_INFO,LOG_FILE,"orgid = %lld", orgid);
		m_orgService->getVisibleOrgUsersSync(orgid, orgs, members);
		orgscount = orgs.size();

		if (!orgs.size() && !members.size()&& nullptr != parent){
			m_orgList->addNoItem(parent);
			return;
		}
		for (int j = 0; j < members.size(); ++j){
			if (m_userid == members.at(j).userID){
				continue;
			}
			bool iscontains = m_filterMemList.contains(members.at(j).userID);
			Log(LOG_LEV_INFO,LOG_FILE,"userID = %lld,name = %s", members.at(j).userID, QString::fromLocal8Bit(members.at(j).enName.data()));
			m_orgList->addChildOrgMemItem(parent, members.at(j),!iscontains);
			QCoreApplication::processEvents();
		}

		for (int index = 0; index < orgs.size(); ++index){
			if (!orgid)
			{
				m_orgList->addRootOrgItem(orgs.at(index));
			}
			else{
				m_orgList->addChildOrgItem(parent, orgs.at(index));
			}
			QCoreApplication::processEvents();
		}
		m_stackWidget->setCurrentIndex(1);
	}
	void OrgListWidget::getSelectedMember(QVector<model::EntpriseUserInfo>&members){
		//LOG_METHOD("OrgListWidget::getSelectedMember", LOG_FILE);
		m_orgList->getSelectedMember(members);
	}
	void OrgListWidget::updateItemState(qint64 id, bool ischecked){
		bool isfind = m_orgList->setMemberState(id, ischecked);
		if (!isfind)
		{
			if (!m_filterMemList.contains(id) && ischecked){
				m_filterMemList.push_back(id);
			}
			else{
				if (m_filterMemList.contains(id)){
					//m_filterMemList.removeOne(id);
					m_filterMemList.remove(id);
				}
			}
		}
	}
}