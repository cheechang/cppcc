#include "BurnMsgWin.h"
#include <QVBoxLayout>
#include "../../controls/ChatEdit.h"
#include "common/Connect.h"
#include "../../imageBrowser/ImageBrowser.h"
#include "RecordMessageWidget.h"
#include "CardMessageWidget.h"
#include "controls/UserInfoCommon.h"
#include "controls/UserInfoCommitee.h"
#include "json.h"
#include <log.h>
namespace ui{
	BurnMsgWin::BurnMsgWin(QWidget *parent,CSharedPtr<data::Msg>& msg)
		: QDialog(parent), m_msg(CNull), burnAudio(CNull)
	{
		Qt::WindowFlags flags = this->windowFlags();
		flags |= Qt::Popup;
		flags |= Qt::WindowStaysOnTopHint;
		this->setWindowFlags(flags);
		this->setObjectName("BurnMsgWin");

		m_chatcontrol = CHATMGRCONTROL;
		
		mCenterWidget.setParent(this);
		mCenterWidget.setObjectName("BurnMsgWinCenterWidget");
		mCenterWidget.setFixedSize(320,410);
		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->addWidget(&mCenterWidget,0,Qt::AlignCenter);
		
		mClck = new QLabel(this);
		mMovie = new QMovie(this);
		mBtnBurn = new QPushButton(this);
		mTime = new QLabel(this);

		mBurnTime = 20;
		connect(&mTimer,SIGNAL(timeout()),this,SLOT(onTimerInterval()));
		mTime->setText(transfer("倒计时 ")+QString::number(mBurnTime));
		mTimer.setInterval(1000);

		QWidget* contextWidget = new QWidget(this);;
		QVBoxLayout* contentLayout = new QVBoxLayout(contextWidget);
		contextWidget->setLayout(contentLayout);
		if (msg && msg->msgType == data::MSG_TYPE_TEXT)
		{
			mBurnTime = burnTime(QString::fromUtf8(msg->body.c_str()));
			ChatEdit* chatEdit = new ChatEdit(this);
			chatEdit->setReadOnly(true);
			chatEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
			chatEdit->setText(QString::fromUtf8(msg->body.c_str()));
			//contextWidget = chatEdit;
			contentLayout->addWidget(chatEdit, 0, Qt::AlignCenter);
			mTimer.start();
		}else if(msg && msg->msgType == data::MSG_TYPE_IMG){
			BurnImage* burnImg = new BurnImage(this,msg);
			connect(burnImg,SIGNAL(downloadImgFinish()),&mTimer,SLOT(start()));
			//contextWidget = burnImg;
			contentLayout->addWidget(burnImg, 0, Qt::AlignCenter);
			mBtnBurn->setEnabled(false);
		}else if(msg && msg->msgType == data::MSG_TYPE_AUDIO){
			m_msg = msg;
			burnAudio = new RecordMessageWidget(this);
			msg->isRecvMsg = true;
			burnAudio->SetRecordMsg(msg);
			connect(burnAudio,SIGNAL(startPlay()),&mTimer,SLOT(start()));
			//contextWidget = burnAudio;
			contentLayout->addWidget(burnAudio, 0, Qt::AlignCenter);
			mBurnTime = ((data::MsgAudio*)msg.get())->mediaTime/1000;
			mTime->setText(transfer("倒计时 ")+QString::number(mBurnTime));
			burnAudio->setFixedSize(120,30);
			mBtnBurn->setEnabled(false);
		}
		else if (msg && msg->msgType == data::MSG_TYPE_CARD)
		{
			CardMessageWidget* burnCard = new CardMessageWidget(this);
			burnCard->setIsBurnCard(true);
			connect(burnCard, SIGNAL(signalSerShowUserInfo(int64, QString, QString)), this, SLOT(onSerShowUserInfo(int64, QString, QString)));
			burnCard->setCardMsg(msg);
			contentLayout->addWidget(burnCard,0,Qt::AlignCenter);
			mTimer.start();
		}

		connect(mBtnBurn,SIGNAL(clicked(bool)),this,SLOT(onBurnMsg()));
		mClck->setMovie(mMovie);
		mMovie->setFileName(":/chat/clock-gif");
		mMovie->start();
		mBtnBurn->setText(transfer("立即焚烧"));
		mBtnBurn->setMinimumSize(120,30);

		mBtnBurn->setObjectName("sendbtn");
		mTime->setObjectName("BurnLbl");

		QVBoxLayout* layout = new QVBoxLayout(this);
		if(msg && msg->msgType == data::MSG_TYPE_AUDIO){
			layout->addStretch();
		}
        layout->addWidget(contextWidget,0,Qt::AlignCenter);
		layout->addStretch();
		layout->addWidget(mClck,0,Qt::AlignHCenter);
		layout->addWidget(mTime,0,Qt::AlignHCenter);
		layout->addWidget(mBtnBurn,0,Qt::AlignHCenter);
		mCenterWidget.setLayout(layout);

		CONNECT_SERVICE(GetUserInfo(int, data::UserData&, int64, QString, QString));
	}

