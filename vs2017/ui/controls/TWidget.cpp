#include "TWidget.h"
#include <QPainter>
#include <QStyleOption>
#include <qmath.h>
#include <QMouseEvent>
#include <QTimer>
#include <QCoreApplication>
namespace ui{
	TWidget::TWidget(QWidget *parent)
		: QWidget(parent)
	{
		this->setMouseTracking(true);
		m_timer = CMakePtr<QTimer>();
		QObject::connect(m_timer.get(),SIGNAL(timeout()),this,SLOT(onTimeout()));
		m_timer->setInterval(100);
	}

	TWidget::~TWidget()
	{

	}
	void TWidget::setSupportStretch(bool isSupportStretch){
		this->setMouseTracking(isSupportStretch);
		QList<QWidget*> widgetList = this->findChildren<QWidget*>();
		for(int i=0;i<widgetList.size();++i)
		{
			QWidget* widget  = widgetList.at(i);
			widget->setMouseTracking(isSupportStretch);
		}
	}
	void TWidget::updateUI(bool start){
		if(start){
		   m_timer->start();
		}
		else{
			m_timer->stop();
		}
	}
	void TWidget::paintEvent( QPaintEvent *event )
	{
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		QWidget::paintEvent(event);
	}
	void TWidget::mouseMoveEvent(QMouseEvent *event)
	{
		if(QMouseEvent::MouseMove == event->type()){
			QWidget::mouseMoveEvent(event);
		    event->ignore();
		}
		else{
			QWidget::mouseMoveEvent(event);
		}
	}
	void TWidget::onTimeout(){
		QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
	}
}
