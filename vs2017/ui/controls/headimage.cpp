#include "headimage.h"

#include "common/Common.h"
#include <QImage>
#include <QDebug>
#include <QBitmap>
#include <log.h>
#include "qlabel.h"
#include "qboxlayout.h"
namespace ui{
HeadImage::HeadImage(QWidget *parent, const QSize& avatarSize, bool hasHoverBorder)
: QWidget(parent), mImgFullPath(""), m_hasHoverBorder(hasHoverBorder), m_isClicked(false)
{
    mIsMouseOver = mIsMousePressed = false;
    mAvatarSize = avatarSize;

	////QVBoxLayout *vl = new QVBoxLayout();

	mOriginalImage.load(":/login/login_head");//DEFAULT_AVATAR);
    mMask.load(":/contact/mask_max.png");

    setFixedSize(avatarSize);
	mIsShowGray = false;
	this->setMouseTracking(true);

 
	////nameInfo = new QLabel(this);
 	
}
 
void HeadImage::setMouseInStyle(bool isTrue)
{
	if (isTrue){
		this->setCursor(Qt::PointingHandCursor);
		m_isClicked = true;
	}
	else{
		this->setCursor(Qt::ArrowCursor);
		this->setToolTip("");
		m_isClicked = false;
	}
}

void HeadImage::enterEvent(QEvent *event)
{
    mIsMouseOver = true;
	if (m_hasHoverBorder)
	{
		repaint();
	}
	event->accept();
}

void HeadImage::leaveEvent(QEvent *event)
{
    mIsMouseOver = false;
	if (m_hasHoverBorder)
	{
		repaint();
	}
	event->accept();
}

void HeadImage::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton){
		if (m_isClicked)
		{
			if (rect().contains(event->pos()))
			{
				emit clicked(event->globalPos());
			}
		}
	}
	QWidget::mousePressEvent(event);
}

void HeadImage::paintEvent(QPaintEvent *event)
{
    //Q_UNUSED(event)
    QPainter painter(this);

 
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);

    QPainterPath path;
    path.addEllipse(rect());
    painter.setClipPath(path);
    QImage scaledAvatar;
	if (!mIsShowGray)
	{
		scaledAvatar = mOriginalImage.scaled(mAvatarSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}else{
		QImage iGray(mAvatarSize.width(),mAvatarSize.height(),QImage::Format_RGB32);   
		QImage ori = mOriginalImage.scaled(mAvatarSize);
		for(int i=0; i<mAvatarSize.width(); i++){  
			for(int j=0;j<mAvatarSize.height(); j++){  
				QRgb pixel = ori.pixel(i,j);  
				int gray = qGray(pixel);  
				QRgb grayPixel = qRgb(gray,gray,gray);  
				iGray.setPixel(i,j,grayPixel);  
			}  
		} 
		scaledAvatar = iGray;
	}
    painter.drawImage(rect(), scaledAvatar);

	if (mIsMouseOver && m_hasHoverBorder)
	{
		QPen pen;
		pen.setWidth(3);
		pen.setColor(Qt::white);
		painter.setPen(pen);
		painter.drawEllipse(rect());
	}
	
	QWidget::paintEvent(event);
}

void HeadImage::setAvatarPath(const QString& fullPath)
{
////	return;

    mImgFullPath = fullPath;

    // in case set a invalid avatar
	 bool ret = mOriginalImage.load(mImgFullPath);
	 if (ret == false) {
		 QString path = QString::fromLocal8Bit(fullPath.toStdString().data());
		 ret = mOriginalImage.load(path);
		 if (ret) {
			 mImgFullPath = path;
		 }
	 }
    update();
}

QString HeadImage::AvatarPath(){
	return mImgFullPath;
}

void HeadImage::setHasHoverBorder(const bool hasHoverBorder)
{
    m_hasHoverBorder = hasHoverBorder;
}

void HeadImage::setShowAsGray( bool isGray )
{
	mIsShowGray = isGray;
	update();
}

void HeadImage::setAvaterSize( QSize size )
{
	setFixedSize(size);
	mAvatarSize = size;
	update();
}

}
