#include "GroupInforWidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPushButton>

#include <data/GroupData.h>
#include <data/UserData.h>
#include <interface/IUserControl.h>

#include "ui/mainwindow/SelectHeadImgWidget.h"
#include "../../../utils/Error.h"
#include<qmessagebox.h>

#include "controls/headimage.h"
#include "common/Controlptr.h"
#include "common/Connect.h"
#include "controls/ToolButton.h"
#include "controls/PushButton.h"
#include "data/ChatData.h"
#include "../../../utils/common.h"
#include "GroupInforSettingTabWidget.h"
#include "../../../common/Common.h"
namespace ui{
	GroupInforWidget::GroupInforWidget(QWidget *parent)
		: m_btnBottomSendMsg(CNull),m_btnSendMsg(CNull),QWidget(parent)
	{
		mCLoseAfterChat = false;
		this->setMouseTracking(true);
		setObjectName("enterpriseInfo_centerWidget");
		initControl();

		m_backgroundLayout = CMakePtr<QVBoxLayout>();
		m_backgroundLayout->setAlignment(Qt::AlignHCenter);
		m_backgroundLayout->setSpacing(0);
		m_backgroundLayout->setContentsMargins(0,35,0,0);

		m_headAreaBackWidget = CMakePtr<QWidget>();
		m_headAreaBackWidget->setObjectName("enterpriseInfo_centerHeadWidget");
		m_headAreaBackWidget->setMinimumSize(QSize(440,180));
		m_headAreaBackWidget->setMaximumSize(QSize(440,180));

		m_headAreaLayout = CMakePtr<QVBoxLayout>();
		m_headAreaLayout->setSpacing(0);
		m_headAreaLayout->setContentsMargins(0,10,0,0);

		m_groupHeadWidget = CMakePtr<HeadImage>(m_headAreaBackWidget.get());
		m_lblName = CMakePtr<QLineEdit>(m_headAreaBackWidget.get());
		m_lblName->setFont(QFont("",12));

		m_lblId = CMakePtr<QLineEdit>(m_headAreaBackWidget.get());
		m_lblName->setAlignment(Qt::AlignHCenter);
		m_lblId->setAlignment(Qt::AlignHCenter);
		m_lblName->setReadOnly(true);
		m_lblId->setReadOnly(true);
		m_lblName->setObjectName("groupinfolineedit");
		m_lblId->setObjectName("groupinfolineedit");
		
		m_headAreaLayout->addWidget(m_groupHeadWidget.get(),0,Qt::AlignHCenter);
		m_headAreaLayout->addWidget(m_lblName.get());
		m_headAreaLayout->addWidget(m_lblId.get());
		m_headAreaBackWidget->setLayout(m_headAreaLayout.get());

		m_inforAreaBackWidget = CMakePtr<QWidget>();
		m_inforAreaBackWidget->setObjectName("groupinfobackground");
		m_inforAreaBackWidget->setMinimumSize(QSize(440,360));
		m_inforAreaBackWidget->setMaximumSize(QSize(440,360));

		m_inforTab = CMakePtr<GroupInforSettingTabWidget>(m_inforAreaBackWidget.get());
		/*m_inforTab->setMinimumSize(QSize(420,300));
		m_inforTab->setMaximumSize(QSize(440,300));*/
		m_inforTab->setFixedSize(420, 300);
		
		connect(m_inforTab.get(),SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));		
		connect(m_inforTab.get(), SIGNAL(signalSerDelUiFile(int64)), this, SLOT(onSerDelUiFile(int64)));
		//m_btnEditInfo = CMakePtr<QPushButton>(m_inforAreaBackWidget.get());
		//m_btnEditInfo->setText(transfer("编辑资料"));
		//m_btnEditInfo->setObjectName("goupinfoeidtprofile");
		//m_btnEditInfo->move(30,8);	
		
