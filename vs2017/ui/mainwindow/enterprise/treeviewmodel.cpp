#include "treeviewmodel.h"
#include <QIcon>
#include <QBrush>
#include "../../common/Common.h"
namespace ui{
	bool TreeModel::isInit = true;
	TreeModel::TreeModel(QObject *parent)
		: QAbstractItemModel(parent)
	{
		QList<QVariant> rootData;
		rootData << "Title";
		rootItem = new TreeItem(rootData);
	}

	TreeModel::~TreeModel()
	{
		delete rootItem;
	}

	int TreeModel::columnCount(const QModelIndex &parent) const
	{
		if (parent.isValid())
			return static_cast<ui::TreeItem*>(parent.internalPointer())->columnCount();
		else
			return rootItem->columnCount();
	}

	QVariant TreeModel::data(const QModelIndex &index, int role) const
	{
		if (!index.isValid())
			return QVariant();

		TreeItem *item = static_cast<ui::TreeItem*>(index.internalPointer());
		QList<QVariant> dataList = item->getItemData();
		data::OrgAndUserInfo outData;
		parceOrgDataFromItem(dataList,outData);
		
		if (role == TileRole)
		{
			if(outData.leaf){
				return outData.enName.c_str();
			}
			return outData.orgName.c_str();
		}
		else if (role == HeadRole)
		{
			return outData.head.c_str();
		}
		else if (role == ToolTipRole)
		{
			return !outData.leaf ? outData.orgName.c_str():outData.enName.c_str();
		}else if(role == IsLeafRole){
			return outData.leaf;
		} else if (role == Qt::DecorationRole && !outData.leaf)
		{   
			return  item->childCount()<=0 ? QIcon(QString(":/contact/branchClose")):QVariant();
		}else if(role == TipNodeRole){
			return outData.orgName.empty();
		}
		else
		{
			return QVariant();
		}
	}

	void TreeModel::parceOrgDataFromItem(QList<QVariant> &dataList,data::OrgAndUserInfo &outData) const
	{
		outData.userID = dataList.at(0).toLongLong();
		outData.status = (data::ORG_NODE_STATUS)dataList.at(1).toInt();
		outData.enterpriseID = dataList.at(2).toLongLong();
		outData.orgID = dataList.at(3).toLongLong();
		outData.parentOrgID = dataList.at(4).toLongLong();

		outData.head = dataList.at(5).toString().toStdString();
		outData.orgName = dataList.at(6).toString().toStdString();
		outData.enName = dataList.at(7).toString().toStdString();
		outData.duty = dataList.at(8).toString().toStdString();
		outData.enMail = dataList.at(9).toString().toStdString();
		outData.enMobile = dataList.at(10).toString().toStdString(); 

		outData.orgCode = dataList.at(11).toString().toStdString();
		outData.leaf = dataList.at(12).toBool(); 
		outData.remark = dataList.at(13).toString().toStdString();
	}

	Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
	{
		if (!index.isValid())
			return 0;

		return QAbstractItemModel::flags(index);
	}

	QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
		int role) const
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
			return rootItem->data(section);

		return QVariant();
	}

	QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
		const
	{
		if (!hasIndex(row, column, parent))
			return QModelIndex();

		TreeItem *parentItem;

		if (!parent.isValid())
			parentItem = rootItem;
		else
			parentItem = static_cast<TreeItem*>(parent.internalPointer());

		TreeItem *childItem = parentItem->child(row);
		if (childItem)
			return createIndex(row, column, childItem);
		else
			return QModelIndex();
	}

	QModelIndex TreeModel::parent(const QModelIndex &index) const
	{
		if (!index.isValid())
			return QModelIndex();

		TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
		TreeItem *parentItem = childItem->parent();

		if (parentItem == rootItem)
			return QModelIndex();

		return createIndex(parentItem->row(), 0, parentItem);
	}

	int TreeModel::rowCount(const QModelIndex &parent) const
	{
		TreeItem *parentItem;
		if (parent.column() > 0)
			return 0;

		if (!parent.isValid())
			parentItem = rootItem;
		else
			parentItem = static_cast<TreeItem*>(parent.internalPointer());

		return parentItem->childCount();
	}

	TreeItem * TreeModel::item(TreeItem *item, data::OrgAndUserInfo data)
	{
		TreeItem *treeItem = NULL;
		if (item == NULL)
		{
			return treeItem;
		}

		int64 parentId = data.parentOrgID;
		QList<QVariant> listData = item->getItemData();
		data::OrgAndUserInfo itemData;
		parceOrgDataFromItem(listData,itemData);

		if (itemData.parentOrgID == parentId)
		{
			treeItem = item;
		}
		else
		{
			for (int j = 0; j < item->childCount(); ++j)
			{
				TreeItem *childItem = item->child(j);
				TreeItem *item2 = this->item(childItem, itemData);
				if (item2)
				{
					treeItem = item2;
					break;
				}
			}
		}

		return treeItem;
	}

	TreeItem * TreeModel::item( const QModelIndex &index )
	{
		TreeItem* item = CNull;
		if(index.isValid()){
			return static_cast<TreeItem*>(index.internalPointer());
		}
		return item;
	}

	QList<QVariant> TreeModel::formatVariantListFromData( data::OrgAndUserInfo data,bool isFromService)
	{
		QList<QVariant> list;
		if(isFromService){
			list << data.userID << data.status << data.enterpriseID << data.orgID << data.parentOrgID 
				<< QString::fromUtf8(data.head.c_str()) 
				<< QString::fromUtf8(data.orgName.c_str())
				<< QString::fromUtf8(data.enName.c_str())
				<< QString::fromUtf8(data.duty.c_str())
				<< QString::fromUtf8(data.enMail.c_str())
				<< QString::fromUtf8(data.enMobile.c_str())
				<< QString::fromUtf8(data.orgCode.c_str())
				<< data.leaf 
				<< QString::fromUtf8(data.remark.c_str());
		}else{
			list << data.userID << data.status << data.enterpriseID << data.orgID << data.parentOrgID 
				<< QString(data.head.c_str()) 
				<< QString(data.orgName.c_str())
				<< QString(data.enName.c_str())
				<< QString(data.duty.c_str())
				<< QString(data.enMail.c_str())
				<< QString(data.enMobile.c_str())
				<< QString(data.orgCode.c_str())
				<< data.leaf 
				<< QString(data.remark.c_str());
		}

		return list;
	}

	void TreeModel::updateModelData( std::vector<data::OrgAndUserInfo>orgs )
	{
		int childsCount = orgs.size();
		if(childsCount == 1 && orgs.at(0).orgID == 1 && !orgs.at(0).leaf){//root
			QList<QVariant> itemData = formatVariantListFromData(orgs[0]);
			rootItem->appendChild(new TreeItem(itemData,rootItem));
		}
		
		beginResetModel();
		endResetModel();
	}

	void TreeModel::updateModelData( TreeItem*parent,std::vector<data::OrgAndUserInfo>orgs )
	{
		isInit = false;

		if(parent != CNull){
			if(orgs.size()>0){
				for (int i =0;i<orgs.size();++i)
				{
					insertItem(orgs.at(i), parent);
				}
			}else{
				data::OrgAndUserInfo org;
				org.leaf = true;
				org.enName = transfer("该部门下没有成员！").toStdString();
				org.orgName = "";
				QList<QVariant> itemData = formatVariantListFromData(org,false);
				parent->appendChild(new TreeItem(itemData,parent));

				QModelIndex resultIndex = getChildIndex(parent);
				this->beginInsertRows(resultIndex,0,0);
				this->endInsertColumns();
			}

			refreshUiData(parent);

		}
	}

	void TreeModel::insertItem( data::OrgAndUserInfo org, TreeItem* parent ) 
	{
		QList<QVariant> itemData = formatVariantListFromData(org);
		parent->appendChild(new TreeItem(itemData,parent));

		QModelIndex resultIndex = getChildIndex(parent);
		this->beginInsertRows(resultIndex,0,0);
		this->endInsertColumns();
	}

	QModelIndex TreeModel::getChildIndex(TreeItem* item)
	{
		QModelIndex modelIndex;
		if (rootItem != item->parent())
		{
			modelIndex = getChildIndex(item->parent());
		}
		int row = item->row();
		QModelIndex resultIndex = this->index(row, 0, modelIndex);

		return resultIndex;
	}

	bool TreeModel::isTipNode( const QModelIndex &index )
	{
		TreeItem*item = this->item(index);
		QList<QVariant> inData = item->getItemData();
		data::OrgAndUserInfo itemData;
		parceOrgDataFromItem(inData,itemData);
		if(itemData. leaf &&itemData.orgName.empty()){
			return true;
		}
		return false;
	}

	void TreeModel::refreshUiData( TreeItem* parent )
	{
		QModelIndex beginIndex = getChildIndex(parent);
		emit dataChanged(beginIndex,beginIndex);
	}

	void TreeModel::refreshUiData( QModelIndex &index )
	{
		emit dataChanged(index,index);
	}

}