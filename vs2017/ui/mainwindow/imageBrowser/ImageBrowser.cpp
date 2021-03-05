#include "ImageBrowser.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QDesktopServices>

#include "../controls/PushButton.h"
#include "../controls/ToolButton.h"
#include "../common/Common.h"
namespace ui{
	ImageBrowser* ImageBrowser::mPInstance = CNull;
	int ImageBrowser::mCurrentImgIndex = 0;
	QList<QString> ImageBrowser::mImgs;
	ImageHandlerWidget* ImageBrowser::mImageHandlerWidget = CNull;

	ImageBrowser::ImageBrowser(QWidget *parent)
		: BaseDialog(parent)
	{
		this->setSupportStretch(false);
		this->setMouseTracking(true);
		this->setMinimumSize(720,620);
		mMainLayout = new QVBoxLayout(this);
		mMainLayout->setContentsMargins(0,0,0,0);
		mMainLayout->setSpacing(0);
		setLayout(mMainLayout);
		mIsMax = false;
		initTitleWidget();
		initImagePanelWidget();
		initToolWidget();

		mTimer.setInterval(500);
		connect(&mTimer,SIGNAL(timeout()),this,SLOT(showPags()));
		mTimer.start();
	}

	ImageBrowser::~ImageBrowser()
	{
		mTimer.stop();
	}

	void ImageBrowser::initToolWidget()
	{
		mBtnRotate = new PushButton(this);
		mBtnDownload = new PushButton(this);
		mBtnZoomIn = new PushButton(this);
		mBtnZoomOut = new PushButton(this);
		mBtnZoomOut->setPicName(":/pictureView/zoomOut");
		mBtnDownload->setPicName(":/pictureView/download");
		mBtnRotate->setPicName(":/pictureView/rotate");
		mBtnZoomIn->setPicName(":/pictureView/zoomIn");
		mBtnZoomIn->setToolTip(transfer("放大"));
		mBtnZoomOut->setToolTip(transfer("缩小"));
		mBtnRotate->setToolTip(transfer("旋转"));
		mBtnDownload->setToolTip(transfer("另存为"));
		mBtnZoomIn->setCursor(Qt::PointingHandCursor);
		mBtnZoomOut->setCursor(Qt::PointingHandCursor);
		mBtnDownload->setCursor(Qt::PointingHandCursor);
		mBtnRotate->setCursor(Qt::PointingHandCursor);

		connect(mBtnZoomIn, SIGNAL(clicked()), this, SLOT(onZoomIn()));
		connect(mBtnZoomOut, SIGNAL(clicked()), this, SLOT(onZoomOut()));
		connect(mBtnRotate, SIGNAL(clicked()), this, SLOT(onRotate()));
		connect(mBtnDownload, SIGNAL(clicked()), this, SLOT(onDownload()));

		QHBoxLayout* toolLayout = new QHBoxLayout(this);
		toolLayout->setContentsMargins(0,0,0,0);
		toolLayout->setSpacing(20);
		toolLayout->addStretch();
		toolLayout->addWidget(mBtnZoomIn);
		toolLayout->addWidget(mBtnZoomOut);
		toolLayout->addWidget(mBtnRotate);
		toolLayout->addWidget(mBtnDownload);
		toolLayout->addStretch();
		QWidget* widget = new QWidget(this);
		widget->setLayout(toolLayout);
		widget->setMinimumHeight(40);
		widget->setStyleSheet("QWidget{background:rgb(245,245,245);}");
		mMainLayout->addStretch();
		mMainLayout->addWidget(widget);
	}

	void ImageBrowser::onDownload()
	{
		QString fileName = mImgs.at(mCurrentImgIndex);
		QFileInfo fileInfo(fileName);
		QString lastPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+QString("\\")+fileInfo.fileName();
		QString filePath = QFileDialog::getSaveFileName(this, transfer("文件另存为"),lastPath,transfer("文件(*.")+fileInfo.suffix()+")");
		QImage img(fileName);
		img.save(filePath);
	}

