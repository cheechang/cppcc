#include "abstractmessagewidget.h"
#include "flexaction.h"
#include "common/UIUtils.h"
#include "data/ChatData.h"
#include "data/GroupData.h"
#include "MsgBubbleConfig.h"
#include "utils/common.h"
#include "common/Controlptr.h"
#include "../ForwardMsgWin.h"
#include "../MsgStatusWin.h"
#include <QDebug>
#include <QDateTime>
#include <QCoreApplication>
#include "log.h"
#include "json.h"
#include <QMessageBox>
extern int gNameSectorOpen;
class AbstractMessageWidgetPrivate
{
public:
	AbstractMessageWidgetPrivate():m_msg(CNull){
	}
	CSharedPtr<data::Msg> m_msg;
    QList<FlexAction* > actions;
};

UserInfo	AbstractMessageWidget::m_user;
QMap<qint64,TargetInfo>	AbstractMessageWidget::m_targetinfomap;
QMap<qint64,std::vector<CSharedPtr<data::Member>>> AbstractMessageWidget::m_memberlistmap;
AbstractMessageWidget::AbstractMessageWidget(QWidget* parent) : SpeechBubbleWidget(parent)
{
    d_ptr = new AbstractMessageWidgetPrivate;
	m_chatcontrol = CHATMGRCONTROL;
	m_ContactCtrl = CONTACTMGRCONTROL;
#ifdef CLOUDDISK_ON
	m_clouddiskcontrol = CLOUDDISKCONTROL;
#endif
	CONNECT_SERVICE(SendMsg(int,qint64,qint64,qint64));
	CONNECT_SERVICE(ForwardMessage(int,int64,int64));
	CONNECT_SERVICE(GetTopUser(int, data::UserData&));
	this->setMouseTracking(true);
	this->installEventFilter(this);
	ui::ForwardMsgWin* pWin = ui::ForwardMsgWin::Instance();
	connect(pWin,SIGNAL(forwardMsgTargetId(int64,int64)),this,SLOT(onGetForwardMsgToIdResult(int64,int64)));
	mRightMenuEnabled = true;
}

AbstractMessageWidget::~AbstractMessageWidget()
{
    delete d_ptr;
}

void AbstractMessageWidget::initialize()
{
    initializeContextActions();
}

int AbstractMessageWidget::maxUnReadCount()
{
	return mMaxUnReadCount;
}

