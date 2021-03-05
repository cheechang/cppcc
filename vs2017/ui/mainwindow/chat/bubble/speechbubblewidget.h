#ifndef SPEECHBUBBLEWIDGET_H
#define SPEECHBUBBLEWIDGET_H

#include <QWidget>
class SpeechBubblePainter;
class SpeechBubbleWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
public:
    enum Direction { TopLeft, TopRight, BottomRight, BottomLeft,Center};

    explicit SpeechBubbleWidget(QWidget *parent = 0);
    ~SpeechBubbleWidget();

    void setDirection(Direction d);
    Direction direction() const;

    void setBorderColor(const QColor& clr);
    QColor borderColor() const;

    void setBorderWidth(int width);
    int borderWidth() const;

    void setBorderRadius(int radius);
    int borderRadius() const;

    void setBrush(const QBrush& brush);
    QBrush brush() const;

    void setCentralWidget(QWidget* widget);
    QWidget* centralWidget() const;

    QSize sizeHint() const;

    virtual QSize suggestWidth(int width);

signals:

protected:
    void paintEvent(QPaintEvent* event);
    void contextMenuEvent(QContextMenuEvent* event);
private:
    class SpeechBubbleWidgetPrivate* d_ptr;
};

#endif // SPEECHBUBBLEWIDGET_H
