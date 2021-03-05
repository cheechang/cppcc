#include "ScreenShot.h"
#include <QCoreApplication>
#include <log.h>
#include <QBuffer>
#include <QSharedMemory>
#include <QDataStream>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include "../utils/common.h"
#include "common/ChineseInfos.hpp"
ScreenShot::ScreenShot(QObject *parent):m_isCanShootScreen(true),m_isExistShootScreenCmd(false),
QObject(parent)
{

}
ScreenShot::~ScreenShot(){

}
void  ScreenShot::InitSreenShotProcess(){
	QString keystr("LinkdoodSendToScreenShot");
	bool isexist = false;
	QString processPath("");
	QString processName(SCREEN_SHOOT_APP);

#ifdef _WIN32
	processName.append(QString(".exe"));
#endif
	processPath.append("\"");
	processPath.append(QCoreApplication::applicationDirPath());
	processPath.append("/");
	processPath.append(processName);

	processPath.append("\" ");
	processPath.append(keystr);

	Log(LOG_LEV_INFO, LOG_FILE, "screenshotPath=%s", processPath.toLocal8Bit().data());
	isexist = utils::KillProcess(processName.toLocal8Bit().data(), false, true);
	if (!isexist)
	{
		bool bret = QProcess::startDetached(processPath);
		if (!bret)
		{
			Log(LOG_LEV_ERROR, LOG_FILE, "screenshotPath=%s,started failed!", processPath.toLocal8Bit().data());
		}
	}
	if (m_sharedMemory.isNull())
	{
		m_sharedMemory = QSharedPointer<QSharedMemory>(new QSharedMemory(keystr));
	}
	if (m_receivedSharedMemory.isNull())
	{
		m_receivedSharedMemory = QSharedPointer<QSharedMemory>(new QSharedMemory("ScreenShotSendToLinkdood"));
	}
	if (m_timer.isNull())
	{
		m_timer = QSharedPointer<QTimer>(new QTimer());
		connect(m_timer.data(), SIGNAL(timeout()), this, SLOT(onReceiveMsgFromScreenshot()));
	}
	if(!isexist){
		QString cmd("SendProcessID:");
		cmd += QString::number(QCoreApplication::applicationPid());
		AddLog(LOG_LEV_DEBUG,"WindowsManager::InitSreenShotProcess%s",cmd.toLocal8Bit().data());
		SendCmdToScreenShotProcess(cmd);
		delaymsec(300);
	}
}
void ScreenShot::SendCmdToScreenShotProcess(QString cmd){
BEGIN;
	QBuffer		buffer;
	QDataStream out(&buffer);
	char*		to = NULL;
	const char *from = NULL;

	buffer.open(QBuffer::ReadWrite);
	if ( m_sharedMemory.isNull())
	{
		m_isExistShootScreenCmd = false;
		return;
	}
	//将该进程与共享内存段分离  
	if (m_sharedMemory->isAttached())
	{
		m_sharedMemory->detach();
	}
	//填充数据值
	out << cmd;
	qDebug() << buffer.size();
	int size = buffer.size();

	//创建共享内存值
	if (!m_sharedMemory->create(size))
	{
		qDebug() << m_sharedMemory->error();
		Log(LOG_LEV_ERROR, LOG_FILE, "can't create memory segment:%s", m_sharedMemory->errorString().toStdString().c_str());
		if (QSharedMemory::AlreadyExists != m_sharedMemory->error())
		{
			m_isExistShootScreenCmd = false;
			return;
		}
		if (!m_sharedMemory->isAttached())
		{
			bool bret = m_sharedMemory->attach();
			if (!bret)
			{
				m_isExistShootScreenCmd = false;
				Log(LOG_LEV_DEBUG, LOG_FILE, "WindowsManager::SendCmdToScreenShotProcess attach failed,bret=%d", bret);
			}
		}
	}
	qDebug() << "Create shareMemory success size:" << m_sharedMemory->size();
	//加锁写入数据
	m_sharedMemory->lock();
	to = static_cast<char*>(m_sharedMemory->data());
	from = buffer.data().data();
	int memsize = m_sharedMemory->size();
	memcpy(to, from, qMin(memsize,size));//数据从该进程中拷贝到共享数据内存中
	m_sharedMemory->unlock();//共享内层解锁  
END;
}
void ScreenShot::onReceiveMsgFromScreenshot(){
BEGIN;
	QBuffer			buffer;
	QDataStream		in(&buffer);
	QString			strReceiveData = "";
	char*			to = NULL;

	//将shareMemory与该进程绑定使之可以访问shareMemory里的内容  
	if (!m_receivedSharedMemory->attach())
	{
		return;
	}
	//给shareMemory枷锁  
	m_receivedSharedMemory->lock();
	//将shareMemeory里的数据放到buffer里  
	buffer.setData((char*)m_receivedSharedMemory->constData(), m_receivedSharedMemory->size());
	buffer.open(QBuffer::ReadOnly);
	in >> strReceiveData;
	if (!strReceiveData.isEmpty())
	{
		Log(LOG_LEV_DEBUG, LOG_FILE, "====strReceiveData=%s===", strReceiveData.toLocal8Bit().data());
		m_timer->stop();
		int code = strReceiveData.toInt();
		emit finished(code, QProcess::NormalExit);
		if (NULL != m_lastScrootReceObj)
		{
			QObject::disconnect(this, SIGNAL(finished(int, QProcess::ExitStatus)), m_lastScrootReceObj, SLOT(onScreenShoot(int, QProcess::ExitStatus)));
		}
		m_isExistShootScreenCmd = false;
		Log(LOG_LEV_DEBUG, LOG_FILE, "code=%d", code);
	}
	//清空缓存
	to = (char*)m_receivedSharedMemory->data();
	memset(to, 0, m_receivedSharedMemory->size());
	m_receivedSharedMemory->unlock();//将shareMemory解锁  
	m_receivedSharedMemory->detach();//将shareMemeory与该进程分离  
	Log(LOG_LEV_DEBUG, LOG_FILE, "m_isExistShootScreenCmd=%d", m_isExistShootScreenCmd);
}
void  ScreenShot::CloseScreenshot(){
#if defined(__linux__) || defined(_WIN32)
	if (!m_timer.isNull())
	{
		if (m_timer->isActive())
		{
			m_timer->stop();
		}
	}
	QString cmd("ExitScreenShot:");
	cmd += QString::number(QCoreApplication::applicationPid());
	qDebug() << "WindowsManager::CloseScreenshot" << cmd;
	SendCmdToScreenShotProcess(cmd);
	delaymsec(500);
#else
	if (!m_ScreenShotPtr.isNull())
	{
		m_ScreenShotPtr->close();
		if (!m_ScreenShotPtr->waitForFinished(3000)){
			qDebug() << "screenshot has exit(0)";
		}
	}
#endif
END;
}
void ScreenShot::ShootScreen(QObject*reciever)
{
BEGIN;
	Log(LOG_LEV_DEBUG, LOG_FILE, "WindowsManager::ShootScreen:m_isCanShootScreen=%d", m_isCanShootScreen);
	/*如果不允许截图，则不启动截图进程，直接返回*/
	if (!m_isCanShootScreen)
		return;
#if defined(__linux__) || defined(_WIN32)
	Log(LOG_LEV_DEBUG, LOG_FILE, "m_isExistShootScreenCmd=%d", m_isExistShootScreenCmd);
	if (!m_isExistShootScreenCmd)
	{
		m_isExistShootScreenCmd = true;
		m_lastScrootReceObj = reciever;
		QObject::connect(this, SIGNAL(finished(int, QProcess::ExitStatus)), reciever, SLOT(onScreenShoot(int, QProcess::ExitStatus)));
		//发送截图命令给screenshot进程
		if (!m_timer.isNull() && !m_timer->isActive())
		{
			m_timer->start(200);
		}
		QString cmd("StartScreenShot");
		Log(LOG_LEV_DEBUG, LOG_FILE, "WindowsManager::ShootScreen:%s", cmd.toStdString().c_str());
		SendCmdToScreenShotProcess(cmd);
		delaymsec(300);
	}

#else
	std::string appPath("");
	QString processPath("");
	appPath = QCoreApplication::applicationDirPath().toLocal8Bit().data();
	processPath.append("\"");
	processPath.append(QString::fromLocal8Bit(appPath.data()));
	processPath.append("/");
	processPath.append(SCREEN_SHOOT_APP);
	processPath.append("\"");
	Log(LOG_LEV_INFO, LOG_FILE, "screenshotPath=%s", processPath.toLocal8Bit().data());
	QProcess::ProcessState procesState = m_ScreenShotPtr.isNull() ? QProcess::NotRunning : m_ScreenShotPtr->state();
	if (procesState != QProcess::NotRunning) return;
	m_ScreenShotPtr.reset(new QProcess());
	QObject::connect(m_ScreenShotPtr.data(), SIGNAL(finished(int, QProcess::ExitStatus)), reciever, SLOT(onScreenShoot(int, QProcess::ExitStatus)));
	QObject::connect(m_ScreenShotPtr.data(), SIGNAL(error(QProcess::ProcessError)), this, SLOT(onProcessError(QProcess::ProcessError)));
	QObject::connect(m_ScreenShotPtr.data(), SIGNAL(readyRead()), this, SLOT(onReadFromClient()));
	m_ScreenShotPtr->start(processPath);
	m_ScreenShotPtr->waitForStarted();
#endif
END;
}
void ScreenShot::delaymsec(int msec)
{
	QTime n = QTime::currentTime();

	QTime now;
	do{
		now = QTime::currentTime();
	} while (n.msecsTo(now) <= msec);
}