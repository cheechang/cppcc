#pragma once

#include "controls/TWidget.h"
#include <data/ContactData.h>
#include <data/ChatData.h>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QListWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include "interface/Defines.h"
#include "common/Controlptr.h"
namespace ui{
	class SearchResultListWidgetItem;
	class SearchResultListWidget : public TWidget
	{
		Q_OBJECT
	public:
		SearchResultListWidget(QWidget *parent=CNull);
		~SearchResultListWidget();
		void searchKey(QString strKey);
		void clearList();
	signals:
		void signalSerSearchFromNet(int err, std::vector<data::SearchResultInfo>& result);
		void signalAddContact(const data::SearchResultInfo data);
		void signalSerAddAppContact(int err);
	public slots:
		void onSerSearchFromNet(int err, std::vector<data::SearchResultInfo>& result);
		void onAddContactBtnClicked(int64 targetId, void* itemWidget);
		void onSerAddAppContact(int err);
	private:
		int addItemToList(const data::SearchResultInfo& data);
		
		QMap<int64,data::SearchResultInfo> mMapData;

		QListWidget* mListWidget;
		QLabel*  m_totalCountLbl;

		QVBoxLayout*mainLayout;
		IContactMgrControl_Ptr mContactControl;
	};
}