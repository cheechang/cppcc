#include "CreateGroupEnterprise.h"
#include <QLabel>
#include "SelectMemberItemWidget.h"
#include "LoadingDataWidget.h"
#include <common/Connect.h>
#include "../../../common/Common.h"
namespace ui{
	void CreateGroupEnterprise::clearList()
	{
		mTreeWidget->clear();
		mRootItem = CNull;
		mhasRootItem = false;
		mCurItem = CNull;
	}

	CreateGroupEnterprise::CreateGroupEnterprise( QWidget *parent /*=CNull*/ )
		:TWidget(parent)
	{
		setObjectName("bg_fa");
		mTreeWidget = new QTreeWidget(this);
		mTreeWidget->setObjectName("bg_fa");
		mTreeWidget->setHeaderHidden(true);
		mTreeWidget->setFixedHeight(420);
		mTreeWidget->setFocusPolicy(Qt::NoFocus);
		connect(mTreeWidget,SIGNAL(itemClicked(QTreeWidgetItem* ,int)), this, SLOT(onItemClicked(QTreeWidgetItem* ,int)));
		mCurItem = CNull;
		mType = 1;
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->setContentsMargins(0,0,0,10);
		layout->addWidget(mTreeWidget);
		layout->addStretch();
		setLayout(layout);
		mhasRootItem = false;

		mLoadPage =new LoadingDataWidget(this);
		mLoadPage->hide();
		mLoadPage->setTipText(transfer("正在更新数据..."));
		mGroupControl = GROUPMGRCONTROL;
		mEent = ENTMGRCONTROL;
		CONNECT_SERVICE(GetVisibleOrgUsers(int ,std::vector<data::OrgAndUserInfo>));
	}

	CreateGroupEnterprise::~CreateGroupEnterprise()
	{

	}

	void CreateGroupEnterprise::addItem( QTreeWidgetItem*parent,data::OrgAndUserInfo& data )
	{
		if (parent == CNull)
		{
			mRootItem = new QTreeWidgetItem(mTreeWidget);
			DepartmentWidget* widget = new DepartmentWidget(this);
			widget->setData(data);
			widget->setFixedHeight(30);
			mTreeWidget->setItemWidget(mRootItem,0,widget);
			mRootItem->setData(0, Qt::UserRole, 0);//0：部门,1:成员
			mTreeWidget->addTopLevelItem(mRootItem);
			return;
		}

		//获取账户信息
		IUserControl_Ptr auth = USERCONTROL;
		if(auth){
			CSharedPtr<data::AccountInfo> account = auth->GetAccountInfo();
			if(account->id.value() == data.userID){
				return;
			}
		}
		QTreeWidgetItem* item = new QTreeWidgetItem(parent);
		parent->addChild(item);
		if(data.leaf){
			SelectMemberItemWidget* widget = new SelectMemberItemWidget(this);
			data::UserBasicData org;
			org.id = data.userID;
			org.name = QString::fromUtf8(data.enName.c_str()).toStdString();
			org.thumbAvatar = QString::fromUtf8(data.head.c_str()).toStdString();
			if ( data.userID == -1)
			{
				org.name = transfer("此部门下没有可选的成员！").toStdString();
				widget->showNameOnly();
			}
			widget->setData(org);
			widget->setFixedHeight(45);
			if ( mType == 2 && mGroupControl!=CNull)
			{
				bool ret = mGroupControl->IsInGroup(mGroupId,data.userID);
				if (ret)
				{
					widget->setCheckboxEnabled(false,true);
				}
			}
			if ( mOriSelMems.contains(data.userID))
			{
				widget->setCheckboxEnabled(false,true);
			}
			mTreeWidget->setItemWidget(item,0,widget);
			item->setData(0, Qt::UserRole, 1);//0：部门,1:成员

		}else{
			DepartmentWidget* widget = new DepartmentWidget(this);
			widget->setData(data);
			widget->setFixedHeight(30);
			mTreeWidget->setItemWidget(item,0,widget);
			item->setData(0, Qt::UserRole, 0);//0：部门,1:成员
		}
	}

