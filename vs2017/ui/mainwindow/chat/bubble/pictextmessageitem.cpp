#include "pictextmessageitem.h"
#include "detail/clicklabel.h"
#include "data/ChatData.h"
#include "common/Common.h"
#include "common/UIUtils.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QFile>
#include <QUrl>
#include <QApplication>
#include "../../workbench/AppWebView.h"
extern ui::AppWebView gAppWebView;
PicTextDelegate::PicTextDelegate(DelegateType type,data::MsgPicWithText::picTextBean*msg,IChatMgrControl_Ptr& chatcontrol,qint64 targetId,QWidget *parent):ui::TWidget(parent),m_tiltle(CNull),m_image(CNull),
m_chatcontrol(chatcontrol),m_targetid(targetId),m_desc(CNull),m_readall(CNull),m_url(""),m_sigletitlelayout(CNull),m_multicontentlayout(CNull)
{
	switch(type){
	case DELEGATE_SIGLETITLEMSG:
		{
			CreateSigleTitleItem(msg);
			break;
		}
	case DELEGATE_TITLE_MULTIMSG:
		{
			CreateMultiTitleItem(msg);
			break;				 
		}
	case DELEGATE_MULTIMSG:
		{
			CreateMultiContentItem(msg);
			break;
		}
	default:
		{
			break;
		}
	}
	CONNECT_SERVICE(DownLoadImg(int,const std::string&,int64));
}
PicTextDelegate::~PicTextDelegate(){

}

void PicTextDelegate::CreateSigleTitleItem(data::MsgPicWithText::picTextBean*msg){
	 if (CNull == msg) return;

	  m_tiltle = CMakePtr<QLabel>(this);
	  m_image  = CMakePtr<QLabel>(this);
	  m_desc   = CMakePtr<QLabel>(this);
	  m_readall = CMakePtr<ClickLabel>(this);
	  m_image->setFixedSize(390,230);
	  m_image->setScaledContents(true);
	  m_sigletitlelayout = new QVBoxLayout(this);
	  m_sigletitlelayout->addWidget(m_tiltle.get());
	  m_sigletitlelayout->addWidget(m_image.get());
	  m_sigletitlelayout->addWidget(m_desc.get());
	  m_sigletitlelayout->addWidget(m_readall.get());
	  m_sigletitlelayout->setSpacing(3);
	  m_sigletitlelayout->setContentsMargins(5,5,5,5);
	  m_sigletitlelayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
	  this->setLayout(m_sigletitlelayout);

	  m_tiltle->setText(QString::fromUtf8(msg->title.c_str()));
	  m_image->setPixmap(QPixmap(DEFAULT_PICTURE));
	  m_desc->setPixmap(QString::fromUtf8(msg->dsc.c_str()));
	  m_url = QString::fromUtf8(msg->url.c_str());
	  m_readall->setText(transfer("ÔÄ¶ÁÈ«ÎÄ"));
	  downLoadImg(msg->picUrl);
}
void  PicTextDelegate::CreateMultiTitleItem(data::MsgPicWithText::picTextBean*msg){
	m_image  = CMakePtr<QLabel>(this);
	m_tiltle = CMakePtr<QLabel>(this);

	m_image->setFixedSize(390,230);
	m_image->setScaledContents(true);
	m_sigletitlelayout = new QVBoxLayout(this);
	m_sigletitlelayout->addWidget(m_image.get());
	m_sigletitlelayout->addWidget(m_tiltle.get());
	m_sigletitlelayout->setSpacing(3);
	m_sigletitlelayout->setContentsMargins(5,5,5,5);
	m_sigletitlelayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
	this->setLayout(m_sigletitlelayout);
	this->setObjectName("picText");
	m_tiltle->setText(QString::fromUtf8(msg->title.c_str()));
	m_image->setPixmap(QPixmap(DEFAULT_PICTURE));
	m_url = QString::fromUtf8(msg->url.c_str());
	downLoadImg(msg->picUrl);
}
void  PicTextDelegate::CreateMultiContentItem(data::MsgPicWithText::picTextBean*msg){
	m_tiltle = CMakePtr<QLabel>(this);
	m_image  = CMakePtr<QLabel>(this);

	m_image->setFixedSize(50,50);
	m_image->setScaledContents(true);
	m_multicontentlayout = new QHBoxLayout(this);
	m_multicontentlayout->addWidget(m_tiltle.get());
	m_multicontentlayout->addStretch();
	m_multicontentlayout->addWidget(m_image.get());
	m_multicontentlayout->setSpacing(3);
	m_multicontentlayout->setContentsMargins(5,5,5,5);
	this->setObjectName("picText");
	this->setLayout(m_multicontentlayout);

	m_tiltle->setText(QString::fromUtf8(msg->title.c_str()));
	m_image->setPixmap(QPixmap(DEFAULT_PICTURE));
	m_url = QString::fromUtf8(msg->url.c_str());
	downLoadImg(msg->picUrl);
}
void  PicTextDelegate::downLoadImg(std::string&url){
	QString path = UIUtils::GetDataFullPath(DATAPATH_USERIMG)+UIUtils::GetPicNameByUrl(QString::fromStdString(url));
	if ( UIUtils::IsFileExist(path))
	{
		m_image->setPixmap(path);
	}
	else{
		m_chatcontrol->DownLoadImage(
			m_targetid,
			url,
			CBind(&PicTextDelegate::signalSerDownLoadImg,
			this,
			CPlaceholders  _1,
			CPlaceholders  _2,
			CPlaceholders  _3));
	}
}
void PicTextDelegate::onSerDownLoadImg(int err,const std::string& imgname,int64 targetid){
	if ( !err && CNull != m_image)
	{
		QString path = UIUtils::GetDataFullPath(DATAPATH_USERIMG)+QString::fromStdString(imgname);
		QString destpath = UIUtils::GetDataFullPath(DATAPATH_USERIMG)+UIUtils::GetNameByUrl(QString::fromStdString(imgname));
		QFile::copy(path,destpath);
		QFile::remove(path);
		m_image->setPixmap(destpath);
	}
}
void PicTextDelegate::enterEvent(QEvent* event)
{
	Q_UNUSED(event)
	setCursor(Qt::PointingHandCursor);
}

