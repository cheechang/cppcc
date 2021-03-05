#include "GroupListItemWidgetWeb.h"
#include "controls/headimage.h"
#include "controls/ToolButton.h"
#include "common/Common.h"
#include <QPicture>
#include  "controls/PushButton.h"
namespace ui{
	GroupListItemWidgetWeb::GroupListItemWidgetWeb(QWidget *parent, int64 id, bool bBigImage)
		: QWidget(parent)
	{
		this->setMouseTracking(true);
		////setObjectName("groupinfobackground");
		m_id = id;
		m_lblName = CMakePtr<QLabel>(this);

	  ///  QFont font("Microsoft YaHei",14, 50);
	  ////  m_lblName->setFont(font);

		////m_lblName->setAlignment(Qt::AlignLeft);
		m_VSign = CMakePtr<ToolButton>(":/group/VSign",this,false);
		m_VSign->setVisible(false);
		m_VSign->setToolTip(transfer("V标群"));

		///if (bBigImage){
			m_imgHead = CMakePtr<HeadImage>(this, QSize(50, 50));// QSize(HEAD_SIZE, HEAD_SIZE));
		///}
		///else {
		///	m_imgHead = CMakePtr<HeadImage>(this, QSize(20, 20));
		///}
		
		m_lblHaremMaster = CMakePtr<ToolButton>(":/group/haremMaster",this,false);
		m_pLabelOrg = CMakePtr<ToolButton>(":/group/right", this, false);
		connect(m_imgHead.get(),SIGNAL(clicked(QPoint)),this,SLOT(onHeadClicked()));

		m_lblHaremMaster->setVisible(false);
		m_lblHaremMaster->setToolTip(transfer("我的群"));
		m_pLabelOrg->setVisible(false);
		m_pLabelOrg->setToolTip(transfer("组织群"));
		m_pLabelOrg->setSize(QSize(20, 20));

		ToolButton *rightImage = new ToolButton(":/group/right",this,false);
		////rightImage->setPicName(":/group/right");
		

		m_hMainLayout = CMakePtr<QHBoxLayout>();
		///m_hMainLayout->addStretch(2);
		m_hMainLayout->addWidget(m_imgHead.get(),0,Qt::AlignVCenter);
		////m_hMainLayout->addStretch(0.5);
		m_imgHead->setContentsMargins(0, 0, 10, 0);
		m_hMainLayout->addWidget(m_lblName.get(), 0, Qt::AlignVCenter);
		///m_hMainLayout->addWidget(m_lblHaremMaster.get(),0,Qt::AlignVCenter);
		////m_hMainLayout->addWidget(m_VSign.get(),0, Qt::AlignVCenter);
		m_hMainLayout->addStretch(4);
		m_hMainLayout->addWidget(rightImage);
		m_hMainLayout->addStretch(1);
		m_hMainLayout->setContentsMargins(6,0,0,0);

		//分割线
		mLineWidget = CMakePtr<QWidget>(this);
		mLineWidget->setObjectName("linebottom");
		mLineWidget->setFixedSize(QSize(260,2));
		mLineWidget->move(0,this->height()-mLineWidget->height());
		mLineWidget->setVisible(false);

		setLayout(m_hMainLayout.get());
	}

	GroupListItemWidgetWeb::~GroupListItemWidgetWeb()
	{

	}

	void GroupListItemWidgetWeb::setData(QString head, QString name, bool isShowHaremMaster, bool isVSign, int groupType)
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

	void GroupListItemWidgetWeb::setHead(QString head)
	{
		if (!head.isEmpty())
		{
			m_imgHead->setAvatarPath(head);
		}
	}

	void GroupListItemWidgetWeb::setName(QString name)
	{
		m_lblName->setText(name);
		m_lblName->setToolTip(name);
	}

	void GroupListItemWidgetWeb::setShowHaremMaster(bool isShow, QString tooltip)
	{
		m_lblHaremMaster->setVisible(isShow);
		if (!tooltip.isEmpty())
		{
			m_lblHaremMaster->setToolTip(tooltip);
		}
	}

	void GroupListItemWidgetWeb::setGroupType(int type, QString tooltip)
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

	void GroupListItemWidgetWeb::showItemAsTeam(QString itemName)
	{
		m_lblHaremMaster->setVisible(false);
		m_imgHead->setVisible(false);
		m_lblName->setText(itemName);
		m_lblName->setToolTip(itemName);
		mLineWidget->setVisible(true);
	}

	QString GroupListItemWidgetWeb::head()
	{
		return m_imgHead->AvatarPath();
	}

	void GroupListItemWidgetWeb::setHeadGray( bool isGray )
	{
		m_imgHead->setShowAsGray(isGray);
	}

	void GroupListItemWidgetWeb::setAvaterSize(QSize size)
	{
		m_imgHead->setAvaterSize(size);
	}

	void GroupListItemWidgetWeb::onHeadClicked()
	{
		emit headClicked(m_id);
	}

	void GroupListItemWidgetWeb::SetVGroupSignVisible(bool IsVisible)
	{
		m_VSign->setVisible(IsVisible);
	}

}
