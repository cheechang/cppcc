#include "speechbubblewidget.h"
#include "speechbubblepainter.h"

#include <QPainter>
#include <QDebug>

class SpeechBubbleWidgetPrivate
{
public:
    SpeechBubbleWidgetPrivate();
    ~SpeechBubbleWidgetPrivate();

    void layoutCentralWidget();

    SpeechBubbleWidget* q_ptr;
    SpeechBubblePainter* painter;
    SpeechBubbleWidget::Direction direction;
    QWidget* centralWidget;
};

SpeechBubbleWidgetPrivate::SpeechBubbleWidgetPrivate() : direction(SpeechBubbleWidget::TopLeft), centralWidget(0)
{
    painter = new SpeechBubblePainter;
}

SpeechBubbleWidgetPrivate::~SpeechBubbleWidgetPrivate()
{
    delete painter;
}

void SpeechBubbleWidgetPrivate::layoutCentralWidget()
{
    if (!centralWidget || !painter)
        return;

    QRect centralRect = painter->centralRect().toRect();
    centralWidget->move(centralRect.topLeft());
    centralWidget->setGeometry(centralRect);
    centralWidget->show();
}

SpeechBubbleWidget::SpeechBubbleWidget(QWidget *parent) : QWidget(parent)
{
    d_ptr = new SpeechBubbleWidgetPrivate;
    d_ptr->q_ptr = this;
    setAttribute(Qt::WA_TranslucentBackground);
	setContextMenuPolicy(Qt::ActionsContextMenu);

}

SpeechBubbleWidget::~SpeechBubbleWidget()
{
    delete d_ptr;
}

void SpeechBubbleWidget::setDirection(Direction d)
{
    if (d_ptr->direction != d) {
        d_ptr->direction = d;
        update();
    }
}

void SpeechBubbleWidget::setBorderColor(const QColor& clr)
{
    d_ptr->painter->setBorderColor(clr);
    update();
}

QColor SpeechBubbleWidget::borderColor() const
{
    return d_ptr->painter->borderColor();
}

void SpeechBubbleWidget::setBorderWidth(int width)
{
    d_ptr->painter->setBorderWidth(width);
    update();
}

int SpeechBubbleWidget::borderWidth() const
{
    return d_ptr->painter->borderWidth();
}

void SpeechBubbleWidget::setBorderRadius(int radius)
{
    d_ptr->painter->setBorderRadius(radius);
    update();
}

int SpeechBubbleWidget::borderRadius() const
{
    return d_ptr->painter->borderRadius();
}

void SpeechBubbleWidget::setBrush(const QBrush& brush)
{
    d_ptr->painter->setBrush(brush);
}

QBrush SpeechBubbleWidget::brush() const
{
    return d_ptr->painter->brush();
}

void SpeechBubbleWidget::setCentralWidget(QWidget* widget)
{
    if (d_ptr->centralWidget != widget) {
        d_ptr->centralWidget = widget;

        QSizePolicy sp = widget->sizePolicy();
        sp.setVerticalPolicy(QSizePolicy::Expanding);
        d_ptr->centralWidget->setSizePolicy(sp);

        widget->setParent(this);
        resize(QSize(50+widget->width(), 10 + widget->height()));
        d_ptr->layoutCentralWidget();
    }
}

QWidget* SpeechBubbleWidget::centralWidget() const
{
    return d_ptr->centralWidget;
}

QSize SpeechBubbleWidget::sizeHint() const
{
    if (d_ptr->centralWidget)
        return QSize(50 + d_ptr->centralWidget->width(), 10 + d_ptr->centralWidget->height());
    else
        return QSize(200, 80);
}

QSize SpeechBubbleWidget::suggestWidth(int width)
{
    return QSize();
}

SpeechBubbleWidget::Direction SpeechBubbleWidget::direction() const
{
    return d_ptr->direction;
}

void SpeechBubbleWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    d_ptr->painter->draw(&painter, this->rect(), static_cast<SpeechBubblePainter::Direction>(d_ptr->direction));
    d_ptr->layoutCentralWidget();

#if 0
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(d_ptr->painter->centralRect());
    painter.restore();
#endif
}

void SpeechBubbleWidget::contextMenuEvent(QContextMenuEvent* event)
{
    // no impl
}


