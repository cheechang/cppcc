#include "ContactWidgetWeb.h"
#include "common/controlptr.h"
#include "../enterprise/EnterpriseWidget.h"
#include "../controls/DefaultWidget.h"
#include "../enterprise/enterpriseinfowidget.h"
#include "ContactTabWidgetAreaWeb.h"
#include "group/GroupInforWidget.h"
#include "friend/FriendInfoWidgetWeb.h"
#include "friend/AppInfoWidget.h"
#include "friend/EnterpriseAccountList.h"
#include "friend/AppAccountList.h"
#include "friend/FriendListWidgetWeb.h"
#include "searchcontact/SearchContactWindow.h"
#include "createGroup/CreateGroupWindow.h"
#include <QHBoxLayout>
#include <QSize>
#include <QResizeEvent>
#include <qsettings>
#include  "controls/PushButton.h"
#include "common/Common.h"
#include "QtWebEngineWidgets\qwebenginesettings.h"
#include <qmessagebox.h>
#include <QtWebEngineWidgets\QWebEngineDownloadItem.h>
#include "controls/UserInfoCommon.h"
#include "controls/UserInfoCommitee.h"
#include "utils/common.h"
#include <log.h>
#include <QTextCodec>
#include "../mainwindow/contact/searchcontact/AddContactWindow.h"
#include <QDesktopServices>
#include <QUrl>

int g_webRunning = 0;
extern bool my_question(QString buttonYesText, QString buttonNoText, QString title, QString content);
const QString HttpUserAgent_H5 = QString("Toon-pc/1.0.0 windows,android,iphone,ipad");
ui::WebDlg*gWebdlg = CNull;
namespace ui{
	
		WebDlg::WebDlg(QWidget *parent) : QDialog(parent){
			this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
			this->setMinimumSize(800, 600);
			init();
		}
		WebDlg::~WebDlg(){	}
		void WebDlg::init(){
			QWebChannel *channel = new QWebChannel(this);
			channel->registerObject(QStringLiteral("cppObject"), this);
 			m_webView = new QWebEngineView(this);
			m_webView->setContextMenuPolicy(Qt::NoContextMenu); // 2019-8-22 屏蔽右键
			m_webView->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
			m_webView->page()->profile()->setHttpUserAgent(HttpUserAgent_H5);
			m_webView->page()->setWebChannel(channel);
			m_webView->setFixedSize(QSize(800,600));
		}
		void WebDlg::callQTProcess(const QString &taskid, const QString &text)
		{
			/////QMessageBox::information(this, "", text);
			QString str;
			str = text.section(':', 0, 0);   // str == "surname"

			if (str == QString::fromLocal8Bit("getAppList")){
		 		extern QString access_info;
				sendToWeb(taskid, access_info);
				return;
			}
			if (str == QString::fromLocal8Bit("getUserInfo")){
				extern QString login_info;
				emit  sendToWeb(taskid, login_info);
				return;
			}
			emit  sendToWeb(taskid, transfer("没有数据"));
			return;
		}

		void WebDlg::openUrl(QString urlpath)
		{
			m_webView->setUrl(QUrl(urlpath));
			m_webView->show();
			this->show();
		}
 
}

void OpenWebDlg(QString urlPath)
{
	if (gWebdlg == CNull){
		gWebdlg = new ui::WebDlg();
		gWebdlg->setFixedSize(800, 600);
	}
	gWebdlg->openUrl(urlPath);
	gWebdlg->showNormal();
	gWebdlg->activateWindow();
}

