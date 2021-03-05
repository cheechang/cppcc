#include <QCoreApplication>

#include "AppAccountList.h"
#include "FriendListWidgetItem.h"
#include "common/Connect.h"
#include "common/Common.h"

namespace ui
{

	void AppAccountList::paintEvent( QPaintEvent *event )
	{
		if (mlblBg)
		{
			mlblBg->move((width()-mlblBg->width())/2,(height()-mlblBg->height())/2);
		}
	}

	AppAccountList::AppAccountList(QWidget *parent)
		: TWidget(parent)
	{
		m_pContactControl = CONTACTMGRCONTROL;
		m_pListWidget = new QListWidget(this);
		m_pMainLayout = new QVBoxLayout(this);

		m_pMainLayout->addWidget(m_pListWidget);
		this->setLayout(m_pMainLayout);
		m_pMainLayout->setContentsMargins(0, 2, 0, 0);
		setObjectName("bg_fa");
		m_pListWidget->setSelectionMode(QAbstractItemView::NoSelection);

		mlblBg = new QLabel(this);
		mlblBg->setPixmap(QPixmap(":/base/default"));
		mlblBg->setFixedSize(160,160);

		initMenu();
		connect(m_pListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
		if(m_pContactControl)
		{
			//CONNECT_SERVICE(GetEntAccountCb(int, std::vector<data::EnterpriseAccount>&));
			bool noAppItem = true;
			CONNECT_SERVICE(RemoveAppCB(int));
			std::vector<CSharedPtr<data::Contact>> contacts;
			m_pContactControl->GetContactList(contacts);
			for (int i=0; i < contacts.size(); i++)
			{
				if ((contacts.at(i))->isApp.value() == 1)
				{
					addItemToList(*(contacts.at(i)));
					QCoreApplication::processEvents();
					noAppItem = false;
				}
			}
			mlblBg->setVisible(noAppItem);
		}
	}

	AppAccountList::~AppAccountList()
	{
		if(m_pMenu)
		{
			delete m_pMenu;
			m_pMenu = CNull;
		}
		if(m_pActionDel)
		{
			delete m_pActionDel;
			m_pActionDel = CNull;
		}
	}

	//void AppAccountList::onSerGetEntAccountCb(int code, std::vector<data::EnterpriseAccount>& entAccounts)
	//{
	//	clearList();
	//	for (int i=0; i < entAccounts.size(); i++)
	//	{
	//		addItemToList(entAccounts.at(i));
	//		QCoreApplication::processEvents();
	//	}
	//}

	void AppAccountList::onItemDoubleClicked( QListWidgetItem*item )
	{
		FriendListWidgetItem* widget = (FriendListWidgetItem*)m_pListWidget->itemWidget(item);
		if(widget != CNull)
		{
			data::Contact data = m_mapData.value(widget->id());
			CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
			chat->chatType = data::APP_CHAT;
			chat->isStartChat = true;
			chat->avatar = data.thumbAvatar.value();
			chat->name = QString::fromUtf8(data.name.value().c_str()).toStdString();
			chat->targetid = data.id.value();
			emit startChat(chat);
		}
	}

	void AppAccountList::clearList()
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

	void AppAccountList::contextMenuEvent( QContextMenuEvent *e )
	{
		QListWidgetItem* item = m_pListWidget->itemAt(mapFromGlobal(QCursor::pos()));
		if(item != CNull)
		{
			FriendListWidgetItem* widget = (FriendListWidgetItem*)m_pListWidget->itemWidget(item);
			if(widget)
			{
				m_curItemId = widget->id();
				m_pMenu->exec(QCursor::pos());
			}
		}
	}

	void AppAccountList::initMenu()
	{
		m_pMenu = new QMenu(this);
		m_pActionDel = new QAction(transfer("È¡Ïû¹Ø×¢"), this);
		m_pMenu->addAction(m_pActionDel);
		connect(m_pActionDel, SIGNAL(triggered(bool)), this, SLOT(onDeleteMenuItemClicked()));
	}

	int AppAccountList::addItemToList(const data::Contact& data)
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

	void AppAccountList::editItemFromIist(const data::Contact &data)
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

	void AppAccountList::removeItemFromList( const data::Contact &data ,bool selectNextItem)
	{
		for (int i=0; i < m_pListWidget->count(); i++)
		{
			QListWidgetItem* item = m_pListWidget->item(i);
			FriendListWidgetItem* widget = (FriendListWidgetItem*)m_pListWidget->itemWidget(item);
			if(widget != CNull && widget->id() == data.id.value())
			{
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

	void AppAccountList::onDeleteMenuItemClicked()
	{
		if(m_pContactControl)
		{
			m_pContactControl->RemoveContact(m_curItemId,CBind
				(&AppAccountList::signalSerRemoveAppCB, this, CPlaceholders  _1));
		}
	}

	void AppAccountList::onSerRemoveAppCB(int code)
	{
		if (code == 0)
		{
			clearList();
			std::vector<CSharedPtr<data::Contact>> contacts;
			m_pContactControl->GetContactList(contacts);
			for (int i=0; i < contacts.size(); i++)
			{
				if ((contacts.at(i))->isApp.value() == 1)
				{
					addItemToList(*(contacts.at(i)));
					QCoreApplication::processEvents();
				}
			}
		}
	}
}