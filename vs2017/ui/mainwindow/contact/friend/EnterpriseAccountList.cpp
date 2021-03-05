#include <QCoreApplication>

#include "EnterpriseAccountList.h"
#include "FriendListWidgetItem.h"
#include "common/Connect.h"
#include "common/Common.h"

namespace ui
{
	EnterpriseAccountList::EnterpriseAccountList(QWidget *parent)
		: TWidget(parent)
	{
		m_pContactControl = CONTACTMGRCONTROL;
		m_pListWidget = new QListWidget(this);
		m_pMainLayout = new QVBoxLayout(this);

		m_pMainLayout->addWidget(m_pListWidget);
		this->setLayout(m_pMainLayout);
		m_pMainLayout->setContentsMargins(0, 1, 0, 0);
		setObjectName("bg_fa");
		m_pListWidget->setSelectionMode(QAbstractItemView::NoSelection);

		//initMenu();

		mlblBg = new QLabel(this);
		mlblBg->setPixmap(QPixmap(":/base/default"));
		mlblBg->setFixedSize(160,160);
		mlblBg->move(width()/3,80);

		connect(m_pListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
		if(m_pContactControl)
		{
			CONNECT_SERVICE(GetEntAccountCb(int, std::vector<data::EnterpriseAccount>&));
			m_pContactControl->getEntAccount(CBind(&EnterpriseAccountList::signalSerGetEntAccountCb,
				this, CPlaceholders _1, CPlaceholders _2));
		}
	}

	EnterpriseAccountList::~EnterpriseAccountList()
	{
		//if(m_pMenu){
		//	delete m_pMenu;
		//}
		//if(m_pActionDel){
		//	delete m_pActionDel;
		//}
	}

	void EnterpriseAccountList::onSerGetEntAccountCb(int code, std::vector<data::EnterpriseAccount>& entAccounts)
	{
		clearList();
		for (int i=0; i < entAccounts.size(); i++)
		{
			addItemToList(entAccounts.at(i));
			QCoreApplication::processEvents();
		}
		mlblBg->setVisible(entAccounts.size() == 0);
	}

	void EnterpriseAccountList::onItemDoubleClicked( QListWidgetItem*item )
	{
		FriendListWidgetItem* widget = (FriendListWidgetItem*)m_pListWidget->itemWidget(item);
		if(widget != CNull)
		{
			data::Contact data = m_mapData.value(widget->id());
			CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
			chat->chatType = data::ENT_CHAT;
			chat->isStartChat = true;
			chat->avatar = data.thumbAvatar.value();
			chat->name = QString::fromUtf8(data.name.value().c_str()).toStdString();
			chat->targetid = data.id.value();
			emit startChat(chat);
		}
	}

	void EnterpriseAccountList::clearList()
	{
		for (int i=0;i<m_pListWidget->count();)
		{
			QListWidgetItem* item = m_pListWidget->item(i);
			QWidget* widget = m_pListWidget->itemWidget(item);
			m_pListWidget->removeItemWidget(item);
			if(item != CNull){
				delete item;
			}
			if(widget != CNull){
				delete widget;
			}
			QCoreApplication::processEvents();
		}
		m_mapData.clear();
	}

	//void EnterpriseAccountList::contextMenuEvent( QContextMenuEvent *e )
	//{
	//	QListWidgetItem* item = m_pListWidget->itemAt(mapFromGlobal(QCursor::pos()));
	//	if(item != CNull)
	//	{
	//		FriendListWidgetItem* widget = (FriendListWidgetItem*)m_pListWidget->itemWidget(item);
	//		if(widget)
	//		{
	//			m_curItemId = widget->id();
	//			m_pMenu->exec(QCursor::pos());
	//		}
	//	}
	//}

	//void EnterpriseAccountList::initMenu()
	//{
	//	m_pMenu = new QMenu(this);
	//	m_pActionDel = new QAction(transfer("删除好友"), this);
	//	m_pMenu->addAction(m_pActionDel);
	//	connect(m_pActionDel, SIGNAL(triggered(bool)),  this,SLOT(onDeleteMenuItemClicked()));
	//}

	int EnterpriseAccountList::addItemToList(const data::Contact& data)
	{
		QListWidgetItem* item = new QListWidgetItem();
		FriendListWidgetItem* widget = new FriendListWidgetItem(this);
		QString head = transfer(data.thumbAvatar.value().c_str());
		if(head.isEmpty())
		{
			head = DEFAULT_APP;
		}
		QString name = QString::fromUtf8(data.name.value().c_str());
		widget->setData(head, name);
		widget->setId(data.id.value());

		m_pListWidget->addItem(item);
		m_pListWidget->setItemWidget(item, widget);
		m_mapData.insert(data.id.value(), data);
		return m_pListWidget->row(item);
	}

	void EnterpriseAccountList::editItemFromIist(const data::Contact &data)
	{
		for (int i=0; i < m_pListWidget->count(); i++)
		{
			QListWidgetItem* item = m_pListWidget->item(i);
			FriendListWidgetItem* widget = (FriendListWidgetItem*)m_pListWidget->itemWidget(item);
			if(widget != CNull && widget->id() == data.id.value())
			{
				data::Contact newItemData = m_mapData.value(data.id.value());
				if(data.remark.isSet())
				{
					QString name = data.remark.value().empty() ? QString::fromUtf8(data.name.value().c_str()) : QString::fromUtf8(data.remark.value().c_str());
					widget->setName(name);
					newItemData.remark = data.remark.value();
				}
				if(data.thumbAvatar.isSet())
				{
					QString head = transfer(data.thumbAvatar.value().c_str());
					if(head.isEmpty())
					{
						head = DEFAULT_APP;
					}
					widget->setHead(head);
					newItemData.thumbAvatar = data.thumbAvatar.value();
				}
				removeItemFromList(data, false);
                addItemToList(newItemData);
				return;
			}
		}
	}

	void EnterpriseAccountList::removeItemFromList( const data::Contact &data ,bool selectNextItem)
	{
		for (int i=0; i < m_pListWidget->count(); i++)
		{
			QListWidgetItem* item = m_pListWidget->item(i);
			FriendListWidgetItem* widget = (FriendListWidgetItem*)m_pListWidget->itemWidget(item);
			if(widget != CNull && widget->id() == data.id.value())
			{
				//if(selectNextItem)
				//{
				//	this->selectNextItem(i);
				//}
				m_pListWidget->removeItemWidget(item);
				if(item != CNull){
					delete item;
				}
				if(widget != CNull){
					delete widget;
				}
				m_mapData.remove(data.id.value());
				return;
			}
		}
	}

	void EnterpriseAccountList::paintEvent( QPaintEvent *event )
	{
		if (mlblBg)
		{
			mlblBg->move((width()-mlblBg->width())/2,(height()-mlblBg->height())/2);
		}
	}

	//void EnterpriseAccountList::onDeleteMenuItemClicked()
	//{
	//	if(m_pContactControl){
	//		m_pContactControl->RemoveContact(m_curItemId,CBind
	//			(&EnterpriseAccountList::signalRemoveContactCb,this,CPlaceholders  _1));
	//	}
	//}

	//void EnterpriseAccountList::onSerRemoveContactCb( int code )
	//{

	//}

	//void EnterpriseAccountList::selectNextItem( int prevRow )
	//{
	//	if(prevRow == m_pListWidget->currentRow()){//删除当前选中项
	//		if(prevRow == m_pListWidget->count()-1){
	//			m_pListWidget->setCurrentRow(0);
	//		}else{
	//			m_pListWidget->setCurrentRow(prevRow+1);
	//		}
	//		FriendListWidgetItem* next = (FriendListWidgetItem*)m_pListWidget->itemWidget(m_pListWidget->currentItem());
	//	}
	//}
}