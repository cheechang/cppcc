#include "MessageTopWidget.h"
#include "common/controlptr.h"
#include "common/Connect.h"
#include "common/ChineseInfos.hpp"
#include "common/Common.h"
#include "log.h"
#include "json.h"
#include "../../../utils/common.h"
#include <QPushButton>
#include<qmessagebox.h>
#include <QAbstractScrollArea>
#include <QTextEdit>
#include <QScrollBar>
namespace ui {

	MsgListWidgetItem::MsgListWidgetItem(QWidget *parent) : QWidget(parent)
	{
		m_groupMbr = GROUPMGRCONTROL;
		m_chatMbr = CHATMGRCONTROL;
		init();

		CONNECT_SERVICE(GetTopUser(int, data::UserData&, data::ZxTopInformation&));
	}

	MsgListWidgetItem::~MsgListWidgetItem()
	{

	}

	void MsgListWidgetItem::setData(data::ZxTopInformation& msg, bool isCanopr)
	{
		m_msg = msg;
		std::string nameMark;
		std::string content;
		std::string jsoninfo = msg.topContent;
		Json::Reader  reader;
		Json::Value root;
		if (jsoninfo.find("{") == -1)
		{
			Log(LOG_LEV_ERROR, LOG_FILE, "topmsgJson=%s", jsoninfo.c_str());
			return;
		}
		bool ret = reader.parse(jsoninfo, root);
		if (!ret){
			Log(LOG_LEV_ERROR, LOG_FILE, "topmsgJson=%s", jsoninfo.c_str());
			return;
		}
		else{
			if (root.isMember("content"))
			{
				if (root["content"].isString())
				{
					content = root["content"].asString();
					//解析表情
					if (m_chatMbr){
						content = m_chatMbr->parceEmojiDeal(content);
					}
				}
			}
			if (root.isMember("name"))
			{
				if (root["name"].isString())
				{
					nameMark = root["name"].asString();
				}
			}
			if (root.isMember("jiebie"))
			{
				if (root["jiebie"].isString())
				{
					nameMark += "-" + root["jiebie"].asString();
				}
			}
		}
		m_lblTitle->setText(QString::fromUtf8(nameMark.c_str()) + transfer("的发言："));
		QString rescontent = QString::fromStdString(content.c_str()).trimmed();
		//rescontent = QString::fromLocal8Bit("传的是传的是是传的是的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的rttyuui传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的123a的是传的是传的是dfg是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是的是传的是传的是传的是传的是传的是传的wwqqasdfghjkmnnbbgg传的是传的是传dfgds爱上对方的发送到发送的法律发的发撒的按时打发第三方dd传的是传的是传的是传传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的rttyuui传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的传的是传的是传的是传传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的rttyuui传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的是传的fdsfsdfsdfdsf士大夫士大夫大幅度发送搭范德萨范德萨发三大发生的范德萨发生的范德萨额外热舞土卫二太热太热特威人体364665梵蒂冈发的好地方换个和规范化干得好的规划的后果的蝴蝶谷未发文二恶特然委托人为台湾人e23");
		m_msgBody->setText(rescontent);
		m_msgBody->setFixedWidth(380);
		m_msgBody->setStyleSheet("border:none;");
		m_msgBody->setReadOnly(true);
		m_btnDel->setEnabled(isCanopr);
		m_btnDel->setVisible(isCanopr);
	}

	int MsgListWidgetItem::getContentHigh()
	{
		bool isCalculateHeight = true;
		int fontH = m_msgBody->fontMetrics().height();
		int length = m_msgBody->toPlainText().length();
		int MaxWidth = m_msgBody->fontMetrics().width(m_msgBody->toPlainText().mid(0, 1600));
		int gheight = 0;
		int width = m_msgBody->fontMetrics().width(m_msgBody->toPlainText());
		int gmaxWidth = 0;
		if (width > MaxWidth)
		{
			isCalculateHeight = false;
			gmaxWidth = 370;
		}else {
			gmaxWidth = 380;
		}
		
		if (!isCalculateHeight)
		{
			width = MaxWidth;
		}

		if (width > gmaxWidth) {
			int rowcount = width / gmaxWidth;
			int dx = width % gmaxWidth;
			if (dx != 0) {
				rowcount += 1;
			}
			gheight = fontH * rowcount + 10;
		}
		else {
			gheight = fontH + 10;
		}		
		m_msgBody->resize(gheight, gmaxWidth);
		return gheight;
	}

