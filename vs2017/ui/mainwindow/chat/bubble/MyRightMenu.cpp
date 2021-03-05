#include "MyRightMenu.h"
#include "common/ChineseInfos.hpp"
#include <QDateTime>
MyRightMenu::MyRightMenu(QWidget *parent):QMenu(parent),
m_pDelItem(nullptr), m_pRecallItem(nullptr), m_pCollectItem(nullptr), m_pTransportItem(nullptr), m_pCopyItem(nullptr),
m_pSaveItem(nullptr), m_pMsgStatus(nullptr), m_pCloudDisdkItem(nullptr), m_pMsgTopItem(nullptr),m_targetId(0), m_localId(0), m_msgTime(0), m_isRecv(0)
{
	QString style1 = "QMenu{background-color: white; border: 1px solid white;padding:0px 0px;}";
	QString style2 = "QMenu::item {background-color: white;padding:4px 20px;margin:0px 0px;color:#3f3f3f}";
	QString style3 = "QMenu::item:selected{ background-color: #efefef;}";
	QString style = style2 + style3;
	this->setStyleSheet(style);
}
MyRightMenu::~MyRightMenu(){

}
void MyRightMenu::init(int64 targetId, int64 localId, int64 msgTime, bool isRecv){
	m_targetId = targetId;
	m_localId = localId;
	m_msgTime = msgTime;
	m_isRecv = isRecv;

	m_pCopyItem = CMakePtr<QAction>(COPY_TIP_MSG,this); 			      //复制
	m_pSaveItem = CMakePtr<QAction>(SAVE_TIP, this); 				      //保存
	m_pTransportItem = CMakePtr<QAction>(TRANSPOND_TIP_MSG, this); 	      //转发
	m_pCollectItem = CMakePtr<QAction>(COLLECT_TIP_MSG, this);		      //收藏
	m_pRecallItem = CMakePtr<QAction>(RECALL_TIP_MSG, this);			  //撤回
	m_pDelItem = CMakePtr<QAction>(DEL_TIP_MSG, this);					  //删除
	m_pMsgStatus = CMakePtr<QAction>(MSGSTATUS_TIP_MSG, this);			  //消息状态
	m_pCloudDisdkItem = CMakePtr<QAction>(SAVECLOUDDISK_TIP_MSG, this);   //保存云盘
	m_pRecallEditItem = CMakePtr<QAction>(RECALLEDIT_TIP_MSG, this);      //撤回重编辑
	m_pMsgTopItem = CMakePtr<QAction>(MSGTOP_TIP_MSG,this);				  //消息置顶

	QObject::connect(m_pCopyItem.get(), SIGNAL(triggered()), this, SLOT(onCtrlCopyMenu()));
	QObject::connect(m_pSaveItem.get(), SIGNAL(triggered()), this, SLOT(onCtrlSaveMenu()));
	QObject::connect(m_pTransportItem.get(), SIGNAL(triggered()), this, SLOT(onCtrlTransportMenu()));
	QObject::connect(m_pCollectItem.get(), SIGNAL(triggered()), this, SLOT(onCtrlCollectMenu()));
	QObject::connect(m_pRecallItem.get(), SIGNAL(triggered()), this, SLOT(onCtrlRecallMenu()));
	QObject::connect(m_pDelItem.get(), SIGNAL(triggered()), this, SLOT(onCtrlDelMenu()));
	QObject::connect(m_pMsgStatus.get(), SIGNAL(triggered()), this, SLOT(onCtrlMsgStatusMenu()));
	QObject::connect(m_pCloudDisdkItem.get(), SIGNAL(triggered()), this, SLOT(onCtrlSaveCloudDiskMenu()));
	QObject::connect(m_pRecallEditItem.get(), SIGNAL(triggered()), this, SLOT(onCtrlRecallEditMenu()));
	//QObject::connect(m_pMsgTopItem.get(), SIGNAL(triggered()), this, SLOT(onCtrMsgTopMenu()));
}
void MyRightMenu::onCtrlDelMenu(){
	emit signalCtrlDelMenu(m_targetId, m_localId);
}
void MyRightMenu::onCtrlRecallMenu(){
	emit signalCtrlRecallMenu(m_targetId, m_localId);
}
void MyRightMenu::onCtrlRecallEditMenu()
{
	emit signalCtrlRecallEditMenu(m_targetId, m_localId);
}
void MyRightMenu::onCtrlCollectMenu(){
	emit signalCtrlCollectMenu(m_targetId, m_localId);
}
void MyRightMenu::onCtrlTransportMenu(){
	emit signalCtrlTransportMenu(m_targetId, m_localId);
}
void MyRightMenu::onCtrlCopyMenu(){
	emit signalCtrlCopyMenu(m_targetId, m_localId);
}
void MyRightMenu::onCtrlSaveMenu(){
	emit signalCtrlSaveMenu(m_targetId, m_localId);
}
void MyRightMenu::onCtrlMsgStatusMenu(){
	emit signalCtrlMsgStatusMenu(m_targetId, m_localId);
}
void MyRightMenu::onCtrlSaveCloudDiskMenu(){
	emit signalCtrlSaveCloudDiskMenu(m_targetId, m_localId);
}
void MyRightMenu::onCtrMsgTopMenu(){
	emit siganlCtrMsgTopMenu(m_targetId, m_localId);
}
void MyRightMenu::setMenuState(MenuItem item, bool isShow){
	switch (item)
	{
	case MENU_DEL:
		isShow ? this->addAction(m_pDelItem.get()) : this->removeAction(m_pDelItem.get());
		break;
	
	case MENU_COLLECT:
		isShow ? this->addAction(m_pCollectItem.get()) : this->removeAction(m_pCollectItem.get());
		break;
	case MENU_TRANSPORT:
		isShow ? this->addAction(m_pTransportItem.get()) : this->removeAction(m_pTransportItem.get());
		break;
	case MENU_COPY:
		isShow ? this->addAction(m_pCopyItem.get()) : this->removeAction(m_pCopyItem.get());
		break;
	case MENU_SAVE:
		isShow ? this->addAction(m_pSaveItem.get()) : this->removeAction(m_pSaveItem.get());
		break;
	case MENU_RECALL:{
		isShow ? this->addAction(m_pRecallItem.get()) : this->removeAction(m_pRecallItem.get());
		//int64 serverTime = gWinManger->getCurrentServeTime();  
		//(isShow && !m_isRecv && ((serverTime - m_msgTime) <= utils::FunctionConfig::GetRecallTimes())) ? this->addAction(m_pRecallItem.data()) : this->removeAction(m_pRecallItem.data());
		break;
	}
	case MENU_MSGSTATUS:
		isShow ? this->addAction(m_pMsgStatus.get()) : this->removeAction(m_pMsgStatus.get());
		if (isShow) {
			QObject::connect(m_pMsgStatus.get(), SIGNAL(triggered()), this, SLOT(onCtrlMsgStatusMenu()));
		}
		break;
	case MENU_SAVECLOUDDISK:
		isShow ? this->addAction(m_pCloudDisdkItem.get()) : this->removeAction(m_pCloudDisdkItem.get());
		break;
	case MENU_RECALLEDIT:
		isShow ? this->addAction(m_pRecallEditItem.get()) : this->removeAction(m_pRecallEditItem.get());
		break;
	case MENU_TOPMSG:
		isShow ? this->addAction(m_pMsgTopItem.get()) : this->removeAction(m_pMsgTopItem.get());
		if (isShow){
			QObject::connect(m_pMsgTopItem.get(), SIGNAL(triggered()), this, SLOT(onCtrMsgTopMenu()));
		}
		break;
	default:
		break;
	}
}
void MyRightMenu::show(){
	QPoint op = QCursor().pos();
	this->move(op);
	this->exec();
}
