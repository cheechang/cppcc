#pragma once
#include <qdialog.h>
class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QToolButton;
class QLineEdit;
class QLabel;
namespace ui{
	class TitleBar;
	class CreateFolderWindow :public QDialog{
		Q_OBJECT
	public:
		explicit CreateFolderWindow(QWidget*parent = nullptr);
		virtual ~CreateFolderWindow();
	protected slots:
		void onOkBtnClicked();
		void onCancelClicked();
	signals:
		void signalCreateFolder(QString&foldername);
	protected:
		void paintEvent(QPaintEvent *event);
	private:
		TitleBar* m_title;
		QLabel*   m_label;
		QLineEdit* m_edit;
		QToolButton* m_ok;
		QToolButton* m_cancel;
		QVBoxLayout* m_contentlayout;
		QHBoxLayout* m_btnLayout;
		QVBoxLayout* m_mainlayout;
	};
}