#ifndef FRIENDLISTWIDGETITEM_H
#define FRIENDLISTWIDGETITEM_H

#include "../group/GroupListItemWidget.h"
namespace ui{
	class FriendListWidgetItem : public GroupListItemWidget
	{
		Q_OBJECT
	public:
		FriendListWidgetItem(QWidget *parent=CNull);
		~FriendListWidgetItem();
		void setPingyin(std::string pinyin);
		std::string pingyin();
	private:
		std::string mPingyin;
	};
}
#endif // FRIENDLISTWIDGETITEM_H
