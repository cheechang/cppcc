#include <QDateTime>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include "GroupFileListItem.h"
#include "controls/headimage.h"
#include "controls/ToolButton.h"
#include "common/Common.h"
#include "common/UIUtils.h"

namespace ui{
	GroupFileListItem::GroupFileListItem(QWidget *parent, int64 id)
		: TWidget(parent), m_id(id), m_iFromId(0),FileUpisFinish(false),isDownding(false)
	{
		m_pChatControl = CHATMGRCONTROL;
		
		m_pMainLayout = new QGridLayout();
		m_pLabelIcon = new QLabel(this);
		m_pLabelName = new QLabel(this);
		m_pLabelSize = new QLabel(this);
		m_pLabelTime = new QLabel(this);
		m_pLabelAuther = new QLabel(this);
		m_pProgress = new QProgressBar(this);
		m_fileUptip = new QLabel(this);
		m_fileDowntip = new QLabel(this);
		m_CancelTip = new QLabel(this);

		timer = new QTimer(this);
		
		
		m_pButtonDownload = new ToolButton(":/group/downloadFile", this, false);
		m_pButtonOpenFile = new ToolButton(":/group/openFile", this, false);

		m_pButtonDownload->setToolTip(transfer("下载"));
		m_pButtonOpenFile->setToolTip(transfer("打开所在目录"));
		m_pButtonOpenFile->hide();
		m_pButtonDownload->hide();
		m_pProgress->setFixedHeight(2*gDdpi);
		m_pProgress->setFixedWidth(240*gDdpi);
		m_pProgress->setMinimum(0);
		m_pProgress->setMaximum(100*gDdpi);
		m_pProgress->setValue(0);
		m_pProgress->setTextVisible(false);
		m_pProgress->setVisible(false);

		m_pLabelAuther->setFixedWidth(67*gDdpi);
		m_pMainLayout->addWidget(m_pLabelIcon, 0, 0, 2, 1);
		m_pMainLayout->addWidget(m_pLabelName, 0, 1, 1, 2);
		m_pMainLayout->addWidget(m_pLabelSize, 1, 1);
		m_pMainLayout->addWidget(m_pLabelAuther, 1, 2);
		m_pMainLayout->setColumnMinimumWidth(1, 67*gDdpi);
		m_pMainLayout->addWidget(m_pProgress, 1, 2, 1, 2);
		m_pMainLayout->addWidget(m_pLabelTime, 0, 3, Qt::AlignRight);
		m_pMainLayout->setColumnMinimumWidth(2*gDdpi, 240*gDdpi);
		m_pMainLayout->addWidget(m_pButtonDownload, 0, 4, 2, 1);
		m_pMainLayout->addWidget(m_pButtonOpenFile, 0, 4, 2, 1);
		m_pMainLayout->setSpacing(10*gDdpi);
		//m_pMainLayout->setContentsMargins(10, 0, 10, 0);
		this->setLayout(m_pMainLayout);

		m_fileUptip->setText(transfer("上传文件失败"));
		m_fileUptip->setObjectName("UpFileTip");
		m_fileUptip->move(230,30);
		m_fileUptip->hide();

		m_fileDowntip->setText(transfer("下载文件失败"));
		m_fileDowntip->setObjectName("UpFileTip");
		m_fileDowntip->move(230,30);
		m_fileDowntip->hide();

		m_CancelTip->setText(transfer("取消失败"));
		m_CancelTip->setObjectName("UpFileTip");
		m_CancelTip->move(230,30);
		m_CancelTip->hide();
		

		connect(m_pButtonOpenFile, SIGNAL(clicked()), this, SLOT(openFileDir()));
		connect(m_pButtonDownload, SIGNAL(clicked()), this, SLOT(downloadFile()));
		connect(timer,SIGNAL(timeout()),this, SLOT(onSerSetTip()));
		CONNECT_SERVICE(ProgressCb(qint64, qint32, qint32, const std::string&));
		CONNECT_SERVICE(DownLoadFile(int, const std::string&, int64));
		
		

		m_pChatControl->RegProcessCb(id, CBind(&GroupFileListItem::signalSerProgressCb,
			this, CPlaceholders  _1, CPlaceholders  _2, CPlaceholders  _3, CPlaceholders  _4));
	}

	GroupFileListItem::~GroupFileListItem()
	{
		if(m_id != 0)
		{
			m_pChatControl->RegProcessCb(m_id, CNull);
		}
	}

