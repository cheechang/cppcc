#ifndef CARDMESSAGEWIDGET_H
#define CARDMESSAGEWIDGET_H
#include "AbstractMessageWidget.h"
#include "../../controls/headimage.h"

class ElidedLabel;
class CardMessageWidget : public AbstractMessageWidget
{
	Q_OBJECT

public:
	CardMessageWidget(QWidget *parent=CNull);
	~CardMessageWidget();
	void setCardMsg(CSharedPtr<data::Msg>&msg);
	QSize suggestWidth(int width);
	void setIsBurnCard(bool isBurn);
signals:
	void signalSerGetUserInfo(int, data::UserData&);
	void showUserInfoWidget(int64, QString, QString);
	void signalSerShowUserInfo(int64, QString, QString);
protected slots:
	void onSerGetUserInfo(int code, data::UserData&user);
	void onHeadClicked();
private:
	ElidedLabel*mName;
	int64 mUserId;
	ui::HeadImage*mHead;
	bool m_isBurn;
};

#endif // CARDMESSAGEWIDGET_H
