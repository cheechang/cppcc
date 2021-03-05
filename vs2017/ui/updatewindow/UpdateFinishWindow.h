#ifndef UPDATEFINISHWINDOW_H
#define UPDATEFINISHWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "core/BaseDialog.h"
#include <interface/Defines.h>
namespace ui{
	class PushButton;
	class UpdateFinishWindow : public BaseDialog
	{
		Q_OBJECT

	public:
		UpdateFinishWindow(QWidget *parent =CNull);
		~UpdateFinishWindow();
	signals:
		void RestartApp();
	private:
		PushButton* mBtnClose;
		QPushButton*mBtnRestart;
	};
}

#endif // UPDATEFINISHWINDOW_H
