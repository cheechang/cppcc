#include "CloudDiskWidget.h"
#include "Controls/TitleBar.h"
#include "Controls/DefaultWidget.h"
#include "LeftWidget.h"
#include "FileListWidget.h"
#include "Controls/TableWidgetItem.h"
#include "CloudDiskUploadWnd.h"
#include "AuthMemberSelWnd.h"
#include <qicon.h>
#include <QVBoxLayout>
#include <qstackedwidget.h>
#include <QCoreApplication>
#include <QTableWidgetItem>
#include "ProgressWindow.h"
#include "AuthMemberListWnd.h"
#include <interface/IService.h>
#include <interface/jsonToolExport.h>
#include <interface/jsonTransTool.h>
#include <QFileInfo>
//#include <QJsonObject>
//#include <QJsonDocument>
//#include <QJsonArray>

#include <json.h>
#include <QDebug>
#include <QStringList>
#include <QFileDialog>
#include <QMetaType>
#include <log.h>
#include "Controls/MyMessageBox.h"
namespace ui{
	CloudDiskWidget::CloudDiskWidget(QWidget *parent) :TWidget(parent), m_titleBar(nullptr),
    m_leftWidget(nullptr),
	m_defaultWidget(nullptr),
	m_myselfWidget(nullptr),
	m_sharedWidget(nullptr),
	m_rightWidget(nullptr),
	m_contentLayout(nullptr),
	m_mainLayout(nullptr),
	m_cloudservice(nullptr),
	m_progressTip(nullptr),
	m_extrareq(0),
	m_authMemberListWnd(nullptr),
	m_isFirstFlag(true)
	{
		//LOG_METHOD("CloudDiskWidget::CloudDiskWidget", LOG_FILE);
		resize(800, 600);
		setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint|Qt::WindowMaximizeButtonHint);

		m_titleBar = std::make_shared<TitleBar>();

		installEventFilter(m_titleBar.get());
		setWindowTitle(tr("云盘"));
		setWindowIcon(QIcon(":/img/logo"));

		m_leftWidget = std::make_shared<LeftWidget>(this);
		m_sharedWidget = std::make_shared<FileListWidget>(SHARED_FILE,this);
		m_myselfWidget = std::make_shared<FileListWidget>(SELF_FILE,this);
		m_rightWidget = std::make_shared<QStackedWidget>(this);
		m_defaultWidget = std::make_shared<DefaultWidget>(this);

		connect(m_leftWidget.get(), SIGNAL(singalSelfBtnClicked()), this, SLOT(onSelfBtnClicked()));
		connect(m_leftWidget.get(), SIGNAL(signalShareBtnClicked()), this, SLOT(onShareBtnClicked()));
		
		m_rightWidget->addWidget(m_myselfWidget.get());
		m_rightWidget->addWidget(m_sharedWidget.get());

		m_leftWidget->resize(200, 600);
		m_leftWidget->setMaximumWidth(200);
		m_defaultWidget->resize(620, 600);
	
		m_contentLayout = new QHBoxLayout();
		m_contentLayout->setSpacing(0);
		m_contentLayout->setContentsMargins(0, 0, 0, 0);
		m_contentLayout->setAlignment(Qt::AlignTop);
		m_contentLayout->addWidget(m_leftWidget.get());
		m_contentLayout->addWidget(m_rightWidget.get());

		m_mainLayout = new QVBoxLayout(this);
		m_mainLayout->setSpacing(0);
		m_mainLayout->setContentsMargins(0, 0, 0, 0);
		m_mainLayout->setAlignment(Qt::AlignTop);
		m_mainLayout->addWidget(m_titleBar.get());
		m_mainLayout->addLayout(m_contentLayout);
		setLayout(m_mainLayout);

		m_userservice  = USERSERVICE;
		m_cloudservice = CLOUDSERVICE;
		m_fileservice = FILESERVICE;
		m_contactservice = CONTACTSERVICE;
		model::Account account;
		m_userservice->getAccountInfo(account);
		m_userid = account.id.value();		
		m_username = QString::fromUtf8(account.name.value().data());
		CONNECT_SERVICE(OperUser(const model::Account&));
		m_userservice->regOperateUserCb(std::bind(&CloudDiskWidget::signalSerOperUser, this, std::placeholders::_1));
		//获取文件目录		
		connect(m_myselfWidget.get(), SIGNAL(signalGetFolderFiles(int, model::CloudFileInfo)), this,
			SLOT(onGetFolderFiles(int, model::CloudFileInfo)));
		connect(m_sharedWidget.get(), SIGNAL(signalGetFolderFiles(int, model::CloudFileInfo)), this,
			SLOT(onGetFolderFiles(int, model::CloudFileInfo)));

		//获取目录权限
		connect(m_myselfWidget.get(), SIGNAL(signalGetFolderPermission(int, model::CloudFileInfo)), this,
			SLOT(onGetFolderPermission(int, model::CloudFileInfo)));
		connect(m_sharedWidget.get(), SIGNAL(signalGetFolderPermission(int, model::CloudFileInfo)), this,
			SLOT(onGetFolderPermission(int, model::CloudFileInfo)));

		connect(m_myselfWidget.get(), SIGNAL(signalSpaceInfo(QString&, QString&, int&)), m_leftWidget.get(),
			SLOT(onSpaceInfo(QString&, QString&, int&)));
		connect(m_sharedWidget.get(), SIGNAL(signalSpaceInfo(QString&, QString&, int&)), m_leftWidget.get(),
			SLOT(onSpaceInfo(QString&, QString&, int&)));

		connect(m_myselfWidget.get(), SIGNAL(signalRename(qint64, QString&)), this,SLOT(onRename(qint64, QString&)));
		connect(m_sharedWidget.get(), SIGNAL(signalRename(qint64, QString&)), this, SLOT(onRename(qint64, QString&)));

