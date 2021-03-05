#include "CloudDiskMenu.h"
#include <qpainter.h>
#include <model/Packet.h>
#include "TableWidgetItem.h"
namespace ui{
	CloudDiskMenu::CloudDiskMenu(QWidget *parent) :QMenu(parent),
		m_pDelItem(nullptr), m_pRenameItem(nullptr), m_pRefresh(nullptr),
		m_pSortByTime(nullptr), m_isowner(false), m_isrootnode(false)
	{
		m_pDelItem = std::make_shared<QAction>(tr("删除"), this);   //重命名
		m_pRenameItem = std::make_shared<QAction>(tr("重命名"), this); //重命名
		m_pRefresh = std::make_shared<QAction>(tr("刷新"), this); //刷新菜单
		m_pSortByTime = std::make_shared<QAction>(tr("时间排序"), this);//按时间排序

		QObject::connect(m_pDelItem.get(), SIGNAL(triggered()), this, SIGNAL(signalDelMenu()));
		QObject::connect(m_pRenameItem.get(), SIGNAL(triggered()), this, SIGNAL(signalRenameMenu()));
		QObject::connect(m_pRefresh.get(), SIGNAL(triggered()), this, SIGNAL(signalRefresh()));
		QObject::connect(m_pSortByTime.get(), SIGNAL(triggered()), this, SIGNAL(signalSortByTime()));

		setMenuState(MENU_SORTBYTIME, true);
		setMenuState(MENU_REFRESH, true);
		this->setObjectName("clouddiskmenu");
	}
	CloudDiskMenu::~CloudDiskMenu(){

	}
	void CloudDiskMenu::setIsOwner(bool isowned){
		m_isowner = isowned;
	}
	void CloudDiskMenu::setIsRootNode(bool isrootnode){
		m_isrootnode = isrootnode;
	}
	void CloudDiskMenu::setMenuState(MenuItem item, bool isShow){
		model::CloudPermission permis = TableWidgetItem::getItemPermission();
		switch (item)
		{
		case MENU_DEL:
			(m_isowner? (isShow&&m_isowner):(isShow&&permis.isDelete)) ? this->addAction(m_pDelItem.get()) : this->removeAction(m_pDelItem.get());
			break;

		case MENU_RENAME:
			(m_isowner? (isShow&&m_isowner):(isShow&&permis.isReName)) ? this->addAction(m_pRenameItem.get()) : this->removeAction(m_pRenameItem.get());
			break;
		case MENU_REFRESH:
			isShow? this->addAction(m_pRefresh.get()) : this->removeAction(m_pRefresh.get());
			break;
		case MENU_SORTBYTIME:
			isShow ? this->addAction(m_pSortByTime.get()) : this->removeAction(m_pSortByTime.get());
			break;
		default:
			break;
		}
	}
	void CloudDiskMenu::setMenuEnable(MenuItem item, bool enable){
		switch (item)
		{
		case MENU_DEL:
			m_pDelItem->setDisabled(enable);
			break;

		case MENU_RENAME:
			m_pRenameItem->setDisabled(enable);
			break;
		case MENU_REFRESH:
			m_pRefresh->setDisabled(enable);
			break;
		case MENU_SORTBYTIME:
			m_pSortByTime->setDisabled(enable);
			break;
		default:
			break;
		}
	}
	void CloudDiskMenu::show(QPoint pt){
		int menucount = this->actions().size();
		if (menucount){
			this->exec(pt);
		}
	}

}