#ifndef GROUPINFORSETTINGAREA_H
#define GROUPINFORSETTINGAREA_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include "controls/TWidget.h"
#include "interface/Defines.h"
#include "common/Controlptr.h"
#include <data/GroupData.h>
namespace ui{
	class GroupInforSettingArea : public TWidget
	{
		Q_OBJECT
		enum{
			ANY_CAN_ADD_GROUP,
			NEED_CONFIRM_ADD_GROUP,
			ALL_CAN_NOT_ADD_GROUP
		};
	public:
		GroupInforSettingArea(QWidget *parent=CNull);
		~GroupInforSettingArea();

		void updateData(int64 groupId);
		void GetOldSetInfo(data::Group&);
	signals:
		void signalSerGetGroupSet(int ,int8,int8);
		void signalSerGetMemberList(int, std::vector<CSharedPtr<data::Member> >&);
		void signalSerCallBack(int);
		void signalGroupSet(int code, int8 verify_type, int8 is_allow);
		void signalGroupRefreshSecret(int8, const data::Group&);
		void signalGroupRefresh(int8, const data::Group&);
		void signalSerGetGroupMem(int code, data::Member& mem);
	public slots:
		void onSerGetGroupSet(int code ,int8 verify_type,int8 is_allow);
		void onSerGetMemberList(int code , std::vector<CSharedPtr<data::Member> >&mems);
		void onSerCallBack(int code);
		void onSerGetGroupMem(int code, data::Member& mem);

		void onAddWayGroupClicked(int type);
		void onSearchStateChanged();
		void onInviteStateChanged();
		void onSaveGroupNameClicked();
		void onSerSecretCheck(bool);
	private:
		void setControlUIEnable(bool isEnable);

		QList<CSharedPtr<QRadioButton>> m_addGroupWays;
		CSharedPtr<QButtonGroup> m_addGroupWaysGroup;
		CSharedPtr<QVBoxLayout>  m_mainLayout;
		CSharedPtr<QGridLayout>  m_addGroupWayLayout;
		CSharedPtr<QLabel>			m_lblAddGroupWay;

		CSharedPtr<QCheckBox>   m_checkInvited;
		CSharedPtr<QCheckBox>   m_checkSearched;
		CSharedPtr<QGridLayout> m_checkLayout;
		CSharedPtr<QLabel>		 m_lblDisturb;

		CSharedPtr<QLineEdit>    m_editName;
		CSharedPtr<QLabel>		  m_lblEditName;
		CSharedPtr<QPushButton> m_editNameSave;
		CSharedPtr<QHBoxLayout>   m_editNameLayout;

		/*CSharedPtr<QLabel>	m_SecretChatName;
		CSharedPtr<QCheckBox> m_checkSecretChat;
		CSharedPtr<QHBoxLayout> m_SecretChatLayout;*/

		IGroupMgrControl_Ptr m_groupmgrcontrol;
		QString mGroupName;
		int64 mAccountId,mGroupId;
	};
}

#endif // GROUPINFORSETTINGAREA_H
