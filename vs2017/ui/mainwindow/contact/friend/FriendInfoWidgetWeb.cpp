#include "FriendInfoWidgetWeb.h"
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
//#include <utils/parson.h>
//#include <utils/parson.c>
#include <QDebug>
#include <QtWebEngineWidgets/QWebEngineView>
//#include "json.h"
namespace ui{
	FriendInfoWidgetWeb::FriendInfoWidgetWeb(QWidget *parent)
		: EnterpriseInfoWidget(parent)
	{
		__super::signalsDisconnect();
		connect(m_btnSendMsg.get(),SIGNAL(clicked()),this,SLOT(slotStartChat()));
		__super::mExtendType = 1;
		mEntControl = ENTMGRCONTROL;
		if(mEntControl){
			CONNECT_SERVICE(GetOrgUserInfo(int, std::vector<data::OrgAndUserInfo>&));
		}

		CONNECT_SERVICE(ShowMoreInfo());


		m_webEngineView = CMakePtr<QWebEngineView>(this);
		///m_webEngineView = NULL;
	}

	FriendInfoWidgetWeb::~FriendInfoWidgetWeb()
	{

	}

	void FriendInfoWidgetWeb::slotStartChat()
	{
		CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
		chat->chatType = data::BUDDY_CHAT;
		chat->isStartChat = true;
		chat->avatar   = utils::FileIsExist(mData.thumbAvatar.value())?mData.thumbAvatar.value():"";
		chat->name     = QString::fromUtf8(mData.remark.value().c_str()).toStdString();
		if (chat->name.empty())
		{
			chat->name  = QString::fromUtf8(mData.name.value().c_str()).toStdString();
		}
		chat->targetid = mData.id.value();
		emit startChat(chat);
	}
	void FriendInfoWidgetWeb::updateData(data::Contact contact)
	{

		/*if (m_webEngineView == NULL)  {
			m_webEngineView = new QWebEngineView(this);
		}
		if (m_webEngineView){*/
			m_webEngineView->setUrl(QUrl(QStringLiteral("https://www.baidu.com/")));
			m_webEngineView->setGeometry(this->rect());
			m_webEngineView->show();
		//}
		return;

 


	}

	void FriendInfoWidgetWeb::onSerGetOrgUserInfo(int code, std::vector<data::OrgAndUserInfo>&users)
	{
		QString duty(""),depart("");
		if(users.size()>0){
			data::OrgAndUserInfo data = users.at(0);
			duty   = QString::fromUtf8(data.duty.c_str());
			depart = QString::fromUtf8(data.orgName.c_str());
		}
		m_edtList.at(0)->setText(depart);
		m_edtList.at(1)->setText(duty);
	}

	void FriendInfoWidgetWeb::onSerShowMoreInfo()
	{
	}
}
