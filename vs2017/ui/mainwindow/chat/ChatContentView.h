#pragma  once
#include <QWidget>
#include <memory>
#include <QTime>
#include <QMap>
#include "common/Common.h"
#include "common/controlptr.h"
#include "interface/Defines.h"
#include "ChatItemCache.h"
#include <QToolButton>
#include <QThread>

namespace data{
	class MsgStatus;
	class Member;
};
class MsgFactory;
class QGraphicsItem;
class GeneralMessageItem;
class AbstractMessageWidget;
class ChatScene;
class ChatView;
class FlexMessageWidget;
class LoadMsgWidget;
namespace ui{

	class SendMsgFailureWidgetPrivate:public QToolButton
	{
		Q_OBJECT
	public:
		SendMsgFailureWidgetPrivate(GeneralMessageItem*msg=CNull,QWidget*parent=CNull):QToolButton(parent){
			mMsg = msg;
			connect(this,SIGNAL(clicked(bool)),this,SLOT(onClick()));
		}
	signals:
		void clicked(GeneralMessageItem*msg);
	public slots:
		void onClick(){
				emit clicked(mMsg);
			}
	protected:
		GeneralMessageItem*mMsg;
	};
	class UserInfoWindow;
	class UserInfoCommon;
	class UserInfoCommitee;

	class ChatContentView:public QWidget{
		Q_OBJECT
	public:
		enum MessageState { Ok, Processing, Error };
		ChatContentView(QWidget *parent = 0);
		~ChatContentView();
		void clear();
		void setGetMemsStatus(bool isGetMems);
		void setChatType(int ChatType);
		void setUserInfo(UserInfo&user);
		UserInfo getUserInfo()const;
		void setTargetInfo(TargetInfo& target,bool updateHisMsg=false);
		void setBackgroundImage(const QPixmap& pixmap);
		QPixmap backgroundImage() const;
		void SetIsHistoryMsg(bool ishis);
		void setNomoreData();
		void addMsg(CSharedPtr<data::Msg>&msg);
		void getMemberList(qint64 targetid);
		void getHistoryMsg(qint64 targetid,int unreadcount,qint64 msgid,CSharedPtr<data::ChatInfo>chat,bool ishis);
		void setCurSelWndId(qint64& targetid);
		void useByCombineMsgWin();
		void updateMsgItemNameAndAvatar(QMap<int64,data::UserData>mapData);
		void DelUpfileUi(int64 Uilocalid);
		void setNomoreState(bool isClicked);
		void settopMsgCount(int topmsgNum);
		void setMemberHeadImgUpdate(int64 userid, const std::string&head,QString name="");
		void addNotifyMsg(CSharedPtr<data::Msg>&msg);
	signals:
		void signalSerGetGroupMem(int code, data::Member& mem,QString oldAvatar);
		void signalSerGetBatchMemberByID(int, std::vector<CSharedPtr<data::Member> >&);
		void addIsReceiptMsg(int64);
		void noticeInputEditFocus();
		void downLoadImg(int64,int64,std::string&,std::string&,bool);
		void signalSerSendMsg();
		void signalSerGetGroupMemberList(int,std::vector<CSharedPtr<data::Member>>&,qint64);
		void signalSerGetMessages(int,int64,std::vector<CSharedPtr<data::Msg>>&,int64,int,CSharedPtr<data::ChatInfo>,bool);
		void addChatListItem(CSharedPtr<data::ChatInfo>&);
		void groupAtMessageTip(CSharedPtr<data::Msg>);
		void signalSerGetAppInfo(int, data::UserData&);
		void signalSerDeleteMsgById(int);
		void messageAvatarClicked();
		void startChat(CSharedPtr<data::ChatInfo>&);
		void viewBurnMsg(CSharedPtr<data::Msg>& msg);
		void signalSerGetDecryptMsgs(int , int64 , std::vector<CSharedPtr<data::Msg>>& );
		void openUrl(std::string);
		void signalSerSearchGetMessage(int, int64, std::vector<CSharedPtr<data::Msg>>&);
		void signalSerSearchSendedGetMessage(int code, int64 targetid, std::vector<CSharedPtr<data::Msg>>& msgs);
		void signalSerMsgReaded(int64);
		void signalSerRecallEdit(QString&);
		void signalSerGetUserInfo(int, data::UserData&, int64 id,QString name, QString avatar);
		void signalSerMsgTop(data::ZxTopInformation&);
		void signalSerCancelMsgTop();
		void signalSercppccTopInfo(int, const std::string&, data::ZxTopInformation&);
		void signalSerDeleteMsg(int);
		void hideAtWin();
		void signalSerGetGroupMsgUnreadCounter(int64, int, std::vector<data::MsgUnreadCounter>&);
		void signalSerGetContractMaxReadId(int64, std::vector<MsgDataPtr>&, int, int64);
	private slots:
		void onSerGetGroupMsgUnreadCounter(int64 groupId, int code, std::vector<data::MsgUnreadCounter>& counters);
		void onSerGetContractMaxReadId(int64 targetId, std::vector<MsgDataPtr>& msgs, int code, int64 maxMsgId);
		void onSerGetGroupMem(int code, data::Member& mem, QString oldAvatar);
		void onSerSearchGetMessage(int code, int64 targetid, std::vector<CSharedPtr<data::Msg>>& msgs);
		void onSerSearchSendedGetMessage(int code, int64 targetid, std::vector<CSharedPtr<data::Msg>>& msgs);
		void onRevokeMsgItem(int64 id);
		void onRemoveMsgItem(int64 id);
		void onEventFiltered(QEvent* event);
		void onSizeChanged();
		void onSerGetGroupMemberList(int err,std::vector<CSharedPtr<data::Member>>&memberlist,qint64 targetid);
		void onSerGetMessages(int err,int64 chatid,std::vector<CSharedPtr<data::Msg>>&msglist,int64 targetid,int unreadcount,CSharedPtr<data::ChatInfo>chat,bool ishisflag);
		void onGetHistoryMsg();
		void onMsgStatusChanged(int err,qint64 uilocalid);
		void onGetMemberlist(qint64 targetid);
		void onSerGetAppInfo(int code, data::UserData& data);
		void onReSendMsgClicked(GeneralMessageItem*msg);
		void onSerGetDecryptMsgs(int Rcode, int64 DecryptMsgId, std::vector<CSharedPtr<data::Msg>>& DecryMsgList);
		void onDecryptMsg(QString&);
		void onUpdateSendMsgTime(qint64 localId,qint64 time);
		void onSerDeleteMsgById(int code);
		void onShowUserInfoWidget(int64 id, QString name, QString avatar);
		void onSerGetUserInfo(int, data::UserData&, int64 id,QString name, QString avatar);
		void onSerTopMsginfo(data::ZxTopInformation& topInfoMsg);
		void onSercppccTopInfo(int code, const std::string& strError, data::ZxTopInformation&);
		void onSerHistoryChat();
		void onSerDeleteMsg(int code);
		void onSerGetBatchMemberByID(int code, std::vector<CSharedPtr<data::Member> >&mems);
		void onChangeMsgStatus(int cnt, int64 msgid);
	private:
		void setGroupMsgStatusTip(int cnt, int maxCunt,FlexMessageWidget* msgWidget);
		void animateVerScrollBar(int start, int end);
		void flashMessageBorderWidth(AbstractMessageWidget* bubbleWidget);
		void flashMessageBorderColor(AbstractMessageWidget* bubbleWidget);
		void addMessageItem(FlexMessageWidget*&message, bool alignLeft = true);
		void addMsgTime(AbstractMessageWidget*&abmsg);
		void layoutMessageIndicators();
		void getAppInfo(qint64 targetid);
		int64 removeMsgFromUI(int64 id);
		void InsertMsgToUI(int64,CSharedPtr<data::Msg>&);
		void ResetChickFeather(CSharedPtr<data::Msg>&msg, int64 type);
		void DeleteMsg(std::vector<int64> msgIds);

