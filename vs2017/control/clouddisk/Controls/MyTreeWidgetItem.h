#pragma once
#include <QTreeWidgetItem>
#include <model/Packet.h>
class QTreeWidget;
namespace ui{
	class MyTreeWidgetItem :public QTreeWidgetItem{
	public:
		explicit MyTreeWidgetItem(int type = Type);
		explicit MyTreeWidgetItem(QTreeWidget *view, const QStringList &strings, int type = Type);
		explicit MyTreeWidgetItem(QTreeWidgetItem *parent, const QStringList &strings, int type = Type);
		virtual ~MyTreeWidgetItem();
	public:
		void setItemData(model::CloudFileInfo&info);
		model::CloudFileInfo getItemData()const;
	private:
		model::CloudFileInfo m_data;
	};
}