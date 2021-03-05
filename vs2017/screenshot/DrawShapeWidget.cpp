#include "DrawShapeWidget.h"
#include <QtGui>
#include <QListView>


PaintWidgetScene::PaintWidgetScene(QWidget *parent) 
	: QGraphicsScene(parent), m_currShapeCode(Shape::Line), m_currItem(NULL), m_perm(false) 
{ 
	m_curPen.setColor(QColor(255, 0, 0));  //默认红色
	m_curPen.setWidth(THIN_LINE);
	m_curFont.setPixelSize(12);

	m_bIsTextEdit = false;
	m_bIsPressText = false;
} 

void PaintWidgetScene::mousePressEvent(QGraphicsSceneMouseEvent *event) 
{ 
	if (event->button() == Qt::RightButton)
	{
		return;
	}
	switch(m_currShapeCode) 
	{ 
	case Shape::Line: 
		{ 
			Line *line = new Line; 
			m_currItem = line; 
			addItem(line); 
			line->setPen(m_curPen);
			int curIndex = m_itemGroupMap.size();
			m_itemGroupMap[curIndex] = line;
			break; 
		} 
	case Shape::Rect: 
		{ 
			Rect *rect = new Rect; 
			m_currItem = rect; 
			addItem(rect); 
			rect->setPen(m_curPen);
			rect->SetVisibleRect(m_visibleRect);
			int curIndex = m_itemGroupMap.size();
			m_itemGroupMap[curIndex] = rect;
			break; 
		} 
	case Shape::Ellipse:
		{
			DrawEllipse *ellipse = new DrawEllipse;
			m_currItem = ellipse; 
			addItem(ellipse); 
			ellipse->setPen(m_curPen);
			ellipse->SetVisibleRect(m_visibleRect);
			int curIndex = m_itemGroupMap.size();
			m_itemGroupMap[curIndex] = ellipse;
			break; 
		}
	case Shape::Arrow:
		{
			Arrow *arrow = new Arrow; 
			m_currItem = arrow; 
			addItem(arrow); 
			arrow->setPen(m_curPen);
			arrow->SetVisibleRect(m_visibleRect);
			int curIndex = m_itemGroupMap.size();
			m_itemGroupMap[curIndex] = arrow;
			break; 
		}
	case Shape::Text:
		{
			m_bIsPressText = !m_bIsPressText;
			if (m_bIsPressText)
			{
				Text *text = new Text; 
				m_currItem = text; 
				addItem(text); 
				text->SetTextFontAndPen(m_curPen, m_curFont);
				QPointF beginPoint(event->scenePos().x()+6, event->scenePos().y()+5);

				text->SetTextRectF(QRectF(beginPoint, QSizeF(m_visibleRect.width()-event->scenePos().x(),m_visibleRect.height()-event->scenePos().y())));
				int curIndex = m_itemGroupMap.size();
				m_itemGroupMap[curIndex] = text;
				//通知主窗口显示textedit
				emit signalLeftBtnPressed(event->scenePos(), m_bIsPressText);
			}
			else
			{	//通知主窗口隐藏textEidt
				emit signalLeftBtnPressed(event->scenePos(), m_bIsPressText);
				m_perm = false;
				QGraphicsScene::mousePressEvent(event); 
				return;
			}

			break; 
		}
	case Shape::PathBrush:
		{
			Path *path = new Path; 
			m_currItem = path; 
			addItem(path); 
			path->SetCurPen(m_curPen);
			//路径不需要
			//path->SetVisibleRect(QRectF(0, 0, this->width(), this->height()));
			QColor col = m_curPen.color();
			int curIndex = m_itemGroupMap.size();
			m_itemGroupMap[curIndex] = path;
			break; 
		}
	} 
	if(m_currItem)
	{ 
		m_currItem->startDraw(event); 
		m_perm = false; 
	} 
	QGraphicsScene::mousePressEvent(event); 
} 
void PaintWidgetScene::SetTextToScene(){
	qDebug() << "PaintWidgetScene::SetTextToScene";
	m_currShapeCode = Shape::Text;
	QCoreApplication::sendEvent(this, new QGraphicsSceneMouseEvent(QEvent::MouseButtonPress));
}
void PaintWidgetScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) 
{ 
	if(m_currItem && !m_perm) 
	{ 
		if (Shape::Text  != m_currShapeCode)
		{
			m_currItem->SetCurPen(m_curPen);
			m_currItem->drawing(event); 	
		}
	} 
	QGraphicsScene::mouseMoveEvent(event); 
	//必须要更新场景
	this->update();
} 

void PaintWidgetScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) 
{ 
	m_perm = true; 
	QGraphicsScene::mouseReleaseEvent(event); 
}
void PaintWidgetScene::slotSetCurrentShape(Shape::Code s, QPen pen) 
{ 
	if(s != m_currShapeCode)
	{ 
		if (Shape::Text == m_currShapeCode)
		{
			m_bIsPressText = false;
			emit signalLeftBtnPressed(QPointF(0, 0), m_bIsPressText);
		}
		m_currShapeCode = s; 
		m_curPen = pen;
		if (Shape::Text == s)
		{
			m_bIsTextEdit =true; 
		}
		else
		{
			m_bIsTextEdit =false;
		}
	} 
} 
void PaintWidgetScene::slotSetCurPen(QPen pen)
{
	m_curPen = pen;
}
void PaintWidgetScene::slotSetCurFont(QPen pen, QFont font)
{
	m_curPen = pen;
	m_curFont = font;
	if (Shape::Text == m_currShapeCode && NULL != m_currItem)
	{
		Text* itemText = (Text*)m_currItem;
		itemText->SetTextFontAndPen(m_curPen, m_curFont);
	}
}
void PaintWidgetScene::slotAddText(QString content)
{
	if (Shape::Text == m_currShapeCode)
	{
		if (content.isEmpty())
		{
			slotDelLastDraw();
		}
		else
		{
			if (NULL != m_currItem)
			{
				Text* itemText = (Text*)m_currItem;
				itemText->addText(content);
			}

		}
	}
	this->update();
}
void PaintWidgetScene::slotDelLastDraw()
{
	int curIndex = m_itemGroupMap.size()-1;
	if ( m_itemGroupMap.contains(curIndex))
	{
		QGraphicsItem *lastItem = (QGraphicsItem*)m_itemGroupMap[curIndex];
		m_itemGroupMap.remove(curIndex);
		
		QList<QGraphicsItem*> itemList = this->items();

		if (itemList.isEmpty())
		{
			//如果scene的item删除完了，但是map里面还有item则把map清空
			for (int i=0; i<m_itemGroupMap.size(); i++)
			{
				QGraphicsItem *lastTempItem = (QGraphicsItem*)m_itemGroupMap[i];
				m_itemGroupMap.remove(i);
				delete lastTempItem;
			}
			m_itemGroupMap.clear();
			return;
		}
		if (itemList.contains(lastItem))
		{
			this->removeItem(lastItem);
			delete lastItem;
		}
		this->update();
	}

}

////////////////////////////////// 划线/////////////////////////////
void Line::startDraw(QGraphicsSceneMouseEvent * event)
{ 
	setLine(QLineF(event->scenePos(), event->scenePos())); 
}
void Line::drawing(QGraphicsSceneMouseEvent * event)
{    
	QLineF newLine(line().p1(), event->scenePos()); 
	setLine(newLine);
}

