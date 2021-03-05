#pragma once
#include <QList>
#include <QMap>
class QGraphicsItem;
class AbstractMessageWidget;
class ChatView;
class FlexMessageWidget;
class GeneralMessageItem;

using namespace std;
namespace ui{
class ChatItemCache{
public:
	ChatItemCache(){};
	virtual ~ChatItemCache(){};
	void clear();
	void AddMsgItem(QGraphicsItem*msgItem,bool ishis);
	void removeItem(QGraphicsItem*msgItem);
	QGraphicsItem* removeMsgItem(qint64 localid);
	QList<QGraphicsItem*>GetMessageList();
	GeneralMessageItem* GetGeneralMessageItem(qint64 localid);
	qint64 GetLocalIdByMsgId(qint64 msgId);
	QList<qint64> getLocalIdByTime(int type); //type 1:获取今天消息localid  2:获取所有消息的localid
	QMap<qint64,FlexMessageWidget*>getMySendMessageWidgets();
private:
	typedef QList<QGraphicsItem*> MsgList;
	MsgList m_messageList;				//消息列表所有项
	QMap<int,MsgList>m_maplist;			//按类型分类存储
};
}