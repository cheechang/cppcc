#include "SystemMsgPage.h"
#include "SystemMsgItem.h"
#include <qgridlayout.h>
#include <log.h>
#include <QCoreApplication>
#include <data/ChatData.h>
#include <QDateTime>
#include <qmessagebox.h>
#include "../../common/Common.h"
#include <utils/Error.h>
namespace ui{
	bool SystemMsgPage::isSysPageSelect = false;
	SystemMsgPage::SystemMsgPage(QWidget *parent): QWidget(parent),m_isGetData(true)
	{
		m_sysmsgcontrol = SYSMSGCONTROL;
		CONNECT_SERVICE(GetAllSysMsg(int ,std::vector< data::SysMsg>& ));
		CONNECT_SERVICE(SetSysMsgRead(int ));
		CONNECT_SERVICE(RemoveSysMsg(int ));
		CONNECT_SERVICE(RegLastSysMsg(const  data::SysMsg& , int ));
		CONNECT_SERVICE(AddBuddyResp(int ));
		CONNECT_SERVICE(AddGroupResp(int ));
		CONNECT_SERVICE(RegSysMsg(const data::SysMsg&));
		

		this->setStyleSheet("QWidget{background:white;}");
		
		m_ptrListWidget = CMakePtr<QListWidget>(this);

		//m_ptrListWidget->setFlow(QListView::TopToBottom);
	//	m_ptrListWidget->setMovement(QListView::Static);
		m_ptrListWidget->setSpacing(8);

		this->setVisible(false);

		m_Layout = CMakePtr<QVBoxLayout>(this);
		m_Layout->addWidget(m_ptrListWidget.get());
		m_Layout->setContentsMargins(0, 0, 0, 0);
		this->setLayout(m_Layout.get());
		if (m_sysmsgcontrol)
		{
			m_sysmsgcontrol->regLastSysMsgCb(CBind(&SystemMsgPage::signalSerRegLastSysMsg, this, CPlaceholders  _1, CPlaceholders  _2));
			m_sysmsgcontrol->regSysMsgCb(CBind(&SystemMsgPage::signalSerRegSysMsg,this,CPlaceholders  _1));
		}
		
		CONNECT_SERVICE(SendMsg(int,int64 ,int64));
		mChatCtrl = CHATMGRCONTROL;
		
	}

	SystemMsgPage::~SystemMsgPage()
	{
		clearData();
	}
	void SystemMsgPage::InitData()
	{
		if (m_isGetData)
		{
			AddLog(LOG_LEV_DEBUG,"SystemMsgPage::InitData() getAllData");
			m_isGetData = false;
			clearData();
			m_sysmsgcontrol->getMessages(0,5000,0,1,CBind(&SystemMsgPage::signalSerGetAllSysMsg, this,CPlaceholders  _1, CPlaceholders  _2));
		}
	}
	void SystemMsgPage::clearData()
	{
		BEGIN;
		int count = m_ptrListWidget->count();
		for(int i = 0; i < count; i++)
		{
			QListWidgetItem * ret = m_ptrListWidget->takeItem(0);
			if(ret != 0)
			{
				m_ptrListWidget->removeItemWidget(ret);
			}
		}

		std::map<int64, SysMsgItem>::iterator iter = m_itemMap.begin();
		while(iter != m_itemMap.end())
		{
			if(CNull != iter->second.listItem)
			{
				delete iter->second.listItem;
			}

			if(CNull != iter->second.msgItem)
			{
				delete iter->second.msgItem;
			}
			++iter;
		}
		m_itemMap.clear();
		m_mapData.clear();
		END;
	}

	void SystemMsgPage::dealAddFridenSysMsg(int64 usrId)
	{
		SystemMsgItem* ptrItem = CNull;

		for (int i = 0; i < m_ptrListWidget->count(); i++)
		{
			ptrItem = (SystemMsgItem*)m_ptrListWidget->item(i);
			if (ptrItem->getSysUserid() == usrId)
			{

			}
		}
	}

	void SystemMsgPage::onSerRegSysMsg(const  data::SysMsg& sysMsg)
	{
		SystemMsgItem* ptrItem = CNull;

		for (int i = 0; i < m_ptrListWidget->count(); i++)
		{
			ptrItem = (SystemMsgItem*)m_ptrListWidget->item(i);
			if (ptrItem->getSysMsgid() == sysMsg.msgId)
			{

			}
		}
	}

