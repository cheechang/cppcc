#pragma once
#include "Controls/TWidget.h"
#include "Common/ServiceDefine.h"
#include <qlistwidget.h>
#include <iostream>
#include <qsharedpointer.h>

class QCheckBox;
class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QStackedWidget;
namespace ui{
	class HeadImage;
	class ElidedLabel;
	class DefaultWidget;
	class ChangePermissionWindow;
	class AuthMemListItem :public QWidget{
		Q_OBJECT
	public:
		explicit AuthMemListItem(QString&head, QString&name, QWidget*parent = nullptr);
		virtual  ~AuthMemListItem();
		void			setItemData(model::TeamMemberInfo&);
		model::TeamMemberInfo  getItemData() const;
		void			setUserData(model::EntpriseUserInfo&user);
		model::EntpriseUserInfo getUserData()const;
	public slots:
		void onChangePermissionClick();
		void onDeleteMembersClick();
		void onSerRolesResult(service::ErrorInfo, std::vector<model::CloudRoleInfo>&);
		void onChangePerm(int);
	signals:
		void signalChangePermission();
		void signalDeleteMembers();
		void signalSerRolesResult(service::ErrorInfo, std::vector<model::CloudRoleInfo>&);
		void signalDeleteMems(model::TeamMemberInfo);
		void signalChangeMems(model::TeamMemberInfo);
	private:
		model::EntpriseUserInfo m_userdata;
		model::TeamMemberInfo  m_contact;
		HeadImage*	 m_head;
		ElidedLabel* m_name;
		QLabel*      m_spliter;
		QPushButton* m_changePermission;
		QPushButton* m_deleteMembers;
		QHBoxLayout* m_mainLayout;
		QVBoxLayout* m_contentLayout;
		ICloudService_Ptr m_cloud;
		std::shared_ptr<ChangePermissionWindow> m_permission;
	};
	class AuthMemList :public QListWidget{
		Q_OBJECT
	public:
		explicit AuthMemList(QListWidget *parent = nullptr);
		virtual  ~AuthMemList();
		void addItem(model::TeamMemberInfo&contact);
		void addItem(QString);
	public slots:
	signals :
		void signalDeleteMems(model::TeamMemberInfo);
		void signalChangeMems(model::TeamMemberInfo);
	private:
		ISearchService_Ptr m_search;
		IUserService_Ptr m_user;
		model::Account m_account;
	};
	class AuthMemListWidget :public TWidget{
		Q_OBJECT
	public:
		explicit AuthMemListWidget(model::CloudFileInfo&info,QWidget*parent = nullptr);
		virtual  ~AuthMemListWidget();
		void updateData();
		QVector<qint64> getMemberList();
	public slots:
		void loadData();
		void onSerRolesResult(service::ErrorInfo, std::vector<model::CloudRoleInfo>&);
		void onSerTeamMembers(service::ErrorInfo, std::vector<model::TeamMemberInfo>&);
		void onAuthMembers(std::vector<model::TeamMemberInfo>&);
		void onDeleteMems(model::TeamMemberInfo);
		void onChangeMems(model::TeamMemberInfo);
		void onSerResetMember(service::ErrorInfo);
		void onConfirm();
	protected:
		void showTipMessageBox(int code);
	signals:
		void signalSerRolesResult(service::ErrorInfo, std::vector<model::CloudRoleInfo>&);
		void signalSerTeamMembers(service::ErrorInfo, std::vector<model::TeamMemberInfo>&);
		void signalSerResetMember(service::ErrorInfo);
		void signalClose();
	private:
		AuthMemList*        m_contactList;
		DefaultWidget*      m_loadingWidget;
		DefaultWidget*		m_defaultAuthmem;
		QStackedWidget*     m_stackWidget;
		QVBoxLayout*		m_mainLayout;
	private:
		QVector<qint64>     m_memberlist;
		IContactService_Ptr m_contact;
		ICloudService_Ptr m_cloud;	
		IUserService_Ptr m_user;
		QMap<int, std::vector<model::TeamMemberInfo>> m_group;
	private:
		model::CloudFileInfo m_info;
		std::vector<model::CloudRoleInfo>  m_roles;
		std::vector<model::TeamMemberInfo> m_members;
		model::Account m_account;
		int m_isChange;
	};
}