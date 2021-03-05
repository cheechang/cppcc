#include "SearchResultListWidgetItem.h"
#include "controls/headimage.h"
#include "controls/ToolButton.h"
#include "controls/PushButton.h"
#include "common/Common.h"
#include <QPicture>
namespace ui{
	SearchResultListWidgetItem::SearchResultListWidgetItem(QWidget *parent,int64 id)
		: TWidget(parent)
	{
		m_id = id;
		m_lblName = CMakePtr<ElidedLabel>(this);
		m_isExistLbl = CMakePtr<QLabel>(this);
		m_isExistLbl->setVisible(false);

		m_imgHead = CMakePtr<HeadImage>(this,QSize(HEAD_SIZE,HEAD_SIZE));
		m_btnAdd = CMakePtr<QPushButton>(this);
		m_btnAdd->setObjectName("sendbtn");

		m_btnAdd->setText(transfer("+ºÃÓÑ"));
		m_btnAdd->setFixedSize(85, 20);

		m_vLayout=  CMakePtr<QVBoxLayout>();
		m_vLayout->setContentsMargins(2, 5, 1,1);
		m_vLayout->setSpacing(5);
		m_vLayout->addWidget((QWidget*)m_lblName.get());
		m_vLayout->addWidget(m_isExistLbl.get());
		m_vLayout->addWidget(m_btnAdd.get());
		m_vLayout->addStretch();

		m_hMainLayout = CMakePtr<QHBoxLayout>();
		m_hMainLayout->setSpacing(5);
		m_hMainLayout->addWidget(m_imgHead.get());
		m_hMainLayout->addLayout(m_vLayout.get());
		m_hMainLayout->addStretch();

		setLayout(m_hMainLayout.get());

		connect(m_btnAdd.get(), SIGNAL(clicked()), this, SLOT(onAddBtnClicked()));
	}

	SearchResultListWidgetItem::~SearchResultListWidgetItem()
	{

	}

	void SearchResultListWidgetItem::setData( QString head,QString name ,bool IsShowAddBtn)
	{
		m_lblName->setTextLimitShrink(name, 160);
		m_lblName->setToolTip(name);
		m_imgHead->setAvatarPath(head);
		m_btnAdd->setVisible(IsShowAddBtn);
		m_isExistLbl->setVisible(!IsShowAddBtn);
	}
	void SearchResultListWidgetItem::setExistInfo(QString tipInfo)
	{
		if ( !tipInfo.isEmpty())
		{
			m_btnAdd->setVisible(false);
			m_isExistLbl->setVisible(true);
		}
		m_isExistLbl->setText(tipInfo);
	}
	void SearchResultListWidgetItem::setAddBtnText(QString txt)
	{
		m_btnAdd->setText(txt);
	}
	void SearchResultListWidgetItem::setHead( QString head )
	{
		if (!head.isEmpty())
		{
			m_imgHead->setAvatarPath(head);
		}
	}

	void SearchResultListWidgetItem::setName( QString name )
	{
		m_lblName->setText(name);
		m_lblName->setToolTip(name);
	}

	QString SearchResultListWidgetItem::head()
	{
		return m_imgHead->AvatarPath();
	}
	void SearchResultListWidgetItem::onAddBtnClicked()
	{
		emit signalAddContactBtnClicked(m_id, this);
	}
}
