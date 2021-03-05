#include "MainWeb.h"
#include <QCoreApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QIcon>
#include <QLayout>
#include "common/common.h"
#include "log.h"
#include  "controls/PushButton.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../common/Common.h"
#include <QStackedWidget>
#include <QPushButton>
#include <QWidget>
#include "headimage.h"
#include "PushButton.h"
namespace ui{
	enum { MaxLimitTimes = 15 };
	enum { MaxLimitSpace = 5 };
	MainWeb::MainWeb(QWidget *parent) :BaseDialog(parent), m_is_running(false), m_isMax(false){
		this->setMinimumSize(1000, 700);
		setWindowIcon(QIcon(":/base/linkdood"));
		connect(this, SIGNAL(closeClicked()), this, SLOT(close()));
		//this->setContextMenuPolicy(Qt::NoContextMenu);
		mMainLayout = new QVBoxLayout(this);
		mTitleLayout = new QHBoxLayout(this);
		workbench_widget = new Workbench(this);

		HeadImage* logo = new HeadImage(this);
		logo->setAvatarPath(":/base/tray");
		logo->setFixedSize(18, 18);

		mTitleName = new QLabel(this);
		mTitleName->setObjectName("whiteLabel");
		mTitleName->setText(transfer("政协办公"));
		
		mBtnMin = new PushButton(this);
		mBtnMin->setPicName(":/title/min");
		connect(mBtnMin, SIGNAL(clicked()), this, SLOT(onSerMin()));
		//mBtnMin->setVisible(false);

		mBtnMax = new PushButton(this);
		mBtnMax->setPicName(":/title/max");
		connect(mBtnMax, SIGNAL(clicked()), this, SLOT(onSerMax()));

		mBtnClose = new PushButton(this);
		mBtnClose->setPicName(":/title/close");
		connect(mBtnClose, SIGNAL(clicked()), this, SLOT(close()));

		mTitleLayout->addWidget(logo);
		mTitleLayout->addWidget(mTitleName);
		mTitleLayout->addStretch();
		mTitleLayout->addWidget(mBtnMin,0,Qt::AlignCenter);
		mTitleLayout->addWidget(mBtnMax, 0, Qt::AlignCenter);
		mTitleLayout->addWidget(mBtnClose, 0, Qt::AlignCenter);
		mTitleLayout->setContentsMargins(5,0,5,0);
		mTitleLayout->setSpacing(5);

		QLabel* backlabl = new QLabel(this);
		backlabl->setLayout(mTitleLayout);
		backlabl->setObjectName("loginBackground");
		backlabl->setMinimumHeight(30);

		QVBoxLayout *center_layout = new QVBoxLayout(this);
		center_layout->addWidget(workbench_widget);
		center_layout->setSpacing(0);
		center_layout->setContentsMargins(2,2,2,2);

		QVBoxLayout *main_layout = new QVBoxLayout(this);
		main_layout->addWidget(backlabl);
		main_layout->addLayout(center_layout);
		main_layout->setSpacing(0);
		main_layout->setContentsMargins(0, 0, 0, 0);
		mMainLayout->addLayout(main_layout);

		this->setWindowModality(Qt::NonModal);
		connect(workbench_widget, SIGNAL(signalSerOpenChatWidget(int64)), this, SIGNAL(signalSerOpenChatWidget(int64)));

		/*	widget1 = new QWidget();
		widget2 = new QWidget();*/

		//StackWidget = new QStackedWidget();
	 //   layout1 = new QHBoxLayout();
		//btn1 = new QPushButton(transfer("btn1"));
		//btn2 = new QPushButton(transfer("btn2"));

		//connect(btn1,SIGNAL(clicked()),this, SLOT(onSerClicked1()));
		//connect(btn2, SIGNAL(clicked()), this, SLOT(onSerClicked2()));

		//mlbl = new QLabel(transfer("西湖的水，水漫金山寺"));
		//layout1->addWidget(mlbl);
		//

		//widget1->setLayout(center_layout);

		//widget2->setLayout(layout1);

		//StackWidget->addWidget(workbench_widget);
		//StackWidget->addWidget(widget2);

		//StackWidget->setCurrentWidget(widget2);

		//QVBoxLayout *main_layout = new QVBoxLayout(this);
		//main_layout->addWidget(btn1);
		//main_layout->addWidget(btn2);
		//main_layout->addWidget(StackWidget);
		//main_layout->setSpacing(0);
		//main_layout->setContentsMargins(0, 0, 0, 0);
		//mMainLayout->addLayout(main_layout);

		//title = new WinTitleWidget();

		}
	MainWeb::~MainWeb(){

	}

	void MainWeb::paintEvent(QPaintEvent *event)
	{
		BaseDialog::paintEvent(event);
	}

	void MainWeb::onSerClose()
	{

	}

	void MainWeb::onSerMin()
	{
		this->showMinimized();
	}

	void MainWeb::onSerMax()
	{
		QRect screenrect = QApplication::desktop()->availableGeometry();
		if (!m_isMax)
		{
			mBtnMax->setPicName(":/title/restore");
			this->setGeometry(-SHADOW_WIDTH, -SHADOW_WIDTH, screenrect.width() + 2 * SHADOW_WIDTH, screenrect.height() + 2 * SHADOW_WIDTH);
			m_isMax = true;
		}
		else
		{
			int x = screenrect.x() + (screenrect.width() - WINDOW_WIDTH) / 2;
			int y = screenrect.y() + (screenrect.height() - WINDOW_HEIGHT) / 2;
			this->setGeometry(x, y, WINDOW_WIDTH, WINDOW_HEIGHT);
			mBtnMax->setPicName(QString(":/title/max"));
			m_isMax = false;
		}
	}
















	/*void MainWeb::onSerClicked1()
	{
		StackWidget->setCurrentWidget(workbench_widget);
	}

	void MainWeb::onSerClicked2()
	{
		StackWidget->setCurrentWidget(widget2);
	}*/
}