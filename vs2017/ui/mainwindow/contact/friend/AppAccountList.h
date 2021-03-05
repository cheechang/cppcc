#pragma once

#include <QListWidget>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <data/ContactData.h>
#include <data/ChatData.h>
#include "controls/TWidget.h"
#include "interface/Defines.h"
#include "common/Controlptr.h"
#include <QLabel>

namespace ui{
	class FriendListWidgetItem;
	class AppAccountList : public TWidget
	{
		Q_OBJECT
	public:
		AppAccountList(QWidget *parent = CNull);
		~AppAccountList();

	signals:
		void startChat(CSharedPtr<data::ChatInfo>&);
		//void signalSerGetEntAccountCb(int, std::vector<data::EnterpriseAccount>&);
		void signalSerRemoveAppCB(int);

	public slots:
		void onItemDoubleClicked(QListWidgetItem* item);
		void onDeleteMenuItemClicked();
		//void onSerGetEntAccountCb(int code, std::vector<data::EnterpriseAccount>& entAccounts);
		void onSerRemoveAppCB(int code);

	protected:
		void contextMenuEvent(QContextMenuEvent *e);
		void paintEvent(QPaintEvent *event);
	private:
		void initMenu();
		int addItemToList(const data::Contact& data);
		void editItemFromIist(const data::Contact &data);
		void removeItemFromList(const data::Contact &data, bool selectNextItem = true);
		void clearList();
		
		IContactMgrControl_Ptr m_pContactControl;
		QMap<int64, data::Contact> m_mapData;

		QListWidget* m_pListWidget;
		QVBoxLayout* m_pMainLayout;
		QMenu*  m_pMenu;
		QAction* m_pActionDel;
		QLabel*mlblBg;

		int64 m_curItemId;
	};
}
