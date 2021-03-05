#include "MiniVedioMessageWidget.h"
//#include "MiniVedioMessageWidgetWidget.h"
#include <QWidget>
#include <QProgressBar>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QMovie>
#include <QFileInfo>
#include <QTimer>
#include <QEventLoop>
#include <QTime>
#include "common/ChineseInfos.hpp"
#include "common/UIUtils.h"
#include "controls/PushButton.h"
#include "controls/ClickQLabel.h"
#include <log/log.h>
#include "MyRightMenu.h"

namespace ui
{
	MiniVedioMessageWidget::MiniVedioMessageWidget(QWidget *parent):AbstractMessageWidget(parent),
		m_process(NULL),moviePlay(NULL),imglabel(NULL),mimgwidget(NULL),mstackwidget(NULL),	
		mainlayout(NULL),m_strUrl(""),m_strCachePath(""),m_strImgUrl(""),m_strImgPath(""),m_strVedioPath(""),
		IsSetValue(false)
															
	{
		m_oriWidth = 0;
		initWidgets();
	}

	MiniVedioMessageWidget::~MiniVedioMessageWidget()
	{
		if (m_process)
		{
			m_process->kill();
		}
		m_process = NULL;
	}

	void MiniVedioMessageWidget::setLoadVideo()
	{
		imglabel->setMovie(moviePlay);
		moviePlay->start();
	}


	void MiniVedioMessageWidget::initWidgets()
	{
		mstackwidget = new QStackedWidget(this);

		imglabel = new ClickQLabel(this);
		connect(imglabel,SIGNAL(clicked()),this,SLOT(onSerPlayVideo()));

		imglabel->setPixmap(QPixmap(":/chat/VideoPlayer"));
		moviePlay = new QMovie(":/chat/loadVideo");
		mainlayout = new QVBoxLayout(this);
		mainlayout->addWidget(imglabel, 0, Qt::AlignCenter);
		mainlayout->setContentsMargins(0,0,0,0);
		mimgwidget = new QLabel(this);
		mimgwidget->setLayout(mainlayout);	
		mstackwidget->addWidget(mimgwidget);
		this->setCentralWidget(mstackwidget);

		CONNECT_SERVICE(DownVedioMsgResult(int, const std::string&, int64, bool));
		CONNECT_SERVICE(DownLoadImg(int, const std::string&, int64));
	}

	void MiniVedioMessageWidget::SetMsg(MsgDataPtr& msg)
	{
		AbstractMessageWidget::setMsg(msg);
		data::MsgMiniVedio* videomsg = (data::MsgMiniVedio*)msg.get();
		//m_RightMenu.setMenuState(MENU_SILENT_PLAY, true);
		//connect(&m_RightMenu, SIGNAL(signalCtrlSilentPlayMenu(int64,int64)),
		//	this, SLOT(onCtrlSilentPlayMenu()));

		SetSourcePath(videomsg->vedioFileName,
			videomsg->preImgPath,
			videomsg->vedioHight,
			videomsg->vedioWideth,
			videomsg->encryptKey);

		QString path = QString::fromStdString(m_strVedioPath);
		if (UIUtils::IsFileExist(path))
		{
			if(m_strCachePath == "")
			{
				m_strCachePath = (UIUtils::GetDataFullPath(DATACACHEPATH_USERVIDEO)
					+ UIUtils::GetNameByUrl(path)).toStdString();
				if(!IsSetValue)
				{
					IsSetValue = true;
				}
			}
		}
		downLoadImg(m_strImgUrl, true);
		Log(LOG_LEV_INFO, LOG_FILE, "enkey:%s,path:%s",
			videomsg->encryptKey.c_str(), videomsg->localVedioPath.c_str());
	}

	void MiniVedioMessageWidget::SetSourcePath(std::string pVideopath, std::string pPreImgPath,
		int64 pHight, int64 pWideth,std::string encryptkey)
	{
		m_strVedioPath = (UIUtils::GetDataFullPath(DATAPATH_USERVIDEO)
			+ UIUtils::GetNameByUrl(pVideopath.c_str())).toStdString();
		m_strUrl = pVideopath;
		m_strImgUrl = pPreImgPath;
		vedioHight = pHight;
		vedioWideth = pWideth;
		encyptkey = encryptkey;
	}

	QSize MiniVedioMessageWidget::suggestWidth(int width)
	{
		return QSize(200, 220);
	}

	QString MiniVedioMessageWidget::decryptFile(const std::string& url, std::string& Key)
	{
		QString path = QString::fromUtf8(url.data());
		QString destPath = UIUtils::GetDataFullPath(DATACACHEPATH_USERVIDEO)
			+ UIUtils::GetNameByUrl(QString::fromUtf8(url.data()));
		if (UIUtils::IsFileExist(path))
		{
			if(Key.empty())
			{
				QFile file(path);
				file.copy(destPath);
			}
			else
			{
				bool bret = m_chatcontrol->decryptFile(Key, path.toUtf8().data(),
					destPath.toUtf8().data());
				Log(LOG_LEV_INFO,LOG_FILE,"decryfile:%d",bret);
			}
			m_strCachePath = destPath.toStdString();
		}
		return destPath;
	}

