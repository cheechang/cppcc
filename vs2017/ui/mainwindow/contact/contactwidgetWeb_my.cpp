#include "ContactWidgetWeb_my.h"
#include "common/controlptr.h"
#include "../enterprise/EnterpriseWidget.h"
#include "../controls/DefaultWidget.h"
#include "../enterprise/enterpriseinfowidget.h"
#include "ContactTabWidgetAreaWeb.h"
#include "group/GroupInforWidget.h"
#include "friend/FriendInfoWidgetWeb.h"
#include "friend/AppInfoWidget.h"
#include "friend/EnterpriseAccountList.h"
#include "friend/AppAccountList.h"
#include "friend/FriendListWidgetWeb.h"
#include "searchcontact/SearchContactWindow.h"
#include "createGroup/CreateGroupWindow.h"
#include <QHBoxLayout>
#include <QSize>
#include <QResizeEvent>
#include <qsettings>
#include  "controls/PushButton.h"
#include "common/Common.h"
#include "QtWebEngineWidgets\qwebenginesettings.h"





namespace ui{
	ContactWidgetWeb_my::ContactWidgetWeb_my(QWidget *parent)
		: QWidget(parent)
		,m_ismax(false)
	{
		
		////bool flag = qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "3333");

		//////setMinimumWidth(RightContentWidth);
		m_mainLayout = CMakePtr<QHBoxLayout>();


		QVBoxLayout *left_layout = new QVBoxLayout();   //中心区域

		////left_layout->addLayout(initLocalSearchLayout());
		/////zleft_layout->addStretch();
		
	 	m_listWidget = CMakePtr<ui::FriendListWidgetWeb>(this);

		m_listWidget->setFixedWidth(LeftContentWidth);
 
		m_listWidget->setObjectName("bg_fa");

		connect(m_listWidget.get(), SIGNAL(showContactInfoPage(data::Contact)), this, SLOT(onShowContactInfoPage(data::Contact)));

		left_layout->addWidget(m_listWidget.get());
	    left_layout->setContentsMargins(0, 0, 1,0);

		
	 	m_defaultWidget = CMakePtr<ui::DefaultWidgetWeb>(this);
	
		m_mainLayout->addLayout(left_layout);// List 区域

		/* 
		PushButton *min_button = new PushButton(this);
		PushButton *max_button = new PushButton(this);
		PushButton *close_button = new PushButton(this);

		m_max_button = max_button;
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
		right_layout->addLayout(top_layout);*/
		///right_layout->addStretch();


		QVBoxLayout *right_layout = new QVBoxLayout();
		right_layout->addWidget(m_defaultWidget.get());   //Web 区域

		m_defaultWidget->setContentsMargins(0, 0, 0, 0);

		right_layout->setContentsMargins(0, 0, 0, 0);

		m_mainLayout->addLayout(right_layout);
	 
		////// ＝＝＝＝＞channel  2019-3-22
		m_webchannel = CMakePtr<QWebChannel>(this);
		m_webchannel->registerObject(QStringLiteral("cppObject"), this);
		////// ＜＜＜＜＝＝＝＝　channel  2019-3-22


		/////QHBoxLayout  *contactLayout = new QHBoxLayout();
 
		m_mainLayout->setSpacing(0);
		m_mainLayout->setContentsMargins(0,0,0,0);
 
		this->setLayout(m_mainLayout.get());

 

		connect(this, SIGNAL(GetControlInfo(QString &text)), this, SLOT(onGetControlInfo(QString &text)));
		connect(this, SIGNAL(MySelectListItem(int item)), m_listWidget.get(), SLOT(onMySelectListItem(int item)));





		m_enterpriseAccountList = CMakePtr<EnterpriseAccountList>(this);
		/////m_enterpriseAccountList->setMinimumWidth(RightContentWidth);
		m_enterpriseAccountList->setVisible(false);

	}

	ContactWidgetWeb_my::~ContactWidgetWeb_my()
	{

	}

