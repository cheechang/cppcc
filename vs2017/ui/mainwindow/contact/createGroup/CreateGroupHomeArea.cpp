#include "CreateGroupHomeArea.h"
#include "../../controls/headimage.h"
#include "../../controls/ToolButton.h"
#include "CreateGroupContacts.h"
#include <QMessageBox>
#include <common/Connect.h>
#include "../../../common/Common.h"

namespace ui{
	CreateGroupHomeArea::CreateGroupHomeArea( QWidget *parent /*=CNull*/ ):TWidget(parent)
	{
		mName = new QLineEdit(this);
		mName->setPlaceholderText(transfer("������Ⱥ��"));
		mName->setStyleSheet("QLineEdit{background-color:#eeeeee;border:1px;border-radius:2px;min-width:250px;min-height:28px;}");
		mName->setMaxLength(12);
		
		QLabel* lblName = new QLabel(this);
		lblName->setText(transfer("Ⱥ����"));
		QHBoxLayout* hLayout = new QHBoxLayout(this);
		hLayout->addWidget(lblName);
		hLayout->addWidget(mName);
		hLayout->setContentsMargins(0,0,0,0);
		QWidget*widget = new QWidget(this);
		widget->setLayout(hLayout);

		//��Ա�б�
		mMems = new CreateGroupContacts(this);
		mMems->setFixedHeight(340);
		mMems->setListWidgetFixedHeight(340);
		mBtnAddMems = new ToolButton(":/group/addGroup",this,false);
		mBtnAddMems->setFixedSize(28,28);
		mBtnAddMems->move(260,54);
		
		connect(mBtnAddMems,SIGNAL(clicked(bool)),this,SLOT(onAddGroupClicked()));

		QVBoxLayout* layoutMems = new QVBoxLayout(this);
		layoutMems->setContentsMargins(0,0,0,0);
		mLblTip = new QLabel(this);
		mLblTip->setText(transfer("Ⱥ��Ա"));
		layoutMems->addWidget(mLblTip);
		layoutMems->addWidget(mMems);
		QWidget*widgetMems = new QWidget(this);
		widgetMems->setLayout(layoutMems);

		//��������
		mBtnSendReq = new QPushButton(this);
		mBtnSendReq->setText(transfer("����Ⱥ"));
		mBtnSendReq->setFixedSize(100,30);
		mBtnSendReq->setObjectName("updateOk");

		mBtnAddFridenReq = new QPushButton(this);
		mBtnAddFridenReq->setText(transfer("��Ӻ���"));
		mBtnAddFridenReq->setFixedSize(100,30);
		mBtnAddFridenReq->setObjectName("updateOk");

		connect(mBtnSendReq,SIGNAL(clicked(bool)),this,SLOT(onBtnCreateGroup()));
		connect(mBtnAddFridenReq,SIGNAL(clicked()),this, SLOT(onBtnAddFriendClicked()));
		mBtnSendReq->setFocus();
		QHBoxLayout* BtnLayout = new QHBoxLayout(this);
		BtnLayout->addWidget(mBtnSendReq);
		BtnLayout->addWidget(mBtnAddFridenReq);
		BtnLayout->setSpacing(20);
		BtnLayout->setContentsMargins(25,0,0,0);
		QWidget* BtnWidget = new QWidget(this);
		BtnWidget->setLayout(BtnLayout);
		BtnWidget->setFixedHeight(35);

		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->setSpacing(20);
		layout->addWidget(widget);
		layout->addWidget(widgetMems);
		//layout->addWidget(mBtnSendReq,0,Qt::AlignHCenter);
		layout->addWidget(BtnWidget);
		/*layout->addStretch();
		layout->addStretch();*/
		setLayout(layout);
		mType = 1;
		mGroupControl = GROUPMGRCONTROL;
		CONNECT_SERVICE(CreateGroup(int,int64));
		CONNECT_SERVICE(InviteMember(int));
		CONNECT_SERVICE(GroupSet(int));
	}

	CreateGroupHomeArea::~CreateGroupHomeArea()
	{

	}

	void CreateGroupHomeArea::hideDesWidget(bool hide)
	{
		//mLblTip->setVisible(!hide);
		//mDesc->setVisible(!hide);
	}

	void CreateGroupHomeArea::onLevelChanged( int index )
	{
		hideDesWidget(index == 0);
	}

	void CreateGroupHomeArea::resetMemsData( std::vector<data::UserBasicData>& mems )
	{
		//mMems->clearList();
		mMems->setDataAndCanDel(mems);
	}

	void CreateGroupHomeArea::paintEvent( QPaintEvent *e )
	{
		if (mBtnAddMems != CNull)
		{
			mBtnAddMems->raise();
		}
		
		TWidget::paintEvent(e);
	}

	void CreateGroupHomeArea::onBtnCreateGroup()
	{
		mBtnSendReq->setEnabled(false);
		if (mType == 1)
		{
			createGroup();
		}else{
			inviteGroupMem();
		}
	}

