#ifndef FRIENDLISTWIDGET_WEB_H
#define FRIENDLISTWIDGET_WEB_H
#include "controls/TWidget.h"
#include <data/ContactData.h>
#include <data/ChatData.h>
#include <QMenu>
#include <QAction>
#include <QListWidget>
#include <QVBoxLayout>
#include "interface/Defines.h"
#include "common/Controlptr.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
namespace ui{
	class FriendListWidgetItem;
	class ModifyFriendRemarkWindow;
	class FriendListWidgetWeb : public QWidget
	{
		Q_OBJECT
	public:
		FriendListWidgetWeb(QWidget *parent = CNull);
		~FriendListWidgetWeb();
	signals:
 		void showContactInfoPage(data::Contact);
 	public slots:
 
		void onItemClicked(QListWidgetItem*item);
		void onMySelectItem(int itemid);
			;
	private:
 
		int addItemToList(const data::Contact& data,bool bBigImage);
		void clearList();
		 
	public:
		QMap<int64,data::Contact> mMapData;
		QListWidget* mListWidget;
		QVBoxLayout*mainLayout;
	 
		int64 mCurCickItemId;
		CSharedPtr<data::AccountInfo> muserinfo;

		IUserControl_Ptr m_usercontrol;

		QString m_homeurl;

		void Init_Home();
		void Init_MyInfo();
		int m_MyInfoMode;
		QString m_WebSearchUrl;

/// 根据排序APP的顺序重新排位置
	public:
		QNetworkRequest* m_AppSortRrequest;
		QNetworkAccessManager* m_AppSortManager;
		void getAppSortInfo(void);
		QString m_AppSortInfo;
		void Init_Sort_Home();
	public slots:
		void onAppSortRsp(QNetworkReply* preplay);
	};
}

#endif // FRIENDLISTWIDGET_WEB_H
