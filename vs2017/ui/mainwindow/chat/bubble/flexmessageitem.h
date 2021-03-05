#ifndef FLEXMESSAGEITEM_H
#define FLEXMESSAGEITEM_H

#include <QGraphicsItemGroup>
#include <QIcon>

class AbstractMessageWidget;
class FlexMessageItem : public QGraphicsItemGroup
{
public:
    enum SenderType { Self, Others };

    explicit FlexMessageItem(QGraphicsItem *parent = 0);
    ~FlexMessageItem();

    void setNameVisible(bool visible);
    bool nameVisible() const;
    
    void setName(const QString& name);
    QString name() const;

    void setAvatar(const QPixmap& avatar);
    QPixmap avatar() const;

    void setMessageWidget(AbstractMessageWidget* msgWidget);
    AbstractMessageWidget* messageWidget() const;

    void setSenderType(SenderType sender);
    SenderType senderType() const;

    QRectF boundingRect() const;

private:
    class FlexMessageItemPrivate* d_ptr;
};

#endif // FLEXMESSAGEITEM_H
