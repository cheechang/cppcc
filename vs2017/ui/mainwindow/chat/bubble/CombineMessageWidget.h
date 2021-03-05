#ifndef COMBINEMESSAGEWIDGET_H
#define COMBINEMESSAGEWIDGET_H
#include <QListWidget>
#include "TWidget.h"
#include "abstractmessagewidget.h"
#include "../../controls/ElidedLabel.h"
#include "detail/clicklabel.h"

class CombineMessageItem:public QWidget{
	Q_OBJECT
public:
	CombineMessageItem(QWidget*parent);
	ElidedLabel*mLblName;
	ElidedLabel* mLblContext;
	int64 mFromId;
};

class CombineMessageWidgetPrivate:public ui::TWidget{
	Q_OBJECT
public:
	CombineMessageWidgetPrivate(QWidget*parent,IChatMgrControl_Ptr chatCtrl=CNull);
	void setData(std::vector<CSharedPtr<data::Msg>>data);
	QSize size();
	QMap<int64,data::UserData> users();
signals:
	void signalSerGetUserInfor(int, data::UserData&);
	void clicked();
protected slots:
	void onSerGetUserInfor(int code, data::UserData& data);
private:
	QListWidget* mListwidget;
	ClickLabel* mBtnViewInfo;
	IChatMgrControl_Ptr mChatCtrl;
	QMap<int64,data::UserData>mMapUser;
	QList<int64>mNeedGetItems;
};

class CombineMessageWidget : public AbstractMessageWidget
{
	Q_OBJECT
public:
	CombineMessageWidget(QWidget *parent=0);
	~CombineMessageWidget();

	void setCombineMsg(CSharedPtr<data::Msg>&msg);
	QSize suggestWidth(int width);
protected slots:
	void onShowMsgWin();
private:
	CombineMessageWidgetPrivate* d_ptr;
};

#endif // COMBINEMESSAGEWIDGET_H
