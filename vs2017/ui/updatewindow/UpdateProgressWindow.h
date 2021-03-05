#ifndef UPDATEPROGRESSWINDOW_H
#define UPDATEPROGRESSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include "core/BaseDialog.h"
#include <interface/Defines.h>
namespace ui{
	class PushButton;
	class UpdateProgressWindow : public BaseDialog
	{
		Q_OBJECT
	public:
		enum ErrType{
			ERR_INIT,
			ERR_USERCANCEL,
			ERR_DOWNLOADFAILED,
			ERR_CHECKCOMPLETEFAILED
		};
		UpdateProgressWindow(QWidget *parent =CNull);
		~UpdateProgressWindow();
		void updateProgress(int value);
		void seterrtip(ErrType type);
    signals:
		void CancelDownLoad();
		void ReDownLoad();
		void ShowErrInfo(int);
	public slots:
		void ShowWindow();
		void onBtnCloseClicked();
		void onShow();
		void onBtnReDownLoadClicked();
	private:
		QPushButton* mBtnExit;
		QPushButton* mBtnReDownLoad;
		PushButton* mBtnClose;
		PushButton* mBtnMin;
		QProgressBar* mProgressBar;
		QLabel*mLblProgress;
		QLabel*merrtip;
	};
}

#endif // UPDATEPROGRESSWINDOW_H
