#include <QApplication>
#include <QDesktopWidget>
#include "UserInfoCommitee.h"
#include "headimage.h"
#include "../mainwindow/UserHeadImg.h"
#include "../mainwindow/contact/searchcontact/AddContactWindow.h"
#include "../common/Common.h"
#include "json.h"
#include <log/log.h>
const int CONTENTWIDTH = 190;
namespace ui
{
	UserInfoCommitee::UserInfoCommitee(QWidget *parent)
	: TWidget(parent)
	, m_id(0)
	, m_sex(transfer("女"))
	{
		m_memberNum = transfer("无");
		this->setObjectName("UserInfoWidget");
		m_closeAfterChat = true;
		Qt::WindowFlags flags = this->windowFlags();
		//flags |= Qt::Popup;
		///flags |= Qt::WindowStaysOnTopHint;
		flags |= Qt::Dialog;
		flags |= Qt::WindowCloseButtonHint;
		flags &= ~Qt::WindowMaximizeButtonHint;
		flags &= ~Qt::WindowMinimizeButtonHint;
 		this->setWindowFlags(flags);
		this->setWindowTitle(transfer("详细信息"));
		this->setFixedSize(300,524);

		m_pContactControl = CONTACTMGRCONTROL;
		CONNECT_SERVICE(AddContactResult(int));
		CONNECT_SERVICE(GetBuddyInfoFromNetResult(int, data::Contact&));

		initWidget();
		initLayout();
	}

	UserInfoCommitee::~UserInfoCommitee()
	{
	}
	void UserInfoCommitee::setAfterChatStatus(bool isClose)
	{
		m_closeAfterChat = isClose;
	}
	void UserInfoCommitee::ParseJsonGetUserInfo(std::string jsoninfo)
	{ 
		QString jsonInStr = QString::fromUtf8(jsoninfo.c_str());
		Json::Reader  reader;
		Json::Value root;
		bool ret = reader.parse(jsoninfo, root);
		if (!ret)
		{
			return;
		}

		if (root.isArray())
		{
			for (int i = 0; i < root.size(); i++)
			{
				if (root[i]["nation"].isString())
				{
					m_nation = QString::fromUtf8(root[i]["nation"].asString().data());
				}

				if (root[i]["gender"].isString())
				{
					m_sex = QString::fromUtf8(root[i]["gender"].asString().data());
				}

				if (root[i]["CPPCCPosition"].isString())
				{
					m_position = QString::fromUtf8(root[i]["CPPCCPosition"].asString().data());
				}

				if (root[i]["sector"].isString())
				{
					m_sector = QString::fromUtf8(root[i]["sector"].asString().data());
				}

				if (root[i]["group"].isString())
				{
					m_group = QString::fromUtf8(root[i]["group"].asString().data());
				}

				if (root[i]["specialCommittee"].isString())
				{
					m_specialCommittee = QString::fromUtf8(root[i]["specialCommittee"].asString().data());
				}

				if (root[i]["specialCommitteeDuty"].isString())
				{
					m_specialCommitteeDuty = QString::fromUtf8(root[i]["specialCommitteeDuty"].asString().data());
				}

				if (root[i]["currentPosition"].isString())
				{
					m_currentPosition = QString::fromUtf8(root[i]["currentPosition"].asString().data());
				}
				
				if (root[i]["myLocation"].isString())
				{
					m_myLocation = QString::fromUtf8(root[i]["myLocation"].asString().data());
				}
				if (root[i]["memberNum"].isString())
				{
					m_memberNum = QString::fromUtf8(root[i]["memberNum"].asString().data());
				}
				break;
			}
		}
	}

