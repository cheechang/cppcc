#pragma once
#include <QListWidget>
#include <qlistwidget.h>
#include "data/SysMsgData.h"
#include <interface/ISysMsgMgrControl.h>
#include "common/Controlptr.h"
class QVBoxLayout;
namespace ui{
	class SystemMsgItem;
	struct SystemItemInfo;
	
	struct SysMsgItem
	{
		SysMsgItem()
		{
			msgItem = CNull;
			listItem = CNull;
		}

		SystemMsgItem*  msgItem;
		QListWidgetItem*  listItem;
	};

	class SystemMsgPage : public QWidget
	{
		Q_OBJECT

	public:
		SystemMsgPage(QWidget *parent=CNull);
		~SystemMsgPage();
		void InitData();
		static bool isSysPageSelect;
		void dealAddFridenSysMsg(int64 usrId);
	public slots:
		void onDelBtnClicked(int64 msgId);
		void onAgreeClicked(int64 msgId);
		void onIgnoreClicked(int64 msgId);

		void onSerGetAllSysMsg(int err,std::vector< data::SysMsg>& sysMsg);
		void onSerSetSysMsgRead(int err);
		void onSerRemoveSysMsg(int err);
		void onSerRegLastSysMsg(const  data::SysMsg& sysMsg, int count);
		void onSerAddBuddyResp(int err);
		void onSerAddGroupResp(int err);
		void onSerSendMsg(int err,int64 msgtime,int64 msgid);
		void onSerRegSysMsg(const data::SysMsg& sysMsg);
	signals:
		void signalSerGetAllSysMsg(int err,std::vector< data::SysMsg>& sysMsg);
		void signalSerSetSysMsgRead(int err);
		void signalSerRemoveSysMsg(int err);
		void signalSerRegLastSysMsg(const  data::SysMsg& sysMsg, int count);
		void signalSerAddBuddyResp(int err);
		void signalSerAddGroupResp(int err);
		void signalSerSendMsg(int err,int64 msgtime,int64 msgid);
		void signalSerRegSysMsg(const data::SysMsg& sysMsg);
	private:
		void addSysMsgListItem(data::SysMsg sysmsg,int pos=-1);
		void clearData();
		void setSysMsgReaded( const std::vector< data::SysMsg>& sysMsg);
		bool isItemShow(const data::SysMsg& sysMsg);
	   
	private:
		bool m_isGetData;   //标识是否有新的系统消息要拉取
		CSharedPtr<QVBoxLayout>      m_Layout;
		std::map<int64,SysMsgItem>        m_itemMap;
		std::map<int64, data::SysMsg>    m_mapData;
		CSharedPtr<QListWidget>	  m_ptrListWidget;
		ISysMsgMgrControl_ptr			  m_sysmsgcontrol;
		
		data::SysMsg mAddFriendAgreeMsg;
		IChatMgrControl_Ptr mChatCtrl;
	};
}

