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
			mSearchBox->setPlaceholderText(transfer("搜索：联系人"));
			mSearchBox->setFixedWidth(190);
			connect(mSearchBox,SIGNAL(clearBtnClicked()),this,SLOT(onClearBtnClicked()));
			connect(mSearchBox,SIGNAL(textChanged(const QString &)),this,SLOT(onTextChanged(const QString &)));

			widget = new QWidget(this);
			widget->setObjectName("SearchBoxBg");
			widget->setStyleSheet("QWidget#SearchBoxBg{background:#fafafa;}");
			widget->setFixedHeight(50);

			HighSerch = new QPushButton();
			HighSerch->setText(transfer("高级搜索"));
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
			m_AllSelectBtn->setText(transfer("全选"));
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

			m_sendmsg = std::make_shared<QAction>(transfer("发消息"),this);
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
		// 高级查询
		m_highNamelbel = new QLabel(transfer("姓          名："));
		m_highSexlbel =  new QLabel(transfer("性          别："));
		m_highMzlbel = new QLabel(transfer("民          族："));
		m_highadresslbel = new QLabel(transfer("所   在   地："));
		m_highjoblbel = new QLabel(transfer("现 任  职 务："));
		m_highcircleslbel = new QLabel(transfer("界          别："));
		m_highgrouplbel = new QLabel(transfer("组          别："));
		m_highSpecialComlbel = new QLabel(transfer("专   委   会："));
		m_highzxzwlbel = new QLabel(transfer("政 协  职 务："));
		m_highzwhzwlbel = new QLabel(transfer("专委会职务："));
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
		okBtn->setText(transfer("搜索"));
		okBtn->setObjectName(transfer("updateOk"));
		okBtn->setFixedSize(80,30);//80，26（2020年8月31日）
		connect(okBtn,SIGNAL(clicked()),this, SLOT(onSerHighSerchClicked()));

		cancelBtn = new QPushButton(this);
		cancelBtn->setText(transfer("取消"));
		cancelBtn->setObjectName(transfer("updateOk"));
		cancelBtn->setFixedSize(80,30);//80，26
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
		//			if (mSearchBox)//处理搜索：名称模糊匹配
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
		QString juststr = QString(transfer("--请选择"));
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
		m_highSexCom->insertItem(0,QString(transfer("--请选择")));
		m_highSexCom->addItem(transfer("男"));
		m_highSexCom->addItem(transfer("女"));

		QStringList tadresslist;
		tadresslist<<QString(transfer("北京"))<<QString(transfer("天津"))<<QString(transfer("河北"))<<QString(transfer("山西"))<<QString(transfer("内蒙"))<<QString(transfer("辽宁"))
			       <<QString(transfer("吉林"))<<QString(transfer("黑龙江"))<<QString(transfer("上海"))<<QString(transfer("江苏"))<<QString(transfer("浙江"))<<QString(transfer("安徽"))<<QString(transfer("福建"))
			       <<QString(transfer("江西"))<<QString(transfer("山东"))<<QString(transfer("河南"))<<QString(transfer("湖北"))<<QString(transfer("湖南"))<<QString(transfer("广东"))<<QString(transfer("广西"))
			       <<QString(transfer("海南"))<<QString(transfer("重庆"))<<QString(transfer("四川"))<<QString(transfer("贵州"))<<QString(transfer("云南"))<<QString(transfer("西藏"))<<QString(transfer("陕西"))
			       <<QString(transfer("甘肃"))<<QString(transfer("青海"))<<QString(transfer("宁夏"))<<QString(transfer("新疆"))<<QString(transfer("台湾"))<<QString(transfer("香港"))<<QString(transfer("澳门"));
		m_highAdressCom->insertItem(0,QString(transfer("--请选择")));
		m_highAdressCom->addItems(tadresslist);

		QStringList Mzlist;
		Mzlist<<(transfer("汉族"))<<(transfer("壮族"))<<(transfer("回族"))<<(transfer("满族"))<<(transfer("维吾尔族"))<<(transfer("苗族"))<<(transfer("彝族"))<<(transfer("土家族")) 
			  <<(transfer("藏族"))<<(transfer("蒙古族"))<<(transfer("侗族"))<<(transfer("布依族"))<<(transfer("瑶族"))<<(transfer("白族"))<<(transfer("朝鲜族"))<<(transfer("哈尼族"))
			  <<(transfer("黎族"))<<(transfer("哈萨克族"))<<(transfer("傣族"))<<(transfer("畲族"))<<(transfer("傈僳族"))<<(transfer("东乡族"))<<(transfer("仡佬族"))<<(transfer("拉祜族"))
			  <<(transfer("佤族"))<<(transfer("水族"))<<(transfer("纳西族"))<<(transfer("羌族"))<<(transfer("土族"))<<(transfer("仫佬族"))<<(transfer("锡伯族"))<<(transfer("柯尔克孜族")) 
			  <<(transfer("景颇族"))<<(transfer("达斡尔族"))<<(transfer("撒拉族"))<<(transfer("布朗族"))<<(transfer("毛南族"))<<(transfer("塔吉克族"))<<(transfer("普米族"))<<(transfer("阿昌族"))
			  <<(transfer("怒族"))<<(transfer("鄂温克族"))<<(transfer("京族"))<<(transfer("基诺族"))<<(transfer("德昂族"))<<(transfer("保安族"))<<(transfer("俄罗斯族"))<<(transfer("裕固族"))
			  <<(transfer("乌孜别克族"))<<(transfer("门巴族"))<<(transfer("鄂伦春族"))<<(transfer("独龙族"))<<(transfer("赫哲族"))<<(transfer("高山族"))<<(transfer("珞巴族"))<<(transfer("塔塔尔族 "))
			  <<(transfer("未识别民族"))<<(transfer("入籍外国人"));
		m_highMzCom->insertItem(0,QString(transfer("--请选择")));
		m_highMzCom->addItems(Mzlist);

		QStringList Jblist;
		Jblist<< transfer("中国共产党")<< transfer("中国国民党革命委员会")<< transfer("中国民主同盟")
			  << transfer("中国民主建国会")<< transfer("中国民主促进会")<< transfer("中国农工民主党")
			  << transfer("中国致公党")<< transfer("九三学社")<< transfer("台湾民主自治同盟")
			  << transfer("无党派人士")<< transfer("教育界")<< transfer("中国共产主义青年团")
			  << transfer("中华全国总工会")<< transfer("经济界")<< transfer("中华全国妇女联合会")
			  << transfer("少数民族界")<< transfer("中华全国青年联合会")<< transfer("中华全国工商业联合会")
			  << transfer("中国科学技术协会")<< transfer("中华全国台湾同胞联谊会")<< transfer("中华全国归国华侨联合会")
			  << transfer("文化艺术界")<< transfer("科学技术界")<< transfer("社会科学界")
			  << transfer("农业界")<< transfer("体育界")<< transfer("新闻出版界")<< transfer("医药卫生界")
			  << transfer("对外友好界")<< transfer("社会福利和社会保障界")<< transfer("宗教界")
			  << transfer("特邀香港人士")<< transfer("特邀澳门人士")<< transfer("特别邀请人士");		
		m_highJbCom->insertItem(0,QString(transfer("--请选择")));
		m_highJbCom->addItems(Jblist);

		QStringList Zwhlist;
		Zwhlist<<transfer("文史和学习委员会")<<transfer("外事委员会")<<transfer("提案委员会")
			   <<transfer("社会和法制委员会")<<transfer("人口资源环境委员会")<<transfer("民族和宗教委员会")
			   <<transfer("经济委员会")<<transfer("教科文卫体委员会")<<transfer("港澳台侨委员会");
		m_highZwhCom->insertItem(0,QString(transfer("--请选择")));
		m_highZwhCom->addItems(Zwhlist);

		QStringList Zxzwlist;
		Zxzwlist << transfer("主席") << transfer("副主席") << transfer("常务委员") << transfer("委员");
		m_highZxzwCom->insertItem(0,QString(transfer("--请选择")));
		m_highZxzwCom->addItems(Zxzwlist);

		QStringList Zwhzwlist;
		Zwhzwlist << transfer("主任") << transfer("副主任") << transfer("驻会副主任") << transfer("专委");
		m_highZwhzwCom->insertItem(0,QString(transfer("--请选择")));
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
