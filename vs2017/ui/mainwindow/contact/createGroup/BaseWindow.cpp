#include "BaseWindow.h"
#include "PushButton.h"
#include "headimage.h"
namespace ui{
	BaseWindow::BaseWindow(QWidget *parent)
		: BaseDialog(parent)
	{
		mMainLayout = new QVBoxLayout(this);
		mMainLayout->setSpacing(0);
		mMainLayout->setContentsMargins(10,10,10,10);
		setLayout(mMainLayout);
		
		//БъЬт
		titleWidget();
	}

	BaseWindow::~BaseWindow()
	{

	}

	void BaseWindow::setTitle( QString title )
	{
		mTitle->setText(title);
	}

	void BaseWindow::SetBtnVisible(int index, bool isVisible)
	{
		if (index == 0)
		{
			//mBtnMin->setVisible(isVisible);
		}
	}


	void BaseWindow::titleWidget()
	{
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setContentsMargins(6,0,0,0);

		HeadImage* logo = new HeadImage(this);
		logo->setAvatarPath(":/base/tray");
		logo->setFixedSize(18,18);
		mTitle = new QLabel(this);
		mTitle->setObjectName("whiteLabel");

		mBtnClose = new PushButton(this);
		mBtnClose->setPicName(":/login/close");
		connect(mBtnClose, SIGNAL(clicked()), this, SIGNAL(closeClicked()));

		layout->addWidget(logo);
		layout->addWidget(mTitle);
		layout->addStretch();
	
		layout->addWidget(mBtnClose);
		QLabel*widget = new QLabel(this);
		widget->setLayout(layout);
		widget->setObjectName("loginBackground");
		widget->setMinimumHeight(30);
		mMainLayout->addWidget(widget);
	}

	void BaseWindow::onSerMaxShow()
	{
		this->showMaximized();
	}
}
