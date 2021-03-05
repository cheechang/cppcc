#pragma once
#include<QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include "common/controlptr.h"
#include "controls/MyQComboBox.h"

namespace ui{
    class MyQComboBox;

    class UserBasicInfo :    public QWidget
    {
        Q_OBJECT
    public:
        explicit UserBasicInfo(QWidget* parent);
        ~UserBasicInfo(void);
       // void setWidgetsEnable(bool enable);
       // void ResetUserInfo();
		bool GetUserInfo();
		void SetUserInfo();
    signals:
        void signalSerUpdateInfoResult(int);
        void signalSetUserInfoResult(int);
    public slots:
        void onSerUpdateInfoResult(int result);
        //void onBtnSaveUserInfoClicekd();
        //void onBtnEditClicked();
    protected:
        void IntWidgets();
       // void getUserInfo();
       // bool doodNameRule();
    private:
		QFormLayout* m_pInfoLayout;
		QWidget* m_UserInfoCommonWidget;
		QWidget* m_UserInfoCommiteeWidget;
		
		QHBoxLayout* m_pNameLayout;
		QVBoxLayout* m_pMainLayout;

		QWidget* m_FormWidget;

		QLabel*	m_pLabelName;    //����
		QLabel*	m_pLabelSex;    //�Ա�
		QLabel*	m_pLabelNation;  //����
		QLabel* m_pLabelunit;    //��λ
		QLabel* m_pLabeloffice;   //����
		QLabel* m_pLabelposition;  //ְλ

		QLabel*	m_pLabelsector;    //���
		QLabel*	m_pLabelgroup;  //����
		QLabel* m_pLabelspecialCommittee;    //רί��
		QLabel* m_pLabelspecialCommitteeDuty;   //רί��ְ��
		QLabel* m_pLabelcurrentPosition;  //����ְ��
		QLabel*	m_pLabelmyLocation;    //���ڵ�

		std::string type;  //�û����  0��ίԱ 1��������Ա
		QString	m_Name;
		QString	m_Sex;    //�Ա�
		QString	m_Nation;  //����
		QString	m_unit;    //��λ
		QString	m_office;   //����
		QString	m_position;  //ְλ

		QString	m_sector;    //���
		QString	m_group;  //����
		QString	m_specialCommittee;    //רί��
		QString	m_specialCommitteeDuty;   //רί��ְ��
		QString	m_currentPosition;  //����ְ��
		QString	m_myLocation;    //���ڵ�

        IUserControl_Ptr m_usercontrol;
        CSharedPtr<data::AccountInfo> m_userInfo;

        QGridLayout m_contentLayout;
        QVBoxLayout m_mainLayout;

    };
}


