#include "systemmsgitem.h"
#include <PushButton.h>
#include <QGridLayout>
#include <QEvent>
#include <qsignalmapper.h>
#include "common/MsgTimeDeal.hpp"
#include "common/Common.h"
#include <QLabel>
namespace ui{
	SystemMsgItem::SystemMsgItem(QWidget *parent) : TWidget(parent),m_msgID(0)
	{
		this->setFixedHeight(80);
		this->setStyleSheet("background-color: white");

		m_ptrDel= CMakePtr<PushButton>(this);

		m_ptrDel->setPicName(":/chat/delete");
		m_ptrDel->setVisible(false);

		m_ptrDate = CMakePtr<QLabel>(this);
		m_ptrDate->setAlignment(Qt::AlignVCenter);
		m_ptrDate->setFixedHeight(24);

		m_ptrName = CMakePtr<QLabel>(this);
		m_ptrName->setFixedWidth(140);

		m_ptrNotifyMsg = CMakePtr<QLabel>(this);
		m_ptrExtraMsg = CMakePtr<QLabel>(this);
		m_ptrSplitteLine = CMakePtr<QLabel>(this);

		m_ptrAgree = CMakePtr<QPushButton>(this);
		m_ptrIgnore = CMakePtr<QPushButton>(this);

		m_ptrGridLayout = CMakePtr<QGridLayout>(this);
		m_ptrMainLayout = CMakePtr<QVBoxLayout>(this);

		connect(m_ptrAgree.get(), SIGNAL(clicked()),this, SLOT(onBtnAgreeClicekd()));
		connect(m_ptrIgnore.get(), SIGNAL(clicked()),this, SLOT(onBtnIgnoreClicked()));
		connect(m_ptrDel.get(),SIGNAL(clicked()),this, SLOT(onBtnDelClicekd()));

		Init();
	}
	void SystemMsgItem::onBtnDelClicekd()
	{
		emit signalDelBtnClicked(m_msgID);
	}

	void SystemMsgItem::onBtnAgreeClicekd()
	{
		m_ptrIgnore->setEnabled(false);
		m_ptrIgnore->setText(QString::fromLocal8Bit("已同意"));
		m_ptrAgree->setVisible(false);
		m_ptrIgnore->setStyleSheet("QPushButton{background-color: white;border-radius:2px;border:1px solid rgb(190, 190, 190);}");
		emit signalAgreeClicked(m_msgID);
	}
	void SystemMsgItem::onBtnIgnoreClicked()
	{
		if(m_ptrAgree->isVisible())
		{
			m_ptrAgree->setVisible(false);
			m_ptrIgnore->setText(QString::fromLocal8Bit("已拒绝"));
		}
		m_ptrIgnore->setEnabled(false);
		m_ptrIgnore->setStyleSheet("QPushButton{background-color: white;border-radius:2px;border:1px solid rgb(190, 190, 190);}");	
		emit signalIgnoreClicked(m_msgID);
	}
	
	SystemMsgItem::~SystemMsgItem()
	{

	}

	void SystemMsgItem::enterEvent(QEvent *e)
	{
		m_ptrDel->setVisible(true);
		e->accept();
	}

