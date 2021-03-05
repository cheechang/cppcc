#include "loadmsgwidget.h"
#include "common/Common.h"
#include "detail/loadindicator.h"
#include <interface/Defines.h>
LoadMsgWidget::LoadMsgWidget(QGraphicsItem *parent):QGraphicsProxyWidget(parent),
m_loadIndicator(CNull)
{
	m_loadIndicator = new LoadIndicator();
	m_loadIndicator->setLoading(false);
	connect(m_loadIndicator, SIGNAL(startLoading()), this, SIGNAL(getHistoryMsg()));
	this->setWidget(m_loadIndicator);
}
LoadMsgWidget::~LoadMsgWidget()
{
	if (CNull != m_loadIndicator)
	{
	   m_loadIndicator->deleteLater();
	}
}

void LoadMsgWidget::setNoMoreState(bool isClicked)
{
	m_loadIndicator->setNoMoreDataState(isClicked);
}

int LoadMsgWidget::type() const
{
	return QGraphicsProxyWidget::type();
}
 void LoadMsgWidget::setLoading(bool loading){
	 if ( CNull != m_loadIndicator)
	 {
		 m_loadIndicator->setLoading(loading);
	 }
 }
 void LoadMsgWidget::setNoMoreData(){
	 if ( CNull != m_loadIndicator)
	 {
		 m_loadIndicator->setNoMoreData();
	 }
 }

 bool LoadMsgWidget::isLoading()
 {
	 return m_loadIndicator->loading();
 }

 bool LoadMsgWidget::hasMoreData()
 {
	 return m_loadIndicator->hasMoreData();
 }
