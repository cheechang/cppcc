#include "RemarkWindow.h"
#include "../../../common/Common.h"

namespace ui
{
	RemarkWindow::RemarkWindow(QWidget *parent): BaseWindow(parent)
	{
		setTitle(transfer("修改备注"));
		m_pEdit = new QLineEdit(this);
		m_pButton = new QPushButton(this);
		m_pButton->setObjectName("sendbtn");
		m_pButton->setText(transfer("确定"));
		m_pButton->setMinimumSize(60, 20);
		m_pEdit->setMaxLength(15);
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->addWidget(m_pEdit);
		layout->addWidget(m_pButton);
		layout->setContentsMargins(10, 10, 10, 10);

		QWidget* widget = new QWidget(this);
		widget->setLayout(layout);
		mMainLayout->addWidget(widget);
		mMainLayout->setContentsMargins(10, 10, 10, 10);

		connect(this, SIGNAL(closeClicked()), this, SLOT(reject()));
		connect(m_pButton, SIGNAL(clicked()), this, SLOT(accept()));
	}

	RemarkWindow::~RemarkWindow()
	{
	}

	int RemarkWindow::showWin(QString& remark)
	{
		int ret = this->exec();
		remark = m_pEdit->text();
		return ret;
	}
}
