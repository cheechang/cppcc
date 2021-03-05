#include "AvatarWidget.h"
#include <QImage>
#include <QBitmap>
#include <QEvent>
#include <QPainter>
#include <QMouseEvent>
#include <log/log.h>
#include <ui/common/Common.h>

namespace uicontrols{
	AvatarWidget::AvatarWidget(QWidget *parent, const QSize& avatarSize, bool hasHoverBorder)
		: QWidget(parent),m_imgFullPath(""), m_hasHoverBorder(hasHoverBorder)
	{
		m_isMouseOver = m_isMousePressed = false;
		m_avatarSize = avatarSize;
		m_originalImage.load(DEFAULT_AVATAR);
		m_maskImg.load(":/contact/mask_max.png");
		setFixedSize(avatarSize);
		m_isShowGray = false;
		this->setMouseTracking(true);
	}

	void AvatarWidget::enterEvent(QEvent *event)
	{
		m_isMouseOver = true;
		if (m_hasHoverBorder)
		{
			repaint();
		}
		emit signalEnter();
		event->accept();
	}

	void AvatarWidget::leaveEvent(QEvent *event)
	{
		m_isMouseOver = false;
		if (m_hasHoverBorder)
		{
			repaint();
		}
		event->accept();
	}

	void AvatarWidget::mousePressEvent(QMouseEvent *event)
	{
		if(event->button() == Qt::LeftButton){
			if (rect().contains(event->pos()))
			{
				emit clicked(event->globalPos());
			}
		}else{
			if (rect().contains(event->pos()))
			{
				emit rightClicked();
			}
		}
		QWidget::mousePressEvent(event);
	}

	void AvatarWidget::paintEvent(QPaintEvent *event)
	{
		Q_UNUSED(event)
		QPainter painter(this);
		painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
		int minLen = qMin(width(), height());
        QRect topRect(QPoint(0, 0), QSize(minLen, minLen));
		QPainterPath path;
		path.addEllipse(topRect);
		painter.setClipPath(path);
		QImage scaledAvatar;
		if (!m_isShowGray)
		{
			scaledAvatar = m_originalImage.scaled(m_avatarSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		}else{
			QImage iGray(m_avatarSize,QImage::Format_RGB32);   
			QImage ori = m_originalImage.scaled(m_avatarSize);
			for(int i=0; i<m_avatarSize.width(); i++){  
				for(int j=0;j<m_avatarSize.height(); j++){  
					QRgb pixel = ori.pixel(i,j);  
					int gray = qGray(pixel);  
					QRgb grayPixel = qRgb(gray,gray,gray);  
					iGray.setPixel(i,j,grayPixel);  
				}  
			} 
			scaledAvatar = iGray;
		}
		painter.drawImage(topRect,scaledAvatar);
		/*if (m_hasHoverBorder)
		{
			QPen pen;
			pen.setWidth(3);
			pen.setColor(Qt::white);
			painter.setPen(pen);
			painter.drawEllipse(topRect);
		}
		else{
			QPen pen;
			pen.setWidth(1);
			pen.setColor(Qt::gray);
			painter.setPen(pen);
			painter.drawEllipse(topRect);
		}*/

		QWidget::paintEvent(event);
	}

	QString AvatarWidget::getImgRealType(QString fileName){
		QString imgtype("");
		QString magicStr("0x");
		QFile file(fileName);
		file.open(QIODevice::ReadOnly);
		QDataStream in(&file);
		// Read and check the header
		quint32 magic;
		in >> magic;
		magicStr.append(QString::number(magic,16));
		if (magicStr.contains("0xffd8ff"))
		{
			//png
			imgtype= "jpg";
		}
		else if (magicStr.contains("0x89504e47"))
		{
			//png
			imgtype= "png";
		}
		else if (magicStr.contains("0x47494638"))
		{
			//png
			imgtype= "gif";
		}
		else if (magicStr.contains("0x49492a00"))
		{
			//png
			imgtype= "tif";
		}
		else if (magicStr.contains("0x424d"))
		{
			//bmp
			imgtype= "bmp";
		}
		else{
			imgtype = "unknown";
		}
		return imgtype;
	}

	void AvatarWidget::setAvatarPath(const QString& fullPath)
	{
		m_imgFullPath = fullPath;
		bool ret = false;
		QString type = getImgRealType(fullPath);
		if(type != "unknown"){
			ret = m_originalImage.load(m_imgFullPath,type.toStdString().c_str());
		}else{
			ret = m_originalImage.load(m_imgFullPath);
		}
		if (!ret)
		{
			m_originalImage.load(DEFAULT_AVATAR);
		}
		update();
	}

	QString AvatarWidget::AvatarPath(){
		return m_imgFullPath;
	}

	void AvatarWidget::setHasHoverBorder(const bool hasHoverBorder)
	{
		m_hasHoverBorder = hasHoverBorder;
	}

	void AvatarWidget::setShowAsGray( bool isGray )
	{
		m_isShowGray = isGray;
		update();
	}

	void AvatarWidget::setAvaterSize( QSize size )
	{
		setFixedSize(size);
		m_avatarSize = size;
		update();
	}
}