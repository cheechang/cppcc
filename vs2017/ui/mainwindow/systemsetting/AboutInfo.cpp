#include "AboutInfo.h"
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QPalette>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <utils/common.h>
#include "common/Common.h"
#include "json.h"
#include <QApplication>
#include <qdir.h>
#include "log.h"
#include "../../loginwindow/LoginWindow.h"
extern QString g_WebServerIP;
extern QString gUserDataPath;

extern QString CUR_UPDATE_VERSION;// "1.0.0"
extern QString APP_VERSION;

extern ui::MyUpdateWindow *mUpdateWindows;
extern void utf2gbk(QString &str, QByteArray &ch);
bool my_question(QString buttonYesText, QString buttonNoText, QString title, QString content)
{
	QMessageBox msg(QMessageBox::Question, title, content, QMessageBox::Yes | QMessageBox::No);
 	msg.setButtonText(QMessageBox::Yes, buttonYesText);
 	msg.setButtonText(QMessageBox::No, buttonNoText);
 	msg.exec();
 	if (msg.clickedButton() == msg.button(QMessageBox::Yes)) { 	return true;  }
	else{ 	return false; }
}
namespace ui{
	DownloadDialog::DownloadDialog(QWidget *parent)
		: QDialog(parent)
	{
		setFixedSize(300, 200);
		download_Btn = new QPushButton("download");
		stop_Btn = new QPushButton("stop");
		stop_Btn->hide();
		download_Btn->hide();
		progressBar = new QProgressBar;
		progressBar->hide();
		setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);  /// 2019-8-21 4  去掉问号

		layout = new QVBoxLayout();
		layout->addStretch(1);
		layout->addWidget(progressBar);
		layout->addStretch(1);
		layout->addWidget(download_Btn, 0, Qt::AlignBottom);
		layout->addWidget(stop_Btn, 0, Qt::AlignBottom);

		setLayout(layout);
		httpRequestAbort = false;
		connect(download_Btn, SIGNAL(clicked()), this, SLOT(httpDownload()));
		connect(stop_Btn, SIGNAL(clicked()), this, SLOT(stop()));
	}

	DownloadDialog::~DownloadDialog()
	{
	}
	void DownloadDialog::Download(QString url, QString localFile)
	{
		m_url = QUrl(url);
		m_localfile = localFile;
	}
 
	void  DownloadDialog::UrlDownload()
	{
		QFile::remove(m_localfile);
 		file = new QFile(m_localfile);
		file->open(QIODevice::WriteOnly);//只写方式打开文件  
		accessManager = new QNetworkAccessManager(this);
		request.setUrl(m_url);
		setWindowTitle(transfer("正在下载....."));
		///setWindowTitle(m_localfile);
		/******************设置http的header***********************/
		// request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");  
		// request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");  
		// request.setRawHeader("Content-Disposition","form-data;name='doc';filename='a.txt'");  
		//request.setHeader(QNetworkRequest::ContentLengthHeader,post_data.length());  

		request.setRawHeader("User-Agent", "CytoViewer 1.0");
		request.setHeader(QNetworkRequest::ContentTypeHeader, "application/CytoViewer");

		reply = accessManager->get(request);//通过发送数据，返回值保存在reply指针里.  
		connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));//finish为manager自带的信号，replyFinished是自定义的  
		connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));//download文件时进度  
		connect((QObject *)reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		progressBar->setValue(0);
		progressBar->show();
	}
	void DownloadDialog::httpDownload()
	{
		UrlDownload();
	}
 

