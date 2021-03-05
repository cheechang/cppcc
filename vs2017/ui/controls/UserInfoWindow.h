#pragma once

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
	class UserInfoWindow : public TWidget
	{
		Q_OBJECT

	public:
		explicit UserInfoWindow(QWidget *parent = NULL);
		~UserInfoWindow();
		void setInfo(const int64 id, const QString name = "", const QString avatar = "");
		void show(const QPoint& point = QPoint(0, 0));
		void show(const int64 id, const QString name = "", const QString avatar = "", const QPoint& point = QPoint(0, 0));

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
		QLabel*	m_pLabelSex;
		QLabel*	m_pLabelPhone;
		QLabel* m_pLabelEmail;
		QPushButton* m_pButtonAdd;

		AddContactWindow* m_addContactWin;

		int64 m_id;
		data::Contact m_contactInfo;
	};
}