////////////////////////////////// 矩形/////////////////////////////
void Rect::startDraw(QGraphicsSceneMouseEvent * event)
{
	setRect(QRectF(event->scenePos(), QSizeF(0, 0)));
}
void Rect::drawing(QGraphicsSceneMouseEvent * event)
{
	QPointF endPoint = QPointF(event->scenePos());
	if (event->scenePos().x() > m_visibleRect.width())
	{
		endPoint.setX(m_visibleRect.width());
	}
	if (event->scenePos().y() > m_visibleRect.height())
	{
		endPoint.setY(m_visibleRect.height());
	}
	if (event->scenePos().x()<0)
	{
		endPoint.setX(0);
	}
	if (event->scenePos().y()<0)
	{
		endPoint.setY(0);
	}
	QPointF pointTemp = rect().topLeft();
	QPointF pointScenePos = endPoint;
	QRectF result;
	qreal width = pointScenePos.x() - pointTemp.x();
	qreal heigth = pointScenePos.y() - pointTemp.y(); 
	result = QRectF(pointTemp, QSizeF((width), (heigth))); 
	setRect(result); 

}
/////////////////////////////////////椭圆//////////////////////////
void DrawEllipse::startDraw(QGraphicsSceneMouseEvent * event)
{
	setRect(QRectF(event->scenePos(), QSizeF(0, 0)));
}
void DrawEllipse::drawing(QGraphicsSceneMouseEvent * event)
{
	QPointF endPoint = QPointF(event->scenePos());
	if (event->scenePos().x() > m_visibleRect.width())
	{
		endPoint.setX(m_visibleRect.width());
	}
	if (event->scenePos().y() > m_visibleRect.height())
	{
		endPoint.setY(m_visibleRect.height());
	}
	if (event->scenePos().x()<0)
	{
		endPoint.setX(0);
	}
	if (event->scenePos().y()<0)
	{
		endPoint.setY(0);
	}
	QRectF r(rect().topLeft(), QSizeF(endPoint.x() - rect().topLeft().x(), endPoint.y() - rect().topLeft().y())); 
	setRect(r); 
}
///////////////////////////////////文本//////////////////////////
void Text::startDraw(QGraphicsSceneMouseEvent * event)
{

	m_beginPointF = event->scenePos();
}
void Text::drawing(QGraphicsSceneMouseEvent * event)
{
	//m_endPointF = event->scenePos();
}
void Text::addText(QString text)
{
	m_strText = text;
	m_bIsAdd = true;
	this->update();
}

void Text::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget )
{
	painter->setPen(m_curPen);
	painter->setFont(m_curFont);

	painter->drawText(m_rect, m_strText);
}
void Text::SetTextFontAndPen(QPen pen, QFont font)
{
	if ( !m_bIsAdd)
	{
		m_curPen = pen;
		m_curFont = font;
	}
}
void Text::SetTextRectF(QRectF rect)
{
	m_rect = rect;
	m_rect.setWidth(m_rect.width()-10);
}
/////////////////////////////////画箭头/////////////////////////////
void Arrow::SetCurPen(QPen pen)
{
	m_curPen = pen;
	int width = m_curPen.width();
	if (THIN_LINE == width)
	{
		m_fArrowAngle = 0.2;
		m_fArrowLength = 8;
	}
	else if (MEDIATE_LINE == width)
	{
		m_fArrowAngle = 0.28;
		m_fArrowLength = 10;
	}
	else if (BIG_LINE == width)
	{
		m_fArrowAngle = 0.31;
		m_fArrowLength = 20;
	}
}

void Arrow::startDraw(QGraphicsSceneMouseEvent * event)
{
	m_pointF = event->scenePos();
	m_bIsDraw = false;
}
void Arrow::drawing(QGraphicsSceneMouseEvent * event)
{
	QPointF endPoint = QPointF(event->scenePos());
	if (event->scenePos().x() > m_visibleRect.width())
	{
		endPoint.setX(m_visibleRect.width());
	}
	if (event->scenePos().y() > m_visibleRect.height())
	{
		endPoint.setY(m_visibleRect.height());
	}
	if (event->scenePos().x()<0)
	{
		endPoint.setX(0);
	}
	if (event->scenePos().y()<0)
	{
		endPoint.setY(0);
	}

	m_endPointF = endPoint;
	m_bIsDraw = true;
	this->update();
}

