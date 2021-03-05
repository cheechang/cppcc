#include "GroupAtSelectListWidget.h"
#include <QListWidgetItem>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPainter>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>

#include <ui/controls/Label.h>
#include <ui/common/ChineseInfos.hpp>
#include <ui/common/Common.h>
#include <ui/common/ChineseInfos.hpp>
#include <ui/common/UIUtils.h>
#include <ui/controls/BaseQListWidget.h>
#include <ui/controls/AvatarWidget.h>
#include <ui/common/UIUtils.h>

namespace ui
{
	GroupAtSelectListWidget::GroupAtSelectListWidget(QWidget* parent)
		: QWidget(parent)
	{
		mGroupCtrl = nullptr;
		mChatCtrl = nullptr;
		mGroupId = 0;

		setWindowFlags(Qt::ToolTip);
		mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(0, 2, 2, 2); //框体边界距离（2020年8月26日）
		mainLayout->setSpacing(0);
		setLayout(mainLayout);

		mListWidget = new uicontrols::BaseQListWidget(this);
		mListWidget->setObjectName("groupAtList");
		connect(mListWidget,SIGNAL(signalSrcollToBottom()), this,SLOT(onLazyLoadMember()));

		QLabel* title = new QLabel(this);
		title->setText(TEXT_TIP_MSG_AT_TIP);
		title->setObjectName("groupAt");

		QLabel* lbl = new QLabel(this);
		lbl->setText(TEXT_TIP_MSG_AT_UP_DOWN);
		lbl->setObjectName("groupAt");

		QLabel* lbl1 = new QLabel(this);
		lbl1->setText(TEXT_TIP_MSG_AT_ENTER);
		lbl1->setObjectName("groupAt");

		QHBoxLayout* hlayout = new QHBoxLayout(this);
		hlayout->addWidget(title);
		hlayout->addStretch();
		hlayout->addWidget(lbl);
		hlayout->addWidget(lbl1);
		QWidget* widget = new QWidget(this);
		widget->setLayout(hlayout);
		widget->setFixedHeight(50 * gDdpi); //28（2020年8月26日）
		widget->setObjectName("groupAtTitle");

		mainLayout->addWidget(widget);
		mainLayout->addWidget(mListWidget);
		this->setFixedWidth(WIDTH + 40); //WIDTH（2020年8月26日）
		hide();
	}

	GroupAtSelectListWidget::~GroupAtSelectListWidget()
	{
	}

	void GroupAtSelectListWidget::showWin(int64 groupId, QPoint pos, QString regText)
	{
		mPos = pos;
		if (groupId != 0 && mGroupId != groupId)
		{
			if (mGroupCtrl == CNull)
			{
				mGroupCtrl = GROUPMGRCONTROL;
				CONNECT_SERVICE(GetGroupMems(QString, int, std::vector<CSharedPtr<data::Member>>&, int64));
			}
			if (mUserCtrl == CNull)
			{
				mUserCtrl = USERCONTROL;
			}
			m_reqLocalId = UIUtils::getLocalId();
			mGroupCtrl->GetMemberList(groupId,CBind(&GroupAtSelectListWidget::signalSerGetGroupMems, this, regText,
			                                        CPlaceholders _1,CPlaceholders _2, m_reqLocalId));
		}
		else
		{
			setData(mMems, regText);
		}
	}

	void GroupAtSelectListWidget::onSerGetGroupMems(QString regText, int code,
	                                                std::vector<CSharedPtr<data::Member>>& mems, int64 localId)
	{
		if (m_reqLocalId != localId || mMems.size() > 0)
		{
			return;
		}
		data::AccountInfo userInfor;
		userInfor = *mUserCtrl->GetAccountInfo().get();
		mUserId = userInfor.id.value();
		if (mems.size() > 0)
		{
			mGroupId = mems.at(0)->groupId.value();
			//全体成员
			MemberPtr allItem = CMakePtr<data::Member>();
			allItem->id = mGroupId;
			allItem->remark = TEXT_TIP106.toUtf8().data();
			allItem->thumbAvatar = DEFAULT_GROUP;
			mems.push_back(allItem);
			mMems = mems;
		}
		setData(mems, regText);
		this->setFocus();
	}

