#pragma once
#include <qdialog.h>
#include <model/Packet.h>
class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QToolButton;
class QLineEdit;
class QLabel;
namespace ui{
	class TitleBar;
	class ProgressWidget;
	class ProgressWindow :public QDialog{
		Q_OBJECT
	public:
		explicit ProgressWindow(QWidget*parent = nullptr);
		virtual ~ProgressWindow();
		void addItem(model::CloudFileInfo& data, QString name);
		void setTitle(QString title);
		void SetProcess(int32, int64,std::string&);
	public slots:
		void onClose();
		void onCancel(int64);
		void onRetry(int64);
		void onWindowSizeChanged();
	signals :
		void signalClose();
		void signalDownClose();
		void signalUpClose();
		void signalDownCancel(int64);
		void signalUpCancel(int64);
		void signalUpRetry(int64);
		void signalDownRetry(int64);
		void signalDownFail(int64);
		void signalUpFail(int64);
		void signalDecryptFile(int64, model::CloudFileInfo&, std::string&);
	protected:
		void paintEvent(QPaintEvent *event);
	private:
		TitleBar* m_title;
		ProgressWidget* m_progress;
		QVBoxLayout* m_tableLayout;
		QVBoxLayout* m_mainlayout;
	};
}