namespace ui{
	//网页窗口
	DefaultWidgetWeb::DefaultWidgetWeb(QWidget *parent){
		/////this->setMouseTracking(true);
		////m_webEngineView = CMakePtr<QWebEngineView>(this);  
		////setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
		m_webEngineView = NULL;
		m_bUsing = false;
		m_bFinished = true;
	}
	DefaultWidgetWeb::~DefaultWidgetWeb(){
		if (m_webEngineView) delete m_webEngineView;
	}
	/*void DefaultWidgetWeb::paintEvent(QPaintEvent *event)
	{
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	QPixmap pixmap(QString(":/base/default"));
	int x = SHADOW_WIDTH + (this->width() - pixmap.width()) / 2;
	int y = SHADOW_WIDTH + (this->height() - pixmap.height()) / 2;
	painter.drawPixmap(QRect(x, y, pixmap.width() - 2 * SHADOW_WIDTH, pixmap.height() - 2 * SHADOW_WIDTH), pixmap);
	}*/
	const QString HttpUserAgent_H5 = QString("Toon-pc/1.0.0 windows,android,iphone,ipad");
	void DefaultWidgetWeb::setUrl(data::Contact  contact, QPoint pos, CSharedPtr<QWebChannel> *Channel){

		if (!m_bFinished)  return; //如果没有浏览结束者不进入

		if (Channel == NULL)
		{
			if (m_webEngineView){
				m_webEngineView->setGeometry(0, 0, 0, 0);
				m_bUsing = false;
			}
			return;
		}
		m_bUsing = true;

		extern  QWidget *g_MainWidget;
		QWidget * mainWindow = g_MainWidget;
		if (!m_webEngineView && Channel){
			m_webEngineView = new QWebEngineView(mainWindow);
			m_webEngineView->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
			m_webEngineView->setContextMenuPolicy(Qt::NoContextMenu); //屏蔽右键  2019-8-22
			//m_webEngineView->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
			m_webEngineView->page()->setWebChannel(Channel->get());
			m_webEngineView->page()->profile()->setHttpUserAgent(HttpUserAgent_H5);
			connect(m_webEngineView, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));

			connect(m_webEngineView->page()->profile(), SIGNAL(downloadRequested(QWebEngineDownloadItem*)),
				this, SLOT(downloadRequested(QWebEngineDownloadItem*)));
			////connect(m_webEngineView, SIGNAL(downloadRequested(QWebEngineDownloadItem *)), this, SLOT(loadFinished(bool)));
		

		}
		if (m_webEngineView) {
			//m_webEngineView->setVisible(true);
			///m_webEngineView->setUrl(QUrl(QStringLiteral("https://www.baidu.com/")));
			QString url = QString::fromStdString(contact.server.value());
			m_bFinished = false;

			g_webRunning = 1;

 

			m_webEngineView->setUrl(QUrl(url));

			QPoint pos0 = ((QWidget *)(this->parent()))->pos();
			QPoint pos = ((QWidget *)(this->parent()->parent()))->pos();
			QPoint pos1 = this->pos();
			int x = pos.x() + pos1.x();
			int y = pos.y() + pos1.y();
			QRect  rect = this->rect();
			m_webEngineView->setGeometry(x, y, rect.width(), rect.height());
			/////*/
			////m_webEngineView->setGeometry(this->geometry());// pos.x() + rect.x(), pos.y() + rect.y(), rect.width(), rect.height());
			m_webEngineView->show();
		}

	}
	void DefaultWidgetWeb::loadFinished(bool flag)
	{
		//m_webEngineView->show();
		m_bFinished = true;
		g_webRunning = 0;
	}
	void DefaultWidgetWeb::resize()
	{
		if (!m_bUsing) return;
		QPoint pos0 = ((QWidget *)(this->parent()))->pos();
		QPoint pos = ((QWidget *)(this->parent()->parent()))->pos();
		QPoint pos1 = this->pos();
		int x = pos.x() + pos1.x();
		int y = pos.y() + pos1.y();
		QRect  rect = this->rect();
		m_webEngineView->setGeometry(x, y, rect.width(), rect.height());
		/////*/
		////m_webEngineView->setGeometry(this->geometry());// pos.x() + rect.x(), pos.y() + rect.y(), rect.width(), rect.height());
		m_webEngineView->show();
	}

	/*
	QString file_full, file_name, file_path，file_suffix; 
		QFileInfo fileinfo; file_full = QFileDialog::getOpenFileName(this, .....);
		fileinfo = QFileInfo(file_full);
		
		//文件名 
		file_name = fileinfo.fileName(); //文件后缀 
		file_suffix = fileinfo.suffix() //绝对路径 
		file_path = fileinfo.absolutePath();
		*/
	void DefaultWidgetWeb::downloadRequested(QWebEngineDownloadItem *download)
	{
		connect(download, SIGNAL(finished()), this, SLOT(downfinished()));
		connect(download, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(setCurrentProgress(qint64, qint64)));
		QString downFile = download->path();

	 
		QTextCodec *codec = QTextCodec::codecForName("gbk");
		QByteArray ba = codec->fromUnicode(downFile);
		ba = QByteArray::fromPercentEncoding(ba);
		downFile = codec->toUnicode(ba); // path = xxx – 3 xxx.
	 
		//////QMessageBox::warning(this, transfer("提示"), downFile);
		QString file_full, file_name, file_path,file_suffix;
		QFileInfo fileinfo; 

		fileinfo = QFileInfo(downFile);
		file_name = fileinfo.fileName();
		file_suffix = fileinfo.suffix();  

		QString fileName = QFileDialog::getSaveFileName(this,
			QString::fromLocal8Bit("文件另存为"),
			file_name,
			tr("*.")+file_suffix);
		if (fileName.isEmpty()){
			QMessageBox::warning(this, transfer("提示"), transfer("请选择保存的文件名"));
			return;
		}
		download->setPath(fileName);
		download->accept();

		QString info;
		info = fileName+transfer("  保存完成!");
		QMessageBox::warning(this, transfer("提示"), info);

		//////CopyFile(download->path().toStdString().c_str(), fileName.toStdString().c_str(),false);
 

  		/*if (download->savePageFormat() != QWebEngineDownloadItem::UnknownSaveFormat)  {
			qDebug() << "Format: " << download->savePageFormat();
			qDebug() << "Path: " << download->path();
			// If you want to modify something like the default path or the format
			download->setSavePageFormat(...);
			download->setPath(...);
			// Check your url to accept/reject the download
			download->accept();
		}*/
 	
	}

	void DefaultWidgetWeb::downloadFinished()
	{
		QString info;
		info = transfer("保存完成:");
		QMessageBox::warning(this, transfer("提示"), info);
	}
	
}

