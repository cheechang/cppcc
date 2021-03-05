#include "ChatContentView.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QCoreApplication>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>
#include "bubble/chatview.h"
#include "bubble/chatscene.h"
#include "bubble/speechbubblewidget.h"
#include "bubble/detail/flexmessagewidget.h"
#include "bubble/generalmessageitem.h"
#include "bubble/flexmessageitem.h"
#include "bubble/abstractmessagewidget.h"
#include "bubble/richtextmessagewidget.h"
#include "bubble/imagemessagewidget.h"
#include "bubble/gifmessagewidget.h"
#include "bubble/CardMessageWidget.h"
#include "bubble/BurnMessageWidget.h"
#include "bubble/detail/textutils.h"
#include "bubble/detail/QProgressIndicator.h"
#include "bubble/filemessagewidget.h"
#include "controls/ToolButton.h"
#include "bubble/eventfilter.h"
#include "bubble/msgtimeitem.h"
#include "bubble/loadmsgwidget.h"
#include "common/Common.h"
#include "common/MsgTimeDeal.hpp"
#include "data/ChatData.h"
#include "data/GroupData.h"
#include "utils/common.h"
#include "bubble/MsgFactory.h"
#include "bubble/MsgBubbleConfig.h"
#include "controls/UserInfoWindow.h"
#include "controls/UserInfoCommon.h"
#include "controls/UserInfoCommitee.h"
#include "ui/common/ChineseInfos.hpp"
#include "controls/WeMessageBox.h"
#include "bubble/PrivateChatmessageWidget.h"
#include "bubble/pictextmessagewidget.h"
#include <log.h>
#include "json.h"
#include <qsettings>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebChannel/qwebchannel.h>
#include "QtWebEngineWidgets\qwebenginesettings.h"
#include <QtWebEngineWidgets\QWebEngineDownloadItem.h>
#include <QtWebEngineWidgets/QWebEngineProfile>
#include "utils/Error.h"
#include <utils/functionconfig.h>
extern void OpenWebDlg(QString urlPath);
extern int gNameSectorOpen;
namespace ui{
	ChatContentView::ChatContentView(QWidget *parent):QWidget(parent),m_scene(CNull),m_messageCount(0),m_messageHeight(0),
		m_ishistory(false), m_chatType(data::ChatType::BUDDY_CHAT), m_hismessageHeight(0), m_factory(CNull), m_groupcontrol(CNull), m_chatcontrol(CNull), m_firstmsgid(0),
	m_cursel(0),m_isFirstGetMsg(true), mGroupType(0)
	{
		m_pUserInfoCommiteeWidget = CNull;
		m_needGetMems = false;
		m_isStartChat = true;
		m_graphicsView = CMakePtr<ChatView>(this);
		m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		connect(m_graphicsView.get(), SIGNAL(hideAtWin()), this, SIGNAL(hideAtWin()));
		m_scene = CMakePtr<ChatScene>(this);
		m_graphicsView->setScene(m_scene.get());
		m_messageHeight =MsgBubbleConfig::VerticalMargin()+MsgBubbleConfig::MsgVerticalMargin();

		EventFilter* evtFilter = new EventFilter(this);
		m_graphicsView->verticalScrollBar()->installEventFilter(evtFilter);
		evtFilter->setTargetObject(m_graphicsView->verticalScrollBar());
		connect(evtFilter, SIGNAL(eventFiltered(QEvent*)), this, SLOT(onEventFiltered(QEvent*)));

	    QVBoxLayout* mainlayout = new QVBoxLayout();
		mainlayout->addWidget(m_graphicsView.get());
		mainlayout->setContentsMargins(0,0,0,0);
		setLayout(mainlayout);

		m_pUserInfoWidget = CMakePtr<UserInfoWindow>(this);
		//m_pUserInfoCommomWidget = CMakePtr<UserInfoCommon>(this);
		//m_pUserInfoCommiteeWidget = CMakePtr<UserInfoCommitee>(this);
		connect(m_pUserInfoWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
			this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));

		m_graphicsView->setObjectName("chatview");
		createLoadIndicator();
		mUseByCombineMsgWin = false;

		m_factory = CMakePtr<MsgFactory>();
		m_authControl = AUTHCONTROL;
		m_chatcontrol  = CHATMGRCONTROL;
		m_userControl = USERCONTROL;
		m_acountInfo = *m_userControl->GetAccountInfo().get();

