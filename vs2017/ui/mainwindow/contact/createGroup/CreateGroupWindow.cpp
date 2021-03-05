#include "CreateGroupWindow.h"
#include "CreateGroupHomeArea.h"
#include "CreateGroupSelectMemberArea.h"
#include "PushButton.h"
namespace ui{
	CreateGroupWindow::CreateGroupWindow(QWidget *parent): BaseWindow(parent)
	{
		connect(this,SIGNAL(closeClicked()),this,SLOT(onColse()));
		mHomeArea = new CreateGroupHomeArea(this);
		connect(mHomeArea,SIGNAL(closeWin()),this,SLOT(close()));
		connect(mHomeArea,SIGNAL(addGroupClicked(QMap<int64,int64>)),this,SLOT(onShowSelMemsArea(QMap<int64,int64>)));
		connect(mHomeArea,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));

		mSelMemArea = new CreateGroupSelectMemberArea(this);
		connect(mSelMemArea, SIGNAL(closeWin()), this, SLOT(close()));
		connect(mSelMemArea,SIGNAL(backClicked()),this,SLOT(onShowHomeArea()));
		connect(mSelMemArea,SIGNAL(selectMemsBack(std::vector<data::UserBasicData>&)),this,SLOT(onSelectMemsResult(std::vector<data::UserBasicData>&)));
		connect(mSelMemArea, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));

        mStackedWidget = new QStackedWidget(this);
		mStackedWidget->addWidget(mHomeArea);
		mStackedWidget->addWidget(mSelMemArea);
		mStackedWidget->setCurrentIndex(0);
		mMainLayout->addWidget(mStackedWidget);
		mMainLayout->addStretch();
	}

	CreateGroupWindow::~CreateGroupWindow()
	{
		
	}

	void CreateGroupWindow::onShowHomeArea()
	{
		mStackedWidget->setCurrentIndex(0);
		mSelMemArea->clearData();
	}

	void CreateGroupWindow::onShowSelMemsArea(QMap<int64,int64> oriMems)
	{
		mStackedWidget->setCurrentIndex(1);
		mSelMemArea->reqData(oriMems);
	}

	void CreateGroupWindow::onSelectMemsResult( std::vector<data::UserBasicData>&mems )
	{
		mStackedWidget->setCurrentIndex(0);
		//mSelMemArea->clearData();
		mHomeArea->resetMemsData(mems);
	}

	void CreateGroupWindow::showWin()
	{
		mSelMemArea->clearData();
		mHomeArea->clearData();
		mStackedWidget->setCurrentIndex(0);
		mSelMemArea->setType(1);
		this->showNormal();
	}

	void CreateGroupWindow::showWin( data::TinyGroup group )
	{
		mGroup = group;
		mSelMemArea->clearData();
		mHomeArea->clearData();
		mStackedWidget->setCurrentIndex(0);
		mHomeArea->setType(QString::fromUtf8(group.groupName.value().c_str()),2,group.groupId.value());
		mSelMemArea->setType(2,group.groupId.value());
		this->showNormal();
		
	}

	void CreateGroupWindow::onColse()
	{
		if(1== mBtnClose->btnStatus()){
			close();
		}
	}

}
