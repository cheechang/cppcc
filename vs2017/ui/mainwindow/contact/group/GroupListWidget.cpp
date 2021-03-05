#include "GroupListWidget.h"
#include "common/Controlptr.h"
#include "common/Connect.h"
#include "GroupListItemWidget.h"
#include <log.h>
#include <QCoreApplication>
#include <QPainter>
#include <QStyleOption>
#include <data/ChatData.h>
#include "utils/common.h"
#include <ui/controls/SortListWidget.h>
#include <ui/controls/SortListWidgetItem.h>
#include <ui/controls/WeMessageBox.h>
#include "ui/common/ChineseInfos.hpp"
#include "../../../common/Common.h"

const int LIST_ITEM_HEIGHT = 80 * gDdpi; //62(2020年8月26日)
const int LIST_ITEM_WIDTH = 250 * gDdpi; //226(2020年8月26日)
const int NAMEWIDRH = 150; //NAMEWIDTH 135(2020年8月26日)
namespace ui
{
	GroupListWidget::GroupListWidget(QWidget* parent)
		: TWidget(parent)
	{
		mListWidget = new uicontrols::SortListWidget(nullptr, uicontrols::SortListWidget::Use_GroupList);
		//mListWidget->setSortingEnabled(true);
		//mListWidget->setMouseTracking(false);
		mCurSelectItemId = 0;
		setObjectName("bg_fa");

		connect(mListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
		connect(mListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this,
		        SLOT(onItemDoubleClicked(QListWidgetItem*)));
		connect(mListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onListWidgetCurrentRowChanged(int)));
		connect(mListWidget, SIGNAL(signalSrcollToBottom()), this, SLOT(onLazyLoadMember()));
		mListWidget->setAutoSelectNextAfterRemovingItem(true);
		CSharedPtr<control::IUserControl> userControl = USERCONTROL;
		if (userControl)
		{
			CSharedPtr<data::AccountInfo> account = userControl->GetAccountInfo();
			mAccountId = account->id.value();
		}
		initMenuItem();
		mMainLayout = CMakePtr<QVBoxLayout>();
		mMainLayout->setContentsMargins(0, 2, 0, 0);
		mMainLayout->addWidget(mListWidget);
		setLayout(mMainLayout.get());

		m_groupmgrcontrol = GROUPMGRCONTROL;
		if (m_groupmgrcontrol)
		{
			CONNECT_SERVICE(GroupListNotify(std::vector<CSharedPtr<data::TinyGroup> >&));
			CONNECT_SERVICE(GroupHeadImgNotify(int64, const std::string&));
			CONNECT_SERVICE(GroupOpertorNotify(int));
			CONNECT_SERVICE(GroupRefreshNotify(int8, const data::Group&));
			CONNECT_SERVICE(TransferGroupNotify(int64, const std::string&, int64, const std::string&));
			m_groupmgrcontrol->RegGroupListCb(CBind(&GroupListWidget::signalSerGroupListNotify,
			                                        this,CPlaceholders _1));
			m_groupmgrcontrol->RegGroupHeadImgUpdateCb(CBind(&GroupListWidget::signalSerGroupHeadImgNotify,
			                                                 this,CPlaceholders _1,CPlaceholders _2));
			m_groupmgrcontrol->RegGroupRefreshCb(CBind(&GroupListWidget::signalSerGroupRefreshNotify,
			                                           this,CPlaceholders _1,CPlaceholders _2));
			m_groupmgrcontrol->RegTransferGroupCb(CBind(&GroupListWidget::signalSerTransferGroupNotify,
			                                            this, CPlaceholders _1, CPlaceholders _2, CPlaceholders _3,
			                                            CPlaceholders _4));

			std::vector<CSharedPtr<data::TinyGroup>> groups;
			m_groupmgrcontrol->GetGroupList(groups);
			emit signalSerGroupListNotify(groups);
		}
	}

	GroupListWidget::~GroupListWidget()
	{
		clearList();
	}

	void GroupListWidget::onSerGroupListNotify(std::vector<CSharedPtr<data::TinyGroup>>& groups)
	{
		//clearList();
		//onGetVGroupSign(groups);
		for (int i = 0; i < groups.size(); ++i)
		{
			DataPtr data = groups.at(i);
			addListNewItem(data);
		}
	}

	void GroupListWidget::clearList()
	{
		for (int i = 0; i < mListWidget->count();)
		{
			removeItem(i);
		}
	}

