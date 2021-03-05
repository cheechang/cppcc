#ifndef TREEVIEWMODEL_H
#define TREEVIEWMODEL_H

#include <QModelIndex>
#include <QVariant>
#include <QAbstractItemModel>
#include <vector>

#include <data/entpriseInfo.h>
#include "TreeViewItem.h"
namespace ui{
	enum{
		HeadRole=Qt::UserRole+1,
		NameRole,
		ToolTipRole,
		IsLeafRole,
		TileRole,
		TipNodeRole
	};
	class TreeModel : public QAbstractItemModel
	{
		Q_OBJECT
	public:
		static bool isInit;
		explicit TreeModel(QObject *parent = 0);
		~TreeModel();

		void updateModelData(std::vector<data::OrgAndUserInfo>orgs);
		void updateModelData(TreeItem*parent,std::vector<data::OrgAndUserInfo>orgs);

		void refreshUiData( TreeItem* parent );
		void refreshUiData( QModelIndex &index);

		bool isTipNode(const QModelIndex &index);

		void insertItem( data::OrgAndUserInfo org, TreeItem* parent );
		TreeItem * item(const QModelIndex &index);
		QModelIndex getChildIndex(TreeItem* item);

		QVariant data(const QModelIndex &index, int role) const;
		void parceOrgDataFromItem( QList<QVariant> &dataList, data::OrgAndUserInfo &outData) const;
		Qt::ItemFlags flags(const QModelIndex &index) const;
		QVariant headerData(int section, Qt::Orientation orientation,
			int role = Qt::DisplayRole) const;
		QModelIndex index(int row, int column,
			const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
	private:
		
		TreeItem *item(TreeItem *item, data::OrgAndUserInfo data);
		QList<QVariant> formatVariantListFromData( data::OrgAndUserInfo data,bool isFromService=true);

		TreeItem *rootItem;
	};
}
#endif // TREEVIEWMODEL_H
