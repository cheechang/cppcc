#ifndef APPINFOWIDGET_H
#define APPINFOWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "../enterprise/enterpriseinfowidget.h"
#include <common/Controlptr.h>
#include <common/Connect.h>
#include <data/UserData.h>


namespace ui{
	class AppInfoWidget : public EnterpriseInfoWidget
	{
		Q_OBJECT

	public:
		void updateData(int64 appId);
		AppInfoWidget(QWidget *parent=CNull);
		~AppInfoWidget();
	signals:
		void signalSerGetAppInfo(int, data::EntAppinfo&);
	protected slots:
		void onSerGetAppInfo(int code, data::EntAppinfo&data);
		void slotStartChat();
		void onBtnViewHistoryMsg();
	private:
		void init();
		CSharedPtr<QPushButton>mBtnGetHistoryMsg;
		data::EntAppinfo mData;
		IUserControl_Ptr mUserControl;
	};
}
#endif // APPINFOWIDGET_H
