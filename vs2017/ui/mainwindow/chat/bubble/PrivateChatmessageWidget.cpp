#include "PrivateChatmessageWidget.h"
#include <QLabel>
#include <QTextEdit>
#include "data/ChatData.h"
#include "../../../controls/ToolButton.h"
#include "DecryptSetPassChatDialog.h"

namespace ui
{
	PrivateChatmessageWidget::PrivateChatmessageWidget(QWidget *parent)
		: AbstractMessageWidget(parent)
	{
		Init();
	}

	PrivateChatmessageWidget::~PrivateChatmessageWidget()
	{
	}

	void PrivateChatmessageWidget::Init()
	{	

		m_ToolBtn = CMakePtr<ToolButton>(":/chat/MsgLoack",this);
		m_ToolBtn->setFixedSize(40,40);
		this->setFixedSize(60,50);
		setCentralWidget(m_ToolBtn.get());
		connect(m_ToolBtn.get(),SIGNAL(clicked()), this, SLOT(onSerSetDecryptPass()));	
	}

	void PrivateChatmessageWidget::setTip(CSharedPtr<data::Msg>&msg)
	{
		AbstractMessageWidget::setMsg(msg);
	}

	void PrivateChatmessageWidget::InitSerSetDecryptPass()
	{
				
	}

	void PrivateChatmessageWidget::onSerSetDecryptPass()
	{
		if (mRightMenuEnabled)
		{
			CSharedPtr<DecryptSetPassChatDialog> m_DecryDialog;
			m_DecryDialog = CMakePtr<DecryptSetPassChatDialog>();
			connect(m_DecryDialog.get(), SIGNAL(signalSetDecryptKey(QString&)), this, SIGNAL(signalSetDecryptKey(QString&)));
			m_DecryDialog->exec();
		}
	}

	QSize PrivateChatmessageWidget::suggestWidth(int width)
	{
		return this->sizeHint();
	}

}