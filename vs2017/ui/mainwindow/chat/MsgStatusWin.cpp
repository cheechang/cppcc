#include "MsgStatusWin.h"
#include "bubble/abstractmessagewidget.h"
#include "ChatPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QListWidget>

#include <controls/Button.h>
#include <controls/WeMessageBox.h>
#include <common/Connect.h>
#include <mainwindow/contact/group/GroupListItemWidget.h>
#include <common/ChineseInfos.hpp>
#include <controls/BaseQListWidget.h>

namespace ui{
	MsgStatusWin* MsgStatusWin::mPInstance = CNull;
	MsgStatusWin::MsgStatusWin(QWidget *parent)
		: BaseWindow(parent)
	{
		connect(this,SIGNAL(closeClicked()),this,SLOT(close()));
		this->setFixedSize(310*gDdpi,(550-52)*gDdpi);
		//this->setObjectName("bg_fa");
		
		mTabWidget = new QTabWidget(this);
		mReadMsgListWidget = new MsgStatusListWidget(this);
		mUnReadMsgListWidget = new MsgStatusListWidget(this);
		mBtnCancel = new uicontrols::Button(this);
		mBtnChasing = new uicontrols::Button(this);
		mBtnChasing->hide();
		connect(mBtnCancel,SIGNAL(clicked(bool)),this,SLOT(close()));
		connect(mBtnChasing,SIGNAL(clicked(bool)),this,SLOT(onChasing()));

		mTabWidget->addTab(mUnReadMsgListWidget,TEXT_TIP107);
		mTabWidget->addTab(mReadMsgListWidget,TEXT_TIP108);
		mTabWidget->setStyleSheet("QTabBar::tab{width:120px;}");

		mBtnCancel->setText(TEXT_TIP47);
		mBtnChasing->setText(TEXT_TIP109);
		this->setWindowTitle(TEXT_TIP110);
		mTitle->setText(TEXT_TIP110);
		mMainLayout->addWidget(mTabWidget);
		mMainLayout->setSpacing(0);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->addWidget(mBtnChasing);
		layout->addWidget(mBtnCancel);
		QWidget* widget = new QWidget(this);
		widget->setFixedHeight(52*gDdpi);
		widget->setLayout(layout);
		//mMainLayout->addWidget(widget);
		//mMainLayout->addStretch();

		mBtnCancel->setObjectName("updateCancel");
		mBtnChasing->setObjectName("sendbtn");
		mBtnCancel->setFixedSize(80*gDdpi,30*gDdpi);
		mBtnChasing->setFixedSize(80*gDdpi,30*gDdpi);
		mReadMsgListWidget->setFixedHeight(410*gDdpi);
		mUnReadMsgListWidget->setFixedHeight(410*gDdpi);
		mBtnCancel->hide();
		mChatCtrl = CHATMGRCONTROL;
		CONNECT_SERVICE(SendShortMsg(int, std::map<int64, std::string>));
		CONNECT_SERVICE(GetMemberList(int, std::vector<MemberPtr >&));
		CONNECT_SERVICE(GetGroupUnreadInfo(int, std::vector<int64>&, std::vector<int64>&,int64));
		//CONNECT_SERVICE(GetGroupMsgReadState(int, std::map<std::string, std::vector<int64>>&));
	}

	MsgStatusWin::~MsgStatusWin()
	{

	}

	void MsgStatusListWidget::clearData() {
		mListWidget->clear();
		m_memberpage.clearData();
	}

	void MsgStatusWin::reqData( int64 groupId,data::SnapshotInfo info )
	{
		mGroupId = groupId;
		if (mChatCtrl)
		{
			mReadMsgListWidget->clearData();
			mUnReadMsgListWidget->clearData();
			mTabWidget->setTabText(0,TEXT_TIP107);
			mTabWidget->setTabText(1,TEXT_TIP108);
			//mChatCtrl->getGroupMsgReadState(groupId,info.msgId,CBind(&MsgStatusWin::signalSerGetGroupUnreadInfo,this,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3,info.msgId));
			mChatCtrl->getGroupMsgUnreadInfo(groupId,info,CBind(&MsgStatusWin::signalSerGetGroupUnreadInfo,this,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3,info.msgId));
		}
	}

	void MsgStatusWin::onSerGetGroupMsgReadState(int code, std::map<std::string, std::vector<int64> >&states) {
		if (code) {
		}
	}
	void MsgStatusWin::onSerGetMemberList(int code , std::vector<MemberPtr >&mems)
	{
		if(mems.size()>0 && mems.at(0)->groupId.value() == mGroupId){
			setListData(mems);
		}
	}

