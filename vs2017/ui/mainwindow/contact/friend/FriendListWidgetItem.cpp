#include "FriendListWidgetItem.h"
#include "controls/ToolButton.h"
#include "../../../common/Common.h"
namespace ui{
	FriendListWidgetItem::FriendListWidgetItem(QWidget *parent)
		: GroupListItemWidget(parent)
	{
		m_lblHaremMaster->setToolTip(transfer("V±Í∫√”—"));
	}

	FriendListWidgetItem::~FriendListWidgetItem()
	{

	}

	void FriendListWidgetItem::setPingyin( std::string pinyin )
	{
		mPingyin = pinyin;
	}

	std::string FriendListWidgetItem::pingyin()
	{
		return mPingyin;
	}

}