namespace ui{
	WebTitleWidget::WebTitleWidget(QWidget *parent){
		///setFixedSize(20, 20);
		setFixedHeight(64);
	}
	WebTitleWidget::~WebTitleWidget(){
		 
	}
};



namespace ui{
	ContactWidgetWeb::ContactWidgetWeb(QWidget *parent)
		: QWidget(parent)
		,m_ismax(false)
	{
		
		////bool flag = qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "3333");

		//////setMinimumWidth(RightContentWidth);
		m_mainLayout = CMakePtr<QHBoxLayout>();
		
		QFont font("Microsoft YaHei",14, 50);
		setFont(font);

		QVBoxLayout *left_layout = new QVBoxLayout();   //中心区域

		////left_layout->addLayout(initLocalSearchLayout());
		/////zleft_layout->addStretch();
		
	 	m_listWidget = CMakePtr<ui::FriendListWidgetWeb>(this);
		m_listWidget->Init_Home();
		m_listWidget->setFixedWidth(LeftContentWidth);
		m_listWidget->setObjectName("bg_fa_n");
		connect(m_listWidget.get(), SIGNAL(showContactInfoPage(data::Contact)), this, SLOT(onShowContactInfoPage(data::Contact)));


		m_listWidget_my = CMakePtr<ui::FriendListWidgetWeb>(this);
		m_listWidget_my->Init_MyInfo();
		m_listWidget_my->setFixedWidth(LeftContentWidth);
		m_listWidget_my->setObjectName("bg_fa_n");
		connect(m_listWidget_my.get(), SIGNAL(showContactInfoPage(data::Contact)), this, SLOT(onShowContactInfoPage(data::Contact)));

		

		left_layout->addWidget(m_listWidget.get());
		left_layout->addWidget(m_listWidget_my.get());
	    left_layout->setContentsMargins(0, 0, 1,0);
		m_listWidget->setVisible(false);

		
	 	m_defaultWidget = CMakePtr<ui::DefaultWidgetWeb>(this);
	


		m_mainLayout->addLayout(left_layout);// List 区域
		
		 
		QVBoxLayout *right_layout = new QVBoxLayout();
		right_layout->addWidget(m_defaultWidget.get());   //Web 区域

		m_defaultWidget->setContentsMargins(0, 0, 0, 0);

		right_layout->setContentsMargins(0, 0, 0, 0);

		m_mainLayout->addLayout(right_layout);
	 
		////// ＝＝＝＝＞channel  2019-3-22
		m_webchannel = CMakePtr<QWebChannel>(this);
		m_webchannel->registerObject(QStringLiteral("cppObject"), this);
		////// ＜＜＜＜＝＝＝＝　channel  2019-3-22


		/////QHBoxLayout  *contactLayout = new QHBoxLayout();
 
		m_mainLayout->setSpacing(0);
		m_mainLayout->setContentsMargins(0,0,0,0);
 
		this->setLayout(m_mainLayout.get());

		connect(this, SIGNAL(GetControlInfo(QString &text)), this, SLOT(onGetControlInfo(QString &text)));
		connect(this, SIGNAL(MySelectListItem(int item)), m_listWidget.get(), SLOT(onMySelectListItem(int item)));

		m_enterpriseAccountList = CMakePtr<EnterpriseAccountList>(this);
		/////m_enterpriseAccountList->setMinimumWidth(RightContentWidth);
		m_enterpriseAccountList->setVisible(false);


		mChatMgrControl = CHATMGRCONTROL;
		CONNECT_SERVICE(GetUserInfo(int, data::UserData&));
		CONNECT_SERVICE(ChatListNotify(int, std::vector<CSharedPtr<data::ChatData>>&));

	}

