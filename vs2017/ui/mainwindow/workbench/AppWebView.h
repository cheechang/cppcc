#pragma once

#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineSettings>
#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtWebEngineWidgets/QWebEngineDownloadItem>
#include <QVBoxLayout>
#include <QProgressBar>
#include "../../common/Common.h"
#include <interface/Defines.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QWebChannel>
#include "DownFileWidget.h"
class WebBrowserController;
namespace ui {
	class AppWebPage : public QWebEnginePage
	{
		Q_OBJECT

	public:
		explicit AppWebPage(QObject *parent = 0) : QWebEnginePage(parent) {

		}
		~AppWebPage() {}
		virtual QString userAgentForUrl(const QUrl& url) const 
		{
			return USER_AGENT;
		}
	
		void Setwebchannel(QWebChannel* channel){
			this->setWebChannel(channel);
		}
		
	};

	class AppWebView : public QWebEngineView
	{
		Q_OBJECT

	public:
		AppWebView(QWidget *parent = 0);
		~AppWebView();
		WebBrowserController* m_BrowserControl;
	signals:
		void signalSerOpenChatWidget(int64);
		void signalSerNewWebView(AppWebView*);

		void signaldownloadRequested(QWebEngineDownloadItem *softdownload);
		void dataChanged(qint64, qint64);
	public:
		virtual AppWebView *createWindow(QWebEnginePage::WebWindowType type);
	public slots:
		void populateJavaScriptWindowObject();
		void onLoadStart();
		void onFinished(bool ok);
		void onLoadProgress(int progress);
		void onSerOpenChatWidget(int64);
		void setValue(int);
		void downloadJump(QWebEngineDownloadItem *softdownload);
	private:
		
		CSharedPtr<QVBoxLayout> m_pLayout;
		CSharedPtr<QProgressBar> m_pProgressBar;
		//CSharedPtr<QWebChannel> m_WebChannel;
	public:
		AppWebPage* page;
		//std::map<int32, QString> m_DownFileMap;
		std::vector<int32> m_DownFileIdVector;
	};
}