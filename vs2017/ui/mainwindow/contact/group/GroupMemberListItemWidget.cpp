#include "GroupMemberListItemWidget.h"
#include "controls/headimage.h"
namespace ui{
	GroupMemberListItemWidget::GroupMemberListItemWidget(QWidget *parent)
		: GroupListItemWidget(parent)
		, m_isMouseOver(false)
		, m_isMousePressed(false)
	{
		m_imgHead->setFixedSize(QSize(30,30));
		connect(m_imgHead.get(),SIGNAL(clicked(QPoint)),this,SIGNAL(clicked()));
	}

	GroupMemberListItemWidget::~GroupMemberListItemWidget()
	{

	}

	void GroupMemberListItemWidget::enterEvent(QEvent *event)
	{
		m_isMouseOver = true;
		event->accept();
	}

	void GroupMemberListItemWidget::leaveEvent(QEvent *event)
	{
		m_isMouseOver = false;
		event->accept();
	}

	void GroupMemberListItemWidget::mousePressEvent(QMouseEvent *event)
	{
		if(event->button() == Qt::LeftButton)
		{
			m_isMousePressed = true;
		}
		QWidget::mousePressEvent(event);
	}

	void GroupMemberListItemWidget::mouseReleaseEvent(QMouseEvent* event)
	{
		if(m_isMousePressed && m_isMouseOver)
		{
			//emit clicked();
		}
		QWidget::mouseReleaseEvent(event);
	}
}