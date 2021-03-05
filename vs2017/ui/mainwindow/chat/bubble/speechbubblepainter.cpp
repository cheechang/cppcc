#include "speechbubblepainter.h"

#include <QPainter>
#include <QColor>
#include <QBrush>

const int TopMargin = 1;
const int LeftMargin = 10;
const int CentralRectMargin = 5;
const int MaxAngleHeight = 5;

class SpeechBubblePainterPrivate
{
public:
    SpeechBubblePainterPrivate() : margin(3), borderRadius(20), borderWidth(2),
        borderColor(Qt::lightGray), brush(QBrush(Qt::white)) {}

    void drawBubbleByTopLeft(QPainter* painter, const QRect& rect);
    void drawBubbleByTopRight(QPainter* painter, const QRect& rect);
    void drawBubbleByBottomRight(QPainter* painter, const QRect& rect);
    void drawBubbleByBottomLeft(QPainter* painter, const QRect& rect);
	void drawBubbleByNone(QPainter* painter, const QRect& rect);
    int margin;
    int borderRadius;
    int borderWidth;
    QColor borderColor;
    QBrush brush;
    QRectF centralRect;
};

void SpeechBubblePainterPrivate::drawBubbleByTopLeft(QPainter* painter, const QRect& rect)
{
    if (!painter) return;

    const int Radius = borderRadius;
    QRectF bodyRect(QPointF(LeftMargin, TopMargin), rect.bottomRight());

    QPainterPath path;
    path.moveTo(QPointF(0, 0));
    path.lineTo(bodyRect.left(), bodyRect.top() + MaxAngleHeight);
    path.lineTo(bodyRect.left(), bodyRect.bottom() - Radius);

    // bottom left corner
    path.arcTo(QRectF(bodyRect.left(), bodyRect.bottom() - Radius, Radius, Radius), 180, 90);
    path.lineTo(bodyRect.left() + Radius, bodyRect.bottom());

    // bottom right corner
    path.lineTo(bodyRect.right() - Radius, bodyRect.bottom());
    path.arcTo(QRectF(bodyRect.right() - Radius, bodyRect.bottom() - Radius, Radius, Radius), 270, 90);
    path.lineTo(bodyRect.right(), bodyRect.top() + Radius);

    // top right corner
    QRectF topRightRect(bodyRect.right() - Radius, bodyRect.top(), Radius, Radius);
    path.arcTo(topRightRect, 0.0, 90.0);

    painter->setPen(QPen(borderColor, borderWidth));
    painter->setBrush(brush);
    painter->drawPath(path.simplified());

    this->centralRect = bodyRect.adjusted(CentralRectMargin, CentralRectMargin, -CentralRectMargin, -CentralRectMargin);
}

void SpeechBubblePainterPrivate::drawBubbleByTopRight(QPainter* painter, const QRect& rect)
{
    if (!painter) return;

    const int Radius = borderRadius;
    QPointF bodyTopRight(rect.width() - LeftMargin, TopMargin);
    QRectF bodyRect(QPointF(0, 0), QPointF(rect.width() - LeftMargin, rect.bottom()));

    QPainterPath path;
    path.moveTo(QPointF(rect.right(), 0));
    path.lineTo(bodyTopRight.x(), bodyTopRight.y() + MaxAngleHeight);
    path.lineTo(bodyRect.right(), bodyRect.bottom() - Radius);

    // bottom right corner
    path.arcTo(QRectF(bodyRect.right() - Radius, bodyRect.bottom() - Radius, Radius, Radius), 0, -90);

    // bottom left corner
    path.lineTo(bodyRect.left() - Radius, bodyRect.bottom());
    path.arcTo(QRectF(bodyRect.left(), bodyRect.bottom() - Radius, Radius, Radius), -90, -90);
    path.lineTo(bodyRect.left(), bodyRect.top() - Radius);

    // top left corner
    path.arcTo(QRectF(bodyRect.left(), bodyRect.top(), Radius, Radius), -180, -90.0);

    painter->setPen(QPen(borderColor, borderWidth));
    painter->setBrush(brush);
    painter->drawPath(path.simplified());

    this->centralRect = bodyRect.adjusted(CentralRectMargin, CentralRectMargin, -CentralRectMargin, -CentralRectMargin);
}