	void GroupListWidget::removeItem(int row)
	{
		if (row >= 0 && row < mListWidget->count())
		{
			QListWidgetItem* curItem = mListWidget->item(row);
			if (curItem != CNull)
			{
				GroupListItemWidget* curWidget = static_cast<GroupListItemWidget*>(mListWidget->itemWidget(curItem));
				if (curWidget != CNull)
				{
					int64 groupId = curWidget->id();

					mListWidget->takeItem(row);

					m_mapItem.remove(groupId);
					m_mapItemWidget.remove(groupId);
					m_mapData.remove(groupId);
				}
			}
		}
	}

	void GroupListWidget::addListNewItem(DataPtr data, int pos)
	{
		if (data != CNull)
		{
			/*ItemPtr item = CMakePtr<QListWidgetItem>();
			ItemWidgetPtr widget = CMakePtr<GroupListItemWidget>(CNull,data->groupId.value());
			QString name = QString::fromUtf8(data->groupName.value().c_str());
			QString head = QString::fromUtf8(data->avatar.value().c_str());
			if(head.isEmpty() || !utils::FileIsExist(head.toStdString())){
				head = ":/base/group_head";
			}

			bool isCreator = (mAccountId == data->createrId.value());
			bool isVsign = false;
			if(m_mapVSign.contains(data->groupId.value()))
				isVsign = m_mapVSign[data->groupId.value()];
			int type = data->type.isSet() ? data->type.value() : 0;
			widget->setData(head,name,isCreator, isVsign,type);
			int row = (pos == -1)?mListWidget->count():pos;
			int count = mListWidget->count();

			mListWidget->insertItem(row,item.get());
			mListWidget->setItemWidget(item.get(),widget.get());*/
			if (data != CNull)
			{
				int64 id = data->groupId.value();

				uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(id);
				if (widget)
				{
					Log(LOG_LEV_INFO, LOG_FILE, "%lld has existed.", id);
					return;
				}
				widget = new uicontrols::SortListWidgetItem(uicontrols::SortListWidget::Use_GroupList, this);
				widget->setFixedSize(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT);
				QString name = QString::fromUtf8(data->groupName.value().c_str());
				QString head = transfer(data->avatar.value().c_str());
				if (head.isEmpty() || !utils::FileIsExist(data->avatar.value()))
				{
					head = DEFAULT_GROUP;
				}
				bool isCreator = (mAccountId == data->createrId.value());
				bool isVsign = data->isVSign.value();
				QString teamKey = mListWidget->makeSection(data->pinyin.value().c_str(), isVsign);
				widget->setItemData(id, name, head, isCreator);
				widget->setName(name, NAMEWIDRH * gDdpi);
				widget->setCanDel(data->cantExit.value());
				widget->setTeamKey(teamKey);
				widget->setVip(isVsign);
				mListWidget->addNewItem(widget);
			}
		}
	}

	void GroupListWidget::onSerGroupHeadImgNotify(int64 groupId, const std::string& head)
	{
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(groupId);
		if (widget)
		{
			widget->setAvatarPath(head.c_str());
		}
	}

	void GroupListWidget::onItemClicked(QListWidgetItem* item)
	{
		uicontrols::SortListWidgetItem* widget = mListWidget->itemToWidget(item);
		if (widget)
		{
			Log(LOG_LEV_INFO, LOG_FILE, "id:%lld", widget->id());
			emit showGroupInforPage(widget->id());
		}
	}

	void GroupListWidget::contextMenuEvent(QContextMenuEvent* e)
	{
		QListWidgetItem* item = mListWidget->itemAt(mapFromGlobal(QCursor::pos()));
		if (item != CNull)
		{
			uicontrols::SortListWidgetItem* widget = mListWidget->itemToWidget(item);
			if (widget)
			{
				mMenuSelectItemGroupId = widget->id();
				popMenu->clear();
				int64 creatorId = 0;
				bool isExistGroup = true;
				data::Group infoGroup;
				if (m_groupmgrcontrol)
				{
					m_groupmgrcontrol->GetGroupInfo(mMenuSelectItemGroupId, infoGroup);
					creatorId = infoGroup.info.value().createrId.value();
					isExistGroup = infoGroup.info.value().cantExit.value();
				}

				if (infoGroup.info.value().type.value() != 2 && infoGroup.info.value().type.value() != 1)
				{
					if (infoGroup.info.value().createrId.value() == mAccountId)
					{
						popMenu->addAction(m_actionDissolutionGroup.get());
					}
					else
					{
						popMenu->addAction(m_actionExistGroup.get());
					}
				}

				if (widget->isVip())
				{
					popMenu->addAction(m_actionCancelVGroup.get());
				}
				else
				{
					popMenu->addAction(m_actionSetVGroup.get());
				}
				popMenu->exec(QCursor::pos());
			}
		}
	}

