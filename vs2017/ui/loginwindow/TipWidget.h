#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class QTimer;
namespace ui {
	class PushButton;
	class TipWidget :
		public QWidget
	{
		Q_OBJECT
	public:
		TipWidget(QWidget *parent = 0);
		~TipWidget(void);
		virtual void paintEvent(QPaintEvent* event);
		void setTipText(QString tipText);

		void setTipSize(QSize size);
		void setTime(int time);
		void ErrShow();
		public slots:
		void onTimeOut();
	private:
		QHBoxLayout*	m_pTitleBtnLayout;
		PushButton*		m_pCloseButton;		//¹Ø±Õ
		QLabel*			m_pTipText;
		int				m_showTime;
		QTimer*		    m_timer;
	};
}