void SpeechBubblePainterPrivate::drawBubbleByBottomRight(QPainter* painter, const QRect& rect)
{
    if (!painter) return;

    const int Radius = borderRadius;
    QRectF bodyRect(QPointF(0, 0), QPointF(rect.width() - LeftMargin, rect.height() - TopMargin));
    QPainterPath path;
    path.moveTo(rect.bottomRight());
    path.lineTo(bodyRect.right(), bodyRect.height() - MaxAngleHeight);
    path.lineTo(bodyRect.right(), bodyRect.top() + Radius);

    // top right corner
    path.arcTo(QRectF(bodyRect.right() - Radius, bodyRect.top(), Radius, Radius), 0, 90);

    // top left corner
    path.lineTo(bodyRect.left() + Radius, bodyRect.top());
    path.arcTo(QRectF(bodyRect.left(), bodyRect.top(), Radius, Radius), 90, 90);
    path.lineTo(bodyRect.left(), bodyRect.bottom() - Radius);

    // bottom left corner
    path.arcTo(QRectF(bodyRect.left(), bodyRect.bottom() - Radius, Radius, Radius), 180, 90.0);

    painter->setPen(QPen(borderColor, borderWidth));
    painter->setBrush(brush);
    painter->drawPath(path.simplified());

    this->centralRect = bodyRect.adjusted(CentralRectMargin, CentralRectMargin, -CentralRectMargin, -CentralRectMargin);
}

void SpeechBubblePainterPrivate::drawBubbleByBottomLeft(QPainter* painter, const QRect& rect)
{
    if (!painter) return;

    const int Radius = borderRadius;
    QRectF bodyRect(QPointF(LeftMargin, TopMargin), rect.bottomRight());

    QPainterPath path;
    path.moveTo(QPointF(0, rect.height()));
    path.lineTo(bodyRect.left(), bodyRect.height() - MaxAngleHeight);
    path.lineTo(bodyRect.left(), bodyRect.top() - Radius);

    // top left corner
    path.arcTo(QRectF(bodyRect.left(), bodyRect.top(), Radius, Radius), 180, -90);

    // bottom left corner
    path.lineTo(bodyRect.right() - Radius, bodyRect.top());
    path.arcTo(QRectF(bodyRect.right() - Radius, bodyRect.top(), Radius, Radius), 90, -90);
    path.lineTo(bodyRect.right(), bodyRect.bottom() - Radius);

    // top left corner
    path.arcTo(QRectF(bodyRect.right() - Radius, bodyRect.bottom() - Radius, Radius, Radius), 0, -90.0);

    painter->setPen(QPen(borderColor, borderWidth));
    painter->setBrush(brush);
    painter->drawPath(path.simplified());

    this->centralRect = bodyRect.adjusted(CentralRectMargin, CentralRectMargin, -CentralRectMargin, -CentralRectMargin);
}

void SpeechBubblePainterPrivate::drawBubbleByNone(QPainter* painter, const QRect& rect){
	if (!painter) return;

	const int Radius = borderRadius;
	QRectF bodyRect(QPointF(LeftMargin, TopMargin), rect.bottomRight());

	QPainterPath path;
	path.addRoundedRect(bodyRect, 10, 10);
	painter->setPen(QPen(QColor(225,226,227),borderWidth));
	painter->setBrush(QBrush(QColor(225,226,227)));
	painter->drawPath(path.simplified());

	this->centralRect = bodyRect.adjusted(CentralRectMargin, CentralRectMargin, -CentralRectMargin, -CentralRectMargin);
}

SpeechBubblePainter::SpeechBubblePainter()
{
    d_ptr = new SpeechBubblePainterPrivate;
}

SpeechBubblePainter::~SpeechBubblePainter()
{
    delete d_ptr;
}

void SpeechBubblePainter::draw(QPainter *painter, const QRect &rect, Direction direction)
{
    if (!painter) return;

    painter->setRenderHints(QPainter::Antialiasing);

    switch (direction) {
    case TopLeft:
        d_ptr->drawBubbleByTopLeft(painter, rect);
        break;

    case TopRight:
        d_ptr->drawBubbleByTopRight(painter, rect);
        break;

    case BottomRight:
        d_ptr->drawBubbleByBottomRight(painter, rect);
        break;

    case BottomLeft:
        d_ptr->drawBubbleByBottomLeft(painter, rect);
	case Center:
		d_ptr->drawBubbleByNone(painter, rect);
    }
}

void SpeechBubblePainter::setMargin(int margin)
{
    d_ptr->margin = margin;
}

int SpeechBubblePainter::margin() const
{
    return d_ptr->margin;
}

void SpeechBubblePainter::setBorderColor(const QColor& clr)
{
    d_ptr->borderColor = clr;
}

QColor SpeechBubblePainter::borderColor() const
{
    return d_ptr->borderColor;
}

void SpeechBubblePainter::setBorderWidth(int width)
{
    d_ptr->borderWidth = width;
}

int SpeechBubblePainter::borderWidth() const
{
    return d_ptr->borderWidth;
}

void SpeechBubblePainter::setBorderRadius(int radius)
{
    d_ptr->borderRadius = radius;
}

int SpeechBubblePainter::borderRadius() const
{
    return d_ptr->borderRadius;
}

void SpeechBubblePainter::setBrush(const QBrush& brush)
{
    d_ptr->brush = brush;
}

QBrush SpeechBubblePainter::brush() const
{
    return d_ptr->brush;
}

QRectF SpeechBubblePainter::centralRect() const
{
    return d_ptr->centralRect;
}

