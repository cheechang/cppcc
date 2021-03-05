#ifndef LOCALSEARCHLISTITEMWIDGET_H
#define LOCALSEARCHLISTITEMWIDGET_H

#include "../group/GroupListItemWidget.h"
namespace ui{
	class LocalSearchListItemWidget : public GroupListItemWidget
	{
		Q_OBJECT
	public:
		LocalSearchListItemWidget(QWidget *parent=CNull);
		~LocalSearchListItemWidget();
	private:

	};
}

#endif // LOCALSEARCHLISTITEMWIDGET_H
