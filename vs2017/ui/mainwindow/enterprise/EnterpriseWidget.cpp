#include "EnterpriseWidget.h"
#include "TreeViewItemDelegate.h"
#include "treeviewmodel.h"
#include "common/controlptr.h"
#include <QHBoxLayout>

namespace ui{
	EnterpriseWidget::EnterpriseWidget(QWidget *parent,CSharedPtr<control::IEntMgrControl>entMgr)
		: QWidget(parent)
	{
		qRegisterMetaType<data::OrgAndUserInfo > ("data::OrgAndUserInfo");
		qRegisterMetaType<std::vector<data::OrgAndUserInfo> > ("std::vector<data::OrgAndUserInfo>");

		CONNECT_SERVICE(GetVisibleOrgUsers(int ,std::vector<data::OrgAndUserInfo>));
		

		m_curGetingDataItem = CNull;

		m_treeView = new QTreeView(this);
		ui::TreeViewItemDelegate *delegate = new ui::TreeViewItemDelegate(CNull);
		model = new ui::TreeModel(this);

		m_treeView->setHeaderHidden(true);
		m_treeView->setAnimated(true);
		m_treeView->setMouseTracking(true);
		m_treeView->setExpandsOnDoubleClick(true);
		m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
		m_treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		connect(m_treeView,SIGNAL(clicked(const QModelIndex &)),this,SLOT(onClickTreeItem(const QModelIndex &)));
		//connect(m_treeView,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(onDoubleClickTreeItem(const QModelIndex &)));

		m_treeView->setModel(model);
		delegate->setView(m_treeView);
		m_treeView->setItemDelegate(delegate);
	
		setObjectName("bg_fa");
		m_treeView->setObjectName("bg_fa");

		QHBoxLayout *centerLayout = new QHBoxLayout(this);
		centerLayout->addWidget(m_treeView);
		centerLayout->setSpacing(0);
		centerLayout->setContentsMargins(0, 0, 0, 0);
		setLayout(centerLayout);
		
		if(entMgr != CNull){
			m_entmgr = entMgr;
		}else{
			m_entmgr = ENTMGRCONTROL;
			getVisibleOrgUsers(0);
		}

	}

	EnterpriseWidget::~EnterpriseWidget()
	{

	}

	void EnterpriseWidget::onSerGetVisibleOrgUsers( int code,std::vector<data::OrgAndUserInfo>orgs )
	{   
		if(code == 0){
			if(m_curGetingDataItem != CNull){
				model->updateModelData(m_curGetingDataItem,orgs);
				QModelIndex index = model->getChildIndex(m_curGetingDataItem);
				if(!m_treeView->isExpanded(index)){
					m_treeView->expand(index);
				}
				m_curGetingDataItem = CNull;
				
			}else{
				model->updateModelData(orgs);
			}
		}
	}

	void EnterpriseWidget::onClickTreeItem( const QModelIndex &index )
	{
		if(!model->isTipNode(index)){
			TreeItem*item = model->item(index);
			QList<QVariant> inData = item->getItemData();
			data::OrgAndUserInfo itemData;
			model->parceOrgDataFromItem(inData,itemData);
			if(itemData.leaf){
				emit showOrgUserInfor(itemData);
			}else{
				onDoubleClickTreeItem(index);
			}
		}
	}

	void EnterpriseWidget::onDoubleClickTreeItem( const QModelIndex &index )
	{
		TreeItem*item = model->item(index);
		if(!model->hasChildren(index)){
			if(item != CNull){
				QList<QVariant> inData = item->getItemData();
				data::OrgAndUserInfo itemData;
				model->parceOrgDataFromItem(inData,itemData);
				m_curGetingDataItem = item;
				if(!itemData.leaf){
					getVisibleOrgUsers(itemData.orgID);
				}else{
					CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
					chat->chatType = data::ENT_USER_CHAT;
					chat->isStartChat = true;
					chat->avatar   =itemData.head;
					chat->name     = itemData.enName;
					chat->targetid = itemData.userID;
					emit startChat(chat);
				}
			}
		}else{
			if(m_treeView->isExpanded(index)){
				m_treeView->collapse(index);
			}else{
				m_treeView->expand(index);
			}
			
		}
		m_treeView->update();
	}

	void EnterpriseWidget::getVisibleOrgUsers(int64 orgId){
		m_entmgr->getVisibleOrgUsers(orgId,CBind(&EnterpriseWidget::_getVisibleOrgUsers,this,
			CPlaceholders  _1,CPlaceholders  _2));
	}

	void EnterpriseWidget::_getVisibleOrgUsers( int code,std::vector<data::OrgAndUserInfo>orgs )
	{
		emit signalSerGetVisibleOrgUsers(code,orgs);
	}
}
