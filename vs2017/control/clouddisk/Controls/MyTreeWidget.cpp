#include "MyTreeWidget.h"
#include "NoFocusDelegate.h"
#include "MyTreeWidgetItem.h"
#include <qheaderview.h>
#include <QScrollBar>
namespace ui{
	MyTreeWidget::MyTreeWidget(QWidget*parent) :QTreeWidget(parent){
		this->setColumnCount(1); //设置列数 

		this->setHeaderLabel(tr("构件选择")); //设置头的标题  
		this->setHeaderHidden(true);//隐藏表头
		setItemDelegate(new NoFocusDelegate());

		QPalette p(this->palette());//设置背景色  
		p.setColor(QPalette::Base, QColor(Qt::white));
		this->setPalette(p);
		this->setIconSize(QSize(25,25));
		connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem*, int)));
	}
	MyTreeWidget::~MyTreeWidget(){

	}
	void MyTreeWidget::addRootItem(model::CloudFileInfo&data)
	{
		MyTreeWidgetItem *item = nullptr;
		QString filename("");
		filename = QString::fromUtf8(data.fileName.c_str());
		item = new MyTreeWidgetItem();
		item->setIcon(0, QIcon(":/img/folder"));
		item->setSizeHint(0, QSize(0,30));
		item->setItemData(data);
		item->setText(0,filename);
		item->setExpanded(true);
		this->insertTopLevelItem(0, item);
		emit signalGetNetFolder(item, data);
		m_fileid.push_back(data.fileId);
	}
	void MyTreeWidget::addChildItem(QTreeWidgetItem* parent, model::CloudFileInfo&data){
		MyTreeWidgetItem *item = nullptr;
		QString filename("");

		if (nullptr == parent || m_fileid.contains(data.fileId)) return;
		filename = QString::fromUtf8(data.fileName.c_str());
		item = new MyTreeWidgetItem(parent, QStringList(filename));
		item->setIcon(0, QIcon(":/img/folder"));
		item->setSizeHint(0, QSize(0, 30));
		item->setItemData(data);
		parent->addChild(item);
		parent->setExpanded(true);
		emit signalGetNetFolder(item, data);
		m_fileid.push_back(data.fileId);
	}
}