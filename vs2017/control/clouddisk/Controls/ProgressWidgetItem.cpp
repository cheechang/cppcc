#include "ProgressWidgetItem.h"
#include "QClickLabel.h"
#include "PushButton.h"
#include "MyLineEdit.h"
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>
#include "MyMessageBox.h"
#include <QStackedLayout>
#include "ProgressingItem.h"
#include "FailedItem.h"
#include "SuccessItem.h"
namespace ui{
	ProgressWidgetItem::ProgressWidgetItem(QWidget *parent) :QWidget(parent)
	, m_row(-1)
	, m_pro(0)
	, m_stack(nullptr)
	, m_failedItem(nullptr)
	, m_progressingItem(nullptr)
	, m_successItem(nullptr)
	, m_localId(0)
	{
		setMouseTracking(true);

		m_stack = new QStackedLayout(this);
		m_progressingItem = new ProgressingItem(this);
		m_successItem = new SuccessItem(this);
		m_failedItem = new FailedItem(this);
		m_stack->addWidget(m_progressingItem);
		m_stack->addWidget(m_failedItem);
		m_stack->addWidget(m_successItem);		
		m_mainlayout = new QVBoxLayout(this);
		m_stack->setCurrentIndex(0);
		m_mainlayout->addLayout(m_stack);
		setLayout(m_mainlayout);

		connect(this, SIGNAL(signalProgress(int32, int64, std::string&)), m_progressingItem, SLOT(onProgress(int32, int64, std::string&)));
		connect(m_progressingItem, SIGNAL(signalPath(QString,int64)), m_successItem, SLOT(onGetpath(QString,int64)));
		connect(m_progressingItem, SIGNAL(display(int,int64)), this, SLOT(onSetCurrentStack(int, int64)));
		connect(m_failedItem, SIGNAL(display(int,int64)), this, SLOT(onSetCurrentStack(int,int64)));
		
		//ÖØÊÔ
		connect(m_failedItem, SIGNAL(signalRetry(int64)), this, SLOT(onRetry(int64)));
		//È¡Ïû
		connect(m_progressingItem, SIGNAL(signalCancel(int64)), this, SIGNAL(signalCancle(int64)));
		connect(m_progressingItem, SIGNAL(signalCancel(int64)), m_failedItem, SLOT(onCancel(int64)));
		
		connect(this, SIGNAL(signalDecryptFile(int64, model::CloudFileInfo&, std::string&)), m_successItem, SLOT(onDecryptFile(int64, model::CloudFileInfo&, std::string&)));

		connect(this, SIGNAL(signalError(int64)), m_failedItem, SLOT(onError(int64)));
	}
	ProgressWidgetItem::~ProgressWidgetItem(){

	}
	void ProgressWidgetItem::setItemRow(int row){
		m_row = row;
	}
	int ProgressWidgetItem::getItemRow()const{
		return m_row;
	}
	void ProgressWidgetItem::onRetry(int64 localid){
		emit signalRetry(localid);
	}
	void ProgressWidgetItem::onCancel(int64 localid){
		emit signalCancle(localid);
	}
	void ProgressWidgetItem::onFailed(int64 localid){
		if (m_localId == localid){
			m_stack->setCurrentIndex(1);
			emit signalError(localid);
		}
	}

	void ProgressWidgetItem::onProgress(int32 pro, int64 localId, std::string& info){
		if (!m_localId){
			m_localId = localId;
		}
		emit(signalProgress(pro, localId, info));	
	}

	void ProgressWidgetItem::onSetCurrentStack(int index,int64 localid){
		if (m_localId == localid){
			m_stack->setCurrentIndex(index);
		}
	}
}