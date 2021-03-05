#include "MyTreeWidgetItem.h"
namespace ui {
	MyTreeWidgetItem::MyTreeWidgetItem(int type):QTreeWidgetItem(type){

	}
	MyTreeWidgetItem::MyTreeWidgetItem(QTreeWidget *view, const QStringList &strings, int type) :QTreeWidgetItem(view, strings,type){

	}
	MyTreeWidgetItem::MyTreeWidgetItem(QTreeWidgetItem *parent, const QStringList &strings, int type) : QTreeWidgetItem(parent, strings, type){

	}
	MyTreeWidgetItem::~MyTreeWidgetItem(){

	}
	void MyTreeWidgetItem::setItemData(model::CloudFileInfo&info){
		m_data = info;
	}
	model::CloudFileInfo MyTreeWidgetItem::getItemData()const{
		return m_data;
	}
}

