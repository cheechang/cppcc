#include "RecordMessageWidget.h"
#include <QLabel>
#include <QMouseEvent>
#include <QPixMap>
#include "../Record.h"
#include "common/UIUtils.h"
#include <QMovie>
#include <QHBoxLayout>

    RecordMessageWidget::RecordMessageWidget(QWidget* parent) : AbstractMessageWidget(parent),m_audioPath("")
    {
        initWidget();
        m_isMsgRecv = false;
        QObject::connect(m_record,SIGNAL(signalPlayFinish()),this,SLOT(onPlayFinished()));
        CONNECT_SERVICE(DownAudioMsgResult(int, const std::string&, int64));
    }

     void RecordMessageWidget::initWidget()
     {
        //m_record = new Record(this);
		m_record = Record::getInstance();
        m_MsgTime = new QLabel(this);
        m_MsgGif = new QLabel(this);
        m_MsgPng = new QLabel(this);
        m_MsgPng->setFixedSize(10,14);
        m_MsgPng->setScaledContents(true);
        m_MsgGif->setVisible(false);
        m_mainLayout = new QHBoxLayout();

        m_mainLayout->addWidget(m_MsgTime);
        m_mainLayout->addSpacing(5);
        m_mainLayout->addWidget(m_MsgPng);
        m_mainLayout->addWidget(m_MsgGif);
        m_mainLayout->addStretch();
        this->setLayout(m_mainLayout);
     }
    RecordMessageWidget::~RecordMessageWidget()
    {
    }

    QSize RecordMessageWidget::suggestWidth( int width )
    {
        QSize size = QSize(120,10);
        return size;
    }

    void RecordMessageWidget::SetRecordMsg( std::shared_ptr<data::Msg>&msg )
    {
        if (NULL == msg)
        {
           return;
        }

        int recordTIme =  ((data::MsgAudio*)msg.get())->mediaTime /1000;
        QString strTime = QString::number(recordTIme) + " \"";

        m_isMsgRecv = ((data::MsgAudio*)msg.get())->isRecvMsg;
        m_audioPath = ((data::MsgAudio*)msg.get())->meidaUrl;
        QString url= "";
        if (m_isMsgRecv)
        {
            m_moviePlay = new QMovie(":/chat/audioLeftGif");
            m_MsgPng->setPixmap(QPixmap(":/chat/audioLeftPng"));
            strTime = "  " + strTime;
        }else{
            m_moviePlay = new QMovie(":/chat/audioRightGif");
            m_MsgPng->setPixmap(QPixmap(":/chat/audioRightPng"));
        }
        m_MsgTime->setText(strTime);
        m_MsgGif->setMovie(m_moviePlay);
		m_framCount = m_moviePlay->frameCount();
        AbstractMessageWidget::setMsg(msg); 
        //return;
    }

    void RecordMessageWidget::mousePressEvent( QMouseEvent *event )
    {
        if (event->button() != Qt::LeftButton)
        {
			AbstractMessageWidget::mousePressEvent(event);
           return;
        }

        QString path= QString::fromStdString(m_audioPath);
        if ( UIUtils::IsFileExist(path))
        {
            PlayAudioMsg();
        }
        else
        {
            DownLoadAduioMsg(m_audioPath,true);
        }
    }

    void RecordMessageWidget::onPlayFinished()
    {
        if(m_moviePlay->state() == QMovie::Running)
        {
            m_moviePlay->stop();
            m_MsgGif->setVisible(false);
            m_MsgPng->setVisible(true);
        }
    }

	void RecordMessageWidget::stopPlay()
	{
		m_record->StopPlay();
		m_moviePlay->stop();
		m_MsgGif->setVisible(false);
		m_MsgPng->setVisible(true);
	}

    void RecordMessageWidget::PlayAudioMsg()
    {
        QMovie::MovieState cutstate = ((m_moviePlay->state() == QMovie::Running) ? QMovie::Running : QMovie::NotRunning);
        if (cutstate == QMovie::Running)
        {
            m_record->StopPlay();
            m_moviePlay->stop();
            m_MsgGif->setVisible(false);
            m_MsgPng->setVisible(true);
        }else{

			if (m_record->isPlaying())
			{
				m_record->StopPlay();
				m_record->setStopPlaying();
				m_record->reset();
			}
			m_record->setPlayingAudioObj(this);
			
            bool isPlay = m_record->Play(QString::fromStdString(m_audioPath));
			emit startPlay();
            //播放失败，不显示播放动画
            if (isPlay)
            {
                m_moviePlay->start();
                m_MsgGif->setVisible(true);
                m_MsgPng->setVisible(false);
            }
        }
    }

	void RecordMessageWidget::stopMoviePlay()
	{
		m_moviePlay->stop();
		m_MsgGif->setVisible(false);
		m_MsgPng->setVisible(true);
	}

    void RecordMessageWidget::DownLoadAduioMsg( std::string url,bool isSrc )
    {
        std::shared_ptr<data::DownLoadFile> download = nullptr;
        download = std::make_shared<data::DownLoadFile>();

        download->bisP2P = false;
        download->bIsResume = false;
        data::MsgAudio*  audiomsg = (data::MsgAudio*)msg().get();

        download->encryptKey = audiomsg->encryptKey;
        download->fileName = audiomsg->fileName;
        QString path = UIUtils::GetDataFullPath(DATAPATH_USERAUDIO) + QString::fromStdString(audiomsg->fileName);
        download->localPath = path.toStdString();
        download->fromUserId = audiomsg->fromId;
        download->localId = audiomsg->localId;
        download->msgid = audiomsg->msgId;
        download->url = url;
		download->targetId = audiomsg->targetId;

        m_chatcontrol->DownLoadFile(download,CBind(&RecordMessageWidget::signalSerDownAudioMsgResult,this,CPlaceholders _1, CPlaceholders _2, CPlaceholders _3));

    }

    void RecordMessageWidget::onSerDownAudioMsgResult( int code , const std::string& path, int64 senderID )
    {
        if (! code)
        {
            std::string key = ((data::MsgAudio*)(msg().get()))->encryptKey;
            if (key.empty())
            {
                m_audioPath = path;
                PlayAudioMsg();
            }else{
                decryptFile(path,key);
            }
           
        }
    }

    void RecordMessageWidget::decryptFile(const std::string& url,std::string& Key )
    {
        QString path = QString::fromUtf8(url.data());
        QString destPath = UIUtils::GetDataFullPath(DATACACHEPATH_USERAUDIO) + UIUtils::GetNameByUrl(QString::fromUtf8(url.data()));
        if (UIUtils::IsFileExist(path))
        {
            bool bret = m_chatcontrol->decryptFile(Key, path.toUtf8().data(), destPath.toUtf8().data());
            if (bret)
            {
                m_audioPath = destPath.toStdString();
                PlayAudioMsg();
            }
        }

    }