	void MsgListWidgetItem::init()
	{
		m_lblTitle = CMakePtr<QLabel>(this);
		m_msgBody = CMakePtr<QTextEdit>(this);
		m_msgBody->setAcceptRichText(true);
		//m_msgBody->setWordWrap(true);
		//m_msgBody->adjustSize();

		m_btnDel = CMakePtr<QPushButton>(this);
		m_btnDel->setText(transfer("撤销置顶"));
		m_btnDel->setFixedSize(60,20);
		m_btnDel->setObjectName("appblueButton");
		m_btnDel->setCursor(Qt::PointingHandCursor);
		m_btnDel->setContentsMargins(0, 0, 0, 0);		

		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		QHBoxLayout* topTitleLayout = new QHBoxLayout(this);
		topTitleLayout->addWidget(m_lblTitle.get());
		topTitleLayout->addStretch();
		topTitleLayout->addWidget(m_btnDel.get());
		topTitleLayout->setContentsMargins(0,0,0,0);
		/*mainLayout->addWidget(m_btnDel.get(),0,Qt::AlignRight);
		mainLayout->addWidget(m_lblTitle.get(), 0, Qt::AlignLeft);*/
		mainLayout->addLayout(topTitleLayout);
		mainLayout->addWidget(m_msgBody.get(), 0, Qt::AlignLeft);
		mainLayout->setContentsMargins(20,10,20,10);
		this->setLayout(mainLayout);

		connect(m_btnDel.get(),SIGNAL(clicked()),this,SLOT(onCancelTopMessage()));
	}

	void MsgListWidgetItem::onCancelTopMessage()
	{
		emit signalSerCancelTopMsg(m_msg);
	}

	MessageTopWidget::MessageTopWidget(QWidget*parent) :BaseWindow(parent)
    {
		this->setTitle(transfer("置顶消息"));
		setFixedSize(450,600);
		mContactControl = CONTACTMGRCONTROL;
		m_groupMbr = GROUPMGRCONTROL;
		m_usercontrol = USERCONTROL;

		m_TopmessageList = new QListWidget(this);
		m_TopmessageList->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
		m_TopmessageList->setFixedSize(429,545);
		m_TopmessageList->setObjectName("whiteListWidget");

		m_TopmessageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		m_TopmessageList->setVerticalScrollMode(QListWidget::ScrollPerPixel);
		//m_TopmessageList->verticalScrollBar-setSingleStep(10);

		m_mainLayout = new QVBoxLayout(this);
		m_mainLayout->setContentsMargins(0,0,0,0);
		m_mainLayout->addWidget(m_TopmessageList);
		mMainLayout->addLayout(m_mainLayout);

		connect(this, SIGNAL(closeClicked()),this,SLOT(onClose()));
		CONNECT_SERVICE(cppccTopInfo(int, const std::string&, int64));
    }

	MessageTopWidget::~MessageTopWidget()
	{

	}

	void MessageTopWidget::onClose()
	{
		this->close();
		m_TopmessageList->clear();
	}

	void MessageTopWidget::addMsgItemToList()
	{

	}

	void MessageTopWidget::setEnableCancelTop(bool isCanOpr)
	{
		m_CanOpr = isCanOpr;
	}

	void MessageTopWidget::setTopMessage(std::vector<data::ZxTopInformation>& topMsgV)
	{
		for (int i = 0; i < topMsgV.size();i++)
		{
			MsgListWidgetItem* widget = new MsgListWidgetItem(this);
			widget->setData(topMsgV.at(i), m_CanOpr);
			QListWidgetItem* item = new QListWidgetItem();
			connect(widget, SIGNAL(signalSerCancelTopMsg(data::ZxTopInformation&)), this, SLOT(onSerCancelTopMsg(data::ZxTopInformation&)));
			int h = widget->getContentHigh();
			item->setSizeHint(QSize(420,h+70));
			m_TopmessageList->addItem(item);
			m_TopmessageList->setItemWidget(item,widget);
		}
	}

	void MessageTopWidget::onSerCancelTopMsg(data::ZxTopInformation& cancelMsg)
	{
		m_usercontrol->cppccTopInformation(cancelMsg, 7, CBind(&MessageTopWidget::signalSercppccTopInfo, this, CPlaceholders  _1, CPlaceholders  _2, cancelMsg.id));
	}

	void MessageTopWidget::onSercppccTopInfo(int code, const std::string& strError,int64 id)
	{
		if (code != 0){
			utils::Error::InitErrInfo(true);
			std::string error = utils::Error::GetErrMsg(code);
			QMessageBox::information(this, transfer("提示"), transfer(error.c_str()), transfer("确认"));
			return;
		}
		for (int i = 0; i < m_TopmessageList->count(); i++)
		{
			QListWidgetItem* item = m_TopmessageList->item(i);
			MsgListWidgetItem* widget = (MsgListWidgetItem*)m_TopmessageList->itemWidget(item);
			if (widget->getMsgId() == id)
			{
				if (widget != CNull)
				{
					delete widget;
					widget = CNull;
				}
				
				if (item != CNull)
				{
					delete item;
					item = CNull;
				}
				m_TopmessageList->removeItemWidget(item);
				return;
			}
		}
	}
}
