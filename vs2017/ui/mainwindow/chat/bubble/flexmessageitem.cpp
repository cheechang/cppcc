#include "flexmessageitem.h"
#include "abstractmessagewidget.h"

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsGridLayout>
#include <QPainter>
#include <QLabel>
class FlexMessageItemPrivate
{
public:
    void init();

    FlexMessageItem* q_ptr;
    FlexMessageItem::SenderType sender;
    QIcon avatar;
    QGraphicsProxyWidget* messageProxyWidget;
    QGraphicsPixmapItem* avatarItem;
    QGraphicsTextItem*   nameItem;
};

void FlexMessageItemPrivate::init()
{
    // create child items and do layout
    messageProxyWidget = new QGraphicsProxyWidget(q_ptr);
    avatarItem = new QGraphicsPixmapItem(q_ptr);
    nameItem = new QGraphicsTextItem(q_ptr);
    nameItem->setPlainText("Default Name");

    QPixmap pixmap(QSize(120, 120));
    QPainter painter(&pixmap);
    painter.drawEllipse(pixmap.rect().center(), 50, 50);

    avatarItem->setPixmap(QPixmap(":/base/avatar.png"));

    q_ptr->addToGroup(nameItem);
//    q_ptr->addToGroup(avatarItem);
    q_ptr->addToGroup(messageProxyWidget);

    messageProxyWidget->setZValue(8);
    nameItem->setZValue(9);
//    avatarItem->setZValue(10);

}

FlexMessageItem::FlexMessageItem(QGraphicsItem *parent) : QGraphicsItemGroup(parent)
{
    d_ptr = new FlexMessageItemPrivate;
    d_ptr->q_ptr = this;
    d_ptr->init();
}

void FlexMessageItem::setNameVisible(bool visible)
{
    d_ptr->nameItem->setVisible(visible);
}

bool FlexMessageItem::nameVisible() const
{
    return d_ptr->nameItem->isVisible();
}

FlexMessageItem::~FlexMessageItem()
{
    delete d_ptr;
}

void FlexMessageItem::setName(const QString& name)
{
    d_ptr->nameItem->setPlainText(name);
}

QString FlexMessageItem::name() const
{
    return d_ptr->nameItem->toPlainText();
}

void FlexMessageItem::setAvatar(const QPixmap& avatar)
{
    d_ptr->avatarItem->setPixmap(avatar);
}

QPixmap FlexMessageItem::avatar() const
{
    return d_ptr->avatarItem->pixmap();
}

void FlexMessageItem::setMessageWidget(AbstractMessageWidget* msgWidget)
{
    d_ptr->messageProxyWidget->setWidget(msgWidget);
}

AbstractMessageWidget* FlexMessageItem::messageWidget() const
{
    return qobject_cast<AbstractMessageWidget*>(d_ptr->messageProxyWidget->widget());
}

void FlexMessageItem::setSenderType(FlexMessageItem::SenderType sender)
{
    d_ptr->sender = sender;
    update();
}

FlexMessageItem::SenderType FlexMessageItem::senderType() const
{
    return d_ptr->sender;
}

QRectF FlexMessageItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), QSize(d_ptr->messageProxyWidget->boundingRect().width() + 120, d_ptr->messageProxyWidget->boundingRect().height() + 50));
}

