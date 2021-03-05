#include "ModifyFriendRemarkWindow.h"
#include <QApplication>
#include "controls/PushButton.h"
#include "../../../common/Common.h"
namespace ui{
	ModifyFriendRemarkWindow::ModifyFriendRemarkWindow(QWidget *parent,QString text)
		: BaseDialog(parent)
	{
		setFixedSize(328,155);
		setModal(true);
		setAttribute();
		layout();

		m_pRemarkLineEdit->setText(text);
	}

	ModifyFriendRemarkWindow::~ModifyFriendRemarkWindow()
	{
		if (m_pRemarkLineEdit)
		{
			m_pRemarkLineEdit->deleteLater();
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
		if (m_pBtnOk)
		{
			m_pBtnOk->deleteLater();
		}
		if (m_pTitleBtnLayout)
		{
			m_pTitleBtnLayout->deleteLater();
		}
	}

	void ModifyFriendRemarkWindow::setAttribute()
	{
		//������
		m_pCloseButton = new PushButton(this);
		m_pBackground  = new QLabel(this);
		m_pTitleBtnLayout = new QHBoxLayout(this);
		m_pBackground->setTextFormat(Qt::PlainText);
		m_pBackground->setScaledContents(true);
		m_pBackground->setObjectName("loginBackground");
		m_pCloseButton->setPicName(QString(":/login/close"));
		m_pTitleBtnLayout = new QHBoxLayout(this);
		
		m_pTitle = new QLabel(this);
		m_pTitle->setText(transfer("�޸ı�ע"));
		m_pTitle->setObjectName("whiteLabel");
		//�����
		m_pRemarkLineEdit = new QLineEdit(this);
		m_pRemarkLineEdit->setObjectName("accountEdit");
		m_pRemarkLineEdit->setFixedSize(QSize(260,30));
		m_pRemarkLineEdit->setMaxLength(24);

		//ȷ��
		m_pBtnOk = new QPushButton(this);
		m_pBtnOk->setObjectName("sendbtn");
		m_pBtnOk->setText(transfer("ȷ��"));
		m_pBtnOk->setFixedWidth(60);

		connect(m_pCloseButton,SIGNAL(clicked()),this,SLOT(close()));
		connect(m_pBtnOk,SIGNAL(clicked(bool)),this,SLOT(onOk()));
	}

	void ModifyFriendRemarkWindow::layout()
	{
		//������
		m_pTitleBtnLayout->setContentsMargins(10, 0, 0, 0);
		m_pTitleBtnLayout->addWidget(m_pTitle);
		m_pTitleBtnLayout->addStretch();
		m_pTitleBtnLayout->addWidget(m_pCloseButton, 0, Qt::AlignTop);

		//����ͼ
		m_pBackground->setLayout(m_pTitleBtnLayout);
		m_pBackground->setMinimumSize(308, m_pCloseButton->height());
		m_pBackground->move(10,0);

		//�����
		m_pRemarkLineEdit->move(30,60);
		m_pBtnOk->move(230,100);
	}

	void ModifyFriendRemarkWindow::onOk()
	{
		emit textChanged(m_pRemarkLineEdit->text());
		close();
	}

	void ModifyFriendRemarkWindow::showWin( QString text )
	{
		m_pRemarkLineEdit->setText(text);
		this->show();
		m_pRemarkLineEdit->setFocus();
	}

	QString ModifyFriendRemarkWindow::text()
	{
		return m_pRemarkLineEdit->text();
	}

}