void Arrow::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget )
{
	if ( !m_bIsDraw)
	{
		return;
	}
	m_curPen.setWidth(THIN_LINE);
	painter->setPen(m_curPen);
	painter->setRenderHint(QPainter::Antialiasing, true);

	float x1 = m_pointF.x();         //lastPoint 起点  
	float y1 = m_pointF.y();  

	float x2 = m_endPointF.x();           //endPoint 终点  
	float y2 = m_endPointF.y();  

	float length = 30.0;                   //箭头的那长度  
	float a = 0.3;                       //箭头与线段角度 (箭头的夹角) 

	float x3 = x2 - m_fArrowLength * cos(atan2((y2 - y1) , (x2 - x1)) - m_fArrowAngle);    //右边的线
	float y3 = y2 - m_fArrowLength * sin(atan2((y2 - y1) , (x2 - x1)) - m_fArrowAngle);  

	float x4 = x2 - m_fArrowLength * sin(atan2((x2 - x1) , (y2 - y1)) - m_fArrowAngle);  
	float y4 = y2 - m_fArrowLength * cos(atan2((x2 - x1) , (y2 - y1)) - m_fArrowAngle);  
	
	float x5 = x2 - (m_fArrowLength+3) * cos(atan2((y2 - y1) , (x2 - x1)) - m_fArrowAngle-0.2);  
	float y5 = y2 - (m_fArrowLength+3) * sin(atan2((y2 - y1) , (x2 - x1)) - m_fArrowAngle-0.2);  

	float x6 = x2 - (m_fArrowLength+3) * sin(atan2((x2 - x1) , (y2 - y1)) - m_fArrowAngle-0.2);  
	float y6 = y2 - (m_fArrowLength+3) * cos(atan2((x2 - x1) , (y2 - y1)) - m_fArrowAngle-0.2);  

	painter->drawLine(x1,y1,x3,y3);  
	painter->drawLine(x1,y1,x4,y4); 
	painter->drawLine(x3, y3, x5, y5);
	painter->drawLine(x5, y5, m_endPointF.x(), m_endPointF.y());
	painter->drawLine(x4, y4, x6, y6);
	painter->drawLine(x6, y6, m_endPointF.x(), m_endPointF.y());

	//填充颜色
	QVector<QPointF>  VecPoints;
	VecPoints.push_back(QPointF(m_pointF));
	VecPoints.push_back(QPointF(x3, y3));
	VecPoints.push_back(QPointF(x5, y5));
	VecPoints.push_back(m_endPointF);
	VecPoints.push_back(QPointF(x6, y6));
	VecPoints.push_back(QPointF(x4, y4));
	VecPoints.push_back(m_pointF);
	QPolygonF polygonF(VecPoints);
	QPainterPath path;
	path.addPolygon(polygonF);
	QBrush brush(m_curPen.color());
	painter->fillPath(path, brush);
}
/////////////////////////////////画路径( 画刷工具)/////////////////
void Path::startDraw(QGraphicsSceneMouseEvent * event)
{
	m_paintPath = QPainterPath(event->scenePos());
	this->setPath(m_paintPath);
}
void Path::drawing(QGraphicsSceneMouseEvent * event)
{
	m_paintPath.lineTo(event->scenePos());
	this->update();
}
void Path::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget )
{

	painter->setPen(m_curPen);
	painter->drawPath(m_paintPath);

}
void Path::SetVisibleRect(QRectF rect)
{
	m_visibleRect = rect;
}

CustomColorButton::CustomColorButton(QWidget* parent ):QToolButton(parent)
{
	connect(this, SIGNAL(clicked()), this, SLOT(slotBtnClicked()),Qt::QueuedConnection);
}

