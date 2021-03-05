#pragma once

#include <QListWidget>
#include "common/controlptr.h"

namespace ui{
	class QAppListModel;
	class AppStoreList : public QListWidget
	{
		Q_OBJECT

	public:
		AppStoreList(QWidget *parent = CNull);
		~AppStoreList();

	signals:
		void signalSerGetApplication(std::vector<data::AppInfo>);
		void openLink(QString);
		void installApp(int64, QString, QString, QString);
		void uninstallApp(int64);

	public slots:
		void onSerGetApplication(std::vector<data::AppInfo> vec);
		void onInstallApp(int64 iAppID, QString strName, QString strIcon,
			QString strUrl);
		void onUninstallApp(int64 iAppID);

	private:
		IAppMgrControl_Ptr m_pAppMgr;
	};
}
