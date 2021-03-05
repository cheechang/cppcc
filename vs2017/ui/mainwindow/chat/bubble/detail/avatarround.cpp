#include "avatarround.h"

#include <QImage>
#include <QDebug>
#include <QBitmap>
#include "common/Common.h"
AvatarRound::AvatarRound(QWidget *parent, const QSize& avatarSize)
    : QWidget(parent)
{
    mIsMouseOver = mIsMousePressed = false;
    mAvatarSize = avatarSize;
    mOriginalImage.load(DEFAULT_AVATAR);
    mMask.load(":/contact/mask_max.png");
//    setFixedSize(avatarSize);

    setStyleSheet("border: 1px solid red;");
}

void AvatarRound::enterEvent(QEvent *)
{
    mIsMouseOver = true;
}

void AvatarRound::leaveEvent(QEvent *)
{
    mIsMouseOver = false;
}

void AvatarRound::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
	{
        mIsMousePressed = true;
	}
}

void AvatarRound::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && mIsMousePressed)
	{
        emit clicked();
	}
    mIsMousePressed = false;
}

void AvatarRound::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);

    int minLen = std::min(width(), height());
    QRect topRect(QPoint(0, 0), QSize(minLen, minLen));

    QPainterPath path;
    path.addEllipse(topRect);
    painter.setClipPath(path);
    QImage scaledAvatar = mOriginalImage.scaled(mAvatarSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawImage(topRect, scaledAvatar);
}

void AvatarRound::setAvatarPath(const QString& fullPath)
{
    mImgFullPath = fullPath;

    // in case set a invalid avatar
    if (!mOriginalImage.load(mImgFullPath))
        mOriginalImage.load(DEFAULT_AVATAR);
    update();
}

void AvatarRound::setAvatar(const QPixmap& pixmap)
{
    mOriginalImage = pixmap.toImage();
    update();
}

QPixmap AvatarRound::avatar() const
{
    return QPixmap::fromImage(mOriginalImage);
}

QSize AvatarRound::sizeHint() const
{
    return QSize(64, 64);
}


