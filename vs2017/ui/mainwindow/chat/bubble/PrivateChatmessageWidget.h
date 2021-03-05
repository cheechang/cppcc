#pragma once
#include "abstractmessagewidget.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
namespace ui{
	class ToolButton;
	class DecryptSetPassChatDialog;
	//class QStackedWidget;
	class PrivateChatmessageWidget:public AbstractMessageWidget
	{
		Q_OBJECT
	public:
		explicit PrivateChatmessageWidget(QWidget* parent = 0);
		~PrivateChatmessageWidget();

		void Init();
		void setTip(CSharedPtr<data::Msg>&msg);
		QSize suggestWidth(int width);
	public:
		void InitSerSetDecryptPass();
	signals:
		void signalSetDecryptKey(QString&);
	public slots:
		void onSerSetDecryptPass();
	private:
		CSharedPtr<ToolButton> m_ToolBtn;
		CSharedPtr<QVBoxLayout>m_Privatelayout;
		//QWidget* m_LockWidget;
	};
}

