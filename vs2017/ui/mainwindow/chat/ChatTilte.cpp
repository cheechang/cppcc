#include "ChatTilte.h"
#include "controls/ToolButton.h"
#include "../contact/searchcontact/AddContactWindow.h"
#include <QLabel>
#include <QLayout>
#include "../../common/Common.h"
#include <QSettings>
#include  "../contact/group/GroupInforWidget.h"
#include <QMessageBox>
#include <QMenu>
#include <QCoreApplication>
#include  <QDesktopServices>
#include <qsettings>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebChannel/qwebchannel.h>
#include "QtWebEngineWidgets/qwebenginesettings.h"
#include <QtWebEngineWidgets/QWebEngineDownloadItem.h>
#include <QtWebEngineWidgets/QWebEngineProfile>

#include <QtWebChannel/qwebchannel.h>
extern QString g_WebServerIP;
extern QString g_access_token;
extern QString g_Mac;
extern void OpenWebDlg(QString urlPath);

namespace ui
{
	ChatTitle::ChatTitle(QWidget* parent): QWidget(parent), m_title(CNull), m_spliter(CNull),
	                                       m_mainlayout(CNull)
	{
		mGroupControl = GROUPMGRCONTROL;
		m_title = CMakePtr<QLabel>(this);
		m_spliter = CMakePtr<QWidget>(this);

		m_title->setFixedHeight(60);//40（2020年10月10日）
		m_title->setContentsMargins(10, 0, 0, 30);//(10,0,0,0)(2020年10月10日）
		m_spliter->setFixedHeight(1);//（1）
		m_spliter->setObjectName("spliter");
		QFont font;
		font.setPixelSize(28); //2020-8-24font.setPixelSize(14);
		font.bold();
		m_title->setFont(font);

		m_btnAdd = CMakePtr<ToolButton>(":/group/add_group_mem", this, false);
		m_btnAdd->setToolTip(transfer("添加好友"));
		m_btnAdd->setVisible(false);
		connect(m_btnAdd.get(),SIGNAL(clicked()), this,SLOT(onAddContact()));

		m_btnDispGroup = CMakePtr<ToolButton>(":/group/group_info", this, false);
		m_btnDispGroup->setToolTip(transfer("群信息"));
		m_btnDispGroup->setContentsMargins(0, 0, 0, 0);
		///m_btnDispGroup->setFixedSize(40, 40);
		m_btnDispGroup->setVisible(true);
		m_btnDispGroup->setEnabled(true);
		connect(m_btnDispGroup.get(), SIGNAL(clicked()), this, SLOT(onShowMenu()));

		m_topmsgWidget = new QWidget(this);
		m_topmsgWidget->setMinimumWidth(150);
		m_topmsgWidget->setFixedHeight(40);

		/*	m_TopMsgTip = CMakePtr<QLabel>(m_topmsgWidget);
			m_TopMsgTip->setObjectName("UpFileTip");
			m_TopMsgTip->setText(transfer("最新"));
			m_TopMsgTip->setFont(font);*/

		m_newTopMsglblShow = CMakePtr<QLabel>(m_topmsgWidget);
		m_newTopMsglblShow->setFont(font);
		m_newTopMsglblShow->setObjectName("topContent");

		m_moreTopMsg = CMakePtr<QPushButton>(m_topmsgWidget);
		m_moreTopMsg->setFixedWidth(50);
		m_moreTopMsg->setText(transfer("更多"));
		m_moreTopMsg->setObjectName("moreMsgbtn");
		m_moreTopMsg->setFont(font);
		QHBoxLayout* topmsgLayout = new QHBoxLayout(m_topmsgWidget);
		topmsgLayout->setSpacing(0);
		//topmsgLayout->addWidget(m_TopMsgTip.get());
		topmsgLayout->addWidget(m_newTopMsglblShow.get());
		topmsgLayout->addWidget(m_moreTopMsg.get());
		topmsgLayout->setSpacing(5);
		topmsgLayout->setContentsMargins(20, 0, 20, 0);

		m_topmsgWidget->setLayout(topmsgLayout);

		QHBoxLayout* titlelayout = new QHBoxLayout;
		titlelayout->addWidget(m_title.get());
		//titlelayout->addLayout(topmsgLayout);
		//titlelayout->addWidget(m_newTopMsglblShow.get());
		titlelayout->addWidget(m_topmsgWidget);
		titlelayout->addStretch(1);
		titlelayout->addWidget(m_btnDispGroup.get());
		titlelayout->addWidget(m_btnAdd.get());
		titlelayout->addSpacing(10);

		//添加到布局
		m_mainlayout = CMakePtr<QVBoxLayout>(this);
		//m_mainlayout->addWidget(m_title.get());
		m_mainlayout->addLayout(titlelayout);
		m_mainlayout->addWidget(m_spliter.get());
		m_mainlayout->setContentsMargins(0, 0, 0, 0);
		m_mainlayout->setSpacing(5);

		setLayout(m_mainlayout.get());


		m_Menu = new QMenu(this);
		m_actionGounp = new QAction(this);
		m_actionGounp->setText(transfer("群信息"));
		m_Menu->addAction(m_actionGounp);
		m_actionDoc = new QAction(this);
		m_actionDoc->setText(transfer("参阅材料"));
		m_Menu->addAction(m_actionDoc);
		m_actionSpeech = new QAction(this);
		m_actionSpeech->setText(transfer("发言汇编"));
		m_Menu->addAction(m_actionSpeech);

		m_actionSpeechCount = new QAction(this);
		m_actionSpeechCount->setText(transfer("发言统计"));
		m_Menu->addAction(m_actionSpeechCount);
		m_actionSpeechSummary = new QAction(this);
		m_actionSpeechSummary->setText(transfer("发言综述"));
		m_Menu->addAction(m_actionSpeechSummary);


		m_actionReadingDoc = new QAction(this);
		m_actionReadingDoc->setText(transfer("参阅材料"));
		m_Menu->addAction(m_actionReadingDoc);

		m_actionEssenceArea = new QAction(this);
		m_actionEssenceArea->setText(transfer("精华区"));
		m_Menu->addAction(m_actionEssenceArea);


		connect(m_moreTopMsg.get(), SIGNAL(clicked()), this, SIGNAL(signalSerMoretopMsg()));
		connect(m_actionGounp, SIGNAL(triggered(bool)), this, SLOT(onDispGroup()));
		connect(m_actionDoc, SIGNAL(triggered(bool)), this, SLOT(onShowDoc()));
		connect(m_actionSpeech, SIGNAL(triggered(bool)), this, SLOT(onShowSpeech()));

		connect(m_actionSpeechCount, SIGNAL(triggered(bool)), this, SLOT(onShowSpeechCount()));
		connect(m_actionSpeechSummary, SIGNAL(triggered(bool)), this, SLOT(onShowSpeechSummary()));

		connect(m_actionReadingDoc, SIGNAL(triggered(bool)), this, SLOT(onShowReadingDoc())); // 2020-4-16
		connect(m_actionEssenceArea, SIGNAL(triggered(bool)), this, SLOT(onShowEssenceArea()));
	}