	void MiniVedioMessageWidget::onSerDownLoadAduioMsg(std::string url,bool isSilent)
	{
		Log(LOG_LEV_INFO,LOG_FILE,"url=%s",url.c_str());
		CSharedPtr<data::DownLoadFile> download = CNull;
		download = CMakePtr<data::DownLoadFile>();

		download->bisP2P = false;
		download->bIsResume = false;
		data::MsgMiniVedio* vediomsg = (data::MsgMiniVedio*)msg().get();

		download->encryptKey = vediomsg->encryptKey;
		download->fileName = vediomsg->vedioFileName;
		QString localPath = UIUtils::GetDataFullPath(DATAPATH_USERVIDEO);
		Log(LOG_LEV_INFO,LOG_FILE,"Enter onSerDownLoadAduioMsg path=%s",localPath.toLocal8Bit().data());

		QString path = UIUtils::GetDataFullPath(DATAPATH_USERVIDEO) + UIUtils::GetNameByUrl(vediomsg->vedioFileName.c_str());
		download->localPath = path.toUtf8().data();
		download->fromUserId = vediomsg->fromId;
		download->localId = vediomsg->localId;
		download->msgid = vediomsg->msgId;
		download->url = vediomsg->vedioFileName;
		download->targetId = vediomsg->targetId;

		Log(LOG_LEV_INFO,LOG_FILE,"Enter onSerDownLoadAduioMsg path=%s",path.toLocal8Bit().data());
		m_chatcontrol->DownLoadFile(download,
			CBind(&MiniVedioMessageWidget::signalSerDownVedioMsgResult, this,
			CPlaceholders  _1, CPlaceholders  _2, CPlaceholders  _3, isSilent));
	}

	void MiniVedioMessageWidget::onSerDownVedioMsgResult(int code,
		const std::string& path, int64 senderID, bool isSilent)
	{
		Log(LOG_LEV_INFO, LOG_FILE, "code = %d", code);
		if (!code)
		{
			std::string key = ((data::MsgMiniVedio*)(msg().get()))->encryptKey;
			if (key.empty())
			{
				m_strVedioPath = path;
			}
			else
			{
				m_strVedioPath = decryptFile(path, key).toStdString();
			}
			/*data::MsgMiniVedio* vediomsg = (data::MsgMiniVedio*)msg().get();
			if (vediomsg->vedioHight <vediomsg->vedioWideth){
				m_strCachePath = srcConvertMp4(m_strVedioPath.c_str()).toStdString();
			}
			else{
				m_strCachePath = m_strVedioPath;
			}*/
			m_strCachePath = m_strVedioPath;
		}
		setFinishLoad();
	}

	void MiniVedioMessageWidget::dealVideopalyerPro()
	{
		QProcess killPro;
		QString c = "taskkill /im ffplay.exe /f";
		killPro.execute(c);
		killPro.close();
	}

	void MiniVedioMessageWidget::palyMinVideo(bool isSilent)
	{
		Log(LOG_LEV_INFO,LOG_FILE,"Enter palyMinVideo");
		imglabel->setPixmap(QPixmap(":/chat/VideoPlayer"));
		QString path = QString::fromStdString(m_strVedioPath);
		path = UIUtils::RepairLocalFilePath(path);
		if (UIUtils::IsFileExist(path))
		{
			if(m_strCachePath == "")
			{
				m_strCachePath = (UIUtils::GetDataFullPath(DATACACHEPATH_USERVIDEO)
					+ UIUtils::GetNameByUrl(path)).toStdString();
			}
			QString tempath= QString::fromStdString(m_strCachePath);
			if(!UIUtils::IsFileExist(tempath))
			{
				decryptFile(path.toStdString(),encyptkey);
			}
			Log(LOG_LEV_INFO,LOG_FILE,"Enter Exsit palyMinVideo");
			dealVideopalyerPro();
			QFile file(tempath);
			if (!file.exists()){
				return;
			}
			QString	ExeName = QString("ffplay.exe");
			QStringList arguments;
			m_process = new QProcess(this);
			arguments << "-window_title";
			arguments << APP_NAME;
			arguments << "-autoexit";
			arguments << "-x";
			arguments << "360";
			arguments << "-y";
			arguments << "460";
			arguments << tempath;
			m_process->start(ExeName, arguments);
		}
		else
		{
			Log(LOG_LEV_INFO,LOG_FILE,"Enter palyMinVideo onSerDownLoadAduioMsg");
			setLoadVideo();
			onSerDownLoadAduioMsg(m_strUrl,isSilent);
		}
	}

	void MiniVedioMessageWidget::onSerPlayVideo()
	{	
		palyMinVideo();
	}

	void MiniVedioMessageWidget::downLoadImg(std::string& url,bool isSrc)
	{
		QString path = UIUtils::GetDataFullPath(DATACACHEPATH_USERIMG) 
			+ UIUtils::GetPicNameByUrl(QString::fromUtf8(url.data()));
		path = UIUtils::RepairLocalFilePath(path);
		if (UIUtils::IsFileExist(path))
		{
			m_strImgPath = path.toStdString();
			PlayFinish();
		}
		else
		{
			int64 id = this->targetId();
			m_chatcontrol->DownLoadImage(id, url,
				CBind(&MiniVedioMessageWidget::signalSerDownLoadImg,
				this, CPlaceholders _1, CPlaceholders  _2, CPlaceholders  _3));
		}
	}

