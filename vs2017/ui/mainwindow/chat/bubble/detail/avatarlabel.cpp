#include "avatarlabel.h"

#include <QApplication>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
AvatarLabel::AvatarLabel(QWidget* parent) : QLabel(parent)
{
    setMouseTracking(true);
}

void AvatarLabel::mousePressEvent(QMouseEvent* event)
{
    if (m_cursorPos.y() <= width())
        emit clicked();

    QLabel::mousePressEvent(event);
}

void AvatarLabel::mouseMoveEvent(QMouseEvent* event)
{
    m_cursorPos = event->pos();
    QLabel::mouseMoveEvent(event);
}