		m_btnSendMsg = new ToolButton(":/contact/sendmsg",m_headAreaBackWidget.get(),false);
		m_btnSendMsg->setToolTip(transfer("发消息"));
		m_btnSendMsg->move(m_headAreaBackWidget->width() - 80,m_headAreaBackWidget->height()-m_btnSendMsg->height()/2);

		m_btnBottomSendMsg = new ToolButton(":/contact/sendmsg",m_inforAreaBackWidget.get(),false);
		m_btnBottomSendMsg->setToolTip(transfer("发消息"));
		m_btnBottomSendMsg->move(m_headAreaBackWidget->width() - 80,-m_btnSendMsg->height()/2);
		connect(m_btnSendMsg,SIGNAL(clicked()),this,SLOT(onStartChat()));
		connect(m_btnBottomSendMsg,SIGNAL(clicked()),this,SLOT(onStartChat()));
		//m_SendMsgBtn->move((m_inforAreaBackWidget->width() - 150) / 2, m_inforAreaBackWidget->height() - 320);
		m_btnBottomSendMsg->setVisible(false);
		m_btnSendMsg->setVisible(false);
		
		m_SendMsgBtn = new QPushButton(m_inforAreaBackWidget.get());
		m_SendMsgBtn->setObjectName("sendbtn");
		
		m_SendMsgBtn->setText(transfer("发消息"));
		m_SendMsgBtn->setFixedSize(200, 35);
		//m_SendMsgBtn->move(m_headAreaBackWidget->width() - 80, m_headAreaBackWidget->height() - m_btnSendMsg->height() / 2);
		connect(m_SendMsgBtn, SIGNAL(clicked()),this,SLOT(onStartChat()));
		
		QVBoxLayout* tempLayout = new QVBoxLayout(m_inforAreaBackWidget.get());
		tempLayout->addWidget(m_inforTab.get(),0,Qt::AlignHCenter);
		tempLayout->addWidget(m_SendMsgBtn, 0, Qt::AlignHCenter);
		tempLayout->setSpacing(20);
		m_inforAreaBackWidget->setLayout(tempLayout);

		m_backgroundLayout->addWidget(m_headAreaBackWidget.get());
		m_backgroundLayout->addWidget(m_inforAreaBackWidget.get());
		setLayout(m_backgroundLayout.get());

		CONNECT_SERVICE(UpgroupInfo(int));
		CONNECT_SERVICE(GetMemInfo(int, data::Member&));
		connect(m_groupHeadWidget.get(), SIGNAL(clicked(QPoint)), this,SLOT(onSerModifyHead()));
		//connect(m_btnEditInfo.get(),SIGNAL(clicked(bool)),this,SLOT(onEditProfile()));