/***************响应结束**************************/
	 void DownloadDialog::replyFinished(QNetworkReply *reply){
		 //获取响应的信息，状态码为200表示正常  
		 file->close();
		 QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
		 if (status_code == 301 || status_code == 302){
			 QList<QNetworkReply::RawHeaderPair> tmp = reply->rawHeaderPairs();
 			 for (int i = 0; i < tmp.size(); i++) {
				 QNetworkReply::RawHeaderPair pair = tmp[i];
				 QByteArray bytes  = pair.second;
				 QByteArray bytes0 = pair.first;
				 QString name,data;
				 name = QString::fromUtf8(bytes0);
				 data = QString::fromUtf8(bytes);
				 if (name == "Location"){
					 DownloadDialog *dl = new  DownloadDialog;
					 dl = new DownloadDialog();
					 dl->m_fileMD5 = m_fileMD5;
					 dl->Download(data, m_localfile);
					 dl->UrlDownload();
					 dl->show();
					 break;
				 }
			 }
			 reply->deleteLater();//要删除reply，但是不能在repyfinished里直接delete，要调用deletelater;  
			 hide();
			 return;
		 }
  
		 ////QByteArray bytes = reply->readAll();  //获取字节  
		 ////QString result(bytes);  //转化为字符串  
		 /////qDebug() << result;

		int  neterr = reply->error();
		 //无错误返回  
		 if (reply->error() == QNetworkReply::NoError)
		 {
			setWindowTitle(transfer("下载完成,正在更新....."));
			////// download_Btn->setText("success");
			///// QByteArray bytes = reply->readAll();  //获取字节  
			/// QString result(bytes);  //转化为字符串  
			////// qDebug() << result;
			 extern QString GetFileMD5(QString filePath);
			 QString rcv_md5 = GetFileMD5(m_localfile);
			 m_fileMD5.toUpper();
			 if (m_fileMD5 != "" ){
				 if (rcv_md5 != m_fileMD5) {
					 QString info;
					 info = transfer("下载文件，MD5 错误!") +"\n"+ m_fileMD5 + "\n" + rcv_md5;
					 QMessageBox::information(this, "", info);
					 AddLog(LOG_LEV_DEBUG, "*****************MD5 不一样, MD5:%s  rcv:%s *************", m_fileMD5,rcv_md5);
					 reply->deleteLater();//要删除reply，但是不能在repyfinished里直接delete，要调用deletelater;  
 					 hide();
					 return;
				 }
			 }
 
			 bool flag = my_question(transfer("更新"), transfer("取消"), transfer("更新系统"), transfer("下载更新数据完成,是否退出系统,继续进行安装..."));

			 if (flag == true) {
				 // Do something here
				 QString oldfile = m_localfile;
				 m_localfile.replace("._xe", ".exe");
			 	 QFile::remove(m_localfile);  
				 QFile::rename(oldfile, m_localfile);
				 
				 QString app_path = QCoreApplication::applicationDirPath();
				 QString runpath = "\""+app_path + "/update/run.bat\"  " + "\""+m_localfile+"\"";
		 


#ifdef _WIN32
				/* HINSTANCE hinstance = NULL; 
				 hinstance = ShellExecuteA(NULL, "open", "run.bat", m_localfile.toStdString().c_str(), runpath.toStdString().c_str(), SW_SHOW);
				 if ((int)(hinstance) > 32)
				 {
					 exit(0);
					 AddLog(LOG_LEV_DEBUG, "*****************repalce.exe start success!*************");
				 }
				 else
				 {
					 QMessageBox::information(this, "",transfer("启动安装程序失败!"));
					 AddLog(LOG_LEV_ERROR, "*****************repalce.exe start failed!,errorcode(%d)*************", (int)(hinstance));
				 }
				 */

 				 ///int ret = WinExec(runpath.toStdString().c_str(), SW_SHOW);
				 /////m_localfile.replace("/", "\\");
				 ///QMessageBox::information(this, "", runpath);
				
				 /////int ret = WinExec(runpath.toStdString().c_str(), SW_HIDE);

 				 QByteArray runpath_ch;
				 utf2gbk(runpath, runpath_ch);
				 int ret = WinExec(runpath_ch, SW_HIDE);  ///2019-9-5
				 if (ret > 31){
					 AddLog(LOG_LEV_DEBUG, "*****************/update/run.bat start success!*************");
					 exit(0);
				 }
				 else {
					 QMessageBox::information(this, "", transfer("启动安装程序失败!"));
					 AddLog(LOG_LEV_DEBUG, "*****************/update/run.bat start failed!!!,errorcode(%d)*************", ret);
				 }
#endif

			 }
		
		 }
		 else
		 {
			 //处理错误  
			 setWindowTitle(transfer("下载失败 ....."));
			 QMessageBox::information(this, "", transfer("错误代码:") +QString::number(neterr));
			 ////download_Btn->setText("failed");
		 }

		 reply->deleteLater();//要删除reply，但是不能在repyfinished里直接delete，要调用deletelater;  

		 hide();

	 }
