#include "templatemessagewidget.h"
#include "detail/clicklabel.h"
#include "detail/textutils.h"
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
TemplateRepeatItem::TemplateRepeatItem(QString&key,QString&val,QWidget* parent):QWidget(parent),m_key(CNull),
m_val(CNull)
{
	this->setFixedWidth(280);
	m_key = CMakePtr<ClickLabel>(this);
	m_val = CMakePtr<ClickLabel>(this);
	m_mainlayout = CMakePtr<QHBoxLayout>(this);

	m_key->setText(key+QString(":"));
	m_val->setText(val);
	m_key->setTextColor(Qt::gray);
	m_key->setAlignment(Qt::AlignLeft);
	m_mainlayout->addWidget(m_key.get());
	m_mainlayout->addWidget(m_val.get());
	m_mainlayout->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	m_mainlayout->setSpacing(5);
	m_mainlayout->setContentsMargins(0,0,0,0);
	this->setLayout(m_mainlayout.get());
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(Qt::white));
	this->setPalette(palette);
}
TemplateRepeatItem::~TemplateRepeatItem(){

}
TemplateMessageItem::TemplateMessageItem(QWidget* parent):ui::TWidget(parent),m_detailurl(""){
	this->setFixedWidth(300);
	m_tiltlewidget = CMakePtr<QWidget>(this);
	m_tiltle       = CMakePtr<ClickLabel>(this);
	m_content      = CMakePtr<QTextEdit>(this);
	m_fields	   = CMakePtr<QListWidget>(this); 
	m_spliter	   = CMakePtr<QWidget>(this); 
	m_detail	   = CMakePtr<ClickLabel>(this); 
	m_mainlayout   = CMakePtr<QVBoxLayout>(this); 

	QVBoxLayout* tiltlelayout = new QVBoxLayout(this);
	tiltlelayout->addWidget(m_tiltle.get());
	tiltlelayout->setAlignment(Qt::AlignTop);
	m_tiltlewidget->setLayout(tiltlelayout);
	m_tiltlewidget->setFixedHeight(30);
	m_tiltle->setFixedHeight(20);

	m_spliter->setFixedHeight(1);
	m_spliter->setStyleSheet("QWidget{background-color:gray;}");

	m_content->document()->setDocumentMargin(0);
	m_content->setFrameShape(QFrame::NoFrame);
	m_content->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	m_content->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_content->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_content->setReadOnly(true);
	m_content->setFixedWidth(280);

	m_fields->setFixedSize(0,0);
	m_detail->setText(transfer("²é¿´ÏêÇé"));
	m_detail->setTextColor(QColor(64,153,242));
	CONNECT_SUBCTRL(m_detail,clicked());

	QHBoxLayout* detaillayout = new QHBoxLayout(this);
	detaillayout->addStretch();
	detaillayout->addWidget(m_detail.get());
	detaillayout->setContentsMargins(0,0,0,0);
	m_mainlayout->setSpacing(5);
	m_mainlayout->addWidget(m_tiltlewidget.get());
	m_mainlayout->addWidget(m_content.get());
	m_mainlayout->addWidget(m_fields.get());
	m_mainlayout->addWidget(m_spliter.get());
	m_mainlayout->addLayout(detaillayout);
	m_mainlayout->setAlignment(Qt::AlignTop);
	this->setLayout(m_mainlayout.get());
	this->setStyleSheet("background-color:white;border-radius:5;");
}
TemplateMessageItem::~TemplateMessageItem(){

}
void TemplateMessageItem::onclicked(){
#ifdef _WIN32
	//emit openUrl(m_detailurl.toStdString());
	//QDesktopServices::openUrl(QUrl::fromLocalFile(m_detailurl));
	mWebview.setUrl(QUrl(m_detailurl));
	mWebview.show();
#else
	QDesktopServices::openUrl(QUrl("file:///" + m_detailurl, QUrl::TolerantMode));
#endif 
}
void TemplateMessageItem::setTemplateMsg(CSharedPtr<data::Msg>&msg){
	data::MsgMasterplate* msgTemplate = CNull;
	if(CNull == msg)return;
	msgTemplate = (data::MsgMasterplate* )(msg.get());

	QString titlestyle = QString("background-color:%1;border-radius:5;").arg(QString::fromStdString(msgTemplate->titleBGColor.c_str()));
	m_tiltlewidget->setStyleSheet(titlestyle);
	m_tiltle->setText(QString::fromUtf8(msgTemplate->title.c_str()));
	m_tiltle->setTextColor(QColor(QString::fromUtf8(msgTemplate->titleColor.c_str())));
	m_content->setText(QString::fromUtf8(msgTemplate->content.c_str()));
	QSize size = ContentSize();
	m_content->setFixedHeight(size.height());
	m_detailurl = QString::fromUtf8(msgTemplate->detailUrl.c_str());
	AddFields(msgTemplate->fields);
	int hei = this->sizeHint().height();
	this->setFixedHeight(hei);
}
QSize TemplateMessageItem::ContentSize()
{
	QSize sz;
	int hei =0;
	int wid = 0;
	int textSpace = m_content->width();
	bool bret = TextUtils::singleLine(textSpace,m_content->toPlainText(), m_content->fontMetrics());
	QSize txtSz = TextUtils::textSize(textSpace, m_content->toPlainText(), m_content->fontMetrics());
	if (bret)
	{
		hei =m_content->fontMetrics().height();
		wid = txtSz.width();
	}
	else{
		hei = txtSz.height();
		wid = txtSz.width();
	}
	sz = QSize(wid,hei);
	return sz;
}
int TemplateMessageItem::AddFields(std::map<std::string,std::string> fields){
	int height = 0;
	TemplateRepeatItem* itemdelegate=CNull;
	QListWidgetItem* item=CNull;
	std::map<std::string,std::string>::iterator itr;
	for ( itr = fields.begin();itr!=fields.end(); ++itr)
	{
		itemdelegate = new TemplateRepeatItem(QString::fromUtf8(itr->first.c_str()),QString::fromUtf8(itr->second.c_str()),m_fields.get());
		item = new QListWidgetItem();
		item->setBackgroundColor(QColor(Qt::white));
		item->setFlags(Qt::NoItemFlags);
		item->setSizeHint(QSize(280,30));
		height+=item->sizeHint().height();
		int row = m_fields->count();
		m_fields->insertItem(row,item);
		m_fields->setItemWidget(item,itemdelegate);
		QCoreApplication::processEvents();
	}
	m_fields->setSpacing(0);
	m_fields->setFixedSize(280,height);
	m_mainlayout->addStretch();
	return height;
}
class TemplateMessageWidgetPrivate
{
public:
	void init();
	QSize sizeHint() const;
	TemplateMessageWidget* q_ptr;
	TemplateMessageItem*   templateMessageItem;
};
void TemplateMessageWidgetPrivate::init(){
	templateMessageItem = new TemplateMessageItem(q_ptr);
	q_ptr->setCentralWidget(templateMessageItem);
}
QSize TemplateMessageWidgetPrivate::sizeHint()const{
	QSize size;
	size = templateMessageItem->sizeHint();
	return size;
}


TemplateMessageWidget::TemplateMessageWidget(QWidget* parent):AbstractMessageWidget(parent){
	d_ptr = new TemplateMessageWidgetPrivate;
	d_ptr->q_ptr = this;
	d_ptr->init();
}
TemplateMessageWidget::~TemplateMessageWidget(){

}
void TemplateMessageWidget::setTemplate(CSharedPtr<data::Msg>&msg){
	d_ptr->templateMessageItem->setTemplateMsg(msg);
}
QSize TemplateMessageWidget::suggestWidth(int width){
	Q_UNUSED(width);
	QSize size = d_ptr->sizeHint()+QSize(58,18);
	return size;
}