	void GroupListWidget::initMenuItem()
	{
		m_actionExistGroup = CMakePtr<QAction>(transfer("退出群"), this);
		m_actionDissolutionGroup = CMakePtr<QAction>(transfer("解散群"), this);
		m_actionTransferGroup = CMakePtr<QAction>(transfer("转让群"), this);
		m_actionSetVGroup = CMakePtr<QAction>(transfer("设置V标"), this);
		m_actionCancelVGroup = CMakePtr<QAction>(transfer("取消V标"), this);
		popMenu = CMakePtr<QMenu>(this);

		connect(m_actionExistGroup.get(),SIGNAL(triggered(bool)), this,SLOT(onExistGroupClicked()));
		connect(m_actionDissolutionGroup.get(),SIGNAL(triggered(bool)), this,SLOT(onDissolutionGroupClicked()));
		connect(m_actionTransferGroup.get(),SIGNAL(triggered(bool)), this,SLOT(onTransferGroupClicked()));
		connect(m_actionSetVGroup.get(), SIGNAL(triggered(bool)), this, SLOT(onSerSetVGroupClicked()));
		connect(m_actionCancelVGroup.get(), SIGNAL(triggered(bool)), this, SLOT(onSerCancelVGroupClicked()));
	}

	void GroupListWidget::onExistGroupClicked()
	{
		BEGIN;
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(mMenuSelectItemGroupId);
		if (widget && !widget->isCanDel())
		{
			END;
			return;
		}

		QString TipInfo = TEXT_TIP_EXISTGROUP + " " + widget->name() + " ?";
		int Res = uicontrols::WeMessageBox::showTipInformation(CNull, PROMPT, TipInfo, false, true);
		if (uicontrols::WeMessageBox::Cancel == Res) return;

		if (m_groupmgrcontrol)
		{
			Log(LOG_LEV_INFO, LOG_FILE, "exit group:%lld", mMenuSelectItemGroupId);
			m_groupmgrcontrol->RemoveGroup(2, mMenuSelectItemGroupId,
			                               CBind(&GroupListWidget::signalSerGroupOpertorNotify, this,
			                                     CPlaceholders _1));
		}
		END;
	}

	void GroupListWidget::onTransferGroupClicked()
	{
		DataPtr data = m_mapData.value(mMenuSelectItemGroupId);
		if (data != CNull)
		{
			deleteMenuSelItemAndShowNextItemInfo();
		}
	}

	void GroupListWidget::onDissolutionGroupClicked()
	{
		BEGIN;
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(mMenuSelectItemGroupId);
		if (widget && m_groupmgrcontrol)
		{
			QString TipInfo = TEXT_TIP_DISSOLUGROUP + " " + widget->name() + " ?";
			int Res = uicontrols::WeMessageBox::showTipInformation(CNull, PROMPT, TipInfo, false, true);
			if (uicontrols::WeMessageBox::Cancel == Res) return;

			Log(LOG_LEV_INFO, LOG_FILE, "dissolution group:%lld", mMenuSelectItemGroupId);
			m_groupmgrcontrol->RemoveGroup(1, mMenuSelectItemGroupId,
			                               CBind(&GroupListWidget::signalSerGroupOpertorNotify, this,
			                                     CPlaceholders _1));
		}
		END;
	}

	void GroupListWidget::deleteMenuSelItemAndShowNextItemInfo()
	{
		int row = mListWidget->row(m_mapItem.value(mMenuSelectItemGroupId).get());
		removeItem(row);
		if (mListWidget->count() == 0)
		{
			emit showGroupInforPage(0);
			return;
		}
		if (row > 0 && row >= mListWidget->count())
		{
			row--;
		}
		QListWidgetItem* item = mListWidget->item(row);
		GroupListItemWidget* widget = static_cast<GroupListItemWidget*>(mListWidget->itemWidget(item));
		if (widget)
		{
			emit showGroupInforPage(widget->id());
			mCurSelectItemId = widget->id();
			mListWidget->setItemSelected(item, true);
		}
		mMenuSelectItemGroupId = 0;
	}

