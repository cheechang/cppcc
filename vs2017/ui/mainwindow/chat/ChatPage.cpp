#include "ChatPage.h"
#include "ChatWidget.h"
#include "controls/DefaultWidget.h"
#include "data/ChatData.h"
#include "data/ContactData.h"
#include "chatList/ChatListWidget.h"
#include "common/UIUtils.h"
#include "mainwindow/ScreenShot.h"
#include "globalshortcut/qxtglobalshortcut.h"
#include "mainwindow/systemmsg/SystemMsgPage.h"
#include "../contact/group/GroupInforSettingArea.h"
#include "../MainWindow.h"
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QDesktopServices>
#include <QApplication>
#include <QClipboard>
#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QSplitter>
#include <QSound>
#include <QTimer>
#include <QTextStream>
#include <log.h>
#include <utils/common.h>
#include "json.h"
#include <qmessagebox.h>
#include  "controls/PushButton.h"

int gNameSectorOpen = 0;
namespace ui{
	ChatPage::ChatPage(QWidget*parent):QWidget(parent),m_chatlist(CNull),
	m_userInfo(CNull),m_stack(CNull),m_default(CNull),m_mainlayout(CNull),
	m_chatcontrol(CNull),m_usercontrol(CNull),m_IntervalTime(true),m_soundPlay(CNull),m_bPlaySound(true){

		m_chatlist = CMakePtr<ChatListWidget>(this);//
		m_sysMsgPaget = CNull;
		m_stack    = CMakePtr<QStackedWidget>(this);
		m_default  = CMakePtr<DefaultWidget>(this);
		//m_sysMsgPaget = CMakePtr<SystemMsgPage>(this);
		m_splitter  =  new QSplitter(Qt::Horizontal,this);
		m_mainlayout = CMakePtr<QVBoxLayout>(this);
		m_screenprocess = CMakePtr<ScreenShot>(this);
		m_screenprocess->InitSreenShotProcess();

		QPalette palette;
		palette.setBrush(QPalette::Window, QBrush(Qt::white));
		m_stack->setPalette(palette);
		m_stack->setAutoFillBackground(true);
		m_stack->setContentsMargins(0,0,0,0);
		m_stack->addWidget(m_default.get());
		//m_stack->addWidget(m_sysMsgPaget.get());
 
		m_stack->setCurrentWidget(m_default.get());

		m_chatlist->setMinimumSize(290,370);
		m_chatlist->setMaximumWidth(290);

		connect(m_chatlist.get(), SIGNAL(noticeTrayFlash(bool)), 
			this, SIGNAL(signalNotifyTrayFlash(bool)));
		connect(m_chatlist.get(), SIGNAL(palySound()), 
			this, SLOT(onStartPlayNotifySound()));
		connect(m_chatlist.get(), SIGNAL(unreadMsgCount(int)), 
			this, SIGNAL(unreadMsgCount(int)));
		connect(m_chatlist.get(), SIGNAL(RemoveChat(int64)), 
			this, SLOT(onRemoveChat(int64)));
		connect(m_chatlist.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), 
			this, SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
		connect(this, SIGNAL(addChatListItem(CSharedPtr<data::ChatInfo>&)), 
			m_chatlist.get(),SLOT(onAddChatListItem(CSharedPtr<data::ChatInfo>&)));
		connect(this, SIGNAL(signalSerCloseSession(int64)), m_chatlist.get(), SLOT(onItemDelete(int64)));

		m_splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);  
		m_splitter->addWidget(m_chatlist.get());
		m_splitter->addWidget(m_stack.get());
		m_splitter->setChildrenCollapsible(false);
		m_splitter->setOpaqueResize(true);
		QList<int> list_src;
		list_src.append(270);// 230);
		list_src.append(840);// 550);
		m_splitter->setSizes(list_src);
		m_splitter->setHandleWidth(1);
		m_splitter->setStyleSheet("QSplitter:handle{background:transparent;}");
		m_splitter->handle(1)->setCursor(Qt::SizeHorCursor);


		m_mainlayout->addWidget(m_splitter);
		m_mainlayout->setContentsMargins(0,0,0,0);
		m_mainlayout->setSpacing(0);
		setLayout(m_mainlayout.get());
		m_stack->setCurrentIndex(DEFAULTPAGE);

