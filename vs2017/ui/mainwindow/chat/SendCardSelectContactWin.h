#ifndef SENDCARDSELECTCONTACTWIN_H
#define SENDCARDSELECTCONTACTWIN_H
#include <QListWidget>
#include "../contact/createGroup/BaseWindow.h"
#include "interface/Defines.h"
#include "common/Controlptr.h"

namespace ui{
	class LocalSearchLineEdit;
	class LocalSearchListWidget;
	class SendCardSelectContactWin : public BaseWindow
	{
		Q_OBJECT

	public:
		SendCardSelectContactWin(QWidget *parent=CNull);
		~SendCardSelectContactWin();
		void showWin();
	signals:
		void signalSendId(int64);
	protected:
		void init();
	protected slots:
		void onClearBtnClicked();
		void onTextChanged(const QString &text);
		void onClickedItem(CSharedPtr<data::ChatInfo>&chat);
	private:
		LocalSearchLineEdit* mSearchBox;
		LocalSearchListWidget*mContactList;
	};
}

#endif // SENDCARDSELECTCONTACTWIN_H