	void GroupListWidget::onSerGroupOpertorNotify(int code)
	{
		BEGIN;
		Log(LOG_LEV_INFO, LOG_FILE, "code:%d,id:%lld", code, mMenuSelectItemGroupId);
		if (code == 0 || code == 309)
		{
			mListWidget->removeItem(mMenuSelectItemGroupId, true);
			mMenuSelectItemGroupId = 0;
			if (mListWidget->itemCount() == 0)
			{
				emit showGroupInforPage(0);
			}
		}
		else
		{
			uicontrols::WeMessageBox::showCritical(this, FORCE_LOGGINEDOFF_TITLE,
			                                       QString::fromLocal8Bit(utils::Error::GetErrMsg(code).c_str()));
		}
		END;
	}

	void GroupListWidget::onSerGroupRefreshNotify(int8 type, const data::Group& group)
	{
		int64 groupId = group.info.value().groupId.value();
		int row = mListWidget->row(m_mapItem.value(groupId).get());

		if (type == 31 || type == 32 || type == 33)
		{
			//删除等操作
			mListWidget->removeItem(groupId, true);
			if (mListWidget->itemCount() == 0)
			{
				emit showGroupInforPage(0);
			}
		}
		else if (type == 1)
		{
			//添加
			DataPtr data = makeDataPtr(group);
			addListNewItem(data);
		}
		else if (type == 2)
		{
			//更新
			DataPtr data = makeDataPtr(group);
			updateItem(data);
		}
	}

	void GroupListWidget::updateItem(DataPtr data)
	{
		BEGIN;
		if (data)
		{
			int64 id = data->groupId.value();
			if (data->isVSign.isSet())
			{
				bool isVip = data->isVSign.value();
				uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(data->groupId.value());
				if (widget)
				{
					if (data->groupName.isSet())
					{
						bool isVip = widget->isVip();
						if (data->isVSign.isSet())
						{
							isVip = data->isVSign.value();
						}
						QString name = data->groupName.value().empty()
							               ? QString::fromUtf8(data->groupName.value().c_str())
							               : QString::fromUtf8(data->groupName.value().c_str());
						QString section = mListWidget->makeSection(data->pinyin.value().c_str(), isVip);
						mListWidget->updateItemName(id, name, section, NAMEWIDRH * gDdpi);
						mListWidget->updateVip(id, isVip);
					}
					else if (data->isVSign.isSet())
					{
						QString name = widget->name();
						bool isVip = widget->isVip();
						QString section = mListWidget->makeSection(data->pinyin.value().c_str(), isVip);
						mListWidget->updateItemName(id, name, section, NAMEWIDRH * gDdpi);
						mListWidget->updateVip(id, isVip);
					}
				}
			}
		}
		END;
	}

	void GroupListWidget::onSerTransferGroupNotify(int64 creatorId, const std::string& creatorName,
	                                               int64 groupId, const std::string& groupName)
	{
		BEGIN;
		Log(LOG_LEV_INFO, LOG_FILE, "creatorId:%lld", creatorId);
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(groupId);
		if (widget)
		{
			bool isCreator = (mAccountId == creatorId);
			widget->setFlagVisible(isCreator, TEXT_TIP239);
			QListWidgetItem* item = mListWidget->itemById(groupId);
			if (item == mListWidget->currentItem())
			{
				emit showGroupInforPage(groupId);
			}
		}
		END;
	}


	void GroupListWidget::deleteItemAndSelNextItemInfo(int& row)
	{
		bool isSel = mListWidget->currentRow() == row;
		removeItem(row);
		if (mListWidget->count() == 0)
		{
			emit showGroupInforPage(0);
			return;
		}
		if (isSel)
		{
			if (row > 0 && row >= mListWidget->count())
			{
				row--;
			}
			QListWidgetItem* item = mListWidget->item(row);
			GroupListItemWidget* widget = static_cast<GroupListItemWidget*>(mListWidget->itemWidget(item));
			if (widget)
			{
				emit showGroupInforPage(widget->id());
				mCurSelectItemId = widget->id();
				mListWidget->setItemSelected(item, true);
			}
		}
	}

	int GroupListWidget::getPosByName(std::string pingyin)
	{
		int row = 0;
		for (row = 0; row < mListWidget->count(); ++row)
		{
			QListWidgetItem* item = mListWidget->item(row);
			GroupListItemWidget* widget = static_cast<GroupListItemWidget*>(mListWidget->itemWidget(item));
			if (widget)
			{
				DataPtr data = m_mapData.value(widget->id(),CNull);
				if (data)
				{
					if (data->pinyin.value() >= pingyin)
					{
						return row;
					}
				}
			}
		}
		return row;
	}

