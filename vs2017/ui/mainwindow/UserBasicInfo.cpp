#include "UserBasicInfo.h"
#include "log.h"
#include <QFont>
#include <QMessageBox>
#include "../common/Common.h"
#include "json.h"
namespace ui{
    UserBasicInfo::UserBasicInfo(QWidget* parent):QWidget(parent)
    {
        m_usercontrol = USERCONTROL;
        CONNECT_SERVICE(UpdateInfoResult(int));

		GetUserInfo();
        IntWidgets();
		SetUserInfo();
    }


    UserBasicInfo::~UserBasicInfo(void)
    {
    }

	bool UserBasicInfo::GetUserInfo()
	{
		if (m_usercontrol)
			m_userInfo = m_usercontrol->GetAccountInfo();

		m_Name = QString::fromUtf8(m_userInfo->name.value().data());
		std::string ExtendInfo = m_userInfo->entExtends.value();
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(ExtendInfo,root);
		if (!ret)
		{
			return false;
		}

		if (root.isArray())
		{
			
			for (int i = 0; i < root.size(); i++)
			{
				if (root[i]["type"].isString())
				{
					type = root[0]["type"].asString();
				}

				//if (root[i]["sex"].isInt())
				//{
				//	int sex = root[i]["sex"].asInt();
				//	if (sex == 1)
				//	{
				//		m_Sex = transfer("��");
				//	}
				//	if (sex == 2)
				//	{
				//		m_Sex = transfer("Ů");
				//	}

				//	if (sex == 0)
				//	{
				//		m_Sex = transfer("����");
				//	}
				//	//m_Sex = root[i]["sex"].asInt() == 1 ? transfer("��") : root[i]["sex"].asInt() == 2 ?
				//	//	transfer("Ů") : transfer("����");
				//}

				if (root[i]["nation"].isString())
				{
					m_Nation = QString::fromUtf8(root[i]["nation"].asString().data());
				}

				if ("1" == type)
				{
					if (root[i]["unit"].isString())
					{
						m_unit = QString::fromUtf8(root[i]["unit"].asString().data());
					}

					if (root[i]["office"].isString())
					{
						m_office = QString::fromUtf8(root[i]["office"].asString().data());
					}

					if (root[i]["m_position"].isString())
					{
						m_position = QString::fromUtf8(root[i]["m_position"].asString().data());
					}
				}

				if ("0" == type)
				{
					if (root[i]["CPPCCPosition"].isString())
					{
						m_position = QString::fromUtf8(root[i]["CPPCCPosition"].asString().data());
					}

					if (root[i]["sector"].isString())
					{
						m_sector = QString::fromUtf8(root[i]["sector"].asString().data());
					}

					if (root[i]["group"].isString())
					{
						m_group = QString::fromUtf8(root[i]["group"].asString().data());
					}

					if (root[i]["specialCommittee"].isString())
					{
						m_specialCommittee = QString::fromUtf8(root[i]["specialCommittee"].asString().data());
					}

					if (root[i]["specialCommitteeDuty"].isString())
					{
						m_specialCommitteeDuty = QString::fromUtf8(root[i]["specialCommitteeDuty"].asString().data());
					}

					if (root[i]["currentPosition"].isString())
					{
						m_currentPosition = QString::fromUtf8(root[i]["currentPosition"].asString().data());
					}

					if (root[i]["myLocation"].isString())
					{
						m_myLocation = QString::fromUtf8(root[i]["myLocation"].asString().data());
					}
				}	
				break;
			}
		return true;
		}
	}

