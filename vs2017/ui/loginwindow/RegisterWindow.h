#pragma once
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <qcombobox.h>
#include <qformlayout.h>
#include "../contact/createGroup/BaseWindow.h"
#include "common/controlptr.h"
class QHBoxLayout;
class QTimer;
class QPushButton;
namespace ui{
	class TipWidget;
	class RegisterWindow : public BaseWindow
	{
		Q_OBJECT;
	public:
		RegisterWindow(void);
		~RegisterWindow(void);
signals:
		void signalSignResult(std::string& ser, std::string& account, std::string& pwd);
		void signalGetVerifyCode(int code,int outTime);
		void signalRegisterResult(int coode,int);
	public slots:
		void onGetVerifyCode(int code,int outTime);
		void onTimerOut();
		void onRegisterResult(int coode,int code);
		void onGetVerifyCodeClicked();
		void onBtnSingUPClicked();
		
	protected:
		void initUI();
		bool validityChecking();
	private:
		QLineEdit*   m_editServer;
		QLabel*      m_labServer;

		QComboBox*	 m_comContryArea;
		QLineEdit*   m_editPhone;
		QLabel*		 m_labPhone;

		QLineEdit*   m_editUserName;
		QLabel*		 m_labUserName;

		QLineEdit*   m_editPassword;
		QLabel*		 m_labPassword;

		QLineEdit*   m_editConfirm;
		QLabel*		 m_labConfirm;

		QLineEdit*	 m_editVerifyCode;
		QPushButton*  m_btnGetCode;

		QPushButton*  m_btnSingUp;

		QPushButton*       m_btnCancel;

		QHBoxLayout*     m_getCodeLayout;
		TipWidget*       m_loginResultTip;
		QFormLayout*     m_formLayout;
		QWidget*		 m_MainLayoutWidget;
		IAuthControl_Ptr    m_authcontrol;
		int				 m_time;
		QTimer*			 m_qTimer;
	};
}