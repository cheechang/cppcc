#ifndef ENTERPRISEWIDGET_H
#define ENTERPRISEWIDGET_H

#include <QWidget>
#include <QTreeView>

#include <interface/IEntMgrControl.h>
#include <data/entpriseInfo.h>
#include <data/ChatData.h>
#include "common/controlptr.h"
namespace ui{
	class TreeModel;
	class TreeItem;
	class EnterpriseWidget : public QWidget
	{
		Q_OBJECT
	public:
		EnterpriseWidget(QWidget *parent=CNull,CSharedPtr<control::IEntMgrControl>entMgr=CNull);
		~EnterpriseWidget();

		void getVisibleOrgUsers(int64 orgId);
		void _getVisibleOrgUsers(int code,std::vector<data::OrgAndUserInfo>orgs);

	signals:
		void showOrgUserInfor(data::OrgAndUserInfo user);
		void signalSerGetVisibleOrgUsers(int code,std::vector<data::OrgAndUserInfo>orgs);
		void startChat(CSharedPtr<data::ChatInfo>&chat);
	protected slots:
		void onSerGetVisibleOrgUsers(int code,std::vector<data::OrgAndUserInfo>orgs);
		
	protected slots:
		void onClickTreeItem(const QModelIndex &index);
		void onDoubleClickTreeItem(const QModelIndex &index);
	private:
		QTreeView* m_treeView;
		TreeModel* model;
		TreeItem*  m_curGetingDataItem;
		CSharedPtr<control::IEntMgrControl> m_entmgr;
	};
}

#endif // ENTERPRISEWIDGET_H