	ChatTitle::~ChatTitle()
	{
	}

	void ChatTitle::setTopMsgVisible(bool isVisible)
	{
		m_topmsgWidget->setVisible(isVisible);
	}

	const QString HttpUserAgent_H5 = QString("Toon-pc/1.0.0 windows,android,iphone,ipad");
	//applicationDirPath() + "/dist/index.html?window=speech&groupID=";
	/////window = speech&groupId = 发言 window = document&groupId = 文件材料

	void ChatTitle::onShowEssenceArea() /// 2020-4-16  读书群-精化区
	{
		QString url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=essenceArea&groupId=" +
			QString::number(m_curTargetInfo.targetId);
		/// QMessageBox::information(this, "", url_path);
		OpenWebDlg(url_path);
	}

	void ChatTitle::onShowReadingDoc() // 参阅材料
	{
		QString url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=readingDocument&groupId=" +
			QString::number(m_curTargetInfo.targetId);
		////  QMessageBox::information(this, "", url_path);
		OpenWebDlg(url_path);
	}


	void ChatTitle::onShowDoc()
	{
		QString url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=document&groupId=" + QString::number(
			m_curTargetInfo.targetId);

		OpenWebDlg(url_path);


		//////OpenWebDlg("E:/myWorkspace/html/testWeb.htm");
		return;

		QDialog* webdlg = new QDialog();
		webdlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

		/*	Qt::WindowFlags flags = Qt::Dialog;
			flags |= Qt::WindowMinMaxButtonsHint;
			flags |= Qt::WindowCloseButtonHint;
			webdlg->setWindowFlags(flags);
	*/
		webdlg->setMinimumSize(800, 600);