	ContactWidgetWeb::~ContactWidgetWeb()
	{

	}

	void ContactWidgetWeb::sendTextToCpp(const QString &text)
	{
		//onTurnPage(1);
		////onTurnPage(0);
		CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
		chat->chatType = data::GROUP_CHAT;
		chat->isStartChat = true;
		//chat->avatar = itemData.head;
		//chat->name = itemData.enName;
		//chat->targetid = itemData.userID;
		//chat->targetid = 21265121852;
	 
		chat->targetid = text.toLongLong();
		chat->name = "";
		emit startChat(chat);
	}
 
	void ContactWidgetWeb::callQTProcess(const QString &taskid,const QString &text)
	{
		m_TaskID = taskid;

		QString str;
		str = text.section(':', 0, 0);   // str == "surname"
		
		if (str == QString::fromLocal8Bit("getAppList")){
			/*QString res;
			QMap<int64, data::Contact> ::Iterator it = m_enterpriseAccountList->m_mapData.begin();
			while (it != m_enterpriseAccountList->m_mapData.end())
			{
				int64 appid = it.key();//"AA"
				res+=QString::number(appid, 10);
				
				data::Contact &c = (data::Contact)it.value();
				QString name = QString::fromUtf8(c.name.value().c_str());
				res += ":";
				res += name;
				res += "|";
  				it++;
			}
			emit  sendToWeb(m_TaskID,res);
			*/
			extern QString access_info;
			//// Log(LOG_LEV_DEBUG, LOG_FILE, access_info.toStdString().c_str());
			sendToWeb(m_TaskID, access_info);

			return;
 		} 

		if (str == QString::fromLocal8Bit("getAppInfo")){
			IUserControl_Ptr mUserControl;
			mUserControl = USERCONTROL;
			str = text.section(':',1,1);   // str == "surname"
			int64 appid = str.toLongLong();
			if (appid){
				m_AppInfo.clear();
				mUserControl->getAppInfo(appid, CBind(&ContactWidgetWeb::onGetAppInfo, this, CPlaceholders  _1, CPlaceholders  _2));
			}
			else {

				emit  sendToWeb(m_TaskID,m_AppInfo);
			}
			return;
		}
		if (str == QString::fromLocal8Bit("getUserInfo")){
 			/*IUserControl_Ptr mUserControl;
			mUserControl = USERCONTROL;
			CSharedPtr<data::AccountInfo> user = mUserControl->GetAccountInfo();
			QString info = QString::number(user->id.value(), 10);;
			info += ":";
			QString name = QString::fromStdString(user->name.value());
			info += name;
			*/
			extern QString login_info;
			////Log(LOG_LEV_DEBUG, LOG_FILE, login_info.toStdString().c_str());
			emit  sendToWeb(m_TaskID, login_info);
			return;
		}
		if (str == QString::fromLocal8Bit("loginOut")){
  			extern void LogLoginMode(QString mode);
			bool flag = my_question(transfer("是"), transfer("否"), transfer("提醒"), transfer("请求超时请重新登录."));
			if (flag == true){
				LogLoginMode("FRE_AUTO");  //设置下次为刷新自动登陆模式; 
			}
			else {
				LogLoginMode("MANUAL");  //设置下次为刷新手工登陆模式; 
			}
			UnClockProcess();
 			emit  loginOut(true);
			return;
		}
		if (str == QString::fromLocal8Bit("dispUser")){
			str = text.section(':', 1, 1);   // str == "surname"
			int64 userid = str.toLongLong();
			GetUserInfo(userid);
			return;
		}
		if (str == QString::fromLocal8Bit("addUserList")){     ///添加到联系人  2019-8-18
			str = text.section(':', 1, 1);   // str == "surname"
			int64 userid = str.toLongLong();
			data::SearchResultInfo info;
			info.targetid = userid;
			//info.name = m_pLabelName->text().toUtf8().data();
			//info.avatar = m_pAvatar->AvatarPath().toUtf8().data();
			info.resultType = data::USER_TYPE;
 			AddContactWindow *addContactWin = new AddContactWindow(this);
			addContactWin->InitData(info);
			addContactWin->show();
 			return;
		}
		if (str == QString::fromLocal8Bit("openUrl")){    // 2019-9-10

			//str = text.section(':', 1, 1);   // str == "url "
			str = text.section(':', 1);   // str == "url "
			////QMessageBox::warning(this, transfer("openUrl"), str );  //调试语句2019-9-18

			QDesktopServices::openUrl(QUrl(str));
			return ;
		}
		// unreadcount 2020-4-19
		///QMessageBox::information(this, "", str);
		if (str == QString::fromLocal8Bit("unreadcount")){ /// unread count
		 	m_GroupID = text.section(':', 1,1);

		/////	sendToWeb(m_TaskID,  m_GroupID+" "+"1") ;
			extern QStringList g_unreadcount;
			int cnt = g_unreadcount.size();
			QString info;
			for (int i = 0; i < cnt; i++) {
				QString tt = g_unreadcount.at(i);
				QString gid = tt.section(",", 0, 0);
				if (gid == m_GroupID) {
					sendToWeb(m_TaskID, m_GroupID + " " + tt.section(",",1, 1));
					return;
				} 
			}
			sendToWeb(m_TaskID, m_GroupID + " "+"-1");
			return;
		}

		if (str == QString::fromLocal8Bit("getAllGroupInfo")) { /// unread count
			m_GroupID = text.section(':', 1, 1);

			/////	sendToWeb(m_TaskID,  m_GroupID+" "+"1") ;
			extern QStringList g_unreadcount;
			int cnt = g_unreadcount.size();
			QString info;
			for (int i = 0; i < cnt; i++) {
				info += g_unreadcount.at(i);
				info += "|";
			}
			sendToWeb(m_TaskID, info);
			///mChatMgrControl->RegChatListNotify(CBind(&ContactWidgetWeb::signalSerChatListNotify, this, CPlaceholders  _1,
				////CPlaceholders  _2));
			return;
		}
  		emit  sendToWeb(m_TaskID,transfer("没有数据"));
	}

