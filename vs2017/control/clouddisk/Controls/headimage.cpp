#include "headimage.h"

#include "common/Common.h"
#include <QImage>
#include <QDebug>
#include <QBitmap>
namespace ui{
#define DEFAULT_AVATAR          ":/img/default_head"
HeadImage::HeadImage(QWidget *parent, const QSize& avatarSize, bool hasHoverBorder)
    : QWidget(parent),mImgFullPath(""), m_hasHoverBorder(hasHoverBorder)
{
    mIsMouseOver = mIsMousePressed = false;
    mAvatarSize = avatarSize;
    mOriginalImage.load(DEFAULT_AVATAR);
    mMask.load(":/contact/mask_max.png");
    setFixedSize(avatarSize);
	mIsShowGray = false;
	this->setMouseTracking(true);
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
    if(event->button() == Qt::LeftButton)
        emit clicked(event->globalPos());
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

	if (mIsMouseOver)
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
    mImgFullPath = fullPath;

    // in case set a invalid avatar
	 bool ret = mOriginalImage.load(mImgFullPath);
    if (!ret)
        mOriginalImage.load(DEFAULT_AVATAR);
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

}
