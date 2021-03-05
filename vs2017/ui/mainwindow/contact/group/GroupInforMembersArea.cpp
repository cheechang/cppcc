#include "GroupInforMembersArea.h"
#include<QMessageBox>
#include <QCoreApplication>
#include <thread>
#include<QThread>
#include<QDebug>

#include "RemarkWindow.h"
#include "GroupMemberListItemWidget.h"
#include "createGroup/CreateGroupWindow.h"
#include "controls/UserInfoWindow.h"
#include "controls/UserInfoCommon.h"
#include "controls/UserInfoCommitee.h"
#include "ui/common/ChineseInfos.hpp"
#include "controls/WeMessageBox.h"
#include "common/UIUtils.h"
#include "json.h"

namespace ui
{
	GroupInforMembersArea::GroupInforMembersArea(QWidget *parent)
		: TWidget(parent), m_isLoadDataing(false)
	{
		setObjectName("groupinfobackground");

		mGroupId = 0;
		mListWidget = new uicontrols::BaseQListWidget(this);
		connect(mListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onItemDoubleClicked(QListWidgetItem*)));
		mListWidget->setSelectionMode(QAbstractItemView::NoSelection);
		connect(mListWidget, SIGNAL(signalSrcollToBottom()), this, SLOT(onLazyLoadMember()));

		mListWidget->setObjectName("groupMemberListWidget");
		mListWidget->setFixedHeight(250);
		mainLayout = new QVBoxLayout(this);
		m_pLoadData = new QLabel(this);
		m_pLoadData->setText(transfer("正在加载数据..."));
		m_pLoadData->hide();
		m_pLoadData->setAlignment(Qt::AlignCenter);
		mainLayout->addWidget(m_pLoadData, Qt::AlignHCenter);
		mainLayout->addWidget(mListWidget,Qt::AlignHCenter);

		mainLayout->addStretch();
		setLayout(mainLayout);
		menuWidget();

