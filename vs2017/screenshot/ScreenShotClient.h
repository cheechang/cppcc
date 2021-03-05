#ifndef SCREEN_SHOOT_CLIENT__H
#define SCREEN_SHOOT_CLIENT__H
#include <QObject>
#include <QSharedPointer>
#include <QList>
class fullScreenWidget;
class QSharedMemory;
class QTimer;
class ScreenShotClient :public QObject{
	Q_OBJECT
public:
	ScreenShotClient();
	virtual ~ScreenShotClient();
	void Init();
	void SendCmdToLinkdoodProcess(QString cmd);
	void delaymsec(int msec);
public slots:
    void onReadFromServer();
	void onExit();
	void onfinished(QString code);
signals:
	void signalexit();
private:
	QSharedPointer<fullScreenWidget> m_screenwidget;
	QSharedPointer<QSharedMemory>    m_sharedMem;
	QSharedPointer<QSharedMemory>    m_replySharedMem;
	QSharedPointer<QTimer> m_timer;
	QList<QString> m_processList;
};
#endif