	void ContactWidgetWeb ::onSerChatListNotify(int flags, std::vector<CSharedPtr<data::ChatData>>&dataList)
	{
		QMessageBox::information(this, "", "abc");
		typedef CSharedPtr<data::ChatData> DataPtr;
	 	int unreadcount = 0;
		int size = dataList.size();
		DataPtr data_1;
		for (int i = size - 1; i >= 0; --i) {
			DataPtr data = dataList.at(i);
			unreadcount+= data->unReadCnt;
		}
		QString info;
		info = "Groutp::" + m_GroupID;
		QMessageBox::information(this, "", info);
		emit  sendToWeb(m_TaskID, info);
	}

	void ContactWidgetWeb::UnClockProcess()
	{
		BEGIN;
		//取消登陆，取消锁
#ifdef _WIN32
		utils::is_same_account_ReleaseMutex();
#else
		SingleApplication *single = SingleApplication::getInstance();
		single->detachApplication();
#endif // _WIN32
		END;
	}
 
	void ContactWidgetWeb::OnGetControlInfo(const QString &text)
	{
		emit  sendToWeb(m_TaskID,text);
	}
	void ContactWidgetWeb::onGetAppInfo(int64 code, data:: EntAppinfo& app)
	{
	 	QString res;
		res = QString::number(app.appID, 10);
	 	QString token  = QString::fromStdString(app.appToken);
		res += ":";
		res += token;
		m_AppInfo = res;
		emit GetControlInfo(m_AppInfo);

	/*	if (res ==QString("")){
			emit  sendToWeb(transfer("没有数据"));
		}
		else {
			emit  sendToWeb(res);
		}
		*/
	 
	}

	void ContactWidgetWeb::HideWeb()
	{
		QPoint pos;
		data::Contact  aa;
		m_defaultWidget->setUrl(aa, pos, NULL);

	}