	void ContactWidgetWeb_my::sendTextToCpp(const QString &text)
	{
		//onTurnPage(1);
		onTurnPage(0);
		CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
		chat->chatType = data::GROUP_CHAT;
		chat->isStartChat = true;
		//chat->avatar = itemData.head;
		//chat->name = itemData.enName;
		//chat->targetid = itemData.userID;
		//chat->targetid = 21265121852;
	 
		chat->targetid = text.toLongLong();
		chat->name = "";
		emit startChat(chat);
	}
 
	void ContactWidgetWeb_my::callQTProcess(const QString &taskid,const QString &text)
	{
		m_TaskID = taskid;

		QString str;
		str = text.section(':', 0, 0);   // str == "surname"
		
		if (str == QString::fromLocal8Bit("getAppList")){
			QString res;
			QMap<int64, data::Contact> ::Iterator it = m_enterpriseAccountList->m_mapData.begin();
			while (it != m_enterpriseAccountList->m_mapData.end())
			{
				int64 appid = it.key();//"AA"
				res+=QString::number(appid, 10);
				
				data::Contact &c = (data::Contact)it.value();
				QString name = QString::fromUtf8(c.name.value().c_str());
				res += ":";
				res += name;
				res += "|";
  				it++;
			}
			emit  sendToWeb(m_TaskID,res);
			return;
 		} 

		if (str == QString::fromLocal8Bit("getAppInfo")){
			IUserControl_Ptr mUserControl;
			mUserControl = USERCONTROL;
			str = text.section(':',1,1);   // str == "surname"
			int64 appid = str.toLongLong();
			if (appid){
				m_AppInfo.clear();
			
				mUserControl->getAppInfo(appid, CBind(&ContactWidgetWeb_my::onGetAppInfo, this, CPlaceholders  _1, CPlaceholders  _2));
			}
			else {
				emit  sendToWeb(m_TaskID,m_AppInfo);
			}
			return;
		}
		if (str == QString::fromLocal8Bit("getUserInfo")){
 			IUserControl_Ptr mUserControl;
			mUserControl = USERCONTROL;
			CSharedPtr<data::AccountInfo> user = mUserControl->GetAccountInfo();
			QString info = QString::number(user->id.value(), 10);;
			info += ":";
			QString name = QString::fromStdString(user->name.value());
			info += name;
			emit  sendToWeb(m_TaskID,info);
			return;
		}
 

  		emit  sendToWeb(m_TaskID,transfer("没有数据"));
	}
 
	void ContactWidgetWeb_my::OnGetControlInfo(const QString &text)
	{
		emit  sendToWeb(m_TaskID,text);
	}
	void ContactWidgetWeb_my::onGetAppInfo(int64 code, data:: EntAppinfo& app)
	{
	 	QString res;
		res = QString::number(app.appID, 10);
	 	QString token  = QString::fromStdString(app.appToken);
		res += ":";
		res += token;
		m_AppInfo = res;
		emit GetControlInfo(m_AppInfo);

	/*	if (res ==QString("")){
			emit  sendToWeb(transfer("没有数据"));
		}
		else {
			emit  sendToWeb(res);
		}
		*/
	 
	}
	void ContactWidgetWeb_my::onTurnPage(int i)
	{
		QPoint pos;
		data::Contact  aa;
		if (i != APP_PAGE){
			// 切换的时候 处理Web网页
			m_defaultWidget->setUrl(aa, pos, NULL);
		}
		else {
			////// emit showContactInfoPage(mMapData.value(widget->id()));
			m_Pos = this->pos();
			aa.server = m_listWidget->m_homeurl.toStdString();
			onShowContactInfoPage(aa);
			m_listWidget->mListWidget->setCurrentRow(0);
			/*if (m_defaultWidget->m_webEngineView){
				onShowContactInfoPage(m_listWidget->mMapData.value(1));
			}
			else {

			}
			*/
			
			////emit  MySelectListItem(1);
		}
	}/*
	void ContactWidgetWeb_my::onShowOrgUserInfoPage(data::OrgAndUserInfo user)
	{
		m_contactInfoWidget->setVisible(false);
		m_defaultWidget->setVisible(false);
		
		m_enterpriseInfoWidget->setVisible(true);
		m_groupInforWidget->setVisible(false);
		m_appInfoWidget->setVisible(false);
		m_enterpriseAccountList->setVisible(false);
		m_appAccountList->setVisible(false);
		m_enterpriseInfoWidget->updateData(user);
		
	}*/
	/* 
	void ContactWidgetWeb_my::onShowGroupInforPage(int64 groupId)
	{
		if(groupId == 0){
			m_defaultWidget->setVisible(true);
			m_contactInfoWidget->setVisible(false);
	 		m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(false);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(false);
			m_appAccountList->setVisible(false);
	 		}else{
			m_defaultWidget->setVisible(false);
			m_contactInfoWidget->setVisible(false);
	 			m_enterpriseInfoWidget->setVisible(false);
			m_groupInforWidget->setVisible(true);
			m_groupInforWidget->updateData(groupId);
			m_appInfoWidget->setVisible(false);
			m_enterpriseAccountList->setVisible(false);
			m_appAccountList->setVisible(false);
	 		}
	}
	*/
	
