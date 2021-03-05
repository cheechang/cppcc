#include "DefaultWidget.h"
#include <QPainter>
#include <QMovie>
#include <qlabel.h>
#include <qlayout.h>
namespace ui{
	DefaultWidget::DefaultWidget(QWidget *parent):m_movie(nullptr){
		m_gifLabel = new QLabel(this);
		m_tipInfo = new QLabel(this);
		m_movie = new QMovie(":/img/loading");
		m_gifLabel->setScaledContents(true);
		m_gifLabel->setMovie(m_movie);
		m_movie->start();

		m_tipInfo->setText(tr("正在加载数据"));
		m_tipInfo->setAlignment(Qt::AlignHCenter);
		m_pMainLayout = new QVBoxLayout(this);
		m_pMainLayout->setContentsMargins(0, 150, 0, 0);
		m_pMainLayout->setAlignment(Qt::AlignCenter);
		m_pMainLayout->addWidget(m_gifLabel);
		m_pMainLayout->addWidget(m_tipInfo);
		m_pMainLayout->addStretch();
		m_pMainLayout->setSpacing(10);
		setLayout(m_pMainLayout);
	}
	DefaultWidget::DefaultWidget(QString&picname, QWidget *parent):m_movie(nullptr){
		m_gifLabel = new QLabel(this);

		m_gifLabel->setScaledContents(true);
		m_gifLabel->setPixmap(QPixmap(picname));

		m_pMainLayout = new QVBoxLayout(this);
		m_pMainLayout->setContentsMargins(0, 150, 0, 0);
		m_pMainLayout->setAlignment(Qt::AlignCenter);
		m_pMainLayout->addWidget(m_gifLabel);
		m_pMainLayout->addStretch();
		m_pMainLayout->setSpacing(10);
		setLayout(m_pMainLayout);
	}
	DefaultWidget::~DefaultWidget(){
		if (nullptr != m_movie){
			m_movie->stop();
		}
	}
	void DefaultWidget::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		painter.setBrush(QBrush(Qt::white));
		painter.setPen(Qt::NoPen);  //边框色
		painter.drawRect(QRect(0, 0, this->width(), this->height()));
	}
}