	void SystemMsgItem::SetItemData(data::SysMsg& data)
	{
		m_msgID = data.msgId;
		m_userId = data.userId;
		QFont ft = m_ptrName->font();  
		QFontMetrics fm(ft);
		int textWidth = 135;
		QString textName =  QString::fromUtf8(data.userName.c_str());
		textName = fm.elidedText(textName, Qt::ElideRight,textWidth); 
		m_ptrName->setText(textName);
		m_ptrName->setToolTip(textName);

		QString strDateTime = DealMsgTime(data.time,CHATLIST_TIME);
		m_ptrDate->setText(strDateTime);
		handleMsg(data);
	}
	void SystemMsgItem::handleMsg(data::SysMsg sysMsg)
	{
		int msgtype = sysMsg.msgType;
		int subtype = sysMsg.subType;
		int opertype = sysMsg.operType;
		int isResponse = sysMsg.isResponse;
		QString extraMsg = transfer("附加消息：")+QString::fromUtf8(sysMsg.info.c_str());
		QFont ft = m_ptrName->font();  
		QFontMetrics fm(ft);
		int textWidth = 260;
		extraMsg = fm.elidedText(extraMsg, Qt::ElideRight,textWidth); 
		if (1 == msgtype && 1 == subtype) {
			//好友添加请求信息
			m_ptrNotifyMsg->setText(transfer("请求添加你为好友  来自账号查找"));
			m_ptrExtraMsg->setText(extraMsg);
			if (2 == isResponse)
			{
				QString resultText =(opertype ==1 ? transfer("已同意") : transfer("已拒绝")  );
				m_ptrAgree->setVisible(false);
				m_ptrIgnore->setText(resultText);
				m_ptrIgnore->setEnabled(false);
				m_ptrIgnore->setStyleSheet("QPushButton{background-color: white;border-radius:2px;border:1px solid rgb(190, 190, 190);}");		
			}
		//	return 1;
		}
		else if (1 == msgtype && 2 == subtype) {
			//关注验证消息
			//return 2;
		}
		else if (2 == msgtype && 1 == opertype) {
			//对方同意添加好友验证消息
			m_ptrNotifyMsg->setText(transfer("通过了您的好友请求"));
			m_ptrExtraMsg->setVisible(false);
			m_ptrAgree->setVisible(false);
			m_ptrIgnore->setVisible(false);
			//return 3;
		}
		else if (2 == msgtype && 2 == opertype) {
			//对方拒绝添加好友验证消息 不展示
		//	return 4;
		}
		else if (2 == msgtype && 3 == opertype) {
			//对方永久拒绝您添加好友验证消息 不展示
			//return 5;
		}
		else if (3 == msgtype && 1 == subtype) {
			//群邀请验证消息
			m_ptrNotifyMsg->setText(transfer("邀请您加入群  ")+QString::fromUtf8(sysMsg.groupName.c_str()));
			m_ptrExtraMsg->setText(extraMsg);
			if (2 == isResponse)
			{
				QString resultText =(opertype ==1 ? transfer("已同意") : transfer("已拒绝")  );
				m_ptrAgree->setVisible(false);
				m_ptrIgnore->setText(resultText);
				m_ptrIgnore->setEnabled(false);
				m_ptrIgnore->setStyleSheet("QPushButton{background-color: white;border-radius:2px;border:1px solid rgb(190, 190, 190);}");		
			}
			//return 6;
		}
		else if (3 == msgtype && 2 == subtype) {
			//申请加入群验证消息
			m_ptrNotifyMsg->setText(transfer("申请加入群  ")+QString::fromUtf8(sysMsg.groupName.c_str()));
			m_ptrExtraMsg->setText(extraMsg);
			if (2 == isResponse)
			{
				QString resultText =(opertype ==1 ? transfer("已同意") : transfer("已拒绝")  );
				m_ptrAgree->setVisible(false);
				m_ptrIgnore->setText(resultText);
				m_ptrIgnore->setEnabled(false);
				m_ptrIgnore->setStyleSheet("QPushButton{background-color: white;border-radius:2px;border:1px solid rgb(190, 190, 190);}");		
			}
			//return 7;
		}
		else if (4 == msgtype && 2 == opertype) {
			//群管理员同意您加入群验证消息
			m_ptrNotifyMsg->setText(transfer("同意您加入群  ")+QString::fromUtf8(sysMsg.groupName.c_str()));
			m_ptrExtraMsg->setVisible(false);
			m_ptrAgree->setVisible(false);
			m_ptrIgnore->setVisible(false);
		//	return 8;
		}
		else if (4 == msgtype && 3 == opertype) {
			//群管理员拒绝您加入群验证消息 不展示
		//	return 9;
		}
		else if (4 == msgtype && 4 == opertype) {
			//群管理员永久拒绝您加入群验证消息 不展示
		//	return 10;
		}
		else if (4 == msgtype && 5 == opertype) {
			//群主解散了群验证消息
			m_ptrNotifyMsg->setText(transfer("解散了群  ")+QString::fromUtf8(sysMsg.groupName.c_str()));
			m_ptrExtraMsg->setVisible(false);
			m_ptrAgree->setVisible(false);
			m_ptrIgnore->setVisible(false);
			//return 11;
		}
		else if (4 == msgtype && 6 == opertype) {
			//群管理员把您移出群验证消息
			m_ptrNotifyMsg->setText(transfer("已经将您移出群  ")+QString::fromUtf8(sysMsg.groupName.c_str()));
			m_ptrExtraMsg->setVisible(false);
			m_ptrAgree->setVisible(false);
			m_ptrIgnore->setVisible(false);
			//return 12;
		}
		else if (4 == msgtype && 7 == opertype) {
			//成员退群验证消息
			m_ptrNotifyMsg->setText(transfer("已经退出群  ")+QString::fromUtf8(sysMsg.groupName.c_str()));
			m_ptrExtraMsg->setVisible(false);
			m_ptrAgree->setVisible(false);
			m_ptrIgnore->setVisible(false);
			//return 13;
		}

	}
	void SystemMsgItem::leaveEvent(QEvent *e)
	{
		if(m_ptrDel != CNull)
		{
			m_ptrDel->setVisible(false);
		}
		e->accept();
	}

