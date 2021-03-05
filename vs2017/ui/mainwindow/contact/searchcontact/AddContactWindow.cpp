#include "AddContactWindow.h"
#include <QApplication>
#include "controls/PushButton.h"
#include "SearchResultListWidget.h"
#include <log.h>
#include "controls/headimage.h"
#include "common/Common.h"
#include "controls/WeMessageBox.h"
namespace ui{
	AddContactWindow::AddContactWindow(QWidget *parent)
		: BaseDialog(parent),m_id(0),type(0)
	{
		m_usercontrol = USERCONTROL;
		m_contactControl = CONTACTMGRCONTROL;
		m_groupControl = GROUPMGRCONTROL;

		CONNECT_SERVICE(GetUserVerifyType(int , data::ContactVerifyType& ));
		CONNECT_SERVICE(AddContact(int ));
		CONNECT_SERVICE(GetGroupVerifyType(int , int8 , int8 ));

		setFixedSize(400,290);
		setModal(true);
		setAttribute();
		layout();
	}

	AddContactWindow::~AddContactWindow()
	{
	}
	void AddContactWindow::InitData(const data::SearchResultInfo& dataInfo)
	{
		type = 0;
		m_id = dataInfo.targetid;
		QString head = dataInfo.avatar.c_str();
		if(head.isEmpty()){
			head = (data::USER_TYPE==dataInfo.resultType) ? DEFAULT_AVATAR : ((data::GROUP_TYPE==dataInfo.resultType) ? DEFAULT_GROUP : DEFAULT_APP);
		}
		m_pLblName->setText(QString::fromUtf8(dataInfo.name.c_str()));
		m_pImgHead->setAvatarPath(head);

		CSharedPtr<data::AccountInfo> accountInfo = m_usercontrol->GetAccountInfo();
		m_verifyInfoEdit->setText(transfer("我是")+QString::fromUtf8(accountInfo->name.value().c_str()));
		//获取验证信息
		if (data::GROUP_TYPE == dataInfo.resultType)
		{
			m_remarkTipLbl->setVisible(false);
			m_pRemakLineEdit->setVisible(false);
			m_pTitle->setText(transfer("添加群"));
			m_groupControl->GetGroupSet(dataInfo.targetid, CBind(&AddContactWindow::signalSerGetGroupVerifyType,
				this, CPlaceholders  _1, CPlaceholders  _2, CPlaceholders  _3));
			
		}
		else if (data::USER_TYPE == dataInfo.resultType)
		{
			m_pTitle->setText(transfer("添加好友"));
			m_contactControl->GetVerifyType(dataInfo.targetid, CBind(&AddContactWindow::signalSerGetUserVerifyType,
				this, CPlaceholders  _1, CPlaceholders  _2));

		}
	}
	void AddContactWindow::setAttribute()
	{
		//标题栏
		m_pCloseButton = new PushButton(this);
		m_pBackground  = new QLabel(this);
		m_pTitleBtnLayout = new QHBoxLayout();

		m_pMainLayout = new QVBoxLayout(this);
		m_pMainLayout->setSpacing(10);
		m_pMainLayout->setContentsMargins(25, 5, 30 ,20);

		m_pBackground->setTextFormat(Qt::PlainText);
		m_pBackground->setScaledContents(true);
		m_pBackground->setObjectName("loginBackground");
		m_pCloseButton->setPicName(QString(":/login/close"));

		m_pTitle = new QLabel(this);
		m_pTitle->setText(transfer(""));
		m_pTitle->setObjectName("whiteLabel");

		m_pLblName = new QLabel(this);
		m_pImgHead =new HeadImage(this,QSize(HEAD_SIZE,HEAD_SIZE));
		//输入框
		m_pRemakLineEdit = new QLineEdit(this);
		m_pRemakLineEdit->setObjectName("accountEdit");
		m_pRemakLineEdit->setFixedSize(QSize(150,30));
		m_pRemakLineEdit->setMaxLength(25);

		//验证信息输入框
		m_verifyInfoEdit = new QTextEdit(this);
		m_verifyInfoEdit->setFixedSize(350,74);
		m_pRemakLineEdit->setMaxLength(100);
	
		//确定
		m_pBtnOk = new QPushButton(this);
		m_pBtnOk->setObjectName("sendbtn");
		m_pBtnOk->setText(transfer("确定"));
		m_pBtnOk->setFixedSize(50, 22);

		//取消
		m_pBtnCancel = new QPushButton(this);
		m_pBtnCancel->setObjectName("sendbtn");
		m_pBtnCancel->setText(transfer("取消"));
		m_pBtnCancel->setFixedSize(50, 22);

		connect(m_pCloseButton,SIGNAL(clicked()),this,SLOT(close()));
		connect(m_pBtnOk, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
		connect(m_pBtnCancel, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));

	}