	void ImageBrowser::onZoomIn()
	{
		mImageHandlerWidget->zoomIn();
	}

	void ImageBrowser::onZoomOut()
	{
		mImageHandlerWidget->zoomOut();
	}

	void ImageBrowser::onRotate()
	{
		mImageHandlerWidget->rotate();
	}

	void ImageBrowser::paintEvent( QPaintEvent *event )
	{
		if (mImageHandlerWidget != CNull)
		{
			mImageHandlerWidget->setFixedHeight(height() - 77);
		}
		if (mBtnLeft != CNull)
		{
			mBtnLeft->move(20,(height()-mBtnLeft->height())/2);
		}
		if (mBtnRight != CNull)
		{
			mBtnRight->move(width()-20-mBtnRight->width(),(height()-mBtnRight->height())/2);
		}
		BaseDialog::paintEvent(event);	
	}

	void ImageBrowser::leaveEvent( QEvent *e )
	{
		BaseDialog::leaveEvent(e);
	}

	void ImageBrowser::onBtnLeft()
	{
		mCurrentImgIndex--;
		if(mCurrentImgIndex <0){
			mCurrentImgIndex = 0;
		}
		mImageHandlerWidget->setPixmap(QPixmap(mImgs.at(mCurrentImgIndex)),mIsMax);
	}

	void ImageBrowser::onBtnRight()
	{
		mCurrentImgIndex++;
		if(mCurrentImgIndex >= mImgs.size()){
			mCurrentImgIndex = mImgs.size()-1;
		}
		mImageHandlerWidget->setPixmap(QPixmap(mImgs.at(mCurrentImgIndex)),mIsMax);
	}

	void ImageBrowser::mouseMoveEvent( QMouseEvent *e )
	{
		//showPags();
		BaseDialog::mouseMoveEvent(e);
	}

	void ImageBrowser::showPags()
	{
		QPoint pos = QCursor::pos();
		pos = this->mapFromGlobal(pos);
		if (pos.x() >= rect().width()*3/4 && pos.y()>=37)
		{
			mBtnRight->show();
		}else{
			mBtnRight->hide();
		}
		if (pos.x() <= rect().width()*1/4 && pos.y()>=37)
		{
			mBtnLeft->show();
		}else{
			mBtnLeft->hide();
		}
	}

	void ImageBrowser::onMin()
	{
		this->showMinimized();
	}

	void ImageBrowser::onClose()
	{
		this->close();
	}

	void ImageBrowser::onMax()
	{
		if (mIsMax)
		{
			mBtnMax->setPicName(":/pictureView/nor_max");
			mBtnMax->setToolTip(transfer("最大化"));
		}else{
			mBtnMax->setPicName(":/pictureView/max");
			mBtnMax->setToolTip(transfer("还原"));
		}
		QRect screenrect = QApplication::desktop()->availableGeometry();
		if (!mIsMax)
		{
			this->setGeometry(-SHADOW_WIDTH,-SHADOW_WIDTH,screenrect.width()+2*SHADOW_WIDTH,screenrect.height()+2*SHADOW_WIDTH);
		}
		else{
			int x = screenrect.x() + (screenrect.width()-this->minimumWidth()) / 2;
			int y = screenrect.y() + (screenrect.height()-this->minimumHeight()) / 2;
			this->setGeometry(x,y,this->minimumWidth(),this->minimumHeight());
		}
		mIsMax = !mIsMax;
		mImageHandlerWidget->setPixmap(mImgs.at(mCurrentImgIndex),mIsMax);
	}

