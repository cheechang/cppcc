#ifndef TWIDGET_H
#define TWIDGET_H

#include <QWidget>
#include <Defines.h>
class QTimer;
namespace ui{
	class TWidget : public QWidget
	{
		Q_OBJECT

	public:
		TWidget(QWidget *parent=CNull);
		~TWidget();
		void updateUI(bool start);
		void setSupportStretch(bool isSupportStretch);
    protected slots:
		void onTimeout();
	protected:
		virtual void paintEvent(QPaintEvent *event);
		virtual void mouseMoveEvent(QMouseEvent *event);
	private:
		CSharedPtr<QTimer> m_timer;
	};
}
#endif // TWIDGET_H