	void AddContactWindow::layout()
	{
		//标题栏
		m_pTitleBtnLayout->setContentsMargins(10, 0, 0, 0);
		m_pTitleBtnLayout->addWidget(m_pTitle);
		m_pTitleBtnLayout->addStretch();
		m_pTitleBtnLayout->addWidget(m_pCloseButton, 0, Qt::AlignTop);

		//背景图
		m_pBackground->setLayout(m_pTitleBtnLayout);
		m_pBackground->setMinimumSize(this->width()-20, m_pCloseButton->height());
		m_pBackground->move(10,0);

		//输入框按钮布局
		QHBoxLayout* pHeadLayout =new QHBoxLayout();
		pHeadLayout->setSpacing(20);
		pHeadLayout->setAlignment(Qt::AlignHCenter);
		pHeadLayout->setContentsMargins(1, 5, 1 ,5);

		pHeadLayout->addWidget(m_pImgHead);
		pHeadLayout->addWidget(m_pLblName);
		pHeadLayout->addStretch();
	
		m_verifyTipLbl = new QLabel(this);
		m_verifyTipLbl->setText(transfer("请输入验证信息："));
		m_verifyTipLbl->setAlignment(Qt::AlignVCenter);

		m_remarkTipLbl = new QLabel(this);
		m_remarkTipLbl->setText(transfer("备注："));

		QHBoxLayout* pHRemarkLayout = new QHBoxLayout;
		pHRemarkLayout->setSpacing(8);
		pHRemarkLayout->addWidget(m_remarkTipLbl);
		pHRemarkLayout->addWidget(m_pRemakLineEdit);
		pHRemarkLayout->addStretch();

		QHBoxLayout* pHBtnayout = new QHBoxLayout;
		pHBtnayout->setSpacing(12);
		pHBtnayout->addStretch();
		pHBtnayout->addWidget(m_pBtnOk);
		pHBtnayout->addWidget(m_pBtnCancel);
		

		m_pMainLayout->addLayout(m_pTitleBtnLayout);
		m_pMainLayout->addSpacing(30);
		m_pMainLayout->addLayout(pHeadLayout);
		m_pMainLayout->addStretch();
		m_pMainLayout->addWidget(m_verifyTipLbl);
		m_pMainLayout->addWidget(m_verifyInfoEdit);
		m_pMainLayout->addStretch();
		m_pMainLayout->addLayout(pHRemarkLayout);
		m_pMainLayout->addLayout(pHBtnayout);


		setLayout(m_pMainLayout);

	}
	void AddContactWindow::onSerGetGroupVerifyType(int err, int8 verifyType, int8 isInvite)
	{
		BEGIN;
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"errCode=%d",err);
			return;
		}
		//_2  验证类型: 1.不允许任何人添加, 2.需要验证信息, 3.允许任何人添加.\n
		//_3	 是否允许群成员邀请好友加入群: 1.允许 2.不允许.
		AddLog(LOG_LEV_DEBUG,"verifyType = %d", verifyType);
		if (1 == verifyType)
		{
			m_verifyTipLbl->setAlignment(Qt::AlignHCenter);
			m_verifyTipLbl->setText(transfer("该群设置了不允许任何人添加！"));
			m_verifyInfoEdit->setVisible(false);
			m_pRemakLineEdit->setVisible(false);
			m_remarkTipLbl->setVisible(false);
			m_pBtnOk->setVisible(false);
		}
		else if (3 == verifyType)
		{
			m_verifyTipLbl->setVisible(false);
			m_verifyInfoEdit->setVisible(false);
		}
		else
		{

		}
		END;
	}
	void AddContactWindow::onSerGetUserVerifyType(int err, data::ContactVerifyType& verifyType)
	{
		BEGIN;
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"errCode=%d",err);
			return;
		}
		 ///<验证类型1需要验证信息:2:不允许任何人添加,3:允许任何人添加
		AddLog(LOG_LEV_DEBUG,"targetId =%lld, verifyType = %d", verifyType.userid, verifyType.type);
		if (2 == verifyType.type)
		{
			m_verifyTipLbl->setAlignment(Qt::AlignHCenter);
			m_verifyTipLbl->setText(transfer("对方设置不允许任何人添加！"));
			m_verifyInfoEdit->setVisible(false);
			m_pRemakLineEdit->setVisible(false);
			m_remarkTipLbl->setVisible(false);
			m_pBtnOk->setVisible(false);
		}
		else if (3 == verifyType.type)
		{
			m_verifyTipLbl->setVisible(false);
			m_verifyInfoEdit->setVisible(false);
		}
		END;
	}
	void AddContactWindow::onSerAddContact(int err)
	{
		BEGIN;
		if (err != 0)
		{
			AddLog(LOG_LEV_ERROR,"errCode=%d",err);
		}
		else {
			uicontrols::WeMessageBox::showInformation(this,transfer("提示"),transfer("申请添加好友消息已发送，等待对方同意"));
		}
		if (type == 1)
		{
			emit signalSerAddFriden();
		}
		this->close();
		END;
	}
	void AddContactWindow::onOkBtnClicked()
	{
		if(0 == type)
		{
			QString remakName = m_pRemakLineEdit->text();
			remakName = remakName.trimmed();
			QString verifyInfo = m_verifyInfoEdit->toPlainText();
			verifyInfo = verifyInfo.trimmed();
			if (m_pTitle->text() == transfer("添加好友"))
			{
				m_contactControl->AddContact(m_id, remakName.toUtf8().data(),verifyInfo.toUtf8().data(),
					CBind(&AddContactWindow::signalSerAddContact, this, CPlaceholders  _1));
			}else{
				IGroupMgrControl_Ptr groupControl = GROUPMGRCONTROL;
				if(groupControl){
					groupControl->AddGroup(m_id,verifyInfo.toUtf8().data(),
						CBind(&AddContactWindow::signalSerAddContact, this, CPlaceholders  _1));
				}
			}
		}
		
		if(type == 1)
		{		
			QString remakName = m_pRemakLineEdit->text();
			remakName = remakName.trimmed();
			QString verifyInfo = m_verifyInfoEdit->toPlainText();
			verifyInfo = verifyInfo.trimmed();
			if (m_pTitle->text() == transfer("添加好友"))
			{
				for(int i=0; i<mVectorId.size(); i++)
				{
					m_contactControl->AddContact(mVectorId.at(i), remakName.toUtf8().data(),verifyInfo.toUtf8().data(),
						CBind(&AddContactWindow::signalSerAddContact, this, CPlaceholders  _1));
				}	
			}
		}
	}

	void AddContactWindow::onCancelBtnClicked()
	{
		this->close();
	}

	void AddContactWindow::InitDatas(std::vector<data::SearchResultInfo>& dataInfo)
	{	
		mVectorId.clear();
		type = 1;
		QString head =   DEFAULT_GROUP ;
		QString tName = "";
		for(int i=0; i<dataInfo.size() && i<3; i++)
		{
			tName += dataInfo.at(i).name.c_str();
			if(i != 2)
				tName += ",";
		}
		m_pLblName->setText(tName);
		m_pImgHead->setAvatarPath(head);

		CSharedPtr<data::AccountInfo> accountInfo = m_usercontrol->GetAccountInfo();
		m_verifyInfoEdit->setText(transfer("我是")+QString::fromUtf8(accountInfo->name.value().c_str()));

		for(int i=0; i<dataInfo.size(); i++)
		{
			if (data::USER_TYPE == dataInfo.at(i).resultType)
			{
				m_pTitle->setText(transfer("添加好友"));
				m_contactControl->GetVerifyType(dataInfo.at(i).targetid, CBind(&AddContactWindow::signalSerGetUserVerifyType,
					this, CPlaceholders  _1, CPlaceholders  _2));
				mVectorId.push_back(dataInfo.at(i).targetid);
			}
		}
	}


}