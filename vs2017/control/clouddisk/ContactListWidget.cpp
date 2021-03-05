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
#include <qscrollbar.h>
#include <log.h>
namespace ui {
	ContactListItem::ContactListItem(QString&head, QString&name, bool ischeckable, QWidget*parent) : QWidget(parent), m_type(0)
	{
		//LOG_METHOD("ContactListItem::ContactListItem",LOG_FILE);
		m_check = new QCheckBox(this);
		m_head = new HeadImage(this,QSize(40,40));
		m_name = new ElidedLabel(this);
		m_mainLayout = new QHBoxLayout(this);

		
		m_check->setObjectName("checkbtn");
		m_head->setAvatarPath(head);
		m_name->setTextLimitExpand(name);
		m_name->setFixedSize(250, 30);
		m_mainLayout->setAlignment(Qt::AlignLeft);
		m_mainLayout->addWidget(m_check);
		m_mainLayout->addWidget(m_head);
		m_mainLayout->addWidget(m_name);
		m_mainLayout->addStretch();
		setLayout(m_mainLayout);

		connect(m_check, SIGNAL(stateChanged(int)), this, SLOT(slotClicked(int)));
		m_check->setChecked(!ischeckable);
		this->setDisabled(!ischeckable);
		m_ischeckable = ischeckable;
	}
	ContactListItem::~ContactListItem(){

	}
	void ContactListItem::setItemData(model::Contact&contact){
		//LOG_METHOD("ContactListItem::setItemData", LOG_FILE);
		m_contact = contact;
	}
	model::Contact ContactListItem::getItemData()const{
		//LOG_METHOD("ContactListItem::getItemData", LOG_FILE);
		return m_contact;
	}
	void ContactListItem::setUserData(model::EntpriseUserInfo&user){
		//LOG_METHOD("ContactListItem::setUserData", LOG_FILE);
		m_userdata = user;
	}
	bool ContactListItem::isCheckable(){
		//LOG_METHOD("ContactListItem::isCheckable", LOG_FILE);
		return m_ischeckable;
	}
	void  ContactListItem::setItemType(int type){
		m_type = type;
	}
	void ContactListItem::slotClicked(int checked){
		bool ischecked = m_check->isChecked();
		if (1 == m_type){
			emit signalChecked(m_type, m_contact.id.value(),ischecked);
		}
		else{
			emit signalChecked(m_type, m_userdata.userID,ischecked);
		}
	}
	model::EntpriseUserInfo ContactListItem::getUserData()const{
		//LOG_METHOD("ContactListItem::getUserData", LOG_FILE);
		return m_userdata;
	}
	ContactList::ContactList(QListWidget *parent) :QListWidget(parent){
		//LOG_METHOD("ContactList::ContactList", LOG_FILE);
		setFocusPolicy(Qt::NoFocus);						 // 去除item选中时的虚线边框  
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭 
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		setSelectionMode(QAbstractItemView::ExtendedSelection);
		connect(this, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onItemPressed(QListWidgetItem*)));
	}
	ContactList::~ContactList(){

	}
	void ContactList::getSelectedMember(QVector<model::Contact>&members){
		//LOG_METHOD("ContactList::getSelectedMember", LOG_FILE);
		ContactListItem* contactWidget = nullptr;
		for (int j = 0; j < this->count(); ++j){
			contactWidget = (ContactListItem*)this->itemWidget(this->item(j));
			if (nullptr == contactWidget)continue;
			QCheckBox* checkbtn = contactWidget->findChild<QCheckBox*>("checkbtn");
			if (nullptr == checkbtn) continue;
			if (!checkbtn->isChecked())continue;
			if (contactWidget->isCheckable()){
				model::Contact data = contactWidget->getItemData();
				members.push_back(data);
			}
		}
	}
	void ContactList::onItemPressed(QListWidgetItem* item){
		//LOG_METHOD("ContactList::onItemPressed", LOG_FILE);
		QWidget* contactWidget = nullptr;
		if (nullptr == item)return;
		contactWidget = this->itemWidget(item);
		if (nullptr == contactWidget)return;
		QCheckBox* checkbtn = contactWidget->findChild<QCheckBox*>("checkbtn");
		if (nullptr == checkbtn) return;
		bool ischeckable = ((ContactListItem*)contactWidget)->isCheckable();
		if (ischeckable){
			checkbtn->setChecked(!checkbtn->isChecked());
		}
	}
	void ContactList::setMemberState(qint64 id, bool ischecked){
		ContactListItem* contactWidget = nullptr;
		for (int j = 0; j < this->count(); ++j){
			contactWidget = (ContactListItem*)this->itemWidget(this->item(j));
			if (nullptr == contactWidget)continue;
			if (contactWidget->getItemData().id.value() == id){
				QCheckBox* checkbtn = contactWidget->findChild<QCheckBox*>("checkbtn");
				if (nullptr == checkbtn) continue;
				checkbtn->setChecked(ischecked);
				break;
			}
		}
	}
	void ContactList::addItem(model::Contact&contact, bool ischeckable){
		//LOG_METHOD("ContactList::addItem", LOG_FILE);
		QListWidgetItem* item = nullptr;
		ContactListItem* itemWidget = nullptr;
		QString headpath("");
		QString name("");
		int row = 0;

		headpath = QString::fromUtf8(contact.thumbAvatar.value().data());
		name = QString::fromUtf8(contact.name.value().data());
		item = new QListWidgetItem(this);
		item->setSizeHint(QSize(this->width(),60));
		itemWidget = new ContactListItem(headpath, name,ischeckable);
		itemWidget->setItemType(1);
		connect(itemWidget, SIGNAL(signalChecked(qint32, qint64, bool)), this, SIGNAL(signalChecked(qint32, qint64, bool)));
		row = this->count();
		itemWidget->setItemData(contact);
		this->insertItem(row,item);
		this->setItemWidget(item, itemWidget);
	}
	ContactListWidget::ContactListWidget(QVector<qint64>&memberlist, QWidget*parent) :TWidget(parent), m_contactList(nullptr){
		//LOG_METHOD("ContactListWidget::ContactListWidget", LOG_FILE);
		m_filterMemList.clear();
		m_contactList = new ContactList((QListWidget*)this);
		m_loadingWidget = new DefaultWidget(this);
		m_stackWidget = new QStackedWidget(this);
		m_mainLayout = new QVBoxLayout(this);

		m_stackWidget->addWidget(m_loadingWidget);
		m_stackWidget->addWidget(m_contactList);

		m_mainLayout->addWidget(m_stackWidget);
		this->setLayout(m_mainLayout);
		m_stackWidget->setCurrentIndex(0);

		connect(m_contactList, SIGNAL(signalChecked(qint32, qint64, bool)), this, SIGNAL(signalChecked(qint32, qint64, bool)));
		m_filterMemList = memberlist;
		m_contact = CONTACTSERVICE;
		QTimer::singleShot(0, this, SLOT(loadData()));
	}
	ContactListWidget::~ContactListWidget(){

	}
	void ContactListWidget::loadData(){
		//LOG_METHOD("ContactListWidget::loadData", LOG_FILE);
		m_contactList->clear();
		std::vector<SSharedPtr<Contact>>contacts;
		m_contact->getContactList(contacts);
		for (int index = 0; index < contacts.size(); ++index){
			if (1 == contacts.at(index)->isApp.value()){
				continue;
			}
			bool iscontains = m_filterMemList.contains(contacts.at(index)->id.value());
			m_contactList->addItem(*contacts.at(index), !iscontains);
			QCoreApplication::processEvents();
		}
		m_stackWidget->setCurrentIndex(1);
	}
	void ContactListWidget::getSelectedMember(QVector<model::Contact>&members){
		//LOG_METHOD("ContactListWidget::getSelectedMember", LOG_FILE);
		m_contactList->getSelectedMember(members);
	}
	void ContactListWidget::updateItemState(qint64 id, bool ischecked){
		m_contactList->setMemberState(id, ischecked);
	}
}