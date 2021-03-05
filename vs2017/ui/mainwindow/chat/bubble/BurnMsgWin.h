#ifndef BURNMSGWIN_H
#define BURNMSGWIN_H
#include<QLabel>
#include <QPushButton>
#include <QMovie>
#include <QDialog>
#include <QTimer>
#include "data/ChatData.h"
#include "common/Controlptr.h"
#include "common/UIUtils.h"
#include "detail/clicklabel.h"
class RecordMessageWidget;
namespace ui{
	class UserInfoCommon;
	class UserInfoCommitee;

	class BurnImage :public ClickLabel{
		Q_OBJECT
	public:
		BurnImage(QWidget *parent,CSharedPtr<data::Msg>& msg);
		~BurnImage();
	signals:
		void signalSerDownloadImg(int err,const std::string&imgName,int64 tarid);
		void downloadImgFinish();
	public slots:
		void onSerDownloadImg(int err,const std::string&imgName,int64 tarid);
		void onViewBigImg();
	private:
		QString enctrptFile(std::string&url,std::string&encrptkey,FileDefaultPathType filepath,FileCachePathType cacheType);
		int64 mTargetId;
		IChatMgrControl_Ptr mChatCtrl;
		std::string mEncrptkey;
		QString mBigImgPath;
	};
	class BurnMsgWin : public QDialog
	{
		Q_OBJECT
	public:
		BurnMsgWin(QWidget *parent,CSharedPtr<data::Msg>& msg);
		~BurnMsgWin();
	protected:
		int burnTime(QString text);
	signals:
		void signalSerGetUserInfo(int, data::UserData&, int64 id, QString name, QString avatar);
		void startChat(CSharedPtr<data::ChatInfo>&);
	protected slots:
		void onBurnMsg();
		void onTimerInterval();
		void onSerGetUserInfo(int, data::UserData&, int64 id, QString name, QString avatar);
		void onSerShowUserInfo(int64 id, QString name, QString avatar);
		void onStartChat(CSharedPtr<data::ChatInfo>& chat);
	private:
		QWidget mCenterWidget;
		QLabel* mTime;
		QLabel* mClck;
		QMovie* mMovie;
		QPushButton*mBtnBurn;
		QTimer mTimer;
		int mBurnTime;
		CSharedPtr<data::Msg> m_msg;
		RecordMessageWidget* burnAudio;
		IChatMgrControl_Ptr			m_chatcontrol;
		CSharedPtr<UserInfoCommon> m_pUserInfoCommomWidget;
		CSharedPtr<UserInfoCommitee> m_pUserInfoCommiteeWidget;
	};
}

#endif // BURNMSGWIN_H
