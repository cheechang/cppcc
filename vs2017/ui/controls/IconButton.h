#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QToolButton>

namespace uicontrols{
	class IconButton : public QToolButton
	{
		Q_OBJECT
	public:
		//枚举按钮的几种状态
		enum ButtonStatus{
			NORMAL,
			ENTER, 
			PRESS,
			NOSTATUS
		};

		explicit IconButton(QWidget *parent = 0);
		~IconButton();

		//设置ICON
		void setPicName(QString pic_name);
		//获取状态
		ButtonStatus  btnStatus();
		void		  setBtnStatus(ButtonStatus status);
		//设置是否可选中状态
		void setCheckable( bool canCheckable,bool checked);
		//获取选中
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
		//声明
		void mouseDoubleClickEvent(QMouseEvent*);
	private:
		QString m_pic_name;
		ButtonStatus m_status;

		int  m_btnWidth; //按钮宽度
		int  m_btnHeight; //按钮高度
		bool m_bMousePressed; //按钮左键是否按下
		bool m_btnCanchecked;
		bool m_btnChecked;
	};
}
#endif // ICONBUTTON_H
