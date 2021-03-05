#ifndef SYSTEMSETTINGBASICAREA_H
#define SYSTEMSETTINGBASICAREA_H
#include <QLabel>
#include <QWidget>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include "TWidget.h"
#include <common/Connect.h>
#include <common/Controlptr.h>
#include <data/UserData.h>
class QPushButton;
namespace ui{
    class setSaveFileItem;

	class SystemSettingBasicArea : public TWidget
	{
		Q_OBJECT

	public:
		SystemSettingBasicArea(QWidget *parent=CNull);
		void addFirendWayWidget();
		void reqVerificationMode();//获取验证信息
		~SystemSettingBasicArea();
	signals:
		void signalSerGetPersonalData(int, std::vector<data::PersonalData>&);
		void signalSerSetUserVerify(int);
        void signalSerDeleteRecordsResult(int);
		void signalSerGetUserSetInfo(int, data::UserInfoSetData&);

	protected slots:
        void onSerDeleteRecordsResult(int);
		void onSerGetPersonalData(int code, std::vector<data::PersonalData>&datas);
		void onButtonClicked(int index);
		void onSerSetUserVerify(int);
        void onCheckBoxStateChange(int state);
        void onBtnClearRecordsClicked();
		void onCheckStartMsgRome(int state);

		void onSetDoodNumSearchWay(int state);
		void onSetPhoneNumSearchWay(int state);
		void onSetMailNumSearchWay(int state);
		void onSerGetUserSetInfo(int code, data::UserInfoSetData& USetInfo);
    protected:
        void setAutoStart(bool isAutoRun);
        void setAddWay(int);
        void setStartUp(int);
        void getStartUpSetting();
	private:
		QRadioButton*mBtnNeedAgree;
		QRadioButton*mBtnAnyOne;
		QRadioButton*mBtnCanNotAdded;

		QCheckBox*	mBtnDoodNum;
		QCheckBox*	mBtnPhoneNum;
		QCheckBox*	mBtnMailNum;

        QLabel*      mLabSplitLine;
        QLabel*      mLabClearLine;
		QLabel*      mLabSearchWay;
        
        setSaveFileItem*   mSaveFile;
		 QCheckBox*   mCheBoxStartWay;
		QCheckBox*  mCheckStartMsgRome;
        QPushButton* mBtnClearRecords;
		QVBoxLayout* mMainLayout;

		IUserControl_Ptr mUserControl;
        IChatMgrControl_Ptr mChatControl;
		IAuthControl_Ptr mAuthControl;
	};
}
#endif // SYSTEMSETTINGBASICAREA_H