void AbstractMessageWidget::setMaxUnReadCount(int cnt)
{
	mMaxUnReadCount = cnt;
}
void AbstractMessageWidget::InitMsg(CSharedPtr<data::Msg>&msg,AbstractMessageWidget*&abstmsgwidget){
	SpeechBubbleWidget::Direction d;
	QColor bubblecolor;
	QColor bordercolor;
	QString avatar("");
	QString name("");

	m_target = GetTargetInfo(msg->targetId);
	d =msg->isRecvMsg?SpeechBubbleWidget::TopLeft:SpeechBubbleWidget::TopRight;
	if(data::MSG_TYPE_TIP == msg->msgType || data::MSG_TYPE_PICTEXT == msg->msgType) d=SpeechBubbleWidget::Center;
	bubblecolor = msg->isRecvMsg?MsgBubbleConfig::otherBubbleColor():MsgBubbleConfig::selfBubbleColor();
	bordercolor = msg->isRecvMsg?MsgBubbleConfig::othersBorderColor():MsgBubbleConfig::selfBorderColor();
	bool groupNeedGetInfo = false;
	mMaxUnReadCount = msg->maxUnReadCount;
	if ( msg->isGroup)
	{
		IGroupMgrControl_Ptr groupCtrl = GROUPMGRCONTROL;
		if (groupCtrl) {
			data::Member mem;

			bool res = groupCtrl->GetMemberInfo(msg->targetId, msg->fromId, mem);
			if (res) {
				QString extends = QString::fromUtf8(mem.entExtends.value().c_str());
				QString sector = QString::fromUtf8(mem.sector.value().c_str());
				if (sector.isEmpty()) {
					sector = parceSector(extends);
				}
				name = QString::fromUtf8(mem.remark.value().c_str());
				if (!sector.isEmpty() &&(gNameSectorOpen ==1)) {
					name.append("-" + sector);
				}
				//优先从好友缓存取
				data::Contact con;
				m_ContactCtrl->GetContactInfo(msg->fromId, con);
				if (con.id.value() != 0) {
					avatar = transfer(con.thumbAvatar.value().c_str());
				}
				else {
					avatar = transfer(mem.thumbAvatar.value().c_str());
				}
			}
		}
		avatar = msg->isRecvMsg?(avatar.isEmpty()?DEFAULT_AVATAR:avatar):m_user.selfavatar;
		name   =  msg->isRecvMsg?(name.isEmpty()?transfer("群成员"):name):m_user.selfName;
	}
	else{
		avatar = msg->isRecvMsg?m_target.targetAvatar:m_user.selfavatar;
		name   =  msg->isRecvMsg?m_target.targetName:m_user.selfName;
	}
	if (avatar.isEmpty())
	{
		avatar = DEFAULT_AVATAR;
	}
	if (msg->targetId == m_user.selfid && msg->isRecvMsg){
		avatar = ":/base/device";
	}
	if (MSG_SENDING == msg->status)
	{
		msg->targetId = m_target.targetId;
		/*QDateTime test; 
		test.msecsTo(QDateTime::currentDateTime());*/
		
		msg->localId = QDateTime::currentDateTime().toMSecsSinceEpoch();
		msg->deviceType=DEVICE_PC;
		msg->fromId = GetUserInfo().selfid;

		IUserControl_Ptr userCtrl = USERCONTROL;
		int64 svrTime = 0;
		bool ret = false;
		if (userCtrl)
		{
			ret = userCtrl->getServerTimeSync(svrTime);
		}
		svrTime = ret ? svrTime :QDateTime::currentMSecsSinceEpoch();

		msg->time = svrTime;
		setUiLocalId(msg->localId);
		setTargetId(m_target.targetId);
		setMsgTime(msg->time);
		setSendId(msg->fromId);
	}
	mIsSendMsg = !msg->isRecvMsg;
	mIsCanRevokeMsg = true;

	abstmsgwidget->initialize();
	abstmsgwidget->setDirection(d);
	abstmsgwidget->setBrush(bubblecolor);
	abstmsgwidget->setBorderColor(bordercolor);
	abstmsgwidget->setAvatar(avatar);
	abstmsgwidget->setName(name);
	abstmsgwidget->setIsRecv(msg->isRecvMsg);
	abstmsgwidget->setIsDevice(msg->isDeviceMsg);
	abstmsgwidget->setMsgType(msg->msgType);
	abstmsgwidget->setMsgId(msg->msgId);
	abstmsgwidget->setUiLocalId(msg->localId);
	abstmsgwidget->setStatus(msg->status);
	abstmsgwidget->setSendId(msg->fromId);
	abstmsgwidget->setTargetId(msg->targetId);
	abstmsgwidget->setMsgTime(msg->time);
	abstmsgwidget->setSnapeId(msg->snapshotId);

	mRightMenu.init(targetId(),uiLocalId(),msg->time,msg->isRecvMsg);
	mRightMenu.setMenuState(MENU_DEL,true);
	mRightMenu.setMenuState(MENU_TRANSPORT,true);
	if (msg->isGroup)
	{
		mRightMenu.setMenuState(MENU_MSGSTATUS,true);
	}
	connect(&mRightMenu,SIGNAL(signalCtrlDelMenu(qint64,qint64)),this,SLOT(onDeleteMessage()));
	connect(&mRightMenu,SIGNAL(signalCtrlTransportMenu(qint64,qint64)),this,SLOT(onForwardMessage()));
	connect(&mRightMenu,SIGNAL(signalCtrlRecallMenu(qint64,qint64)),this,SLOT(onRevokeMessage()));
	connect(&mRightMenu,SIGNAL(signalCtrlMsgStatusMenu(qint64,qint64)),this,SLOT(onMessageStatus()));
	connect(&mRightMenu, SIGNAL(signalCtrlSaveCloudDiskMenu(qint64, qint64)), this, SLOT(onSaveCloudDisk()));
	connect(&mRightMenu, SIGNAL(signalCtrlRecallEditMenu(qint64, qint64)), this, SLOT(onRecallEdit()));
	connect(&mRightMenu, SIGNAL(siganlCtrMsgTopMenu(qint64, qint64)), this, SLOT(onMsgTop()));
	if (groupNeedGetInfo){
		CONNECT_SERVICE(GetGroupMem(int, data::Member&, bool));
		IGroupMgrControl_Ptr groupCtrl = GROUPMGRCONTROL;
		groupCtrl->getGroupMemberFromNet(msg->targetId, msg->fromId, CBind(&AbstractMessageWidget::signalSerGetGroupMem,
			this, std::placeholders::_1, std::placeholders::_2, msg->isRecvMsg));
	}
}

