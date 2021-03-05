#pragma  once
#include <QGraphicsTextItem>
class MsgTimeItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    MsgTimeItem(QGraphicsItem *parent =0);
    ~MsgTimeItem();

	 int type() const;
};
