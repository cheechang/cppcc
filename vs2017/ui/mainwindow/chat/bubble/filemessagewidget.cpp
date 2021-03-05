#include "filemessagewidget.h"
#include "flexaction.h"
#include <functional>
#include <memory>
#include <QFileInfo>
#include <QDebug>
#include <QLabel>
#include <QUrl>
#include <QFileDialog>
#include <QProcess>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "detail/clicklabel.h"
#include "controls/ElidedLabel.h"
#include "common/Common.h"
#include "common/Controlptr.h"
#include "common/UIUtils.h"
#include "data/ChatData.h"
#include <log.h>
#include <QDesktopServices>
static QString convert2ReadableSize(double size)
{
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("Bytes");

    while(size >= 1024.0 && i.hasNext())    {
        unit = i.next();
        size /= 1024.0;
    }

    return QString().setNum(size, 'f', 2) + " " + unit;
}
FileMessageItem::FileMessageItem(IChatMgrControl_Ptr& chatcontrol,QWidget *parent):ui::TWidget(parent),
m_fileNameLabel(CNull),m_fileSizeLabel(CNull),m_fileIconLabel(CNull),m_fileTip(CNull),
m_progress(CNull),m_openfile(CNull),m_openDir(CNull),m_download(CNull),m_saveas(CNull),
m_fileLayout(CNull),m_mainLayout(CNull),m_btndownloadlayout(CNull),m_btnfinishlayout(CNull),
m_btnfailedlayout(CNull), m_tipInfo(CNull),m_localid(0), m_chatcontrol(chatcontrol), m_isClouddisk(false)
{
	m_fileIconLabel = new QLabel(this);
	m_fileNameLabel = new ElidedLabel(this);
	m_fileSizeLabel = new QLabel(this);
	m_fileTip       = new ElidedLabel(this);
	m_progress		= new QProgressBar(this);
	m_openfile		= new ClickLabel(this);
	m_openDir		= new ClickLabel(this);
	m_download		= new ClickLabel(this);
	m_saveas		= new ClickLabel(this);
	m_redownload    = new ClickLabel(this);
	
	m_progress->setFixedHeight(2 * gDdpi);
	m_progress->setFixedWidth(240 * gDdpi);
	m_progress->setMinimum(0);
	m_progress->setMaximum(100);
	m_progress->setValue(0);
	m_progress->setTextVisible(false);
	m_progress->setStyleSheet("background:rgb(235,235,236);");

	m_fileNameLabel->setFixedHeight(20 * gDdpi);
	m_fileSizeLabel->setFixedHeight(20 * gDdpi);
	m_fileNameLabel->setMinimumWidth(190);
	m_fileTip->setFixedSize(180 * gDdpi,20 * gDdpi);

	m_openfile->setTextColor(QColor(35, 155, 219));
	m_openfile->setUnderlined(true);
	

	m_openDir->setTextColor(QColor(35, 155, 219));
	m_openDir->setUnderlined(true);


	m_download->setTextColor(QColor(35, 155, 219));
	m_download->setUnderlined(true);

	m_saveas->setTextColor(QColor(35, 155, 219));
	m_saveas->setUnderlined(true);

	m_redownload->setTextColor(QColor(35, 155, 219));
	m_redownload->setUnderlined(true);

	m_fileTip->setTextColor(QColor(119,119,119));

	m_fileLayout = new QGridLayout();
	m_fileLayout->addWidget(m_fileIconLabel,0,0,2,1,Qt::AlignTop);
	m_fileLayout->addWidget(m_fileNameLabel,0,1,1,1,Qt::AlignLeft);
	//m_fileLayout->addWidget(m_fileSizeLabel,0,2,1,1);
	m_fileLayout->addWidget(m_fileTip,1,1,1,2);

	m_mainLayout = new QVBoxLayout(this);
	m_mainLayout->addLayout(m_fileLayout);
	m_mainLayout->addWidget(m_progress);
	
	this->setLayout(m_mainLayout);
	this->translateLanguage();
	this->setStyleSheet("background-color:white;border-radius:3;");
}

