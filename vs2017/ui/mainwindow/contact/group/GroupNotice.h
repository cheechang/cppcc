#pragma once

#include <QListWidget>
#include <QVBoxLayout>
#include <data/ContactData.h>
#include <data/ChatData.h>
#include "controls/TWidget.h"
#include "interface/Defines.h"
#include "common/Controlptr.h"
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QAction>
#include "common/UIUtils.h"
#include <QPushButton>
#include <QFileDialog>
#include <QStackedWidget>
#include <QDesktopServices>
#include <QTextEdit>
#include "json.h"

namespace ui
{
	class GroupNoticeItem;
	class GroupNotice : public TWidget
	{
		Q_OBJECT
	public:
		GroupNotice(QWidget *parent = CNull);
		~GroupNotice();
		void updateData(int64 groupId);
		void AddDataToList(QString filepath);
	protected:
		bool isGroupOwner();
		void setBtnEnble(bool isEnble);
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&);
		void signalSerGetGroupInfo(int, CSharedPtr<data::Group>&);
		void signalSerNoticePushResult(int);
		void signalSerGetGroupMem(int code, data::Member& mem);
	public slots:
		void onMaxChatCheck();
		void onSerPushNotice();
		void onSerCancelNoticeBtn();
		void onSerNoticeBtn();
		void onSerNoticePushResult(int);
		void onSerGetGroupMem(int code, data::Member& mem);
	private:
		int addItemToList(const data::Group& pGroupInfo);
		int insertItemToList(const data::Group& pGroupInfo);
		void clearList();
		
		IGroupMgrControl_Ptr m_pGroupControl;
		QMap<int64, data::FileInfo> m_mapData;

		QListWidget* m_pListWidget;
		QLabel* m_NoticeExPlainLab;
		QWidget* m_NoticeEditWidget;
		QHBoxLayout* m_NoticeBtnLayout;
		QVBoxLayout* m_NoticeLayout;
		QTextEdit* m_NoticeTextEdit;
		QPushButton* m_NoticeBtn;
		QPushButton* m_CancelNoticeBtn;
		

		QStackedWidget* m_NoticeStackWidget;
		QHBoxLayout* m_FuncLayout;
		QVBoxLayout* m_pMainLayout;
		QWidget* Funcwidget;
		QLabel* mlblBg;
		int64 m_groupId;
		int64 m_curItemId;
		CSharedPtr<data::AccountInfo> m_userinfo;

		QPushButton*  m_PushNoticebtn;

		QLabel*	m_tipInfo;

	};
}
