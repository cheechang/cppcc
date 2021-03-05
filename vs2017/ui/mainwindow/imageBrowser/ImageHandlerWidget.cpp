#include "ImageHandlerWidget.h"

ImageHandlerWidget::ImageHandlerWidget(QWidget *parent)
	: QWidget(parent) ,m_scale(0.0)
	,m_percentage(0.0)
	,m_originX(0.0), m_originY(0.0)
	,m_basicX(0.0), m_basicY(0.0)
{
	m_isInit = true;
	m_isPress = false;
}

ImageHandlerWidget::~ImageHandlerWidget()
{

}

void ImageHandlerWidget::setPixmap( const QPixmap &pixmap,bool isNotCcale)
{
	m_pixmap = pixmap;


	QSize sourceSize;
	int sourceWidth = 0;
	int sourceHeight = 0;
	int resultWidth = 0;
	int resultHeight = 0;
	float scaledNum = 0;      //缩放比例
	int scaledWidth = 780,scaledHeight = 600;
	sourceSize = pixmap.size();
	sourceWidth = pixmap.width();
	sourceHeight = pixmap.height();

	float winScale = height()*1.0/width();
	float picScale = pixmap.height()*1.0/pixmap.width();

	if (sourceWidth >= scaledWidth && sourceHeight >= scaledHeight)
	{
		if (sourceWidth >= sourceHeight)
		{
			scaledNum = scaledWidth*1.0 / sourceWidth;
			resultWidth = scaledWidth;
			resultHeight = scaledNum*sourceHeight;
		}
		else
		{
			scaledNum = scaledHeight*1.0 / sourceHeight;
			resultHeight = scaledHeight;
			resultWidth = scaledNum*sourceWidth;
		}
	}
	else if (sourceWidth >= scaledWidth && sourceHeight <= scaledHeight)
	{
		scaledNum = scaledWidth*1.0 / sourceWidth;
		resultWidth = scaledWidth;
		resultHeight = scaledNum*sourceHeight;
	}
	else if (sourceWidth <= scaledWidth && sourceHeight >= scaledHeight)
	{
		scaledNum = scaledHeight*1.0 / sourceHeight;
		resultHeight = scaledHeight;
		resultWidth = scaledNum*sourceWidth;
	}
	else
	{
		resultWidth = sourceWidth;
		resultHeight = sourceHeight;
	}	

	if ( resultWidth <10)
	{
		resultWidth = 10;
	}
	if (resultHeight < 10)
	{
		resultHeight = 10;
	}

	m_pixmap = m_pixmap.scaled(resultWidth,resultHeight);
	if(m_pixmap.isNull()){
		m_pixmap.load(":/pictureView/bad");
	}
	reset();
	/*m_pixmap = pixmap;
	if (!isNotCcale)
	{
		int w = m_pixmap.width()>width()?width():m_pixmap.width();
		int h = m_pixmap.height()>height()?height():m_pixmap.height();
		m_pixmap = m_pixmap.scaled(w,h);
	}
	if(m_pixmap.isNull()){
		m_pixmap.load(":/pictureView/bad");
	}
	reset();*/

}

void ImageHandlerWidget::showSuitableSize()
{
	double pixwidth = static_cast<double>(m_pixmap.width());
	double pixheight = static_cast<double>(m_pixmap.height());
	double showwidth = static_cast<double>(width());
	double showheight = static_cast<double>(height());

	//缩放比例
	double Wpercentage = showwidth / pixwidth;
	double Hpercentage = showheight / pixheight;
	m_percentage = qMin(Wpercentage, Hpercentage);
	m_suitableWidth = pixwidth*m_percentage;
	m_suitableHeight = pixheight*m_percentage;
	if( m_percentage < 0.01 )
	{
		m_percentage = 0.01;
	}
	else if( m_percentage > 10 )
	{
		m_percentage = 10;
	}
	m_scale = 1.0;

	//图片初始位置（用于移动）
	m_basicX = showwidth/2.0 - pixwidth*m_percentage/2.0;
	m_originX = m_basicX;
	m_basicY = showheight/2.0- pixheight*m_percentage/2.0;
	m_originY = m_basicY;

	update();
	emit percentageChanged( m_percentage );
}

void ImageHandlerWidget::zoomIn()
{
	ariseScale(1);
}

void ImageHandlerWidget::zoomOut()
{
	ariseScale(-1);
}

void ImageHandlerWidget::rotate()
{
	QMatrix matrix;
	matrix.rotate(90);
	m_isInit = true;
	m_pixmap = m_pixmap.transformed(matrix, Qt::FastTransformation);
	showSuitableSize();
}

