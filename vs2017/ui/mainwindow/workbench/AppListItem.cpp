#include "AppListItem.h"
#include "controls/headimage.h"
#include "common/Common.h"


namespace ui{
	AppListItem::AppListItem(QWidget *parent)
		: QWidget(parent)
		, m_iAppID(0)
	{
		m_pLayout = CMakePtr<QHBoxLayout>(this);
		m_pAvatar = CMakePtr<HeadImage>(this, QSize(HEAD_SIZE, HEAD_SIZE));
		m_pLabelName = CMakePtr<QLabel>(this);

		m_pLayout->addWidget(m_pAvatar.get());
		m_pLayout->addWidget(m_pLabelName.get());

		this->setLayout(m_pLayout.get());
	}

	AppListItem::~AppListItem()
	{

	}

	int64 AppListItem::appID(void) const
	{
		return m_iAppID;
	}

	void AppListItem::setAppID(const int64 appID)
	{
		m_iAppID = appID;
	}

	void AppListItem::setAvatar(const QString strAvartar)
	{
		m_pAvatar->setAvatarPath(strAvartar);
	}

	void AppListItem::setName(const QString strName)
	{
		m_pLabelName->setText(strName);
	}

	QString AppListItem::url(void) const
	{
		return m_strUrl;
	}

	void AppListItem::setUrl(const QString strUrl)
	{
		m_strUrl = strUrl;
	}
}