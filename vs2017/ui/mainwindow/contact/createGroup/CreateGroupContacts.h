#ifndef CREATEGROUPCONTACTS_H
#define CREATEGROUPCONTACTS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include "../../controls/TWidget.h"
#include "data/UserData.h"
#include "common/Controlptr.h"
namespace ui{
	/**
	** 好友显示界面
	**/
	class UserInfoCommon;
	class UserInfoCommitee;
	class LocalSearchLineEdit;
	class CreateGroupContacts:public TWidget{
		Q_OBJECT
	public:
		CreateGroupContacts(QWidget *parent =CNull,bool hasSearchBox=false);
		~CreateGroupContacts();

		void setData(std::vector<data::UserBasicData>&datas);
		void setDataAndCanDel(std::vector<data::UserBasicData>&datas);
		void addItem(data::UserBasicData data,bool canDel = false);
		void setOriSelMems(QMap<int64,int64> data);
		QMap<int64,int64> oriSelMems(){return mMapSelMems;}
		void clearList();
		QList<data::UserBasicData> getCheckedItems();
		QList<data::UserBasicData> getAllItems();
		bool isExist(int64 id);
		void reqData();
		void setType(int type,int64 groupId=0);
		void setListWidgetFixedHeight(int height);
		void initData();
		void SwitchPage();
		void contextMenuEvent(QContextMenuEvent *ev);
		void setHighSearch(){onSerHighSearch(); }
	protected slots:
		void onDeleteItem(QString id);
		void onClearBtnClicked();
		void onTextChanged(const QString &text);

		void onSerHighSearch();
		void onSerHighSerchClicked();
		void onSerCancelBtnClicked();
		void onSerAllSelClicked();

		void onSerZxSerchResult(int code, int32 page, std::vector<data::UserBasicData>& userdata);
		void onSerSendMessage();

		void onSerShowUserInfo(int64, QString, QString, std::string);

		void onStartChat(CSharedPtr<data::ChatInfo>&);
	signals:
		void signalSerZxSerchResult(int code, int32 page, std::vector<data::UserBasicData>& userdata);
		void signalSerSendMsg(int64);
		void signalSerHighSerch();
		void signalSerHighSerchResult();
		void StartChat(CSharedPtr<data::ChatInfo>&);
		void signalZxSerchResult(std::vector<data::ChatInfo>);
	protected:
		CSharedPtr<UserInfoCommon> m_pUserInfoCommomWidget;
		CSharedPtr<UserInfoCommitee> m_pUserInfoCommiteeWidget;

		QListWidget*mListWidget;
		QWidget* mFridListWidget;
		QStackedWidget* m_Highstackwidget;
		QWidget* m_highwidget;
		QVBoxLayout* m_HighLayout;
		//高级搜索
		QLabel *m_highNamelbel;
		QLabel *m_highSexlbel;
		QLabel *m_highMzlbel;
		QLabel *m_highadresslbel;
		QLabel *m_highjoblbel;
		QLabel *m_highcircleslbel;
		QLabel *m_highgrouplbel;
		QLabel *m_highSpecialComlbel;
		QLabel *m_highzxzwlbel;
		QLabel *m_highzwhzwlbel;


		QLineEdit *m_highNameEdit;
		QComboBox *m_highSexCom;
		QComboBox *m_highMzCom;
		QComboBox *m_highAdressCom;
		QLineEdit *m_highJobEdit;
		QComboBox *m_highJbCom;
		QLineEdit *m_highGroupEdit;
		QComboBox *m_highZwhCom;
		QComboBox *m_highZxzwCom;
		QComboBox *m_highZwhzwCom;

		QHBoxLayout* Layout1;
		QHBoxLayout* Layout2; 
		QHBoxLayout* Layout3; 
		QHBoxLayout* Layout4; 
		QHBoxLayout* Layout5; 
		QHBoxLayout* Layout6; 
		QHBoxLayout* Layout7; 
		QHBoxLayout* Layout8; 
		QHBoxLayout* Layout9; 
		QHBoxLayout* Layout10;

		IContactMgrControl_Ptr mContactControl;
		IGroupMgrControl_Ptr mGroupControl;
		IUserControl_Ptr muserserviceControl;
		int mType;//1:创建群；2：邀请群成员 
		int64 mGroupId;
		LocalSearchLineEdit* mSearchBox;
		QPushButton* HighSerch;

		QPushButton* okBtn;
		QPushButton* cancelBtn;
		QHBoxLayout* m_BtnLayout;

		QPushButton* m_AllSelectBtn;

		QMap<int64,int64> mMapSelMems;
		QMap<int64,int64> mOriSelMems;//记录已经选择的成员

		CSharedPtr<QMenu> popMenu;
		std::shared_ptr<QAction> m_sendmsg;
	};
}
#endif // CREATEGROUPCONTACTS_H
