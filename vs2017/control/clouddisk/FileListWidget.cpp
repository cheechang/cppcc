#include "FileListWidget.h"
#include "Controls/ToolButton.h"
#include "Controls/TableWidget.h"
#include <QFileDialog>
#include "Controls/LocalSearchLineEdit.h"
#include "Controls/QClickLabel.h"
#include "CreateFolderWindow.h"
#include "Common/Common.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qstackedwidget.h>
#include <QTableWidgetItem>
#include <QLinkedList>
#include "Controls/DefaultWidget.h"
#include "Controls/TableWidgetItem.h"
#include "Controls/MyMessageBox.h"
#include "Utils/utils.h"
#include <ctime>
#include <log.h>
namespace ui{
	
	FileListWidget::FileListWidget(FileType type, QWidget *parent) :QWidget(parent), m_createfolderbtn(nullptr),
		m_uploadbtn(nullptr), m_pBtnLayout(nullptr), m_mainLayout(nullptr), m_fileList(nullptr), m_parentLabel(nullptr),
		m_stackWidget(nullptr), m_defaultWidget(nullptr), m_isFirstFlag(true), m_createfolderwin(nullptr), m_defaultListTip(nullptr),
		m_userid(0), m_firstSharedOwnerId(0){
		//LOG_METHOD("FileListWidget::FileListWidget", LOG_FILE);
		m_uploadbtn = new ToolButton(QString(":/img/upload"), this);
		m_createfolderbtn = new ToolButton(QString(":/img/createfolder"), this);
		m_search = new LocalSearchLineEdit(type,this);
		m_fileList = new TableWidget(this);
		m_pBtnLayout = new QHBoxLayout();
		m_mainLayout = new QVBoxLayout(this);
		m_allFileLabel = new QClickLabel(this);
		m_rightLabel   = new QClickLabel(this);
		m_returnLabel  = new QClickLabel(this);
		m_vspliter	   = new QClickLabel(this);
		m_labelLayout  = new QHBoxLayout(this);
		m_tipLayout    = new QHBoxLayout(this);
		m_stackWidget  = new QStackedWidget(this);
		m_defaultWidget = new DefaultWidget(this);
		m_defaultListTip = new DefaultWidget(QString(":/img/defalutlist"),this);

		IUserService_Ptr userService = USERSERVICE;
		model::Account info;
		userService->getAccountInfo(info);
		m_userid = info.id.value();

		
		m_tipLayout->addWidget(m_returnLabel);
		m_tipLayout->addWidget(m_vspliter);
		m_tipLayout->addWidget(m_allFileLabel);
		m_labelLayout->addLayout(m_tipLayout);
		m_labelLayout->addStretch();
		m_labelLayout->addWidget(m_rightLabel);
		m_labelLayout->setAlignment(Qt::AlignLeft);
		m_labelLayout->setContentsMargins(0, 0, 0, 5);

		m_returnLabel->setTextColor(QColor(19, 134, 235));
		m_returnLabel->setText(tr("返回上一级"));
		m_returnLabel->setUnderlined(true);
		m_returnLabel->setVisible(false);

		m_vspliter->setTextColor(QColor(19, 134, 235));
		m_vspliter->setText(tr("|"));
		m_vspliter->setVisible(false);

		m_allFileLabel->setTextColor(QColor(102,101,96));
		m_allFileLabel->setText(tr("全部文件"));

		m_rightLabel->setTextColor(QColor(102, 101, 96));
		m_rightLabel->setText(tr("..."));

		m_search->setFixedSize(240, 30);

		//设置表格行标题
		QStringList headerLabels;
		headerLabels << tr("文件夹") << tr("大小") << tr("创建日期")<< tr("修改日期");
		m_fileList->setType(type);
		m_fileList->setColumnValue(headerLabels.size(), headerLabels);
		m_fileList->resize(QSize(480, 470));
		m_fileList->setContentsMargins(0,0,0,0);
		m_fileList->setFocus();

		model::CloudFileInfo rootData;
		if (SHARED_FILE == type){
			m_createfolderbtn->setText(tr("创建授权文件夹"));
			m_createfolderbtn->setSize(QSize(100, 0));
			initPermission(SHARED_FILE);
			rootData.fileId = SHARED_FILE_ROOT_PID;
			rootData.fileCode = SHARED_FILE_ROOT_FILECODE;
			rootData.roleId = SHARED_FILE_ROOT_ROLEID;
			rootData.fileType = SHARED_FILE_FILETYPE;
			rootData.ownerId = m_userid;
		}
		else{
			m_createfolderbtn->setSize(QSize(100, 0));
			m_createfolderbtn->setText(tr("创建普通文件夹"));
			initPermission(SELF_FILE);
			rootData.fileId = MYSELF_FILE_ROOT_PID;
			rootData.fileCode = MYSELF_FILE_ROOT_FILECODE;
			rootData.roleId = MYSELF_FILE_ROLEID;
			rootData.fileType = MYSELF_FILE_FILETYPE;
			rootData.ownerId = m_userid;
		}
		m_currentfolder = rootData;
		m_allFileLabel->setData(rootData);
		m_returnLabel->setData(rootData);

		m_uploadbtn->setText(tr("上传文件"));
		m_uploadbtn->setVisible(m_permisson.isUpload);
		m_uploadbtn->setObjectName("blueToolButton");
		m_createfolderbtn->setObjectName("grayToolButton");
		m_uploadbtn->setTextColor(QColor(255, 255, 255));
		m_createfolderbtn->setTextColor(QColor(9, 139, 255));
		m_uploadbtn->setSize(QSize(75, 0));
		
		m_pBtnLayout->setSpacing(15);
		m_pBtnLayout->setAlignment(Qt::AlignLeft);
		m_pBtnLayout->setContentsMargins(0, 10, 0, 5);
		m_pBtnLayout->addWidget(m_uploadbtn);
		m_pBtnLayout->addWidget(m_createfolderbtn);
		m_pBtnLayout->addStretch();
		m_pBtnLayout->addWidget(m_search);


		m_stackWidget->addWidget(m_defaultWidget);
		m_stackWidget->addWidget(m_fileList);
		m_stackWidget->addWidget(m_defaultListTip);
		m_stackWidget->setCurrentIndex(0);
		
		m_mainLayout->addLayout(m_pBtnLayout);
		m_mainLayout->addLayout(m_labelLayout);
		m_mainLayout->addWidget(m_stackWidget);
		m_mainLayout->setSpacing(0);
		m_mainLayout->setAlignment(Qt::AlignTop);
		m_mainLayout->setContentsMargins(10, 0, 10, 10);
		setLayout(m_mainLayout);
		connect(m_uploadbtn,SIGNAL(clicked()),this,SLOT(onUpLoadFile()));
		connect(m_search, SIGNAL(signalRefreshList()), this, SLOT(onRefreshList()));
		connect(m_search, SIGNAL(signalSearchFile(QString&)), this, SLOT(onSearchFile(QString&)));
		connect(m_fileList, SIGNAL(signalUpdateFileCount()), this, SIGNAL(onUpdateFileCount()));
		connect(m_fileList, SIGNAL(signalDelFile(std::vector<std::string>&)), this, SLOT(onDelFile(std::vector<std::string>&)));
		connect(m_fileList, SIGNAL(signalGetFolderFiles(int, model::CloudFileInfo)), this, SIGNAL(signalGetFolderFiles(int, model::CloudFileInfo)));
		connect(m_fileList, SIGNAL(signalGetFolderPermission(int, model::CloudFileInfo)), this, SLOT(onGetFolderPermission(int, model::CloudFileInfo)));
		connect(m_fileList, SIGNAL(signalRename(qint64, QString&)), this, SIGNAL(signalRename(qint64, QString&)));
		connect(m_fileList, SIGNAL(signalAuthorMgr(model::CloudFileInfo)), this, SIGNAL(signalAuthorMgr(model::CloudFileInfo)));
		connect(m_fileList, SIGNAL(signalDownLoad(model::CloudFileInfo)), this, SLOT(onDownload(model::CloudFileInfo)));
		connect(m_fileList, SIGNAL(signalRefresh()), this, SLOT(onRefreshList()));
		connect(this, SIGNAL(signalUpdateName(QString&)), m_fileList, SIGNAL(signalUpdateName(QString&)));
		connect(m_returnLabel, SIGNAL(signalClicked(model::CloudFileInfo)), this, SLOT(onClicked(model::CloudFileInfo)));
		connect(m_allFileLabel, SIGNAL(signalClicked(model::CloudFileInfo)), this, SLOT(onClicked(model::CloudFileInfo)));
		connect(m_createfolderbtn, SIGNAL(clicked()), this, SLOT(onCreateFolder()));
	}
	FileListWidget::~FileListWidget(){
		//LOG_METHOD("FileListWidget::~FileListWidget", LOG_FILE);
		if (nullptr != m_createfolderwin){
			m_createfolderwin->close();
			m_createfolderwin->deleteLater();
		}
		if (nullptr != m_pBtnLayout){
			m_pBtnLayout->deleteLater();
			m_pBtnLayout = nullptr;
		}
		if (nullptr != m_mainLayout){
			m_mainLayout->deleteLater();
			m_mainLayout = nullptr;
		}
	}
	void FileListWidget::addFolder(model::CloudFileInfo&fileinfo){
		//LOG_METHOD("FileListWidget::addFolder", LOG_FILE);
		m_fileList->addItem(fileinfo,m_userid == fileinfo.ownerId);
	}

