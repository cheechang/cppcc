#include "FriendListWidgetWeb.h"
#include "common/Connect.h"
#include "FriendListWidgetItem.h"
#include "ModifyFriendRemarkWindow.h"
#include "common/Common.h"
#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>
#include "common/UIUtils.h"
#include "log.h"
#include <QSettings>
#include "GroupListItemWidgetWeb.h"
#include "json.h"
extern QString g_WebServerIP;
extern QString g_access_token;
namespace ui{
	QString GetConfigContent(QString key)
	{
		QString systemdbPath = QCoreApplication::applicationDirPath() +"/rxdebug.ini";
		if (UIUtils::IsFileExist(systemdbPath))
		{
			QSettings settings(systemdbPath, QSettings::IniFormat);
			return settings.value(key).toString();
		}
		else
		{
			return "";
		}
	}
	void FriendListWidgetWeb::getAppSortInfo(void)
	{
		m_AppSortManager = new QNetworkAccessManager(this);
		m_AppSortRrequest = new QNetworkRequest();
		
		// Authorization=Bearer TOKEN 

	 	QString url = "http://" + g_WebServerIP + "/cppcc-management/api/appWeight/order";
		connect(m_AppSortManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAppSortRsp(QNetworkReply*)));
		////QMessageBox::information(this, "", QUrl(url).toEncoded());
		m_AppSortRrequest->setUrl(QUrl(url));
		m_AppSortManager->get(*m_AppSortRrequest);
	}



	void FriendListWidgetWeb::onAppSortRsp(QNetworkReply* preplay)
	{
		///	if (preplay->error() == QNetworkReply::NoError)
		{

			QByteArray bytes = preplay->readAll();
			QString RepContent(bytes);
        	///QMessageBox::information(this, "", RepContent);
			m_AppSortInfo = RepContent;
			Init_Sort_Home();
			return;
			std::string ExtendInfoJson = RepContent.toStdString();
			Json::Reader reader;
			Json::Value root, data;
			bool ret = reader.parse(ExtendInfoJson, root);
			data = root["data"];
			QString tel = QString::fromStdString(data["codeText"].asString());
			////m_telephone->setText(tel);

		}
	}

	/*{
	title: "联络联系", path : "Connect",
	title : "主题议政", path : "Meeting",
	title : "通知公告", path : "Notice",
	title : "要闻动态", path : "News",
	title : "组群交流", path : "Exchange",
	title : "委员学习", path : "Study",
	title : "提案提交", path : "SubPro",
	title : "履职报告", path : "DutyReport",
	title : "履职管理", path : "DutyAdmin",  *
	title : "文件材料", path : "Document",
	title : "履职风采", path : "Mien",
	title : "工作建议", path : "Advise",     *
	title : "建议反馈", path : "AdviseFeedback",
	title : "大会发言", path : "Speech",
	title : "社情民意", path : "Social",
	title : "建言资政", path : "Politics",    
	title : "值班日报", path : "LogBook",
	title : "查看建议", path : "SysAdvise",   *
	title : "会议请假", path : "Leave",       *


	txt : '我的履职', path : 'MyDuty'
	txt : '我的统计', path : 'Count'
	txt : '我的主题', path : 'MyMeeting'
	txt : '我的反馈', path : 'MyNotice'
	txt : '系统建议', path : 'SystemAdvice'
	}
	*/
	//获得图片名
	QString getthumbAvatar(QString code){
		const int TITLE_SIZE = 20;   // 2019-9-6
		static char *Title_Path[TITLE_SIZE] = {
			"Meeting", "Notice", "Study", "Politics", "SubPro",
			"Speech", "Social", "Document", "Connect",
			"Mien", "DutyReport", "Advise", "News", "Exchange", "AdviseFeedback", "LogBook","SysAdvise","Video70th","QuestionsAnswers","academyApp"};

		static char *thumbAvatar[TITLE_SIZE] = {
			"ztyz", "tzgg", "wyxx", "jyzz", "tatj",
			"dhfy", "sqmy", "wjcl", "lllx", "lzfc", "lzfc", "gzjy",
			"ywdt", "zqjl", "jyfk", "zbrb","gzjy","70th","jhdy","zxsy" };
		for (int i = 0; i < TITLE_SIZE; i++){
			if (QString(Title_Path[i]) == code){
				return QString(thumbAvatar[i]);
			}
		}
		return QString("");
 	}
	


	void FriendListWidgetWeb::Init_Sort_Home()
	{
	 
		QList <QString> code;
		QList <QString> name;
		{ //排序列表
			Json::Reader reader;
			Json::Value root, root1, approot;
			//QMessageBox::information(this, "APP 提示", m_AppSortInfo);  ///《====== 2019-9-18
			std::string ExtendInfoJson = m_AppSortInfo.toStdString();
			bool ret = reader.parse(ExtendInfoJson, root);
			root1 = root["data"];

			int size = root1.size();
			/////	QString aa;

			for (int i = 0; i < size; ++i)
			{
				approot = root1[i];
				code.append(QString::fromStdString(approot["functionCode"].asString()));
				name.append(QString::fromStdString(approot["functionName"].asString()));
			}
		}

		QList <QString> accesslist;

		{  //权限列表
			extern QString access_info;
			Json::Reader reader;
			Json::Value root, root1, approot;
		      	//QMessageBox::information(this, "权限列表", access_info);  ///《====== 2019-9-18
			std::string ExtendInfoJson = access_info.toStdString();
			bool ret = reader.parse(ExtendInfoJson, root);
			root1 = root["authorities"];

			approot = root1[0]["app"];
			int size = approot.size();
			/////	QString aa;

			for (int i = 0; i < size; ++i)
			{
				accesslist.append(QString::fromStdString(approot[i].asString()));
			}
		}

  		m_MyInfoMode = 0;
	 	int id = 1;
 
		/////QString url_path = QCoreApplication::applicationDirPath() + "/dist/index.html?window=home&path=";
		QString curdate = QDateTime::currentDateTime().toString("yyyyMMdd");
		QString url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=home&temp="+curdate+"&path=";   /// 2019-8-21  1
		///QString url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=home&path=";

		/*QString path = GetConfigContent("addr/path");
		if (!path.isEmpty()){
			url_path = path + "?window=home&path=";
		}
		*/



		
 		m_WebSearchUrl = url_path + "Search";
		m_homeurl      = url_path + "First";

		int appsize = code.size();


		if (appsize==0) {
			AddLog(LOG_LEV_INFO, LOG_FILE, "Get App Order ListInfo Error ..... ");
		}
		data::Contact data;
		
		
		if(0){///2019-9-6 
			QString addurl = url_path + "Video70th";
			QString av = QString(":/my/70th");
			{
				data.name = transfer("70周年").toUtf8().data();
				data.thumbAvatar = av.toStdString();
				data.server = addurl.toStdString();
				data.id.value() = id;
				addItemToList(data, 0);
				id++;
			}
		}
		
		for (int i = 0; i < appsize; i++){
			int cnt = accesslist.size();
			for (int kk = 0; kk < cnt; kk++){
				if (accesslist[kk] == code[i]){
					QString ava = getthumbAvatar(code[i]);
					if (ava == "") continue;
					QString av = QString(":/web/") + ava;
					data.thumbAvatar = av.toStdString();
					data.name = name[i].toUtf8().data();
					QString url = url_path + code[i];
					if (url == ""){
						url = "about:blank";
					}
					data.server = url.toStdString();
					data.id.value() = id;
					addItemToList(data, 1);
					id++;
					break;
				}
			}
		}
	}
	void FriendListWidgetWeb::Init_Home()
	{
		/*	QString url_path_ext = QCoreApplication::applicationDirPath() + "/dist/index.html?window=home&path=";
			QString path_ext = GetConfigContent("addr/path");
			if (!path_ext.isEmpty()){
				url_path_ext = path_ext + "?window=home&path=";
			}
	*/
		QString curdate = QDateTime::currentDateTime().toString("yyyyMMdd");
		QString url_path_ext = "http://" + g_WebServerIP + "/pcdist/index.html?window=home&temp=" + curdate + "&path=";  ///2019-8-21 2
		//// QString url_path_ext = "http://" + g_WebServerIP + "/pcdist/index.html?window=home&path=";

		m_WebSearchUrl = url_path_ext + "Search";
		m_homeurl = url_path_ext + "First";


		getAppSortInfo();  //获得排序信息且初始化菜单

		return;
	}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////
		
		

	
	void FriendListWidgetWeb::Init_MyInfo()
	{

		extern QString access_info;
		Json::Reader reader;
		Json::Value root, root1, approot;
		/////	QMessageBox::information(this, "提示", access_info);
		std::string ExtendInfoJson = access_info.toStdString();
		bool ret = reader.parse(ExtendInfoJson, root);
		root1 = root["authorities"];

		approot = root1[0]["app"];
		int size = approot.size();
		/////	QString aa;
		QList <QString> list;
		for (int i = 0; i<size; ++i)
		{
			list.append(QString::fromStdString(approot[i].asString()));
		}


		m_MyInfoMode = 1;
		data::Contact data;
	/*	char *Title_Msg[9] = {
			"我的履职\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1",
			"我的统计\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1", 
			"我的主题\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1",
			"我的通知公告反馈\xA1\xA1\xA1\xA1",
			"我的首页图标大小设置",
		  "字体大小设置\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1",
			"新消息通知\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1", 
			  "系统设置\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1",
			  "系统建议\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1\xA1" };
			  */

		char *Title_Msg[10] = {
		"我的履职",
		"我的统计",
		"我的主题",
		"我的反馈",
		"解惑答疑",
		"首页设置",
		"字体设置",
		"消息通知",
		"系统设置",
		"系统建议" 
		};
		char *thumbAvatar[10] = {
				"wdlz", "wdtj", "wdzt", "wdfk","wdjhdy",
				"tbsz", "ztdx", "xxxtz", "xtsz", "xtjy" };
		char *Title_Path[10] = {
			"MyDuty", "Count", "MyMeeting", "MyNotice","MyDisabuse",
			0, 0, 0, 0, "SystemAdvice"
		};


 		int id = 1;
 

	                 QString curdate = QDateTime::currentDateTime().toString("yyyyMMdd");
		QString url_path_ext = "http://" + g_WebServerIP + "/pcdist/index.html?window=home&temp=" + curdate + "&path=";  /// 2019-8-21 2
		//// QString url_path_ext = "http://" + g_WebServerIP + "/pcdist/index.html?window=home&path=";
		m_WebSearchUrl = url_path_ext + "Search";

		QString url_path = "http://" + g_WebServerIP + "/pcdist/index.html?window=user&temp=" + curdate + "&path="; /// 2019-8-21 3
                             ////QString url_path = "http://" + g_WebServerIP  + "/pcdist/index.html?window=user&path=";
		m_homeurl = url_path + "MyDuty";


		for (int i = 0; i < 10; i++){
			int cnt = list.size();
			for (int kk = 0; kk < cnt; kk++){
				if (list.at(kk) == Title_Path[i]){
					QString av = QString(":/my/") + QString(thumbAvatar[i]);
					data.thumbAvatar = av.toStdString();
					data.name = transfer(Title_Msg[i]).toUtf8().data();
					/////QString url = GetConfigContent("addr/url" + QString::number(id));
					QString url;
					if (Title_Path[i] == 0){
						url = "about:blank";
					}
					else {
						url  = url_path + Title_Path[i];
					}
					data.server = url.toStdString();
					data.id.value() = id;
					addItemToList(data,0);
					id++;
					break;
				}
			}
		}
		{///2019-8-19
			QString bookurl = url_path + "Book";
			QString av = QString(":/my/bzsc");
			{
				data.name = transfer("使用手册").toUtf8().data();
				data.thumbAvatar = av.toStdString();
				data.server = bookurl.toStdString();
				data.id.value() = id;
				addItemToList(data, 0);
				id++;
			}
		}

		/*{///2019-9-6 
			QString addurl = url_path + "Video70th";
			QString av = QString(":/my/70th");
			{
				data.name = transfer("70周年").toUtf8().data();
				data.thumbAvatar = av.toStdString();
				data.server = addurl.toStdString();
				data.id.value() = id;
				addItemToList(data, 0);
				id++;
			}
		}*/


		if (0){
			/////QString av = GetConfigContent("my/rxtest");

			QString av = QCoreApplication::applicationDirPath() + "/testWeb.htm";
			{
				data.name = transfer("测试网页").toUtf8().data();
		 
				data.server = av.toStdString();
				data.id.value() = id;
				addItemToList(data, 0);
				id++;
			}
		}


	}

	FriendListWidgetWeb::FriendListWidgetWeb(QWidget *parent)
		: QWidget(parent)
	{
		/////mContactControl = CONTACTMGRCONTROL;
		m_usercontrol = USERCONTROL;
		mListWidget = new QListWidget(this);
		mListWidget->setObjectName("myList");

		
		///mListWidget->setObjectName("bg_fa");

		mainLayout = new QVBoxLayout(this);
		mainLayout->addWidget(mListWidget);
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(0, 0, 0, 0);
		
		///setObjectName("bg_fa");

		mListWidget->setSortingEnabled(false);
 
		connect(mListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
  
		muserinfo = m_usercontrol->GetAccountInfo();
 
 	}
 
	FriendListWidgetWeb::~FriendListWidgetWeb()
	{
 		clearList();
	}
 
	void FriendListWidgetWeb::clearList()
	{
		for (int i = 0; i < mListWidget->count();)
		{
			QListWidgetItem* item = mListWidget->item(i);
			QWidget* widget = mListWidget->itemWidget(item);
			mListWidget->removeItemWidget(item);
			if (item != CNull){
				delete item;
			}
			if (widget != CNull){
				delete widget;
			}
	 	}
		mMapData.clear();
	}

	int FriendListWidgetWeb::addItemToList(const data::Contact& data,bool bBigImage)
	{
		QListWidgetItem* item = new QListWidgetItem();
		GroupListItemWidgetWeb* widget = new GroupListItemWidgetWeb(this, 0, bBigImage);
		int64 id = data.id.value();
		widget->setId(id);
		QString head = transfer(data.thumbAvatar.value().c_str());
		if (head.isEmpty()){
			head = (1 == data.isApp.value() ? DEFAULT_APP : DEFAULT_AVATAR);
		}
		QString name = data.remark.value().empty() ? QString::fromUtf8(data.name.value().c_str()) : QString::fromUtf8(data.remark.value().c_str());
		widget->setData(head, name, data.isStar.value() == 1);
		 
		mListWidget->insertItem(id, item);
		//item->setSizeHint(QSize(60, 60));
		item->setSizeHint(QSize(80, 80));
		mListWidget->setItemWidget(item, widget);
		mMapData.insert(data.id.value(), data);
	
		return mListWidget->row(item);
	}

	void FriendListWidgetWeb::onItemClicked(QListWidgetItem*item)
	{
		GroupListItemWidgetWeb* widget = (GroupListItemWidgetWeb*)mListWidget->itemWidget(item);
		if (widget != CNull){
			emit showContactInfoPage(mMapData.value(widget->id()));
		}
	}

	void FriendListWidgetWeb::onMySelectItem(int itemid)
	{
		/////GroupListItemWidgetWeb* widget = (GroupListItemWidgetWeb*) mListWidget->takeItem(itemid);
		mListWidget->setCurrentRow(itemid);
		////////emit showContactInfoPage(mMapData.value(itemid));
	}
}