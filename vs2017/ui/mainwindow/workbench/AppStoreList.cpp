#include "AppStoreList.h"
#include <QListWidgetItem>
#include "AppStoreListItem.h"

namespace ui{
	AppStoreList::AppStoreList(QWidget *parent)
		: QListWidget(parent)
	{
		m_pAppMgr = APPMGRCONTROL;

		CONNECT_SERVICE(GetApplication(std::vector<data::AppInfo>));

		if (m_pAppMgr != CNull)
		{
			m_pAppMgr->getAllApplication(CBind
				(&AppStoreList::signalSerGetApplication, this, 
					CPlaceholders  _1));
		}

		this->setSelectionMode(SelectionMode::NoSelection);
		
		this->setObjectName("appStoreList");
	}

	AppStoreList::~AppStoreList()
	{

	}

	void AppStoreList::onSerGetApplication(std::vector<data::AppInfo> vec)
	{

		for (int i = 0; i < vec.size(); i++)
		{
			QListWidgetItem* pItem = new QListWidgetItem(this);
			AppStoreListItem* pListItem = new AppStoreListItem(this);
			connect(pListItem, SIGNAL(installApp(int64, QString, QString, QString)),
				this, SLOT(onInstallApp(int64, QString, QString, QString)));
			connect(pListItem, SIGNAL(uninstallApp(int64)),
				this, SLOT(onUninstallApp(int64)));
			pListItem->setAppID(vec[i].appID);
			pListItem->setName(QString::fromUtf8(vec[i].name.data()));
			pListItem->setAvatar(QString::fromUtf8(vec[i].icon.data()));
			pListItem->setIntroduce(QString::fromUtf8(vec[i].introduction.data()));
			pListItem->setUrl(QString::fromUtf8(vec[i].url.data()));
			pListItem->setButtonStatus(vec[i].isInstalled);
			this->setItemWidget(pItem, pListItem);
		}

		//this->update();
	}

	void AppStoreList::onInstallApp(int64 iAppID, QString strName,
		QString strIcon, QString strUrl)
	{
		emit installApp(iAppID, strName, strIcon, strUrl);
	}

	void AppStoreList::onUninstallApp(int64 iAppID)
	{
		emit uninstallApp(iAppID);
	}

}
