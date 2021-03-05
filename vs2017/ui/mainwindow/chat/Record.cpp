#include "Record.h"
#include <QDebug>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioOutput>
#include <QFile>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include "common/UIUtils.h"
#include "bubble/RecordMessageWidget.h"
#include "RecordUI.h"
#include <log/log.h>

QString DECODE = "audio/pcm";
Record* Record::m_instanceRecord = CNull;
Record* Record::getInstance()
{
	if(m_instanceRecord == CNull){
		m_instanceRecord = new Record();
	}
	return m_instanceRecord;
}

Record::Record(QObject *parent) : QObject(parent)
{
    m_saveFile = new QFile();
	m_isPlaying = false;
	m_audioInput=CNull;
	m_audioOutput=CNull;
	m_AudioObj = CNull;
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
	m_isPlaying = true;
    return playRecord(UIUtils::RepairLocalFilePath(path));
}

void Record::reset()
{
	m_audioOutput->reset();
}

void Record::setPlayingAudioObj(RecordMessageWidget* obj)
{
	m_AudioObj = obj;
}

void Record::setStopPlaying()
{
	if (m_AudioObj)
	{
		m_AudioObj->stopMoviePlay();
	}
}

void Record::onRecordState(QAudio::State state)
{
    switch(state)
    {
        case QAudio::ActiveState:
        {
            Log(LOG_LEV_DEBUG,LOG_FILE,LOG_FILE,"audio data is available to be processed.") ;
            break;
        }

        case QAudio::SuspendedState:
        {
            Log(LOG_LEV_DEBUG,LOG_FILE,LOG_FILE,"The audio device is in a suspended state, this state will only be entered after suspend() is called");
            break;
        }

        case QAudio::StoppedState:
        {
            Log(LOG_LEV_DEBUG,LOG_FILE,LOG_FILE," The audio device is closed, and is not processing any audio data");
            break;
        }

        case QAudio::IdleState:
        {
            Log(LOG_LEV_DEBUG,LOG_FILE,LOG_FILE,"The QIODevice passed in has no data and audio system's buffer is empty, this state is set after start() is called and while no audio data is available to be processed.");
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
         Log(LOG_LEV_DEBUG,LOG_FILE,LOG_FILE, "open file Faile");
         return;
    }

    QAudioFormat input;
#if(QT_VERSION < QT_VERSION_CHECK(5,6,0))
	input.setFrequency(8000);
	input.setChannels(1);
#else
	input.setSampleRate(8000);
	input.setChannelCount(1);
#endif

    input.setSampleSize(16);
    input.setCodec(DECODE);

    input.setByteOrder(QAudioFormat::LittleEndian);
    input.setSampleType(QAudioFormat::UnSignedInt);

	QAudioDeviceInfo deviceInfo = QAudioDeviceInfo::defaultInputDevice();
    if(!deviceInfo.isFormatSupported(input))
    {
         Log(LOG_LEV_DEBUG,LOG_FILE,LOG_FILE, "device no support----->devicename ");
        input = deviceInfo.nearestFormat(input);
    }

    m_audioInput = new QAudioInput(input,this);
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
	bool isConver = false;
	QString WavAudioPath = AmrConvertWav(path,isConver);

	m_saveFile->setFileName(WavAudioPath);
    bool isRead = m_saveFile->open(QIODevice::ReadOnly);
    if(!isRead)
    {
        Log(LOG_LEV_DEBUG,LOG_FILE,LOG_FILE,"read file faile");
        return false;
    }

    QAudioFormat output;

#if(QT_VERSION < QT_VERSION_CHECK(5,6,0))
	output.setFrequency(8000);
	output.setChannels(1);
#else
	output.setSampleRate(8000);
	output.setChannelCount(1);
#endif

    output.setSampleSize(16);
    output.setCodec(DECODE);

    output.setByteOrder(QAudioFormat::LittleEndian);
    output.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(output))
    {
         Log(LOG_LEV_DEBUG,LOG_FILE,LOG_FILE,"raw audio format not supported by backend, cannot play audio.");
         output = info.nearestFormat(output);
    }

    m_audioOutput = new QAudioOutput(output,this);

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

QList<QString> Record::AvailableDevices(QAudio::Mode mode)
{
	QList<QString> tmpData;
	QList<QAudioDeviceInfo> audioDeviceListI = QAudioDeviceInfo::availableDevices(mode);
	for( int i =0 ;i <audioDeviceListI.size(); ++i)
	{
		QAudioDeviceInfo devInfo = audioDeviceListI.at(i);
		QString strName = devInfo.deviceName();

		if (devInfo.isNull())
			continue;
		if (strName[0] == 65533)
			continue;

		if(tmpData.contains(strName))
		{
			continue;
		}
		tmpData.push_back(strName);
	}
	return tmpData;
}

bool Record::hasDefaultDevices()
{
	QAudioDeviceInfo deviceInfo = QAudioDeviceInfo::defaultInputDevice();
	QString devicename = deviceInfo.deviceName();
	if (deviceInfo.isNull())
	{
		Log(LOG_LEV_DEBUG,LOG_FILE, LOG_FILE, "deviceInfo.isNull()");
		return false;
	}
	else
	{
		Log(LOG_LEV_DEBUG,LOG_FILE, LOG_FILE, "deviceInfo info name = %s",devicename.data());
		return true;
	}
}

void Record::StopPlay()
{
	m_isPlaying = false;
    QAudio::State cur = m_audioOutput->state();

    m_audioOutput->stop();
}

QString Record::AmrConvertWav(QString srcPath, bool& isConverted)
{
	isConverted = false;
	QString tempSrcPath = srcPath;
	tempSrcPath.replace(".amr", ".wav");
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
	outWavpath.replace(".amr", ".wav");
	QFile			 fileInfo;

	//音频文件从amr转换成wav
	process = new QProcess;
	processAgrc << "-i" << srcPath << "-ac" << "1" << "-vol" << "500" << "-ab" << "128" << outWavpath;
	process->start(ExeName, processAgrc);
	bRet = process->waitForFinished();
	if (!bRet)
	{

		Log(LOG_LEV_ERROR, LOG_FILE, "amr convert wav failed !!!");
		process->deleteLater();
		process = NULL;
		return "";
	}

	process->deleteLater();
	process = NULL;

	return outWavpath;
}
