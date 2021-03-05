#pragma once
#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QProcess>
class QSharedMemory;
class QTimer;
class ScreenShot:public QObject{
	Q_OBJECT
public:
	ScreenShot(QObject *parent=0);
	virtual ~ScreenShot();
public:
	void  InitSreenShotProcess();
	void  SendCmdToScreenShotProcess(QString cmd);
	void  CloseScreenshot();
	void  ShootScreen(QObject*reciever);
	void  delaymsec(int msec);
signals:
	void finished(int, QProcess::ExitStatus);
public slots:
	void onReceiveMsgFromScreenshot();
private:
	QSharedPointer<QSharedMemory> m_sharedMemory;
	QSharedPointer<QSharedMemory> m_receivedSharedMemory;
	QSharedPointer<QTimer> m_timer;
	bool m_isCanShootScreen;		//全局的截屏是否可用（包括快捷键）
	bool m_isExistShootScreenCmd;   //存在截图命令未执行
	QObject* m_lastScrootReceObj;   //保存截图完成后，接收数据的对象，为了是否连接，解决xp截图重复问题
};