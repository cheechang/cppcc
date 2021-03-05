#include <QApplication>
#include <QDesktopWidget>
#include "UserInfoWindow.h"
#include "headimage.h"
#include "../mainwindow/UserHeadImg.h"
#include "../mainwindow/contact/searchcontact/AddContactWindow.h"
#include "../common/Common.h"

namespace ui
{
	UserInfoWindow::UserInfoWindow(QWidget *parent)
	: TWidget(parent)
	, m_id(0)
	{
		this->setObjectName("UserInfoWidget");

		Qt::WindowFlags flags = this->windowFlags();
		flags |= Qt::Popup;
		flags |= Qt::WindowStaysOnTopHint;
		this->setWindowFlags(flags);
		
		this->setMinimumHeight(336);

		m_pContactControl = CONTACTMGRCONTROL;
		CONNECT_SERVICE(AddContactResult(int));
		CONNECT_SERVICE(GetBuddyInfoFromNetResult(int, data::Contact&));

		initWidget();
		initLayout();
	}

	UserInfoWindow::~UserInfoWindow()
	{
	}

	void UserInfoWindow::setInfo(const int64 id, const QString name, const QString avatar)
	{
		m_id = id;
		m_pLabelName->setText(name);
		m_pAvatar->setAvatarPath(avatar);

		if(m_pContactControl != CNull)
		{
			/* 是好友显示发起会话 */
			if(m_pContactControl->ContactIsBuddy(m_id))
			{
				m_pButtonAdd->setText(transfer("发起会话"));
				m_pButtonAdd->disconnect();
				connect(m_pButtonAdd, SIGNAL(clicked()), this, SLOT(onStartChatClicked()));

				data::Contact contact;
				m_pContactControl->GetContactInfo(id, contact);
				this->setContact(contact, name, transfer(contact.thumbAvatar.value().c_str()));
				if (contact.isApp.value() == 1)
				{
					m_pButtonAdd->setText(transfer("进入公众号"));
				}
			}
			/* 是陌生人显示添加好友 */
			else
			{
				m_pButtonAdd->setText(transfer("添加到联系人"));
				m_pButtonAdd->disconnect();
				connect(m_pButtonAdd, SIGNAL(clicked()), this, SLOT(onAddClicked()));
				
				m_pContactControl->GetBuddyInfoFromNet(id, 
					CBind(&UserInfoWindow::signalSerGetBuddyInfoFromNetResult,
					this, CPlaceholders  _1, CPlaceholders  _2));
			}
		}
	}

	void UserInfoWindow::show(const QPoint& point)
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

	void UserInfoWindow::show(const int64 id, const QString name, const QString avatar, const QPoint& point)
	{
		this->setInfo(id, name, avatar);
		this->show(point);
	}

	void UserInfoWindow::onSerGetBuddyInfoFromNetResult(int code, data::Contact& contact)
	{
		if (code == 0)
		{
			this->setContact(contact);
		}
	}

	void UserInfoWindow::focusOutEvent(QFocusEvent* event)
	{
		this->hide();
		event->accept();
	}

	void UserInfoWindow::initWidget()
	{
		m_pMainLayout = new QVBoxLayout(this);
		m_pLabelHeadBackground = new QLabel(this);
		m_pAvatar = new HeadImage(this);
		m_pLabelName = new QLabel(this);
		m_pInfoLayout = new QFormLayout(this);
		m_pLabelSex = new QLabel(this);
		m_pLabelPhone = new QLabel(this);
		m_pLabelEmail = new QLabel(this);
		m_pButtonAdd = new QPushButton(this);

		m_pButtonAdd->setObjectName("sendbtn");
		m_pLabelName->setObjectName("grayLabel");
		m_pLabelSex->setObjectName("grayLabel");
		m_pLabelPhone->setObjectName("grayLabel");
		m_pLabelEmail->setObjectName("grayLabel");

		connect(m_pButtonAdd, SIGNAL(clicked()), this, SLOT(onAddClicked()));

        QFont ft;
        ft.setPointSize(18);
        m_pLabelName->setFont(ft);
		m_pLabelName->resize(QSize(m_pLabelName->width(), 50));
		
		QPixmap pixTmp(":/contact/contact_bg");
		QPixmap pixmap = pixTmp.scaled(300, 150);
		m_pLabelHeadBackground->setPixmap(pixmap);
		m_pAvatar->setAvatarPath(":/base/default_head");
		m_pLabelSex->setText(transfer("保密"));
		m_pButtonAdd->setText(transfer("添加好友"));
	}

