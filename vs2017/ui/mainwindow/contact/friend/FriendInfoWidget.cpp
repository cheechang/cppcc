#include "FriendInfoWidget.h"
#include <interface/IUserControl.h>
#include "data/ChatData.h"
#include "data/ContactData.h"
#include "../../../utils/common.h"
#include "../../common/Common.h"
#include "common/controlptr.h"
#include "../controls/PushButton.h"
#include "../controls/headimage.h"
#include "controls/UserInfoCommon.h"
#include "controls/UserInfoCommitee.h"
#include <utils/parson.h>
#include <utils/parson.c>
#include <QDebug>
#include <QtWebEngineWidgets/QWebEngineView>
#include "json.h"
namespace ui{
	FriendInfoWidget::FriendInfoWidget(QWidget *parent)
		: ui::TWidget(parent)
	{
		m_pUserInfoCommomWidget = CNull;
		m_pUserInfoCommiteeWidget = CNull;

		m_pMainLayout = new QVBoxLayout(this);
		m_pMainLayout->setContentsMargins(0,0,0,0);
		m_pMainLayout->setAlignment(Qt::AlignCenter);
		this->setLayout(m_pMainLayout);
		this->setObjectName("BgWidget");
		this->setStyleSheet("QWidget#BgWidget{background:#e5e7ec;}");
	}

	FriendInfoWidget::~FriendInfoWidget()
	{

	}

	void FriendInfoWidget::updateData( data::Contact contact )
	{
		mData = contact;
		mUserInfo = contact.entExtends.value();
		adjustWidget();
	}



	void FriendInfoWidget::adjustWidget()
	{
		std::string type("");
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(mUserInfo, root);
		if (ret)
		{
			if (root.isArray())
			{
				if (root[0]["type"].isString())
				{
					type = root[0]["type"].asString();
				}
			}
		}
		if (type == "1")
		{
			if (m_pUserInfoCommomWidget == CNull){
				m_pUserInfoCommomWidget = CMakePtr<UserInfoCommon>(this);
				m_pUserInfoCommomWidget->setFixedSize(300, 480);
				m_pUserInfoCommomWidget->setWindowFlags(Qt::SubWindow);
				m_pUserInfoCommomWidget->setAfterChatStatus(false);
				connect(m_pUserInfoCommomWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
					this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
			}
			
			m_pUserInfoCommomWidget->setInfo(mData.id.value(),
				QString::fromUtf8(mData.name.value().data()),
				QString::fromUtf8(mData.avatar.value().data()),
				mUserInfo);

			if (m_pUserInfoCommiteeWidget){
				m_pMainLayout->removeWidget(m_pUserInfoCommiteeWidget.get());
				m_pUserInfoCommiteeWidget->hide();
			}
			
			if (m_pUserInfoCommomWidget){
				m_pMainLayout->removeWidget(m_pUserInfoCommomWidget.get());
				m_pUserInfoCommomWidget->show();
			}
			m_pMainLayout->addWidget(m_pUserInfoCommomWidget.get());

		}

		if (type == "0")
		{
			if (m_pUserInfoCommiteeWidget == CNull){
				m_pUserInfoCommiteeWidget = CMakePtr<UserInfoCommitee>(this);
				m_pUserInfoCommiteeWidget->setFixedSize(300,480);
				m_pUserInfoCommiteeWidget->moveHeadPos(QPoint((300-110)/2,30));
				m_pUserInfoCommiteeWidget->setWindowFlags(Qt::SubWindow);
				m_pUserInfoCommiteeWidget->setAfterChatStatus(false);
				connect(m_pUserInfoCommiteeWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
					this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
			}

			m_pUserInfoCommiteeWidget->setInfo(mData.id.value(),
				QString::fromUtf8(mData.name.value().data()),
				QString::fromUtf8(mData.avatar.value().data()),
				mUserInfo);

			if (m_pUserInfoCommomWidget){
				m_pMainLayout->removeWidget(m_pUserInfoCommomWidget.get());
				m_pUserInfoCommomWidget->hide();
			}

			if (m_pUserInfoCommiteeWidget){
				m_pMainLayout->removeWidget(m_pUserInfoCommiteeWidget.get());
				m_pUserInfoCommiteeWidget->show();
			}
			m_pMainLayout->addWidget(m_pUserInfoCommiteeWidget.get());

		}
	}
}
