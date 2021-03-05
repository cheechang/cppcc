#include "ProgressWindow.h"
#include "Controls/TitleBar.h"
#include "Controls/ProgressWidget.h"
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <QPainter>
#include <log.h>
namespace ui{
	ProgressWindow::ProgressWindow(QWidget*parent) :QDialog(parent)
	, m_progress(nullptr)
	,m_mainlayout(nullptr)
	,m_tableLayout(nullptr)
	{
		//LOG_METHOD("ProgressWindow::ProgressWindow", LOG_FILE);
		this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
		this->resize(500, 300);

		m_title = new TitleBar(this,false,false,true,true);
		m_progress = new ProgressWidget(this);
		m_mainlayout = new QVBoxLayout(this);

		installEventFilter(m_title);
		setWindowIcon(QIcon(":/img/logo"));

		m_tableLayout = new QVBoxLayout();
		QStringList heads;
		heads << tr("文件") << tr("大小") << tr("根目录") << tr("状态");
		m_progress->setColumnValue(heads.size(), heads);
		m_progress->setFixedSize(QSize(480, 245));
		m_title->setFixedSize(500, 40);
		m_tableLayout->setAlignment(Qt::AlignTop);
		m_tableLayout->setContentsMargins(10, 5, 5, 5);
		m_tableLayout->addWidget(m_progress);

		m_mainlayout->setAlignment(Qt::AlignTop);
		m_mainlayout->setContentsMargins(0, 0, 0, 0);
		m_mainlayout->addWidget(m_title);
		m_mainlayout->addLayout(m_tableLayout);
		setLayout(m_mainlayout);

		connect(m_title, SIGNAL(signalClose()), this, SLOT(onClose()));
		connect(m_progress, SIGNAL(signalCancle(int64)), this, SLOT(onCancel(int64)));
		connect(m_progress, SIGNAL(signalRetry(int64)), this, SLOT(onRetry(int64)));
		connect(this, SIGNAL(signalDownFail(int64)), m_progress, SIGNAL(signalDownFail(int64)));
		connect(this, SIGNAL(signalUpFail(int64)), m_progress, SIGNAL(signalUpFail(int64)));
		connect(this, SIGNAL(signalDecryptFile(int64, model::CloudFileInfo&, std::string&)), m_progress, SIGNAL(signalDecryptFile(int64, model::CloudFileInfo&, std::string&)));

		QPoint pt = QPoint(this->parentWidget()->width(), this->parentWidget()->height()) - QPoint(this->width(), this->height());
		this->move(pt);
	}
	ProgressWindow::~ProgressWindow(){
		if (nullptr != m_tableLayout){
			m_tableLayout->deleteLater();
		}
	}
	void ProgressWindow::paintEvent(QPaintEvent *event)
	{
		//LOG_METHOD("ProgressWindow::paintEvent", LOG_FILE);
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		p.setBrush(QBrush(Qt::white));
		p.setPen(Qt::gray);  //边框色
		p.drawRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
	}
	void ProgressWindow::addItem(model::CloudFileInfo& data, QString name){
		//LOG_METHOD("ProgressWindow::addItem", LOG_FILE);
		m_progress->addItem(data, name);
	}
	void ProgressWindow::setTitle(QString title)
	{
		//LOG_METHOD("ProgressWindow::setTitle", LOG_FILE);
		setWindowTitle(title);
		
	}
	void ProgressWindow::SetProcess(int32 pro, int64 localId, std::string& filename){
		//LOG_METHOD("ProgressWindow::SetProcess", LOG_FILE);
		m_progress->setProgress(pro, localId,filename);
	}
	void ProgressWindow::onClose(){	
		//LOG_METHOD("ProgressWindow::onClose", LOG_FILE);
		emit signalClose();
	}
	void ProgressWindow::onCancel(int64 localid){
		//LOG_METHOD("ProgressWindow::onCancel", LOG_FILE);
		emit signalDownCancel(localid);
		emit signalUpCancel(localid);
	}
	void ProgressWindow::onRetry(int64 localid){
		//LOG_METHOD("ProgressWindow::onRetry", LOG_FILE);
		emit signalDownRetry(localid);
		emit signalUpRetry(localid);
	}
	void ProgressWindow::onWindowSizeChanged(){
		//LOG_METHOD("ProgressWindow::onWindowSizeChanged", LOG_FILE);
		QPoint pt = QPoint(this->parentWidget()->width(), this->parentWidget()->height()) - QPoint(this->width(), this->height());
		this->move(pt);
	}
}