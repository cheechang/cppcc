#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QMap>
#include <QLabel>
#include <QTabWidget>
#include <interface/Defines.h>
#include "AppWebView.h"
#include "json.h"
#include "DownFileWidget.h"
#include "log.h"
#include "WebBrowserController.h"

namespace ui{
	class DefaultWidget;
	class EnterpriseInfoWidget;
	class ContactTabWidgetArea;
	class GroupInforWidget;
	class FriendInfoWidget;
	class AppInfoWidget;
	class SearchContactWindow;
	class CreateGroupWindow;
	class EnterpriseAccountList;
	class AppAccountList;
	class Workbench : public QWidget
	{
		Q_OBJECT

	public:
		Workbench(QWidget *parent = CNull);
		~Workbench();

	protected:
		QString GetVerifyRes();
		QString GetConfigContent();
	signals:
		void signalSerOpenChatWidget(int64 targetid);
		void signalSerDownFileFinish(int32 id);
	public slots:
		void onOpenLink(QString url);
		void onSerOpenChatWidget(int64 targetid);
		void onSerNewWebView(AppWebView*);
		void onSerdownloadJump(QWebEngineDownloadItem *softdownload);
		void removeSubTab(int);
		void onSerDownFileFinish(int32 id);
		void onSerTabClicked(int);
		//void setCurrentProgress(qint64, qint64);
	private:
		CSharedPtr<QHBoxLayout> m_pLayout;
		CSharedPtr<QStackedWidget> m_pStack;
		CSharedPtr<QTabWidget> m_pTableWidget;
		CSharedPtr<AppWebView> m_pWebView;
		CSharedPtr<QLabel> m_UrlTip;
		CSharedPtr<QWidget> m_widgettip;
		CSharedPtr<QHBoxLayout> m_layouttip;
		CSharedPtr<QWebChannel> m_WebChannel;
		int Count;
		WebBrowserController* m_BrowserControl;
		DownFileWidget* m_DownFileWidget;
	};
}