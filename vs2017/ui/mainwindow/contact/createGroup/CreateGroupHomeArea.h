#ifndef CREATEGROUPHOMEAREA_H
#define CREATEGROUPHOMEAREA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include "../../controls/TWidget.h"
#include "data/UserData.h"
#include <common/Controlptr.h>
#include "data/ChatData.h"
#include "../searchcontact/AddContactWindow.h"
namespace ui{
	class HeadImage;
	class ToolButton;
	class CreateGroupContacts;
	/**
	** 创建群首页，填写群名称，秘级页面
	**/
	class CreateGroupHomeArea:public TWidget{
		Q_OBJECT
	public:
		CreateGroupHomeArea(QWidget *parent =CNull);
		~CreateGroupHomeArea();
		void hideDesWidget(bool hide);
		void resetMemsData(std::vector<data::UserBasicData>& mems);
		void clearData();
		void setType(QString groupName,int type=1,int64 groupId=0);
	signals:
		void addGroupClicked(QMap<int64,int64>);
		void signalSerCreateGroup(int,int64);
		void signalSerInviteMember(int);
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		void closeWin();
		void signalSerGroupSet(int code);
	protected slots:
		void onLevelChanged(int index);
		void onBtnCreateGroup();
		void onBtnAddFriendClicked();
		void onSerCreateGroup(int code,int64 groupId);
		void onSerInviteMember(int code);
		void onSerGroupSet(int code);
		void onAddGroupClicked();
	protected:
		void paintEvent(QPaintEvent *e);
		void createGroup();
		void inviteGroupMem();
	protected:
		QLineEdit* mName;

		CreateGroupContacts* mMems;
		QPushButton* mBtnSendReq;
		QPushButton* mBtnAddFridenReq;
		ToolButton* mBtnAddMems;
		IGroupMgrControl_Ptr mGroupControl;
		int mType;
		int64 mGroupId;
		QLabel*mLblTip;
		AddContactWindow* m_addContactWin;
	};
}
#endif // CREATEGROUPHOMEAREA_H