/***********更新进度条*************/
	 void DownloadDialog::onDownloadProgress(qint64 bytesSent, qint64 bytesTotal)
	 {
		 progressBar->setMaximum(bytesTotal);
		 progressBar->setValue(bytesSent);
	 }
	 void DownloadDialog::onReadyRead(){
		 file->write(reply->readAll());
		 download_Btn->setText("downloading");
	 }
	 void DownloadDialog::stop(){
	 if (!httpRequestAbort)
	 {
		 reply->abort();//响应终止  
		 httpRequestAbort = true;
		 stop_Btn->setText("start");
	 }
	 else
		 {  
			 httpDownload();
			 httpRequestAbort = false;
			 stop_Btn->setText("stop");
	   }
	}
}


#include "../../loginwindow/LoginWindow.h"



namespace ui{

	AboutInfo::AboutInfo(QWidget* parent):TWidget(parent)
	{
        m_updateServer = UPDATECONTROL;
        m_userServer    = USERCONTROL;
        m_autherServer = AUTHCONTROL;

		setObjectName("groupinfobackground");
		InitWidgets();
	}


	AboutInfo::~AboutInfo(void)
	{
	}

	void AboutInfo::InitWidgets()
	{
		 m_labImage = CMakePtr<QLabel>(this);
		 m_labImage->setFixedSize(110,110);
		 m_labImage->setScaledContents(true);
		 m_labImage->setPixmap(QPixmap(":/base/linkdood"));

		 m_labName  = CMakePtr<QLabel>(this);
		 m_labName->setText(APP_NAME);
		 QFont font;
		 font.setPixelSize(22);
		 m_labName->setFont(font);
		 QPalette pe;
		 pe.setColor(QPalette::Text,QColor(58,46,184));
		 m_labName->setPalette(pe);

		 m_labName->setFixedSize(QSize(280,40));
		 m_labVersion = CMakePtr<QLabel>(this);

		 font.setPixelSize(16);
		 m_labVersion->setFont(font);
		 ///std::string retVer = utils::get_client_info(utils::CLIENTINFO_TYPE_VERSION);   //app 版本号
         ///std::string retSvn = utils::get_client_info(utils::CLIENTINFO_TYPE_SVNVER);  
         ///retVer = retVer + "." + retSvn;
		 //; // 
		 QString version;
		 version = QString::fromLocal8Bit("     版本号:  ") + APP_VERSION ;////+"("+CUR_UPDATE_VERSION + ")";// QS+"("tring::fromStdString(retVer.data());

 
		 m_labVersion->setText(version);
		 m_labVersion->setFixedSize(QSize(200,35));

         m_btnCkeckUp = CMakePtr<QPushButton>(this);
         m_btnCkeckUp->setFixedSize(QSize(150,28));
         connect(m_btnCkeckUp.get(),SIGNAL(clicked()),this,SLOT(onBtnCheckUpClicked()));
         m_btnCkeckUp->setObjectName("sendbtn");
         m_btnCkeckUp->setText(transfer("检测更新"));

		 m_mainLayout = CMakePtr<QVBoxLayout>(this);
		 m_mainLayout->addWidget(m_labImage.get(),0,Qt::AlignCenter);
		 m_mainLayout->addWidget(m_labName.get(),0,Qt::AlignCenter);
		 m_mainLayout->addWidget(m_labVersion.get(),0,Qt::AlignCenter);
         m_mainLayout->addSpacing(10);
         m_mainLayout->addWidget(m_btnCkeckUp.get(),0,Qt::AlignCenter);
		 m_mainLayout->setSpacing(0);
		 m_mainLayout->setContentsMargins(20,20,20,20);
		 m_mainLayout->addStretch();
		 this->setLayout(m_mainLayout.get());


		 m_downloadDlg = new DownloadDialog(this);
	}

    void AboutInfo::onBtnCheckUpClicked()
    {
       /* int64 curentID = 0;
        int retValue = 0;
        std::string server = "";

        if (m_userServer)
        {
           CSharedPtr<data::AccountInfo> user = m_userServer->GetAccountInfo();
           curentID = user->id.value();
        }

        if (m_autherServer)
        {
            std::vector<data::AuthInfo> authVec;
            authVec = m_autherServer->getLoginInfos();
            for (int i =0; i< authVec.size(); ++i)
            {
                if (curentID == authVec.at(i).userId)
                {
                    server = authVec.at(i).server;
                    break;
                }
            }
        }

        if (m_updateServer)
        {
           retValue = m_updateServer->CheckUpdateOnline(server);
        }

        
        if (data::NONEED_UPDATE == retValue)
        {
            QMessageBox box(QMessageBox::Information,APP_NAME,transfer("当前已是最新版本"));
            box.exec();
        }
		*/

		///int ret = WinExec("C:\\Users\\lk\\AppData\\Local\\CPPCCP\\update\\run.bat   C:\\Users\\lk\\AppData\\Local\\CPPCCP\\update\\setup.exe", SW_SHOW);
	///	int ret = WinExec("C:\\Users\\lk\\AppData\\Local\\CPPCCP\\update\\setup.exe", SW_SHOW);
	///	QMessageBox::information(this, "", "ret= " + QString::number(ret));
	///	return;



		GetVersionInfo();
    }


