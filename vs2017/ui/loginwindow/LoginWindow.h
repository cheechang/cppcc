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
		int m_bShowCheckFlag;  // ����Ƿ񵯳���.
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

		bool GetZZYVerifyCodeInfo(); //��ȡָ������֤��
		void UnicomLoginVerify(data::AuthInfo userinfo); //��ͨ��½��֤

		bool ZZYIdentityVerify(data::AuthInfo userinfo);  //ָ���������֤	
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
		void onLockedOutAccount();	 // �����źţ��߳�ת��
        void onActiveAccount();
		void onAccountLockedOut();   // �յ������ź�

		//http��������
		void onSerDealVerifyCode(QNetworkReply* preplay);
		void onSerIdVerifyRep(QNetworkReply* preplay);
		void onSerUnicomRepResult(QNetworkReply*);
		void onSerSaveAccount(int type, QString& pAccount);

		void onSerGetNextVerifyCode();      //��ȡ��һ����֤��
	private:
		IAuthControl_Ptr	m_pAuthCtrl;		//��֤�ӿ�ָ��
		QVBoxLayout*	m_pMainLayout;			//������
		QLabel*			m_pBackground;			//����ͼƬ
		QStackedLayout*	m_pInputLayout;			//��������л�����
		QWidget*		m_pAccountBackground;	//��¼������汳��
		QWidget*		m_pServerBackground;	//������������汳��
		QWidget*		m_pWaitingBackground;	//�ȴ���¼�������
		QHBoxLayout*	m_pTitleBtnLayout;		//��������ť����
		QGridLayout*	m_pAccountLayout;		//��¼������沼��

		QHBoxLayout*    m_pSerBackgroundLayout; //������ҳ�沼��
		QVBoxLayout*    m_pLoginTypeLayout;		//��������¼��ʽ����
		QVBoxLayout*	m_pServerLayout;		//������ѡ����沼��

		PushButton*		m_pMinButton;			//��С��
		PushButton*		m_pCloseButton;			//�ر�
		HeadImage*		m_pAvatar;				//ͷ��
		//QComboBox*		m_pAccountInput;		//�˺�����
		QLineEdit*		m_pAccountInput;		//�˺�����
		QLineEdit*		m_pPasswordInput;		//��������

		QLineEdit*      m_pVerifyNumInput;      //��֤������
		ElidedLabel*    m_pShowVerifyBtn;       //��֤��ͼƬչʾ
		//QPushButton*    m_pShowVerifyBtn;

		QCheckBox*		m_pRememberCheck;		//��ס����
		QCheckBox*		m_pAutoLoginCheck;		//�Զ���¼
		QPushButton*	m_pRegisterButton;		//ע���˺�
		QPushButton*	m_pForgetButton;		//��������

		QPushButton*	m_pLoginButton;			//��¼��ť
		PushButton*		m_pSwitchButton;		//�л���ť
		QLabel*			m_pServerLabel;
		QLineEdit*		m_pServerInput;			//CHAT����������

		QLabel*			m_pServerLabelWeb;
		QLineEdit*		m_pServerInputWeb;		//WEB����������


		MyQComboBox*	m_pCountryCombo;		//����ѡ��

		MyQComboBox*	m_pLoginTypecombo;		//��¼��ʽ����
		QLabel*			m_pLoginTypeLabel;      //��¼��ʽ����

		HeadImage*		m_pLoadingAvatar;		//��¼�ȴ�����ͷ��
		QPushButton*	m_pAbortButton;			//ȡ����¼��ť
		TipWidget*		m_pLoginResultTip;		//��¼ʧ�ܷ�����Ϣ

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

		QString m_VerifyRandData;   //�����

		data::AuthInfo authInfo;


		void GetNewVerifyCodeInfo(QString userName);
		bool IdentityNewVerify(data::AuthInfo userinfo);
		bool getAccessInfo();


		QNetworkRequest* m_accessRrequest;
		QNetworkAccessManager* m_accessManager;
	public slots:
		void onIdentityNewVerifyRsp(QNetworkReply* preplay);
		void onAccessInfoRsp(QNetworkReply* preplay);

		////�绰����
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


	/// ��������APP��˳��������λ��
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


	QLabel*		m_pLoginWaittingInfo;      //��½�ڼ���ʾ����Ϣ

	};
}

