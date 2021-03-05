#pragma once
#include "TWidget.h"
class QLabel;
class QPushButton;
namespace ui{
	class TitleBar : public TWidget
	{
		Q_OBJECT
	public:
		explicit TitleBar(QWidget *parent = 0,bool showMinbtn=true,bool showMaxBtn=true,bool showCloseBtn=true,bool isSelfdeal=false);
		~TitleBar();
		void setWindowMove(bool ismove);
	protected:
		// 双击标题栏进行界面的最大化/还原
		virtual void mouseDoubleClickEvent(QMouseEvent *event);
		// 进行鼠界面的拖动
		virtual void mousePressEvent(QMouseEvent *event);
		// 设置界面标题与图标
		virtual bool eventFilter(QObject *obj, QEvent *event);
	protected:
		void paintEvent(QPaintEvent *event);
	signals:
		void signalMin();
		void signalMax();
		void signalClose();
		void signalWindowSizeChanged();
	private slots:
		// 进行最小化、最大化/还原、关闭操作
		void onClicked();
	private:
		// 最大化/还原
		void updateMaximize();
	private:
		bool m_ismove;
		bool m_isSelfdeal;
		QLabel *m_pIconLabel;
		QLabel *m_pTitleLabel;
		QPushButton *m_pMinimizeButton;
		QPushButton *m_pMaximizeButton;
		QPushButton *m_pCloseButton;
	};

}