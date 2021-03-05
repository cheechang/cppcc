#include "AppMenuButton.h"
#include "json.h"
#include "common/Controlptr.h"
#include <QDateTime>
namespace ui{
	AppMenuButton::AppMenuButton(QWidget *parent)
		: QPushButton(parent)
	{
		//this->setContextMenuPolicy(Qt::CustomContextMenu);

		this->setObjectName("AppMenuButton");
		mIcon = new QLabel(this);
		mIcon->setPixmap(QPixmap(":/chat/appMenus"));
		mTitle = new QLabel(this);
		mLayout = new QHBoxLayout(this);
		mLayout->setContentsMargins(0,0,0,0);
		mLayout->addStretch();
		mLayout->addWidget(mIcon);
		mLayout->addWidget(mTitle);
		mLayout->addStretch();
		setLayout(mLayout);
		connect(this,SIGNAL(clicked(bool)),this,SLOT(onClicked()));
		mMenu = CNull;
		//this->connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showMenu(const QPoint&)));
	}

	AppMenuButton::~AppMenuButton()
	{

	}

	void AppMenuButton::setData( data::AppMenuData&data )
	{
		mData = data;
		if (data.name.empty())
		{
			mTitle->setVisible(false);
			return;
		}
		if (data.sub_menu.empty())
		{
			mIcon->hide();
		}
		mTitle->setText(QString::fromUtf8(data.name.c_str()));
	}

	void AppMenuButton::onClicked()
	{
		//
		if (mData.hasSubMenu)
		{
			AppMenu* appMenu  = new AppMenu(CNull,mData);
			connect(appMenu,SIGNAL(openUrl(std::string)),this,SIGNAL(openUrl(std::string)));
			mMenu = appMenu->menu();
			makeSubMenus(appMenu,mData);
			QPoint pos = QCursor::pos();
			int count = mMenu->actions().size();
			pos.setY(pos.y() - count*mMenu->height());
			mMenu->exec(pos);
		}else{
			if (mData.type != "view")
			{
				IChatMgrControl_Ptr chatCtrl = CHATMGRCONTROL;
				CSharedPtr<data::Msg>msg;
				CSharedPtr<data::MsgText> textMsg= CMakePtr<data::MsgText>();
				textMsg->body = mData.key;
				textMsg->targetId = mData.appId;
				textMsg->isRbtMsg = true;

				IUserControl_Ptr userCtrl = USERCONTROL;
				int64 svrTime = 0;
				bool ret = false;
				if (userCtrl)
				{
					ret = userCtrl->getServerTimeSync(svrTime);
				}
				svrTime = ret ? svrTime :QDateTime::currentMSecsSinceEpoch();

				textMsg->time = svrTime;
				textMsg->fromId = userCtrl->GetAccountInfo()->id.value();
				textMsg->localId = svrTime;

				msg = textMsg;
				chatCtrl->SendMessage(msg,CNull);
				//emit openUrl("http://172.16.16.130:8080/");
			}else{
				emit openUrl(mData.url);
			}
		}
	}

	void AppMenuButton::makeSubMenus( QWidget*parent,data::AppMenuData parentData )
	{
		Json::Reader reader;
		Json::Value obj;
		if (reader.parse(parentData.sub_menu,obj))
		{
			if (obj.isArray())
			{
				int count = obj.size();
				for (int i=0;i<count;++i)
				{
					Json::Value val = obj[i];
					if (val.isObject())
					{
						data::AppMenuData data;
						data.name = val["name"].asString();
						data.type = val["type"].asString();
						data.appId = parentData.appId;
						if (val.isMember("sub_menu"))
						{
							data.sub_menu =  val["sub_menu"].toStyledString();
							data.hasSubMenu = true;
						}else{
							data.sub_menu  = "[]";
						}
						if (val.isMember("url"))
						{
							data.url = val["url"].asString();
						}
						if (val.isMember("key"))
						{
							data.key = val["key"].asString();
						}
						AppMenu* subMenu = new AppMenu(parent,data);
						connect(subMenu,SIGNAL(openUrl(std::string)),this,SIGNAL(openUrl(std::string)));
						if (data.hasSubMenu)
						{
							makeSubMenus(subMenu,data);
						}
						
					}
				}
			}
		}
	}

	AppMenu::AppMenu(QWidget*parent,data::AppMenuData data ):QWidget(parent)
	{
		mData = data;
		if (data.hasSubMenu)//ÓÐ×Ó²Ëµ¥
		{
			mMenu = new QMenu(this);
			mMenu->setTitle(QString::fromUtf8(data.name.c_str()));
			if (parent == CNull)
			{
				return;
			}
			AppMenu* menu = (AppMenu*)parent;
			if (menu->menu())
			{
				menu->menu()->addMenu(mMenu);
			}
			
		}else{
			mAction = new QAction(QString::fromUtf8(data.name.c_str()),this);
			connect(mAction,SIGNAL(triggered()),this,SLOT(onClicked()));
			AppMenu* menu = (AppMenu*)parent;
			menu->menu()->addAction(mAction);
		}
	}

	AppMenu::~AppMenu()
	{

	}

	void AppMenu::onClicked()
	{
		if (mData.type != "view")
		{
			IChatMgrControl_Ptr chatCtrl = CHATMGRCONTROL;
			CSharedPtr<data::Msg>msg;
			CSharedPtr<data::MsgText> textMsg= CMakePtr<data::MsgText>();
			textMsg->body = mData.key;
			textMsg->targetId = mData.appId;
			textMsg->isRbtMsg = true;

			IUserControl_Ptr userCtrl = USERCONTROL;
			int64 svrTime = 0;
			bool ret = false;
			if (userCtrl)
			{
				ret = userCtrl->getServerTimeSync(svrTime);
			}
			svrTime = ret ? svrTime :QDateTime::currentMSecsSinceEpoch();

			textMsg->time = svrTime;
			textMsg->fromId = userCtrl->GetAccountInfo()->id.value();
			textMsg->localId = svrTime;

			msg = textMsg;
			chatCtrl->SendMessage(msg,CNull);
		}else{
			emit openUrl(mData.url);
		}
	}

}