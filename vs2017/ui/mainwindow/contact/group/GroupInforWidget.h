#ifndef GROUPINFORWIDGET_H
#define GROUPINFORWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <interface/IGroupMgrControl.h>
#include "common/controlptr.h"
#include <QFileDialog>
#include <QDesktopServices>
#include "interface/Defines.h"
#include "ServiceDefine.h"
#include "json.h"
class QPushButton;
namespace data{
	class ChatInfo;
}
namespace ui{
	class HeadImage;
	class ToolButton;
	class PushButton;
	class GroupInforSettingTabWidget;
	class GroupInforWidget : public QWidget
	{
		Q_OBJECT

	public:
		GroupInforWidget(QWidget *parent=CNull);
		~GroupInforWidget();
		void updateData(int64 groupId);
		void initControl();
		void setStartChatCLose(bool close=false);
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		void signalSerDelUiFile(int64, int64);
		void signalSerUpgroupInfo(int);
		void signalSerUpSuccess(int);
		void signalSerGetMemInfo(int, data::Member&);
	protected slots:
		void onStartChat();
		void onEditProfile();
		void onSerDelUiFile(int64);
		void onSerModifyHead();
		void onGroupHeadSucc(std::string& headUrl);
		void onSerUpgroupInfo(int code);
		void onUserHeadSucc(QString headImg);
		void onSerGetMemInfo(int, data::Member&);
	protected:
		void paintEvent(QPaintEvent *event);
	private:
		CSharedPtr<QVBoxLayout> m_backgroundLayout;

		CSharedPtr<QWidget>    m_headAreaBackWidget;
		CSharedPtr<HeadImage>    m_groupHeadWidget;
		CSharedPtr<QVBoxLayout> m_headAreaLayout;
		CSharedPtr<QLineEdit>    m_lblName,m_lblId;
		ToolButton*  m_btnSendMsg;
		ToolButton*  m_btnBottomSendMsg;

		QPushButton*  m_SendMsgBtn;

		CSharedPtr<QWidget>    m_inforAreaBackWidget;
		CSharedPtr<GroupInforSettingTabWidget> m_inforTab;
		CSharedPtr<QPushButton> m_btnEditInfo;

		CSharedPtr<control::IGroupMgrControl> m_groupmgrcontrol;
		IUserControl_Ptr m_usercontrol;
		data::Group group;
		int64 m_userid;
		bool mCLoseAfterChat;
	};

	class GroupInforWidgetDlg : public GroupInforWidget
	{
	public:

		GroupInforWidgetDlg(QWidget *parent = CNull){
			Qt::WindowFlags flags = this->windowFlags();
			//flags |= Qt::Popup;
			///flags |= Qt::WindowStaysOnTopHint;
			flags |= Qt::Dialog;
			flags |= Qt::WindowCloseButtonHint;
			flags &= ~Qt::WindowMaximizeButtonHint;
			flags &= ~Qt::WindowMinimizeButtonHint;
		
		};
		~GroupInforWidgetDlg(){
		
		};
	};


}

#endif // GROUPINFORWIDGET_H
