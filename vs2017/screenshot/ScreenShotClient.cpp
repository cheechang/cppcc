#include "ScreenShotClient.h"
#include "FullScreenWidget.h"
#include <QSocketNotifier>
#include <QTimer>
#include <QSharedMemory>
#include <QtWidgets/QApplication>
#include <../utils/Error.h>
ScreenShotClient::ScreenShotClient(){

	m_processList.clear();
}
ScreenShotClient::~ScreenShotClient(){
	qDebug() << "ScreenShotClient::~ScreenShotClient()";
	if ( !m_timer.isNull())
	{
		m_timer->stop();
		m_timer.clear();
	}
	if ( !m_sharedMem.isNull())
	{
		m_sharedMem->detach();
		m_sharedMem.clear();
	}
	if ( !m_replySharedMem.isNull())
	{
		m_replySharedMem->detach();
		m_replySharedMem.clear();
	}
	if ( !m_screenwidget.isNull())
	{
		m_screenwidget.clear();
	}
}

void ScreenShotClient::Init(){
	qDebug() << "ScreenShotClient::Init()";
	if ( m_screenwidget.isNull())
	{
		m_screenwidget.reset(fullScreenWidget::GetInstance());
		connect(m_screenwidget.data(), SIGNAL(exitPixmap()), this, SLOT(onExit()));
		connect(m_screenwidget.data(), SIGNAL(finishedshot(QString)), this, SLOT(onfinished(QString)));
		m_screenwidget->hide();
	}
	if ( m_sharedMem.isNull())
	{
		m_sharedMem.reset(new QSharedMemory());
		QStringList argument = QApplication::arguments();
		QString keystr("");
		if ( argument.size()>=2)
		{
			keystr = argument.at(1);
			qDebug() << "====screenshot.exe==keystr=%s" << keystr;
		}
		m_sharedMem->setKey(keystr);
	}
	if ( m_replySharedMem.isNull())
	{
		m_replySharedMem.reset(new QSharedMemory(QString("ScreenShotSendToLinkdood")));
	}
	if (m_timer.isNull())
	{
		m_timer.reset(new QTimer());
		connect(m_timer.data(), SIGNAL(timeout()), this, SLOT(onReadFromServer()));
		m_timer->start(200);
	}
}
//client端接收数据
void ScreenShotClient::onReadFromServer(){
	QBuffer			buffer;
	QDataStream		in(&buffer);
	QString			strReceiveData = "";
	char*			to = NULL;

	//将shareMemory与该进程绑定使之可以访问shareMemory里的内容  
	if (!m_sharedMem->attach())
	{
		return;
	}
	//给shareMemory枷锁  
	m_sharedMem->lock();
	//将shareMemeory里的数据放到buffer里  
	buffer.setData((char*)m_sharedMem->constData(), m_sharedMem->size());
	buffer.open(QBuffer::ReadOnly);
	in >> strReceiveData;
	if (strReceiveData.contains("StartScreenShot"))
	{
		qDebug() << "strReceiveData=" << strReceiveData;
		m_timer->stop();
		if (!m_screenwidget.isNull() && m_screenwidget->isHidden())
		{
			#if defined(__linux__)
				delaymsec(300);
			#endif
			QPixmap pixmap = m_screenwidget->getFullScreenPixmap();
			m_screenwidget->loadBackgroundPixmap(pixmap);
			m_screenwidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
			m_screenwidget->showFullScreen();
			m_screenwidget->raise();
			m_screenwidget->activateWindow();
		}
	}
	else if (strReceiveData.contains("ExitScreenShot"))
	{
		qDebug() << "strReceiveData=" << strReceiveData;
		QStringList temp = strReceiveData.split(":");
		if (temp.size() >= 2)
		{
			if (m_processList.contains(temp.at(1)))
			{
				m_processList.removeOne(temp.at(1));
			}
			if ( m_processList.empty())
			{
				emit signalexit();
			}
		}
	}
	else if (strReceiveData.contains("SendProcessID"))
	{
		QStringList temp = strReceiveData.split(":");
		if (temp.size() >= 2)
		{
			if (!m_processList.contains(temp.at(1)))
			{
				m_processList.push_back(temp.at(1));
			}
			qDebug() << "processid=" << temp.at(1);
		}
	}
	//清空缓存
	to = (char*)m_sharedMem->data();
	memset(to, 0, m_sharedMem->size());
	m_sharedMem->unlock();//将shareMemory解锁  
	m_sharedMem->detach();//将shareMemeory与该进程分离  
	
}
void ScreenShotClient::onExit(){
	 qDebug() << "ScreenShotClient::onExit()";
	 if ( !m_timer.isNull() && !m_timer->isActive())
	 {
		 m_timer->start(200);
	 }
}
void ScreenShotClient::onfinished(QString code){
	qDebug() << "ScreenShotClient::onfinished()";
	SendCmdToLinkdoodProcess(code);
}
void ScreenShotClient::SendCmdToLinkdoodProcess(QString cmd){
	qDebug() << "ScreenShotClient::SendCmdToLinkdoodProcess()";
	QBuffer		buffer;
	QDataStream out(&buffer);
	char*		to = NULL;
	const char *from = NULL;

	buffer.open(QBuffer::ReadWrite);
	if (m_replySharedMem.isNull())
	{
		m_replySharedMem.reset(new QSharedMemory(QString("ScreenShotSendToLinkdood")));
	}
	//将该进程与共享内存段分离  
	if (m_replySharedMem->isAttached())
	{
		m_replySharedMem->detach();
	}
	//填充数据值
	out << cmd;
	qDebug() << buffer.size();
	int size = buffer.size();

	//创建共享内存值
	if (!m_replySharedMem->create(size))
	{
		qDebug() << tr("can't create memory segment") << m_replySharedMem->errorString();
		qDebug() << m_replySharedMem->error();
		if (QSharedMemory::AlreadyExists != m_replySharedMem->error())
		{
			return;
		}
		if (!m_replySharedMem->isAttached())
		{
			bool bret = m_replySharedMem->attach();
			if (!bret)
			{
			}
		}
		return;
	}
	qDebug() << "Create shareMemory success size:" << m_replySharedMem->size();
	//加锁写入数据
	m_replySharedMem->lock();
	to = static_cast<char*>(m_replySharedMem->data());
	from = buffer.data().data();
	int memsize = m_replySharedMem->size();
	memcpy(to, from, qMin(size, memsize));//数据从该进程中拷贝到共享数据内存中 
	m_replySharedMem->unlock();//共享内层解锁  
}
void ScreenShotClient::delaymsec(int msec)
{
	QTime n = QTime::currentTime();
	QTime now;
	do{
		now = QTime::currentTime();
	} while (n.msecsTo(now) <= msec);
}