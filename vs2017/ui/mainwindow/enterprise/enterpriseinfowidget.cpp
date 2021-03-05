#include "enterpriseinfowidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QLabel>
#include <json.h>
#include <interface/IUserControl.h>
#include "controls/UserInfoCommon.h"
#include "controls/UserInfoCommitee.h"
#include "../controls/PushButton.h"
#include "../controls/headimage.h"
#include "data/ChatData.h"
#include "../../../utils/common.h"
#include "common/Common.h"
#include "common/controlptr.h"
namespace ui{
	EnterpriseInfoWidget::EnterpriseInfoWidget(QWidget *parent)
		: QWidget(parent)
	{
		m_centerWidget = CMakePtr<QWidget>();
		m_centerWidget->setMinimumSize(QSize(CenterWidgetMinWidth,CenterWidgetMinHeight));
		m_centerWidget->setMaximumSize(QSize(CenterWidgetMinWidth,CenterWidgetMinHeight));
		m_centerWidget->setObjectName("enterpriseInfo_centerWidget");
		mCurExtendId = 0;
		mExtendType = 0;
		m_centerHeadWidget = CMakePtr<QWidget>();
		m_centerHeadWidget->setObjectName("enterpriseInfo_centerHeadWidget");
		m_centerHeadWidget->setAutoFillBackground(true);
		m_centerHeadWidget->setMinimumSize(QSize(CenterWidgetMinWidth,CenterWidgetMinHeight/2));

		m_centerContentWidget = CMakePtr<QWidget>();
		m_centerContentWidget->setObjectName("enterpriseInfo_centerContentWidget");
		m_centerContentWidget->setMinimumSize(QSize(CenterWidgetMinWidth,CenterWidgetMinHeight/2));

		
		m_centerWidgetLayout = CMakePtr<QVBoxLayout>(m_centerWidget.get());
		m_centerWidgetLayout->addWidget(m_centerHeadWidget.get());


		m_vOrgInfoLayout = CMakePtr<QVBoxLayout>();
		m_nameLineEdit = CMakePtr<QLineEdit>();
		m_nameLineEdit->setAlignment(Qt::AlignHCenter);
		m_nameLineEdit->setReadOnly(true);
		m_nameLineEdit->setContentsMargins(0,NameTopMargin,0,0);
		m_nameLineEdit->setObjectName("enterInfoQLineEdit");
		m_nameLineEdit->setFont(QFont("",14));
		m_gridOrgInfoLayout = CMakePtr<QGridLayout>();
		m_gridOrgInfoLayout->setVerticalSpacing(GridLayoutInforSpacing);
		//m_gridOrgInfoLayout->setAlignment(Qt::AlignHCenter);
		m_gridOrgInfoLayout->setContentsMargins(25,0,0,0);
		m_gridOrgInfoLayout->setContentsMargins(GridLayoutInforLeftMargin,ConterWidgetTopMargin,0,0);
		m_gridOrgInfoLayout->setVerticalSpacing(10);


		m_lblList.append(CMakePtr<QLabel>(transfer("性别：")));
		m_lblList.append(CMakePtr<QLabel>(transfer("民族：")));
		m_lblList.append(CMakePtr<QLabel>(transfer("组别：")));

		m_edtList.append(CMakePtr<QLineEdit>());
		m_edtList.append(CMakePtr<QLineEdit>());
		m_edtList.append(CMakePtr<QLineEdit>());

		for (int i = 0; i < m_lblList.size(); ++i){
			m_gridOrgInfoLayout->addWidget(m_lblList.at(i).get(), i, 0, 1, 1);
			m_gridOrgInfoLayout->addWidget(m_edtList.at(i).get(), i, 1, 1, 1);
			m_edtList.at(i)->setReadOnly(true);
			m_edtList.at(i)->setObjectName("enterInfoQLineEdit");
			m_lblList.at(i)->setEnabled(false);
		}

		//mInfoStactked = new QStackedWidget(this);
		mBasicWidget = new QWidget(this);
		//mExtendsWidget= new QWidget(this);

		mBtnViewMoreInfo = new QPushButton(mBasicWidget);
		//mBtnViewMoreInfo->setText(transfer("查看扩展信息"));
		mBtnViewMoreInfo->setText(transfer("详细信息"));
		mBtnViewMoreInfo->setFixedSize(180,30);
		connect(mBtnViewMoreInfo,SIGNAL(clicked()),this,SLOT(onBtnViewExtendsInfo()));
		mBtnViewMoreInfo->setObjectName("sendbtn");
		mBtnViewMoreInfo->setCursor(Qt::PointingHandCursor);

		m_gridOrgInfoLayout->addWidget(mBtnViewMoreInfo,4,0,1,2,Qt::AlignLeft);
		mBasicWidget->setLayout(m_gridOrgInfoLayout.get());
		//mInfoStactked->addWidget(mBasicWidget);
		
		//扩展信息
	//	mExtendInfoList = new QListWidget(this);
	///	QVBoxLayout* extendInfoLayout = new QVBoxLayout(this);
	//	extendInfoLayout->setContentsMargins(0,0,0,10);
	//	extendInfoLayout->addWidget(mExtendInfoList,0,Qt::AlignHCenter);
	//	mExtendInfoList->setFixedWidth(220);
		/*mBtnBackBasicInfo = new QPushButton(this);
		mBtnBackBasicInfo->setText(transfer("返回基本信息"));
		mBtnBackBasicInfo->setFixedSize(220,30);
		connect(mBtnBackBasicInfo,SIGNAL(clicked()),this,SLOT(onBtnBackToBasicInfo()));
		mBtnBackBasicInfo->setObjectName("sendbtn");
		mBtnBackBasicInfo->setCursor(Qt::PointingHandCursor);
		extendInfoLayout->addWidget(mBtnBackBasicInfo,0,Qt::AlignHCenter);*/

		//extendInfoLayout->addStretch();
		//mExtendsWidget->setLayout(extendInfoLayout);
		//mInfoStactked->addWidget(mExtendsWidget);
		m_vOrgInfoLayout->addWidget(m_nameLineEdit.get());
		//m_vOrgInfoLayout->addWidget(mInfoStactked);
		m_vOrgInfoLayout->addWidget(mBasicWidget);
		m_vOrgInfoLayout->addStretch();

		m_centerContentWidget->setLayout(m_vOrgInfoLayout.get());
		m_centerWidgetLayout->addWidget(m_centerContentWidget.get());

		m_btnSendMsg = CMakePtr<PushButton>(m_centerWidget.get());
		m_btnSendMsg->setPicName(QString(":/contact/sendmsg"));
		m_btnSendMsg->setToolTip(transfer("发消息"));
		m_btnSendMsg->setCursor(Qt::PointingHandCursor);
		m_btnSendMsg->move(m_centerWidget->width() - SendMsgBtnRightMargin,(m_centerWidget->height() - m_btnSendMsg->height())/2);
		connect(m_btnSendMsg.get(),SIGNAL(clicked()),this,SLOT(slotStartChat()));

		m_btnHead = CMakePtr<HeadImage>(m_centerWidget.get());
		m_btnHead->setAvatarPath(DEFAULT_AVATAR);
		m_btnHead->move((CenterWidgetMinWidth - m_btnHead->width())/2+2,(m_centerHeadWidget->height() - m_btnHead->height())/5+9);

		m_centerWidget->setLayout(m_centerWidgetLayout.get());

		m_centerVWidgetLayout = CMakePtr<QVBoxLayout>(this);
		m_centerVWidgetLayout->addWidget(m_centerWidget.get(),0,Qt::AlignHCenter);
		m_centerVWidgetLayout->setContentsMargins(0,ConterWidgetTopMargin,0,0);

		m_contentLayout = CMakePtr<QHBoxLayout>(this);
		m_contentLayout->addSpacing(0);
		m_contentLayout->addStretch();
		m_contentLayout->addLayout(m_centerVWidgetLayout.get());
		m_contentLayout->addStretch();
		setLayout(m_contentLayout.get());
		
		mChatMgrControl = CHATMGRCONTROL;
		mContactContrl = CONTACTMGRCONTROL;
		CONNECT_SERVICE(GetUserExtendInfo(int64,std::vector<data::EnterpriseDictionary>&));
		CONNECT_SERVICE(GetUserInfo(int, data::UserData&));
}

