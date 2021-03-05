#pragma once

#include <QVBoxLayout>
#include<QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include "TWidget.h"
#include "common/controlptr.h"


namespace ui
{
	class UserHeadImg;
	class HeadImage;
	class AddContactWindow;
	class UserInfoCommitee : public TWidget
	{
		Q_OBJECT

	public:
		explicit UserInfoCommitee(QWidget *parent = NULL);
		~UserInfoCommitee();
		void setInfo(const int64 id, const QString name = "", const QString avatar = "", std::string userinfo = "");
		void show(const QPoint& point = QPoint(0, 0));
		void show(const int64 id, const QString name = "", const QString avatar = "", const QPoint& point = QPoint(0, 0));
		void ParseJsonGetUserInfo(std::string jsoninfo);
		void moveHeadPos(QPoint pos);
		void setAfterChatStatus(bool isClose);
		void setSector(int64 id, QString sector);
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

		QVBoxLayout* m_pMainLayout;
		QLabel*  m_pLabelHeadBackground;
		HeadImage*  m_pAvatar;
		QFormLayout* m_pInfoLayout;
		QLabel*	m_pLabelName;
		QLabel*	m_pLabelSex;    //�Ա�
		QLabel*	m_pLabelNation;  //����
		QLabel* m_pLabelposition;  //ְλ
		QLabel*	m_pLabelsector;    //���
		QLabel*	m_pLabelgroup;  //����
		QLabel* m_pLabelspecialCommittee;    //רί��
		QLabel* m_pLabelspecialCommitteeDuty;   //רί��ְ��
		QLabel* m_pLabelcurrentPosition;  //����ְ��
		QLabel*	m_pLabelmyLocation;    //���ڵ�
		QLabel*	m_pLabelmemNum;    //ίԱ��

		QWidget* widget;
	//	QScrollArea* scroll;

		QVBoxLayout*m_pSendMsgOrAddLayout;
		QPushButton* m_pButtonAdd;
		QPushButton* m_pButtonSendMsg;
		AddContactWindow* m_addContactWin;

		int64 m_id;
		data::Contact m_contactInfo;

		QString m_sex;
		QString m_nation;
		QString m_position;
		QString m_sector;
		QString m_group;
		QString m_specialCommittee;
		QString m_specialCommitteeDuty;
		QString m_currentPosition;
		QString m_myLocation;
		QString m_memberNum;
		bool m_closeAfterChat;
	};
}