#include "RecordUI.h"
#include <QProgressBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDir>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QProcess>
#include "controls/PushButton.h"
#include "Record.h"
#include "common/ChineseInfos.hpp"
#include <log/log.h>

using namespace ui;
const int OUTTIME = 60;

RecordUI::RecordUI(QWidget *parent) : QProgressBar(parent),m_time(0)
{
    m_chatPtr = CHATMGRCONTROL;
    //m_record = new Record();

	m_record = Record::getInstance();
    m_audioPath = "";
    m_startTime = 0;

    this->setMaximum(60);
    this->setMinimum(0);

    this->setTextVisible(false);
    initWidgets();
}


void RecordUI::onTimerOut()
{
    if(m_time < OUTTIME)
    {
       ++m_time;
       this->setValue(m_time);
    }else{
        onOKClicked();
    }
}

void RecordUI::initWidgets()
{
    m_recordTime = new QTimer();
    m_recordTime->setInterval(1000);

    m_audioPoint = new PushButton(this);
    m_audioPoint->setPicName(":/chat/point");
    m_audioPoint->setFixedSize(8,8);

    m_audioText = new QLabel(this);
	m_audioText->setText(transfer("正在录音..."));

	m_audioErrText = new QLabel(this);
	m_audioErrText->setText(transfer("未检测到音频输入设备"));
	m_audioErrText->setObjectName("redlabel");
	m_audioErrText->setVisible(false);

    m_recordOk = new PushButton(this);
	m_recordOk->setToolTip(transfer("确定"));
    m_recordOk->setPicName(":/chat/ok");
	 m_audioPoint->setFixedSize(8,8);
    m_recordOk->setFixedSize(RECORD_BUTTON_WIDTH,RECORD_BUTTON_WIDTH);
    connect(m_recordOk,SIGNAL(clicked()),this,SLOT(onOKClicked()));

    m_recordCancel = new PushButton(this);
	m_recordCancel->setToolTip(transfer("取消"));
    m_recordCancel->setFixedSize(RECORD_BUTTON_WIDTH,RECORD_BUTTON_WIDTH);
    connect(m_recordCancel,SIGNAL(clicked()),this,SLOT(onStopClicked()));

    m_mainLayout = new QHBoxLayout();
    m_mainLayout->setContentsMargins(0,2,0,2);
    m_mainLayout->addSpacing(5);
    m_mainLayout->addWidget(m_audioPoint,0,Qt::AlignCenter);
    m_mainLayout->addWidget(m_audioText);
	m_mainLayout->addSpacing(220);
	m_mainLayout->addWidget(m_audioErrText);
    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_recordCancel);
    m_mainLayout->addWidget(m_recordOk);
    m_mainLayout->addSpacing(8);

    connect(m_recordTime,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    this->setLayout(m_mainLayout);
}

QString RecordUI::initLocalSetting()
{
    BEGIN;
    if (!m_chatPtr)
    {
        return "";
    }

    std::string path = m_chatPtr->userAudioPath();
    QString tempAudioPath = QString::fromUtf8(path.c_str());
    QDir tempDir;
    if (!tempDir.exists(tempAudioPath))
    {
        tempDir.mkdir(tempAudioPath);
    }

    return tempAudioPath;
    END;

}

void RecordUI::StartRecord()
{
    BEGIN;
	if (!m_record->hasDefaultDevices())
	{
		m_audioText->setVisible(false);
		m_audioPoint->setVisible(false);
		m_recordOk->setVisible(false);
		m_audioErrText->setVisible(true);
		m_recordCancel->setPicName(":/chat/delete");
		return;
	}
	m_recordCancel->setPicName(":/chat/stop");
    m_recordTime->start();
    QString audioPath= initLocalSetting();
    if (audioPath == "")
    {
        return;
    }
	m_startTime = QDateTime::currentMSecsSinceEpoch();
	QString filename = QString::number(m_startTime);
	m_audioPath = audioPath + filename + FILE_POSTFIX;
    m_record->Start(m_audioPath);
    END;
}

void RecordUI::onStopClicked()
{
    BEGIN;
    StopRecord();
    emit signalStopRecord();
    END;
}

void RecordUI::onOKClicked()
{
    m_record->Stop();
    m_recordTime->stop();

    int recordTime = QDateTime::currentMSecsSinceEpoch() - m_startTime;

    QString rep = "_" + QString::number(m_time) +FILE_POSTFIX;
    m_audioPath = m_audioPath.replace(FILE_POSTFIX,rep);

    if (m_record->FileRename(m_audioPath))
    {
		bool isConvert = false;
		QString WavAudioPath = RawConvertWav(m_audioPath,isConvert);
        emit signalRecordResult(WavAudioPath,recordTime);
    }
    m_time = 0;
	this->setValue(0);
    this->setVisible(false);
    emit signalStopRecord();
}

void RecordUI::StopRecord()
{
    BEGIN;
	if (m_recordTime->isActive())
	{
		m_record->Delete();
		m_recordTime->stop();
	}
	this->setValue(0);
    m_startTime = 0;
    m_time = 0;
    this->setVisible(false);
    END;
}

QString RecordUI::RawConvertWav(QString srcPath, bool& isConverted)
{
	LOG_METHOD("AudioMsgItemControler::amrConvertWav", LOG_FILE);
	isConverted = false;
	QString tempSrcPath = srcPath;
	tempSrcPath.replace(".raw", ".amr");
	if (QFile::exists(tempSrcPath))
	{
		Log(LOG_LEV_DEBUG, LOG_FILE, "wav file exist");
		isConverted = true;
		return tempSrcPath;
	}
	bool			 bRet = false;
	QProcess*		 process = NULL;
	QString			 ExeName = "ffmpeg.exe";
	QStringList		 processAgrc;
	QString			outWavpath = srcPath;
	outWavpath.replace(".raw", ".amr");
	QFile			 fileInfo;

	//音频文件从raw转换成wav
	process = new QProcess;
	//processAgrc << "-f" << "s16le" <<"-v" << "8"<<"-y"<<"-ar"<<"8000"<<"-ac"<<"1"<<"-i"<< srcPath << outWavpath; //raw转wav
	processAgrc << "-f" << "s16le" <<"-ar"<<"8000"<<"-ac"<<"1"<<"-i"<< srcPath << outWavpath;
	process->start(ExeName, processAgrc);
	bRet = process->waitForFinished();
	if (!bRet)
	{
		Log(LOG_LEV_ERROR, LOG_FILE, "Ram convert wav failed !!!");
		process->deleteLater();
		process = NULL;
		return "";
	}
	process->deleteLater();
	process = NULL;

	return outWavpath;
}