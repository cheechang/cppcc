#include "MsgManagerWidget.h"

#include "common/Common.h"
#include "MsgManagerListItem.h"
#include <QDateTime>
#include <QListWidgetItem>
#include <QStringList>
#include <QTextCursor>

namespace ui{
	MsgManagerWidget::MsgManagerWidget(QWidget *parent):BaseWindow(parent)
	{
		connect(this, SIGNAL(closeClicked()),this, SLOT(close()));
		setFixedSize(660,495);//(660,495)（2020年9月23日）
		setTitle(transfer("消息管理器"));
		Init();
	}

	MsgManagerWidget::~MsgManagerWidget()
	{

	}

	void MsgManagerWidget::Init()
	{
		
		m_Funclayout = new QHBoxLayout();
		m_TimeLabel = new QLabel(transfer("范围："));
		m_TimeLabel->setFixedHeight(28);

		m_TimeRangBox =  new QComboBox();
		m_TimeRangBox->setFixedSize(85,28);
		QStringList list;
		list << transfer("近一个月") << transfer("近三个月") << transfer("近半年") << transfer("全部");
		m_TimeRangBox->addItems(list);

		m_deleteBtn = new QPushButton();
		m_deleteBtn->setIcon(QPixmap(QString(":/chat/delete")));
		m_deleteBtn->setObjectName("ClearEdit");

		m_SerchTextEdit = new QLineEdit();
		m_SerchTextEdit->setFixedSize(387,28);
		m_SerchTextEdit->setPlaceholderText(transfer("请输入搜索关键字"));

		m_SerchBtn = new QPushButton(transfer("搜 索"));
		m_SerchBtn->setObjectName("sendbtn");
		m_SerchBtn->setFixedSize(80,28);

		m_Funclayout->addWidget(m_TimeLabel);
		m_Funclayout->addWidget(m_TimeRangBox);
		m_Funclayout->addWidget(m_SerchTextEdit);
		m_Funclayout->addWidget(m_deleteBtn);
		m_Funclayout->addWidget(m_SerchBtn);
		m_Funclayout->addStretch();
		m_Funclayout->setSpacing(8);
		m_Funclayout->setContentsMargins(14,0,15,0);
		Funcwidget = new QWidget();
		Funcwidget->setFixedHeight(40);
		Funcwidget->setLayout(m_Funclayout);

		m_Frideshowlayout = new QVBoxLayout();
		m_Frideshowlayout->setContentsMargins(0,0,0,0);
		m_Frideshowlayout->setSpacing(0);
		m_SerchResultlbl = new QLabel(transfer("搜索结果："));
		m_SerchResultlbl->setObjectName("Promptbel");
		m_SerchResultlbl->setFixedHeight(28);
		m_FridelistWidget = new QListWidget(this);
		m_FridelistWidget->setObjectName("ListScrollBar");

		m_Frideshowlayout->addWidget(m_SerchResultlbl);
		m_Frideshowlayout->addWidget(m_FridelistWidget);
		Frideshowwidget = new QWidget();
		Frideshowwidget->setFixedWidth(150);
		Frideshowwidget->setLayout(m_Frideshowlayout);

		m_MsgContentShowEdit = new QTextEdit();
		m_MsgContentShowEdit->setReadOnly(true);

		m_MsgContentShowEdit->setContentsMargins(15,8,15,8);

		m_Msgshowlayout =  new QVBoxLayout();
		m_Msgshowlayout->setContentsMargins(0,0,0,0);
		Msgshowwidget = new QWidget();
		m_Msgshowlayout->addWidget(m_MsgContentShowEdit);
		Msgshowwidget->setLayout(m_Msgshowlayout);


		m_FrideMsgLayout = new QHBoxLayout();
		m_FrideMsgLayout->addWidget(Frideshowwidget);
		m_FrideMsgLayout->addWidget(Msgshowwidget);
		m_FrideMsgLayout->setContentsMargins(0,0,0,0);
		m_FrideMsgLayout->setSpacing(0);

		FrideMsgshowwidget = new QWidget();
		FrideMsgshowwidget->setLayout(m_FrideMsgLayout);

		mMainLayout->addWidget(Funcwidget);
		mMainLayout->addWidget(FrideMsgshowwidget);

		m_chatcontrol = CHATMGRCONTROL;
		m_contactcontrol = CONTACTMGRCONTROL;
		m_usercontrol = USERCONTROL;
		connect(m_SerchBtn, SIGNAL(clicked()), this, SLOT(onSerSerchMsg()));
		CONNECT_SERVICE(SerchGlobalMsg(int, data::MsgSearchResult&))
		CONNECT_SERVICE(SerchDetailMsg(int, data::MsgDetailSearchResult&));
		CONNECT_SERVICE(GetUserInfo(int, data::UserData&,CSharedPtr<data::Msg>));

		connect(m_FridelistWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onSerClickItem(QListWidgetItem*)));
		connect(m_deleteBtn,SIGNAL(clicked()), this, SLOT(onSerClearBtnClicked()));
		if(m_usercontrol)
		{
			CSharedPtr<data::AccountInfo> userinfo = m_usercontrol->GetAccountInfo();
			m_curUserId = userinfo->id.value();
		}
	}

	void MsgManagerWidget::onSerSerchMsg()
	{
		clearlist();

		
		QDateTime currentDateTime = QDateTime::currentDateTime();
		if(!m_chatcontrol)
			return;
 		std::string key = m_keyword = m_SerchTextEdit->text().toUtf8().data();
		if(key == "")
		{
			return;
		}

		if(0 == m_TimeRangBox->currentIndex())
		{
			m_starttime = currentDateTime.addMonths(-1).toTime_t();
		}

		if(1 == m_TimeRangBox->currentIndex())
		{
			m_starttime = currentDateTime.addMonths(-3).toTime_t();
		}

		if(2 == m_TimeRangBox->currentIndex())
		{
			m_starttime = currentDateTime.addMonths(-6).toTime_t();
		}

		if(3 == m_TimeRangBox->currentIndex())
		{
			m_starttime = 0;
			m_endtime = 0;
		}
		else
		{
			m_endtime = currentDateTime.toTime_t();
		}
		data::MsgSearchProperty msgProperty;
		msgProperty.start_time = m_starttime;
		msgProperty.end_time = m_endtime;
		msgProperty.targetid = 0;
		msgProperty.count = 0;

		m_chatcontrol->searchMessage(key, msgProperty, std::bind(&MsgManagerWidget::signalSerSerchGlobalMsg,this, std::placeholders::_1, std::placeholders::_2));
	}

	void MsgManagerWidget::onSerSerchGlobalMsg(int code, data::MsgSearchResult& msg)
	{
		m_NextTargetid = msg.nextTargetId;

		for(int i=0; i<msg.infos.size(); i++)
		{
			if (msg.infos.at(i).simpleInfo.name.empty()) {
				continue;
			}
			addListItem(msg.infos.at(i).simpleInfo.avatar, msg.infos.at(i).simpleInfo.name,msg.infos.at(i).targetId,msg.infos.at(i).count);
		}
	}

	void MsgManagerWidget::addListItem(std::string head, std::string name, int64 id,int CountMsg)
	{
		QListWidgetItem* item = new QListWidgetItem();
		MsgManagerListItem* widget = new MsgManagerListItem(this,id);
		QString headstr;
		if(head == "")
		{
			headstr = DEFAULT_AVATAR;
		}
		else
		{
			headstr = transfer(head.c_str());
		}
		widget->SetData(headstr, QString::fromUtf8(name.c_str()),CountMsg);
		item->setSizeHint(QSize(150,43));
		m_FridelistWidget->addItem(item);
		m_FridelistWidget->setItemWidget(item, widget);
	}

	void MsgManagerWidget::clearlist()
	{
		for(int i=0; i<m_FridelistWidget->count();i++)
		{
			QListWidgetItem* item = m_FridelistWidget->item(i);
			QWidget* widget = m_FridelistWidget->itemWidget(item);

			if(CNull != item)
			{
				delete item;
				item = NULL;
			}

			if(CNull != widget)
			{
				delete widget;
				widget = NULL;
			}
		}
		m_FridelistWidget->clear();
		m_MsgContentShowEdit->clear();
	}


	void MsgManagerWidget::onSerSerchDetailMsg(int code, data::MsgDetailSearchResult& detailmsg)
	{
		data::Contact userInfo;

		for(int i=0; i<detailmsg.msgs.size(); i++)
		{
			int64 userid = detailmsg.msgs.at(i)->fromId;
			int64 msgid = detailmsg.msgs.at(i)->msgId;
			m_chatcontrol->getUserInfo(userid, msgid,std::bind(&MsgManagerWidget::signalSerGetUserInfo,this, std::placeholders::_1, std::placeholders::_2,detailmsg.msgs.at(i)));
		}
	}

	void MsgManagerWidget::onSerClickItem(QListWidgetItem* item)
	{
		m_MsgContentShowEdit->clear();
		MsgManagerListItem* widget = (MsgManagerListItem*)m_FridelistWidget->itemWidget(item);
		int64 targetid = widget->GetTargetid();
		int countmsg = widget->GetCountMsg();
		if(m_chatcontrol)
		{
			data::MsgDetailSearchProperty detailMsgPro;
			detailMsgPro.targetid = targetid;

			detailMsgPro.start_time = m_starttime;
			detailMsgPro.end_time = m_endtime;
			detailMsgPro.count = countmsg;

			m_chatcontrol->searchDetailMessage(m_keyword,detailMsgPro, std::bind(&MsgManagerWidget::signalSerSerchDetailMsg,this, std::placeholders::_1, std::placeholders::_2));
		}
	}

	void MsgManagerWidget::MsgShowDeal(CSharedPtr<data::Msg> msg, std::string username)
	{
		std::string msgText = msg->body;
		QString timestr = QDateTime::fromMSecsSinceEpoch(msg->time).toString("MM/dd hh:mm");
		QString headlbl = QString::fromUtf8(username.c_str()) + " " + timestr;
		QString Content = QString::fromUtf8(msgText.c_str());
		QString htmlhead;
		QString setColorstr;
		if(m_curUserId == msg->fromId)
		{
			setColorstr = "color:#5DBD84;";
		}
		else
		{
			setColorstr = "color:#3495E4;";
		}

		if(m_MsgContentShowEdit->toPlainText().isEmpty())
		{
			htmlhead = "<p style='" + setColorstr +"font-size:14px;margin:3;'>" + headlbl + "</p>" + "<p style='color:#555555;font-size:12px;margin:3;text-indent:2em;'>" + Content + "</p>";
			
		}
		else
		{
			htmlhead = "<br/><p style='" + setColorstr +"font-size:14px;margin:3;'>" + headlbl + "</p>" + "<p style='color:#555555;font-size:12px;margin:3;text-indent:2em;'>" + Content + "</p>";
		}
		m_MsgContentShowEdit->insertHtml(htmlhead);
	}

	void MsgManagerWidget::onSerGetUserInfo(int code, data::UserData& usrdata,CSharedPtr<data::Msg> msg)
	{
		if(!code)
		{
			MsgShowDeal(msg,usrdata.name.value());
		}	
	}

	void MsgManagerWidget::keyPressEvent(QKeyEvent * event)
	{
		if(event->key() == Qt::Key_Return)
		{
			onSerSerchMsg();
		}
	}

	void MsgManagerWidget::onSerClearBtnClicked()
	{
		m_SerchTextEdit->clear();
	}


}
