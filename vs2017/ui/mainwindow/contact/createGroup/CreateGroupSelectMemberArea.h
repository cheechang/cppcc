#ifndef CREATEGROUPSELECTMEMBERAREA_H
#define CREATEGROUPSELECTMEMBERAREA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QPushButton>
#include "../../controls/TWidget.h"
#include "data/UserData.h"
#include "data/ChatData.h"
namespace ui{
	class CreateGroupEnterprise;
	class CreateGroupContacts;
	/**
	** ����Ⱥѡ���Աҳ��
	**/
	class CreateGroupSelectMemberArea:public TWidget{
		Q_OBJECT
	public:
		CreateGroupSelectMemberArea(QWidget *parent =CNull);
		~CreateGroupSelectMemberArea();
		void clearData();
		void reqData(QMap<int64,int64> oriMems);
		void setType(int type=1,int64 groupId=0);
	signals:
		void backClicked();
		void closeWin();
		void selectMemsBack(std::vector<data::UserBasicData>&mems);
		void startChat(CSharedPtr<data::ChatInfo>&chat);
	protected slots:
		void onBtnOKClicked();
		void onTabCurentChanged(int index);
		void onSerHighSerch();
		void onSerHighSerchResult();
		void onStartChat(CSharedPtr<data::ChatInfo>&chat);
	protected:
		QPushButton*mBtnBack;
		QPushButton*mBtnOK;
		QLabel*mLblNavText;

		CreateGroupContacts* mFriend;
		CreateGroupEnterprise*mOrg;
		QTabWidget*mTabWidget;
		int mType;//1:����Ⱥ��2������Ⱥ��Ա 
	};
}
#endif // CREATEGROUPSELECTMEMBERAREA_H
