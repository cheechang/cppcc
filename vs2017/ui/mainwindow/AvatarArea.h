#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include "common/Controlptr.h"


namespace ui{
	class HeadImage;
	class AvatarArea :
		public QWidget
	{
		Q_OBJECT
	public:
		explicit AvatarArea(QWidget *parent = 0);
		~AvatarArea(void);

		void setAvatarPath(QString avatarPath);
	signals:
		void click(QPoint pos);
		void signalSerHeadUpdate(int64,const std::string&);
		void signalSerSetUserVerify(int err);
		void signalSerNetChangedCb(int);
		void signalSerReLoginCb(int,int64);
		void signalSerUserAccount(data::AccountInfo&);
	public slots:
		void onSerUserAccount(data::AccountInfo&account);
		void onSerHeadUpdate(int64 targetID,const std::string& avatar);
		void onSerSetUserVerify(int err);
		void onSerNetChangedCb(int flag);
		void onSerReLoginCb(int code,int64 userId);
	private:
		CSharedPtr<data::AccountInfo>m_userinfo;
		IUserControl_Ptr m_pUserCtrl;
		QHBoxLayout* m_pLayout;
		HeadImage* m_pAvatar;
		IAuthControl_Ptr mAuthControl;
	};
}

