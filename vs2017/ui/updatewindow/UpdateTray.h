#pragma once
#include <QSystemTrayIcon>
class QAction;
class QMenu;
namespace ui{
	class UpdateTray : public QSystemTrayIcon{
		Q_OBJECT
	public:
		UpdateTray(QObject*parent=0);
		~UpdateTray();
	    void showTipInfo(QString& content,bool isexittray=false);
	protected:
		void translateLanguage();
	signals:
		void signalQuit();
		void signalShow();
	public slots:
		void onActivated(QSystemTrayIcon::ActivationReason reason);
		void onQuit();
		void onShowErrInfo(int errtype);
	private:
		QMenu *tray_menu;		  //ÍÐÅÌ²Ëµ¥
		QAction *action_quit;	  //ÍË³ö
	};
}