	void CreateGroupHomeArea::onBtnAddFriendClicked()
	{
		
		std::vector<data::SearchResultInfo> Vectorinfo;
		QList<data::UserBasicData> datas = mMems->getAllItems();
		if(datas.size() == 0){
			QMessageBox::warning(this,transfer("��ʾ"),transfer("��ѡ��Ⱥ��Ա��"));
			mBtnSendReq->setEnabled(true);
			return;
		}
		
		for(int i=0; i<datas.size(); i++)
		{
			data::SearchResultInfo tdata;
			tdata.targetid = datas.at(i).id.value();
			tdata.name = datas.at(i).name.value();
			tdata.avatar = datas.at(i).thumbAvatar.value();
			tdata.resultType = data::USER_TYPE;
			Vectorinfo.push_back(tdata);
		}

		mMems->clearList();
		m_addContactWin = new AddContactWindow(this);
		connect(m_addContactWin, SIGNAL(signalSerAddFriden()), this, SIGNAL(closeWin()));
		m_addContactWin->InitDatas(Vectorinfo);
		m_addContactWin->show();
	}

	void CreateGroupHomeArea::onSerCreateGroup( int code,int64 groupId )
	{
		mBtnSendReq->setEnabled(true);
		if (code == 0)
		{
			CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
			chat->chatType = data::GROUP_CHAT;
			chat->isStartChat = true;
			chat->avatar   ="";
			QString name = mName->text().trimmed();
			chat->name =name.toStdString();
			chat->targetid = groupId;
			chat->lastMsg = transfer("[��Ϣ��ʾ]").toStdString();

			mMems->clearList();
			mName->clear();
			mGroupControl->SetGroupSet(groupId,3,1,CBind(&CreateGroupHomeArea::signalSerGroupSet,this,CPlaceholders  _1));
			int ret = QMessageBox::information(this,transfer("��ʾ"),transfer("����Ⱥ�ɹ�"));
	
			if (ret == 1024)
			{
				emit closeWin();
				emit startChat(chat);
			}
		}else{
			if (303 == code)
			{
				QMessageBox::warning(this,transfer("��ʾ"),transfer("����������ͨȺ�������ޣ������ٴ���Ⱥ��"));
				return;
			}
			QMessageBox::warning(this,transfer("��ʾ"),transfer("����Ⱥʧ�ܣ�"));
		}
	}

	void CreateGroupHomeArea::clearData()
	{
		mMems->clearList();
		mName->clear();
	}

	void CreateGroupHomeArea::setType(QString groupName ,int type/*=1*/ ,int64 groupId)
	{
		if (type ==1)
		{
			mLblTip->setText(transfer("Ⱥ��Ա"));
			mBtnSendReq->setText(transfer("��Ⱥ"));
		}else{
			mBtnSendReq->setText(transfer("���"));
			mName->setText(groupName);
			mName->setReadOnly(true);
			mLblTip->setText(transfer("�����Ⱥ��Ա"));
		}
		mGroupId=groupId;
		mType = type;
		//emit mBtnSendReq->clicked(true);
	}

	void CreateGroupHomeArea::createGroup()
	{
		QString name = mName->text().trimmed();
		if (name.isEmpty())
		{
			QMessageBox::warning(this,transfer("��ʾ"),transfer("������Ⱥ����"));
			mBtnSendReq->setEnabled(true);
			return;
		}
		QList<data::UserBasicData> datas = mMems->getAllItems();
		if(datas.size() == 0){
			QMessageBox::warning(this,transfer("��ʾ"),transfer("��ѡ��Ⱥ��Ա��"));
			mBtnSendReq->setEnabled(true);
			return;
		}
		if (mGroupControl == CNull)
		{
			mGroupControl = GROUPMGRCONTROL;
		}
		if (mGroupControl != CNull)
		{
			std::vector<int64> members;
			for (int i=0;i<datas.size();++i)
			{
				members.push_back(datas.at(i).id.value());
			}
			mGroupControl->CreateGroup(1,name.toUtf8().data(),members,CBind
				(&CreateGroupHomeArea::signalSerCreateGroup,this,CPlaceholders  _1,CPlaceholders  _2));
		}

		mMems->clearList();
	}

	void CreateGroupHomeArea::inviteGroupMem()
	{
		QList<data::UserBasicData> datas = mMems->getAllItems();
		if(datas.size() == 0){
			QMessageBox::warning(this,transfer("��ʾ"),transfer("��ѡ��Ⱥ��Ա��"));
			mBtnSendReq->setEnabled(true);
			return;
		}
		if (mGroupControl != CNull)
		{
			std::vector<int64> members;
			for (int i=0;i<datas.size();++i)
			{
				members.push_back(datas.at(i).id.value());
			}
			mGroupControl->InviteMember(mGroupId,members,CBind
				(&CreateGroupHomeArea::signalSerInviteMember,this,CPlaceholders  _1));
		}
	}

	void CreateGroupHomeArea::onSerInviteMember( int code )
	{
		mBtnSendReq->setEnabled(true);
		if (code == 0)
		{
			QMessageBox::information(this,transfer("��ʾ"),transfer("���Ⱥ��Ա�ɹ�"));
			emit closeWin();
		}else{
				QMessageBox::warning(this,transfer("��ʾ"),transfer("����Ⱥ��Աʧ�ܣ�")+QString::number(code));
		}
	}

	void CreateGroupHomeArea::onSerGroupSet( int code )
	{

	}

	void CreateGroupHomeArea::onAddGroupClicked()
	{
		emit addGroupClicked(mMems->oriSelMems());
	}
}
