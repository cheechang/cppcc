#ifndef COMBINEMSGWIN_H
#define COMBINEMSGWIN_H
#include <QWidget>
#include "../contact/createGroup/BaseWindow.h"
#include "ChatContentView.h"
namespace ui{
	class CombineMsgWin : public BaseWindow
	{
		Q_OBJECT
	public:
		CombineMsgWin(QWidget *parent=CNull);
		~CombineMsgWin();
		void addMsg(CSharedPtr<data::Msg>msg);
		void updateUserInfo(QMap<int64,data::UserData>data);
	private:
		ChatContentView* mChatView;
	};
}

#endif // COMBINEMSGWIN_H
