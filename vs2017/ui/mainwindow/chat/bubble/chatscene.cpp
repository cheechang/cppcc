#include "chatscene.h"

#include <QPainter>
#include "generalmessageitem.h"
#include "detail/flexmessagewidget.h"
#include "abstractmessagewidget.h"

ChatScene::ChatScene(QObject* parent) : QGraphicsScene(parent)
{

}

ChatScene::~ChatScene()
{

}

void ChatScene::setBackgroundImage(const QPixmap &image)
{
    m_bgImage = image;
    update();
}

AbstractMessageWidget* ChatScene::getMsgWidgetByMsgId(int64 msgId) {
	static AbstractMessageWidget* absmsg = CNull;
	foreach(QGraphicsItem* item, this->items())
	{
		if (GENERAL_MSG != item->type()) {
			continue;
		}
		GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(item);
		if (CNull != msgItem) {
			FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
			if (CNull != msgWidget) {
				absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
				if (CNull != absmsg && absmsg->msgId() == msgId)
				{
					break;
				}
			}
		}
	}
	return absmsg;
}
QMap<int64, FlexMessageWidget*> ChatScene::getMySendMessageWidgets()
{
	QMap<int64, FlexMessageWidget*>map;
	GeneralMessageItem* msgItem = CNull;
	foreach(QGraphicsItem* item, this->items())
	{
		if (GENERAL_MSG != item->type()) {
			continue;
		}
		msgItem = dynamic_cast<GeneralMessageItem*>(item);
		if (CNull != msgItem) {
			FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
			if (CNull != msgWidget) {
				AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
				if (CNull != absmsg && !absmsg->isRecv())
				{
					map[absmsg->msgId()] = msgWidget;
				}
			}
		}
	}
	return map;
}

QPixmap ChatScene::backgroundImage() const
{
    return m_bgImage;
}

void ChatScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (!m_bgImage.isNull())
        painter->drawPixmap(rect.toRect(), m_bgImage);
}

