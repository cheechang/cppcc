#include "CombineMsgWin.h"
#include "PushButton.h"
namespace ui{
	CombineMsgWin::CombineMsgWin(QWidget *parent)
		: BaseWindow(parent)
	{
		this->setFixedSize(420,480);
		connect(mBtnClose,SIGNAL(clicked()),this,SLOT(close()));
		mChatView = new ChatContentView(this);
		mChatView->useByCombineMsgWin();
		mMainLayout->addWidget(mChatView);
		mMainLayout->addStretch();
	}

	CombineMsgWin::~CombineMsgWin()
	{

	}

	void CombineMsgWin::addMsg( CSharedPtr<data::Msg>msg )
	{
		mChatView->addMsg(msg);
	}

	void CombineMsgWin::updateUserInfo( QMap<int64,data::UserData>data )
	{
		mChatView->updateMsgItemNameAndAvatar(data);
	}

}