		m_usercontrol = USERCONTROL;
		m_userid = m_usercontrol->GetAccountInfo()->id.value();
	}

	void GroupInforWidget::setStartChatCLose(bool bClose)
	{
		mCLoseAfterChat = bClose;
	}
	GroupInforWidget::~GroupInforWidget()
	{
		if(m_btnSendMsg != CNull){
			delete m_btnSendMsg;
		}
		if(m_btnBottomSendMsg != CNull){
			delete m_btnBottomSendMsg;
		}
	}

	void GroupInforWidget::onSerModifyHead()
	{
		SelectHeadImgWidget* m_selImgWidget = new SelectHeadImgWidget;
		connect(m_selImgWidget, SIGNAL(signalUserHeadSucc(QString)), this, SLOT(onUserHeadSucc(QString)), Qt::QueuedConnection);
		connect(m_selImgWidget, SIGNAL(signalSerModifyGroupHead(std::string&)), this, SLOT(onGroupHeadSucc(std::string&)), Qt::QueuedConnection);
		connect(this, SIGNAL(signalSerUpSuccess(int)), m_selImgWidget, SIGNAL(signalSerSetUserInfoHead(int)));
		int x = this->mapToGlobal(QPoint(this->x(), this->y())).x();
		int y = this->mapToGlobal(QPoint(this->x(), this->y())).y();
		m_selImgWidget->setHeadType(2);
		m_selImgWidget->setFixedSize(600, 450);
		m_selImgWidget->setObjectName("widgetHead");
		m_selImgWidget->setFocus();
		m_selImgWidget->show();
	}

	void GroupInforWidget::onUserHeadSucc(QString headImg)
	{
		m_groupHeadWidget->setAvatarPath(headImg);
		emit signalSerUpSuccess(0);
	}

	void GroupInforWidget::onGroupHeadSucc(std::string& headUrl)
	{
		data::GroupUpdate groupData;
		groupData.groupIcon = headUrl;
		m_groupmgrcontrol->SetGroupInfo(group.info.value().groupId.value(), groupData, CBind(&GroupInforWidget::signalSerUpgroupInfo,this,CPlaceholders  _1));
	}

	void GroupInforWidget::onSerUpgroupInfo(int code)
	{
		if (code != 0){
			utils::Error::InitErrInfo(true);
			std::string error = utils::Error::GetErrMsg(code);
			QMessageBox::information(this, transfer("提示"), transfer(error.c_str()), transfer("确认"));
		}
	}

	void GroupInforWidget::paintEvent( QPaintEvent *event )
	{
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

	void GroupInforWidget::initControl()
	{
		m_groupmgrcontrol = GROUPMGRCONTROL;
		if(m_groupmgrcontrol){
		}
	}

	void GroupInforWidget::updateData( int64 groupId )
	{
		if(m_groupmgrcontrol){

			data::Member member;
			bool isTure = m_groupmgrcontrol->GetMemberInfo(groupId, m_userid, member);

			if (isTure)
			{
				if (member.memberType.value() == 3){
					m_groupHeadWidget->setMouseInStyle(true);
					m_groupHeadWidget->setToolTip(transfer("修改图像"));
				}else{
					m_groupHeadWidget->setMouseInStyle(false);
				}
			}
			else{
				m_groupmgrcontrol->getGroupMemberFromNet(groupId, m_userid, CBind(&GroupInforWidget::signalSerGetMemInfo,this,CPlaceholders  _1,CPlaceholders  _2));
			}

			m_groupmgrcontrol->GetGroupInfo(groupId,group);
			QString head = transfer(group.info.value().avatar.value().c_str());
			if(head.isEmpty()){
				head = ":/base/group_head";
			}
			m_groupHeadWidget->setAvatarPath(head);
			m_lblName->setText(QString::fromUtf8(group.info.value().groupName.value().c_str()));
			m_lblId->setText(QString::number(group.info.value().groupId.value()));

			m_inforTab->updateData(groupId);
		}
	}

	void GroupInforWidget::onSerGetMemInfo(int code, data::Member& mem)
	{
		if (code == 0 && mem.memberType.value() == 3)
		{
			m_groupHeadWidget->setMouseInStyle(true);
			m_groupHeadWidget->setToolTip(transfer("修改图像"));
		}
		else{
			m_groupHeadWidget->setMouseInStyle(false);
		}
	}

	void GroupInforWidget::onStartChat()
	{
		CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
		chat->chatType = data::GROUP_CHAT;
		chat->isStartChat = true;
		std::string head = group.info.value().avatar.value().c_str();
		chat->avatar   = utils::FileIsExist(head)?head:"";
		chat->name = QString::fromUtf8(group.info.value().groupName.value().c_str()).toStdString();
		chat->targetid = group.info.value().groupId.value();
		emit startChat(chat);
		if (mCLoseAfterChat) {
			this->close();
		}
	}

	void GroupInforWidget::onEditProfile()
	{
		static int i = 0;
		m_inforTab->setVisible(i%2== 0);
		i++;
	}

	void GroupInforWidget::onSerDelUiFile(int64 filelocalid)
	{
		emit signalSerDelUiFile(filelocalid, group.info.value().groupId.value());
	}

}
