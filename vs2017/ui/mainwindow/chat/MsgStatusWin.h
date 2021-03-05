#ifndef MSGSTATUSWIN_H
#define MSGSTATUSWIN_H
#include <controls/TWidget.h>
#include <mainwindow/contact/createGroup/BaseWindow.h>
#include <common/Controlptr.h>
#include <data/ChatData.h>
#include <PageSizeDataItem.hpp>

class QVBoxLayout;
class QHBoxLayout;
class QTabWidget;
class QListWidget;
namespace uicontrols{
	class Button;
	class BaseQListWidget;
}
namespace ui{
	class MsgStatusListWidget:public TWidget{
		Q_OBJECT
	public:
		MsgStatusListWidget(QWidget *parent=CNull);
		~MsgStatusListWidget(){}
		void setData(std::vector<MemberPtr>mems);
		void clearData();
	protected slots:
		void onLazyLoadMember();
	protected:
		void addItem();
		void addItem(MemberPtr mem);
		uicontrols::BaseQListWidget*mListWidget;
		PageSizeDataItem<MemberPtr> m_memberpage;
	};
	class MsgStatusWin : public BaseWindow
	{
		Q_OBJECT

	public:
		MsgStatusWin(QWidget *parent=CNull);
		~MsgStatusWin();
		static MsgStatusWin* Instance();
		void showWin(int64 groupId,data::SnapshotInfo info);
	signals:
		void signalSerGetGroupMsgReadState(int, std::map<std::string, std::vector<int64>>&);
		void signalSerSendShortMsg(int, std::map<int64, std::string>);
		void signalSerGetGroupUnreadInfo(int, std::vector<int64>&, std::vector<int64>&,int64);
		void signalSerGetMemberList(int, std::vector<MemberPtr >&);
		void signalChangeMsgStatus(int,int64);
	public slots:
		void onSerSendShortMsg(int code, std::map<int64, std::string>results);
		void onSerGetGroupUnreadInfo(int, std::vector<int64>&ReadIds, std::vector<int64>&unReadIds,int64);
		void onChasing();
		void reqData(int64 groupId,data::SnapshotInfo info);
		void onSerGetMemberList(int code , std::vector<MemberPtr >&mems);
		void onSerGetGroupMsgReadState(int code, std::map<std::string, std::vector<int64>>&states);
	private:
		bool isUnRead(int64 id);
		bool isInRead(int64 id);
		void setListData(std::vector<MemberPtr >&mems);

		QTabWidget* mTabWidget;
		MsgStatusListWidget*mReadMsgListWidget;
		MsgStatusListWidget*mUnReadMsgListWidget;
		uicontrols::Button* mBtnCancel;
		uicontrols::Button* mBtnChasing;//×·Ò»ÏÂ
		IChatMgrControl_Ptr mChatCtrl;
		int64 mGroupId;
		std::vector<int64> mUnReadIds;
		std::vector<int64> mReadIds;
	private:
		static MsgStatusWin* mPInstance;
	};
}

#endif // MSGSTATUSWIN_H