void PicTextDelegate::leaveEvent(QEvent* event)
{
	Q_UNUSED(event)
	qApp->restoreOverrideCursor();
}

void PicTextDelegate::ReadAll(){
#ifdef _WIN32

	//gAppWebView.setUrl(QUrl(m_url));
	//gAppWebView.show();
	//QDesktopServices::openUrl(QUrl::fromLocalFile(m_url));
	emit openUrl(m_url.toStdString());
#else
	QDesktopServices::openUrl(QUrl("file:///" + path, QUrl::TolerantMode));
#endif 
}
PicTextMessageItem::PicTextMessageItem(IChatMgrControl_Ptr&chatcontrol,qint64 targetId,QWidget *parent):ui::TWidget(parent),m_listWidget(CNull),
m_chatcontrol(chatcontrol),m_targetid(targetId)
{
	m_listWidget = CMakePtr<QListWidget>(this);
	m_listWidget->setStyleSheet("background-color:transparent;");
	connect(m_listWidget.get(),SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onItemClicked(QListWidgetItem*)));
}
PicTextMessageItem::~PicTextMessageItem(){

}
void PicTextMessageItem::InsertItem(CSharedPtr<data::Msg>&msg){
	QListWidgetItem* item =CNull;
    PicTextDelegate* itemdelegate=CNull;
	data::MsgPicWithText* dataPicTxt = CNull;
	int count = 0;
	int height = 0;
	if (CNull == msg) return;
	dataPicTxt = (data::MsgPicWithText* )(msg.get());
	count = dataPicTxt->vtPtBean.size();
	for (size_t index=0; index<count; ++index)
	{
		item =  new QListWidgetItem();
		if (1==count && index==0)
		{
			item->setSizeHint(QSize(400,280));
			itemdelegate = new PicTextDelegate(PicTextDelegate::DELEGATE_SIGLETITLEMSG,&dataPicTxt->vtPtBean.at(index),m_chatcontrol,m_targetid,m_listWidget.get());
		}
		else if(count>1 && index==0){
			item->setSizeHint(QSize(400,270));
			itemdelegate = new PicTextDelegate(PicTextDelegate::DELEGATE_TITLE_MULTIMSG,&dataPicTxt->vtPtBean.at(index),m_chatcontrol,m_targetid,m_listWidget.get());
		}
		else{
			item->setSizeHint(QSize(400,70));
			itemdelegate = new PicTextDelegate(PicTextDelegate::DELEGATE_MULTIMSG,&dataPicTxt->vtPtBean.at(index),m_chatcontrol,m_targetid,m_listWidget.get());
		}
		connect(itemdelegate,SIGNAL(openUrl(std::string)),this,SIGNAL(openUrl(std::string)));
		height+=item->sizeHint().height();
		int row =m_listWidget->count();
		m_listWidget->insertItem(row,item);
		m_listWidget->setItemWidget(item,itemdelegate);
		QCoreApplication::processEvents();
	}
	m_listWidget->setFixedSize(QSize(400,height));
	this->setFixedSize(QSize(400,height)+QSize(10,15));
}
QSize PicTextMessageItem::sizeHint() const{
	QSize size = this->size();
	return size;
}
void PicTextMessageItem::onItemClicked( QListWidgetItem*item )
{
	PicTextDelegate* widget = CNull;
	if (CNull == item || CNull == m_listWidget)return;
	widget = (PicTextDelegate*)m_listWidget->itemWidget(item);
	if(widget){
		widget->ReadAll();
	}
}