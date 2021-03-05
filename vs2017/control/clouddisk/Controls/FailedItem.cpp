#include "FailedItem.h"
#include "QClickLabel.h"
#include "PushButton.h"
#include "MyLineEdit.h"
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>
#include "MyMessageBox.h"
namespace ui{
	FailedItem::FailedItem(QWidget *parent) :QWidget(parent)
	, m_retryBtn(nullptr)
	, m_result(nullptr)
	, m_mainlayout(nullptr)
	, m_localId(0)
	{
		setMouseTracking(true);

		m_retryBtn = new PushButton(this, true);
		m_mainlayout = new QHBoxLayout(this);
		m_result = new QLabel(this);
		m_result->setText("");

		m_retryBtn->setPicName(QString(":/img/retry"));
		 
		m_retryBtn->setToolTip(QString::fromUtf8("重试")); //重试
		m_retryBtn->setObjectName("retrybtn");

		
		m_mainlayout->setSpacing(0);
		m_mainlayout->setContentsMargins(0, 0, 0, 0);
		m_mainlayout->setAlignment(Qt::AlignLeft);
		m_mainlayout->addWidget(m_result);
		m_mainlayout->addWidget(m_retryBtn);
		m_mainlayout->addStretch();
		setLayout(m_mainlayout);


		connect(m_retryBtn, SIGNAL(clicked()), this, SLOT(btnClicked()));
	}
	FailedItem::~FailedItem(){

	}
	void FailedItem::setItemRow(int row){
		m_row = row;
	}
	int FailedItem::getItemRow()const{
		return m_row;
	}
	void FailedItem::onRetry(){
		emit signalRetry(m_localId);
	}
	void FailedItem::btnClicked(){
		emit display(0, m_localId);
		emit signalRetry(m_localId);
	}
	void FailedItem::onCancel(int64 localid){
		m_localId = localid;
		m_result->setText(QString::fromUtf8("文件传输失败"));
	}
	void FailedItem::onError(int64 localid){
		m_localId = localid;
		m_result->setText(QString::fromUtf8("文件传输失败"));
	}
}