		QString applicationPath = QCoreApplication::applicationDirPath();

        m_soundTime = new QTimer();
		m_soundPlay = new QSound(applicationPath + "/msg.wav", this);

        QObject::connect(m_soundTime, SIGNAL(timeout()), this, SLOT(onSoundTimeOut()));

		m_chatcontrol = CHATMGRCONTROL;
		m_usercontrol = USERCONTROL;
		m_userInfo = m_usercontrol->GetAccountInfo();

		CONNECT_SERVICE(MsgNotify(CSharedPtr<data::Msg>));
		CONNECT_SERVICE(RegOperateUserCb(data::AccountInfo&));
		m_chatcontrol->RegRecvMsgNotice(CBind(&ChatPage::signalSerMsgNotify,this,CPlaceholders  _1));
		m_usercontrol->regOperateUserCb(CBind(&ChatPage::signalSerRegOperateUserCb,this,CPlaceholders  _1));
		
		mContactControl = CONTACTMGRCONTROL;
		if (CNull != mContactControl)
		{
			CONNECT_SERVICE(NameSectorExtendedField(int, std::vector<data::EnterpriseDictionary>&));
			CONNECT_SERVICE(OperateBuddyCb(int, const data::Contact&));
			mContactControl->RegOperateBuddyCb(CBind(&ChatPage::signalSerOperateBuddyCb,this,CPlaceholders _1,CPlaceholders _2));
		
			CONNECT_SERVICE(ContactHeadImgUpdateCb(int64, const std::string&));
			mContactControl->RegContactHeadImgUpdateCb(CBind(&ChatPage::signalSerContactHeadImgUpdateCb, this, CPlaceholders  _1, CPlaceholders  _2));
		}

