#pragma once
#include <core/BaseDialog.h>
#include "workbench/Workbench.h"
class QStackedWidget;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QWidget;
namespace ui{
	class PushButton;
	class Workbench;
	class MainWeb :public BaseDialog{
		Q_OBJECT
	public:
		explicit MainWeb(QWidget *parent = 0);
		~MainWeb();
	protected:
		virtual void paintEvent(QPaintEvent *event);
	signals:
		void signalSerOpenChatWidget(int64);
	public slots:
		void onSerClose();
		void onSerMin();
		void onSerMax();
	/*	void onSerClicked1();
		void onSerClicked2();*/
	private:
		bool		  m_isLeftPressDown;	  //按下鼠标左键
	private:
		//CSharedPtr<Workbench> workbench_widget;
		QVBoxLayout* mMainLayout;
		QHBoxLayout* mTitleLayout;
		Workbench* workbench_widget;

		PushButton* mBtnClose;
		PushButton* mBtnMin;
		PushButton* mBtnMax;

		QLabel* mTitleName;
		bool m_is_running;
		bool m_isMax;
		/*QStackedWidget* StackWidget;
		QHBoxLayout* layout1;
		QPushButton* btn1;
		QPushButton* btn2;
		QWidget* widget1;
		QWidget* widget2;
		QLabel* mlbl;*/
		
	};
}