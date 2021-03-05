#pragma once
#include <qlineedit.h>
class QMouseEvent;
namespace ui{
	class MyLineEdit :public QLineEdit{
		Q_OBJECT
	public:
		explicit MyLineEdit(QWidget *parent = nullptr);
		virtual ~MyLineEdit();
		void setElidedText(QString str);
	signals:
		void signalClicked();
		void signalFocusOut();
	protected:
		void mouseDoubleClickEvent(QMouseEvent *e);
		void mousePressEvent(QMouseEvent *event);
		void focusOutEvent(QFocusEvent *e);
		void keyPressEvent(QKeyEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *e);
	};
}