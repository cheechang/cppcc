#pragma once
#include <core/BaseDialog.h>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QSystemTrayIcon>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "common/Controlptr.h"
#include "../controls/ElidedLabel.h"
 
namespace ui{
	class TipWidget;
	class HeadImage;
	class PushButton;
	class RegisterWindow;
	class LockoutAccount;
    class ActivationAccount;
    class MyQComboBox;
	class ThirdVerifyWidget;
	class DownloadDialog;
	class MyUpdateWindow : public QWidget
	{
		Q_OBJECT
	public:

		MyUpdateWindow(void);
		~MyUpdateWindow(void);
		DownloadDialog *m_downloadDlg;
	public:
		void GetVersionInfo();
		QNetworkAccessManager *m_httpManager;
		QNetworkRequest       *m_httRrequest;
		int m_bShowCheckFlag;  // 检查是否弹出框.
	public slots:
		void onSerUnicomRepResult(QNetworkReply* preplay);

	};
 
	class LoginWindow :
		public BaseDialog
	{
		Q_OBJECT
	public:
		LoginWindow(void);
		~LoginWindow(void);
	

		

	protected:
		virtual void mouseReleaseEvent(QMouseEvent* event);
		virtual void paintEvent(QPaintEvent *event);
		
	private:
		void onGetSecUrlResult(const std::string& url,
			const std::string postfix);
		void onAbortLoginResult(const int err);
		void initWidget(void);
		void setAttribute(void);
		void layout(void);
		void setConnections(void);
		void setPreviousLoginInfo(void);
		void loginAnimation(void);
		void loginAccount();

	signals:
		void loginSuccess(void);
		void showLoginResultTip(QString);
		void swithAccountUI(QWidget *);
		void lockoutAccount();
        void activeAccount();
		void signalSerLoginResult(int err, long long userID,
			const std::string& errStr);
	protected:
		bool eventFilter(QObject *obj, QEvent *event);
		void setLoginType();
		data::AuthInfo getLoginAccount();
		void setUserEditRegExp(int type);
        void LockedProcess(data::AuthInfo auth);
        void UnLockedProcess();

		bool GetZZYVerifyCodeInfo(); //获取指掌易验证码
		void UnicomLoginVerify(data::AuthInfo userinfo); //联通登陆验证

		bool ZZYIdentityVerify(data::AuthInfo userinfo);  //指掌易身份验证	
		void SetLoginInfo();
	public slots:
		void onSerLoginResult(int err, long long userID,
			const std::string& errStr);
		void onLoginBtnClicked(void);
		void onShowLoginResultTip(QString tipText);
		void onSwitchButtonClicked(void);
		void onRegisterBtnClicked(void);
		void onForgetBtnClicked(void);
		void onRememberCheckChanged(bool checked);
		void onAutoLoginCheckChanged(bool checked);
		void onAbortBtnClicked(void);
		void onIconIsActived(QSystemTrayIcon::ActivationReason reason);
		void onCurrentIndexChanged(QString name);
		void onServerLineditFinishi();
		void onServerLineditFinishiWeb();
		void onSerSignResult(std::string& ser, std::string& account, std::string& pwd);
		void onCloseClicked();
        void onPasswordHasChanged(QString pwd);
		void onLockedOutAccount();	 // 发送信号，线程转换
        void onActiveAccount();
		void onAccountLockedOut();   // 收到解锁信号

		//http请求数据
		void onSerDealVerifyCode(QNetworkReply* preplay);
		void onSerIdVerifyRep(QNetworkReply* preplay);
		void onSerUnicomRepResult(QNetworkReply*);
		void onSerSaveAccount(int type, QString& pAccount);

		void onSerGetNextVerifyCode();      //获取下一张验证码
	private:
		IAuthControl_Ptr	m_pAuthCtrl;		//认证接口指针
		QVBoxLayout*	m_pMainLayout;			//主布局
		QLabel*			m_pBackground;			//背景图片
		QStackedLayout*	m_pInputLayout;			//输入界面切换布局
		QWidget*		m_pAccountBackground;	//登录输入界面背景
		QWidget*		m_pServerBackground;	//服务器输入界面背景
		QWidget*		m_pWaitingBackground;	//等待登录结果背景
		QHBoxLayout*	m_pTitleBtnLayout;		//标题栏按钮布局
		QGridLayout*	m_pAccountLayout;		//登录输入界面布局

		QHBoxLayout*    m_pSerBackgroundLayout; //服务器页面布局
		QVBoxLayout*    m_pLoginTypeLayout;		//服务器登录方式布局
		QVBoxLayout*	m_pServerLayout;		//服务器选择界面布局

		PushButton*		m_pMinButton;			//最小化
		PushButton*		m_pCloseButton;			//关闭
		HeadImage*		m_pAvatar;				//头像
		//QComboBox*		m_pAccountInput;		//账号输入
		QLineEdit*		m_pAccountInput;		//账号输入
		QLineEdit*		m_pPasswordInput;		//密码输入

		QLineEdit*      m_pVerifyNumInput;      //验证码输入
		ElidedLabel*    m_pShowVerifyBtn;       //验证码图片展示
		//QPushButton*    m_pShowVerifyBtn;

		QCheckBox*		m_pRememberCheck;		//记住密码
		QCheckBox*		m_pAutoLoginCheck;		//自动登录
		QPushButton*	m_pRegisterButton;		//注册账号
		QPushButton*	m_pForgetButton;		//忘记密码

		QPushButton*	m_pLoginButton;			//登录按钮
		PushButton*		m_pSwitchButton;		//切换按钮
		QLabel*			m_pServerLabel;
		QLineEdit*		m_pServerInput;			//CHAT服务器输入

		QLabel*			m_pServerLabelWeb;
		QLineEdit*		m_pServerInputWeb;		//WEB服务器输入


		MyQComboBox*	m_pCountryCombo;		//国家选择

		MyQComboBox*	m_pLoginTypecombo;		//登录方式设置
		QLabel*			m_pLoginTypeLabel;      //登录方式提醒

		HeadImage*		m_pLoadingAvatar;		//登录等待界面头像
		QPushButton*	m_pAbortButton;			//取消登录按钮
		TipWidget*		m_pLoginResultTip;		//登录失败返回信息

		RegisterWindow*	m_registerWin;
		std::list<data::LoginType>    m_listType;
		data::LoginType				  m_curentLoginType;
		data::AuthInfo				  m_authInfo;
		int mRanddata;

		CSharedPtr<LockoutAccount>	  m_lockoutAccount;
        CSharedPtr<ActivationAccount> m_activeAccount;

		QNetworkAccessManager *m_httpManager;
		QNetworkAccessManager *m_httpManagerIdVerify;
		QNetworkReply* m_httpReply;
		QNetworkRequest* m_httRrequest;
		QNetworkRequest* m_httRrequestIdVerify;

		QString m_VerifyRandData;   //随机数

		data::AuthInfo authInfo;


		void GetNewVerifyCodeInfo(QString userName);
		bool IdentityNewVerify(data::AuthInfo userinfo);
		bool getAccessInfo();


		QNetworkRequest* m_accessRrequest;
		QNetworkAccessManager* m_accessManager;
	public slots:
		void onIdentityNewVerifyRsp(QNetworkReply* preplay);
		void onAccessInfoRsp(QNetworkReply* preplay);

		////电话号码
	public:
		QLabel *m_telephone;
		QNetworkRequest* m_telePhoneRrequest;
		QNetworkAccessManager* m_telePhoneManager;
		void getTelePhoneInfo(void);
	public slots:
		void ontelePhoneRsp(QNetworkReply* preplay);
 
	public:
		void saveMyConfig();
		void loadMyConfig();


	/// 根据排序APP的顺序重新排位置
	public:
	///	QNetworkRequest* m_AppSortRrequest;
	////	QNetworkAccessManager* m_AppSortManager;
	///	void getAppSortInfo(void);
	
	////public slots:
		////void onAppSortRsp(QNetworkReply* preplay);
	public:
		QString m_LoginMode;
	public:
		void login_ext();


	QLabel*		m_pLoginWaittingInfo;      //登陆期间提示的信息

	};
}