	/*
	<JSONObject>
  <data>
    <explain>1.优化用户体验
2.修复已知bug</explain>
    <softwareId>2c90823b6ae8cbac016ae90751fa0007</softwareId>
    <forceUpdate>1</forceUpdate>
    <versionCode>1.0</versionCode>
  </data>
  <resultCode>200</resultCode>
  <resultMessage>success</resultMessage>
</JSONObject>
*/



	void AboutInfo::GetVersionInfo()
	{
		if (mUpdateWindows){
			mUpdateWindows->m_bShowCheckFlag = 1; 
			mUpdateWindows->GetVersionInfo();
		}

	/*	m_httpManager = new QNetworkAccessManager(this);
		m_httRrequest = new QNetworkRequest();

		connect(m_httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onSerUnicomRepResult(QNetworkReply*)));
 

		QString url = "http://" + g_WebServerIP+"/cppcc-management/api/getnewest/getrn";
		m_httRrequest->setUrl(QUrl(url));
		m_httpManager->get(*m_httRrequest);
		*/
	}
 
	void AboutInfo::onSerUnicomRepResult(QNetworkReply* preplay)
	{
		return;
		QByteArray bytes = preplay->readAll();
		QString RepContent(bytes);
		//////QMessageBox::information(this, transfer("提示"), RepContent);

		if (preplay->error() == QNetworkReply::NoError)
		{
			Json::Reader reader;
			Json::Value root, data;
			std::string ExtendInfoJson = RepContent.toStdString();
			bool ret = reader.parse(ExtendInfoJson, root);
			data = root["data"];
			QString  id = QString::fromStdString(data["softwareId"].asString());
			QString  ver = QString::fromStdString(data["versionCode"].asString());
			QString  info = QString::fromStdString(data["explain"].asString());

			QString outinfo = transfer("版本:   ") + ver +  transfer("\n更新内容:\n") + info + "\n\n";
			////QMessageBox::information(this, transfer("提示"), id);

			/*QMessageBox::StandardButton r = QMessageBox::question(this,
				transfer("更新系统"),
				outinfo.toUtf8(),
				QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
                        */
			bool flag = my_question(transfer("更新"), transfer("不更新"),transfer("更新系统"), outinfo.toUtf8());
			if (flag == true){ // QMessageBox::Yes){
				QString url = "http://" + g_WebServerIP + "/cppcc-management/api/show/file?id=" + id;
				QString path = gUserDataPath + "update/" + "setup.exe";
				QDir dir;
				dir.mkdir(gUserDataPath + "update/");
				m_downloadDlg->Download(url, path);
				m_downloadDlg->UrlDownload();
				m_downloadDlg->show();
			}
 		}
		else {
			 QMessageBox::information(this, transfer("提示"),transfer("下载更新信息失败!"));
		}
	}

	////
	////
	////
	void AboutInfo::DownloadPkg(QString v_id)
	{
		m_httpManager = new QNetworkAccessManager(this);
		m_httRrequest = new QNetworkRequest();

		connect(m_httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDownloadResult(QNetworkReply*)));
	 
		QString url = "http://" + g_WebServerIP + "/cppcc-management/api/show/file?id=" + v_id;
		m_httRrequest->setUrl(QUrl(url));
		reply = m_httpManager->get(*m_httRrequest);

		connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));//download文件时进度  
	}

	void AboutInfo::onDownloadResult(QNetworkReply* preplay)
	{
		////QMessageBox::information(this, transfer("提示"), RepContent);

		if (preplay->error() == QNetworkReply::NoError)
		{
			QByteArray bytes = preplay->readAll();
			preplay->size();
  		}
		else {
  
		}
	}
}