QString AbstractMessageWidget::parceSector(QString json){
	Json::Value root;
	Json::Reader reader;
	if (reader.parse(json.toStdString(),root)){
		if (root.isArray() && root.size() > 0){
			Json::Value obj = root[0];
			if (json.contains("sector") && obj.isMember("sector")){
				return obj["sector"].asString().c_str();
			}
		}
	}
	return "";
}
void AbstractMessageWidget::onSerGetGroupMem(int code, data::Member& mem,bool isRecv){
	if (!mem.remark.value().empty()){
		QString avatar("");
		QString name("");
		avatar = isRecv ? (mem.thumbAvatar.value().empty() ? DEFAULT_AVATAR : transfer(mem.thumbAvatar.value().c_str())) : m_user.selfavatar;
		name = isRecv ? (mem.remark.value().empty() ? transfer("群成员") : mem.remark.value().c_str()) : m_user.selfName;
		QString extends = QString::fromUtf8(mem.entExtends.value().c_str());
		QString sector = QString::fromUtf8(mem.sector.value().c_str());
		if (sector.isEmpty()){
			sector = parceSector(extends);
		}
		if (!sector.isEmpty() &&(gNameSectorOpen == 1)){
			name.append("-" + sector);
		}
		__super::setAvatar(avatar);
		__super::setName(name);
	}
}

void AbstractMessageWidget::FillMemberInfo(qint64 memberid,QString&avatar,QString& membername){
	std::vector<CSharedPtr<data::Member>> memberlist = GetMemberList(m_target.targetId);
	if(!memberlist.size()){
		emit signalGetMemberlist(m_target.targetId);
		return;
	}
	for (int index=0 ;index<memberlist.size(); ++index)
	{
		if (memberid ==memberlist.at(index)->id.value())
		{
			QString remark = QString::fromUtf8(memberlist.at(index)->remark.value().data());
			QString name  = QString::fromUtf8(memberlist.at(index)->name.value().data());
			QString portrait = QString::fromUtf8(memberlist.at(index)->thumbAvatar.value().data());
			qint64  memberid = memberlist.at(index)->id.value();
			QString sector("");

			membername = remark.isEmpty()?(name.isEmpty()?QString::number(memberid):name):remark;
			if (!sector.isEmpty() &&(gNameSectorOpen == 1))
			{
				membername = membername + "-" + sector;
			}
			
			if (!utils::FileIsExist(portrait.toLocal8Bit().data()))
			{
				avatar = QString(DEFAULT_AVATAR);
			}
			else{
				avatar = portrait;
			}
			break;
		}
		QCoreApplication::processEvents();
	}
}
void AbstractMessageWidget::SendMsg(){
	int64 localId = m_chatcontrol->SendMessage(d_ptr->m_msg,
		CBind(&AbstractMessageWidget::signalSerSendMsg,
					this,
					CPlaceholders  _1,
					CPlaceholders  _2,
					CPlaceholders  _3,
					uiLocalId()));
}
void AbstractMessageWidget::onSerSendMsg(int err,qint64 msgtime,qint64 msgid,qint64 uiLocalId){
	setMsgId(msgid);
	setMsgTime(msgtime);
	emit msgStatusChanged(err,uiLocalId);
	if (err == 0)
	{
		emit updateMsgTime(uiLocalId,msgtime);
		setStatus(MSG_FINISH);
	}else{
		setStatus(MSG_FAILED);
	}
}
void  AbstractMessageWidget::SetMemberList(qint64& targetId, std::vector<CSharedPtr<data::Member>>&memberlist){
	if (!m_memberlistmap.contains(targetId))
	{
		m_memberlistmap.insert(targetId,memberlist);
	}
	else{
		m_memberlistmap[targetId] = memberlist;
	}
}
std::vector<CSharedPtr<data::Member>>AbstractMessageWidget::GetMemberList(qint64& targetId){
	return m_memberlistmap[targetId];
}

