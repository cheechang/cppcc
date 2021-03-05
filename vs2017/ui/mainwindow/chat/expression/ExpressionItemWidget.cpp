#include "ExpressionItemWidget.h"
#include <QMovie>
#include <QDebug>
#include <QMouseEvent>
namespace ui{
	ExpressionItemWidget::ExpressionItemWidget(QString fileName , QSize emotionMoiveSize,QWidget*parent)
		: QLabel(parent)
	{
		//首先构造函数中进行初始化;
		QMovie* iconMovie = new QMovie(this);
		iconMovie->setFileName(fileName);
		this->setMovie(iconMovie);
		setContentsMargins(3, 3, 3, 3);
		iconMovie->setScaledSize(QSize(emotionMoiveSize.width(), emotionMoiveSize.height()));
		//为了动态图片正常显示，（不加上start图片不显示，不加上stop图片一种处于动态效果）
		iconMovie->start();
		iconMovie->stop();
		setStyleSheet("QLabel:hover{border: 1px solid rgb(111, 156, 207);\
					  color: rgb(2, 65, 132);\
					  background: rgba(255, 255, 255, 200);}");
	}

	ExpressionItemWidget::~ExpressionItemWidget()
	{}

	// 鼠标进入Label事件
	void ExpressionItemWidget::enterEvent(QEvent* event)
	{
		QMovie* movie = this->movie();
		movie->start();
		setContentsMargins(4, 2, 2, 4);
		return __super::enterEvent(event);
	}
	// 鼠标离开Label事件
	void ExpressionItemWidget::leaveEvent(QEvent* event)
	{
		QMovie* movie = this->movie();
		movie->jumpToFrame(0);
		movie->stop();
		setContentsMargins(3, 3, 3, 3);
		return __super::leaveEvent(event);
	}

	void ExpressionItemWidget::mousePressEvent( QMouseEvent *ev )
	{
		if (ev->button() == Qt::LeftButton)
		{
			emit clicked(this->movie()->fileName());
		}
		QLabel::mousePressEvent(ev);
	}

}