	void ContactWidgetWeb::slotAdjustWebWindow(int action)
	{
		if (m_curApp == APP_PAGE)
		{
			m_listWidget->setVisible((action)?true:false);
			return;
		}
		else
		{
			m_listWidget_my->setVisible((action) ? true : false);
			return;
		}
	}
	void ContactWidgetWeb::onTurnPage(int i)
	{

		QPoint pos;
		data::Contact  aa;
		m_curApp = i;
		if (i != APP_PAGE && i != WORKBENCH_PAGE){
			// 切换的时候 处理Web网页
			m_defaultWidget->setUrl(aa, pos, NULL);
		}
		else {
			if (i == APP_PAGE){
				m_listWidget->setVisible(true);
				m_listWidget_my->setVisible(false);
				m_Pos = this->pos();
				aa.server = m_listWidget->m_homeurl.toStdString();
				onShowContactInfoPage(aa);
				m_listWidget->mListWidget->setCurrentRow(0);

				///HideWeb();

 			}
			else {
				m_listWidget->setVisible(false);
				m_listWidget_my->setVisible(true);
				m_Pos = this->pos();
				//aa.server = m_listWidget_my->m_homeurl.toStdString();
				aa.server = m_listWidget_my->m_homeurl.toStdString();
				onShowContactInfoPage(aa);
				m_listWidget_my->mListWidget->setCurrentRow(0);
 			}
		////emit  MySelectListItem(1);
		}
	}/*
	void ContactWidgetWeb::onShowOrgUserInfoPage(data::OrgAndUserInfo user)
	{
		m_contactInfoWidget->setVisible(false);
		m_defaultWidget->setVisible(false);
		
		m_enterpriseInfoWidget->setVisible(true);
		m_groupInforWidget->setVisible(false);
		m_appInfoWidget->setVisible(false);
		m_enterpriseAccountList->setVisible(false);
		m_appAccountList->setVisible(false);
		m_enterpriseInfoWidget->updateData(user);
		
	}*/
	/* 
	void ContactWidgetWeb::onShowGroupInforPage(int64 groupId)
	{
		if(groupId == 0){
			m_defaultWidget->setVisible(true);
			m_contactInfoWidget->setVisible(false);
	 		m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(false);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(false);
			m_appAccountList->setVisible(false);
	 		}else{
			m_defaultWidget->setVisible(false);
			m_contactInfoWidget->setVisible(false);
	 			m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(true);
			m_groupInforWidget->updateData(groupId);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(false);
			m_appAccountList->setVisible(false);
	 		}
	}
	*/
	
	void ContactWidgetWeb::resizeEvent(QResizeEvent *e)
	{
		///m_btnAddContact->move(m_leftTabWidgetArea->size().width()- m_btnAddContact->width()-20,
		////		m_leftTabWidgetArea->size().height()- m_btnAddContact->height()-20);
	    m_defaultWidget->resize();
		QWidget::resizeEvent(e);
	}
/*
	void ContactWidgetWeb::onBtnAddClicked()
	{
		QPoint pos(m_btnAddContact->x()-m_menuMain->width(),m_btnAddContact->y());
		pos = mapToGlobal(pos);
		m_menuMain->exec(pos);
	}

	void ContactWidgetWeb::onBtnCreateGroup()
	{
		mWinCreateGroup->showWin();
	}

	void ContactWidgetWeb::onBtnAddFrindOrGroup()
	{
		m_searchContactWin = CMakePtr<SearchContactWindow>();
		m_searchContactWin->show();
	}
	*/
	void ContactWidgetWeb::onShowContactInfoPage(data::Contact contact)
	{
		//m_defaultWidget->setVisible(true);
		m_defaultWidget->setUrl(contact, m_Pos, &m_webchannel);

		/*m_enterpriseInfoWidget->setVisible(false);
		m_groupInforWidget->setVisible(false);
		m_contactInfoWidget->setVisible(true);
		m_appInfoWidget->setVisible(false);
		m_enterpriseAccountList->setVisible(false);
		m_appAccountList->setVisible(false);
		//m_contactInfoWidget->updateData(contact);
		m_contactInfoWidget->setVisible(false);
		*/
	}

	void ContactWidgetWeb::GetUserInfo(int64 UserID)
	{
		mChatMgrControl->getUserInfo(UserID, 0, CBind(&ContactWidgetWeb::signalSerGetUserInfo, this, std::placeholders::_1, std::placeholders::_2));

	}

