#ifndef APPMENUBUTTON_H
#define APPMENUBUTTON_H
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QHBoxLayout>
#include "../../controls/TWidget.h"
#include "data/ChatData.h"
namespace ui{
	class AppMenu : public QWidget{
		Q_OBJECT
	public:
		AppMenu(QWidget*parent,data::AppMenuData data);
		~AppMenu();
		QMenu* menu(){return mMenu;}; 
		void setMenu(QMenu* menu){mMenu = menu;};
	signals:
		void openUrl(std::string url);
	protected slots:
		void onClicked();
	private:
		data::AppMenuData mData;
		QAction*mAction;
		QMenu* mMenu;
	};
	class AppMenuButton : public QPushButton
	{
		Q_OBJECT
	public:
		AppMenuButton(QWidget *parent=CNull);
		~AppMenuButton();
		void setData(data::AppMenuData&data);
	signals:
		void openUrl(std::string url);
	protected slots:
		void onClicked();
	protected:
		//virtual void contextMenuEvent(QContextMenuEvent *event);
	private:
		void makeSubMenus(QWidget*parent,data::AppMenuData data);
		QLabel*mIcon;
		QLabel*mTitle;
		data::AppMenuData mData;
		QHBoxLayout* mLayout;
		QMenu* mMenu;
	};
}

#endif // APPMENUBUTTON_H
