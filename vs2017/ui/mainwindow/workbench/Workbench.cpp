#include "Workbench.h"
#include <QStackedWidget>
#include "../../../utils/aes.h"
#include "../../common/UIUtils.h"
#include <QDesktopServices>
#include <QFileDialog>
#include <QSettings>
#include <QCoreApplication>

std::string gaccount = "";
namespace ui{
	Workbench::Workbench(QWidget *parent)
		: QWidget(parent), m_pStack(CNull), m_pLayout(CNull), m_pWebView(CNull),Count(0)
	{
		
		m_DownFileWidget = new DownFileWidget();
		m_pLayout = CMakePtr<QHBoxLayout>(this);
		m_pStack = CMakePtr<QStackedWidget>(this);
		m_pWebView = CMakePtr<AppWebView>(this);
		m_WebChannel = CMakePtr<QWebChannel>();
		m_BrowserControl = new WebBrowserController(this);
		m_pWebView->page->setWebChannel(m_WebChannel.get());

		m_pTableWidget = CMakePtr<QTabWidget>(this);
		m_pTableWidget->setTabsClosable(true);


		m_pTableWidget->setObjectName("WebViewSettabbar");
		connect(m_pTableWidget.get(), SIGNAL(tabCloseRequested(int)), this, SLOT(removeSubTab(int)));		
		connect(m_pTableWidget.get(), SIGNAL(currentChanged(int)), this, SLOT(onSerTabClicked(int)));

		m_widgettip = CMakePtr<QWidget>(this);
		m_layouttip = CMakePtr<QHBoxLayout>(this);
		m_UrlTip = CMakePtr<QLabel>(this);
		m_UrlTip->setText(QString::fromLocal8Bit("Çë ¼ì ²é Äú µÄ Íø Ö·£¬ Õâ Àï Ö» ÊÇ ²â ÊÔ  Íø Ò³. . ."));
		m_UrlTip->setObjectName("MWebTip");

		m_layouttip->addWidget(m_UrlTip.get(),0,Qt::AlignHCenter);
		m_widgettip->setLayout(m_layouttip.get());

		connect(m_pWebView.get(), SIGNAL(signalSerOpenChatWidget(int64)),this, SLOT(onSerOpenChatWidget(int64)));
		connect(m_pWebView.get(), SIGNAL(signalSerNewWebView(AppWebView*)), this, SLOT(onSerNewWebView(AppWebView*)));
		//connect(m_pWebView.get(), SIGNAL(signalSerOpenChatWidget(int64)), this, SLOT(onSerOpenChatWidget(int64)));
		connect(m_pWebView.get(), SIGNAL(signaldownloadRequested(QWebEngineDownloadItem*)), this, SLOT(onSerdownloadJump(QWebEngineDownloadItem *)));

		m_pTableWidget->addTab(m_pWebView.get(),QString::fromLocal8Bit("²âÊÔÍøÒ³"));
		((QTabBar*)m_pTableWidget->tabBar())->setTabButton(m_pTableWidget->indexOf(m_pWebView.get()), QTabBar::RightSide, NULL);

		m_pStack->setMinimumWidth(580);	
		m_pStack->setContentsMargins(0,0,0,0);

		m_pStack->addWidget(m_pTableWidget.get());
		m_pStack->addWidget(m_widgettip.get());

		m_pLayout->addWidget(m_pStack.get());
		m_pLayout->setContentsMargins(0, 0, 0, 0);
		m_pLayout->setSpacing(0);
		this->setLayout(m_pLayout.get());

		connect(this, SIGNAL(signalSerDownFileFinish(int32)), this, SLOT(onSerDownFileFinish(int32)));

		m_WebChannel->registerObject(QString(INTERFACE_NAME), m_BrowserControl);
		connect(m_BrowserControl, SIGNAL(signalCtrlStartChat(int64)), this, SLOT(onSerOpenChatWidget(int64)));

		QString url("");
		onOpenLink(url);
	}

	Workbench::~Workbench()
	{
	
	}

