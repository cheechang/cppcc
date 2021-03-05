#ifndef TIPMESSAGEWIDGET_H
#define TIPMESSAGEWIDGET_H
#include "abstractmessagewidget.h"
class TipMessageWidgetPrivate;
class TipMessageWidget:public AbstractMessageWidget
{
	Q_OBJECT
public:
	explicit TipMessageWidget(QWidget* parent = 0);
	~TipMessageWidget();

	 void setTip(CSharedPtr<data::Msg>&msg);
	 QSize suggestWidth(int width);
protected:
	 QString dealTipMsg(CSharedPtr<data::Msg>&msg);
	 virtual void initializeContextActions();
	 void mousePressEvent(QMouseEvent *e);
private:
	  class TipMessageWidgetPrivate* d_ptr;
	  IGroupMgrControl_Ptr		m_groupcontrol;
};
#endif