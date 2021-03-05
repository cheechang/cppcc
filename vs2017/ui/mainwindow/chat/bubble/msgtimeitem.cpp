#include "msgtimeitem.h"
#include "common/Common.h"
MsgTimeItem::MsgTimeItem(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
}

MsgTimeItem::~MsgTimeItem()
{

}
int MsgTimeItem::type() const
{
	return TIME_MSG;
}
