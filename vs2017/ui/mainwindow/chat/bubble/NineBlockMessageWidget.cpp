#include "NineBlockMessageWidget.h"
#include "common/UIUtils.h"
#include "../../imageBrowser/ImageBrowser.h"
#include <QFile>
#include <QDateTime>
NineBlockMessageWidget::NineBlockMessageWidget(QWidget *parent)
	: AbstractMessageWidget(parent)
{
	mMainLayout = new QGridLayout(this);
	QWidget* widget = new QWidget(this);
	widget->setLayout(mMainLayout);
	setCentralWidget(widget);
	this->setMouseTracking(true);
	this->setToolTip(transfer("Ë«»÷²é¿´Ô­Í¼"));
}

NineBlockMessageWidget::~NineBlockMessageWidget()
{

}

void NineBlockMessageWidget::setNineBlockMsg( CSharedPtr<data::Msg>&msg )
{
	AbstractMessageWidget::setMsg(msg);
	if (msg->isRecvMsg)
	{
		this->setStyleSheet("background-color:rgb(238,238,238)");
	}else{
		this->setStyleSheet("background-color:rgb(19,52,83)");
	}
	if (msg->msgType == data::MSG_TYPE_NINEBLOCK)
	{
		data::MsgNineBlock* nineMsg = (data::MsgNineBlock*)msg.get();
		if (nineMsg)
		{
			int row=1,col=1;
			int count = nineMsg->nine.size();

			if (count<=2)
			{
				row = 1;
				col =2;
			}else if(count<=4){
				row = 2;
				col =2;
			}else if(count<=6){
				row = 2;
				col =3;
			}else{
				row = 3;
				col =3;
			}
			this->setFixedSize(NINE_IMG_ITEM_SIZE*col,NINE_IMG_ITEM_SIZE*row);
			mSize = QSize(NINE_IMG_ITEM_SIZE*col,NINE_IMG_ITEM_SIZE*row);
			for (int i=0,index=0;i<row;++i)
			{
				for (int j=0;j<col;++j)
				{
					NineBlockMessageItem*widget = new NineBlockMessageItem(m_chatcontrol,nineMsg->targetId,this);
					if (index<count)
					{
						widget->setNineBlockMsg(nineMsg->nine.at(index));
						mItems.push_back(widget);
						index++;
					}
					mMainLayout->addWidget(widget,i,j,1,1);
				}
			}
		}
	}
}

QSize NineBlockMessageWidget::suggestWidth( int width )
{
	return mSize;
}

void NineBlockMessageWidget::mouseDoubleClickEvent( QMouseEvent* event )
{
    if (mItems.size() == 0)
    {
		return;
    }
	QList<QString>imgs;
	for (int i=0;i<mItems.size();++i)
	{
		NineBlockMessageItem* widget = (NineBlockMessageItem*)mItems.at(i);
		imgs.push_back(widget->bigImgPath);
	}
	ui::ImageBrowser::Instance()->setImgs(imgs,0);
	ui::ImageBrowser::Instance()->showWin();
}

NineBlockMessageItem::NineBlockMessageItem(IChatMgrControl_Ptr ctrl,int64 targetId, QWidget *parent/*=0*/ )
{
	mlblImage = new QLabel(this);
	mlblImage->setFixedSize(NINE_IMG_ITEM_SIZE,NINE_IMG_ITEM_SIZE);
	m_chatcontrol = ctrl;
	mTargetId = targetId;
	CONNECT_SERVICE(DownLoadImg(int,const std::string&,int64,int64,const std::string&,bool));
}

NineBlockMessageItem::~NineBlockMessageItem()
{

}

void NineBlockMessageItem::setNineBlockMsg( data::MsgImg&msgImg )
{
	QString temp(DEFAULT_PICTURE);
	m_media.mainurl = QString::fromUtf8(msgImg.mainUrl.c_str());
	m_media.url= QString::fromUtf8(msgImg.thumbUrl.c_str());
	m_media.binary = QByteArray::fromBase64(msgImg.thumBbinary.c_str());
	m_media.encrptkey = QString::fromUtf8(msgImg.encryptKey.c_str());
	if(!AbstractMessageWidget::isFileExist(m_media.url,DATACACHEPATH_USERIMG)){
		downLoadImg(m_media.url.toStdString(),false);
	}
	else{
		temp = m_media.url;
		bigImgPath = temp;
	}
	QImage img(temp);
	img = img.scaled(NINE_IMG_ITEM_SIZE,NINE_IMG_ITEM_SIZE);
	mlblImage->setPixmap(QPixmap::fromImage(img));
}

void  NineBlockMessageItem::downLoadImg(std::string&url,bool isSrc){
	QString path = UIUtils::GetDataFullPath(DATAPATH_USERIMG)+QString::fromUtf8(url.data());
	if ( UIUtils::IsFileExist(path))
	{
		QString destPath = enctrptFile(url,m_media.encrptkey.toStdString());
		QImage img(destPath);
		img = img.scaled(NINE_IMG_ITEM_SIZE,NINE_IMG_ITEM_SIZE);
		mlblImage->setPixmap(QPixmap::fromImage(img));
	}
	else{
		m_chatcontrol->DownLoadImage(
			mTargetId,
			url,
			CBind(&NineBlockMessageItem::signalSerDownLoadImg,
			this,
			CPlaceholders  _1,
			CPlaceholders  _2,
			CPlaceholders  _3,
			QDateTime::currentMSecsSinceEpoch(),
			m_media.encrptkey.toStdString(),
			isSrc));
	}
}
QString NineBlockMessageItem::enctrptFile(std::string&url,std::string&encrptkey,FileDefaultPathType filepath,FileCachePathType cacheType){

	QString path = UIUtils::GetDataFullPath(filepath)+QString::fromUtf8(url.data());
	QString destPath = UIUtils::GetDataFullPath(cacheType)+UIUtils::GetNameByUrl(QString::fromUtf8(url.data()));
	if ( UIUtils::IsFileExist(path) && !encrptkey.empty())
	{
		bool bret = m_chatcontrol->decryptFile(encrptkey,path.toUtf8().data(),destPath.toUtf8().data());
		if ( !bret)
		{
			destPath="";
		}
	}
	else{
		QFile file(path);
		file.copy(destPath);
	}
	return destPath;
}

void NineBlockMessageItem::onSerDownLoadImg(int err,const std::string& imgname,int64 targetid,int64 localid,const std::string& encrptykey,bool isSrc){
	if ( !err)
	{
		std::string url = imgname;
		std::string key = encrptykey;
		QString destPath = enctrptFile(url,key);
		QImage img(destPath);
		img = img.scaled(NINE_IMG_ITEM_SIZE,NINE_IMG_ITEM_SIZE);
		mlblImage->setPixmap(QPixmap::fromImage(img));
		bigImgPath = destPath;
	}
}