#include "imagemessagewidget.h"
#include "MyRightMenu.h"
#include <QMovie>
#include <QFileInfo>
#include <QLabel>
#include <QUrl>
#include <QDebug>
#include <QDateTime>
#include <QUuid>
#include <QDir>
#include <QTimer>
#include <QApplication>
#include <log/log.h>
#include <QPainter>
#include <QBuffer>
#include <QDesktopServices>
#include <QToolTip>
#include <QApplication>
#include <QClipboard>

#include <common/Common.h>
#include <common/Controlptr.h>
#include <common/UIUtils.h>
#include <common/ChineseInfos.hpp>
#include <mainwindow/imageBrowser/ImageBrowser.h>
#include <controls/CircleProgressBar.h>
#include <controls/ElidedLabel.h>
#include "flexaction.h"

ImageMessageWidget::ImageMessageWidget(QWidget* parent) : TextMessageWidget(parent),
m_image(""), mWidth(0), mHeight(0), m_contextImgs(CNull)
{
	this->setMouseTracking(true);
	this->setStyleSheet("background-color:rgb(238,238,238)");
	this->setToolTip(transfer("双击查看原图"));
	label()->setScaledContents(true);
	m_progressBar = new uicontrols::CircleProgressBar(this);
	m_progressBar->setFixedSize(40*gDdpi,40*gDdpi);
	m_progressBar->setValue(0);
	m_progressBar->hide();

	CONNECT_SERVICE(DownLoadImg(int,const std::string&,int64,int64,const std::string&,bool));
	CONNECT_SERVICE(GetImgMsgs(int, std::map<int64,data::MsgImg>));
	CONNECT_SERVICE(ProgressCb( int32, int32, const std::string&,int64));
	connect(this,SIGNAL(signalSerSendMsgCb(int32,int32,const std::string&,int64)),this, SLOT(onSerProgressCb(int32, int32, const std::string&,int64)),Qt::QueuedConnection);
}
void ImageMessageWidget::setImage(MsgDataPtr&msg)
{
	m_localId = uiLocalId();
	//图片发送
	if (!msg->isRecvMsg && !msg->isDeviceMsg && !msg->msgId)
	{
		dealSendMsg(msg);
	}
	else
	{
		dealHistoryMsg(msg);
	}
	if (!msg->isRecvMsg&&msg->isBurn)
	{
		mRightMenu.setMenuState(MENU_RECALL, false);
		mRightMenu.setMenuState(MENU_TRANSPORT, false);
		mRightMenu.setMenuState(MENU_COPY, false);
	}/*else{
		mRightMenu.setMenuState(MENU_COPY, true);
	}*/
	//mRightMenu.setMenuState(MENU_RECALLEDIT, false);
	//connect(&mRightMenu, SIGNAL(signalCtrlCopyMenu(int64, int64)), this, SLOT(onCopyMsg()));
	AbstractMessageWidget::setMsg(msg);
}

