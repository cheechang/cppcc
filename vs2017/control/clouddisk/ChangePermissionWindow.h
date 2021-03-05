#pragma once
#include <qdialog.h>
#include <model/packet.h>
class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QToolButton;
class QLineEdit;
class QLabel;

namespace ui{
	class TitleBar;
	class ChangePermissionWindow :public QDialog{
		Q_OBJECT
	public:
		explicit ChangePermissionWindow(std::vector<model::CloudRoleInfo>& info,QWidget*parent = nullptr);
		virtual ~ChangePermissionWindow();
	protected slots:
		void onBtnClicked(QString roleid);
	signals:
		void signalChangePerm(int);
	protected:
		void paintEvent(QPaintEvent *event);
	private:
		TitleBar* m_title;
		QList<QToolButton*> m_buttonlist;
		QVBoxLayout* m_contentlayout;
		QVBoxLayout* m_mainlayout;
	};
}