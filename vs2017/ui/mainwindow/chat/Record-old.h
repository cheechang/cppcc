#ifndef RECORD_H
#define RECORD_H

#include <QWidget>
#include <QAudio>
class QAudioInput;
class QFile;
class QPushButton;
class QAudioOutput;
class QAudioFormat;
class QHBoxLayout;
class QVBoxLayout;

class Record : public QObject
{
    Q_OBJECT
public:
    Record(QObject* parent);
    ~Record();
    void Start(QString path);
    void Stop();
    void StopPlay();
    bool Play(QString path);
    void Delete();
    bool FileRename(QString name);
signals:
    void signalPlayFinish();
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
};

#endif // RECORD_H
