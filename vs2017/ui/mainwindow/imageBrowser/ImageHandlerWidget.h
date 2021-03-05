#ifndef IMAGEHANDLERWIDGET_H
#define IMAGEHANDLERWIDGET_H
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QWidget>
#include "interface/Defines.h"
class ImageHandlerWidget : public QWidget
{
	Q_OBJECT
public:
	ImageHandlerWidget( QWidget*parent=CNull);
	~ImageHandlerWidget();

	void setPixmap(const QPixmap &pixmap,bool isCcale=true);

	void reset();

	void showSuitableSize();
	void zoomIn();
	void zoomOut();
	void rotate();
private:
	void ariseScale(int rate);
signals:
	void percentageChanged(double percentage);
	void rightButtonClicked();

protected:
	void paintEvent(QPaintEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
private:
	QPixmap m_pixmap;
	double m_scale;       //缩放比例
	double m_percentage;  //缩放百分比

	QPoint m_pressPoint; //鼠标按下点的坐标
	double m_originX;
	double m_originY;
	double m_basicX;
	double m_basicY;

	int m_suitableWidth;
	int m_suitableHeight;
    bool m_isInit;
	bool m_isPress;
};

#endif // IMAGEHANDLERWIDGET_H
