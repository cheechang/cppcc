#include "UserHeadImg.h"
#include "Log.h"
#include "controls/PushButton.h"
#include <QBitmap>
#include <QPainter>
#include "../common/Common.h"
namespace ui{
UserHeadImg::UserHeadImg(QObject *parent)
{
	PushButton* btn = new PushButton(this);
	m_head = new QLabel(this);
	m_head->setScaledContents(true);
	m_head->setFixedSize(110,110);
	m_head->move(90+25, 30);
	m_head->raise();
											  
	btn->setPicName(":/title/photo");
	btn->setFixedSize(26,26);
	btn->setToolTip(transfer("ÐÞ¸ÄÍ·Ïñ"));
	btn->move(HEAD_WIDTH - 90,2);
	btn->setCursor(Qt::PointingHandCursor);
	connect(btn,SIGNAL(clicked(bool)),this,SIGNAL(mouseLeftRelease()));

    m_closeBtn = CMakePtr<PushButton>(this);
    m_closeBtn->setPicName(":/login/headclose");
    m_closeBtn->setFixedSize(26,26);
    m_closeBtn->setToolTip(transfer("¹Ø±Õ"));
    m_closeBtn->move(HEAD_WIDTH - 50,2);
    connect(m_closeBtn.get(),SIGNAL(clicked(bool)),this,SIGNAL(closeImageWin()));

	QPixmap pixTmp(":/contact/contact_bg");
	QPixmap pixmap = pixTmp.scaled(HEAD_WIDTH, 150);
	this->setPixmap(pixmap);
	setMinimumSize(210, 150);
	setAlignment(Qt::AlignHCenter);
}

UserHeadImg::~UserHeadImg()
{

}
void UserHeadImg::setHeadImg(QString path)
{
	m_head->setPixmap(getRoundHead(path,60));
	m_head->setAlignment(Qt::AlignCenter);
}
void UserHeadImg::mouseReleaseEvent(QMouseEvent *ev)
{
	/*if (ev->button() == Qt::LeftButton)
	{
		AddLog(LOG_LEV_INFO,"----------HeadImage-Clicked------------");
		emit mouseLeftRelease();
	}
	ev->ignore();*/
}

QPixmap UserHeadImg::getRoundHead(const QPixmap &src, int radius)
{
	if ( src.isNull() ) {
		return QPixmap();
	}

	QSize size(2 * radius, 2 * radius);
	QBitmap mask(size);
	QPainter painter(&mask);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
	painter.setBrush(QColor(0, 0, 0));
	painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
	QPixmap image = src.scaled(size);
	image.setMask(mask);
	return image;
}

}