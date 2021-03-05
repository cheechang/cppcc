#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include "interface/Defines.h"
#include "data/ChatData.h"
#include "common/Common.h"
#include "common/controlptr.h"
class QVBoxLayout;
class QSplitter;
namespace data{
	class ChatInfo;
	class Msg;
	class MsgStatus;
	class Member;
};
namespace ui{
	class ChatTitle;
	class ChatContentView;
	class ChatEditWidget;
	class GroupAtMessageTip;
	class RecordUI;
	class MessageTopWidget;
	class ChatWidget:public QWidget{
		Q_OBJECT
	public:
		struct ImgInfo{
			QString thumbpath;
			QString binarydata;
			QSize   thumbsize;
		};
		ChatWidget(QWidget *parent = 0);
		~ChatWidget();
		void StartChat(CSharedPtr<data::ChatInfo>&chat);
		void SetMsg(CSharedPtr<data::Msg>&msg);
		void setIsReceipt(CSharedPtr<data::Msg>msg);

		void showGroupAtMsgTip( CSharedPtr<data::Msg>& msg );
		void setTargetInfo(TargetInfo info,bool updateHisMsg=false);
		void SetUserInfo(int64 userId,QString selfAvatar,QString selfName);
		void setSupportStretch(bool isSupportStretch);
		void getHistoryMsg(qint64 targetid,int unreadcount,qint64 msgid,CSharedPtr<data::ChatInfo>chat,bool ishis,bool getMems=false);
		void setCurSelWndId(qint64& targetid);
		void setScreenShotImage(const QString&path);
		int64 targetId();
		void updateGroupMemInfo(const data::Member&mem);
		void setMemberHeadImgUpdate(int64 targetId, const std::string&head);

		void SendSuggestionFile(data::MSGTYPE msgtype,QString msg,std::vector<int64> atlist);
		void ReplyChickFeather(int64 msgId, bool isFeather);
		void DealReplyChickFeather();

		void DelUpFileUi(int64 fileLocalid);

		void SetNotSpeak(bool istrue,int type=0);
		void onSerbtnCloseSession(bool isVisible);
		void setNoMoreState(bool isClicked);
		void getTopMsg();
		void setAtListVisible(bool isVis);
	public slots:
		void onSerGetGroupMem(int code, data::Member& mem);
		void onSerSendisReceiptMsg(int err, int64 msgtime, int64 msgid, CSharedPtr<data::Msg>msg);
		void onSendDelayMsg(int64 time,QString text);
		void onSendDnyMsg(QString fileName);
		void onSendCard(int64 cardId,bool isburn,bool isdelay,bool isreceipt);
		void onSendMsg(QString text,QStringList imagelist,QStringList filelist,std::vector<int64> atlist,bool isburn,bool isdelay,bool isreceipt);
		void onShowGroupAtMsgTip(CSharedPtr<data::Msg> msg);
		void onSerGetUrlInfo(QString text,int code, const std::string& url, const std::string& title, const std::string&imgPath, const std::string&desc);
		void onSetPrivateKey(QString& pPassword);
		void onSerGroupRefreshUpdate(int8, const data::Group&);
		void onSerGetContactInfo();
		void onShakeWinClicked();
		void onShowRecordWin();
		void onRecordResult(QString path,int time);
		void onSerGetUserInfo(int code, data::UserData&user);
		void onSerChickMsgReaded(int64 pmsgid);
		void SetTileContent(int type, int64 MemCount);//type 0:查询获取  1:增加   2:移除或退出
		void onSerGroupMemCountRefresh(int type, int64 pMemCount);
		void onSerSendMsgByType(int type);
		void onSerMoretopMsg();
		void onSerCanceltopMsg();
		void onSerGetMemberInfo(int code, data::Member& member,std::string& content);
		void onHideAtWin();
		void onSerGetTopMsg(int, int32, int32, std::vector<data::ZxTopInformation>&);
		void onSerCancelTopMsg(int code, int32 pageNum, int32 Count, std::vector<data::ZxTopInformation>& ResultTopMsg);
	protected:
		void SendMsg(data::MSGTYPE msgtype, QString msg, std::vector<int64> atlist, bool isBurn = false,bool isreceipt=false);
		bool isWebUrl(QString text);
		virtual void paintEvent(QPaintEvent *event);
		virtual void hideEvent(QHideEvent *);
		virtual void  resizeEvent ( QResizeEvent * event );
		void InitGroupInfo();
		void FeatherMsgDeal(int64 msgid, bool isInsertOrDel);
		//void onSerbtnCloseSession(bool isVisible);
	signals:
		void signalSerGetGroupMem(int code, data::Member& mem);
		void addIsReceiptMsg(int64);
		void signalSerSendisReceiptMsg(int err, int64 msgtime, int64 msgid, CSharedPtr<data::Msg>msg);
		void sendMsgHotKeyUpdate(int);
		void signalShakeWin();
		void openUrl(std::string url);
		void viewBurnMsg(CSharedPtr<data::Msg>& msg);
		void addChatListItem(CSharedPtr<data::ChatInfo>&);
		void startChat(CSharedPtr<data::ChatInfo>&);
		void signalScreenShot(int flag);
		void signalSendImage(const QString);
        void signalSendMsgShot(int key);
		void signalSetSecretIsvisible(bool,bool);
		void signalSerGroupRefreshUpdate(int8, const data::Group&);
		// 传入接收结果回调 _1 错误信息  _2网址  _3标题  _4图片的地址  _5摘要
		void signalSerGetUrlInfo(QString text,int, const std::string&, const std::string&, const std::string&, const std::string&);
		void signalSerGroupMemCountRefresh(int, int64);
		void signalSerGetUserInfo(int, data::UserData&);
		void signalSerbtnCloseSession(bool);
		void signalSerGetTopMsg(int, int32, int32, std::vector<data::ZxTopInformation>&);
		void signalSerCancelTopMsg(int, int32, int32, std::vector<data::ZxTopInformation>&);
		void signalSerGetMemberInfo(int, data::Member&,std::string&);
	private:
		CSharedPtr<ChatTitle> m_chattitle; //标题信息
		CSharedPtr<ChatContentView> m_chatview;//聊天列表框
		CSharedPtr<ChatEditWidget> m_chatedit; //聊天编辑框
		CSharedPtr<RecordUI> m_recordWin;      //音频录音
		CSharedPtr<QVBoxLayout> m_rightlayout;
		QSplitter*  m_splitter;
		TargetInfo  m_target;
		QList<qint64> m_PrivateTargetId;
		int Msgid;
		int64 MemCount;
		int64 mCurrentUserId;
		std::vector<int64> FeatherMsgId;

		bool m_isFirstCreate;
		GroupAtMessageTip* mGroupAtMsgTip;
		IChatMgrControl_Ptr mChatCtrl;
		IGroupMgrControl_Ptr mGroupControl;
		IContactMgrControl_Ptr mContactControl;
		IUserControl_Ptr m_usercontrol;

		MessageTopWidget* m_topMessageWindow;
		QHBoxLayout  *initLocalSearchLayout();
	};
}