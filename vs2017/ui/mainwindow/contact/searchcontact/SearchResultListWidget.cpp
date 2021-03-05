#include "SearchResultListWidget.h"
#include "common/Connect.h"
#include "SearchResultListWidgetItem.h"
#include "common/Common.h"
#include <QCoreApplication>
#include <log.h>
namespace ui{
	SearchResultListWidget::SearchResultListWidget(QWidget *parent)
		: TWidget(parent)
	{

		mContactControl = CONTACTMGRCONTROL;
		mListWidget = new QListWidget(this);
		mListWidget->setModelColumn(2);
		mListWidget->setViewMode(QListView::IconMode);
		mListWidget->setObjectName("searchList");
		mListWidget->setStyleSheet("QListWidget#searchList{background:transparent}"
			"QListWidget#searchList::Item{background:transparent;}"
			"QListWidget#searchList::Item:hover{background:transparent }"
			"QListWidget#searchList::item:selected{background:transparent }"
			"QListWidget#searchList::item:selected:!active{background:transparent }"
			);
		m_totalCountLbl = new QLabel(this);
		m_totalCountLbl->setVisible(false);

		mainLayout = new QVBoxLayout(this);
		mainLayout->setSpacing(5);
		mainLayout->addWidget(m_totalCountLbl);
		mainLayout->addWidget(mListWidget);

		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(30,2,0,0);
		if (mContactControl){
			CONNECT_SERVICE(SearchFromNet(int , std::vector<data::SearchResultInfo>& ));
			CONNECT_SERVICE(AddAppContact(int ));
		}
	}

	SearchResultListWidget::~SearchResultListWidget()
	{
	
	}
	void SearchResultListWidget::searchKey(QString strKey)
	{
		if ( !strKey.isEmpty())
		{
			mContactControl->searchFromNet(strKey.toUtf8().data(), CBind
				(&SearchResultListWidget::signalSerSearchFromNet,this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}
	void SearchResultListWidget::onSerSearchFromNet(int err, std::vector<data::SearchResultInfo>& result)
	{
		BEGIN;
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"errCode=%d",err);
			return;
		}
		AddLog(LOG_LEV_DEBUG,"SearchResult size=%d",result.size());
		clearList();
		m_totalCountLbl->setVisible(true);
		m_totalCountLbl->setText(transfer("共找到 ")+QString::number(result.size())+transfer(" 个搜索结果"));
		for (int i=0;i<result.size();++i)
		{
			addItemToList(result.at(i));
			//QCoreApplication::processEvents();
		}
		END;
	}
	
	void SearchResultListWidget::clearList()
	{
		for (int i=0;i<mListWidget->count();)
		{
			QListWidgetItem* item = mListWidget->item(i);
			QWidget* widget = mListWidget->itemWidget(item);
			mListWidget->removeItemWidget(item);
			if(item != CNull){
				delete item;
			}
			if(widget != CNull){
				delete widget;
			}
			//QCoreApplication::processEvents();
		}
		mMapData.clear();
		m_totalCountLbl->setText(transfer(""));
	}

	int SearchResultListWidget::addItemToList( const data::SearchResultInfo& data )
	{
		QListWidgetItem* item = new QListWidgetItem();
		SearchResultListWidgetItem* widget = new SearchResultListWidgetItem(this);
		QString head = data.avatar.c_str();
		if(head.isEmpty()){
			head = (data::USER_TYPE==data.resultType) ? DEFAULT_AVATAR : (data::GROUP_TYPE==data.resultType ? DEFAULT_GROUP : DEFAULT_APP);
		}
		QString name = QString::fromUtf8(data.name.c_str());
		bool isShowAddBtn = false;
		QString tipInfo;
		QString addBtnTxt = transfer("+ 好友");
		if ( data::GROUP_TYPE == data.resultType) 
		{
			isShowAddBtn = !data.isGroupMem;
			tipInfo = isShowAddBtn ? "": transfer("已经是群成员");
			addBtnTxt = transfer("+ 群");
		}
		else if(data::USER_TYPE == data.resultType)
		{
			isShowAddBtn = (data::IS_NOTBUDDY == data.buddyType ? true : false);
			if (data::IS_BUDDY == data.buddyType)
			{
				tipInfo = transfer("已经是好友");
			}
			else if (data::IS_MYSELF == data.buddyType)
			{
				tipInfo = transfer("不能添加自己");
			}
		}
		else if (data::APP_TYPE == data.resultType)
		{
			isShowAddBtn = (data::IS_NOTBUDDY == data.buddyType ? true : false);
			if (data::IS_BUDDY == data.buddyType)
			{
				tipInfo = transfer("已关注");
			}
			addBtnTxt = transfer("+ 关注");
		}
		widget->setData(head,name, isShowAddBtn);
		widget->setExistInfo(tipInfo);
		widget->setId(data.targetid);
		widget->setAddBtnText(addBtnTxt);

		mListWidget->addItem(item);
		
		mListWidget->setItemWidget(item,widget);
		mMapData.insert(data.targetid, data);
		connect(widget, SIGNAL(signalAddContactBtnClicked(int64, void*)), this, SLOT(onAddContactBtnClicked(int64, void*)));

		return mListWidget->row(item);
	}
	void SearchResultListWidget::onAddContactBtnClicked(int64 targetId, void* itemWidget)
	{
		if (mMapData.contains(targetId))
		{
			SearchResultListWidgetItem* pWidget = (SearchResultListWidgetItem*)itemWidget;
			if (mMapData[targetId].resultType == data::APP_TYPE)
			{
				//公众号直接关注
				pWidget->setExistInfo(transfer("已关注"));
				mContactControl->AddContact(targetId, "", "", CBind(&SearchResultListWidget::signalSerAddAppContact, this, 
					CPlaceholders  _1));
			}
			else
			{
				emit signalAddContact(mMapData[targetId]);
			}
		}

	}
	void SearchResultListWidget::onSerAddAppContact(int err)
	{
		BEGIN;
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"errCode=%d",err);
		}
		END;
	}

}
