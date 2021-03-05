#include "clicklabel.h"

#include <QMouseEvent>
#include <QApplication>

ClickLabel::ClickLabel(QWidget* parent) : QLabel(parent), m_underlined(false), m_textColor(Qt::black)
{
    setMouseTracking(true);
}

void ClickLabel::setUnderlined(bool underlined)
{
    m_underlined = underlined;
}

bool ClickLabel::underlined() const
{
    return m_underlined;
}

void ClickLabel::setTextColor(const QColor& clr)
{
    if (m_textColor != clr) {
        m_textColor = clr;
        QString style = QString("color: rgb(%1, %2, %3);").arg(clr.red()).arg(clr.green()).arg(clr.blue());
        setStyleSheet(style);
    }
}

QColor ClickLabel::textColor() const
{
    return m_textColor;
}

void ClickLabel::enterEvent(QEvent* event)
{
    Q_UNUSED(event)
    if (m_underlined) {
        setCursor(Qt::PointingHandCursor);
        makeUnderlined(true);
    }
}

void ClickLabel::leaveEvent(QEvent* event)
{
    Q_UNUSED(event)
    if (m_underlined) {
        qApp->restoreOverrideCursor();
        makeUnderlined(false);
    }
}

void ClickLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
        emit clicked();
    QLabel::mousePressEvent(event);
}

void ClickLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
        emit clicked();
    QLabel::mouseReleaseEvent(event);
}

void ClickLabel::makeUnderlined(bool underline)
{
    QFont f = font();
    f.setUnderline(underline);
    setFont(f);
}