void  AbstractMessageWidget::setMsg(CSharedPtr<data::Msg>&val){
	d_ptr->m_msg = val;
}
CSharedPtr<data::Msg> AbstractMessageWidget::msg()const{
	return d_ptr->m_msg;
}

QList<FlexAction*> AbstractMessageWidget::actions() const
{
    return d_ptr->actions;
}
bool AbstractMessageWidget::isFileExist(QString& url,int type){
	bool isexist = false;
	QString path("");
	path = UIUtils::GetDataFullPath(type)+UIUtils::GetPicNameByUrl(url);
	isexist = UIUtils::IsFileExist(path);
	if (isexist)
	{
		url = path;
	}
	return isexist;
}
void AbstractMessageWidget::update(){
	 emit sizechanged();
}

void AbstractMessageWidget::addAction(FlexAction* action)
{
    if (!d_ptr->actions.contains(action))
        d_ptr->actions.append(action);
}

void AbstractMessageWidget::addSeparator()
{
    FlexAction* sep = new FlexAction(this);
    sep->setSeparator(true);
    addAction(sep);
}
void AbstractMessageWidget::SetUserInfo(UserInfo& user){
	m_user = user;
}
UserInfo AbstractMessageWidget::GetUserInfo(){
	return m_user;
}
void AbstractMessageWidget::SetTargetInfo(TargetInfo& target){
	if (!m_targetinfomap.contains(target.targetId))
	{
		m_targetinfomap.insert(target.targetId,target);
	}
	else{
		m_targetinfomap[target.targetId] = target;
	}
}
TargetInfo AbstractMessageWidget::GetTargetInfo(qint64& targetId){
	return m_targetinfomap[targetId];
}

void AbstractMessageWidget::onForwardMessage()
{
	if ( MSG_FAILED != status())
	{
		ui::ForwardMsgWin::Instance()->showWin(msgId());
	}
	
}

void AbstractMessageWidget::onDeleteMessage()
{
	emit deleteMsg(uiLocalId());
}

void AbstractMessageWidget::onGetForwardMsgToIdResult( int64 toId,int64 curMsgId)
{
	if (curMsgId == msgId())
	{
		m_chatcontrol->forwardMessage(targetId(),toId,msgId(),CBind(&AbstractMessageWidget::signalSerForwardMessage,this,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3));
	}
}

void AbstractMessageWidget::onSerForwardMessage( int code,int64 time,int64 msgId )
{
	if(code != 0){
		AddLog(LOG_LEV_ERROR,"forward msg err:%d",code);
		QMessageBox::information(ui::ForwardMsgWin::Instance(),transfer("提示"),transfer("转发消息失败!"));
	}else{
		ui::ForwardMsgWin::Instance()->hide();
	}
}

void AbstractMessageWidget::ReSendMsg()
{
	CSharedPtr<data::Msg> msg = d_ptr->m_msg;
	//msg->msgType = msg->msgType|0x00FF;
	int64 localId = m_chatcontrol->SendMessage(msg,
		CBind(&AbstractMessageWidget::signalSerSendMsg,
		this,
		CPlaceholders  _1,
		CPlaceholders  _2,
		CPlaceholders  _3,
		uiLocalId()));
}

