#pragma once

#include <QListWidget>
#include <QVBoxLayout>
//#include <QMenu>
//#include <QAction>
#include <data/ContactData.h>
#include <data/ChatData.h>
#include "controls/TWidget.h"
#include "interface/Defines.h"
#include "common/Controlptr.h"
#include <QLabel>

namespace ui{
	class FriendListWidgetItem;
	class EnterpriseAccountList : public TWidget
	{
		Q_OBJECT
	public:
		EnterpriseAccountList(QWidget *parent = CNull);
		~EnterpriseAccountList();

	signals:
		void startChat(CSharedPtr<data::ChatInfo>&);
		void signalSerGetEntAccountCb(int, std::vector<data::EnterpriseAccount>&);

	public slots:
		void onItemDoubleClicked(QListWidgetItem* item);
		void onSerGetEntAccountCb(int code, std::vector<data::EnterpriseAccount>& entAccounts);

	protected:
		void paintEvent(QPaintEvent *event);
	//	void contextMenuEvent(QContextMenuEvent *e);

	private:
		//void initMenu();
		int addItemToList(const data::Contact& data);
		void editItemFromIist(const data::Contact &data);
		void removeItemFromList(const data::Contact &data, bool selectNextItem = true);
		void clearList();
		
		IContactMgrControl_Ptr m_pContactControl;
	

		QListWidget* m_pListWidget;
		QVBoxLayout* m_pMainLayout;
		//QMenu*  m_pMenu;
		//QAction* m_pActionDel;
		QLabel*mlblBg;
		int64 m_curItemId;
	public:
		QMap<int64, data::Contact> m_mapData;
	};
}
