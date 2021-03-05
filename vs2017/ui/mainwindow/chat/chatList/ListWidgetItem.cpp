#include "ListWidgetItem.h"
#include "controls/headimage.h"
#include "controls/PushButton.h"
#include "controls/UnreadMsgLabel.h"
#include "controls/ToolButton.h"
#include "common/Common.h"

namespace ui
{
	ListWidgetItem::ListWidgetItem(int64 targetId, QWidget* parent) : QWidget(parent)
	{
		this->setMouseTracking(true);
		mTargetId = targetId;
		mUnreadCount = 0;
		init();
	}

	void ListWidgetItem::init()
	{
		m_btnDel = CMakePtr<PushButton>(this);
		m_lblTitle = CMakePtr<QLabel>(this);

		{
			QFont font;
			font.setFamily("Microsoft YaHei");
			//font.setPointSize(10);//自适应大小
			font.setPixelSize(13);//固定大小
			font.setWeight(50); //会话列表标题大小QFont font("Microsoft YaHei", 12, 50);
			m_lblTitle->setFont(font); //8-7
		}

		//TODO：增加m_lblTittle、m_lblTime、m_lblLasMsg窗体的高度
		m_lblLasMsg = CMakePtr<QLabel>(this);//最新消息摘要
		m_lblTime = CMakePtr<QLabel>(this);//最新消息时间
		m_head = CMakePtr<HeadImage>(this, QSize(HEAD_SIZE,HEAD_SIZE ));//HEAD_SIZE,HEAD_SIZE（2020年8月27日）//消息标签图标大小
		m_lblUnreadMsg = CMakePtr<UnreadMsgLabel>(this);//未读消息标签
		mMsgTime = 0;//时间初始化
		m_btnDel->setPicName(":/chat/delete");
		m_btnDel->setToolTip(transfer("删除会话"));
		m_btnDel->setVisible(false);//默认不可见
		connect(m_btnDel.get(),SIGNAL(clicked(bool)), this,SLOT(onClicked(bool)));//鼠标触发事件
		//m_lblTitle->setMaximumWidth(200); //200（2020-8-24）//标签标题最大宽度？？设置无效？？
		//m_lblTitle->setMaximumHeight(100); //80（2020-8-27）

		//m_lblTitle->setMaximumWidth(150);
		QPalette color;
		color.setColor(QPalette::Text, Qt::gray);//文本颜色
		m_lblLasMsg->setPalette(color);
		m_lblLasMsg->setMaximumWidth(180); //180(2020-8-24)//
		m_lblLasMsg->setMaximumHeight(80); //80（2020年8月27日）

		//m_lblLasMsg->setMaximumWidth(180);
		m_lblTime->setPalette(color);


		m_lblChatTop = CMakePtr<ToolButton>(":/chat/chat-top", this, false);
		m_lblChatTop->setSize(QSize(30, 30)); //25,25（2020年8月25日）
		//m_lblChatTop->move(-15,-15);
		m_lblChatTop->setVisible(true); //false

		m_lblNotDisturb = CMakePtr<ToolButton>(":/chat/notDisturb", this, false);
		m_lblNotDisturb->setSize(QSize(18, 18)); //12,12
		m_lblNotDisturb->move(180, 10);
		m_lblNotDisturb->setVisible(false);

		mainLayout = CMakePtr<QGridLayout>();
		mainLayout->setHorizontalSpacing(2);
		mainLayout->addWidget(m_head.get(), 0, 0, 2, 1, Qt::AlignVCenter);//消息头，居中
		mainLayout->addWidget(m_lblTitle.get(), 0, 1, 1, 1);//消息标题
		mainLayout->addWidget(m_lblTime.get(), 0, 2, 1, 1, Qt::AlignRight);//消息时间，右对齐
		mainLayout->addWidget(m_lblLasMsg.get(), 1, 1, 1, 1);//最新消息
		mainLayout->addWidget(m_lblUnreadMsg.get(), 1, 2, 1, 1, Qt::AlignRight);//未读消息红点，右对齐
		mainLayout->addWidget(m_btnDel.get(), 1, 2, 1, 1, Qt::AlignRight);//删除消息button（与未读重叠）

		setLayout(mainLayout.get());
		//设置支持拖拽
		setSupportStretch(true);
	}

