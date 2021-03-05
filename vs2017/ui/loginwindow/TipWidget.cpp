#include "TipWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include "controls/PushButton.h"
#include <QTimer>

namespace ui {
	TipWidget::TipWidget(QWidget *parent)
		: QWidget(parent)
		, m_pTitleBtnLayout(NULL)
		, m_pCloseButton(NULL)
		, m_pTipText(NULL)
		, m_timer(NULL)
		, m_showTime(3)
	{
		m_pTitleBtnLayout = new QHBoxLayout(this);
		m_pCloseButton = new PushButton(this);

		m_timer = new QTimer();
		connect(m_timer,  SIGNAL(timeout()), this, SLOT(onTimeOut()));

		m_pTipText = new QLabel(this);
		m_pTipText->setStyleSheet("QLabel{color:red;}");

		this->resize(580, 40);
		m_pCloseButton->setPicName(QString(":/title/close"));

		m_pTitleBtnLayout->addStretch();
		m_pTitleBtnLayout->addWidget(m_pTipText, 0, Qt::AlignCenter);
		m_pTitleBtnLayout->addStretch();
		m_pTitleBtnLayout->addWidget(m_pCloseButton, 0, Qt::AlignTop);
		m_pTitleBtnLayout->setSpacing(0);
		m_pTitleBtnLayout->setContentsMargins(0, 0, 0, 0);



		connect(m_pCloseButton, SIGNAL(clicked()), this, SLOT(hide()));
	}


	TipWidget::~TipWidget(void)
	{
		if (m_pTipText != NULL)
		{
			delete m_pTipText;
			m_pTipText = NULL;
		}
		if (m_pCloseButton != NULL)
		{
			delete m_pCloseButton;
			m_pCloseButton = NULL;
		}
		if (m_pTitleBtnLayout != NULL)
		{
			delete m_pTitleBtnLayout;
			m_pTitleBtnLayout = NULL;
		}
	}

	void TipWidget::paintEvent(QPaintEvent* event)
	{
		QPainterPath path;
	    path.setFillRule(Qt::WindingFill);
	    path.addRect(event->rect());
	
		QPainter painter(this);
	    painter.setRenderHint(QPainter::Antialiasing, true);
		painter.fillPath(path, QBrush("#febdbc"));
	}

	void TipWidget::setTipText(QString tipText)
	{
		m_pTipText->setText(tipText);
		m_pTipText->setAlignment(Qt::AlignCenter);

		QWidget *parent_widget = (QWidget *)parent();
		move((parent_widget->width() - width()) / 2,
			(parent_widget->height() - height()) / 2 - 20);
	
		
	}

	void TipWidget::setTipSize( QSize size )
	{
		this->resize(size);
	}

	void TipWidget::setTime( int time )
	{
	   m_showTime = time;
	}

	void TipWidget::onTimeOut()
	{
		static int ti = 0;
		ti++;

		if (m_showTime < ti)
		{
		   ti = 0;
		   this->setVisible(false);
		}
	}

	void TipWidget::ErrShow()
	{
		m_timer->start(1000);
		this->setVisible(true);
	}

}