	void UserInfoCommitee::setInfo(const int64 id, const QString name, const QString avatar, std::string userinfo)
	{
		ParseJsonGetUserInfo(userinfo);

		m_id = id;
		m_pLabelName->setText(name);
		m_pAvatar->setAvatarPath(avatar);
		m_pLabelmemNum->setText(m_memberNum);
		m_pLabelSex->setText(m_sex);    //性别
		m_pLabelNation->setText(m_nation);  //民族
		m_pLabelposition->setText(m_position);  //职务
		m_pLabelsector->setText(m_sector);    //界别
		m_pLabelgroup->setText(m_group);  //组别
		m_pLabelspecialCommittee->setText(m_specialCommittee);    //专委会
		m_pLabelspecialCommitteeDuty->setText(m_specialCommitteeDuty);   //专委会职务
		m_pLabelcurrentPosition->setText(m_currentPosition);  //现任职务
		m_pLabelmyLocation->setText(m_myLocation);    //所在地		

		if(m_pContactControl != CNull)
		{
			/* 是好友显示发起会话 */
			if(m_pContactControl->ContactIsBuddy(m_id))
			{
				m_pButtonAdd->hide();
				/*m_pButtonAdd->setText(transfer("发起会话"));
				m_pButtonAdd->disconnect();
				connect(m_pButtonAdd, SIGNAL(clicked()), this, SLOT(onStartChatClicked()));
				*/
				data::Contact contact;
				m_pContactControl->GetContactInfo(id, contact);
				this->setContact(contact, name, transfer(contact.thumbAvatar.value().c_str()));
				if (contact.isApp.value() == 1)
				{
					m_pButtonSendMsg->setText(transfer("进入公众号"));
				}
				
			}
			/* 是陌生人显示添加好友 */
			else
			{
				/*m_pButtonAdd->setText(transfer("添加到联系人"));
				m_pButtonAdd->disconnect();
				connect(m_pButtonAdd, SIGNAL(clicked()), this, SLOT(onAddClicked()));*/
				m_pButtonAdd->show();
				m_pContactControl->GetBuddyInfoFromNet(id, 
					CBind(&UserInfoCommitee::signalSerGetBuddyInfoFromNetResult,
					this, CPlaceholders  _1, CPlaceholders  _2));
			}
		}

		if (m_pLabelcurrentPosition->width() > CONTENTWIDTH)
		{
			m_pLabelspecialCommitteeDuty->resize(m_pLabelcurrentPosition->width(), m_pLabelspecialCommitteeDuty->height() + 12);
			m_pLabelspecialCommitteeDuty->adjustSize();
		}

		if (m_pLabelspecialCommitteeDuty->width() > CONTENTWIDTH)
		{
			m_pLabelspecialCommitteeDuty->resize(m_pLabelspecialCommitteeDuty->width(), m_pLabelspecialCommitteeDuty->height() + 12);
			m_pLabelspecialCommitteeDuty->adjustSize();
		}
		
		this->adjustSize();
	}

	void UserInfoCommitee::show(const QPoint& point)
	{
		/* ID为自己时不弹 */
		IUserControl_Ptr userControl = USERCONTROL;
		if(userControl)
		{
			CSharedPtr<data::AccountInfo> account = userControl->GetAccountInfo();
			int64 id = account->id.value();
			if (id == m_id)
			{
				return;
			}
		}

		/* 超出屏幕上移 */
		QPoint validPoint = point == QPoint(0, 0) ? QCursor::pos() : point;
		QDesktopWidget *deskWgt = QApplication::desktop();
		if (deskWgt != CNull)
		{
			int height = this->height();
			if (validPoint.y() + this->height() > deskWgt->availableGeometry(validPoint).height())
			{
				int y = deskWgt->availableGeometry(validPoint).height() - this->height()+30;
				validPoint.setY(y);
			}
		}

		this->move(validPoint);
		TWidget::show();
	}

	void UserInfoCommitee::show(const int64 id, const QString name, const QString avatar, const QPoint& point)
	{
		this->setInfo(id, name, avatar);
		this->show(point);
	}

	void UserInfoCommitee::onSerGetBuddyInfoFromNetResult(int code, data::Contact& contact)
	{
		if (code == 0)
		{
			this->setContact(contact);
		}
	}

	void UserInfoCommitee::focusOutEvent(QFocusEvent* event)
	{
		this->hide();
		event->accept();
	}

