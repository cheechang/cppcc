#ifndef GENERALMESSAGEITEM_H
#define GENERALMESSAGEITEM_H
#include "interface/Defines.h"
#include <QGraphicsProxyWidget>
class SpeechBubblePainter;
class GeneralMessageItem : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    enum SenderType { Self, Others };

    GeneralMessageItem(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~GeneralMessageItem();

	 int type() const;

    void setSenderType(SenderType sender);
    SenderType senderType() const;
protected:
    SpeechBubblePainter* m_bubblePainter;
    SenderType  m_sender;
};

#endif // GENERALMESSAGEITEM_H