		mGroupControl = GROUPMGRCONTROL;
		if (CNull != mGroupControl)
		{
			CONNECT_SERVICE(GroupRefreshNotify(int8, const data::Group&));
			CONNECT_SERVICE(GrpMemInfoRefreshCb(int64 , const data::Member&));
			CONNECT_SERVICE(MemberHeadImgUpdateCb(int64, const std::string&));
			mGroupControl->RegMemberHeadImgUpdateCb(CBind(&ChatPage::signalSerMemberHeadImgUpdateCb,
				this,CPlaceholders _1,CPlaceholders _2));
			mGroupControl->RegGroupRefreshCb(CBind(&ChatPage::signalSerGroupRefreshNotify,
				this,CPlaceholders  _1,CPlaceholders  _2));
			mGroupControl->RegGrpMemInfoRefreshCb(CBind(&ChatPage::signalSerGrpMemInfoRefreshCb,this,CPlaceholders _1,CPlaceholders _2));
		}
	}
	ChatPage::~ChatPage(){
		if (CNull != m_screenprocess)
		{
			m_screenprocess->CloseScreenshot();
		}
		if ( CNull != m_splitter)
		{
			m_splitter->deleteLater();
		}
	}

	void ChatPage::onSerNameSectorExtendedField(int code, std::vector<data::EnterpriseDictionary>&dicts)
	{
		if (dicts.size() > 0) {
			data::EnterpriseDictionary dict = dicts.at(0);
			Log(LOG_LEV_INFO,LOG_FILE,"key:%s,value:%d",dict.dickey.c_str(),dict.extend.c_str());
			if (dict.extend == "1") {
				gNameSectorOpen = 1;
			}
			else {
				gNameSectorOpen = 0;
			}
		}
	}
	void ChatPage::onSendSuggestionMsg(CSharedPtr<data::ChatInfo>&chat, QString& filepath)
	{
		onStartChat(chat);
		std::vector<int64> atlist;
		atlist.clear();
		m_chatwnd[chat->targetid]->SendSuggestionFile(data::MSG_TYPE_FILE,filepath,atlist);
	}

	void ChatPage::onStartChat(CSharedPtr<data::ChatInfo>&chat){

		AddLog(LOG_LEV_INFO, "Into ChatPage onStartChat");
		if (!chat->targetid)return;
		m_cursel = chat->targetid;

		typedef CSharedPtr<data::ChatData> DataPtr;
	 
		DataPtr data = m_chatlist->m_mapData.value(m_cursel);

		if (data){
			if (chat->name == ""){
				chat->chatType = (data::ChatType)data->chatType;
				chat->avatar = utils::FileIsExist(data->thumbAvatar.value().c_str()) ? data->thumbAvatar.value() : "";
				chat->name = QString::fromUtf8(data->name.value().c_str()).toStdString();
				chat->targetid = data->id.value();
				chat->unreadcount = data->realUnReadCnt;
				chat->msgid = data->lastMsgId;
			}
		}
		else { 
			if (chat->chatType == data::GROUP_CHAT){
				//<====2019-5-31  重新获得group信息
				data::Group groupinfo;
				mGroupControl->GetGroupInfo(chat->targetid, groupinfo);
 				chat->isStartChat = true;
 				chat->name = QString::fromUtf8(groupinfo.info.value().groupName.value().data()).toStdString();
				chat->avatar = groupinfo.info.value().avatar.value();
			}
		}

		if (chat->isStartChat)
		{
			emit turnPage(CHAT_PAGE);
		}
		if (chat->targetid == SYSMSG_ID)
		{
			//系统消息页面
			if (m_sysMsgPaget == CNull) {
				m_sysMsgPaget = CMakePtr<SystemMsgPage>(this);
				m_sysMsgPaget->InitData(/*chat->msgid*/);
				m_stack->addWidget(m_sysMsgPaget.get());
			}
			m_stack->setCurrentWidget(m_sysMsgPaget.get());
			SystemMsgPage::isSysPageSelect = true;
			return;
		}
		else if (m_chatwnd.contains(chat->targetid))
		{
			AddLog(LOG_LEV_INFO,"Into ChatPage m_stack->setCurrentWidget(m_chatwnd[chat->targetid].get())");
			SystemMsgPage::isSysPageSelect = false;
			m_stack->setCurrentWidget(m_chatwnd[chat->targetid].get());
			addIsReceiptMsgToUi(chat->targetid);
		}
		else
		{
			SystemMsgPage::isSysPageSelect = false;
			CSharedPtr<ChatWidget> chatwnd  = CMakePtr<ChatWidget>(this);
			connect(this,SIGNAL(sendMsgHotKeyUpdate(int)),chatwnd.get(),SIGNAL(sendMsgHotKeyUpdate(int)));
			connect(chatwnd.get(),SIGNAL(openUrl(std::string)),this,SLOT(onOpenUrl(std::string)));
			connect(chatwnd.get(), SIGNAL(signalShakeWin()),this, SIGNAL(signalShakeWin()));
            connect(this, SIGNAL(signalSendMsgShot(int)),chatwnd.get(), SIGNAL(signalSendMsgShot(int)));
			connect(chatwnd.get(),SIGNAL(addChatListItem(CSharedPtr<data::ChatInfo>&)),
				this,SIGNAL(addChatListItem(CSharedPtr<data::ChatInfo>&)));
			connect(chatwnd.get(),SIGNAL(signalScreenShot(int)),this,SLOT(onScreenShotBtnClicked(int)));
			connect(chatwnd.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
				this, SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
			connect(chatwnd.get(), SIGNAL(viewBurnMsg(CSharedPtr<data::Msg>&)),
				this, SIGNAL(viewBurnMsg(CSharedPtr<data::Msg>&)));
			connect(chatwnd.get(), SIGNAL(addIsReceiptMsg(int64)), this, SLOT(onAddIsReceiptMsg(int64)));
			chatwnd->setSupportStretch(false);
			chatwnd->StartChat(chat);
			chatwnd->SetUserInfo(m_userInfo->id.value(),transfer(utils::GetHeadPath(m_userInfo->gender.value(), m_userInfo->thumbAvatar.value().data()).c_str()),QString::fromUtf8(m_userInfo->name.value().data()));
			chatwnd->getTopMsg();
			m_chatwnd.insert(chat->targetid,chatwnd);
			m_stack->addWidget(chatwnd.get());
			m_stack->setCurrentWidget(chatwnd.get());

			//拉取消息处理
			bool ishistory = chat->unreadcount>0?false:true;
			int unreadcount = chat->unreadcount>0?chat->unreadcount:3;
			if (GetGroupSetInfo(chat->targetid) != -1)
			{
				chatwnd->setNoMoreState(true);
				if (unreadcount > MAX_UNREADMSG_COUNT) {
					unreadcount = MAX_UNREADMSG_COUNT;
				}
				AddLog(LOG_LEV_INFO,LOG_FILE,"chat open 1:getHistoryMsg");
				chatwnd->getHistoryMsg(chat->targetid, unreadcount, chat->msgid, chat, ishistory,true);
			}
			else{
				chatwnd->setNoMoreState(false);
			}
		}
		m_chatwnd[chat->targetid]->setCurSelWndId(m_cursel);
		m_chatlist->setSelectItem(chat->targetid);
		m_chatwnd[chat->targetid]->DealReplyChickFeather();

		if(chat->chatType == data::GROUP_CHAT)
		{
			m_chatwnd[chat->targetid]->onSerbtnCloseSession(false);
			int type = GetGroupSetInfo(chat->targetid);
			if (type == 0){
				m_chatwnd[chat->targetid]->SetNotSpeak(false,0);
			}
			
			if (type == -1){
				m_chatwnd[chat->targetid]->SetNotSpeak(true,-1);
			}

			if (type == 1){
				m_chatwnd[chat->targetid]->SetNotSpeak(true,1);
			}
		}

		/*if((mContactControl && mContactControl->ContactIsBuddy(chat->targetid)) || !GetUserInfolevel())
		{
			
			//m_chatwnd[chat->targetid]->onSerbtnCloseSession(false);
			
		}
		else
		{
			m_chatwnd[chat->targetid]->onSerbtnCloseSession(true);
		}
		*/
		//获取是否显示界别
		if (mContactControl) {
			mContactControl->queryExtendedField("nameSector", -2,CBind(&ChatPage::signalSerNameSectorExtendedField,this,
				CPlaceholders _1,CPlaceholders _2));
		}
	}

	void ChatPage::addIsReceiptMsgToUi(int64 targetId)
	{
		QList<CSharedPtr<data::Msg>> msgs = m_cacheIsReceipt.value(targetId);
		CSharedPtr<ChatWidget> chatwnd = m_chatwnd.value(targetId,NULL);
		if (NULL == chatwnd){
			return;
		}
		for (int i = 0; i < msgs.size(); ++i){
			chatwnd->setIsReceipt(msgs.at(i));
		}
		msgs.clear();
		m_cacheIsReceipt[targetId] = msgs;
	}

	void ChatPage::onAddIsReceiptMsg(int64 targetId)
	{
		addIsReceiptMsgToUi(targetId);
	}
	void ChatPage::onRemoveChat(int64 targetId){
		if (m_chatwnd.contains(targetId))
		{
			if ( CNull != m_chatwnd[targetId])
			{
				m_cacheDelWnds.push_back(m_chatwnd[targetId]);
				m_stack->removeWidget(m_chatwnd[targetId].get());
			}
			m_chatcontrol->RemoveChat(targetId);
			m_chatwnd.remove(targetId); //2019-6-26 暂时不删除
		}
		if(m_chatwnd.count() == 0){//删除完毕
			m_stack->setCurrentWidget(m_default.get());
		}
	}

	bool ChatPage::dealMeetNoStartMsg(int64 targetId, bool isGroup)
	{
		if (isGroup && GetGroupSetInfo(targetId) != -1)
			return true;
		else
			return false;
	}

   void ChatPage::onSerMsgNotify(CSharedPtr<data::Msg>msg){
	  
	   if(CNull == msg) return;

	   if (msg->isGroup)
	   {
		   if (!dealMeetNoStartMsg(msg->targetId, msg->isGroup)){
			   return;
		   }
	   }

	   if(onSerCheckIsCloseSession(msg))
		   return ;
	   Log(LOG_LEV_INFO, LOG_FILE, "msgtype:%d,subType:%d", msg->msgType,msg->subType);
	   if (msg->msgType == MSG_TYPE_SYS && m_sysMsgPaget)
	   {
		  // m_sysMsgPaget->recvMsgNotice(msg);
	   }

	   if (m_chatwnd.contains(msg->targetId))
	   {
		   m_chatwnd[msg->targetId]->SetMsg(msg);
		   if (msg->isRecvMsg && msg->isReceipt && (m_cursel != msg->targetId)){
			   addIsReceiptMsg(msg);
		   }
	   }
	   else{
		   if (msg->isRecvMsg && msg->isReceipt){
			   addIsReceiptMsg(msg);
		   }
	   }
	   //单条消息设置已读
	   if (m_cursel == msg->targetId)
	   {
		   
		   if (ui::MainWindow::mIsCurChatPage)
		   {
			   m_chatcontrol->setMessageRead(msg->targetId,msg->msgId);
			   if (msg->isRecvMsg && msg->isReceipt){
				   m_chatwnd[msg->targetId]->setIsReceipt(msg);
			   }
		   }
	   }
	   if (!msg->isDeviceMsg && msg->body == SHAKE_TEXT)
	   {
		   emit signalShakeWin();
	   }
   }

   void ChatPage::addIsReceiptMsg(CSharedPtr<data::Msg>msg)
   {
	   QList<CSharedPtr<data::Msg>> msgs = m_cacheIsReceipt.value(msg->targetId);
		msgs.push_back(msg);
		m_cacheIsReceipt[msg->targetId] = msgs;
   }

   void ChatPage::onScreenShoot(int code, QProcess::ExitStatus status){
	   BEGIN;
	   //为1说明是按了取消按钮或者ESC取消截图
	   if (1 == code)
	   {
		   return;
	   }
	   QString strSavePath = "";
	   strSavePath = QString::fromUtf8(USERIMGPATH) + "cache/";
	   QDir tempDir;
	   if (!tempDir.exists(strSavePath))
	   {
		   tempDir.mkdir(strSavePath);
	   }
	   QString tempPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/temp_screenshot.png";
#if defined(__APPLE__)
	   tempPath.replace("Application Support", "Containers/com.vrv.linkood/Data/");
#endif
	   strSavePath = strSavePath + "temp_" + QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch()) + ".png";
	   //tempPath = tempPath.replace(APP_NAME,"Linkdood-Xp");
	   //拷贝文件到指定目录下
	   QFile::copy(tempPath, strSavePath);
	   //删除临时文件
	   QFile::remove(tempPath);
	   ///判断文件是否存在
	   QFileInfo fileInfo(strSavePath);
	   if (!fileInfo.exists())
	   {
		   return;
	   }
	   else
	   {
		   if ( CNull !=  m_chatwnd[m_cursel])
		   {
			  m_chatwnd[m_cursel]->setScreenShotImage(strSavePath);
		   }
	   }
	   //设置剪切板
	   QClipboard *board = QApplication::clipboard();
	   QImage tempImg(strSavePath);
	   board->setImage(tempImg);
	END;
   }
   void ChatPage::onScreenShotBtnClicked(int flag){
	   onStartScreenShot();
   }
   void ChatPage::onStartScreenShot(){
	   m_screenprocess->InitSreenShotProcess();
	   m_screenprocess->ShootScreen(this);
   }
   void ChatPage::setSupportStretch(bool isSupportStretch){
	   this->setMouseTracking(isSupportStretch);
	   // 这里对子控件也进行了设置，是因为如果不对子控件设置，当鼠标移动到子控件上时，不会发送mouseMoveEvent事件，也就获取不到当前鼠标位置，无法判断鼠标状态及显示样式了。
	   QList<QWidget*> widgetList = this->findChildren<QWidget*>();
	   for each (QWidget* widget in widgetList)
	   {
		   widget->setMouseTracking(isSupportStretch);
	   }
   }

   void ChatPage::onSerRegOperateUserCb( data::AccountInfo&accountInfo )
   {
	   if (accountInfo.thumbAvatar.isSet())
	   {
		   m_userInfo->thumbAvatar = accountInfo.thumbAvatar;
	   }
	   if (accountInfo.name.isSet())
	   {
		   m_userInfo->name = accountInfo.name;
	   }
	   
	  QList<CSharedPtr<ChatWidget> > wnds = m_chatwnd.values();
	  for (int i=0;i<wnds.size();++i)
	  {
		  CSharedPtr<ChatWidget> wnd = wnds.at(i);
		  if(wnd != CNull){
			  wnd->SetUserInfo(m_userInfo->id.value(),utils::GetHeadPath(m_userInfo->gender.value(),m_userInfo->thumbAvatar.value().data()).c_str(),QString::fromUtf8(m_userInfo->name.value().data()));
		  }
	  }
	  
   }

   void ChatPage::onSerContactHeadImgUpdateCb(int64 id, const std::string& head)
   {
	   qDebug() << Q_FUNC_INFO << "id:" << id << ",th:" << head.c_str();
	   QString avatar = head.c_str();
	   if (avatar.isEmpty())
	   {
		   avatar = DEFAULT_AVATAR;
	   }
	   QList<CSharedPtr<ChatWidget> > wnds = m_chatwnd.values();
	   for (int i = 0; i<wnds.size(); ++i)
	   {
		   CSharedPtr<ChatWidget> wnd = wnds.at(i);
		   if (wnd != CNull && wnd->targetId() == id){
			   TargetInfo info;
			   info.targetAvatar = avatar;
			   wnd->setTargetInfo(info, true);
			   break;
		   }
	   }
	   onSerMemberHeadImgUpdateCb(id, head);
   }

   void ChatPage::onSerMemberHeadImgUpdateCb(int64 userid, const std::string&head) {
	   QList<CSharedPtr<ChatWidget> > wnds = m_chatwnd.values();
	   for (int i = 0; i < wnds.size(); ++i)
	   {
		   CSharedPtr<ChatWidget> wnd = wnds.at(i);
		   if (wnd != CNull) {
			   wnd->setMemberHeadImgUpdate(userid, head);
		   }
	   }
   }

   void ChatPage::onSerOperateBuddyCb( int type, const data::Contact& contact )
   {
	   Log(LOG_LEV_DEBUG, LOG_FILE, "onSerOperateBuddyCb type=%d", type);
	   if (type == 1)
	   {
		   //m_sysMsgPaget->dealAddFridenSysMsg(contact.id.value());
	   }
	   if (type == 2)//更新
	   {
		   if (contact.remark.isSet()||contact.thumbAvatar.isSet())
		   {
			   QString remark = QString::fromUtf8(contact.remark.value().c_str());
			   if (remark.isEmpty())
			   {
				   remark = QString::fromUtf8(contact.name.value().c_str());
			   }
			   QString avatar = transfer(contact.thumbAvatar.value().c_str());
			   if (avatar.isEmpty())
			   {
				   avatar = DEFAULT_AVATAR;
			   }
			 
			   Log(LOG_LEV_DEBUG, LOG_FILE, "onSerOperateBuddyCb avatar=%s", avatar.data());
			   QList<CSharedPtr<ChatWidget> > wnds = m_chatwnd.values();
			   for (int i = 0;i<wnds.size();++i)
			   {
				   CSharedPtr<ChatWidget> wnd = wnds.at(i);
				   if(wnd != CNull && wnd->targetId() == contact.id.value()){
					   TargetInfo info;
					   info.targetName = remark;
					   info.targetAvatar = avatar;
					   wnd->setTargetInfo(info,true);
					   break;
				   }
			   }
		   }
	   }
   }

   void ChatPage::onSerGroupRefreshNotify( int8 type, const data::Group&group )
   {
	   if (type == 2)
	   {
		   QList<CSharedPtr<ChatWidget> > wnds = m_chatwnd.values();
		   for (int i = 0;i<wnds.size();++i)
		   {
			   CSharedPtr<ChatWidget> wnd = wnds.at(i);
			   if(wnd != CNull && wnd->targetId() == group.info.value().groupId.value() && group.info.value().groupName.isSet()){
				   TargetInfo info;
				   info.targetName = QString::fromUtf8(group.info.value().groupName.value().c_str());
				   info.targetAvatar = group.info.value().avatar.value().c_str();
				   wnd->setTargetInfo(info,false);
				   break;
			   }
			   if(wnd != CNull && wnd->targetId() == group.info.value().groupId.value() ){
				   wnd->onSerGroupRefreshUpdate(type,group);
			   }
		   }
	   }
   }

   void ChatPage::onSerGrpMemInfoRefreshCb( int64 groupId, const data::Member&mems )
   {
	   QList<CSharedPtr<ChatWidget> > wnds = m_chatwnd.values();
	   for (int i=0;i<wnds.size();++i)
	   {
		   CSharedPtr<ChatWidget> wnd = wnds.at(i);
		   if(wnd != CNull && wnd->targetId() == groupId){
				wnd->updateGroupMemInfo(mems);
				if (mems.thumbAvatar.isSet()) {
					wnd->setMemberHeadImgUpdate(mems.id.value(), mems.thumbAvatar.value());
				}
		   }
	   }
   }

   void ChatPage::onSoundTimeOut()
   {
       m_IntervalTime = true;
       //停止运行定时器
       if (m_soundTime->isActive())
           m_soundTime->stop();
   }

   void ChatPage::onStartPlayNotifySound()
   {
       if (m_IntervalTime && m_soundPlay)
       {
           m_IntervalTime = false;
           m_soundPlay->play();
           //开始运行定时器，定时时间间隔为5000ms
           if (!m_soundTime->isActive())
           {
               m_soundTime->start(5000);
           }
       }
   }

   void ChatPage::onMsgSoundPlay( bool isPlay )
   {
       m_bPlaySound = isPlay;
   }

   void ChatPage::onOpenUrl( std::string url )
   {
	   AddLog(LOG_LEV_INFO,"===========open url:%s",url.c_str());
	   //url = "http://172.16.16.130:8080";
	   mAppWebView.setUrl(QUrl(url.c_str()));
	   mAppWebView.show();
   }

   void ChatPage::onSerDelUiFile(int64 filelocalid,int64 targetid)
   {
	   if(m_chatwnd.contains(targetid))
		   m_chatwnd[targetid]->DelUpFileUi(filelocalid);
   }

   void ChatPage::onSerByTargetIdChat(int64 targetid)
   {
	   CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
	   data::Group groupinfo;
	   mGroupControl->GetGroupInfo(targetid,groupinfo);
	   
	   chat->targetid = targetid;
	   chat->isStartChat = true;
	   chat->chatType = data::GROUP_CHAT;
	   chat->name = QString::fromUtf8(groupinfo.info.value().groupName.value().data()).toStdString();
	   chat->avatar = groupinfo.info.value().avatar.value();
	   onStartChat(chat);
   }

   int ChatPage::GetGroupSetInfo(int64 targetid)
   {
	   LOG_METHOD("ChatPage::GetGroupSetInfo", LOG_FILE);
	   data::Group groupInfo;
	   mGroupControl->GetGroupInfo(targetid, groupInfo);
	   QString  ExtentdContent = QString::fromStdString(groupInfo.extend.value());
	   QString groupName = QString::fromUtf8(groupInfo.info.value().groupName.value().c_str());
	   AddLog(LOG_LEV_INFO,LOG_FILE,"groupInfo:%s,name:%s", ExtentdContent.toStdString().c_str(), groupName.toLocal8Bit().data());
	   if (groupInfo.info.value().type.value() != 2 || ExtentdContent.isEmpty() )
	   {
		   return 0;
	   }
	   QStringList list = ExtentdContent.split(',');
	   int64 StartTime=0;
	   int64 EndTime=0;
	   if(list.size() == 2)
	   {
		   StartTime = list.at(0).toLongLong();
		   EndTime = list.at(1).toLongLong();
	   }
	   	   
	   int64 mCurrentTime = 0; //// QDateTime::currentMSecsSinceEpoch();   2019-5-20 bxy change
	   bool ret = m_usercontrol->getServerTimeSync(mCurrentTime);
	   if (!ret)
	   {
		   AddLog(LOG_LEV_ERROR, "ChatPage::GetGroupSetInfo getServerTimeSync failed");
		   return -1;
	   }

	   if (mCurrentTime < StartTime)
	   {
		   return -1;
	   }

	   if (mCurrentTime > EndTime)
	   {
		   return 1;
	   }

	   if(mCurrentTime>=StartTime && mCurrentTime<=EndTime)
	   {
		   return 0;
	   }
   }

   bool ChatPage::onSerCheckIsCloseSession(CSharedPtr<data::Msg>msg)
   {
	   QString CheckStr = transfer("[[结束会话]]");
	   QString text = QString::fromUtf8(msg->body.c_str());
	   if(CheckStr == text)
	   {
		   emit signalSerCloseSession(msg->targetId);
		   return true;
	   }
	   return false;
   }

   void ChatPage::onMainWindowDeactivate()
   {
	   mainWinPosChanged();
   }

   void ChatPage::mainWinPosChanged()
   {
	   CSharedPtr<ChatWidget> chatWin = m_chatwnd.value(m_cursel, CNull);
	   if (chatWin != CNull){
		   chatWin->setAtListVisible(false);
	   }
   }


   bool ChatPage::GetUserInfolevel()
   {
	   LOG_METHOD("ChatPage::GetUserInfolevel", LOG_FILE);
	   CSharedPtr<data::AccountInfo> Udata;
	   Udata = m_usercontrol->GetAccountInfo();

	   std::string ExtendInfoJson = Udata->extends.value();
	   Json::Reader reader;
	   Json::Value root,fieldsarry, mJvalue;
	   AddLog(LOG_LEV_INFO,LOG_FILE,"user extends json=%s", ExtendInfoJson.c_str());
	   int ret = reader.parse(ExtendInfoJson, root);
	   if (!ret)
	   {
		   AddLog(LOG_LEV_ERROR,"json parse filed,err=%d,json=%s",ret,ExtendInfoJson.c_str());
			return false;
	   }
	   else
	   {
		   if (ExtendInfoJson.find("closeSession") != -1) {
			   int level;
			   if (root.isMember("closeSession") && root["closeSession"].isInt())
			   {
				   level = root["closeSession"].asInt();
			   }
			   if (level == 1)
				   return true;
			   else
				   return false;
		   }
		   else {
			   return false;
		   }
		 
	   }
	   
	   
   }

   QHBoxLayout  *ChatPage::initLocalSearchLayout()
   {
	   QHBoxLayout *search_layout = new QHBoxLayout(this);
	   QPushButton *mBtnLocalSearch = new QPushButton(this);
	   mBtnLocalSearch->setObjectName("localsearchbtn");
	   mBtnLocalSearch->setStyleSheet("background:rgb(228,228,228)");
	   PushButton *m_searchBtnLogo = new PushButton(mBtnLocalSearch);
	   m_searchBtnLogo->setPicName(":/title/search");
	   mBtnLocalSearch->setFixedWidth(200);// LeftContentWidth - 60);
	   search_layout->addWidget(mBtnLocalSearch);
	   search_layout->addWidget(m_searchBtnLogo);
	   mBtnLocalSearch->setToolTip(transfer("搜索联系人、组织成员和群"));
	   connect(mBtnLocalSearch, SIGNAL(clicked(bool)), this, SLOT(onSearchBtnClicked()));
	   ///search_layout->setContentsMargins(5, 25, 5, 10);

	 
	   PushButton *min_button = new PushButton(this);
	   PushButton *max_button = new PushButton(this);
	   PushButton *close_button = new PushButton(this);

	   min_button->setPicName(QString(":/title/min"));
	   max_button->setPicName(QString(":/title/max"));
	   close_button->setPicName(QString(":/title/close"));

	   connect(min_button, SIGNAL(clicked()), this, SIGNAL(showMin()));
	   connect(max_button, SIGNAL(clicked()), this, SLOT(onMaxWiget()));
	   connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeWidget()));

	   QHBoxLayout *top_layout = new QHBoxLayout(this);
	   top_layout->addStretch();
	   top_layout->addWidget(min_button, 0, Qt::AlignVCenter);
	   top_layout->setSpacing(5);
	   top_layout->addWidget(max_button, 0, Qt::AlignVCenter);
	   top_layout->setSpacing(5);
	   top_layout->addWidget(close_button, 0, Qt::AlignVCenter);
	   top_layout->setSpacing(5);
	   top_layout->setContentsMargins(0, 0, 0, 0);
	   close_button->setMinimumHeight(30);
	   close_button->setMaximumHeight(30);

	   search_layout->addLayout(top_layout);

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


}