#include "SortListWidget.h"
#include "SortListWidgetItem.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QScrollBar>

#include <ui/common/ChineseInfos.hpp>
#include <ui/common/Common.h>

namespace uicontrols
{
	SortListWidget::SortListWidget(QWidget* parent, useSectionType useType)
		: BaseQListWidget(parent)
	{
		m_useType = useType;
		m_bShowTeam = true;
		setSortingEnabled(false);
		setAutoSelectNextAfterRemovingItem(false);
		initSectionItems(useType);
	}

	void SortListWidget::addSectionItem(QString key, QString value)
	{
		m_mapKeys.insert(key, value);
		QListWidgetItem* item = new QListWidgetItem(this);
		SortListWidgetTeamItem* widget = new SortListWidgetTeamItem(m_useType, this, key, value);
		item->setData(ItemRole, 0);
		this->addItem(item);
		this->setItemWidget(item, widget);
		item->setSizeHint(QSize(item->sizeHint().width(), TEAMITEMHEIGHT));
		item->setHidden(true);
	}

	SortListWidget::~SortListWidget()
	{
		//清空缓存
		while (this->count() > 0)
		{
			QListWidgetItem* item = this->item(0);
			QWidget* widget = this->itemWidget(item);
			if (widget)
			{
				this->takeItem(0);
				delete item;
				delete widget;
				item = nullptr;
				widget = nullptr;
			}
		}
	}

