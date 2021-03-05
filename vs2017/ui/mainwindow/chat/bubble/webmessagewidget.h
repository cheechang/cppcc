#ifndef WEBMESSAGEWIDGET_H
#define WEBMESSAGEWIDGET_H
#include "AbstractMessageWidget.h"
class ElidedLabel;
class QTextEdit;
class QLabel;
class QVBoxLayout;
class QGridLayout;
class QHBoxLayout;
class ClickLabel;
class WebMessageWidget : public AbstractMessageWidget
{
	Q_OBJECT
public:
	void setWebMsg(CSharedPtr<data::Msg>&msg);
	WebMessageWidget(QWidget *parent=CNull);
	~WebMessageWidget();
	QSize suggestWidth(int width);

protected slots:
	void onOpenUrl();
protected:
	CSharedPtr<ElidedLabel> mWebUrl;
	CSharedPtr<ElidedLabel> mWebTilte;
	CSharedPtr<QTextEdit>   mWebContent;
	CSharedPtr<QLabel> mWebIcon;
	CSharedPtr<QLabel> mHorLine;
	CSharedPtr<ClickLabel>mBtnOpen;

	CSharedPtr<QGridLayout> mainLayout;
private:
	void init();
	std::string mStrWebUrl;
};

#endif // WEBMESSAGEWIDGET_H
