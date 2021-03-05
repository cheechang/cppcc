#ifndef ABSTRACTMESSAGEWIDGET_H
#define ABSTRACTMESSAGEWIDGET_H
#include "common/Controlptr.h"
#include "common/Common.h"
#include "speechbubblewidget.h"
#include "MsgItemBase.h"
#include "MyRightMenu.h"
#include <QMap>
#include <QObject>
#include <qstring.h>
namespace data{
	class Msg;
	class Member;
}
class FlexAction;
class AbstractMessageWidget : public SpeechBubbleWidget,public MsgItemBase
{
    Q_OBJECT
public:
    explicit AbstractMessageWidget(QWidget* parent = 0);
    virtual ~AbstractMessageWidget();

    virtual void initialize();
	virtual void SendMsg();
	virtual void ReSendMsg();
	virtual void InitMsg(CSharedPtr<data::Msg>&msg,AbstractMessageWidget*&abstmsgwidget);
	void FillMemberInfo(qint64 memberid,QString&avatar,QString& membername);

	static void SetUserInfo(UserInfo& user);
	static UserInfo GetUserInfo();

	static void SetTargetInfo(TargetInfo& target);
	static TargetInfo GetTargetInfo(qint64& targetId);

	static void  SetMemberList(qint64& targetId,std::vector<CSharedPtr<data::Member>>&memberlist);
	static std::vector<CSharedPtr<data::Member>> GetMemberList(qint64& targetId);

    QList<FlexAction*> actions() const;

	void  setMsg(CSharedPtr<data::Msg>&val);
	void setRightMenuEnabled(bool enable);
	CSharedPtr<data::Msg> msg()const;
	int maxUnReadCount();
	void setMaxUnReadCount(int cnt);
	static bool  isFileExist(QString& url,int type);
	void  update();
	void  RevokeMessage();
signals:
    void shake();
	void sizechanged();
	void SendMsg(CSharedPtr<data::Msg>&msg);
	void downLoadImg(qint64,qint64,std::string&,std::string&,bool);
	void signalSerSendMsg(int,qint64,qint64,qint64);
	void msgStatusChanged(int,qint64);
	void signalGetMemberlist(qint64);
	void signalSerForwardMessage(int,int64,int64);
	void deleteMsg(int64 id);
	void revokeMsg(int64 id);
	void updateMsgTime(qint64 localId,qint64 time);
	void signalSerCloudDisk();
	void signalSerRecallEdit();
	void signalSerMsgTop(data::ZxTopInformation&);
	void signalSerGetTopUser(int, data::UserData&);
	void signalSerGetGroupMem(int code, data::Member& mem,bool isRev);
	void signalChangeMsgStatus(int, int64);
public slots:
	void onChangeMsgStatus(int, int64);
	void onSerSendMsg(int err,qint64 msgtime,qint64 msgid,qint64 uiLocalId);
	void onForwardMessage();
	void onDeleteMessage();
	void onRevokeMessage();
	void onGetForwardMsgToIdResult(int64 toId,int64 msgId);
	void onSerForwardMessage(int code,int64 time,int64 msgId);
	void onMessageStatus();
	void onSaveCloudDisk();
	void onRecallEdit();
	void onMsgTop();
	void onSerGetTopUser(int code, data::UserData&user);
	void onSerGetGroupMem(int code, data::Member& mem,bool isRev);
protected:
    virtual void initializeContextActions();
	void mousePressEvent(QMouseEvent *e);
    void addAction(FlexAction* action);
    void addSeparator();
	bool JudgeIsCanRevokeMsg();
	QString parceSector(QString json);
protected:
	IChatMgrControl_Ptr	m_chatcontrol;
	IContactMgrControl_Ptr m_ContactCtrl;
#ifdef CLOUDDISK_ON
	ICloudDiskControl_ptr m_clouddiskcontrol;
#endif
	MyRightMenu mRightMenu;
	bool mIsSendMsg;
	bool mIsCanRevokeMsg;
	bool mRightMenuEnabled;
	int mMaxUnReadCount;
	static UserInfo	m_user;
private:
	
	static QMap<qint64,TargetInfo>m_targetinfomap;
	static QMap<qint64,std::vector<CSharedPtr<data::Member>>>m_memberlistmap;
	TargetInfo	m_target;
    class AbstractMessageWidgetPrivate* d_ptr;

};

#endif // ABSTRACTMESSAGEWIDGET_H
