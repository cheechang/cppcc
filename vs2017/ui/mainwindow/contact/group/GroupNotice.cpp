#include <QCoreApplication>

#include "GroupNotice.h"
#include "GroupNoticeItem.h"
#include "common/Connect.h"
#include "common/Common.h"
#include <QFileInfo>
#include <QRgb>

const int MAXLENGTH = 200;
namespace ui
{
	GroupNotice::GroupNotice(QWidget *parent)
		: TWidget(parent)
		, m_groupId(0)
	{
		QPalette palette;
		palette.setColor(QPalette::Window,QColor(235,242,249));

		m_pGroupControl = GROUPMGRCONTROL;
		m_NoticeStackWidget = new QStackedWidget(this);
		m_NoticeStackWidget->setFixedHeight(225);
		m_pListWidget = new QListWidget(this);
		m_pListWidget->setFixedHeight(200);
		m_NoticeEditWidget = new QWidget(this);
		m_NoticeLayout = new QVBoxLayout(this);
		m_NoticeBtnLayout = new QHBoxLayout(this);

		m_tipInfo = new QLabel(this);
		m_tipInfo->setObjectName("redlabel");
		m_tipInfo->setVisible(false);
		m_tipInfo->setFixedWidth(200);

		m_tipInfo->setText(transfer("输入已超过最大字数限制"));
		m_tipInfo->move(75,190);

		m_NoticeTextEdit = new QTextEdit(m_NoticeEditWidget);
		m_NoticeTextEdit->setFixedHeight(180);

		m_NoticeBtn = new QPushButton(m_NoticeEditWidget);
		m_NoticeBtn->setText(transfer("发 布"));
		m_NoticeBtn->setFixedSize(80, 25);
		m_NoticeBtn->setObjectName("NoticeOkBtn");
		m_CancelNoticeBtn = new QPushButton(m_NoticeEditWidget);
		m_CancelNoticeBtn->setText(transfer("取 消"));
		m_CancelNoticeBtn->setFixedSize(80, 25);
		m_CancelNoticeBtn->setObjectName("NoticeCancelBtn");

		m_NoticeBtnLayout->addWidget(m_NoticeBtn);
		m_NoticeBtnLayout->addWidget(m_CancelNoticeBtn);

		m_NoticeLayout->addWidget(m_NoticeTextEdit);
		m_NoticeLayout->addLayout(m_NoticeBtnLayout);
		m_NoticeLayout->setContentsMargins(2,0,0,5);
		m_NoticeLayout->addStretch();
		m_NoticeEditWidget->setLayout(m_NoticeLayout);

		m_NoticeStackWidget->addWidget(m_pListWidget);
		m_NoticeStackWidget->addWidget(m_NoticeEditWidget);
		m_NoticeStackWidget->setCurrentWidget(m_pListWidget);

		m_pMainLayout = new QVBoxLayout(this);
		m_FuncLayout = new QHBoxLayout(this);
		m_PushNoticebtn = new QPushButton(this);
		m_NoticeExPlainLab = new QLabel(this);

		m_NoticeExPlainLab->setText(transfer("本群须知给朋友说点什么吧..."));
		m_PushNoticebtn->setText(transfer("发布公告"));
		m_PushNoticebtn->setFixedSize(60,20);
		m_PushNoticebtn->setObjectName("PushNotice");
		
		m_FuncLayout->addWidget(m_NoticeExPlainLab);
		m_FuncLayout->addStretch();
		m_FuncLayout->addWidget(m_PushNoticebtn);
		m_FuncLayout->setContentsMargins(10,0,10,0);

		Funcwidget = new QWidget(this);
		Funcwidget->setFixedHeight(30);
		Funcwidget->setObjectName("GroupNoticeTip");
		Funcwidget->setLayout(m_FuncLayout);

		m_pMainLayout->addWidget(Funcwidget);
		m_pMainLayout->addWidget(m_NoticeStackWidget);
		m_pMainLayout->addStretch();
		this->setLayout(m_pMainLayout);
		setObjectName("bg_fa");

		mlblBg = new QLabel(this);
		mlblBg->setPixmap(QPixmap(":/base/default"));
		mlblBg->setVisible(false);
		mlblBg->setFixedSize(160,160);
		mlblBg->move(160,80);

		connect(m_PushNoticebtn,SIGNAL(clicked()), this, SLOT(onSerPushNotice()));
		connect(m_NoticeBtn,SIGNAL(clicked()), this, SLOT(onSerNoticeBtn()));
		connect(m_CancelNoticeBtn,SIGNAL(clicked()), this, SLOT(onSerCancelNoticeBtn()));
		connect(m_NoticeTextEdit, SIGNAL(textChanged()), this, SLOT(onMaxChatCheck()));
		CONNECT_SERVICE(NoticePushResult(int));
	}

	GroupNotice::~GroupNotice()
	{
	}

