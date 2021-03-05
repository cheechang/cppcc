#include "CreateGroupContacts.h"
#include "SelectMemberItemWidget.h"
#include "common/Common.h"
#include "controls/UserInfoCommon.h"
#include "controls/UserInfoCommitee.h"
#include <QMenu>
#include <QAction>
#include "../localsearch/LocalSearchLineEdit.h"
#include "json.h"

namespace ui
{
	CreateGroupContacts::CreateGroupContacts( QWidget *parent /*=CNull*/,bool hasSearchBox ):TWidget(parent)
	{
		setObjectName("bg_fa");
		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(0,0,0,0);
		mainLayout->setSpacing(0);
		mType = 1;
		mSearchBox =CNull;
		QWidget* widget = CNull;
		m_Highstackwidget = new QStackedWidget(this);
		QHBoxLayout* layout = new QHBoxLayout(this);
		QVBoxLayout* VLayout = new QVBoxLayout(this);

		if (hasSearchBox)
		{
			mSearchBox = new LocalSearchLineEdit(this,false);
			mSearchBox->setPlaceholderText(transfer("��������ϵ��"));
			mSearchBox->setFixedWidth(190);
			connect(mSearchBox,SIGNAL(clearBtnClicked()),this,SLOT(onClearBtnClicked()));
			connect(mSearchBox,SIGNAL(textChanged(const QString &)),this,SLOT(onTextChanged(const QString &)));

			widget = new QWidget(this);
			widget->setObjectName("SearchBoxBg");
			widget->setStyleSheet("QWidget#SearchBoxBg{background:#fafafa;}");
			widget->setFixedHeight(50);

			HighSerch = new QPushButton();
			HighSerch->setText(transfer("�߼�����"));
			HighSerch->setObjectName("HighSerchBtn");
			HighSerch->setFixedWidth(60);
			layout->addWidget(mSearchBox);
			layout->addWidget(HighSerch);
			layout->setSpacing(0);
			connect(HighSerch, SIGNAL(clicked()), this, SLOT(onSerHighSearch()));

			layout->setContentsMargins(0,0,0,0);
			//layout->addWidget(mSearchBox,0,Qt::AlignHCenter);
			VLayout->addLayout(layout);
			widget->setLayout(VLayout);
			mainLayout->setContentsMargins(0,1,0,0);

		}

		mListWidget = new QListWidget(this);
		mFridListWidget = new QWidget(this);
		QVBoxLayout* FridlistLaout = new QVBoxLayout(this);
		FridlistLaout->addWidget(mListWidget);
		
		if(hasSearchBox)
		{
			QHBoxLayout* FuncHlayout = new QHBoxLayout(this);
			m_AllSelectBtn = new QPushButton(this);
			m_AllSelectBtn->setVisible(false);
			m_AllSelectBtn->setText(transfer("ȫѡ"));
			m_AllSelectBtn->setObjectName("HighAllSelectBtn");
			connect(m_AllSelectBtn, SIGNAL(clicked()),this, SLOT(onSerAllSelClicked()));

			FuncHlayout->addStretch();
			FuncHlayout->addWidget(m_AllSelectBtn);
			FuncHlayout->setContentsMargins(0,0,30,5);
			FridlistLaout->addLayout(FuncHlayout);
			FridlistLaout->setSpacing(0);
			//FridlistLaout->addLayout(FuncHlayout);
		}

		if(hasSearchBox)
		{
			popMenu = std::make_shared<QMenu>(this);

			m_sendmsg = std::make_shared<QAction>(transfer("����Ϣ"),this);
			connect(m_sendmsg.get(), SIGNAL(triggered()), this, SLOT(onSerSendMessage()));

			popMenu->addAction(m_sendmsg.get());
		}
		
		mFridListWidget->setLayout(FridlistLaout);
		mListWidget->setObjectName("groupMemberListWidget");
		if (hasSearchBox)
		{
			mainLayout->addWidget(widget,0,Qt::AlignHCenter);
			mListWidget->setFixedHeight(330);
		}else{
			mListWidget->setFixedHeight(420);
		}

		m_highwidget = new QWidget(this);
		m_HighLayout = new QVBoxLayout(this);
		m_highwidget->setLayout(m_HighLayout);
		// �߼���ѯ
		m_highNamelbel = new QLabel(transfer("��          ����"));
		m_highSexlbel =  new QLabel(transfer("��          ��"));
		m_highMzlbel = new QLabel(transfer("��          �壺"));
		m_highadresslbel = new QLabel(transfer("��   ��   �أ�"));
		m_highjoblbel = new QLabel(transfer("�� ��  ְ ��"));
		m_highcircleslbel = new QLabel(transfer("��          ��"));
		m_highgrouplbel = new QLabel(transfer("��          ��"));
		m_highSpecialComlbel = new QLabel(transfer("ר   ί   �᣺"));
		m_highzxzwlbel = new QLabel(transfer("�� Э  ְ ��"));
		m_highzwhzwlbel = new QLabel(transfer("רί��ְ��"));
		m_highNamelbel->setObjectName(transfer("m_highNamelbel"));
		m_highNamelbel->setFixedWidth(74);

		m_highSexlbel->setObjectName(transfer("m_highNamelbel"));
		m_highSexlbel->setFixedWidth(74);

		m_highMzlbel->setObjectName(transfer("m_highNamelbel"));
		m_highMzlbel->setFixedWidth(74);

		m_highadresslbel->setObjectName(transfer("m_highNamelbel"));
		m_highadresslbel->setFixedWidth(74);

		m_highjoblbel->setObjectName(transfer("m_highNamelbel"));
		m_highjoblbel->setFixedWidth(74);

		m_highcircleslbel->setObjectName(transfer("m_highNamelbel"));
		m_highcircleslbel->setFixedWidth(74);

		m_highgrouplbel->setObjectName(transfer("m_highNamelbel"));
		m_highgrouplbel->setFixedWidth(74);

		m_highSpecialComlbel->setObjectName(transfer("m_highNamelbel"));
		m_highSpecialComlbel->setFixedWidth(74);

		m_highzxzwlbel->setObjectName(transfer("m_highNamelbel"));
		m_highzxzwlbel->setFixedWidth(74);

		m_highzwhzwlbel->setObjectName(transfer("m_highNamelbel"));
		m_highzwhzwlbel->setFixedWidth(74);

		m_highNameEdit = new QLineEdit(this);
		m_highSexCom = new QComboBox(this);
		m_highMzCom = new QComboBox(this);
		m_highAdressCom = new QComboBox(this);
		m_highJobEdit = new QLineEdit(this);
		m_highJbCom = new QComboBox(this);
		m_highGroupEdit = new QLineEdit(this);
		m_highZwhCom = new QComboBox(this);
		m_highZxzwCom = new QComboBox(this);
		m_highZwhzwCom = new QComboBox(this);

		m_highNameEdit->setObjectName("HighSearchEdit");
		m_highSexCom->setObjectName("HighSearchBox");
		m_highMzCom->setObjectName("HighSearchBox");
		m_highAdressCom->setObjectName("HighSearchBox"); 
		m_highJobEdit->setObjectName("HighSearchEdit");
		m_highJbCom->setObjectName("HighSearchBox");
		m_highGroupEdit->setObjectName("HighSearchEdit");
		m_highZwhCom->setObjectName("HighSearchBox");
		m_highZxzwCom->setObjectName("HighSearchBox");
		m_highZwhzwCom->setObjectName("HighSearchBox");

		Layout1 = new QHBoxLayout(this);
		Layout2 = new QHBoxLayout(this);
		Layout3 = new QHBoxLayout(this);
		Layout4 = new QHBoxLayout(this);
		Layout5 = new QHBoxLayout(this);
		Layout6 = new QHBoxLayout(this);
		Layout7 = new QHBoxLayout(this);
		Layout8 = new QHBoxLayout(this);
		Layout9 = new QHBoxLayout(this);
		Layout10 = new QHBoxLayout(this);

		Layout1->addWidget(m_highNamelbel);
		Layout1->addWidget(m_highNameEdit);
		Layout1->addStretch();
		

		Layout2->addWidget(m_highSexlbel);
		Layout2->addWidget(m_highSexCom);
		Layout2->addStretch();

		Layout3->addWidget(m_highMzlbel);
		Layout3->addWidget(m_highMzCom);
		Layout3->addStretch();

		Layout4->addWidget(m_highadresslbel);
		Layout4->addWidget(m_highAdressCom);
		Layout4->addStretch();

		Layout5->addWidget(m_highjoblbel);
		Layout5->addWidget(m_highJobEdit);
		Layout5->addStretch();

		Layout6->addWidget(m_highcircleslbel);
		Layout6->addWidget(m_highJbCom);
		Layout6->addStretch();

		Layout7->addWidget(m_highgrouplbel);
		Layout7->addWidget(m_highGroupEdit);
		Layout7->addStretch();

		Layout8->addWidget(m_highSpecialComlbel);
		Layout8->addWidget(m_highZwhCom);
		Layout8->addStretch();
		
		Layout9->addWidget(m_highzxzwlbel);
		Layout9->addWidget(m_highZxzwCom);
		Layout9->addStretch();

		Layout10->addWidget(m_highzwhzwlbel);
		Layout10->addWidget(m_highZwhzwCom);
		Layout10->addStretch();

		m_HighLayout->addLayout(Layout1);
		m_HighLayout->addLayout(Layout2);
		m_HighLayout->addLayout(Layout3);
		m_HighLayout->addLayout(Layout4);
		m_HighLayout->addLayout(Layout5);
		m_HighLayout->addLayout(Layout6);
		m_HighLayout->addLayout(Layout7);
		m_HighLayout->addLayout(Layout8);
		m_HighLayout->addLayout(Layout9);
		m_HighLayout->addLayout(Layout10);
		m_HighLayout->setContentsMargins(25,0,0,25);
		m_HighLayout->setSpacing(2);

		m_BtnLayout = new QHBoxLayout(this);
		okBtn = new QPushButton(this);
		okBtn->setText(transfer("����"));
		okBtn->setObjectName(transfer("updateOk"));
		okBtn->setFixedSize(80,30);//80��26��2020��8��31�գ�
		connect(okBtn,SIGNAL(clicked()),this, SLOT(onSerHighSerchClicked()));

		cancelBtn = new QPushButton(this);
		cancelBtn->setText(transfer("ȡ��"));
		cancelBtn->setObjectName(transfer("updateOk"));
		cancelBtn->setFixedSize(80,30);//80��26
		connect(cancelBtn, SIGNAL(clicked()),this, SLOT(onSerCancelBtnClicked()));
		m_HighLayout->addLayout(m_BtnLayout);


		m_BtnLayout->addWidget(okBtn);
		m_BtnLayout->addWidget(cancelBtn);
		m_BtnLayout->setSpacing(15);
		m_BtnLayout->setContentsMargins(0,15,25,0);


		m_Highstackwidget->addWidget(mFridListWidget);
		m_Highstackwidget->addWidget(m_highwidget);
		mainLayout->addWidget(m_Highstackwidget);
		mainLayout->addStretch();
		setLayout(mainLayout);
		mOriSelMems.clear();
		mContactControl = CONTACTMGRCONTROL;
		mGroupControl = GROUPMGRCONTROL;
		muserserviceControl = USERCONTROL;

		initData();
		m_Highstackwidget->setCurrentWidget(mFridListWidget);

		CONNECT_SERVICE(ZxSerchResult(int, int32, std::vector<data::UserBasicData>&));
	}
	CreateGroupContacts::~CreateGroupContacts()
	{
		clearList();
	}