	void GroupFileListItem::setData(const data::FileInfo& file)
	{
		m_id = file.fileid;
		m_iFromId = file.userid;
		m_strEncryptKey = QString::fromUtf8(file.encrypt_key.data());
		m_strUrl = QString::fromUtf8(file.url.data());

		QString temp = QString::fromUtf8(file.name.data());
		QPixmap pixmap(getFileType(temp));
		m_pLabelIcon->setPixmap(pixmap.scaled(40*gDdpi, 40*gDdpi, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		m_pLabelIcon->setFixedSize(QSize(40*gDdpi, 40*gDdpi));

		m_pLabelName->setText(temp);
		m_pLabelName->setToolTip(temp);

		temp = QString::fromUtf8(file.size.data());
		m_pLabelSize->setText(temp);
		
		QString strDate = QDateTime::fromMSecsSinceEpoch(file.time).toString("MM-dd hh:mm:ss");
		m_pLabelTime->setText(strDate);
		
		temp = QString::fromUtf8(file.auther.data());
		//m_pLabelAuther->setText(tr("上传者：") + temp);
		
		/*m_orgfilepath = file.path.empty()
			? UIUtils::GetDataFullPath(DATAPATH_USERFILE) + UIUtils::GetNameByUrl(m_strUrl)
			: QString::fromUtf8(file.path.data());*/
		///* 判断文件是否已经存在本地 */
		QString path = file.path.empty()
			? UIUtils::GetDataFullPath(DATAPATH_USERFILE) + UIUtils::GetNameByUrl(m_strUrl)
			: QString::fromUtf8(file.path.data());
		if (UIUtils::IsFileExist(path))
		{
			m_pButtonDownload->hide();
			m_pButtonOpenFile->show();
			m_strFilePath = path;
		}
		else
		{
			m_pButtonDownload->show();
			m_pButtonOpenFile->hide();
		}
	}
	
	void GroupFileListItem::downloadFile()
	{
		if (m_pProgress->isVisible())
		{
			return;
		}
		m_pProgress->show();
		isDownding = true;
		SetOperType(FILEDOWNOP);
		CSharedPtr<data::DownLoadFile> pDownload = CNull;
		pDownload = CMakePtr<data::DownLoadFile>();
		pDownload->bisP2P = false;
		pDownload->bIsResume = true;
		pDownload->fileName = m_pLabelName->text().toUtf8().data();
		pDownload->fromUserId = m_iFromId;
		pDownload->encryptKey = m_strEncryptKey.toUtf8().data();
		pDownload->localId = m_id;
		pDownload->url = m_strUrl.toUtf8().data();
		QString Path = UIUtils::GetDataFullPath(DATAPATH_USERFILE) + UIUtils::GetNameByUrl(m_strUrl);
		pDownload->localPath = Path.toUtf8().data();
		m_pChatControl->DownLoadFile(pDownload,
									CBind(&GroupFileListItem::signalSerDownLoadFile,
									this,
									CPlaceholders  _1,
									CPlaceholders  _2,
									CPlaceholders  _3)
									);
	}

	void GroupFileListItem::onSerDownLoadFile(int err, const std::string& filepath, int64 targetId)
	{
		if (err == 0)
		{
			//if (m_media.issaveas)
			//{
			//	QString saveAsPath = QString::fromUtf8(filepath.data());
			//	QString destPath = EnctrptFile(saveAsPath);
			//	m_file = destPath;
			//}
			//else
			//{
			//	m_strFilePath = enctrptFile();
			//}
			enctrptFile();
			m_pButtonDownload->hide();
			m_pButtonOpenFile->show();
			m_pProgress->hide();
			isDownding = false;
		}
		else
		{
			m_fileDowntip->show();
			timer->start(6000);
			m_pButtonDownload->show();
			m_pButtonOpenFile->hide();
			m_pProgress->hide();
		}
		//m_media.issaveas = false;
	}
	void GroupFileListItem::onSerProgressCb(qint64 localid, qint32 extra_req, qint32 process, const std::string& info)
	{
		if (m_id == localid)
		{
			m_pButtonDownload->hide();
			m_pProgress->setValue(process);
		}
	}

	void GroupFileListItem::onSerFileUpProGress(qint32 progress)
	{
		if(progress == 100)
		{
			setProgressVisible(false);
			FileUpisFinish = false;
			SetDownOrOpen();
		}
		else
		{
			m_pProgress->setValue(progress);
		}
	}
	
	void GroupFileListItem::openFileDir()
	{
		QString destPath = enctrptFile();//!m_media.issaveas ? enctrptFile() : m_strFilePath;
		destPath.replace("/", "\\");
		if (destPath.contains(" "))
		{
			//如果文件名中有空格，explorer会打开失败，用Qt打开
			QFileInfo tempFileInfo(destPath);
			QDesktopServices::openUrl(QUrl::fromLocalFile(tempFileInfo.absolutePath()));
		}
		else
		{
			//打开上面获取的目录
			bool isSucces = QProcess::startDetached("explorer /select, " + destPath);
		}
	}

	QString GroupFileListItem::getFileType(QString fileName)
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

	QString GroupFileListItem::enctrptFile(QString saveaspath)
	{
		QString path = saveaspath.isEmpty()
			? UIUtils::GetDataFullPath(DATAPATH_USERFILE) + UIUtils::GetNameByUrl(m_strUrl)
			: saveaspath;
		QString destPath = saveaspath.isEmpty()
			? UIUtils::GetDataFullPath(DATACACHEPATH_USERFILE) + m_pLabelName->text()
			: saveaspath + QString(".temp");
		if (!UIUtils::IsFileExist(destPath))
		{
			bool bret = m_pChatControl->decryptFile(m_strEncryptKey.toUtf8().data(), path.toUtf8().data(), destPath.toUtf8().data());
			if (!bret)
			{
				//AddLog(LOG_LEV_ERROR,"decryptFile Failed!");
			}
		}
		if (!saveaspath.isEmpty())
		{
			QFile::remove(path);
			QFile::rename(destPath,path);
			destPath = path;
		}
		return destPath;
	}


	void GroupFileListItem::setProgressVisible(bool isShow)
	{
		m_pProgress->setVisible(isShow);
	}

	void GroupFileListItem::SetUpFileState(bool IsFinish)
	{
		FileUpisFinish = IsFinish;
	}

	bool GroupFileListItem::GetUpFileState()
	{
		return FileUpisFinish;
	}

	void GroupFileListItem::setfilelocalid(int64 filelocalid)
	{
		SendFileLocalId = filelocalid;
	}

	int64 GroupFileListItem::Getfilelocalid()
	{
		return SendFileLocalId;
	}

	void GroupFileListItem::setNewData(const data::FileInfo& file)
	{
		m_id = file.fileid;
		m_iFromId = file.userid;
		m_strEncryptKey = QString::fromUtf8(file.encrypt_key.data());
		m_strUrl = QString::fromUtf8(file.url.data());

		QString temp = QString::fromUtf8(file.name.data());
		QPixmap pixmap(getFileType(temp));
		m_pLabelIcon->setPixmap(pixmap.scaled(40*gDdpi, 40*gDdpi, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		m_pLabelIcon->setFixedSize(QSize(40*gDdpi, 40*gDdpi));

		m_pLabelName->setText(temp);
		m_pLabelName->setToolTip(temp);

		temp = QString::fromUtf8(file.size.data());
		m_pLabelSize->setText(temp);
		
		QString strDate = QDateTime::fromMSecsSinceEpoch(file.time).toString("MM-dd");
		m_pLabelTime->setText(strDate);
		
		temp = QString::fromUtf8(file.auther.data());
		//m_pLabelAuther->setText(tr("上传者：") + temp);
		
		m_orgfilepath = file.path.empty()
			? UIUtils::GetDataFullPath(DATAPATH_USERFILE) + UIUtils::GetNameByUrl(m_strUrl)
			: QString::fromUtf8(file.path.data());
		///* 判断文件是否已经存在本地 */
		/*	QString path = file.path.empty()
		? UIUtils::GetDataFullPath(DATAPATH_USERFILE) + UIUtils::GetNameByUrl(m_strUrl)
		: QString::fromUtf8(file.path.data());
		if (UIUtils::IsFileExist(path))
		{
		m_pButtonDownload->hide();
		m_pButtonOpenFile->show();
		m_strFilePath = path;
		}
		else
		{
		m_pButtonDownload->show();
		m_pButtonOpenFile->hide();
		}*/
	}

	void GroupFileListItem::SetDownOrOpen()
	{
		///* 判断文件是否已经存在本地 */
		//QString path = file.path.empty()
		//	? UIUtils::GetDataFullPath(DATAPATH_USERFILE) + UIUtils::GetNameByUrl(m_strUrl)
		//	: QString::fromUtf8(file.path.data());

		if (UIUtils::IsFileExist(m_orgfilepath))
		{
			m_pButtonDownload->hide();
			m_pButtonOpenFile->show();
			m_strFilePath = m_orgfilepath;
		}
		else
		{
			m_pButtonDownload->show();
			m_pButtonOpenFile->hide();
		}
	}

	void GroupFileListItem::Setfileurl(std::string url)
	{
		m_strUrl = QString::fromUtf8(url.data());
	} 

	QString GroupFileListItem::GetfileUrl()
	{
		return m_strUrl;
	}

	void GroupFileListItem::SetTipVisible(bool istrue,int type)
	{
		if(type == 1)
		{
			istrue? m_fileUptip->show():m_fileUptip->hide();
		}
		if(type == 2) //取消
		{
			m_CancelTip->show();
		}
		
	}

	void GroupFileListItem::StartTimer(int ntime)
	{
		timer->start(ntime);
	}

	void GroupFileListItem::SetOperType(OPERTYPE type)
	{
		opertype = type;
	}

	int GroupFileListItem::GetOperType()
	{
		return opertype;
	}

	void ui::GroupFileListItem::onSerSetTip()
	{
		if(GetIsDowning())
		{
			m_fileDowntip->hide();
		}
		else
		{
			m_CancelTip->hide();
		}
		
	}

}
