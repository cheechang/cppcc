#ifndef TEMPLATEMESSAGEWIDGET_H
#define TEMPLATEMESSAGEWIDGET_H
#include "abstractmessagewidget.h"
#include "controls/TWidget.h"
#include "../../workbench/AppWebView.h"
class QTextEdit;
class QListWidget;
class ClickLabel;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class TemplateMessageWidgetPrivate;

class TemplateRepeatItem:public QWidget{
public:
	explicit TemplateRepeatItem(QString&key,QString&val,QWidget* parent = 0);
	~TemplateRepeatItem();
private:
	CSharedPtr<ClickLabel> m_key;
	CSharedPtr<ClickLabel> m_val;
	CSharedPtr<QHBoxLayout> m_mainlayout;
};
class TemplateMessageItem:public ui::TWidget
{
	Q_OBJECT
public:
	explicit TemplateMessageItem(QWidget* parent = 0);
	~TemplateMessageItem();
	void setTemplateMsg(CSharedPtr<data::Msg>&msg);
signals:
	void openUrl(std::string url);
protected:
	QSize ContentSize();
	int  AddFields(std::map<std::string,std::string> fields);
public slots:
	void onclicked();
private:
	ui::AppWebView mWebview;
	CSharedPtr<QWidget> m_tiltlewidget;
	CSharedPtr<ClickLabel> m_tiltle;
	CSharedPtr<QTextEdit> m_content; 
	CSharedPtr<QListWidget> m_fields; 
	CSharedPtr<QWidget>m_spliter; 
	CSharedPtr<ClickLabel> m_detail;
	CSharedPtr<QVBoxLayout> m_mainlayout;
	QString m_detailurl;
};

class TemplateMessageWidget:public AbstractMessageWidget
{
	Q_OBJECT
public:
	explicit TemplateMessageWidget(QWidget* parent = 0);
	~TemplateMessageWidget();

	void setTemplate(CSharedPtr<data::Msg>&msg);
	QSize suggestWidth(int width);
private:
	TemplateMessageWidgetPrivate* d_ptr;
};
#endif