	void UserInfoCommitee::initWidget()
	{
		m_pMainLayout = new QVBoxLayout(this);
		m_pLabelHeadBackground = new QLabel(this);
		m_pAvatar = new HeadImage(this);
		m_pLabelName = new QLabel(this);
		m_pInfoLayout = new QFormLayout(this);
		m_pLabelSex = new QLabel(this); //性别
		m_pLabelNation = new QLabel(this);   //民族
		m_pLabelposition = new QLabel(this);  //职位
		m_pLabelmemNum = new QLabel(this);
		m_pLabelsector = new QLabel(this);    //界别
		m_pLabelgroup = new QLabel(this); //组族
		m_pLabelspecialCommittee = new QLabel(this);   //专委会
		m_pLabelspecialCommitteeDuty = new QLabel(this);   //专委会职务
		m_pLabelcurrentPosition = new QLabel(this);  //现任职务
		m_pLabelmyLocation = new QLabel(this);    //所在地

		m_pButtonAdd = new QPushButton(this);
		m_pButtonAdd->setObjectName("sendbtn");

		m_pButtonSendMsg = new QPushButton(this);
		m_pButtonSendMsg->setObjectName("sendbtn");
		m_pButtonSendMsg->setText(transfer("发起会话"));

		m_pLabelspecialCommitteeDuty->setFixedWidth(CONTENTWIDTH);
		m_pLabelspecialCommitteeDuty->setWordWrap(true);
		m_pLabelspecialCommitteeDuty->setContentsMargins(0, 5, 0, 0);

		m_pLabelcurrentPosition->setFixedWidth(CONTENTWIDTH);
		m_pLabelcurrentPosition->setWordWrap(true);
		m_pLabelcurrentPosition->setContentsMargins(0, 0, 0, 0);
	
		connect(m_pButtonAdd, SIGNAL(clicked()), this, SLOT(onAddClicked()));
		connect(m_pButtonSendMsg, SIGNAL(clicked()), this, SLOT(onStartChatClicked()));

        QFont ft;
        ft.setPointSize(14);
        m_pLabelName->setFont(ft);
		m_pLabelName->resize(QSize(m_pLabelName->width(), m_pLabelName->height()+5));
		
		QPixmap pixTmp(":/contact/contact_bg");
		QPixmap pixmap = pixTmp.scaled(350, 150);
		m_pLabelHeadBackground->setPixmap(pixmap);
		m_pButtonAdd->setText(transfer("添加好友"));

		m_pInfoLayout->setLabelAlignment(Qt::AlignTop);
	}

	void UserInfoCommitee::moveHeadPos(QPoint pos)
	{
		m_pAvatar->move(pos.x(), pos.y());
		m_pAvatar->raise();
	}
	void UserInfoCommitee::initLayout()
	{
		
		m_pAvatar->setAvaterSize(QSize(110, 110));
		m_pAvatar->move((300 - 110)/2, 30);
		m_pAvatar->raise();

		m_pInfoLayout->addRow(transfer("性          别："), m_pLabelSex);
		m_pInfoLayout->addRow(transfer("委   员    号："), m_pLabelmemNum);
		m_pInfoLayout->addRow(transfer("民          族："), m_pLabelNation);
		m_pInfoLayout->addRow(transfer("职          务："), m_pLabelposition);
		m_pInfoLayout->addRow(transfer("界          别："), m_pLabelsector);
		m_pInfoLayout->addRow(transfer("组          别："), m_pLabelgroup);
		m_pInfoLayout->addRow(transfer("专   委    会："), m_pLabelspecialCommittee);
		m_pInfoLayout->addRow(transfer("专委会职务："), m_pLabelspecialCommitteeDuty);
		m_pInfoLayout->addRow(transfer("现 任 职 务："), m_pLabelcurrentPosition);
		m_pInfoLayout->addRow(transfer("所   在   地："), m_pLabelmyLocation);

		m_pInfoLayout->setHorizontalSpacing(5);
		m_pInfoLayout->setVerticalSpacing(6);
		m_pInfoLayout->setContentsMargins(15,0,0,0);
		widget = new QWidget(this);
		//scroll = new QScrollArea(this);
		widget->setLayout(m_pInfoLayout);

		//scroll->setBackgroundRole(QPalette::Dark);
		//scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		//scroll->setFrameShape(QFrame::NoFrame);
		//widget->setMinimumSize(350, 273);

		//widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //可选;
		//scroll->setWidget(widget);
		//scroll->show();

		m_pButtonAdd->setFixedSize(220,28);
		m_pButtonSendMsg->setFixedSize(220, 28);

		m_pMainLayout->addWidget(m_pLabelHeadBackground, 0, Qt::AlignHCenter);
		m_pMainLayout->addWidget(m_pLabelName, 0, Qt::AlignHCenter);
		m_pMainLayout->addWidget(widget, 0, Qt::AlignHCenter);
		
		m_pSendMsgOrAddLayout = new QVBoxLayout(this);
		m_pSendMsgOrAddLayout->addWidget(m_pButtonSendMsg,0,Qt::AlignHCenter);
		m_pSendMsgOrAddLayout->addWidget(m_pButtonAdd, 0, Qt::AlignHCenter);

		m_pMainLayout->addLayout(m_pSendMsgOrAddLayout, 0);
		m_pMainLayout->setSpacing(10);
		m_pMainLayout->setContentsMargins(0, 0, 0, 5);
		this->setLayout(m_pMainLayout);
	}