	void SortListWidget::setShowCheckBox(bool visible)
	{
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (item->data(ItemRole) == 0)
			{
				continue;
			}
			SortListWidgetItem* widget = static_cast<SortListWidgetItem*>(this->itemWidget(item));
			if (widget)
			{
				widget->setCheckBoxVisible(visible);
			}
		}
	}

	void SortListWidget::setCanChecked(int64 id, bool isCheckable, bool isChecked)
	{
		SortListWidgetItem* widget = widgetById(id);
		if (widget)
		{
			widget->setCheckable(isCheckable);
			widget->setChecked(isChecked);
		}
	}

	QList<int64> SortListWidget::getCheckedItems()
	{
		QList<int64> ids;
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (item->data(ItemRole) == 0)
			{
				continue;
			}
			SortListWidgetItem* widget = static_cast<SortListWidgetItem*>(this->itemWidget(item));
			if (widget && widget->isChecked())
			{
				ids.push_back(widget->id());
			}
		}
		return ids;
	}

	QString SortListWidget::makeSection(QString oriSection, bool isVip/*=false*/, bool isAmin)
	{
		if (isAmin)
		{
			return ADMIN_SECTION_KEY;
		}
		if (isVip)
		{
			//群主或v标好友
			return VIP_SECTION_KEY;
		}
		if (oriSection == CONSTANT_SECTION_KEY ||
			oriSection == VIP_SECTION_KEY)
		{
			return oriSection;
		}
		oriSection.replace(CONSTANT_SECTION_KEY, "");
		oriSection.replace(VIP_SECTION_KEY, "");
		if (oriSection.length() > 0)
		{
			QString key = oriSection.at(0).toUpper();
			return m_mapKeys.value(key, "#");
		}
		return "#";
	}

	void SortListWidget::addNewItem(SortListWidgetItem* widget)
	{
		int index = 0;
		QString key = widget->teamKey();
		if (m_mapKeys.contains(key))
		{
			if (!m_bShowTeam)
			{
				index = this->count();
			}
			else
			{
				for (int i = 0; i < this->count(); ++i)
				{
					QListWidgetItem* itemTeam = this->item(i);
					if (itemTeam->data(ItemRole) == 1)
					{
						continue;
					}
					SortListWidgetTeamItem* widgetTeam = static_cast<SortListWidgetTeamItem*>(this->itemWidget(itemTeam)
					);
					if (widgetTeam && widgetTeam->key() == key)
					{
						if (m_bShowTeam && key != "@")
						{
							itemTeam->setHidden(false);
						}
						index = i + 1;
						break;
					}
				}
			}

			QListWidgetItem* item = new QListWidgetItem();
			if (m_useType == Use_GroupMemsList || m_useType == Use_PopList)
			{
				item->setSizeHint(QSize(item->sizeHint().width(), LIST_ITEM_HEIGHT)); //LIST_ITEM_HEIGHT/2(2020-8-25)
			}
			else
			{
				item->setSizeHint(QSize(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
			}
			item->setData(ItemRole, 1);
			this->insertItem(index, item);
			this->setItemWidget(item, widget);
		}
		emit itemCntChange();
	}

	SortListWidgetItem* SortListWidget::itemToWidget(QListWidgetItem* item)
	{
		if (item->data(ItemRole) == 0)
		{
			return nullptr;
		}
		SortListWidgetItem* widget = static_cast<SortListWidgetItem*>(this->itemWidget(item));
		if (widget && widget->id() != -1)
		{
			return widget;
		}
		return nullptr;
	}

	void SortListWidget::removeItem(int64 id)
	{
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (item->data(ItemRole) == 0)
			{
				continue;
			}
			SortListWidgetItem* widget = static_cast<SortListWidgetItem*>(this->itemWidget(item));
			if (widget && widget->id() == id)
			{
				QString key = widget->teamKey();
				this->removeItemWidget(item);
				delete item;
				item = nullptr;
				widget = nullptr;
				if (m_bShowTeam && !hasItemOfSection(key))
				{
					int index = -1;
					item = indexOfSection(key, index);
					if (item)
					{
						item->setHidden(true);
					}
				}
			}
		}
	}

	void SortListWidget::removeItem(int64 id, bool isAutoSelNextItem)
	{
		if (isAutoSelNextItem && m_bAutoSelNextItem)
		{
			bool isNeedSelNext = false;
			int index = this->currentRow();
			QListWidgetItem* item = itemById(id);
			if (item == this->currentItem())
			{
				isNeedSelNext = true;
			}
			if (isNeedSelNext)
			{
				int nextIndex = nextItemIndex(id);
				if (nextIndex >= 0 && nextIndex < this->count())
				{
					this->setCurrentRow(nextIndex);
				}
			}
		}
		removeItem(id);
		emit itemCntChange();
	}

	QListWidgetItem* SortListWidget::itemById(int64 id)
	{
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (item->data(ItemRole) == 0)
			{
				continue;
			}
			SortListWidgetItem* widget = static_cast<SortListWidgetItem*>(this->itemWidget(item));
			if (widget && widget->id() == id)
			{
				return item;
			}
		}
		return nullptr;
	}

	int SortListWidget::nextItemIndex(int64 nowId)
	{
		int itemCnt = this->count() - m_mapKeys.count();
		if (itemCnt == 0)
		{
			return -1; //列表空，返回
		}
		QListWidgetItem* item = this->itemById(nowId);
		if (item)
		{
			int index = this->row(item);
			//向下遍历
			bool findNextItem = false;
			int nextIndex = -1;
			for (int i = index + 1; i < this->count(); ++i)
			{
				item = this->item(i);
				if (item && item->data(ItemRole) == 0)
				{
					continue;
				}
				nextIndex = i;
				findNextItem = true;
				break;
			}
			if (findNextItem)
			{
				return nextIndex;
			}
			//向上查找
			for (int i = index - 1; i > 0; --i)
			{
				item = this->item(i);
				if (item && item->data(ItemRole) == 0)
				{
					continue;
				}
				return i;
			}
		}
		return -1;
	}

	void SortListWidget::setShowSection(bool vis/*=true*/)
	{
		m_bShowTeam = vis;
		QList<QString> keys = m_mapKeys.keys();
		for (int i = 0; i < keys.size(); ++i)
		{
			QString key = keys.at(i);
			int index = -1;
			QListWidgetItem* item = indexOfSection(key, index);
			if (item)
			{
				if (m_bShowTeam && key != "@")
				{
					if (hasItemOfSection(key))
					{
						item->setHidden(false);
					}
				}
				else
				{
					item->setHidden(true);
				}
			}
		}
	}

	void SortListWidget::removeAllItems()
	{
		QMap<QWidget*, QListWidgetItem*> mapItems;
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (item->data(ItemRole) == 0)
			{
				item->setHidden(true);
			}
			else
			{
				SortListWidgetItem* widget = static_cast<SortListWidgetItem*>(this->itemWidget(item));
				if (widget)
				{
					mapItems.insert(widget, item);
				}
			}
		}
		QList<QListWidgetItem*> values = mapItems.values();
		for (int i = 0; i < values.size(); ++i)
		{
			QListWidgetItem* item = values.at(i);
			if (item)
			{
				this->removeItemWidget(item);
				delete item;
				item = nullptr;
			}
		}
		QList<QWidget*> keys = mapItems.keys();
		for (int i = 0; i < keys.size(); ++i)
		{
			QWidget* widget = keys.at(i);
			if (widget)
			{
				delete widget;
				widget = nullptr;
			}
		}
	}

	void SortListWidget::updateItemName(int64 id, QString name, QString sectionKey, int namewidth)
	{
		bool hasItem = false;
		SortListWidgetItem* widget = hasItemOfList(id, hasItem);
		if (!hasItem)
		{
			return;
		}
		if (widget && widget->teamKey() == sectionKey)
		{
			widget->setName(name, namewidth);
		}
		else
		{
			SortListWidgetItem* newWidget = new SortListWidgetItem(m_useType, this);
			newWidget->setTeamKey(sectionKey);
			newWidget->setItemData(id,
			                       name,
			                       widget->avatarPath(),
			                       widget->flagVisible(),
			                       widget->flagVisibleTips(),
			                       widget->onlineStatus(),
			                       widget->avatarSize(),
			                       widget->isVip(),
			                       widget->flagPix());
			bool isNeedSelItem = false;
			if (m_bAutoSelNextItem)
			{
				QListWidgetItem* item = itemById(id);
				if (this->currentItem() == item)
				{
					isNeedSelItem = true;
				}
			}
			removeItem(id);
			addNewItem(newWidget);
			newWidget->setName(name, namewidth);
			if (isNeedSelItem)
			{
				QListWidgetItem* item = itemById(id);
				this->setCurrentItem(item);
			}
		}
	}

	void SortListWidget::updateAvatar(int64 id, QString avatar)
	{
		bool hasItem = false;
		SortListWidgetItem* widget = hasItemOfList(id, hasItem);
		if (widget)
		{
			widget->setAvatarPath(avatar);
		}
	}

	void SortListWidget::updateOnlineStatus(int64 id, int type)
	{
		bool hasItem = false;
		SortListWidgetItem* widget = hasItemOfList(id, hasItem);
		if (widget)
		{
			widget->setOnlineStatus(type);
		}
	}

	void SortListWidget::updateVip(int64 id, bool isVip)
	{
		SortListWidgetItem* widget = widgetById(id);
		if (widget)
		{
			widget->setVip(isVip);
		}
	}

	SortListWidgetItem* SortListWidget::hasItemOfList(int64 id, bool& existed)
	{
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (item->data(ItemRole) == 0)
			{
				continue;
			}
			SortListWidgetItem* widget = static_cast<SortListWidgetItem*>(this->itemWidget(item));
			if (widget && widget->id() == id)
			{
				existed = true;
				return widget;
			}
		}
		return nullptr;
	}

	SortListWidgetItem* SortListWidget::widgetById(int64 id)
	{
		bool hasItem = false;
		return hasItemOfList(id, hasItem);
	}

	void SortListWidget::setItemData(int64 id, QString name, QString avatar, bool flagVis/*=false*/,
	                                 QString flagTips/*=""*/, int onlineType/*=-1*/, QSize AvatarSz, QString pix)
	{
		bool isFind = false;
		SortListWidgetItem* widget = hasItemOfList(id, isFind);
		if (widget)
		{
			widget->setName(name);
			widget->setAvatarPath(avatar);
			widget->setAvatarSize(AvatarSz);
			widget->setFlagVisible(flagVis, flagTips);
			widget->setOnlineStatus(onlineType);
			widget->setAvatarSize(AvatarSz);
		}
	}

	void SortListWidget::setAutoSelectNextAfterRemovingItem(bool isAutoSelNext/*=false*/)
	{
		m_bAutoSelNextItem = isAutoSelNext;
	}

	void SortListWidget::initSectionItems(useSectionType useType)
	{
		//特殊显示项
		addSectionItem(CONSTANT_SECTION_KEY, CONSTANT_SECTION_KEY);
		switch (useType)
		{
		case Use_ContactList:
			{
				//V标好友
				addSectionItem(VIP_SECTION_KEY,VIP_BUDDY);
				break;
			}
		case Use_GroupList:
			{
				//V标群
				addSectionItem(VIP_SECTION_KEY,TEXT_TIP238);
				break;
			}
		case Use_GroupMemsList:
			{
				//群主
				addSectionItem(VIP_SECTION_KEY,GROUP_CREATER);
				//管理员
				addSectionItem(ADMIN_SECTION_KEY,GROUP_MANAGER);
				break;
			}
		}
		for (char ch = 'A'; ch <= 'Z'; ++ch)
		{
			QString key(ch);
			addSectionItem(key, key);
		}
		//数字或其他分组
		addSectionItem("#", "#");
	}

	bool SortListWidget::hasItemOfSection(QString sectionKey)
	{
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (item->data(ItemRole) == 0)
			{
				continue;
			}
			SortListWidgetItem* widget = static_cast<SortListWidgetItem*>(this->itemWidget(item));
			if (widget && widget->teamKey() == sectionKey)
			{
				return true;
			}
		}
		return false;
	}

	QListWidgetItem* SortListWidget::indexOfSection(QString sectionKey, int& index)
	{
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (item->data(ItemRole) == 1)
			{
				continue;
			}
			SortListWidgetTeamItem* widget = static_cast<SortListWidgetTeamItem*>(this->itemWidget(item));
			if (widget && widget->id() == -1 && widget->key() == sectionKey)
			{
				index = i;
				return item;
			}
		}
		return nullptr;
	}

	bool SortListWidget::isExisted(int64 id)
	{
		return (itemById(id) != nullptr);
	}

	int SortListWidget::itemCount()
	{
		int cnt = 0;
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (item->data(ItemRole) == 0)
			{
				continue;
			}
			if (!item->isHidden())
			{
				cnt++;
			}
		}
		return cnt;
	}

	void SortListWidget::setHide(int64 id, bool isHide)
	{
		QListWidgetItem* item = itemById(id);
		if (item)
		{
			item->setHidden(isHide);
		}
	}

	int SortListWidget::allItemsHeight()
	{
		int h = 0;
		for (int i = 0; i < this->count(); ++i)
		{
			QListWidgetItem* item = this->item(i);
			if (!item->isHidden())
			{
				h += item->sizeHint().height();
			}
		}
		return h;
	}
}