	void FileListWidget::insertFolder(model::CloudFileInfo&info){
		//LOG_METHOD("FileListWidget::insertFolder", LOG_FILE);
		m_fileList->insertItem(0, info, m_userid == info.ownerId);
		m_stackWidget->setCurrentIndex(1);
	}
	void FileListWidget::setFileCount(int count){
		//LOG_METHOD("FileListWidget::setFileCount", LOG_FILE);
		QString str = tr("已全部加载，共%1个").arg(count);
		m_rightLabel->setText(str);
	}
	void FileListWidget::setFolderInfo(int type, model::CloudFileInfo info){
		//LOG_METHOD("FileListWidget::setFolderInfo", LOG_FILE);
		QSharedPointer<QClickLabel> foldername;
		QSharedPointer<QClickLabel> vspliter;

		if (!m_returnLabel->isVisible()){
			m_returnLabel->setVisible(true);
		}
		if (!m_vspliter->isVisible()){
			m_vspliter->setVisible(true);
		}
		if (!m_allFileLabel->underlined()){
			m_allFileLabel->setTextColor(QColor(19, 134, 235));
			m_allFileLabel->setUnderlined(true);
		}
		foldername= QSharedPointer<QClickLabel>(new QClickLabel(this));
		vspliter= QSharedPointer<QClickLabel>(new QClickLabel(this));
		connect(foldername.data(), SIGNAL(signalClicked(model::CloudFileInfo)), this, SLOT(onClicked(model::CloudFileInfo)));
		QString webunicodename = utils::webUnicodeToString(QString::fromUtf8(info.fileName.data()));
		foldername->setText(webunicodename);
		vspliter->setText(tr(">>"));
		vspliter->setTextColor(QColor(19, 134, 235));
		vspliter->setUnderlined(false);
		m_tipLayout->addWidget(vspliter.data());
		m_tipLayout->addWidget(foldername.data());
		
		foldername->setData(info);
		m_currentfolder = info;
		m_tipLabelList.push_back(vspliter);
		m_tipLabelList.push_back(foldername);
		foldername->setVisible(false);
		vspliter->setVisible(false);
		if (nullptr == m_parentLabel){
			model::CloudFileInfo rootData;
			if (SELF_FILE == m_fileList->getType()){
				rootData.fileId = MYSELF_FILE_ROOT_PID;
				rootData.fileCode = MYSELF_FILE_ROOT_FILECODE;
				rootData.roleId = MYSELF_FILE_ROLEID;
				rootData.fileType = MYSELF_FILE_FILETYPE;
				rootData.ownerId = m_userid;
			}
			else{
				rootData.fileId = SHARED_FILE_ROOT_PID;
				rootData.fileCode = SHARED_FILE_ROOT_FILECODE;
				rootData.roleId = SHARED_FILE_ROOT_ROLEID;
				rootData.fileType = SHARED_FILE_FILETYPE;
				rootData.ownerId = m_userid;
			}
			m_returnLabel->setData(rootData);
		}
		else{
			m_parentLabel->setTextColor(QColor(19, 134, 235));
			m_parentLabel->setUnderlined(true);
			m_returnLabel->setData(m_parentLabel->getData());
		}
		m_parentLabel = foldername.data();
	}
	void FileListWidget::onClicked(model::CloudFileInfo data){
		//LOG_METHOD("FileListWidget::onClicked", LOG_FILE);
		int type = m_fileList->getType();
		//返回根目录要区分个人文件及共享文件
		if (SHARED_FILE_ROOT_PID == data.fileId || MYSELF_FILE_ROOT_PID == data.fileId){
		  clearTipLabelData();
		  onGetFolderPermission(type,data);
		  m_currentfolder = m_allFileLabel->getData();
		  m_returnLabel->setData(m_currentfolder);
		}
		else{
			int j = 0;
			for(int listindex =0; listindex < m_tipLabelList.size(); listindex++)
			{
				if(m_tipLabelList.at(listindex)->getData().fileName == data.fileName)
				{
					break;
				}
				j++;
			}
			/*for (auto index : m_tipLabelList){
			if (index->getData().fileName == data.fileName){
			break;
			}
			++j;
			}*/
			//布局上移除
			for(int index=j-1; index < m_tipLabelList.size() && index>0; ++index){
				m_tipLayout->removeWidget(m_tipLabelList.at(index).data());
			}
			int k = 0,size=0;
			size = m_tipLabelList.size();
			k = size - j + 1;
			while (k>0 && size>0)
			{
				m_tipLabelList.pop_back();
				size = m_tipLabelList.size();
				--k;
			}
			int count = m_tipLabelList.size() - 1;
			if (count > 0){
			  m_parentLabel = m_tipLabelList.at(count).data();
			  m_returnLabel->setData(m_parentLabel->getData());
			}
			else{
				m_parentLabel = nullptr;
			}
			onGetFolderPermission(type, data);
		}
		//SELF_FILE == m_fileList->getType() ? data.fileId = 1:data.fileId=0;
		//emit signalGetFolderFiles(m_fileList->getType(),data);
	}
	void FileListWidget::clearTipLabelData(){
		//LOG_METHOD("FileListWidget::clearTipLabelData", LOG_FILE);
		m_returnLabel->setVisible(false);
		m_vspliter->setVisible(false);
		m_allFileLabel->setTextColor(QColor(102, 101, 96));
		m_allFileLabel->setUnderlined(false);
		m_parentLabel = nullptr;
		for (int index = 0; index < m_tipLabelList.size(); ++index){
			m_tipLayout->removeWidget(m_tipLabelList.at(index).data());
		}
		m_tipLabelList.clear();
	}
	void FileListWidget::clearData(){
		//LOG_METHOD("FileListWidget::clearData", LOG_FILE);
		m_fileList->clearData();
	}
	void FileListWidget::setNoFileTip(){
		//LOG_METHOD("FileListWidget::setNoFileTip", LOG_FILE);
		m_stackWidget->setCurrentIndex(2);
	}
	void FileListWidget::setStopLoadingAnimate(){
		//LOG_METHOD("FileListWidget::setStopLoadingAnimate", LOG_FILE);
		if (m_isFirstFlag){
			m_stackWidget->setCurrentIndex(1);
			m_isFirstFlag = false;
		}
	}
	void FileListWidget::setStartLoadingAnimate(){
		//LOG_METHOD("FileListWidget::setStartLoadingAnimate", LOG_FILE);
		if (!m_isFirstFlag){
			m_stackWidget->setCurrentIndex(0);
			m_isFirstFlag = true;
		}
	}
	void FileListWidget::refreshList(bool isrefreshcur){
		//LOG_METHOD("FileListWidget::refreshList", LOG_FILE);
		if (!isrefreshcur&&nullptr != m_returnLabel){
			onClicked(m_returnLabel->getData());
		}
		else{
			onClicked(m_currentfolder);
		}
		
	}
	void FileListWidget::restorePermission(){
		//LOG_METHOD("FileListWidget::restorePermission", LOG_FILE);
		TableWidgetItem::setItemPermission(m_permisson);
	}
	void FileListWidget::setFolderPermission(model::CloudPermission&permission, model::CloudFileInfo info){
		//LOG_METHOD("FileListWidget::setFolderPermission", LOG_FILE);
		QString foldername("");
		int type = m_fileList->getType();
		if (SELF_FILE ==type){
			initPermission(SELF_FILE);
		}
		else{
			//todo
			m_permisson = permission;
			TableWidgetItem::setItemPermission(permission);
		}

		Log(LOG_LEV_DEBUG,LOG_FILE,"[isCreateTeam=%d,isDelete=%d,isDownLoad=%d,isManager=%d,isRead=%d,isReName=%d,isUpload=%d,uploadsize=%d]",
			permission.isCreateTeam, permission.isDelete, permission.isDownLoad, permission.isManager, permission.isRead, permission.isReName, permission.isUpload, permission.uploadSize);

		foldername = QString::fromUtf8(info.fileName.c_str());
		int proval = 0;
		/*if (m_permisson.uploadSize < 0){
			m_permisson.uploadSize = 0;
		}
		if (m_permisson.totalSize < 0){
			m_permisson.totalSize = 2;
		}
		QString space = QString("%1").arg(m_permisson.uploadSize) + QString("/%1T").arg(m_permisson.totalSize);
		emit signalSpaceInfo(foldername, space, proval);*/
		m_uploadbtn->setVisible(m_permisson.isUpload);
		if (SHARED_FILE == type){
			m_createfolderbtn->setVisible(m_permisson.isCreateTeam);
		}
		else{
			m_createfolderbtn->setVisible(m_permisson.isUpload);
		}
		//不是首次登陆获取文件目录
		emit signalGetFolderFiles(type, info);
	}
	void FileListWidget::onCreateFolder(){
		//LOG_METHOD("FileListWidget::onCreateFolder", LOG_FILE);
		m_createfolderwin = new CreateFolderWindow;
		connect(m_createfolderwin, SIGNAL(signalCreateFolder(QString&)), this, SLOT(onDealCreateFolder(QString&)));
		m_createfolderwin->exec();
	}
	void FileListWidget::onDealCreateFolder(QString&foldername){
		//LOG_METHOD("FileListWidget::onDealCreateFolder", LOG_FILE);
	    QRegExp exp("[ </:>*?|]");
		bool bcontains = foldername.contains(exp);
		if (bcontains){
			showWarning(nullptr, tr("错误提示"), tr("文件夹名不能包含空格和其他特殊字符!"));
			return;
		}
		if (foldername.isEmpty()){
			showWarning(nullptr, tr("错误提示"), tr("文件夹名不能为空!"));
			return;
		}
		model::CloudAddFileInfo addfile;
		int type = 0;
		type = m_fileList->getType();
		addfile.fileName = foldername.toUtf8().data();
		addfile.fileType = ((SELF_FILE == type) ? TYPE_COMMON : TYPE_TEAM);

		//个人区跟目录为pid为1
		if (SELF_FILE == type && nullptr == m_parentLabel){
			addfile.pid = MYSELF_FILE_ROOT_PID;
		}
		else if (SELF_FILE == type && nullptr != m_parentLabel){
			addfile.pid = m_parentLabel->getData().fileId;
		}
		else if (SHARED_FILE == type && nullptr == m_parentLabel){
			addfile.pid = SHARED_FILE_ROOT_PID;
		}
		else if (SHARED_FILE == type && nullptr != m_parentLabel){
			addfile.pid = m_parentLabel->getData().fileId;
		}
		else{
			addfile.pid = 0;
		}

		//fileCode
		if (SELF_FILE == type && nullptr == m_parentLabel){
			addfile.fileCode = MYSELF_FILE_ROOT_FILECODE;
		}
		else if (SELF_FILE == type && nullptr != m_parentLabel){
			addfile.fileCode = m_parentLabel->getData().fileCode;
		}
		else if (SHARED_FILE == type && nullptr == m_parentLabel){
			addfile.fileCode = SHARED_FILE_ROOT_FILECODE;
		}
		else if (SHARED_FILE == type && nullptr != m_parentLabel){
			addfile.fileCode = m_parentLabel->getData().fileCode;
		}
		else{
			addfile.fileCode = std::string("");
		}
		emit sigalCreateFolder(addfile, type);
	}
	void FileListWidget::onDelFile(std::vector<std::string>&hashcode){
		//LOG_METHOD("FileListWidget::onDelFile", LOG_FILE);
		emit signalDelFile(hashcode, m_fileList->getType());
	}
	void FileListWidget::onSearchFile(QString&key){
		//LOG_METHOD("FileListWidget::onSearchFile", LOG_FILE);
		emit signalSearchFiles(key, m_fileList->getType());
	}
	void FileListWidget::onRefreshList(){
		//LOG_METHOD("FileListWidget::onRefreshList", LOG_FILE);
		 refreshList(true);
	}
	void FileListWidget::onGetFolderPermission(int type, model::CloudFileInfo info){
		//LOG_METHOD("FileListWidget::onGetFolderPermission", LOG_FILE);
		if (SELF_FILE == type){
			getFolderOperate(type, info, false);
		}
		else{
			getFolderOperate(type, info, true);
		}
	}
	void FileListWidget::getFolderOperate(int type, model::CloudFileInfo info,bool ispermission){
		//LOG_METHOD("FileListWidget::getFolderOperate", LOG_FILE);
		if (!m_isFirstFlag){
			clearData();
			setStartLoadingAnimate();
		}
		if (ispermission){
			if (nullptr == m_parentLabel){
				m_firstSharedOwnerId = info.ownerId;
			}
			emit signalGetFolderPermission(type, info);
		}
		else{
			emit signalGetFolderFiles(type, info);
		}
	}
	void FileListWidget::onUpLoadFile()
	{
		//LOG_METHOD("FileListWidget::onUpLoadFile", LOG_FILE);
		QString fileNameStr = QFileDialog::getOpenFileName(
			NULL,
			"",
			"",
			"");
		if (!fileNameStr.isEmpty()){

			double iK = 1024;
			double iM = 1024 * 1024;
			double iG = 1024 * 1024 * 1024;
			int type = 0;
			QFileInfo fileInfo(fileNameStr);
			QString filename = fileInfo.completeBaseName();
			model::CloudUploadFileInfo info;
			qint64 filesize = fileInfo.size();
			qint64 uploadSize = 0;

			if (m_permisson.uploadSize > 0 && m_permisson.totalSize>0){
			    uploadSize = qMin(m_permisson.uploadSize,m_permisson.totalSize)*iM;
			}
			else if(m_permisson.uploadSize > 0 && m_permisson.totalSize <0){
				uploadSize = m_permisson.uploadSize*iM;
			}
			else if (m_permisson.uploadSize <0 && m_permisson.totalSize >0){
				uploadSize = m_permisson.totalSize*iM;
			}
			else{
				uploadSize = -1;
			}

			if (filesize > uploadSize && -1 != uploadSize){
				QString tipinfo(tr("上传的单个文件不能超过"));
				tipinfo.append(QString::number(m_permisson.uploadSize));
				tipinfo.append(tr("M"));
				showWarning(nullptr, tr("提示"), tipinfo);
				return;
			}

			type = m_fileList->getType();
			info.fileSize = fileInfo.size();
			info.localPath = fileInfo.filePath().toUtf8().data();
			info.fileCode = (SELF_FILE == type&&m_currentfolder.fileCode.empty())?MYSELF_FILE_ROOT_FILECODE:m_currentfolder.fileCode;
			info.pid = (SELF_FILE == type&&!m_currentfolder.pid)?MYSELF_FILE_ROOT_PID:m_currentfolder.fileId;
			info.localId = time(NULL);
			info.isResume = true;
			Log(LOG_LEV_INFO,LOG_FILE, "info.fileSize = %lld,info.localPath = %s,info.fileCode = %s,info.pid =%lld", info.fileSize, info.localPath.c_str(), info.fileCode.c_str(), info.pid);
			if (info.fileSize <= MAX_FILE_LIMIT){
				info.encryptKey = m_encryptKey.get_key();
			}		
			QString webunicodename = utils::webUnicodeToString(QString::fromUtf8(m_currentfolder.fileName.data()));
			Log(LOG_LEV_INFO,LOG_FILE, "webunicodename = %s", webunicodename.toLocal8Bit().data());
			emit signalUpLoadFile(info,webunicodename);
		}
	}
	void FileListWidget::onDownload(model::CloudFileInfo data){
		//LOG_METHOD("FileListWidget::onDownload", LOG_FILE);
		QString webunicodename = utils::webUnicodeToString(QString::fromUtf8(m_currentfolder.fileName.data()));
		Log(LOG_LEV_INFO,LOG_FILE,"webunicodename = %s", webunicodename.toLocal8Bit().data());
		emit signalDown(data, webunicodename,time(NULL));
	}
	void FileListWidget::initPermission(int type){
		//LOG_METHOD("FileListWidget::initPermission", LOG_FILE);
		if (SHARED_FILE == type){
			m_permisson.isUpload = 0;
			m_permisson.isCreateTeam = 0;
			m_permisson.isDelete = 0;
			m_permisson.isDownLoad = 0;
			m_permisson.isManager = 0;
			m_permisson.isRead = 0;
			m_permisson.isReName = 0;
		}
		else{
			m_permisson.isUpload = 1;
			m_permisson.isCreateTeam = 0;
			m_permisson.isManager = 0;
			m_permisson.isDelete = 1;
			m_permisson.isDownLoad = 1;
			m_permisson.isRead = 1;
			m_permisson.isReName = 1;
		}
		TableWidgetItem::setItemPermission(m_permisson);
	}
	void FileListWidget::sortDescByTime(){
		//LOG_METHOD("FileListWidget::sortDescByTime", LOG_FILE);
		m_fileList->sortDescByTime();
	}
	void FileListWidget::updateFileName(QString&newname){
		//LOG_METHOD("FileListWidget::updateFileName", LOG_FILE);
		emit signalUpdateName(newname);
	}
	qint64 FileListWidget::getSharedDirOwnerId()const{
		return m_firstSharedOwnerId;
	}
}