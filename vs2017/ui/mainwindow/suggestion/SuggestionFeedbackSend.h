#pragma once

#include <QPushbutton>
#include <QLineEdit>
#include <QListWidget>
#include <QDialog>
#include <data/ChatData.h>
#include <data/ContactData.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "common/Controlptr.h"
#include "controls/TWidget.h"
#include "common/Controlptr.h"
#include "interface/Defines.h"
#include "../contact/createGroup/BaseWindow.h"

namespace ui{
	class ChatPage;
	class LocalSearchLineEdit;
	class FriendListWidgetItem;
	class ModifyFriendRemarkWindow;
	class SuggestionFeedbackSendDialog : public BaseWindow
	{
		Q_OBJECT
	public:
		explicit SuggestionFeedbackSendDialog(QWidget *parent = 0);
		virtual ~SuggestionFeedbackSendDialog();

	signals:
		void signalSerGetLocalFriendInfo(int, std::vector<data::ChatInfo>&);
		void startChat(CSharedPtr<data::ChatInfo>&);
	public slots:
		void onEditClear();
		void onSearchFriend(const QString&);
		void onSerGetLocalFriendInfo(int, std::vector<data::ChatInfo>&);
		void onItemDoubleClicked(QListWidgetItem* item);
	public:
		void SuggestionFeedSendInit();
		int addItemToList(const data::Contact& data);
		int SearchAddItemToList(const data::ChatInfo& data);
		void ShowFriendList();
		void ClearFriendList();
	private:
		CSharedPtr<QVBoxLayout> mainLayout;
		//CSharedPtr<QLineEdit> mSearchEdit;
		CSharedPtr<LocalSearchLineEdit> mSearchEdit;
		CSharedPtr<QListWidget> mFriendListWidget;
		
		QMap<int64,data::Contact> mMapData;
		//QMap<int64,data::ChatInfo> mSearchMapData;
		IContactMgrControl_Ptr mContactControl;
	};
}