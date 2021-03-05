#pragma once
#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>
#include <memory>
namespace ui{
	class BaseDialog : public QDialog
	{
		Q_OBJECT
	public:
		explicit BaseDialog(QWidget *parent = 0);
		virtual ~BaseDialog();
	public:
		virtual void setSupportStretch(bool isSupportStretch);
	public slots:
		void onMoveWindow(bool val);
	protected:
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		virtual void paintEvent(QPaintEvent *event);
	protected:
		void region(const QPoint &cursorGlobalPoint);
		bool eventFilter(QObject *obj, QEvent *event);
		void updateWindowSize(QPoint& gloPoint,QMouseEvent *event);
	private:
		QPoint    m_movePosition;		  //移动的距离
		bool      m_isMoveWindow;		  //是否是移动窗口
	};
}

