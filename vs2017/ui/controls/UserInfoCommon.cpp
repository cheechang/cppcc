#include <QApplication>
#include <QDesktopWidget>
#include "UserInfoCommon.h"
#include "headimage.h"
#include "../mainwindow/UserHeadImg.h"
#include "../mainwindow/contact/searchcontact/AddContactWindow.h"
#include "../common/Common.h"
#include "json.h"

namespace ui
{
	UserInfoCommon::UserInfoCommon(QWidget *parent)
	: TWidget(parent)
	, m_id(0)
	, m_sex(transfer("女"))
	{
		this->setObjectName("UserInfoWidget");
		m_closeAfterChat = true;
		Qt::WindowFlags flags = this->windowFlags();
		///flags |= Qt::Popup;
		///flags |= Qt::WindowStaysOnTopHint;
		//flags |= Qt::WindowCloseButtonHint;

		flags |= Qt::Dialog;
		flags |= Qt::WindowCloseButtonHint;
		flags &= ~Qt::WindowMaximizeButtonHint;
		flags &= ~Qt::WindowMinimizeButtonHint;
		this->setWindowTitle(transfer("详细信息"));
		this->setWindowFlags(flags);
		this->setFixedSize(300,446);

		m_pContactControl = CONTACTMGRCONTROL;
		m_pUserControl = USERCONTROL;
		CONNECT_SERVICE(AddContactResult(int));
		CONNECT_SERVICE(GetBuddyInfoFromNetResult(int, data::Contact&));

		if (m_pUserControl)
		{
			CSharedPtr<data::AccountInfo> userdata;
			userdata = m_pUserControl->GetAccountInfo();

			std::string jsonstr = userdata->entExtends.value();
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonstr, root);
			if (ret)
			{
				if (root.isArray())
				{
					if (root[0]["type"].isString())
					{
						Currenttype = root[0]["type"].asString();
					}
				}
			}
		}

