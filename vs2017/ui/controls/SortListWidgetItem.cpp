#include "SortListWidgetItem.h"
#include "SortListWidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include <qevent.h>
#include <log/log.h>
#include <ui/common/ChineseInfos.hpp>
#include <ui/common/Common.h>
#include <AvatarWidget.h>
#include <Label.h>
#include <RadioButton.h>
#include <IconButton.h>


namespace uicontrols
{
	SortListWidgetItem::SortListWidgetItem(int type, QWidget* parent)
		: TWidget(parent), m_onlineStatus(4), m_IsDelBtnShow(true), m_isCanDel(true)
	{
		this->setAttribute(Qt::WA_DeleteOnClose);
		m_pMainLayout = new QHBoxLayout(this);
		m_pAvatar = new AvatarWidget(this);
		connect(m_pAvatar,SIGNAL(clicked(QPoint)), this,SLOT(onAvatarClicked(QPoint)));
		m_pFlag = new QLabel(this);

		m_pOnline = new QLabel(this);
		m_pName = new Label(this);
		m_lblMsg = new QLabel(this);
		m_lblMsg->hide();
		QFont font;
		//font.setPointSize(8); //列表摘要消息字体大小
		font.setPixelSize(10);//(2020年8月27日)
		m_lblMsg->setFont(font);
		QVBoxLayout* vlayout = new QVBoxLayout(this);
		vlayout->addWidget(m_pName);
		vlayout->addWidget(m_lblMsg, 0, Qt::AlignTop);
		vlayout->setContentsMargins(0, 0, 0, 0);
		vlayout->setSpacing(0);

		m_checkBox = new RadioButton(this);
		m_pBtnDel = new IconButton(this);
		m_pBtnDel->setPicName(":/chat/delete");
		connect(m_pBtnDel, SIGNAL(clicked()), this,
		        SLOT(onDelBtnClicked()));
		connect(m_checkBox, SIGNAL(clicked()), this,
		        SLOT(onCheckBoxStateChanged()));
		m_pMainLayout->addWidget(m_pAvatar, 1, Qt::AlignVCenter); //0(2020年8月26日)
		m_pMainLayout->addLayout(vlayout);
		m_pMainLayout->addStretch();
		m_pMainLayout->addWidget(m_pFlag, 1, Qt::AlignRight); //0

		m_pMainLayout->addWidget(m_checkBox, 1, Qt::AlignRight); //0
		m_pMainLayout->addWidget(m_pBtnDel, 1, Qt::AlignRight); //0


		if (type != SortListWidget::Use_GroupMemsList && type != SortListWidget::Use_PopList)
		{
			m_pName->setObjectName("themeText");
		}

		m_pOnline->setVisible(false);
		m_pFlag->setVisible(false);

		m_id = -1;
		m_onlineStatus = -1;
		m_name = "";
		m_teamKey = "#";
		m_pOnline->move(40, 30);
		m_pBtnDel->hide();

		setDelBtnVisible(false);
		setCheckBoxVisible(false);

		m_pMainLayout->setContentsMargins(0, 0, 0, 0); //(10, 0, 10, 0)联系人列表边界距离（2020年9月23日）
		this->setLayout(m_pMainLayout);
	}

	SortListWidgetItem::~SortListWidgetItem()
	{
		this->disconnect();
	}

	bool SortListWidgetItem::isChecked()
	{
		return m_checkBox->isChecked();
	}

	void SortListWidgetItem::setChecked(bool isChecked)
	{
		m_checkBox->setChecked(isChecked);
		onCheckBoxStateChanged();
	}

	void SortListWidgetItem::setCheckBoxVisible(bool vis)
	{
		m_checkBox->setVisible(vis);
	}

	void SortListWidgetItem::setCheckable(bool isCheckable)
	{
		m_checkBox->setEnabled(isCheckable);
	}