void FileMessageItem::setFile(const QString& file)
{
    m_file = file;
	setFileInfo(m_file);
}
void FileMessageItem::setStatus(int status){
	switch(status){
	case FILE_TRANSFORMAT:
		{
			dealtransformat();
			break;
		}
	case FILE_DOWNLOAD:
		{
			dealdownload();
			break;
		}
	case FILE_FINISH:
		{
			dealFinish();
			break;
		}
	case FILE_FAILED:
		{
			dealFailed();
			break;
		}
	}
}
void FileMessageItem::dealtransformat(){
	if (CNull != m_btndownloadlayout)
	{
	   m_mainLayout->removeItem(m_btndownloadlayout);
	}
	if (CNull != m_btnfailedlayout)
	{
		m_mainLayout->removeItem(m_btnfailedlayout);
	}
	if ( CNull != m_btnfinishlayout)
	{
		m_mainLayout->removeItem(m_btnfinishlayout);
	}
	m_openfile->setVisible(false);
	m_openDir->setVisible(false);
	m_download->setVisible(false);
	m_redownload->setVisible(false);
	m_saveas->setVisible(false);
	m_fileSizeLabel->hide();
	m_mainLayout->addStretch();
}
void FileMessageItem::dealdownload(){
	if (CNull == m_btndownloadlayout)
	{
		m_btndownloadlayout = new QHBoxLayout();
		m_btndownloadlayout->addStretch();
		m_btndownloadlayout->addWidget(m_download);
		m_btndownloadlayout->addWidget(m_saveas);
	}
	if (CNull != m_btnfailedlayout)
	{
		m_mainLayout->removeItem(m_btnfailedlayout);
	}
	if ( CNull != m_btnfinishlayout)
	{
		m_mainLayout->removeItem(m_btnfinishlayout);
		m_openfile->setVisible(false);
		m_openDir->setVisible(false);
	}
	m_download->setVisible(true);
	m_saveas->setVisible(true);
	m_progress->setValue(0);
	m_progress->hide();
	m_fileTip->setText("");
	m_fileSizeLabel->show();
	m_mainLayout->addLayout(m_btndownloadlayout);
}
void FileMessageItem::dealFinish(){
	if (CNull == m_btnfinishlayout)
	{
		m_btnfinishlayout = new QHBoxLayout();
		m_btnfinishlayout->addStretch();
		m_btnfinishlayout->addWidget(m_openfile);
		m_btnfinishlayout->addWidget(m_openDir);
	}
	if (CNull != m_btnfailedlayout)
	{
		m_mainLayout->removeItem(m_btnfailedlayout);
	}
	if ( CNull != m_btndownloadlayout)
	{
		m_mainLayout->removeItem(m_btndownloadlayout);
	}
	m_openfile->setVisible(true);
	m_openDir->setVisible(true);
	m_progress->setValue(0);
	m_progress->setVisible(false);
	m_fileSizeLabel->show();
	if ( m_isrecv)
	{
		m_fileTip->setTextLimitExpand(transfer("成功存至")+m_file);
	}
	else{
		m_fileTip->setTextLimitExpand(transfer("成功发送文件"));
	}
	m_openDir->setVisible(true);
	m_redownload->setVisible(false);
	m_mainLayout->addLayout(m_btnfinishlayout);
}
void FileMessageItem::dealFailed(){
	if (CNull == m_btnfailedlayout)
	{
		m_btnfailedlayout = new QHBoxLayout();
		m_btnfailedlayout->addStretch();
		m_btnfailedlayout->addWidget(m_redownload);
	}
	if (CNull != m_btndownloadlayout)
	{
		m_mainLayout->removeItem(m_btndownloadlayout);
	}
	if ( CNull != m_btnfinishlayout)
	{
		m_mainLayout->removeItem(m_btnfinishlayout);
	}
	m_progress->setValue(0);
	m_redownload->setVisible(true);
	m_fileSizeLabel->hide();
	m_mainLayout->addLayout(m_btnfailedlayout);
}
void FileMessageItem::setFileInfo(QString&path){
	QString filename = m_media.name;
	qint64  size = m_media.size;
	m_fileNameLabel->setTextLimitShrink(filename,190);
	QString filesize("");
	filesize+=convert2ReadableSize(size);
	m_fileSizeLabel->setText(filesize);
	m_fileSizeLabel->move(10,58);
	QPixmap pixmap(getFileType(filename));
	m_fileIconLabel->setPixmap(pixmap.scaled(40 * gDdpi, 40 * gDdpi, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	m_fileIconLabel->setFixedSize(QSize(40 * gDdpi, 40 * gDdpi));

	// cannot use lambda
	connect(m_openfile, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(m_openDir, SIGNAL(clicked()), this, SLOT(openFileDir()));
	connect(m_download, SIGNAL(clicked()), this, SLOT(downloadFile()));
	connect(m_saveas, SIGNAL(clicked()), this, SLOT(saveAsFile()));
	connect(m_redownload, SIGNAL(clicked()), this, SLOT(downloadFile()));

	m_openfile->setVisible(false);
	m_openDir->setVisible(false);
	m_download->setVisible(false);
	m_redownload->setVisible(false);
	m_saveas->setVisible(false);

	CONNECT_SERVICE(ProgressCb(qint64, qint32, qint32, const std::string&));
	CONNECT_SERVICE(DownLoadFile(int,const std::string&,int64));
	m_chatcontrol->RegProcessCb(
		m_localid,
		CBind(&FileMessageItem::signalSerProgressCb,
		this,
		CPlaceholders  _1,
		CPlaceholders  _2,
		CPlaceholders  _3,
		CPlaceholders  _4));

	if ( !m_media.issaveas && (m_isrecv || m_media.isdevice))
	{
		QString localPath = UIUtils::GetDataFullPath(DATAPATH_USERFILE)+UIUtils::GetNameByUrl(m_media.url);
		path = localPath;
	}

	bool bret = UIUtils::IsFileExist(path);
	if (!bret)
	{
		this->setStatus(FILE_DOWNLOAD);
	}
	else{
		m_file = path;
		if (m_isrecv && !m_media.issaveas)
		{
			m_file = UIUtils::GetDataFullPath(DATACACHEPATH_USERFILE)+m_media.name;
		}
		if (!m_media.msgid)
		{
			this->setStatus(FILE_TRANSFORMAT);
		}
		else{
			this->setStatus(FILE_FINISH);
		}
	}
}

void FileMessageItem::translateLanguage(){
	m_openfile->setText(transfer("打开"));
	m_openDir->setText(transfer("打开目录"));
	m_download->setText(transfer("下载"));
	m_saveas->setText(transfer("另存为"));
	m_redownload->setText(transfer("重新下载"));
}

QString FileMessageItem::file() const
{
    return m_file;
}

void FileMessageItem::openFile()
{
	QString destPath = (!m_media.issaveas && (m_isrecv || m_media.isdevice)) ? EnctrptFile() : m_file;
	if (!UIUtils::IsFileExist(destPath)){
		dealdownload();
		tipInfoShow(true);
		return;
	}
#ifdef _WIN32
	QDesktopServices::openUrl(QUrl::fromLocalFile(destPath));
#else
	QDesktopServices::openUrl(QUrl("file:///" + filePath, QUrl::TolerantMode));
#endif 
}

void FileMessageItem::openFileDir()
{
#ifdef _WIN32
	QString destPath =(!m_media.issaveas&&(m_isrecv|| m_media.isdevice))?EnctrptFile():m_file;
	destPath.replace("/", "\\");
	if (!UIUtils::IsFileExist(destPath)){
		dealdownload();
		tipInfoShow(true);
		return;
	}
	
	if (destPath.contains(" "))
	{
		//如果文件名中有空格，explorer会打开失败，用Qt打开
		QFileInfo tempFileInfo(destPath);
		QDesktopServices::openUrl(QUrl::fromLocalFile(tempFileInfo.absolutePath()));
	}
	else
	{
		bool isSucces = QProcess::startDetached("explorer /select, " + destPath);//打开上面获取的目录
	}
#else
	QFileInfo tempFileInfo(filePath);
	QDesktopServices::openUrl(QUrl::fromLocalFile(tempFileInfo.absolutePath()));
#endif 
}
void FileMessageItem::downloadFile(){
	tipInfoShow(false);
	m_media.issaveas = false;
	DownLoadFile();
}
void FileMessageItem::saveAsFile(){
	tipInfoShow(false);
	m_media.issaveas = true;
	QString lastPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + QString("\\") + m_media.name;
	QString filePath = QFileDialog::getSaveFileName(CNull, transfer("文件另存为"),lastPath,transfer("所有文件(*.*)"));
	if(!filePath.isEmpty()){
	 m_media.issaveas = true;
	  DownLoadFile(filePath);
	}
	else{
		m_media.issaveas = false;
	}
}
void FileMessageItem::onSerProgressCb(qint64 localid, qint32 extra_req, qint32 process, const std::string& info){
	if ( m_localid == localid)
	{
		m_progress->setValue(process);
		if (process == 100){
			m_progress->hide();
			this->setStatus(FILE_FINISH);
		}
	}
}

void FileMessageItem::tipInfoShow(bool isVisble)
{
	if (!m_tipInfo){
		m_tipInfo = new QLabel(this);
	}
	m_tipInfo->setText(transfer("文件已被移除"));
	m_tipInfo->move(55 * gDdpi, 30 * gDdpi);
	m_tipInfo->setObjectName("UpFileTip");
	m_tipInfo->setVisible(isVisble);
}

QString FileMessageItem::getFileType(QString fileName)
{
	//文件类型 0.未知文件类型 1.图片 2.word 3.execl 4.ppt 5.视频 6.安装文件 7.压缩文件 8.文本文件 9.pdf
	QString strImageName = "";
	QString strFileExtension = "";
	QString fileIcon(":/fileicon/unknown");

	if (fileName.isEmpty())
	{
		return fileIcon;
	}
	else
	{
		//匹配文件类型对应的文件图标
		QStringList strList = fileName.split(".");
		if (strList.count() <= 1)
		{
			return fileIcon;
		}
		else
		{
			strFileExtension = strList.at(strList.length() - 1);
		}
	}
	QString tempStr = strFileExtension;
	strFileExtension = tempStr.toLower();
	if (0 == strFileExtension.compare("txt"))
	{
		fileIcon = QString(":/fileicon/txt");
	}
	else if ((0 == strFileExtension.compare("doc")) || (0 == strFileExtension.compare("docx")))
	{
		fileIcon = QString(":/fileicon/word");
	}
	else if ((0 == strFileExtension.compare("xls")) || 0 == strFileExtension.compare("xlsx"))
	{
		fileIcon = QString(":/fileicon/execl");
	}
	else if ((0 == strFileExtension.compare("png")) || (0 == strFileExtension.compare("bmp"))
		|| (0 == strFileExtension.compare("jpg")) || (0 == strFileExtension.compare("xpm"))
		|| (0 == strFileExtension.compare("gif")) || (0 == strFileExtension.compare("jpeg"))
		|| (0 == strFileExtension.compare("ico")) || (0 == strFileExtension.compare("tiff")))
	{
		fileIcon = QString(":/fileicon/picture");
	}
	else if ((0 == strFileExtension.compare("ppt")) || (0 == strFileExtension.compare("pptx")))
	{
		fileIcon = QString(":/fileicon/ppt");
	}
	else if ((0 == strFileExtension.compare("rar")) || (0 == strFileExtension.compare("zip")))
	{
		fileIcon = QString(":/fileicon/package");
	}
	else if ((0 == strFileExtension.compare("avi")) || (0 == strFileExtension.compare("3gp"))
		|| (0 == strFileExtension.compare("rmvb")) || (0 == strFileExtension.compare("wav"))
		|| (0 == strFileExtension.compare("flv")) || (0 == strFileExtension.compare("rm"))
		|| (0 == strFileExtension.compare("wmv")) || (0 == strFileExtension.compare("mkv"))
		|| (0 == strFileExtension.compare("mov")) || (0 == strFileExtension.compare("raw"))
		|| (0 == strFileExtension.compare("wma")) || (0 == strFileExtension.compare("amr"))
		|| (0 == strFileExtension.compare("mp4")) || (0 == strFileExtension.compare("mp3"))
		)
	{
		fileIcon = QString(":/fileicon/vidio");
	}
	else if ((0 == strFileExtension.compare("exe")))
	{
		fileIcon = QString(":/fileicon/install");
	}
	else if ((0 == strFileExtension.compare("pdf")))
	{
		fileIcon = QString(":/fileicon/pdf");
	}
	else
	{
		fileIcon = QString(":/fileicon/unknown");
	}
	return fileIcon;
}
void FileMessageItem::DownLoadFile(QString& saveAsPath){
	CSharedPtr<data::DownLoadFile> download = CNull;
	this->setStatus(FILE_TRANSFORMAT);
	download = CMakePtr<data::DownLoadFile>();
	download->bisP2P = false;
	download->bIsResume = true;
	download->fileName = m_media.name.toUtf8().data();
	download->fromUserId = m_media.fromid;
	download->encryptKey = m_media.encrptkey.toUtf8().data();
	download->localId = m_localid;
	download->msgid = m_media.msgid;
	download->targetId = m_media.targetId;
	download->url = m_media.url.toUtf8().data();
	m_progress->show();
	if (saveAsPath.isEmpty())
	{
		QString Path = UIUtils::GetDataFullPath(DATAPATH_USERFILE) + UIUtils::GetNameByUrl(m_media.url);
		download->localPath = Path.toUtf8().data();
	}
	else{
		download->localPath = saveAsPath.toUtf8().data();
	}
	m_chatcontrol->DownLoadFile(download,
								CBind(&FileMessageItem::signalSerDownLoadFile,
								this,
								CPlaceholders  _1,
								CPlaceholders  _2,
								CPlaceholders  _3)
								);
}
void FileMessageItem::onSerDownLoadFile(int err,const std::string&filepath, int64 targetId){
	if ( !err)
	{
		if (m_media.issaveas)
		{
			QString saveAsPath = QString::fromUtf8(filepath.data());
			QString destPath = EnctrptFile(saveAsPath);
			m_file = destPath;
		}
		else{
			QString destPath =EnctrptFile();
			m_file = destPath;
			m_media.issaveas = false;
		}
		this->setStatus(FILE_FINISH);
		if(getCloudDisk())
		{
			emit signalDownfileFinish();
			m_isClouddisk = false;
		}
	}
	else{
		this->setStatus(FILE_FAILED);
	}
	
}
QString FileMessageItem::EnctrptFile(QString saveaspath){

	QString path;
	QString destPath;
	if (m_media.issaveas){
		path = saveaspath;
		destPath = path + ".tmp";
	}
	else{
		path = UIUtils::GetDataFullPath(DATAPATH_USERFILE) + UIUtils::GetNameByUrl(m_media.url);
		destPath = UIUtils::GetDataFullPath(DATACACHEPATH_USERFILE) + UIUtils::GetNameByUrl(m_media.name);
		QString destPathNew = hasFileInCache(destPath);
		if (!destPathNew.isEmpty())
		{
			QFileInfo fileInfo(destPathNew);
			m_fileNameLabel->setTextLimitShrink(fileInfo.fileName(), 190);
			m_media.name = fileInfo.fileName();
			return destPathNew;
		}
		else{
			QFile file(destPath);
			int64 size = file.size();
			if (size != m_media.size){
				destPath = makeFileName(destPath);
				QFileInfo fileInfo(destPath);
				m_fileNameLabel->setTextLimitShrink(fileInfo.fileName(), 190);
				m_media.name = fileInfo.fileName();
			}
		}
	}
	Log(LOG_LEV_ERROR, LOG_FILE, "decryptFileKey:%s", m_media.encrptkey.toStdString().c_str());
	if (!m_media.encrptkey.isEmpty()){
		bool bret = m_chatcontrol->decryptFile(m_media.encrptkey.toUtf8().data(), path.toUtf8().data(), destPath.toUtf8().data());
		if (!bret)
		{
			Log(LOG_LEV_ERROR, LOG_FILE, "decryptFile Failed!");
		}
	}
	else{
		QFile file(path);
		file.copy(path, destPath);
	}
	if (!saveaspath.isEmpty() && m_media.issaveas)
	{
		QFile::remove(path);
		QFile::rename(destPath, path);
		destPath = path;
	}
	return destPath;
	END;
	/*QString path = saveaspath.isEmpty()?UIUtils::GetDataFullPath(DATAPATH_USERFILE)+UIUtils::GetNameByUrl(m_media.url):saveaspath;
	QString destPath =saveaspath.isEmpty()?UIUtils::GetDataFullPath(DATACACHEPATH_USERFILE)+m_media.name:saveaspath+QString(".temp");
	if (!UIUtils::IsFileExist(destPath))
	{
		if(!m_media.encrptkey.isEmpty()){
			bool bret = m_chatcontrol->decryptFile(m_media.encrptkey.toUtf8().data(),path.toUtf8().data(),destPath.toUtf8().data());
			if ( !bret)
			{
				AddLog(LOG_LEV_ERROR,"decryptFile Failed!");
			}
		}else{
			QFile file(path);
			file.copy(path,destPath);
		}

	}
	if (!saveaspath.isEmpty())
	{
		QFile::remove(path);
		QFile::rename(destPath,path);
		destPath = path;
	}*/
	return destPath;
}

QString FileMessageItem::makeFileName(QString localpath, int index)
{
	if (UIUtils::IsFileExist(localpath)){
		QFileInfo fileInfo(localpath);
		QString localpathNew = fileInfo.path() + "/" + fileInfo.baseName() + "(" + QString::number(index) + ")." + fileInfo.suffix();
		if (!UIUtils::IsFileExist(localpathNew)){
			return localpathNew;
		}
		else{
			return makeFileName(localpath, ++index);
		}
	}
	else{
		return localpath;
	}
}

QString FileMessageItem::hasFileInCache(QString localpath)
{
	QFile file(localpath);
	if (file.size() == m_media.size && UIUtils::IsFileExist(localpath)){
		return localpath;
	}
	else{
		for (int i = 0; i<6; ++i){
			QFileInfo fileInfo(localpath);
			QString localpathNew = fileInfo.path() + "/" + fileInfo.baseName() + "(" + QString::number(i) + ")." + fileInfo.suffix();
			if (UIUtils::IsFileExist(localpathNew)){
				QFile file(localpathNew);
				if (file.size() == m_media.size){
					return localpathNew;
				}
			}
		}
	}
	return "";
}

FileMessageItem::~FileMessageItem()
{
	m_chatcontrol->RegProcessCb(m_localid, CNull);
}

class FileMessageWidgetPrivate
{
public:
    void init(IChatMgrControl_Ptr& chatcontrol);

    FileMessageWidget* q_ptr;
    FileMessageItem* fileMessageItem;
};

void FileMessageWidgetPrivate::init(IChatMgrControl_Ptr& chatcontrol)
{
    fileMessageItem = new FileMessageItem(chatcontrol,q_ptr);
    q_ptr->setCentralWidget(fileMessageItem);
}

FileMessageWidget::FileMessageWidget(QWidget* parent) : AbstractMessageWidget(parent), d_ptr(0)
{
    d_ptr = new FileMessageWidgetPrivate;
    d_ptr->q_ptr = this;
    d_ptr->init(m_chatcontrol);
	CONNECT_SERVICE(CloudDisk());
	connect(d_ptr->fileMessageItem,SIGNAL(signalDownfileFinish()),this, SLOT(onSerDownfileFinish()));
}

FileMessageWidget::~FileMessageWidget()
{
    delete d_ptr;
}
void FileMessageWidget::dealSendFile(CSharedPtr<data::Msg>&msg){
	data::MsgFile* msgFile = dynamic_cast<data::MsgFile*>(msg.get());
	if(CNull == msgFile) return;
	QString path = QString::fromUtf8(msgFile->filePath.c_str());
	QFileInfo info(path);
	m_media.size = info.size();
	m_media.name = info.fileName();
	msgFile->fileName = m_media.name.toUtf8();
	msgFile->size = m_media.size;
	msgFile->isResume = true;
	msgFile->isFolder = 0;
	d_ptr->fileMessageItem->setStatus(FILE_TRANSFORMAT);
	setFile(path);
	setMsg(msg);
}
void FileMessageWidget::dealHistoryMsg(CSharedPtr<data::Msg>&msg){
	data::MsgFile* msgFile = dynamic_cast<data::MsgFile*>(msg.get());
	if(CNull == msgFile) return;

	m_media.fromid = msgFile->fromId;
	m_media.targetId = msgFile->targetId;
	m_media.msgid = msgFile->msgId;
	m_media.url= QString::fromUtf8(msgFile->url.c_str());
	m_media.encrptkey = QString::fromUtf8(msgFile->encryptKey.c_str());
	m_media.name = QString::fromUtf8(msgFile->fileName.c_str());
	m_media.size = msgFile->size;
	m_media.isdevice = msgFile->isDeviceMsg;
	m_media.issaveas = msgFile->isSaveAs;
	QString path = QString::fromUtf8(msgFile->filePath.c_str());
	QString filePath = (!msgFile->isRecvMsg)?(path.isEmpty()?m_media.url:path):m_media.url;
	msg->isDeviceMsg?this->setStatus(FILE_DOWNLOAD):((!msgFile->isRecvMsg)?this->setStatus(FILE_FINISH):this->setStatus(FILE_DOWNLOAD));
	if (msg->isRecvMsg) {
		QString cachePath = UIUtils::GetDataFullPath(DATACACHEPATH_USERFILE) + m_media.name;
		if (UIUtils::IsFileExist(cachePath)) {
			setFile(cachePath);
		}
		else if(UIUtils::IsFileExist(path)){
			if (path.contains(UIUtils::GetDataFullPath(DATACACHEPATH_USERFILE))) {
				if (m_media.encrptkey.isEmpty()) {
					QFile file(path);
					file.copy(cachePath);
				}
				else {
					m_chatcontrol->decryptFile(m_media.encrptkey.toStdString(),
						msgFile->filePath, cachePath.toUtf8().data());
				}
				setFile(cachePath);
			}
			else {	//另存为
				setFile(path);
			}
		}
		else {
			setFile(filePath);
		}
	}
	else {
		setFile(filePath);
	}
}
void FileMessageWidget::setFile(CSharedPtr<data::Msg>&msg){
	//文件发送
	if (!msg->isRecvMsg && !msg->isDeviceMsg && !msg->msgId)
	{
		dealSendFile(msg);
	}
	else
	{
		dealHistoryMsg(msg);
	}
	AbstractMessageWidget::setMsg(msg);
}

void FileMessageWidget::setFile(const QString& file)
{
	d_ptr->fileMessageItem->setLocalId(this->uiLocalId());
	d_ptr->fileMessageItem->setIsRecv(this->isRecv());
	d_ptr->fileMessageItem->setMedia(m_media);
    d_ptr->fileMessageItem->setFile(file);
}

QString FileMessageWidget::file() const
{
    return d_ptr->fileMessageItem->file();
}

QSize FileMessageWidget::suggestWidth(int width)
{
    Q_UNUSED(width);
    return d_ptr->fileMessageItem->sizeHint();
}

void FileMessageWidget::initializeContextActions()
{
	AbstractMessageWidget::initializeContextActions();
#if 0
    FlexAction* action = new FlexAction(transfer("Copy"), this);
    addAction(action);

    connect(action, &QAction::triggered, this, [this] {
        qDebug() << "copy";
    });
#endif
}
void FileMessageWidget::setFileStatus(int status){
	d_ptr->fileMessageItem->setStatus(status);
}
void FileMessageWidget::onSerSendMsg(int err,qint64 msgtime,qint64 msgid,qint64 uiLocalId){
	if (!err)
	{
		d_ptr->fileMessageItem->setStatus(FILE_FINISH);
	}
	else{
		d_ptr->fileMessageItem->setStatus(FILE_FAILED);
	}
	AbstractMessageWidget::onSerSendMsg(err,msgtime,msgid,uiLocalId);
}

void FileMessageWidget::onSerCloudDisk()
{
	d_ptr->fileMessageItem->setCloudDisk(true);
	QString Filepath = d_ptr->q_ptr->file();
	if(!UIUtils::IsFileExist(Filepath))
	{
		d_ptr->fileMessageItem->DownLoadFile();
	}
	else
	{
		onSerDownfileFinish();
	}
}

void FileMessageWidget::onSerDownfileFinish()
{
	QString filepath = d_ptr->q_ptr->file();
	data::MsgFile* msgFile = (data::MsgFile*)(msg().get());
	std::string encryptkey = msgFile->encryptKey;
#ifdef CLOUDDISK_ON
	if(m_clouddiskcontrol)
		m_clouddiskcontrol->ShowSelectUploadDirWnd(NULL, encryptkey,filepath.toStdString());
#endif
}
