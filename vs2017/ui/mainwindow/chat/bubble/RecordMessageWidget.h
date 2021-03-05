#pragma once
#include "abstractmessagewidget.h"
class QWidget;
class QLabel;
class QHBoxLayout;
class Record;
class QMovie;

class RecordMessageWidget :  public AbstractMessageWidget
{
    Q_OBJECT
public:
    RecordMessageWidget(QWidget* parent = CNull);
    ~RecordMessageWidget();

    QSize suggestWidth(int width);
    void SetRecordMsg(std::shared_ptr<data::Msg>&msg);
	void stopMoviePlay();
	void stopPlay();
signals:
    //  _1错误信息  _2接收成功后文件路径 localPath _3发送者ID 4 发送者类型
    void signalSerDownAudioMsgResult(int code, const std::string& path, int64 senderID );
    void startPlay();
public slots:
    void onPlayFinished();
    void onSerDownAudioMsgResult(int code , const std::string& path, int64 senderID);
protected:
    void initWidget();
    void DownLoadAduioMsg(std::string url,bool isSrc);
    void PlayAudioMsg();
    virtual void  mousePressEvent(QMouseEvent *event);
    void decryptFile(const std::string& url, std::string& Key);

private:
    QLabel*  m_MsgTime;
    QLabel*  m_MsgGif;
    QLabel*  m_MsgPng;
    Record*  m_record;
    QMovie*  m_moviePlay;
    std::string m_audioPath;
    QHBoxLayout* m_mainLayout;
    bool     m_isMsgRecv;
	int m_framCount;
};