	void CreateGroupContacts::addItem( data::UserBasicData data ,bool canDel)
	{
		QListWidgetItem* item = new QListWidgetItem();
		SelectMemberItemWidget* widget = new SelectMemberItemWidget(this,canDel);
		connect(widget,SIGNAL(deleteClicked(QString)),this,SLOT(onDeleteItem(QString)));
		connect(widget, SIGNAL(signalSerShowUserInfo(int64, QString, QString, std::string)), this, SLOT(onSerShowUserInfo(int64, QString, QString, std::string)));
		QString head = transfer(data.thumbAvatar.value().c_str());
		if(head.isEmpty()){
			head = ":/base/default_head";
		}
		widget->setData(data);
		if ( mType == 2 && mGroupControl!=CNull)
		{
			bool ret = mGroupControl->IsInGroup(mGroupId,data.id.value());
			if (ret)
			{
				widget->setCheckboxEnabled(false,true);
			}
		}
		if ( mOriSelMems.contains(data.id.value()))
		{
			widget->setCheckboxEnabled(false,true);
		}
		int n = this->width();
		item->setSizeHint(QSize(255,60));
		mListWidget->addItem(item);	
		mListWidget->setItemWidget(item,widget);
	}

	void CreateGroupContacts::clearList()
	{
		for (int i=0;i<mListWidget->count();)
		{
			QListWidgetItem* item = mListWidget->item(i);
			QWidget* widget = mListWidget->itemWidget(item);
			mListWidget->removeItemWidget(item);
			if(item != CNull){
				delete item;
			}
			/*
			if(widget != CNull){
				delete widget;
			}*/
		}
		mListWidget->clear();
		mMapSelMems.clear();
		mOriSelMems.clear();
	}

