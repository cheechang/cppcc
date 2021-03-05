#include "ChatWidget.h"
#include "ChatTilte.h"
#include "ChatContentView.h"
#include "ChatEditWidget.h"
#include <QLayout>
#include "data/ChatData.h"
#include "common/Connect.h"
#include <QCoreApplication>
#include <QSplitter>
#include <QDir>
#include <QBuffer>
#include <log.h>
#include <QPainter>
#include "common/Controlptr.h"
#include <QDateTime>
#include "GroupAtMessageTip.h"
#include "bubble/abstractmessagewidget.h"
#include <json.h>
#include "RecordUI.h"
#include "MessageTopWidget.h"
#include "DelayMsgDateWin.h"
namespace ui{
	ChatWidget::ChatWidget(QWidget *parent):QWidget(parent)
	,m_chattitle(CNull),m_chatview(CNull),m_chatedit(CNull),m_rightlayout(CNull),
	m_splitter(CNull), mGroupAtMsgTip(CNull), m_topMessageWindow(CNull)
	, MemCount(0), mCurrentUserId(0), m_isFirstCreate(false){
		m_chattitle = CMakePtr<ChatTitle>(this);
		m_chatview  = CMakePtr<ChatContentView>(this);
		m_chatedit  = CMakePtr<ChatEditWidget>();
		m_splitter  =  new QSplitter(Qt::Vertical,this);

		m_recordWin = std::make_shared<RecordUI>(this);
		m_recordWin->setVisible(false);
		m_recordWin->setFixedHeight(RECORD_HEIGTH);
		CONNECT_SERVICE(GetMemberInfo(int, data::Member&,std::string&));
		CONNECT_SERVICE(SendisReceiptMsg(int, int64, int64, CSharedPtr<data::Msg>));
		CONNECT_SUBCTRL(m_chatedit,SendCard(int64,bool,bool,bool));
		CONNECT_SUBCTRL(m_chatedit,SendMsg(QString,QStringList,QStringList,std::vector<int64>,bool,bool,bool));
		CONNECT_SERVICE(GetTopMsg(int, int32, int32, std::vector<data::ZxTopInformation>&));
		CONNECT_SERVICE(CancelTopMsg(int, int32, int32, std::vector<data::ZxTopInformation>&));
		connect(this,SIGNAL(signalSendImage(const QString)),m_chatedit.get(),SLOT(onSendImage(const QString)));
		connect(this,SIGNAL(sendMsgHotKeyUpdate(int)),m_chatedit.get(),SLOT(onSendMsgHotKeyUpdate(int)));
        connect(this,SIGNAL(signalSendMsgShot(int)),m_chatedit.get(),SIGNAL(signalSendMsgShot(int)));
		connect(m_chatview.get(),SIGNAL(openUrl(std::string)),this,SIGNAL(openUrl(std::string)));
		connect(m_chatedit.get(),SIGNAL(openUrl(std::string)),this,SIGNAL(openUrl(std::string)));
		connect(m_recordWin.get(),SIGNAL(signalRecordResult(QString,int)),this,SLOT(onRecordResult(QString,int)));
		connect(m_recordWin.get(),SIGNAL(signalStopRecord()),m_chatedit.get(),SLOT(onStopRecord()));
		connect(m_chatedit.get(),SIGNAL(showRecordWin()),this,SLOT(onShowRecordWin()));
		connect(m_chatview.get(),SIGNAL(noticeInputEditFocus()),
			m_chatedit.get(),SLOT(onNoticeInputEditFocus()));

		connect(m_chatview.get(), SIGNAL(addIsReceiptMsg(int64)),
			this, SIGNAL(addIsReceiptMsg(int64)));

		connect(m_chatview.get(),SIGNAL(signalSerRecallEdit(QString&)),
			m_chatedit.get(),SLOT(onSerRecallEdit(QString&)));

		connect(m_chatview.get(), SIGNAL(signalSerMsgTop(data::ZxTopInformation&)),
			m_chattitle.get(), SLOT(onSerMsgTop(data::ZxTopInformation&)));

		connect(m_chatview.get(), SIGNAL(signalSerCancelMsgTop()),
			this, SLOT(onSerCanceltopMsg()));

		connect(m_chattitle.get(), SIGNAL(signalSerMoretopMsg()),this, SLOT(onSerMoretopMsg()));
		connect(m_chattitle.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));

		connect(this,SIGNAL(signalSerbtnCloseSession(bool)), m_chatedit.get(),SIGNAL(signalSerbtnCloseSession(bool)));
		
		connect(m_chatedit.get(), SIGNAL(signalSerbtnChatHis()), m_chatview.get(), SLOT(onSerHistoryChat()));
		

		connect(m_chatview.get(), SIGNAL(signalSerMsgReaded(int64)),this, SLOT(onSerChickMsgReaded(int64)));

