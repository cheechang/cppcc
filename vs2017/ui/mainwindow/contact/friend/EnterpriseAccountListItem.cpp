#include "EnterpriseAccountListItem.h"
#include "controls/headimage.h"
#include "controls/ToolButton.h"
#include "common/Common.h"
#include <QPicture>
namespace ui{
	EnterpriseAccountListItem::EnterpriseAccountListItem(QWidget *parent,int64 id)
		: TWidget(parent)
	{
		m_id = id;
		m_lblName = CMakePtr<QLabel>(this);
		m_imgHead = CMakePtr<HeadImage>(this,QSize(HEAD_SIZE,HEAD_SIZE));
		m_lblHaremMaster = CMakePtr<ToolButton>(":/group/haremMaster",this,false);
		m_lblHaremMaster->setVisible(false);
		m_lblHaremMaster->setToolTip(transfer("ÎÒµÄÈº"));

		m_hMainLayout = CMakePtr<QHBoxLayout>();
		m_hMainLayout->addWidget(m_imgHead.get());
		m_hMainLayout->addWidget(m_lblName.get());
		m_hMainLayout->addWidget(m_lblHaremMaster.get(),0,Qt::AlignVCenter);

		mLineWidget = CMakePtr<QWidget>(this);
		mLineWidget->setObjectName("linebottom");
		mLineWidget->setFixedSize(QSize(260,2));
		mLineWidget->move(0,this->height()-mLineWidget->height());
		mLineWidget->setVisible(false);
		setLayout(m_hMainLayout.get());
	}

	EnterpriseAccountListItem::~EnterpriseAccountListItem()
	{

	}

	void EnterpriseAccountListItem::setData( QString head,QString name ,bool isShowHaremMaster)
	{
		m_lblName->setText(name);
		m_lblName->setToolTip(name);
		m_imgHead->setAvatarPath(head);
		m_lblHaremMaster->setVisible(isShowHaremMaster);
	}

	void EnterpriseAccountListItem::setHead( QString head )
	{
		if (!head.isEmpty())
		{
			m_imgHead->setAvatarPath(head);
		}
	}

	void EnterpriseAccountListItem::setName( QString name )
	{
		m_lblName->setText(name);
		m_lblName->setToolTip(name);
	}

	void EnterpriseAccountListItem::setShowHaremMaster( bool isShow,QString tooltip )
	{
		m_lblHaremMaster->setVisible(isShow);
		if (!tooltip.isEmpty())
		{
			m_lblHaremMaster->setToolTip(tooltip);
		}
	}

	void EnterpriseAccountListItem::showItemAsTeam(QString itemName)
	{
		m_lblHaremMaster->setVisible(false);
		m_imgHead->setVisible(false);
		m_lblName->setText(itemName);
		m_lblName->setToolTip(itemName);
		mLineWidget->setVisible(true);
	}

	QString EnterpriseAccountListItem::head()
	{
		return m_imgHead->AvatarPath();
	}

	void EnterpriseAccountListItem::setHeadGray( bool isGray )
	{
		m_imgHead->setShowAsGray(isGray);
	}

}
