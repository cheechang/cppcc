#ifndef FORWARDMSGWIN_H
#define FORWARDMSGWIN_H
#include <QListWidget>
#include "../contact/createGroup/BaseWindow.h"
#include "interface/Defines.h"
#include "common/Controlptr.h"
namespace ui{
	class LocalSearchLineEdit;
	class LocalSearchListWidget;
	class ForwardMsgWin : public BaseWindow
	{
		Q_OBJECT
	public:
		virtual ~ForwardMsgWin();
		static ForwardMsgWin* Instance();
		static void showWin(int64 msgId);
	signals:
		void forwardMsgTargetId(int64 toId,int64 msgId);
	protected:
		ForwardMsgWin(QWidget *parent =CNull);
		void init();

	protected slots:
		void onClearBtnClicked();
		void onTextChanged(const QString &text);
		void onClickedItem(CSharedPtr<data::ChatInfo>&chat);
	private:
		LocalSearchLineEdit* mSearchBox;
		LocalSearchListWidget*mSearchList;

		static LocalSearchListWidget* mChatList;
		static ForwardMsgWin* mPInstance;
		static int64 mMsgId;
	};
}

#endif // FORWARDMSGWIN_H
