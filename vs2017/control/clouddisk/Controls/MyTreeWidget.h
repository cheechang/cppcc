#pragma once
#include <qtreewidget.h>
#include <model/Packet.h>
namespace ui{
	class MyTreeWidgetItem;
	class MyTreeWidget:public QTreeWidget{
		Q_OBJECT
	public:
		explicit MyTreeWidget(QWidget*parent = nullptr);
		virtual ~MyTreeWidget();
		void addRootItem(model::CloudFileInfo&data);
		void addChildItem(QTreeWidgetItem* parent, model::CloudFileInfo&data);
	signals:
		void signalGetNetFolder(QTreeWidgetItem*,model::CloudFileInfo&);
	private:
		QList<qint64> m_fileid;
	};
}