#ifndef TREEVIEWITEMDELEGATE_H
#define TREEVIEWITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QTreeView>
#include "common/Common.h"

namespace ui{
	class TreeViewItemDelegate : public QStyledItemDelegate
	{
		Q_OBJECT
		enum{
			ImageSize = HEAD_SIZE,
			DepartHeigth = 30,
			UserHeight = 60
		};
	public:
		TreeViewItemDelegate(QObject *parent);
		virtual ~TreeViewItemDelegate();

		void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
		bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

		void setView(QTreeView *treeView);
		QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const;
		QImage getRoundQImage(QImage& img,QSize size) const;
	private:
		 QTreeView *m_treeView;
	};
}

#endif // TREEVIEWITEMDELEGATE_H
