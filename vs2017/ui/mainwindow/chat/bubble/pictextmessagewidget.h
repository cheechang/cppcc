#ifndef PICTEXTMESSAGEWIDGET_H
#define PICTEXTMESSAGEWIDGET_H
#include "abstractmessagewidget.h"
class PicTextMessageWidgetPrivate;
class PicTextMessageWidget:public AbstractMessageWidget
{
	Q_OBJECT
public:
	explicit PicTextMessageWidget(QWidget* parent = 0);
	~PicTextMessageWidget();
	void setPicText(CSharedPtr<data::Msg>&msg);
	QSize suggestWidth(int width);
signals:
	void openUrl(std::string url);
private:
	PicTextMessageWidgetPrivate* d_ptr;
};
#endif