#include "AppWebView.h"
#include <QUrl>
#include <QDebug>
#include "common/Common.h"
#include <QDebug>
#include <QFileDialog>
#include "common/UIUtils.h"
//CSharedPtr<QWebChannel> m_WebChannel = CMakePtr<QWebChannel>();
namespace ui {
	AppWebView::AppWebView(QWidget *parent)
		: QWebEngineView(parent)
	{
		//m_BrowserControl = new WebBrowserController(this);
		m_pLayout = CMakePtr<QVBoxLayout>(this);
		m_pProgressBar = CMakePtr<QProgressBar>(this);
		page = new AppWebPage(this);
		//m_WebChannel = CMakePtr<QWebChannel>(this);
		//page->Setwebchannel(m_WebChannel.get());

		this->setPage(page);

		connect(page->profile(), SIGNAL(downloadRequested(QWebEngineDownloadItem*)),
			this, SLOT(downloadJump(QWebEngineDownloadItem*)));

		connect(this, SIGNAL(loadStarted()), 
			m_pProgressBar.get(), SLOT(show()));
		connect(this, SIGNAL(loadFinished(bool)),
			m_pProgressBar.get(), SLOT(hide()));
		connect(this, SIGNAL(loadProgress(int)),
			m_pProgressBar.get(), SLOT(setValue(int)));
		//connect(this, SIGNAL(urlChanged(const QUrl&)),);
		populateJavaScriptWindowObject();
		m_pProgressBar->setMinimum(0);
		m_pProgressBar->setMaximum(100);
		m_pProgressBar->setTextVisible(false);
		m_pProgressBar->setFixedHeight(3);

		m_pLayout->addWidget(m_pProgressBar.get(), 0, Qt::AlignBottom);
		m_pLayout->setContentsMargins(0, 0, 0, 0);

		//connect(m_BrowserControl, SIGNAL(signalCtrlStartChat(int64)), this, SLOT(onSerOpenChatWidget(int64)));

		this->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
		this->settings()->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard,true);
		this->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows,true);
		this->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled,true);
		this->settings()->setAttribute(QWebEngineSettings::AutoLoadImages,true);
		this->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
		this->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
		this->settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, false);
	}

	AppWebView::~AppWebView()
	{
	}

	void AppWebView::populateJavaScriptWindowObject()
	{
		//m_WebChannel->registerObject(QString(INTERFACE_NAME), m_BrowserControl);
	}

	void AppWebView::onLoadStart()
	{
		m_pProgressBar->setVisible(true);
	}

	void AppWebView::onFinished(bool ok)
	{
		m_pProgressBar->setVisible(false);
	}

	void AppWebView::onLoadProgress(int progress)
	{
		m_pProgressBar->setValue(progress);
	}

	void AppWebView::onSerOpenChatWidget(int64 id)
	{
		emit signalSerOpenChatWidget(id);
	}

	void AppWebView::setValue(int Value)
	{
		m_pProgressBar->setValue(Value);
	}

	void AppWebView::downloadJump(QWebEngineDownloadItem *softdownload)
	{
		emit signaldownloadRequested(softdownload);
	}

	AppWebView *AppWebView::createWindow(QWebEnginePage::WebWindowType type)
	{
		if (type == QWebEnginePage::WebBrowserTab) {
			AppWebView* NewView = new AppWebView();
			//page = new AppWebPage();
			//m_WebChannel = CMakePtr<QWebChannel>(this);
			//NewView->setPage(page);
			emit signalSerNewWebView(NewView);
			return NewView;
		}
		/*else if (type == QWebEnginePage::WebBrowserWindow) {
			BrowserApplication::instance()->newMainWindow();
			BrowserMainWindow *mainWindow = BrowserApplication::instance()->mainWindow();
			return mainWindow->currentTab()->page();
		}
		else {
			PopupWindow *popup = new PopupWindow(profile());
			popup->setAttribute(Qt::WA_DeleteOnClose);
			popup->show();
			return popup->page();
		}*/
	}
}

