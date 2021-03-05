#pragma once
#include "QWidget"
#include "../contact/createGroup/BaseWindow.h"
#include "common/controlptr.h"


class QLineEdit;
class QLabel;
class QPushButton;
class QVBoxLayout;
class QTimer;

namespace ui{

	class TipWidget;
	class LockoutAccount :  public BaseWindow
	{
		Q_OBJECT;
	public:
		LockoutAccount(std::string account);
		~LockoutAccount(void);
		void InitWidgets();
	signals:
		void signalLockout();
		void signalDoLockoutResult(int err, const std::string codeUrl);
		void signalSerGetVerifyCode(int err, const std::string codeUrl);
	public slots:
		void onSerGetNextImage();
		void onSerLockoutResult(int err, const std::string codeUrl);
		void onBtnLockOutClicekd();
		void onSerGetVerifyCode(int err, const std::string codeUrl);

	protected:
		void DoVerifyCode(std::string account);
	private:
		 std::string         m_strAccount;
		CSharedPtr<QLabel>   m_labTitleMsg;
		CSharedPtr<QLineEdit> m_editCodeInput;
		CSharedPtr<QLabel>   m_labCodeImage;
		CSharedPtr<QPushButton> m_btnNextImage;
		CSharedPtr<QPushButton>  m_btnOk;
		CSharedPtr<QVBoxLayout>   m_mainLayout;
		CSharedPtr<TipWidget>     m_errTip;

		IAuthControl_Ptr     m_authcontrol;

	};

}


