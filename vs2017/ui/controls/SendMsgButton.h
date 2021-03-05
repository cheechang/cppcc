#pragma once
#include <QToolButton>
#include <interface/Defines.h>
class QMenu;
class QAction;
namespace ui{
class SendMsgButton : public QToolButton
{
	Q_OBJECT

public:
	explicit SendMsgButton(QWidget *parent = 0);
	~SendMsgButton();
	void translateLanguage();
protected:
	void mouseMoveEvent(QMouseEvent *event);
signals:
	void signalSetSendShorcut(int&);
public slots:
	void onEnterActionClicked(bool checked);
	void onCtrlEnterActionClicked(bool checked);
private:
	CSharedPtr<QMenu> m_menu;
	CSharedPtr<QAction> m_enter;
	CSharedPtr<QAction> m_ctrlenter;
};
}