void AbstractMessageWidget::onRevokeMessage()
{
	CSharedPtr<data::Msg> baseMsg = CNull;
	CSharedPtr<data::MsgRevoke> msgRevoke = CMakePtr<data::MsgRevoke>();
	msgRevoke->targetId = targetId();
	msgRevoke->fromId = m_user.selfid;
	msgRevoke->revokeMsgId = msgId();
	msgRevoke->body = m_user.selfName.toUtf8().data();
	IUserControl_Ptr userCtrl = USERCONTROL;
	int64 svrTime = 0;
	bool ret = false;
	if (userCtrl)
	{
		ret = userCtrl->getServerTimeSync(svrTime);
	}
	svrTime = ret ? svrTime :QDateTime::currentMSecsSinceEpoch();
	msgRevoke->time = svrTime;
	baseMsg = msgRevoke;

	Log(LOG_LEV_INFO, "msgbody--------1=%s", m_user.selfName.toLocal8Bit().data());
	Log(LOG_LEV_INFO, "msgbody--------2=%s", QString::fromUtf8(baseMsg->body.c_str()).toLocal8Bit().data());
	int64 localId = m_chatcontrol->SendMessage(baseMsg,
		CBind(&AbstractMessageWidget::signalSerSendMsg,
		this,
		CPlaceholders  _1,
		CPlaceholders  _2,
		CPlaceholders  _3,
		uiLocalId()));
	emit revokeMsg(uiLocalId());
}

void AbstractMessageWidget::initializeContextActions()
{

}

void AbstractMessageWidget::mousePressEvent( QMouseEvent *e )
{

	if (e->button() == Qt::RightButton )
	{

		if (!mRightMenuEnabled)
		{
			mRightMenu.setMenuState(MENU_TRANSPORT,false);
			mRightMenu.setMenuState(MENU_RECALL,false);
			mRightMenu.setMenuState(MENU_DEL,false);
			mRightMenu.setMenuState(MENU_MSGSTATUS,false);
			mRightMenu.setMenuState(MENU_RECALLEDIT,false);
			mRightMenu.show();
			return;
		}

		if (status() == MSG_FINISH || status() == MSG_INIT)
		{
			if (msg() == CNull)
			{
				return;
			}
			bool ret = JudgeIsCanRevokeMsg();
			if ( msg()->isBurn)
			{
				mRightMenu.setMenuState(MENU_RECALL,false);
			}else{
				mRightMenu.setMenuState(MENU_RECALL,ret);
			}
			
			if(msg()->isPrivateMsg == 1 || msg()->isPrivateMsg == 2)
			{
				mRightMenu.setMenuState(MENU_TRANSPORT,false);
				mRightMenu.setMenuState(MENU_MSGSTATUS,false);
			}
		}
#ifdef CLOUD_ENABLED
		if(msg()->msgType == MSG_TYPE_FILE)
		{
			mRightMenu.setMenuState(MENU_SAVECLOUDDISK,true);
		}
#endif
		
		if (msg()->msgType == MSG_TYPE_TEXT)
		{
			IGroupMgrControl_Ptr m_groupcontrol = GROUPMGRCONTROL;
			data::Group groupInfo;
			m_groupcontrol->GetGroupInfo(msg()->targetId, groupInfo);
			data::Member mem;
			m_groupcontrol->GetMemberInfo(msg()->targetId, m_user.selfid,mem);
			if ((mem.memberType.value() == 2 || mem.memberType.value() == 3) && groupInfo.info.value().type.value() == 2)
			{
				mRightMenu.setMenuState(MENU_TOPMSG, true);
			}
			else {
				mRightMenu.setMenuState(MENU_TOPMSG, false);
			}
		}
		else{
			mRightMenu.setMenuState(MENU_TOPMSG, false);
		}
		if (m_user.selfid == sendId() && m_target.chattype == data::GROUP_CHAT) {
			mRightMenu.setMenuState(MENU_MSGSTATUS, true);
		}
		else {
			mRightMenu.setMenuState(MENU_MSGSTATUS, false);
		}
		mRightMenu.show();
	}
}