		connect(m_chatview.get(),SIGNAL(viewBurnMsg(CSharedPtr<data::Msg>&)),
			this,SIGNAL(viewBurnMsg(CSharedPtr<data::Msg>&)));
		connect(m_chatview.get(), SIGNAL(hideAtWin()), this, SLOT(onHideAtWin()));
		connect(m_chatview.get(),SIGNAL(addChatListItem(CSharedPtr<data::ChatInfo>&)),
			this,SIGNAL(addChatListItem(CSharedPtr<data::ChatInfo>&)));
		connect(m_chatedit.get(),SIGNAL(signalScreenShot(int)),this,SIGNAL(signalScreenShot(int)));
		connect(m_chatedit.get(),SIGNAL(signalSetPrivateKey(QString&)), this, SLOT(onSetPrivateKey(QString&)));
		connect(m_chatview.get(),SIGNAL(groupAtMessageTip(CSharedPtr<data::Msg>)),
			this,SLOT(onShowGroupAtMsgTip(CSharedPtr<data::Msg>)));
		connect(m_chatview.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
			this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_chatedit.get(),SIGNAL(sendDnyMsg(QString)),this,SLOT(onSendDnyMsg(QString)));
		connect(m_chatedit.get(),SIGNAL(signalShakeWin()),this,SLOT(onShakeWinClicked()));
		connect(this, SIGNAL(signalSetSecretIsvisible(bool,bool)), m_chatedit.get(),SIGNAL(signalSetSecretIsvisible(bool,bool)));
		connect(m_chatedit.get(),SIGNAL(signalSerCloseSession(int)),this,SLOT(onSerSendMsgByType(int)));
		m_chattitle->setFixedHeight(40);
	
