#pragma once

#include <QListWidget>
#include "common/controlptr.h"

namespace ui{
	class QAppListModel;
	class AppList : public QListWidget
	{
		Q_OBJECT

	public:
		AppList(QWidget *parent = CNull);
		~AppList();

	signals:
		void signalSerGetApplication(std::vector<data::AppInfo>);
		void openLink(QString);

	public slots:
		void onSerGetApplication(std::vector<data::AppInfo> vec);
		void onCurrentItemChanged(QListWidgetItem* item);
		void onInstallApp(int64 iAppID, QString strName, QString strIcon,
			QString strUrl);
		void onUninstallApp(int64 appID);

	private:
		IAppMgrControl_Ptr m_pAppMgr;

		void insertHomePage();
	};
}