	void UserInfoCommitee::setContact(data::Contact& contact, const QString name, const QString avatar)
	{
		std::string temp = contact.remark.isSet() && !contact.remark.value().empty()
			? contact.remark.value() : contact.name.value();
		QString qstrTemp = !temp.empty() ? QString::fromUtf8(temp.data()) : name;
		m_pLabelName->setText(qstrTemp);
		
		temp = contact.thumbAvatar.isSet() ? contact.thumbAvatar.value() : "";
		if (!temp.empty()){
			qstrTemp = transfer(temp.data());
		}/*if (!avatar.isEmpty()){
			qstrTemp = avatar;
		}*/else if (contact.gender.value() == 1){
			qstrTemp = ":/base/default_head";
		}
		else if (contact.gender.value() == 2){
			qstrTemp = ":/base/default_female_head";
		}
		else if (contact.gender.value() == 0){
			qstrTemp = ":/base/default_unknow_head";
		}
		/*QString headPath = m_pAvatar->AvatarPath();
		if (headPath.startsWith(":/") || headPath.isEmpty()){
			m_pAvatar->setAvatarPath(qstrTemp);
		}*/
		m_pAvatar->setAvatarPath(qstrTemp);
		contact.thumbAvatar = qstrTemp.toStdString();

	/*	if(contact.gender.isSet())
			qstrTemp = contact.gender.value() == 1 ? transfer("男") : contact.gender.value() == 2 ? transfer("女") : transfer("保密");
		m_pLabelSex->setText(qstrTemp);*/
		
		qstrTemp = contact.phones.isSet() && contact.phones.value().size() > 0
			? QString::fromUtf8(contact.phones.value().at(0).data()) : "";
		qstrTemp.remove("0086");
		
		qstrTemp = contact.emails.isSet() && contact.emails.value().size()
			? QString::fromUtf8(contact.emails.value().at(0).data()) : "";

		m_contactInfo = contact;
		if(contact.isApp.value() == 1){
			m_pLabelName->setVisible(false);
			m_pLabelSex->setText("");
		}
	}

	void UserInfoCommitee::setSector(int64 id, QString sector)
	{
		Log(LOG_LEV_INFO,LOG_FILE,"new id:%lld,sector:%s",id,sector.toLocal8Bit().data());
		if (m_id == id) {
			m_sector = sector;
			m_pLabelsector->setText(m_sector);
		}
	}
	void UserInfoCommitee::onAddClicked()
	{
		if (m_contactInfo.isApp.isSet() && m_contactInfo.isApp.value() == 2)
		{
			data::SearchResultInfo info;
			info.targetid = m_id;
			info.name = m_pLabelName->text().toUtf8().data();
			info.avatar = m_pAvatar->AvatarPath().toUtf8().data();
			info.resultType = data::USER_TYPE;
			///emit addContact(info);

			m_addContactWin = new AddContactWindow(this);
			m_addContactWin->InitData(info);
			m_addContactWin->show();
		}
		else
		{
			if(m_pContactControl != CNull)
			{
				m_pContactControl->AddContactNoVerify(m_id, "", "",
					CBind(&UserInfoCommitee::signalSerAddContactResult, this, CPlaceholders  _1));
			}
		}
		
		///this->hide();  2019-6-12
	}

	void UserInfoCommitee::onSerAddContactResult(int code)
	{
	}

	void UserInfoCommitee::onStartChatClicked()
	{
		CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
		chat->chatType = data::BUDDY_CHAT;
		chat->targetid = m_id;
		chat->isStartChat = true;
		chat->avatar = m_contactInfo.thumbAvatar.value();
		chat->name = m_pLabelName->text().toStdString();
		emit startChat(chat);
		if (m_closeAfterChat){
			this->hide();
		}
	}
}