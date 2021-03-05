#pragma once
#include "TWidget.h"
#include <qstring.h>
class QLabel;
namespace ui{
  class PushButton;
}
namespace uicontrols{
	class TitleBar : public ui::TWidget
	{
		Q_OBJECT
	public:
		explicit TitleBar(QWidget *parent = 0,bool showMinbtn=true,bool showMaxBtn=true,bool showCloseBtn=true);
		~TitleBar();
		enum OBJTYPE{
		   OBJ_SELF,
		   OBJ_TITLE=1,
		   OBJ_ICON,
		   OBJ_MIN,
		   OBJ_MAX,
		   OBJ_CLOSE,
		   OBJ_ADVANCESET
		};
		//设置为true则自己处理最大化、最小化、关闭按钮事件需要连接对应的信号,默认值为false
		void setSelfDealBtnEvent(bool isSelfdeal);
		void setWindowMove(bool ismove);
		void setBackGroudImg(QString img);
		void setBackGroudColor(QColor color);
		void setTitleText(QString title);
		void setIcon(QString icon);
		void setObjectSize(OBJTYPE type,QSize size);
		void setElemObjectName(OBJTYPE type,QString name);
		void setBtnPicName(OBJTYPE type,QString name);
		void setBtnToolTip(OBJTYPE type,QString name);
		void setObjectVisible(OBJTYPE type,bool visible);
		void setWindowRadius(qint32 val);
		void setWindowMargin(qint32 val);
		QObject* getObj(OBJTYPE type);
		void setShowMax();
	protected:
		// 双击标题栏进行界面的最大化/还原
		void mouseDoubleClickEvent(QMouseEvent *event);
		// 进行鼠界面的拖动
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent*event);
		// 设置界面标题与图标
		bool eventFilter(QObject *obj, QEvent *event);
	protected:
		void paintEvent(QPaintEvent *event);
	signals:
		void signalMin();
		void signalMax();
		void signalClose();
		void signalMaxStateChanged(bool isMax);
		void signalWindowSizeChanged();
		void signalAdvanceSet();
	private slots:
		// 进行最小化、最大化/还原、关闭操作
		void onClicked();
	private:
		// 最大化/还原
		void updateMaximize();
	private:
		bool m_Drag;
		bool m_ismove;
		bool m_isSelfdeal;
		bool m_isMax;
		QSize m_windowNormalSize;
		QPoint m_DragPosition;
		QString m_BackImg;
		QColor  m_backColor;
		QLabel *m_pIconLabel;
		QLabel *m_pTitleLabel;
		ui::PushButton *m_pMinimizeButton;
		ui::PushButton *m_pMaximizeButton;
		ui::PushButton *m_pCloseButton;
		ui::PushButton *m_pAdvanceSetButton;
		qint32 m_WindowRadius;
		qint32 m_WindowMargin;
	};
}