#include "generalmessageitem.h"
#include "speechbubblepainter.h"
#include <QStyleOptionGraphicsItem>
#include "common/Common.h"
GeneralMessageItem::GeneralMessageItem(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsProxyWidget(parent, wFlags),m_sender(Self)
{
    m_bubblePainter = new SpeechBubblePainter;
}

GeneralMessageItem::~GeneralMessageItem()
{
    delete m_bubblePainter;
}
int GeneralMessageItem::type() const
{
	return GENERAL_MSG;
}
void GeneralMessageItem::setSenderType(GeneralMessageItem::SenderType sender)
{
    m_sender = sender;
    update();
}
GeneralMessageItem::SenderType GeneralMessageItem::senderType() const
{
    return m_sender;
}
