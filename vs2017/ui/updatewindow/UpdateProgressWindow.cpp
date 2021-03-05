#include "UpdateProgressWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "controls/PushButton.h"
#include "../common/Common.h"
namespace ui{
	UpdateProgressWindow::UpdateProgressWindow(QWidget *parent)
		: BaseDialog(parent)
	{
		setFixedSize(450,180);
		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(10,10,10,10);
		mainLayout->setSpacing(0);
		setLayout(mainLayout);

		mBtnClose = new PushButton(this);
		mBtnClose->setPicName(QString(":/login/close"));

		mBtnMin = new PushButton(this);
		mBtnMin->setPicName(QString(":/login/min"));

		mBtnExit = new QPushButton(this);
		mBtnExit->setText(transfer("取消"));
		mBtnExit->setObjectName("updateCancel");
		mBtnExit->setMinimumSize(80,28);

		mBtnReDownLoad = new QPushButton(this);
		mBtnReDownLoad->setText(transfer("重新下载"));
		mBtnReDownLoad->setObjectName("updateCancel");
		mBtnReDownLoad->setMinimumSize(80,28);
		mBtnReDownLoad->setVisible(false);

		mProgressBar = new QProgressBar(this);
		mProgressBar->setMinimumSize(392,10);
		mProgressBar->setMaximumSize(392,10);
		mProgressBar->setObjectName("updateProgrssBar");
		mLblProgress = new QLabel(this);
		mLblProgress->setText(transfer("总进度：0%"));
		merrtip      = new QLabel(this);
		merrtip->setObjectName("redlabel");
		mProgressBar->setRange(0,100);
		mProgressBar->setValue(0);
		mProgressBar->setTextVisible(false);
		//标题栏
		QHBoxLayout* titleLayout = new QHBoxLayout(this);
		titleLayout->setContentsMargins(10,0,0,0);
		titleLayout->setSpacing(0);
		QLabel* logoText = new QLabel(this);
		logoText->setText(transfer("正在准备升级数据"));
		logoText->setObjectName("whiteLabel");
		titleLayout->addWidget(logoText,0,Qt::AlignLeft);
		titleLayout->addStretch();
		titleLayout->addWidget(mBtnMin);
		titleLayout->addWidget(mBtnClose,0,Qt::AlignRight);
		QWidget* widget = new QWidget(this);
		widget->setObjectName("updateTitleBg");
		widget->setMinimumHeight(30);
		widget->setMaximumHeight(30);
		widget->setLayout(titleLayout);
		mainLayout->addWidget(widget);

		//进度区域
		QVBoxLayout* centerLayout = new QVBoxLayout(this);
		centerLayout->setContentsMargins(30,20,0,0);
		centerLayout->setSpacing(0);
		centerLayout->addWidget(mLblProgress);
		centerLayout->addWidget(mProgressBar);
		centerLayout->addWidget(merrtip);
		centerLayout->setSpacing(5);
		widget = new QWidget(this);
		widget->setLayout(centerLayout);
		mainLayout->addWidget(widget);

		//按钮区域
		QHBoxLayout* btnsLayout = new QHBoxLayout(this);
		btnsLayout->setContentsMargins(0,10,10,10);
		btnsLayout->setSpacing(20);
		btnsLayout->addStretch();
		btnsLayout->addWidget(mBtnExit);
		btnsLayout->addWidget(mBtnReDownLoad);

		widget = new QWidget(this);
		widget->setLayout(btnsLayout);
		mainLayout->addWidget(widget);

		connect(mBtnMin, SIGNAL(clicked()), this, SLOT(onBtnCloseClicked()));
		connect(mBtnClose,SIGNAL(clicked()),this,SLOT(onBtnCloseClicked()));
		connect(mBtnExit,SIGNAL(clicked()),this,SIGNAL(CancelDownLoad()));
		connect(mBtnReDownLoad,SIGNAL(clicked()),this,SLOT(onBtnReDownLoadClicked()));
		this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::X11BypassWindowManagerHint|Qt::WindowStaysOnTopHint);
	}

	UpdateProgressWindow::~UpdateProgressWindow()
	{

	}

	void UpdateProgressWindow::updateProgress( int value )
	{
		QString progtext =transfer("总进度：%1%").arg(QString::number(value));
		mProgressBar->setValue(value);
		mLblProgress->setText(progtext);
	}
	void UpdateProgressWindow::seterrtip(ErrType type){
		QString errInfo;
		switch(type){
		case ERR_DOWNLOADFAILED:
			{
				errInfo = transfer("由于网络原因升级包下载失败,请检查您的网络是否正常,稍后重试!");
				mBtnExit->setVisible(false);
				mBtnReDownLoad->setVisible(true);
				break;
			}
		case ERR_CHECKCOMPLETEFAILED:
			{
				errInfo = transfer("升级包安全性校验失败，请联系管理员!");
				break;
			}
		case ERR_USERCANCEL:
			{
				errInfo = transfer("用户取消升级包下载");
				break;
			}
		default:
			{
				errInfo = transfer("未知原因");
			}
		}
		emit ShowErrInfo(type);
		merrtip->setText(errInfo);
	}
	void UpdateProgressWindow::ShowWindow(){
		this->showNormal();
		this->raise();
		this->activateWindow();
		if (!this->isVisible())
		{
			this->setVisible(true);
		}
	}
	void UpdateProgressWindow::onBtnCloseClicked(){
		this->showMinimized();
		this->hide();
	}
	void UpdateProgressWindow::onShow(){
		ShowWindow();
	}
	void UpdateProgressWindow::onBtnReDownLoadClicked(){
		mBtnExit->setVisible(true);
		mBtnReDownLoad->setVisible(false);
		merrtip->setText("");
		emit ReDownLoad();
	}
}
