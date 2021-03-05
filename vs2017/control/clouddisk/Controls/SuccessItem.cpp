#include "SuccessItem.h"
#include "QClickLabel.h"
#include "PushButton.h"
#include "MyLineEdit.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>
#include <QProgressBar>
#include "MyMessageBox.h"
#include <QFileInfo>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>
#include <QFileDialog>
#include <QProcess>
namespace ui{
	SuccessItem::SuccessItem(QWidget *parent) :QWidget(parent)
	, m_progress(nullptr)
	, m_openDir(nullptr)
	, m_openFile(nullptr)
	, m_row(-1)
	, m_pro(0)
	, m_localId(0)
	{
		setMouseTracking(true);

		m_mainlayout = new QHBoxLayout(this);
		m_progress = new QLabel(this);
		m_progress->setPixmap(QPixmap(QString(":/img/sucess")));
		m_openFile = new QClickLabel(this);
		m_openDir = new QClickLabel(this);
		m_openDir->setText(QString::fromUtf8("打开目录"));
		m_openDir->setTextColor(QColor(19, 134, 235));
		m_openDir->setUnderlined(true);
		m_openFile->setText(QString::fromUtf8("打开"));
		m_openFile->setTextColor(QColor(19, 134, 235));
		m_openFile->setUnderlined(true);
		
		m_mainlayout->setSpacing(5);
		m_mainlayout->setContentsMargins(3, 0, 3, 0);
		m_mainlayout->setAlignment(Qt::AlignCenter);
		m_mainlayout->addWidget(m_progress);
		m_mainlayout->addWidget(m_openFile);
		m_mainlayout->addWidget(m_openDir);
		m_mainlayout->addStretch();
		this->setLayout(m_mainlayout);
		m_openFile->setVisible(false);
		m_openDir->setVisible(false);
		//打开
		m_fileservice = FILESERVICE;
		connect(m_openFile, SIGNAL(signalClicked(model::CloudFileInfo)), this, SLOT(onOpenFile()));
		//打开文件夹
		connect(m_openDir, SIGNAL(signalClicked(model::CloudFileInfo)), this, SLOT(onOpenDir()));
		
	}
	SuccessItem::~SuccessItem(){

	}
	void SuccessItem::onGetpath(QString path, int64 localId){
		m_filePath = path;
		m_localId = localId;
	}
	void SuccessItem::onOpenDir(){
#ifdef _WIN32
		m_filePath.replace("/", "\\");
			//如果文件名中有空格，explorer会打开失败，用Qt打开
		QFileInfo tempFileInfo(m_filePath);
		QDesktopServices::openUrl(QUrl::fromLocalFile(tempFileInfo.absolutePath()));
		//AddLog(LOG_LEV_INFO, "m_filePath = %s", m_filePath.toLocal8Bit().data());
#else
		QFileInfo tempFileInfo(m_filePath);
		QDesktopServices::openUrl(QUrl::fromLocalFile(tempFileInfo.absolutePath()));
		AddLog(LOG_LEV_INFO, "m_filePath = %s", m_filePath.toLocal8Bit().data());
#endif 
	}
	void SuccessItem::onOpenFile(){
		QDesktopServices::openUrl(QUrl::fromLocalFile(m_filePath));
	}
	void SuccessItem::onDecryptFile(int64 localId,model::CloudFileInfo& data, std::string& path){
		if (m_localId == localId){

			if (!data.encryptKey.empty()){
				QString encrytname("");
				QFileInfo qfile(data.filePath.data());
				encrytname = qfile.baseName();
				
				QString filepath = QString::fromStdString(path) + encrytname;
				QString filename = QString::fromStdString(data.fileName + "." + data.fileSuffix);
				QString outPath("");
				bool decry =  decryptFile(data.encryptKey, filepath, filename, outPath, QString::fromStdString(path));
				//AddLog(LOG_LEV_INFO, "outPath = %s", outPath.toLocal8Bit().data());
				if (decry){
					
					m_filePath = outPath;
					m_openFile->setVisible(true);
					m_openDir->setVisible(true);
				}
			}
			else{
				QString encrytname("");
				QFileInfo qfile(data.filePath.data());
				encrytname = qfile.baseName();
				QString filepath = QString::fromStdString(path) + encrytname;
				QString outPath("");	
				outPath = QString::fromStdString(path) + QString("clouddisk/") + QString::fromUtf8(data.fileName.data()) +"."+ QString::fromUtf8(data.fileSuffix.data());
				//AddLog(LOG_LEV_INFO, "outPath = %s", outPath.toLocal8Bit().data());
				QFile::copy(filepath, outPath);
				m_filePath = outPath;
				m_openFile->setVisible(true);
				m_openDir->setVisible(true);
			}

		}
	}
	bool SuccessItem::decryptFile(std::string encryptKey, QString filePath, QString fileName, QString&outPath, QString inCachePath){
		QString cachePath("");
		QDir tempDir;

		cachePath = inCachePath + "clouddisk/";

		if (filePath.isEmpty() || fileName.isEmpty())
		{
			return false;
		}
		outPath.clear();
		outPath.append(cachePath);
		if (!tempDir.exists(outPath))
		{
			tempDir.mkdir(outPath);
		}
		outPath = getDecryptFilePath(outPath, fileName);
		if (QFile::exists(outPath))
		{
			return true;
		}
		//存在并且不是另存为的加密文件，则解密
		bool decyCode = m_fileservice->decryptFile(encryptKey.c_str(), filePath.toUtf8().data(), outPath.toUtf8().data());
		if (!decyCode)
		{
			outPath.clear();
			return false;
		}
		else{
			return true;
		}
	}
	QString SuccessItem::getDecryptFilePath(QString cacheDirPath, QString fileName)
	{
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

	bool SuccessItem::IsFileExist(QString path){
		bool bret = false;
		QFileInfo fileInfo;
		fileInfo.setFile(path);
		if (!path.isEmpty() && fileInfo.exists())
		{
			bret = true;
		}
		return bret;
	}
	
}