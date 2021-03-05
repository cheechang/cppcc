#ifndef SPEECHBUBBLEPAINTER_H
#define SPEECHBUBBLEPAINTER_H

#include <QObject>
#include <QColor>
#include <QBrush>

class QPainter;
class SpeechBubblePainter
{
public:
    enum Direction { TopLeft, TopRight, BottomRight, BottomLeft,Center};

    SpeechBubblePainter();
    ~SpeechBubblePainter();

    void setMargin(int margin);
    int margin() const;

    void setBorderColor(const QColor& clr);
    QColor borderColor() const;

    void setBorderWidth(int width);
    int borderWidth() const;

    void setBorderRadius(int radius);
    int borderRadius() const;

    void setBrush(const QBrush& brush);
    QBrush brush() const;

    QRectF centralRect() const;

    void draw(QPainter* painter, const QRect& rect, Direction direction = TopLeft);

private:
    class SpeechBubblePainterPrivate* d_ptr;
};

#endif // SPEECHBUBBLEPAINTER_H
