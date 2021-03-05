#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include "core/BaseDialog.h"
#include "common/Controlptr.h"
class IUpdateControl;
namespace ui{
	class PushButton;
	class UpdateFinishWindow;
	class UpdateProgressWindow;
	class UpdateTray;
	class UpdateWindow : public BaseDialog
	{
		Q_OBJECT

	public:
		UpdateWindow(QWidget *parent=CNull);
		~UpdateWindow();
		 void CheckUpdate();
		 int CheckReplace();
	protected:
		QString GetUrlByLocalFile();
		void StartReplace();
		int IsNeedReplace();
		void ShowWindow();
		void SetDesktopLinkNew();
		void ReplaceSelf();
		void CreateReplaceTipWnd();
	signals:
		 void updateNewVersion();
		 void signalSerUpdateInfoNotice(data::UpdateInfo&info);
		 void signalSerDownloadUpdate(int);
		 void signalSerCancelDownLoad(int);
		 void signalSerProgressUpdate(int32, int32,const std::string&,int64);
		 void signalExitClient(bool isrestart);
	protected slots:
		void onUpdate();
		void onSerUpdateInfoNotice(data::UpdateInfo&info);
		void onSerDownloadUpdate(int err);
	    void onSerProgressUpdate(int32 extra, int32 progress, const std::string& info,int64 uilocalid);
		void onTimerShowUpdateWindow();
		void onCancelDownLoad();
		void onSerCancelDownLoad(int err);
		void onRestartApp();
	protected:
		void RestartClient();
		void WriteMd5ToFile();
	private:
		PushButton* mBtnClose;
		PushButton* mBtnMin;
		QTextEdit*mText;
		QPushButton* mBtnUpdate;
		QPushButton* mBtnExit;
	private:
		data::UpdateInfo m_updateinfo;
		int64		m_uilocalid;
		int64		m_marfileid;
		QString m_userdatapath;
		CSharedPtr<UpdateFinishWindow>   m_finishwin;
		CSharedPtr<UpdateTray> m_updatetray;
		CSharedPtr<UpdateProgressWindow> m_progresswin;
	private:
		IUpdateControl_Ptr m_updatecontrol;
	};
}
#endif // UPDATEWINDOW_H
	