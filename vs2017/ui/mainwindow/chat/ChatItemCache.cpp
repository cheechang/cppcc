#include "ChatItemCache.h"
#include <QGraphicsItem>
#include "common/Common.h"
#include "bubble/generalmessageitem.h"
#include "bubble/flexmessageitem.h"
#include "bubble/detail/FlexMessageWidget.h"
#include "bubble/abstractmessagewidget.h"
#include <QDateTime>
namespace ui{
void ChatItemCache::clear(){
	m_maplist.clear();
	m_messageList.clear();
}

void ChatItemCache::AddMsgItem(QGraphicsItem*msgItem,bool ishis){
	int msgtype =0;
	QList<QGraphicsItem*> msglist;
	msglist.clear();

	msgtype = msgItem->type();
	if (!m_maplist.contains(msgtype))
	{
		msglist.append(msgItem);
		m_maplist.insert(msgtype,msglist);
	}
	else{
		msglist = m_maplist.value(msgtype);
		msglist.append(msgItem);
		m_maplist[msgtype] = msglist;
	}
	ishis?m_messageList.prepend(msgItem):m_messageList.append(msgItem);
}
QList<QGraphicsItem*>ChatItemCache::GetMessageList(){
	return m_messageList;
}
GeneralMessageItem*  ChatItemCache::GetGeneralMessageItem(qint64 localid){
	GeneralMessageItem* ItemTemp = CNull;
	QList<QGraphicsItem*> messageList;
	
	if (!m_maplist.contains(GENERAL_MSG))
	{
		return ItemTemp;
	}
	messageList = m_maplist[GENERAL_MSG];
	for ( size_t index=0 ;index<messageList.size();++index)
	{
		GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(messageList.at(index));
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
		AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
		if ( CNull != absmsg && absmsg->uiLocalId() == localid)
		{
			ItemTemp = msgItem;
			break;
		}
	}
	return ItemTemp;
}

QMap<int64,FlexMessageWidget*> ChatItemCache::getMySendMessageWidgets()
{
	QMap<qint64,FlexMessageWidget*>map;
	QList<QGraphicsItem*> messageList;
	messageList = m_maplist[GENERAL_MSG];
	for ( size_t index=0 ;index<messageList.size();++index)
	{
		GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(messageList.at(index));
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
		AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
		if ( CNull != absmsg && msgWidget != CNull && !absmsg->isRecv())
		{
			map[absmsg->msgId()] = msgWidget;
		}
	}
	return map;
}

QGraphicsItem* ChatItemCache::removeMsgItem( qint64 localid )
{
    //É¾³ý»º´æ
	QGraphicsItem*gMsgItem=CNull;
	QList<QGraphicsItem*> messageList;
	messageList = m_maplist[GENERAL_MSG];
	for (int index=0;index<messageList.size();index++)
	{
		GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(messageList.at(index));
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
		AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
		if ( CNull != absmsg && absmsg->uiLocalId() == localid)
		{
			gMsgItem = messageList.at(index);
			break;
		}
	}
	if (gMsgItem)
	{
		m_messageList.removeAll(gMsgItem);
		int msgtype =0;
		QList<QGraphicsItem*> msglist;
		msglist.clear();

		msgtype = gMsgItem->type();
		msglist = m_maplist.value(msgtype);
		msglist.append(gMsgItem);
		m_maplist[msgtype] = msglist;
	}
	return gMsgItem;
}

void ChatItemCache::removeItem( QGraphicsItem*msgItem )
{
	if (msgItem == CNull)
	{
		return ;
	}
	m_messageList.removeAll(msgItem);
	int msgtype =0;
	QList<QGraphicsItem*> msglist;
	msglist.clear();

	msgtype = msgItem->type();
	msglist = m_maplist.value(msgtype);
	msglist.append(msgItem);
	m_maplist[msgtype] = msglist;
}

qint64 ChatItemCache::GetLocalIdByMsgId( qint64 msgId )
{
	QList<QGraphicsItem*> messageList;
	messageList = m_maplist[GENERAL_MSG];
	for (int index=0;index<messageList.size();index++)
	{
		GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(messageList.at(index));
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
		AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
		if ( CNull != absmsg && absmsg->msgId() == msgId)
		{
			return absmsg->uiLocalId();
		}
	}
	return 0;
}

QList<qint64> ChatItemCache::getLocalIdByTime(int type)
{
	QList<qint64> localIdV;
	QDateTime currentTime = QDateTime::currentDateTime();
	qint64 currentSecs = currentTime.toMSecsSinceEpoch();
	QString time = currentTime.toString("yyyy-MM-dd");
	qint64 startCurrentTime = QDateTime::fromString(time, "yyyy-MM-dd").toMSecsSinceEpoch();
	
	QList<QGraphicsItem*> messageList;
	messageList = m_maplist[GENERAL_MSG];
	for (int index = 0; index<messageList.size(); index++)
	{
		GeneralMessageItem* msgItem = dynamic_cast<GeneralMessageItem*>(messageList.at(index));
		FlexMessageWidget* msgWidget = dynamic_cast<FlexMessageWidget*>(msgItem->widget());
		AbstractMessageWidget* absmsg = dynamic_cast<AbstractMessageWidget*>(msgWidget->messageWidget());
		if (type == 1)
		{
			if (absmsg->msgTimeMsc() >= startCurrentTime && absmsg->msgTimeMsc() <= currentSecs){
				localIdV.push_back(absmsg->uiLocalId());
			}
		}
		else{
			localIdV.push_back(absmsg->uiLocalId());
		}
			
	}
	return localIdV;
}
}