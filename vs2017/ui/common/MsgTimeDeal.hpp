#pragma once
#include <qstring.h>
#include <qmath.h>
#include <qdatetime.h>
#include "../utils/Error.h"

#define	  MSGDATETIME_TODAY	    (utils::Error::IsChinese() ? QString::fromLocal8Bit("HH:mm") :QString::fromLocal8Bit("HH:mm"))
#define	  MSGDATETIME_TODAY_CHAT	    (utils::Error::IsChinese() ? QString::fromLocal8Bit("HH:mm:ss") :QString::fromLocal8Bit("HH:mm:ss"))
#define	  MSGDATETIME_YESTERDAY  (utils::Error::IsChinese() ? QString::fromLocal8Bit("昨天") :QString::fromLocal8Bit("yesterday"))
#define	  MSGDATETIME_YESTERDAYAFTERNOON	(utils::Error::IsChinese() ? QString::fromLocal8Bit("前天") :QString::fromLocal8Bit("the day before yesterday"))
#define	  MSGDATETIME_LONGLONGAGO			(utils::Error::IsChinese() ? QString::fromLocal8Bit("MM-dd") :QString::fromLocal8Bit("MM-dd"))
#define	  MSGDATETIME_LONGLONGAGO_CHAT	   (utils::Error::IsChinese() ? QString::fromLocal8Bit("yyyy/MM/dd") :QString::fromLocal8Bit("yyyy/MM/dd"))

//type 1 会话列表时间 2聊天界面时间
inline QString DealMsgTime(qint64 msgtime,int type){
	QString strDateTime("");
	QDateTime msgDateTime;
	int distance = 0;
	if (!msgtime)
	{
		return strDateTime;
	}
	msgDateTime.setMSecsSinceEpoch(msgtime);
	distance = msgDateTime.daysTo(QDateTime::currentDateTime());
	//今天
	if (qFabs(distance) <= 0)
	{
		if ( 1 == type)
		{
		  strDateTime = msgDateTime.toString(MSGDATETIME_TODAY);
		}
		else{
		  strDateTime = msgDateTime.toString(MSGDATETIME_TODAY_CHAT);
		}
	}
	//昨天
	else if (qFabs(distance) <= 1)
	{
		if ( 1 == type)
		{
			strDateTime = MSGDATETIME_YESTERDAY;
		}
		else {
			strDateTime = msgDateTime.toString(MSGDATETIME_LONGLONGAGO_CHAT) +QString::fromLocal8Bit(" ")+msgDateTime.toString(MSGDATETIME_TODAY_CHAT);
		}

	}
	//前天
	else if (qFabs(distance) <= 2)
	{
		if (1 == type)
		{
			strDateTime = MSGDATETIME_YESTERDAYAFTERNOON;
		}
		else {
			strDateTime = msgDateTime.toString(MSGDATETIME_LONGLONGAGO_CHAT) +QString::fromLocal8Bit(" ")+msgDateTime.toString(MSGDATETIME_TODAY_CHAT);
		}
	}
	else
	{
		if (1 == type)
		{
			strDateTime = msgDateTime.toString(MSGDATETIME_LONGLONGAGO);
		}
		else {
			strDateTime = msgDateTime.toString(MSGDATETIME_LONGLONGAGO_CHAT) +QString::fromLocal8Bit(" ")+msgDateTime.toString(MSGDATETIME_TODAY_CHAT);
		}
	}
	return strDateTime;
}