		QWebEngineView* m_webView = new QWebEngineView(webdlg);
		m_webView->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
		/////m_webView->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
		m_webView->page()->profile()->setHttpUserAgent(HttpUserAgent_H5);
		QWebChannel* m_webchannel = new QWebChannel;
		m_webView->page()->setWebChannel(m_webchannel);

		/////	QMessageBox::information(this, "", url_path);

		////m_webView->load(QUrl("https://www.baidu.com/"));
		m_webView->setUrl(QUrl(url_path));
		m_webView->show();
		webdlg->show();
		return;
	}

	void ChatTitle::onShowSpeechCount()
	{
		///QMessageBox::information(this, "", "onShowSpeechCount");
		QString url_path;
		if (!m_bBooking)
		{
			url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=speechcount&groupId=" +
				QString::number(m_curTargetInfo.targetId) + "&endTime=" + mLastSendTime;
		}
		else
		{
			// 读书群
			url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=readingSpeechcount&groupId=" +
				QString::number(m_curTargetInfo.targetId); // +"&endTime=" + mLastSendTime;
		}
		////QMessageBox::information(this, "", url_path);
		OpenWebDlg(url_path);
	}

	void ChatTitle::onShowSpeechSummary()
	{
		///QMessageBox::information(this, "", "onShowSpeechSummary");
		QString url_path;
		if (!m_bBooking)
		{
			url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=speechsketch&groupId=" +
				QString::number(m_curTargetInfo.targetId) + "&endTime=" + mLastSendTime;
		}
		else
		{
			// 读书群
			url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=readingSpeechsketch&groupId=" +
				QString::number(m_curTargetInfo.targetId); // +"&endTime=" + mLastSendTime;
		}
		///QMessageBox::information(this, "", url_path);
		OpenWebDlg(url_path);
	}

	void ChatTitle::onShowSpeech()
	{
		QString url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=speech&groupId=" + QString::number(
			m_curTargetInfo.targetId);

		OpenWebDlg(url_path);


		//////OpenWebDlg("E:/myWorkspace/html/testWeb.htm");
		return;

		QDialog* webdlg = new QDialog();

		QWebChannel* channel = new QWebChannel(this);
		channel->registerObject(QStringLiteral("cppObject"), this);

		webdlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
		webdlg->setMinimumSize(800, 600);

		QWebEngineView* m_webView = new QWebEngineView(webdlg);
		m_webView->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
		m_webView->page()->profile()->setHttpUserAgent(HttpUserAgent_H5);
		m_webView->setUrl(QUrl(url_path));
		m_webView->show();
		webdlg->show();
		return;
	}

	void ChatTitle::onDispGroup()
	{
		GroupInforWidgetDlg* giw = new GroupInforWidgetDlg(this);
		connect(giw,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this,
		        SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		giw->updateData(m_curTargetInfo.targetId);
		giw->setStartChatCLose(true);
		giw->show();
	}


	void ChatTitle::onShowMenu()
	{
		QPoint pos = QCursor::pos();
		///pos.setY(pos.y() - 40); 
		pos.setY(pos.y() + 10); //2020-4-20
		pos.setX(pos.x() - 20);
		m_Menu->exec(pos);
	}

	void ChatTitle::SetTitleText(QString& text, QString avatar)
	{
		QFont ft;
		QFontMetrics fm(ft);
		QString textformat = fm.elidedText(text, Qt::ElideRight, 500);
		m_title->setText(textformat);
		m_title->setToolTip(text);
		mAvatar = avatar;
	}

	void ChatTitle::SetTargetInfo(TargetInfo& tagetInfo)
	{
		m_curTargetInfo = tagetInfo;
		SetTitleText(tagetInfo.targetName, tagetInfo.targetAvatar);
		if (m_curTargetInfo.chattype == data::GROUP_CHAT)
		{
			m_btnDispGroup->setVisible(true);
		}
		else
		{
			m_btnDispGroup->setVisible(false);
		}

		data::Group infoGroup; ///<==== 根据群类型屏蔽菜单功能. 2019-8-31 
		mGroupControl->GetGroupInfo(m_curTargetInfo.targetId, infoGroup);
		QString type1;
		type1 = QString(infoGroup.info.value().groupType.value().data());
		//QMessageBox::information(this, "", type1);
		/*if (infoGroup.info.value().groupType.value() != "org"&&infoGroup.info.value().groupType.value() != "eid") {
			m_actionDoc->setVisible(false);
			m_actionSpeech->setVisible(false);
		};*/

		m_actionDoc->setVisible(false);
		m_actionSpeech->setVisible(false);

		m_actionSpeechCount->setVisible(false);
		m_actionSpeechSummary->setVisible(false);
		mLastSendTime = "0";
		m_bBooking = 0;

		m_actionReadingDoc->setVisible(false);
		m_actionEssenceArea->setVisible(false);

		/*if (infoGroup.info.value().groupType.value() != "eid") {
			return;
		}*/


		///<======
		//
		//   检查数据
		//
		m_httpManager = new QNetworkAccessManager(this);
		m_httpRequest = new QNetworkRequest();

		connect(m_httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onHttpInfoRsp(QNetworkReply*)));

		//QString url = "http://" + g_WebServerIP + "/cppcc-subjectdiscuss/api/summarize/enterGroup?groupId=" + QString::number(m_curTargetInfo.targetId);

		QString url = "http://" + g_WebServerIP + "/cppcc-questionnaire/api/summarize/enterGroup?groupId=" +
			QString::number(m_curTargetInfo.targetId);


		QString author = "Authorization=Bearer " + g_access_token + "&client_id=c++&deviceId=" + g_Mac +
			"&deviceModel=pc&deviceType=pc";
		url = url + "&" + author; // QUrl::toPercentEncoding(author);

		m_httpRequest->setUrl(QUrl(url)); //?token=" + g_access_token))
		m_httpManager->get(*m_httpRequest); // , Bytedata);

		////============= bookdiscuss  2020-4-16
		m_httpBookingManager = new QNetworkAccessManager(this);
		m_httpBookingRequest = new QNetworkRequest();

		connect(m_httpBookingManager, SIGNAL(finished(QNetworkReply*)), this,
		        SLOT(onHttpInfoBookingRsp(QNetworkReply*)));

		url = "http://" + g_WebServerIP + "/cppcc-questionnaire/api/bookDiscuss/isBook?groupId=" + QString::number(
			m_curTargetInfo.targetId);
		author = "Authorization=Bearer " + g_access_token + "&client_id=mrhcapp&deviceId=" + g_Mac +
			"&deviceModel=pc&deviceType=pc";
		url = url + "&" + author;
		////QMessageBox::information(this, "Error", url);
		m_httpBookingRequest->setUrl(QUrl(url)); //?token=" + g_access_token))
		m_httpBookingManager->get(*m_httpBookingRequest); // , Bytedata);


		///============= Speech 主题  2020-4-20
		m_httpSubjectManager = new QNetworkAccessManager(this);
		m_httpSubjectRequest = new QNetworkRequest();

		connect(m_httpSubjectManager, SIGNAL(finished(QNetworkReply*)), this,
		        SLOT(onHttpInfoSubjectRsp(QNetworkReply*)));

		url = "http://" + g_WebServerIP + "/cppcc-subjectdiscuss/api/subjectDiscuss/isSubject/" + QString::number(
			m_curTargetInfo.targetId);
		author = "?Authorization=Bearer " + g_access_token + "&client_id=mrhcapp&deviceId=" + g_Mac +
			"&deviceModel=pc&deviceType=pc";
		author += "&tid=a7e1ee6f40d6502fabf4878fa0ea2584&client_secret=98890563be65564991e223b6eadc5c0a";
		url = url + author;
		////QMessageBox::information(this, "Error", url);
		m_httpSubjectRequest->setUrl(QUrl(url)); //?token=" + g_access_token))
		m_httpSubjectManager->get(*m_httpSubjectRequest); // , Bytedata);
	}

	void ChatTitle::onHttpInfoSubjectRsp(QNetworkReply* preplay)
	{
		if (preplay->error() == QNetworkReply::NoError)
		{
			QByteArray bytes = preplay->readAll();
			QString RepContent(bytes);
			////QMessageBox::information(this, "onHttpInfoSubjectRsp", RepContent);
			Json::Reader reader;
			Json::Value root, data;
			std::string ExtendInfoJson = RepContent.toStdString();
			bool ret = reader.parse(ExtendInfoJson, root);
			data = root["data"];
			QString stats = QString::fromStdString(data.asString());
			//QMessageBox::information(this, "", stats+" "+ lastTime);
			if (stats == "1")
			{
				m_actionDoc->setVisible(true);
				m_actionSpeech->setVisible(true);
			}
		}
		else
		{
			////QMessageBox::information(this, "onHttpInfoSubjectRsp Error", preplay->readAll());
		}
	}

	void ChatTitle::onHttpInfoRsp(QNetworkReply* preplay)
	{
		if (preplay->error() == QNetworkReply::NoError)
		{
			QByteArray bytes = preplay->readAll();
			QString RepContent(bytes);
			///QMessageBox::information(this, "onHttpInfoRsp", RepContent);
			Json::Reader reader;
			Json::Value root, data;
			std::string ExtendInfoJson = RepContent.toStdString();
			bool ret = reader.parse(ExtendInfoJson, root);
			data = root["data"];
			QString stats = QString::fromStdString(data["houldPullStats"].asString());
			QString lastTime = QString::fromStdString(data["lastSendTime"].asString());
			//QMessageBox::information(this, "", stats+" "+ lastTime);
			if (stats == "true")
			{
				///m_bBooking = 0;
				m_actionSpeechCount->setVisible(true);
				m_actionSpeechSummary->setVisible(true);
				mLastSendTime = lastTime;
			}
		}
		else
		{
			/////QMessageBox::information(this, "Error onHttpInfoRsp", preplay->readAll());
		}
	}

	void ChatTitle::onHttpInfoBookingRsp(QNetworkReply* preplay)
	{
		if (preplay->error() == QNetworkReply::NoError)
		{
			QByteArray bytes = preplay->readAll();
			QString RepContent(bytes);
			////QMessageBox::information(this, "onHttpInfoBookingRsp", RepContent);
			Json::Reader reader;
			Json::Value root, data;
			std::string ExtendInfoJson = RepContent.toStdString();
			bool ret = reader.parse(ExtendInfoJson, root);
			QString type = QString::fromStdString(root["groupType"].asString());
			if (type == "book")
			{
				//m_actionGounp->setVisible(false);
				//m_actionDoc->setVisible(false);
				//m_actionSpeech->setVisible(false);
				///m_actionSpeechCount->setVisible(true);
				///m_actionSpeechSummary->setVisible(true);
				m_actionReadingDoc->setVisible(true);
				m_actionEssenceArea->setVisible(true);
				m_bBooking = 1;
			}
		}
		else
		{
			////QMessageBox::information(this, "ErrorBooking", preplay->readAll());
		}
	}

	void ChatTitle::paintEvent(QPaintEvent* event)
	{
		/*if (m_btnAdd && m_btnAdd->isVisible())
		{
			m_btnAdd->move(width()-m_btnAdd->width(),0);
		}
		*/
	}

	void ChatTitle::showAddBtn(int64 id, bool show)
	{
		mId = id;
		m_btnAdd->setVisible(show);
	}

	void ChatTitle::onAddContact()
	{
		data::SearchResultInfo info;
		info.targetid = mId;
		info.name = m_title->text().toUtf8().data();
		info.avatar = mAvatar.toUtf8().data();
		info.resultType = data::USER_TYPE;

		AddContactWindow addContactWin;
		addContactWin.InitData(info);
		addContactWin.exec();
	}

	void ChatTitle::onSerMsgTop(data::ZxTopInformation& topMsgInfo)
	{
		m_topmsgWidget->setVisible(true);
		data::Member meminfo;
		mGroupControl->GetMemberInfo(topMsgInfo.groupId, topMsgInfo.topUserId, meminfo);
		std::string name = meminfo.remark.value();
		if (name == "")
		{
			name = meminfo.name.value();
		}

		QString content = QString::fromUtf8(name.c_str()) + transfer("有新发言：") + topMsgInfo.topContent.c_str();
		QString showContent;
		int fontH = m_newTopMsglblShow->fontMetrics().height();
		int height = fontH;
		int width = m_newTopMsglblShow->fontMetrics().width(content);
		int maxWidth = 30;
		if (width > maxWidth)
		{
			showContent = content.mid(0, maxWidth);
			showContent += "...";
		}
		else
		{
			showContent = content;
		}

		m_newTopMsglblShow->setText(showContent);
	}

	void ChatTitle::setTopMsgContent(QString content)
	{
		QString showContent;
		int fontH = m_newTopMsglblShow->fontMetrics().height();
		int height = fontH;
		int width = m_newTopMsglblShow->fontMetrics().width(content);
		int maxWidth = 30;
		if (width > maxWidth)
		{
			showContent = content.mid(0, maxWidth);
			showContent += "...";
		}
		else
		{
			showContent = content;
		}
		m_newTopMsglblShow->setText(showContent);
	}
}