	void ContactWidgetWeb_my::resizeEvent(QResizeEvent *e)
	{
		///m_btnAddContact->move(m_leftTabWidgetArea->size().width()- m_btnAddContact->width()-20,
		////		m_leftTabWidgetArea->size().height()- m_btnAddContact->height()-20);
	    m_defaultWidget->resize();
		QWidget::resizeEvent(e);
	}
/*
	void ContactWidgetWeb_my::onBtnAddClicked()
	{
		QPoint pos(m_btnAddContact->x()-m_menuMain->width(),m_btnAddContact->y());
		pos = mapToGlobal(pos);
		m_menuMain->exec(pos);
	}

	void ContactWidgetWeb_my::onBtnCreateGroup()
	{
		mWinCreateGroup->showWin();
	}

	void ContactWidgetWeb_my::onBtnAddFrindOrGroup()
	{
		m_searchContactWin = CMakePtr<SearchContactWindow>();
		m_searchContactWin->show();
	}
	*/
	void ContactWidgetWeb_my::onShowContactInfoPage(data::Contact contact)
	{
		//m_defaultWidget->setVisible(true);
		m_defaultWidget->setUrl(contact, m_Pos, &m_webchannel);

		/*m_enterpriseInfoWidget->setVisible(false);
		m_groupInforWidget->setVisible(false);
		m_contactInfoWidget->setVisible(true);
		m_appInfoWidget->setVisible(false);
		m_enterpriseAccountList->setVisible(false);
		m_appAccountList->setVisible(false);
		//m_contactInfoWidget->updateData(contact);
		m_contactInfoWidget->setVisible(false);
		*/
	}
	/* 
	void ContactWidgetWeb_my::onShowAddContactOrCreateGroup(int type)
	{
		if (type == 1)
		{
			onBtnAddFrindOrGroup();
		}else{
			onBtnCreateGroup();
		}
	}
	*/


	QHBoxLayout  *ContactWidgetWeb_my::initLocalSearchLayout()
	{
		QHBoxLayout *search_layout = new QHBoxLayout(this);
	
		QPushButton *mBtnLocalSearch = new QPushButton(this);
		mBtnLocalSearch->setObjectName("localsearchbtn");

		mBtnLocalSearch->setStyleSheet("background:rgb(228,228,228)");
 
		PushButton *m_searchBtnLogo = new PushButton(mBtnLocalSearch);
		m_searchBtnLogo->setPicName(":/title/search");
		mBtnLocalSearch->setFixedWidth(LeftContentWidth - 60);
		search_layout->addWidget(mBtnLocalSearch);
		search_layout->addWidget(m_searchBtnLogo);
		mBtnLocalSearch->setToolTip(transfer("搜索联系人、组织成员和群"));
		connect(mBtnLocalSearch, SIGNAL(clicked(bool)), this, SLOT(onSearchBtnClicked()));
		search_layout->setContentsMargins(5, 25, 5,10);
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
	void ContactWidgetWeb_my::onMaxWiget()
	{
		m_ismax = !m_ismax;
		if (m_ismax)
		{
			m_max_button->setPicName(QString(":/title/restore"));
		}
		else{
			m_max_button->setPicName(QString(":/title/max"));
		}
		//m_max_button->setFixedHeight(30);
		emit maxWiget();
	}

}