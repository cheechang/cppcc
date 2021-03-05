#ifndef CLIPWIDGET_H
#define CLIPWIDGET_H

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QImage>
#include <QLabel>
#include <QSlider>
#include <QEvent>
#include "DragScrollArea.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>

class ClipWidget : public QWidget
{
	Q_OBJECT

public:
	ClipWidget(QWidget *parent=NULL);
	~ClipWidget();

	void saveImg();
	void setImgPath(QString filename);
public slots:
	void onScaledChanged(int nValue);
	void LoadHeader(const QPixmap& pixmap);
signals:
	void clipImgSucc(QString file400, QString file150);
protected:
	bool eventFilter(QObject* watched, QEvent* event);
	//void mousePressEvent(QMouseEvent *event);
private:
	QString m_fileName;
	DragScrollArea *scrollArea;
	QWidget *scrollAreaWidgetContents;
	QLabel *label_header;
	QSlider *horizontalSlider;

	QWidget* m_pDivWidget;
	QPixmap m_sourceHeader;

	QVBoxLayout* verticalLayout;
};

#endif // CLIPWIDGET_H
