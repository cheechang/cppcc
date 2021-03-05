#ifndef LOCALSEARCHLINEEDIT_H
#define LOCALSEARCHLINEEDIT_H
#include "controls/TWidget.h"
#include "controls/PushButton.h"
#include <QVBoxLayout>
#include <QLineEdit>
namespace ui{
	class LocalSearchLineEdit : public TWidget
	{
		Q_OBJECT
	public:
		LocalSearchLineEdit(QWidget *parent=CNull,bool setfocus=true);
		~LocalSearchLineEdit();
		void clearText();
	    void setPlaceholderText(QString text);
		QString text();
	protected:
		bool eventFilter(QObject *obj, QEvent *e);
	signals:
		void clearBtnClicked();
		void textChanged(const QString &text);
	private:
		QVBoxLayout* mMainLayout;
		QLineEdit*   mSearchLineEdit;
		PushButton*  mBtnDel;
		bool mShowSetFocus;
	};
}

#endif // LOCALSEARCHLINEEDIT_H