	void Workbench::onSerNewWebView(AppWebView* newweb)
	{
		newweb->page->setWebChannel(m_WebChannel.get());
		QString url = newweb->url().toString();
		QString title = newweb->title() == "" ? QString::fromLocal8Bit("untitle") : newweb->title();
		m_pTableWidget->addTab(newweb, title);
		connect(newweb, SIGNAL(signalSerNewWebView(AppWebView*)), this, SLOT(onSerNewWebView(AppWebView*)));
		connect(newweb, SIGNAL(signaldownloadRequested(QWebEngineDownloadItem*)), this, SLOT(onSerdownloadJump(QWebEngineDownloadItem *)));

		Count++;
		m_pTableWidget->setCurrentIndex(Count);
	}

	QString Workbench::GetConfigContent()
	{
		QString systemdbPath = QCoreApplication::applicationDirPath() + QString::fromLocal8Bit("/ZXConfig.ini");	
		if (UIUtils::IsFileExist(systemdbPath))
		{
			QSettings settings(systemdbPath, QSettings::IniFormat);
			return settings.value("addr/url").toString();
		}
		else
		{
			return "";
		}
	}

	void Workbench::onOpenLink(QString url)
	{
		url = GetConfigContent();
		AddLog(LOG_LEV_INFO, "onOpenLink url:%s", url.toLocal8Bit().data());
		//url = "http://www.baidu.com";
		if (url != "")
		{
			if (url[0] =='#')
			{
				url.replace("#", "");
				m_pWebView->load(QUrl(url));
			}
			else
			{
				QString Encryptstr = GetVerifyRes();
				url = url + "key=" + Encryptstr;
				m_pWebView->load(QUrl(url));
			}
		}
		else
		{
			m_pStack->setCurrentWidget(m_widgettip.get());
		}
	}

	void Workbench::onSerOpenChatWidget(int64 targetid)
	{
		emit signalSerOpenChatWidget(targetid);
	}

	QString Workbench::GetVerifyRes()
	{
		Json::Value root;
		Json::FastWriter fastwrite;

		QString EncryptResult("");	
		char randstr[10] = {0};
		utils::getrandstr(9, randstr);
		
		root["key"] = randstr + std::string("||ABC");
		root["user"] = gaccount;
		std::string json = fastwrite.write(root);

		std::string key = "16BytesLengthKey";
		UINT8 VI[] = "Z-zhengX-xie-Key";
		std::string EncryptResultStr = utils::encrypt(key, json, VI);
		return QString::fromStdString(EncryptResultStr);
	}

	void Workbench::onSerdownloadJump(QWebEngineDownloadItem *softdownload)
	{
		int32 id = softdownload->id();
		qint64 totalSize = softdownload->totalBytes();
		if (!m_DownFileWidget->FileIdIsExit(id))
		{
			QUrl url = softdownload->url();
			QString DefaultName = UIUtils::GetNameByUrl(url.toString()).toUtf8();
			QString filepath = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("ÏÂÔØ"), DefaultName);
			if (filepath.isEmpty())
			{
				return;
			}
			m_DownFileWidget->SetData(DefaultName, id, filepath, softdownload->totalBytes());
			m_DownFileWidget->show();
		}
	
		softdownload->setPath(m_DownFileWidget->GetFilePath(id));
		softdownload->accept();
		if (softdownload->isFinished())
		{
			//onSerDownFileFinish(softdownload->id());
			//emit signalSerDownFileFinish(softdownload->id());
		}

		connect(softdownload, SIGNAL(downloadProgress(qint64, qint64)), m_DownFileWidget->GetItemWidget(softdownload->id()), SIGNAL(signalSersetProgress(qint64, qint64)));
	}

	void Workbench::removeSubTab(int index)
	{
		m_pTableWidget->removeTab(index);
		AppWebView* appwebview = (AppWebView*)m_pTableWidget->widget(index);
		if (appwebview != CNull)
		{
			delete appwebview;
			appwebview = CNull;
		}
		Count--;
	}

	void Workbench::onSerDownFileFinish(int32 id)
	{
		m_DownFileWidget->EraserMap(id);
	}

	void Workbench::onSerTabClicked(int index)
	{
		m_pWebView->reload();
	}

}
