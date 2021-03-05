#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QToolButton>

namespace uicontrols{
	class IconButton : public QToolButton
	{
		Q_OBJECT
	public:
		//ö�ٰ�ť�ļ���״̬
		enum ButtonStatus{
			NORMAL,
			ENTER, 
			PRESS,
			NOSTATUS
		};

		explicit IconButton(QWidget *parent = 0);
		~IconButton();

		//����ICON
		void setPicName(QString pic_name);
		//��ȡ״̬
		ButtonStatus  btnStatus();
		void		  setBtnStatus(ButtonStatus status);
		//�����Ƿ��ѡ��״̬
		void setCheckable( bool canCheckable,bool checked);
		//��ȡѡ��
		bool checkedStatus();
   signals:
		void  signalDoubleClicked();
	protected:
		void enterEvent(QEvent *);
		void leaveEvent(QEvent *);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *);
		//����
		void mouseDoubleClickEvent(QMouseEvent*);
	private:
		QString m_pic_name;
		ButtonStatus m_status;

		int  m_btnWidth; //��ť���
		int  m_btnHeight; //��ť�߶�
		bool m_bMousePressed; //��ť����Ƿ���
		bool m_btnCanchecked;
		bool m_btnChecked;
	};
}
#endif // ICONBUTTON_H
