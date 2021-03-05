#ifndef SELECTMEMBERWINDOW_H
#define SELECTMEMBERWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include "BaseWindow.h"
#include "../../controls/TWidget.h"
#include "data/UserData.h"
#include "data/ChatData.h"
#include "data/GroupData.h"
namespace ui{
	class CreateGroupHomeArea;
	class CreateGroupSelectMemberArea;
	/**
	** 创建群主界面
	**/
	class CreateGroupWindow :public BaseWindow
	{
		Q_OBJECT
	public:
		CreateGroupWindow(QWidget *parent =CNull);
		~CreateGroupWindow();
		void showWin();
		void showWin(data::TinyGroup group);
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&chat);
	protected slots:
		void onShowHomeArea();
		void onShowSelMemsArea(QMap<int64,int64>);
		void onSelectMemsResult(std::vector<data::UserBasicData>&);
		void onColse();
	private:
		QStackedWidget* mStackedWidget;
		CreateGroupHomeArea* mHomeArea;
		CreateGroupSelectMemberArea* mSelMemArea;
		data::TinyGroup mGroup;
	};
}
#endif // SELECTMEMBERWINDOW_H
