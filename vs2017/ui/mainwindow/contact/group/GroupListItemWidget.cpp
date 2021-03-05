#include "GroupListItemWidget.h"
#include "controls/headimage.h"
#include "controls/ToolButton.h"
#include "common/Common.h"
#include <QPicture>

namespace ui
{
	GroupListItemWidget::GroupListItemWidget(QWidget* parent, int64 id)
		: TWidget(parent)
	{
		this->setMouseTracking(true);
		m_id = id;
		m_lblName = CMakePtr<QLabel>(this);
		QFont font("Microsoft YaHei", 18, 50);
		m_lblName->setFont(font);

		m_VSign = CMakePtr<ToolButton>(":/group/VSign", this, false);
		m_VSign->setVisible(false);
		m_VSign->setToolTip(transfer("V标群"));

		m_imgHead = CMakePtr<HeadImage>(this, QSize(HEAD_SIZE,HEAD_SIZE));
		m_lblHaremMaster = CMakePtr<ToolButton>(":/group/haremMaster", this, false);
		m_pLabelOrg = CMakePtr<ToolButton>(":/group/org_group", this, false);
		connect(m_imgHead.get(),SIGNAL(clicked(QPoint)), this,SLOT(onHeadClicked()));

		m_lblHaremMaster->setVisible(false);
		m_lblHaremMaster->setToolTip(transfer("我的群"));
		m_pLabelOrg->setVisible(false);
		m_pLabelOrg->setToolTip(transfer("组织群"));
		m_pLabelOrg->setSize(QSize(30, 30)); //20,20

		m_hMainLayout = CMakePtr<QHBoxLayout>();
		m_hMainLayout->addWidget(m_imgHead.get(), 0, Qt::AlignVCenter);
		m_hMainLayout->addWidget(m_lblName.get(), 0, Qt::AlignVCenter);
		m_hMainLayout->addWidget(m_lblHaremMaster.get(), 0, Qt::AlignVCenter);
		m_hMainLayout->addWidget(m_VSign.get(), 0, Qt::AlignVCenter);
		m_hMainLayout->addStretch();
		m_hMainLayout->setContentsMargins(6, 0, 0, 0);

		mLineWidget = CMakePtr<QWidget>(this);
		mLineWidget->setObjectName("linebottom");
		mLineWidget->setFixedSize(QSize(260, 50)); //260,2
		mLineWidget->move(0, this->height() - mLineWidget->height());
		mLineWidget->setVisible(false);
		setLayout(m_hMainLayout.get());
	}

	GroupListItemWidget::~GroupListItemWidget()
	{
	}

	void GroupListItemWidget::setData(QString head, QString name, bool isShowHaremMaster, bool isVSign, int groupType)
	{
		QString elidedName = name;
		QFontMetrics fontWidth(m_lblName->font());
		int width = fontWidth.width(name);
		if (width >= 130)
		{
			elidedName = fontWidth.elidedText(name, Qt::ElideRight, 130);
		}
		m_lblName->setText(elidedName);
		m_lblName->setToolTip(name);
		m_imgHead->setAvatarPath(head);
		m_lblHaremMaster->setVisible(isShowHaremMaster);
		m_VSign->setVisible(isVSign);
		this->setGroupType(groupType);
	}

	void GroupListItemWidget::setHead(QString head)
	{
		if (!head.isEmpty())
		{
			m_imgHead->setAvatarPath(head);
		}
	}

	void GroupListItemWidget::setName(QString name)
	{
		m_lblName->setText(name);
		m_lblName->setToolTip(name);
	}

	void GroupListItemWidget::setShowHaremMaster(bool isShow, QString tooltip)
	{
		m_lblHaremMaster->setVisible(isShow);
		if (!tooltip.isEmpty())
		{
			m_lblHaremMaster->setToolTip(tooltip);
		}
	}

	void GroupListItemWidget::setGroupType(int type, QString tooltip)
	{
		switch (type)
		{
		case 1:
			m_pLabelOrg->setVisible(true);
			m_hMainLayout->insertWidget(2, m_pLabelOrg.get(), 0, Qt::AlignVCenter);
			if (!tooltip.isEmpty())
			{
				m_pLabelOrg->setToolTip(tooltip);
			}
			break;
			//case 2:
			//	m_hMainLayout->removeWidget(m_pLabelOrg.get());
			//	m_hMainLayout->addWidget(m_pLabelOrg.get(),0,Qt::AlignVCenter);
			//	if (!tooltip.isEmpty())
			//	{
			//		m_lblHaremMaster->setToolTip(tooltip);
			//	}
			//	break;
		default:
			m_hMainLayout->removeWidget(m_pLabelOrg.get());
			m_pLabelOrg->setToolTip("");
			m_pLabelOrg->setVisible(false);
			break;
		}
	}

	void GroupListItemWidget::showItemAsTeam(QString itemName)
	{
		m_lblHaremMaster->setVisible(false);
		m_imgHead->setVisible(false);
		m_lblName->setText(itemName);
		m_lblName->setToolTip(itemName);
		mLineWidget->setVisible(true);
	}

	QString GroupListItemWidget::head()
	{
		return m_imgHead->AvatarPath();
	}

	void GroupListItemWidget::setHeadGray(bool isGray)
	{
		m_imgHead->setShowAsGray(isGray);
	}

	void GroupListItemWidget::setAvaterSize(QSize size)
	{
		m_imgHead->setAvaterSize(size);
	}

	void GroupListItemWidget::onHeadClicked()
	{
		emit headClicked(m_id);
	}

	void GroupListItemWidget::SetVGroupSignVisible(bool IsVisible)
	{
		m_VSign->setVisible(IsVisible);
	}
}
