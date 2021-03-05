#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "interface/Defines.h"


namespace ui{
	class HeadImage;
	class AppListItem : public QWidget
	{
		Q_OBJECT

	public:
		explicit AppListItem(QWidget *parent = CNull);
		~AppListItem();
		int64 appID(void) const;
		void setAppID(const int64 appID);
		void setAvatar(const QString strAvartar);
		void setName(const QString strName);
		QString url(void) const;
		void setUrl(const QString strUrl);

	private:
		CSharedPtr<QHBoxLayout> m_pLayout;
		CSharedPtr<HeadImage> m_pAvatar;
		CSharedPtr<QLabel> m_pLabelName;
		int64 m_iAppID;
		QString m_strUrl;
	};
}