	void SortListWidgetItem::setDelBtnVisible(bool vis)
	{
		m_IsDelBtnShow = vis;
		//m_pBtnDel->setVisible(vis);
	}

	int64 SortListWidgetItem::id()
	{
		return m_id;
	}

	void SortListWidgetItem::setId(int64 id)
	{
		m_id = id;
	}

	QString SortListWidgetItem::name()
	{
		return m_name;
	}

	void SortListWidgetItem::setName(QString name, int width)
	{
		m_name = name;
		if (width != 0)
		{
			m_pName->setFixedWidth(width);
		}
		m_pName->setText(name);
	}

	QString SortListWidgetItem::avatarPath()
	{
		return m_pAvatar->AvatarPath();
	}

	void SortListWidgetItem::setAvatarPath(QString path)
	{
		m_pAvatar->setAvatarPath(path);
	}

	void SortListWidgetItem::setAvatarVisible(bool isVis)
	{
		m_pAvatar->setVisible(isVis);
	}

	QString SortListWidgetItem::teamKey()
	{
		return m_teamKey;
	}

	void SortListWidgetItem::setTeamKey(QString key)
	{
		m_teamKey = key.toUpper();
	}

	QString SortListWidgetItem::pinYin()
	{
		return m_pinYin;
	}

	void SortListWidgetItem::setPinYin(QString pinyin)
	{
		m_pinYin = pinyin;
	}

	int SortListWidgetItem::onlineStatus()
	{
		return m_onlineStatus;
	}

	void SortListWidgetItem::setOnlineStatus(int type)
	{
		m_onlineStatus = type;
		QString path("");
		switch (type)
		{
		case OnlineOnPC:
			{
				path = ":/chat/computer";
				break;
			}
		case OnlineOnPhone:
			{
				path = ":/chat/phone";
				break;
			}
		case OnlineOnPad:
			{
				path = ":/chat/pad";
				break;
			}
		case Vip:
			{
				path = ":/group/VSign";
				break;
			}
		}
		QImage pixOnline;
		bool ret = pixOnline.load(path);
		pixOnline = pixOnline.scaled(12, 12);
		m_pOnline->setPixmap(QPixmap::fromImage(pixOnline));
		m_pOnline->setVisible(ret);
	}

	bool SortListWidgetItem::flagVisible()
	{
		return m_pFlag->isVisible();
	}

	QString SortListWidgetItem::flagVisibleTips()
	{
		return m_pFlag->toolTip();
	}

	void SortListWidgetItem::setPix(QString pix)
	{
		m_pix = pix;
	}

	QString SortListWidgetItem::flagPix()
	{
		return m_pix;
	}

	void SortListWidgetItem::setFlagVisible(bool vis, QString tips/*=""*/, QString pix)
	{
		if (vis)
		{
			m_pFlag->setToolTip(tips.isEmpty() ? TEXT_TIP197 : tips);
			QImage pixOnline;
			setPix(pix);
			bool ret = pix.isEmpty() ? pixOnline.load(":/group/haremMaster") : pixOnline.load(pix);
			pixOnline = pixOnline.scaled(12, 12);
			m_pFlag->setPixmap(QPixmap::fromImage(pixOnline));
		}
		m_pFlag->setVisible(vis);
	}

	QSize SortListWidgetItem::avatarSize()
	{
		return m_pAvatar->size();
	}

	void SortListWidgetItem::setAvatarSize(QSize sz)
	{
		m_pAvatar->setAvaterSize(sz);
	}

	bool SortListWidgetItem::isVip()
	{
		return m_vip;
	}

	void SortListWidgetItem::setVip(bool vip)
	{
		m_vip = vip;
		if (vip)
		{
			setOnlineStatus(Vip);
		}
		else
		{
			setOnlineStatus(-1);
		}
	}

	bool SortListWidgetItem::isCanDel()
	{
		return m_isCanDel;
	}

