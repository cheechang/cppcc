#include "SendCardSelectContactWin.h"
#include "common/Connect.h"
#include "data/ChatData.h"
#include "data/ContactData.h"
#include "../contact/localsearch/LocalSearchLineEdit.h"
#include "../contact/localsearch/LocalSearchListWidget.h"
#include <QMessageBox>
#include "common/Common.h"
namespace ui{
	SendCardSelectContactWin::SendCardSelectContactWin(QWidget *parent)
		: BaseWindow(parent)
	{
		init();
		connect(mBtnClose,SIGNAL(clicked()),this,SLOT(close()));
	}

	SendCardSelectContactWin::~SendCardSelectContactWin()
	{
		mContactList->clearList();
	}

	void SendCardSelectContactWin::showWin()
	{
		onTextChanged("");
		this->exec();
	}

	void ui::SendCardSelectContactWin::init()
	{
		this->setFixedSize(280,510);
		setTitle(transfer("发送名片"));
		mSearchBox = new LocalSearchLineEdit(this,false);
		mSearchBox->setPlaceholderText(transfer("搜索：联系人"));
		connect(mSearchBox,SIGNAL(clearBtnClicked()),this,SLOT(onClearBtnClicked()));
		connect(mSearchBox,SIGNAL(textChanged(const QString &)),this,SLOT(onTextChanged(const QString &)));

		QWidget* widget = new QWidget(this);
		widget->setObjectName("SearchBoxBg");
		widget->setStyleSheet("QWidget#SearchBoxBg{background:#f9f7f6;}");
		widget->setFixedSize(260,60);
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setContentsMargins(0,0,0,0);
		layout->addWidget(mSearchBox,0,Qt::AlignHCenter);
		widget->setLayout(layout);
		mMainLayout->addWidget(widget,0,Qt::AlignHCenter);
		mMainLayout->addStretch();

		mContactList = new LocalSearchListWidget(this,false,false);
		connect(mContactList,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SLOT(onClickedItem(CSharedPtr<data::ChatInfo>&)));
		mContactList->move(10,50);
		mContactList->setMinimumSize(260,400);
	}

	void ui::SendCardSelectContactWin::onTextChanged( const QString &text )
	{
		mContactList->clearList();
		IContactMgrControl_Ptr contactCtrl = CONTACTMGRCONTROL;
		std::vector<CSharedPtr<data::Contact>> cons;
		contactCtrl->GetContactList(cons);
		IUserControl_Ptr userCtrl = USERCONTROL;
		CSharedPtr<data::AccountInfo> user = userCtrl->GetAccountInfo();
		std::vector<data::ChatInfo>chatlist;

		for (int i=cons.size()-1;i>=0;--i)
		{
			CSharedPtr<data::Contact> con = cons.at(i);
			if (con->id.value() == user->id.value()) {
				continue;
			}
			if (con /*&& con->isApp.value() == 2 */&& con->isHidden.value() != 1)
			{
				data::ChatInfo chat;
				QString name = QString::fromUtf8(con->remark.value().c_str());
				if (name.isEmpty())
				{
					name = QString::fromUtf8(con->name.value().c_str());
				}
				chat.targetid = con->id.value();
				chat.name = name.toUtf8().data();
				chat.avatar = con->thumbAvatar.value();
				chat.chatType = con->isApp.value() == 1 ?data::ENT_CHAT:data::BUDDY_CHAT;
				if (text.isEmpty())
				{
					chatlist.push_back(chat);
				}else if(name.contains(text)){
					chatlist.push_back(chat);
				}
			}
		}
		mContactList->setData(chatlist);
	}

	void ui::SendCardSelectContactWin::onClickedItem( CSharedPtr<data::ChatInfo>&chat )
	{
		int ret = QMessageBox::question(this, transfer("发送名片"), transfer("您确定发送名片\"") + chat->name.c_str() + transfer("\"到此聊天？"), transfer("是"), transfer("否"));
		if (ret == 0)
		{
			emit signalSendId(chat->targetid);
		}
		this->close();
	}

	void ui::SendCardSelectContactWin::onClearBtnClicked()
	{
		mSearchBox->clearText();
	}

}