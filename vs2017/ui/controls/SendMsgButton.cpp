#include "SendMsgButton.h"
#include "common/Common.h"
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
namespace ui{
SendMsgButton::SendMsgButton(QWidget *parent)
	:QToolButton(parent),m_menu(CNull),m_enter(CNull),m_ctrlenter(CNull)
{	
    m_menu  = CMakePtr<QMenu>();
	m_enter = CMakePtr<QAction>(this);
	m_ctrlenter =CMakePtr<QAction>(this);

	m_menu->addAction(m_enter.get());
	m_menu->addAction(m_ctrlenter.get());
	m_menu->setFixedWidth(160);
	m_menu->setContentsMargins(0,5,0,0);

	connect(m_enter.get(),SIGNAL(triggered(bool)),this,SLOT(onEnterActionClicked(bool)));
	connect(m_ctrlenter.get(),SIGNAL(triggered(bool)),this,SLOT(onCtrlEnterActionClicked(bool)));

	m_enter->setCheckable(true);
	m_ctrlenter->setCheckable(true);
	m_enter->setChecked(true);

	//this->setPopupMode(QToolButton::MenuButtonPopup);
	//this->setMenu(m_menu.get());
	this->setObjectName("sendbtn");
	this->translateLanguage();
	this->setMouseTracking(true);
}
SendMsgButton::~SendMsgButton()
{
	
}
void SendMsgButton::translateLanguage(){
	m_enter->setText(transfer("按Enter键发送消息"));
	m_ctrlenter->setText(transfer("按Ctrl+Enter键发送消息"));
	this->setToolTip(transfer("按Enter键发送,Ctrl+Enter换行"));
}

void SendMsgButton::onEnterActionClicked(bool checked){
	m_enter->setChecked(checked);
	m_ctrlenter->setChecked(false);
	if (checked)
	{
		this->setToolTip(transfer("按Enter键发送,Ctrl+Enter换行"));
		int shortcut = ENTER_SEND;
		emit signalSetSendShorcut(shortcut);
	}
}
void SendMsgButton::onCtrlEnterActionClicked(bool checked){
	m_enter->setChecked(false);
	m_ctrlenter->setChecked(checked);
	if (checked)
	{
		this->setToolTip(transfer("按Ctrl+Enter键发送,Enter换行"));
		int shortcut = CTRLENTER_SEND;
		emit signalSetSendShorcut(shortcut);
	}
}
void SendMsgButton::mouseMoveEvent(QMouseEvent *event){
	event->accept();
}
}