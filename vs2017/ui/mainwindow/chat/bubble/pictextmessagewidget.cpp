#include "pictextmessagewidget.h"
#include "pictextmessageitem.h"
class PicTextMessageWidgetPrivate
{
public:
	void init(IChatMgrControl_Ptr&chatcontrol,qint64 targetid);
	QSize sizeHint() const;
	PicTextMessageWidget* q_ptr;
	PicTextMessageItem* pictextitem;
};
void PicTextMessageWidgetPrivate::init(IChatMgrControl_Ptr&chatcontrol,qint64 targetid)
{
	pictextitem = new PicTextMessageItem(chatcontrol,targetid,q_ptr);
	pictextitem->setStyleSheet("background-color:transparent;");
	q_ptr->setCentralWidget(pictextitem);
}
QSize PicTextMessageWidgetPrivate::sizeHint() const
{
	return pictextitem->sizeHint();
}

PicTextMessageWidget::PicTextMessageWidget(QWidget* parent):d_ptr(CNull){
	d_ptr = new PicTextMessageWidgetPrivate;
	d_ptr->q_ptr = this;
	d_ptr->init(m_chatcontrol,this->targetId());
	d_ptr->q_ptr->setStyleSheet("background-color:transparent;");
	connect(d_ptr->pictextitem,SIGNAL(openUrl(std::string)),this,SIGNAL(openUrl(std::string)));
}
PicTextMessageWidget::~PicTextMessageWidget(){
	delete d_ptr;
}
void PicTextMessageWidget::setPicText(CSharedPtr<data::Msg>&msg){
	if (CNull == msg) return;
	//图文消息发送
	if (!msg->isRecvMsg && !msg->isDeviceMsg && !msg->msgId)
	{
		
	}
	d_ptr->pictextitem->InsertItem(msg);
}
QSize PicTextMessageWidget::suggestWidth(int width){
	Q_UNUSED(width);
	QSize size = d_ptr->sizeHint()+QSize(30,0);
	return size;
}