	void ListWidgetItem::setData(QString strTitle, QString strLastMsg, QString strTime, QString strHeadPath,
	                             QString unreadMsg, int count, bool isShowAtTip)
	{
		if (mTargetId == 10000)
		{
			strTitle = transfer("系统消息");
			strHeadPath = ":/base/sysMsg";
			strLastMsg = "";
		}
		m_lblTime->setText(strTime);
		m_head->setAvatarPath(strHeadPath);
		m_lblUnreadMsg->setText(unreadMsg);

		QFont ft = m_lblLasMsg->font();
		QFontMetrics fm(ft);
		QString atTip = transfer("<font color=red>[有人@我]</font>");
		int textWidth = isShowAtTip ? 80 : 135;
		QString textformat = fm.elidedText(strLastMsg, Qt::ElideRight, textWidth);
		if (!isShowAtTip)
		{
			atTip = "";
		}
		m_lblLasMsg->setText(atTip + textformat);
		m_lblLasMsg->setToolTip(strLastMsg);

		QString texttitle = fm.elidedText(strTitle, Qt::ElideRight, textWidth );//textWidth - 10 文本省略显示（2020年8月26日）
		m_lblTitle->setText(texttitle);
		m_lblTitle->setToolTip(strTitle);
		mUnreadCount = count;
		showUnreadMsg();
	}

	void ListWidgetItem::enterEvent(QEvent* e)
	{
		m_btnDel->setVisible(true);
		m_lblUnreadMsg->setVisible(false);
		e->accept();
	}

	void ListWidgetItem::leaveEvent(QEvent* e)
	{
		if (m_btnDel != CNull)
		{
			m_btnDel->setVisible(false);
			showUnreadMsg();
		}
		e->accept();
	}

	void ListWidgetItem::onClicked(bool isClick)
	{
		emit signalDelItem(mTargetId);
	}

	void ListWidgetItem::showUnreadMsg()
	{
		if (m_lblUnreadMsg->text().isEmpty() || m_lblUnreadMsg->text() == "0")
		{
			m_lblUnreadMsg->setVisible(false);
		}
		else
		{
			m_lblUnreadMsg->setVisible(true);
		}
	}

	void ListWidgetItem::setUnreadCount(QString unreadMsg)
	{
		if (unreadMsg.isEmpty())
		{
			mUnreadCount = 0;
			QString atTip = transfer("<font color=red>[有人@我]</font>");
			if (m_lblLasMsg->text().contains(atTip))
			{
				int textWidth = 150;//135（2020年9月1日）
				QFont ft = m_lblLasMsg->font();
				QFontMetrics fm(ft);
				QString strLastMsg = m_lblLasMsg->toolTip();
				QString textformat = fm.elidedText(strLastMsg, Qt::ElideRight, textWidth);
				m_lblLasMsg->setText(textformat);
			}
		}
		else
		{
			mUnreadCount = unreadMsg.toInt();
		}
		m_lblUnreadMsg->setText(unreadMsg);
		showUnreadMsg();
	}

	void ListWidgetItem::updateHead(QString head)
	{
		m_head->setAvatarPath(head);
	}

	void ListWidgetItem::updateName(QString name)
	{
		m_lblTitle->setText(name);
	}

	void ListWidgetItem::setSupportStretch(bool isSupportStretch)
	{
		this->setMouseTracking(isSupportStretch);
		// 这里对子控件也进行了设置，是因为如果不对子控件设置，当鼠标移动到子控件上时，不会发送mouseMoveEvent事件，也就获取不到当前鼠标位置，无法判断鼠标状态及显示样式了。
		QList<QWidget*> widgetList = this->findChildren<QWidget*>();
		for each (QWidget* widget in widgetList)
		{
			widget->setMouseTracking(isSupportStretch);
		}
	}

	void ListWidgetItem::mousePressEvent(QMouseEvent* event)
	{
		if (event->button() == Qt::LeftButton)
		{
			emit signalClicked(mTargetId);
			QWidget::mousePressEvent(event);
		}
		else
		{
			event->accept();
		}
	}

	void ListWidgetItem::setChatTop(bool isTop)
	{
		m_lblChatTop->setVisible(isTop);
	}

	void ListWidgetItem::setNotDisturb(bool isDisturb)
	{
		m_lblNotDisturb->setVisible(isDisturb);
	}

	int64 ListWidgetItem::msgTime()
	{
		return mMsgTime;
	}

	void ListWidgetItem::setMsgTime(int64 time)
	{
		mMsgTime = time;
	}
}
