#pragma once
#include "Controls/TWidget.h"
#include "Common/ServiceDefine.h"
#include <extModel/extpacket.h>
#include <qtreewidget.h>
class QStackedWidget;
class QVBoxLayout;
namespace ui{
	class DefaultWidget;
	class QrgTreeItem :public QTreeWidgetItem{
	public:
		explicit QrgTreeItem(QTreeWidget *view, int type = Type);
		explicit QrgTreeItem(QTreeWidgetItem *parent, int type = Type);
		virtual  ~QrgTreeItem();
		void			setItemData(model::OrganizationInfo&org);
		model::OrganizationInfo  getItemData() const;
		void           setItemIsMember(bool ismember);
		bool           ItemIsMember()const;
	private:
		model::OrganizationInfo m_data;
		bool   m_ismember;
	};
	class OrgTreeList:public QTreeWidget{
		Q_OBJECT
	public:
		explicit OrgTreeList(QWidget*parent = nullptr);
		virtual  ~OrgTreeList();
		void	  getSelectedMember(QVector<model::EntpriseUserInfo>&members);
		int		  getMemberSize();
		bool      setMemberState(qint64 id, bool ischecked);
	public:
		void addRootOrgItem(model::OrganizationInfo&org);
		void addLoadingItem(QTreeWidgetItem* parent);
		void addNoItem(QTreeWidgetItem* parent);
		void addChildOrgItem(QTreeWidgetItem* parent,model::OrganizationInfo&org);
		void addChildOrgMemItem(QTreeWidgetItem* parent, model::EntpriseUserInfo&member, bool ischeckable=true);
	signals:
		void signalGetChildrenOrgItem(QTreeWidgetItem*,model::OrganizationInfo&);
		void signalChecked(int, qint64, bool);
	public slots:
		void onItemPressed(QTreeWidgetItem *item, int column);
		void onItemDoubleClicked(QTreeWidgetItem *item, int column);
	protected:
		QrgTreeItem* getOrgItem(QTreeWidgetItem* parent, model::OrganizationInfo&org);
		QrgTreeItem* getOrgMemItem(QTreeWidgetItem* parent, model::EntpriseUserInfo&member, bool ischeckable = true);
	private:
		QrgTreeItem* m_item;
		QList<QTreeWidgetItem*> m_memberlist;
	};
	class OrgListWidget :public TWidget{
		Q_OBJECT
	public:
		explicit OrgListWidget(QVector<qint64>&memberlist,QWidget*parent = nullptr);
		virtual  ~OrgListWidget();
		void      getSelectedMember(QVector<model::EntpriseUserInfo>&members);
		void      updateItemState(qint64 id, bool ischecked);
	signals:
		void      signalChecked(int, qint64, bool);
	protected:
		void      getOrgs(qint64 orgid, QTreeWidgetItem*parent = nullptr);
	public slots:
		void  loadData();
		void  onGetNextOrgItem(QTreeWidgetItem*parent,model::OrganizationInfo&org);
	private:
		OrgTreeList*        m_orgList;
		DefaultWidget*      m_loadingWidget;
		QStackedWidget*     m_stackWidget;
		QVBoxLayout*		m_mainLayout;
	private:
		qint64			    m_userid;
		QVector<qint64>     m_filterMemList;
		ILddService_Ptr		m_orgService;
	};
}