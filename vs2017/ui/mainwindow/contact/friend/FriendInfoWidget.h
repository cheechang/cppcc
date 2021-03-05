#ifndef FRIENDINFOWIDGET_H
#define FRIENDINFOWIDGET_H

#include <QObject>
#include <data/ContactData.h>
#include <data/entpriseInfo.h>
#include <common/Controlptr.h>
#include <common/Connect.h>
#include "../enterprise/enterpriseinfowidget.h"
#include "controls/TWidget.h"
#include <QtWebEngineWidgets/QWebEngineView>
namespace ui{
	class UserInfoCommon;
	class UserInfoCommitee;
	class FriendInfoWidget : public ui::TWidget
	{
		Q_OBJECT
	public:
		FriendInfoWidget(QWidget *parent=CNull);
		~FriendInfoWidget();
		void updateData(data::Contact contact);
		void adjustWidget();
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&);
	private:
		CSharedPtr<UserInfoCommon> m_pUserInfoCommomWidget;
		CSharedPtr<UserInfoCommitee> m_pUserInfoCommiteeWidget;
		data::Contact mData;
		std::string mUserInfo;
		QVBoxLayout*m_pMainLayout;
	};
}

#endif // FRIENDINFOWIDGET_H
