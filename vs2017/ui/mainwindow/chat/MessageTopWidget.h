#ifndef MESAAGETOPWIDGET_H
#define MESAAGETOPWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <data/ChatData.h>
#include <interface/IChatMgrControl.h>
#include "bubble/richtextmessagewidget.h"
#include <data/GroupData.h>
#include <data/ContactData.h>
#include <common/Controlptr.h>
#include "../contact/createGroup/BaseWindow.h"
#include <QAction>
#include <QMenu>

class QPushButton;
class QTextEdit;
namespace ui {
	class MsgListWidgetItem : public QWidget
	{
		Q_OBJECT
	public:
		explicit MsgListWidgetItem(QWidget *parent = CNull);
		~MsgListWidgetItem();
		void init();
		void setData(data::ZxTopInformation& msg,bool isCanopr);
		int getContentHigh();
		int64 getMsgId(){ return m_msg.id;}
	signals:
		void signalSerCancelTopMsg(data::ZxTopInformation& m_msg);
	public slots:
		void onCancelTopMessage();
	private:
		CSharedPtr<QLabel> m_lblTitle;
		CSharedPtr<QTextEdit> m_msgBody;
		CSharedPtr<QPushButton> m_btnDel;
		data::ZxTopInformation m_msg;
		IGroupMgrControl_Ptr m_groupMbr;
		IChatMgrControl_Ptr m_chatMbr;
	};

	class MessageTopWidget :public BaseWindow
    {
		Q_OBJECT
     public:
		MessageTopWidget(QWidget*parent = 0);
		~MessageTopWidget();
		void setTopMessage(std::vector<data::ZxTopInformation>& topMsgV);
		//void getTopMessage();
		void setEnableCancelTop(bool isCanOpr);
	protected:
		void addMsgItemToList();
	signals:
		void signalSerCancelTopMsg();
		void signalSercppccTopInfo(int, const std::string&,int64 id);
	public slots:
		void onSercppccTopInfo(int code, const std::string& strError,int64 id);
		void onSerCancelTopMsg(data::ZxTopInformation& cancelMsg);
		void onClose();
	private:
		bool m_CanOpr;
		QListWidget* m_TopmessageList;
		QVBoxLayout* m_mainLayout;
		IContactMgrControl_Ptr mContactControl;
		IGroupMgrControl_Ptr m_groupMbr;
		IUserControl_Ptr m_usercontrol;
    };
}

#endif // MESAAGETOPWIDGET_H
