#ifndef BURNMESSAGEWIDGET_H
#define BURNMESSAGEWIDGET_H

#include "AbstractMessageWidget.h"
#include <QMovie>
#include <QLabel>
#include <QPushButton>
class BurnMessageWidget : public AbstractMessageWidget
{
	Q_OBJECT

public:
	BurnMessageWidget(QWidget *parent=CNull);
	~BurnMessageWidget();
	void setBurnMsg(CSharedPtr<data::Msg>&msg);
	QSize suggestWidth(int width);
signals:
	void viewBurnMsg(CSharedPtr<data::Msg>& msg);
protected slots:
	void onViewBurnMsg();
private:
	QMovie* mMovie;
	QLabel* mLblMve;
	QPushButton* mBtnBurn;
};

#endif // BURNMESSAGEWIDGET_H
