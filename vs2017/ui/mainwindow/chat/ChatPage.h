#pragma  once
#include <QWidget>
#include <memory>
#include <QMap>
#include <QProcess>
#include "common/controlptr.h"
#include "common/Common.h"
#include "../workbench/AppWebView.h"
namespace data{
	class ChatInfo;
	class MsgStatus;
	class Contact;
	class Group;
}
class QSplitter;
class QHBoxLayout;
class QStackedWidget;
class ScreenShot;
class QSound;

namespace ui{
	class DefaultWidget;
	class ChatWidget;
	class ChatListWidget;
	class SystemMsgPage;
	class GroupInforSettingArea;
	class ChatPage:public QWidget{
		Q_OBJECT
	public:
		enum PAGE_INDEX{
			DEFAULTPAGE,
			CHATPAGE,
			SYSMSGPAGE
		};
		explicit ChatPage(QWidget*parent = CNull);
		virtual ~ChatPage();
		void setSupportStretch(bool isSupportStretch);
		int GetGroupSetInfo(int64 targetid);// 返回值 -1:未开始 0:正常 1:已结束
		bool GetUserInfolevel();
		bool dealMeetNoStartMsg(int64 targetId, bool isGroup);
		void mainWinPosChanged();
	signals:
		void unreadMsgCount(int count);
		void turnPage(int current_page);
		void addChatListItem(CSharedPtr<data::ChatInfo>&chat);
		void signalNotifyTrayFlash(bool flash);
		void signalSerMemberHeadImgUpdateCb(int64 targetId, const std::string&head);
		void signalSerMsgNotify(CSharedPtr<data::Msg>msg);
		void signalSendImage(const QString& path);
		void signalSerRegOperateUserCb(data::AccountInfo&);
		void signalSerOperateBuddyCb(int, const data::Contact&);
		void signalSerGroupRefreshNotify(int8, const data::Group&);
        void signalSendMsgShot(int key);
		void signalSerGrpMemInfoRefreshCb(int64 , const data::Member&);
		void viewBurnMsg(CSharedPtr<data::Msg>& msg);
		void signalShakeWin();
		void sendMsgHotKeyUpdate(int);
		void signalSerCloseSession(int64);
		void signalSerContactHeadImgUpdateCb(int64, const std::string&);
		void signalSerNameSectorExtendedField(int,std::vector<data::EnterpriseDictionary>&);
  public slots:
		void onSerNameSectorExtendedField(int, std::vector<data::EnterpriseDictionary>&);
	    void onSerMemberHeadImgUpdateCb(int64 targetId, const std::string&head);
	    void onOpenUrl(std::string url);
        void onMsgSoundPlay(bool isPlay);
        void onSoundTimeOut();
		void onSendSuggestionMsg(CSharedPtr<data::ChatInfo>&chat, QString& filePath);
		void onStartChat(CSharedPtr<data::ChatInfo>&chat);
		void onRemoveChat(int64 targetId);
		void onSerMsgNotify(CSharedPtr<data::Msg>msg);
		void onScreenShoot(int code, QProcess::ExitStatus status);
		void onScreenShotBtnClicked(int flag);
		void onStartScreenShot();
		void onSerRegOperateUserCb(data::AccountInfo&accountInfo);
		void onSerOperateBuddyCb(int type, const data::Contact& contact);
		void onSerGroupRefreshNotify(int8 type, const data::Group&group);//操作类型 1.添加 2.更新，31.解散 32.移除 33.退出
		void onSerGrpMemInfoRefreshCb(int64 groupId, const data::Member&mems);
        void onStartPlayNotifySound();
		void onSerDelUiFile(int64,int64);
		void onSerByTargetIdChat(int64 targetid);
		bool onSerCheckIsCloseSession(CSharedPtr<data::Msg>msg);
		void onSerContactHeadImgUpdateCb(int64 id, const std::string& head);
		void onAddIsReceiptMsg(int64 targetId);
		void onMainWindowDeactivate();
	private:
		CSharedPtr<ChatListWidget> m_chatlist;
		CSharedPtr<QStackedWidget> m_stack;
		CSharedPtr<DefaultWidget>  m_default;
		CSharedPtr<QVBoxLayout> m_mainlayout;
		CSharedPtr<SystemMsgPage>  m_sysMsgPaget;
 private:
		void addIsReceiptMsg(CSharedPtr<data::Msg>msg);
		void addIsReceiptMsgToUi(int64 targetId);
		qint64 m_cursel;
		CSharedPtr<data::AccountInfo>m_userInfo;
		QMap<int64,CSharedPtr<ChatWidget>> m_chatwnd;
		CSharedPtr<ScreenShot>  m_screenprocess;
		QSplitter*  m_splitter;

        bool                m_bPlaySound;
        QTimer*             m_soundTime; //播放声音的间隔时间Timer
        QSound*             m_soundPlay;
        bool                m_IntervalTime;

		IChatMgrControl_Ptr m_chatcontrol;
		IUserControl_Ptr    m_usercontrol;
		IContactMgrControl_Ptr mContactControl;
		IGroupMgrControl_Ptr mGroupControl;
		AppWebView mAppWebView;
		QHBoxLayout  *initLocalSearchLayout();
		QList<CSharedPtr<ChatWidget>> m_cacheDelWnds;
		QMap<int64, QList<CSharedPtr<data::Msg>>> m_cacheIsReceipt;
	};
}