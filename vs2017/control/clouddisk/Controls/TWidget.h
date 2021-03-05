#ifndef TWIDGET_H
#define TWIDGET_H

#include <QWidget>
namespace ui{
	class TWidget : public QWidget
	{
		Q_OBJECT

	public:
		TWidget(QWidget *parent=nullptr);
		~TWidget();
	protected:
		void paintEvent(QPaintEvent *event);
	private:

	};
}
#endif // TWIDGET_H
