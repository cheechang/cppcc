#include "MsgManagerListItem.h"

#include "controls/headimage.h"
#include "common/Common.h"

namespace ui
{
	MsgManagerListItem::MsgManagerListItem(QWidget* parent, int64 targetid): TWidget(parent), mTargetId(targetid)
	{
		Init();
	}

	MsgManagerListItem::~MsgManagerListItem()
	{
	}

	void MsgManagerListItem::SetData(QString head, QString name, int count)
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
		m_count = count;
	}

	void MsgManagerListItem::Init()
	{
		m_Mainlayout = CMakePtr<QHBoxLayout>();
		m_lblName = CMakePtr<QLabel>();

		///2019-5-14
		QFont font("Microsoft YaHei", 18, 50); //"Microsoft YaHei", 18, 50£¨2020Äê8ÔÂ26ÈÕ£©
		m_lblName->setFont(font);

		m_imgHead = CMakePtr<HeadImage>(this, QSize(HEAD_SIZE - 8,HEAD_SIZE)); //HEAD_SIZE-8,HEAD_SIZE-8

		m_Mainlayout->addWidget(m_imgHead.get(), 0, Qt::AlignVCenter);
		m_Mainlayout->addWidget(m_lblName.get(), 0, Qt::AlignVCenter);
		setLayout(m_Mainlayout.get());
	}

	int64 MsgManagerListItem::GetTargetid()
	{
		return mTargetId;
	}

	int MsgManagerListItem::GetCountMsg()
	{
		return m_count;
	}
}
