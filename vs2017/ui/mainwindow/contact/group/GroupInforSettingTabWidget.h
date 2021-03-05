#ifndef GROUPINFORSETTINGTABWIDGET_H
#define GROUPINFORSETTINGTABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include "interface/Defines.h"
#include <data/ChatData.h>
#include <data/GroupData.h>
#include <PushButton.h>
namespace ui{
	class GroupInforSettingArea;
	class GroupInforMembersArea;
	class GroupFileList;
	class GroupNotice;
	class GroupInforSettingTabWidget : public QWidget
	{
		Q_OBJECT
	public:
		GroupInforSettingTabWidget(QWidget *parent=CNull);
		~GroupInforSettingTabWidget();
		void initGroupSetting();
		void intitGroupMems();
		void initGroupFiles();
		void initGroupNotice();
		void updateData(int64 gorupId);
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		void signalSerSecret(bool);
		void signalSerDelUiFile(int64);
	protected:
		void paintEvent(QPaintEvent *event);

	protected slots:
		void onTabCurentChanged(int index);
	private:
		CSharedPtr<QVBoxLayout> m_mainLayout;
		CSharedPtr<QTabWidget> m_tabWidget;
		CSharedPtr<GroupInforSettingArea> m_areaSetting;
		CSharedPtr<GroupInforMembersArea> m_areaMems;
		CSharedPtr<GroupFileList> m_areaFiles;
		CSharedPtr<GroupNotice> m_areaNotice;

		int64 mGorupId;
	};
}
#endif // GROUPINFORSETTINGTABWIDGET_H