	void GroupAtSelectListWidget::clearData()
	{
		for (; mListWidget->count() > 0;)
		{
			QListWidgetItem* item = mListWidget->item(0);
			mListWidget->removeItemWidget(item);
			mListWidget->takeItem(0);
			if (item != CNull)
			{
				delete item;
			}
		}
		mListWidget->clear();
	}

	void GroupAtSelectListWidget::onItemClicked(QListWidgetItem* item)
	{
		makeImg(item);
		hide();
	}

	void GroupAtSelectListWidget::onItemClicked(int64 id)
	{
		if (id > 0)
		{
			for (int i = 0; i < mListWidget->count(); ++i)
			{
				QListWidgetItem* item = static_cast<QListWidgetItem*>(mListWidget->item(i));
				GroupAtWidgetItem* widget = static_cast<GroupAtWidgetItem*>(mListWidget->itemWidget(item));
				if (widget && widget->id() == id)
				{
					onItemClicked(item);
				}
			}
		}
		else
		{
			onItemClicked(mListWidget->currentItem());
		}
	}

	void GroupAtSelectListWidget::onKeyPressed(QEvent* event)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			int keyValue = keyEvent->key();
			if (keyValue == Qt::Key_Return || keyValue == Qt::Key_Enter)
			{
				this->setFocus();
				onItemClicked(mListWidget->currentItem());
			}
			else if (keyValue == Qt::Key_Backspace && isVisible())
			{
				hide();
			}
			else if (keyValue == Qt::Key_Up)
			{
				int index = mListWidget->currentRow() - 1;
				if (index >= 0)
				{
					mListWidget->setCurrentRow(index);
				}
			}
			else if (keyValue == Qt::Key_Down)
			{
				int index = mListWidget->currentRow() + 1;
				if (index < mListWidget->count())
				{
					mListWidget->setCurrentRow(index);
				}
				else
				{
					onLazyLoadMember();
				}
			}
		}
	}

	void GroupAtSelectListWidget::focusOutEvent(QFocusEvent*)
	{
		hide();
	}

	void GroupAtSelectListWidget::makeImg(QListWidgetItem* item)
	{
		if (item == CNull)
		{
			return;
		}
		GroupAtWidgetItem* widget = static_cast<GroupAtWidgetItem*>(mListWidget->itemWidget(item));
		QString fileName = QString::number(widget->id());
		//文件名加入成员名称和ID
		fileName = fileName + "@_" + widget->name();

		//转换
		QByteArray byteArr(fileName.toLocal8Bit());
		QString tempFileName = byteArr.toBase64();
		tempFileName.replace("/", "_"); //文件名不能有 / 符号，所有替换
		/////
		if (mChatCtrl == CNull)
		{
			mChatCtrl = CHATMGRCONTROL;
		}
		QString tempImagePath = QString::fromUtf8(mChatCtrl->userCachePath().c_str());
		tempImagePath = tempImagePath + tempFileName + ".png";

		QString imageText = "@" + widget->name();

		///////
		QFont font;
		font.setPointSize(9); //setPixelSize(10)改变右侧聊天标题字体大小2020-8-24

		QFontMetrics fm(font);
		int charWidth = fm.width(imageText);
		charWidth = fm.boundingRect(imageText).width();
		QSize size(charWidth + 8, 20); //17指定图片大小;

		QImage image(size, QImage::Format_ARGB32); //以ARGB32格式构造一个QImage,
		image.fill(qRgba(255, 255, 255, 0)); //填充图片背景,120/250为透明度

		QPainter painter(&image); //为这个QImage构造一个QPainter
		painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
		//设置画刷的组合模式CompositionMode_SourceOut这个模式为目标图像在上。
		//改变组合模式和上面的填充方式可以画出透明的图片。

		//改变画笔和字体
		QPen pen = painter.pen();
		pen.setColor(QColor(0, 141, 239));

		painter.setPen(pen);
		painter.setFont(font);

		painter.drawText(image.rect(), Qt::AlignCenter, imageText);
		//将名称写在Image的中心
		image.save(tempImagePath, "PNG", 100);

		emit memInfo(tempImagePath);
	}

	void GroupAtSelectListWidget::setData(std::vector<MemberPtr>& mems, QString& regText)
	{
		clearData();
		std::vector<MemberPtr> selMems;
		for (int i = mems.size() - 1; i >= 0; --i)
		{
			MemberPtr data = mems.at(i);

			if (data->id.value() == mUserId)
			{
				continue;
			}
			QString name = QString::fromUtf8(data->remark.value().c_str());
			if (name.isEmpty())
			{
				name = QString::fromUtf8(data->name.value().c_str());
			}
			if (!regText.isEmpty() && !name.contains(regText))
			{
				continue;
			}
			selMems.push_back(data);
		}
		//设置分页加载参数
		m_memberpage.setPageSize(8);
		m_memberpage.clearData();
		m_memberpage.setData(selMems);
		addItems();
		moveWinPos();
	}

	void GroupAtSelectListWidget::addItem(MemberPtr& data)
	{
		GroupAtWidgetItem* widget = new GroupAtWidgetItem(this);
		connect(widget,SIGNAL(clicked(int64)), this,SLOT(onItemClicked(int64)));

		QString name = QString::fromUtf8(data->remark.value().c_str());
		if (name.isEmpty())
		{
			name = QString::fromUtf8(data->name.value().c_str());
		}
		widget->setData(data->id.value(), name, transfer(data->thumbAvatar.value().c_str()));
		QListWidgetItem* item = new QListWidgetItem();
		item->setSizeHint(QSize(0, 30 * gDdpi));
		mListWidget->addItem(item);
		mListWidget->setItemWidget(item, widget);
	}

	void GroupAtSelectListWidget::addItems()
	{
		std::vector<MemberPtr> mems;
		m_memberpage.getPageData(mems);
		for (int i = 0; i < mems.size(); ++i)
		{
			addItem(mems.at(i));
		}
	}

	void GroupAtSelectListWidget::onLazyLoadMember()
	{
		if (m_memberpage.isLoadFinished())
		{
			m_memberpage.clearData();
			return;
		}
		addItems();
	}

	void GroupAtSelectListWidget::moveWinPos()
	{
		mListWidget->setCurrentRow(0);
		int height = mListWidget->count() * 50; //30(2020-8-25)
		if (height > Max_Height)
		{
			height = Max_Height;
		}
		mListWidget->setFixedHeight(height);
		this->setFixedSize(WIDTH + 40, height + 30 * gDdpi); //WIDTH,height + 28*gDdpi(2020-8-25)

		mPos.setY(mPos.y() - this->height() - 2);
		mPos.setX(mPos.x());
		QDesktopWidget* pDesktopWidget = QApplication::desktop();
		int wPos = mPos.x() + WIDTH;
		if (pDesktopWidget->width() < wPos)
		{
			wPos = pDesktopWidget->width() - WIDTH;
			mPos.setX(wPos);
		}
		this->move(mPos);

		if (mListWidget->count() > 0)
		{
			show();
			mListWidget->setFocus();
		}
		else
		{
			hide();
		}
		mListWidget->setFocus();
		emit dataFinish();
	}

	GroupAtWidgetItem::GroupAtWidgetItem(QWidget* parent): QWidget(parent)
	{
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(4 * gDdpi, 0, 0, 0);
		mWidget = new uicontrols::Label(this);
		m_pHead = new uicontrols::AvatarWidget(this, QSize(20 * gDdpi, 50 * gDdpi)); //h;20(2020-8-25)
		mWidget->setMinimumSize(136 * gDdpi, 50 * gDdpi); //h:30(2020-8-25)
		QWidget* circleWidget = new QWidget(this);
		circleWidget->setFixedSize(10 * gDdpi, 30 * gDdpi); //h;10(2020-8-25)
		circleWidget->setObjectName("groupAtPoint");
		mainLayout->addWidget(circleWidget);
		mainLayout->addWidget(m_pHead);
		mainLayout->addWidget(mWidget);
		mainLayout->addStretch();
		setLayout(mainLayout);
	}

	void GroupAtWidgetItem::setData(int64 id, QString name, QString avatar)
	{
		memId = id;
		mName = name;
		mWidget->setText(name);
		m_pHead->setAvatarPath(avatar);
	}

	int64 GroupAtWidgetItem::id()
	{
		return memId;
	}

	QString GroupAtWidgetItem::name()
	{
		return mName;
	}

	void GroupAtWidgetItem::mousePressEvent(QMouseEvent* e)
	{
		if (e->button() == Qt::LeftButton)
		{
			emit clicked(memId);
		}
		QWidget::mousePressEvent(e);
	}
}
