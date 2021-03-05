#include "AccountComboBox.h"


namespace ui {
	AccountComboBox::AccountComboBox(QWidget* parent)
		: QComboBox(parent)
	{
		m_pAccountInput = std::make_shared<QLineEdit>(this);
		
		m_pAccountInput->setContextMenuPolicy(Qt::NoContextMenu);
		this->setLineEdit(m_pAccountInput.get());
	}


	AccountComboBox::~AccountComboBox(void)
	{
	}

	void AccountComboBox::setPlaceholderText(const QString text)
	{
		m_pAccountInput->setPlaceholderText(text);
	}

	void AccountComboBox::setMaxLength(const unsigned int length)
	{
		m_pAccountInput->setMaxLength(length);
	}
}
