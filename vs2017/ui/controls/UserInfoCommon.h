#pragma once
#include<QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include "TWidget.h"
#include "common/controlptr.h"


namespace ui
{
	class UserHeadImg;
	class HeadImage;
	class AddContactWindow;
	class UserInfoCommon : public TWidget
	{
		Q_OBJECT

	public:
		explicit UserInfoCommon(QWidget *parent = NULL);
		~UserInfoCommon();
		void setInfo(const int64 id, const QString name = "", const QString avatar = "",std::string userinfo = "");
		void show(const QPoint& point = QPoint(0, 0));
		void show(const int64 id, const QString name = "", const QString avatar = "", const QPoint& point = QPoint(0, 0));

		void ParseJsonGetUserInfo(std::string jsoninfo);
		void setAfterChatStatus(bool isClose);
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&);
		void addContact(data::SearchResultInfo&);
		void signalSerGetBuddyInfoFromNetResult(int, data::Contact&);
		void signalSerAddContactResult(int);

	public slots:
		void onAddClicked();
		void onStartChatClicked();
		void onSerAddContactResult(int code);
		void onSerGetBuddyInfoFromNetResult(int code, data::Contact& contact);

	protected:
		virtual void focusOutEvent(QFocusEvent* event);

	private:
		void initWidget();
		void initLayout();
		void setContact(data::Contact& contact, const QString name = "", const QString avatar = "");
		
		IContactMgrControl_Ptr m_pContactControl;
		IUserControl_Ptr m_pUserControl;

		QVBoxLayout* m_pMainLayout;
		QLabel*  m_pLabelHeadBackground;
		HeadImage*  m_pAvatar;
		QFormLayout* m_pInfoLayout;
		QLabel*	m_pLabelName;
		QLabel*	m_pLabelSex;    //性别
		QLabel*	m_pLabelNation;  //民族
		QLabel* m_pLabelunit;    //单位
		QLabel* m_pLabeloffice;   //处室
		QLabel* m_pLabelposition;  //职位

		QVBoxLayout*m_pSendMsgOrAddLayout;
		QPushButton* m_pButtonAdd;
		QPushButton* m_pButtonSendMsg;

		AddContactWindow* m_addContactWin;

		int64 m_id;
		data::Contact m_contactInfo;

		std::string Currenttype;
		QString m_sex;
		QString m_nation;
		QString m_unit;
		QString m_office;
		QString m_position;
		bool m_closeAfterChat;
	};
}