void ImageMessageWidget::dealImgRecv(MsgDataPtr&msg){
	QString temp(DEFAULT_PICTURE);
	data::MsgImg* msgImg = dynamic_cast<data::MsgImg*>(msg.get());
	if (CNull == msgImg) return;

	m_media.mainurl = QString::fromUtf8(msgImg->mainUrl.c_str());
	m_media.url= QString::fromUtf8(msgImg->thumbUrl.c_str());
	m_media.binary = QByteArray::fromBase64(msgImg->thumBbinary.c_str());
	m_media.encrptkey = QString::fromUtf8(msgImg->encryptKey.c_str());

	if (!m_media.binary.isEmpty())
	{
		QString filePath = QString::fromUtf8(USERIMGPATH)+"tempFile/";
		QString fileName = QUuid::createUuid().toString()+".jpg";
		QPixmap temppix;
		bool bret = false;
		QDir tempDir;

		if (!tempDir.exists(filePath))
		{
			tempDir.mkdir(filePath);
		}
		filePath+=fileName;
		bret = temppix.loadFromData(m_media.binary,"JPEG");
		bret = temppix.save(filePath,"JPEG", 99);
		if (bret)
		{
			temp = filePath;
		}
	}
	if(!isFileExist(m_media.mainurl,DATACACHEPATH_USERIMG)){
		std::string url = m_media.mainurl.toStdString();
		downLoadImg(url,false);
	}
	else{
		temp = m_media.mainurl;
	}
	setPixImage(temp);
}
void ImageMessageWidget::setPixImage(QString& path){
	if ( m_image != path)
	{
		m_image = path;
		QPixmap pixmap=loadImgByFormat(m_image);
		if(pixmap.isNull()){
			pixmap.load(":/chat/pic");
		}
		QSize imgSize = calculateImgSize(mWidth,mHeight);
		pixmap = pixmap.scaled(imgSize, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
		label()->setPixmap(pixmap);
		resize(pixmap.size());
		emit sizechanged();
	}
}

QString ImageMessageWidget::image() const
{
    return m_image;
}
QSize ImageMessageWidget::suggestWidth(int width)
{
	QPixmap pixmap = loadImgByFormat(m_image);
	if(pixmap.isNull()){
		pixmap.load(":/chat/pic");
	}
	QSize imgSize = calculateImgSize(mWidth,mHeight);
	pixmap = pixmap.scaled(imgSize, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
	label()->setPixmap(pixmap);
	QSize sz = pixmap.size()+QSize(40*gDdpi,10*gDdpi);
	resize(pixmap.size());
	return sz;
}

void ImageMessageWidget::setStatus(const qint32&val)
{
	TextMessageWidget::setStatus(val);
	if(val == MSG_FINISH || MSG_FAILED == val){
		m_progressBar->hide();
	}
}

void ImageMessageWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	if(!m_progressBar->isVisible()){
		viewImg(m_image);
	}
}

void ImageMessageWidget::initializeContextActions()
{
	AbstractMessageWidget::initializeContextActions();
}
void ImageMessageWidget::enterEvent(QEvent* event)
{
	Q_UNUSED(event)
	setCursor(Qt::PointingHandCursor);
}

void ImageMessageWidget::leaveEvent(QEvent* event)
{
	Q_UNUSED(event)
	qApp->restoreOverrideCursor();
}
void ImageMessageWidget::scaledImage(QString sourceImagePath, float scaledWidth, float scaledHeight, QPixmap &outPixmap)
{
	QSize sourceSize;
	int sourceWidth = 0;
	int sourceHeight = 0;
	int resultWidth = 0;
	int resultHeight = 0;
	float scaledNum = 0;      //缩放比例

#ifndef  _WIN32
	sourceImagePath = "/" + sourceImagePath;
#endif

	QPixmap sourceImage = loadImgByFormat(sourceImagePath);

	sourceSize = sourceImage.size();
	sourceWidth = sourceSize.width();
	sourceHeight = sourceSize.height();

	if (sourceWidth >= scaledWidth && sourceHeight >= scaledHeight)
	{
		if (sourceWidth >= sourceHeight)
		{
			scaledNum = scaledWidth / sourceWidth;
			resultWidth = scaledWidth;
			resultHeight = scaledNum*sourceHeight;
		}
		else
		{
			scaledNum = scaledHeight / sourceHeight;
			resultHeight = scaledHeight;
			resultWidth = scaledNum*sourceWidth;
		}
	}
	else if (sourceWidth >= scaledWidth && sourceHeight <= scaledHeight)
	{
		scaledNum = scaledWidth / sourceWidth;
		resultWidth = scaledWidth;
		resultHeight = scaledNum*sourceHeight;
	}
	else if (sourceWidth <= scaledWidth && sourceHeight >= scaledHeight)
	{
		scaledNum = scaledHeight / sourceHeight;
		resultHeight = scaledHeight;
		resultWidth = scaledNum*sourceWidth;
	}
	else
	{
		resultWidth = sourceWidth;
		resultHeight = sourceHeight;
	}	

	if ( resultWidth <MinWidthOrHeight)
	{
		resultWidth = MinWidthOrHeight;
	}
	if (resultHeight < MinWidthOrHeight)
	{
		resultHeight = MinWidthOrHeight;
	}
	
	outPixmap = sourceImage.scaled(QSize(resultWidth, resultHeight), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}

QSize ImageMessageWidget::calculateImgSize(int imgWidth,int imgHeight,int containerWidth,int containerHeight)
{
	int width=0, height=0;
	if(imgWidth && imgHeight){
		if (imgWidth < containerWidth && imgHeight < containerHeight) {  
			width = imgWidth;
			height =  imgHeight;
		} else { //原图片宽高比例 大于 图片框宽高比例,则以框的宽为标准缩放，反之以框的高为标准缩放  
			if ((1.0*containerWidth / containerHeight)  <= (1.0*imgWidth / imgHeight)) { //原图片宽高比例 大于 图片框宽高比例  
				width = containerWidth; //以框的宽度为标准  
				height = containerWidth * (1.0*imgHeight/imgWidth);
			}else{//原图片宽高比例 小于 图片框宽高比例  
				width = containerHeight * (1.0*imgWidth / imgHeight);
				height = containerHeight;  //以框的高度为标准  
			}  
		}
	}else{ // 当消息中不存在宽高的时候
		width = containerWidth;
		height = containerHeight; 
	}
	if ( width <MinWidthOrHeight)
	{
		width = MinWidthOrHeight;
	}
	if (height < MinWidthOrHeight)
	{
		height = MinWidthOrHeight;
	}
	return QSize(width,height);
}

QPixmap ImageMessageWidget::loadImgByFormat(QString sourceImagePath)
{
	QPixmap sourceImage(sourceImagePath);
	bool ret = sourceImage.isNull();
	if(sourceImage.isNull()){
		ret = sourceImage.load(sourceImagePath,"png");
	}
	if(!ret){
		ret = sourceImage.load(sourceImagePath,"jpg");
	}
	if(!ret){
		ret = sourceImage.load(sourceImagePath,"jpeg");
	}
	if(!ret){
		ret = sourceImage.load(sourceImagePath,"mng");
	}
	return sourceImage;
}

void ImageMessageWidget::dealSendMsg(MsgDataPtr&msg){
	QString path("");
	QByteArray byteData;
	QString thumbpath("");
	QSize thumbsize;

	if (CNull == msg) return;
	data::MsgImg* msgImg = dynamic_cast<data::MsgImg*>(msg.get());
	path = QString::fromUtf8(msgImg->mainPath.c_str());

	scaledImage(path, THUMP_PIC_WIDTH, THUMP_PIC_HEIGHT,thumbpath);
	thumbsize = getImageThumpSize(thumbpath);
	getImgBinaryData(byteData, thumbpath,thumbsize);
	mWidth = msgImg->width = thumbsize.width();
	mHeight = msgImg->height = thumbsize.height();
	msgImg->fileName = QFileInfo(thumbpath).fileName().toUtf8().data();
	msgImg->thumBbinary = QString(byteData).toUtf8().data();
	msgImg->thumbPath =thumbpath.toUtf8().data();
	msgImg->mainPath = path.toUtf8().data();
	setMsg(msg);
	setPixImage(path);
}
void ImageMessageWidget::dealHistoryMsg(MsgDataPtr&msg){
	data::MsgImg* msgImg = dynamic_cast<data::MsgImg*>(msg.get());
	if ( CNull == msgImg) return;

	mWidth = msgImg->width;
	mHeight = msgImg->height;
	//接收图片或者设备消息
	if (msg->isRecvMsg || msg->isDeviceMsg ||msgImg->mainPath.empty())
	{
		dealImgRecv(msg);
	}
	//发送的
	else{
		QString localPath = QString::fromUtf8(msgImg->mainPath.c_str());
		localPath = UIUtils::IsFileExist(localPath)?localPath:DEFAULT_PICTURE;
		setPixImage(localPath);
	}
	if (!msgImg->imageContents.empty()){
		m_contextImgs = new ElidedLabel(label());
		m_contextImgs->setTextColor(Qt::black);
		m_contextImgs->move(10,220);
		m_contextImgs->setFixedWidth(120);
		//m_contextImgs->setStyleSheet("QLabel{background:transaprent;}");
		m_contextImgs->setText(QString::fromUtf8(msgImg->imageContents.c_str()));
	}
}
QSize ImageMessageWidget::getImageThumpSize(QString filePath)
{
	//计算图片实际缩略图大小
	QString strThumbPath("");
	QPixmap TempThumbPixmap;
	bool	bRet = false;

#ifndef  _WIN32
	filePath = "/" + filePath;
#endif
	strThumbPath = filePath;
	bRet = TempThumbPixmap.load(strThumbPath); //获取位图
	QSize sourceSize = TempThumbPixmap.size();
	if (!bRet)
	{
		Log(LOG_LEV_ERROR, LOG_FILE, "(error load Picture failed)");
	}
	/////////////////////////////////////////////////////处理缩略图显示///////////
	float scaledWidth = 260.1;
	float scaledHeight = 195.1;
	int sourceWidth = 0;
	int sourceHeight = 0;
	int resultWidth = 0;
	int resultHeight = 0;
	float scaledNum = 0;      //缩放比例
	sourceWidth = sourceSize.width();
	sourceHeight = sourceSize.height();
	if (sourceWidth >= scaledWidth && sourceHeight >= scaledHeight)
	{
		if (sourceWidth >= sourceHeight)
		{
			scaledNum = scaledWidth / sourceWidth;
			resultWidth = scaledWidth;
			resultHeight = scaledNum*sourceHeight;
		}
		else
		{
			scaledNum = scaledHeight / sourceHeight;
			resultHeight = scaledHeight;
			resultWidth = scaledNum*sourceWidth;
		}
	}
	else if (sourceWidth >= scaledWidth && sourceHeight <= scaledHeight)
	{
		scaledNum = scaledWidth / sourceWidth;
		resultWidth = scaledWidth;
		resultHeight = scaledNum*sourceHeight;
	}
	else if (sourceWidth <= scaledWidth && sourceHeight >= scaledHeight)
	{
		scaledNum = scaledHeight / sourceHeight;
		resultHeight = scaledHeight;
		resultWidth = scaledNum*sourceWidth;
	}
	else
	{
		resultWidth = sourceWidth;
		resultHeight = sourceHeight;
	}
	if ( resultWidth <10)
	{
		resultWidth = 10;
	}
	if (resultHeight < 10)
	{
		resultHeight = 10;
	}
	QSize resultSize;
	resultSize.setWidth(resultWidth);
	resultSize.setHeight(resultHeight);
	return resultSize;
}
void ImageMessageWidget::getImgBinaryData(QByteArray& imgData, const QString thumbImgPath, const QSize thumbSize)
{
	QString srcImgPath = thumbImgPath;
	QPixmap sourceImage;
	int sizeTemp = 0;
	int index = 0;
	QByteArray byteData;
	QBuffer buffer(&byteData);

	QString tempImgPath = QString::fromUtf8(USERIMGPATH);
	tempImgPath = tempImgPath + "tempFile/";
	QString fileName = "tempImageFile.jpg";
	QDir tempDir;
	if (!tempDir.exists(tempImgPath))
	{
		tempDir.mkdir(tempImgPath);
	}
	tempImgPath = tempImgPath + fileName;

	do 
	{
		byteData.clear();
		sourceImage.load(srcImgPath);

		buffer.open(QIODevice::WriteOnly);
		sourceImage.save(&buffer, "JPEG", 0);
		sizeTemp = byteData.size();
		if (sizeTemp>2500 &&  index <3)
		{
			QPixmap tempPixmap(sourceImage);
			QPixmap destinationImage400x300 = sourceImage.scaled(thumbSize);
			destinationImage400x300.save(tempImgPath, "JPEG", 0);
			srcImgPath = tempImgPath;
		}
		index++;
		Log(LOG_LEV_DEBUG,LOG_FILE,"ByteData size = %d, index= %d", sizeTemp, index);
	} while (sizeTemp > 2500 && index < 3);

	//处理成base64
	imgData = byteData.toBase64();
}
void ImageMessageWidget::scaledImage(QString sourceImagePath, float scaledWidth, float scaledHeight, QString &outImagePath)
{
	QSize sourceSize;
	int sourceWidth = 0;
	int sourceHeight = 0;
	int resultWidth = 0;
	int resultHeight = 0;
	float scaledNum = 0;      //缩放比例

#ifndef  _WIN32
	sourceImagePath = "/" + sourceImagePath;
#endif

	QPixmap sourceImage = loadImgByFormat(sourceImagePath);
	sourceSize = sourceImage.size();
	sourceWidth = sourceSize.width();
	sourceHeight = sourceSize.height();

	if (sourceWidth >= scaledWidth && sourceHeight >= scaledHeight)
	{
		if (sourceWidth >= sourceHeight)
		{
			scaledNum = scaledWidth / sourceWidth;
			resultWidth = scaledWidth;
			resultHeight = scaledNum*sourceHeight;
		}
		else
		{
			scaledNum = scaledHeight / sourceHeight;
			resultHeight = scaledHeight;
			resultWidth = scaledNum*sourceWidth;
		}
	}
	else if (sourceWidth >= scaledWidth && sourceHeight <= scaledHeight)
	{
		scaledNum = scaledWidth / sourceWidth;
		resultWidth = scaledWidth;
		resultHeight = scaledNum*sourceHeight;
	}
	else if (sourceWidth <= scaledWidth && sourceHeight >= scaledHeight)
	{
		scaledNum = scaledHeight / sourceHeight;
		resultHeight = scaledHeight;
		resultWidth = scaledNum*sourceWidth;
	}
	else
	{
		resultWidth = sourceWidth;
		resultHeight = sourceHeight;
	}	

	if ( resultWidth <10)
	{
		resultWidth = 10;
	}
	if (resultHeight < 10)
	{
		resultHeight = 10;
	}
	QPixmap destinationImage400x300 = sourceImage.scaled(QSize(resultWidth, resultHeight), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
	QFileInfo fileInfo(sourceImagePath);
	QString tempImagePath = QString::fromUtf8(USERIMGPATH) + "cache";
	QDir tempDir;
	if (!tempDir.exists(tempImagePath))
	{
		tempDir.mkdir(tempImagePath);
	}

	QString fileName = fileInfo.baseName().toLocal8Bit().toBase64();
	fileName = fileName.toLocal8Bit().toBase64();
	outImagePath = tempImagePath + "/" + fileName + "_" + QString::number(scaledWidth)
		+ "x" + QString::number(scaledHeight) + ".png";

	destinationImage400x300.save(outImagePath, "PNG", 99);
	//解决背景透明，jpg为黑色背景问题
	QImage pngImage;
	bool isRet = pngImage.load(outImagePath);
	QImage jpgImage(pngImage.size(), QImage::Format_ARGB32);
	jpgImage.fill(QColor(Qt::white).rgb());
	QPainter painter(&jpgImage);
	painter.drawImage(0, 0, pngImage);
	outImagePath = tempImagePath + "/" + fileName+ "_" + QString::number(scaledWidth)
		+ "x" + QString::number(scaledHeight) + ".jpg";
	jpgImage.save(outImagePath, "JPEG", 99);
}
void  ImageMessageWidget::downLoadImg(std::string&url,bool isSrc){
	QString path = UIUtils::GetDataFullPath(DATAPATH_USERIMG)+QString::fromUtf8(url.data());
	if ( UIUtils::IsFileExist(path))
	{
		std::string enkey = m_media.encrptkey.toStdString();
		QString destPath = enctrptFile(url,enkey);
		if (isSrc)
		{
			viewImg(destPath);	
		}
		else{
			setPixImage(destPath);
		}
	}
	else{
		m_localId = uiLocalId();
		m_progressBar->show();
		m_chatcontrol->DownLoadImage(
			this->targetId(),
			url,
			CBind(&ImageMessageWidget::signalSerDownLoadImg,
			this,
			CPlaceholders  _1,
			CPlaceholders  _2,
			CPlaceholders  _3,
			uiLocalId(),
			m_media.encrptkey.toStdString(),
			isSrc));
	}
}
QString ImageMessageWidget::enctrptFile(std::string&url,std::string&encrptkey,FileDefaultPathType filepath,FileCachePathType cacheType){

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
void ImageMessageWidget::onSerDownLoadImg(int err,const std::string& imgname,int64 targetid,int64 localid,const std::string& encrptykey,bool isSrc){
	if ( !err)
	{
		std::string url = imgname;
		std::string key = encrptykey;
		QString destPath = enctrptFile(url,key);
		if (isSrc)
		{
			viewImg(destPath);
		}
		else{
			setPixImage(destPath);
		}
	}
	if(err == 0xFF00000A){
		this->setToolTip(transfer("资源已过期"));
	}
	if(m_progressBar){
		m_progressBar->setValue(0);
		m_progressBar->hide();
	}
}

void ImageMessageWidget::onSerProgressCb(int32 extra_req, int32 process, const std::string&info,int64 localId)
{
	if(m_localId == localId){
		if(m_progressBar){
			if(!m_progressBar->isVisible()){
				m_progressBar->show();
			}
			m_progressBar->setValue(process);
			if(process == 100){
				m_progressBar->hide();
			}
		}
	}
}

void  ImageMessageWidget::viewImg(QString&path){
//#ifdef _WIN32
	QList<QString>imgs;
	imgs.push_back(path);
	QSize sz(mWidth,mHeight);
	ui::ImageBrowser::Instance()->setImgs(imgs,0);
	ui::ImageBrowser::Instance()->showWin();
	if (this->targetId()<=0)
	{
		return;
	}
	m_chatcontrol->getImgMsg(this->targetId(),CBind(&ImageMessageWidget::signalSerGetImgMsgs,this,CPlaceholders  _1,CPlaceholders  _2));
	//QDesktopServices::openUrl(QUrl::fromLocalFile(path));
//#else
//	QDesktopServices::openUrl(QUrl("file:///" + path, QUrl::TolerantMode));
//#endif 
}

void ImageMessageWidget::paintEvent(QPaintEvent *e)
{
	if(m_progressBar && m_progressBar->isVisible()){
		int x = (this->width()-m_progressBar->width())/2;
		int y = (this->height()-m_progressBar->height())/2;
		m_progressBar->move(x,y);
	}
	TextMessageWidget::paintEvent(e);
}

void ImageMessageWidget::onCopyMsg()
{
	QPixmap pix(m_image);
	if(!pix.isNull()){
		QApplication::clipboard()->setPixmap(pix);
	}
}

void ImageMessageWidget::onSerGetImgMsgs( int code, std::map<int64,data::MsgImg> msg )
{
	std::map<int64,data::MsgImg>::iterator iter = msg.begin();
	int index = 0;
	QList<QString>imgs;
	for (int i=0;iter != msg.end();++iter,++i)
	{
		int64 msgId = this->msgId();
		data::MsgImg img = iter->second;
		if (iter->first == this->msgId())
		{
			index = i;
			//if(img.mainPath.empty() ){
			//	return;
			//}
		}

		Log(LOG_LEV_INFO,LOG_FILE,"bigimages index:%d,path:%s,key:%s",i,img.mainPath.c_str(),img.encryptKey.c_str());
		if (img.mainPath.empty() && img.encryptKey.empty())
		{
			img.mainPath = img.fileName;
			std::string key("");
			QString destPath = enctrptFile(img.mainUrl,key);
			Log(LOG_LEV_INFO,LOG_FILE,"destPath:%s",destPath.toStdString().c_str());
		}

		imgs.push_back(QString::fromUtf8(img.mainPath.c_str()));
	}
	QSize sz;
	ui::ImageBrowser::Instance()->setImgs(imgs,index);
	ui::ImageBrowser::Instance()->showWin();
}
