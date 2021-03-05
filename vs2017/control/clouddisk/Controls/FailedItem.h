#pragma once
#include<QWidget>
#include <model/Packet.h>
class QLabel;
class QHBoxLayout;
class QLineEdit;
namespace ui{
	class QClickLabel;
	class PushButton;
	class MyLineEdit;
	class FailedItem : public QWidget
	{
		Q_OBJECT
	public:
		explicit FailedItem(QWidget *parent = 0);
		~FailedItem();
		void setItemRow(int row);
		int  getItemRow()const;
	public slots:
		void onRetry();
		void btnClicked();
		void onCancel(int64);
		void onError(int64);
	signals:
		void display(int,int64);
		void signalRetry(int64);
	private:
		PushButton*		m_retryBtn;  //重试
		QHBoxLayout*	m_mainlayout;
		QHBoxLayout*    m_progressLayout;
		QHBoxLayout*    m_failLayout;
		QLabel*			m_result;
		int m_row; //保存item在列表中的行数
		int64 m_localId;
	};
}