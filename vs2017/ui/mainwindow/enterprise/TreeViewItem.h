#pragma once
#include <QList>
#include <QVariant>
namespace ui{
	class TreeItem
	{
	public:
		explicit TreeItem( QList<QVariant> &data, TreeItem *parent = 0);
		~TreeItem();

		void appendChild(TreeItem *child);
		void updateData(int index,QVariant data);
		TreeItem *child(int row);
		int childCount() const;
		int columnCount() const;
		QVariant data(int column) const;
		int row() const;
		TreeItem *parent();
		int size(){return itemData.count();}
		QList<QVariant> getItemData();
	private:
		QList<TreeItem*> childItems;
		QList<QVariant> itemData;
		TreeItem *parentItem;
	};
}
