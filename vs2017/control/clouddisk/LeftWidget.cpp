#include "LeftWidget.h"
#include "Controls/ToolButton.h"
#include <QPainter>
#include <qprogressbar.h>
#include <qlabel.h>
#include <QVBoxLayout>
#include <log.h>
namespace ui{
	LeftWidget::LeftWidget(QWidget *parent):QWidget(parent),m_myselfbtn(nullptr),
	m_sharebtn(nullptr),m_mainLayout(nullptr){
		//LOG_METHOD("LeftWidget::LeftWidget", LOG_FILE);
		m_myselfbtn = new ToolButton(QString(":/img/myselffile"),this);
		m_sharebtn  = new ToolButton(QString(":/img/sharefile"), this);
		m_mainLayout = new QVBoxLayout(this);
		m_progressbar = new QProgressBar(this);
		m_sizeLabel = new QLabel(this);
		m_sizeTipLabel = new QLabel(this);
		m_hlayout = new QVBoxLayout(this);

		m_progressbar->setMinimum(0);
		m_progressbar->setMaximum(100);
		m_progressbar->setValue(50);
		m_progressbar->setFixedHeight(12);
		m_progressbar->setTextVisible(false);

		m_hlayout->addWidget(m_sizeTipLabel, Qt::AlignLeft);
		m_hlayout->addWidget(m_progressbar,Qt::AlignBottom);
		m_hlayout->addWidget(m_sizeLabel, Qt::AlignLeft);
		m_hlayout->setAlignment(Qt::AlignBottom);
		m_hlayout->setSpacing(0);
		m_hlayout->setContentsMargins(5,5,5,5);

		m_sizeLabel->setText(tr("0/2T"));
		m_sizeLabel->setFixedSize(190,30);

		m_sizeTipLabel->setText(tr("当前文件夹空间使用情况:"));
		m_sizeTipLabel->setFixedSize(190, 30);

		m_progressbar->setVisible(false);
		m_sizeLabel->setVisible(false);
		m_sizeTipLabel->setVisible(false);

		connect(m_myselfbtn, SIGNAL(clicked()), this, SLOT(onSelfBtnClicked()));
		connect(m_sharebtn, SIGNAL(clicked()), this, SLOT(onShareBtnClicked()));

		m_myselfbtn->setText(tr("我的文件"));
		m_sharebtn->setText(tr("共享文件"));

		m_myselfbtn->setObjectName("transparentToolButton");
		m_sharebtn->setObjectName("transparentToolButton");

		m_sharebtn->setSize(QSize(175, 25));
		m_myselfbtn->setSize(QSize(175, 25));

		m_mainLayout->setAlignment(Qt::AlignTop);
		m_mainLayout->addWidget(m_myselfbtn);
		m_mainLayout->addWidget(m_sharebtn);
		m_mainLayout->addLayout(m_hlayout);
		m_mainLayout->setSpacing(0);
		m_mainLayout->setContentsMargins(0, 0, 0, 10);
		setLayout(m_mainLayout);

		m_myselfbtn->setMousePress(true);
	}
	LeftWidget::~LeftWidget(){

	}
	void LeftWidget::SetMySelfBtnSelected(){
		m_myselfbtn->setMousePress(true);
		m_sharebtn->setMousePress(false);
	}
	void LeftWidget::paintEvent(QPaintEvent *event)
	{
		//LOG_METHOD("LeftWidget::paintEvent", LOG_FILE);
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		painter.setPen(Qt::gray);
		painter.setBrush(QColor(240,240,240));
		painter.drawRect(QRect(0, 0, this->width(), this->height()));
	}
	void LeftWidget::onSelfBtnClicked(){
		//LOG_METHOD("LeftWidget::onSelfBtnClicked", LOG_FILE);
		m_myselfbtn->setMousePress(true);
		m_sharebtn->setMousePress(false);
		emit singalSelfBtnClicked();
	}
	void LeftWidget::onShareBtnClicked(){
		//LOG_METHOD("LeftWidget::onShareBtnClicked", LOG_FILE);
		m_myselfbtn->setMousePress(false);
		m_sharebtn->setMousePress(true);
		emit signalShareBtnClicked();
	}
	void LeftWidget::onSpaceInfo(QString&foldername,QString&size, int&proval){
		//LOG_METHOD("LeftWidget::onSpaceInfo", LOG_FILE);
		m_sizeTipLabel->setText(foldername+tr("文件夹空间使用情况:"));
		m_sizeLabel->setText(size);
		m_progressbar->setValue(proval);
	}
}