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

		QLabel*	m_pLabelName;    //姓名
		QLabel*	m_pLabelSex;    //性别
		QLabel*	m_pLabelNation;  //民族
		QLabel* m_pLabelunit;    //单位
		QLabel* m_pLabeloffice;   //处室
		QLabel* m_pLabelposition;  //职位

		QLabel*	m_pLabelsector;    //界别
		QLabel*	m_pLabelgroup;  //组族
		QLabel* m_pLabelspecialCommittee;    //专委会
		QLabel* m_pLabelspecialCommitteeDuty;   //专委会职务
		QLabel* m_pLabelcurrentPosition;  //现任职务
		QLabel*	m_pLabelmyLocation;    //所在地

		std::string type;  //用户类别  0：委员 1：工作人员
		QString	m_Name;
		QString	m_Sex;    //性别
		QString	m_Nation;  //民族
		QString	m_unit;    //单位
		QString	m_office;   //处室
		QString	m_position;  //职位

		QString	m_sector;    //界别
		QString	m_group;  //组族
		QString	m_specialCommittee;    //专委会
		QString	m_specialCommitteeDuty;   //专委会职务
		QString	m_currentPosition;  //现任职务
		QString	m_myLocation;    //所在地

        IUserControl_Ptr m_usercontrol;
        CSharedPtr<data::AccountInfo> m_userInfo;

        QGridLayout m_contentLayout;
        QVBoxLayout m_mainLayout;

    };
}