		m_pUserInfoWidget = new UserInfoWindow(this);
		connect(m_pUserInfoWidget, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
			this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));

		m_chatcontrol = CHATMGRCONTROL;
		m_groupmgrcontrol = GROUPMGRCONTROL;
		if (m_groupmgrcontrol)
		{
			CONNECT_SERVICE(GetMemberList( int , std::vector<CSharedPtr<data::Member>>& ));
			CONNECT_SERVICE(GrpMemRefreshCb(int, int64, std::vector<CSharedPtr<data::Member> >&));
			CONNECT_SERVICE(RemoveMember(int64));
			CONNECT_SERVICE(SetAdminResult(int));
			CONNECT_SERVICE(SetRemarkResult(int));
			CONNECT_SERVICE(TransferGroupResult(int));
			CONNECT_SERVICE(GrpMemInfoRefreshCb(int64 , const data::Member&));
			m_groupmgrcontrol->RegGrpMemRefreshCb(CBind(&GroupInforMembersArea::signalSerGrpMemRefreshCb,
				this,CPlaceholders  _1,CPlaceholders  _2,CPlaceholders  _3));
			m_groupmgrcontrol->RegGrpMemInfoRefreshCb(CBind(&GroupInforMembersArea::signalSerGrpMemInfoRefreshCb,
				this,CPlaceholders  _1,CPlaceholders  _2));
		}

		if (m_chatcontrol)
		{
			CONNECT_SERVICE(GetUserInfo(int, data::UserData&, int64, QString, QString));
		}
	}

	GroupInforMembersArea::~GroupInforMembersArea()
	{
		clearList();
		if(mListWidget != CNull){
			delete mListWidget;
		}
		if(mainLayout != CNull){
			delete mainLayout;
		}
	}

	void GroupInforMembersArea::onLazyLoadMember(){
		if (m_memberpage.isLoadFinished()){
			m_memberpage.clearData();
			return;
		}
		addMember();
	}

	void GroupInforMembersArea::addMember(){
		std::vector<int64>users;
		std::vector<DataPtr>mems;
		m_memberpage.getPageData(mems);
		for (int i = 0; i<mems.size(); ++i){
			DataPtr data = mems.at(i);
			users.push_back(data->id.value());
			addItemToUI(data);
		}
	}

	void GroupInforMembersArea::addItemToUI(DataPtr data)
	{
		data::Group groupInfo;
		m_groupmgrcontrol->GetGroupInfo(mGroupId, groupInfo);

		QListWidgetItem* item = new QListWidgetItem(mListWidget);
		GroupMemberListItemWidget* widget = new GroupMemberListItemWidget(this);
		connect(widget, SIGNAL(clicked()), this, SLOT(onItemClicked()));
		widget->setId(data->id.value());
		QString name = QString::fromUtf8(data->remark.value().c_str());
		if (data->memberType.value() == 3)
		{
			name += transfer("[群主]");
		}
		if (data->memberType.value() == 2)
		{
			name += transfer("[管理员]");
		}
		widget->setData(transfer(data->thumbAvatar.value().c_str()), name);
		int64 memId = data->id.value();
		int64 creatorId = groupInfo.info.value().createrId.value();
		if (memId == creatorId)//群主
		{
			widget->setShowHaremMaster(true, transfer("群主"));
		}
		else
		{
			widget->setShowHaremMaster(false);
		}
		mListWidget->insertItem(mListWidget->count(), item);
		mListWidget->setItemWidget(item, widget);
	}
	void GroupInforMembersArea::onSerGetMemberList( int code , std::vector<CSharedPtr<data::Member> >&mems )
	{
		
		if(mems.size()>0 && mems.at(0)->groupId == mGroupId){
			clearList();
		}
		//设置分页加载参数
		m_memberpage.setPageSize(15);
		m_memberpage.clearData();
		m_memberpage.setData(mems);

		//添加一页
		addMember();
		m_pLoadData->hide();
		mListWidget->show();
		m_isLoadDataing = false;
	}

	void doWork(GroupInforMembersArea*mainObj,int64 groupId)
	{
		if (mainObj) {
			mainObj->getMemberList(groupId);
		}
	}

	void GroupInforMembersArea::getMemberList(int64 groupId) {
		m_groupmgrcontrol->GetMemberList(groupId, CBind(&GroupInforMembersArea::signalSerGetMemberList,
			this, CPlaceholders  _1, CPlaceholders  _2));
	}
	void GroupInforMembersArea::updateData( int64 groupId )
	{
		if (groupId == mGroupId && m_memberpage.getDataCount()>0){
			return;
		}
		mGroupId = groupId;
		if(m_groupmgrcontrol){
			clearList();
			m_pLoadData->show();
			mListWidget->hide();
			if (!m_isLoadDataing) {
				m_isLoadDataing = true;
				std::thread th(doWork,this,groupId);
				th.join();
			}

		}
	}

	void GroupInforMembersArea::clearList()
	{
		for (int i=0;i<mListWidget->count();)
		{
			QListWidgetItem* item = mListWidget->item(i);
			QWidget* widget = mListWidget->itemWidget(item);
			mListWidget->removeItemWidget(item);
			if(item != CNull){
				delete item;
			}
			if(widget != CNull){
				delete widget;
			}
		}
		mListWidget->clear();
	}

	void GroupInforMembersArea::onItemClicked()
	{
		GroupMemberListItemWidget* widget = qobject_cast<GroupMemberListItemWidget*>(QObject::sender());
		
		if(widget != CNull)
		{
			if (m_chatcontrol)
			{
				m_chatcontrol->getUserInfo(widget->id(), 0, std::bind(&GroupInforMembersArea::signalSerGetUserInfo,
					this,std::placeholders::_1,std::placeholders::_2,
					widget->id(), widget->name(), widget->head()));
			}
			
			//m_pUserInfoWidget->show(widget->id(), widget->name(), widget->head());
		}
		else
		{
			m_pUserInfoWidget->show(mCurMemId);
		}
	}

	void GroupInforMembersArea::onSerGetUserInfo(int code, data::UserData& userinfo, int64 id, QString name, QString avatar)
	{
		std::string type("");
		std::string jsonstr = userinfo.entExtends.value();
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(jsonstr, root);
		if (ret)
		{
			if (root.isArray())
			{
				if (root[0]["type"].isString())
				{
					type = root[0]["type"].asString();
				}
			}
		}

		if (type == "1")
		{
			m_pUserInfoCommomWidget = CMakePtr<UserInfoCommon>(this);
			connect(m_pUserInfoCommomWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommomWidget->setInfo(id, name, avatar, userinfo.entExtends.value());
			m_pUserInfoCommomWidget->show();
		}

		if (type == "0")
		{
			m_pUserInfoCommiteeWidget = CMakePtr<UserInfoCommitee>(this);
			connect(m_pUserInfoCommomWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommiteeWidget->setInfo(id, name, avatar, userinfo.entExtends.value());
			m_pUserInfoCommiteeWidget->show();
		}
	}

	void GroupInforMembersArea::onItemDoubleClicked( QListWidgetItem*item )
	{
		GroupMemberListItemWidget* widget = (GroupMemberListItemWidget*)mListWidget->itemWidget(item);
		if(widget){
			CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
			int64 accountID = 0;
			IUserControl_Ptr auth = USERCONTROL;
			if(auth){
				CSharedPtr<data::AccountInfo> account = auth->GetAccountInfo();
				accountID = account->id.value();
				if (accountID == widget->id())
				{
					return;
				}
			}
			chat->chatType = data::STRANGER_CHAT;
			chat->isStartChat = true;
			chat->avatar   = widget->head().toStdString();
			chat->name     =widget->name().toStdString();
			chat->targetid = widget->id();
			emit startChat(chat);
		}
	}

	void GroupInforMembersArea::onInviteGroup()
	{
		/*data::Group groupInfo;
		m_groupmgrcontrol->GetGroupInfo(mGroupId,groupInfo);
		mInviteWin->setTitle(transfer("添加群成员"));
		mInviteWin->showWin(groupInfo.info.value());*/
	}

	void GroupInforMembersArea::hideInviteMemWidget(bool hide)
	{
		/*mBtnInvite->setVisible(!hide);
		mIcon->setVisible(!hide);*/
	}

	void GroupInforMembersArea::onGroupSet( int code, int8 verify_type, int8 is_allow )
	{
		int64 accountID = 0;
		IUserControl_Ptr auth = USERCONTROL;
		if(auth){
			CSharedPtr<data::AccountInfo> account = auth->GetAccountInfo();
			accountID = account->id.value();
		}
		data::Member mem;
		m_groupmgrcontrol->GetMemberInfo(mGroupId,accountID,mem);
		if (is_allow == 2 && mem.memberType == 1)//不允许邀请成员
		{
			hideInviteMemWidget(true);
		}else{
			hideInviteMemWidget(false);
		}
	}

	void GroupInforMembersArea::onSerGrpMemRefreshCb( int type, int64 groupId, std::vector<CSharedPtr<data::Member> >&mems )
	{
		if (groupId == mGroupId)
		{
			data::Group groupInfo;
			m_groupmgrcontrol->GetGroupInfo(mGroupId,groupInfo);
			if (type == 1)//add
			{
				for(int i=0;i<mems.size();++i){
					DataPtr data = mems.at(i);
					QListWidgetItem* item = new QListWidgetItem(mListWidget);
					GroupMemberListItemWidget*widget = new GroupMemberListItemWidget(this);
					connect(widget, SIGNAL(clicked(QPoint)), this, SIGNAL(itemClicked(QPoint)));
					widget->setId(data->id.value());
					widget->setData(transfer(data->thumbAvatar.value().c_str()),QString::fromUtf8(data->remark.value().c_str()));
					int64 memId = data->id.value();
					int64 creatorId = groupInfo.info.value().createrId.value();
					if (memId == creatorId)//群主
					{
						widget->setShowHaremMaster(true,transfer("群主"));
					}else{
						widget->setShowHaremMaster(false);
					}
					mListWidget->insertItem(i,item);
					mListWidget->setItemWidget(item,widget);
					QCoreApplication::processEvents();
				}
			}
			else if(type==31 || type==32){
				updateData(groupId);
			}
		}
	}

	void GroupInforMembersArea::contextMenuEvent( QContextMenuEvent *e )
	{
		QListWidgetItem* item = mListWidget->itemAt(mapFromGlobal(QCursor::pos()));
		if(item != CNull)
		{
			GroupMemberListItemWidget* widget = (GroupMemberListItemWidget*)mListWidget->itemWidget(item);
			if(widget)
			{
				mCurMemId = widget->id();
				refreshMenu();
				mainMenu->exec(QCursor::pos());
			}
		}
	}

	void GroupInforMembersArea::menuWidget()
	{
		mainMenu = new QMenu(this);
		mActionDel = new QAction(this);
		m_ActionAdmin = new QAction(this);
		m_ActionRemark = new QAction(this);
		m_ActionTransfer = new QAction(this);
		mActionDel->setText(transfer("移除群成员"));
		m_ActionAdmin->setText(transfer("设置管理员"));
		m_ActionRemark->setText(transfer("设置群名片"));
		m_ActionTransfer->setText(transfer("转让群"));
		mainMenu->addAction(mActionDel);
		mainMenu->addAction(m_ActionAdmin);
		mainMenu->addAction(m_ActionRemark);
		mainMenu->addAction(m_ActionTransfer);
		connect(mActionDel,SIGNAL(triggered(bool)),this,SLOT(onMenuItemClicked()));
		connect(m_ActionAdmin,SIGNAL(triggered(bool)),this,SLOT(onMenuItemAdminClicked()));
		connect(m_ActionRemark,SIGNAL(triggered(bool)),this,SLOT(onMenuItemRemarkClicked()));
		connect(m_ActionTransfer,SIGNAL(triggered(bool)),this,SLOT(onMenuItemTransferClicked()));
	}

	void GroupInforMembersArea::refreshMenu()
	{
		int64 accountId = 0;
		CSharedPtr<control::IUserControl> userControl = USERCONTROL;
		if(userControl){
			CSharedPtr<data::AccountInfo> account = userControl->GetAccountInfo();
			accountId = account->id.value();
		}

		data::Member self, mem;
		m_groupmgrcontrol->GetMemberInfo(mGroupId, accountId, self);
		m_groupmgrcontrol->GetMemberInfo(mGroupId, mCurMemId, mem);
		
		data::Group groupInfo;
		m_groupmgrcontrol->GetGroupInfo(mGroupId,groupInfo);

		mainMenu->clear();
		if (self.memberType.value() == 3) //自己是群主
		{
			if (mCurMemId == accountId)
			{
				mainMenu->addAction(m_ActionRemark);
			}
			else
			{
				if (mem.memberType.value() != 3 && groupInfo.info.value().type.value() != 2)
				{
					mainMenu->addAction(m_ActionTransfer);
				}
				if (mem.memberType.value() == 2)
				{
					m_ActionAdmin->setText(transfer("取消管理员"));
				}
				else
				{
					m_ActionAdmin->setText(transfer("设置管理员"));
				}
				mainMenu->addAction(mActionDel);
				mainMenu->addAction(m_ActionAdmin);
				mainMenu->addAction(m_ActionRemark);
			}
		}
		else if (self.memberType.value() == 2)	//自己是管理员
		{
			if (mCurMemId == accountId)
			{
				mainMenu->addAction(m_ActionRemark);
			}
			else if (mem.memberType.value() == 1)
			{
				mainMenu->addAction(mActionDel);
			}
		}
		else if (self.memberType.value() == 1)	//自己是群成员
		{
			if (mCurMemId == accountId)
			{
				mainMenu->addAction(m_ActionRemark);
			}
		}
	}

	void GroupInforMembersArea::onMenuItemClicked()
	{/*
		int64 mAccountId = 0;
		CSharedPtr<control::IUserControl> userControl = USERCONTROL;
		if(userControl){
			CSharedPtr<data::AccountInfo> account = userControl->GetAccountInfo();
			mAccountId = account->id.value();
		}
		*/
		data::Member mem;
		m_groupmgrcontrol->GetMemberInfo(mGroupId,mCurMemId,mem);
		if (mem.memberType.value() == 1 && mCurMemId != 0);//普通用户
		{
			m_groupmgrcontrol->RemoveMember(mGroupId,mCurMemId,CBind(&GroupInforMembersArea::signalSerRemoveMember,
				this,CPlaceholders  _1));
			mCurMemId = 0;
		}
	}

	void GroupInforMembersArea::onSerRemoveMember(int64 code)
	{
		if (code == 0)
		{
			//updateData(mGroupId);
		}
		else
		{
			uicontrols::WeMessageBox::showWarning(CNull, PROMPT, transfer("消息置顶成功")+QString::number(code));
		}
	}

	void GroupInforMembersArea::onMenuItemAdminClicked()
	{
		data::Member member;
		m_groupmgrcontrol->GetMemberInfo(mGroupId, mCurMemId, member);
		data::Member mem;
		mem.groupId = mGroupId;
		mem.id = mCurMemId;
		if (member.memberType.value() == 2)
		{
			mem.memberType = 1;
		}
		else if (member.memberType.value() == 1)
		{
			mem.memberType = 2;
		}
		m_groupmgrcontrol->SetMemberInfo(mem, 
			CBind(&GroupInforMembersArea::signalSerSetAdminResult,
			this, CPlaceholders _1));
	}

	void GroupInforMembersArea::onSerSetAdminResult(int code)
	{
		if (code == 0)
		{
			//updateData(mGroupId);
		}
		else
		{
			QMessageBox::warning(this,transfer("提示"), transfer("设置管理员失败：")+QString::number(code));
		}
	}

	void GroupInforMembersArea::onMenuItemRemarkClicked()
	{
		QString remark;
		RemarkWindow remarkWindow;
		int ret = remarkWindow.showWin(remark);
		if (ret == QDialog::Rejected)
		{
			return;
		}
		
		UIUtils::removeSpaceBeforeCharacter(remark);

		data::Member member;
		member.groupId = mGroupId;
		member.id = mCurMemId;
		member.remark = remark.toUtf8().data();
		m_groupmgrcontrol->SetMemberInfo(member, 
			CBind(&GroupInforMembersArea::signalSerSetAdminResult,
			this, CPlaceholders _1));
	}

	void GroupInforMembersArea::onSerSetRemarkResult(int code)
	{
		if (code == 0)
		{
			//updateData(mGroupId);
		}
		else
		{
			QMessageBox::warning(this,transfer("警告"), transfer("设置群名片失败：")+QString::number(code));
		}
	}

	void GroupInforMembersArea::onMenuItemTransferClicked()
	{
		QMessageBox::StandardButton button = QMessageBox::warning(this, transfer("警告"), transfer("您确定要将群转让给该成员？"),
			QMessageBox::Ok | QMessageBox::Cancel);
		if (button == QMessageBox::Ok)
		{
			m_groupmgrcontrol->TransferGroup(mGroupId, mCurMemId,
				CBind(&GroupInforMembersArea::signalSerTransferGroupResult,
					this, CPlaceholders _1));
		}
	}

	void GroupInforMembersArea::onSerTransferGroupResult(int code)
	{
		if (code == 0)
		{
			updateData(mGroupId);
		}
		else
		{
			QMessageBox::warning(this,transfer("提示"), transfer("转让群失败：")+QString::number(code));
		}
	}

	void GroupInforMembersArea::onSerGrpMemInfoRefreshCb( int64 groupId, const data::Member&memberInfo )
	{
		QString remark("");
		int memType = 0;

		if (memberInfo.remark.isSet())
		{
			remark = QString::fromUtf8(memberInfo.remark.value().c_str());
		}
		if (memberInfo.memberType.isSet())
		{
			memType = memberInfo.memberType.value();
		}
		if (groupId == mGroupId)
		{
			updateData(groupId);
		}
	}

}