	QList<data::UserBasicData> CreateGroupContacts::getCheckedItems()
	{
		QList<data::UserBasicData> datas;
		for (int i=0;i<mListWidget->count();++i)
		{
			QListWidgetItem* item = mListWidget->item(i);
			SelectMemberItemWidget* widget = static_cast<SelectMemberItemWidget*>( mListWidget->itemWidget(item));
			if (widget!= CNull && widget->isSelect())
			{
				datas.append(widget->data());
			}
		}
		return datas;
	}

	void CreateGroupContacts::setData( std::vector<data::UserBasicData>&datas )
	{
		for (int i=0;i<datas.size();++i)
		{
			addItem(datas.at(i));
		}
	}

	void CreateGroupContacts::setDataAndCanDel( std::vector<data::UserBasicData>&datas )
	{
		for (int i=0;i<datas.size();++i)
		{
			if(!isExist(datas.at(i).id.value())){
				addItem(datas.at(i),true);
				mMapSelMems.insert(datas.at(i).id.value(),datas.at(i).id.value());
			}
			
		}
	}

	void CreateGroupContacts::onDeleteItem( QString id )
	{
		for (int i=0;i<mListWidget->count();++i)
		{

			QListWidgetItem* item = mListWidget->item(i);
			SelectMemberItemWidget* widget = (SelectMemberItemWidget*)( mListWidget->itemWidget(item));
			if (widget!= CNull && widget->id() == id)
			{
				mListWidget->takeItem(i);
				mListWidget->update();
				int64 memId = id.toLongLong();
				if (mMapSelMems.contains(memId))
				{
					mMapSelMems.remove(memId);
				}
				if(item != CNull){
					delete item;
				}
				/*
				if(widget != CNull){
					delete widget;
				}*/
				int64 curCount = mListWidget->count();
				return;
			}
		}
	}

