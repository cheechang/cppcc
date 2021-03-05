#include "record.h"
#include <QDebug>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioOutput>
#include <QFile>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "RecordUI.h"
#include "log.h"

Record::Record(QObject *parent) : QObject(parent)
{
    m_saveFile = new QFile();
}

Record::~Record()
{

}

void Record::Start(QString name)
{
    startRecord(name);
}

void Record::Stop()
{
    stopRecord();
}

bool Record::Play(QString path)
{
    return playRecord(path);
}

void Record::onRecordState(QAudio::State state)
{
    switch(state)
    {
        case QAudio::ActiveState:
        {
            AddLog(LOG_LEV_DEBUG,LOG_FILE,"audio data is available to be processed.") ;
            break;
        }

        case QAudio::SuspendedState:
        {
            AddLog(LOG_LEV_DEBUG,LOG_FILE,"The audio device is in a suspended state, this state will only be entered after suspend() is called");
            break;
        }

        case QAudio::StoppedState:
        {
            AddLog(LOG_LEV_DEBUG,LOG_FILE," The audio device is closed, and is not processing any audio data");
            break;
        }

        case QAudio::IdleState:
        {
            AddLog(LOG_LEV_DEBUG,LOG_FILE,"The QIODevice passed in has no data and audio system's buffer is empty, this state is set after start() is called and while no audio data is available to be processed.");
            emit signalPlayFinish();
            break;
        }
    default:
        break;
    }
}

void Record::startRecord(QString name)
{
	QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
	qDebug() << Q_FUNC_INFO<<"================="<<info.supportedCodecs();
	QStringList strs =  info.supportedCodecs();
    AddLog(LOG_LEV_DEBUG,LOG_FILE,"startRecord name = %s",name.toLocal8Bit().data());
    m_saveFile->setFileName(name);
    bool openFile = m_saveFile->open(QIODevice::WriteOnly |QIODevice::Truncate);
    if(!openFile)
    {
         AddLog(LOG_LEV_DEBUG,LOG_FILE, "open file Faile");
         return;
    }

    QAudioFormat input;

	
   /* input.setFrequency(8000);
    input.setChannels(1);*/

	input.setSampleRate(8000);
	input.setChannelCount(1);
    input.setSampleSize(8);
    input.setCodec("audio/pcm");

    input.setByteOrder(QAudioFormat::LittleEndian);
    input.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo deviceInfo = QAudioDeviceInfo::defaultInputDevice();
    QString devicename = deviceInfo.deviceName();
    if(!deviceInfo.isFormatSupported(input))
    {
         AddLog(LOG_LEV_DEBUG,LOG_FILE, "device no support----->devicename = %s", devicename.toLocal8Bit().data());
        input = deviceInfo.nearestFormat(input);
    }

    m_audioInput = new QAudioInput(input,this);//input,
    connect(m_audioInput,SIGNAL(stateChanged(QAudio::State)),this, SLOT(onRecordState(QAudio::State)));

    m_audioInput->start(m_saveFile);
}

void Record::stopRecord()
{
    m_audioInput->stop();
    m_saveFile->close();
}

bool Record::playRecord(QString path)
{
    AddLog(LOG_LEV_DEBUG,LOG_FILE,"playRecord name = %s",path.toLocal8Bit().data());
    m_saveFile->setFileName(path);
    bool isRead = m_saveFile->open(QIODevice::ReadOnly);
    if(!isRead)
    {
        AddLog(LOG_LEV_DEBUG,LOG_FILE,"read file faile");
        return false;
    }

    QAudioFormat output;
    /*output.setFrequency(8000);
    output.setChannels(1);*/
	output.setSampleRate(8000);
	output.setChannelCount(1);
    output.setSampleSize(8);
    output.setCodec("audio/pcm");

    output.setByteOrder(QAudioFormat::LittleEndian);
    output.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(output))
    {
         AddLog(LOG_LEV_DEBUG,LOG_FILE,"raw audio format not supported by backend, cannot play audio.");
         return false;
    }

    m_audioOutput = new QAudioOutput(output,this);//

    connect(m_audioOutput,SIGNAL(stateChanged(QAudio::State)),this, SLOT(onRecordState(QAudio::State)));
    m_audioOutput->start(m_saveFile);
    return true;
}

void Record::Delete()
{
    stopRecord();
    m_saveFile->remove();
}

bool Record::FileRename( QString name )
{
    return m_saveFile->rename(name);
}

void Record::StopPlay()
{
    QAudio::State cur = m_audioOutput->state();

    m_audioOutput->stop();
}