	bool MsgStatusWin::isInRead(int64 id)
	{
		for (int i = 0; i < mReadIds.size(); ++i)
		{
			if (id == mReadIds.at(i))
			{
				return true;
			}
		}
		return false;
	}
	void MsgStatusWin::setListData(std::vector<MemberPtr >&mems)
	{
		std::vector<MemberPtr> unReadData,readData;
		/*IUserControl_Ptr userCtrl = USERCONTROL;
		int64 myId = 0;
		if(userCtrl){
			CSharedPtr<data::AccountInfo> user = userCtrl->GetAccountInfo();
			myId = user->id.value();
		}*/
		for (int i=0;i<mems.size();++i)
		{
			MemberPtr mem = mems.at(i);
			/*if(mem->id.value() == myId){
				continue;
			}*/
			if (isUnRead(mem->id.value()))
			{
				unReadData.push_back(mem);
			}else if(isInRead(mem->id.value())){
				readData.push_back(mem);
			}
		}
		mReadMsgListWidget->setData(readData);
		mUnReadMsgListWidget->setData(unReadData);
	}

	MsgStatusWin* MsgStatusWin::Instance(){
		if (CNull == mPInstance)
		{
			mPInstance = new MsgStatusWin();
		}
		return mPInstance;
	}
	void MsgStatusWin::showWin(int64 groupId,data::SnapshotInfo info){
		mPInstance->reqData(groupId,info);
		mPInstance->showNormal();
		mPInstance->activateWindow();
	}
	void MsgStatusWin::onSerGetGroupUnreadInfo( int code, std::vector<int64>&readIds, std::vector<int64>&unReadIds,int64 msgid )
	{
		if (code == 11100 || code == -1) {
			uicontrols::WeMessageBox::showInformation(this,transfer("提示"), transfer("网络超时请重试"));
			return;
		}
		mTabWidget->setTabText(0,TEXT_TIP111+QString::number(unReadIds.size())+"]");
		emit signalChangeMsgStatus(unReadIds.size(),msgid);
		mTabWidget->setTabText(1, TEXT_TIP112 + QString::number(readIds.size()) + "]");

		mUnReadIds = unReadIds;
		mReadIds = readIds;
		IGroupMgrControl_Ptr groupCtrl = GROUPMGRCONTROL;
		groupCtrl->GetMemberList(mGroupId,CBind(&MsgStatusWin::signalSerGetMemberList,this,CPlaceholders _1,CPlaceholders _2));

	}

	void MsgStatusWin::onSerSendShortMsg( int code, std::map<int64, std::string>results )
	{
		close();
	}

	void MsgStatusWin::onChasing()
	{
		if (mUnReadIds.size() ==0)
		{
			uicontrols::WeMessageBox::showInformation(this,TEXT_TIP109,TEXT_TIP113);
			return;
		}
		/*if (ChatPage::chasingTime()>0)
		{
			uicontrols::WeMessageBox::showInformation(this,TEXT_TIP109,TEXT_TIP114);
			return;
		}*/
		int ret = uicontrols::WeMessageBox::showQuestion(this,TEXT_TIP109,TEXT_TIP115);
		if (ret != uicontrols::WeMessageBox::Ok)
		{
			return;
		}
		/*if (mChatCtrl){
			mChatCtrl->sendShortMessage(mUnReadIds,CBind(&MsgStatusWin::signalSerSendShortMsg,this,CPlaceholders:: _1,CPlaceholders:: _2));
			ChatPage::startChasingTimer();
		}*/
	}

	bool MsgStatusWin::isUnRead( int64 id )
	{
		for (int i=0;i<mUnReadIds.size();++i)
		{
			if (id == mUnReadIds.at(i))
			{
				return true;
			}
		}
		return false;
	}

	MsgStatusListWidget::MsgStatusListWidget(QWidget *parent):TWidget(parent)
	{
			mListWidget = new uicontrols::BaseQListWidget(this);
			mListWidget->setObjectName("whiteListWidget");
			connect(mListWidget,SIGNAL(signalSrcollToBottom()),this,SLOT(onLazyLoadMember()));
			QVBoxLayout*layout = new QVBoxLayout(this);
			layout->setContentsMargins(0,0,0,0);
			layout->addWidget(mListWidget);
			setLayout(layout);
	}
	void MsgStatusListWidget::setData( std::vector<MemberPtr>mems )
	{
		mListWidget->clear();
		//设置分页加载参数
		m_memberpage.setPageSize(8);
		m_memberpage.clearData();
		m_memberpage.setData(mems);
		//加载第一页
		addItem();
	}	

	void MsgStatusListWidget::onLazyLoadMember()
	{
		if(m_memberpage.isLoadFinished()){
			m_memberpage.clearData();
			return;
		}
		addItem();
	}

	void MsgStatusListWidget::addItem()
	{
		std::vector<MemberPtr>contacts;
		m_memberpage.getPageData(contacts);
		for(int i =0; i<contacts.size();++i)
		{
			addItem(contacts.at(i));
		}
	}

	void MsgStatusListWidget::addItem(MemberPtr mem)
	{
		QListWidgetItem* item = new QListWidgetItem();
		GroupListItemWidget*widget = new GroupListItemWidget(this);
		widget->setData(transfer(mem->thumbAvatar.value().c_str()),QString::fromUtf8(mem->remark.value().c_str()));
		mListWidget->addItem(item);
		mListWidget->setItemWidget(item,widget);
	}

}
