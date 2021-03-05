#ifndef ENTERPRISEINFOWIDGET_H
#define ENTERPRISEINFOWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <data/entpriseInfo.h>
#include <data/ContactData.h>
#include <QLabel>
#include<QStackedWidget>
#include <QPushButton>
#include <QListWidget>
#include "../controls/ElidedLabel.h"
#include <common/Controlptr.h>
#include <common/Connect.h>
#include "../../common/Common.h"
namespace data{
	class ChatInfo;
}
namespace ui{
	class UserInfoCommon;
	class UserInfoCommitee;
	class PushButton;
	class HeadImage;
	class UserExtendInfoWidgetItem:public QWidget{
		Q_OBJECT
	public:
		UserExtendInfoWidgetItem(QWidget*parent=CNull);
		virtual ~UserExtendInfoWidgetItem();
		void setData(QString key,QString value);
	protected:
		ElidedLabel* mLblKey;
		ElidedLabel* mLblValue;
	};
	class EnterpriseInfoWidget : public QWidget
	{
		Q_OBJECT
	public:
		enum{
			CenterWidgetMinWidth = 340,
			CenterWidgetMinHeight = 500,
			ConterWidgetTopMargin = 20,
			SendMsgBtnRightMargin = 64,
			NameTopMargin = 20,
			GridLayoutInforSpacing = 10,
			GridLayoutInforLeftMargin = 60

		};
		EnterpriseInfoWidget(QWidget *parent = CNull);
		~EnterpriseInfoWidget();

		void updateData( data::OrgAndUserInfo user );
		void signalsDisconnect();
		void hideMoreInfoBtn();
		void addExtendInfoItem(QString key,QString value);
		void removeAllsExtendInfoItem();
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		void signalSerGetUserExtendInfo(int64 userId,std::vector<data::EnterpriseDictionary>&);
		void signalSerShowMoreInfo();
		void signalSerGetUserInfo(int, data::UserData&);
	protected slots:
	    void slotStartChat();
		void onBtnViewExtendsInfo();
		void onBtnBackToBasicInfo();
		void onSerGetUserExtendInfo(int64 userId,std::vector<data::EnterpriseDictionary>&infos);
		void onSerGetUserInfo(int, data::UserData&);
	protected:
		void paintEvent(QPaintEvent *event);
	protected:
		CSharedPtr<QWidget> m_centerWidget;
		CSharedPtr<QVBoxLayout> m_centerWidgetLayout;

		CSharedPtr<QWidget> m_centerHeadWidget;
		CSharedPtr<QWidget> m_centerContentWidget;
		
		CSharedPtr<PushButton>  m_btnSendMsg;
		CSharedPtr<HeadImage>  m_btnHead;

		QList<CSharedPtr<QLabel>>    m_lblList;
		QList<CSharedPtr<QLineEdit>> m_edtList;

		CSharedPtr<QLineEdit> m_nameLineEdit;
		CSharedPtr<QVBoxLayout> m_vOrgInfoLayout;
		CSharedPtr<QGridLayout> m_gridOrgInfoLayout;
		CSharedPtr<QHBoxLayout> m_contentLayout;
		CSharedPtr<QVBoxLayout> m_centerVWidgetLayout;

		CSharedPtr<UserInfoCommon> m_pUserInfoCommomWidget;
		CSharedPtr<UserInfoCommitee> m_pUserInfoCommiteeWidget;
		//扩展字段相关
		//QStackedWidget* mInfoStactked;
		QWidget* mBasicWidget;
	//	QWidget* mExtendsWidget;
		QPushButton* mBtnViewMoreInfo;
		//扩展字段列表
		//QListWidget* mExtendInfoList;
		int64 mCurExtendId;
		int64 id;
		QString name ;
		QString avatar;
		std::string UserInfoExtend;
		std::string Usertype;
		QString m_sex;
		QString m_nation;

	//	QPushButton* mBtnBackBasicInfo;
		data::OrgAndUserInfo  m_user;
		int mExtendType;//0:组织架构;1:好友;2:陌生人
		IContactMgrControl_Ptr mContactContrl;
		IChatMgrControl_Ptr mChatMgrControl;
	};
}

#endif // ENTERPRISEINFOWIDGET_H