		connect(m_myselfWidget.get(), SIGNAL(signalDelFile(std::vector<std::string>&,int)),
			this, SLOT(onDelFile(std::vector<std::string>&,int)));
		connect(m_sharedWidget.get(), SIGNAL(signalDelFile(std::vector<std::string>&,int)),
			this, SLOT(onDelFile(std::vector<std::string>&,int)));

		connect(m_myselfWidget.get(), SIGNAL(signalDown(model::CloudFileInfo, QString, int64)), this, SLOT(onSignalDown(model::CloudFileInfo, QString, int64)));
		connect(m_sharedWidget.get(), SIGNAL(signalDown(model::CloudFileInfo, QString, int64)), this, SLOT(onSignalDown(model::CloudFileInfo, QString, int64)));
		
		connect(m_myselfWidget.get(), SIGNAL(sigalCreateFolder(model::CloudAddFileInfo&, int)),
			this, SLOT(onCreateFolder(model::CloudAddFileInfo&, int)));
		connect(m_sharedWidget.get(), SIGNAL(sigalCreateFolder(model::CloudAddFileInfo&, int)),
			this, SLOT(onCreateFolder(model::CloudAddFileInfo&, int)));

		connect(m_myselfWidget.get(), SIGNAL(signalSearchFiles(QString&, int)),this, SLOT(onSearchFiles(QString&, int)));
		connect(m_sharedWidget.get(), SIGNAL(signalSearchFiles(QString&, int)),this, SLOT(onSearchFiles(QString&, int)));

		connect(m_myselfWidget.get(), SIGNAL(signalUpLoadFile(model::CloudUploadFileInfo&,  QString)), this, SLOT(onUpLoadFile(model::CloudUploadFileInfo&,  QString)));
		connect(m_sharedWidget.get(), SIGNAL(signalUpLoadFile(model::CloudUploadFileInfo&,  QString)), this, SLOT(onUpLoadFile(model::CloudUploadFileInfo&,  QString)));

		connect(m_myselfWidget.get(), SIGNAL(signalAuthorMgr(model::CloudFileInfo)), this, SLOT(onAuthorMgr(model::CloudFileInfo)));
		connect(m_sharedWidget.get(), SIGNAL(signalAuthorMgr(model::CloudFileInfo)), this, SLOT(onAuthorMgr(model::CloudFileInfo)));
		
		CONNECT_SERVICE(QueryFolder(service::ErrorInfo, std::vector<model::CloudFileInfo>&, int, int64));
		CONNECT_SERVICE(GetPermission(service::ErrorInfo, model::CloudPermission&, model::CloudFileInfo,int));
		CONNECT_SERVICE(Rename(service::ErrorInfo, std::string&));
		CONNECT_SERVICE(DelFile(service::ErrorInfo,int));
		CONNECT_SERVICE(CreateFolder(service::ErrorInfo, model::CloudFileInfo&, int));
		CONNECT_SERVICE(SearchFiles(service::ErrorInfo, std::vector<model::CloudFileInfo>&, int));
		CONNECT_SERVICE(UploadFileResult(service::ErrorInfo, const std::string&, int64));
		CONNECT_SERVICE(UploadFileProgress(int32, int32, const std::string&, int64));
		CONNECT_SERVICE(DownloadResult(service::ErrorInfo, int64, model::CloudFileInfo));
		CONNECT_SERVICE(DownloadProgress(int32, int32, const std::string&, int64,std::string&));
		CONNECT_SERVICE(UpCancelRlt(service::ErrorInfo));
		CONNECT_SERVICE(UpCancelRlt(service::ErrorInfo));
		CONNECT_SERVICE(GetSysSetResult(service::ErrorInfo, std::vector<model::LocalSetting>));
		
		//首次获取个人文件夹目录	
		model::CloudFileInfo info;
		info.fileId = 1;
		onGetFolderFiles(SELF_FILE, info);

		m_config = CONFIGSERVICE;

