#ifndef FRIENDINFOWIDGET_WEB_H
#define FRIENDINFOWIDGET_WEB_H

#include <QObject>
#include <data/ContactData.h>
#include <data/entpriseInfo.h>
#include <common/Controlptr.h>
#include <common/Connect.h>
#include "../enterprise/enterpriseinfowidget.h"
#include <QtWebEngineWidgets/QWebEngineView>
namespace ui{
	class UserInfoCommon;
	class UserInfoCommitee;
	class FriendInfoWidgetWeb : public EnterpriseInfoWidget
	{
		Q_OBJECT
	public:
		FriendInfoWidgetWeb(QWidget *parent = CNull);
		~FriendInfoWidgetWeb();
		void updateData(data::Contact contact);
	signals:
		void signalSerGetOrgUserInfo(int, std::vector<data::OrgAndUserInfo>&);
	protected slots:
		void slotStartChat();
		void onSerGetOrgUserInfo(int code, std::vector<data::OrgAndUserInfo>&users);
		void onSerShowMoreInfo();
	private:
		CSharedPtr<UserInfoCommon> m_pUserInfoCommomWidget;
		CSharedPtr<UserInfoCommitee> m_pUserInfoCommiteeWidget;
		data::Contact mData;
		IEntMgrControl_Ptr mEntControl;
		std::string mUserInfo;
		QString m_sex;
		QString m_nation;
		QString	m_myLocation;
		CSharedPtr<QWebEngineView> m_webEngineView;
	};
}

#endif // FRIENDINFOWIDGET_WEB_H
