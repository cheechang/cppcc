#pragma once
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <interface/Defines.h>
#include "../contact/createGroup/BaseWindow.h"
class QHBoxLayout;
class QVBoxLayout;
namespace ui{
	class PushButton;
	class SetSecretChatDialog:public BaseWindow
	{
		Q_OBJECT
	public:
		explicit SetSecretChatDialog(QWidget *parent =CNull);
		virtual ~SetSecretChatDialog();		
		void Init();
	signals:
		void signalSetPrivateKey(QString&);
		void signalCancelSet();
		void signalclose();
	public slots:
		void onPlainOrcipher();
		void onAckBtnClicked();
		void onCancelBtnClicked();
		void onclose();
	private:
		CSharedPtr<QHBoxLayout> SetPasswordLayout;
		CSharedPtr<QLineEdit> m_PasswordEdit;
		CSharedPtr<PushButton> m_PlainOrcipher;
		CSharedPtr<QLabel> m_WarningMsg;
		CSharedPtr<QPushButton> m_AckBtn;
		CSharedPtr<QPushButton> m_CancelBtn;
		CSharedPtr<QHBoxLayout> m_btnlayout;
		CSharedPtr<QHBoxLayout> m_Warninglayout;
		CSharedPtr<QVBoxLayout> m_Reslayout;
		
		//IChatMgrControl_Ptr mChatCtrl;
	};
}

