#pragma  once
#include <memory>
#include <QWidget>
#include <QPushButton>
#include <interface/Defines.h>
#include "common/controlptr.h"
#include "data/UserData.h"
#include "ServiceDefine.h"
#include "..\common\Common.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qmenu.h>
class QVBoxLayout;
class QLabel;
namespace ui{
	class ToolButton;
	class ChatTitle:public QWidget{
		Q_OBJECT
	public:
		explicit ChatTitle(QWidget *parent=CNull);
		virtual ~ChatTitle();
		void SetTitleText(QString& text,QString avatar="");

		void SetTargetInfo(TargetInfo &tagetInfo);
		void showAddBtn(int64 id,bool show);
		void setTopMsgVisible(bool isVisible);
		void setTopMsgContent(QString content);

		TargetInfo  m_curTargetInfo;
	protected:
		void paintEvent(QPaintEvent *event);
	signals:
		void signalSerMoretopMsg();
		void startChat(CSharedPtr<data::ChatInfo>&chat);
	protected slots:
		void onAddContact();
		void onDispGroup();

		void onShowMenu();
		void onShowDoc();
		void onShowSpeech();
		void onSerMsgTop(data::ZxTopInformation&);

		void onShowSpeechCount();
		void onShowSpeechSummary();

		void onShowEssenceArea(); /// 2020-4-16  读书群
		void onShowReadingDoc();

	private:
		CSharedPtr<QLabel> m_title;
		CSharedPtr<QWidget> m_spliter;
		CSharedPtr<ToolButton> m_btnAdd;
		CSharedPtr<QVBoxLayout> m_mainlayout;
		CSharedPtr<ToolButton> m_btnDispGroup;
		int64 mId;
		QString mAvatar;
		QString mLastSendTime;

		//CSharedPtr<QLabel> m_TopMsgTip;
		CSharedPtr<QLabel> m_newTopMsglblShow;
		CSharedPtr<QPushButton> m_moreTopMsg;
		QWidget* m_topmsgWidget;
		IGroupMgrControl_Ptr mGroupControl;

		int m_bBooking; // 是否是读书群
	public:
		QMenu* m_Menu;
		QAction* m_actionGounp;
		QAction* m_actionDoc;
		QAction* m_actionSpeech;
		QAction* m_actionSpeechCount;   // 2019-12-16
		QAction* m_actionSpeechSummary;

		QAction* m_actionEssenceArea; //读书群精华区 2020-4-16
		QAction* m_actionReadingDoc;  //读书群参阅资料
			
		
		QNetworkRequest* m_httpRequest;  // 2019-12-16
		QNetworkAccessManager* m_httpManager;

	public slots:
		void onHttpInfoRsp(QNetworkReply* preplay);


	//判断是否是booking	 
	public :
		QNetworkRequest* m_httpBookingRequest;  // 2020-4-15
		QNetworkAccessManager*  m_httpBookingManager;

	public slots:
		void onHttpInfoBookingRsp(QNetworkReply* preplay);

//判断是否是主题议政
	public:
		QNetworkRequest* m_httpSubjectRequest;  // 2020-4-20
		QNetworkAccessManager*  m_httpSubjectManager;

	public slots:
		void onHttpInfoSubjectRsp(QNetworkReply* preplay);
	};
}