#include "AvatarArea.h"
#include "controls/headimage.h"
#include "data/UserData.h"
#include "log.h"
#include <interface/IUserService.h>
#include<utils/common.h>
namespace ui{
	AvatarArea::AvatarArea(QWidget *parent)
		: QWidget(parent)
		, m_pLayout(NULL)
		, m_pAvatar(NULL)
		,m_userinfo(CNull)
	{
		m_pUserCtrl = USERCONTROL;

		m_pLayout = new QHBoxLayout(this);
		m_pAvatar = new HeadImage(this, QSize(40, 40), true);
		m_pAvatar->setMouseInStyle(true);
		connect(m_pAvatar, SIGNAL(clicked(QPoint)), this, SIGNAL(click(QPoint)));
		m_pLayout->addWidget(m_pAvatar);
		m_pLayout->setContentsMargins(10, 0, 20, 0);
		m_pLayout->addStretch();
		setLayout(m_pLayout);
		CONNECT_SERVICE(HeadUpdate(int64,const std::string&));
		CONNECT_SERVICE(SetUserVerify(int ));
		CONNECT_SERVICE(UserAccount(data::AccountInfo&));

		m_pUserCtrl->RegHeadUpdate(CBind
			(&AvatarArea::signalSerHeadUpdate,this,CPlaceholders  _1,
			CPlaceholders  _2));
		m_pUserCtrl->regOperateUserCb(CBind(&AvatarArea::signalSerUserAccount,this,CPlaceholders  _1));
		m_userinfo = m_pUserCtrl->GetAccountInfo();
		QString path = QString::fromLocal8Bit(utils::GetHeadPath(m_userinfo->gender.value(), m_userinfo->avatar.value()).c_str());
		//Log(LOG_LEV_INFO, LOG_FILE, "avatar path:%s", path.toStdString().c_str());
		m_pAvatar->setAvatarPath(path);

		mAuthControl = AUTHCONTROL;
		CONNECT_SERVICE(NetChangedCb(int));
		CONNECT_SERVICE(ReLoginCb(int,int64));
		mAuthControl->regReLoginCb(CBind(&AvatarArea::signalSerReLoginCb,this,CPlaceholders  _1,CPlaceholders  _2));
		mAuthControl->regNetChangedCb(CBind(&AvatarArea::signalSerNetChangedCb,this,CPlaceholders  _1));
			/*type:   4 (好友验证方式)
	*value : 1：需要验证信息, 2 : 不允许任何人添加, 3 : 允许任何人添加，默认1*/
	/*	std::vector<model::PersonalData> items;
		model::PersonalData item;
		item.type = 4;
		item.val = 3;
		items.push_back(item);
		m_pUserCtrl->setPersonalData(items, CBind(&AvatarArea::signalSerSetUserVerify, this, CPlaceholders  _1));*/
	}


	AvatarArea::~AvatarArea(void)
	{
	}
	void AvatarArea::onSerHeadUpdate(int64 targetID,const std::string& avatar){
	  BEGIN;
		if ( targetID ==m_userinfo->id.value() )
		{
			QString avatarPath = QString::fromUtf8(avatar.data());
			AddLog(LOG_LEV_DEBUG,"***update user head,path=%s",avatar.c_str());
			m_pAvatar->setAvatarPath(avatarPath);
		}
	  END;
	}
	void AvatarArea::onSerSetUserVerify(int err){
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"onSerSetUserVerify errCode=%s",err);
		}
	}
	void AvatarArea::setAvatarPath(QString avatarPath)
	{
		m_pAvatar->setAvatarPath(avatarPath);
	}

	void AvatarArea::onSerNetChangedCb( int flag )
	{
		m_pAvatar->setShowAsGray(flag == -1);
	}

	void AvatarArea::onSerReLoginCb( int code,int64 userId )
	{
		if (code == 0)
		{
			m_pAvatar->setShowAsGray(false);
		}
	}

	void AvatarArea::onSerUserAccount( data::AccountInfo&account )
	{
		m_pAvatar->setAvatarPath(QString::fromLocal8Bit(account.thumbAvatar.value().c_str()));
	}

}
