#include "AppList.h"
#include <QListWidgetItem>
#include "AppListItem.h"
#include "Common/Common.h"
namespace ui{
	AppList::AppList(QWidget *parent)
		: QListWidget(parent)
	{
		m_pAppMgr = APPMGRCONTROL;

		CONNECT_SERVICE(GetApplication(std::vector<data::AppInfo>));

		if (m_pAppMgr != CNull)
		{
			m_pAppMgr->getInstalledApplication(CBind
				(&AppList::signalSerGetApplication, this, 
				CPlaceholders  _1));
		}
		connect(this, SIGNAL(itemClicked(QListWidgetItem*)), this,SLOT(onCurrentItemChanged(QListWidgetItem*)));
	}

	AppList::~AppList()
	{

	}

	void AppList::onSerGetApplication(std::vector<data::AppInfo> vec)
	{
#ifdef ONLY_HOME_PAGE
		insertHomePage();
		return;
#endif
		for (int i = 0; i < vec.size(); i++)
		{
			//CSharedPtr<QListWidgetItem> pItem = CMakePtr<QListWidgetItem>(this);
			//CSharedPtr<AppListItem> pListItem = CMakePtr<AppListItem>(this);
			QListWidgetItem* pItem = new QListWidgetItem(this);
			AppListItem* pListItem = new AppListItem(this);
			pListItem->setAppID(vec[i].appID);
			pListItem->setName(QString::fromUtf8(vec[i].name.data()));
			pListItem->setAvatar(QString::fromUtf8(vec[i].icon.data()));
			pListItem->setUrl(QString::fromUtf8(vec[i].url.data()));
			//this->addItem(pItem);
			this->setItemWidget(pItem, pListItem);
		}
		QListWidgetItem* pItem = new QListWidgetItem(this);
		AppListItem* pListItem = new AppListItem(this);
		pListItem->setName(transfer("添加应用"));
		pListItem->setAvatar(":/app/add");
		pListItem->setUrl("appstore");
		this->setItemWidget(pItem, pListItem);

	}

	void AppList::onCurrentItemChanged(QListWidgetItem* item)
	{
		if(item != CNull)
		{
			this->setCurrentItem(item);
			AppListItem* listitem = (AppListItem*)this->itemWidget(item);
			if(listitem != CNull)
			{
				emit openLink(listitem->url());
			}
		}
	}

	void AppList::onInstallApp(int64 iAppID, QString strName,
		QString strIcon, QString strUrl)
	{
		//CSharedPtr<QListWidgetItem> pItem = CMakePtr<QListWidgetItem>(this);
		//CSharedPtr<AppListItem> pListItem = CMakePtr<AppListItem>(this);
		QListWidgetItem* pItem = new QListWidgetItem();
		AppListItem* pListItem = new AppListItem();
		pListItem->setAppID(iAppID);
		pListItem->setName(strName);
		pListItem->setAvatar(strIcon);
		pListItem->setUrl(strUrl);
		this->insertItem(this->count() - 1, pItem);
		this->setItemWidget(pItem, pListItem);
	}

	void AppList::onUninstallApp(int64 appID)
	{
		for(int i = 0; i < this->count(); i++)
		{
			QListWidgetItem* pItem = this->item(i);
			AppListItem* pListItem = (AppListItem*)this->itemWidget(pItem);
			if(pListItem->appID() == appID)
			{
				this->takeItem(i);
			}
		}
	}

	void AppList::insertHomePage()
	{
 
		QListWidgetItem* pItem = new QListWidgetItem(this);
		AppListItem* pListItem = new AppListItem(this);
		pListItem->setAppID(1001);
		pListItem->setName(transfer("首页1234"));
		pListItem->setAvatar(":/app/home");
		pListItem->setUrl(transfer("http://www.baidu.com"));
		this->setItemWidget(pItem, pListItem);
		emit openLink(pListItem->url());
	}
}