	void CreateGroupContacts::reqData()
	{

		if(muserserviceControl)
		{
			data::ZXSearchParam data;

			data.sector = "";              
			data.name = mSearchBox->text().toUtf8().data();                
			data.nation = "";              
			data.gender = "";              
			data.currentPosition = "";   
			data.group = "";               
			data.specialCommittee = "";
			data.specialCommitteeDuty = "";
			data.CPPCCPosition = "";
			data.myLocation = "";

			int32 pageSize = 100;
			int32 page = 0;
			muserserviceControl->cppccSearch(pageSize,page,data,std::bind(&CreateGroupContacts::signalSerZxSerchResult,this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));

		}

		//std::vector<data::UserBasicData>datas;
		//if(mContactControl != CNull){
		//	std::vector< CSharedPtr<data::Contact> >contacts;
		//	mContactControl->GetContactList(contacts);
		//	for (int i=contacts.size()-1;i>=0;--i)
		//	{
		//		CSharedPtr<data::Contact> con = contacts.at(i);
		//		if (con != CNull)
		//		{
		//			data::UserBasicData data;
		//			data.id = con->id;
		//			data.name = con->remark.value().empty()?con->name.value():con->remark.value();
		//			data.name = QString::fromUtf8(data.name.value().c_str()).toStdString();
		//			data.thumbAvatar = con->thumbAvatar.value();
		//			if (mSearchBox)//��������������ģ��ƥ��
		//			{
		//				QString text = mSearchBox->text();
		//				QString name = data.name.value().c_str();
		//				if (!text.isEmpty() && !name.contains(text))
		//				{
		//					continue;
		//				}

		//			}
		//			if (data.thumbAvatar.value().empty())
		//			{
		//				if (con->isApp.value() == 1)
		//				{
		//					data.thumbAvatar = DEFAULT_APP;
		//				}else{
		//					data.thumbAvatar = DEFAULT_AVATAR;
		//				}
		//			}
		//			datas.push_back(data);
		//		}
		//	}
		//}
		//setData(datas);
	}

