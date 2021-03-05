#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "interface/Defines.h"
#include "common/controlptr.h"


namespace ui{
	class HeadImage;
	class AppStoreListItem : public QWidget
	{
		Q_OBJECT

	public:
		explicit AppStoreListItem(QWidget *parent = CNull);
		~AppStoreListItem();
		void setAppID(const int64 appID);
		void setAvatar(const QString strAvartar);
		void setName(const QString strName);
		void setIntroduce(const QString strIntroduce);
		void setButtonStatus(const bool isInstalled);
		void setUrl(const QString strUrl);

	signals:
		void signalSerAddOrDeleteApplication(int);
		void installApp(int64, QString, QString, QString);
		void uninstallApp(int64);

	public slots:
		void onSerAddOrDeleteApplication(int err);
		void onBtnClicked(void);

	private:
		IAppMgrControl_Ptr m_pAppMgr;
		CSharedPtr<QGridLayout> m_pLayout;
		CSharedPtr<HeadImage> m_pAvatar;
		CSharedPtr<QLabel> m_pLabelName;
		CSharedPtr<QLabel> m_pLabelIntroduce;
		CSharedPtr<QPushButton> m_pBtnInstall;
		CSharedPtr<QPushButton> m_pBtnUninstall;
		int64 m_iAppID;
		QString m_strUrl;
		bool m_isInstalled;
	};
}
