#include "AppInfoWidget.h"
#include "../../../utils/common.h"
#include "controls/PushButton.h"
#include "controls/headimage.h"
#include <data/ChatData.h>
#include "../../../common/Common.h"
namespace ui{
	AppInfoWidget::AppInfoWidget(QWidget *parent)
		: EnterpriseInfoWidget(parent)
	{
		__super::signalsDisconnect();
		__super::hideMoreInfoBtn();
		connect(m_btnSendMsg.get(),SIGNAL(clicked()),this,SLOT(slotStartChat()));
		init();
		mUserControl = USERCONTROL;
		if(mUserControl){
			CONNECT_SERVICE(GetAppInfo(int, data::EntAppinfo&));
		}
	}

	AppInfoWidget::~AppInfoWidget()
	{

	}

	void AppInfoWidget::slotStartChat()
	{
		CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
		chat->chatType = data::APP_CHAT;
		chat->isStartChat = true;
		chat->avatar   = utils::FileIsExist(mData.appIcon.c_str())?mData.appIcon.c_str():"";
		chat->name     = QString::fromUtf8(mData.appName.c_str()).toStdString();
		chat->targetid = mData.appID;
		emit startChat(chat);
	}

	void AppInfoWidget::updateData( int64 appId )
	{
		if(mUserControl){
			mUserControl->getAppInfo(appId,CBind(&AppInfoWidget::signalSerGetAppInfo,
				this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	void AppInfoWidget::onSerGetAppInfo( int code, data::EntAppinfo&data )
	{
		mData = data;
		if(m_btnHead){
			m_btnHead->setAvatarPath(mData.appIcon.c_str());
		}
		if(m_nameLineEdit){
			QString name = QString::fromUtf8(mData.appName.c_str());
			m_nameLineEdit->setText(name);
		}
		m_edtList.at(0)->setText(QString::fromUtf8(mData.appSign.c_str()));
	}

	void AppInfoWidget::init()
	{
		m_btnSendMsg->setToolTip(transfer("进入企业号"));
		m_lblList.at(0)->setText(transfer("标识"));
		/*m_lblList.at(1)->setVisible(false);
		m_lblList.at(2)->setVisible(false);*/
		//m_lblList.at(3)->setVisible(false);

		m_edtList.at(0)->setVisible(false);
	/*	m_edtList.at(1)->setVisible(false);
		m_edtList.at(2)->setVisible(false);*/
		//m_edtList.at(3)->setVisible(false);

		mBtnGetHistoryMsg = CMakePtr<QPushButton>();
		connect(mBtnGetHistoryMsg.get(),SIGNAL(clicked()),this,SLOT(onBtnViewHistoryMsg()));
		mBtnGetHistoryMsg->setMinimumSize(240, 36);
		mBtnGetHistoryMsg->setMaximumSize(240, 36);
		mBtnGetHistoryMsg->setObjectName("sendbtn");
		mBtnGetHistoryMsg->setText(transfer("查看历史消息"));
		m_vOrgInfoLayout->addWidget(mBtnGetHistoryMsg.get(),0,Qt::AlignHCenter);
		m_vOrgInfoLayout->addStretch();
	}

	void AppInfoWidget::onBtnViewHistoryMsg()
	{
		QString url = mData.messageHistoryUrl.c_str();
		//TODO
	}

}