	void ImageBrowser::initTitleWidget()
	{
		mBtnMin = new PushButton(this);
		mBtnClose = new PushButton(this);
		mBtnMax = new PushButton(this);

		mBtnMin->setPicName(":/pictureView/min");
		mBtnClose->setPicName(":/pictureView/exit");
		mBtnMax->setPicName(":/pictureView/nor_max");

		mBtnMin->setToolTip(transfer("最小化"));
		mBtnClose->setToolTip(transfer("关闭"));
		mBtnMax->setToolTip(transfer("最大化"));;

		mBtnMin->setCursor(Qt::PointingHandCursor);
		mBtnMax->setCursor(Qt::PointingHandCursor);
		mBtnClose->setCursor(Qt::PointingHandCursor);

		connect(mBtnMin, SIGNAL(clicked()), this, SLOT(onMin()));
		connect(mBtnMax, SIGNAL(clicked()), this, SLOT(onMax()));
		connect(mBtnClose, SIGNAL(clicked()), this, SLOT(onClose()));

		QHBoxLayout* toolLayout = new QHBoxLayout(this);
		toolLayout->setContentsMargins(0,0,0,0);
		toolLayout->setSpacing(2);
		toolLayout->addStretch();
		toolLayout->addWidget(mBtnMin);
		toolLayout->addWidget(mBtnMax);
		toolLayout->addWidget(mBtnClose);
		QWidget* widget = new QWidget(this);
		widget->setLayout(toolLayout);
		widget->setMinimumHeight(37);
		widget->setStyleSheet("QWidget{background:rgb(245,245,245);}");
		mMainLayout->addWidget(widget);
	}

	void ImageBrowser::initImagePanelWidget()
	{
		mImageHandlerWidget = new ImageHandlerWidget(this);
		mImageHandlerWidget->setPixmap(QPixmap(":/chat/pic"));
		mImageHandlerWidget->setMinimumHeight(this->height()-40);
		mMainLayout->addWidget(mImageHandlerWidget);

		mBtnLeft = new ToolButton(":/pictureView/left",this,false);
		mBtnRight = new ToolButton(":/pictureView/right",this,false);
		mBtnRight->setToolTip(transfer("下一张"));
		mBtnLeft->setToolTip(transfer("上一张"));
		mBtnLeft->setCursor(Qt::PointingHandCursor);
		mBtnRight->setCursor(Qt::PointingHandCursor);
		mBtnRight->hide();
		mBtnLeft->hide();
		connect(mBtnLeft,SIGNAL(clicked(bool)),this,SLOT(onBtnLeft()));
		connect(mBtnRight,SIGNAL(clicked(bool)),this,SLOT(onBtnRight()));
		connect(mBtnLeft,SIGNAL(mouseEnter()),this,SLOT(onSetLeftBtnTooltip()));
		connect(mBtnRight,SIGNAL(mouseEnter()),this,SLOT(onSetRightBtnTooltip()));
	}

	void ImageBrowser::setImgs( QList<QString>imgs,int index )
	{
		mImgs = imgs;
		mCurrentImgIndex = index;
		mImageHandlerWidget->setPixmap(QPixmap(mImgs.at(mCurrentImgIndex)));
	}

	ImageBrowser* ImageBrowser::Instance()
	{
		if (CNull == mPInstance)
		{
			mPInstance = new ImageBrowser();
		}
		return mPInstance;
	}

	void ImageBrowser::showWin()
	{
		mPInstance->showNormal();
	}

	void ImageBrowser::onSetRightBtnTooltip()
	{
		if (mCurrentImgIndex == mImgs.size() -1)
		{
			mBtnRight->setToolTip(transfer("已经是最后一张"));
		}else{
			mBtnRight->setToolTip(QString::number(mCurrentImgIndex+1)+"/"+QString::number(mImgs.size()));
		}
	}

	void ImageBrowser::onSetLeftBtnTooltip()
	{
		if (mCurrentImgIndex == 0)
		{
			mBtnLeft->setToolTip(transfer("没有更多了"));
		}else{
			mBtnLeft->setToolTip(QString::number(mCurrentImgIndex+1)+"/"+QString::number(mImgs.size()));
		}
	}

}