	void CreateGroupEnterprise::getSelItems(QTreeWidgetItem*parent, QList<data::UserBasicData>&list )
	{
		//递归获取选中项
		if (parent == CNull)
		{
			return;
		}
		int type = parent->data(0, Qt::UserRole).toInt();
		if (type == 1)//叶子节点
		{
			SelectMemberItemWidget* widget = static_cast<SelectMemberItemWidget*>(mTreeWidget->itemWidget(parent,0));
			if(widget != CNull && widget->isSelect()){
				list.append(widget->data());
			}
		}else{//部门节点
			for (int i=0;i<parent->childCount();++i)
			{
				QTreeWidgetItem* item = parent->child(i);
				getSelItems(item,list);
			}
		}
	}

	QList<data::UserBasicData> CreateGroupEnterprise::getCheckedItems()
	{
		QList<data::UserBasicData> datas;
		getSelItems(mRootItem,datas);
		return datas;
	}


	DepartmentWidget::DepartmentWidget(QWidget*parent):QWidget(parent)
	{
		mName = new QLabel(this);
		branchLogo = new QLabel(this);
		branchLogo->setPixmap(QPixmap(":/contact/branchClose"));
		branchLogo->setFixedSize(4,9);
		QHBoxLayout*layout = new QHBoxLayout(this);
		layout->setContentsMargins(0,0,0,0);
		layout->addWidget(branchLogo);
		layout->addWidget(mName);
		layout->addStretch();
		setLayout(layout);
	}

	DepartmentWidget::~DepartmentWidget()
	{

	}

	void DepartmentWidget::setData( data::OrgAndUserInfo& data )
	{
		mName->setText(QString::fromUtf8(data.orgName.c_str()));
		mData = data;
	}

	void DepartmentWidget::hidebranchLogo( bool hide )
	{
		branchLogo->setVisible(!hide);
	}

	void CreateGroupEnterprise::reqData()
	{
		if (mhasRootItem)
		{
			return;
		}
		mhasRootItem = true;
		mEent->getVisibleOrgUsers(0,CBind(&CreateGroupEnterprise::signalSerGetVisibleOrgUsers,this,CPlaceholders  _1,
			CPlaceholders  _2));
		mLoadPage->raise();
		mLoadPage->show();
	}

	void CreateGroupEnterprise::onSerGetVisibleOrgUsers( int code,std::vector<data::OrgAndUserInfo>orgs)
	{
		mLoadPage->hide();
		if (!mhasRootItem)//根节点
		{
			addItem(CNull,orgs.at(0));
		}else{
			for (int i=0;i<orgs.size();++i)
			{
				addItem(mCurItem,orgs.at(i));
			}
			if(orgs.size() == 0){
				data::OrgAndUserInfo data;
				data.userID = -1;
				data.leaf = true;
				addItem(mCurItem,data);
			}
			//隐藏图标
			DepartmentWidget* widget = static_cast<DepartmentWidget*>(mTreeWidget->itemWidget(mCurItem,0));
			if(widget){
				widget->hidebranchLogo(true);
			}
			mTreeWidget->expandItem(mCurItem);
		}
		mCurItem = CNull;
	}

	void CreateGroupEnterprise::onItemClicked( QTreeWidgetItem* item, int col )
	{
		int type = item->data(0, Qt::UserRole).toInt();
		if (type != 1 && item->childCount()<=0)//部门
		{
			DepartmentWidget* widget = static_cast<DepartmentWidget*>(mTreeWidget->itemWidget(item,0));
			if(widget != CNull){
				int64 orgId = widget->getData().orgID;
				mCurItem = item;
				mEent->getVisibleOrgUsers(orgId,CBind(&CreateGroupEnterprise::signalSerGetVisibleOrgUsers,this,CPlaceholders  _1,
					CPlaceholders  _2));
			}
		}
	}

	void CreateGroupEnterprise::setType( int type,int64 groupId )
	{
		mType = type;
		mGroupId = groupId;
	}

	void CreateGroupEnterprise::paintEvent( QPaintEvent *e )
	{
		if (mLoadPage != CNull)
		{
			mLoadPage->setFixedSize(size());
		}
	}

	void CreateGroupEnterprise::setOriSelMems( QMap<int64,int64> data )
	{
		mOriSelMems = data;
	}

}