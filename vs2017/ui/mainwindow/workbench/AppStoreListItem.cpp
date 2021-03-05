#include "AppStoreListItem.h"
#include "controls/headimage.h"
#include "common/Common.h"


namespace ui{
	AppStoreListItem::AppStoreListItem(QWidget *parent)
		: QWidget(parent)
		, m_iAppID(0)
		, m_isInstalled(false)
	{
		m_pAppMgr = APPMGRCONTROL;
		m_pLayout = CMakePtr<QGridLayout>(this);
		m_pAvatar = CMakePtr<HeadImage>(this, QSize(APP_ICON_SIZE, APP_ICON_SIZE));
		m_pLabelName = CMakePtr<QLabel>(this);
		m_pLabelIntroduce = CMakePtr<QLabel>(this);
		m_pBtnInstall = CMakePtr<QPushButton>(this);
		m_pBtnUninstall = CMakePtr<QPushButton>(this);
		
		CONNECT_SERVICE(AddOrDeleteApplication(int));
		connect(m_pBtnInstall.get(), SIGNAL(clicked()), 
			this, SLOT(onBtnClicked()));
		connect(m_pBtnUninstall.get(), SIGNAL(clicked()), 
			this, SLOT(onBtnClicked()));

		m_pBtnInstall->setObjectName("sendbtn");
		m_pBtnInstall->setMinimumSize(80, 30);
		m_pBtnUninstall->setObjectName("deleteBtn");
		m_pBtnUninstall->setMinimumSize(80, 30);
		m_pBtnInstall->setText(transfer("°²×°"));
		m_pBtnUninstall->setText(transfer("Ð¶ÔØ"));

		m_pLayout->addWidget(m_pAvatar.get(), 0, 0, 2, 1);
		m_pLayout->addWidget(m_pLabelName.get(), 0, 1, Qt::AlignVCenter);
		m_pLayout->addWidget(m_pLabelIntroduce.get(), 1, 1, Qt::AlignTop);
		m_pLayout->addWidget(m_pBtnInstall.get(), 0, 2, 2, 1);
		m_pLayout->addWidget(m_pBtnUninstall.get(), 0, 2, 2, 1);
		m_pLayout->setColumnStretch(1, 200);
		m_pLayout->setVerticalSpacing(0);
		m_pLayout->setHorizontalSpacing(20);
		m_pLayout->setContentsMargins(20, 10, 20, 10);

		this->setLayout(m_pLayout.get());
	}

	AppStoreListItem::~AppStoreListItem()
	{

	}

	void AppStoreListItem::onBtnClicked(void)
	{
		m_pBtnInstall->setEnabled(false);
		m_pAppMgr->addOrDeleteApplication(!m_isInstalled, m_iAppID,
			CBind(&AppStoreListItem::signalSerAddOrDeleteApplication,
				this, CPlaceholders  _1));
	}

	void AppStoreListItem::onSerAddOrDeleteApplication(int err)
	{
		m_pBtnInstall->setEnabled(true);
		if (err == 0)
		{
			if (m_isInstalled)
			{
				emit uninstallApp(m_iAppID);
			}
			else
			{
				emit installApp(m_iAppID, m_pLabelName->text(),
					m_pAvatar->AvatarPath(), m_strUrl);
			}
			setButtonStatus(!m_isInstalled);
		}
	}

	void AppStoreListItem::setAppID(const int64 appID)
	{
		m_iAppID = appID;
	}

	void AppStoreListItem::setAvatar(const QString strAvartar)
	{
		m_pAvatar->setAvatarPath(strAvartar);
	}

	void AppStoreListItem::setName(const QString strName)
	{
		m_pLabelName->setText(strName);
	}

	void AppStoreListItem::setIntroduce(const QString strIntroduce)
	{
		m_pLabelIntroduce->setText(strIntroduce);
	}

	void AppStoreListItem::setButtonStatus(const bool isInstalled)
	{
		m_isInstalled = isInstalled;
		m_pBtnInstall->setVisible(!m_isInstalled);
		m_pBtnUninstall->setVisible(m_isInstalled);
	}

	void AppStoreListItem::setUrl(const QString strUrl)
	{
		m_strUrl = strUrl;
	}
}