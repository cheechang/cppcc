#pragma once
#include "../contact/createGroup/BaseWindow.h"
#include "common/controlptr.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QStackedWidget>

namespace ui
{

	class MsgManagerWidget : public BaseWindow{
		Q_OBJECT
	public:
		MsgManagerWidget(QWidget *parent=CNull);
		~MsgManagerWidget();

		void Init();
		void addListItem(std::string head, std::string name, int64 id,int CountMsg);
		void clearlist();
		void MsgShowDeal(CSharedPtr<data::Msg> msg, std::string username);
		void keyPressEvent(QKeyEvent * event);
	signals:
		void signalSerSerchGlobalMsg(int, data::MsgSearchResult&);
		void signalSerSerchDetailMsg(int, data::MsgDetailSearchResult&);
		void signalSerGetUserInfo(int, data::UserData&,CSharedPtr<data::Msg>);
	public slots:
		void onSerSerchMsg();
		void onSerSerchGlobalMsg(int code, data::MsgSearchResult& msg);
		void onSerSerchDetailMsg(int code, data::MsgDetailSearchResult& detailmsg);
		void onSerClickItem(QListWidgetItem*);
		void onSerGetUserInfo(int code, data::UserData& usrdata,CSharedPtr<data::Msg>);
		void onSerClearBtnClicked();
	private:
		QVBoxLayout* m_Mainlayout;
		QHBoxLayout* m_Funclayout;
		QVBoxLayout* m_Msgshowlayout;
		QHBoxLayout* m_FrideMsgLayout;
		QVBoxLayout* m_Frideshowlayout;
		QWidget* Funcwidget;
		QWidget* Msgshowwidget;
		QWidget* Frideshowwidget;
		QWidget* FrideMsgshowwidget;

		QStackedWidget* m_MsgshowStackWidget;

		QComboBox* m_TimeRangBox;
		QLabel* m_TimeLabel;

		QLineEdit* m_SerchTextEdit;

		QPushButton* m_SerchBtn;
		QPushButton* m_deleteBtn;

		QLabel* m_SerchResultlbl;
		QListWidget* m_FridelistWidget;

		QTextEdit* m_MsgContentShowEdit;


		IChatMgrControl_Ptr	m_chatcontrol;
		IContactMgrControl_Ptr m_contactcontrol;
		IUserControl_Ptr m_usercontrol;

		int64 m_NextTargetid;
		std::string m_keyword;
		int64 m_starttime;
		int64 m_endtime;
		int64 m_curUserId;
	};
}