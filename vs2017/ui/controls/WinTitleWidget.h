#pragma once

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QHBoxLayout>
#include "PushButton.h"

namespace ui{
class WinTitleWidget : public QLabel
{
	Q_OBJECT

public:
	WinTitleWidget(QLabel *parent=NULL);
	~WinTitleWidget();
public slots:
		void onBtnClose();
protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
public: signals:
	void mouseMoveTo(QPoint gloPoint);
	void closeClicked();
private:
	QPoint m_pos;
	PushButton m_btnClose;
	QHBoxLayout m_hLayout;
};
}