		void handleHistoryMsgStatus(std::vector<MsgDataPtr>&msglist);
		void handleMsgStatusMsg(MsgDataPtr&msg);
	protected:
		int burnTime( QString text );
		void startBurnMsgTimer( GeneralMessageItem* genMsg );
		void resizeEvent(QResizeEvent* evt);
		bool event(QEvent *event);
		void adjustSceneHeight();
		void layoutMessageItems();
		void scrollToBottom();
		void scrollToTop();
		void layoutBackgroundImage();
		void updateSceneRect();
		void setMessageState(GeneralMessageItem* msgItem, MessageState state);
		void clearMessageState(GeneralMessageItem *msgItem);
		void createLoadIndicator();
		void layoutLoadMessageIndicator();
		void updateMsgItemAvatar(std::vector<CSharedPtr<data::Member>>&memberlist);
		void SetMsgs(std::vector<CSharedPtr<data::Msg>>&msglist,bool ishisflag=false);
		void DealEraserMsg(CSharedPtr<data::Msg>& msg);
		virtual void paintEvent(QPaintEvent *event);
	private:
		int m_messageCount;
		int m_messageHeight;
		int m_hismessageHeight;
		int m_chattype;
		bool m_ishistory;
		UserInfo m_user;
		MsgItemInfo m_msgitem;
		MediaMsgItemInfo m_msgmediaitem;
		CSharedPtr<ChatScene> m_scene;
		CSharedPtr<ChatView> m_graphicsView;
		CSharedPtr<LoadMsgWidget> m_loading;
		CSharedPtr<UserInfoWindow> m_pUserInfoWidget;
		CSharedPtr<UserInfoCommon> m_pUserInfoCommomWidget;
		CSharedPtr<UserInfoCommitee> m_pUserInfoCommiteeWidget;
		ChatItemCache m_cache;
		QMap<GeneralMessageItem*, QGraphicsItem*> m_messageIndicatorMap;
		QMap<int64,QGraphicsItem*>mMapTimeItems;
	private:
		int64 m_cursel;
		int64 m_firstmsgid;
		bool  m_isFirstGetMsg;
		bool  m_isStartChat;
		std::vector<int64> DecryptMsgIdList;
		QMap<int64,int64> mMapPrivateMsgs;
		QMap<int64, int64> m_CacheChickFeather;
		CSharedPtr<MsgFactory> m_factory;
		IUserControl_Ptr			m_userControl;
		IAuthControl_Ptr			m_authControl;
		IChatMgrControl_Ptr			m_chatcontrol;
		IGroupMgrControl_Ptr		m_groupcontrol;
		bool mUseByCombineMsgWin;
		std::map<int64, int64> m_SendLocalidUiMap;
		data::ChatType m_chatType;
		int m_topMsgTallNum;
		bool m_needGetMems;
		data::AccountInfo m_acountInfo;
		int mGroupType;
	};
}