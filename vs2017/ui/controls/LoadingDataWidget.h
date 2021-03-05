#ifndef LOADINGDATAWIDGET_H
#define LOADINGDATAWIDGET_H

#include <QWidget>
#include <QLabel>
#include <interface/Defines.h>
namespace ui{
	class LoadingDataWidget : public QWidget
	{
		Q_OBJECT

	public:
		LoadingDataWidget(QWidget *parent = CNull);
		~LoadingDataWidget();
	void setTipText(QString text);
	protected:
		virtual void paintEvent(QPaintEvent* event);
	private:
		QLabel* mTipText;
	};
}

#endif // LOADINGDATAWIDGET_H
