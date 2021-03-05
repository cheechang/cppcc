#ifndef GROUPMEMBERLISTITEMWIDGET_H
#define GROUPMEMBERLISTITEMWIDGET_H

#include "GroupListItemWidget.h"

namespace ui{
	class GroupMemberListItemWidget : public GroupListItemWidget
	{
		Q_OBJECT

	public:
		GroupMemberListItemWidget(QWidget *parent=CNull);
		~GroupMemberListItemWidget();

	signals:
		void clicked();

	protected:
		virtual void enterEvent(QEvent *event);
		virtual void leaveEvent(QEvent *event);
		virtual void mousePressEvent(QMouseEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent* event);

	private:
		bool m_isMouseOver;
		bool m_isMousePressed;
	};
}

#endif // GROUPMEMBERLISTITEMWIDGET_H