	bool CreateGroupContacts::isExist( int64 id )
	{
		int64 value = mMapSelMems.value(id,0);
		return value != 0;

		/*
		for (int i=0;i<mListWidget->count();++i)
		{

			QListWidgetItem* item = mListWidget->item(i);
			SelectMemberItemWidget* widget = static_cast<SelectMemberItemWidget*>( mListWidget->itemWidget(item));
			if (widget!= CNull && widget->id() == QString::number(id))
			{
				return true;
			}
		}
		return false;
		*/
	}

	QList<data::UserBasicData> CreateGroupContacts::getAllItems()
	{
		QList<data::UserBasicData> datas;
		for (int i=0;i<mListWidget->count();++i)
		{
			QListWidgetItem* item = mListWidget->item(i);
			SelectMemberItemWidget* widget = static_cast<SelectMemberItemWidget*>( mListWidget->itemWidget(item));

			if (widget!= CNull )
			{
				data::UserBasicData data = widget->data();
				if (mMapSelMems.contains(data.id.value()))
				{
					datas.append(data);
				}		
			}
		}
		return datas;
	}

	void CreateGroupContacts::setType( int type ,int64 groupId)
	{
		mType = type;
		mGroupId = groupId;
	}

	void CreateGroupContacts::setListWidgetFixedHeight( int height )
	{
		mListWidget->setFixedHeight(height);
	}

	void CreateGroupContacts::setOriSelMems( QMap<int64,int64> data )
	{
		mOriSelMems = data;
	}

	void CreateGroupContacts::onClearBtnClicked()
	{
		mSearchBox->clearText();
	}

	void CreateGroupContacts::onTextChanged( const QString &text )
	{
		clearList();
		reqData();
	}

	void CreateGroupContacts::onSerHighSearch()
	{
		emit signalSerHighSerch();
		m_Highstackwidget->setCurrentWidget(m_highwidget);
	}

	void CreateGroupContacts::onSerCancelBtnClicked()
	{
		this->close();
		/*emit signalSerHighSerchResult();
		m_Highstackwidget->setCurrentWidget(mFridListWidget);*/
	}

	void CreateGroupContacts::onSerAllSelClicked()
	{
		QList<data::UserBasicData> datas;
		for (int i=0;i<mListWidget->count();++i)
		{
			QListWidgetItem* item = mListWidget->item(i);
			SelectMemberItemWidget* widget = static_cast<SelectMemberItemWidget*>( mListWidget->itemWidget(item));
			if (widget!= CNull && widget->isSelect())
			{
				continue;
			}
			else
			{
				widget->SetChecked(true);
			}
		}
	}