		m_filePath = m_config->userFilePath();
	}
	CloudDiskWidget::~CloudDiskWidget(){
		//LOG_METHOD("CloudDiskWidget::~CloudDiskWidge", LOG_FILE);
		if (nullptr != m_contentLayout){
			m_contentLayout->deleteLater();
			m_contentLayout = nullptr;
		}
		if (nullptr != m_mainLayout){
			m_mainLayout->deleteLater();
			m_mainLayout = nullptr;
		}
	}
	void CloudDiskWidget::onSelfBtnClicked(){
		//LOG_METHOD("CloudDiskWidget::onSelfBtnClicked", LOG_FILE);
		m_myselfWidget->restorePermission();
		m_rightWidget->setCurrentWidget(m_myselfWidget.get());
	}
	void CloudDiskWidget::onShareBtnClicked(){
		//LOG_METHOD("CloudDiskWidget::onShareBtnClicked", LOG_FILE);
		m_sharedWidget->restorePermission();
		m_rightWidget->setCurrentWidget(m_sharedWidget.get());
		if (m_isFirstFlag){
			model::CloudFileInfo info;
			info.fileId = SHARED_FILE_ROOT_PID;
			info.fileCode = SHARED_FILE_ROOT_FILECODE;
			info.roleId = SHARED_FILE_ROOT_ROLEID;
			info.fileType = SHARED_FILE_FILETYPE;
			info.ownerId = m_userid;
			onGetFolderPermission(SHARED_FILE,info);
			m_isFirstFlag = false;
		}
	}
	void CloudDiskWidget::onSerQueryFolder(service::ErrorInfo err, std::vector<model::CloudFileInfo>&folderlist, int type,int64 fileid){
		//LOG_METHOD("CloudDiskWidget::onSerQueryFolder", LOG_FILE);
		Log(LOG_LEV_DEBUG, LOG_FILE,"err=%d,folderlist.size=%d,type=%d", err, folderlist.size(),type);
			FileListWidget* fileList = nullptr;
			int count = 0;
			if (SELF_FILE == type){
				fileList = m_myselfWidget.get();
			}
			else{
				fileList = m_sharedWidget.get();
			}
			//后台处理了，暂时屏蔽
			//if (SHARED_FILE == type &&   SHARED_FILE_ROOT_PID == fileid){
			//	//getteams返回需要特殊处理
			//	for (int i = 0; i < folderlist.size(); ++i)
			//	{
			//		int j = 0;
			//		QString filecode = QString::fromUtf8(folderlist[i].fileCode.data());
			//		for (; j < folderlist.size(); ++j)
			//		{
			//			QString temp = QString::fromUtf8(folderlist[j].fileCode.data());
			//			if (temp.contains(filecode) && j !=i)
			//			{
			//				break;
			//			}
			//		}
			//		if (j >= folderlist.size()){
			//			++count;
			//			if (folderlist[i].uploaderName.empty()){
			//				qint64 id = ((1 == folderlist[i].fileType) ? folderlist[i].uploaderId : folderlist[i].ownerId);
			//				folderlist[i].uploaderName = getUploadName(id).toUtf8().data();
			//			}
			//			fileList->addFolder(folderlist[i]);
			//			QCoreApplication::processEvents();
			//		}
			//	}

			//}
			//else{
			for (int index = 0; index <folderlist.size(); ++index){
				Log(LOG_LEV_DEBUG, LOG_FILE, "name=%s", QString::fromUtf8(folderlist[index].fileName.data()).toLocal8Bit().data());
				if ((SHARED_FILE == type && 1 == folderlist[index].fileId)){
					continue;
				}
				++count;
				if (folderlist[index].uploaderName.empty()){
					qint64 id = ((1 == folderlist[index].fileType) ? folderlist[index].uploaderId : folderlist[index].ownerId);
					folderlist[index].uploaderName = getUploadName(id).toUtf8().data();
				}
				fileList->addFolder(folderlist[index]);
				QCoreApplication::processEvents();
			}
			//}
			fileList->setFileCount(count);
			if (!count){
				fileList->setStopLoadingAnimate();
				fileList->setNoFileTip();
			}
			else{
				fileList->sortDescByTime();
				fileList->setStopLoadingAnimate();
			}
			showTipMessageBox(err);
	}
	void CloudDiskWidget::onGetFolderFiles(int type, model::CloudFileInfo info){
		//LOG_METHOD("CloudDiskWidget::onGetFolderFiles", LOG_FILE);
		FileListWidget* fileList = nullptr;
		if (SELF_FILE == type){
			fileList = m_myselfWidget.get();
		}
		else if(SHARED_FILE == type){
			fileList = m_sharedWidget.get();
		}
		if (nullptr != fileList && SHARED_FILE_ROOT_PID != info.fileId && MYSELF_FILE_ROOT_PID != info.fileId){
			fileList->setFolderInfo(type, info);
		}
		Log(LOG_LEV_DEBUG,LOG_FILE,"pid=%lld,userid=%lld", info.fileId,m_userid);
		if (SHARED_FILE_ROOT_PID == info.fileId && SHARED_FILE == type){

			m_cloudservice->getTeams(m_userid, 
									std::bind(&CloudDiskWidget::signalSerQueryFolder,
									this,
									std::placeholders::_1,
									std::placeholders::_2,
									type,
									info.fileId));
		}
		else{
			qint64 userid = 0;
			qint64 ownerid = 0;
			ownerid = fileList->getSharedDirOwnerId();
			if (SHARED_FILE == type && ownerid == m_userid){
				userid = info.ownerId;
			}
			else{
				userid = m_userid;
			}
			m_cloudservice->queryFloder(
									info.fileId,
									userid,
									std::bind(&CloudDiskWidget::signalSerQueryFolder,
									this,
									std::placeholders::_1,
									std::placeholders::_2,
									type,
									info.fileId));
		}
	}
	void CloudDiskWidget::onGetFolderPermission(int type, model::CloudFileInfo info){
		//LOG_METHOD("CloudDiskWidget::onGetFolderPermission", LOG_FILE);
		model::CloudPermission permission = TableWidgetItem::getItemPermission();
		FileListWidget* fileList = nullptr;
		qint64 userid = 0;
		qint64 ownerid = 0;
		qint64 roleid = 0;
		if (SELF_FILE == m_rightWidget->currentIndex() + 1){
			fileList = m_myselfWidget.get();
		}
		else{
			fileList = m_sharedWidget.get();
		}
		ownerid = fileList->getSharedDirOwnerId();
		if (SHARED_FILE == type && ownerid == m_userid){
			userid = info.ownerId;
		}
		else{
			userid = m_userid;
		}
		if (4 == info.fileType || SHARED_FILE_ROOT_PID == info.fileId){
			roleid = info.roleId;
		}
		else{
			roleid = 0;
		}
		//获取权限
		m_cloudservice->getPermission(
									roleid,
									info.fileId,
									userid,
									std::bind(&CloudDiskWidget::signalSerGetPermission,
									this,
									std::placeholders::_1,
									std::placeholders::_2,
									info,
									type));
	}
	void CloudDiskWidget::onSerGetPermission(service::ErrorInfo err, model::CloudPermission& permission, model::CloudFileInfo info, int type){
		//LOG_METHOD("CloudDiskWidget::onSerGetPermission", LOG_FILE);
		Log(LOG_LEV_DEBUG,LOG_FILE,"err=%d,type=%d", err,type);
		FileListWidget* fileList = nullptr;
		if (SELF_FILE == type){
			fileList = m_myselfWidget.get();
		}
		else{
			fileList = m_sharedWidget.get();
		}
		fileList->setFolderPermission(permission, info);
		showTipMessageBox(err);
	}
	void CloudDiskWidget::onRename(qint64 fileid, QString&newname){
		//LOG_METHOD("CloudDiskWidget::onRename", LOG_FILE);
		m_cloudservice->renameFile(
								fileid, 
								newname.toUtf8().data(),
								std::bind(&CloudDiskWidget::signalSerRename,
								this,
								std::placeholders::_1,
								newname.toStdString()));
	}
	void CloudDiskWidget::onSerRename(service::ErrorInfo err, std::string&newname){
		//LOG_METHOD("CloudDiskWidget::onSerRename", LOG_FILE);
		Log(LOG_LEV_DEBUG,LOG_FILE,"err=%d", err);
		if (!err){
			FileListWidget* fileList = nullptr;
			int type = m_rightWidget->currentIndex() + 1;
			if (SELF_FILE == type){
				fileList = m_myselfWidget.get();
			}
			else{
				fileList = m_sharedWidget.get();
			}
			fileList->updateFileName(QString::fromStdString(newname));
		}
		showTipMessageBox(err);
	}
	void CloudDiskWidget::onDelFile(std::vector<std::string>&hascodes,int type){
		//LOG_METHOD("CloudDiskWidget::onDelFile", LOG_FILE);
		m_cloudservice->delFile(
								hascodes,
								std::bind(&CloudDiskWidget::signalSerDelFile,
								this,
								std::placeholders::_1,
								type));
	}
	void CloudDiskWidget::onSerDelFile(service::ErrorInfo err,int type){
		//LOG_METHOD("CloudDiskWidget::onSerDelFile", LOG_FILE);
		Log(LOG_LEV_DEBUG,LOG_FILE,"err=%d", err);
		if (!err){
			FileListWidget* fileList = nullptr;
			if (SELF_FILE == type){
				fileList = m_myselfWidget.get();
			}
			else{
				fileList = m_sharedWidget.get();
			}
			fileList->refreshList(true);
		}
		showTipMessageBox(err);
	}
	void CloudDiskWidget::onCreateFolder(model::CloudAddFileInfo&data,int type){
		//LOG_METHOD("CloudDiskWidget::onCreateFolder", LOG_FILE);
		data.ownerId = m_userid;
		data.uploaderId = m_userid;
		data.uploaderName = m_username.toUtf8().data();
		if (SELF_FILE == type){
			m_cloudservice->addFile(
				data,
				std::bind(&CloudDiskWidget::signalSerCreateFolder,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				type));
		}
		else{
			m_cloudservice->createTeam(data,
				std::bind(&CloudDiskWidget::signalSerCreateFolder,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				type));
		}
	}
	void CloudDiskWidget::onSerCreateFolder(service::ErrorInfo err, model::CloudFileInfo&info, int type){
		//LOG_METHOD("CloudDiskWidget::onSerCreateFolder", LOG_FILE);
		Log(LOG_LEV_DEBUG,LOG_FILE,"err=%d,type=%d", err,type);
		if (!err){
			FileListWidget* fileList = nullptr;
			if (SELF_FILE == type){
				fileList = m_myselfWidget.get();
			}
			else{
				fileList = m_sharedWidget.get();
			}
			if (info.uploaderName.empty()/* || info.ownerId == m_userid*/){
				qint64 id = ((1 == info.fileType) ? info.uploaderId : info.ownerId);
				info.uploaderName = getUploadName(id).toUtf8().data();
			}
			fileList->insertFolder(info);
		}
		showTipMessageBox(err);
	}
	void CloudDiskWidget::onSearchFiles(QString&key, int type){
		//LOG_METHOD("CloudDiskWidget::onSearchFiles", LOG_FILE);
		FileListWidget* fileList = nullptr;
		if (SELF_FILE == type){
			fileList = m_myselfWidget.get();
		}
		else{
			fileList = m_sharedWidget.get();
		}
		fileList->clearData();
		fileList->setStartLoadingAnimate();
		m_cloudservice->searchFiles(
								m_userid, 
								key.toUtf8().data(),
								std::bind(&CloudDiskWidget::signalSerSearchFiles,
								this,
								std::placeholders::_1,
								std::placeholders::_2,
								type));	
	}

	void CloudDiskWidget::onSerSearchFiles(service::ErrorInfo err, std::vector<model::CloudFileInfo>&files, int type){
			//LOG_METHOD("CloudDiskWidget::onSerSearchFiles", LOG_FILE);
			Log(LOG_LEV_DEBUG,LOG_FILE,"err=%d,type=%d", err, type);
			FileListWidget* fileList = nullptr;
			int count = files.size();
			if (SELF_FILE == type){
				fileList = m_myselfWidget.get();
			}
			else{
				fileList = m_sharedWidget.get();
			}
			fileList->setFileCount(count);
			if (!count){
				fileList->setStopLoadingAnimate();
				fileList->setNoFileTip();
			}
			else{
				for (int index = 0; index <count; ++index){
					if (files[index].uploaderName.empty() /*|| files[index].ownerId == m_userid*/){
						qint64 id = ((1 == files[index].fileType) ? files[index].uploaderId : files[index].ownerId);
						files[index].uploaderName = getUploadName(id).toUtf8().data();
					}
					fileList->addFolder(files[index]);
					QCoreApplication::processEvents();
				}
				fileList->sortDescByTime();
				fileList->setStopLoadingAnimate();
			}
	}

	void CloudDiskWidget::onUpLoadFile(model::CloudUploadFileInfo& info, QString name){
		//LOG_METHOD("CloudDiskWidget::onUpLoadFile", LOG_FILE);
		Log(LOG_LEV_INFO,LOG_FILE,"CloudDiskWidget::onUpLoadFile fileinfo.fileSize = %ld,info.localId = %ld", info.fileSize, info.localId);
		if (m_progressTip == nullptr){
			m_progressTip = std::make_shared<ProgressWindow>(this);
			//CONNECT_SUBCTRL(m_progressTip, UpClose());
			CONNECT_SUBCTRL(m_progressTip, UpCancel(int64));
			CONNECT_SUBCTRL(m_progressTip, UpRetry(int64));
			connect(m_progressTip.get(), SIGNAL(signalClose()), this, SLOT(onUpClose()));
			connect(m_titleBar.get(), SIGNAL(signalWindowSizeChanged()), m_progressTip.get(), SLOT(onWindowSizeChanged()));
			connect(this, SIGNAL(signalUpFail(int64)), m_progressTip.get(), SIGNAL(signalUpFail(int64)));
			m_progressTip->setTitle(tr("文件上传"));
			m_progressTip->show();
		}
		UpInfo infos;
		infos.info = info;
		infos.type = 0;
		infos.sdklocalId = 0;
		if (name.isEmpty()){
			name = "-";
		}
		infos.rootname = name;
		infos.localId = info.localId;
		CloudUpInfos.push_back(infos);
		QFileInfo filename(info.localPath.data());
		model::CloudFileInfo fileinfo;
		fileinfo.fileSize = info.fileSize;
		fileinfo.fileName = filename.completeBaseName().toUtf8().data();
		fileinfo.fileSuffix = filename.completeSuffix().toUtf8().data();
		m_progressTip->addItem(fileinfo, name);
		m_progressTip->SetProcess(0, info.localId, name.toStdString());
		
		m_cloudservice->uploadFile(info, std::bind(&CloudDiskWidget::signalSerUploadFileResult, this, std::placeholders::_1, std::placeholders::_2,  info.localId),std::bind(&CloudDiskWidget::signalSerUploadFileProgress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, info.localId));
	}

	void CloudDiskWidget::onSerUploadFileResult(service::ErrorInfo error, const std::string& info,int64 localid){
		//LOG_METHOD("CloudDiskWidget::onSerUploadFileResult", LOG_FILE);
		Log(LOG_LEV_DEBUG,LOG_FILE,"err=%d", error);
		if (!error){
			ReFreshData();			
			std::vector<UpInfo>::iterator iter;
			for (iter = CloudUpInfos.begin(); iter != CloudUpInfos.end(); iter++)
			{
				if (iter->localId == localid){
					CloudUpInfos.erase(iter);
					break;
				}
			}
			if (!CloudUpInfos.size()){
				onUpClose();
			}
		}
		else{
			emit signalUpFail(localid);
			showTipMessageBox(error);
		}
	}
	void CloudDiskWidget::onSerUploadFileProgress(int32 extra_req, int32 progress, const std::string& info,int64 localId){		
		//LOG_METHOD("CloudDiskWidget::onSerUploadFileProgress", LOG_FILE);
		if (m_progressTip != nullptr){
			std::string path("");
			m_progressTip->SetProcess(progress, localId, path);
		}	
	}
	void CloudDiskWidget::onUpCancel(int64 localid){
		//LOG_METHOD("CloudDiskWidget::onUpCancel", LOG_FILE);
		m_fileservice->cancelTransfer(localid, 1, std::bind(&CloudDiskWidget::signalSerUpCancelRlt, this, std::placeholders::_1));
	}
	void CloudDiskWidget::onUpRetry(int64 localid){
		//LOG_METHOD("CloudDiskWidget::onUpRetry", LOG_FILE);
		if (CloudUpInfos.size()){

			std::vector<UpInfo>::iterator iter;
			for (iter = CloudUpInfos.begin(); iter != CloudUpInfos.end(); iter++)
			{
				if (iter->localId == localid){
					QFileInfo filename(iter->info.localPath.data());
					model::CloudFileInfo fileinfo;
					fileinfo.fileSize = iter->info.fileSize;
					fileinfo.fileName = filename.completeBaseName().toStdString();
					std::string path("");
					m_progressTip->SetProcess(0, localid, path);
					//m_progressTip->addItem(fileinfo, iter->rootname, iter->localId);
					m_cloudservice->uploadFile(iter->info, std::bind(&CloudDiskWidget::signalSerUploadFileResult, this, std::placeholders::_1, std::placeholders::_2,iter->localId)
						, std::bind(&CloudDiskWidget::signalSerUploadFileProgress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, iter->localId));
				}
			}
		}
	}
	void CloudDiskWidget::onDownRetry(int64 localid){
		//LOG_METHOD("CloudDiskWidget::onDownRetry", LOG_FILE);
		if (CloudDownInfos.size()){
			std::vector<DownInfo>::iterator iter;
			for (iter = CloudDownInfos.begin(); iter != CloudDownInfos.end(); iter++)
			{
				if (iter->localId == localid){
					std::string filename("");
					filename = m_filePath + iter->info.fileRemark + "." + iter->info.fileSuffix;
					std::string localpath("");
					QFileInfo qfile(iter->info.filePath.data());
					localpath = m_filePath + qfile.baseName().toStdString();
					m_downloadWnd->SetProcess(0, localid, filename);
					int64 sdklocalid = m_fileservice->downloadExternalFile(localpath, iter->info.filePath, 1, std::bind(&CloudDiskWidget::signalSerDownloadResult,
						this, std::placeholders::_1, iter->localId,iter->info),
						std::bind(&CloudDiskWidget::signalSerDownloadProgress, this,
						std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, iter->localId, filename));
					iter->sdklocalId = sdklocalid;
				}
			}
		}
	}
	void CloudDiskWidget::onUpClose()
	{
		//LOG_METHOD("CloudDiskWidget::onUpClose", LOG_FILE);
	/*	if (m_progressTip != nullptr)
		{
			m_progressTip->deleteLater();
			m_progressTip->clear();
		}*/
		if (CloudUpInfos.size()){
			std::vector<UpInfo>::iterator iter;
			for (iter = CloudUpInfos.begin(); iter != CloudUpInfos.end(); iter++)
			{
				m_fileservice->cancelTransfer(iter->localId, 1, std::bind(&CloudDiskWidget::signalSerUpCancelRlt, this, std::placeholders::_1));
			}
			
		}
	}
	void CloudDiskWidget::onSerUpCancelRlt(service::ErrorInfo error){
		//LOG_METHOD("CloudDiskWidget::onSerUpCancelRlt", LOG_FILE);
		Log(LOG_LEV_DEBUG,LOG_FILE,"err=%d", error);
	}
	void CloudDiskWidget::onDownClose(){
		//LOG_METHOD("CloudDiskWidget::onDownClose", LOG_FILE);
		/*if (m_downloadWnd != nullptr)
		{
			m_downloadWnd->deleteLater();
			m_downloadWnd.clear();
		}*/
	}

	void CloudDiskWidget::onSerDownloadResult(service::ErrorInfo error, int64 localId, model::CloudFileInfo data){
		//LOG_METHOD("CloudDiskWidget::onSerDownloadResult", LOG_FILE);
		Log(LOG_LEV_DEBUG,LOG_FILE,"err=%d", error);
		if (!error){
			emit signalDecryptFile(localId, data, m_filePath);
		}
		else{
			emit signalDownFail(localId);
		}	
	}

	void CloudDiskWidget::onSerDownloadProgress(int32 extra_req, int32 progress, const std::string& info, int64 localId, std::string& filename){
		//LOG_METHOD("CloudDiskWidget::onSerDownloadProgress", LOG_FILE);
		if (m_downloadWnd != nullptr){
			m_downloadWnd->SetProcess(progress, localId, filename);
		}
	}
	void CloudDiskWidget::onShowAuthorMemSelWnd(){
		//LOG_METHOD("CloudDiskWidget::onShowAuthorMemSelWnd", LOG_FILE);
		ShowAuthorMemSelWnd();
	}
	void CloudDiskWidget::ShowAuthorMemSelWnd(){
		//LOG_METHOD("CloudDiskWidget::ShowAuthorMemSelWnd", LOG_FILE);

		QVector<qint64> filtermemberlist;
		if (m_authMemberListWnd != nullptr){
			filtermemberlist = m_authMemberListWnd->getMemberList();
		}
		m_authorSelWnd = std::make_shared<AuthMemberSelWnd>(filtermemberlist);
		connect(m_authorSelWnd.get(), SIGNAL(signalAuthMembers(std::vector<model::TeamMemberInfo>&)), m_authMemberListWnd.get(), SIGNAL(signalAuthMembers(std::vector<model::TeamMemberInfo>&)));
		m_authorSelWnd->show();
		m_authorSelWnd->activateWindow();
		m_authorSelWnd->raise();
	}
	void CloudDiskWidget::ShowUploadSelectDirWnd(QString&filePath,QString&encrptkey){
		//LOG_METHOD("CloudDiskWidget::ShowUploadSelectDirWnd", LOG_FILE);

		m_uploadWnd = std::make_shared<CloudDiskUploadWnd>(filePath,encrptkey);
		connect(m_uploadWnd.get(), SIGNAL(signalUpLoadFile(model::CloudUploadFileInfo&, QString)), this, SLOT(onUpLoadFile(model::CloudUploadFileInfo&, QString)));
		connect(m_uploadWnd.get(), SIGNAL(signalShowCloudDiskWnd()), this, SLOT(onShowCloudDiskWnd()));
		m_uploadWnd->show();
		m_uploadWnd->activateWindow();
		m_uploadWnd->raise();
	}

	void CloudDiskWidget::onShowCloudDiskWnd(){
		//LOG_METHOD("CloudDiskWidget::onShowCloudDiskWnd", LOG_FILE);
		ShowWindow();
	}
	void CloudDiskWidget::ShowWindow(){
		//LOG_METHOD("CloudDiskWidget::ShowWindow", LOG_FILE);
		if (this->isMinimized()){
			this->showNormal();
		}
		else{
			this->show();
		}
		this->activateWindow();
		this->raise();
	}
	void CloudDiskWidget::ReFreshData(){
		//LOG_METHOD("CloudDiskWidget::ReFreshData", LOG_FILE);
		FileListWidget* fileList = nullptr;
		if (SELF_FILE == m_rightWidget->currentIndex()+1){
			fileList = m_myselfWidget.get();
		}
		else{
			fileList = m_sharedWidget.get();
		}
		fileList->refreshList(true);
	}
	void CloudDiskWidget::ReInitData(){
		//LOG_METHOD("CloudDiskWidget::ReFreshData", LOG_FILE);
		if (m_myselfWidget != nullptr){
			m_myselfWidget->clearData();
			m_rightWidget->setCurrentWidget(m_myselfWidget.get());
			m_leftWidget->SetMySelfBtnSelected();
		}
		if (m_sharedWidget != nullptr){
			m_sharedWidget->clearData();
		}
		m_isFirstFlag = true;
		//首次获取个人文件夹目录	
		model::CloudFileInfo info;
		info.fileId = 1;
		onGetFolderFiles(SELF_FILE, info);
	}
	void CloudDiskWidget::onSignalDown(model::CloudFileInfo data, QString name, int64 localId){		
		//LOG_METHOD("CloudDiskWidget::onSignalDown", LOG_FILE);
		if (m_downloadWnd == nullptr){
			m_downloadWnd = std::make_shared<ProgressWindow>(this);			
			CONNECT_SUBCTRL(m_downloadWnd, DownCancel(int64));	
			CONNECT_SUBCTRL(m_downloadWnd, DownRetry(int64));
			connect(m_downloadWnd.get(), SIGNAL(signalClose()), this, SLOT(onDownClose()));
			connect(m_titleBar.get(), SIGNAL(signalWindowSizeChanged()), m_downloadWnd.get(), SLOT(onWindowSizeChanged()));
			connect(this, SIGNAL(signalDownFail(int64)), m_downloadWnd.get(), SIGNAL(signalDownFail(int64)), Qt::QueuedConnection);
			connect(this, SIGNAL(signalDecryptFile(int64, model::CloudFileInfo&, std::string&)), m_downloadWnd.get(), SIGNAL(signalDecryptFile(int64, model::CloudFileInfo&, std::string&)));
			m_downloadWnd->setTitle(tr("文件下载"));
			m_downloadWnd->show();
			}
		if (name.isEmpty()){
			name = "-";
		}
		m_downloadWnd->addItem(data, name);
		std::string filename("");
		filename = m_filePath + data.fileRemark + "." + data.fileSuffix;
		std::string localpath("");
		QFileInfo qfile(data.filePath.data());
		localpath = m_filePath + qfile.baseName().toStdString();
		m_downloadWnd->SetProcess(0, localId, filename);
		int64 sdklocalid = m_fileservice->downloadExternalFile(localpath, data.filePath, 1, std::bind(&CloudDiskWidget::signalSerDownloadResult, this, std::placeholders::_1, localId, data),
				std::bind(&CloudDiskWidget::signalSerDownloadProgress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, localId, filename));
		DownInfo infos;
		infos.info = data;
		infos.type = 0;
		infos.sdklocalId = sdklocalid;
		infos.rootname = name;
		infos.localId = localId;
		infos.filename = filename;
		CloudDownInfos.push_back(infos);
	}
	void CloudDiskWidget::onDownCancel(int64 localid){
		//LOG_METHOD("CloudDiskWidget::onDownCancel", LOG_FILE);
		if (CloudDownInfos.size() > 0){
			std::vector<DownInfo>::iterator iter;
			for (iter = CloudDownInfos.begin(); iter != CloudDownInfos.end(); iter++)
			{
				if (iter->localId == localid){
					m_fileservice->cancelTransfer(iter->sdklocalId, 3, std::bind(&CloudDiskWidget::signalSerDownCancelRlt,
						this, std::placeholders::_1));
				}
			}
		}
	}
	void CloudDiskWidget::onSerDownCancelRlt(service::ErrorInfo error){
		//LOG_METHOD("CloudDiskWidget::onSerDownCancelRlt", LOG_FILE);
	}
	void CloudDiskWidget::onAuthorMgr(model::CloudFileInfo info){
		//LOG_METHOD("CloudDiskWidget::onAuthorMgr", LOG_FILE);
		m_authMemberListWnd = std::make_shared<AuthMemberListWnd>(info);
		m_authMemberListWnd->show();
		connect(m_authMemberListWnd.get(), SIGNAL(signalAddMember()), this, SLOT(onShowAuthorMemSelWnd()));
	}

	void CloudDiskWidget::decryptFile(std::string encryptKey, QString filePath, QString fileName, QString&outPath, QString inCachePath){
		//LOG_METHOD("CloudDiskWidget::decryptFile", LOG_FILE);
		QString cachePath("");
		QDir tempDir;

		cachePath = inCachePath + "clouddisk/";

		if (filePath.isEmpty() || fileName.isEmpty())
		{
			return;
		}
		outPath.clear();
		outPath.append(cachePath);
		if (!tempDir.exists(outPath))
		{
			tempDir.mkpath(outPath);
		}
		outPath = getDecryptFilePath(outPath, fileName);
		if (QFile::exists(outPath))
		{
			return;
		}
		//存在并且不是另存为的加密文件，则解密
		bool decyCode = m_fileservice->decryptFile(encryptKey.c_str(), filePath.toUtf8().data(), outPath.toUtf8().data());
		if (!decyCode)
		{
			outPath.clear();
			return;
		}
		else{
			return;
		}
	}
	QString CloudDiskWidget::getDecryptFilePath(QString cacheDirPath, QString fileName)
	{
		//LOG_METHOD("CloudDiskWidget::getDecryptFilePath", LOG_FILE);
		QString resultFilePath("");
		QDir dir(cacheDirPath);

		if (cacheDirPath.isEmpty() || fileName.isEmpty())
		{
			return resultFilePath;
		}
		//目录不存在则创建
		if (!dir.exists(cacheDirPath))
		{
			dir.mkpath(cacheDirPath);
		}
		resultFilePath = cacheDirPath + fileName;
		if (!IsFileExist(resultFilePath))
		{
			return resultFilePath;
		}
		else
		{
			QFile::remove(resultFilePath);
		}
		return resultFilePath;
	}

	bool CloudDiskWidget::IsFileExist(QString path){
		//LOG_METHOD("CloudDiskWidget::IsFileExist", LOG_FILE);
		bool bret = false;
		QFileInfo fileInfo;
		fileInfo.setFile(path);
		if (!path.isEmpty() && fileInfo.exists())
		{
			bret = true;
		}
		return bret; 
	}
	QString CloudDiskWidget::getUploadName(qint64 id){
		QString name("");

		if (m_userid == id){
			name = m_username;
		}
		else{
			model::Contact contact;
			m_contactservice->getContactInfo(id, contact);
			name = QString::fromUtf8(contact.name.value().data());
		}
		return name;
	}

	int CloudDiskWidget::ParseUpdateJson(QString json, model::CloudFileInfo& info)
	{
		//LOG_METHOD("CloudDiskWidget::ParseUpdateJson", LOG_FILE);
		bool ret = false;
		Json::Reader JsonReader;
		Json::Value JsonRoot;
		 bool RetJsonParse = JsonReader.parse(json.toStdString(), JsonRoot);
		 if(!RetJsonParse)
		 {
			 return -1;
		 }
		
		 Json::Value ArrayJson =  JsonRoot["files"];
		 for(int i=0; i<ArrayJson.size(); i++)
		 {
			 if(ArrayJson[i]["fileReMark"].isString())
			 {
				  info.fileRemark = ArrayJson[i]["fileReMark"].asString();
			 }
			
			 if(ArrayJson[i]["filename"].isString())
			 {
				  info.fileName = ArrayJson[i]["filename"].asString();
			 }
			
			 if(ArrayJson[i]["createdAt"].isInt64())
			 {
				 info.updateTime = ArrayJson[i]["createdAt"].asLargestInt();
			 }

			 if(ArrayJson[i]["createdAt"].isInt64())
			 {
				 info.createTime = ArrayJson[i]["createdAt"].asLargestInt();
			 }

			 if(ArrayJson[i]["filesize"].isInt64())
			 {
				 info.fileSize = ArrayJson[i]["filesize"].asLargestInt();
			 }

			 if(ArrayJson[i]["fileCode"].isInt64())
			 {
				 info.fileCode = ArrayJson[i]["fileCode"].asLargestInt();
			 }

			 if(ArrayJson[i]["uploadid"].isInt64())
			 {
				 info.uploaderId = ArrayJson[i]["uploadid"].asLargestInt();
			 }

			 if(ArrayJson[i]["fileId"].isInt64())
			 {
				info.fileId = ArrayJson[i]["fileId"].asLargestInt();
			 }

			 if(ArrayJson[i]["url"].isString())
			 {
				info.filePath = ArrayJson[i]["url"].asString();		 
			 }		 	 
		 }

		//QJsonParseError json_error;
		//QJsonDocument parse_doucment = QJsonDocument::fromJson(json.toUtf8().data(), &json_error);
		//if (json_error.error == QJsonParseError::NoError)
		//{
		//	if (parse_doucment.isObject())
		//	{
		//		QJsonObject obj = parse_doucment.object();
		//		if (obj.contains("files"))
		//		{
		//			QJsonValue content_value = obj.take("files");
		//			if (content_value.isArray())//鍒ゆ柇浠栨槸涓嶆槸json鏁扮粍  
		//			{
		//				QJsonArray array = content_value.toArray();
		//				for (int i = 0; i < array.size(); i++){
		//					if (array.at(i).isObject())
		//					{
		//						QJsonObject arrarobj = array.at(i).toObject();
		//						if (arrarobj.contains("fileReMark"))
		//						{
		//							QJsonValue value = arrarobj.take("fileReMark");
		//							if (value.isString())
		//							{
		//								info.fileRemark = value.toString().toStdString();
		//							}
		//						}
		//						if (arrarobj.contains("filename"))
		//						{
		//							QJsonValue value = arrarobj.take("filename");
		//							if (value.isString())
		//							{
		//								info.fileName = value.toString().toStdString();
		//							}
		//						}
		//						if (arrarobj.contains("createdAt"))
		//						{
		//							QJsonValue value = arrarobj.take("createdAt");
		//							if (value.isUndefined())
		//							{
		//								info.updateTime = value.toString().toLongLong();
		//								info.createTime = value.toString().toLongLong();
		//							}
		//						}
		//						if (arrarobj.contains("filesize"))
		//						{
		//							QJsonValue value = arrarobj.take("filesize");
		//							if (value.isDouble())
		//							{
		//								info.fileSize = value.toString().toLongLong();
		//							}
		//						}
		//						if (arrarobj.contains("fileCode"))
		//						{
		//							QJsonValue value = arrarobj.take("fileCode");
		//							if (value.isString())
		//							{
		//								info.fileCode = value.toString().toStdString();
		//							}
		//						}
		//						if (arrarobj.contains("uploadid"))
		//						{
		//							QJsonValue value = arrarobj.take("uploadid");
		//							if (value.isString())
		//							{
		//								info.uploaderId = value.toString().toLongLong();
		//							}
		//						}
		//						if (arrarobj.contains("fileId"))
		//						{
		//							QJsonValue value = arrarobj.take("fileId");
		//							if (value.isString())
		//							{
		//								info.fileId = value.toString().toLongLong();
		//							}
		//						}
		//						if (arrarobj.contains("url"))
		//						{
		//							QJsonValue value = arrarobj.take("url");
		//							if (value.isString())
		//							{
		//								info.filePath = value.toString().toStdString();
		//							}
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
		//return json_error.error;
		 return 0;
	}
	void CloudDiskWidget::onSerOperUser(const model::Account& userInfo){
		m_username = QString::fromUtf8(userInfo.name.value().data());
	}

	void  CloudDiskWidget::showTipMessageBox(int code){
		//LOG_METHOD("CloudDiskWidget::showTipMessageBox", LOG_FILE);
		Log(LOG_LEV_DEBUG, LOG_FILE, "code=%d", code);
		if (9 == code){
			QString tipinfo(tr("文件夹已被删除!"));
			showWarning(nullptr, tr("提示"), tipinfo);
		}
		else if (551 == code){
			QString tipinfo(tr("云盘目录不存在!"));
			showWarning(nullptr, tr("提示"), tipinfo);
		}
	}
}