#include "ForwardMsgWin.h"
#include "common/Connect.h"
#include "data/ChatData.h"
#include "../contact/localsearch/LocalSearchLineEdit.h"
#include "../contact/localsearch/LocalSearchListWidget.h"
#include <QMessageBox>
#include "../../common/Common.h"
namespace ui{
	LocalSearchListWidget* ForwardMsgWin::mChatList = CNull;
	ForwardMsgWin* ForwardMsgWin::mPInstance = CNull;
	int64 ForwardMsgWin::mMsgId = 0;
	ForwardMsgWin::ForwardMsgWin(QWidget *parent)
		: BaseWindow(parent)
	{
		connect(mBtnClose,SIGNAL(clicked()),this,SLOT(close()));
		init();
	}

	ForwardMsgWin::~ForwardMsgWin()
	{

	}

	void ForwardMsgWin::init()
	{
		this->setFixedSize(280,510);
		setTitle(transfer("消息转发"));
		mSearchBox = new LocalSearchLineEdit(this,false);
		mSearchBox->setPlaceholderText(transfer("搜索：联系人、群"));
		connect(mSearchBox,SIGNAL(clearBtnClicked()),this,SLOT(onClearBtnClicked()));
		connect(mSearchBox,SIGNAL(textChanged(const QString &)),this,SLOT(onTextChanged(const QString &)));
		mSearchBox->setFixedSize(250, 50);
		QWidget* widget = new QWidget(this);
		widget->setObjectName("SearchBoxBg");
		widget->setStyleSheet("QWidget#SearchBoxBg{background:#f9f7f6;}");
		widget->setFixedSize(260,80);//(260,60)（2020年9月23日）
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setContentsMargins(0,0,0,0);
		layout->addWidget(mSearchBox,0,Qt::AlignCenter);
		widget->setLayout(layout);
		mMainLayout->addWidget(widget,0,Qt::AlignHCenter);
		mMainLayout->addStretch();

		//本地搜索
		mSearchList = new LocalSearchListWidget(this,false,false);
		connect(mSearchList,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SLOT(onClickedItem(CSharedPtr<data::ChatInfo>&)));
		mSearchList->move(10,100);
		mSearchList->setMinimumSize(260,400);
		mSearchList->hide();

		//最近会话
		mChatList = new LocalSearchListWidget(this,false,false);
		connect(mChatList,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SLOT(onClickedItem(CSharedPtr<data::ChatInfo>&)));
		mChatList->move(10,100);
		mChatList->setMinimumSize(260,400);
	}

	ForwardMsgWin* ForwardMsgWin::Instance()
	{
		if (CNull == mPInstance)
		{
			mPInstance = new ForwardMsgWin();
		}
		return mPInstance;
	}

	void ForwardMsgWin::onClearBtnClicked()
	{
		mSearchBox->clearText();
	}

	void ForwardMsgWin::onTextChanged( const QString &text )
	{
		if (text.isEmpty())
		{
			mSearchList->clearList();
			mSearchList->hide();
			mChatList->show();
		}else{
			mSearchList->searchFromLocal(text);
			mSearchList->show();
			mChatList->hide();
		}
	}

	void ForwardMsgWin::showWin(int64 msgid)
	{
		std::vector<CSharedPtr<data::ChatData> >chatlist;
		std::vector<data::ChatInfo> chats;
		IChatMgrControl_Ptr mChatControl = CHATMGRCONTROL;
		mChatControl->GetChatList(chatlist);
		for (int i=0;i<chatlist.size();++i)
		{
			CSharedPtr<data::ChatData> data = chatlist.at(i);
			data::ChatInfo chat;
			chat.targetid = data->id.value();
			chat.name = data->name.value();
			chat.avatar = data->thumbAvatar.value();
			chat.chatType = (data::ChatType)data->chatType;
			chats.push_back(chat);
		}
		mMsgId = msgid;
		mChatList->setData(chats);
		mChatList->show();
		mPInstance->showNormal();
		mPInstance->activateWindow();
	}

	void ForwardMsgWin::onClickedItem( CSharedPtr<data::ChatInfo>&chat )
	{
		int ret = QMessageBox::question(this, transfer("消息转发"), transfer("是否转发给：") + chat->name.c_str() + transfer("?"), transfer("是"),transfer("否"));
		if (0 == ret)
		{
			mSearchBox->clearText();
			emit forwardMsgTargetId(chat->targetid,mMsgId);
		}
		else{
			//mChatList->clearList();
			mPInstance->hide();
		}
	}

}