	void CreateGroupContacts::onSerHighSerchClicked()
	{
		QString juststr = QString(transfer("--��ѡ��"));
		if(muserserviceControl)
		{
			data::ZXSearchParam data;

			data.sector = (m_highJbCom->currentText() == juststr)?"":m_highJbCom->currentText().toUtf8().data();              
			data.name = m_highNameEdit->text().toUtf8().data();                
			data.nation = (m_highMzCom->currentText() == juststr)?"":m_highMzCom->currentText().toUtf8().data();              
			data.gender = (m_highSexCom->currentText() == juststr)?"":m_highSexCom->currentText().toUtf8().data();              
			data.currentPosition = m_highJobEdit->text().toUtf8().data();     
			data.group = m_highGroupEdit->text().toUtf8().data();               
			data.specialCommittee = (m_highZwhCom->currentText() == juststr)?"":m_highZwhCom->currentText().toUtf8().data();    
			data.specialCommitteeDuty = (m_highZwhzwCom->currentText() == juststr)?"":m_highZwhzwCom->currentText().toUtf8().data();
			data.CPPCCPosition = (m_highZxzwCom->currentText() == juststr)?"":m_highZxzwCom->currentText().toUtf8().data();       
			data.myLocation = (m_highAdressCom->currentText() == juststr)?"":m_highAdressCom->currentText().toUtf8().data();  

			int32 pageSize = 100;
			int32 page = 0;
			muserserviceControl->cppccSearch(pageSize,page,data,std::bind(&CreateGroupContacts::signalSerZxSerchResult,this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
		}
	}

	void CreateGroupContacts::onSerZxSerchResult(int code, int32 page, std::vector<data::UserBasicData>& userdata)
	{
		std::vector<data::ChatInfo>datas;
		for(int i=0; i<userdata.size(); i++)
		{
			data::ChatInfo data;
			data.targetid= userdata.at(i).id.value();
			data.name = QString::fromUtf8(userdata.at(i).name.value().c_str()).toStdString();
			data.avatar = userdata.at(i).thumbAvatar.value();
			data.chatType = data::ENT_USER_CHAT;
			//data. = userdata.at(i).extends.value();
			if (data.avatar.empty())
			{
				data.avatar = DEFAULT_AVATAR;
			}
			datas.push_back(data);
		}
		emit signalZxSerchResult(datas);
		/*
		if(datas.size()>0)
		{
			m_AllSelectBtn->setVisible(true);
		}
		clearList();
		setData(datas);
		emit signalSerHighSerchResult();
		m_Highstackwidget->setCurrentWidget(mFridListWidget);*/
	}
	void CreateGroupContacts::initData()
	{
		m_highSexCom->insertItem(0,QString(transfer("--��ѡ��")));
		m_highSexCom->addItem(transfer("��"));
		m_highSexCom->addItem(transfer("Ů"));

		QStringList tadresslist;
		tadresslist<<QString(transfer("����"))<<QString(transfer("���"))<<QString(transfer("�ӱ�"))<<QString(transfer("ɽ��"))<<QString(transfer("����"))<<QString(transfer("����"))
			       <<QString(transfer("����"))<<QString(transfer("������"))<<QString(transfer("�Ϻ�"))<<QString(transfer("����"))<<QString(transfer("�㽭"))<<QString(transfer("����"))<<QString(transfer("����"))
			       <<QString(transfer("����"))<<QString(transfer("ɽ��"))<<QString(transfer("����"))<<QString(transfer("����"))<<QString(transfer("����"))<<QString(transfer("�㶫"))<<QString(transfer("����"))
			       <<QString(transfer("����"))<<QString(transfer("����"))<<QString(transfer("�Ĵ�"))<<QString(transfer("����"))<<QString(transfer("����"))<<QString(transfer("����"))<<QString(transfer("����"))
			       <<QString(transfer("����"))<<QString(transfer("�ຣ"))<<QString(transfer("����"))<<QString(transfer("�½�"))<<QString(transfer("̨��"))<<QString(transfer("���"))<<QString(transfer("����"));
		m_highAdressCom->insertItem(0,QString(transfer("--��ѡ��")));
		m_highAdressCom->addItems(tadresslist);

		QStringList Mzlist;
		Mzlist<<(transfer("����"))<<(transfer("׳��"))<<(transfer("����"))<<(transfer("����"))<<(transfer("ά�����"))<<(transfer("����"))<<(transfer("����"))<<(transfer("������")) 
			  <<(transfer("����"))<<(transfer("�ɹ���"))<<(transfer("����"))<<(transfer("������"))<<(transfer("����"))<<(transfer("����"))<<(transfer("������"))<<(transfer("������"))
			  <<(transfer("����"))<<(transfer("��������"))<<(transfer("����"))<<(transfer("���"))<<(transfer("������"))<<(transfer("������"))<<(transfer("������"))<<(transfer("������"))
			  <<(transfer("����"))<<(transfer("ˮ��"))<<(transfer("������"))<<(transfer("Ǽ��"))<<(transfer("����"))<<(transfer("������"))<<(transfer("������"))<<(transfer("�¶�������")) 
			  <<(transfer("������"))<<(transfer("���Ӷ���"))<<(transfer("������"))<<(transfer("������"))<<(transfer("ë����"))<<(transfer("��������"))<<(transfer("������"))<<(transfer("������"))
			  <<(transfer("ŭ��"))<<(transfer("���¿���"))<<(transfer("����"))<<(transfer("��ŵ��"))<<(transfer("�°���"))<<(transfer("������"))<<(transfer("����˹��"))<<(transfer("ԣ����"))
			  <<(transfer("���α����"))<<(transfer("�Ű���"))<<(transfer("���״���"))<<(transfer("������"))<<(transfer("������"))<<(transfer("��ɽ��"))<<(transfer("�����"))<<(transfer("�������� "))
			  <<(transfer("δʶ������"))<<(transfer("�뼮�����"));
		m_highMzCom->insertItem(0,QString(transfer("--��ѡ��")));
		m_highMzCom->addItems(Mzlist);

		QStringList Jblist;
		Jblist<< transfer("�й�������")<< transfer("�й����񵳸���ίԱ��")<< transfer("�й�����ͬ��")
			  << transfer("�й�����������")<< transfer("�й������ٽ���")<< transfer("�й�ũ��������")
			  << transfer("�й��¹���")<< transfer("����ѧ��")<< transfer("̨����������ͬ��")
			  << transfer("�޵�����ʿ")<< transfer("������")<< transfer("�й���������������")
			  << transfer("�л�ȫ���ܹ���")<< transfer("���ý�")<< transfer("�л�ȫ����Ů���ϻ�")
			  << transfer("���������")<< transfer("�л�ȫ���������ϻ�")<< transfer("�л�ȫ������ҵ���ϻ�")
			  << transfer("�й���ѧ����Э��")<< transfer("�л�ȫ��̨��ͬ�������")<< transfer("�л�ȫ������������ϻ�")
			  << transfer("�Ļ�������")<< transfer("��ѧ������")<< transfer("����ѧ��")
			  << transfer("ũҵ��")<< transfer("������")<< transfer("���ų����")<< transfer("ҽҩ������")
			  << transfer("�����Ѻý�")<< transfer("��ḣ������ᱣ�Ͻ�")<< transfer("�ڽ̽�")
			  << transfer("���������ʿ")<< transfer("����������ʿ")<< transfer("�ر�������ʿ");		
		m_highJbCom->insertItem(0,QString(transfer("--��ѡ��")));
		m_highJbCom->addItems(Jblist);

		QStringList Zwhlist;
		Zwhlist<<transfer("��ʷ��ѧϰίԱ��")<<transfer("����ίԱ��")<<transfer("�᰸ίԱ��")
			   <<transfer("���ͷ���ίԱ��")<<transfer("�˿���Դ����ίԱ��")<<transfer("������ڽ�ίԱ��")
			   <<transfer("����ίԱ��")<<transfer("�̿�������ίԱ��")<<transfer("�۰�̨��ίԱ��");
		m_highZwhCom->insertItem(0,QString(transfer("--��ѡ��")));
		m_highZwhCom->addItems(Zwhlist);

		QStringList Zxzwlist;
		Zxzwlist << transfer("��ϯ") << transfer("����ϯ") << transfer("����ίԱ") << transfer("ίԱ");
		m_highZxzwCom->insertItem(0,QString(transfer("--��ѡ��")));
		m_highZxzwCom->addItems(Zxzwlist);

		QStringList Zwhzwlist;
		Zwhzwlist << transfer("����") << transfer("������") << transfer("פ�ḱ����") << transfer("רί");
		m_highZwhzwCom->insertItem(0,QString(transfer("--��ѡ��")));
		m_highZwhzwCom->addItems(Zwhzwlist);
	}

	void CreateGroupContacts::SwitchPage()
	{
		m_Highstackwidget->setCurrentWidget(mFridListWidget);
	}

	void CreateGroupContacts::contextMenuEvent(QContextMenuEvent *ev)
	{
		popMenu->exec();
	}

	void CreateGroupContacts::onSerSendMessage()
	{
		QListWidgetItem*item = mListWidget->currentItem();
		SelectMemberItemWidget* widget = (SelectMemberItemWidget*)mListWidget->itemWidget(item);
		emit signalSerSendMsg(widget->GetId());
	}

	void CreateGroupContacts::onSerShowUserInfo(int64 id, QString name, QString avatar, std::string userinfo)
	{
		std::string type("");
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(userinfo, root);
		if (ret)
		{
			if (root.isArray())
			{
				if (root[0]["type"].isString())
				{
					type = root[0]["type"].asString();
				}
			}
		}

		if (type == "1")
		{
			m_pUserInfoCommomWidget = CMakePtr<UserInfoCommon>(this);
			connect(m_pUserInfoCommomWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SIGNAL(StartChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommomWidget->setInfo(id, name, avatar, userinfo);
			m_pUserInfoCommomWidget->show();
		}

		if (type == "0")
		{
			m_pUserInfoCommiteeWidget = CMakePtr<UserInfoCommitee>(this);
			connect(m_pUserInfoCommiteeWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), this, SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommiteeWidget->setInfo(id, name, avatar, userinfo);
			m_pUserInfoCommiteeWidget->show();
		}
	}

	void CreateGroupContacts::onStartChat(CSharedPtr<data::ChatInfo>& chat)
	{
		emit StartChat(chat);
	}
}
