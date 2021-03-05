#ifndef MYEMOTIONITEMWIDGET_H
#define MYEMOTIONITEMWIDGET_H

#include <QLabel>
#include <interface/Defines.h>
namespace ui{
	class ExpressionItemWidget : public QLabel
	{
		Q_OBJECT

	public:
		ExpressionItemWidget(QString fileName, QSize emotionMoiveSize,QWidget*parent=CNull);
		~ExpressionItemWidget();
	signals:
		void clicked(QString fileName);
	protected:
		void mousePressEvent(QMouseEvent *ev);
	private:
		void enterEvent(QEvent *event);
		void leaveEvent(QEvent *event);
	private:

	};
}
#endif // MYEMOTIONITEMWIDGET_H
