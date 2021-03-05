#ifndef DRAW_SHAPE_WIDGET_H
#define DRAW_SHAPE_WIDGET_H

#include <QObject>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QToolButton>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsLineItem>
#include <QWheelEvent>
#include <QTextEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QtGui>
#include <QStackedWidget>

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QGraphicsTextItem>

#define THIN_LINE			1					//细线的宽度
#define MEDIATE_LINE		3				//中线
#define  BIG_LINE				6				//粗线
class Shape 
{ 
public: 
	enum Code { Line, Rect,Ellipse,Arrow,Text, PathBrush}; 
	Shape(){}
	virtual void startDraw(QGraphicsSceneMouseEvent * event) = 0;
	virtual void drawing(QGraphicsSceneMouseEvent * event) = 0; 
	virtual void SetCurPen(QPen pen){}
	virtual void SetVisibleRect(QRectF rect){}
}; 
class GraphicsViewWidget : public QGraphicsView
{
	Q_OBJECT 
public: 
	GraphicsViewWidget(QGraphicsScene * scene, QWidget * parent = 0 ):QGraphicsView(scene,parent){}
protected:
	void wheelEvent ( QWheelEvent * event ){event->ignore();}
};
class PaintWidgetScene : public QGraphicsScene 
{ 
	Q_OBJECT 
public: 
	PaintWidgetScene(QWidget *parent = 0); 
	void SetVisibleRect(QRectF rect){m_visibleRect = rect;}
	void SetTextToScene();
public slots: 
	void slotSetCurrentShape(Shape::Code s, QPen pen);
	void slotDelLastDraw();
	void slotSetCurPen(QPen pen);
	void slotSetCurFont(QPen pen, QFont font);
	void slotAddText(QString content);
signals:
	void signalLeftBtnPressed(QPointF, bool);			//发给主窗口，判断是否显示文本编辑框
protected: 
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent ){wheelEvent->ignore();}
private:
	QTextEdit*   m_pEditText;
private: 
	Shape::Code m_currShapeCode; 
	Shape *		m_currItem; 
	bool				m_perm; 
	QMap<int, QGraphicsItem*>  m_itemGroupMap;            //item添加顺序的映射(为了撤销绘图)
	QPen			m_curPen;
	QFont			m_curFont;
	bool				m_bIsTextEdit;
	bool				m_bIsPressText;			//当操作是编辑时，标志是否左键按下
	QRectF			m_visibleRect;
}; 

class Line : public Shape, public QGraphicsLineItem 
{ 
public: 
	Line(){}
	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);
}; 
class Arrow : public Shape, public QGraphicsPolygonItem 
{ 
public: 
	Arrow(){m_fArrowAngle = 0.2;m_fArrowLength = 8; m_bIsDraw = false;}
	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);
	void SetCurPen(QPen pen);
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = 0);
	void SetVisibleRect(QRectF rect){m_visibleRect=rect;}
private:
	QPen			 m_curPen;
	QPointF		m_pointF;
	QPointF		m_endPointF;
	float			    m_fArrowLength;      //箭头的那长度  
	float				m_fArrowAngle;      // 箭头与线段角度 (箭头的夹角) 
	bool				m_bIsDraw;
	QRectF			m_visibleRect;
}; 

class Path : public Shape, public QGraphicsPathItem
{ 
public: 
	Path(){}
	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);
	void SetCurPen(QPen pen){m_curPen = pen;}
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = 0);
	void SetVisibleRect(QRectF rect);
private:
	QPainterPath m_paintPath;
	QPen			 m_curPen;
	QRectF			m_visibleRect;
}; 

class Rect : public Shape, public QGraphicsRectItem 
{ 
public: 
	Rect(){}
	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);
	void SetVisibleRect(QRectF rect){m_visibleRect = rect;}
private:
	QRectF			m_visibleRect;
}; 
class DrawEllipse : public Shape, public QGraphicsEllipseItem 
{ 
public: 
	DrawEllipse(){}
	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);
	void SetVisibleRect(QRectF rect){m_visibleRect = rect;}
private:
	QRectF			m_visibleRect;
}; 

class Text : public Shape, public QGraphicsTextItem 
{ 
public: 
	Text(){m_bIsAdd = false;}
	void startDraw(QGraphicsSceneMouseEvent * event);
	void drawing(QGraphicsSceneMouseEvent * event);
	void SetTextFontAndPen(QPen pen, QFont font);
	void SetTextRectF(QRectF rect);
	void addText(QString text);
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = 0);
private:
	QPointF		m_beginPointF;
	QPointF		m_endPointF;
	QPen			m_curPen;
	QFont			m_curFont;
	QString		m_strText;
	QRectF			m_rect;
	bool				m_bIsAdd;          //这个Item是否已经添加到view中
}; 
class CustomColorButton : public QToolButton
{
	Q_OBJECT
public:
	CustomColorButton(QWidget* parent = 0);
	~CustomColorButton(){}
	void SetIndex(int index){m_index = index;}
signals:
	void Clicked(int index);
protected slots:
	void slotBtnClicked(){emit Clicked(m_index);}
private:
	int		m_index;
};
class SelectColorWidget : public QWidget
{
	Q_OBJECT
public:
	SelectColorWidget(QWidget *parent = 0, int type = 0);						//type : 0.非字体， 1.设置字体
	~SelectColorWidget();
	void LoadQssFile(  QString qssFileName );
	void updateToolBtnStytle(QToolButton* &toolBtn,QString picNormal,QString PicHot,QString PicPressed);
	void updateCustomToolBtnStytle(CustomColorButton* &toolBtn,QString picNormal,QString PicHot,QString PicPressed);
	QPen GetCurPen(){return m_curPen;}
	QFont GetCurFont(){return m_curFont;}
protected slots:
	void slotColorBtnClicked(int index);			//选择颜色
	void	slotThinLineClicked();					  //细线
	void slotMediateLineClicked();               //中线
	void slotBigLineClicked();						//粗线
	void slotFontChanged(const QString font);   //字体大小改变
signals:
	void signalSelectChange(QPen);
	void signalSelectFontChange(QPen, QFont);
protected:
	void	  paintEvent(QPaintEvent *event);
private:
	QComboBox*		m_pFontComBox;
	QHBoxLayout*     m_pFontLayout;
	QToolButton*		m_pThinLineBtn;
	QToolButton*       m_pMediateLineBtn;
	QToolButton*		m_pBigLineBtn;
	QLabel*				m_pCutLineLabel;
	QLabel*				m_pSeledColorLabel;
	QWidget*				m_pSelectColorWidget;
	QHBoxLayout*		m_pSelectColorLayout;
	std::map<int, CustomColorButton*>   m_mapIndexColorBtn;
	std::map<int, QColor>				m_mapIndexColorValue;
	QGridLayout*		m_pColorLayout;
	QWidget*				m_pColorWidget;
	QHBoxLayout*     m_pLineLayout;
	QWidget*				m_pLineWidget;
	QStackedWidget* m_pLineOrFontWidget;
	QHBoxLayout*		m_pMainLayout;

private:
	QString m_imagePath;
	QPen		m_curPen;
	QFont		m_curFont;
	int			m_iType;
};


class CustomTextEditWidget : public QWidget
{
	Q_OBJECT
public:
	CustomTextEditWidget(QWidget *parent = 0);
	~CustomTextEditWidget();
private:
	QGridLayout*		m_pMainLayout;
	QTextEdit*		    m_pTextEdit;
};

#endif // DRAWPRACTISE_H
