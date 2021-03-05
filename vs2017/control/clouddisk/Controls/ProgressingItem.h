#pragma once
#include<QWidget>
#include <model/Packet.h>
class QLabel;
class QHBoxLayout;
class QLineEdit;
class QTableWidgetItem;
class QProgressBar;
namespace ui{
	class QClickLabel;
	class PushButton;
	class MyLineEdit;
	class ProgressingItem : public QWidget
	{
		Q_OBJECT
	public:
		explicit ProgressingItem(QWidget *parent = 0);
		~ProgressingItem();
		void setItemRow(int row);
		int  getItemRow()const;
		void setProgress(int32, int64,std::string& filename);
	public slots:
		void onProgress(int32 proval, int64 localid,  std::string&);
		void onCancel();
	signals:		
		void display(int number,int64 localid);
		void signalCancel(int64 localid);
		void signalPath(QString , int64);
	private:
		QProgressBar*	m_progress; // 进度
		PushButton*		m_pauseBtn; //暂停
		PushButton*     m_cancelBtn; //取消
		QHBoxLayout*	m_mainlayout;
		int64 m_localId;

	private:
		int m_row; //保存item在列表中的行数
		int32 m_pro;
	};
}