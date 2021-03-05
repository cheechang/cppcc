#include "webmessagewidget.h"
#include <QLabel>
#include <QTextEdit>
#include <QGridLayout>
#include <QDesktopServices>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QNetworkReply>
#include "../controls/ElidedLabel.h"
#include "data/ChatData.h"
#include "./detail/clicklabel.h"
#include "common/Connect.h"

WebMessageWidget::WebMessageWidget(QWidget *parent)
	: AbstractMessageWidget(parent)
{
	init();
}

WebMessageWidget::~WebMessageWidget()
{

}

void WebMessageWidget::setWebMsg( CSharedPtr<data::Msg>&msg )
{
	data::MsgWeb* webMsg = (data::MsgWeb*)(msg.get());
	if (webMsg != CNull){
	
		AbstractMessageWidget::setMsg(msg);
		mWebUrl->setText(webMsg->url.c_str());
		mWebUrl->setToolTip(mWebUrl->text());
		mWebTilte->setText(QString::fromUtf8(webMsg->title.c_str()));
		mWebTilte->setToolTip(QString::fromUtf8(webMsg->title.c_str()));
		mWebContent->setText(QString::fromUtf8(webMsg->desc.c_str()));
		mWebContent->setToolTip(QString::fromUtf8(webMsg->desc.c_str()));
		//mWebContent->setEnabled(false);
		QString imgPath = ":/chat/webLinkDefault";
		if (!webMsg->img.empty())
		{
				imgPath = webMsg->img.c_str();
				QUrl url(imgPath);  
				QNetworkAccessManager manager;  
				QEventLoop loop;  
				QNetworkReply *reply = manager.get(QNetworkRequest(url));   
				connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));  
				loop.exec();  
				QByteArray jpegData = reply->readAll();  
				QPixmap pixmap;  
				pixmap.loadFromData(jpegData);    
				mWebIcon->setPixmap(pixmap);  
				mWebIcon->setScaledContents(true); 
		}else{
			mWebIcon->setPixmap(QPixmap(imgPath));
		}
		mStrWebUrl = webMsg->url;
	}
}

QSize WebMessageWidget::suggestWidth(int width)
{
	Q_UNUSED(width);
	return QSize(300,140);
}

void WebMessageWidget::init()
{
	mWebUrl = CMakePtr<ElidedLabel>(this);
	mWebTilte = CMakePtr<ElidedLabel>(this);
	mWebIcon = CMakePtr<QLabel>(this);
	mWebContent = CMakePtr<QTextEdit>(this);
	mHorLine = CMakePtr<QLabel>(this);
	mBtnOpen = CMakePtr<ClickLabel>(this);
	connect(mWebUrl.get(),SIGNAL(clicked()),this,SLOT(onOpenUrl()));
	connect(mBtnOpen.get(),SIGNAL(clicked()),this,SLOT(onOpenUrl()));

	mWebUrl->setFixedSize(260,20);
	mWebUrl->setTextColor(QColor(35, 155, 219));
	QFont underLineFont;
	underLineFont.setUnderline(true);
	mWebUrl->setFont(underLineFont);

	QFont font;
	font.setBold(true);
	mWebTilte->setFont(font);
	mWebTilte->setFixedSize(210,18);

	mWebIcon->setFixedSize(60,60);

	mWebContent->setFixedSize(210,40);
	mWebContent->setReadOnly(true);

	mBtnOpen->setFixedSize(30,30);
	mBtnOpen->setText(transfer("´ò¿ª"));
	mBtnOpen->setTextColor(QColor(35, 155, 219));
	mBtnOpen->setUnderlined(true);
	
	mHorLine->setFixedSize(280,1);
	mHorLine->setStyleSheet("background-color:gray;");

	mainLayout = CMakePtr<QGridLayout>(this);
	mainLayout->setContentsMargins(2,0,0,0);
	mainLayout->setSpacing(2);
	mainLayout->addWidget(mWebUrl.get(),0,0,1,2);
	mainLayout->addWidget(mWebIcon.get(),1,0,2,1);
	mainLayout->addWidget(mWebTilte.get(),1,1,1,1);
	mainLayout->addWidget(mWebContent.get(),2,1,1,1);
	mainLayout->addWidget(mHorLine.get(),3,0,1,2);
	mainLayout->addWidget(mBtnOpen.get(),4,0,1,2,Qt::AlignRight);
	
	QWidget* widget = new QWidget(this);
	widget->setLayout(mainLayout.get());
	widget->setFixedSize(280,120);
	widget->setStyleSheet("background-color:white;border-radius:3;");
	__super::setCentralWidget(widget);
    setFixedSize(300,130);
}

void WebMessageWidget::onOpenUrl()
{
	QDesktopServices::openUrl(QUrl(mStrWebUrl.c_str()));
}