	void SystemMsgItem::Init()
	{
		initWidgets();
		initLayout();
	}

	void SystemMsgItem::initLayout()
	{
		m_ptrGridLayout->addWidget(m_ptrDate.get(),0,0,1,1,Qt::AlignLeft);
		m_ptrGridLayout->addWidget(m_ptrName.get(),1,0,1,1,Qt::AlignLeft);

		m_ptrGridLayout->addWidget(m_ptrName.get(),1,0,1,1,Qt::AlignLeft);
		//通知
		m_ptrGridLayout->addWidget(m_ptrNotifyMsg.get(),1,1,1,1,Qt::AlignVCenter);
		m_ptrGridLayout->addWidget(m_ptrExtraMsg.get(),2,1,1,1,Qt::AlignVCenter);

		m_ptrGridLayout->addWidget(m_ptrDel.get(),0,3,1,1,Qt::AlignRight);
		m_ptrGridLayout->addWidget(m_ptrAgree.get(),1,2,1,1,Qt::AlignVCenter);
		m_ptrGridLayout->addWidget(m_ptrIgnore.get(),1,3,1,1,Qt::AlignVCenter);

		m_ptrGridLayout->setVerticalSpacing(7);
		m_ptrGridLayout->setContentsMargins(10,0,10,0);
		m_ptrGridLayout->setColumnStretch(1, 10);

 		QWidget* tmp = new QWidget(this);
 		tmp->setLayout(m_ptrGridLayout.get());

		m_ptrMainLayout->addWidget(tmp);
		m_ptrMainLayout->addWidget(m_ptrSplitteLine.get(),0,Qt::AlignBottom);

		m_ptrMainLayout->setContentsMargins(10,0,10,0);
		this->setLayout(m_ptrMainLayout.get());
	}

	void SystemMsgItem::initWidgets()
	{
		m_ptrSplitteLine->setFixedHeight(1);
		m_ptrSplitteLine->setStyleSheet("QLabel{background-color: rgb(190, 190, 190);}");

		m_ptrDate->setObjectName("SysNotifyFont12");
		m_ptrDate->setMinimumWidth(80);
		//m_ptrDate->setStyleSheet("QLabel{background-color: transparent;border:none; font: 12px}");

		m_ptrName->setMinimumWidth(40);
		m_ptrName->setObjectName("SysNotifyFont12");
		//m_ptrName->setStyleSheet("QLabel{background-color: transparent;border:none; font: 14px}");

		m_ptrExtraMsg->setMinimumWidth(40);
		m_ptrExtraMsg->setObjectName("SysNotifyFont12");
		//m_ptrExtraMsg->setStyleSheet("QLabel{background-color:transparent;border:none; font: 14px}");

		m_ptrAgree->setFixedSize(50,20);
		m_ptrAgree->setText(QString::fromLocal8Bit("同意"));
		m_ptrAgree->setObjectName("SysMsg");
		m_ptrAgree->setStyleSheet("QPushButton{background-color: rgb(1, 136, 251);border-radius:2px;border:1px; font: 12px}"
			"QPushButton:pressed {background-color: rgb(10, 120, 230);}");

		m_ptrIgnore->setFixedSize(50,20);
		m_ptrIgnore->setText(QString::fromLocal8Bit("拒绝"));
		m_ptrIgnore->setStyleSheet("QPushButton{background-color: rgb(1, 136, 251);border-radius:2px;border:1px; font: 12px}"
			"QPushButton:pressed {background-color: rgb(10, 120, 230);}");

		m_ptrNotifyMsg->setObjectName("SysNotifyFont12");
		m_ptrNotifyMsg->setMinimumWidth(350);
		//m_ptrNotifyMsg->setStyleSheet("QPushButton{background-color: transparent;border:none; font: 12px}");
	}

}

