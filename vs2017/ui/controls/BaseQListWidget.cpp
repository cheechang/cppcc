#include "BaseQListWidget.h"
namespace uicontrols{
	BaseQListWidget::BaseQListWidget(QWidget *parent,bool isShowScrollBarNormal)
		: QListWidget(parent),m_isfirst(false)
	{
		this->viewport()->setMinimumWidth(LIST_ITEM_WIDTH);
		this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		this->setVerticalScrollMode(QListWidget::ScrollPerPixel);
		this->verticalScrollBar()->setValue(0);
		//this->setObjectName("skinListWidget");
		m_isShowScrollBarNormal = isShowScrollBarNormal ;
	}
	BaseQListWidget::~BaseQListWidget()
	{

	}
	void BaseQListWidget::mouseMoveEvent(QMouseEvent *event)
	{
		if(QMouseEvent::MouseMove == event->type()){
			QListWidget::mouseMoveEvent(event);
		    event->ignore();
		}
		else{
			QListWidget::mouseMoveEvent(event);
		}
	}
	void BaseQListWidget::animateVerScrollBar(int start, int end)
	{
		QPropertyAnimation* propAnim = new QPropertyAnimation(this->verticalScrollBar(), "value");
		propAnim->setEasingCurve(QEasingCurve::OutCubic);
		propAnim->setDuration(350);
		propAnim->setStartValue(start);
		propAnim->setEndValue(end);
		propAnim->start(QAbstractAnimation::DeleteWhenStopped);
	}
	void BaseQListWidget::wheelEvent(QWheelEvent *event){
		int numberDegrees = event->delta()/8; //滚动的角度，*8就是鼠标滚动的距离 正数值表示滑轮相对于用户在向前滑动，相反，负数值表示滑轮相对于用户是向后滑动的。
		int numSteps =qAbs(numberDegrees)*8+60; //numberDegrees /15;//滚动的步数，*15就是鼠标滚动的角度
		if(event->orientation() == Qt::Vertical)
		{   
			int end = 0;
			int start  = this->verticalScrollBar()->value();
			emit signalScrollChanged();
			if(numberDegrees>=0){
				end = start-numSteps;
			}
			else{
				end = start+numSteps;
			}
			if(end<=this->verticalScrollBar()->minimum()){
				end = this->verticalScrollBar()->minimum();
			}
			if(end>=this->verticalScrollBar()->maximum()){
				emit signalSrcollToBottom();
				end = this->verticalScrollBar()->maximum();
			}
			animateVerScrollBar(start,end);
		}
		event->ignore();
	}
	void BaseQListWidget::enterEvent(QEvent* event)
	{
		Q_UNUSED(event)
		if (!m_isShowScrollBarNormal)
		{
			this->verticalScrollBar()->setVisible(true);
		}
		event->accept();
	}

	void BaseQListWidget::leaveEvent(QEvent* event)
	{
		Q_UNUSED(event)
			if (!m_isShowScrollBarNormal)
			{
				this->verticalScrollBar()->setVisible(false);
			}
		event->accept();
	}
	void BaseQListWidget::resizeEvent(QResizeEvent *e){
		QSize contentsize = this->contentsSize();
		if(-1 != contentsize.height() && !m_isfirst){
			emit signalSrcollToBottom();
			m_isfirst = true;
		}
		QListWidget::resizeEvent(e);
	}
}