bool AbstractMessageWidget::JudgeIsCanRevokeMsg()
{
	if (!mIsSendMsg)
	{
		return false;
	}
	if (mIsCanRevokeMsg)
	{
		IUserControl_Ptr userCtrl = USERCONTROL;
		if (userCtrl)
		{
			int64 srvTime  = 0;
			userCtrl->getServerTimeSync(srvTime);
			int64 msgTime = msgTimeMsc();
			if (srvTime - msgTime <MSG_RECALL_VALID_TIME*1000*60)
			{
				return true;
			}else{
				mIsCanRevokeMsg = false;
			}
		}
	}
	return false;
}

void AbstractMessageWidget::setRightMenuEnabled( bool enable )
{
	mRightMenuEnabled = enable;
}

void AbstractMessageWidget::onMessageStatus()
{
	//ui::MsgStatusWin win;
	//win.exec();
	if (m_target.chattype != data::GROUP_CHAT)
	{
		return;
	}
	if (status() == MSG_SENDING)
	{
		//uicontrols::WeMessageBox::showInformation(CNull, FORCE_LOGGINEDOFF_TITLE, TEXT_TIP80);
		return;
	}
	data::SnapshotInfo info;
	info.msgId = msgId();
	info.snapshotId = snapeId();
	static ui::MsgStatusWin* msgWin = ui::MsgStatusWin::Instance();
	connect(msgWin, SIGNAL(signalChangeMsgStatus(int, int64)), this, SLOT(onChangeMsgStatus(int, int64)));
	msgWin->showWin(targetId(), info);
}

void AbstractMessageWidget::onSaveCloudDisk()
{
	emit signalSerCloudDisk();
}

void AbstractMessageWidget::onChangeMsgStatus(int cnt, int64 msgid)
{
	emit signalChangeMsgStatus(cnt, msgid);
}

void AbstractMessageWidget::RevokeMessage()
{
	onRevokeMessage();
}

void AbstractMessageWidget::onRecallEdit()
{
	onRevokeMessage();
	emit signalSerRecallEdit();
}

void AbstractMessageWidget::onMsgTop()
{
	m_chatcontrol->getUserInfo(msg()->fromId, 0, CBind(&AbstractMessageWidget::signalSerGetTopUser, this, CPlaceholders  _1, CPlaceholders  _2));
}

void AbstractMessageWidget::onSerGetTopUser(int code, data::UserData&user)
{
	std::string msector;
	std::string jsoninfo = user.entExtends.value();
	Json::Reader  reader;
	Json::Value root;
	bool ret = reader.parse(jsoninfo, root);
	if (!ret){
		msector = "";
	}else{
		if (root.isArray())
		{
			for (int i = 0; i < root.size(); i++)
			{
				if (root[i]["sector"].isString())
				{
					msector = root[i]["sector"].asString();
				}
			}
		}
	}

	Json::Value obj;
	//解析表情
	std::string content;
	if (m_chatcontrol){
		content = m_chatcontrol->parceEmojiDeal(msg()->body);
	}
	obj["content"] = content;
	obj["name"] = user.name.value().c_str();
	obj["jiebie"] = msector;

	Json::FastWriter fast_writer;
	std::string ContentStr = fast_writer.write(obj);

	data::ZxTopInformation TopInfo;
	int64 mCurrentTime = 0;
	TopInfo.createUserId = m_user.selfid;
	TopInfo.groupId = msg()->targetId;
	TopInfo.topUserId = msg()->fromId;
	TopInfo.topContent = ContentStr;
	TopInfo.status = 1;
	TopInfo.topType = 1;
	TopInfo.msgId = msgId();
	emit signalSerMsgTop(TopInfo);
}