SelectColorWidget::SelectColorWidget(QWidget *parent , int type):QWidget(parent)
{
#ifndef _DEBUG
	m_imagePath =  ":/image/screenShot/";
#else
	m_imagePath = "ui/image/screenShot/";
#endif

	m_curFont.setPixelSize(12);
	m_curPen.setColor(QColor(255, 0, 0));  //默认红色
	m_curPen.setWidth(THIN_LINE);
	m_iType = type;
	m_pThinLineBtn = new QToolButton(this);
	m_pThinLineBtn->setFixedSize(24, 21);
	updateToolBtnStytle(m_pThinLineBtn, "dot1_down.png","dot1_enter.png","dot1_down.png");
	
	m_pMediateLineBtn = new QToolButton(this);
	m_pMediateLineBtn->setFixedSize(24, 21);
	updateToolBtnStytle(m_pMediateLineBtn, "dot2.png","dot2_enter.png","dot2_down.png");

	m_pBigLineBtn = new QToolButton(this);
	m_pBigLineBtn->setFixedSize(24, 21);
	updateToolBtnStytle(m_pBigLineBtn, "dot3.png","dot3_enter.png","dot3_down.png");

	m_pLineLayout = new QHBoxLayout(this);
	m_pLineLayout->setContentsMargins(2, 0, 0, 0);
	m_pLineLayout->setSpacing(1);
	m_pLineLayout->addWidget(m_pThinLineBtn);
	m_pLineLayout->addWidget(m_pMediateLineBtn);
	m_pLineLayout->addWidget(m_pBigLineBtn);

	m_pLineWidget = new QWidget(this);
	m_pLineWidget->setLayout(m_pLineLayout);

	QStringList DrawTypeList;
	DrawTypeList.clear();  
	DrawTypeList.push_back(tr(" 8"));
	DrawTypeList.push_back(tr(" 9")); 
	DrawTypeList.push_back(tr(" 10"));
	DrawTypeList.push_back(tr(" 11"));
	DrawTypeList.push_back(tr(" 12"));
	DrawTypeList.push_back(tr(" 13"));
	DrawTypeList.push_back(tr(" 14"));
	DrawTypeList.push_back(tr(" 15")); 
	DrawTypeList.push_back(tr(" 16"));
	DrawTypeList.push_back(tr(" 17"));
	DrawTypeList.push_back(tr(" 18"));
	DrawTypeList.push_back(tr(" 19"));
	DrawTypeList.push_back(tr(" 20"));
	m_pFontComBox = new QComboBox(this);
	m_pFontComBox->setObjectName("SelectFontCombox");
	QString strComboxStyle = "QComboBox#SelectFontCombox{font-size:12px;color: rgb(0, 0, 0);border-image:url(" + m_imagePath+ \
		+ "fontsize1.png);border:0px;}QComboBox#SelectFontCombox:hover{font-size:12px;color: rgb(0, 0, 0);border-image:url(" + m_imagePath\
		+ "fontsize1_enter.png);border:0px;}QComboBox#SelectFontCombox:pressed{font-size:12px;color: rgb(0, 0, 0);border-image:url(" + m_imagePath\
 		+"fontsize1_down.png);border:0px;}";
	m_pFontComBox->setStyleSheet(strComboxStyle);
	m_pFontComBox->setFont(QFont(tr("微软雅黑")));
	m_pFontComBox->setFixedSize(68, 20);
	m_pFontComBox->addItems(DrawTypeList);
	QListView* itemView = new QListView;
	m_pFontComBox->setView(itemView);
	m_pFontComBox->setCurrentIndex(4);

	m_pFontLayout = new QHBoxLayout;
	m_pFontLayout->setContentsMargins(5, 5, 5, 5);
	m_pFontLayout->setSpacing(0);
	m_pFontLayout->addWidget(m_pFontComBox);

	QWidget* fontWidget = new QWidget(this);
	fontWidget->setLayout(m_pFontLayout);

	m_pLineOrFontWidget = new QStackedWidget(this);
	m_pLineOrFontWidget->addWidget(m_pLineWidget);
	m_pLineOrFontWidget->addWidget(fontWidget);

	m_pLineOrFontWidget->setCurrentIndex(m_iType);

	m_pCutLineLabel = new QLabel(this);
	m_pCutLineLabel->setObjectName("ColorCutLineLabel");

	m_pCutLineLabel->setPixmap(QPixmap(m_imagePath + "devide.png"));

	m_pSeledColorLabel = new QLabel(this);
	
	m_pSelectColorLayout = new QHBoxLayout;
	m_pSelectColorLayout->setContentsMargins(2, 2, 2, 2);
	m_pSelectColorLayout->setSpacing(0);
	m_pSelectColorLayout->addWidget(m_pSeledColorLabel);

	m_pSelectColorWidget = new QWidget(this);
	m_pSelectColorWidget->setFixedSize(22, 21);
	m_pSelectColorWidget->setObjectName("SelectColorWidget");
	m_pSelectColorWidget->setStyleSheet("QWidget#SelectColorWidget{border-image:url(" + m_imagePath + "selectcolor.png);}");
	m_pSelectColorWidget->setLayout(m_pSelectColorLayout);

	m_pColorLayout = new QGridLayout;
	m_pColorLayout->setContentsMargins(2, 1, 3, 0);
	m_pColorLayout->setSpacing(1);

	for (int i=0; i<16; i++)
	{
		CustomColorButton* colorBtn = new CustomColorButton(this);
		colorBtn->setFixedSize(14, 14);
		colorBtn->SetIndex(i);
		QString strFilename(tr("color")+QString::number(i+1)+tr(".png"));
		QString strFileNameEnter(tr("color")+QString::number(i+1)+tr("_enter.png"));
		updateCustomToolBtnStytle(colorBtn, strFilename, strFileNameEnter,strFileNameEnter);
		m_mapIndexColorBtn[i] = colorBtn;
		int col = i%8;
		int row = 0;
		if (i > 7)
		{
			row = 1;
		}
		m_pColorLayout->addWidget(colorBtn, row, col, 1, 1);
		connect(colorBtn, SIGNAL(Clicked(int)),this, SLOT(slotColorBtnClicked(int)),Qt::QueuedConnection);
	}
	m_pColorWidget = new QWidget(this);
	m_pColorWidget->setLayout(m_pColorLayout);
	
	m_pMainLayout = new QHBoxLayout;
	m_pMainLayout->setContentsMargins(2, 0, 0, 0);
	m_pMainLayout->setSpacing(3);

	m_pMainLayout->addWidget(m_pLineOrFontWidget);
	m_pMainLayout->addWidget(m_pCutLineLabel);
	m_pMainLayout->addWidget(m_pSelectColorWidget);
	m_pMainLayout->addWidget(m_pColorWidget);

	connect(m_pThinLineBtn, SIGNAL(clicked()), this, SLOT(slotThinLineClicked()), Qt::QueuedConnection);
	connect(m_pMediateLineBtn, SIGNAL(clicked()), this, SLOT(slotMediateLineClicked()), Qt::QueuedConnection);
	connect(m_pBigLineBtn, SIGNAL(clicked()), this, SLOT(slotBigLineClicked()), Qt::QueuedConnection);

	connect(m_pFontComBox, SIGNAL(	currentIndexChanged(const QString)), this, SLOT(slotFontChanged(const QString)), Qt::QueuedConnection);

	setLayout(m_pMainLayout);

	m_mapIndexColorValue[0] = QColor(0, 0, 0);
	m_mapIndexColorValue[1] = QColor(138, 137, 135);
	m_mapIndexColorValue[2] = QColor(254, 1, 0);
	m_mapIndexColorValue[3] = QColor(241, 151, 2);
	m_mapIndexColorValue[4] = QColor(1, 155, 69);
	m_mapIndexColorValue[5] = QColor(0, 69, 159);
	m_mapIndexColorValue[6] = QColor(152, 0, 239);
	m_mapIndexColorValue[7] = QColor(1, 110, 105);
	m_mapIndexColorValue[8] = QColor(254, 254, 254);
	m_mapIndexColorValue[9] = QColor(204, 201, 196);
	m_mapIndexColorValue[10] = QColor(237, 99, 60);
	m_mapIndexColorValue[11] = QColor(254, 243, 1);
	m_mapIndexColorValue[12] = QColor(140, 195, 32);
	m_mapIndexColorValue[13] = QColor(3, 184, 241);
	m_mapIndexColorValue[14] = QColor(249, 2, 255);
	m_mapIndexColorValue[15] = QColor(14, 180, 180);

}
SelectColorWidget::~SelectColorWidget()
{

}
void SelectColorWidget::LoadQssFile(  QString qssFileName )
{
	QFile file( qssFileName );

	//读取界面样式字符串
	file.open(QFile::ReadOnly);
	if ( file.isOpen() )
	{
		this->setStyleSheet(file.readAll());
		file.close();
	}
}
//更新按钮的样式
void SelectColorWidget::updateToolBtnStytle(QToolButton* &toolBtn,QString picNormal,QString PicHot,QString PicPressed)
{
	QString strStytleSheet = "QToolButton{border-image:url(" + m_imagePath;
	strStytleSheet  += picNormal;
	strStytleSheet += ");}QToolButton:hover{border-image:url(" + m_imagePath;
	strStytleSheet  += PicHot;
	strStytleSheet += ");}QToolButton:hover{border-image:url(" + m_imagePath;
	strStytleSheet  += PicPressed;
	strStytleSheet  += ");}";
	toolBtn->setStyleSheet(strStytleSheet);
}
void SelectColorWidget::updateCustomToolBtnStytle(CustomColorButton* &toolBtn,QString picNormal,QString PicHot,QString PicPressed)
{
	QString strStytleSheet = "QToolButton{border-image:url(" + m_imagePath;
	strStytleSheet  += picNormal;
	strStytleSheet += ");}QToolButton:hover{border-image:url(" + m_imagePath;
	strStytleSheet  += PicHot;
	strStytleSheet += ");}QToolButton:hover{border-image:url(" + m_imagePath;
	strStytleSheet  += PicPressed;
	strStytleSheet  += ");}";
	toolBtn->setStyleSheet(strStytleSheet);
}
void	SelectColorWidget::paintEvent(QPaintEvent *event)
{
	QPixmap pixBmp(QPixmap(m_imagePath + "corlorbg.png"));
	QPainter painter(this);  
	painter.drawPixmap(0,0,pixBmp);  
	painter.end();
}
void SelectColorWidget::slotColorBtnClicked(int index)
{
	QColor color = m_mapIndexColorValue[index];
	QString red = QString::number(color.red());
	QString gre = QString::number(color.green());
	QString ble = QString::number(color.blue());
	m_pSeledColorLabel->setStyleSheet("QLabel{background:rgb("+red+","+gre+","+ble+");}");

	m_curPen.setColor(color);
	if (1 == m_iType)
	{
		int fontpix = m_pFontComBox->currentText().toInt();
		emit signalSelectFontChange(m_curPen, m_curFont);
	}
	else
	{
		emit signalSelectChange(m_curPen);
	}
}
void	SelectColorWidget::slotThinLineClicked()
{
	updateToolBtnStytle(m_pThinLineBtn, "dot1_down.png","dot1_enter.png","dot1_down.png");
	updateToolBtnStytle(m_pMediateLineBtn, "dot2.png","dot2_enter.png","dot2_down.png");
	updateToolBtnStytle(m_pBigLineBtn, "dot3.png","dot3_enter.png","dot3_down.png");

	m_curPen.setWidth(THIN_LINE);
	emit signalSelectChange(m_curPen);
}
void SelectColorWidget::slotMediateLineClicked()
{
	updateToolBtnStytle(m_pThinLineBtn, "dot1.png","dot1_enter.png","dot1_down.png");
	updateToolBtnStytle(m_pMediateLineBtn, "dot2_down.png","dot2_enter.png","dot2_down.png");
	updateToolBtnStytle(m_pBigLineBtn, "dot3.png","dot3_enter.png","dot3_down.png");
	m_curPen.setWidth(MEDIATE_LINE);
	emit signalSelectChange(m_curPen);
}
void SelectColorWidget::slotBigLineClicked()
{
	updateToolBtnStytle(m_pThinLineBtn, "dot1.png","dot1_enter.png","dot1_down.png");
	updateToolBtnStytle(m_pMediateLineBtn, "dot2.png","dot2_enter.png","dot2_down.png");
	updateToolBtnStytle(m_pBigLineBtn, "dot3_down.png","dot3_enter.png","dot3_down.png");
	m_curPen.setWidth(BIG_LINE);
	emit signalSelectChange(m_curPen);
}
void SelectColorWidget::slotFontChanged(const QString font)
{
	int fontPix = font.toInt();
	m_curFont.setPixelSize(fontPix);
	
	emit signalSelectFontChange(m_curPen, m_curFont);
}

CustomTextEditWidget::CustomTextEditWidget(QWidget *parent ) : QWidget(parent)
{
	m_pTextEdit = new QTextEdit(this);
	m_pTextEdit->setMinimumSize(50, 23);
	m_pTextEdit->resize(60, 23);
	m_pTextEdit->setStyleSheet("QTextEdit{border-image:url(images/textEditboder.png);}");
	m_pTextEdit->setLineWrapMode(QTextEdit::WidgetWidth);
	m_pTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_pMainLayout = new QGridLayout;
	m_pMainLayout->setContentsMargins(0, 0, 0, 0);
	m_pMainLayout->setSpacing(2);
	m_pMainLayout->addWidget(m_pTextEdit, 0, 0, 1, 1);
	m_pMainLayout->sizeHint();
	m_pMainLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 1, 1, 1);
	m_pMainLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 0, 1, 1);


	setLayout(m_pMainLayout);

}
CustomTextEditWidget::~CustomTextEditWidget()
{

}