	void ContactWidgetWeb::onSerGetUserInfo(int code, data::UserData& data)
	{
		std::string type("");
		std::string jsonstr = data.entExtends.value();
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(jsonstr, root);
		if (ret)
		{
			if (root.isArray())
			{
				if (root[0]["type"].isString())
				{
					type = root[0]["type"].asString();
				}
			}
		}

 
		int64 id = data.id.value();
		QString name = QString::fromStdString(data.name.value());
		QString avatar = QString::fromStdString(data.avatar.value());
		std::string UserInfoExtend = data.entExtends.value();
		std::string Usertype = type;

		if (Usertype == "1")
		{
			m_pUserInfoCommomWidget = CMakePtr<UserInfoCommon>(this);
			connect(m_pUserInfoCommomWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommomWidget->setInfo(id, name, avatar, UserInfoExtend);
			m_pUserInfoCommomWidget->show(this->pos());
		}

		if (Usertype == "0")
		{
			m_pUserInfoCommiteeWidget = CMakePtr<UserInfoCommitee>(this);
			connect(m_pUserInfoCommiteeWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommiteeWidget->setInfo(id, name, avatar, UserInfoExtend);
			m_pUserInfoCommiteeWidget->show(this->pos());
		}
	}
	/* 
	void ContactWidgetWeb::onShowAddContactOrCreateGroup(int type)
	{
		if (type == 1)
		{
			onBtnAddFrindOrGroup();
		}else{
			onBtnCreateGroup();
		}
	}
	*/


	QHBoxLayout  *ContactWidgetWeb::initLocalSearchLayout()
	{
		QHBoxLayout *search_layout = new QHBoxLayout(this);
	
		QPushButton *mBtnLocalSearch = new QPushButton(this);
		mBtnLocalSearch->setObjectName("localsearchbtn");

		mBtnLocalSearch->setStyleSheet("background:rgb(228,228,228)");
 
		PushButton *m_searchBtnLogo = new PushButton(mBtnLocalSearch);
		m_searchBtnLogo->setPicName(":/title/search");
		mBtnLocalSearch->setFixedWidth(LeftContentWidth - 60);
		search_layout->addWidget(mBtnLocalSearch);
		search_layout->addWidget(m_searchBtnLogo);
		mBtnLocalSearch->setToolTip(transfer("搜索联系人、组织成员和群"));
		connect(mBtnLocalSearch, SIGNAL(clicked(bool)), this, SLOT(onSearchBtnClicked()));
		search_layout->setContentsMargins(5, 25, 5,10);
		return search_layout;
		///mBtnLocalSearch->move(80,24);
		/*mBtnLocalSearch->move(100, 18);
		mSearchBackground = new QWidget(this);
		mSearchBackground->setFixedSize(QSize(240, 55));
		///mSearchBackground->setStyleSheet("background:rgb(19,52,83)");
		///mSearchBackground->setStyleSheet("background:rgb(39,104,194)");
		mSearchBackground->setStyleSheet("background:rgb(28,28,28");
		mSearchBackground->move(78, 2);

		mLocalSearchLineEdit = new LocalSearchLineEdit(mSearchBackground);
		mSearchBackground->setVisible(false);
		mLocalSearchLineEdit->move(0, 15);
		mLocalSearchLineEdit->setFixedSize(QSize(220, 28));
		mLocalSearchLineEdit->setStyleSheet("background:white;border-radius:14px;");
		connect(mLocalSearchLineEdit, SIGNAL(clearBtnClicked()), this, SLOT(onShowAvatar()));
		connect(mLocalSearchLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onSearchTextChanged(const QString&)));
		*/
	}
	void ContactWidgetWeb::onMaxWiget()
	{
		m_ismax = !m_ismax;
		if (m_ismax)
		{
			m_max_button->setPicName(QString(":/title/restore"));
		}
		else{
			m_max_button->setPicName(QString(":/title/max"));
		}
		//m_max_button->setFixedHeight(30);
		emit maxWiget();
	}

	void ContactWidgetWeb::onSearchWeb()
	{
		QPoint pos;
		data::Contact  aa;
 		m_Pos = this->pos();
 		aa.server = m_listWidget->m_WebSearchUrl.toStdString();
		onShowContactInfoPage(aa);
	}

}