	void MiniVedioMessageWidget::onSerDownLoadImg(int err,
		const std::string& imgname, int64 targetid)
	{
		if ( !err)
		{
			std::string url = imgname;
			m_strImgPath = enctrptFile(url,encyptkey).toStdString();
			setImgBackgroundColor();
			mstackwidget->setCurrentWidget(mimgwidget);
			//onSerPlayVideo();
		}
	}

	QString MiniVedioMessageWidget::enctrptFile(std::string&url,std::string&encrptkey,FileDefaultPathType filepath/*=DATAPATH_USERIMG*/,FileCachePathType cacheType/*=DATACACHEPATH_USERIMG*/)
	{
		QString path = UIUtils::GetDataFullPath(filepath)+QString::fromUtf8(url.data());
		QString destPath = UIUtils::GetDataFullPath(cacheType)+UIUtils::GetNameByUrl(QString::fromUtf8(url.data()));
		if ( UIUtils::IsFileExist(path) && !encrptkey.empty())
		{
			bool bret = m_chatcontrol->decryptFile(encrptkey,path.toUtf8().data(),destPath.toUtf8().data());
			if ( !bret)
			{
				destPath="";
			}
		}
		else{
			QFile file(path);
			file.copy(destPath);
		}
		return destPath;
	}

	void MiniVedioMessageWidget::setImgBackgroundColor()
	{
		QPixmap pix;
		bool ret = pix.load(m_strImgPath.c_str());
		pix = pix.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
		mimgwidget->setPixmap(pix);
	}

	void MiniVedioMessageWidget::PlayFinish()
	{
		mstackwidget->setCurrentWidget(mimgwidget);
	}

	QString MiniVedioMessageWidget::srcConvertMp4(QString srcPath)
	{
		if ((srcPath.right(4) != ".mp4") || (srcPath.length() == 0) || (srcPath == ""))
		{
			printf("format error, is not mp4 file!");
			return "";
		}

		QString			 ExeName = QString("ffmpeg.exe");
		QStringList		 processAgrc;
		QString			outAviPath = srcPath;
		QString tmpFile = srcPath;
		tmpFile = tmpFile.replace(".mp4", "_temp.mp4");
		QFile file(srcPath);
		file.rename(tmpFile);


		if (m_process != NULL)
		{
			m_process->kill();
			m_process = NULL;
		}
		m_process = new QProcess;
		QObject::connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFormatConvertFinished(int, QProcess::ExitStatus)), Qt::QueuedConnection);

		//processAgrc << "-i" << srcPath << "-vf" <<"transpose=1"<< "-qscale" << "4" << "-r" << "24" << "-y" << outAviPath;
		processAgrc << "-i" << tmpFile << "-vf" << "transpose=1" << outAviPath;
		m_process->start(ExeName, processAgrc);
		
		QTime dieTime = QTime::currentTime().addMSecs(100);
		while (QTime::currentTime() < dieTime)
			QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

		return outAviPath;
	}

	void MiniVedioMessageWidget::onFormatConvertFinished(int exitCode, QProcess::ExitStatus exitStatus)
	{
		printf("convert success!!!");
		m_process->deleteLater();
		m_process = NULL;

		QString tmpFile = m_strCachePath.c_str();
		tmpFile = tmpFile.replace(".mp4", "_temp.mp4");
		QFile file(tmpFile);
		file.remove();
	}

	QString MiniVedioMessageWidget::GetAviVideoPath(QString pVideoPath)
	{
		if ((pVideoPath.right(4) != ".mp4") || (pVideoPath.length() == 0) || (pVideoPath == ""))
		{
			printf("format error, is not mp4 file!");
			return "";
		}

		QString destPath = UIUtils::GetDataFullPath(DATACACHEPATH_USERVIDEO) + UIUtils::GetNameByUrl(QString::fromUtf8(pVideoPath.toStdString().c_str()));

		QString	outAviPath = destPath;

		QFile fileInfo(destPath);
		QString fileSize = QString::number(fileInfo.size());
		outAviPath.replace(".mp4", fileSize + "_temp.avi");
		fileInfo.close();
		return outAviPath;
	}

	void MiniVedioMessageWidget::paintEvent(QPaintEvent *e)
	{
		if(mimgwidget && mimgwidget->isVisible()){
			if(m_oriWidth != this->size().width()){
				m_oriWidth = this->size().width();
				setImgBackgroundColor();
			}
		}
		AbstractMessageWidget::paintEvent(e);
	}

	void MiniVedioMessageWidget::onCtrlSilentPlayMenu()
	{
		palyMinVideo(true);
	}

	void MiniVedioMessageWidget::setFinishLoad()
	{
		moviePlay->stop();
		imglabel->setPixmap(QPixmap(":/chat/VideoPlayer"));
	}
}