	void UserInfoWindow::initLayout()
	{
		
		m_pAvatar->setAvaterSize(QSize(110, 110));
		m_pAvatar->move((300 - 110)/2, 30);
		m_pAvatar->raise();

		m_pInfoLayout->addRow(transfer("性  别："), m_pLabelSex);
		m_pInfoLayout->addRow(transfer("手  机："), m_pLabelPhone);
		m_pInfoLayout->addRow(transfer("邮  箱："), m_pLabelEmail);
		QWidget* widget = new QWidget(this);
		widget->setLayout(m_pInfoLayout);

		m_pButtonAdd->setFixedSize(100,28);

		m_pMainLayout->addWidget(m_pLabelHeadBackground, 0, Qt::AlignHCenter);
		m_pMainLayout->addWidget(m_pLabelName, 0, Qt::AlignHCenter);
		m_pMainLayout->addWidget(widget, 0, Qt::AlignHCenter);
		m_pMainLayout->addWidget(m_pButtonAdd, 0, Qt::AlignHCenter);
		m_pMainLayout->setSpacing(10);
		m_pMainLayout->setContentsMargins(0, 0, 0, 10);
		this->setLayout(m_pMainLayout);
	}

	void UserInfoWindow::setContact(data::Contact& contact, const QString name, const QString avatar)
	{
		std::string temp = contact.remark.isSet() && !contact.remark.value().empty()
			? contact.remark.value() : contact.name.value();
		QString qstrTemp = !temp.empty() ? QString::fromUtf8(temp.data()) : name;
		m_pLabelName->setText(qstrTemp);
		
		temp = contact.thumbAvatar.isSet() ? contact.thumbAvatar.value() : "";
		qstrTemp = !temp.empty() ? QString::fromUtf8(temp.data())
			: avatar.isEmpty() ? ":/base/default_head" : avatar;
		m_pAvatar->setAvatarPath(qstrTemp);
		contact.thumbAvatar = qstrTemp.toStdString();

		qstrTemp = contact.gender.isSet()
			? contact.gender.value() == 1 ? transfer("男")
			: contact.gender.value() == 2 ? transfer("女") : transfer("保密") : transfer("保密");
		m_pLabelSex->setText(qstrTemp);
		
		qstrTemp = contact.phones.isSet() && contact.phones.value().size() > 0
			? QString::fromUtf8(contact.phones.value().at(0).data()) : "";
		qstrTemp.remove("0086");
		m_pLabelPhone->setText(qstrTemp);
		
		qstrTemp = contact.emails.isSet() && contact.emails.value().size()
			? QString::fromUtf8(contact.emails.value().at(0).data()) : "";
		m_pLabelEmail->setText(qstrTemp);

		m_contactInfo = contact;
		if(contact.isApp.value() == 1){
			m_pLabelEmail->setVisible(false);
			m_pLabelPhone->setVisible(false);
			m_pLabelName->setVisible(false);
			m_pLabelSex->setText("");
		}
	}

	void UserInfoWindow::onAddClicked()
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
					CBind(&UserInfoWindow::signalSerAddContactResult, this, CPlaceholders  _1));
			}
		}
		
		this->hide();
	}

	void UserInfoWindow::onSerAddContactResult(int code)
	{
	}

	void UserInfoWindow::onStartChatClicked()
	{
		CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
		chat->chatType = data::BUDDY_CHAT;
		chat->targetid = m_id;
		chat->isStartChat = true;
		chat->avatar = m_contactInfo.thumbAvatar.value();
		chat->name = m_pLabelName->text().toStdString();
		emit startChat(chat);
		this->hide();
	}
}