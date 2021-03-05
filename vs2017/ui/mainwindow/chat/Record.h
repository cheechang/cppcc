#ifndef RECORD_H
#define RECORD_H

#include <QWidget>
#include <QtMultimedia/QAudio>

#include "common/Common.h"
class QAudioInput;
class QFile;
class QPushButton;
class QAudioOutput;
class QAudioFormat;
class QHBoxLayout;
class QVBoxLayout;
class RecordMessageWidget;

class Record : public QObject
{
    Q_OBJECT
public:
    ~Record();
	static Record* getInstance();
	//Record(QObject* parent = 0);
    void Start(QString path);
	bool isPlaying(){return m_isPlaying;};
    void Stop();
    void StopPlay();
    bool Play(QString path);
    void Delete();
    bool FileRename(QString name);
	QList<QString> AvailableDevices(QAudio::Mode mode);
	bool hasDefaultDevices();
	QString AmrConvertWav(QString srcPath, bool& isConverted);
	void setPlayingAudioObj(RecordMessageWidget* obj);
	void setStopPlaying();
	void reset();
signals:
    void signalPlayFinish();
	void signalStopOtherPlay();
public slots:
    void onRecordState(QAudio::State state);
protected:
    void startRecord(QString path);
    void stopRecord();
    bool playRecord(QString filename);
private:
    QAudioInput*   m_audioInput;
    QAudioOutput*  m_audioOutput;
    QFile*         m_saveFile;
	bool		   m_isPlaying;
	RecordMessageWidget* m_AudioObj;
	Record(QObject* parent = 0);
	static Record* m_instanceRecord;
	
};

#endif // RECORD_H