		CONNECT_SERVICE(GetGroupMem(int, data::Member&, QString));
		CONNECT_SERVICE(GetBatchMemberByID(int, std::vector<CSharedPtr<data::Member> >&));
		CONNECT_SERVICE(DeleteMsg(int));
		CONNECT_SERVICE(GetMessages(int,int64,std::vector<CSharedPtr<data::Msg>>&,int64,int,CSharedPtr<data::ChatInfo>,bool));
		CONNECT_SERVICE(GetAppInfo(int, data::UserData&));
		CONNECT_SERVICE(DeleteMsgById(int));
			CONNECT_SERVICE(GetDecryptMsgs(int , int64 , std::vector<CSharedPtr<data::Msg>>& ));
		m_groupcontrol = GROUPMGRCONTROL;
		CONNECT_SERVICE(GetGroupMemberList(int,std::vector<CSharedPtr<data::Member>>&,qint64));
		CONNECT_SERVICE(SearchGetMessage(int, int64, std::vector<CSharedPtr<data::Msg>>&));
		CONNECT_SERVICE(SearchSendedGetMessage(int, int64, std::vector<CSharedPtr<data::Msg>>&));	
		CONNECT_SERVICE(GetUserInfo(int, data::UserData&, int64,QString, QString));
		CONNECT_SERVICE(cppccTopInfo(int, const std::string&, data::ZxTopInformation&));
		CONNECT_SERVICE(GetGroupMsgUnreadCounter(int64, int, std::vector<data::MsgUnreadCounter>&));
		CONNECT_SERVICE(GetContractMaxReadId(int64, std::vector<MsgDataPtr>&, int, int64));
	}
	ChatContentView::~ChatContentView(){

	}
	void ChatContentView::clear()
	{
		m_scene->clear();
		m_messageCount = 0;
		m_cache.clear();
		m_scene->update();
		m_messageHeight = MsgBubbleConfig::VerticalMargin()+MsgBubbleConfig::MsgVerticalMargin();
		updateSceneRect();
		layoutMessageItems();
	}

	void ChatContentView::setGetMemsStatus(bool isGetMems){
		m_needGetMems = isGetMems;
	}
	void ChatContentView::setBackgroundImage(const QPixmap& pixmap)
	{
		m_graphicsView->setBackgroundImage(pixmap);
	}

	QPixmap ChatContentView::backgroundImage() const
	{
		return m_graphicsView->backgroundImage();
	}
	void ChatContentView::addMsgTime(AbstractMessageWidget*&abmsg)
	{   
		QGraphicsTextItem*timeItem = CNull;
		if (CNull == abmsg) return;
		timeItem = m_factory->GetMessageTimeWidget(abmsg->msgTime());
		if (CNull == timeItem) return;
		timeItem->setPos((m_graphicsView->width()- timeItem->boundingRect().width())/2,m_ishistory?MsgBubbleConfig::VerticalMargin():m_messageHeight);
		m_scene->addItem(timeItem);
		m_messageHeight += timeItem->boundingRect().height();
		m_cache.AddMsgItem(timeItem,m_ishistory);
		if(m_ishistory){
			m_hismessageHeight+=(timeItem->boundingRect().height()+MsgBubbleConfig::VerticalMargin());
			layoutMessageItems();
		}
		//缓存时间items
		mMapTimeItems.insert(abmsg->uiLocalId(),timeItem);
	}
	void ChatContentView::resizeEvent(QResizeEvent* evt)
	{
		Q_UNUSED(evt)
		layoutMessageItems();
		layoutMessageIndicators();
		layoutLoadMessageIndicator();
		updateSceneRect();
		layoutBackgroundImage();
		scrollToBottom();
	}
	bool ChatContentView::event(QEvent *event)
	{
		// handling window maximized
		if (event->type() == QEvent::WindowStateChange){
			layoutMessageItems();
			layoutMessageIndicators();
			layoutLoadMessageIndicator();
			updateSceneRect();
		}
		return QWidget::event(event);
	}
	void ChatContentView::layoutMessageItems()
	{
		// TODO: switch to layout policy to re-position message items

		// We only need to reset message item's horizontal position
		QList<QGraphicsItem*> messagelist =  m_cache.GetMessageList();
		QList<QGraphicsItem*>::const_iterator msgItemIter = messagelist.begin();
		if (m_loading && m_loading->isVisible())
			m_messageHeight = MsgBubbleConfig::VerticalMargin() * 2+ m_loading->boundingRect().height()+MsgBubbleConfig::MsgVerticalMargin(); // top & bottom margins
		else
			m_messageHeight = MsgBubbleConfig::VerticalMargin()+MsgBubbleConfig::MsgVerticalMargin();

		int maxWidgetWidth = qMin<int>(m_graphicsView->width() * MsgBubbleConfig::WidthRatio(), MsgBubbleConfig::MaxChatBubbleWidth());

		while (msgItemIter != messagelist.end()) {
			QGraphicsItem* item = *msgItemIter;
			QPointF pos;
			int width = 0;

			width = m_graphicsView->width();
			if ( GENERAL_MSG == item->type()) {
				GeneralMessageItem* msgItem = CNull;
				FlexMessageWidget* msgWidget = CNull;
				QScrollBar* verscrobar = CNull;

				msgItem = dynamic_cast<GeneralMessageItem*>(*msgItemIter);
				msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
				verscrobar = m_graphicsView->verticalScrollBar();
				if (msgWidget) {
					msgWidget->suggestWidth(maxWidgetWidth);
					msgWidget->update();
					if (msgItem->senderType() == FlexMessageItem::Others){
						pos = QPointF(MsgBubbleConfig::horizontalMargin(),m_messageHeight);
					}
					else{
						pos = QPointF(width-msgItem->boundingRect().width()-MsgBubbleConfig::horizontalMargin()-(verscrobar->isVisible()? 
								MsgBubbleConfig::VerticalScrollBarWidth():0),m_messageHeight);
					}
					if (data::MSG_TYPE_TIP== msgWidget->messageWidget()->msgType()||
						data::MSG_TYPE_PICTEXT== msgWidget->messageWidget()->msgType())
					{
						pos = QPointF((width-MsgBubbleConfig::horizontalMargin()-msgItem->boundingRect().width())/2,m_messageHeight);
					}
					msgItem->setPos(pos);
				}
			}else if (TIME_MSG == item->type()) {
				pos = QPointF((width - item->boundingRect().width())/2,m_messageHeight);
				item->setPos(pos);
			}
			m_messageHeight += item->boundingRect().height() + MsgBubbleConfig::VerticalMargin();
			++msgItemIter;
		}
	}
	void ChatContentView::layoutMessageIndicators()
	{
		QMap<GeneralMessageItem*, QGraphicsItem*>::const_iterator msgItemIter = m_messageIndicatorMap.begin();
		QPoint msgPos;
		QRect msgRect;
		QPoint pos;
		int width = 0;
		int verBarWidth = 0;

		verBarWidth = m_graphicsView->verticalScrollBar()->isVisible() ? 20 : 0;
		width = m_graphicsView->width();
		while (msgItemIter != m_messageIndicatorMap.end()) {
			GeneralMessageItem* msgItem = msgItemIter.key();

			msgPos = msgItem->pos().toPoint();
			msgRect = msgItem->widget()->rect();

			QGraphicsProxyWidget* indicatorWidget = dynamic_cast<QGraphicsProxyWidget*>(msgItemIter.value());

			if (msgItem->senderType() == GeneralMessageItem::Others)
				pos = QPoint(msgRect.width(), msgPos.y() + 20);
			else
				pos = QPoint(width- msgRect.width() - indicatorWidget->widget()->width() - verBarWidth, msgPos.y() + 20);

			indicatorWidget->setPos(pos);

			++msgItemIter;
		}
	}
	void ChatContentView::updateSceneRect()
	{
		QRectF canvasRect(QPointF(0, 0), QSizeF(m_graphicsView->width(), qMax<int>(m_messageHeight, m_graphicsView->height() - 2)));
		m_scene->setSceneRect(canvasRect);
	}
	
	void ChatContentView::layoutBackgroundImage()
	{

	}
	void ChatContentView::setMessageState(GeneralMessageItem* msgItem, MessageState state)
	{
		if (!msgItem) return;

		switch (state) {
		case Ok:
			clearMessageState(msgItem);
			break;

		case Processing:
			{
				clearMessageState(msgItem);
				QProgressIndicator* pgsIndicator = new QProgressIndicator();
				pgsIndicator->setToolTip(transfer("消息正在发送，请稍候..."));
				pgsIndicator->setAttribute(Qt::WA_TranslucentBackground);
				pgsIndicator->setFixedSize(QSize(20, 20));
				pgsIndicator->startAnimation();
				QGraphicsProxyWidget* gpw = m_scene->addWidget(pgsIndicator);
				QPoint msgPos = msgItem->pos().toPoint();
				QRect msgRect = msgItem->widget()->rect();
				QPoint pos;

				int verBarWidth = m_graphicsView->verticalScrollBar()->isVisible() ? 20 : 0;
				if (msgItem->senderType() == GeneralMessageItem::Others)
					pos = QPoint(msgRect.width(), msgPos.y() + 20);
				else
					pos = QPoint(m_graphicsView->width() - msgRect.width() - pgsIndicator->width() - verBarWidth, msgPos.y() + 20);

				gpw->setPos(pos);
				m_messageIndicatorMap[msgItem] = gpw;
			}
			break;

		case Error:
			{
				clearMessageState(msgItem);
				SendMsgFailureWidgetPrivate* warningButton = new SendMsgFailureWidgetPrivate(msgItem);
				warningButton->setToolTip(transfer("重新发送"));
				warningButton->setAttribute(Qt::WA_TranslucentBackground);
				warningButton->setAutoRaise(true);
				warningButton->setIcon(QIcon(":/chat/failed"));
				QGraphicsProxyWidget* gpw = m_scene->addWidget(warningButton);

				QPoint msgPos = msgItem->pos().toPoint();
				QRect msgRect = msgItem->widget()->rect();
				QPoint pos;

				int verBarWidth = m_graphicsView->verticalScrollBar()->isVisible() ? 20 : 0;

				if (msgItem->senderType() == GeneralMessageItem::Others)
					pos = QPoint(msgRect.width(), msgPos.y() + 20);
				else
					pos = QPoint(m_graphicsView->width() - msgRect.width() - warningButton->width() - verBarWidth, msgPos.y() + 20);

				gpw->setPos(pos);
				m_messageIndicatorMap[msgItem] = gpw;
				// TODO: when pressed the button to resend the message.
				connect(warningButton,SIGNAL(clicked(GeneralMessageItem*)),this,SLOT(onReSendMsgClicked(GeneralMessageItem*)));
			}
			break;
		}
	}

	void ChatContentView::clearMessageState(GeneralMessageItem *msgItem)
	{
		if (m_messageIndicatorMap.contains(msgItem)) {
			QGraphicsItem* indicatorItem = m_messageIndicatorMap.value(msgItem);
			if (indicatorItem) {
				m_scene->removeItem(indicatorItem);
				QGraphicsProxyWidget* indicatorProxy = dynamic_cast<QGraphicsProxyWidget*>(indicatorItem);
				if (indicatorProxy)
					indicatorProxy->deleteLater();
				m_scene->update();
			}
			m_messageIndicatorMap.remove(msgItem);
		}
	}
	void ChatContentView::createLoadIndicator(){
		m_loading = CMakePtr<LoadMsgWidget>();
		connect(m_loading.get(), SIGNAL(getHistoryMsg()),this,SLOT(onGetHistoryMsg()));
		m_scene->addItem(m_loading.get());
		layoutLoadMessageIndicator();
		layoutMessageItems();
	}

	void ChatContentView::setNomoreState(bool isClicked)
	{
		m_loading->setNoMoreState(isClicked);
	}

	void ChatContentView::layoutLoadMessageIndicator(){
		if (!m_loading || !m_loading->isVisible()) return;
		m_loading->setPos((m_graphicsView->width() - m_loading->boundingRect().width())/2,0);
	}
	void ChatContentView::scrollToBottom()
	{
		animateVerScrollBar(m_graphicsView->verticalScrollBar()->value(), m_graphicsView->verticalScrollBar()->maximum());
	}

	void ChatContentView::scrollToTop()
	{
		animateVerScrollBar(m_graphicsView->verticalScrollBar()->value(),m_graphicsView->verticalScrollBar()->minimum());
	}
	void ChatContentView::animateVerScrollBar(int start, int end)
	{
		QPropertyAnimation* propAnim = new QPropertyAnimation(m_graphicsView->verticalScrollBar(), "value");
		propAnim->setEasingCurve(QEasingCurve::OutCubic);
		propAnim->setDuration(MsgBubbleConfig::ScrollDuration());
		propAnim->setStartValue(start);
		propAnim->setEndValue(end);
		propAnim->start(QAbstractAnimation::DeleteWhenStopped);
	}
	void ChatContentView::adjustSceneHeight()
	{
		m_scene->setSceneRect(QRectF(QPointF(0, 0), QSizeF(m_graphicsView->width(), qMax<int>(m_graphicsView->height()-2, m_messageHeight))));
	}
	void ChatContentView::setChatType(int ChatType){
		m_chattype = ChatType;
	}
	void ChatContentView::setUserInfo(UserInfo&user){
		m_user.selfavatar = user.selfavatar;
		m_user.selfName = user.selfName;
		m_user.selfid = user.selfid;
		AbstractMessageWidget::SetUserInfo(user);
		//更新历史消息信息
		QMap<qint64,FlexMessageWidget*>map = m_cache.getMySendMessageWidgets();
		AddLog(LOG_LEV_INFO,"............update my avatar:%s",user.selfavatar.toStdString().c_str());
		QList<FlexMessageWidget*>msgs = map.values();
		for (int i=0;i<msgs.size();++i)
		{
			FlexMessageWidget* msg = msgs.at(i);
			if (msg != CNull)
			{
				QPixmap pix;
				bool ret = pix.load(user.selfavatar);
				if(!ret){
					ret = pix.load(user.selfavatar,"*.png");
				}
				if(!ret){
					ret = pix.load(DEFAULT_AVATAR);
				}
				msg->setAvatar(pix);
			}
		}

	}
	void ChatContentView::setTargetInfo(TargetInfo& target,bool updateHisMsg){
		m_chatType = (data::ChatType)target.chattype;
		AbstractMessageWidget::SetTargetInfo(target);
		Log(LOG_LEV_DEBUG, LOG_FILE, "targetid=%lld,name=%s,target.avar=%s", target.targetId, target.targetName.toLocal8Bit().data(), target.targetAvatar.data());
		//更新历史消息
		if (updateHisMsg)
		{
			QList<QGraphicsItem*> messagelist =  m_cache.GetMessageList();
			QList<QGraphicsItem*>::const_iterator msgItemIter = messagelist.begin();
			while (msgItemIter != messagelist.end()){
				QGraphicsItem* item = *msgItemIter;
				if ( GENERAL_MSG == item->type()) {
					GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(*msgItemIter);
					FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
					AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
					if ( target.targetId == absmsg->sendId())
					{
						msgWidget->setAvatar(target.targetAvatar);
						msgWidget->setName(target.targetName);
						QCoreApplication::processEvents();
					}
				}
				++msgItemIter;
			}
		}
		//群类型
		if (target.chattype == data::GROUP_CHAT) {
			data::Group group;
			m_groupcontrol->GetGroupInfo(target.targetId, group);
			mGroupType = group.info.value().type.value();
		}
	}
	UserInfo ChatContentView::getUserInfo()const{
		return m_user;
	}
	void ChatContentView::onEventFiltered(QEvent* event)
	{
		// when graphicsview's vertical scrollbar's visiblitys changed, we need to
		// re-position message items
		if (QEvent::Show  == event->type() || QEvent::Hide == event->type()) {
			layoutMessageItems();
			layoutMessageIndicators();
		}
		else if (QEvent::Wheel == event->type())
		{
			QWheelEvent* ev = static_cast<QWheelEvent*>(event);
			if ( Qt::Vertical == ev->orientation())
			{
				bool scrollDown = ev->delta() < 0;
				QScrollBar* verBar = m_graphicsView->verticalScrollBar();
				// If at top or bottom, just returns
				if ((verBar->value() == verBar->maximum() && scrollDown )||
					(verBar->value() == 0 && !scrollDown))
					/*if (!m_loading->isLoading()&& m_loading->hasMoreData() && (verBar->value() == 0 && !scrollDown))
					{
						onGetHistoryMsg();
					}*/
					return;

				const int DeltaValue =m_graphicsView->height();
				int endValue = 0;
				if (scrollDown) {
					endValue = verBar->value() + DeltaValue;
					if (endValue >= verBar->maximum())
						endValue = verBar->maximum();
				} else{
					endValue = verBar->value() - DeltaValue;
					if (endValue <= 0)
						endValue = 0;
				}
				animateVerScrollBar(verBar->value(),endValue);
				ev->accept();
			}

		}
	}
	void ChatContentView::onSizeChanged(){
		layoutMessageItems();
		adjustSceneHeight();
		updateSceneRect();
		if (!m_ishistory)
		{
			scrollToBottom();
		}
	}
	void ChatContentView::updateMsgItemAvatar(std::vector<CSharedPtr<data::Member>>&memberlist){
		QList<QGraphicsItem*> messagelist =  m_cache.GetMessageList();
		QList<QGraphicsItem*>::const_iterator msgItemIter = messagelist.begin();
		while (msgItemIter != messagelist.end()){
			QGraphicsItem* item = *msgItemIter;
			if ( GENERAL_MSG == item->type()) {
				GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(*msgItemIter);
				FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
				AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
				for (int index=0 ;index<memberlist.size(); ++index)
				{
					qint64  memberid = memberlist.at(index)->id.value();
					if ( memberid == absmsg->sendId() && memberid != m_user.selfid)
					{
						QString remark = QString::fromUtf8(memberlist.at(index)->remark.value().data());
						QString name  = QString::fromUtf8(memberlist.at(index)->name.value().data());
						QString portrait = QString::fromUtf8(memberlist.at(index)->thumbAvatar.value().data());

						QString membername = remark.isEmpty()?(name.isEmpty()?QString::number(memberid):name):remark;
						if ( portrait.startsWith(":/")||!utils::FileIsExist(portrait.toLocal8Bit().data()))
						{
							portrait = "";
						}
			
						if (!memberlist.at(index)->sector.value().empty()){
							if (gNameSectorOpen == 1) {
								membername = membername + "-" + QString::fromUtf8(memberlist.at(index)->sector.value().c_str());
							}
						}
						if (!portrait.isEmpty()){
							msgWidget->setAvatar(portrait);
						}
						msgWidget->setName(membername);
						QCoreApplication::processEvents();
						break;
					}
				}
			}
			++msgItemIter;
		}

	}
	void ChatContentView::SetIsHistoryMsg(bool ishis){
		m_ishistory = ishis;
		ishis?m_loading->setLoading(true):m_loading->setLoading(false);
		if (m_isStartChat)
		{   m_isStartChat = false;
			m_hismessageHeight+=MsgBubbleConfig::VerticalMargin()+MsgBubbleConfig::MsgVerticalMargin();
			animateVerScrollBar(m_graphicsView->verticalScrollBar()->value(),m_hismessageHeight);
			m_hismessageHeight=0;
		}
	}
	void ChatContentView::setNomoreData(){
		m_loading->setNoMoreData();
	}
	void ChatContentView::addMsg(CSharedPtr<data::Msg>&msg){

		if (msg->status == MSG_SENDING) {
			msg->maxUnReadCount = 0;
		}
		m_chatType = msg->isGroup ? data::ChatType::GROUP_CHAT : data::ChatType::BUDDY_CHAT;
		if (mGroupType >= 1 && msg->msgType == data::MSG_TYPE_TIP) {
			data::MsgTip* msgTip = (data::MsgTip*)msg.get();
			if (msgTip != CNull && msgTip->tipType == 3 &&(msgTip->operType == 3||
				msgTip->operType == 4|| msgTip->operType == 5)) {
				return;
			}
		}

		if (msg->msgType == MSG_TYPE_REVOKE)
		{ 
			data::MsgRevoke* msgRevoke = (data::MsgRevoke*)msg.get();
			int64 localId = m_cache.GetLocalIdByMsgId(msgRevoke->revokeMsgId);
			onRemoveMsgItem(localId);
			
			CSharedPtr<data::MsgTip> msgTip = CMakePtr<data::MsgTip>();
			msgTip->tipType = 18;
			//msgTip->isGroup = msg->isGroup;
			msgTip->targetId = msg->targetId;
			msgTip->fromId = msg->fromId;
			msgTip->time = msg->time;
			if (msg->fromId == m_user.selfid)
			{
				msgTip->body =(DealMsgTime(msgRevoke->time, CHATWND_TIME) + transfer(" 您撤回了一条消息")).toUtf8().data();
			}else{
				std::vector<int64> msgIds;
				msgIds.push_back(msgRevoke->msgId);
				DeleteMsg(msgIds);
				msgIds.clear();
				msgIds.push_back(msgRevoke->revokeMsgId);
				DeleteMsg(msgIds);
				return;
				if(msg->isUser){
					QString userName = AbstractMessageWidget::GetTargetInfo(msg->targetId).targetName;
					userName +=transfer("撤回了一条消息");
					msgTip->body = userName.toUtf8().data();
				}else{
					data::Member mem;
					m_groupcontrol->GetMemberInfo(msg->targetId,msg->fromId,mem);
					QString userName = QString::fromUtf8(mem.remark.value().c_str());
					if (userName.isEmpty())
					{
						userName = QString::fromUtf8(mem.name.value().c_str());
					}
					userName +=transfer("撤回了一条消息");
					msgTip->body = userName.toUtf8().data();
				}
			}
			msg = msgTip;
		}
		if (utils::FunctionConfig::isOnShowMsgReadStatus()) {
			if (msg->msgType == data::MSG_TYPE_UNREADSTATE)
			{
				handleMsgStatusMsg(msg);
				return;
			}
		}

		if(msg->msgType == data::MSG_TYPE_TIP)
		{
			data::MsgTip* tipMsg = (data::MsgTip*)(msg.get());
			if (tipMsg->operType == 6 || tipMsg->operType == 7)
			{
				emit signalSerCancelMsgTop();
			}

			if (msg->isRecvMsg && (tipMsg->tipType == data::MSG_TYPE_TIP_READED || tipMsg->tipType == data::MSG_TYPE_TIP_NOREAD))
			{
				ResetChickFeather(msg,tipMsg->tipType);
				return ;
			}
		}
		AbstractMessageWidget* abmsg = CNull;
		FlexMessageWidget* flexmsg = CNull;
		abmsg = m_factory->GetMessageWidget(msg);
		if (mUseByCombineMsgWin)
		{
			abmsg->setRightMenuEnabled(false);
		}
		if ( CNull == abmsg) return;
		if( data::MSG_TYPE_TEXT == abmsg->msgType()){
			connect(qobject_cast<RichTextMessageWidget*>(abmsg),SIGNAL(noticeInputEditFocus()),this,SIGNAL(noticeInputEditFocus()));
			connect(qobject_cast<RichTextMessageWidget*>(abmsg),SIGNAL(signalSerRecallEdit(QString&)), this, SIGNAL(signalSerRecallEdit(QString&)));
			connect(qobject_cast<RichTextMessageWidget*>(abmsg), SIGNAL(signalSerMsgTop(data::ZxTopInformation&)), this, SLOT(onSerTopMsginfo(data::ZxTopInformation&)));
		}
		else if( data::MSG_TYPE_IMG == abmsg->msgType()){
			connect(qobject_cast<ImageMessageWidget*>(abmsg),SIGNAL(downLoadImg(int64,int64,std::string&,std::string&,bool)),this,SIGNAL(downLoadImg(int64,int64,std::string&,std::string&,bool)));
		}
		else if (data::MSG_TYPE_CARD == abmsg->msgType())
		{
			connect(qobject_cast<CardMessageWidget*>(abmsg),SIGNAL(showUserInfoWidget(int64, QString, QString)),this,SLOT(onShowUserInfoWidget(int64, QString, QString)));
		}
		if (msg->isBurn && msg->isRecvMsg)
		{
			connect(qobject_cast<BurnMessageWidget*>(abmsg),SIGNAL(viewBurnMsg(CSharedPtr<data::Msg>&)),this,SIGNAL(viewBurnMsg(CSharedPtr<data::Msg>&)));
		}
		flexmsg = m_factory->GetFlexMessageWidget(abmsg);
		if (!mUseByCombineMsgWin)
		{
			connect(flexmsg, SIGNAL(showUserInfoWidget(int64, QString, QString)),
				this, SLOT(onShowUserInfoWidget(int64, QString, QString)));
		}

		//addMessageItem(flexmsg,msg->isRecvMsg || msg->isDeviceMsg);
		addMessageItem(flexmsg,msg->isRecvMsg );   // 2019-5-24 bxy change

		if (msg->isGroup && (!m_groupcontrol->IsInGroup(msg->targetId,msg->fromId)))//app
		{
			getAppInfo(msg->fromId);
		}
		if(msg->isPrivateMsg == 1)
		{
			DecryptMsgIdList.push_back(msg->msgId);
			mMapPrivateMsgs.insert(msg->msgId,msg->localId);
			connect(abmsg, SIGNAL(signalSetDecryptKey(QString&)),this, SLOT(onDecryptMsg(QString&)));
		}

		DealEraserMsg(msg);

		if (msg->targetId == m_user.selfid) {
			flexmsg->setMsgStatusLblText("");
		}
		else if (msg->status == MSG_SENDING && msg->isGroup) {
			flexmsg->setMsgStatusLblText(ALL_UNRED_MSG);
		}
	}

	void ChatContentView::DealEraserMsg(CSharedPtr<data::Msg>& msg)
	{
		if (msg->EraserType == 0)return;

		std::vector<int64>::iterator itor;
		std::vector<int64> VrelateUsrId = msg->relatedUsers;

		itor = std::find(VrelateUsrId.begin(), VrelateUsrId.end(), m_acountInfo.id.value());
		if (itor == VrelateUsrId.end()){
			itor = std::find(VrelateUsrId.begin(), VrelateUsrId.end(), msg->targetId);
			if (itor == VrelateUsrId.end())
			{
				return;
			}
		}
		
		CSharedPtr<data::Msg> Resmsg = CNull;
		CSharedPtr<data::MsgTip> tipMsg = CMakePtr<data::MsgTip>();
		tipMsg->tipType = 5;
		tipMsg->tipTime = QString::number(QDateTime::currentMSecsSinceEpoch()).toUtf8().data();
		data::Member memdata;
		bool ret = m_groupcontrol->GetMemberInfo(m_cursel, msg->fromId, memdata);
		tipMsg->operUser = memdata.remark.value().empty() ? memdata.name.value() : memdata.remark.value();
		tipMsg->userInfo = m_acountInfo.name.value();

		if (msg->EraserType == 1)
		{
			int Res = uicontrols::WeMessageBox::showTipInformation(CNull, PROMPT, transfer("删除今天的消息记录"), false, true);
			if (uicontrols::WeMessageBox::Cancel == Res){
				tipMsg->operType = 2;
			}
			else{
				QDateTime currentTime = QDateTime::currentDateTime();
				qint64 currentSecs = currentTime.toMSecsSinceEpoch();
				QString time = currentTime.toString("yyyy-MM-dd");
				qint64 startCurrentTime = QDateTime::fromString(time, "yyyy-MM-dd").toMSecsSinceEpoch();
				m_chatcontrol->deleteMessageByTime(m_cursel, startCurrentTime, currentSecs, CBind(&ChatContentView::signalSerDeleteMsg, this, CPlaceholders  _1));
				QList<qint64> localidList = m_cache.getLocalIdByTime(1);
				for each (int64 locaid in localidList){
					removeMsgFromUI(locaid);
				}
				tipMsg->operType = 1;
			}
		}
		else if (msg->EraserType == 2)
		{
			int Res = uicontrols::WeMessageBox::showTipInformation(CNull, PROMPT, transfer("删除所有的消息记录"), false, true);
			if (uicontrols::WeMessageBox::Cancel == Res){
				tipMsg->operType = 2;
			}
			else{
				std::vector<int64> msgidv;
				DeleteMsg(msgidv);
				QList<qint64> localidList = m_cache.getLocalIdByTime(2);
				for each (int64 locaid in localidList){
					removeMsgFromUI(locaid);
				}
				tipMsg->operType = 1;
			}
		}
		Resmsg = tipMsg;
		Resmsg->targetId = msg->targetId;
		Resmsg->fromId = m_acountInfo.id.value();
		Resmsg->toId = msg->targetId;
		Resmsg->relatedMsgId = 0;
		Resmsg->status = MSG_SENDING;
		addMsg(Resmsg);
	}

	void ChatContentView::onSerDeleteMsg(int code)
	{

	}

	void ChatContentView::onSerTopMsginfo(data::ZxTopInformation& topInfoMsg)
	{
		m_userControl->cppccTopInformation(topInfoMsg, 5, CBind(&ChatContentView::signalSercppccTopInfo, this, CPlaceholders  _1, CPlaceholders  _2, topInfoMsg));
	}

	void ChatContentView::onSercppccTopInfo(int code, const std::string& strError, data::ZxTopInformation& topinfo)
	{
		AddLog(LOG_LEV_INFO, "ChatContentView::onSercppccTopInfo code=%d,strError=%s", code, strError.c_str());
		if (code == 0){
			uicontrols::WeMessageBox::showTipInformation(CNull, PROMPT, transfer("消息置顶成功"), false, false);
		}else{
			utils::Error::InitErrInfo(true);
			std::string error = utils::Error::GetErrMsg(code);
			uicontrols::WeMessageBox::showTipInformation(CNull, PROMPT, transfer(error.c_str()), false, false);
		}
	}

	void ChatContentView::addMessageItem(FlexMessageWidget*&message, bool alignLeft){
		GeneralMessageItem* msgItem = CNull;
		AbstractMessageWidget* absmsg = CNull;
		QScrollBar* verscrobar = CNull;
		int width = 0;
		QPointF pos;

		if ( CNull == message)return;
		absmsg = message->messageWidget();

		if (!m_ishistory)
		{
			addMsgTime(absmsg);
			connect(absmsg,SIGNAL(updateMsgTime(qint64,qint64)),this,SLOT(onUpdateSendMsgTime(qint64,qint64)));
		}
		width = m_graphicsView->width();
		verscrobar = m_graphicsView->verticalScrollBar();
		message->suggestWidth(qMin<int>(width*MsgBubbleConfig::WidthRatio(),MsgBubbleConfig::MaxChatBubbleWidth()));
		msgItem = new GeneralMessageItem;
		msgItem->setZValue(0);
		msgItem->setWidget(message);
		m_cache.AddMsgItem(msgItem,m_ishistory);
		msgItem->setSenderType(alignLeft ? GeneralMessageItem::Others : GeneralMessageItem::Self);
		m_scene->addItem(msgItem);	
		if ( alignLeft )
		{
		  pos = QPointF(MsgBubbleConfig::horizontalMargin(), m_ishistory?MsgBubbleConfig::VerticalMargin():m_messageHeight);
		}
		else{
			pos = QPointF(width-msgItem->boundingRect().width()-MsgBubbleConfig::horizontalMargin()-(verscrobar->isVisible()? 
				MsgBubbleConfig::VerticalScrollBarWidth():0),m_ishistory?MsgBubbleConfig::VerticalMargin():m_messageHeight);
		}
		if (data::MSG_TYPE_TIP== absmsg->msgType() || data::MSG_TYPE_PICTEXT == absmsg->msgType())
		{
			pos = QPointF((width-MsgBubbleConfig::horizontalMargin()-msgItem->boundingRect().width())/2, m_ishistory?MsgBubbleConfig::VerticalMargin():m_messageHeight);
		}
		msgItem->setPos(pos);
		m_messageHeight += msgItem->boundingRect().height() + MsgBubbleConfig::VerticalMargin();
		++m_messageCount;
		if (MSG_SENDING == absmsg->status() && alignLeft == false) 
		{
		   setMessageState(msgItem,Processing);
		}
		if ( m_ishistory)
		{
			addMsgTime(absmsg);
			m_hismessageHeight+=(msgItem->boundingRect().height()+MsgBubbleConfig::VerticalMargin());
		}
		adjustSceneHeight();
		connect(message,SIGNAL(sizechanged()),this,SLOT(onSizeChanged()));
		connect(absmsg,SIGNAL(sizechanged()),this,SLOT(onSizeChanged()));
		connect(absmsg,SIGNAL(signalGetMemberlist(qint64)),this,SLOT(onGetMemberlist(qint64)));
		connect(absmsg,SIGNAL(deleteMsg(int64)),this,SLOT(onRemoveMsgItem(int64)));
		connect(absmsg,SIGNAL(revokeMsg(int64)),this,SLOT(onRevokeMsgItem(int64)));
		connect(qobject_cast<PicTextMessageWidget*>(absmsg),SIGNAL(openUrl(std::string)),this,SIGNAL(openUrl(std::string)));
	        	if(!m_ishistory){
			scrollToBottom();
			//发送消息
			if(MSG_SENDING == absmsg->status()){
				connect(absmsg,SIGNAL(msgStatusChanged(int,qint64)),this,SLOT(onMsgStatusChanged(int,qint64)));
				connect(message,SIGNAL(burnMsg(int64)),this,SLOT(onRemoveMsgItem(int64)));
				absmsg->SendMsg();
			}
		}
                onSizeChanged(); /// 2019-5-24 bxy change
	}

	void ChatContentView::paintEvent(QPaintEvent *event)
	{
		QWidget::paintEvent(event);
	}

	void ChatContentView::getMemberList(qint64 targetid){
	BEGIN;
		if (CNull == m_groupcontrol)
		{
			AddLog(LOG_LEV_DEBUG,"targetid=%lld",targetid);
		}
		if (m_groupcontrol != CNull)
		{//暂时不拉群成员
			//m_groupcontrol->GetMemberList(targetid,CBind(&ChatContentView::signalSerGetGroupMemberList,this,CPlaceholders  _1,CPlaceholders  _2,targetid));
		}
		
	END;
	}
	void ChatContentView::onSerGetGroupMemberList(int err,std::vector<CSharedPtr<data::Member>>&memberlist,qint64 targetid){
		if (memberlist.size()>0)
		{
			//AbstractMessageWidget::SetMemberList(targetid,memberlist);
		}
		Log(LOG_LEV_DEBUG,LOG_FILE,"targetid=%lld,memberlistSize=%d",memberlist.size());
		//updateMsgItemAvatar(memberlist);
	}
	void ChatContentView::getHistoryMsg(qint64 targetid, int unreadcount, qint64 msgid, CSharedPtr<data::ChatInfo>chat, bool ishis){
		m_cursel = targetid;
		m_chatcontrol->GetMessages(
			targetid,
			msgid,
			unreadcount,
			0,
			CBind(&ChatContentView::signalSerGetMessages,this,CPlaceholders  _1,CPlaceholders  _2,CPlaceholders  _3,targetid,unreadcount,chat,ishis));
	}

	void ChatContentView::onDecryptMsg(QString& pDecryptKey)
	{
		QList<int64> msgIDs = mMapPrivateMsgs.values();
		m_chatcontrol->setPrivateKey(m_cursel, pDecryptKey.toStdString());
		std::vector<int64> vecMsgIds;
		for (int i=0;i<msgIDs.size();++i)
		{
			vecMsgIds.push_back(msgIDs.at(i));
		}
		m_chatcontrol->decryptMsg(m_cursel,vecMsgIds , CBind(&ChatContentView::signalSerGetDecryptMsgs, this, CPlaceholders  _1,CPlaceholders  _2,CPlaceholders  _3));
	}

	void ChatContentView::onSerGetDecryptMsgs(int Rcode, int64 DecryptMsgId, std::vector<CSharedPtr<data::Msg>>& DecryMsgList)
	{
		for (int i=0;i<DecryMsgList.size();++i)
		{
			CSharedPtr<data::Msg> msg = DecryMsgList.at(i);
			if (msg->isPrivateMsg == 1)
			{

			}else{
				int64 localId = mMapPrivateMsgs.value(msg->msgId);
				InsertMsgToUI(localId,msg);
				mMapPrivateMsgs.remove(msg->msgId);
			}
			if(msg->isFeather != 0)
				emit signalSerMsgReaded(msg->msgId);
		}
		m_scene->update();		
		updateSceneRect();
	}

	void ChatContentView::onSerGetMessages(int err,int64 chatid,std::vector<CSharedPtr<data::Msg>>&msglist,int64 targetid,int unreadcount,CSharedPtr<data::ChatInfo>chat,bool ishisflag){
		CSharedPtr<data::Msg> firstMsg = msglist.size()>0?msglist.at(0):CNull;
		CSharedPtr<data::Msg> lastMsg = msglist.size()>0?msglist.at(msglist.size()-1):CNull;
		qint64 MaxmsgId = (CNull != lastMsg)?lastMsg->msgId:0;
		m_firstmsgid = (CNull != firstMsg)?firstMsg->msgId:0;

		//标示不是拉取历史消息则是未读消息，设置消息已读
		if (!ishisflag && MaxmsgId>0 && unreadcount>0)
		{
			m_chatcontrol->setMessageRead(targetid,MaxmsgId);
			if(lastMsg->isGroup && lastMsg->relatedUsers.size()>0){//显示@提示
				emit groupAtMessageTip(lastMsg);
			}
		}

		if (CNull!=chat && chat->isStartChat)
		{
			IUserControl_Ptr userCtrl = USERCONTROL;
			int64 svrTime = 0;
			bool ret = false;
			if (userCtrl)
			{
				ret = userCtrl->getServerTimeSync(svrTime);
			}
			svrTime = ret ? svrTime :QDateTime::currentMSecsSinceEpoch();

			chat->lastMsg = (CNull != lastMsg)?QString::fromUtf8(lastMsg->body.data()).toStdString():"";
			chat->msgtime = (CNull != lastMsg)?lastMsg->time:svrTime;
			chat->msgid   = MaxmsgId;
			emit addChatListItem(chat);
		}
		SetMsgs(msglist,ishisflag);
		if (m_needGetMems){
			m_needGetMems = false;
			emit addIsReceiptMsg(m_cursel);
		}
	}
	void ChatContentView::SetMsgs(std::vector<CSharedPtr<data::Msg>>&msglist, bool ishisflag){
		SetIsHistoryMsg(ishisflag);
		QMap<int64, int64> mems;
		if (ishisflag)
		{
			int index = 0;
			int count = msglist.size();

			if (m_isFirstGetMsg && count>0)
			{
				index = count - 1;
			}
			else if (!m_isFirstGetMsg && count >= 2)
			{
				index = count - 2;
			}
			else
			{
				//说明没有历史记录了
				setNomoreData();
				m_isFirstGetMsg = false;
				SetIsHistoryMsg(false);
				return;
			}
			for (; index >= 0; --index)
			{
				AddLog(LOG_LEV_DEBUG, "msgid=%lld", msglist.at(index)->msgId);
				addMsg(msglist.at(index));
				mems.insert(msglist.at(index)->fromId, msglist.at(index)->fromId);
				QCoreApplication::processEvents();
			}
		}
		else{
			for (int index = 0; index<msglist.size(); ++index)
			{
				AddLog(LOG_LEV_DEBUG, "msgid=%lld", msglist.at(index)->msgId);
				addMsg(msglist.at(index));
				mems.insert(msglist.at(index)->fromId, msglist.at(index)->fromId);
				QCoreApplication::processEvents();
			}
		}
		m_isFirstGetMsg = false;
		SetIsHistoryMsg(false);
		if (m_chatType == 2) {
			std::vector<int64> ids;
			for (int i = 0; i<mems.keys().size(); ++i) {
				ids.push_back(mems.keys().at(i));
			}
			m_groupcontrol->getBatchMemberByID(m_cursel, ids,
				CBind(&ChatContentView::signalSerGetBatchMemberByID,this,
					CPlaceholders _1,CPlaceholders _2));
		}
		if (utils::FunctionConfig::isOnShowMsgReadStatus()) {
			//处理历史消息已读状态
			handleHistoryMsgStatus(msglist);
		}
	}

	void ChatContentView::handleHistoryMsgStatus(std::vector<MsgDataPtr>&msglist)
	{
		if (m_user.selfid == m_cursel) {
			return;
		}
		if (m_chatType == data::BUDDY_CHAT || m_chatType == data::STRANGER_CHAT || m_chatType == data::ENT_USER_CHAT)
		{
			m_chatcontrol->getContractMaxReadId(m_cursel, CBind(&ChatContentView::signalSerGetContractMaxReadId, this, m_cursel, msglist, CPlaceholders _1, CPlaceholders _2));
			return;
		}
		QMap<int64, FlexMessageWidget*> msgMap = m_scene->getMySendMessageWidgets();
		std::vector<data::SnapshotInfo> snapshotIds;
		for (int i = 0; i < msglist.size(); ++i)
		{
			MsgDataPtr msg = msglist.at(i);
			if (msg && msg->isBurn) {
				continue;
			}
			int64 msgid = msg->msgId;
			FlexMessageWidget*msgWidget = msgMap.value(msgid, CNull);
			if (msg->isGroup)
			{
				if (msgWidget != CNull)
				{
					setGroupMsgStatusTip(msg->unReadCount,msg->maxUnReadCount, msgWidget);
					AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
					if (absmsg != CNull) {
						int64 id = msg->snapshotId;
						absmsg->setSnapeId(id);
						disconnect(absmsg, SIGNAL(signalChangeMsgStatus(int, int64)), this, SLOT(onChangeMsgStatus(int, int64)));
						connect(absmsg, SIGNAL(signalChangeMsgStatus(int, int64)), this, SLOT(onChangeMsgStatus(int, int64)));
					}

				}
				//if (msg->unReadCount != 0)
				//{
				data::SnapshotInfo snap;
				snap.msgId = msg->msgId;
				snap.snapshotId = msg->snapshotId;
				snapshotIds.push_back(snap);
				//}
			}
		}
		if (snapshotIds.size() > 0)
		{
			//m_chatcontrol->getGroupMsgUnreadCounter(m_cursel, snapshotIds, CBind(&ChatContentView::signalSerGetGroupMsgUnreadCounter, this, m_cursel, CPlaceholders _1, CPlaceholders _2));
		}
	}


	void ChatContentView::onSerGetGroupMsgUnreadCounter(int64 groupId, int code, std::vector<data::MsgUnreadCounter>& counters)
	{
		if (groupId == m_cursel)
		{
			QMap<int64, FlexMessageWidget*> msgMap = m_scene->getMySendMessageWidgets();
			for (int i = 0; i < counters.size(); ++i)
			{
				data::MsgUnreadCounter counter = counters.at(i);
				int64 msgid = counter.messageId;
				FlexMessageWidget*msgWidget = msgMap.value(msgid, CNull);
				if (msgWidget != CNull)
				{
					setGroupMsgStatusTip(counter.unreadCount, counter.maxUnreadCount,msgWidget);
					AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
					if (absmsg) {
						absmsg->setSnapeId(counter.snapshotId);
					}
				}

			}
		}
	}
	void ChatContentView::onSerGetContractMaxReadId(int64 targetId, std::vector<MsgDataPtr>& msgs, int code, int64 maxMsgId)
	{
		if (targetId == m_cursel)
		{
			QMap<int64, FlexMessageWidget*> msgMap = m_scene->getMySendMessageWidgets();
			for (int i = 0; i < msgs.size(); ++i)
			{
				MsgDataPtr msg = msgs.at(i);
				if (msg && msg->isBurn) {
					continue;
				}
				int64 msgid = msg->msgId;
				FlexMessageWidget*msgWidget = msgMap.value(msgid, CNull);
				if (msgWidget) {
					if (msg->msgId <= maxMsgId)
					{
						msgWidget->setMsgStatusLblText(TEXT_TIP85);
					}
					else {
						msgWidget->setMsgStatusLblText(TEXT_TIP150);
					}
				}
			}
		}
	}

	void ChatContentView::onChangeMsgStatus(int cnt, int64 msgid)
	{
		AbstractMessageWidget* absmsg = m_scene->getMsgWidgetByMsgId(msgid);
		QMap<int64, FlexMessageWidget*> msgMap = m_scene->getMySendMessageWidgets();
		FlexMessageWidget*msgWidget = msgMap.value(msgid, CNull);
		if (msgWidget != CNull)
		{
			if (msgWidget->isBurning()) {
				return;
			}
			setGroupMsgStatusTip(cnt, absmsg->maxUnReadCount(),msgWidget);
		}
	}

	void ChatContentView::handleMsgStatusMsg(MsgDataPtr&msg)
	{
		AbstractMessageWidget* absmsg = m_scene->getMsgWidgetByMsgId(msg->msgId);
		if (absmsg)
		{
			int64 id = int64(msg->snapshotId);
			absmsg->setSnapeId(id);
			absmsg->setMaxUnReadCount(msg->maxUnReadCount);
		}
		//更新消息已读状态
		QMap<int64, FlexMessageWidget*> msgMap = m_scene->getMySendMessageWidgets();
		if (msg->isGroup)
		{
			int64 msgid = msg->msgId;
			FlexMessageWidget*msgWidget = msgMap.value(msgid, CNull);
			if (msgWidget != CNull)
			{
				if (msgWidget->isBurning()) {
					return;
				}
				int cnt = msg->unReadCount;
				setGroupMsgStatusTip(cnt,msg->maxUnReadCount,msgWidget);
				disconnect(absmsg, SIGNAL(signalChangeMsgStatus(int, int64)), this, SLOT(onChangeMsgStatus(int, int64)));
				connect(absmsg, SIGNAL(signalChangeMsgStatus(int, int64)), this, SLOT(onChangeMsgStatus(int, int64)));
			}
		}
		else {
			QList<FlexMessageWidget*> msgWidgets = msgMap.values();
			for (int i = 0; i < msgWidgets.size(); ++i)
			{
				FlexMessageWidget*msgWidget = msgWidgets.at(i);
				if (msgWidget->isBurning()) {
					return;
				}
				if (msgWidget != CNull && msg->maxUnReadCount == 1)
				{
					AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
					if (absmsg && absmsg->direction() != SpeechBubbleWidget::Center)
					{
						msgWidget->setMsgStatusLblText(TEXT_TIP85);
					}
				}
			}
		}
	}

	void ChatContentView::setGroupMsgStatusTip(int cnt,int maxCunt, FlexMessageWidget* msgWidget)
	{
		if (cnt > 0) {
			if (cnt == maxCunt - 1) {
				msgWidget->setMsgStatusLblText(ALL_UNRED_MSG);
			}
			else {
				QString readText = QString::number(cnt) + TEXT_TIP84;
				msgWidget->setMsgStatusLblText(readText);
			}
		}
		else {
			msgWidget->setMsgStatusLblText(TEXT_TIP_ALL_READ);
		}
	}

	void ChatContentView::addNotifyMsg(CSharedPtr<data::Msg>&msg)
	{
		addMsg(msg);
		if (m_chatType == 2) {
			data::Member mem;
			bool res = m_groupcontrol->GetMemberInfo(msg->targetId, msg->fromId, mem);
			if (false == res) {
				std::vector<int64> ids;
				ids.push_back(msg->fromId);
				m_groupcontrol->getBatchMemberByID(m_cursel, ids,
					CBind(&ChatContentView::signalSerGetBatchMemberByID, this,
						CPlaceholders _1, CPlaceholders _2));
			}
		}
	}

	void ChatContentView::onSerGetBatchMemberByID(int code, std::vector<CSharedPtr<data::Member> >&mems)
	{
		updateMsgItemAvatar(mems);
	}
	void ChatContentView::onSerHistoryChat()
	{
		if (m_chatType == data::ChatType::GROUP_CHAT){  //5-29
			std::string ip = m_authControl->getServerIp();
			QString url = "http://" + QString::fromStdString(ip.c_str()) + ":8888/vrvFront/groupInfoPc?groupId=" + QString::number(m_cursel);

			OpenWebDlg(url);
		}
	}

	void ChatContentView::onGetHistoryMsg(){
		//拉取消息处理
		int unreadcount = MAX_UNREADMSG_COUNT;
		getHistoryMsg(m_cursel,unreadcount,m_firstmsgid,CNull,true);
	}
	void ChatContentView::setCurSelWndId(qint64& targetid){
		m_cursel = targetid;
	}
	void ChatContentView::onMsgStatusChanged(int err,qint64 uilocalid){
		GeneralMessageItem* genMsg = CNull;
		genMsg = m_cache.GetGeneralMessageItem(uilocalid);
		if (err == Ok)
		{
			if (utils::FunctionConfig::isOnShowMsgReadStatus()) {
				if (m_cursel != m_user.selfid) {
					FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(genMsg->widget());
					if (msgWidget) {
						msgWidget->setMsgStatusLblText(TEXT_TIP150);
					}
				}
			}
			startBurnMsgTimer(genMsg);
		}
		if (CNull != genMsg)
		{
			setMessageState(genMsg,err !=0?Error:Ok);
		}
	}
	void ChatContentView::onGetMemberlist(qint64 targetid){
		BEGIN;
		    getMemberList(targetid);
		END;
	}

	void ChatContentView::getAppInfo( qint64 targetid )
	{
		if (m_chatcontrol)
		{
			m_chatcontrol->getUserInfo(targetid,0,CBind(&ChatContentView::signalSerGetAppInfo,this,CPlaceholders _1,CPlaceholders _2));
		}
	}

	void ChatContentView::onSerGetAppInfo( int code, data::UserData& data )
	{
		std::vector<CSharedPtr<data::Member>> mems = AbstractMessageWidget::GetMemberList(m_cursel);
		CSharedPtr<data::Member> user = CMakePtr<data::Member>();
		user->id = data.id;
		user->groupId = m_cursel;
		user->name = data.name;
		user->thumbAvatar = data.thumbAvatar;
		user->thumbAvatarUrl = data.thumbAvatarUrl;
		mems.push_back(user);
		onSerGetGroupMemberList(code,mems,m_cursel);
	}

	void ChatContentView::onReSendMsgClicked( GeneralMessageItem*msgItem )
	{
		if (msgItem != CNull)
		{
			FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
			AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
			if (absmsg != CNull)
			{
				absmsg->setStatus(MSG_SENDING);
				setMessageState(msgItem,Processing);
				absmsg->ReSendMsg();
			}
		}
	}

	void ChatContentView::DeleteMsg(std::vector<int64> msgIds)
	{
		if (m_chatcontrol)
			m_chatcontrol->deleteMessageById(m_cursel, msgIds, CBind(&ChatContentView::signalSerDeleteMsgById, this, CPlaceholders _1));
	}

	void ChatContentView::onRemoveMsgItem( int64 id )
	{
		int64 msgId = removeMsgFromUI(id);
		if (m_chatcontrol)
		{
			std::vector<int64> msgIds;
			msgIds.push_back(msgId);
			m_chatcontrol->deleteMessageById(m_cursel,msgIds,CBind(&ChatContentView::signalSerDeleteMsgById,this,CPlaceholders _1));
		}
	}

	void ChatContentView::onSerDeleteMsgById( int code )
	{
		AddLog(LOG_LEV_ERROR,"delete msg code:%d",code);
	}

	void ChatContentView::onRevokeMsgItem( int64 id )
	{
		GeneralMessageItem* genMsg = m_cache.GetGeneralMessageItem(id);
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(genMsg->widget());
		AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
		int64 msgId = absmsg->msgId();

		CSharedPtr<data::Msg>msg = CNull;
		CSharedPtr<data::MsgRevoke> msgTip = CMakePtr<data::MsgRevoke>();
		msgTip->targetId = m_cursel;
		msgTip->revokeMsgId = msgId;
		IUserControl_Ptr userCtrl = USERCONTROL;
		int64 svrTime = 0;
		bool ret = false;
		if (userCtrl)
		{
			ret = userCtrl->getServerTimeSync(svrTime);
		}
		msgTip->time = ret ? svrTime :QDateTime::currentMSecsSinceEpoch();
		msgTip->fromId = m_user.selfid;
		msg = msgTip;
		addMsg(msg);
	}

	/*
	void ChatContentView::onSerGrpMemInfoRefreshCb( int64 groupId, const data::Member&mems )
	{
		if (m_cursel == groupId)
		{
			if (mems.remark.isSet() || mems.thumbAvatar.isSet())
			{
				getMemberList(groupId);
			}
		}
	}*/

	void ChatContentView::onShowUserInfoWidget(int64 id, QString name, QString avatar)
	{
		m_chatcontrol->getUserInfo(id, 0, std::bind(&ChatContentView::signalSerGetUserInfo, this, std::placeholders::_1, std::placeholders::_2, id,name, avatar));
	}

	void ChatContentView::onSerGetGroupMem(int code, data::Member& mem, QString oldAvatar) {
		bool headChanged = oldAvatar != mem.thumbAvatar.value().c_str() && !mem.thumbAvatar.value().empty();
		QString sector = QString::fromUtf8(mem.sector.value().c_str());
		QString name = QString::fromUtf8(mem.remark.value().c_str());
		QString extends = QString::fromUtf8(mem.entExtends.value().c_str());
		if (!sector.isEmpty() && (gNameSectorOpen == 1)) {
			name.append("-" + sector);
		}
		if (m_pUserInfoCommiteeWidget && m_pUserInfoCommiteeWidget->isVisible()) {
			m_pUserInfoCommiteeWidget->setSector(mem.id.value(), sector);
		}
		Log(LOG_LEV_INFO, LOG_FILE, "name:%s", name.toLocal8Bit().data());
		setMemberHeadImgUpdate(mem.id.value(), mem.thumbAvatar.value(), name);
	}
	void ChatContentView::onSerGetUserInfo(int code, data::UserData& userinfo, int64 id,QString name, QString avatar)
	{
		std::string type("");
		std::string jsonstr = userinfo.entExtends.value();
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(jsonstr,root);
		if (ret)
		{
			if (root.isArray())
			{
				if (root[0]["type"].isString())
				{
					type = root[0]["type"].asString();
				}
			}
		}
		AddLog(LOG_LEV_DEBUG, "exters=%s", userinfo.entExtends.value().c_str());
		QString extends = QString::fromUtf8(userinfo.entExtends.value().c_str());
		if (type == "1")
		{
			m_pUserInfoCommomWidget = CMakePtr<UserInfoCommon>(this);
			connect(m_pUserInfoCommomWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommomWidget->setInfo(id, name, avatar, userinfo.entExtends.value());
			m_pUserInfoCommomWidget->show();
		}

		if (type =="0")
		{
			m_pUserInfoCommiteeWidget = CMakePtr<UserInfoCommitee>(this);
			connect(m_pUserInfoCommiteeWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
				this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommiteeWidget->setInfo(id, name, avatar, userinfo.entExtends.value());
			m_pUserInfoCommiteeWidget->show();
		}
		if (m_chatType == 2 && m_groupcontrol->IsInGroup(m_cursel,id)) {
			m_groupcontrol->getGroupMemberFromNet(m_cursel, id, CBind(&ChatContentView::signalSerGetGroupMem,
				this, std::placeholders::_1, std::placeholders::_2, avatar));
		}
	}

	void ChatContentView::startBurnMsgTimer( GeneralMessageItem* genMsg )
	{
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(genMsg->widget());
		AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
		if (absmsg->msg() && absmsg->msg()->isBurn)
		{ 
			int time = 20;
			if (absmsg->msgType() == data::MSG_TYPE_TEXT)
			{
				time = burnTime( QString::fromUtf8(absmsg->msg()->body.c_str()));
			}
			msgWidget->startBurnTimer(time);
		}
	}

	int ChatContentView::burnTime( QString text )
	{
		int len = text.length();
		if (len == 0){
			return 2;
		}else if (len < 20){
			return 5;
		}else if (len < 40){
			return 10;
		}else if (len < 60){
			return 15;
		}else{
			return 20;
		}
	}

	int64 ChatContentView::removeMsgFromUI(int64 id)
	{
		GeneralMessageItem* genMsg = m_cache.GetGeneralMessageItem(id);
		if (genMsg == CNull)
		{
			return 0;
		}
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(genMsg->widget());
		AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
		int64 msgId = absmsg->msgId();
		int64 targetId = absmsg->targetId();
		QGraphicsItem* gItem  = m_cache.removeMsgItem(id);
		if (gItem)
		{
			QGraphicsItem* timeItem = mMapTimeItems.value(id);
			m_cache.removeItem(timeItem);
			m_scene->removeItem(timeItem);
			mMapTimeItems.remove(id);

			m_scene->removeItem(gItem);
			m_scene->update();
			m_messageIndicatorMap.remove(genMsg);

			layoutMessageItems();
			adjustSceneHeight();
			updateSceneRect();
		}
		return msgId;
	}

	void ChatContentView::InsertMsgToUI(int64 id,CSharedPtr<data::Msg>&msg)
	{
		GeneralMessageItem* genMsg = m_cache.GetGeneralMessageItem(id);
		if (genMsg == CNull)
		{
			return ;
		}
		int width = 0;
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(genMsg->widget());
		AbstractMessageWidget* abmsg =  m_factory->GetMessageWidget(msg);
		if ( CNull == abmsg) return;
		if( data::MSG_TYPE_TEXT == abmsg->msgType()){
			connect(qobject_cast<RichTextMessageWidget*>(abmsg),SIGNAL(noticeInputEditFocus()),this,SIGNAL(noticeInputEditFocus()));
		}
		else if( data::MSG_TYPE_IMG == abmsg->msgType()){
			connect(qobject_cast<ImageMessageWidget*>(abmsg),SIGNAL(downLoadImg(int64,int64,std::string&,std::string&,bool)),this,SIGNAL(downLoadImg(int64,int64,std::string&,std::string&,bool)));
		}
		else if (data::MSG_TYPE_CARD == abmsg->msgType())
		{
			connect(qobject_cast<CardMessageWidget*>(abmsg),SIGNAL(showUserInfoWidget(int64, QString, QString)),this,SLOT(onShowUserInfoWidget(int64, QString, QString)));
		}
		if (msg->isBurn && msg->isRecvMsg)
		{
			connect(qobject_cast<BurnMessageWidget*>(abmsg),SIGNAL(viewBurnMsg(CSharedPtr<data::Msg>&)),this,SIGNAL(viewBurnMsg(CSharedPtr<data::Msg>&)));
		}
		msgWidget->addMessageWidget(abmsg);	

		m_scene->update();		
		updateSceneRect();
	}

	void ChatContentView::useByCombineMsgWin()
	{
		m_loading->setVisible(false);
		mUseByCombineMsgWin = true;
	}

	void ChatContentView::setMemberHeadImgUpdate(int64 userid, const std::string&head, QString name)
	{
		QList<QGraphicsItem*> messagelist = m_cache.GetMessageList();
		QList<QGraphicsItem*>::const_iterator msgItemIter = messagelist.begin();
		while (msgItemIter != messagelist.end()) {
			QGraphicsItem* item = *msgItemIter;
			if (GENERAL_MSG == item->type()) {
				GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(*msgItemIter);
				FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
				AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
				if (absmsg->sendId() == userid) {
					if (!head.empty()) {
						msgWidget->setAvatar(QPixmap(head.c_str()));
						absmsg->setAvatar(head.c_str());
					}
					if (!name.isEmpty()) {
						msgWidget->setName(name);
					}
				}
			}
			++msgItemIter;
		}
	}
	void ChatContentView::updateMsgItemNameAndAvatar( QMap<int64,data::UserData>mapData )
	{
		QList<QGraphicsItem*> messagelist =  m_cache.GetMessageList();
		QList<QGraphicsItem*>::const_iterator msgItemIter = messagelist.begin();
		while (msgItemIter != messagelist.end()){
			QGraphicsItem* item = *msgItemIter;
			if ( GENERAL_MSG == item->type()) {
				GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(*msgItemIter);
				FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
				AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
				int64 userId = absmsg->msg()->fromId;
				data::UserData data = mapData.value(userId);
				msgWidget->setName(QString::fromUtf8(data.name.value().c_str()));
				msgWidget->setAvatar(QPixmap(transfer(data.thumbAvatar.value().c_str())));
				absmsg->setAvatar(transfer(data.thumbAvatar.value().c_str()));
			}
			++msgItemIter;
		}
	}

	void ChatContentView::ResetChickFeather(CSharedPtr<data::Msg>&msg, int64 type)
	{
		if(m_chatcontrol)
			if(type == data::MSG_TYPE_TIP_READED)
				m_chatcontrol->GetMessages(m_cursel, msg->relatedMsgId, 1, 2, std::bind(&ChatContentView::signalSerSearchGetMessage,this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
		    if(type == data::MSG_TYPE_TIP_NOREAD)
				m_chatcontrol->GetMessages(m_cursel, msg->relatedMsgId, 1, 2, std::bind(&ChatContentView::signalSerSearchSendedGetMessage,this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));	
	}

	void ChatContentView::onSerSearchGetMessage(int code, int64 targetid, std::vector<CSharedPtr<data::Msg>>& msgs)
	{
		if(!code && msgs.size() > 0)
		{
			CSharedPtr<data::Msg> msg = msgs[0];
			int64 uilocalid = m_cache.GetLocalIdByMsgId(msg->msgId);
			GeneralMessageItem* genMsg = m_cache.GetGeneralMessageItem(uilocalid);
			if (genMsg == CNull)
			{
				return ;
			}
			FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(genMsg->widget());
			msgWidget->SetChickFeather();
			m_scene->update();
			msg->isFeather = data::MSG_TYPE_TIP_READED;
			if(m_chatcontrol)
				m_chatcontrol->updateMsg(msg);
		}
	}

	void ChatContentView::onSerSearchSendedGetMessage(int code, int64 targetid, std::vector<CSharedPtr<data::Msg>>& msgs)
	{
		if(!code && msgs.size() > 0)
		{
			CSharedPtr<data::Msg> msg = msgs[0];
			int64 uilocalid = m_cache.GetLocalIdByMsgId(msg->msgId);
			GeneralMessageItem* genMsg = m_cache.GetGeneralMessageItem(uilocalid);
			if (genMsg == CNull)
			{
				return ;
			}
			FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(genMsg->widget());
			msgWidget->SetChickSendedMsg();
			m_scene->update();
			msg->isFeather = data::MSG_TYPE_TIP_READED;
			if(m_chatcontrol)
				m_chatcontrol->updateMsg(msg);
		}
	}

	void ChatContentView::onUpdateSendMsgTime( qint64 localId,qint64 time )
	{
		QGraphicsTextItem* item = (QGraphicsTextItem*)mMapTimeItems.value(localId);
		if (item != CNull)
		{
			QString strTime = DealMsgTime(time,CHATWND_TIME);
			item->setPlainText(strTime);
		}
	}

	void ChatContentView::DelUpfileUi(int64 Uilocalid)
	{
		int64 TUilocalid = m_cache.GetLocalIdByMsgId(Uilocalid);
		GeneralMessageItem* genMsg = m_cache.GetGeneralMessageItem(TUilocalid);
		if (genMsg == CNull)
		{
			return;
		}
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(genMsg->widget());
		AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
		absmsg->RevokeMessage();
		//m_SendLocalidUiMap.erase(Uilocalid);
	}

}