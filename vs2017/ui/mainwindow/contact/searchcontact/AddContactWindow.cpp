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
		m_verifyInfoEdit->setText(transfer("����")+QString::fromUtf8(accountInfo->name.value().c_str()));
		//��ȡ��֤��Ϣ
		if (data::GROUP_TYPE == dataInfo.resultType)
		{
			m_remarkTipLbl->setVisible(false);
			m_pRemakLineEdit->setVisible(false);
			m_pTitle->setText(transfer("���Ⱥ"));
			m_groupControl->GetGroupSet(dataInfo.targetid, CBind(&AddContactWindow::signalSerGetGroupVerifyType,
				this, CPlaceholders  _1, CPlaceholders  _2, CPlaceholders  _3));
			
		}
		else if (data::USER_TYPE == dataInfo.resultType)
		{
			m_pTitle->setText(transfer("��Ӻ���"));
			m_contactControl->GetVerifyType(dataInfo.targetid, CBind(&AddContactWindow::signalSerGetUserVerifyType,
				this, CPlaceholders  _1, CPlaceholders  _2));

		}
	}
	void AddContactWindow::setAttribute()
	{
		//������
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
		//�����
		m_pRemakLineEdit = new QLineEdit(this);
		m_pRemakLineEdit->setObjectName("accountEdit");
		m_pRemakLineEdit->setFixedSize(QSize(150,30));
		m_pRemakLineEdit->setMaxLength(25);

		//��֤��Ϣ�����
		m_verifyInfoEdit = new QTextEdit(this);
		m_verifyInfoEdit->setFixedSize(350,74);
		m_pRemakLineEdit->setMaxLength(100);
	
		//ȷ��
		m_pBtnOk = new QPushButton(this);
		m_pBtnOk->setObjectName("sendbtn");
		m_pBtnOk->setText(transfer("ȷ��"));
		m_pBtnOk->setFixedSize(50, 22);

		//ȡ��
		m_pBtnCancel = new QPushButton(this);
		m_pBtnCancel->setObjectName("sendbtn");
		m_pBtnCancel->setText(transfer("ȡ��"));
		m_pBtnCancel->setFixedSize(50, 22);

		connect(m_pCloseButton,SIGNAL(clicked()),this,SLOT(close()));
		connect(m_pBtnOk, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
		connect(m_pBtnCancel, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));

	}

	void AddContactWindow::layout()
	{
		//������
		m_pTitleBtnLayout->setContentsMargins(10, 0, 0, 0);
		m_pTitleBtnLayout->addWidget(m_pTitle);
		m_pTitleBtnLayout->addStretch();
		m_pTitleBtnLayout->addWidget(m_pCloseButton, 0, Qt::AlignTop);

		//����ͼ
		m_pBackground->setLayout(m_pTitleBtnLayout);
		m_pBackground->setMinimumSize(this->width()-20, m_pCloseButton->height());
		m_pBackground->move(10,0);

		//�����ť����
		QHBoxLayout* pHeadLayout =new QHBoxLayout();
		pHeadLayout->setSpacing(20);
		pHeadLayout->setAlignment(Qt::AlignHCenter);
		pHeadLayout->setContentsMargins(1, 5, 1 ,5);

		pHeadLayout->addWidget(m_pImgHead);
		pHeadLayout->addWidget(m_pLblName);
		pHeadLayout->addStretch();
	
		m_verifyTipLbl = new QLabel(this);
		m_verifyTipLbl->setText(transfer("��������֤��Ϣ��"));
		m_verifyTipLbl->setAlignment(Qt::AlignVCenter);

		m_remarkTipLbl = new QLabel(this);
		m_remarkTipLbl->setText(transfer("��ע��"));

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
		//_2  ��֤����: 1.�������κ������, 2.��Ҫ��֤��Ϣ, 3.�����κ������.\n
		//_3	 �Ƿ�����Ⱥ��Ա������Ѽ���Ⱥ: 1.���� 2.������.
		AddLog(LOG_LEV_DEBUG,"verifyType = %d", verifyType);
		if (1 == verifyType)
		{
			m_verifyTipLbl->setAlignment(Qt::AlignHCenter);
			m_verifyTipLbl->setText(transfer("��Ⱥ�����˲������κ�����ӣ�"));
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
		 ///<��֤����1��Ҫ��֤��Ϣ:2:�������κ������,3:�����κ������
		AddLog(LOG_LEV_DEBUG,"targetId =%lld, verifyType = %d", verifyType.userid, verifyType.type);
		if (2 == verifyType.type)
		{
			m_verifyTipLbl->setAlignment(Qt::AlignHCenter);
			m_verifyTipLbl->setText(transfer("�Է����ò������κ�����ӣ�"));
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
			uicontrols::WeMessageBox::showInformation(this,transfer("��ʾ"),transfer("������Ӻ�����Ϣ�ѷ��ͣ��ȴ��Է�ͬ��"));
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
			if (m_pTitle->text() == transfer("��Ӻ���"))
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
			if (m_pTitle->text() == transfer("��Ӻ���"))
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
		m_verifyInfoEdit->setText(transfer("����")+QString::fromUtf8(accountInfo->name.value().c_str()));

		for(int i=0; i<dataInfo.size(); i++)
		{
			if (data::USER_TYPE == dataInfo.at(i).resultType)
			{
				m_pTitle->setText(transfer("��Ӻ���"));
				m_contactControl->GetVerifyType(dataInfo.at(i).targetid, CBind(&AddContactWindow::signalSerGetUserVerifyType,
					this, CPlaceholders  _1, CPlaceholders  _2));
				mVectorId.push_back(dataInfo.at(i).targetid);
			}
		}
	}


}