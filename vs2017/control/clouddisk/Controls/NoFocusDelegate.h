#pragma once
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QItemDelegate>
class QPainter;
namespace ui{
class NoFocusDelegate : public QStyledItemDelegate
{
public:
	NoFocusDelegate(void);
	void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	~NoFocusDelegate(void);
};
}


