#include "SystemSettingBasicArea.h"
#include<QGridLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QFormLayout>
#include <QPushButton>
#include <QSettings>
#include <QMessageBox>
#include "log.h"
#include <utils/Error.h>
#include <QButtonGroup>
#include "setSaveFileItem.h"
#include "../../common/Common.h"
namespace ui{
    #define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
    #define START_UP "startup"
	SystemSettingBasicArea::SystemSettingBasicArea(QWidget *parent)
		: TWidget(parent)
	{
		setObjectName("groupinfobackground");
		mMainLayout = new QVBoxLayout(this);
		mMainLayout->setContentsMargins(10,15,1,0);
		setLayout(mMainLayout);
		addFirendWayWidget();

		mUserControl = USERCONTROL;
        mChatControl = CHATMGRCONTROL;
		mAuthControl = AUTHCONTROL;

		CONNECT_SERVICE(GetPersonalData(int, std::vector<data::PersonalData>&));
		CONNECT_SERVICE(SetUserVerify(int));
        CONNECT_SERVICE(DeleteRecordsResult(int));
		CONNECT_SERVICE(GetUserSetInfo(int, data::UserInfoSetData&));

		if(mAuthControl)
		{
			if(mAuthControl->getIsRoming())
			{
				mCheckStartMsgRome->setChecked(true);
			}
		}
		if(mUserControl)
		{
			mUserControl->getUserSetting(0, CBind(&SystemSettingBasicArea::signalSerGetUserSetInfo,this, CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	SystemSettingBasicArea::~SystemSettingBasicArea()
	{

	}

	void SystemSettingBasicArea::addFirendWayWidget()
	{
		mBtnCanNotAdded = new QRadioButton(transfer("不允许任何人"),this);
		mBtnAnyOne = new QRadioButton(transfer("允许任何人"),this);
		mBtnNeedAgree = new QRadioButton(transfer("需要验证信息"),this);

		mBtnCanNotAdded->hide();
		mBtnAnyOne->hide();
		mBtnNeedAgree->hide();

		mBtnDoodNum = new QCheckBox(transfer("ID"), this);		
		mBtnDoodNum->setVisible(false);
		mBtnPhoneNum = new QCheckBox(transfer("手机号"), this);
		mBtnPhoneNum->setVisible(false);
		mBtnMailNum = new QCheckBox(transfer("邮箱"), this);
		mBtnMailNum->setVisible(false);

		connect(mBtnDoodNum, SIGNAL(stateChanged(int)), this, SLOT(onSetDoodNumSearchWay(int)));
		connect(mBtnPhoneNum, SIGNAL(stateChanged(int)), this, SLOT(onSetPhoneNumSearchWay(int)));
		connect(mBtnMailNum, SIGNAL(stateChanged(int)), this, SLOT(onSetMailNumSearchWay(int)));

        mCheBoxStartWay = new QCheckBox(transfer("开机时自启动"),this);
        connect(mCheBoxStartWay,SIGNAL(stateChanged(int)),this,SLOT(onCheckBoxStateChange(int)));
		mCheckStartMsgRome = new QCheckBox(transfer("开启消息漫游"), this);
		connect(mCheckStartMsgRome, SIGNAL(stateChanged(int)), this, SLOT(onCheckStartMsgRome(int)));


        mLabSplitLine = new QLabel(this);
        mLabSplitLine->setFixedSize(QSize(660,1));
        mLabSplitLine->setObjectName("SpliteLine");

        mLabClearLine = new QLabel(this);
        mLabClearLine->setFixedSize(QSize(660,1));
        mLabClearLine->setObjectName("SpliteLine");

		mLabSearchWay = new QLabel(this);
		mLabSearchWay->setFixedSize(QSize(660,1));
		mLabSearchWay->setObjectName("SpliteLine");

        mSaveFile = new setSaveFileItem(this);

		QLabel*addFriendWay = new QLabel(this);
		addFriendWay->setText(transfer("验证方式："));
		addFriendWay->hide();

        mBtnClearRecords = new QPushButton(this);
        mBtnClearRecords->setObjectName("sendbtn");
        mBtnClearRecords->setText(transfer("开始清空"));
        mBtnClearRecords->setFixedSize(128,24);

        connect(mBtnClearRecords,SIGNAL(clicked()),this,SLOT(onBtnClearRecordsClicked()));

		mBtnCanNotAdded->setCheckable(true);
		mBtnAnyOne->setCheckable(true);
		mBtnNeedAgree->setCheckable(true);

		QGridLayout* addFriendWayLayout = new QGridLayout(this);
		addFriendWayLayout->addWidget(addFriendWay,0,0,1,3);
		addFriendWayLayout->addWidget(mBtnAnyOne,1,0,1,1);
		addFriendWayLayout->addWidget(mBtnCanNotAdded,1,1,1,1);
		addFriendWayLayout->addWidget(mBtnNeedAgree,1,2,1,1);
		QWidget* widget = new QWidget(this);
		widget->setLayout(addFriendWayLayout);
		//mMainLayout->addWidget(widget);
        mMainLayout->addWidget(mLabSplitLine);
        mMainLayout->addSpacing(10);

        QFormLayout*  oneCkeckLayout = new QFormLayout();
        oneCkeckLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
        oneCkeckLayout->addRow(transfer("启动设置: "),mCheBoxStartWay);
		oneCkeckLayout->addRow(transfer("消息漫游："), mCheckStartMsgRome);
        oneCkeckLayout->addRow(transfer("清空聊天记录: "),mBtnClearRecords);
        oneCkeckLayout->setContentsMargins(10,5,20,0);
        oneCkeckLayout->setHorizontalSpacing(28);
        oneCkeckLayout->setFormAlignment(Qt::AlignRight|Qt::AlignTop);

        mMainLayout->addLayout(oneCkeckLayout);
        mMainLayout->addSpacing(10);
        mMainLayout->addWidget(mLabClearLine);
        mMainLayout->addSpacing(10);
        mMainLayout->addWidget(mSaveFile,0,Qt::AlignLeft);

		QLabel* SearchWay = new QLabel(this);
		SearchWay->setText(transfer("请选择允许别人查找您的方式："));
		SearchWay->setVisible(false);

		QVBoxLayout* vsearchwaylayout = new QVBoxLayout(this);
		QHBoxLayout* hsearchwaylayout = new QHBoxLayout(this);

		hsearchwaylayout->addWidget(mBtnDoodNum);
		hsearchwaylayout->addWidget(mBtnPhoneNum);
		hsearchwaylayout->addWidget(mBtnMailNum);
		//hsearchwaylayout->setSpacing(20);
		hsearchwaylayout->setContentsMargins(20,0,0,0);
		vsearchwaylayout->addWidget(SearchWay);
		vsearchwaylayout->addLayout(hsearchwaylayout);

		mMainLayout->addWidget(mLabSearchWay);
		mMainLayout->addSpacing(10);
		mMainLayout->addLayout(vsearchwaylayout);
		mMainLayout->addStretch();

		QButtonGroup* btnGroup = new QButtonGroup(this);
		btnGroup->addButton(mBtnNeedAgree,1);
		btnGroup->addButton(mBtnAnyOne,3);
		btnGroup->addButton(mBtnCanNotAdded,2);
		connect(btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(onButtonClicked(int)));
	}

	void SystemSettingBasicArea::reqVerificationMode()
	{
		if (mUserControl)
		{
            getStartUpSetting();
			std::vector<int16> types;
			types.push_back(4);//验证方式
			mUserControl->getPersonalData(types,CBind
				(&SystemSettingBasicArea::signalSerGetPersonalData,this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}


    void SystemSettingBasicArea::getStartUpSetting()
    {
        std::vector<std::string> keys;
        keys.push_back("startup");

        std::vector<data::UserLocalSetting> retData;
        bool isGet = mUserControl->getLocalSettingSync(keys,retData);
        if (retData.empty())
        {
            mCheBoxStartWay->setCheckState(Qt::Unchecked);
            data::UserLocalSetting set;
            set.key = "startup";
            set.val = "";

            std::vector<data::UserLocalSetting> vec;
            vec.push_back(set);

            bool ret = mUserControl->addLocalSettingSync(vec);
            AddLog(LOG_LEV_INFO,LOG_FILE,"add StartUP LocalSetting ret = %d",ret);
        }else{
            for (qint16 index = 0; index < retData.size(); ++index)
            {
                if (retData[index].key == std::string("startup"))
                {
                    QString sdMsg = QString::fromUtf8(retData[index].val.data());
                    sdMsg = sdMsg.replace(" ", "");
                    sdMsg = sdMsg.toLower();
                    if (sdMsg == "checked")
                    {
                        mCheBoxStartWay->setCheckState(Qt::Checked);
                    }else{
                        mCheBoxStartWay->setCheckState(Qt::Unchecked);
                    }
                }
            }
        }
    }

	void SystemSettingBasicArea::onSerGetPersonalData( int code, std::vector<data::PersonalData>&datas )
	{	
        for (int i =0 ; i< datas.size(); ++i)
        {
            if (datas.at(i).type == 4)
            {
                setAddWay(datas.at(i).val);
            }
        }
	}


    void SystemSettingBasicArea::setAddWay( int state)
    {
        //value : 1：需要验证信息, 2 : 不允许任何人添加, 3 : 允许任何人添加，默认1*/
        switch(state){
        case 1:{
            mBtnNeedAgree->setChecked(true);
            break;
               }
        case 2:{
            mBtnCanNotAdded->setChecked(true);
            break;
               }
        case 3:{
            mBtnAnyOne->setChecked(true);
            break;
           }
        }
    }

    void SystemSettingBasicArea::setStartUp( int state)
    {
        if (state ==  Qt::Checked)
        {
            mCheBoxStartWay->setChecked(true);
        }else{
           mCheBoxStartWay->setChecked(false);
    }
    }

	void SystemSettingBasicArea::onButtonClicked( int index )
	{
		std::vector<data::PersonalData> items;
		data::PersonalData item;
		item.type = 4;
		item.val = index;
		items.push_back(item);
		mUserControl->setPersonalData(items, CBind(&SystemSettingBasicArea::signalSerSetUserVerify, this, CPlaceholders  _1));
	}

	void SystemSettingBasicArea::onSerSetUserVerify( int code)
	{

	}

    void SystemSettingBasicArea::setAutoStart(bool is_auto_start)  
    {  
        QString application_name = QApplication::applicationName();
        QSettings *settings = new QSettings(REG_RUN, QSettings::NativeFormat);
        if(is_auto_start)  
        {  
            QString application_path = QApplication::applicationFilePath();  
            settings->setValue(application_name, application_path.replace("/", "\\"));
        }  
        else  
        {  
            settings->remove(application_name);
        }  
        delete settings;  
    }  

    void SystemSettingBasicArea::onCheckBoxStateChange( int state )
    {
        AddLog(LOG_LEV_INFO,LOG_FILE,"onCheckBoxStateChange = %d",state);
        std::string val("");
        if (state ==  Qt::Unchecked)
        {
            setAutoStart(false);//取消开机启动
            val = "unchecked";
        }else{
            if (state == Qt::Checked)
            {
                setAutoStart(true);//开机启动
                val = "checked";
            }
        }

        data::UserLocalSetting set;
        set.key = "startup";
        set.val = val;

        std::vector<data::UserLocalSetting> vec;
        vec.push_back(set);

        bool ret = mUserControl->updateLocalSettingSync(vec);
        AddLog(LOG_LEV_INFO,LOG_FILE,"update LocalSetting ret = %d",ret);
    }

    void SystemSettingBasicArea::onBtnClearRecordsClicked()
    {
        QMessageBox box(QMessageBox::Warning,transfer("提示"),transfer("确定删除聊天记录? "));
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
		box.setButtonText(QMessageBox::Ok, transfer("确 定"));
		box.setButtonText(QMessageBox::Cancel, transfer("取 消"));
        if (box.exec () == QMessageBox::Cancel)
            return;

        if (mChatControl)
        {
            mChatControl->deleteAllMessage(true,CBind(&SystemSettingBasicArea::signalSerDeleteRecordsResult,this,std::placeholders::_1));
        }
    }

    void SystemSettingBasicArea::onSerDeleteRecordsResult( int  err)
    {
        /*注释：
		*		删除记录成功，SDK会自动删除最近会话联系人，
		*		然后给PC一个更新最近会话联系人的推送
		*/
    if (err)
	{
        QString errMsg = QString::fromLocal8Bit(utils::Error::GetErrMsg(err).c_str());
        QMessageBox box;
        box.setText(errMsg);
        box.exec();
	}
    }

	void SystemSettingBasicArea::onCheckStartMsgRome(int state)
	{
		if(state == Qt::Checked)
		{
			if(mAuthControl)
			{
				mAuthControl->setIsRoming(1);
			}
		}
		else
		{
			if(mAuthControl)
			{
				mAuthControl->setIsRoming(0);
			}	
		}
	}

	void SystemSettingBasicArea::onSetDoodNumSearchWay(int state)
	{
		if(mUserControl != NULL)
		{
			if(state == Qt::Checked)
			{
				mUserControl->setSetting(0,3);
			}
			else
			{
				mUserControl->setSetting(1,3);
			}
		}
	}

	void SystemSettingBasicArea::onSetPhoneNumSearchWay(int state)
	{
		if(mUserControl != NULL)
		{
			if(state == Qt::Checked)
			{
				mUserControl->setSetting(0,4);
			}
			else
			{
				mUserControl->setSetting(1,4);
			}
		}
	}

	void SystemSettingBasicArea::onSetMailNumSearchWay(int state)
	{
		if(mUserControl != NULL)
		{
			if(state == Qt::Checked)
			{
				mUserControl->setSetting(0,5);
			}
			else
			{
				mUserControl->setSetting(1,5);
			}
		}
	}

	void SystemSettingBasicArea::onSerGetUserSetInfo(int code, data::UserInfoSetData& USetInfo)
	{

		if(USetInfo.isSearchByDoodNum == 0)
		{
			mBtnDoodNum->setChecked(true);
		}
		else
		{
			mBtnDoodNum->setChecked(false);
		}
		
		if(USetInfo.isSearchByPhoneNum == 0)
		{
			mBtnPhoneNum->setChecked(true);
		}
		else
		{
			mBtnPhoneNum->setChecked(false);
		}

		if(USetInfo.isSearchByMailNum == 0)
		{
			mBtnMailNum->setChecked(true);
		}
		else
		{
			mBtnMailNum->setChecked(false);
		}
	}
}