		m_splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);  
		m_splitter->addWidget(m_chatview.get());
		m_splitter->addWidget(m_chatedit.get());
		m_splitter->setChildrenCollapsible(false);
		m_splitter->setOpaqueResize(true);
		QList<int> list_src;
		list_src.append(420);
		list_src.append(APP_MENU_HEIGHT);
		m_splitter->setSizes(list_src);
		m_splitter->setHandleWidth(2);
		m_splitter->setStyleSheet("QSplitter:handle{background:transparent;}");
		m_splitter->handle(1)->setCursor(Qt::SizeVerCursor);
		m_splitter->setContentsMargins(0,0,0,0);

		//群@
		mGroupAtMsgTip = new GroupAtMessageTip(this);
		mGroupAtMsgTip->setMinimumSize(600, 24);         ////
		mGroupAtMsgTip->setMaximumHeight(26);
		mGroupAtMsgTip->move(0,40);
		mGroupAtMsgTip->setObjectName("GroupAtMsgTip");
		mGroupAtMsgTip->hide();

		m_rightlayout = CMakePtr<QVBoxLayout>(this);
		m_rightlayout->addWidget(m_chattitle.get());
		m_rightlayout->addWidget(m_splitter);
		m_rightlayout->setContentsMargins(0,0,0,0);
		m_rightlayout->setSpacing(0);

		setLayout(m_rightlayout.get());

		mContactControl = CONTACTMGRCONTROL;
		mChatCtrl = CHATMGRCONTROL;
		CONNECT_SERVICE(GetUserInfo(int, data::UserData&));
		CONNECT_SERVICE(GetUrlInfo(QString,int, const std::string&, const std::string&, const std::string&, const std::string&));
		
		mGroupControl = GROUPMGRCONTROL;
		if (CNull != mGroupControl)
		{
			CONNECT_SERVICE(GetGroupMem(int, data::Member&));
			CONNECT_SERVICE(GroupRefreshUpdate(int8, const data::Group&));
			mGroupControl->RegGroupRefreshCb(CBind(&ChatWidget::signalSerGroupRefreshUpdate,
				this,CPlaceholders  _1,CPlaceholders  _2));		
		}

		m_usercontrol = USERCONTROL;
		if(m_usercontrol)
		{
			CSharedPtr<data::AccountInfo> tuserinfo;
			tuserinfo = m_usercontrol->GetAccountInfo();			
			mCurrentUserId = tuserinfo->id.value();
		}		
	}
	ChatWidget::~ChatWidget(){
		if ( CNull != m_splitter)
		{
			m_splitter->deleteLater();
		}
	}

	void ChatWidget::onHideAtWin()
	{
		setAtListVisible(false);
	}

	void ChatWidget::onSerGetGroupMem(int code, data::Member& memInfo)
	{
		Log(LOG_LEV_INFO, LOG_FILE,"code:%d", code);
		if (!m_topMessageWindow)
			m_topMessageWindow = new MessageTopWidget(this);

		if (memInfo.memberType.value() == 3 || memInfo.memberType.value() == 2) {
			m_topMessageWindow->setEnableCancelTop(true);
		}
		else {
			m_topMessageWindow->setEnableCancelTop(false);
		}
		m_isFirstCreate = true;
		onSerCanceltopMsg();
	}

	void ChatWidget::getTopMsg()
	{
		LOG_METHOD("ChatWidget::getTopMsg()",LOG_FILE);
		if (m_target.chattype != data::GROUP_CHAT)
		{
			m_chattitle->setTopMsgVisible(false);
			return;
		}
		Log(LOG_LEV_INFO, LOG_FILE, "groupId:%lld,userid:%lld", m_target.targetId, mCurrentUserId);
		mGroupControl->getGroupMemberFromNet(m_target.targetId, mCurrentUserId,
			CBind(&ChatWidget::signalSerGetGroupMem,this,CPlaceholders _1,CPlaceholders _2));
		/*data::Member memInfo;
		mGroupControl->GetMemberInfo(m_target.targetId, mCurrentUserId, memInfo);
		if (!m_topMessageWindow)
			m_topMessageWindow = new MessageTopWidget(this);

		if (memInfo.memberType.value() == 3){
			m_topMessageWindow->setEnableCancelTop(true);
		}
		else{
			m_topMessageWindow->setEnableCancelTop(false);
		}
		m_isFirstCreate = true;
		onSerCanceltopMsg();*/
	}

	void ChatWidget::onSetPrivateKey(QString& pPassword)
	{
		if(pPassword.isEmpty())
		{
			for(int i =0; i<m_PrivateTargetId.size(); i++)
			{
					if(m_PrivateTargetId.at(i) == m_target.targetId)
					{
						m_PrivateTargetId.removeAt(i);
						break;
					}
			}
		}
		else
		{
			m_PrivateTargetId.append(m_target.targetId);	
		}
		mChatCtrl->setPrivateKey(m_target.targetId, pPassword.toStdString());
	}

	void ChatWidget::StartChat(CSharedPtr<data::ChatInfo>&chat){
		LOG_METHOD("ChatWidget::StartChat",LOG_FILE);
		QString avatar = QString::fromStdString(chat->avatar);
		m_target.targetId = chat->targetid;
		m_target.chattype = chat->chatType;
		if (m_target.chattype != data::GROUP_CHAT && m_target.targetAvatar.isEmpty())
		{
			if (mChatCtrl)
			{
				mChatCtrl->getUserInfo(m_target.targetId,0,CBind(&ChatWidget::signalSerGetUserInfo,this,CPlaceholders _1,CPlaceholders _2));
			}
		}
		m_target.targetName = QString::fromStdString(chat->name);
		m_target.targetAvatar = avatar.isEmpty()?(data::APP_CHAT ==chat->chatType||data::ENT_CHAT==chat->chatType||data::APPLICATION_CHAT==chat->chatType?QString(DEFAULT_APP):QString(DEFAULT_AVATAR)):avatar;
		if(chat->targetid == mCurrentUserId)
		{
			m_target.targetName = QString(transfer("我的设备"));
		}
		///m_chattitle->SetTitleText(m_target.targetName,m_target.targetAvatar);  2019-5-26
		m_chattitle->SetTargetInfo(m_target);// .targetName, m_target.targetAvatar);
		if (m_target.chattype != data::GROUP_CHAT && m_target.chattype != data::APP_CHAT && m_target.chattype != data::ENT_CHAT && m_target.chattype != data::APPLICATION_CHAT )
		{
			bool isNotBuddy = false;
			isNotBuddy = !mContactControl->ContactIsBuddy(m_target.targetId);
			if (chat->targetid == mCurrentUserId)
			{
				isNotBuddy = false;
			}
			m_chattitle->showAddBtn(m_target.targetId,isNotBuddy);
		}
		m_chatview->setTargetInfo(m_target);
		if (data::GROUP_CHAT == chat->chatType)
		{
			//m_chatview->getMemberList(m_target.targetId); //2019-7-01
		}
		m_chatedit->setTargetInfo(m_target);
		if(mGroupControl)
		{
			CONNECT_SERVICE(GroupMemCountRefresh(int,int64));
			mGroupControl->SetGroupMemCountCb(m_target.targetId,std::bind(&ChatWidget::signalSerGroupMemCountRefresh, this, std::placeholders::_1,std::placeholders::_2));
		}
		//InitGroupInfo();
		onSerGetContactInfo();

		if (m_target.chattype == data::GROUP_CHAT){
			m_chatedit->setHistoryMsgVisible(true);
		}else{
			m_chatedit->setHistoryMsgVisible(false);
		}
		
	}
	void ChatWidget::SetUserInfo(int64 userId,QString selfAvatar,QString selfName){
		UserInfo info;
		info.selfavatar = selfAvatar;
		info.selfid = userId;
		info.selfName = selfName;
		m_chatview->setUserInfo(info);
	}
	void ChatWidget::onSendMsg(QString text,QStringList imagelist,QStringList filelist,std::vector<int64>atlist,bool isburn,bool isdelay,bool isreceipt){
		if (!text.isEmpty()&&  QString(" ") != text)
		{
			if (isWebUrl(text))
			{
				std::string path="";
				mChatCtrl->getUrlInfo(text.toStdString(),path,CBind(&ChatWidget::signalSerGetUrlInfo,this,text,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3,CPlaceholders _4,CPlaceholders _5));
				return;
			}else{
				if (isdelay)
				{
					DelayMsgDateWin win(text);
					connect(&win,SIGNAL(signalSendDelayMsg(int64,QString)),this,SLOT(onSendDelayMsg(int64,QString)));
					win.ShowDelayWin();
				}else{
					SendMsg(data::MSG_TYPE_TEXT, text, atlist, isburn, isreceipt);
				}
				
			}
		}
		for ( size_t imgindex=0; imgindex<imagelist.size();++imgindex)
		{
			QString path = imagelist.at(imgindex);
			SendMsg(data::MSG_TYPE_IMG,path,atlist,isburn);
		}
		for ( size_t fileindex=0; fileindex<filelist.size();++fileindex)
		{
			QString path = filelist.at(fileindex);
			SendMsg(data::MSG_TYPE_FILE,path,atlist);
		}
	}
	void ChatWidget::SendSuggestionFile(data::MSGTYPE msgtype,QString msg,std::vector<int64> atlist)
	{
		SendMsg(data::MSG_TYPE_FILE,msg,atlist);
	}
	void ChatWidget::SendMsg(data::MSGTYPE msgtype, QString msg, std::vector<int64> atlist, bool isBurn, bool isreceipt){
		CSharedPtr<data::Msg> msgptr =CNull;
		switch(msgtype){
		case data::MSG_TYPE_TEXT:{
			CSharedPtr<data::MsgText> msgtext = CMakePtr<data::MsgText>();
			msgtext->body = msg.toUtf8().data();
			msgtext->relatedUsers = atlist;
			msgtext->isBurn = isBurn;
			msgtext->isReceipt = isreceipt;
			msgtext->isReceiptAll = isreceipt;
			if (m_target.chattype == 2 && isreceipt){
				msgtext->relatedUsers.push_back(m_target.targetId);
			}
			msgptr = msgtext;
			
			break;
			}
		case data::MSG_TYPE_WEB:{
			CSharedPtr<data::MsgWeb> msgweb = CMakePtr<data::MsgWeb>();
			msgweb->body = msg.toUtf8().data();
			msgweb->relatedUsers = atlist;
			msgptr = msgweb;
			break;
			}
		case data::MSG_TYPE_IMG:{
			CSharedPtr<data::MsgImg> msgImg = CMakePtr<data::MsgImg>();
			msgImg->mainPath = msg.toUtf8().data();
			msgImg->isBurn = isBurn;
			msgptr = msgImg;
			break;
		}
		//case data::MSG_TYPE_CARD:{
		//	CSharedPtr<data::MsgCard> msgCard = CMakePtr<data::MsgCard>();
		//	msgCard->isBurn = isBurn;
		//	msgptr = msgCard;
		//}
		case data::MSG_TYPE_FILE:{
			CSharedPtr<data::MsgFile> msgFile = CMakePtr<data::MsgFile>();
			msgFile->filePath = msg.toUtf8().data();
			msgptr = msgFile;
			break;
		}
		case data::MSG_TYPE_TIP:{
			CSharedPtr<data::MsgTip> msgtip = CMakePtr<data::MsgTip>();
			msgtip->tipType = data::MSG_TYPE_TIP_READED;
			msgptr = msgtip;
			msgptr->relatedMsgId = Msgid;
			msgptr->msgType = data::MSG_TYPE_TIP;
			msgptr->isFeather = data::MSG_TYPE_TIP_READED;
			msgptr->isPrivateMsg = 0;
			break;
		}
	}
		msgptr->targetId = m_target.targetId;
		msgptr->status = MSG_SENDING;
		if (m_target.chattype == data::GROUP_CHAT)
		{
			msgptr->isGroup = true;
		}

		if(msgtype == data::MSG_TYPE_TIP)
		{
			//mChatCtrl->SendMessage(msgptr, NULL);
			return ;
		}

		if(m_PrivateTargetId.contains(msgptr->targetId))
		{
			msgptr->isPrivateMsg = 2;
		}
		else
		{
			msgptr->isPrivateMsg = 0;
		}
		m_chatview->addMsg(msgptr);
	}
	//接收消息
	void ChatWidget::SetMsg(CSharedPtr<data::Msg>&msg){
		if (CNull == msg)return;

		showGroupAtMsgTip(msg);
		if(msg->isFeather == 1)
			FeatherMsgDeal(msg->msgId, true);

		m_chatview->addNotifyMsg(msg);
	}

	void ChatWidget::setIsReceipt(CSharedPtr<data::Msg>msg){
		CSharedPtr<data::Msg> inMsg = CNull;
		CSharedPtr<data::MsgTip> msgText = CMakePtr<data::MsgTip>();
		msgText->targetId = m_target.targetId;
		msgText->body = "";
		msgText->localId = QDateTime::currentMSecsSinceEpoch();
		msgText->time = QDateTime::currentMSecsSinceEpoch();
		msgText->tipTime = msgText->time;
		msgText->tipType = 4;
		msgText->operType = 1 ;
		if (m_target.chattype == 2){
			data::Member mem;
			mGroupControl->GetMemberInfo(m_target.targetId,msg->fromId,mem);
			msgText->userInfo = mem.remark.value();
		}
		else{
			msgText->userInfo = m_target.targetName.toUtf8().data();
		}
		CSharedPtr<data::AccountInfo> act = m_usercontrol->GetAccountInfo();
		msgText->operUser = act->name.value();
		msgText->fromId = act->id.value();
		inMsg = msgText;
		if (mChatCtrl)
		{
			mChatCtrl->SendMessage(inMsg, CBind(&ChatWidget::signalSerSendisReceiptMsg, this, CPlaceholders _1, CPlaceholders _2, CPlaceholders _3,inMsg));
		}
	}

	void ChatWidget::onSerSendisReceiptMsg(int err, int64 msgtime, int64 msgid, CSharedPtr<data::Msg>msg)
	{
		if (err == 0){
			msg->msgId = msgid;
			msg->time = msgtime;
			m_chatview->addMsg(msg);
		}
	}

	void ChatWidget::setSupportStretch(bool isSupportStretch){
		this->setMouseTracking(isSupportStretch);
	}
	void ChatWidget::getHistoryMsg(qint64 targetid, int unreadcount, qint64 msgid, CSharedPtr<data::ChatInfo>chat, bool ishis, bool getMems){
		m_chatview->setGetMemsStatus(true);
		m_chatview->getHistoryMsg(targetid, unreadcount, msgid, chat, ishis);
	}
	void ChatWidget::setCurSelWndId(qint64& targetid){
		m_chatview->setCurSelWndId(targetid);
	}
	void ChatWidget::setScreenShotImage(const QString&path){
		emit signalSendImage(path);
	}

	void ChatWidget::showGroupAtMsgTip( CSharedPtr<data::Msg>& msg )
	{
		if(!msg->isGroup ||msg->relatedUsers.size()<=0){
			return;
		}
		IUserControl_Ptr userCtrl = USERCONTROL;
		CSharedPtr<data::AccountInfo> account = userCtrl->GetAccountInfo();

		bool isShowAtTip =false;
		for (int i=0;i< msg->relatedUsers.size();++i)
		{
			if((msg->relatedUsers.at(i) == account->id.value())||(msg->relatedUsers.at(i) == m_target.targetId)){
				isShowAtTip = true;
				break;
			}
		}
		if (msg->isGroup &&isShowAtTip)
		{
			data::Member member;
			if (!mGroupControl->GetMemberInfo(msg->targetId, msg->fromId, member))
			{
				mGroupControl->getGroupMemberFromNet(msg->targetId, msg->fromId, CBind(&ChatWidget::signalSerGetMemberInfo,this,CPlaceholders  _1,CPlaceholders  _2,msg->body));
				return;
			}
			QString name = QString::fromUtf8(member.remark.value().c_str());
			if (name.isEmpty()){
				name = QString::fromUtf8(member.name.value().c_str());
			}
			QString msgText = QString::fromUtf8(msg->body.c_str());
			mGroupAtMsgTip->setData(transfer(member.thumbAvatar.value().c_str()), name + ":" + msgText);
			mGroupAtMsgTip->show();
		}
	}

	void ChatWidget::onSerGetMemberInfo(int code, data::Member& member, std::string& content)
	{
		BEGIN;
		if (code != 0)
		{
			Log(LOG_LEV_ERROR, LOG_FILE, "ChatWidget::onSerGetMemberInfo code=%d", code);
			return;
		}
		
		QString name = QString::fromUtf8(member.remark.value().c_str());
		if (name.isEmpty()){
			name = QString::fromUtf8(member.name.value().c_str());
		}
		QString msgText = QString::fromUtf8(content.c_str());
		mGroupAtMsgTip->setData(transfer(member.thumbAvatar.value().c_str()), name + ":" + msgText);
		mGroupAtMsgTip->show();
		END;
	}

	void ChatWidget::paintEvent( QPaintEvent *event )
	{
		QWidget::paintEvent(event);
		if (mGroupAtMsgTip != CNull)
		{
			mGroupAtMsgTip->setFixedWidth(m_chattitle->width());
		}
	}

	void ChatWidget::onShowGroupAtMsgTip( CSharedPtr<data::Msg> msg )
	{
		showGroupAtMsgTip(msg);
	}

	int64 ChatWidget::targetId()
	{
		return m_target.targetId;
	}

	void ChatWidget::setTargetInfo( TargetInfo info ,bool updateHisMsg)
	{
		m_target.targetName = info.targetName;
		m_target.targetAvatar = info.targetAvatar;
		///// m_chattitle->SetTitleText(m_target.targetName,info.targetAvatar);  2019-5-26

		m_chattitle->SetTargetInfo(m_target);


		m_chatview->setTargetInfo(m_target,updateHisMsg);
		if (m_target.chattype != data::GROUP_CHAT && m_target.chattype != data::APP_CHAT && m_target.chattype != data::ENT_CHAT && m_target.chattype != data::APPLICATION_CHAT )
		{
			bool isNotBuddy = false;
			isNotBuddy = !mContactControl->ContactIsBuddy(m_target.targetId);
			m_chattitle->showAddBtn(m_target.targetId,isNotBuddy);
		}
	}

	void ChatWidget::updateGroupMemInfo(const data::Member&mem)
	{
		if (m_topMessageWindow != CNull) {
			if (mem.memberType.value() == 3 || mem.memberType.value() == 2) {
				m_topMessageWindow->setEnableCancelTop(true);
			}
			else {
				m_topMessageWindow->setEnableCancelTop(false);
			}
		}
	}

	void ChatWidget::setMemberHeadImgUpdate(int64 targetId, const std::string&head)
	{
		if (m_target.chattype == data::GROUP_CHAT) {
			m_chatview->setMemberHeadImgUpdate(targetId, head);
		}
	}
	bool ChatWidget::isWebUrl(QString text)
	{
		bool isLink = false;
		QString str("^(((ht|f)tp(s?))\\://)?(www.|[a-zA-Z].)[a-zA-Z0-9\\-\\.]+\\.(com|edu|gov|mil|net|org|biz|info|name|museum|us|ca|uk|cn)(\\:[0-9]+)*(/($|[a-zA-Z0-9\\.\\,\\;\?\'\\\\+&amp;%\\$#\\=~_\\-]+))*$");
		QRegExp rx(str);

		bool match = rx.exactMatch(text);
		isLink = match;
		return isLink;
	}

	void ChatWidget::onSerGetUrlInfo(QString text, int code, const std::string& url, const std::string& title, const std::string&imgPath, const std::string&desc )
	{
		if (code == 0)
		{
			CSharedPtr<data::Msg> msgptr =CNull;
			CSharedPtr<data::MsgWeb> msgweb = CMakePtr<data::MsgWeb>();
			msgweb->url = url;
			msgweb->title = title;
			msgweb->img = imgPath;
			msgweb->desc = desc;
			msgweb->body = url;
			msgptr = msgweb;
			if (m_target.chattype == data::GROUP_CHAT)
			{
				msgptr->isGroup = true;
			}
			msgptr->targetId = m_target.targetId;
			msgptr->status = MSG_SENDING;
			m_chatview->addMsg(msgptr);
		}else{
			std::vector<int64>atlist;
			SendMsg(data::MSG_TYPE_TEXT,text,atlist);
		}
	}

	void ChatWidget::onSendCard( int64 cardId,bool isburn,bool isdelay,bool isreceipt )
	{
		CSharedPtr<data::Msg> msgptr =CNull;
		CSharedPtr<data::MsgCard> msgcard = CMakePtr<data::MsgCard>();
		msgcard->mediaUrl = QString::number(cardId).toStdString();
		msgcard->isBurn = isburn;
		msgptr = msgcard;
		msgptr->targetId = m_target.targetId;
		msgptr->status = MSG_SENDING;


		if (m_target.chattype == data::GROUP_CHAT)
		{
			msgptr->isGroup = true;
		}

		if(m_PrivateTargetId.contains(msgptr->targetId))
		{
			msgptr->isPrivateMsg = 2;
		}
		else
		{
			msgptr->isPrivateMsg = 0;
		}

		/*if(m_chatedit->ReturnChickFeatherStat())
		{
			msgptr->isFeather = 1;
		}
		else
		{	
			msgptr->isFeather = 0;
		}*/
		m_chatview->addMsg(msgptr);
	}

	void ChatWidget::onSendDnyMsg( QString fileName )
	{
		CSharedPtr<data::Msg> msgptr =CNull;
		CSharedPtr<data::MsgDynExpression> msgDny = CMakePtr<data::MsgDynExpression>();
		msgDny->body = fileName.toStdString();
		msgptr = msgDny;
		msgptr->targetId = m_target.targetId;
		msgptr->status = MSG_SENDING;
		msgptr->isFeather = 0;
		if (m_target.chattype == data::GROUP_CHAT)
		{
			msgptr->isGroup = true;
		}
		if(m_PrivateTargetId.contains(msgptr->targetId))
		{
			msgptr->isPrivateMsg = 2;
		}
		else
		{
			msgptr->isPrivateMsg = 0;
		}
		m_chatview->addMsg(msgptr);
	}

	void ChatWidget::onSerGroupRefreshUpdate(int8 type, const data::Group& groupInfo)
	{
		/*if(m_target.chattype == 2 && type == 2 && groupInfo.info.value().groupId.value())
		{
			std::string ExtendInfoJson = groupInfo.extend.value();
			Json::Reader reader;
			Json::Value root,fieldsarry, mJvalue;
			int ret = reader.parse(ExtendInfoJson, root);
			if (!ret)
			{
				AddLog(LOG_LEV_ERROR,"json parse filed,err=%d,json=%s",ret,ExtendInfoJson.c_str());
			}
			if (!root.isMember("privateMsg")){
				return;
			}
			int SecretValue = root["privateMsg"].asInt();
			if(SecretValue)
			{
				emit signalSetSecretIsvisible(true,false);
			}
			else
			{
				onSetPrivateKey(QString(""));
				mChatCtrl->setPrivateKey(m_target.targetId, "");
				emit signalSetSecretIsvisible(false,false);
			}		
		}*/
	}

	void ChatWidget::InitGroupInfo()
	{
		LOG_METHOD("ChatWidget::InitGroupInfo", LOG_FILE);
		/*data::Group groupInfo;
		if(mGroupControl && m_target.chattype == 2)
		{
			mGroupControl->GetGroupInfo(m_target.targetId, groupInfo);
			MemCount = groupInfo.memberNums.value();
			SetTileContent(0,MemCount);
			mGroupControl->GetGroupInfo(m_target.targetId, groupInfo);
			std::string ExtendInfoJson = groupInfo.extend.value();
			Json::Reader reader;
			Json::Value root,fieldsarry, mJvalue;
			int ret = reader.parse(ExtendInfoJson, root);
			if (!ret)
			{
				AddLog(LOG_LEV_ERROR,"json parse filed,err=%d,json=%s",ret,ExtendInfoJson.c_str());
			}
			int IntSecretValue;
			std::string strSecretValue;
			if(root["privateMsg"].isInt())
			{
				IntSecretValue = root["privateMsg"].asInt();
			}
			else
			{
				strSecretValue = root["privateMsg"].asString();
			}
			
			if(IntSecretValue == 1 || strSecretValue == "1")
			{
				if(mContactControl)
				{
					data::Contact contact;
					mContactControl->GetContactInfo(m_target.targetId,contact);
					std::string MsgPwd = contact.privateMsgPwd.value();
					if(MsgPwd != "")
					{
						m_PrivateTargetId.append(groupInfo.info.value().groupId.value());
						emit signalSetSecretIsvisible(true,true);
					}
					else
					{
						emit signalSetSecretIsvisible(true,false);
					}
				}
			}
			else
			{
				emit signalSetSecretIsvisible(false,false);
			}		
		}*/	
	}

	void ChatWidget::onSerGetContactInfo()
	{
		if(m_target.chattype == 1)
		{
			if(mContactControl)
			{
				data::Contact contact;
				mContactControl->GetContactInfo(m_target.targetId,contact);
				std::string MsgPwd = contact.privateMsgPwd.value();
				if(MsgPwd != "")
				{
					m_PrivateTargetId.append(contact.id.value());
					emit signalSetSecretIsvisible(true,true);
				}
			}	
		}	
	}

	void ChatWidget::onShakeWinClicked()
	{
		BEGIN;
		std::shared_ptr<data::Msg> msgptr = nullptr;
		std::shared_ptr<data::MsgText> msgtext = std::make_shared<data::MsgText>();

		msgtext->body = tr(SHAKE_TEXT).toUtf8().data();
		msgtext->isBurn = false;
		msgtext->targetId = m_target.targetId;
		msgtext->isReceiptAll = true;
		msgtext->status = MSG_SENDING;
		msgptr = msgtext;
		msgptr->isFeather = 0;
		if (m_target.chattype == data::GROUP_CHAT)
		{
			msgptr->isGroup = true;
		}
		m_chatview->addMsg(msgptr);

		emit signalShakeWin();
		END;
	}

	void ChatWidget::onShowRecordWin( )
	{
		bool vis = m_recordWin->isVisible();
		if (vis)
		{
			m_recordWin->StopRecord();
		}else{
			m_recordWin->setVisible(~vis);

			QPoint point = m_chatedit->pos();
			int x = m_chatedit->x();
			int y = m_chatedit->y();

			m_recordWin->setFixedWidth(m_chatedit->width());
			m_recordWin->move(x,y+RECORD_HEIGTH + 5);
			m_recordWin->raise();

			m_recordWin->StartRecord();
		}

	}

	void ChatWidget::resizeEvent( QResizeEvent * event )
	{
		m_recordWin->setFixedWidth(m_chatedit->width());
		int x = m_chatedit->x();
		int y = m_chatedit->y();

		m_chatedit->setAtListWidgetVisible(false);

		m_recordWin->move(x,y+RECORD_HEIGTH + 5);
		m_recordWin->raise();
	}

	void ChatWidget::onRecordResult( QString path,int time )
	{
		QString name = "";
		QStringList split = path.split("/");
		for ( int i =0 ;i < split.size(); ++i)
		{
			if (split.at(i).contains(FILE_AMRPSTFIX))
			{
				name = split.at(i);
				break;
			}
		}

		CSharedPtr<data::Msg> msgptr =CNull;
		CSharedPtr<data::MsgAudio> msgAudio = CMakePtr<data::MsgAudio>();
		
		msgAudio->fileName = name.toUtf8().data();
		msgAudio->encryptKey = "0";
		msgAudio->mediaTime = time;
		msgAudio->localPath = path.toUtf8().data();
		msgAudio->localId = QDateTime::currentDateTime().toMSecsSinceEpoch();
		msgAudio->meidaUrl = path.toUtf8().data();
		msgAudio->isBurn = m_chatedit->resetBurnState();
		msgptr = msgAudio;
		if (m_target.chattype == data::GROUP_CHAT)
		{
			msgptr->isGroup = true;
		}
		/*if(m_chatedit->ReturnChickFeatherStat())
		{
			msgptr->isFeather = 1;
		}
		else
		{	
			msgptr->isFeather = 0;
		}*/

		msgptr->targetId = m_target.targetId;
		msgptr->status = MSG_SENDING;
		m_chatview->addMsg(msgptr);
		
	}

	void ChatWidget::onSendDelayMsg( int64 time,QString text )
	{
		BEGIN;
		std::shared_ptr<data::Msg> msgptr = nullptr;
		std::shared_ptr<data::MsgText> msgtext = std::make_shared<data::MsgText>();

		msgtext->body = text.toUtf8().data();
		msgtext->delayTime = time;
		msgtext->isDelay = true;
		msgtext->msgType =data::MSG_TYPE_TEXT;
		msgtext->isBurn = false;
		msgtext->targetId = m_target.targetId;
		msgtext->status = MSG_SENDING;
		msgptr = msgtext;
		msgptr->isFeather = 0;
		if (m_target.chattype == data::GROUP_CHAT)
		{
			msgptr->isGroup = true;
		}
		m_chatview->addMsg(msgptr);
		m_chatedit->restDelayState();
		END;
	}

	void ChatWidget::ReplyChickFeather(int64 msgId, bool isFeather)
	{
		std::vector<int64> atlist;
		atlist.clear();
		Msgid = msgId;
		SendMsg(data::MSG_TYPE_TIP, "", atlist,true);
	}

	void ChatWidget::DealReplyChickFeather()
	{
		std::vector<int64>::iterator iter = FeatherMsgId.begin();
		while(iter != FeatherMsgId.end())
		{
			Msgid = *iter;
			ReplyChickFeather(Msgid,true);
			iter = FeatherMsgId.erase(iter);
		}	
	}

	void ChatWidget::FeatherMsgDeal(int64 msgid, bool isInsertOrDel)
	{
		if(isInsertOrDel)
		{
			FeatherMsgId.push_back(msgid);
		}
		else
		{
			std::vector<int64>::iterator iter = FeatherMsgId.begin();
			while(iter != FeatherMsgId.end())
			{
				if(*iter == msgid)
				{
					FeatherMsgId.erase(iter);
					break;
				}
				iter++;
			}
		}
	}

	void ChatWidget::onSerChickMsgReaded(int64 pmsgid)
	{
		ReplyChickFeather(pmsgid,true);
	}

	void ChatWidget::SetTileContent(int type ,int64 RangMemCount)
	{
		if(type == 1)
		{
			MemCount += RangMemCount;
		}

		if(type == 2)
		{
			MemCount -= RangMemCount;
		}
		//QString TitleContent = m_target.targetName +"  (" + QString::number(MemCount) + ")";
		QString TitleContent = m_target.targetName;
		m_chattitle->SetTitleText(TitleContent);
	}

	void ChatWidget::onSerGroupMemCountRefresh(int type, int64 pMemCount)
	{
		if(type == 1)
		{
			SetTileContent(1,pMemCount);
		}else
		{
			SetTileContent(2, pMemCount);
		}
	}

	void ChatWidget::onSerGetUserInfo( int code, data::UserData&user )
	{
		if (user.id.value() == m_target.targetId)
		{
			QString th = transfer(user.thumbAvatar.value().c_str());
			if (!th.startsWith(":/")){
				m_target.targetAvatar = transfer(user.thumbAvatar.value().c_str());
			}
			m_chatview->setTargetInfo(m_target);
		}
	}

	void ChatWidget::DelUpFileUi(int64 fileLocalid)
	{
		m_chatview->DelUpfileUi(fileLocalid);
	}

	void ChatWidget::SetNotSpeak(bool istrue,int type)
	{
		m_chatedit->SetNotSpeak(istrue, type);
		m_chatedit->SetBtnIsCicked(!istrue);
	}

	void ChatWidget::onSerSendMsgByType(int type)
	{
		if(1 == type)
		{
			std::vector<int64> atlist;
			QString text = transfer("[[结束会话]]");
			SendMsg(data::MSG_TYPE_TEXT,text,atlist,false);
		}
	}

	void ChatWidget::onSerbtnCloseSession(bool isVisible)
	{
		emit signalSerbtnCloseSession(isVisible);
	}

	void ChatWidget::setNoMoreState(bool isClicked)
	{
		m_chatview->setNomoreState(isClicked);
	}

	QHBoxLayout  *ChatWidget::initLocalSearchLayout()
	{
		QHBoxLayout *search_layout = new QHBoxLayout(this);

		QPushButton *mBtnLocalSearch = new QPushButton(this);
		mBtnLocalSearch->setObjectName("localsearchbtn");

		mBtnLocalSearch->setStyleSheet("background:rgb(228,228,228)");

		PushButton *m_searchBtnLogo = new PushButton(mBtnLocalSearch);
		m_searchBtnLogo->setPicName(":/title/search");
		mBtnLocalSearch->setFixedWidth(240);
		search_layout->addWidget(mBtnLocalSearch);
		search_layout->addWidget(m_searchBtnLogo);
		mBtnLocalSearch->setToolTip(transfer("搜索联系人、组织成员和群"));
		connect(mBtnLocalSearch, SIGNAL(clicked(bool)), this, SLOT(onSearchBtnClicked()));
		search_layout->setContentsMargins(5, 25, 5, 10);
		return search_layout;
		///mBtnLocalSearch->move(80,24);
		/*mBtnLocalSearch->move(100, 18);
		mSearchBackground = new QWidget(this);
		mSearchBackground->setFixedSize(QSize(240, 55));
		///mSearchBackground->setStyleSheet("background:rgb(19,52,83)");
		///mSearchBackground->setStyleSheet("background:rgb(39,104,194)");
		mSearchBackground->setStyleSheet("background:rgb(28,28,28");
		mSearchBackground->move(78, 2);

		mLocalSearchLineEdit = new LocalSearchLineEdit(mSearchBackground);
		mSearchBackground->setVisible(false);
		mLocalSearchLineEdit->move(0, 15);
		mLocalSearchLineEdit->setFixedSize(QSize(220, 28));
		mLocalSearchLineEdit->setStyleSheet("background:white;border-radius:14px;");
		connect(mLocalSearchLineEdit, SIGNAL(clearBtnClicked()), this, SLOT(onShowAvatar()));
		connect(mLocalSearchLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onSearchTextChanged(const QString&)));
		*/
	}

	void ChatWidget::onSerCanceltopMsg()
	{
		m_usercontrol->cppccGetTopInfo(m_target.targetId, 1, 10, CBind(&ChatWidget::signalSerCancelTopMsg, this, CPlaceholders  _1, CPlaceholders  _2, CPlaceholders  _3, CPlaceholders  _4));
	}

	void ChatWidget::onSerCancelTopMsg(int code, int32 pageNum, int32 Count, std::vector<data::ZxTopInformation>& ResultTopMsg)
	{
		if (ResultTopMsg.size() > 0)
		{
			std::string nameMark;
			std::string content;
			m_chattitle->setTopMsgVisible(true);
			std::string jsoninfo = ResultTopMsg.at(0).topContent;
			Json::Reader  reader;
			Json::Value root;
			if (jsoninfo.find("{") == -1)
			{
				m_chattitle->setTopMsgVisible(false);
				Log(LOG_LEV_ERROR, LOG_FILE, "topmsgJson=%s", jsoninfo.c_str());
				return;
			}
				
			bool ret = reader.parse(jsoninfo, root);
			if (!ret){
				m_chattitle->setTopMsgVisible(false);
				Log(LOG_LEV_ERROR, LOG_FILE, "topmsgJson=%s", jsoninfo.c_str());
				return;
			}
			else{
				if (root.isMember("content"))
				{
					if (root["content"].isString())
					{
						content = root["content"].asString();
						//解析表情
						if (mChatCtrl){
							content = mChatCtrl->parceEmojiDeal(content);
						}
					}
				}
				if (root.isMember("name"))
				{
					if (root["name"].isString())
					{
						nameMark = root["name"].asString();
					}
				}
				if (root.isMember("jiebie"))
				{
					if (root["jiebie"].isString())
					{
						nameMark += "-" + root["jiebie"].asString();
					}
				}
			}
			m_chattitle->setTopMsgContent(QString::fromUtf8(nameMark.c_str()) + transfer("的发言：") + QString::fromUtf8(content.c_str()));
		}
		else{
			m_chattitle->setTopMsgVisible(false);
		}
	}

	void ChatWidget::onSerMoretopMsg()
	{
		m_usercontrol->cppccGetTopInfo(m_target.targetId, 1, 10, CBind(&ChatWidget::signalSerGetTopMsg, this, CPlaceholders  _1, CPlaceholders  _2, CPlaceholders  _3, CPlaceholders  _4));
	}

	void ChatWidget::onSerGetTopMsg(int code, int32 pageNum, int32 Count, std::vector<data::ZxTopInformation>& ResultTopMsg)
	{
		if (!m_topMessageWindow)
			m_topMessageWindow = new MessageTopWidget(this);

		m_topMessageWindow->setTopMessage(ResultTopMsg);
		m_topMessageWindow->exec();
	}

	void ChatWidget::hideEvent(QHideEvent *)
	{
		m_chatedit->setAtListWidgetVisible(false);
	}

	void ChatWidget::setAtListVisible(bool isVis)
	{
		m_chatedit->setAtListWidgetVisible(isVis);
	}
}

