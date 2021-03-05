#include "LoginHistoryItem.h"
#include "controls/headimage.h"
#include "controls/PushButton.h"


namespace ui{
	LoginHistoryItem::LoginHistoryItem(QWidget *parent/*, QString avatar, 
		QString account, QString name*/)
		: QWidget(parent)
	{
		m_pLayout = std::make_shared<QGridLayout>(this);
		m_pAvatar = std::make_shared<HeadImage>(this, QSize());
		m_pAccount = std::make_shared<QLabel>(this);
		m_pName = std::make_shared<QLabel>(this);
		m_pCloseButton = std::make_shared<PushButton>(this);

		this->setMinimumHeight(30);
		//m_pAvatar->setAvatarPath(avatar);
		//m_pAccount->setText(account);
		//m_pName->setText(name);

		m_pLayout->addWidget(m_pAvatar.get(), 0, 0, 2, 1);
		m_pLayout->addWidget(m_pAccount.get(), 0, 1);
		m_pLayout->addWidget(m_pName.get(), 1, 1);
		m_pLayout->addWidget(m_pCloseButton.get(), 0, 2, 2, 1);
		this->setLayout(m_pLayout.get());
	}
	
	
	LoginHistoryItem::~LoginHistoryItem(void)
	{
	}

	void LoginHistoryItem::setAvatar(const QString avatar)
	{
		m_pAvatar->setAvatarPath(avatar);
	}

	void LoginHistoryItem::setAccount(const QString account)
	{
		m_pAccount->setText(account);
	}

	void LoginHistoryItem::setName(const QString name)
	{
		m_pName->setText(name);
	}
}
