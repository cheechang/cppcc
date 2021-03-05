#ifndef LOCALSEARCHLINEEDIT_H
#define LOCALSEARCHLINEEDIT_H
#include "controls/TWidget.h"
#include "controls/PushButton.h"
#include "Common/Common.h"
#include <QVBoxLayout>
#include <QLineEdit>
namespace ui{
	class LocalSearchLineEdit : public TWidget
	{
		Q_OBJECT
	public:
		LocalSearchLineEdit(FileType type, QWidget *parent = nullptr);
		~LocalSearchLineEdit();
		void clearText();
	protected:
		bool eventFilter(QObject *obj, QEvent *e);
		void paintEvent(QPaintEvent *event);
	signals:
		void clearBtnClicked();
		void textChanged(const QString &text);
		void signalSearchFile(QString&key);
		void signalRefreshList();
	protected slots:
		void onSearchBtnClicked();
		void onDelBtnClicked();
		void onTextChanged(const QString &text);
	private:
		QVBoxLayout* mMainLayout;
		QLineEdit*   mSearchLineEdit;
		PushButton*  mBtnDel;
		PushButton*  mBtnSearch;
	};
}

#endif // LOCALSEARCHLINEEDIT_H
