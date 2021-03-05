#include "CreateGroupSelectMemberArea.h"
#include "CreateGroupEnterprise.h"
#include "CreateGroupContacts.h"
#include "../../../common/Common.h"
namespace ui{
	CreateGroupSelectMemberArea::CreateGroupSelectMemberArea( QWidget *parent /*=CNull*/ )
	{
		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(0,0,0,0);
		mType = 1;
		//导航条
		mBtnBack = new QPushButton(this);
		mBtnBack->setText(transfer("返回"));
		mBtnBack->setFixedSize(60,28);
		mBtnBack->setObjectName("updateOk");
		connect(mBtnBack,SIGNAL(clicked(bool)),this,SIGNAL(backClicked()));

		mBtnOK = new QPushButton(this);
		mBtnOK->setText(transfer("确定"));
		mBtnOK->setFixedSize(60,28);
		mBtnOK->setObjectName("updateOk");
		connect(mBtnOK,SIGNAL(clicked(bool)),this,SLOT(onBtnOKClicked()));

		mLblNavText = new QLabel(this);
		mLblNavText->setText(transfer("选择联系人"));
		mLblNavText->setObjectName("LabelBold");

		QHBoxLayout*layout = new QHBoxLayout(this);
		layout->setContentsMargins(6,6,6,6);
		layout->addWidget(mBtnBack);
		layout->addWidget(mLblNavText,0,Qt::AlignHCenter);
		layout->addWidget(mBtnOK);
		QWidget*widget = new QWidget(this);
		widget->setLayout(layout);
		widget->setObjectName("updateTextEdit");
		mainLayout->addWidget(widget);

		//联系人列表
		mFriend = new CreateGroupContacts(this,true);
		/*mOrg = new CreateGroupEnterprise(this);
		mTabWidget = new QTabWidget(this);
		mTabWidget->addTab(mFriend,transfer("联系人"));
		mTabWidget->addTab(mOrg,transfer("组织架构"));
		mTabWidget->setFixedHeight(510);
		mainLayout->addWidget(mTabWidget);*/

		mainLayout->addWidget(mFriend);
		mainLayout->addStretch();
		setLayout(mainLayout);
	
		connect(mFriend, SIGNAL(signalSerHighSerch()), this, SLOT(onSerHighSerch()));
		connect(mFriend, SIGNAL(signalSerHighSerchResult()), this, SLOT(onSerHighSerchResult()));
		connect(mFriend, SIGNAL(signalSerHighSerch()), this, SLOT(onSerHighSerch()));
		connect(mFriend, SIGNAL(StartChat(CSharedPtr<data::ChatInfo>&)), this, SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
		//connect(mTabWidget,SIGNAL(currentChanged(int)),this,SLOT(onTabCurentChanged(int)));
	}

	CreateGroupSelectMemberArea::~CreateGroupSelectMemberArea()
	{
		clearData();
	}

	void CreateGroupSelectMemberArea::onBtnOKClicked()
	{
		QList<data::UserBasicData> datas;
		datas.append(mFriend->getCheckedItems());
		//datas.append(mOrg->getCheckedItems());

		std::vector<data::UserBasicData> mems;
		for (int i=0;i<datas.size();++i)
		{
			mems.push_back(datas.at(i));
		}
		emit selectMemsBack(mems);

		clearData();
	}

	void CreateGroupSelectMemberArea::clearData()
	{
		mFriend->clearList();
		//mOrg->clearList();
	}

	void CreateGroupSelectMemberArea::reqData(QMap<int64,int64> oriMems)
	{
		mFriend->clearList();
		mFriend->setOriSelMems(oriMems);
		//mOrg->setOriSelMems(oriMems);
		mFriend->reqData();
		//mOrg->reqData();
	}

	void CreateGroupSelectMemberArea::setType(int type,int64 groupId)
	{
		mType = type;
		mFriend->setType(type,groupId);
		//mOrg->setType(type,groupId);
	}

	void CreateGroupSelectMemberArea::onTabCurentChanged(int index)
	{
		if(index == 1){
			mFriend->SwitchPage();
		}
	}

	void CreateGroupSelectMemberArea::onSerHighSerch()
	{
		mBtnBack->setVisible(false);
		mBtnOK->setVisible(false);
	}
	void CreateGroupSelectMemberArea::onSerHighSerchResult()
	{
		mBtnBack->setVisible(true);
		mBtnOK->setVisible(true);
	}

	void CreateGroupSelectMemberArea::onStartChat(CSharedPtr<data::ChatInfo>&chat)
	{
		emit closeWin();
		emit startChat(chat);
	}
}