    void UserBasicInfo::IntWidgets()
    {
		m_pInfoLayout = new QFormLayout(this);
		m_pMainLayout = new QVBoxLayout(this);
		m_pNameLayout = new QHBoxLayout(this);

		m_FormWidget = new QWidget(this);
		m_pLabelName = new QLabel(this);  //����
		m_pLabelSex = new QLabel(this);   //�Ա�
		m_pLabelSex->setVisible(false);

		m_pLabelNation = new QLabel(this); //����
		m_pLabelunit = new QLabel(this);   //��λ
		m_pLabeloffice = new QLabel(this);   //����
		m_pLabelposition = new QLabel(this); //ְλ

		m_pLabelNation = new QLabel(this);  //����
		m_pLabelposition = new QLabel(this);  //ְλ
		m_pLabelsector = new QLabel(this);    //���
		m_pLabelgroup = new QLabel(this);  //����
		m_pLabelspecialCommittee = new QLabel(this);   //רί��
		m_pLabelspecialCommitteeDuty = new QLabel(this);   //רί��ְ��
		m_pLabelcurrentPosition = new QLabel(this);  //����ְ��
		m_pLabelmyLocation = new QLabel(this);    //���ڵ�

		m_pLabelspecialCommitteeDuty->setFixedWidth(210);
		m_pLabelspecialCommitteeDuty->setWordWrap(true);
		m_pLabelspecialCommitteeDuty->setContentsMargins(0, 5, 0, 0);

		m_pLabelcurrentPosition->setFixedWidth(210);
		m_pLabelcurrentPosition->setWordWrap(true);
		m_pLabelcurrentPosition->setContentsMargins(0,5,0,0);

		QFont ft;
		ft.setPointSize(14);
		m_pLabelName->setFont(ft);
		m_pLabelName->setAlignment(Qt::AlignCenter);
		m_pLabelName->setFixedWidth(250);
		m_pLabelName->setWordWrap(true);

		m_pInfoLayout->setLabelAlignment(Qt::AlignTop);
		m_FormWidget->setLayout(m_pInfoLayout);
		m_pMainLayout->setSpacing(10);
		m_pMainLayout->addWidget(m_pLabelName,0,Qt::AlignHCenter);
		m_pMainLayout->addWidget(m_FormWidget);

		if (type == "1")
		{
			//m_pInfoLayout->addRow(transfer("��  ��"), m_pLabelSex);
			m_pInfoLayout->addRow(transfer("��  �壺"), m_pLabelNation);
			m_pInfoLayout->addRow(transfer("��  λ��"), m_pLabelunit);
			m_pInfoLayout->addRow(transfer("��  �ң�"), m_pLabeloffice);
			m_pInfoLayout->addRow(transfer("ְ  λ��"), m_pLabelposition);
			m_pInfoLayout->setHorizontalSpacing(5);
			m_pInfoLayout->setVerticalSpacing(10);
			m_pInfoLayout->setContentsMargins(25, 0, 0, 10);
		}

		if (type == "0")
		{
			//m_pInfoLayout->addRow(transfer("��          ��"), m_pLabelSex);
			m_pInfoLayout->addRow(transfer("��          �壺"), m_pLabelNation);
			m_pInfoLayout->addRow(transfer("ְ          ��"), m_pLabelposition);
			m_pInfoLayout->addRow(transfer("��          ��"), m_pLabelsector);
			m_pInfoLayout->addRow(transfer("��          ��"), m_pLabelgroup);
			m_pInfoLayout->addRow(transfer("ר   ί   �᣺"), m_pLabelspecialCommittee);
			m_pInfoLayout->addRow(transfer("רί��ְ��"), m_pLabelspecialCommitteeDuty);
			m_pInfoLayout->addRow(transfer("�� �� ְ ��"), m_pLabelcurrentPosition);
			m_pInfoLayout->addRow(transfer("��   ��   �أ�"), m_pLabelmyLocation);
			m_pInfoLayout->setHorizontalSpacing(5);
			m_pInfoLayout->setVerticalSpacing(10);
			m_pInfoLayout->setContentsMargins(25, 0, 0, 10);
		}
		this->setLayout(m_pMainLayout);
    }

	void UserBasicInfo::SetUserInfo()
	{
		m_pLabelName->setText(m_Name);
		if (type == "1")
		{
			m_pLabelSex->setText(m_Sex);
			m_pLabelNation->setText(m_Nation);
			m_pLabelunit->setText(m_unit);
			m_pLabeloffice->setText(m_office);
			m_pLabelposition->setText(m_position);
		}

		if (type == "0")
		{
			m_pLabelSex->setText(m_Sex);
			m_pLabelNation->setText(m_Nation);
			m_pLabelposition->setText(m_position);
			m_pLabelsector->setText(m_sector);
			m_pLabelgroup->setText(m_group);
			m_pLabelspecialCommittee->setText(m_specialCommittee);
			m_pLabelspecialCommitteeDuty->setText(m_specialCommitteeDuty);
			m_pLabelcurrentPosition->setText(m_currentPosition);
			m_pLabelmyLocation->setText(m_myLocation);

			m_pLabelcurrentPosition->resize(m_pLabelcurrentPosition->width(), m_pLabelcurrentPosition->height()+10);
			m_pLabelspecialCommitteeDuty->resize(m_pLabelspecialCommitteeDuty->width(), m_pLabelspecialCommitteeDuty->height()+10);
			m_pLabelspecialCommitteeDuty->adjustSize();
			this->adjustSize();
		}
	}

    void UserBasicInfo::onSerUpdateInfoResult( int result )
    {
        AddLog(LOG_LEV_INFO,LOG_FILE,"onSerUpdateInfoResult result =%d",result);
    }
}