	EnterpriseInfoWidget::~EnterpriseInfoWidget()
	{

	}

	void EnterpriseInfoWidget::paintEvent( QPaintEvent *event )
	{
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

	void EnterpriseInfoWidget::updateData( data::OrgAndUserInfo user )
	{
		m_user = user;
		CSharedPtr<control::IUserControl> userCntrol = USERCONTROL;
		if(userCntrol != CNull){
			CSharedPtr<data::AccountInfo> userInfo = userCntrol->GetAccountInfo();
			if(userInfo && userInfo->id.value() == user.userID){
				m_btnSendMsg->setVisible(false);
			}else{
				m_btnSendMsg->setVisible(true);
			}
		}
		if(m_btnHead){
			m_btnHead->setAvatarPath(user.head.c_str());
		}
		if(m_nameLineEdit){
			m_nameLineEdit->setText(user.enName.c_str());
		}
		mChatMgrControl->getUserInfo(user.userID, 0, CBind(&EnterpriseInfoWidget::signalSerGetUserInfo, this, std::placeholders::_1, std::placeholders::_2));
		
		m_edtList.at(2)->setText(user.orgName.c_str());
		//mInfoStactked->setCurrentIndex(0);
		this->update();
	}

	void EnterpriseInfoWidget::onSerGetUserInfo(int code, data::UserData& data)
	{
		std::string type("");
		std::string jsonstr = data.entExtends.value();
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(jsonstr, root);
		if (ret)
		{
			if (root.isArray())
			{
				if (root[0]["type"].isString())
				{
					type = root[0]["type"].asString();
				}

				m_sex = transfer("保密");
				if (root[0]["sex"].isInt())
				{
					m_sex = root[0]["sex"].asInt() == 1 ? transfer("男") : root[0]["sex"].asInt() == 2 ?
						transfer("女") : transfer("保密");
				}

				if (root[0]["nation"].isString())
				{
					m_nation = QString::fromUtf8(root[0]["nation"].asString().data());
				}

			}
		}
		m_edtList.at(0)->setText(m_sex);
		m_edtList.at(1)->setText(m_nation);

		id = data.id.value();
		name = QString::fromStdString(data.name.value());
		avatar = QString::fromStdString(data.avatar.value());
		UserInfoExtend = data.entExtends.value();
		Usertype = type;
	}

	void EnterpriseInfoWidget::slotStartChat()
	{
		CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
		chat->chatType = data::ENT_USER_CHAT;
		chat->isStartChat = true;
		chat->avatar   = utils::FileIsExist(m_user.head)?m_user.head:"";
		chat->name = m_user.enName;
		chat->targetid = m_user.userID;
		emit startChat(chat);
	}

	void EnterpriseInfoWidget::signalsDisconnect()
	{
		disconnect(m_btnSendMsg.get(),SIGNAL(clicked()),this,SLOT(slotStartChat()));
	}

	void EnterpriseInfoWidget::hideMoreInfoBtn()
	{
		mBtnViewMoreInfo->setVisible(false);
	}

	void EnterpriseInfoWidget::onBtnViewExtendsInfo()
	{
			if (Usertype == "1")
			{
				m_pUserInfoCommomWidget = CMakePtr<UserInfoCommon>(this);
				connect(m_pUserInfoCommomWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
				m_pUserInfoCommomWidget->setInfo(id, name, avatar, UserInfoExtend);
				m_pUserInfoCommomWidget->show();
			}

			if (Usertype == "0")
			{
				m_pUserInfoCommiteeWidget = CMakePtr<UserInfoCommitee>(this);
				connect(m_pUserInfoCommomWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
				m_pUserInfoCommiteeWidget->setInfo(id, name, avatar, UserInfoExtend);
				m_pUserInfoCommiteeWidget->show();
			}


			emit signalSerShowMoreInfo();
		
		/*if (mCurExtendId == m_user.userID)
		{
			mInfoStactked->setCurrentIndex(1);
			return;
		}
		if (mContactContrl)
		{
			mContactContrl->GetBuddyExtendsInfo(m_user.userID,CBind(&EnterpriseInfoWidget::signalSerGetUserExtendInfo,this,m_user.userID,CPlaceholders  _1));
		}*/
	}

	void EnterpriseInfoWidget::addExtendInfoItem( QString key,QString value )
	{
		/*UserExtendInfoWidgetItem* widget = new UserExtendInfoWidgetItem(this);
		widget->setData(key,value);
		QListWidgetItem* item = new QListWidgetItem(mExtendInfoList);
		item->setSizeHint(QSize(180,30));
		mExtendInfoList->addItem(item);
		mExtendInfoList->setItemWidget(item,widget);
		mExtendInfoList->update();*/
	}

	void EnterpriseInfoWidget::onBtnBackToBasicInfo()
	{
		//mInfoStactked->setCurrentIndex(0);
	}

	void EnterpriseInfoWidget::onSerGetUserExtendInfo( int64 userId,std::vector<data::EnterpriseDictionary>&infos )
	{
		if(userId == m_user.userID){
			removeAllsExtendInfoItem();
			for (int i=0;i<infos.size();++i)
			{
				data::EnterpriseDictionary data = infos.at(i);
				if (mExtendType==0 && data.isShow)
				{
					addExtendInfoItem(QString::fromUtf8(data.dicValue.c_str()),QString::fromUtf8(data.dicRealValue.c_str()));
				}
				if (mExtendType==1 && data.isFriend)
				{
					addExtendInfoItem(QString::fromUtf8(data.dicValue.c_str()),QString::fromUtf8(data.dicRealValue.c_str()));
				}
			}
		//	mInfoStactked->setCurrentIndex(1);
			mCurExtendId = m_user.userID;
		}
	}

	void EnterpriseInfoWidget::removeAllsExtendInfoItem()
	{
		//mExtendInfoList->clear();
	}


	 UserExtendInfoWidgetItem::UserExtendInfoWidgetItem( QWidget*parent/*=CNull*/ ):QWidget(parent)
	{
		QHBoxLayout*mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(0,0,0,0);
		mLblValue = new ElidedLabel(this);
		mLblValue->setMinimumWidth(160);
	
		mLblKey = new ElidedLabel(this);
		mLblKey->setMinimumWidth(50);
		mLblKey->setEnabled(false);
		mainLayout->addWidget(mLblKey);
		mainLayout->addWidget(mLblValue);
		mainLayout->addStretch();
		setLayout(mainLayout);
		setFixedHeight(30);
	}

	UserExtendInfoWidgetItem::~UserExtendInfoWidgetItem()
	{

	}

	void UserExtendInfoWidgetItem::setData( QString key,QString value )
	{
		mLblKey->setText(key);
		mLblValue->setText(value);
	}

}