	CSharedPtr<data::TinyGroup> GroupListWidget::makeDataPtr(const data::Group& group)
	{
		DataPtr data = CMakePtr<data::TinyGroup>();
		data->avatar = group.info.value().avatar;
		data->avatarUrl = group.info.value().avatarUrl;
		data->cantExit = group.info.value().cantExit;
		data->createrId = group.info.value().createrId;
		data->groupId = group.info.value().groupId;
		data->groupName = group.info.value().groupName;
		data->pinyin = group.info.value().pinyin;
		data->isVSign = group.info.value().isVSign;
		data->type = group.info.value().type.value();
		return data;
	}

	void GroupListWidget::updateItemAndSelItemInfo(DataPtr data)
	{
		int64 groupId = data->groupId.value();
		QListWidgetItem* item = m_mapItem.value(groupId).get();
		bool isSel = false;
		if (item && item == mListWidget->currentItem())
		{
			isSel = true;
		}
		int row = mListWidget->row(m_mapItem.value(groupId).get());
		removeItem(row);

		row = getPosByName(data->pinyin.value());
		addListNewItem(data, row);

		row = mListWidget->row(m_mapItem.value(groupId).get());
		if (isSel)
		{
			item = mListWidget->item(row);
			GroupListItemWidget* widget = static_cast<GroupListItemWidget*>(mListWidget->itemWidget(item));
			if (widget)
			{
				emit showGroupInforPage(widget->id());
				mCurSelectItemId = widget->id();
				mListWidget->setItemSelected(item, true);
			}
		}
	}

	void GroupListWidget::onItemDoubleClicked(QListWidgetItem* item)
	{
		uicontrols::SortListWidgetItem* widget = mListWidget->itemToWidget(item);
		if (widget != CNull)
		{
			ChatInfoPtr chat = CMakePtr<data::ChatInfo>();
			chat->chatType = data::GROUP_CHAT;
			chat->isStartChat = true;
			chat->avatar = widget->avatarPath().toStdString();
			chat->name = widget->name().toStdString();
			chat->targetid = widget->id();
			Log(LOG_LEV_INFO, LOG_FILE, "id:%lld,nm:%s", widget->id(), widget->name().toStdString().c_str());
			emit startChat(chat);
		}
	}

	void GroupListWidget::onSerSetVGroupClicked()
	{
		BEGIN;
		Log(LOG_LEV_INFO, LOG_FILE, "id:%lld", mMenuSelectItemGroupId);
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(mMenuSelectItemGroupId);
		if (widget && m_groupmgrcontrol)
		{
			m_groupmgrcontrol->SetGroupExtraInfo(mMenuSelectItemGroupId, 1, -1,
			                                     std::bind(&GroupListWidget::onSerSetVGroupCallback, this,
			                                               std::placeholders::_1));
			DataPtr data = CMakePtr<data::TinyGroup>();
			data->groupId = mMenuSelectItemGroupId;
			data->isVSign = true;
			updateItem(data);
		}
		END;
	}

	void GroupListWidget::onSerCancelVGroupClicked()
	{
		BEGIN;
		Log(LOG_LEV_INFO, LOG_FILE, "id:%lld", mMenuSelectItemGroupId);
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(mMenuSelectItemGroupId);
		if (widget && m_groupmgrcontrol)
		{
			m_groupmgrcontrol->SetGroupExtraInfo(mMenuSelectItemGroupId, 0, -1,
			                                     std::bind(&GroupListWidget::onSerSetVGroupCallback, this,
			                                               std::placeholders::_1));
			DataPtr data = CMakePtr<data::TinyGroup>();
			data->groupId = mMenuSelectItemGroupId;
			data->isVSign = false;
			updateItem(data);
		}
		END;
	}

	void GroupListWidget::onSerSetVGroupCallback(int Error)
	{
		BEGIN;
		Log(LOG_LEV_INFO, LOG_FILE, "code:%d", Error);
		END;
	}

	void GroupListWidget::onGetVGroupSign(std::vector<CSharedPtr<data::TinyGroup>> groups)
	{
		std::vector<CSharedPtr<data::TinyGroup>>::iterator iter = groups.begin();
		while (iter != groups.end())
		{
			if ((*iter)->isVSign.value())
			{
				m_mapVSign[((*iter)->groupId.value())] = true;
			}
			else
			{
				m_mapVSign[((*iter)->groupId.value())] = false;
			}
			++iter;
		}
	}
}
