#pragma once
#include <QListWidget>
#include <QMouseEvent>
#include <QWidget>
#include <QScrollBar>
#include <QWheelEvent>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDesktopWidget>

namespace uicontrols
{
	class BaseQListWidget : public QListWidget
	{
	Q_OBJECT
	public:
		BaseQListWidget(QWidget* parent = nullptr, bool isShowScrollBarNormal = false);
		~BaseQListWidget();

		enum
		{
			LIST_ITEM_HEIGHT = 62,
			LIST_ITEM_WIDTH = 226,
		};

	signals:
		void signalSrcollToBottom(); //Êó±êµ½µ×ÁË
		void signalScrollChanged();
	protected:
		void mouseMoveEvent(QMouseEvent* event) override;
		void wheelEvent(QWheelEvent* event) override;
		void enterEvent(QEvent* event) override;
		void leaveEvent(QEvent* event) override;
		void resizeEvent(QResizeEvent* e) override;
	protected slots:
		void animateVerScrollBar(int start, int end);
	private:
		bool m_isfirst;
		bool m_isShowScrollBarNormal;
	};
}
