#include "SearchContactWindow.h"
#include <QApplication>
#include "controls/PushButton.h"
#include "SearchResultListWidget.h"
#include "AddContactWindow.h"
#include "../../../common/Common.h"
#include <log.h>
namespace ui{
	SearchContactWindow::SearchContactWindow(QWidget *parent)
		: BaseDialog(parent)
	{
		setFixedSize(540,500);
		setModal(true);
		setAttribute();
		layout();
	}

	SearchContactWindow::~SearchContactWindow()
	{
		if (m_pKeyLineEdit)
		{
			m_pKeyLineEdit->deleteLater();
		}
		if (m_pCloseButton)
		{
			m_pCloseButton->deleteLater();
		}
		if (m_pBackground)
		{
			m_pBackground->deleteLater();
		}
		if (m_pTitle)
		{
			m_pTitle->deleteLater();
		}
		if (m_pBtnSearch)
		{
			m_pBtnSearch->deleteLater();
		}
		if (m_pTitleBtnLayout)
		{
			m_pTitleBtnLayout->deleteLater();
		}
	}
	
	void SearchContactWindow::setAttribute()
	{
		//标题栏
		m_pCloseButton = new PushButton(this);
		m_pBackground  = new QLabel(this);
		m_pTitleBtnLayout = new QHBoxLayout();
		m_pMainLayout = new QVBoxLayout(this);
		m_pMainLayout->setSpacing(10);
		m_pMainLayout->setContentsMargins(20, 5, 20 ,20);

		m_pBackground->setTextFormat(Qt::PlainText);
		m_pBackground->setScaledContents(true);
		m_pBackground->setObjectName("loginBackground");
		m_pCloseButton->setPicName(QString(":/login/close"));

		m_pTitle = new QLabel(this);
		m_pTitle->setText(transfer("查找"));
		m_pTitle->setObjectName("whiteLabel");
		//输入框
		m_pKeyLineEdit = new QLineEdit(this);
		m_pKeyLineEdit->setObjectName("accountEdit");
		m_pKeyLineEdit->setFixedSize(QSize(260,30));
		m_pKeyLineEdit->setFocus();
		//清空输入框按钮
		m_pClearKeyBtn = new PushButton(this);
		m_pClearKeyBtn->setPicName(":/chat/delete");
		m_pClearKeyBtn->setVisible(false);
		m_pClearKeyBtn->move(332, 45);
		
		//确定
		m_pBtnSearch = new QPushButton(this);
		m_pBtnSearch->setObjectName("sendbtn");
		m_pBtnSearch->setText(transfer("查找"));
		m_pBtnSearch->setFixedSize(70, 30);

		m_resultListWidget = new SearchResultListWidget(this);
		

		connect(m_pCloseButton,SIGNAL(clicked()),this,SLOT(close()));
		connect(m_pBtnSearch, SIGNAL(clicked()), this, SLOT(onSearchBtnClicked()));
		connect(m_pKeyLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onLineEditChanged(const QString&)));
		connect(m_pClearKeyBtn, SIGNAL(clicked()), this, SLOT(onClearKeyBtnClicked()));

		connect(m_resultListWidget, SIGNAL(signalAddContact(const data::SearchResultInfo)), this ,SLOT(onAddContact(const data::SearchResultInfo)));

	}

	void SearchContactWindow::layout()
	{
		//标题栏
		m_pTitleBtnLayout->setContentsMargins(10, 0, 0, 0);
		m_pTitleBtnLayout->addWidget(m_pTitle);
		m_pTitleBtnLayout->addStretch();
		m_pTitleBtnLayout->addWidget(m_pCloseButton, 0, Qt::AlignTop);

		//背景图
		m_pBackground->setLayout(m_pTitleBtnLayout);
		m_pBackground->setMinimumSize(this->width()-20, m_pCloseButton->height());
		m_pBackground->move(10,0);

		//输入框按钮布局
		QHBoxLayout* pFirstRowLayout =new QHBoxLayout();
		pFirstRowLayout->setSpacing(20);
		pFirstRowLayout->setAlignment(Qt::AlignHCenter);
		pFirstRowLayout->setContentsMargins(1, 5, 1 ,5);

		pFirstRowLayout->addWidget(m_pKeyLineEdit);
		pFirstRowLayout->addWidget(m_pBtnSearch);
	
		m_pMainLayout->addLayout(m_pTitleBtnLayout);
		m_pMainLayout->addSpacing(30);
		m_pMainLayout->addLayout(pFirstRowLayout);
		m_pMainLayout->addWidget(m_resultListWidget);


		setLayout(m_pMainLayout);

	}
	void SearchContactWindow::onSearchBtnClicked()
	{
		QString strKey = m_pKeyLineEdit->text();
		strKey = strKey.trimmed();
		if ( !strKey.isEmpty())
		{
			m_resultListWidget->searchKey(strKey);
		}
	}
	void SearchContactWindow::onLineEditChanged(const QString &text)
	{
		if (text.isEmpty())
		{
			m_pClearKeyBtn->setVisible(false);
		}
		else
		{
			m_pClearKeyBtn->setVisible(true);
		}
	}
	void SearchContactWindow::onClearKeyBtnClicked()
	{
		m_pKeyLineEdit->clear();
		m_resultListWidget->clearList();
		m_pClearKeyBtn->setVisible(false);
	}
	void SearchContactWindow::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
			onSearchBtnClicked();
	}
	void SearchContactWindow::onAddContact(const data::SearchResultInfo data)
	{
		m_addContactWin = new AddContactWindow(this);
		m_addContactWin->InitData(data);
		m_addContactWin->show();
	}

}