void ImageHandlerWidget::ariseScale( int rate )
{
	double old_percentage = m_percentage;
	double step = static_cast<double>(rate)/100.0*5*old_percentage; //步进值
	m_percentage += step;
	if( m_percentage < 0.01 )
	{
		m_percentage = 0.01;
	}
	else if( m_percentage > 10 )
	{
		m_percentage = 10;
	}
	m_scale = m_percentage*m_scale/old_percentage;
	update();
	//emit percentageChanged( m_percentage );
}

void ImageHandlerWidget::paintEvent( QPaintEvent *event )
{
	Q_UNUSED(event);

	double pixwidth = static_cast<double>(m_pixmap.width());
	double pixheight = static_cast<double>(m_pixmap.height());
	double showwidth = static_cast<double>(width());
	double showheight = static_cast<double>(height());

	double Wscalerate = pixwidth / showwidth;
	double Hscalerate = pixheight / showheight;
	double compare = qMax(Wscalerate, Hscalerate);

	if( compare < 1.0 )
		compare = 1.0;

	QPainter painter(this);
	//Draw background
	painter.save();
	QRect backgroundRect = rect();
	//QColor color(245, 245, 245);
	QColor color(Qt::lightGray);
	painter.setPen(color);
	painter.setBrush(QBrush(color));
	painter.drawRect(backgroundRect);
	painter.restore();

	//Draw Image
	QRect showRect = QRect( m_originX, m_originY, pixwidth/compare, pixheight/compare);
	painter.save();
	painter.translate(showwidth/2.0, (showheight/2.0));
	painter.scale(m_scale, m_scale);
	painter.translate(-(showwidth/2.0), -(showheight/2.0));
	if(m_isInit){
		QPoint pos = this->rect().center();
		pos.setX(pos.x() - m_pixmap.width()/2);
		pos.setY(pos.y() - m_pixmap.height()/2);
		m_basicX = m_originX = pos.x();
		m_basicY = m_originY = pos.y();
		painter.drawPixmap(pos, m_pixmap);
	}else{
		painter.drawPixmap(showRect, m_pixmap);
	}
	painter.restore();
}

void ImageHandlerWidget::wheelEvent( QWheelEvent *event )
{
	m_isInit = false;
	int numDegrees = event->delta() / 8;//滚动的角度，*8就是鼠标滚动的距离
	int numSteps = numDegrees / 15;//滚动的步数，*15就是鼠标滚动的角度
	if (event->orientation() == Qt::Horizontal) {
		event->accept();      //接收该事件
	} else {
		ariseScale(numSteps);       //垂直滚动
	}
	QCursor cursor;
	cursor.setShape( Qt::SizeAllCursor );
	setCursor( cursor );
}

void ImageHandlerWidget::mousePressEvent( QMouseEvent *event )
{
	m_isInit = false;
	if( event->button() == Qt::LeftButton  )
	{
		m_isPress = true;
		QCursor cursor;
		cursor.setShape( Qt::SizeAllCursor );
		setCursor( cursor );

		m_pressPoint = event->pos();
	}
	else if( event->button() == Qt::RightButton )
	{
		emit rightButtonClicked();
	}
}

void ImageHandlerWidget::mouseReleaseEvent( QMouseEvent *event )
{
	Q_UNUSED(event);
	m_isInit = false;
	if( event->button() == Qt::LeftButton )
	{
		m_isPress = false;
		QCursor cursor;
		cursor.setShape( Qt::ArrowCursor );
		setCursor( cursor );

		m_basicX = m_originX;
		m_basicY = m_originY;
	}
}

void ImageHandlerWidget::mouseMoveEvent( QMouseEvent *event )
{
	//鼠标相对于屏幕的位置
	m_isInit = false;
	QPoint move_pos = event->pos();
	QCursor cursor;
	cursor.setShape( Qt::SizeAllCursor );

	if( rect().contains(event->pos()) )
	{
		move_pos -= m_pressPoint;
		m_originX = m_basicX + move_pos.x()/m_scale;
		m_originY = m_basicY + move_pos.y()/m_scale;
		update();
	}
	else
	{
		QPoint point;
		if( event->pos().x() < 0 )
		{
			point = QPoint( 0, event->pos().y() );
		}
		else if( event->pos().x() > rect().width()-1 )
		{
			point = QPoint( rect().width()-1, event->pos().y() );
		}
		else if( event->pos().y() < 0 )
		{
			point = QPoint( event->pos().x(), 0 );
		}
		else if( event->pos().y() > rect().height()-1 )
		{
			point = QPoint( event->pos().x(), rect().height()-1 );
		}

		cursor.setPos( mapToGlobal(point) );
		setCursor(cursor);
	}
}

void ImageHandlerWidget::reset()
{
	m_isInit = true;
	m_scale = 0;
	m_percentage = 0;
	showSuitableSize();
}
