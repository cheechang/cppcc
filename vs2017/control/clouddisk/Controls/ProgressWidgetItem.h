#pragma once
#include<QWidget>
#include <model/Packet.h>
class QLabel;
class QHBoxLayout;
class QLineEdit;
class QTableWidgetItem;
class QStackedLayout;
class QVBoxLayout;
namespace ui{
	class QClickLabel;
	class PushButton;
	class MyLineEdit;
	class FailedItem;
	class ProgressingItem;
	class SuccessItem;
	class ProgressWidgetItem : public QWidget
	{
		Q_OBJECT
	public:
		explicit ProgressWidgetItem(QWidget *parent = 0);
		~ProgressWidgetItem();
		void setItemRow(int row);
		int  getItemRow()const;
	public slots:
		void onRetry(int64);
		void onCancel(int64);
		void onFailed(int64);
		void onProgress(int32, int64, std::string&);
		void onSetCurrentStack(int,int64);
	signals:
		void signalProgress(int32, int64, std::string&);
		void signalCancle(int64);
		void signalRetry(int64);
		void signalError(int64);
		void signalDecryptFile(int64, model::CloudFileInfo&, std::string&);
	private:
		QStackedLayout* m_stack;
	private:
		int m_row; //保存item在列表中的行数
		int32 m_pro;
		FailedItem* m_failedItem;
		ProgressingItem* m_progressingItem;
		SuccessItem* m_successItem;
		QVBoxLayout*	m_mainlayout;
		int64 m_localId;
	};
}