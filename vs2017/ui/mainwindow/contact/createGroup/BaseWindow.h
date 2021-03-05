#ifndef BASEWINDOW_H
#define BASEWINDOW_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "core/BaseDialog.h"
#include <interface/Defines.h>
namespace ui{
	class PushButton;
	class BaseWindow : public BaseDialog
	{
		Q_OBJECT

	public:
		BaseWindow(QWidget *parent = CNull);
		~BaseWindow();
		void setTitle(QString title);
		void SetBtnVisible(int index, bool isVisible);
	signals:
		void closeClicked();
	public slots:
		void onSerMaxShow();
	protected:
		void titleWidget();
		QLabel*mTitle;//БъЬт
		QVBoxLayout* mMainLayout;
		PushButton* mBtnClose;
	private:

	};
}

#endif // BASEWINDOW_H