	void SystemMsgPage::onSerGetAllSysMsg(int err,std::vector< data::SysMsg>& sysMsg)
	{
		BEGIN;
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"errCode=%d",err);
			return;
		}
		AddLog(LOG_LEV_DEBUG,"sysMsg size = %d", sysMsg.size());
		setSysMsgReaded(sysMsg);
		for (int index = (sysMsg.size()-1); index>=0; index--)
		{
			if (isItemShow(sysMsg.at(index)))
			{
				addSysMsgListItem(sysMsg.at(index));
				QCoreApplication::processEvents();
			}
		}
		END;
	}
	void SystemMsgPage::onSerSetSysMsgRead(int err)
	{
		BEGIN;
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"errCode=%d",err);
		}
		END;
	}
	void SystemMsgPage::onSerRemoveSysMsg(int err)
	{
		BEGIN;
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"errCode=%d",err);
		}
		END;
	}
	void SystemMsgPage::onSerRegLastSysMsg(const  data::SysMsg& sysMsg, int count)
	{
		BEGIN;
		AddLog(LOG_LEV_DEBUG,"RegLastSysMsg count = %d",count);
		m_isGetData = true;
		if (count>0)
		{
			addSysMsgListItem(sysMsg,0);
			std::vector< data::SysMsg>sysMsgs;
			sysMsgs.push_back(sysMsg);
			setSysMsgReaded(sysMsgs);
		}
		END;
	}
	bool SystemMsgPage::isItemShow(const data::SysMsg& sysMsg)
	{
		bool isShow = true;
		 if (2 == sysMsg.msgType && 2 == sysMsg.operType) {
			//对方拒绝添加好友验证消息
			isShow  = false;
		}
		else if (2 == sysMsg.msgType && 3 ==  sysMsg.operType) {
			//对方永久拒绝您添加好友验证消息
			isShow  = false;
		}
		else if (4 == sysMsg.msgType && 3 ==  sysMsg.operType) {
			//群管理员拒绝您加入群验证消息
			isShow  = false;
		}
		else if (4 == sysMsg.msgType && 4 ==  sysMsg.operType) {
			//群管理员永久拒绝您加入群验证消息
			isShow  = false;
		}
		return isShow;
	}
	void SystemMsgPage::setSysMsgReaded( const std::vector< data::SysMsg>& sysMsg)
	{
		std::vector<int64> ReqType1MsgIDs;
		std::vector<int64> ReqType2MsgIDs;
		std::vector<int64> ReqType3MsgIDs;
		std::vector<int64> ReqType4MsgIDs;
		for (int  index = 0; index<sysMsg.size(); index++)
		{
			if (sysMsg.at(index).isRead == 0)
			{
				if (sysMsg.at(index).msgType == 1)
				{
					ReqType1MsgIDs.push_back(sysMsg.at(index).msgId);
				}
				else if (sysMsg.at(index).msgType == 2)
				{
					ReqType2MsgIDs.push_back(sysMsg.at(index).msgId);
				}
				else if (sysMsg.at(index).msgType == 3)
				{
					ReqType3MsgIDs.push_back(sysMsg.at(index).msgId);
				}
				else if (sysMsg.at(index).msgType == 4)
				{
					ReqType4MsgIDs.push_back(sysMsg.at(index).msgId);
				}
			}
		}
		if (!ReqType1MsgIDs.empty())
			m_sysmsgcontrol->setMessagRead(1, ReqType1MsgIDs, CBind(&SystemMsgPage::signalSerSetSysMsgRead, this, CPlaceholders  _1));

		if (!ReqType2MsgIDs.empty())
			m_sysmsgcontrol->setMessagRead(2, ReqType2MsgIDs, CBind(&SystemMsgPage::signalSerSetSysMsgRead, this, CPlaceholders  _1));

		if (!ReqType3MsgIDs.empty())
			m_sysmsgcontrol->setMessagRead(3, ReqType3MsgIDs, CBind(&SystemMsgPage::signalSerSetSysMsgRead, this, CPlaceholders  _1));

		if (!ReqType4MsgIDs.empty())
			m_sysmsgcontrol->setMessagRead(4, ReqType4MsgIDs, CBind(&SystemMsgPage::signalSerSetSysMsgRead, this, CPlaceholders  _1));

	}
	void SystemMsgPage::addSysMsgListItem(data::SysMsg sysmsg,int pos)
	{
		QListWidgetItem* listItem = new QListWidgetItem();
		SystemMsgItem* ptrItem = new SystemMsgItem(this);
		ptrItem->SetItemData(sysmsg);

		connect(ptrItem, SIGNAL(signalDelBtnClicked(int64)), this, SLOT(onDelBtnClicked(int64)));
		connect(ptrItem, SIGNAL(signalIgnoreClicked(int64)), this, SLOT(onIgnoreClicked(int64)));
		connect(ptrItem, SIGNAL(signalAgreeClicked(int64)), this, SLOT(onAgreeClicked(int64)));
		//int pos = m_ptrListWidget->count();
		if (pos == -1)
		{
			m_ptrListWidget->addItem(listItem);
		}else{
			m_ptrListWidget->insertItem(0,listItem);
		}
		

		m_ptrListWidget->setItemWidget(listItem,ptrItem);

		SysMsgItem msg;
		msg.listItem = listItem;
		msg.msgItem = ptrItem;

		m_itemMap.insert(std::make_pair(sysmsg.msgId,msg));
		m_mapData.insert(std::make_pair(sysmsg.msgId,sysmsg));
	}
	
	void SystemMsgPage::onDelBtnClicked(int64 msgID)
	{
		std::map<int64,SysMsgItem>::iterator iter = m_itemMap.find(msgID);
		int row = m_ptrListWidget->row(iter->second.listItem);

		if(iter != m_itemMap.end())
		{
			m_ptrListWidget->takeItem(row);
			m_ptrListWidget->removeItemWidget(iter->second.listItem);
			if(CNull != iter->second.listItem)
			{
				delete iter->second.listItem;
			}

			if(CNull != iter->second.msgItem)
			{
				delete iter->second.msgItem;
			}
			m_itemMap.erase(iter);
		}
		//
		std::map<int64, data::SysMsg>::iterator iterData = m_mapData.find(msgID);
		if (iterData != m_mapData.end())
		{
			std::vector<int64> msgs(msgID);
			int msgType = iterData->second.msgType;
			m_sysmsgcontrol->deleteMessageByType(msgType, msgs, CBind(&SystemMsgPage::signalSerRemoveSysMsg, this, CPlaceholders  _1));
		}
	
	}
	void SystemMsgPage::onAgreeClicked(int64 msgId)
	{
		std::map<int64, data::SysMsg>::iterator iterData = m_mapData.find(msgId);
		if (iterData == m_mapData.end())
		{
			return;
		}
		data::SysOperType operType  =data::eSysAgree;
		int msgType = iterData->second.msgType;
		if (msgType == 1 || msgType == 2)
		{
			mAddFriendAgreeMsg = iterData->second; 
			m_sysmsgcontrol->respToAddBuddy(iterData->second.userId, msgId, operType, "","", CBind(&SystemMsgPage::signalSerAddBuddyResp, this, CPlaceholders  _1));
		}
		else
		{
			m_sysmsgcontrol->respToEnterGroup(iterData->second.groupId, msgId, operType,"", CBind(&SystemMsgPage::signalSerAddGroupResp, this, CPlaceholders  _1));
		}
	}
	void SystemMsgPage::onIgnoreClicked(int64 msgId)
	{
		std::map<int64, data::SysMsg>::iterator iterData = m_mapData.find(msgId);
		if (iterData == m_mapData.end())
		{
			return;
		}
		data::SysOperType operType = data::eSysRefuse;
		int msgType = iterData->second.msgType;
		if (msgType == 1 || msgType == 2)
		{
			m_sysmsgcontrol->respToAddBuddy(iterData->second.userId, msgId, operType, "","", CBind(&SystemMsgPage::signalSerAddBuddyResp, this, CPlaceholders  _1));
		}
		else
		{
			m_sysmsgcontrol->respToEnterGroup(iterData->second.groupId, msgId, operType,"", CBind(&SystemMsgPage::signalSerAddGroupResp, this, CPlaceholders  _1));
		}

	}
	void SystemMsgPage::onSerAddBuddyResp(int err)
	{
		BEGIN;
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"onSerAddBuddyResp errCode=%d",err);
			QMessageBox::information(CNull, transfer("提示"), utils::Error::GetErrMsg(err).c_str());
		
		}else{
			//发送一条消息
			IUserControl_Ptr userCtrl = USERCONTROL;
			int64 svrTime = 0;
			bool ret = false;
			if (userCtrl)
			{
				ret = userCtrl->getServerTimeSync(svrTime);
			}
			svrTime = ret ? svrTime :QDateTime::currentMSecsSinceEpoch();

			CSharedPtr<data::Msg> msg = CNull;
			CSharedPtr<data::MsgText> msgText = CMakePtr<data::MsgText>();
			msgText->targetId = mAddFriendAgreeMsg.userId;
			msgText->body = transfer("你是我的好友了，现在可以开始聊天了").toUtf8().data();
			msgText->localId = svrTime;
			msgText->time = svrTime;
			msgText->fromId = userCtrl->GetAccountInfo()->id.value();
			msg = msgText;
			if (mChatCtrl)
			{
				mChatCtrl->SendMessage(msg,CBind(&SystemMsgPage::signalSerSendMsg,this,CPlaceholders _1,CPlaceholders _2, CPlaceholders _3));
			}
		}
		END;
	}
	void SystemMsgPage::onSerAddGroupResp(int err)
	{
		BEGIN;
		if (err != 0)
		{
			QMessageBox::information(CNull, transfer("提示"), utils::Error::GetErrMsg(err).c_str());
			AddLog(LOG_LEV_ERROR,"errCode=%d",err);
		}
		END;
	}

	void SystemMsgPage::onSerSendMsg( int err,int64 msgtime,int64 msgid )
	{
	}

}