	BurnMsgWin::~BurnMsgWin()
	{

	}

	void BurnMsgWin::onBurnMsg()
	{
		if (m_msg && m_msg->msgType == data::MSG_TYPE_AUDIO)
		{
			burnAudio->stopPlay();
			if (burnAudio)
			{
				delete burnAudio;
				burnAudio = CNull;
			}
			m_msg = CNull;
		}
		
		mTimer.stop();
		close();
	}

	int BurnMsgWin::burnTime( QString text )
	{
		int len = text.length();
		if (len == 0){
			return 2;
		}else if (len < 20){
			return 5;
		}else if (len < 40){
			return 10;
		}else if (len < 60){
			return 15;
		}else{
			return 20;
		}
	}

	void BurnMsgWin::onTimerInterval()
	{
		if (!mBtnBurn->isEnabled())
		{
			mBtnBurn->setEnabled(true);
		}
		mBurnTime -= 1;
		mTime->setText(transfer("倒计时 ")+QString::number(mBurnTime));
		if (mBurnTime == 0)
		{
			onBurnMsg();
		}
	}

	void BurnMsgWin::onSerShowUserInfo(int64 id, QString name, QString avatar)
	{
		m_chatcontrol->getUserInfo(id, 0, std::bind(&BurnMsgWin::signalSerGetUserInfo, this, std::placeholders::_1, std::placeholders::_2, id, name, avatar));
	}

	void BurnMsgWin::onSerGetUserInfo(int code, data::UserData& userinfo, int64 id, QString name, QString avatar)
	{
		std::string type("");
		std::string jsonstr = userinfo.entExtends.value();
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(jsonstr, root);
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
		AddLog(LOG_LEV_DEBUG, "exters=%s", userinfo.entExtends.value().c_str());
		if (type == "1")
		{
			m_pUserInfoCommomWidget = CMakePtr<UserInfoCommon>(this);
			connect(m_pUserInfoCommomWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
				this, SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommomWidget->setInfo(id, name, avatar, userinfo.entExtends.value());
			m_pUserInfoCommomWidget->show();
		}

		if (type == "0")
		{
			m_pUserInfoCommiteeWidget = CMakePtr<UserInfoCommitee>(this);
			connect(m_pUserInfoCommiteeWidget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
				this, SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
			m_pUserInfoCommiteeWidget->setInfo(id, name, avatar, userinfo.entExtends.value());
			m_pUserInfoCommiteeWidget->show();
		}

	}

	void BurnMsgWin::onStartChat(CSharedPtr<data::ChatInfo>& chat)
	{
		emit startChat(chat);
		onBurnMsg();
	}


	BurnImage::~BurnImage()
	{

	}

	BurnImage::BurnImage( QWidget *parent,CSharedPtr<data::Msg>& msg ):ClickLabel(parent)
	{
		mChatCtrl = CHATMGRCONTROL;
		CONNECT_SERVICE(DownloadImg(int,const std::string&,int64));
		connect(this,SIGNAL(clicked()),this,SLOT(onViewBigImg()));
		setToolTip(transfer("点击查看大图"));
		setPixmap(QPixmap(DEFAULT_PICTURE));
		setCursor(Qt::PointingHandCursor);
		if (msg)
		{
			data::MsgImg* msgImg = (data::MsgImg*)msg.get();
			mTargetId = msgImg->targetId;
			mEncrptkey = msgImg->encryptKey;
			mChatCtrl->DownLoadImage(msg->targetId,msgImg->mainUrl,CBind(&BurnImage::signalSerDownloadImg,this,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3));
		}
	}

	void BurnImage::onSerDownloadImg( int err,const std::string&imgName,int64 tarid )
	{
		if (mTargetId == tarid)
		{
			std::string url = imgName;
			QString path = enctrptFile(url,mEncrptkey,DATAPATH_USERIMG,DATACACHEPATH_USERIMG); 
			mBigImgPath = path;
			this->setPixmap(QPixmap(path));
			emit downloadImgFinish();
		}
	}
	QString BurnImage::enctrptFile(std::string&url,std::string&encrptkey,FileDefaultPathType filepath,FileCachePathType cacheType){

		QString path = UIUtils::GetDataFullPath(filepath)+QString::fromUtf8(url.data());
		QString destPath = UIUtils::GetDataFullPath(cacheType)+UIUtils::GetNameByUrl(QString::fromUtf8(url.data()));
		if ( UIUtils::IsFileExist(path) && !encrptkey.empty())
		{
			bool bret = mChatCtrl->decryptFile(encrptkey,path.toUtf8().data(),destPath.toUtf8().data());
			if ( !bret)
			{
				destPath="";
			}
		}
		else{
			destPath = path;
		}
		return destPath;
	}

	void BurnImage::onViewBigImg()
	{
		QList<QString>imgs;
		imgs.push_back(mBigImgPath);
		ui::ImageBrowser::Instance()->setImgs(imgs,0);
		ui::ImageBrowser::Instance()->showWin();
	}

}