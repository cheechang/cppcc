#include "GroupInforSettingArea.h"
#include <data/UserData.h>
#include <interface/IUserControl.h>
#include "common/Connect.h"
#include "../../../common/Common.h"
#include "json.h"
namespace ui{
	GroupInforSettingArea::GroupInforSettingArea(QWidget *parent)
		: TWidget(parent)
	{
		m_groupmgrcontrol = CNull;
		setObjectName("groupinfobackground");

		m_mainLayout = CMakePtr<QVBoxLayout>();
		m_addGroupWaysGroup = CMakePtr<QButtonGroup>();
		m_addGroupWays.append(CMakePtr<QRadioButton>(transfer("不允许任何人加入该群")));
		m_addGroupWays.append(CMakePtr<QRadioButton>(transfer("需要身份认证才能加入该群")));
		m_addGroupWays.append(CMakePtr<QRadioButton>(transfer("允许任何人加入该群")));
		m_addGroupWaysGroup->addButton(m_addGroupWays.at(0).get(),ANY_CAN_ADD_GROUP);
		m_addGroupWaysGroup->addButton(m_addGroupWays.at(1).get(),NEED_CONFIRM_ADD_GROUP);
		m_addGroupWaysGroup->addButton(m_addGroupWays.at(2).get(),ALL_CAN_NOT_ADD_GROUP);

		m_addGroupWayLayout = CMakePtr<QGridLayout>();
		m_addGroupWayLayout->setContentsMargins(60,6,0,0);
		m_lblAddGroupWay = CMakePtr<QLabel>(transfer("加群方式："));
		m_lblAddGroupWay->setMaximumWidth(60);
		m_lblAddGroupWay->setEnabled(false);
		m_addGroupWayLayout->addWidget(m_lblAddGroupWay.get(),0,0,2,1);
		m_addGroupWayLayout->addWidget(m_addGroupWays.at(0).get(),1,1,1,1);
		m_addGroupWayLayout->addWidget(m_addGroupWays.at(1).get(),2,1,1,1);
		m_addGroupWayLayout->addWidget(m_addGroupWays.at(2).get(),3,1,1,1);
		
		m_checkInvited = CMakePtr<QCheckBox>(transfer("允许群成员邀请加入群"));
		m_checkSearched = CMakePtr<QCheckBox>(transfer("允许被搜索"));
		m_checkLayout = CMakePtr<QGridLayout>();
		m_checkLayout->setContentsMargins(60,6,0,0);
		m_lblDisturb  = CMakePtr<QLabel>(transfer("防止骚扰："));
		m_lblDisturb->setEnabled(false);
		m_lblDisturb->setMaximumWidth(60);
		
		m_checkLayout->addWidget(m_lblDisturb.get(),0,0,2,1);
		m_checkLayout->addWidget(m_checkInvited.get(),1,1,1,1);
		m_checkLayout->addWidget(m_checkSearched.get(),2,1,1,1);


		m_editName = CMakePtr<QLineEdit>();
		m_editName->setObjectName("accountEdit");
		m_editName->setMinimumWidth(220);
		m_lblEditName = CMakePtr<QLabel>(transfer("修改群名："));
		m_lblEditName->setEnabled(false);
		m_lblEditName->setMaximumWidth(60);
		m_editName->setMaxLength(12);
		m_editNameSave = CMakePtr<QPushButton>();
		m_editNameSave->setObjectName("sendbtn");
		m_editNameSave->setText(transfer("保存"));
		m_editNameSave->setMinimumWidth(40);
		m_editNameLayout = CMakePtr<QHBoxLayout>();
		m_editNameLayout->setContentsMargins(60,6,0,0);
		m_editNameLayout->addWidget(m_lblEditName.get());
		m_editNameLayout->addWidget(m_editName.get());
		m_editNameLayout->addWidget(m_editNameSave.get());
		m_editNameLayout->addStretch();

		/*m_SecretChatLayout = CMakePtr<QHBoxLayout>();
		m_SecretChatName = CMakePtr<QLabel>();
		m_SecretChatName->setEnabled(false);
		m_SecretChatName->setText(transfer("密聊模式："));
		m_SecretChatName->setMaximumWidth(60);
		m_checkSecretChat = CMakePtr<QCheckBox>();
		m_checkSecretChat->setText(transfer("是否允许群内密聊聊天"));
		m_SecretChatLayout->setContentsMargins(60,6,0,0);

		m_SecretChatLayout->addWidget(m_SecretChatName.get());
		m_SecretChatLayout->addWidget(m_checkSecretChat.get());
		m_SecretChatLayout->addStretch();*/

		m_mainLayout->addLayout(m_editNameLayout.get());
		m_mainLayout->addLayout(m_addGroupWayLayout.get());
		m_mainLayout->addLayout(m_checkLayout.get());
		//m_mainLayout->addLayout(m_SecretChatLayout.get());
		m_mainLayout->addStretch();
		setLayout(m_mainLayout.get());

		connect(m_addGroupWaysGroup.get(),SIGNAL(buttonClicked(int)),this,SLOT(onAddWayGroupClicked(int)));
		connect(m_checkInvited.get(),SIGNAL(clicked(bool)),this,SLOT(onInviteStateChanged()));
		connect(m_checkSearched.get(),SIGNAL(clicked(bool)),this,SLOT(onSearchStateChanged()));
		connect(m_editNameSave.get(),SIGNAL(clicked(bool)),this,SLOT(onSaveGroupNameClicked()));
		//connect(m_checkSecretChat.get(),SIGNAL(clicked(bool)), this, SLOT(onSerSecretCheck(bool)));
	
		IUserControl_Ptr userControl = USERCONTROL;
		if(userControl){
			CSharedPtr<data::AccountInfo> user = userControl->GetAccountInfo();
			mAccountId = user->id.value();
		}
		m_groupmgrcontrol = GROUPMGRCONTROL;
		if(m_groupmgrcontrol){
			CONNECT_SERVICE(GetGroupSet(int ,int8,int8));
			CONNECT_SERVICE(CallBack(int));
			CONNECT_SERVICE(GetGroupMem(int, data::Member&));
			//CONNECT_SERVICE(GetMemberList( int , std::vector<CSharedPtr<data::Member>>& ));
			//m_groupmgrcontrol->RegGetGrpMemListCb(CBind(&GroupInforSettingArea::signalSerGetMemberList,
				//this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	GroupInforSettingArea::~GroupInforSettingArea()
	{

	}

	void GroupInforSettingArea::onAddWayGroupClicked( int type )
	{
		if(m_groupmgrcontrol){
			int8 verify_type = type+1;
			int8 is_allow = (m_checkInvited->checkState() == Qt::Checked)?1:2;
			m_groupmgrcontrol->SetGroupSet(mGroupId,verify_type,is_allow,
				CBind(&GroupInforSettingArea::signalSerCallBack,
				this,CPlaceholders  _1));
		}
	}

	void GroupInforSettingArea::onSearchStateChanged( )
	{
		if(m_groupmgrcontrol){
			data::GroupUpdate update;
			update.groupSearch = (m_checkSearched->checkState() == Qt::Checked)?1:2;
			m_groupmgrcontrol->SetGroupInfo(mGroupId,update,
				CBind(&GroupInforSettingArea::signalSerCallBack,
				this,CPlaceholders  _1));
		}
	}

	void GroupInforSettingArea::onInviteStateChanged( )
	{
		if(m_groupmgrcontrol){
			int8 verify_type = m_addGroupWaysGroup->checkedId()+1;
			int8 is_allow = 2;
			if(m_checkInvited->checkState() == Qt::Checked){
				is_allow = 1;
			}
			m_groupmgrcontrol->SetGroupSet(mGroupId,verify_type,is_allow,
				CBind(&GroupInforSettingArea::signalSerCallBack,
				this,CPlaceholders  _1));
		}
	}

	void GroupInforSettingArea::setControlUIEnable( bool isEnable )
	{
		m_checkInvited->setEnabled(false);
		m_checkSearched->setEnabled(false);
		m_addGroupWays.at(0)->setEnabled(false);
		m_addGroupWays.at(1)->setEnabled(false);
		m_addGroupWays.at(2)->setEnabled(false);
		m_editName->setEnabled(false);
		m_editNameSave->setVisible(false);
		//m_checkSecretChat->setEnabled(isEnable);
		
	}

	void GroupInforSettingArea::updateData( int64 groupId )
	{
		mGroupId = groupId;

		if(m_groupmgrcontrol){
			data::Group group;
			m_groupmgrcontrol->GetGroupInfo(groupId,group);
			//GetOldSetInfo(group);
			m_checkSearched->setChecked(group.isSearch.value());
			m_editName->setText(QString::fromUtf8(group.info.value().groupName.value().c_str()));
			mGroupName = m_editName->text();
			m_groupmgrcontrol->GetGroupSet(groupId,CBind(&GroupInforSettingArea::signalSerGetGroupSet,
				this,CPlaceholders  _1,CPlaceholders  _2,CPlaceholders  _3));
		//	m_groupmgrcontrol->GetMemberList(groupId,CBind(&GroupInforSettingArea::signalSerGetMemberList,
		//		this,CPlaceholders  _1,CPlaceholders  _2));
			data::Member mem;
			bool ret = m_groupmgrcontrol->GetMemberInfo(groupId, mAccountId, mem);
			if (mem.memberType.value() == 2 || mem.memberType.value() == 3){
				setControlUIEnable(true);
			}
			else{
				setControlUIEnable(false);
			}
			if (ret == false){
				m_groupmgrcontrol->getGroupMemberFromNet(groupId, mAccountId,
					CBind(&GroupInforSettingArea::signalSerGetGroupMem,this,
					std::placeholders::_1, std::placeholders::_2));
			}
		}
	}

	void GroupInforSettingArea::onSerGetGroupMem(int code, data::Member& mem){
		if (mem.id.value() == mAccountId){
			if (mem.memberType.value() == 2 || mem.memberType.value() == 3){
				setControlUIEnable(true);
			}
			else{
				setControlUIEnable(false);
			}
		}
	}
	void GroupInforSettingArea::onSerGetGroupSet( int code ,int8 verify_type,int8 is_allow )
	{
		m_checkInvited->setChecked(is_allow == 1);
		if(verify_type>=1 && verify_type<=3){
			m_addGroupWays.at(verify_type-1)->setChecked(true);
		}
		emit signalGroupSet(code,verify_type,is_allow);
	}

	void GroupInforSettingArea::onSerGetMemberList( int code , std::vector<CSharedPtr<data::Member> >&mems )
	{
		for(int i=0;i<mems.size();++i){
			CSharedPtr<data::Member> mem = mems.at(i);
			if(mem == CNull){
				continue;
			}
			if(mem->id.value() == mAccountId && mGroupId == mem->groupId.value()){
				if(mem->memberType.value() == 1){
					setControlUIEnable(false);
				}else{
					setControlUIEnable(true);
				}
				return;
			}
		}
	}

	void GroupInforSettingArea::onSerCallBack( int code )
	{

	}

	void GroupInforSettingArea::onSaveGroupNameClicked()
	{
		if(m_groupmgrcontrol){
			data::GroupUpdate update;
			QString name = m_editName->text().trimmed();
			if(name.isEmpty() || mGroupName == name){
				return;
			}
			mGroupName = name;
			update.groupName = name.toUtf8().data();
			m_groupmgrcontrol->SetGroupInfo(mGroupId,update,
				CBind(&GroupInforSettingArea::signalSerCallBack,
				this,CPlaceholders  _1));
		}
	}

	void GroupInforSettingArea::onSerSecretCheck(bool IsSecretChat)
	{
		if(m_groupmgrcontrol){
			data::GroupUpdate update;
			if(IsSecretChat)
			{
				update.extendProperties = "{\"privateMsg\":1}";
			}
			else
			{
				update.extendProperties = "{\"privateMsg\":0}";
			}
			
			m_groupmgrcontrol->SetGroupInfo(mGroupId,update,
				CBind(&GroupInforSettingArea::signalSerCallBack,
				this,CPlaceholders  _1));	
		}
	}

	void GroupInforSettingArea::GetOldSetInfo(data::Group& groupInfo)
	{
		std::string SecretFlagJson = groupInfo.extend.value();
		Json::Reader reader;
		Json::Value root,fieldsarry, mJvalue;
		int ret = reader.parse(SecretFlagJson, root);
		if (!ret)
		{
			//AddLog(LOG_LEV_ERROR,"json parse filed,err=%d,json=%s",ret,SecretFlagJson.c_str());
		}
		int IntSecretValue;
		std::string strSecretValue;
		if(root["privateMsg"].isInt())
		{
			IntSecretValue = root["privateMsg"].asInt();
		}
		else
		{
			strSecretValue = root["privateMsg"].asString();
		}

		/*if(IntSecretValue == 1 || strSecretValue == "1")
		{
			m_checkSecretChat->setChecked(true);
		}
		else
		{
			m_checkSecretChat->setChecked(false);
		}*/
	}

}
