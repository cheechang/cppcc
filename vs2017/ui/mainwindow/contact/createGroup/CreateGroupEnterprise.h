#ifndef CREATEGROUPENTERPRISE_H
#define CREATEGROUPENTERPRISE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QLabel>
#include "../../controls/TWidget.h"
#include "data/entpriseInfo.h"
#include "data/UserData.h"
#include <common/Controlptr.h>
namespace ui{
	class LoadingDataWidget;
	//���Žڵ�
	class DepartmentWidget:public QWidget{
		Q_OBJECT
	public:
		DepartmentWidget(QWidget*parent=CNull);
		~DepartmentWidget();
		void setData(data::OrgAndUserInfo& data);
		data::OrgAndUserInfo getData(){return mData;};
		void hidebranchLogo(bool hide);
	protected:
		QLabel*mName;
		QLabel*branchLogo;
		data::OrgAndUserInfo mData;
	};
	/**
	** ��֯�ܹ�����
	**/
	class CreateGroupEnterprise:public TWidget{
		Q_OBJECT
	public:
		CreateGroupEnterprise(QWidget *parent =CNull);
		~CreateGroupEnterprise();
		void clearList();
		void addItem(QTreeWidgetItem*parent,data::OrgAndUserInfo& data);
		QList<data::UserBasicData> getCheckedItems();
		void reqData();
		void setType(int type,int64 groupId=0);
		void setOriSelMems(QMap<int64,int64> data);
	signals:
		void signalSerGetVisibleOrgUsers(int,std::vector<data::OrgAndUserInfo>);
	protected slots:
	 void onSerGetVisibleOrgUsers(int code,std::vector<data::OrgAndUserInfo>orgs);
	 void onItemClicked(QTreeWidgetItem* item, int col);
	protected:
		void getSelItems(QTreeWidgetItem*parent,QList<data::UserBasicData>&list);//��ȡѡ����
		virtual void paintEvent(QPaintEvent *e);
	protected:
		QTreeWidget*mTreeWidget;
		QTreeWidgetItem* mRootItem;
		IEntMgrControl_Ptr mEent;
		IGroupMgrControl_Ptr mGroupControl;
		bool mhasRootItem;
		QTreeWidgetItem* mCurItem;
		int mType;//1:����Ⱥ��2������Ⱥ��Ա 
		int64 mGroupId;

		LoadingDataWidget* mLoadPage;
		QMap<int64,int64> mOriSelMems;//��¼�Ѿ�ѡ��ĳ�Ա
	};
}
#endif // CREATEGROUPENTERPRISE_H
