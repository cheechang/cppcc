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
			//font.setPointSize(10);//����Ӧ��С
			font.setPixelSize(13);//�̶���С
			font.setWeight(50); //�Ự�б�����СQFont font("Microsoft YaHei", 12, 50);
			m_lblTitle->setFont(font); //8-7
		}

		//TODO������m_lblTittle��m_lblTime��m_lblLasMsg����ĸ߶�
		m_lblLasMsg = CMakePtr<QLabel>(this);//������ϢժҪ
		m_lblTime = CMakePtr<QLabel>(this);//������Ϣʱ��
		m_head = CMakePtr<HeadImage>(this, QSize(HEAD_SIZE,HEAD_SIZE ));//HEAD_SIZE,HEAD_SIZE��2020��8��27�գ�//��Ϣ��ǩͼ���С
		m_lblUnreadMsg = CMakePtr<UnreadMsgLabel>(this);//δ����Ϣ��ǩ
		mMsgTime = 0;//ʱ���ʼ��
		m_btnDel->setPicName(":/chat/delete");
		m_btnDel->setToolTip(transfer("ɾ���Ự"));
		m_btnDel->setVisible(false);//Ĭ�ϲ��ɼ�
		connect(m_btnDel.get(),SIGNAL(clicked(bool)), this,SLOT(onClicked(bool)));//��괥���¼�
		//m_lblTitle->setMaximumWidth(200); //200��2020-8-24��//��ǩ��������ȣ���������Ч����
		//m_lblTitle->setMaximumHeight(100); //80��2020-8-27��

		//m_lblTitle->setMaximumWidth(150);
		QPalette color;
		color.setColor(QPalette::Text, Qt::gray);//�ı���ɫ
		m_lblLasMsg->setPalette(color);
		m_lblLasMsg->setMaximumWidth(180); //180(2020-8-24)//
		m_lblLasMsg->setMaximumHeight(80); //80��2020��8��27�գ�

		//m_lblLasMsg->setMaximumWidth(180);
		m_lblTime->setPalette(color);


		m_lblChatTop = CMakePtr<ToolButton>(":/chat/chat-top", this, false);
		m_lblChatTop->setSize(QSize(30, 30)); //25,25��2020��8��25�գ�
		//m_lblChatTop->move(-15,-15);
		m_lblChatTop->setVisible(true); //false

		m_lblNotDisturb = CMakePtr<ToolButton>(":/chat/notDisturb", this, false);
		m_lblNotDisturb->setSize(QSize(18, 18)); //12,12
		m_lblNotDisturb->move(180, 10);
		m_lblNotDisturb->setVisible(false);

		mainLayout = CMakePtr<QGridLayout>();
		mainLayout->setHorizontalSpacing(2);
		mainLayout->addWidget(m_head.get(), 0, 0, 2, 1, Qt::AlignVCenter);//��Ϣͷ������
		mainLayout->addWidget(m_lblTitle.get(), 0, 1, 1, 1);//��Ϣ����
		mainLayout->addWidget(m_lblTime.get(), 0, 2, 1, 1, Qt::AlignRight);//��Ϣʱ�䣬�Ҷ���
		mainLayout->addWidget(m_lblLasMsg.get(), 1, 1, 1, 1);//������Ϣ
		mainLayout->addWidget(m_lblUnreadMsg.get(), 1, 2, 1, 1, Qt::AlignRight);//δ����Ϣ��㣬�Ҷ���
		mainLayout->addWidget(m_btnDel.get(), 1, 2, 1, 1, Qt::AlignRight);//ɾ����Ϣbutton����δ���ص���

		setLayout(mainLayout.get());
		//����֧����ק
		setSupportStretch(true);
	}

	void ListWidgetItem::setData(QString strTitle, QString strLastMsg, QString strTime, QString strHeadPath,
	                             QString unreadMsg, int count, bool isShowAtTip)
	{
		if (mTargetId == 10000)
		{
			strTitle = transfer("ϵͳ��Ϣ");
			strHeadPath = ":/base/sysMsg";
			strLastMsg = "";
		}
		m_lblTime->setText(strTime);
		m_head->setAvatarPath(strHeadPath);
		m_lblUnreadMsg->setText(unreadMsg);

		QFont ft = m_lblLasMsg->font();
		QFontMetrics fm(ft);
		QString atTip = transfer("<font color=red>[����@��]</font>");
		int textWidth = isShowAtTip ? 80 : 135;
		QString textformat = fm.elidedText(strLastMsg, Qt::ElideRight, textWidth);
		if (!isShowAtTip)
		{
			atTip = "";
		}
		m_lblLasMsg->setText(atTip + textformat);
		m_lblLasMsg->setToolTip(strLastMsg);

		QString texttitle = fm.elidedText(strTitle, Qt::ElideRight, textWidth );//textWidth - 10 �ı�ʡ����ʾ��2020��8��26�գ�
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
			QString atTip = transfer("<font color=red>[����@��]</font>");
			if (m_lblLasMsg->text().contains(atTip))
			{
				int textWidth = 150;//135��2020��9��1�գ�
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
		// ������ӿؼ�Ҳ���������ã�����Ϊ��������ӿؼ����ã�������ƶ����ӿؼ���ʱ�����ᷢ��mouseMoveEvent�¼���Ҳ�ͻ�ȡ������ǰ���λ�ã��޷��ж����״̬����ʾ��ʽ�ˡ�
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
