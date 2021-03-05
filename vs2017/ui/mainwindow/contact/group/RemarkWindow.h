#ifndef REMARKWINDOW_H
#define REMARKWINDOW_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "../createGroup/BaseWindow.h"
#include "../../controls/TWidget.h"

namespace ui{
	class PushButton;
	class RemarkWindow :public BaseWindow
	{
		Q_OBJECT
	public:
		RemarkWindow(QWidget *parent = CNull);
		~RemarkWindow();
		int showWin(QString& remark);
	private:
		QLineEdit* m_pEdit;
		QPushButton* m_pButton;
	};
}
#endif // REMARKWINDOW_H
