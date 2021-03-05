#include "UpdateFinishWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include "controls/PushButton.h"
#include "../common/Common.h"
namespace ui{
	UpdateFinishWindow::UpdateFinishWindow(QWidget *parent)
		: BaseDialog(parent)
	{
		setFixedSize(260,120);
		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(10,10,10,10);
		mainLayout->setSpacing(0);
		setLayout(mainLayout);

		mBtnClose = new PushButton(this);
		mBtnClose->setPicName(QString(":/login/close"));

		//������
		QHBoxLayout* titleLayout = new QHBoxLayout(this);
		titleLayout->setContentsMargins(10,0,0,0);
		titleLayout->setSpacing(0);
		QLabel* logoText = new QLabel(this);
		logoText->setText(transfer("����"));
		logoText->setObjectName("whiteLabel");
		titleLayout->addWidget(logoText,0,Qt::AlignLeft);
		titleLayout->addStretch();
		titleLayout->addWidget(mBtnClose,0,Qt::AlignRight);
		QWidget* widget = new QWidget(this);
		widget->setObjectName("updateTitleBg");
		widget->setMinimumHeight(30);
		widget->setMaximumHeight(30);
		widget->setLayout(titleLayout);
		mainLayout->addWidget(widget);

		//��ʾ��
		QLabel* lblText = new QLabel(this);
		lblText->setText(transfer("����������ɣ��´�������װ��Ч"));
		mBtnRestart = new QPushButton(this);
		mBtnRestart->setText(transfer("��������"));
		mBtnRestart->setObjectName("updateCancel");
		mBtnRestart->setMinimumSize(80,28);
		QVBoxLayout* centerLayout = new QVBoxLayout(this);
		centerLayout->setContentsMargins(20,0,10,10);
		centerLayout->setSpacing(0);
		centerLayout->addWidget(lblText);
		centerLayout->addWidget(mBtnRestart,0,Qt::AlignRight);
		widget = new QWidget(this);
		widget->setLayout(centerLayout);
		mainLayout->addWidget(widget);

		connect(mBtnClose,SIGNAL(clicked()),this,SLOT(close()));
		connect(mBtnRestart,SIGNAL(clicked()),this,SIGNAL(RestartApp()));

		this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::X11BypassWindowManagerHint|Qt::WindowStaysOnTopHint);
		//���㴰����ʾλ��
		QRect screenrect = QApplication::desktop()->availableGeometry();
		int x = screenrect.width()-this->width();
		int y = screenrect.height()-this->height();
		this->move(x,y);
	}

	UpdateFinishWindow::~UpdateFinishWindow()
	{

	}
}