	void SortListWidgetItem::setCanDel(bool canDel)
	{
		m_isCanDel = canDel;
	}

	void SortListWidgetItem::setItemData(int64 id, QString name, QString avatar, bool flagVis/*=false*/,
	                                     QString flagTips/*=""*/, int onlineType/*=-1*/,
	                                     QSize AvatarSz/*=QSize(40,40)*/, bool isVip, QString pix)
	{
		this->setVip(isVip);
		this->setId(id);
		this->setName(name);
		this->setAvatarPath(avatar);
		this->setAvatarSize(AvatarSz);
		this->setFlagVisible(flagVis, flagTips, pix);
		this->setOnlineStatus(onlineType);
	}

	void SortListWidgetItem::onDelBtnClicked()
	{
		emit signalRemove(m_id);
	}

	void SortListWidgetItem::enterEvent(QEvent* event)
	{
		if (m_IsDelBtnShow)
		{
			m_pBtnDel->setVisible(m_IsDelBtnShow);
		}
		event->ignore();
	}

	void SortListWidgetItem::leaveEvent(QEvent* event)
	{
		m_pBtnDel->setVisible(false);
		event->ignore();
	}

	void SortListWidgetItem::onCheckBoxStateChanged()
	{
		emit signalCheckedChanged(m_id);
	}

	bool SortListWidgetItem::isCanCheckable()
	{
		return m_checkBox->isEnabled();
	}

	void SortListWidgetItem::setOnlyShowName()
	{
		m_pAvatar->setVisible(false);
	}

	void SortListWidgetItem::onAvatarClicked(QPoint pt)
	{
		emit signalHeadClicked(m_id);
	}

	void SortListWidgetItem::setOnlineIconPos(QPoint pos, int sz/*=0*/)
	{
		m_pOnline->move(pos);
		if (sz != 0)
		{
			m_pOnline->setFixedSize(sz, sz);
		}
	}

	void SortListWidgetItem::mousePressEvent(QMouseEvent* e)
	{
		if (e->button() == Qt::LeftButton)
		{
			if (isCanCheckable())
			{
				setChecked(!isChecked());
			}
		}
		TWidget::mousePressEvent(e);
	}

	void SortListWidgetItem::setTextWidth(int width)
	{
		m_pName->setFixedWidth(width);
	}

	void SortListWidgetItem::setMsgContext(std::string text, QString blueText, bool isShow)
	{
		m_lblMsg->setVisible(isShow);
		QString textContext = QString::fromUtf8(text.c_str());
		if (!blueText.isEmpty())
		{
			QRegExp valueRegExp(QString("(%1)").arg(blueText));
			valueRegExp.setCaseSensitivity(Qt::CaseInsensitive);
			textContext = textContext.replace(valueRegExp, "<font style='color:blue;'>\\1</font>");
		}
		m_lblMsg->setToolTip(textContext);
		m_lblMsg->setText(HAS_TEXT_INCLUDE + textContext);
	}

	SortListWidgetTeamItem::SortListWidgetTeamItem(int type, QWidget* parent/*=0*/, QString key/*="#"*/,
	                                               QString value/*=""*/):
		TWidget(parent)
	{
		m_key = key;
		m_value = value;

		QLabel* lbl = new QLabel(this);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->addWidget(lbl);
		lbl->setText("  " + m_value);

		layout->setContentsMargins(0, 0, 0, 0); //修改聊天内容边框位置
		if (type <= 1)
		{
			lbl->setObjectName("themeText");
			this->setObjectName("themeTeamBg");
		}
		else
		{
			this->setObjectName("TeamBg");
		}
		this->setLayout(layout);
	}

	SortListWidgetTeamItem::~SortListWidgetTeamItem()
	{
	}

	QString SortListWidgetTeamItem::key()
	{
		return m_key;
	}

	QString SortListWidgetTeamItem::value()
	{
		return m_value;
	}
}
