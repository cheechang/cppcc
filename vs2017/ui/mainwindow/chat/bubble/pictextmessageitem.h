#ifndef PICTEXTMESSAGEITEM_H
#define PICTEXTMESSAGEITEM_H
#include "TWidget.h"
#include "common/Controlptr.h"
class QListWidget;
class QLabel;
class ClickLabel;
class QListWidgetItem;
class QHBoxLayout;
class QVBoxLayout;
namespace data{
  class Msg;
};
class PicTextDelegate:public ui::TWidget{
	Q_OBJECT
public:
	enum DelegateType{
		DELEGATE_INIT,
		DELEGATE_SIGLETITLEMSG, //单图文单标题
		DELEGATE_TITLE_MULTIMSG,//多图文标题列
	    DELEGATE_MULTIMSG,//多图文非标题列
	};
	PicTextDelegate(DelegateType type,data::MsgPicWithText::picTextBean*msg,IChatMgrControl_Ptr& chatcontrol,qint64 targetId,QWidget *parent=CNull);
	~PicTextDelegate();
	void ReadAll();
signals:
	void signalSerDownLoadImg(int err,const std::string& imgname,int64 targetid);
	void openUrl(std::string url);
public slots:
	void onSerDownLoadImg(int err,const std::string& imgname,int64 targetid);
protected:
	void  CreateSigleTitleItem(data::MsgPicWithText::picTextBean*msg);
	void  CreateMultiTitleItem(data::MsgPicWithText::picTextBean*msg);
	void  CreateMultiContentItem(data::MsgPicWithText::picTextBean*msg);
	void  downLoadImg(std::string&url);
protected:
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
private:
	CSharedPtr<QLabel> m_tiltle;
	CSharedPtr<QLabel> m_image;
	CSharedPtr<QLabel> m_desc;
	CSharedPtr<ClickLabel> m_readall;
	IChatMgrControl_Ptr m_chatcontrol;
	QVBoxLayout* m_sigletitlelayout;
	QHBoxLayout* m_multicontentlayout;
	qint64 m_targetid;
	QString m_url;
	//ui::AppWebView mWebview;
};
class PicTextMessageItem:public ui::TWidget{
	Q_OBJECT
public:
	PicTextMessageItem(IChatMgrControl_Ptr&chatcontrol,qint64 targetId,QWidget *parent=CNull);
	~PicTextMessageItem();
	QSize sizeHint() const;
	void InsertItem(CSharedPtr<data::Msg>&msg);
signals:
	void openUrl(std::string url);
public slots:
	void onItemClicked( QListWidgetItem*item );
private:
	qint64 m_targetid;
	CSharedPtr<QListWidget> m_listWidget;
	IChatMgrControl_Ptr& m_chatcontrol;
};
#endif