	void GroupNotice::onMaxChatCheck()
	{
		QString textContent = m_NoticeTextEdit->toPlainText();

		int length = textContent.count();

		int maxLength = MAXLENGTH; // 最大字符数
		
		if (length > maxLength)
		{
			int position = m_NoticeTextEdit->textCursor().position();

			QTextCursor textCursor = m_NoticeTextEdit->textCursor();

			textContent.remove(position - (length - maxLength), length - maxLength);

			m_NoticeTextEdit->setText(textContent);

			textCursor.setPosition(position - (length - maxLength));

			m_NoticeTextEdit->setTextCursor(textCursor);
			m_tipInfo->setVisible(true);

		}
		else{
			m_tipInfo->setVisible(false);
		}
	}

	void GroupNotice::updateData(int64 groupId)
	{
		m_groupId = groupId;
		if(m_pGroupControl != CNull)
		{
			clearList();
			data::Group groupdata;
			m_pGroupControl->GetGroupInfo(m_groupId, groupdata);
			if(isGroupOwner())
			{
				Funcwidget->setVisible(true);
			}
			else
			{
				Funcwidget->setVisible(false);
			}
			if(groupdata.bulletin.value() == "")
			{
				return ;
			}
			addItemToList(groupdata);
		}
	}

	void GroupNotice::clearList()
	{
		for (int i=0;i<m_pListWidget->count();i++)
		{
			QListWidgetItem* item = m_pListWidget->item(i);
			QWidget* widget = m_pListWidget->itemWidget(item);
			m_pListWidget->removeItemWidget(item);
			if(item != CNull){
				delete item;
			}
			if(widget != CNull){
				delete widget;
			}
			QCoreApplication::processEvents();
		}
	}

	int GroupNotice::addItemToList(const data::Group& pGroupInfo)
	{
		QListWidgetItem* item = new QListWidgetItem();
		GroupNoticeItem* widget = new GroupNoticeItem(this);	
		widget->setData(pGroupInfo);

		if (m_userinfo->id.value() == pGroupInfo.info.value().createrId.value()) {
			widget->setNominition(m_userinfo->name.value());
		}
		else {
			widget->setNominition(transfer("群主").toUtf8().data());
		}
		//widget->setNominition(m_userinfo->name.value());
		item->setSizeHint(QSize(400, widget->getContentHigh()+55));
		m_pListWidget->addItem(item);
		m_pListWidget->setItemWidget(item, widget);
		return m_pListWidget->row(item);
	}


	bool GroupNotice::isGroupOwner()
	{
		CSharedPtr<control::IUserControl> userControl = USERCONTROL;
		if(userControl){
			m_userinfo = userControl->GetAccountInfo();
		}

		if(m_pGroupControl)
		{
			data::Member self, mem;
			bool ret = m_pGroupControl->GetMemberInfo(m_groupId,  m_userinfo->id.value(), self);
			if (ret){
				if (self.memberType.value() == 3 || self.memberType.value() == 2)
				{
					return true;
				}
				else
				{
					return false;
				}
			}else{
				if (!ret){
					CONNECT_SERVICE(GetGroupMem(int, data::Member&));
					m_pGroupControl->getGroupMemberFromNet(m_groupId, m_userinfo->id.value(),
						CBind(&GroupNotice::signalSerGetGroupMem, this,
						std::placeholders::_1, std::placeholders::_2));
				}
				return false;
			}
		}
	}

	void GroupNotice::onSerGetGroupMem(int code, data::Member& mem){
		if (mem.groupId.value() == m_groupId){
			if (mem.memberType.value() == 2 || mem.memberType.value() == 3){
				Funcwidget->setVisible(true);
			}
			else{
				Funcwidget->setVisible(false);
			}
		}
	}

	int GroupNotice::insertItemToList(const data::Group& pGroupInfo)
	{
		QListWidgetItem* item = new QListWidgetItem();
		GroupNoticeItem* widget = new GroupNoticeItem(this);

		widget->setData(pGroupInfo);
		m_pListWidget->insertItem(0,item);
		m_pListWidget->setItemWidget(item, widget);
		return m_pListWidget->row(item);
	}

	void GroupNotice::onSerPushNotice()
	{
		m_NoticeTextEdit->clear();
		m_NoticeStackWidget->setCurrentWidget(m_NoticeEditWidget);
	}

	void GroupNotice::onSerCancelNoticeBtn()
	{
		m_NoticeTextEdit->clear();
		m_NoticeStackWidget->setCurrentWidget(m_pListWidget);
	}

	void GroupNotice::setBtnEnble(bool isEnble)
	{
		m_NoticeBtn->setEnabled(isEnble);
		m_CancelNoticeBtn->setEnabled(isEnble);
	}

	void GroupNotice::onSerNoticeBtn()
	{
		m_tipInfo->setVisible(false);
		data::GroupUpdate date;
		std::string NoticeContent = m_NoticeTextEdit->toPlainText().toUtf8().data();
		if (NoticeContent == "")
		{
			return;
		}

		date.groupBulletin = NoticeContent;
		if (m_pGroupControl)
		{
			setBtnEnble(false);
			m_pGroupControl->SetGroupInfo(m_groupId, date, std::bind(&GroupNotice::signalSerNoticePushResult, this, std::placeholders::_1));
		}
	}

	void GroupNotice::onSerNoticePushResult(int error)
	{
		setBtnEnble(true);
		if(!error)
		{
			updateData(m_groupId);
			m_NoticeStackWidget->setCurrentWidget(m_pListWidget);
		}
		return ;
	}
}