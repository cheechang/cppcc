#include "MsgFactory.h"
#include "data/ChatData.h"
#include "richtextmessagewidget.h"
#include "filemessagewidget.h"
#include "gifmessagewidget.h"
#include "tipmessagewidget.h"
#include "pictextmessagewidget.h"
#include "templatemessagewidget.h"
#include "webmessagewidget.h"
#include "CardMessageWidget.h"
#include "MiniVedioMessageWidget.h"
#include "BurnMessageWidget.h"
#include "MsgBubbleConfig.h"
#include "msgtimeitem.h"
#include "detail/flexmessagewidget.h"
#include "PrivateChatmessageWidget.h"
#include "RecordMessageWidget.h"
#include "CombineMessageWidget.h"
#include "NineBlockMessageWidget.h"
//#include "MsgMiniVedioPlayer.h"
#include <QFileInfo>
MsgFactory::MsgFactory(){

}
MsgFactory::~MsgFactory(){

}
AbstractMessageWidget* MsgFactory::GetMessageWidget(CSharedPtr<data::Msg>&msg){
	AbstractMessageWidget* abstmsgwidget = CNull;
	
	QColor textclr;

	if ( CNull == msg) return abstmsgwidget;
	//根据类型构造消息widget
	if(1 == msg->isPrivateMsg)
	{
		if(msg->isRecvMsg)
		{
			abstmsgwidget = new ui::PrivateChatmessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<ui::PrivateChatmessageWidget*>(abstmsgwidget)->setTip(msg);
		}
	}
	else
	{
	switch(msg->msgType){
	case data::MSG_TYPE_COMBINE:
		{
			abstmsgwidget = new CombineMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<CombineMessageWidget*>(abstmsgwidget)->setCombineMsg(msg);
			break;
		}
	case MSG_TYPE_TASK:
		{
			abstmsgwidget = new RichTextMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			textclr = msg->isRecvMsg?MsgBubbleConfig::otherTextColor():MsgBubbleConfig::selfTextColor();
			qobject_cast<RichTextMessageWidget*>(abstmsgwidget)->setTextColor(textclr);
			qobject_cast<RichTextMessageWidget*>(abstmsgwidget)->setText(msg);
			break;
		}
	case MSG_TYPE_NINEBLOCK:
		{
			abstmsgwidget = new NineBlockMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<NineBlockMessageWidget*>(abstmsgwidget)->setNineBlockMsg(msg);
			break;
		}
	case data::MSG_TYPE_DYNEXPRESSION:
	{
			abstmsgwidget = new GifMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<GifMessageWidget*>(abstmsgwidget)->setDnyMsg(msg);
			break;
	}
	case data::MSG_TYPE_WEB:
		{
			abstmsgwidget = new WebMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<WebMessageWidget*>(abstmsgwidget)->setWebMsg(msg);
			break;
		}
	case data::MSG_TYPE_CARD:
		{
			if (msg->isBurn && msg->isRecvMsg)
			{
				abstmsgwidget = new BurnMessageWidget();
				abstmsgwidget->InitMsg(msg, abstmsgwidget);
				qobject_cast<BurnMessageWidget*>(abstmsgwidget)->setBurnMsg(msg);
			}
			else{
				abstmsgwidget = new CardMessageWidget();
				abstmsgwidget->InitMsg(msg, abstmsgwidget);
				qobject_cast<CardMessageWidget*>(abstmsgwidget)->setCardMsg(msg);
			}
			
			break;
		}
	case data::MSG_TYPE_TEXT:
		{
			if (msg->isBurn && msg->isRecvMsg)
			{
				abstmsgwidget = new BurnMessageWidget();
				abstmsgwidget->InitMsg(msg,abstmsgwidget);
				qobject_cast<BurnMessageWidget*>(abstmsgwidget)->setBurnMsg(msg);
				
			}else{
				abstmsgwidget = new RichTextMessageWidget();
				abstmsgwidget->InitMsg(msg,abstmsgwidget);
				textclr = msg->isRecvMsg?MsgBubbleConfig::otherTextColor():MsgBubbleConfig::selfTextColor();
				qobject_cast<RichTextMessageWidget*>(abstmsgwidget)->setTextColor(textclr);
				qobject_cast<RichTextMessageWidget*>(abstmsgwidget)->setText(msg);
			}
			
			break;
		}
	case data::MSG_TYPE_AUDIO:
		{
			data::MsgAudio* imgMsg = static_cast<data::MsgAudio*>(msg.get());
			if (msg->isBurn && msg->isRecvMsg)
			{
				abstmsgwidget = new BurnMessageWidget();
				abstmsgwidget->InitMsg(msg,abstmsgwidget);
				qobject_cast<BurnMessageWidget*>(abstmsgwidget)->setBurnMsg(msg);
			}
			else
			{
				abstmsgwidget = new RecordMessageWidget();
				abstmsgwidget->InitMsg(msg,abstmsgwidget);
				qobject_cast<RecordMessageWidget*>(abstmsgwidget)->SetRecordMsg(msg);
			}

			break;
		}
	case data::MSG_TYPE_MINIVEDIO:
		{
			abstmsgwidget = new ui::MiniVedioMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<ui::MiniVedioMessageWidget*>(abstmsgwidget)->SetMsg(msg);
			break;
		}
	case data::MSG_TYPE_IMG:
		{
			data::MsgImg* imgMsg = static_cast<data::MsgImg*>(msg.get());
			if (msg->isBurn && msg->isRecvMsg)
			{
				abstmsgwidget = new BurnMessageWidget();
				abstmsgwidget->InitMsg(msg,abstmsgwidget);
				qobject_cast<BurnMessageWidget*>(abstmsgwidget)->setBurnMsg(msg);

			}else{
				abstmsgwidget = new ImageMessageWidget();
				abstmsgwidget->InitMsg(msg,abstmsgwidget);
				qobject_cast<ImageMessageWidget*>(abstmsgwidget)->setImage(msg);
			}
			
			break;
		}
	case data::MSG_TYPE_FILE:
		{
			abstmsgwidget = new FileMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<FileMessageWidget*>(abstmsgwidget)->setFile(msg);
			break;
		}
	case data::MSG_TYPE_TIP:
		{
			abstmsgwidget = new TipMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<TipMessageWidget*>(abstmsgwidget)->setTip(msg);
			break;
		}
	case data::MSG_TYPE_PICTEXT:
		{
			abstmsgwidget = new PicTextMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<PicTextMessageWidget*>(abstmsgwidget)->setPicText(msg);
			break;
		}
	case data::MSG_TYPE_TEMPL:
		{
			abstmsgwidget = new TemplateMessageWidget();
			abstmsgwidget->InitMsg(msg,abstmsgwidget);
			qobject_cast<TemplateMessageWidget*>(abstmsgwidget)->setTemplate(msg);
			break;
		}
	default:
		{
			break;
		}
	}
}
	return abstmsgwidget;
}
QGraphicsTextItem* MsgFactory::GetMessageTimeWidget(QString strtime){
	QGraphicsTextItem* timeItem = CNull;
	timeItem = new MsgTimeItem();
	timeItem->setDefaultTextColor(QColor(128, 128, 128));
	timeItem->setPlainText(strtime);
	return timeItem;
}
FlexMessageWidget* MsgFactory::GetFlexMessageWidget(AbstractMessageWidget*&absmsg){
	FlexMessageWidget* flexMsg = CNull;
	bool alinLeft  = false;
	QString avatar("");
	QString name("");

	if(CNull == absmsg)return flexMsg;
	/// alinLeft = absmsg->isRecv() || absmsg->isDevice()?true:false;
	alinLeft = absmsg->isRecv() ?true:false;  // 2019-5-24 bxy change
	avatar   = absmsg->avatar();
	name     = absmsg->name();
	flexMsg = new FlexMessageWidget(alinLeft);
	flexMsg->setMessageWidget(absmsg);
	flexMsg->setAvatar(avatar);
	flexMsg->setName(absmsg->isRecv()?name:"");
	return flexMsg;
}
