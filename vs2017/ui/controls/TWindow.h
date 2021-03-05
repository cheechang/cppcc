#ifndef TWINDOW_H
#define TWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <qmath.h>
#include <QVBoxLayout>
#include "WinTitleWidget.h"

namespace ui{
class TWindow : public QWidget
{
	Q_OBJECT

public:
	TWindow(QWidget *parent);
	~TWindow();

protected:
	void paintEvent(QPaintEvent *event);
private:
};
}
#endif // TWINDOW_H