		initWidget();
		initLayout();
	}

	UserInfoCommon::~UserInfoCommon()
	{
	}

	void UserInfoCommon::setAfterChatStatus(bool isClose)
	{
		m_closeAfterChat = isClose;
	}
	void UserInfoCommon::setInfo(const int64 id, const QString name, const QString avatar, std::string userinfo)
	{
		ParseJsonGetUserInfo(userinfo);

		m_id = id;
		m_pLabelName->setText(name);
		m_pAvatar->setAvatarPath(avatar);

		m_pLabelSex->setText(m_sex);    //性别
		m_pLabelNation->setText(m_nation);  //民族
		m_pLabelunit->setText(m_unit);    //单位
		m_pLabeloffice->setText(m_office);   //处室
		m_pLabelposition->setText(m_position);  //职位

		
		if (m_pContactControl != CNull)
		{
			/* 是好友显示发起会话 */
			if (m_pContactControl->ContactIsBuddy(m_id))
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
					CBind(&UserInfoCommon::signalSerGetBuddyInfoFromNetResult,
						this, CPlaceholders  _1, CPlaceholders  _2));
			}
		}
	}

	void UserInfoCommon::ParseJsonGetUserInfo(std::string jsoninfo)
	{
		QString jsonInStr = QString::fromUtf8(jsoninfo.c_str());
		Json::Reader  reader;
		Json::Value root;
		bool ret = reader.parse(jsoninfo,root);
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

				if (root[i]["unit"].isString())
				{
					m_unit = QString::fromUtf8(root[i]["unit"].asString().data());
				}

				if (root[i]["office"].isString())
				{
					m_office = QString::fromUtf8(root[i]["office"].asString().data());
				}

				if (root[i]["m_position"].isString())
				{
					m_position = QString::fromUtf8(root[i]["m_position"].asString().data());
				}
				break;
			}
		}
	}

	void UserInfoCommon::show(const QPoint& point)
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
				int y = deskWgt->availableGeometry(validPoint).height() - this->height();
				validPoint.setY(y);
			}
		}

		this->move(validPoint);
		TWidget::show();
	}

	void UserInfoCommon::show(const int64 id, const QString name, const QString avatar, const QPoint& point)
	{
		this->setInfo(id, name, avatar,"");
		this->show(point);
	}

	void UserInfoCommon::onSerGetBuddyInfoFromNetResult(int code, data::Contact& contact)
	{
		if (code == 0)
		{
			this->setContact(contact);
		}
	}

	void UserInfoCommon::focusOutEvent(QFocusEvent* event)
	{
		this->hide();
		event->accept();
	}

	void UserInfoCommon::initWidget()
	{
		m_pMainLayout = new QVBoxLayout(this);
		m_pLabelHeadBackground = new QLabel(this);
		m_pAvatar = new HeadImage(this);
		m_pLabelName = new QLabel(this);
		m_pInfoLayout = new QFormLayout(this);
		m_pLabelSex = new QLabel(this);
		m_pLabelNation = new QLabel(this);
		m_pLabelunit = new QLabel(this);
		m_pLabeloffice = new QLabel(this);
		m_pLabelposition = new QLabel(this);

		m_pButtonAdd = new QPushButton(this);
		m_pButtonAdd->setObjectName("sendbtn");

		m_pButtonSendMsg = new QPushButton(this);
		m_pButtonSendMsg->setObjectName("sendbtn");
		m_pButtonSendMsg->setText(transfer("发起会话"));

		m_pLabelName->setObjectName("grayLabel");
		m_pLabelSex->setObjectName("grayLabel");
		m_pLabelNation->setObjectName("grayLabel");
		m_pLabelunit->setObjectName("grayLabel");
		m_pLabeloffice->setObjectName("grayLabel");
		m_pLabelposition->setObjectName("grayLabel");

		m_pButtonAdd->setFixedSize(220, 28);
		m_pButtonSendMsg->setFixedSize(220, 28);

		connect(m_pButtonAdd, SIGNAL(clicked()), this, SLOT(onAddClicked()));
		connect(m_pButtonSendMsg, SIGNAL(clicked()), this, SLOT(onStartChatClicked()));

        QFont ft;
        ft.setPointSize(13);
        m_pLabelName->setFont(ft);
		m_pLabelName->resize(QSize(m_pLabelName->width(), 50));
		
		QPixmap pixTmp(":/contact/contact_bg");
		QPixmap pixmap = pixTmp.scaled(300, 150);
		m_pLabelHeadBackground->setPixmap(pixmap);
		m_pButtonAdd->setText(transfer("添加好友"));
	}

	void UserInfoCommon::initLayout()
	{
		
		m_pAvatar->setAvaterSize(QSize(110, 110));
		m_pAvatar->move((300 - 110)/2, 30);
		m_pAvatar->raise();

		m_pInfoLayout->addRow(transfer("性          别："), m_pLabelSex);
		m_pInfoLayout->addRow(transfer("民          族："), m_pLabelNation);
		m_pInfoLayout->addRow(transfer("单          位："), m_pLabelunit);
		m_pInfoLayout->addRow(transfer("处           室："), m_pLabeloffice);
		m_pInfoLayout->addRow(transfer("职          位："), m_pLabelposition);
		m_pInfoLayout->setSpacing(10);
		m_pInfoLayout->setContentsMargins(50,0,0,10);
		QWidget* widget = new QWidget(this);
		widget->setLayout(m_pInfoLayout);

		//m_pButtonAdd->setFixedSize(100,28);

		m_pMainLayout->addWidget(m_pLabelHeadBackground, 0, Qt::AlignHCenter);
		m_pMainLayout->addWidget(m_pLabelName, 0, Qt::AlignHCenter);
		m_pMainLayout->addWidget(widget, 0, Qt::AlignLeft);
		m_pMainLayout->addStretch();
		//m_pMainLayout->addWidget(m_pButtonAdd, 0, Qt::AlignHCenter);
		m_pSendMsgOrAddLayout = new QVBoxLayout(this);
		m_pSendMsgOrAddLayout->addWidget(m_pButtonSendMsg, 0, Qt::AlignHCenter);
		m_pSendMsgOrAddLayout->addWidget(m_pButtonAdd, 0, Qt::AlignHCenter);

		m_pMainLayout->addLayout(m_pSendMsgOrAddLayout, 0);
		m_pMainLayout->setSpacing(10);
		m_pMainLayout->setContentsMargins(0, 0, 0, 10);
		this->setLayout(m_pMainLayout);
	}

	void UserInfoCommon::setContact(data::Contact& contact, const QString name, const QString avatar)
	{
		std::string temp = contact.remark.isSet() && !contact.remark.value().empty()
			? contact.remark.value() : contact.name.value();
		QString qstrTemp = !temp.empty() ? QString::fromUtf8(temp.data()) : name;
		if (!qstrTemp.isEmpty()){
			m_pLabelName->setText(qstrTemp);
		}
		
		temp = contact.thumbAvatar.isSet() ? contact.thumbAvatar.value() : "";
		if (!temp.empty()){
			qstrTemp = transfer(temp.data());
		}
		else if (contact.gender.value() == 1){
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

		//if (contact.gender.isSet())
		//	qstrTemp = contact.gender.value() == 1 ? transfer("男") : contact.gender.value() == 2 ? transfer("女") : transfer("保密");
		//m_pLabelSex->setText(qstrTemp);
		
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

	void UserInfoCommon::onAddClicked()
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
					CBind(&UserInfoCommon::signalSerAddContactResult, this, CPlaceholders  _1));
			}
		}
		
		////this->hide();  2019-6-12
	}

	void UserInfoCommon::onSerAddContactResult(int code)
	{
	}

	void UserInfoCommon::onStartChatClicked()
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