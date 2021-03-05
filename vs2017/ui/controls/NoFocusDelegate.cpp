#include "NoFocusDelegate.h"
#include <QPainter>
namespace ui{
	NoFocusDelegate::NoFocusDelegate(void)
	{
	}
	void NoFocusDelegate::paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		QStyleOptionViewItem itemOptin(option);

		if (itemOptin.state & QStyle::State_HasFocus)
		{
			itemOptin.state = itemOptin.state ^ QStyle::State_HasFocus;
		}
		QStyledItemDelegate::paint(painter, itemOptin, index);
	}
	NoFocusDelegate::~NoFocusDelegate(void)
	{
	}
}
